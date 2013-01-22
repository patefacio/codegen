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
                          :name => 'Application_signal_handler',
                          :brief => 'Adds support for handling signals',
                          :log_ctor => true,
                          :log_dtor => true,
                          :singleton => true,
                          :singleton_base_template => 'Application_signal_handler< LOCK_TYPE, GUARD_TYPE >',
                          :template_decls => [ 
                                               'typename LOCK_TYPE = boost::mutex',
                                               'typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE >'
                                              ],
                          :public_typedefs => [      
                                                'typedef boost::function < bool (int) > Handler_function_t',
                                                'typedef std::vector< Handler_function_t > Handler_function_list_t',
                                               ],
                          :members => [                                                  
                                        { 
                                          :cpp_type => 'Handler_function_list_t', 
                                          :brief => 'List of handlers to execute on signal',
                                          :name => 'handler_list', 
                                          :pass_by_ref => true,
                                        }, 
                                        { 
                                          :cpp_type => 'LOCK_TYPE',
                                          :brief => 'Protection for instance data',
                                          :name => 'instance_mutex', 
                                        }, 
                                       ],
                          :ctor_default_init_inline_method => true,
                          :public_header_section => true,
                          :forward_class_decls => [],
                          :header_includes => [ 
                                                'pantheios/pantheios.hpp',
                                                'boost/function.hpp', 
                                                'boost/thread/mutex.hpp', 
                                                'boost/thread/locks.hpp',
                                                'boost/thread/thread.hpp', 
                                                'exception',
                                                'vector', 
                                                'csignal',
                                               ],
                          :enums => [],
                        }),

          ]


lib = Codegen::Cpp::Library.new({ 
                                  :name => 'application_signal_handler',
                                  :header_only => true,
                                  :classes => classes,
                                  :jam_requirements => [ 
                                                        ],
                                  :namespace => ['fcs', 'app_sig_handler']
                                })

