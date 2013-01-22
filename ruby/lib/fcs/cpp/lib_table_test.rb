################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'tenjin'
require 'codegen/cpp'
require 'codegen'
require 'yaml'
include Codegen::Cpp
classes = [

           CppClass.new({ 
                          :name => 'Random_cell_generator',
                          :members => [ 
                                        { :cpp_type =>'boost::uniform_real< long double >', 
                                          #:brief => 'For generating random data',
                                          :name =>'uniform_real', 
                                          :init =>'0, std::numeric_limits< long double >::max()',
                                        }, 
                                        { :cpp_type =>'boost::uniform_int< boost::int64_t >', 
                                          #:brief => 'For generating random integer data',
                                          :name =>'uniform_int', 
                                          :init =>'0, std::numeric_limits< boost::int64_t >::max()',
                                        }, 
                                        { :cpp_type =>'boost::mt19937', 
                                          #:brief => 'For generating random integer data',
                                          :name =>'generator', 
                                          :init =>'std::numeric_limits< boost::int64_t >::max()',
                                        },
                                        { :cpp_type =>'boost::variate_generator< boost::mt19937, boost::uniform_real< long double > >', 
                                          #:brief => 'For generating random integer data',
                                          :name =>'real_generator', 
                                          :init =>'generator_, uniform_real_',
                                        }, 
                                        { :cpp_type =>'boost::variate_generator< boost::mt19937, boost::uniform_int< boost::int64_t > >', 
                                          #:brief => 'For generating random integer data',
                                          :name =>'int_generator', 
                                          :init =>'generator_, uniform_int_',
                                        }, 
                                       ],
                          :brief => 'Support for creating a cell with random data',
                          :ctor_default =>true,
                          :header_includes => [ 
                                               'fcs/table/table.hpp',
                                               'boost/random.hpp',
                                               'boost/random/uniform_int.hpp',
                                               'boost/random/uniform_real.hpp',
                                               'boost/random/variate_generator.hpp',
                                               'limits',
                                              ],
                          :header_only => true,
                          :public_header_section => true,
                        }),



           CppClass.new({ 
                          :name => 'Random_table_generator',
                          :members => [ 
                                        { :cpp_type =>'Index_t', 
                                          :name =>'num_columns', 
                                          :init =>'10',
                                          :member_ctor_defaulted => true,
                                        }, 
                                        { :cpp_type =>'Index_t', 
                                          :name =>'num_rows', 
                                          :member_ctor_defaulted => true,
                                          :init =>'1000',
                                        }, 
                                       ],
                          :brief => 'Support for creating a table with random data',
                          #:ctor_member_init_method => true,
                          #:ctor_member_init_inline_method => true,
                          :header_includes => [ 
                                                'fcs/table/test/random_cell_generator.hpp',
                                                'fcs/table/memory_table_model.hpp',
                                               ],
                          :header_only => true,
                          :public_header_section => true,
                        }),

          ]


lib = Codegen::Cpp::Library.new({ 
                                  :name =>'table',
                                  :header_only => true,
                                  :classes => classes,
                                  :jam_requirements => [ 
                                                        ],
                                  :namespace => ['fcs', 'table', 'test']
                                })

