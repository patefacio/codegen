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
                          :name => 'Q_table_view',
                          #:pimpl_ptr => true,
                          :log_ctor => true,
                          :log_dtor => true,
                          :dtor_impl => true,
                          :pimpl_typedefs => 
                          [
                           'using fcs::gui::table::Q_table_model',
                           'using fcs::gui::table::Q_item_data_role_handler_ptr',
                          ],
                          :header_includes => [ 
                                                'fcs/gui/table/q_table_model.hpp',
                                                'fcs/gui/table/q_item_data_role_handler.hpp',
                                                '<QTableView>', 
                                               ],
                          :impl_includes => [
                                              '<QHeaderView>',
                                             ],
                          :members => [
                                        { :cpp_type =>'Q_table_model *', 
                                          :brief => 'Data source (model) for the view',
                                          :name =>'q_table_model', 
                                          :member_ctor =>true,
                                          :pass_by_ref =>true,
                                          :protected =>true,
                                          :access => Codegen::Access::IA}, 
                                        { :cpp_type =>'Q_item_data_role_handler_ptr', 
                                          :brief => 'User specified data override/formatting functor',
                                          :name =>'item_data_role_handler', 
                                          :member_ctor_defaulted =>true,
                                          :init => 'Q_item_data_role_handler_ptr()',
                                          :pass_by_ref =>true,
                                          :protected =>true,
                                          :access => Codegen::Access::IA}, 

                                       ],

                          :additional_ctor_parms => [[ 'QWidget *', 'parent']],
                          :ctor_member_init_method => true,
                          :include_unit_test => true,
                          :bases_public => [
                                             [ 'QTableView', 'QTableView(parent)' ],
                                            ]
                        }),

           CppClass.new({ 
                          :name => 'Q_table_model',
                          :hide_member_init_ctor => true,
                          :log_ctor => true,
                          :log_dtor => true,
                          :dtor_impl => true,
                          :header_includes => [ 
                                               'fcs/table/table_model.hpp',
                                               'fcs/gui/table/q_item_data_role_handler.hpp',
                                               '<QAbstractTableModel>', 
                                              ],
                          :public_header_section => true,
                          :impl_includes => [ 'sstream', 
                                               'boost/foreach.hpp',
                                            ],
                          :public_typedefs => [        ],
                          :members => [
                                        { :cpp_type =>'fcs::table::Table_model_const_ptr', 
                                          :brief => 'Data source (model) for the view',
                                          :name =>'table_model', 
                                          :member_ctor =>true,
                                          :pass_by_ref =>true,
                                          :protected =>true,
                                          :access => Codegen::Access::IA}, 
                                        { :cpp_type =>'Q_item_data_role_handler_ptr', 
                                          :brief => 'User specified data override/formatting functor',
                                          :name =>'item_data_role_handler', 
                                          :member_ctor_defaulted =>true,
                                          :init => 'Q_item_data_role_handler_ptr()',
                                          :pass_by_ref =>true,
                                          :protected =>true,
                                          :access => Codegen::Access::IA}, 
                                        { :cpp_type =>'bool', 
                                          :brief => 'If true logs data access',
                                          :name =>'log_data_access', 
                                          :init => 'false',
                                          :access => Codegen::Access::RW}, 

                                       ],

                          :additional_ctor_parms => [[ 'QObject *', 'parent']],
                          :ctor_member_init_method => true,
                          :bases_public => [[ 'QAbstractTableModel', 'QAbstractTableModel(parent)' ],],
                        }),

           CppClass.new({ 
                          :name => 'Q_item_data_role_handler',
                          :hide_member_init_ctor => true,
                          :descr =>"

Handler that satisfies the data method call on behalf of the view.
Essentially, takes things that should be view related (formatting,
data text override) and puts in base class allowing clients to
override.

",
                          :header_includes => [ 
                                                '<QAbstractTableModel>', 
                                                'fcs/table/table.hpp',
                                               ],
                          :public_header_section => true,
                          :impl_includes => [ ],
                          :members => [ 
                                        { :cpp_type =>'int', 
                                          :brief => 'Determines which functions should be called',
                                          :name =>'item_data_role_handler_function_mask', 
                                          :member_ctor =>true,
                                          :init => '0',
                                          :streamable_custom =>true,
                                          :access => Codegen::Access::RO}, 
                                        
                                       ],
                          :bases_public => [],
                          #                        :header_only => true,
                          :typedef_ptr => true,
                          :enums => [ Enumeration.new({
                                                        :name => 'Item_data_role_handler_function', 
                                                        :mask => true,
                                                        :values => [
                                                                    'ROLE_FORMAT_DATA_FUNCTION', 
                                                                    'ROLE_OVERRIDE_DATA_FUNCTION'],}), 
                                     ],
                          :streamable => true,
                        }),

          ]

lib = Library.new({ 
                    :name =>'table',
                    :no_api_decl => true,
                    :classes => classes,
                    :jam_requirements => [ 
                                           '$(TOP)//fcs_qt',
                                          ],
                    :namespace => ['fcs', 'gui', 'table']
                  })
