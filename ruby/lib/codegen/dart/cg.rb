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

  module Accessible
    extend Attributes
    attr_accessor :public
  end

  class Member
    extend Attributes
    include Accessible
    attribute_defaults({ :public => false, :id => nil, :type => nil, 
                         :access => :ia, :vname => nil, :name => nil,
                         :init => nil, :ctor => nil, :ctor_opt => nil,
                         :ctor_named => nil
                       })

    def readable()
      return ((access == :ro) or (access == :rw))
    end

    def writable()
      return access == :rw
    end

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


    def initialize(opts={ })
      set_attributes(opts)
      @id = instantiate(method(:make_id), id)
      @type = 'dynamic' if not @type
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
    
  end

  class DClass
    extend Attributes
    include Accessible
    attribute_defaults({
                         :id => nil, 
                         :public => false, 
                         :members => [], 
                         :name => nil,
                         :ctors_to_members => nil
                       })

    def initialize(opts={ })
      require 'yaml'
      set_attributes(opts)
      @members = instantiate(Member, members)
      @id = instantiate(method(:make_id), id)
      @name = id.cap_camel
      ctor_map = Hash.new {|h,k| h[k] = [] }
      members.each do |m|
        if m.ctor
          m.ctor.each do |ctor|
            ctor_map[ctor.camel] << m
          end
        end
      end
      @ctors_to_members = { }
      ctor_map.each_pair do |k,v|
        @ctors_to_members[k] = v
      end
    end
  end

  class Part
    attr_accessor :owner
    extend Attributes
    include Accessible
    attribute_defaults({ :id => nil, :owner => nil, :members => [], :classes => [] })
    def initialize(opts={ })
      set_attributes(opts)
      required_attributes([:id])
      @members = instantiate(Member, members)
      @classes = instantiate(DClass, classes)
      @id = instantiate(method(:make_id), id)
    end
  end

  class Lib
    extend Attributes
    include Accessible
    attribute_defaults({ 
                         :id => nil, :members => [], 
                         :parts => [], 
                         :namespace => [],
                         :root_path => 
                         Place['dart'] ? Place['dart'] : 
                         Codegen::Dart::HERE + '../../../../../dart'
                       })
    def initialize(opts={ })
      set_attributes(opts)
      required_attributes([:id])
      @members = instantiate(Member, members)
      @parts = instantiate(Part, parts)
      @id = instantiate(method(:make_id), id)
      parts.each do |part|
        part.owner = self
      end
      @outpath = root_path
      namespace.each do |name|
        @outpath = @outpath + name
      end
      @outpath = @outpath
    end

    def generate()
      output = Codegen.clean_empty_lines(@@engine.render('lib.tmpl', 
                                                         { 
                                                           :lib => self,
                                                         }))

      # output = @@engine.render('lib.tmpl', 
      #                                                    { 
      #                                                      :lib => self,
      #                                                    })

      Codegen.merge(output, @outpath + (id.to_s + '.dart'))

      parts.each do |part|
        output = Codegen.clean_empty_lines(@@engine.render('part.tmpl',
                                                           { 
                                                             :part => part
                                                           }
                                                           ))

        # output = @@engine.render('part.tmpl',
        #                                                    { 
        #                                                      :part => part
        #                                                    }
        #                                                    )
        Codegen.merge(output, @outpath + 'src' + id.abbrev + (part.id.to_s + '.dart'))
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
