################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

classes = [

           CppClass.new({ 
                          :name => 'H5_random_access_store',
                          :descr => "

Stores objects of type TYPE_STORED in an hdf5 data_set for basic random access
whose hdf5 data_set type (when used for creation) is specified by
H5_DATA_SET_SPECIFIER.

",
                          :template_decls => [ 
                                              'typename TYPE_STORED',
                                              'typename H5_DATA_SET_SPECIFIER = TYPE_STORED',
                                             ],
                          :forward_enums => [  
                                             {
                                               :name => 'Store_open_type', 
                                               :brief => 'Create, open for read or open for read and write',
                                               :inline => true,
                                               :values => [
                                                            'OPEN_CREATE', 
                                                            'OPEN_READ',
                                                           ],
                                             }, 
                                            ],

                          :members => [
                                       { :cpp_type =>'H5_file_ptr', 
                                         :name =>'file',
                                         :pass_by_ref =>true,
                                         :member_ctor => true,
                                         :access => Codegen::Access::RO,
                                       }, 
                                       { :cpp_type =>'Store_open_type', 
                                         :name =>'open_type',
                                         :member_ctor => true,
                                       },
                                       { :cpp_type =>'std::string', 
                                         :name =>'group',
                                         :member_ctor_defaulted => true,
                                         :init => 'std::string()',
                                       },
                                       { :cpp_type =>'FL_PacketTable_ptr', 
                                         :name =>'packet_table', 
                                         :pass_by_ref =>true,
                                         :access => Codegen::Access::RO,
                                       }, 

                                      ],
                          :ctor_member_init_inline_method => true,
                          #:time_ctor_init => true,
                          :public_typedefs => 
                          [ 
                           typedef_shared_ptr_of('FL_PacketTable', 'FL_PacketTable_ptr'),
                           typedef_vector_of('hid_t', 'Group_id'),
                          ],
                          :forward_typedefs =>
                          [
                           typedef_shared_ptr_of('H5::H5File', 'H5_file_ptr')
                          ],
                          #:additional_ctor_parms => [ ['char const*', 'file_path']],
                          :brief => 'Wrapper for packet table tailored to parameterized class',
                          :header_only => true,
                          :header_includes => [
                                               'fcs/utils/file_path.hpp',
                                               'sstream', 'exception', 
                                               'pantheios/pantheios.hpp', 
                                               'pantheios/inserters/integer.hpp',
                                               'H5Cpp.h', 'H5File.h', 'H5PacketTable.h', 
                                               'boost/filesystem/path.hpp',
                                              ],
                          :public_header_section => true,
                          :include_unit_test => true,
                        }),

]

lib = Library.new({ 
                    :classes => classes,
                    :header_only => true,
                    :jam_requirements => [ 
                                          '/site-config//hdf5_hl_cpp',
                                          '/site-config//boost_filesystem',
                                         ],
                    :namespace => ['fcs', 'h5', 'utils']
                  })
