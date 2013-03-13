################################################################################
# Support for generating D packages with their modules/structs/classes
################################################################################
require 'codegen'
require 'codegen/attributes'
require 'codegen/id'
require 'codegen/dlang'
require 'place'
require 'pp'
require 'yaml'
require 'tenjin'

include Codegen
module Codegen::Dlang

  @@engine = Tenjin::Engine.new(:path => [ Place['dlang_tmpl'].to_s ])

  ProtectionAttributes = [ :public, :private, :package, :protected, :export ]

  def public_filter(items) return items.find_all {|c| c.protection == :public } end
  def nonpublic_filter(items) return items.find_all {|c| c.protection != :public } end
  def private_filter(items) return items.find_all {|c| c.protection == :private } end
  def package_filter(items) return items.find_all {|c| c.protection == :package } end
  def protected_filter(items) return items.find_all {|c| c.protection == :protected } end
  def export_filter(items) return items.find_all {|c| c.protection == :export } end

  def alias_filter(items) return items.find_all {|c| c.class == Alias } end
  def mixin_filter(items) return items.find_all {|c| c.class == Mixin } end
  def constant_filter(items) return items.find_all {|c| c.class == Constant } end
  def enum_filter(items) return items.find_all {|c| c.class == Enum } end
  def union_filter(items) return items.find_all {|c| c.class == Union } end
  def struct_filter(items) return items.find_all {|c| c.class == DStruct } end
  def class_filter(items) return items.find_all {|c| c.class == DClass } end
  def member_filter(items) return items.find_all {|c| c.class == Member } end
  def property_filter(items) return items.find_all {|c| c.class == Property } end
  def module_filter(items) return items.find_all {|c| c.class == DModule } end
  def template_filter(items) return items.find_all {|c| c.class == Template } end
  def code_block_filter(items) return items.find_all {|c| c.class == CodeBlock } end
  def section_filter(items) return items.find_all {|c| c.class == Section } end

  module Parent
    attr_accessor :children

    def inception(babies)
      @children = [] if children.nil?
      @children += babies
      babies.map {|item| item.owner = self }
    end

    def public() return children.find_all {|c| c.protection == :public } end
    def private() return children.find_all {|c| c.protection == :private } end
    def package() return children.find_all {|c| c.protection == :package } end
    def protected() return children.find_all {|c| c.protection == :protected } end
    def export() return children.find_all {|c| c.protection == :export } end

    def child_filter(path, func, result = [])
      path = path + [ self ] if name
      @children.each do |child|
        if child.is_a? Parent
          child.child_filter(path, func, result)
        end
      end
      if func.call(path, self)
        result << [path, self]
      end
    end

  end

  module Owned
    attr_accessor :owner
  end

  module GenPrep
    @prep_complete = false
    def prep
      return if @prep_complete
      #puts "GenPrep prep for #{self.respond_to? :name and self.name}"
      if respond_to? :children
        children.each do |child|
          child.prep if child.respond_to? 'prep'
        end
      end
      @prep_complete = true
    end
  end

  class CodeBlock
    extend Attributes
    include Owned
    attribute_defaults({ :block => '', :protection => :public })
    def initialize(opts={ })
      set_attributes(opts)
    end
  end

  class Section
    extend Attributes
    include Owned
    attribute_defaults({ :name => nil, :protection => :public })
    def initialize(opts={ })
      set_attributes(opts)
    end
  end

  module PropertyHolder
    include Parent
    attr_reader :properties
    def create_properties
      @properties = instantiate(Property, properties)
    end
  end

  module DTestable
    attr_reader :d_tests
    @d_tests = []
  end

  module MemberHolder
    include Parent
    include PropertyHolder
    attr_reader :members
    def create_members
      create_properties
      @members = instantiate(Member, members)
      inception(members)
      members.each do |m|
        if m.access and m.access != :ia
          if m.access == :rw
            @mixins << Mixin.new(:t_arg => "ReadWrite!#{m.vname}")
          else
            @mixins << Mixin.new(:t_arg => "ReadOnly!#{m.vname}")
          end
        end
      end
      inception(properties)
    end
  end

  module DeclHolder
    include Parent

    @@named_child_types = 
      [ 
       :aliases, :constants, :enums, :unions, :structs, 
       :classes, :templates, :sections ]

    attr_reader(*@@named_child_types)

    @@unnamed_child_types = [ :mixins, :code_blocks ]
    attr_reader(*@@unnamed_child_types)

    @@child_hashes = @@named_child_types.map{|i| "hash_#{i}".to_sym } 
    attr_reader(*@@child_hashes)

    @@standard_sections = ProtectionAttributes.map { |a| "#{a}_section".to_sym }
    attr_reader(*@@standard_sections)

    attr_reader :unit_test

    def DeclHolder.decl_holder_defaults
      result = { :unit_test => nil, :mixins => [], :code_blocks => [] }
      result = @@named_child_types.inject(result) {|c,i| c[i] =[]; c }
      result = @@standard_sections.inject(result) {|c,i| c[i] = nil; c }
    end

    def create_decl_children
      @aliases = instantiate(Alias, aliases)
      @mixins = instantiate(Mixin, mixins)
      @constants = instantiate(Constant, constants)
      @enums = instantiate(Enum, enums)
      @unions = instantiate(Union, unions)
      @structs = instantiate(DStruct, structs)
      @classes = instantiate(DClass, classes)
      @templates = instantiate(Template, templates)
      @code_blocks = instantiate(CodeBlock, code_blocks)
      @sections = instantiate(Section, sections)
      # If unit_test is Boolean (magic) accept it as empty
      if !!unit_test == unit_test
        @unit_test = instantiate(UnitTest, { }) if unit_test
      else
        @unit_test = instantiate(UnitTest, unit_test) if unit_test
      end
      class_name = self.class.name.downcase.split('::')[-1]

      ProtectionAttributes.each_index do |i|
        protection = ProtectionAttributes[i]
        section = @@standard_sections[i]
        if instance_variable_get("@#{section}")
          @sections << Section.new({
                                     :protection => protection, 
                                     :name => "#{class_name} #{name} #{section}" }) 
        end
      end
      inception(@aliases + @constants + @enums + @unions + @structs + 
                @classes + @templates + @code_blocks + @sections)
      inception(@mixins)
      inception([unit_test]) if unit_test
      @@named_child_types.each {|l| define_hash_from_object_list(l) }
    end
  end

  module TemplateDecl
    def template_decl
      if not template_parms.empty?
        "(" + template_parms.join(', ') + ")"
      else
        ""
      end
    end
  end

  class TemplateParm
    extend Attributes
    attribute_defaults({
                         :type_name => nil,
                         :var_name => nil,
                         :default => nil,
                       })
    attr_reader :type_name, :var_name, :default

    def initialize(opts)
      case opts
      when Hash
        set_attributes(opts)
      when Array
        @type_name, @default = opts
      else
        @type_name = opts
      end
      required_attributes([:type_name])
    end
    
    def to_s
      result = type_name.to_s
      result += " #{var_name}" if var_name
      result += " = #{default}" if default
      result
    end
  end

  class Template
    extend Attributes
    include DeclHolder
    include TemplateDecl
    include Owned

    attribute_defaults({
                         :name => nil,
                         :doc => nil,
                         :template_parms => [],
                         :protection => :public,
                       }.merge(DeclHolder.decl_holder_defaults))

    def initialize(opts={ })
      set_attributes(opts)
      @template_parms = template_parms.map {|tp| TemplateParm.new(tp) }
      initialize_attribute(method(:make_id), :name)
      required_attributes([:name])
      create_decl_children
      @doc = doc.strip if doc
    end
  end

  class Constant
    extend Attributes
    include Owned

    attribute_defaults({
                         :type => nil,
                         :name => nil,
                         :value => nil,
                         :static => nil,
                         :static_this => nil,
                         :doc => nil,
                         :protection => :public,
                         :definition => nil,
                       })
                         
    def initialize(opts)
      set_attributes({ })
      case opts
      when Hash
        set_attributes(opts)
      when Array
        @type, @name, @value, @doc = opts
      when String
        @definition = "const #{opts}"
      else
        @name = opts
      end
      @name = make_id(name) if name
      @type = type_name(type)
      if static
        @static = "static " 
      else
        @static = ""
      end
      if not definition
        if static_this
          assignment = "#{name.cap_camel} = #{value};"
          @definition = "#{static}const(#{type}) #{name.cap_camel};
