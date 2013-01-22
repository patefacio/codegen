################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp
lib = Library.new({ 
                    :classes => 
                    [

                     CppClass.new({ 
                                    :name => 'Block_performance_counter_tracker',
                                    :brief => 'Block timer that uses stlsoft performance counter',
                                    :public_header_section => true,
                                    :ctor_member_init_inline_method => true,
                                    :header_includes => 
                                    [ 
                                     'iostream', 
                                     'platformstl/performance/performance_counter.hpp',
                                     'boost/cstdint.hpp',
                                    ],
                                    :include_unit_test => true,
                                    :members => [
                                                  { 
                                                    :cpp_type => 'std::ostream *',
                                                    :name => 'outstream',
                                                    :member_ctor_defaulted => true,
                                                    :init => '&std::cout',
                                                  },
                                                  { 
                                                    :cpp_type => 'char const *',
                                                    :name => 'stream_label',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                  },
                                                  { 
                                                    :cpp_type => 'boost::int64_t',
                                                    :name => 'iteration_count',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                  },
                                                  { 
                                                    :cpp_type => 'stlsoft::platformstl_project::performance_counter',
                                                    :name => 'performance_counter',
                                                  },

                                                 ],
                                  }),

                     CppClass.new({ 
                                    :name => 'Block_tick_tracker',
                                    :public_header_section => true,
                                    :ctor_member_init_inline_method => true,
                                    :header_includes => 
                                    [ 
                                     'fcs/linux_specific/cpu_info.hpp',
                                     'boost/cstdint.hpp',
                                     'boost/lexical_cast.hpp',
                                     'cycle.h', 
                                     'iostream' 
                                    ],
                                    :include_unit_test => true,
                                    :members => [
                                                  { 
                                                    :cpp_type => 'std::ostream *',
                                                    :name => 'outstream',
                                                    :member_ctor_defaulted => true,
                                                    :init => '&std::cout',
                                                  },
                                                  { 
                                                    :cpp_type => 'char const *',
                                                    :name => 'stream_label',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                  },
                                                  { 
                                                    :cpp_type => 'ticks *',
                                                    :name => 'saved_tick_count',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                  },
                                                  { 
                                                    :cpp_type => 'boost::int64_t',
                                                    :name => 'iteration_count',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                  },
                                                  { 
                                                    :cpp_type => 'ticks',
                                                    :name => 'initial_ticks',
                                                    :init => '0',
                                                  },
                                                  { 
                                                    :cpp_type => 'ticks',
                                                    :name => 'final_ticks',
                                                    :init => '0',
                                                  },
                                                 ],
                                  }),


                     CppClass.new({ 
                                    :name => 'Block_rusage_tracker',
                                    :public_header_section => true,
                                    :include_unit_test => true,
                                    :global_header_section => true,
                                    :ctor_member_init_inline_method => true,
                                    :header_includes => 
                                    [
                                     'boost/cstdint.hpp',
                                     'sys/time.h',
                                     'sys/resource.h',
                                    ],
                                    :members => [ 
                                                  { 
                                                    :cpp_type => 'rusage',
                                                    :name => 'initial_rusage',
                                                  },
                                                  { 
                                                    :cpp_type => 'rusage',
                                                    :name => 'final_rusage',
                                                  },
                                                  { 
                                                    :cpp_type => 'rusage',
                                                    :name => 'delta_rusage',
                                                  },
                                                  { 
                                                    :cpp_type => 'std::ostream *',
                                                    :name => 'outstream',
                                                    :member_ctor_defaulted => true,
                                                    :init => '&std::cout',
                                                    :streamable => false,
                                                  },
                                                  { 
                                                    :cpp_type => 'char const *',
                                                    :name => 'stream_label',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                    :streamable => false,
                                                  },
                                                  { 
                                                    :cpp_type => 'rusage *',
                                                    :name => 'saved_rusage_delta',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                    :pass_by_ref => true,
                                                    :streamable => false,
                                                  },
                                                  { 
                                                    :cpp_type => 'boost::int64_t',
                                                    :name => 'iteration_count',
                                                    :member_ctor_defaulted => true,
                                                    :init => '0',
                                                  },

                                                 ],
                                    #:include_unit_test => true,
                                    :streamable_inline => true,
                                  }),
                    ],
                    :header_only => true,
                    :static_only => true,
                    :namespace => ['fcs', 'utils', 'performance' ],
                    :no_api_decl => true,
                    :build_cpp_includes => [ '$(TBB_INCLUDE_PATH)' ],
                  })

