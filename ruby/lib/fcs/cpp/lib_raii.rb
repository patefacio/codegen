################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
require 'place'
include Codegen::Cpp
classes = [

           CppClass.new({ 
                          :name => 'Change_until_end_of_block',
                          :brief => 'Changes the value of a variable to a new value and replaces it with original on exit of block',
                          :template_decls => [ 'typename T' ],
                          :header_includes => ['boost/call_traits.hpp',],
                          :public_header_section => true,
                          :include_unit_test => true,
                          :members => [
                                       { 
                                         :cpp_type => 'T',
                                         :name => 'saved_value',
                                         :brief => 'The original value, which is saved until block exit',
                                         :access => :read_only,
                                       },
                                       { 
                                         :cpp_type => 'T',
                                         :name => 'target',
                                         :brief => 'A reference to the variable - required to set the original back',
                                         :store_by_ref => true,
                                         :access => :read_only,
                                       },
                                      ],
                        }),

           CppClass.new({ 
                          :name => 'Change_tracker',
                          :template_decls => [ 'typename T' ],
                          :header_includes => ['boost/call_traits.hpp'],
                          :public_header_section => true,
                          :members => [
                                       { 
                                         :cpp_type => 'T',
                                         :name => 'current',
                                         :access => :read_only,
                                       },
                                       { 
                                         :cpp_type => 'T',
                                         :name => 'previous',
                                         :access => :read_only,
                                       },
                                      ],
                          :additional_classes =>
                          [
                           CppClass.new({ 
                                          :name => 'Change_tracker_next_value',
                                          :template_decls => [ 'typename T' ],
                                          :public_typedefs =>
                                          [
                                           'typedef Change_tracker< T > Change_tracker_t',
                                          ],
                                          :header_includes => ['boost/call_traits.hpp'],
                                          :public_header_section => true,
                                          :include_unit_test => true,
                                          :members => [
                                                       { 
                                                         :cpp_type => 'Change_tracker_t',
                                                         :name => 'tracker',
                                                         :store_by_ref => true,
                                                         :access => :read_only,
                                                       },
                                                       { 
                                                         :cpp_type => 'T',
                                                         :name => 'next_value',
                                                         :const => true,
                                                         :access => :read_only,
                                                       },
                                                      ],
                                        })
                          ]
                        }),

          ]

lib = Library.new({ 
                    :classes => classes,
                    :header_only => true,
                    :namespace => ['fcs', 'raii'],
                  })


