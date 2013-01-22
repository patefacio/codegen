################################################################################
# Support for C++ members
################################################################################
require 'codegen'
require 'codegen/cpp'

module Codegen::Cpp

  # Used to store data required to generate members in CppClass
  #
  # =Generated Access
  #
  # The following attributes determine the access level of the attribute in the code.
  # [c++ access] public protected private
  #
  # Whereas the following attributes determine the method accessors in the code.
  # [Codegen::Access] RO, RW, IA
  #
  class Member

    # <b><i>User Supplied:</i></b> The c++ data type of the member
    attr_accessor :cpp_type

    # <b><i>User Supplied:</i></b> The c++ name of the member
    attr_reader :name

    # <b><i>User Supplied:</i></b> The detailed description of the member
    attr_reader :descr

    # <b><i>User Supplied:</i></b> The brief description of the member
    attr_reader :brief

    # <b><i>User Supplied:</i></b> Text required to initiliaze the member in
    # the ctor_member_init and/or ctor_default
    attr_reader :init

    # <b><i>User Supplied:</i></b> If true makes the variable static
    attr_reader :static

    # <b><i>User Supplied:</i></b> If true makes the variable mutable
    attr_reader :mutable

    # <b><i>User Supplied:</i></b> Set to one of
    # <tt>Codegen::Access</tt>. Default is <tt>Codegen::Access::IA</tt> if not
    # set
    attr_accessor :access

    # <b><i>User Supplied:</i></b> True indicates accessors should not be
    # inlined, just declared in class
    attr_accessor :hide_impl

    # <b><i>User Supplied:</i></b> True indicates member of pimpl class and
    # therefore accessors must go through (*this)->
    attr_accessor :member_of_pimpl

    # <b><i>User Supplied:</i></b> If true adds support for streaming
    # <tt>std::ostream &operator<<(...)</tt>
    attr_reader :streamable

    # <b><i>User Supplied:</i></b> If true provides a codeblock to custom
    # stream the value in <tt>std::ostream &operator<<(...)</tt>
    attr_reader :streamable_custom

    # <b><i>User Supplied:</i></b> If true adds support for serialization
    attr_reader :serializable

    # <b><i>User Supplied:</i></b> If true adds  for serialization
    attr_reader :serializable_custom

    # <b><i>User Supplied:</i></b> If true provides a codeblock to custom
    # serialize the member
    attr_reader :streamable_custom

    # <b><i>User Supplied:</i></b> If true makes the variable public
    attr_accessor :public

    # <b><i>User Supplied:</i></b> If true makes the variable protected
    attr_accessor :protected

    # <b><i>User Supplied:</i></b> If true makes the variable private
    attr_accessor :private

    # <b><i>User Supplied:</i></b> If true accessors pass the member by
    # reference
    attr_reader :pass_by_ref

    # <b><i>User Supplied:</i></b> If true the member is itself a reference
    attr_reader :store_by_ref

    # <b><i>User Supplied:</i></b> If true the member is itself a const
    # reference
    attr_reader :store_by_cref

    # <b><i>User Supplied:</i></b> If true the member is passed into the
    # <i>ctor_member_init</i>
    attr_reader :member_ctor

    # <b><i>User Supplied:</i></b> If true the member is passed into the
    # <i>ctor_member_init</i> with a default value
    attr_reader :member_ctor_defaulted

    # <b><i>Calculated:</i></b> Name of the c++ variable
    attr_reader :variable_name

    # <b><i>User Supplied:</i></b> If true member is included in comparable
    # method
    attr_reader :comparable

    # <b><i>Calculated:</i></b> Type for passing the variable as const -
    # either by value or by pass_by_ref depending on @pass_by_ref. Convenience attribute for
    # codegen
    attr_reader :pass_type_const

    # <b><i>Calculated:</i></b> Type for passing the variable as non-const -
    # either by value or by pass_by_ref depending on @pass_by_ref. Convenience attribute for
    # codegen
    attr_reader :pass_type_non_const
    
    # <b><i>User Supplied:</i></b> An override for how to pass variables in
    # the access method definitions.  Should almost never be needed
    attr_accessor :accessor_type

    # <b><i>User Supplied:</i></b> If set, member and accessors are conditional
    attr_accessor :ifdef_identifier

    # <b><i>Calculated:</i></b> True if type is fixed_size_char_array_size
    attr_accessor :is_fixed_size_char_array

    # <b><i>Calculated:</i></b> Special member for fixed size strings - keeps size
    attr_accessor :fixed_size_char_array_size

    # <b><i>User Special:</i></b> What to insert into the stream
    attr_accessor :stream_insert_override

    # <b><i>User Special:</i></b> Member is pointer type - so stream deref
    attr_accessor :stream_deref

    # <b><i>User Special:</i></b> Member is pointer type - so stream deref with address
    attr_accessor :stream_deref_with_address
    
    # <b><i>User Supplied</i></b> const qualifier
    attr_accessor :const

    # <b><i>User Supplied</i></b> volatile qualifier
    attr_accessor :volatile

    # <b><i>User Supplied</i></b> const volatile qualified c++ type
    attr_accessor :cvq_type

    # <b><i>User Supplied</i></b> If true initializes with array syntax
    attr_accessor :initialize_as_array

    # <b><i>User Supplied</i></b> If true desired member accessors may be
    # provided but the real members will appear in pimpl impl_class
    attr_accessor :pimpl

    # <b><i>Program Supplied</i></b>Declaration for reader
    attr_accessor :reader_decl

    # <b><i>Program Supplied</i></b>Implementation for reader
    attr_accessor :reader_impl

    # <b><i>Program Supplied</i></b>Declaration for reader of non const variety
    attr_accessor :reader_decl_non_const

    # <b><i>Program Supplied</i></b>Implementation for reader of non const variety
    attr_accessor :reader_impl_non_const

    # <b><i>Program Supplied</i></b>Declaration for writer
    attr_accessor :writer_decl

    # <b><i>Program Supplied</i></b>Implementation for writer
    attr_accessor :writer_impl

    attr_reader :scoped_class_name
    attr_accessor :return_type_scoped
    attr_accessor :static_text
    attr_accessor :const_text
    

    def initialize(data={})
      # Nil default if not set attributes
      [ 

       :cpp_type, :name, :descr, :brief, :init, :static, :mutable, :pass_by_ref,
       :store_by_ref, :store_by_cref, :accessor_type, :member_ctor,
       :member_ctor_defaulted, :public, :protected, 
       :fixed_size_char_array_size, :ifdef_identifier, :const, :volatile,
       :initialize_as_array, :stream_deref, :stream_deref_with_address,
       :hide_impl, :static_text, :const_text, :scoped_class_name,
       :return_type_scoped, :member_of_pimpl
       
      ].each do | attr |
        self.instance_variable_set("@#{attr.to_s}", data[attr])
      end

      puts data.to_yaml if !data[:name]
      @variable_name = data[:name].to_s + '_'
      @streamable = Codegen.default_to_true_if_not_set(data, :streamable)
      @streamable_custom = data[:streamable_custom]
      @streamable = true if streamable_custom
      @stream_insert_override = data[:stream_insert_override]
      @serializable = Codegen.default_to_true_if_not_set(data, :serializable)
      @serializable_custom = data[:serializable_custom]
      @serializable = true if serializable_custom
      @comparable = Codegen.default_to_true_if_not_set(data, :comparable)
      @private = (data[:private] or (not @public and not @protected))
      @access = data[:access]? data[:access] : Codegen::Access::IA
      @access = Codegen::Access::IA if @public
      make_accessor_text
    end

    def scoped_class_name=(scn)
      @scoped_class_name = scn
      make_accessor_text
    end

    def make_accessor_text
      i = Codegen.single_indent()
      @cpp_type = 'std::string' if (cpp_type.nil? or (cpp_type == 'string'))

      if cpp_type =~ /Fixed_size_char_array\s*<\s*(\d+)\s*>/
        @is_fixed_size_char_array = true
        @fixed_size_char_array_size = $1
      end

      @pass_by_ref = true if(cpp_type == 'std::string')
      if((not @init) and (@cpp_type =~ Codegen::Cpp::FUNDAMENTAL_TYPE_RE))
        warn("WARNING Uninitialized Fundamental Type Member: type=>" + @cpp_type + " member=>" + @name) 
      end
      @pass_type_const = (@pass_by_ref)? "#{@cpp_type} const&" : "#{@cpp_type}"
      @pass_type_non_const = (@pass_by_ref)? "#{@cpp_type} &" : "#{@cpp_type}"
      @cvq_type = (@const? "#{@cpp_type} const" : @cpp_type)
      @cvq_type = "#{@cvq_type} volatile" if @volatile
      @static_text = (static ? 'static ' : '')
      @const_text = (static ? '' : ' const')
      scn = ((scoped_class_name and hide_impl) ? "#{scoped_class_name}::" : '')
      return_type = accessor_type ? accessor_type : pass_type_const
      impl_return_type = "#{return_type_scoped ? scn : ''}#{return_type}"
      @reader_decl = "#{static_text}#{return_type} #{name}()#{const_text};\n"
      @reader_decl_non_const = "#{static_text}#{pass_type_non_const} #{name}();\n"
      impl_variable_text = member_of_pimpl ? "(*this)->#{variable_name}" : variable_name
      @reader_impl_non_const = "#{static_text}#{return_type_scoped ? scn : ''}#{pass_type_non_const} #{scn}#{name}() {
#{i}return #{impl_variable_text};
}
"
      @writer_decl = "#{static_text}void #{name}(#{return_type} val);\n"
      @writer_impl = "#{static_text}void #{scn}#{name}(#{return_type} val) {
#{i}#{impl_variable_text} = val;
}
"
      if accessor_type
        @reader_impl = "#{impl_return_type} #{scn}#{name}()#{const_text} {
#{i}return #{return_type}(#{impl_variable_text});
}
"
      else
        @reader_impl = "#{impl_return_type} #{scn}#{name}()#{const_text} {
#{i}return #{impl_variable_text};
}
"
      end
    end

    def ifdef text
      if ifdef_identifier
"#if defined(#{ifdef_identifier})
#{text}
#endif"     
      else
        text
      end
    end

    # Describes accessibility in codegen comments
    def access_text()
      result = case access
               when Codegen::Access::RW then "read/write"
               when Codegen::Access::RO then "read only"
               when Codegen::Access::IA then "inaccessible"
               end
      result = "open" if public
      result
    end

  end
end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
