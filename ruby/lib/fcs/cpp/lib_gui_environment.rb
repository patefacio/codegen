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
                          :name => 'Q_environment',
                          :q_object => true,
                          :header_includes => [ 
                                               'memory',
                                              ],
                          :impl_includes => [
                                             'fcs/environment.hpp',
                                             'pantheios/pantheios.hpp', 
                                             'pantheios/inserters/character.hpp', 
                                             'pantheios/inserters/integer.hpp',
                                             'boost/foreach.hpp',
                                             '<QVBoxLayout>', 
                                             '<QBoxLayout>', 
                                             '<QLabel>', 
                                             '<QHeaderView>', 
                                            ],
                          :public_header_section => true,
                          :private_header_section => true,
                          :public_typedefs => [
                                              ],
                          :members => [
                                       { :cpp_type =>'QTableWidget *', 
                                         :brief => 'List of variables and values',
                                         :name =>'variable_list_table', 
                                         :init =>'new QTableWidget()',
                                       }, 
                                       { :cpp_type =>'QSplitter *', 
                                         :brief => 'Main variables and the paths',
                                         :name =>'splitter', 
                                         :init =>'new QSplitter(this)',
                                       }, 
                                       { :cpp_type =>'Tree_path_model *', 
                                         :brief => 'Model for paths parsed from path variables stored in tree',
                                         :name =>'tree_path_model', 
                                         :init =>'new Tree_path_model()',
                                       }, 
                                       { :cpp_type =>'QTreeView *', 
                                         :brief => 'Tree view for the parsed paths',
                                         :name =>'tree_path_view', 
                                         :init =>'new QTreeView()',
                                       }, 
                                       { :cpp_type =>'QSplitter *', 
                                         :brief => 'Horizontal splitter dividing parsed paths (top) and potential problems',
                                         :name =>'path_splitter', 
                                         :init =>'new QSplitter(Qt::Vertical)',
                                       }, 
                                       { :cpp_type =>'QTableWidget *', 
                                         :brief => 'List of paths that could be a problem due to duplicates',
                                         :name =>'problem_table', 
                                         :init =>'new QTableWidget()',
                                       }, 
                                      ],

                          :additional_ctor_parms => [[ 'QWidget *', 'parent']],
                          :additional_classes_come_first => true,
                          :additional_classes =>
                          [
                           CppClass.new({ 
                                          :name => 'Tree_path_model',
                                          :q_object => true,
                                          :bases_public =>
                                          [ [ 'QAbstractItemModel', 'QAbstractItemModel(0)']  ],
                                          :public_header_section => true,
                                          :ctor_default => true,
                                          :ctor_default_init_method => true,
                                          :hide_default_ctor => true,
                                          :impl_includes => 
                                          [
                                           'fcs/environment.hpp',
                                           'fcs/utils/file_path.hpp',
                                           'fcs/utils/streamers/streamers.hpp',
                                           'fcs/timestamp.hpp',
                                           'boost/foreach.hpp',
                                           'sstream',
                                          ],
                                          :impl_classes =>
                                          [
                                           CppClass.new({ 
                                                          :name => 'Tree_data_item',
                                                          :streamable => true,
                                                          :streamers_included => true,
                                                          :public_header_section => true,
                                                          :typedef_ptr => true,
                                                          :forward_typedefs =>
                                                          [
                                                           'typedef std::vector< Tree_data_item_ptr > Tree_data_item_list_t',
                                                           'typedef Tree_data_item* Tree_data_item_dumb_ptr',
                                                          ],
                                                          :members =>
                                                          [
                                                           { 
                                                             :name => 'data',
                                                             :const => true,
                                                             :cpp_type => 'std::string',    
                                                             :member_ctor => true,
                                                             :access => Codegen::Access::RO,                                                    
                                                           },
                                                           { 
                                                             :name => 'row',
                                                             :cpp_type => 'int',
                                                             :const => true,
                                                             :member_ctor => true,
                                                             :access => Codegen::Access::RO,
                                                           },
                                                           { 
                                                             :name => 'parent',
                                                             :cpp_type => 'Tree_data_item_dumb_ptr',
                                                             :const => true,
                                                             :init => '0',
                                                             :member_ctor_defaulted => true,
                                                             :access => Codegen::Access::RO,
                                                           },
                                                           { 
                                                             :name => 'file_size',
                                                             :const => true,
                                                             :cpp_type => 'std::string',    
                                                             :init => 'std::string()',
                                                             :member_ctor_defaulted => true,
                                                             :access => Codegen::Access::RO,                                                    
                                                           },
                                                           { 
                                                             :name => 'last_modified',
                                                             :const => true,
                                                             :cpp_type => 'std::string',    
                                                             :init => 'std::string()',
                                                             :member_ctor_defaulted => true,
                                                             :access => Codegen::Access::RO,                                                    
                                                           },
                                                           { 
                                                             :name => 'children',
                                                             :cpp_type => 'Tree_data_item_list_t',
                                                             :pass_by_ref => true,
                                                           },
                                                          ],
                                                        }
                                                        )
                                          ],
                                          :forward_typedefs =>
                                          [
                                           'typedef char const* Header_array_t[3]',
                                           'class Tree_data_item',
                                           typedef_shared_ptr_of('Tree_data_item'),
                                          ],
                                          :members =>
                                          [
                                           # { 
                                           #   :cpp_type => 'fcs::environment::Path_list_map_t',
                                           #   :name => 'path_list_map',
                                           #   :pass_by_ref => true,
                                           #   :init => 'fcs::environment::Environment::get_instance()->path_variable_map()',
                                           # },
                                           { 
                                             :cpp_type => 'Tree_data_item_ptr',
                                             :name => 'root',
                                             :init => 'Tree_data_item_ptr()',
                                           },
                                           { 
                                             :cpp_type => 'Header_array_t',
                                             :name => 'column_headers',
                                             :initialize_as_array => true,
                                             :init => '
      "Variable/Path/File",
      "Size",
      "Last Modified"
',
                                             :static => true,
                                           },
                                           { 
                                             :cpp_type => 'size_t',
                                             :name => 'column_count',
                                             :init => 'sizeof(Header_array_t)/sizeof(char const*)',
                                             :static => true,
                                           },
                                          ]
                                        })
                          ],
                          :ctor_member_init_method => true,
                          :include_unit_test => true,
                          :bases_public => [
                                            [ 'QWidget', 'QWidget(parent)' ],
                                           ]
                        }),

          ]

lib = Library.new({ 
                    :name => 'selection',
                    :no_api_decl => true,
                    :classes => classes,
                    :jam_requirements => [ 
                                          '$(TOP)//fcs_qt',
                                         ],
                    :namespace => ['fcs', 'gui', 'environment']
                  })
