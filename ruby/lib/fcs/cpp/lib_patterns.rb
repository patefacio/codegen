################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

$signaller_class = 
  CppClass.new({ 
               :name => 'Signaller',
               :template_decls => [ 
                                    'typename DATA', 
                                    'typename OBSERVER',
                                    'typename OBSERVER_PTR = typename boost::add_pointer< OBSERVER >::type',
                                    'typename LOCK_AND_GUARD_TRAITS = utils::synch::Boost_mutex_lock_and_guard_traits_tag',
                                   ],
               :public_header_section => true,
               :header_includes => [ 
                                     'set',  
                                     'boost/call_traits.hpp',
                                     'boost/type_traits/add_pointer.hpp',
                                    ],
               :public_typedefs => [ 
                                    'typedef OBSERVER_PTR Observer_ptr_t',
                                    'typedef typename LOCK_AND_GUARD_TRAITS::Lock_t Lock_t',
                                    'typedef typename LOCK_AND_GUARD_TRAITS::Guard_t Guard_t',
                                    typedef_set_of('Observer_ptr_t', 'Observer'),
                                    ],
               :brief => 'Signalling piece of the subject/observer pattern',
               :descr => "Signalling entities create instances of this class
in order to signal updates of type const& DATA to attached observers.
",
               :members => [
                             { 
                               :cpp_type => 'Observer_set_t',
                               :name => 'observers',
                               :brief => 'Container for observers',
                             },
                             { 
                               :cpp_type => 'Lock_t',
                               :name => 'lock',
                               :brief => 'For protecting the observer container',
                             }
                            ],
               :include_unit_test => true,
             })

$signaller_prioritized_class = 
  CppClass.new({ 
               :name => 'Signaller_prioritized',
               :template_decls => [ 
                                    'typename DATA', 
                                    'typename OBSERVER',
                                    'typename OBSERVER_PTR = typename boost::add_pointer< OBSERVER >::type',
                                    'typename LOCK_AND_GUARD_TRAITS = utils::synch::Boost_mutex_lock_and_guard_traits_tag',
                                   ],
               :public_header_section => true,
               :header_includes => [ 
                                     'boost/bimap.hpp', 
                                     'boost/call_traits.hpp',
                                     'boost/type_traits/add_pointer.hpp',
                                    ],
               :public_typedefs => [ 
                                     'typedef OBSERVER_PTR Observer_ptr_t',
                                     'typedef typename LOCK_AND_GUARD_TRAITS::Lock_t Lock_t',
                                     'typedef typename LOCK_AND_GUARD_TRAITS::Guard_t Guard_t',
                                     'typedef std::pair< int, Observer_ptr_t > Priority_and_observer_t',
                                     'typedef boost::bimap< Priority_and_observer_t, Observer_ptr_t > Prioritized_observer_map_t',
                                    ],
               :brief => 'Signalling piece of the subject/observer pattern',
               :descr => "Signalling entities create instances of this class
in order to signal updates of type const& DATA to attached observers. The
callbacks are ordered by priority passed in on the attach.
",
               :members => [
                             { 
                               :cpp_type => 'Prioritized_observer_map_t',
                               :name => 'prioritized_observer_map',
                               :brief => 'Container for priority ordered observers'
                             },
                             { 
                               :cpp_type => 'Lock_t',
                               :name => 'lock',
                               :brief => 'For protecting the observer container',
                             }

                            ],
               :include_unit_test => true,
             })


classes = [

           CppClass.new(
                      { 
                        :name => 'observer',
                        :no_class => true,
                        :header_includes => [ 'fcs/utils/synch/lock_and_guard_traits.hpp', ],
                        :additional_classes => 
                        [
                         $signaller_class,
                         $signaller_prioritized_class,
                        ]
                      }
                      ),
          ]


lib = Library.new({ 
                    :classes => classes,
                    :header_only => true,
                    :namespace => ['fcs', 'patterns'],
                    :no_api_decl => true,
                    :build_cpp_includes => [ ],
                  })