static this() {
#{Codegen.indent_absolute_text(assignment)}
}
"
        else
          if type
            @definition = "#{static}const(#{type}) #{name.cap_camel}#{!value.nil? ? %Q{ = #{value}} :''};"
          else
            @definition = "#{static}const #{name.cap_camel} = #{!value.nil? ? %Q{ = #{value}} :''};"
          end
        end
      end
      @doc = doc.strip if doc
    end
  end


  class Type
    extend Attributes
    include GenPrep
    include Owned
    attribute_defaults({
                         :name => nil,
                         :doc => nil,
                         :init => nil,
                         :d_attributes => [],
                         :static => nil,
                         :static_decl => nil,
                         :final => nil,
                         :deprecated => nil,
                         :protection => :public,
                       })

    def initialize(opts={ })
      set_attributes(opts)
      required_attributes([:name])
      initialize_attribute(method(:make_id), :name)
      @doc = doc.strip if doc
      @static_decl = static ? "static " : ""
    end

    def add_attribute(attr)
      d_attributes << attr
    end
  end

  class BasicType < Type
    extend Attributes
    attribute_defaults(Type.defaults.merge({ 
                                           }))
    def initialize(opts={ })
      set_attributes(opts)
    end
  end

  BasicTypes = { 
    :void => BasicType.new(:name => :void, :init => nil),
    :bool => BasicType.new(:name => :bool, :init => :false),
    :byte => BasicType.new(:name => :byte, :init => 0),
    :ubyte => BasicType.new(:name => :ubyte, :init => 0),
    :short => BasicType.new(:name => :short, :init => 0),
    :ushort => BasicType.new(:name => :ushort, :init => 0),
    :int => BasicType.new(:name => :int, :init => 0),
    :uint => BasicType.new(:name => :uint, :init => 0),
    :long => BasicType.new(:name => :long, :init => 0),
    :ulong => BasicType.new(:name => :ulong, :init => 0),
    :cent => BasicType.new(:name => :cent, :init => 0),
    :ucent => BasicType.new(:name => :ucent, :init => 0),
    :float => BasicType.new(:name => :float, :init => :float_nan),
    :double => BasicType.new(:name => :double, :init => :double_nan),
    :real => BasicType.new(:name => :real, :init => :real_nan),
    :ifloat => BasicType.new(:name => :ifloat, :init => :ifloat_nan),
    :idouble => BasicType.new(:name => :idouble, :init => :idouble_nan),
    :ireal => BasicType.new(:name => :ireal, :init => :ireal_nan),
    :cfloat => BasicType.new(:name => :cfloat, :init => :cfloat_nan),
    :cdouble => BasicType.new(:name => :cdouble, :init => :cdouble_nan),
    :creal => BasicType.new(:name => :creal, :init => :creal_nan),
    :char => BasicType.new(:name => :char, :init => :xff),
    :wchar => BasicType.new(:name => :wchar, :init => :xffff),
    :dchar => BasicType.new(:name => :dchar, :init => :x0000ffff),
  }

  class DerivedType < Type
    extend Attributes
    attribute_defaults(Type.defaults.merge({ 
                                           }))
    def initialize(opts={ })
      super(opts)
      set_attributes(opts)
    end
  end

  DerivedTypes = [
                  :pointer => DerivedType.new(:name => :pointer),
                  :array => DerivedType.new(:name => :array),
                  :a_array => DerivedType.new(:name => :a_array),
                  :function => DerivedType.new(:name => :function),
                  :delegate => DerivedType.new(:name => :delegate),
                 ]

  module UDTType
    ALIAS = 1
    ENUM = 2
    STRUCT = 3
    UNION = 4
    CLASS = 5
  end

  class UDT < Type
    extend Attributes
    attribute_defaults(Type.defaults.merge({ 
                                             :type => nil
                                           }))
    def initialize(opts={ })
      super(opts)
      set_attributes(opts)
      required_attributes([:type])
      if not UDTType.constants.include? type
        raise ArgumentError, "type of UDT #{type} must be in #{UDTType.constants}"
      end
    end
  end

  class Alias < UDT
    extend Attributes
    attribute_defaults(UDT.defaults.merge({ :aliased => nil, }))
    def initialize(opts={ })
      original_name = opts[:name]
      opts[:type] = :ALIAS
      super(opts)
      if original_name.class == String
        @name = original_name 
      else
        @name = name.cap_camel
      end
      set_attributes(opts)
      required_attributes([:aliased])
      @aliased = type_name(aliased)
    end
  end    

  class EnumValue
    extend Attributes
    attribute_defaults({ 
                         :name => nil, 
                         :value => nil,
                         :doc => nil,
                       })
    def initialize(opts={ })
      set_attributes(opts)
      @name = make_id(name)
      @doc = doc.strip if doc
    end

    def decl
      if not value.nil?
        "#{name.cap_camel} = #{value}"
      else
        name.cap_camel
      end
    end

  end

  class Enum < UDT
    extend Attributes
    attribute_defaults(UDT.defaults.merge({ 
                                            :values => [],
                                          }))
    def initialize(opts={ })
      opts[:type] = :ENUM
      super(opts)
      initialize_attribute(method(:make_id), :name)
      values.each_index do |i|
        case values[i]
        when Hash
          values[i] = EnumValue.new(values[i])
        else
          values[i] = EnumValue.new(:name => values[i])
        end
      end
    end
  end    

  class Property
    extend Attributes
    include GenPrep
    include Owned
    attribute_defaults(UDT.defaults.merge({ 
                                            :name => nil,
                                            :vname => nil,
                                            :is_read => true,
                                          }))
    attr_reader :pname

    def initialize(opts={ })
      set_attributes(opts)
      required_attributes([:name])
      @pname = name.camel
    end
  end

  class Member 
    extend Attributes
    include GenPrep
    include Owned
    attribute_defaults(UDT.defaults.merge({ 
                                            :alignment => nil,
                                            :const => nil,
                                            :access => nil,
                                            :init => nil,
                                            :dup_init => nil,
                                            :vname => nil,
                                            :ctor => nil,
                                            :ctor_default => nil,
                                            :ref => nil,
                                          }))

    def initialize(opts={ })
      set_attributes(opts)
      @ctor = true if @ctor_default
      required_attributes([:name])
      access_qualifiers = [:rw, :ro, :ia]
      if type.nil?
        @type = name 
      end
      if type.class == Symbol
        if basic_type(type)
          @type = type.to_s
        else
          @type = make_id(type).cap_camel
        end
      end
      if not access.nil? and not access_qualifiers.include? access
        raise ArgumentError, "Member :access must be one of #{access_qualifiers}"
      end
      initialize_attribute(method(:make_id), :name)
      if protection == :public or protection.nil? and access.nil?
        @vname = name.camel
      else
        @vname = "_#{name.camel}"
      end
      @static_decl = static ? "static " : ""
    end

    def prep()
      if protection == :public and not access.nil?
        @protection = :private
      end
      super
    end

  end

  class DStruct < UDT
    extend Attributes
    include DeclHolder
    include MemberHolder
    include Owned
    include TemplateDecl
    include DTestable

    attribute_defaults \
    UDT.defaults.merge(DeclHolder.decl_holder_defaults).merge({ 
                                                                :template_parms => [], 
                                                                :members => [],
                                                                :properties => [],
                                                                :d_tests => [],
                                                              })

    attr_reader :ctor_members

    def initialize(opts={ })
      opts = opts.dup
      opts[:public_section] = true if !opts.has_key? :public_section
      opts[:type] = :STRUCT
      super(opts)
      set_attributes(opts)
      initialize_attribute(DTest, :d_tests)
      @template_parms = template_parms.map {|tp| TemplateParm.new(tp) }
      create_members
      create_decl_children
      @ctor_members = members.find_all {|m| m.ctor }
    end

  end    

  class Union < UDT
    extend Attributes
    include DeclHolder
    include MemberHolder
    include Owned

    attribute_defaults \
    UDT.defaults.merge(DeclHolder.decl_holder_defaults).merge({ 
                                                                :members => [],
                                                                :properties => [],
                                                              })
    def initialize(opts={ })
      opts[:type] = :UNION
      super(opts)
      set_attributes(opts)
      create_members
      create_decl_children
    end
  end    

  class UnitTest
    extend Attributes
    include GenPrep
    include DeclHolder
    include Owned

    attribute_defaults(DeclHolder.decl_holder_defaults.merge({ 
                                                               :protection => :public,
                                                               :name => nil,
                                                             }))

    def initialize(opts={ })
      set_attributes(opts)      
      create_decl_children
    end

    def prep()
      @name = owner.class.name.downcase.split('::')[-1] + " #{owner.name} unittest"
      super
    end
  end

  class Mixin
    extend Attributes
    include GenPrep
    include Owned

    attribute_defaults({ :t_arg => nil, :arg => nil, :protection => :public, 
                         :mixin_arg => nil, :is_template => nil })

    def initialize(opts={ })
      set_attributes(opts)
      @is_template = !t_arg.nil?
      temp = (arg or t_arg)
      if temp.class == String
        @mixin_arg = temp
      else
        @mixin_arg = make_id(temp).cap_camel
      end
    end
  end


  class DClass < UDT
    extend Attributes
    include DeclHolder
    include MemberHolder
    include Owned
    include TemplateDecl

    attribute_defaults UDT.defaults.merge\
    (DeclHolder.decl_holder_defaults).merge({ 
                                              :template_parms => [],
                                              :abstract => nil,
                                              :members => [],
                                              :properties => [],
                                            })

    def initialize(opts={ })
      opts[:type] = :CLASS
      super(opts)
      set_attributes(opts)
      @template_parms = template_parms.map {|tp| TemplateParm.new(tp) }
      create_decl_children
      create_members
    end
  end

  class DModule
    extend Attributes
    include DeclHolder
    include Owned
    include GenPrep
    include DTestable

    attribute_defaults \
    (DeclHolder.decl_holder_defaults).merge(
                                            :name => nil,
                                            :doc => nil,
                                            :imports => [],
                                            :public_imports => [],
                                            :debug_imports => [],
                                            :path => nil,
                                            :qualified_name => nil,
                                            :vname => nil,
                                            :static_this => nil,
                                            :open_source => nil,
                                            :d_tests => [],
                                            )

    def initialize(opts={ })
      set_attributes(opts)
      required_attributes([:name])      
      @imports = clean_imports(imports)
      @public_imports = clean_imports(public_imports)
      @debug_imports = clean_imports(debug_imports)
      initialize_attribute(method(:make_id), :name)
      initialize_attribute(DTest, :d_tests)
      @vname = name.shorten
      create_decl_children
      @doc = doc.strip if doc
    end

    def prep()
      if owner and owner.pkg_full.length > 0
        @qualified_name = owner.pkg_full + '.' + vname
      else
        @qualified_name = vname
      end
      @path = owner.path + "#{vname}.d"
      super
    end

    def generate()
      output = @@engine.render('module.tmpl', 
                               { 
                                 :mod => self,
                                 :qualified_name => qualified_name,
                               })
      return Codegen.merge(output, path)   
    end

  end

  class DTest
    attr_reader :name, :class_options, :mod_name
    def initialize(opts={ })
      @name = opts[:name]
      @mod_name = opts[:mod_name]
      opts.delete(:mod_name)
      @class_options = opts.clone
      @test_functions = (opts[:tests] or [])
      @class_options.delete(:tests)
      code_blocks = []
      @test_functions.each do |f|
        test_name = make_id("test_#{f}")
        code_blocks << { :block => """
void #{test_name.camel}() {
#{Codegen.protect_block(@name.to_s + test_name.to_s)}
}
""",
          :protection => :public,
        }
      end
      @class_options[:code_blocks] = code_blocks
    end
  end

  class Package
    extend Attributes
    include Parent
    include Owned
    include GenPrep

    @@hash_lists = [ :modules, :packages, :templates ]
    @@hash_maps = @@hash_lists.map{|i| "hash_#{i}".to_sym } 

    attr_reader(*@@hash_maps)

    attribute_defaults \
     (@@hash_lists.inject({}) {|c,i| c[i] =[]; c }).\
    merge(
          :root_path => Place['dlang'],
          :name => nil, 
          :pkg => '',          # base name of package (might be auto-shortened)
          :pkg_full => '',     # full package name starting at root
          :path => nil,         # full path to pkg
          :doc => nil,
          :is_root => false,
          :d_tests => [],
          )

    def initialize(opts={ })
      set_attributes(opts)
