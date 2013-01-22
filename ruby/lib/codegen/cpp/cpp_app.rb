#######################################################################
# Support for generating apps (i.e. executables)
#######################################################################
require 'codegen'
require 'tenjin'
require 'place'
require 'pp'
module Codegen::Cpp

  # Used to generate an application
  #
  class Application
    @@all_apps = []

    def Application.all_apps()
      return @@all_apps
    end

    # <b><i>User Supplied:</i></b> Name of the application
    attr_reader :name

    # <b><i>User Supplied:</i></b> <i>Detailed</i> description of the application
    attr_reader :descr

    # <b><i>User Supplied:</i></b> <i>Brief</i> description of the application
    attr_reader :brief

    # <b><i>User Supplied:</i></b> An additional folder - if present the app
    # will exist under ../cpp/apps/{folder}
    attr_reader :folder

    # <b><i>User Supplied:</i></b> List of classes to generate for the
    # application
    attr_reader :classes

    # <b><i>User Supplied:</i></b> Namespace as a list of names (e.g.<tt> [
    # 'foo', 'bar' ]</tt>)
    attr_reader :namespace
    
    # <b><i>User Supplied:</i></b> List of includes for the module with main
    attr_reader :app_includes

    # <b><i>User Supplied:</i></b> If true includes pantheios headers
    attr_reader :uses_pantheios

    # <b><i>User Supplied:</i></b> If true includes support for capturing
    # signals
    attr_reader :app_sig_handler

    # <b><i>User Supplied:</i></b> List of cpp defines to be included in the app
    attr_reader :build_cpp_defines

    # <b><i>User Supplied:</i></b> Program options 
    attr_reader :program_options

    # <b><i>Calculated:</i></b> Program options class if program_options provided
    attr_reader :program_options_class

    # <b><i>User Supplied:</i></b> Intended for codegen - text just before
    # main_body code block
    attr_reader :additions_main_pre_main_body

    # <b><i>User Supplied:</i></b> Intended for codegen - text just before
    # main_body code block
    attr_reader :additions_main_post_main_body

    # <b><i>User Supplied:</i></b> Extra include directives (eg
    # <include>$(PROTOBUF_INCLUDE_PATH))
    attr_reader :jam_cpp_include_directives

    # <b><i>User Supplied:</i></b> If true app is boost unit_test app
    attr_reader :unit_test

    # <b><i>User Supplied:</i></b> If true adds custom code section before
    # namespace
    attr_reader :include_pre_namespace_custom

    # <b><i>User Supplied:</i></b> If true adds custom code section after
    # namespace
    attr_reader :include_post_namespace_custom

    # <b><i>User Supplied:</i></b> If true adds code block before namespace
    attr_reader :pre_namespace_section

    # <b><i>User Supplied:</i></b> If true adds code block after namespace
    attr_reader :post_namespace_section

    # <b><i>User Supplied:</i></b> If true adds code so app will receive
    # SIGHUP when parent dies
    attr_reader :die_with_parent

    attr_accessor  :cpp_path, :libs, :link_flags, :hand_coded_impls, \
    :hand_coded_headers, :owner, :build_path, :jam_requirements, :main_cpp, \
    :impl_classes, :app_path, :log_pantheios_fe, :standard_logging,
    :additions_main_pre_main_body, :additions_main_post_main_body,
    :standard_otl_logging

    def initialize(data={})

      # Nil default if not set attributes
      [ 
       
       :name, :program_options, :log_pantheios_fe, :standard_logging, :brief,
       :folder, :standard_otl_logging, :unit_test, :pre_namespace_section,
       :post_namespace_section, :die_with_parent

      ].each do | attr |
        self.instance_variable_set("@#{attr.to_s}", data[attr])
      end

      # Empty list default if not set attributes
      
      [
       
       :additions_main_pre_main_body, :additions_main_post_main_body,
       :build_cpp_defines, :app_includes, :defines, :libs, :link_flags,
       :jam_requirements, :jam_cpp_include_directives

      ].each do |attr|
        if data[attr]
          self.instance_variable_set("@#{attr.to_s}", data[attr])
        else
          self.instance_variable_set("@#{attr.to_s}", [])
        end
      end

      @place = Place.place()
      @include_pre_namespace_custom = (data[:include_pre_namespace_custom] and "pre-namespace custom" or "")
      @include_post_namespace_custom = (data[:include_post_namespace_custom] and "post-namespace custom" or "")
      @program_options_class = program_options.cpp_class if program_options
      @standard_logging = true if program_options and program_options.standard_logging
      @standard_otl_logging = true if program_options and program_options.standard_otl_logging
      @classes = data[:classes]
      @classes << program_options_class if program_options_class and !classes.include? program_options_class
      @main_cpp = name + '.cpp'
      @app_sig_handler = Codegen.default_to_true_if_not_set(data, :app_sig_handler)
      @classes.map! { |c| (c.class == Hash)? CppClass.new(c) : c }
      @namespace = (data[:namespace] or [ 'fcs', 'apps' ])
      if folder
        @build_path = @app_path = @place['apps'] + folder + name
      else
        @build_path = @app_path = @place['apps'] + name
      end
      @cpp_path = build_path
      @app_includes << 'fcs/app_sig_handler/application_signal_handler.hpp' if app_sig_handler
      @app_includes << 'sys/prctl.h' if die_with_parent
      if @log_pantheios_fe
        @app_includes << 'pantheios/frontend.h'
        @app_includes << 'fcs/utils/pantheios_debug_log.hpp'
        @app_includes << 'boost/thread/mutex.hpp'
      else
        @app_includes << 'pantheios/frontends/stock.h'
      end

      @app_includes << lambda { @program_options_class.header_as_include } if @program_options_class

      @classes.each do |c|
        c.impl_path = c.header_path = app_path
        c.namespace = @namespace if (@namespace.length>0 and c.namespace.length==0)
      end
