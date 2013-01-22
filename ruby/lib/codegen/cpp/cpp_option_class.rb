################################################################################
# Support for options processing for applications
################################################################################
require 'tenjin'
require 'pathname'
require 'place'
require 'codegen/cpp'
require 'codegen'
require 'place'

module Codegen::Cpp

  class CppCommandOption
    attr_accessor \
    :name, :short_name, :long_name, :is_multiple, :arg_required, :opt_required, \
    :cpp_type, :default_value, :help_text, :descr, :cpp_list_type, :cpp_member_type

    def initialize(data={})
      @name = data[:name]
      @short_name = data[:short_name]
      @long_name = (data[:long_name] or @name)
      @is_multiple = (data[:is_multiple] or false)
      @cpp_type = (data[:cpp_type] or 'int')
      if @cpp_type == 'bool'
        @arg_required = data[:arg_required]
      else
        @arg_required = true
      end
      @opt_required = (data[:opt_required] or false)
      @descr = data[:descr]
      @default_value = data[:default_value]
      @cpp_list_type = nil
      @cpp_list_type = "#{name.capitalize}_list_t" if is_multiple
      @cpp_member_type = (@cpp_list_type or @cpp_type)
    end

  end


  class CppOptionParserGenerator

    attr_accessor \
    :name, :class_name, :namespace, :descr, :brief, :options, \
    :cpp_class_decl, :cpp_class_impl, :cpp_class, :disable_windows_warnings, \
    :no_block_indenter, :get_decription_method_name, :options_object_name, \
    :description_method_name, :standard_logging, :standard_otl_logging, \
    :header_includes

    def initialize(data={})
      @name = data[:name]
      @standard_logging = data[:standard_logging]
      @standard_otl_logging = data[:standard_otl_logging]
      @class_name = (data[:class_name] or "#{name}_program_options")
      @namespace = data[:namespace]
      @brief = data[:brief]
      @descr = data[:descr]
      @brief = descr if !brief and descr !~ /\n/
      @options = data[:options]
      @header_includes = (data[:header_includes] or [])

      @options << { 
        :name => 'log_level',
        :cpp_type => 'int',
        :default_value => 3,
        :descr => 'Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7)',
      } if ((options.select { |o| o[:name] == 'log_level' }.empty?) and standard_logging)

      @options << { 
        :name => 'otl_log_level',
        :cpp_type => 'int',
        :descr => 'Number in mask {Level_1=1 (connect/disconnect), Level_2=2, Level_3=4 (selects), Level_4=8 (selects + parms), Level_5=16 (parm streaming)}',
      } if ((options.select { |o| o[:name] == 'otl_log_level' }.empty?) and standard_otl_logging)

      @disable_windows_warnings = (data[:disable_windows_warnings] or [])
      @no_block_indenter = (data[:no_block_indenter] or false)
      @options_object_name = "#{name.downcase}_options"
      @description_method_name = "get_#{options_object_name}_description"

      @options.unshift(
                       { 
                         :name => 'help',
                         :short_name => 'h',
                         :cpp_type => 'bool',
                         :descr => 'Prints this help message',
                       }
                       )
      error_headers_required = false
      opts = []
      @options.each do |opt|
        opts.push(CppCommandOption.new(opt))
        error_headers_required = true if opts[-1].arg_required
      end

      @options = opts
      type_field_array = @options.collect {|o| [ o.cpp_member_type, o.name ] }
      type_field_array.push [ 'boost::program_options::variables_map', 
                              'parsed_program_options', 
                              'allows access to program_options that were parsed',
                              { :streamable => false, :comparable => false } ]
      streamers_included = @options.select {|o| o.is_multiple }.length > 0

      public_typedefs = []
      options.each do |opt|
        if opt.is_multiple
          public_typedefs.push "typedef std::vector< #{opt.cpp_type} > #{opt.cpp_list_type}"
        end

      end

      engine = Tenjin::Engine.new()
      place = Place.place()

      @cpp_class = CppClass.create_pod(@class_name, @descr, type_field_array,
                                       { 
                                         :streamable => true, 
                                         :streamers_included => streamers_included,
                                         :debug_dump => true,
                                         :namespace => @namespace,
                                         :public_typedefs => public_typedefs,
                                         :header_includes => ['boost/program_options.hpp'] + header_includes,
                                         :disable_windows_warnings => @disable_windows_warnings,
                                         :comparable => false,
                                         :no_block_indenter => @no_block_indenter,
                                         :brief => brief,
                                         #:member_access => Codegen::Access::RO,
                                       })

      @cpp_class.additions_impl = 
        engine.render("#{place['rb_codegen_tmpl']}/cpp_option_class_additional_impl.tmpl", 
                      { :copg => self })      
      @cpp_class.additions_header_post_class = 
        engine.render("#{place['rb_codegen_tmpl']}/cpp_option_class_additional_decl.tmpl", 
                      { :copg => self })      

      if error_headers_required
        @cpp_class.impl_includes.push "sstream"
        @cpp_class.impl_includes.push "exception"
      end

    end
  end

end

if $0 == __FILE__

  c = Codegen::Cpp::CppOptionParserGenerator.new( {
                                                    :name => 'Foo',
                                                    :namespace => ['utils','goo',],
                                                    :descr => 'cool stuff',
                                                    :options => [
                                                                  { 
                                                                    :name => 'goo',
                                                                    :short_name => 'g',
                                                                    :is_multiple => true,
                                                                    :descr => 'save this for lunch',
                                                                  },
                                                                  { 
                                                                    :name => 'moo',
                                                                    :short_name => 'm',
                                                                    :cpp_type => 'std::string',
                                                                    :descr => 'save this for dinner',
                                                                    :is_multiple => true,
                                                                  },
                                                                  { 
                                                                    :name => 'voo',
                                                                    :cpp_type => 'std::string',
                                                                    :default_value => '"foobar"',
                                                                    :descr => 'never eat this',
                                                                  }

                                                                 ]
                                                  })

  #puts c
  require 'pp'
  #pp(c)
  puts "**** IMPL_CONTENTS BEGIN ****\n", c.cpp_class.impl_contents, "\n**** IMPL_CONTENTS END ****\n"
  puts "**** DECL_CONTENTS BEGIN ****\n", c.cpp_class.header_contents, "\n**** DECL_CONTENTS END ****\n"

end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
