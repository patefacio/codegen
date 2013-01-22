################################################################################
# Support for creating C++ enumerations
################################################################################
require 'codegen'
require 'place'

module Codegen::Cpp

  class Enumeration

    # <b><i>User Supplied:</i></b> Name of the enumeration
    attr_accessor :name

    # <b><i>User Supplied:</i></b> If true adds methods to go from string
    # (i.e. picklist representation) back to enum
    attr_accessor :supports_picklist

    # <b><i>User Supplied:</i></b> Brief description of the enumeration
    attr_accessor :brief

    # <b><i>User Supplied:</i></b> Use this to shorten or extend text
    # associated with the picklist. For example, if an enum with values like [
    # 'LONG_NAME_1', 'LONG_NAME_2' ], could have shortened text names with a
    # :pick_list_text_proc of proc {|x| x.gsub(/LONG_/, '').downcase}}),
    attr_accessor :pick_list_text_proc

    # <b><i>User Supplied:</i></b>Strings naming the enumerated values
    attr_accessor :values

    # <b><i>User Supplied:</i></b>In place of a named enumeration with values
    # you can create an anonymous compile time enumeration with a single
    # constant entry named name. No streaming provided.
    attr_accessor :const_value

    # <b><i>User Supplied:</i></b>If true the values are powers of 2 for bit
    # masking
    attr_accessor :mask

    # <b><i>User Supplied:</i></b>If true includes an entry marking the end
    # of the enum
    attr_accessor :include_last

    # <b><i>User Supplied:</i></b>If true the to_c_str, from_c_str are inline
    attr_reader :inline
    
    # For codegen - prototype decorations for to_c_str from_c_str
    attr_reader :proto_decorations

    # For codegen - implementation decorations for to_c_str from_c_str
    attr_reader :impl_decorations

    # For codegen - inline decorations for dump method
    attr_reader :dump_inline_decorations

    # For codegen - impl decorations for dump method
    attr_reader :dump_impl_decorations

    # For codegen - decorations for the inline masking functions
    attr_reader :bit_mask_decorations

    # For codegen - if enum is scoped to type and not inline it is the scoped name "#{scope_class}::#{txt}"
    attr_reader :scoped_type

    # An additional enum outside this enum used just to provide a size (@name.upcase + '_NUMBER_ENTRIES')
    attr_reader :size_enum_name

    # The strings used to identify the values in the enum
    attr_reader :pick_list_text_values

    # The api_decl for non-inline functions (to_c_str, from_c_str dump_)
    attr_reader :api_decl

    # Name of class the enum is scoped to or nil
    attr_reader :scope_class
    
    # Name of enum, scoped to a class, otherwise name of enum
    attr_reader :scope_name

    # Name of dump function for mask enums - which includes the enum name to
    # prevent collisions. Required since it takes an int as opposed to the
    # enumerated type - so if multiple such enums appeared in a class they
    # would collide
    attr_reader :dump_name

    # If actual values assigned to then entries are important
    attr_reader :assigned_values

    def initialize(data={})
      @name = data[:name]
      @values = data[:values]
      @brief = data[:brief]
      @const_value = data[:const_value]
      if const_value
        return
      end
      @supports_picklist = data[:supports_picklist]
      @mask = (data[:mask]? true : false)
      @assigned_values = data[:assigned_values]
      raise "Can not assign values to mask enum" if mask and assigned_values
      @size_enum_name = @name.upcase + '_NUMBER_ENTRIES'
      @include_last = data[:include_last]
      @values.push(@name.upcase + "_LAST") if @include_last
      @pick_list_text_proc = data[:pick_list_text_proc]? data[:pick_list_text_proc] : proc { |m| m }
      @pick_list_text_values = @values.map { |v| @pick_list_text_proc.call(v) }
      @api_decl = data[:api_decl]
      self.inline = data[:inline]
      self.api_decl = @api_decl
      self.scope_class = data[:scope_class]
      @template = Tenjin::Template::new()

      @engine = Tenjin::Engine.new(:path => [Place['rb_codegen_tmpl'].to_s])
    end

    def scope_to_class txt
      if scope_class and !inline
        "#{scope_class}::#{txt}"
      else
        txt
      end
    end

    def make_function_decorations
      @proto_decorations = (scope_class ? 'friend ' : "extern #{@api_decl} ")
      @impl_decorations = (scope_class and 
                           (inline and 'friend inline ' or "#{@api_decl} ") or
                           (inline and 'inline ' or "#{@api_decl} "))
      @bit_mask_decorations = (scope_class and 'friend inline ' or 'inline ')
      @dump_inline_decorations = (scope_class and 'static inline ' or 'inline ')
      @dump_impl_decorations = (inline and 'inline ' or "#{@api_decl} ")
      @scoped_type = scope_to_class(name)
    end

    def inline=(val)
      @inline = val
      make_function_decorations
    end

    def scope_class=(sc) 
      #puts "Scoping #{name} to #{sc} inline is: #{inline}"
      @scope_class = sc
      @scope_name = ((nil!=sc)? "#{sc}::#{@name}" : @name )
      @dump_name = "dump_#{@name.downcase}"
      make_function_decorations
    end

    def api_decl=(d)
      #puts "Setting api_decl to #{d} on #{@name}"
      if !inline
        @api_decl = d
      end
      make_function_decorations
    end

    def enum_header_contents()
      result = ""

      if const_value
        result += "//! #{brief}\n" if brief
        result += "enum { #{name} = #{const_value} };"
      else
        if mask
          result += @engine.render("cpp_mask_enum_declaration.tmpl", { :me => self })
          result += @engine.render("cpp_mask_enum_bit_functions.tmpl", { :me => self })
        else
          result += @engine.render("cpp_enum_declaration.tmpl", { :me => self })
        end

        if inline
          result += @engine.render("cpp_enum_stream_impl_support.tmpl", { :me => self }) if !mask
          result += @engine.render("cpp_mask_enum_dump_function_header.tmpl", { :me => self }) if mask
        else
          result += @engine.render("cpp_enum_static_lib_prototypes.tmpl", { :me => self })
        end

        result += @engine.render("cpp_enum_inline_insertion_operator.tmpl", { :me => self }) if !mask
      end
        
      return result
    end

    def enum_stream_ipml()
      if inline or const_value
        return ""
      end
      if mask
        @engine.render("cpp_mask_enum_dump_function_definition.tmpl", { :me => self })
      else
        @engine.render("cpp_enum_stream_impl_support.tmpl", { :me => self })
      end
    end
  end
end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
