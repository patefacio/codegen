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
                          :name => 'Q_search_request',
                          :q_object => true,
                          #:pimpl_ptr => true,
                          :header_includes => [ 
                                              ],
                          :impl_includes => [
                                             'fcs/environment.hpp',
                                             'pantheios/pantheios.hpp', 
                                             'pantheios/inserters.hpp', 
                                             'boost/foreach.hpp',
                                            ],
                          :public_header_section => true,
                          :private_header_section => true,
                          :bases_public => [
                                            [ 'QWidget', 'QWidget(parent)' ],
                                           ],
                          :members => [
                                       { :cpp_type =>'QTableWidget *', 
                                         :brief => 'List of variables and values',
                                         :name =>'variable_list_table', 
                                         :init =>'new QTableWidget()',
                                       }, 
                                      ],
                          :additional_ctor_parms => [[ 'QWidget *', 'parent']],
                        }),

          ]

lib = Library.new({ 
                    :name => 'selection',
                    :no_api_decl => true,
                    :classes => classes,
                    :jam_requirements => [ 
                                          '$(TOP)//fcs_qt',
                                         ],
                    :namespace => ['fcs', 'gui', 'search']
                  })
