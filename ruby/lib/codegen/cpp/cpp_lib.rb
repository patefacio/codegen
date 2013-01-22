################################################################################
# Support for creating C++ libs
################################################################################
require 'codegen'
require 'codegen/cpp'
require 'tenjin'
require 'place'
require 'pp'

module Codegen::Cpp

  # Provides support for creating a c++ library
  #
  # User specifies a list of CppClasses and various other attributes and this
  # class generates the code and the build scripts.
  #
  class Library
    @@all_libs = []
    @@all_libs_by_name = { }

    def Library.all_libs()
      return @@all_libs
    end

    # <b><i>User Supplied:</i></b> Logical name of the lib. This is also
    # called <i>base_name</i>. The actual name of the library is a combination
    # of namespace text and this provided name
    attr_reader :name

    # <b><i>User Supplied:</i></b> Namespace of classes in this lib, as a list
    # of names (e.g.<tt> [ 'foo', 'bar' ]</tt>)
    attr_reader :namespace

    # <b><i>User Supplied:</i></b> Description of the library
    attr_reader :descr

    # <b><i>User Supplied:</i></b> List of classes to be included in the lib
    attr_reader :classes

    # <b><i>User Supplied:</i></b> List of cpp defines to be included in the lib
    attr_reader :build_cpp_defines

    # <b><i>User Supplied:</i></b> List of paths to be added to include path
    attr_reader :build_cpp_includes

    # <b><i>Calculated:</i></b> List of classes that have implementation
    # files. Determined by iterating over classes and culling those without
    # implementation (like a <i>header_only</i> class). Used in creating
    # script for building
    attr_reader :impl_classes

    # <b><i>Calculated:</i></b> True if any class <i>uses_pantheios</i>
    attr_reader :uses_pantheios

    # <b><i>User Supplied:</i></b> If true will make the library static
    # You can/should sepcify one of:
    # - static_only
    # - shared_only
    # - header_only
    # Choosing one of these decreases build times. However, if building real
    # stuff for clients where clients may want the ability to use shared or
    # static, you can set none. Setting none results in all of them being
    # false and support is there for both static and shared.
    attr_reader :static_only

    # <b><i>User Supplied:</i></b> If true will make the library shared only
    attr_reader :shared_only

    # <b><i>User Supplied:</i></b> If true will set the <i>header_only</i>
    # attribute on all classes, and no implementation files will be generated.
    attr_reader :header_only

    # <b><i>User Supplied:</i></b> List of class names that will be hand coded
    # (i.e. not generated) but still will be included in the build scripts
    attr_reader :hand_coded_impls

    # <b><i>User Supplied:</i></b> List of class header file names that will
    # be hand coded (i.e. not generated) but still will be included in the
    # build scripts
    attr_reader :hand_coded_headers

    # <b><i>Calculated:</i></b> List of all classes, which is the list of
    # classes provided plus any <i>additional_classes</i> of those classes.
    attr_reader :all_classes

    # <b><i>Calculated:</i></b> Path to where Jam build scripts reside,
    # sibling of src
    attr_reader :build_path

    # <b><i>User Supplied:</i></b> Defaulted to true - but if set to false, no
    # unit tests will be generated
    attr_reader :include_unit_tests

    # <b><i>Calculated:</i></b> Lists filtered to paths of all classes with a unit
    # test. The stub for the unit_tests are generated.
    attr_reader :unit_tests

    # <b><i>Calculated:</i></b> Lists filtered to all classes with a unit
    # test. The stub for the unit_tests are generated.
    attr_reader :classes_with_unit_tests

    # <b><i>Calculated:</i></b> True if <i>include_unit_tests</i> is true and
    # there exist some unit tests required in some of the classes
    attr_reader :unit_tests_required

    # <b><i>User Supplied:</i></b> List of flags to pass to the linker
    attr_reader :link_flags

    # <b><i>Calculated:</i></b>Path to the generated header file.
    # Based on namespace of lib
    attr_reader :header_path

    # <b><i>User Supplied or Calculated:</i></b>Path to the generated impl file.
    # If not supplied pulled from the first class in the lib
    attr_reader :cpp_path

    attr_accessor \
    :api_header, :api_decl, :api_impl, \
    :test_path, :no_api_decl, :jam_requirements, \
    :fcs_dependencies, :header_path_macro, \
    :impl_path

    ######################################################################
    # Finds all additional_classes and sibling_classes and makes
    # sure fields are consistent
    ######################################################################
    def walk_all_classes(all_classes, visiting)
      visiting.each do | current_class |

        begin
          # This block sets all fields in classes so they are consistent members of lib
          @uses_pantheios = true if current_class.uses_pantheios
          if current_class.namespace.length > 0 and current_class.namespace != @namespace
            warn "INCONSISTENT namespaces: #{@namespace} versus #{c.namespace}" 
          end
          current_class.namespace = @namespace if current_class.namespace.length == 0
          current_class.library = self
          current_class.header_only = true if header_only
          #p "Setting api_header on #{current_class.name} to #{@api_header}"
          current_class.api_header = @api_header
          #p "Setting #{@api_decl} on #{current_class.name} with ho => #{current_class.header_only}"
          current_class.api_decl = @api_decl if !current_class.header_only 
          current_class.impl_path = impl_path
        end

        all_classes << current_class
        if current_class.sibling_classes.length > 0
          walk_all_classes(all_classes, current_class.sibling_classes)
        end
        if current_class.nested_classes.length > 0
          #walk_all_classes(all_classes, current_class.nested_classes)
          current_class.nested_classes.each do |nc|
            nc.nesting_class = current_class
            current_class.header_includes += nc.header_includes
            current_class.impl_includes += nc.impl_includes
          end
        end
        if current_class.additional_classes.length > 0
          walk_all_classes(all_classes, current_class.additional_classes)
          current_class.additional_classes.each do |additional_class|
            additional_class.owning_class = current_class
            current_class.add_headers_for_class additional_class
          end
        end
      end
    end


    def initialize(data)
      @place = Place.place()
      @base_name = (data[:name] or nil)
      @jam_requirements = (data[:jam_requirements] or [])
      @build_cpp_includes = (data[:build_cpp_includes] or [])
      @build_cpp_defines = (data[:build_cpp_defines] or [])
      @descr = (data[:descr] or '')
      @namespace = data[:namespace]
      raise "LIBS MUST HAVE A NAMESPACE" if not namespace  
      @name = @namespace.join('_') 
      @name += ('_' + @base_name) if @base_name and (@namespace[-1] != @base_name)
      @cpp_path = data[:cpp_path]
      @api_header = data[:api_header]
      @static_only = (data[:static_only] or false)
      @shared_only = (data[:shared_only] or false)
      @header_only = (data[:header_only] or false)
      @static_only = false if @header_only
      @shared_only = false if @header_only
      @api_decl = data[:api_decl]
      @no_api_decl = (data[:no_api_decl] or false or static_only or header_only)
      @header_path_macro = "#{name.upcase}_PUBLIC_HEADER_PATH"
      if !@api_decl and not @no_api_decl
        @api_decl = [ @name.upcase, 'API'].join('_')
      end
      @static_only = true if not api_decl if not header_only
      @include_unit_tests = Codegen.default_to_true_if_not_set(data, 'include_unit_tests')

      @header_path = Codegen::Cpp.header_path(namespace)
      @impl_path = Codegen::Cpp.impl_path(namespace)
      @uses_pantheios = (data[:uses_pantheios] or false)

      ######################################################################
      # Before walking all classes, find the api_header
      ######################################################################
      @classes = data[:classes]
      @classes = classes.collect { |c| (c.class == {}.class)? CppClass.new(c):c }

      unless @api_header
        api_header_class = @classes.select { |c| c.is_api_header }
        header_api = api_header_class[0] if api_header_class.length>0
        if !header_api and @shared_only
          #p "Creating api class for #{@base_name} in ns #{@namespace}"
          header_api = ::Codegen::Cpp::CppClass.new(
                                                    { 
                                                      'name' => "#{@base_name}_api",
                                                      'is_api_header' => true,
                                                      #'namespace' => @namespace,
                                                      'header_path' => header_path,
                                                      'impl_path' => impl_path,
                                                    })

          @classes.push header_api
        end
        if header_api
          header_api.impl_includes.push 'pantheios/pantheios.hpp'
          header_api.impl_includes.push 'pantheios/inserters.hpp'
          header_api.impl_includes.push 'pantheios/frontends/stock.h'
          @jam_requirements.push '$(PANTHEIOS_LIBS)'
          @api_header = lambda { header_api.header_as_include }
        end
      end
      
      @all_classes = []
      walk_all_classes(@all_classes, @classes)

      # This block must be called after the ownership has been assigned so
      # owned classes have a header_as_include path that points to the owning
      # class
      @all_classes.each do |current_class|
        current_class.header_path = header_path
        if current_class.header_path != header_path
          next if current_class.is_api_header
          if current_class.header_path.relative_path_from(header_path).to_s !~ /^\./
            puts "Warning: conflicting header_paths: lib #{header_path} vs #{current_class.header_path}"
          end
        end
      end

      @jam_requirements = Codegen::Cpp.clean_ordered(@jam_requirements)
      @fcs_dependencies = @jam_requirements.collect { |d| $_ = $1 if d=~/\/\/(fcs_\w+)/ }.select {|d| d }
      deps = []
      @fcs_dependencies.each do |d|
        lib = @@all_libs_by_name[d]
        if lib
          deps.push lib
        else
          puts "Warning: invalid dep #{d} for #{name}: provided: [#{@fcs_dependencies.join(':')}]"
        end
      end
      @fcs_dependencies = deps
      @api_impl = data[:api_impl]
      @libs = data[:libs]
      @link_flags = data[:link_flags]
      @hand_coded_impls = (data[:hand_coded_impls] or [])
      @hand_coded_headers = (data[:hand_coded_headers] or [])

      context = { :lib => self }
      @@all_libs.push self
      @@all_libs_by_name[ name ] = self 

      @classes.each do |c|
        if c.is_api_header and ((c.enums.length > 0) or (c.forward_enums.length > 0))
          # Any enums in the api_header will require an api_impl
          @api_impl = true
        end
      end

      build_cpp_includes.push '$(PANTHEIOS_INCLUDE_PATH)' if uses_pantheios

      engine = Tenjin::Engine.new()
      @impl_classes = @all_classes.select { |c| (not c.header_only) and (not c.is_api_header or @api_impl) }
      @cpp_path = @classes.select {|c| c.impl_path }.map {|c| c.impl_path }[0] if not cpp_path
      @build_path = cpp_path.parent + 'build' 
      @test_path = cpp_path.parent + 'unit_test' 

      @all_classes.each do |c|
        c.generate_header() if not c.owning_class
        next if c.header_only
        if c.is_api_header
          if @api_impl
            c.impl_includes.push "fcs/patterns/api_initializer.hpp"
            c.generate_api_impl()
          end
        else
          c.generate_impl()
        end
      end

      @classes_with_unit_tests = @all_classes.select {|c| c.include_unit_test }
      @unit_tests_required = (include_unit_tests and not classes_with_unit_tests.empty?) or false

      required_paths = []
      required_paths += [cpp_path, build_path] if not header_only
      required_paths << test_path if unit_tests_required
      required_paths.each do |p|
        if not p.exist?
          p.mkpath
        end
      end
      if not header_only
        output = engine.render("#{@place['rb_codegen_tmpl']}/cpp_bjam.tmpl", context)
        Codegen.merge(output, "#{build_path}/Jamfile.v2")
        #output = engine.render("#{@place['rb_codegen_tmpl']}/cpp_lib_project_cmake.tmpl", context)
        #Codegen.merge(output, "#{cpp_path}/CMakeLists.txt")
      end


      @unit_tests = []
      if unit_tests_required
        #puts "Including lib unit tests #{name}"
        classes_with_unit_tests.each do |c|
          #puts "Including lib unit tests #{name} $ #{c.name}"
          unit_test_path = Pathname.new("#{test_path}/test_#{c.fqpath_impl.basename}")
          c.generate_unit_test(unit_test_path)
          unit_tests.push unit_test_path
        end
        output = engine.render("#{@place['rb_codegen_tmpl']}/unit_test_bjam.tmpl", context)
        unit_test_bjam = Codegen.merge(output, Pathname.new("#{test_path}/Jamfile"), 
                                       :protected_pair => Codegen::BUILD_PROTECT_BLOCK_DELIMITERS)
      else
        puts "NOT INCLUDING UNIT TESTS FOR #{name}"
      end
    end
  end
end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