#      @lib_path = data[:lib_path]
      @hand_coded_impls = data[:hand_coded_impls]
      @hand_coded_headers = data[:hand_coded_headers]
      @uses_pantheios = (data[:uses_pantheios] or log_pantheios_fe)
      @uses_pantheios = true if @libs.select { |l| l.uses_pantheios }.length > 0      

      context = { :app => self }
      @@all_apps.push self
      
      engine = Tenjin::Engine.new()
      @impl_classes = @classes.select { |c| not c.header_only }

      @classes.each do |c|
        
        raise "ERROR: may not change header filename for app classes" + 
          c.name if c.header_filename != c.default_header_filename

        c.generate_header()

        next if c.header_only

        if c.is_api_header
          raise "ERROR: app classes may not be of type api_header:" + c.name
        elsif c.impl_filename != c.default_impl_filename
          raise "ERROR: differing file locations for app module classes not supported:" + c.name
        end

        c.generate_impl()

        @uses_pantheios = true if c.uses_pantheios

      end

      impl_contents = engine.render("#{@place['rb_codegen_tmpl']}/cpp_app.tmpl", context)

      file_details = FileDetails.new({ 
                                       :filename => "#{name}.cpp",
                                       :brief => brief,
                                       :namespace => namespace,
                                       :includes => app_includes,
                                       :pre_namespace_contents => (@unit_test? '
#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>
' : nil),
                                       :include_pre_namespace_custom => include_pre_namespace_custom,
                                       :include_post_namespace_custom => include_post_namespace_custom,
                                       :include_namespace_custom => "namespace custom",
                                       :post_namespace_contents => impl_contents,
                                       :pre_namespace_section => pre_namespace_section,
                                       :post_namespace_section => post_namespace_section
                                     })
      file_details_context = { :file_details => file_details }
      output = engine.render("#{@place['rb_codegen_tmpl']}/cpp_file.tmpl", file_details_context)
      Codegen.merge(output, app_path + main_cpp)

      output = engine.render("#{@place['rb_codegen_tmpl']}/cpp_app_bjam.tmpl", context)
      Codegen.merge(output, "#{app_path}/Jamfile.v2")

      #output = engine.render("#{@place['rb_codegen_tmpl']}/cpp_app_cmake.tmpl", context)
      #Codegen.merge(output, "#{app_path}/CMakeLists.txt")

    end
  end
end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
