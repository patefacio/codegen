################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

lib = 
  Library.new({ 
                :classes => 
                [

                 CppClass.new({ 
                                :name => 'lock_and_guard_traits',
                                :no_class => true,
                                :additional_classes => 
                                [

                                 CppClass.new({ 
                                                :struct => true,
                                                :template_decls => [ 'typename LOCK_TYPE' ],
                                                :name => 'Lock_and_guard_traits',
                                                :public_typedefs => 
                                                [ 
                                                ]
                                              }),

                                 CppClass.new({ 
                                                :struct => true,
                                                :template_decls => [ '' ],
                                                :name => 'Lock_and_guard_traits< boost::interprocess::null_mutex >',
                                                :public_typedefs => 
                                                [ 
                                                 'typedef boost::interprocess::null_mutex Lock_t',
                                                 'typedef boost::lock_guard< Lock_t > Guard_t',                 
                                                ]
                                              }),

                                 CppClass.new({ 
                                                :struct => true,
                                                :name => 'Null_lock_and_guard_traits_tag',
                                                :bases_public => [ ['Lock_and_guard_traits< boost::interprocess::null_mutex >',] ],
                                              }),

                                 CppClass.new({ 
                                                :struct => true,
                                                :template_decls => [ '' ],
                                                :name => 'Lock_and_guard_traits< boost::mutex >',
                                                :public_typedefs => 
                                                [ 
                                                 'typedef boost::mutex Lock_t',
                                                 'typedef boost::lock_guard< Lock_t > Guard_t',                                       
                                                ]
                                              }),

                                 CppClass.new({ 
                                                :struct => true,
                                                :name => 'Boost_mutex_lock_and_guard_traits_tag',
                                                :bases_public => [ ['Lock_and_guard_traits< boost::mutex >',] ],
                                              }),

                                ],
                                :header_includes => 
                                [
                                 'boost/interprocess/sync/null_mutex.hpp',
                                 'boost/thread/mutex.hpp',
                                 'boost/thread/locks.hpp',
                                ],
                              }),


                 CppClass.new({ 
                                :name => 'lock_and_guard_traits_tbb',
                                :no_class => true,
                                :additional_classes => 
                                [

                                 CppClass.new({ 
                                                :struct => true,
                                                :template_decls => [ '' ],
                                                :name => 'Lock_and_guard_traits< tbb::spin_mutex >',
                                                :public_typedefs => 
                                                [ 
                                                 'typedef tbb::spin_mutex Lock_t',
                                                 'typedef Lock_t::scoped_lock Guard_t',         
                                                ]
                                              }),

                                 CppClass.new({ 
                                                :struct => true,
                                                :name => 'Tbb_spin_mutex_lock_and_guard_traits_tag',
                                                :bases_public => [ ['Lock_and_guard_traits< tbb::spin_mutex >',] ],
                                              }),

                                ],
                                :header_includes => 
                                [
                                 'tbb/spin_mutex.h',
                                 'fcs/utils/synch/lock_and_guard_traits.hpp',
                                ],
                              }),

                ],
                :header_only => true,
                :static_only => true,
                :namespace => ['fcs', 'utils', 'synch'],
                :no_api_decl => true,
              })

