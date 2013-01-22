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

program_options = 
  CppOptionParserGenerator.new( {
                                  :name => 'Performance_timers',
                                  :standard_logging => true,
                                  :header_includes => ['boost/cstdint.hpp'],
                                  :brief => 'Times how long it takes to time code',
                                  :descr => " 
Times over some number of iterations:
- calling performance timer
- calling clock tick timer
- calling rusage timer (optional and alone)

Then goes through the same set of timings with a few 
different functors in between start/stop calls to the
timers.
",
                                  :options => [
                                               { 
                                                 :name => 'iterations',
                                                 :short_name => 'i',
                                                 :cpp_type => 'boost::int64_t',
                                                 :descr => 'How many iterations',
                                                 :default_value => '1LL<<23',
                                               },
                                               { 
                                                 :name => 'rusage_timing',
                                                 :short_name => 'r',
                                                 :cpp_type => 'bool',
                                                 :descr => 'If true times rusage timer',
                                               },
                                               { 
                                                 :name => 'clock_timing',
                                                 :short_name => 'c',
                                                 :cpp_type => 'bool',
                                                 :descr => 'If true times clock timer',
                                               },
                                               { 
                                                 :name => 'platformstl_timing',
                                                 :short_name => 'p',
                                                 :cpp_type => 'bool',
                                                 :descr => 'If true times platformstl_timing',
                                               },

                                              ],

                                })

app = Application.new(
                      { 
                        :name => 'performance_timers',
                        :log_pantheios_fe => true,
                        :program_options => program_options,
                        :classes => [],
                        :folder => 'performance',
                        :namespace => [ 'fcs', 'performance', ],
                        :app_includes => 
                        [ 
                         'fcs/orm/code_metrics/table/rusage_delta.hpp',
                         'fcs/orm/code_metrics/table/code_tick_timings.hpp',
                         'fcs/utils/performance/block_tick_tracker.hpp',
                         'fcs/utils/performance/block_performance_counter_tracker.hpp',
                         'fcs/utils/performance/block_rusage_tracker.hpp',
                        ],
                        :jam_requirements => [ 
                                              '/site-config//otl',
                                              '/site-config//boost_program_options',
                                              '/site-config//boost_filesystem',
                                              '/site-config//boost_date_time',
                                              '$(PANTHEIOS_LIBS)',
                                             ],
                      }
                      )

