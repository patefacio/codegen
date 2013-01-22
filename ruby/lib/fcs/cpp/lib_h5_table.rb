################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'

$cpp = ::Codegen::Cpp
$klass = $cpp::CppClass

classes = [



           $klass.new({ 
                        :name => 'H5_table_model',
                        :forward_typedefs =>
                        [
                         'using fcs::h5::H5_file_ptr',
                         'using fcs::h5::Data_set_ptr',
                        ],
                        :members => [
                                      { :cpp_type =>'boost::filesystem::path', 
                                        :brief => 'Location of hdf5 file with data_sets',
                                        :name =>'h5_file_path', 
                                        :member_ctor =>true,
                                        :pass_by_ref =>true,
                                        :protected =>true,
                                        :const => true,
                                        :access => Codegen::Access::RO}, 
                                      { :cpp_type =>'std::string', 
                                        :brief => 'Data_set name',
                                        :name =>'data_set_name', 
                                        :member_ctor =>true,
                                        :pass_by_ref =>true,
                                        :protected =>true,
                                        :access => Codegen::Access::RO}, 
                                      { 
                                       :cpp_type =>'H5_file_ptr', 
                                       :brief => 'Pointer to the opened file',
                                       :name =>'file', 
                                       :pass_by_ref =>true,
                                       :protected =>true,
                                       :streamable => false,
                                       :init => 'fcs::h5::H5_file_repository::get_instance()->open_file(h5_file_path.string().c_str())',
                                     }, 
                                     { 
                                       :cpp_type =>'Data_set_ptr', 
                                       :brief => 'Pointer to the data set vending the view',
                                       :name =>'data_set', 
                                       :pass_by_ref =>true,
                                       :protected =>true,
                                       :streamable => false,
                                       :init => 'new H5::DataSet(file_->openDataSet(data_set_name))',
                                     }, 
                                     # { 
                                     #   :cpp_type =>'int', 
                                     #   :brief => 'Number of dimensions',
                                     #   :name =>'data_set', 
                                     #   :pass_by_ref =>true,
                                     #   :protected =>true,
                                     #   :streamable => false,
                                     #   :init => 'new H5::DataSet(file_->openDataSet(data_set_name))',
                                     # }, 

                                     ],
                        :public_header_section => true,
                        :ctor_member_init_inline_method => true,
                        :bases_public => [ 
                                           ['fcs::table::Table_model', 
                                            'fcs::table::Table_model(create_table_meta_data(h5_file_path, data_set_name))']
                                          ],
                        :streamable_inline => true,
                        :streamed_bases => [ 'fcs::table::Table_model' ],
                        :include_unit_test => true,
                        :disable_windows_warnings => ['4251'],
                        :brief => 'Table model for hdf5 data_sets',
                        :version_control_commit => true,
                        :header_includes => [ 
                                             'fcs/h5/h5_meta_data.hpp',
                                             'fcs/h5/h5_file_repository.hpp',
                                             'fcs/table/table_model.hpp',
                                             'boost/filesystem/path.hpp',
                                             ],
                        :impl_includes => [ 
                                            'fcs/h5/h5_meta_data.hpp',
                                            'sstream', 
                                            'fcs/utils/streamers/containers.hpp',                                 
                                            'pantheios/pantheios.hpp',
                                           ],
                        :unit_test_includes => [
                                                'fcs/h5/h5_meta_data.hpp',
                                               ],
                      }),
          ]


lib = Codegen::Cpp::Library.new({ 
                                  :name =>'h5_table',
                                  :classes => classes,
                                  :static_only => true,
                                  :header_only => true,
                                  #:no_api_decl => true,
                                  :jam_requirements => 
                                  [
                                   '/site-config//hdf5_hl_cpp',
                                   '/site-config//boost_filesystem',
                                  ],
                                  :namespace => ['fcs', 'h5_table', ]
                                })