#      required_attributes([:name])
      if name
        initialize_attribute(method(:make_id), :name) 
        @pkg = name.shorten
      end
      @modules = instantiate(DModule, modules)
      @packages = instantiate(Package, packages)
      @templates = instantiate(Template, templates)
      initialize_attribute(DTest, :d_tests)
      [ modules, packages, templates ].each do |col|
        col.map {|item| item.owner = self }
      end
      inception(modules + packages)
      @doc = doc.strip if doc
      @@hash_lists.each {|l| define_hash_from_object_list(l) }
    end

    def add_d_tests
      child_tests = []
      # Find all tests of this package
      child_filter([],
                   Proc.new { 
                     |path, child| 
                     child.respond_to?(:d_tests) && 
                     child.d_tests.size>0 &&
                     path.find_all {|p| p.class == Package }[-1]
                   },
                   child_tests)

      if !child_tests.empty?
        # If the d_test named D_T_CLASS declaration appears in: 
        # package: The test appears in package.dtest.pkg_tests.D_T_CLASS
        # module: The test appears in package.dtest.module.D_T_CLASS
        # class: In package.dtest.module.D_T_CLASS
        #
        pkg_test_classes = []
        mod_test_classes = Hash.new {|hash,key| hash[key] = []}
        new_test_mods = { }
        child_tests.each do |path, child|
          pkg = path.find_all {|p| p.class == Package }[-1]
          mods = path.find_all {|p| p.class == DModule }
          child.d_tests.each do |d_test|
            copts = d_test.class_options.clone
            copts[:mixins] = [] if !copts[:mixins]
            copts[:mixins] << {:t_arg => :test_mixin }
            if mods.empty?
              pkg_test_classes << copts
            else
              key = { 
                :mod_name => mods[-1].name,
                :src_mod => mods[-1],
              }
              if d_test.mod_name
                key[:mod_name] = d_test.mod_name
              end
              mod_test_classes[key] << copts
            end
          end
        end

        pkg_tests_options = { 
          :name => :d_test,
          :modules => []
        }

        if !pkg_test_classes.empty?
          pkg_tests_options[:modules] <<
            { 
            :name => :pkg_tests,
            :code_blocks => [ { :block => "
void main() {
  dunit.runTests_Tree();
}

"} ],
            :imports => [ 'dunit', :stdio ],
            :public_section => true,
            :classes => pkg_test_classes,
          }
        end
        
        mod_test_classes.each_pair do |mod_spec, opts|
          pkg_tests_options[:modules] << { 
            :name => mod_spec[:mod_name],
            :open_source => mod_spec[:src_mod].open_source,
            :code_blocks => [ { :block => "
void main() {
  dunit.runTests_Tree();
}

"} ],
            :imports => [ 'dunit', :stdio ] + mod_spec[:src_mod].imports + [mod_spec[:src_mod].qualified_name],
            :public_section => true,
            :classes => opts,
          }
        end
        d_test_pkg = Package.new(pkg_tests_options)
        packages << d_test_pkg
        inception([d_test_pkg])
      end
    end
    
    def prep
      return if @prep_complete

      Package.prep

      @owner = @@root if (@owner.nil? and (@@root != self))

      if owner
        @pkg_full = [owner.pkg_full, @pkg].join('.')
      else
        @pkg_full = pkg
      end
      @path = root_path + pkg_full.split('.').join('/')

      super

      add_d_tests

    end

    def generate()
      prev_root = @@root
      @@root = self if is_root
      prep
      packages.each {|pkg| pkg.generate }
      modules.each {|mod| mod.generate }
      @@root = prev_root
    end
  end

  @@root_name = :plusauri
  @@root = nil

  def Package.root_name(root)
    @@root_name = root
  end

  def Package.prep(root_name = @@root_name) 
    if @@root.nil?
      @@root = Package.new(:name => root_name)
      @@root.prep
    end
  end

  def arr(opts)
    t = opts[:t]
    immutable = ((opts.has_key? :immutable) ? opts.delete(:immutable) : true)
    opts.delete(:t)
    base_name = opts.delete(:base_name)
    base_name = infer_id(t) if base_name.nil?
    aliased = (immutable ? "immutable(#{type_name(t)})[]" : "#{type_name(t)}[]")
    alias_opts = {:name => "#{base_name}_arr".to_sym, :aliased => "#{aliased}"}
    alias_opts.merge!(opts)
    return Alias.new(alias_opts)
  end

  def this_member(name)
    return Alias.new(:name => 'this', :aliased => name)
  end


  def aarr(opts)
    k = opts[:k]
    v = opts[:v]
    base_name = opts[:base_name]
    opts.delete(:k)
    opts.delete(:v)
    opts.delete(:base_name)
    
    kid = infer_id(type_name k) if k.class != String
    vid = infer_id(type_name v) if v.class != String
    base_name = "#{kid}_#{vid}" if base_name.nil?
    alias_opts = { :name => "#{base_name}_map".to_sym, :aliased => "#{type_name(v)}[#{type_name(k)}]" }
    alias_opts.merge!(opts)
    return Alias.new(alias_opts)
  end

  def ptr(t, base_name = nil)
    base_name = infer_id(t) if base_name.nil?
    return Alias.new(:name => "#{base_name}_ptr".to_sym, :aliased => "#{type_name(t)}*" )
  end

end

if __FILE__ == $0
  include Codegen::Dlang
  
pkg = \
  Package.new({ 
  :name => 'an_awesome_pkg',
  :packages => [
    :name => 'a_nested_pkg',
    :modules => [
      { 
        :name => 'module_in_nested_pkg',
      }
    ]
  ],
    :modules => [
      { 
        :name => :m_1_strong,
        :classes => 
        Deprecated([
          #Abstract({ 
          { 
            :name => :my_xml_class, 
            :abstract => true,
            :doc => "This \nmy\nawesome\nclass", 
            :members => Private([
              Ro(:name => :x_member, :type => :foo),
              { :name => :goo, :type => :foo, :doc => 'this is my goo'},
              { :name => :goo1, :type => :foo1, },
              Ia({ :name => :goo2, :type => :foo2, :init => 200 }),
              { :name => :goo3, :type => :foo3, },
              Rw({ :name => :goo4, :type => :string, :init => "Foo goo4", :doc => 'lookie' }),
              { :name => :goo5, :type => :foo5, },
            ]),
            :aliases => [ Private({ 
              :name => :some_random_alias, :aliased => 'int[]'
            }),
                                         { 
                                           :name => :date, :aliased => 'DateRate.TimeType'
                                         }
            ],
            :classes => [{ 
              :name => :some_nested_class,
              :doc => 'use this scoped to parent',
              :members => [
                Const({ :name => 'm_one_two', :type => :x_y_z })
              ]
            }],
            :structs => [{ 
              :name => :some_nested_struct,
              :doc => 'use this scoped to parent',
              :members => [
                Align({ :name => 'm_one_two', 
                        :type => :x_y_z,
                        :doc => "
This is a multiline comment,
docibing in great detail
m_one_two

              "}, 2)
              ]}],
          },
        ]),
      }
  ]
})

#pp pkg
#pp pkg.modules[0].classes[0].classes[0].members[0].name.emacs

#pp pkg
#pp "m_1_string is ",pkg.hash_modules[:m_1_strong]
#pp pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].hash_members[:x_member]
#pp pkg
  puts pkg.prep
  puts pkg.to_yaml
  puts pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].hash_structs[:some_nested_struct].hash_members[:m_one_two].doc
  puts pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].abstract
  pp "public: ", pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].public.map{|i| i.name }
  pp "aliases: ", pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].aliases.map{|i| i.name }
  pp "public aliases: ", pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].aliases.map{|i| i.name }
  #pp "private: ", pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].private
  #pp "protected: ", pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].protected
#puts pkg.hash_modules[:m_1_strong].hash_classes[:my_xml_class].hash_structs[:some_nested_struct].abstract

end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
