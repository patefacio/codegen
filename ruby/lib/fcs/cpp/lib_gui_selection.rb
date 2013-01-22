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
                          :name => 'Q_multiple_pick_list',
                          :q_object => true,
                          :hide_impl => true,
                          :header_includes => [ ],
                          :dtor_impl => true,
                          :log_ctor => true,
                          :log_dtor => true,
                          :impl_includes => [
                                             'pantheios/pantheios.hpp', 
                                             'boost/foreach.hpp',
                                             '<QToolBar>',
                                             '<QVBoxLayout>', 
                                            ],
                          :private_header_section => true,
                          :public_typedefs => [
                                                'typedef std::map< QString, bool > Selection_map_t',
                                               ],
                          :members => [
                                        { :cpp_type =>'Selection_map_t', 
                                          :brief => 'Map of selection strings to corresponding values',
                                          :name =>'selection_map', 
                                          :pass_by_ref =>true,
                                          :member_ctor =>true,
                                          :access => Codegen::Access::RO}, 
                                        { :cpp_type =>'QSplitter *', 
                                          :brief => 'Splitter for the (Choose From) (Chosen) listboxes',
                                          :name =>'splitter', 
                                          :init =>'new QSplitter(this)',
                                          :access => Codegen::Access::IA}, 
                                        { :cpp_type =>'QListWidget *', 
                                          :brief => 'List of items to choose from',
                                          :name =>'choose_from_list', 
                                          :init =>'new QListWidget()',
                                          :access => Codegen::Access::IA}, 
                                        { :cpp_type =>'QListWidget *', 
                                          :brief => 'List of chosen items',
                                          :name =>'chosen_list', 
                                          :init =>'new QListWidget()',
                                          :access => Codegen::Access::IA}, 
                                       ],

                          :additional_ctor_parms => [[ 'QWidget *', 'parent']],
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
                    :namespace => ['fcs', 'gui', 'selection']
                  })
