#######################################################################
# Support for generating c++ classes
#######################################################################
require 'rubygems'
require 'tenjin'
require 'pathname'
require 'place'
require 'pp'
require 'set'
require 'dump_trace'

module Codegen::Cpp

  $use_class_name_only_for_protect_blocks = true

  # $shared_ptr_type = 'boost::shared_ptr'
  $shared_ptr_type = 'std::shared_ptr'  

  def use_boost_shared_ptr
    return ('boost::shared_ptr' == $shared_ptr_type)
  end

  # Used to generate c++ classes.
  #
  # There are two types of constructors that can be automatically generated, a
  # <i>ctor_default</i> and <i>ctor_member_init</i>. 
  #
  # The former will be included if <i>ctor_default</i> attribute is true. In
  # this case the default ctor has all members initialized (based on the
  # <i>CppMember::init</i> attribute of each) and either an empty definition
  # or if <i>ctor_default_init_method</i> is set, a definition that calls
  # <i>ctor_default_init()</i>.
  #
  # The latter is a ctor that initializes members passed in as arguments and
  # will be included if any members have their <i>member_ctor</i> or
  # <i>member_ctor_defaulted</i> attribute set, indicating a
  # <i>ctor_member_init</i> is required. As with the <i>defualt_ctor</i> any
  # members with the attribute <i>CppMember::init</i> will be initialized with
  # the value of the attribute.
  class CppClass

    # <b><i>User Supplied:</i></b> The name of the class to generate
    attr_reader :name

    # <b><i>Program Supplied:</i></b> Sometimes the name of the ctor can
    # differ - e.g. if the class is pimpl< {name} >::implementation
    attr_accessor :ctor_name

    # <b><i>Optional:</i></b> The name of the header file (sans path) -
    # defaulted to <tt>"#{name}.hpp".downcase</tt>.  Only use if you don't
    # like the default
    attr_reader :header_filename

    # The name of the impl file (sans path) - defaulted to
    # <tt>"#{name}.cpp".downcase</tt>.  Only use if you don't like the default
    attr_reader :impl_filename

    # <b>User Supplied</b> The <b>detailed comment</b> for the class
    attr_reader :descr

    # <b>Calculated</b> Type of class 'struct' or 'class'
    attr_reader :cpp_class_type

    # <b><i>User Supplied:</i></b> The <b>brief comment</b> for the class
    attr_reader :brief

    # <b><i>User Supplied:</i></b> If true a boost shared pointer typedef
    # should be provided
    attr_reader :typedef_ptr

    # <b><i>User Supplied</b> If true a <b>const:</i></b> boost shared pointer
    # typedef should be provided
    attr_reader :typedef_const_ptr

    # <b><i>User Supplied:</i></b> If true a public code block will be
    # provided in the header with text <i>public header section</i>. Add
    # public custom code here.
    attr_reader :public_header_section

    # <b><i>User Supplied:</i></b> If true a protected code block will be
    # provided in the header with text <i>protected header section</i>. Add
    # protected custom code here.
    attr_reader :protected_header_section
    
    # <b><i>User Supplied:</i></b> If true a private code block will be
    # provided in the header with text <i>private header section</i>. Add
    # private custom code here
    attr_reader :private_header_section

    # <b><i>User Supplied:</i></b> If true a custom section is included before
    # the namespace in global scope
    attr_reader :global_header_section

    # <b><i>User Supplied:</i></b> If true a custom section is included inside
    # the namespace before the class definition.  This is a useful spot for
    # forward declarations of other namespace symbols
    attr_reader :class_forward_section

    # <b><i>User Supplied:</i></b> If true a custom section is included before
    # the class definition, inside the namespace.  This is useful for
    # providing global inline functions that the class references
    attr_reader :pre_class_section

    # <b><i>User Supplied:</i></b> If true a custom section is included after
    # the class definition, inside the namespace.  This is useful for
    # providing global inline functions that reference the class
    attr_reader :post_class_section

    # <b><i>User Supplied:</i></b> If true a custom section is provided inside
    # the boost serialize generated method, after fields have been
    # serialized. This is useful for validating/modifying successfully
    # serialized data
    attr_reader :serialize_followup_section

    # <b><i>User Supplid:</i></b> Provides a custom section at beginning of
    # the header file directly inside the namespace
    attr_accessor :header_namespace_begin_section

    # <b><i>User Supplid:</i></b> Provides a custom section at the header file
    # directly inside the namespace
    attr_accessor :header_namespace_end_section

    # <b><i>User Supplid:</i></b> Provides a custom section 
    # before the header file directly inside the namespace
    attr_accessor :header_pre_namespace_section

    # <b><i>User Supplid:</i></b> Provides a custom section 
    # after the header file directly inside the namespace
    attr_accessor :header_post_namespace_section


    # <b><i>User Supplied:</i></b> If true provides <tt>serializeToXml</tt>,
    # <tt>serializeToXmlFile</tt>, <tt>serializeFromXml</tt>,
    # <tt>serializeFromXmlFile</tt> using boost serialization
    attr_reader :xml_serializable
    
    # <b><i>User Supplied:</i></b> If true provides <tt>serializeToText</tt>,
    # <tt>serializeToTextFile</tt>, <tt>serializeFromText</tt>,
    # <tt>serializeFromTextFile</tt> using boost serialization
    attr_reader :text_serializable
    
    # <b><i>User Supplied:</i></b> If true provides
    # <tt>serializeToBinary</tt>, <tt>serializeToBinaryFile</tt>,
    # <tt>serializeFromBinary</tt>, <tt>serializeFromBinaryFile</tt> using
    # boost serialization
    attr_reader :binary_serializable
    
    # <b><i>Calculated:</i></b> Set to true <b>iff</b> one of <i><tt>[
    # xml_serializable, text_serializable, binary_serializable ]</tt></i> is
    # set
    attr_reader :boost_serializable

    # <b><i>User Supplied:</i></b> List of bases that should be
    # serialized. Default <tt>[]</tt>
    attr_reader :serialized_bases

    # <b><i>User Supplied:</i></b> List of public <i>non-virtual</i> base
    # classes with their initializer text. Therefore a list of pairs. For
    # example <tt>'bases_public' => [ ['Base1', 'Base1(goo)'], ...]</tt>.
    # Default <tt>[]</tt>.
    attr_reader :bases_public

    # <b><i>User Supplied:</i></b> List of public <i>virtual</i> base classes
    # with their initializer text. Therefore a list of pairs. For example
    # <tt>'bases_public_virtual' => [ ['Base1', 'Base1(goo)'],
    # ...]</tt>. Default <tt>[]</tt>.
    attr_reader :bases_public_virtual
    
    # <b><i>User Supplied:</i></b> List of private <i>non-virtual</i> base
    # classes with their initializer text. Therefore a list of pairs. For
    # example <tt>'bases_private' => [ ['Base1', 'Base1(goo)'],
    # ...]</tt>. Default <tt>[]</tt>.
    attr_reader :bases_private

    # <b><i>User Supplied:</i></b> List of private <i>virtual</i> base classes
    # with their initializer text. Therefore a list of pairs. For example
    # <tt>'bases_private_virtual' => [ ['Base1', 'Base1(goo)'],
    # ...]</tt>. Default <tt>[]</tt>.
    attr_reader :bases_private_virtual

    # <b><i>User Supplied:</i></b> List of protected <i>non-virtual</i> base
    # classes with their initializer text. Therefore a list of pairs. For
    # example <tt>'bases_protected' => [ ['Base1', 'Base1(goo)'],
    # ...]</tt>. Default <tt>[]</tt>
    attr_reader :bases_protected

    # <b><i>User Supplied:</i></b> List of protected <i>virtual</i> base
    # classes with their initializer text. Therefore a list of pairs. For
    # example <tt>'bases_protected_virtual' => [ ['Base1', 'Base1(goo)'],
    # ...]</tt>. Default <tt>[]</tt>
    attr_reader :bases_protected_virtual

    # <b><i>User Supplied:</i></b> List of forward class declarations. Used to
    # forward declare classes not neaded by the header to reduce dependencies.
    # For example - to forward declare a class <tt>namespace H5 { class
    # H5File; }</tt> add <tt>'forward_class_decls' => [ 'H5::H5File', ]</tt>
    attr_reader :forward_class_decls

    # <b><i>Calculated:</i></b> Used by codegen - represents the text
    # (e.g. <tt>namespace H5 { class H5File; }</tt>) associated with the
    # namespace specified class (e.g. <tt>'forward_class_decls' => [
    # 'H5::H5File', ]</tt>)
    attr_reader :forward_class_decls_parsed

    # <b><i>User Supplied:</i></b> List of forward declared classes available
    # from the namespace of the current class (i.e. requiring no scoping and
    # placed inside the namespace block
    attr_reader :namespace_forward_class_decls

    # <b><i>User Supplied:</i></b> List of enumerations that are scoped to the
    # class. <i>Default <tt>[]</tt></i>
    attr_reader :enums

    # <b><i>User Supplied:</i></b> List of enumerations that go before the
    # class definition.  Makes no sense for <i>classes</i> with
    # <tt>is_api_header</tt> set to <i>true</i>
    attr_reader :forward_enums

    # <b><i>User Supplied:</i></b> If true provides <tt>bool operator<(#{name}
    # const& rhs) const</tt>.  Members included in the comparison are
    # determined by the <tt>CppMember's</tt> <i>comparable</i> attribute,
    # which is true by default
    attr_reader :comparable

    # <b><i>User Supplied:</i></b> List of bases to include in <i>less
    # than</i> comparison function. <i>Default <tt>[]</tt></i>
    attr_reader :comparable_bases

    # <b><i>User Supplied:</i></b> If true provides <tt>bool operator<(#{name}
    # const& rhs) const</tt> as well as <tt>bool operator==(#{name} const&
    # rhs) const</tt> that use memcmp.
    attr_reader :memcmp_comparable

    # <b><i>Calculated:</i></b> List of members which are public. Not for
    # client code. To control public/protected/private use those attributes on
    # the member itself.
    attr_reader :public_members

    # <b><i>Calculated:</i></b> List of members which are protected. Not for
    # client code. To control public/protected/private use those attributes on
    # the member itself.
    attr_reader :protected_members
    
    # <b><i>Calculated:</i></b> List of members which are private. Not for
    # client code. To control public/protected/private use those attributes on
    # the member itself.
    attr_reader :private_members

    # <b><i>User Supplied:</i></b> If true provides <tt>std::ostream&
    # operator<<(std::ostream& out, #{@cls.name} const& item)</tt>
    attr_reader :streamable

    # <b><i>User Supplied:</i></b> If true provides <tt>std::ostream&
    # operator<<(std::ostream& out, #{@cls.name} const& item)</tt>
    # with stubbed out implementation
    attr_reader :streamable_custom

    # <b><i>User Supplied:</i></b> If true provides <tt>std::ostream&
    # operator<<(std::ostream& out, #{@cls.name} const& item)</tt>
    # inline. Useful for <i>PODs</i> and keeping classes <i>header_only</i>
    attr_reader :streamable_inline

    # <b><i>User Supplied:</i></b> If true provides <tt>std::ostream&
    # operator<<(std::ostream& out, #{@cls.name} const& item)</tt>
    # inline. Implementation is stubbed out with protect block
    attr_reader :streamable_inline_custom

    attr_reader :streamable_friend_decl_required

    # <b><i>User Supplied:</i></b> If true provides to_string_list method
    attr_reader :to_string_list

    # <b><i>User Supplied:</i></b> Bases to stream in this class's
    # <tt>std::ostream& operator<<(std::ostream& out, #{@cls.name} const&
    # item)</tt> method. If class was not specified as streamable or
    # streamable_inline but streamed_bases were provided, it will be set to
    # streamable_inline
    attr_reader :streamed_bases

    # <b><i>Calculated:</i></b> List of members to include in the
    # <tt>std::ostream& operator<<(std::ostream& out, #{@cls.name} const&
    # item)</tt> method. Not set by users. To control which members, update
    # the <i>comparable</i> attribute of the member.
    attr_reader :comparable_members

    # <b><i>User Supplied:</i></b> List of members in the class.
    attr_reader :members

    # <b><i>Calculated:</i></b> List of <i>static</i> members in the class,
    # determined by filtering on all members and finding those that are
    # static. To control this list, update the <i>static</i> attribute of the
    # members themselves.
    attr_reader :static_members 

    # <b><i>Calculated:</i></b> List of <i>non-static</i> members in the
    # class, determined by filtering on all members and finding those that are
    # not static. To control this list, update the <i>static</i> attribute of
    # the members themselves.
    attr_reader :non_static_members

    # <b><i>Calculated:</i></b> List of <i>streamable</i> members in the
    # class, determined by filtering on all members and finding those that are
    # streamable. To control this list, update the <i>streamable</i> attribute
    # of the members themselves.
    attr_reader :streamable_members

    # <b><i>Calculated:</i></b> List of <i>serializable</i> members in the
    # class, determined by filtering on all members and finding those that are
    # serializable. To control this list, update the <i>serializable</i> attribute
    # of the members themselves.
    attr_reader :serializable_members

    # <b><i>Calculated:</i></b> List of members that are readable. Members
    # with access <tt>Codegen::Access::RW</tt> and
    # <tt>Codegen::Access::RO</tt> are readable.
    attr_reader :readable_members

    # <b><i>Calculated:</i></b> List of members that are writable. Members
    # with access <tt>Codegen::Access::RW</tt> are writable
    attr_reader :writable_members

    # <b><i>Calculated:</i></b> List of members that are to appear in the
    # ctor. To control this list, update the <i>member_ctor</i> or
    # <i>member_ctor_defaulted</i> attribute of the members themselves.
    attr_reader :members_in_ctor

    # <b><i>User Supplied:</i></b> If true prefixes the generated ctor with
    # <tt>private:</tt> and then follows up with <tt>public</tt> after the
    # declaration
    attr_reader :ctor_default_is_private

    # <b><i>User Supplied:</i></b> If true prefixes the generated ctor with
    # <tt>protected:</tt> and then follows up with <tt>public</tt> after the
    # declaration
    attr_reader :ctor_default_is_protected

    # <b><i>User Supplied:</i></b> If true provides an empty default ctor with
    # implementation, defaulting all members as requested.
    attr_reader :ctor_default

    # <b><i>User Supplied:</i></b> If true provides an empty copy ctor with
    # implementation, defaulting all members as requested.
    attr_reader :ctor_copy

    # <b><i>User Supplied:</i></b> If true forces ctor_member
    attr_reader :ctor_member

    # <b><i>User Supplied:</i></b> Provides ability to templatize ctor_member
    attr_reader :ctor_member_template_decls

    
    # <b><i>User Supplied:</i></b> If true provides a default ctor
    # declaration.  Implementation must be provided by the user, which implies
    # any initialization of members must be done by hand. A better approach is
    # to use <i>ctor_default</i> with <i>ctor_default_init_method</i> and then
    # put any initialization code that occurs after member initialization in
    # the <tt>ctor_default_init()</tt> user supplied implmentation
    attr_reader :ctor_default_decl
    attr_reader :ctor_copy_decl

    attr_reader :declare_ctor_default_init
    attr_reader :declare_ctor_default_init_inline

    attr_reader :declare_ctor_copy_init
    attr_reader :declare_ctor_copy_init_inline

    attr_reader :declare_ctor_member_init
    attr_reader :declare_ctor_member_init_inline

    attr_reader :ctor_default_init_method
    attr_reader :ctor_default_init_inline_method

    attr_reader :ctor_copy_init_method
    attr_reader :ctor_copy_init_inline_method

    attr_reader :ctor_member_init_method
    attr_reader :ctor_member_init_inline_method

    attr_reader :ctor_default_init_section
    attr_reader :ctor_copy_init_section
    attr_reader :ctor_member_init_section

    # <b><i>User Supplied:</i></b> List of typedefs provided in the public
    # section of the class, near the top. Provide a list of typedef statements
    # (without the semicolons) (e.g. <tt>'public_typedefs' => [ 'typedef
    # boost::mutex mutex_t' ]</tt>). <i>Default <tt>[]</tt></i>
    attr_reader :public_typedefs
    
    # <b><i>Calculated:</i></b> Types of all public typedefs, created to scope
    # types of accessors that are hidden
    attr_reader :public_typedef_types

    # <b><i>User Supplied:</i></b> When pimpling a class the implementation
    # must be declared/defined at global scope (since the template base class
    # is). These typedefs will appear in the impl file ahead of the pimple
    # definition, allowing member types in the user facing class to not be
    # qualified (e.g. a namespace type for a member does not need to be
    # qualified since the user facing class is declared in the namespace). But
    # for this to work those types need to be available to the imple class
    # which is not scoped. Putting appropriate using statements in the
    # pimpl_typedefs addresses this.
    attr_reader :pimpl_typedefs

    # <b><i>User Supplied:</i></b> List of typedefs defined forward of the
    # class
    attr_reader :forward_typedefs

    # <b><i>User Supplied:</i></b> List of typedefs provided in the namespace
    # after the class definition.  This allows typedefs that include the class
    # itself. Provide a list of typedef statements (without the semicolons)
    # (e.g. <tt>'post_class_typedefs' => [ 'typedef std::vector< My_class >
    # My_class_list_t' ]</tt>)..  <i>Default <tt>[]</tt></i>
    attr_reader :post_class_typedefs

    # <b><i>User Supplied:</i></b> List of static const members defined in the
    # public section, near the top. <i>Default <tt>[]</tt></i>
    attr_reader :public_static_consts

    # <b><i>User Supplied:</i></b> List of global const variables defined
    # inside the namespace before the class definition. <i>Default
    # <tt>[]</tt></i>
    attr_reader :file_level_consts

    # <b><i>User Supplied:</i></b> If true makes the object a singleton
    attr_reader :singleton

    # <b><i>User Supplied:</i></b> If class is templatized, allows the passing
    # of template parameters to singleton base. So, if provided, the singleton
    # class will be derived from <tt>fcs::patterns::Singleton<
    # <i>singleton_base_template</i> ></tt>
    attr_reader :singleton_base_template

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # specified in a public section of the class. The text is indented
    # automatically.
    attr_reader :additions_public_header

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # specified in a protected section of the class. The text is indented
    # automatically.
    attr_reader :additions_protected_header

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # specified in a private section of the class. The text is indented
    # automatically.
    attr_reader :additions_private_header
    
    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # specified in a before the class definition and forward class
    # declarations. The text is indented automatically.
    attr_reader :additions_pre_include_header

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # in the implementation file before the inclusion of other headers. The
    # text is indented automatically.
    attr_reader :additions_pre_include_impl
    
    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # in the implementation file after generation of support for
    # <i>enums</i>. The text is indented automatically.
    attr_accessor :additions_impl

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # in the header file after class definition. The text is indented
    # automatically.
    attr_accessor :additions_header_post_class

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # in the header file directly inside the namespace
    attr_accessor :additions_header_namespace

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # in the header file after namespace is closed. The text is indented
    # automatically.
    attr_accessor :additions_header_post_namespace

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # before the namespace
    attr_accessor :additions_pre_namespace_header

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # before the namespace
    attr_accessor :additions_pre_namespace_impl

    # <b><i>Program Supplied:</i></b> Intended for code that generates
    # specific types of classes, this provides a direct placement of the text
    # before inside the namespace before the class definition
    attr_accessor :additions_namespace_forward_class

    # <b><i>User Supplied:</i></b> A list of windows warning identifiers to
    # disable during the class definition. For example, to disable warning
    # 4251, specify <tt>'disable_windows_warnings' => ['4251']</tt>
    attr_reader :disable_windows_warnings

    # <b><i>User Supplied:</i></b> If true includes
    # <tt>fcs/utils/streamers/containers.hpp</tt> to simplify streaming of
    # various container and pointer classes.
    attr_reader :streamers_included

    # <b><i>User Supplied:</i></b> If true includes a declaration for the
    # <i>non-virtual</i> dtor. The user must supply the implementation
    attr_reader :dtor_decl

    # <b><i>User Supplied:</i></b> If true includes a declaration for the
    # virtual dtor
    attr_reader :dtor_virtual_decl

    # <b><i>User Supplied:</i></b> If true includes a declaration of an inline
    # virtual dtor that is a no-op, defined just outside the class inside the
    # header.
    attr_reader :dtor_virtual_inline_noop

    # <b><i>User Supplied:</i></b> If true adds a a constructor with
    # codeblock in the cpp
    attr_reader :dtor_impl

    # <b><i>Calculated:</i></b> Determines the text to protect a header file
    # contents inside an <tt>##ifdef</tt>. The text is some combination of
    # namespace and file name.
    attr_reader :include_guard
    
    # <b><i>User Supplied:</i></b> A list of headers to include in the
    # generated header.  (e.g. <tt><i>'header_includes' => [
    # 'fcs/sample/sample.hpp', 'boost/filesystem/path.hpp', 'iosfwd',
    # ],</tt></i>
    attr_accessor :header_includes

    # <b><i>User Supplied:</i></b> A list of headers to include in the
    # generated impl file.  (e.g. <tt><i>'impl_includes' => [
    # 'fcs/sample/sample.hpp', 'boost/filesystem/path.hpp', 'iostream',
    # ],</tt></i>
    attr_accessor :impl_includes

    # <b><i>User Supplied:</i></b> If true provides method <tt>bool
    # operator==(#{name} const& rhs) const</tt>
    attr_reader :op_equal

    # <b><i>Calculated:</i></b> Determines the text contents of the <tt>bool
    # operator==(#{name} const& rhs) const</tt> method
    attr_reader :op_equal_text

    # <b><i>Calculated:</i></b> reference to Place.place() for accessing
    # various predefined paths
    attr_reader :place

    # <b><i>User Supplied:</i></b> List of template declarations for the class
    # (e.g. <tt>'template_decls' => [ 'typename T', 'int ARRAY_SIZE' ]</tt>
    attr_reader :template_decls

    # <b><i>Calculated:</i></b> Template text based on the
    # <i>template_decls</i> prefixing the class definition.
    attr_reader :template_decls_text

    # <b><i>User Supplied:</i></b> List of classes to be nested in this class
    attr_reader :nested_classes

    # <b><i>Calculated:</i></b> The class the nested class belongs to. This is
    # set by the CppLib class as it is iterating over classes
    attr_reader :nesting_class

    # <b><i>User Supplied:</i></b> List of additional classes to be included
    # in the header/impl of this class. A mechanism for grouping multiple
    # classes in a single file. The main class being generated is the
    # <i>owning class</i> of the additional classes
    attr_reader :additional_classes

    # <b><i>User Supplied:</i></b> If true additional classes come before the
    # primary (i.e. owning) class.  
    attr_reader :additional_classes_come_first

    # <b><i>User Supplied:</i></b> List of additional classes to be included
    # in the impl
    attr_reader :impl_classes

    # <b><i>User Supplied:</i></b> Set to true if this is an impl class,
    # which is a class that is hidden in another class's impl
    attr_accessor :impl_class

    # <b><i>User Supplied:</i></b> If true this class will derive from
    # boost::pimpl< >::pointer_semantics
    attr_accessor :pimpl_ptr

    # <b><i>User Supplied:</i></b> If true this class will derive from
    # boost::pimpl< >::pointer_value
    attr_accessor :pimpl_value

    # <b><i>Program Supplied:</i></b> If this is an impl_class supporting a
    # pimpl, user_exposed_type is the class exposed in the header
    attr_accessor :user_exposed_type


    # <b><i>Program Supplied:</i></b> If this is a pimpl, this is the hidden
    # class
    attr_accessor :pimpl_impl_class

    # <b><i>User Supplied:</i></b> If true additional parms come after the
    # member init ctor parms
    attr_reader :additional_ctor_parms_come_second

    # <b><i>Calculated:</i></b> The class that this additional class belongs
    # with. It is simply the class in whose header/impl this class will exist
    # as a sibling. This is set by the CppLib class as it is iterating over
    # classes
    attr_accessor :owning_class

    # <b><i>User Supplied</b> or <b>Calculated:</i></b> If true includes
    # pantheios libs in the jamfile. Automatically set to true if any include
    # has <i> =~/pantheios/</i>
    attr_reader :uses_pantheios

    # <b><i>User Supplied:</i></b> If true, CppLib will generate a unit test
    # for this class. All classes with unit tests in a given lib will be built
    # in a jamfile that specifies all the unit tests for that lib.
    attr_reader :include_unit_test

    # <b><i>User Supplied:</i></b> List of includes for the generated unit
    # test of this class (i.e. if <i>include_unit_test</i> is true)
    attr_reader :unit_test_includes

    # <b><i>Calculated:</i></b> The list of classes this class derives
    # from. This is determined by looking at <i>bases_public</i>,
    # <i>bases_protected</i>, <i>bases_private</i>. Not to be set directly.
    attr_reader :base_classes

    # <b><i>User Supplied:</i></b> If true indicates that this <i>CppClass</i>
    # instance is not really a class, but a header and an impl file (assuming
    # not <i>header_only</i>) for namespace and/or global code. For example,
    # you might create a CppClass named <tt>Foo_domain_support</tt> with the
    # <i>no_class</i> attribute and it might have several
    # <i>additional_classes</i> that actually comprise the implementation of
    # that support.
    attr_reader :no_class

    # <b><i>User Supplied:</i></b> If true indicates that this <i>CppClass</i>
    # instance is private to the library. The corresponding header will be
    # placed in the <i>impl_path</i> <b><i>TODO - needs test case:</i></b>
    attr_reader :lib_private

    # <b><i>User Supplied:</i></b> If true indicates that this <i>CppClass</i>
    # is really a holder for the api header. It sets the <i>no_class</i>
    # attribute and provides the windows dll declspecs.
    attr_reader :is_api_header

    # <b><i>User Supplied:</i></b> If true indicates that this <i>CppClass</i>
    # is an the holder for the api_header and is stored one level above the
    # namespace header files.
    attr_reader :is_namespace_header
    

    # <b><i>User Supplied:</i></b> If true includes <tt>Q_OBJECT</tt> macro at
    # top of class, as well as a slots protect block and puts the header of
    # the class into the Jamfile (since it must be processed)
    attr_reader :q_object

    # <b><i>User Supplied:</i></b> If true does not include block_indenter
    # logic.
    attr_reader :no_block_indenter

    # <b><i>User Supplied:</i></b> If true provides methods
    # <tt>to_property_tree</tt> and <tt>from_property_tree</tt> and related
    # methods
    attr_reader :property_tree

    # <b><i>User Supplied:</i></b> List of [ <i>CPP_TYPE</i>, <i>ARG_NAME</i>
    # ] pairs that are part of the <i>ctor_member_init</i>. These additional
    # parms appear before the member initializers in the paramater
    # list. (e.g. <tt>'additional_ctor_parms' => [[ 'QWidget *',
    # 'parent']]</tt> in <tt>My_class</tt> might produce a ctor like
    # <tt>My_class(QWidget * parent, std::string const& title) :
    # title_(title)...</tt>
    attr_reader :additional_ctor_parms

    # <b><i>User Supplied but Optional:</i></b> This is the text of the api
    # declarations for use in windows dlls. If provided in the <i>CppLib</i>
    # then it will be added to all the classes. If not provided at all, but
    # the library is <i>shared</i> (i.e. not <i>static_only</i> and not
    # <i>header_only</i>) then a reasonable api_decl will be provided
    # (<tt>@api_decl = [ @name.upcase, 'API'].join('_')</tt>) where the
    # library name has the namespace encoded in it.
    attr_reader :api_decl

    # <b><i>Calculated:</i></b> The text derived from the <i>api_decl</i>
    # which is either <tt>"#{api_decl} "</tt> or the empty string (for
    # non-shared libraries). Used for convenience in templates.
    attr_reader :api_decl_space
    
    # <b><i>User Supplied:</i></b> If true, does not provide an impl file, but
    # only a header.
    attr_reader :header_only

    # <b><i>User Supplied:</i></b> If true, comments accessor methods. Default
    # is <i>false</i> as the members themselves are commented so documenting
    # the accessors for those is overkill
    attr_accessor :accessor_docs

    # <b><i>Calculated:</i></b> Convenience attribute for codegen which
    # resolves to the c++ scoped name (e.g. <tt>foo::bar::My_class</tt>)
    attr_accessor :fully_qualified_name

    # <b><i>Calculated:</i></b> Defines what should be used to protect class
    # blocks. The default is to use fully-qualifed names, but this makes
    # refactoring difficult because all protect blocks with code are fixed at
    # a location. If only the classname is used - then moving the files can
    # keep the protect block text
    attr_accessor :protect_block_tag

    # <b><i>User Supplied:</i></b> List of strings that comprise the namespace
    # (e.g. <tt>[ 'foo', 'bar' ]</tt> for namespace <i>foo::bar</i>)
    attr_reader :namespace

    # <b><i>Set by CppLib:</i></b> If set <i>api_header=</i> will add the
    # appropriate api header to the list of headers. CppLib iterates over
    # classes and if it finds an appropriate <i>api_header</i> sets it for
    # each class in the lib. <b><i>TODO - needs test cases:</i></b>
    attr_reader :api_header

    # Path to root of source files, defaulted to <i>Place['cpp']</i>. Can be
    # used to output file to different location
    attr_reader :cpp_root_path

    # <b><i>Calculated:</i></b> Determines where the header should be placed
    # and is set to <tt>@place['cpp'] + <i>header_as_include</i></tt>. Used by
    # the generator to merge in the changes with the header at the
    # corresponding location.
    attr_reader :fqpath_header

    # <b><i>Calculated:</i></b> The fully qualified location of the cpp file
    attr_accessor :fqpath_impl

    # <b><i>Calculated:</i></b> The list of initializers for all base
    # classes. This is determined by looking at <i>bases_public</i>,
    # <i>bases_protected</i>, <i>bases_private</i> and pulling out the second
    # element (i.e. the initializer) for each. Not to be set directly, but
    # rather indirectly by setting <i>bases_public</i>,
    # <i>bases_protected</i>, and <i>bases_private</i>
    attr_reader :base_classes_init_text_lines

    # <b><i>User Supplied:</i></b> If true adds a pantheios log message on
    # construction
    attr_reader :log_ctor

    # <b><i>User Supplied:</i></b> If true adds a pantheios log message on
    # destruction
    attr_reader :log_dtor

    # <b><i>User Supplied:</i></b> If true adds support to log entire object
    # as packet table
    attr_reader :hdf5_log_support

    # <b><i>User Supplied:</i></b> Dictionary of subsets of attributes
    attr_reader :hdf5_log_groups

    # <b><i>Created:</i></b> Object responsible for generating log group code
    attr_reader :hdf5_log_group_manager

    # <b><i>Calculated:</i></b> Additional classes created for this class that
    # are neither nested or stored in the same file set, as are the
    # additional_classes
    attr_reader :sibling_classes

    # <b><i>User Supplied:</i></b> If true, class derives from
    # boost::exception and std::exception virtually.
    attr_reader :boost_exception

    # <b><i>User Supplied:</i></b> If true, class derives from
    # boost::exception and std::exception virtually.
    attr_reader :boost_noncopyable


    # <b><i>User Supplied:</i></b> List of class types this class observes
    # updates on. Will include <i>void observe(T const&)</i> for each class,
    # as well as stub implementation.
    attr_reader :observer_of

    # <b><i>User Supplied:</i></b> List of class types this class observes
    # updates on. Will include <i>void observe(T const&)</i> for each class
    # with stub inline implementation.
    attr_reader :observer_of_inline

    # <b><i>User Supplied:</i></b> List of [ class type, signal_variable_name,
    # < POINTER_TYPE > ] this class signals on. This adds members for
    # signalling.
    attr_reader :signaller_of

    # <b><i>User Supplied:</i></b> If true, and if not header only a reference
    # to the fcs::utils::Version_control_commit will be placed in the .cpp
    attr_reader :version_control_commit

    # <b><i>User Supplied:</i></b> If true the type is a struct
    attr_reader :struct

    # <b><i>User Supplied:</i></b> If true adorn's ctor's with explicit
    attr_reader :explicit

    # <b><i>Calculated:</i></b> For codegen
    attr_reader :explicit_tag

    # <b><i>Calculated:</i></b> True if type is templated
    attr_reader :templated

    # <b><i>Calculated:</i></b> Types gleaned from the template_decls
    attr_reader :template_types

    # <b><i>Calculated:</i></b> Joined text of types gleaned from the template_decls
    attr_reader :template_types_text

    # <b><i>User Supplied:</i></b> If true places these friend declarations in
    # the class
    attr_reader :friend_decls

    # <b><i>User Supplied:</i></b> If true times ctor init code
    attr_reader :time_ctor_init

    # Supplied by the lib containing the class
    attr_accessor :library

    # <b><i>User Supplied:</i></b> If true provides the api description in this header
    attr_accessor :describe_api

    attr_accessor :default_header_filename, :default_impl_filename

    attr_accessor :template_specializations
    attr_accessor :class_def_name

    # <b><i>Calculated:</i></b> Set to true if unit test added but no testing
    attr_reader :empty_unit_test

    # <b><i>User Supplied:</i></b> If true, hides as much as possible
    attr_reader :hide_impl

    # <b><i>User Supplied:</i></b> If true, declares the member init ctor in
    # header and puts implementation in impl file to encourage encapsulation
    attr_reader :hide_member_init_ctor

    # <b><i>User Supplied:</i></b> If true, declares the default ctor in
    # header and puts implementation in impl file to encourage encapsulation
    attr_reader :hide_default_ctor

    # <b><i>User Supplied:</i></b> If true, declares the copy ctor in
    # header and puts implementation in impl file to encourage encapsulation
    attr_reader :hide_copy_ctor

    # <b><i>User Supplied:</i></b> If true, hides comparable implementation
    attr_reader :hide_comparable

    # <b><i>User Supplied:</i></b> If true, hides op_equal
    attr_reader :hide_op_equal

    # <b><i>User Supplied:</i></b> List of QT classes to forward declare and
    # includ in impl
    attr_reader :qt_forward_class_decls

    # <b><i>User Supplied:</i></b> If true provides a method to reconstitute
    # an object to default state (using default ctor)
    attr_reader :reconstitute_method

    # <b><i>User Supplied:</i></b> If true provides debug_dump which can
    # be called from gdb to "pretty_print" the object
    attr_reader :debug_dump

    attr_reader \
    :header_path, :impl_path, \
    :header_as_include

    def initialize(data={})
      @initialize_data = data.clone

      # Nil default if not set attributes
      [ 

       :name, :ctor_name, :brief, :descr, :singleton, :singleton_base_template,
       :is_api_header, :is_namespace_header, :dtor_decl, :dtor_virtual_decl,
       :dtor_virtual_inline_noop, :dtor_impl, :ctor_default_is_private,
       :ctor_default_is_protected, :include_unit_test,
       :ctor_default_init_method, :ctor_member_init_method,
       :ctor_default_init_inline_method, :ctor_member_init_inline_method,
       :ctor_copy_init_method, :ctor_copy_init_inline_method,
       :streamable, :streamable_custom, :streamable_inline,
       :streamable_friend_decl_required, :streamable_inline_custom,
       :to_string_list, :xml_serializable, :text_serializable,
       :binary_serializable, :comparable, :memcmp_comparable, :header_only,
       :ctor_default_is_protected, :ctor_default_is_private,
       :public_header_section, :protected_header_section,
       :ctor_default_init_section, :ctor_copy_init_section, :ctor_member_init_section,
       :private_header_section, :global_header_section,
       :header_namespace_begin_section, :header_namespace_end_section,
       :header_pre_namespace_section, :header_post_namespace_section,
       :class_forward_section, :serialize_followup_section,
       :pre_class_section, :post_class_section, :accessor_docs, :lib_private,
       :property_tree, :q_object, :no_block_indenter, :api_decl,
       :ctor_default, :ctor_copy, :ctor_default_decl, :typedef_ptr, :typedef_const_ptr,
       :additional_classes_come_first, :cpp_root_path, :hdf5_log_support,
       :op_equal, :streamers_included, :boost_exception, :boost_noncopyable,
       :version_control_commit, :struct, :time_ctor_init,
       :additional_ctor_parms_come_second, :log_ctor, :log_dtor,
       :template_types_text, :templated, :ctor_member, :library,
       :describe_api, :empty_unit_test, :hide_member_init_ctor,
       :hide_default_ctor, :impl_class, :user_exposed_type, :pimpl_impl_class,
       :pimpl_value, :pimpl_ptr, :hide_impl, :hide_comparable, :hide_op_equal,
       :reconstitute_method, :debug_dump

      ].each do | attr |
        self.instance_variable_set("@#{attr.to_s}", data[attr])
      end

      # Empty list default if not set attributes
      [

       :namespace, :members, :additional_classes, :impl_classes,
       :impl_includes, :enums, :forward_enums, :disable_windows_warnings,
       :additional_ctor_parms, :bases_public, :bases_protected,
       :bases_private, :bases_public_virtual, :bases_protected_virtual,
       :bases_private_virtual, :public_static_consts, :file_level_consts,
       :header_includes, :unit_test_includes, :streamed_bases,
       :serialized_bases, :comparable_bases, :forward_class_decls,
       :namespace_forward_class_decls, :nested_classes,
       :additions_public_header, :additions_protected_header,
       :additions_private_header, :additions_pre_include_header,
       :additions_pre_include_impl, :additions_pre_namespace_impl,
       :additions_header_post_class, :additions_header_namespace,
       :additions_header_post_namespace, :additions_impl,
       :additions_pre_namespace_header, :additions_namespace_forward_class,
       :sibling_classes, :template_decls, :template_types, :public_typedefs,
       :public_typedef_types, :pimpl_typedefs, :forward_typedefs,
       :post_class_typedefs, :observer_of, :observer_of_inline, :signaller_of,
       :friend_decls, :qt_forward_class_decls, :ctor_member_template_decls

      ].each do |attr|
        if data[attr]
          self.instance_variable_set("@#{attr.to_s}", data[attr])
        else
          self.instance_variable_set("@#{attr.to_s}", [])
        end
      end

      # Empty hash default if not set attributes
      [
       :hdf5_log_groups,
      ].each do |attr|
        if data[attr]
          self.instance_variable_set("@#{attr.to_s}", data[attr])
        else
          self.instance_variable_set("@#{attr.to_s}", { })
        end
      end

      @members = members.collect { |m| (m.class == {}.class)? Member.new(m):m }
      @ctor_name = name if !ctor_name
      @hide_impl = true if is_pimpl
      if hide_impl
        @hide_member_init_ctor = true
        @hide_default_ctor = true if ctor_default
        @hide_copy_ctor = true if ctor_copy
        @hide_op_equal = true
        @hide_comparable = true
        @members.each do |m|
          m.hide_impl = true
        end
      end
      @prepared_for_codegen = nil
      @impl_path = nil
      @header_path = nil
      @class_def_name = @name

      @is_api_header = true if @is_namespace_header
      @template_specializations = (data[:template_specializations] or { })
      @cpp_class_type = (struct ? "struct":"class")
      @ctor_default_is_protected = true if singleton
      @default_impl_filename = "#{name}.cpp".downcase
      @default_header_filename = "#{name}.hpp".downcase
      @header_filename = (data[:header_filename] or @default_header_filename)
      @impl_filename = (data[:impl_filename] or @default_impl_filename)
      @public_typedefs = public_typedefs.map {|td| Codegen.clean_templates(td) }
      @public_typedef_types = public_typedefs.map { |td| $1 if td =~ /\s+(\w+)$/ }

      if @pimpl_ptr or @pimpl_value
        make_pimpl
      end
      @impl_classes.each do |c|
        c.impl_class = true
      end
      if (@impl_includes.select { |i| i =~ /streamers..*.hpp/ }.length() > 0) or
          additional_classes.collect {|c| c.streamers_included }.length > 0          
        @streamers_included = true 
      end
      self.impl_path=(Pathname.new(data[:impl_path])) if data[:impl_path]
      @no_class = (data[:no_class] or @is_api_header)
      @template_decls = template_decls.map {|template| Codegen.clean_templates(template) }
      @templated = ! @template_decls.empty?
      if templated
        template_decl_type = []
        if !template_specializations.empty?
          @forward_typedefs = []
          new_template_decls = []
          template_specializations.each_pair do |k,v|
            template_decls.each do |td|
              if td =~ /(\w+)\s+(\w+)(?:\s*=)?/
                if $2 == k
                  template_decl_type << v
                  #puts "Found templated => #{k}, #{v}"
                  public_typedefs.each do |td|
                    td.gsub!(/\b#{k}\b/, v)
                  end
                else
                  template_decl_type << $2
                  new_template_decls << "#{$1} #{$2}"
                end
              end
            end
          end
          @brief = "Specialization of #{name} on #{template_specializations.inspect}"
          @descr = nil
          @class_def_name += '< ' + template_decl_type.join(', ') + ' >'
          @template_decls = new_template_decls
        end
        @template_types = Codegen::Cpp.template_types_from_template_decls @template_decls
        @template_types_text = template_types.join(', ')
      end

      @post_class_typedefs = post_class_typedefs.map {|td| Codegen.clean_templates(td) }
      @comparable = (comparable or @memcmp_comparable)
      @op_equal = (op_equal or @memcmp_comparable)
      @place = Place.place()
      @cpp_root_path = @place['cpp'] if !@cpp_root_path
      self.header_path=(Pathname.new(data[:header_path])) if data[:header_path]
      if @time_ctor_init
        if ctor_default_init_inline_method or ctor_member_init_inline_method
          @header_includes << 'fcs/utils/performance/block_performance_counter_tracker.hpp'
        end
        if ctor_default_init_method or ctor_member_init_method
          @impl_includes << 'fcs/utils/performance/block_performance_counter_tracker.hpp'
        end
      end
      if (signaller_of.length > 0) or (observer_of_inline.length > 0) or (observer_of.length > 0)
          @header_includes << 'fcs/patterns/observer.hpp' 
      end
      signaller_of.each do |signaller|
        class_type, pointer_type, variable_name, lock_type, guard_type = signaller
        variable_name = class_type.downcase if !variable_name
        pointer_type = "#{shared_ptr_type}< #{class_type} >" if !pointer_type
        rest = ""
        rest += ", #{lock_type}" if lock_type
        rest += ", #{guard_type}" if guard_type
        members << Member.new( { 
                                 :cpp_type => "fcs::patterns::Signaller< #{class_type}, #{pointer_type}#{rest} >", 
                                 :name => variable_name,
                                 :streamable => false,
                                 :streamable_inline => false,
                                 :access => Codegen::Access::IA, 
                               } )
      end
      @members_in_ctor = @members.select { |m| m.member_ctor or m.member_ctor_defaulted }
      @explicit = Codegen.default_to_true_if_not_set(data, 'explicit')
      # Explicit if there is 1 non-defaulted member in ctor_member_init
      num_required_parms = @members.select {|m| m.member_ctor }.length + additional_ctor_parms.length
      num_defaulted_parms = @members.select {|m| m.member_ctor_defaulted }.length
      total_parms = num_required_parms + num_defaulted_parms
      maybe_should_be_explicit = (num_required_parms < 2) and total_parms >= 1 
      @explicit_tag = ((@explicit and maybe_should_be_explicit)? "explicit " : "")
      @enums = enums.collect { |e| (e.class == {}.class)? Enumeration.new(e):e }
      @forward_enums = forward_enums.collect { |e| (e.class == {}.class)? Enumeration.new(e):e }      
      @context = { :cls => self }      

      @dtor_decl = true if dtor_impl
      pantheios_in_header = false
      pantheios_in_impl = false
      if log_ctor
        if hide_default_ctor or hide_member_init_ctor
          pantheios_in_impl = true
        else
          pantheios_in_header = true
        end
      end

      if log_dtor
        if dtor_impl
          pantheios_in_impl = true
        else
          pantheios_in_header = true
        end
      end

      if pantheios_in_header
        @header_includes << 'pantheios/pantheios.hpp'
        @header_includes << 'pantheios/inserters.hpp'
      elsif pantheios_in_impl
        @impl_includes << 'pantheios/pantheios.hpp'
        @impl_includes << 'pantheios/inserters.hpp'
      end

      if boost_exception
        @bases_public_virtual << ['boost::exception', '']
        @bases_public_virtual << ['std::exception', '']
        @header_includes << 'exception'
        @header_includes << 'boost/exception/all.hpp'
      end

      @bases_private << ['boost::noncopyable', ''] if @boost_noncopyable

      boost_operators = [
                         :boost_less_than_comparable,
                         :boost_equality_comparable, 
                         :boost_addable, 
                         :boost_subtractable, 
                         :boost_multipliable, 
                         :boost_dividable, 
                         :boost_modable, 
                         :boost_orable, 
                         :boost_andable, 
                         :boost_xorable, 
                         :boost_incrementable, 
                         :boost_decrementable, 
                         :boost_left_shiftable, 
                         :boost_right_shiftable, 
                         # composites
                         :boost_totally_ordered, 
                         :boost_additive, 
                         :boost_multiplicative, 
                         :boost_integer_multiplicative, 
                         :boost_arithmetic, 
                         :boost_integer_arithmetic, 
                         :boost_bitwise, 
                         :boost_unit_steppable, 
                         :boost_shiftable, 
                        ]

      boost_operators.each do |boost_op|
        if data[boost_op]
          op = boost_op.to_s.sub("boost_", "")
          op = "boost::#{op}\< #{@name} \>"
          @bases_public.push [op, '']
          @header_includes += [
                               'boost/operators.hpp',
                              ]
        end
      end

      begin
        add_header_for('boost::shared_ptr', 'boost/shared_ptr.hpp')
        add_header_for('std::shared_ptr', 'memory')
        [
         'ptr_vector', 'ptr_array', 'ptr_deque', 'ptr_list', 'ptr_map', 'ptr_set',
         'ptr_unordered_map', 'ptr_unordered_set'
        ].each do |t|
          add_header_for("boost::#{t}", "boost/ptr_container/#{t}.hpp")
        end
        add_header_for('boost::function', 'boost/function.hpp')
        add_header_for('boost::filesystem', 'boost/filesystem.hpp')
        add_header_for('std::numeric_limits', 'limits')
        add_header_for('Fixed_size_char_array', 'fcs/utils/fixed_size_char_array.hpp')
        [ 'std::vector', 'std::list', 'std::deque', 'std::map', 'std::string', 'std::set' ].each do |t|
          add_header_for(t, t.split(/::/)[1])
        end
      end

      @enums.each do |e|
        scope_enum_to_class(e)
        add_headers_for_enum(e)
      end

      @boost_serializable = (@text_serializable or @xml_serializable or @binary_serializable)
      if text_serializable
        @header_includes += [
                             'boost/archive/text_iarchive.hpp',
                             'boost/archive/text_oarchive.hpp',
                            ]
      end

      if xml_serializable
        @header_includes += [
                             'boost/archive/xml_iarchive.hpp',
                             'boost/archive/xml_oarchive.hpp',
                            ]
      end

      if binary_serializable
        @header_includes += [
                             'boost/archive/binary_iarchive.hpp',
                             'boost/archive/binary_oarchive.hpp',
                            ]
      end

      if (@boost_serializable)
        @header_includes += 
          [
           'boost/serialization/nvp.hpp',
           'boost/serialization/utility.hpp',
           'boost/serialization/version.hpp',
           'fstream', ]        
      end
      
      @header_includes += ['string'] if @members.select { |m| m.cpp_type == 'std::string' }.length > 0
      @header_includes += ['boost/cstdint.hpp'] if @members.select { |m| m.cpp_type=~/boost::u?int/ }.length > 0
      @header_includes += ['cstdint'] if @members.select { |m| m.cpp_type =~ /^(?:std::)?u?int\d*_t$/ }.length > 0
      if (@typedef_ptr or @typedef_const_ptr)
        if use_boost_shared_ptr
          @header_includes += ['boost/shared_ptr.hpp'] 
        else
          @header_includes += ['memory'] 
        end
      end
      @header_includes += ['fcs/patterns/singleton.hpp'] if singleton

      if (not @header_includes.include? 'boost/property_tree.hpp') and @property_tree
        @header_includes.push 'fcs/utils/serialize/property_tree_utils.hpp'
      end
        
      if @bases_public.collect {|pair| pair[0] }.include? 'boost::noncopyable'
        @disable_windows_warnings.push(4275)
        @header_includes += ['boost/noncopyable.hpp'] 
      end

      if @enums.length>0
        all_inline = @enums.select { |e| !e.inline }.length == 0
        if all_inline
          @header_includes.push 'iostream'
        else
          @header_includes.push 'iosfwd'
          @impl_includes.push 'iostream'
        end
      end

      if @comparable or @op_equal
        @header_includes.push 'iso646.h'
      end

      if @hdf5_log_support
        @hdf5_log_groups[name] = members.collect { |m| m.name }
      end

      if @hdf5_log_groups.length>0
        @hdf5_log_group_manager = Codegen::Cpp::Hdf5LogGroup.new({'logged_class' => self, 'log_groups' => @hdf5_log_groups})
        @sibling_classes += hdf5_log_group_manager.logging_classes
      end

      containers_required = @members.select { |m| m.cpp_type =~ /std::(?:list|vector|deque|set|map)/ }.length > 0
      containers_required |= @public_typedefs.select { |td| td =~ /std::(?:list|vector|deque|set|map)/ }.length > 0
      @streamers_included = true if (streamable_inline or streamable or 
                                     streamable_inline_custom or streamable_custom) and containers_required

      warn "debug_dump useless without streaming" if debug_dump and !streamable_inline  and !streamable
      @header_includes.push 'fcs/utils/debug_support.hpp' if debug_dump
      if streamable_inline or additional_classes.select {|c| c.streamers_included }.length > 0
        @header_includes.push 'iostream'
        @header_includes.push 'fcs/utils/block_indenter.hpp' if not no_block_indenter
        @header_includes.push 'fcs/utils/streamers/containers.hpp' if streamers_included
      elsif streamable
        @header_includes.push 'iosfwd'
        @impl_includes.push 'iostream'
        @impl_includes.push 'fcs/utils/block_indenter.hpp' if not no_block_indenter
        @impl_includes.push 'fcs/utils/streamers/containers.hpp' if streamers_included
      end
    end

    def is_pimpl
      return (pimpl_value or pimpl_ptr)
    end

    def make_pimpl
      @impl_class = false
      @hide_member_init_ctor = true
      members.each do |m|
        m.hide_impl = true
        m.member_of_pimpl = true
      end
      @hide_default_ctor = true if @ctor_default
      @hide_copy_ctor = true if @ctor_copy
      members_copy = Marshal.load( Marshal.dump(@members) )
      impl_type_name = "pimpl< User_exposed_type_t >::implementation"
      members_copy.each do |m|
        m.public = true
        m.private = false
        m.protected = false
        m.access = Codegen::Access::IA
        m.cpp_type = "User_exposed_type_t::#{m.cpp_type}" if public_typedef_types.include? m.cpp_type
      end
      @header_includes.unshift "boost/pimpl/pimpl.hpp"
      @pimpl_impl_class = CppClass.new(
                                       { 
                                         :name => impl_type_name,
                                         :ctor_name => 'implementation',
                                         :public_header_section => true,
                                         :user_exposed_type => self,
                                         :ctor_default => true,
                                         :impl_class => true,
                                         :members => members_copy,
                                         :template_decls => [ '' ],
                                         :struct => true
                                       }
                                       )
      @ctor_member_init_inline_method = false
      @ctor_member_init_method = false
      members.each do |member|
        member.pimpl = true
      end
    end

    def prepare_for_codegen()
      return if @prepared_for_codegen

      @additional_classes.each do |c|
        #p "Adding headers #{c.header_includes.join(':')} from class #{c.name}"
        @header_includes += c.header_includes
        @forward_class_decls += c.forward_class_decls
      end

      @impl_classes.each do |c|
        @impl_includes += c.header_includes
        @impl_includes += c.impl_includes
      end

      @header_includes = Codegen::Cpp.resolve_include_lambdas(header_includes)
      @impl_includes = Codegen::Cpp.resolve_include_lambdas(impl_includes)

      # Handle ctor_default - init method and whether to declare it
      begin 
        if @ctor_default_decl or @ctor_default_is_private or @ctor_default_is_protected \
          or @ctor_default_init_method or @ctor_default_init_inline_method
          @ctor_default = true 
        end
        @declare_ctor_default_init = @ctor_default_init_method
        if additions_private_header =~ /ctor_default_init/ or additions_protected_header =~ /ctor_default_init/
          @declare_ctor_default_init = false
        end
        @declare_ctor_default_init_inline = @ctor_default_init_inline_method
        if additions_private_header =~ /ctor_default_init/ or additions_protected_header =~ /ctor_default_init/
          @declare_ctor_default_init_inline = false
        end
      end

      # Handle ctor_member - init method and whether to declare it
      begin 
        @declare_ctor_member_init = @ctor_member_init_method
        if additions_private_header =~ /ctor_member_init/ or additions_protected_header =~ /ctor_member_init/
          @declare_ctor_member_init = false
        end
        @declare_ctor_member_init_inline = @ctor_member_init_inline_method
        if additions_private_header =~ /ctor_member_init/ or additions_protected_header =~ /ctor_member_init/
          @declare_ctor_member_init_inline = false
        end
      end

      # Handle ctor_copy - init method and whether to declare it
      begin 
        @declare_ctor_copy_init = @ctor_copy_init_method
        if additions_private_header =~ /ctor_copy_init/ or additions_protected_header =~ /ctor_copy_init/
          @declare_ctor_copy_init = false
        end
        @declare_ctor_copy_init_inline = @ctor_copy_init_inline_method
        if additions_private_header =~ /ctor_copy_init/ or additions_protected_header =~ /ctor_copy_init/
          @declare_ctor_copy_init_inline = false
        end
      end

      @descr = '' if not @descr
      @api_header = nil
      self.api_decl = @api_decl
      if @singleton_base_template
        @bases_public << [ "fcs::patterns::Singleton< #{singleton_base_template} >", '']
      elsif @singleton
        @bases_public << [ "fcs::patterns::Singleton< #{name} >", '']
      end
      
      if header_only 
        if (streamable and not streamable_inline)
          warn "Prefer streamable_inline to streamable if header_only on #{name} - forcing streamable_inline"
          @streamable_inline = true
        end
        if (streamable_custom and not streamable_inline_custom)
          warn "Prefer streamable_inline_custom to streamable_custom if header_only on #{name} - forcing streamable_inline_custom"
          @streamable_custom_inline = true
        end
        @hide_default_ctor = false
        @hide_member_init_ctor = false
      end
      @streamable_inline = true if ((streamed_bases.length > 0) and (not streamable) and (not streamable_inline))
      @forward_class_decls_parsed = []

      ######################################################################
      # Crafted members
      ######################################################################
      @members.select { |m| m.hide_impl }.each do |member|
        # Before scoping the member, mark the return type as scoped if type found in class
        if public_typedef_types.include? member.cpp_type
          member.return_type_scoped = true
        end
        member.scoped_class_name = class_def_name
      end

      @comparable_members = []
      @members.each { |m| @comparable_members.push m if m.comparable } if @comparable
      @static_members = @members.select { |m| m.static } 
      @non_static_members = @members.select { |m| not m.static } 
      @streamable_members = @non_static_members.select { |m| m.streamable } 
      @serializable_members = @non_static_members.select { |m| m.serializable } 
      @readable_members = @members.select { |m| (m.access == Codegen::Access::RO) or (m.access == Codegen::Access::RW) } 
      @writable_members = @members.select { |m| m.access == Codegen::Access::RW } 
      @public_members = @members.select { |m| m.public } 
      @protected_members = @members.select { |m| m.protected } 
      @private_members = (members - public_members) - protected_members 
      if is_pimpl
        member_parms = Codegen.indent_absolute_text(member_ctor_parm_names.join(','+Codegen::NL), 1).lstrip
        @bases_public.unshift [ "pimpl< #{name} >::pointer_semantics", 
                                "pimpl< #{name} >::pointer_semantics(#{member_parms})" ] if pimpl_ptr
        @bases_public.unshift [ "pimpl< #{name} >::value_semantics",
                                "pimpl< #{name} >::value_semantics(#{member_parms})" ] if pimpl_value
      end
      @template_decls_text = """template < #{@template_decls.join(",\n           ")} > """

      @ctor_default_is_protected = true if(@singleton and @ctor_default)      
      @base_classes = []
      @base_classes_init_text_lines = []
      @bases_public.each { |b| @base_classes.push("public #{b[0]}"); @base_classes_init_text_lines.push("#{b[1]}") if b[1] != nil and b[1].length>0 } 
      @bases_public_virtual.each { |b| @base_classes.push("public virtual #{b[0]}"); @base_classes_init_text_lines.push("#{b[1]}") if b[1].length>0} 
      @bases_protected.each { |b| @base_classes.push("protected #{b[0]}"); @base_classes_init_text_lines.push("#{b[1]}") if b[1].length>0} 
      @bases_protected_virtual.each { |b| @base_classes.push("protected virtual #{b[0]}"); @base_classes_init_text_lines.push("#{b[1]}") if b[1].length>0} 
      @bases_private.each { |b| @base_classes.push("private #{b[0]}"); @base_classes_init_text_lines.push("#{b[1]}") if b[1].length>0} 
      @bases_private_virtual.each { |b| @base_classes.push("private virtual #{b[0]}"); @base_classes_init_text_lines.push("#{b[1]}") if b[1].length>0} 
      members_with_init = @members.select { |m| m.init } 
      if (not members_with_init.empty?) and not (@ctor_default or not @members_in_ctor.empty? or not @additional_ctor_parms.empty?)
        puts "Warning #{name} has members with init but no ctor requested:"
        " [#{members_with_init.collect {|m| m.name }.join(',')} ]."
        " Either put them in the <member_init>ctor, specify ctor_default, or don't bother providing an init." 
      end

#      print "adclasses #{@additional_classes}"

      @impl_includes << 'fcs/utils/version_control_commit.hpp' if version_control_commit
      all_includes = @impl_includes + @header_includes
      @uses_pantheios = true if all_includes.select { |h| h.to_s =~ /pantheios/ }.length > 0

      begin 
        qt_type_members = members.map {|m| $1 if m.cpp_type =~ /(Q\w+)(?:\s+\*)?/}.delete_if {|x| x.nil? }
        qt_type_members += base_classes.map {|m| $1 if m =~ /(Q\w+)/}.delete_if {|x| x.nil? }
        qt_type_members = Codegen::Cpp::QtGuiHeaders.intersection(qt_type_members).to_a.sort!
        qt_type_members.each do |qttm|
          @header_includes << "<#{qttm}>"
        end
        @qt_forward_class_decls.each do |qtfcd|
          @forward_class_decls << "Qt::#{qtfcd}"
          @header_includes << "<#{qtfcd}>"
        end
      end

      @forward_class_decls.each do |fcd|
        ns = fcd.split('::')
        if ns.length>1
          @forward_class_decls_parsed.push " class #{ns.pop}; "
          ns.reverse_each do |namespace|
            @forward_class_decls_parsed[-1] = "namespace #{namespace} { #{@forward_class_decls_parsed[-1]} }"
          end
        else
          @forward_class_decls_parsed.push "class #{fcd};"
        end
      end

      @streamable_friend_decl_required = (streamable or streamable_inline or 
        streamable_custom or streamable_inline_custom)

      @engine = Tenjin::Engine.new(:path => [ Place['rb_codegen_tmpl'].to_s])

      warn "observer_of on header_only #{name}, use observer_of_inline!" if observer_of.length>0 and header_only
      @prepared_for_codegen = true
    end

    def render(template, context = nil)
      context = @context if !context
      # p "Context keys #{context.keys}"
      prepare_for_codegen
      @engine.render(template, context)
    end

    def namespace=(ns)
      if not namespace or namespace.length == 0
        @namespace = ns
        @fully_qualified_name = ns.join('::') + '::' + class_def_name
        @protect_block_tag = $use_class_name_only_for_protect_blocks? @class_def_name : @fully_qualified_name
        #puts "PROTECT BLOCK TAG #{protect_block_tag}"
        @include_guard = "_#{ns.join('_').upcase + '_' + @name.upcase}_H_"
        #p "Namespace now assign skipped #{ns} already at #{namespace} with #{include_guard}"
      else
        #p "Namespace assign skipped #{ns} already at #{namespace} with #{include_guard}"
      end
    end

    def header_as_include=(path, relative_from_path = cpp_root_path)
      path_from_fcs = path.relative_path_from(relative_from_path)
      if  path_from_fcs.to_s !~ /^\./
        @header_as_include = path_from_fcs
      else
        @header_as_include = path
      end
      @impl_includes.unshift @header_as_include if (@header_as_include and not @impl_class)
    end

    def header_path=(path)
      if path and not @header_path
        #p "Setting header_path #{path} #{path.basename} #{is_api_header} for #{name}"
        #p "TL SETTING HEADERPATH #{header_path} on #{name}"
        path = Pathname.new(path) if path.class != Pathname 
        if (path.basename.to_s == name) and is_namespace_header
          path = path.parent
        end
        @header_path = path
        
        # dump_trace "header_path= being called on #{name}"
        if owning_class
          #p "Setting header for #{name} to owning class header to #{path + owning_class.header_filename}"
          self.header_as_include=(path + owning_class.header_filename)
        else
          #p "Setting header for #{name} non-owning header to #{path + header_filename}"
          self.header_as_include=(path + header_filename)
        end

        additional_classes.each do |ac|
          #p "SETTING HEADERPATH #{header_path} on #{ac.name}"
          ac.header_path = path
        end

        impl_classes.each do |ic|
          ic.header_path = path
        end

        @fqpath_header = @cpp_root_path + header_as_include
      end
    end

    def add_headers_for_class(klass)
      #p "Adding headers to #{name} for #{klass.name} -> #{klass.header_includes.join(', ')}"
      @header_includes += klass.header_includes
      @impl_includes += klass.impl_includes
    end

    def impl_path=(user_supplied_impl_path)
      user_supplied_impl_path = Pathname.new(user_supplied_impl_path)
      if not @impl_path
        @impl_path = @user_supplied_impl_path = user_supplied_impl_path
        @fqpath_impl = @impl_path + @impl_filename
        if @lib_private
          #puts "Setting header_path #{name} => #{impl_path}"
          # Note - clearing out header_path first so assignment logic goes through
          @header_path = nil
          self.header_path= @impl_path
        end
      end
    end

    def header_only=(val)
      @header_only = val
      enums.each do |e|
        if e.inline != val
          e.inline = val
          add_headers_for_enum(e)
        end
      end
      forward_enums.each do |e|
        if e.inline != val
          e.inline = val
          add_headers_for_enum(e)
        end
      end
      if header_only
        self.api_decl= nil
      end
    end

    def api_decl=(ad)
      @api_decl = ad
      @api_decl_space = (api_decl and "#{api_decl} " or "")
      #puts "Setting api_decl to #{ad} on class #{name}"
      enums.each do |e|
        e.scope_class = name if not is_api_header
        e.api_decl = api_decl
      end
    end

    def add_header_for(txt, header)
      if(txt == 'boost::shared_ptr' or txt == 'std::shared_ptr') 
        @header_includes += [header] if (members.select { |m| m.cpp_type.index(txt) }.length > 0)
        @header_includes += [header] if (public_typedefs.select { |t| t.index(txt) }.length > 0)
      else
        #p "add header for: #{name} => #{members.collect {|m| m.name }.join(',  ')}"
        @header_includes += [header] if (members.select { |m| m.cpp_type.index(txt) and not m.cpp_type.index('boost::shared_ptr') }.length > 0)
        @header_includes += [header] if (members.select { |m| m.init and m.init.to_s.index(txt) and not m.init.index('boost::shared_ptr') }.length > 0)
        @header_includes += [header] if (public_typedefs.select { |t| t.index(txt) and not t.index('boost::shared_ptr') }.length > 0)
      end
    end

    def ctor_default_member_init_text()
      result = []
      if !pimpl_value and !pimpl_ptr
        non_static_members.each do |member|
          result.push("#{member.variable_name}(#{member.init})")
        end
      end
      result.join(",\n")
    end

    def ctor_copy_member_init_text()
      result = []
      if !pimpl_value and !pimpl_ptr
        non_static_members.each do |member|
          result.push("#{member.variable_name}(other.#{member.variable_name})")
        end
      end
      result.join(",\n")
    end

    def ctor_member_init_text_lines()
      base_classes_init_text_lines + member_ctor_member_init_text_lines
    end
    
    def member_ctor_member_init_text_lines()
      result = []
      if !pimpl_value and !pimpl_ptr
        last_index = non_static_members.length - 1
        non_static_members.each_with_index do |member, i|
          comma = (i == last_index)? '':','
          if member.member_ctor or member.member_ctor_defaulted
            result.push(member.ifdef "#{member.variable_name}(#{member.name})#{comma}") 
          else
            result.push(member.ifdef "#{member.variable_name}(#{member.init})#{comma}")
          end
        end
      end
      if result.empty?
        []
      else
        [ result.join("\n") ]
      end
    end

    def additional_ctor_parms_text_lines()
      additional_ctor_parms.collect {|type_parm| "#{type_parm[0]} #{type_parm[1]}" }
    end

    def members_that_are_parms
      non_static_members.select {|m| m.member_ctor or m.member_ctor_defaulted }
    end

    def member_ctor_member_parm_text_lines(exclude_default_assignments = false)
      result = []
      members_as_parms = members_that_are_parms
      last_index = members_as_parms.length - 1
      members_as_parms.each_with_index do |member, i|
        comma = (i == last_index)? '':','
        if member.store_by_ref 
          pass_type = member.pass_type_non_const
        else
          pass_type = member.pass_type_const
        end
        
        if member.member_ctor or member.member_ctor_defaulted
          if member.member_ctor_defaulted and !exclude_default_assignments
            result.push(member.ifdef "#{pass_type} #{member.name} = #{member.init}#{comma}")            
          else
            result.push(member.ifdef "#{pass_type} #{member.name}#{comma}") 
          end
        end
      end
      if result.empty?
        []
      else
        [ result.join("\n") ]
      end
    end

    def ctor_parm_text_lines
      if additional_ctor_parms_come_second
        return (member_ctor_member_parm_text_lines + additional_ctor_parms_text_lines)
      else
        return (additional_ctor_parms_text_lines + member_ctor_member_parm_text_lines)
      end
    end

    def member_ctor_parm_names      
      members_that_are_parms.each_with_index.map { |member, i| member.name }
    end

    def impl_contents()
      output = render("cpp_class_impl.tmpl")
      if impl_path and not impl_path.exist?
        impl_path.mkpath
      end
      output
    end

    def to_string_list_inline_def
      output = render("cpp_class_to_string_list_inline_def.tmpl")      
    end

    def jamfile_impl_src_name()
      Pathname.new(impl_filename).basename.to_s.split(/\./)[0]
    end

    def generate_impl()
      self.impl_path = @cpp_root_path + 'dead_code' if !impl_path
      if pimpl_impl_class
        pimpl_impl_text = render("cpp_class_pimpl_impl_definition.tmpl")
        @additions_pre_namespace_impl << pimpl_impl_text
      end
      
      guts = { 
        :filename => fqpath_impl.basename,
        :version_control_commit => version_control_commit,
        :brief => @brief,
        :includes => @impl_includes,
        :namespace => @namespace,
        :namespace_contents => impl_contents,
        :post_namespace_contents => additions_header_post_namespace,
        :pre_namespace_contents => additions_pre_namespace_impl,
        :pre_include_additions => additions_pre_include_impl,
        :include_namespace_custom => "namespace custom",
        :include_pre_namespace_custom => "pre-namespace custom",
      }

      guts[:fully_qualified_name] = protect_block_tag if $use_class_name_only_for_protect_blocks

      file_details = FileDetails.new(guts)
      file_details_context = { :file_details => file_details, :impl_classes => @impl_classes }
      output = render("cpp_file.tmpl", file_details_context)
      return Codegen.merge(Codegen.align_preprocessor(output), fqpath_impl)
    end

    def generate_unit_test(test_fqpath)
      output = render("unit_test.tmpl")
      #puts "Generating unit test class #{name} => #{header_as_include}"
      file_details = FileDetails.new({ 
                                       :filename => test_fqpath.basename,
                                       :includes => [ 
                                                      @header_as_include,
                                                      'pantheios/pantheios.hpp'
                                                     ],
                                       :namespace => [],
                                       :namespace_contents => output,
                                     })
      file_details_context = { :file_details => file_details }
      output = render("cpp_file.tmpl", file_details_context)
      result = Codegen.merge(Codegen.align_preprocessor(output), test_fqpath)
      @empty_unit_test = Codegen.merge_statistics[:non_empty_blocks][test_fqpath.basename].empty?
      warn "Unit Test EMPTY ON #{test_fqpath.basename}" if empty_unit_test
      return result
    end


    def generate_api_impl()
      output = render("cpp_api_impl.tmpl")
      if not impl_path.exist?
        impl_path.mkpath
      end
      return Codegen.merge(output, @fqpath_impl)
    end

    def class_definition()
      if nested_classes.length > 0
        result = render("cpp_class_definition.tmpl")
      else
        result = Codegen::Cpp.clean_accessors(render("cpp_class_definition.tmpl"), struct)
      end
      Codegen.clean_empty_lines(Codegen.trim_blank_lines(result))
    end

    def class_definition_wrapper()
      Codegen.clean_empty_lines(Codegen.trim_blank_lines(render("cpp_class_definition_wrapper.tmpl")))
    end

    def api_header_namespace_contents()
      Codegen.clean_empty_lines(Codegen.trim_blank_lines(render("cpp_api_header_namespace_contents.tmpl")))
    end
    
    def windows_api_decl()
      render("cpp_windows_api_decl.tmpl")
    end

    def header_contents()
      output = render("cpp_header.tmpl")
      # sometimes the public/protected/private decls double up...rather than track clean up
      output.gsub!(/public:\s+public:/ms, 'public:')
      output.gsub!(/protected:\s+protected:/ms, 'protected:')
      output.gsub!(/private:\s+private:/ms, 'private:')
      if header_path and not header_path.exist?
        header_path.mkpath
      end
      output
    end

    def generate_header()
      self.header_path = @cpp_root_path + 'dead_code' if !header_path
      Codegen.merge(header_contents, @fqpath_header)
    end

    def friend_template_decl name
      if @templated
        "template <#{template_types.map {|t| "typename #{t}_FRIEND" }.join(', ') } >\n#{name}"
      else
        name
      end
    end

    def friend_templatized name
      if @templated
        "#{name}< #{template_types.map {|t| "#{t}_FRIEND" }.join(', ')} >"
      else
        name
      end
    end

    def template_decl name
      if @templated
        "template < #{template_types.map {|t| "typename #{t}" }.join(', ')} >\n#{name}"
      else
        name
      end
    end

    def templatized name
      if @templated
        "#{name}< #{template_types_text} >"
      else
        name
      end
    end

    def scoped name
      if @nesting_class
        return "#{nesting_class.name}::#{name}"
      else
        return name
      end
    end

    def clean_header_includes
      # Clean includes - be sure to filter our own header_as_include
      result = Codegen::Cpp.clean_includes(header_includes.select {|h| h.to_s != header_as_include.to_s })
    end

    def clean_impl_includes
      #p "hfqp #{fqpath_header.inspect} implfqp #{fqpath_impl.inspect} hai #{header_as_include}"
      result = Codegen::Cpp.clean_includes(impl_includes)
    end

    def nesting_class=(c)
      @nesting_class = c
    end

    def api_header=(h)
      if !h
        return
      end
      @api_header = h
      if is_api_header
        impl_includes.unshift(h)
      else
        header_includes.unshift(h)
      end
    end

    def op_eq_decl()
      return "bool operator==(#{name} const& rhs) const;"
    end

    def op_eq_text()
      scope_text = hide_op_equal ? "#{scoped name}::" : ''
      result = ["bool #{scope_text}operator==(#{name} const& rhs) const {", "    return", "        ((this==&rhs) or (",]
      pieces = []
      comparable_bases.each do |base|
        pieces.push ["static_cast<#{base} const&>(*this)", "rhs"]
      end
      if memcmp_comparable
        pieces.push ["memcmp(this, &rhs, sizeof(#{name}))", "0"]
      else
        non_static_members.each do |m|
          if m.comparable
            pieces.push ["#{m.variable_name}", "rhs.#{m.variable_name}"]
          end
        end
      end

      terms = []
      pieces.each do |p|
        terms.push "        (#{p[0]} == #{p[1]})"
      end
      
      result.push terms.join(" and\n")
      result[-1] += "));\n}"
      result.join("\n")
    end

    def op_less_than_decl()
      return "bool operator<(#{name} const& rhs) const;"
    end

    def op_less_than_text()
      scope_text = hide_comparable ? "#{scoped name}::" : ''
      result = ["bool #{scope_text}operator<(#{name} const& rhs) const {", "    return"]
      pieces = []
      comparable_bases.each do |base|
        pieces.push ["static_cast<#{base} const&>(*this)", "rhs"]
      end
      if memcmp_comparable
        pieces.push ["memcmp(this, &rhs, sizeof(#{name}))", "0"]
      else
        non_static_members.each do |m|
          if m.comparable
            pieces.push ["#{m.variable_name}", "rhs.#{m.variable_name}"]
          end
        end
      end

      terms = []
      pieces.each do |p|
        terms.push "        ((#{p[0]} != #{p[1]})? #{p[0]} < #{p[1]} : ("
      end
      
      result.push terms.join("\n") + "false"
      result.push '        '+ (')' * terms.length*2) + ';'
      result.push '}'
      result.join("\n")
    end

    def op_less_than_eq_text_hist()
      result = ["bool operator<(#{name} const& rhs) const {", "    return"]
      pieces = []
      comparable_bases.each do |base|
        pieces.push ["static_cast<#{base} const&>(*this)", "rhs"]
      end
      if memcmp_comparable
        pieces.push ["memcmp(this, &rhs, sizeof(#{name}))", "0"]
      else
        members.each do |m|
          if m.comparable
            pieces.push ["#{m.variable_name}", "rhs.#{m.variable_name}"]
          end
        end
      end

      terms = []
      pieces[0..-2].each do |p|
        terms.push "        (#{p[0]} < #{p[1]} or (#{p[0]} == #{p[1]}"
      end
      terms.push "        (#{pieces[-1][0]} < #{pieces[-1][1]}"
      
      result.push terms.join(" and\n")
      result.push '        '+ (')' * (terms.length*2-1)) + ';'
      result.push '}'
      result.join("\n")
    end

    def scope_enum_to_class(e)
      e.scope_class = name if !no_class      
    end

    def add_headers_for_enum(e)
      if e.supports_picklist
        if e.inline
          header_includes.push 'cstring'
          header_includes.push 'stdexcept'
        else
          impl_includes.push 'cstring'
          impl_includes.push 'stdexcept'
        end
      end
    end

    def streamable_impl()
      #puts @name, @streamers_included, " streamability "
      render("cpp_streamable_impl.tmpl")
    end

    def property_tree_impl()
      render("cpp_property_tree_impl.tmpl")
    end

    def CppClass.create_pod(name, pod_description, type_field_array, additional_parms = { } )
      pod_members = []
      comparable = additional_parms[:comparable]
      member_access = (additional_parms[:member_access] or Codegen::Access::RW)
      member_public = member_access == Codegen::Access::RW;
      type_field_array.each do |field_type, field_name, field_description, member_additional_parms|
        parms = { 
          :cpp_type => field_type, 
          :brief => field_description,
          :name => field_name, 
          :public => member_public,
          :init => "#{field_type}()",                                                   
          :access => member_access }
        parms.merge! member_additional_parms if member_additional_parms
        pod_members.push(Codegen::Cpp::Member.new(parms))
      end
      ctor_default = true
      ctor_default = additional_parms[:ctor_default] if additional_parms.include? :ctor_default
      parms = { 
        :name => name, 
        :descr => pod_description, 
        :brief => additional_parms[:brief],
        :members => pod_members, 
        :comparable => comparable, 
        :ctor_default => ctor_default,
      }
      parms.merge! additional_parms
      c = CppClass.new(parms)
      return c
    end
  end
end

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
