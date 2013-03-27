require 'codegen'
require 'codegen/attributes'
require 'codegen/id'
require 'codegen/dart'
require 'place'
require 'pp'
require 'tenjin'

include Codegen

module Codegen::Dart

  HERE = Pathname.new(File.expand_path(__FILE__)).parent
  @@engine = Tenjin::Engine.new(:path => [ HERE + 'dart_tmpl' ])

  def name_ctor(ctor_name)
    case ctor_name
    when String
      make_id(ctor_name)
    when Symbol
      make_id(ctor_name)
    when TrueClass
      make_id(:full)
    else
      raise ArgumentError, "ctor name must be one of [String, Symbol, true] not #{ctor_name} of #{ctor_name.class}"
    end
  end      

  module Accessible
    extend Attributes
    attr_accessor :public
  end

  class Member
    extend Attributes
    include Accessible
    attr_accessor :owner
    attribute_defaults({ :public => false, :id => nil, :type => nil, 
                         :access => :ia, :vname => nil, :name => nil,
                         :init => nil, :ctor => nil, :ctor_opt => nil,
                         :ctor_named => nil, :descr => nil, :final => nil,
                         :map_value_type => nil, :list_value_type => nil,
                       })

    def initialize(opts={ })
      set_attributes(opts)
      @id = instantiate(method(:make_id), id)
      @type = 'dynamic' if not @type
      @map_value_type = $2 if type =~ /Map<\s*(\w+),\s*(\w+)\s*>/
      @list_value_type = $1 if type =~ /List<\s*(\w+)\s*>/

      @name = id.camel
      if @public
        @vname = @name
      else
        @vname = '_'+@name
      end

      def ctor_maker(ctor)
        result = []
        if ctor
          case ctor
          when Array
            result = ctor.map {|c| name_ctor(c) }
          else
            result = [name_ctor(ctor)]
          end
        end
      end

      @ctor = ctor_maker(@ctor)
      @ctor_opt = ctor_maker(@ctor_opt)
      @ctor_named = ctor_maker(@ctor_named)
    end

    def final_tag
      final ? "final " : ""
    end

    def readable
      return ((access == :ro) or (access == :rw))
    end

    def writable
      return access == :rw
    end

    def class_map
      return owner.class_map
    end
    
    def as_arg
      return "#{type} #{name}"
    end

    def opt_initializer?
      return (has_init? and not init_is_const?)
    end

    def has_init?
      return (not init.nil?)
    end

    def as_opt_arg
      return init_is_const? ? "#{type} this.#{vname}=#{init}" : (init.nil? ? "#{type} this.#{vname}":"#{type} #{name}")
    end

    def as_named_arg
      return init_is_const? ? "#{type} this.#{vname}:#{init}" : (init.nil? ? "#{type} this.#{vname}":"#{type} #{name}")
    end

    def arg_requires_check?
      return ((not init.nil?) and (not init_is_const?))
    end


    def init_is_const?
      return false if init.nil?
      case init
      when Float
        return true
      when Fixnum
        return true
      when Bignum
        return true
      when /['"].*['"]/
        return true
      else
        return false
      end
    end

    def enum_map
      return owner.enum_map
    end

    def json_out()
      if type=='DateTime'
        return "'${#{vname}.toString()}'"
      elsif class_map.include? type
        return "#{vname}.toJson()"
      else
        return vname
      end
    end    

    def json_in()
      if type=='DateTime'
        return %Q{DateTime.parse(jsonMap["#{name}"])}
      elsif class_map.include?(type) 
        return %Q{#{type}.fromJsonMap(jsonMap["#{name}"])}
      elsif enum_map.include?(type)
        return %Q{#{type}.fromJson(jsonMap["#{name}"])}
      elsif type =~ /Map<\s*(\w+),\s*(\w+)\s*>/
        key, value = $1, $2
        #return "#{vname}.forEach((k,v) => #{key} => #{value})"
        return "makeJsonMap(#{vname})"
      elsif type =~ /List<\s*(\w+)\s*>/
        key = $1
      else
        return %Q{jsonMap["#{name}"]}
      end
    end    
  end

  class Enum
    extend Attributes
    include Accessible
    
    attribute_defaults({ 
                         :id => nil, 
                         :name => nil,
                         :public => true, 
                         :values => [],
                       })
    def initialize(opts={ })
      set_attributes(opts)
      @id = instantiate(method(:make_id), id)
      @name = id.cap_camel
      if not @public
        @name = '_'+@name
      end
      @values = values.map { |v| make_id(v).shout }
    end
  end

  class DClass
    extend Attributes
    include Accessible
    attr_reader :owner
    attribute_defaults({
                         :id => nil, 
                         :owner => nil,
                         :name => nil,
                         :descr => nil,
                         :tname => nil,
                         :template_parms => [],
                         :public => false, 
                         :members => [], 
                         :custom_ctors => [],
                         :ctors => nil,
                         :ctor => false,
                         :ctor_named => false,
                         :ctor_opt => false,
                         :pp => false,
                         :generated => [],
                         :json => false,
                         :no_class_impl => false,
                       })

    def json_sample(map_rand_range=(1..5))
      output = @@engine.render('json_sample.tmpl', 
                               { 
                                 :c => self,
                                 :range => map_rand_range,
                                 :lib => owner.owner,
                               })
    end  

    def owner=(parent)
      @owner = parent
      members.each do |m|
        m.owner = self
      end
    end

    def class_map
      return owner.class_map
    end

    def enum_map
      return owner.enum_map
    end

    def has_ctors?
      ctors.length > 0
    end

    def initialize(opts={ })
      require 'yaml'
      set_attributes(opts)
      @members = instantiate(Member, members)
      @id = instantiate(method(:make_id), id)
      @name = id.cap_camel
      if not @public
        @name = '_'+@name
      end
      if not template_parms.empty?
        @template_parms = template_parms.map{ |p| make_id(p).shout }
        @tname = "#{name}<#{template_parms.join(', ')}>"
      else
        @tname = @name
      end
      ctor_map = Hash.new {|h,k| h[k] = { :args => [], :opt_args => [], :named_args => [] } }
      members.each do |m|
        if m.ctor
          m.ctor.each do |ctor|
            ctor_map[ctor.camel][:args] << m
          end
        end
        if m.ctor_opt
          m.ctor_opt.each do |ctor|
            ctor_map[ctor.camel][:opt_args] << m
          end
        end
        if m.ctor_named
          m.ctor_named.each do |ctor|
            ctor_map[ctor.camel][:named_args] << m
          end
        end
      end
      if ctor
        ctor_map['default'] = { :args => members, :opt_args => [], :named_args => [] }
      end
      if ctor_opt
        ctor_map['default'] = { :args => [], :opt_args => members, :named_args => [] }
      end
      if ctor_named
        ctor_map['default'] = { :args => [], :opt_args => [], :named_args => members }
      end
      @ctors = ctor_map
      @custom_ctors = [ @custom_ctors ] if @custom_ctors.class != Array
      @custom_ctors = Set.new(custom_ctors.map{|c| name_ctor(c).camel })
    end
  end

  class Part
    attr_reader :owner
    extend Attributes
    include Accessible
    attribute_defaults({ 
                         :id => nil, 
                         :owner => nil, 
                         :members => [], 
                         :classes => [],
                         :generated => [],
                         :enums => [],
                         :no_part_impl => false,
                       })

    def initialize(opts={ })
      set_attributes(opts)
      required_attributes([:id])
      @members = instantiate(Member, members)
      @classes = instantiate(DClass, classes)
      @enums = instantiate(Enum, enums)
      @id = instantiate(method(:make_id), id)
    end

    def owner=(parent)
      puts "Part owner set #{parent.name}"
      @owner = parent
      classes.each do |cls|
        cls.owner = self
      end
    end

    def class_map
      return owner.class_map
    end

    def enum_map
      return owner.enum_map
    end

    def find_classes(regex)
      result = []
      classes.each do |c|
        result << c if regex.match(c.name)
      end
      return result
    end

  end

  class Lib
    extend Attributes
    include Accessible
    attribute_defaults({ 
                         :id => nil, :members => [], 
                         :public_constants => [],
                         :public_typedefs => [],
                         :imports => [],
                         :parts => [], 
                         :name => nil,
                         :namespace => [],
                         :generated => [],
                         :generated_main => [],
                         :root_path => 
                         Place['dart'] ? Place['dart'] : 
                         Codegen::Dart::HERE + '../../../../../dart',
                         :class_map => { },
                         :enum_map => { },
                       })

    def initialize(opts={ })
      set_attributes(opts)
      required_attributes([:id])
      @members = instantiate(Member, members)
      @parts = instantiate(Part, parts)
      @id = instantiate(method(:make_id), id)
      @name = ((id.words.length >= 3) and id.abbrev or id.to_s)
      pp_required = false
      parts.each do |part|
        part.owner = self
        part.classes.each do |cls|
          class_map[cls.name] = cls
          if cls.pp or cls.json
            pp_required = true 
          end
        end
        part.enums.each do |enum|
          enum_map[enum.name] = enum
        end
      end
      if pp_required
        @imports << 'pprint.dart' 
      end
      @imports = clean_imports(@imports)
      @outpath = root_path
      namespace.each do |name|
        @outpath = @outpath + name
      end
      @public_constants = public_constants.map {|t,n,v| [ t, make_id(n).shout, v] }
      @public_typedefs = public_typedefs.map {|src,target| [ src, make_id(target).cap_camel ] }
      @outpath = @outpath
    end

    def generate()
      output = Codegen.clean_empty_lines(@@engine.render('lib.tmpl', 
                                                         { 
                                                           :lib => self,
                                                         }))

      Codegen.merge(output, @outpath + (id.to_s + '.dart'))

      parts.each do |part|
        output = Codegen.clean_empty_lines(@@engine.render('part.tmpl',
                                                           { 
                                                             :part => part
                                                           }
                                                           ))

        Codegen.merge(output, @outpath + 'src' + name + (part.id.to_s + '.dart'))
      end

      def find_classes(regex)
        result = []
        parts.each do |part|
          result = result + part.find_classes(regex)
        end
        return result
      end

      def random_json(type, field_name=nil)
        #puts "Creating random #{type} #{field_name} #{class_map.has_key?(type)} #{class_map.keys}"
        case type
        when "String"
          return (field_name and %Q{"#{field_name}-#{rand(10)}"} or "???-#{rand(100)}")
        when "int"
          return rand(100000)
        when /double/i
          return rand(100000) + rand()
        when "DateTime"
          d = DateTime.new(1929,10,29) + rand(40000)
          return d.strftime('"%Y-%m-%dT%H:%M:%S"')
        when /Map<String,\s*(\w+)/
          return @@engine.render('json_map.tmpl', { :v => $1, :lib => self })
        when /List<(\w+)/
          return @@engine.render('json_list.tmpl', { :v => $1, :lib => self })
        else
          if class_map.has_key?(type)
            return @@engine.render('json_sample.tmpl', 
                               { 
                                 :c => class_map[type],
                                 :lib => self,
                               })
          elsif enum_map.has_key?(type)
            e = enum_map[type]
            return rand(e.values.length)
          else
            return %Q{"Nothing for #{type}"}
          end
        end
      end

    end
  end


end

if __FILE__ == $0
  include Codegen::Dart
  require 'yaml'

  dc = Lib.new({
                 :id => 'time_value_of_money',
                 :parts =>
                 [
                  { 
                    :id => 'c_flow',
                    :classes =>
                    [
                     { 
                       :id => 'c_flow',
                       :public => true,
                       :members => [ { :id => 'foo_bar', :access => :rw } ]
                     }
                    ]
                  },

                  { 
                    :id => 'r_curve',
                    :classes =>
                    [
                     { 
                       :id => 'r_curve',
                       :public => true,
                       :members => [ { :id => 'foo_bar', :access => :rw } ]
                     }
                    ]
                  },
                 ]
               })
  puts "Is public:", dc.public, dc.to_yaml
  
end

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
