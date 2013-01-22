################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

streamer_hash = { 
  :name => 'Table_streamer',
  :public_header_section => true,
  :brief => 'Prints data in table - like output from database query',
  :descr => '

Takes a table of data - which must be convertible to std::string with
boost::lexical_cast. Takes an optional header.

',
  :streamable_inline_custom => true,
  :template_decls => 
  [
   'typename MatrixContainer',
   'typename T = typename MatrixContainer::value_type::value_type',
  ],
  :forward_typedefs =>
  [
   'typedef std::vector< std::string > String_list_t',
  ],
  :post_class_section => true,
  :public_typedefs =>
  [
   'typedef typename MatrixContainer::value_type Row_container_t',
#   'typedef std::vector< T, ALLOC > Item_list_t',
#   'typedef std::vector< Item_list_t, ALLOC_OUTER > Item_table_t',
  ],
  :members => 
  [
   { 
     :name => 'matrix_container',
     :cpp_type => 'MatrixContainer',
     :member_ctor => true,
     :pass_by_ref => true,
     :store_by_cref => true,
     :access => Codegen::Access::RO,
   },
   { 
     :name => 'header',
     :cpp_type => 'String_list_t',
     :store_by_cref => true,
     :member_ctor_defaulted => true,
     :pass_by_ref => true,
     :init => 'String_list_t()',
     :access => Codegen::Access::RO,
   },
  ]
}

# streamer_specialized = Marshal.load(Marshal.dump(streamer_hash))
# streamer_specialized[:template_specializations] = { 'T' => 'bool' }
# streamer_specialized[:streamable_inline_custom] = false
lib = 
  Library.new({ 
                :classes => 
                [
                 CppClass.new({ 
                                :header_includes => 
                                [ 
                                 'fcs/utils/streamers/containers.hpp',
                                 'boost/lexical_cast.hpp', 
                                 'boost/range.hpp', 
                                 'vector', 
                                 'algorithm',
                                 'iostream',
                                ],
                                :name => 'table',
                                :pre_class_section => true,
                                :no_class => true,
                                :include_unit_test => true,
                                :additional_classes => 
                                [
                                 CppClass.new(streamer_hash),
#                                 CppClass.new(streamer_specialized),
                                ]
                              })
                ],
                :header_only => true,
                :static_only => true,
                :namespace => ['fcs', 'utils', 'streamers', 'table'],
                :no_api_decl => true,
              })

