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
                          :name => 'H5_api',
                          :is_api_header => true,
                          :header_only => true,
                          :brief => 'Basic support for interfacing with hdf5',
                          :forward_class_decls => 
                          [ 
                           'H5::DataSet',
                           'H5::H5File'
                          ],
                          :public_typedefs => 
                          [ 
                           typedef_shared_ptr_of('H5::DataSet', 'Data_set_ptr'),
                           typedef_shared_ptr_of('H5::H5File', 'H5_file_ptr'),
                           'typedef std::vector< hsize_t > Dimensions_t'
                          ],
                          :header_includes => [ 'H5public.h' ],
                          :enums => [  
                                     {
                                       :name => 'Cpp_type', 
                                       :brief => 'Enumerates data type mappings',
                                       :inline => true,
                                       :values => [
                                                    'CPP_TYPE_INT8', 
                                                    'CPP_TYPE_INT32',
                                                    'CPP_TYPE_INT64',
                                                    'CPP_TYPE_UINT8', 
                                                    'CPP_TYPE_UINT32',
                                                    'CPP_TYPE_UINT64',
                                                    'CPP_TYPE_FLOAT',
                                                    'CPP_TYPE_DOUBLE',
                                                    'CPP_TYPE_LONG_DOUBLE',
                                                    'CPP_TYPE_STRING',
                                                    'CPP_TYPE_UNMAPPED',
                                                   ],
                                     }, 
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
                        }),

           (md = CppClass.new({ 
                                :name => 'H5_meta_data',
                                :members => 
                                [
                                 { :cpp_type =>'boost::filesystem::path', 
                                   :brief => 'Path to an hdf5 file',
                                   :name =>'file_path', 
                                   :member_ctor =>true,
                                   :pass_by_ref =>true
                                 }, 
                                 { :cpp_type =>'H5_file_ptr', 
                                   :brief => 'The file wrapper',
                                   :name =>'file',
                                   :streamable =>false,
                                   :pass_by_ref =>true
                                 }, 
                                 { :cpp_type=>'hid_t', 
                                   :brief => 'The id for the opened file',
                                   :name =>'file_hid'
                                 }, 
                                 { :cpp_type =>'hid_t', 
                                   :brief => 'The id for the group "/"',
                                   :name =>'root_group_hid'
                                 }, 
                                 { :cpp_type =>'Data_set_detail_map_t', 
                                   :brief => 'Map of data_set location to its details',
                                   :name =>'data_set_detail_map'
                                 }, 
                                 { :cpp_type =>'std::ostringstream', 
                                   :brief => 'For internal logging',
                                   :name =>'log_stream',
                                   :streamable =>false,
                                 }, 
                                 { :cpp_type =>'boost::filesystem::path', 
                                   :brief => 'Path to group currently being processed on iteration',
                                   :name =>'current_path',
                                 }, 
                                 { :cpp_type =>'Object_id_to_path_t', 
                                   :brief => 'Map of object id to path of object',
                                   :name =>'object_id_to_path',
                                   :pass_by_ref => true
                                 }, 

                                ],

                                :public_typedefs => 
                                [ 
                                 'typedef std::map< std::string, Data_set_detail > Data_set_detail_map_t',
                                 'typedef std::map< hid_t, boost::filesystem::path > Object_id_to_path_t',
                                ],
                                :public_header_section => true,
                                :private_header_section => true,
                                :streamable_inline => true,
                                :ctor_member_init_inline_method => true,
                                #                              :ctor_default => true,
                                #                              :ctor_default_init_method => true,
                                #                              :ctor_default_init => true,
                                :disable_windows_warnings => [ '4251'],
                                :brief => 'Basic meta_data from hdf5 file',
                                :version_control_commit => true,
                                :header_includes => [ 
                                                     'fcs/utils/streamers/vector.hpp',
                                                     'fcs/utils/streamers/map.hpp',
                                                     'boost/filesystem/operations.hpp',
                                                     "H5public.h", 
                                                     "H5PacketTable.h",
                                                     "H5Cpp.h",
                                                     'boost/filesystem/path.hpp',
                                                     'pantheios/pantheios.hpp',
                                                     'pantheios/inserters/character.hpp',
                                                     'pantheios/inserters/integer.hpp',
                                                     'exception', 
                                                     'sstream', 
                                                     'vector',
                                                     'map',
                                                    ],
                                :impl_includes => [
                                                  ],
                                :include_unit_test => true,
                                :nested_classes => 
                                [ 
                                 CppClass.create_pod(
                                                     'Data_set_member_detail', 
                                                     'Metadata of the data_set member', 
                                                     [['Data_set_ptr', 'parent', 'Data_set holding member', 
                                                       { :streamable => false } ], 
                                                      ['std::string', 'name',],
                                                      ['H5T_class_t', 'h5_class',],
                                                      ['hid_t', 'data_type',],
                                                      ['hsize_t', 'offset',],
                                                      ['hsize_t', 'index',],
                                                      ['size_t', 'size', 'Size of member type in bytes', { :init => 0 } ],
                                                      ['Cpp_type', 'cpp_type', 'Mapping to cpp type', { :init =>'CPP_TYPE_UNMAPPED' } ],
                                                     ],
                                                     { :streamable_inline => true, 
                                                       :brief => 'Metadata of data_set member',
                                                       :default_ctor => true,
                                                       :op_equal => true,
                                                       :boost_equality_comparable => true,
                                                       :post_class_typedefs => [
                                                                                'typedef std::vector< Data_set_member_detail > Data_set_member_detail_list_t',
                                                                               ],
                                                       :header_includes => [ 'boost/tuple/tuple.hpp' ],
                                                     }
                                                     ),

                                 CppClass.create_pod('Data_set_detail', 
                                                     'Metadata of data_set', 
                                                     [
                                                      ['std::string', 'name',],
                                                      ['int', 'rank',],
                                                      ['Dimensions_t', 'dimensions'],
                                                      ['Data_set_member_detail_list_t', 'member_detail'],
                                                     ],
                                                     { :streamable_inline => true, 
                                                       :streamers_included => true,
                                                     }
                                                     )

                                ]
                              })),

           CppClass.new({ 
                          :name => 'H5_file_repository',
                          :descr => 

"Map of file path to open hdf5 file, with methods to add and retrieve files
from the repository. Singleton providing a single point of file retrieval.",


                          :singleton => true,
                          :members => [
                                       { :cpp_type =>'H5_file_map_t', 
                                         :name =>'h5_file_map',
                                         :pass_by_ref =>true,
                                         :access => Codegen::Access::RO,
                                       }, 
                                      ],
                          :public_typedefs => [ 'typedef std::map< boost::filesystem::path, H5_file_ptr > H5_file_map_t' ],
                          :brief => 'File path to hdf5 file',
                          :header_only => true,
                          :header_includes => 
                          [ 
                           'map', 
                           'H5Cpp.h',
                           'boost/filesystem/path.hpp',
                          ],
                          :public_header_section => true,
                        }),


           # Started this, but probably not worth it. Only real difference would be
           #
           #   void append(TYPE const& additional) {
           #      TYPE_STORED stored(additional);
           #      store_.append(stored);
           #   }
           #
           # Maybe better to do store_->append(Subtype(instance));


           #            CppClass.new({ 
           #                         :name => 'H5_random_access_subset_store',
           #                         :descr => "

           # Stores objects of type TYPE_STORED in an hdf5 data_set for basic random access
           # whose hdf5 data_set type (when used for creation) is specified by
           # H5_DATA_SET_SPECIFIER.  The TYPE_STORED is a subset of the TYPE class. For
           # instance if you have many large business objects, but you want only some of
           # the fields put in an hdf5 store. Similarly, if you have fields representing
           # object state that you want logged frequently the business object is of type
           # TYPE and the subset of fields representing the state to store is defined by
           # TYPE_STORED.

           # ",
           #                         :template_decls => [ 
           #                                              'typename TYPE',
           #                                              'typename TYPE_STORED',
           #                                              'typename H5_DATA_SET_SPECIFIER = TYPE_STORED',
           #                                             ],
           #                         :members => [
           #                                       { :cpp_type =>'Data_set_store_t &', 
           #                                         :name =>'store', 
           #                                         #:store_by_ref =>true,
           #                                         #:pass_by_ref =>true,
           #                                         :member_ctor => true}, 
           #                                      ],
           #                         #:ctor_member_init_inline_method => true,
           #                         :public_typedefs => [ 'typedef H5_random_access_store< TYPE_STORED, H5_DATA_SET_SPECIFIER > Data_set_store_t' ],
           #                         :brief => 'Store for subset of fields of TYPE',
           #                         :header_only => true,
           #                         :header_includes => [ 'fcs/h5/h5_random_access_store.hpp', ],
           #                         :public_header_section => true,
           #                         :include_unit_test => true,
           #                       })

          ]

lib = Library.new({ 
                    :descr =>

"Api to support accessing hdf5 files, including reading the meta data
associated with datasets in those files.",

                    :classes => classes,
                    :header_only => true,
                    :jam_requirements => [ 
                                          '/site-config//hdf5_hl_cpp',
                                          '/site-config//boost_filesystem',
                                         ],
                    :namespace => ['fcs', 'h5',]
                  })

