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
                                  :name => 'Timing_report',
                                  :standard_logging => true,
                                  :standard_otl_logging => true,
                                  :brief => 'Reports on rusage or clock timings',
                                  :descr => " 
Given package, location, or other filters will report on timings
",
                                  :options => [
                                               { 
                                                 :name => 'package',
                                                 :short_name => 'p',
                                                 :cpp_type => 'std::string',
                                                 :descr => 'Package to report on',
                                                 :default_value => '"%"',
                                               },
                                               { 
                                                 :name => 'location_label',
                                                 :short_name => 'l',
                                                 :cpp_type => 'std::string',
                                                 :descr => 'Label to report on',
                                                 :default_value => '"%"',
                                               },
                                               { 
                                                 :name => 'rusage',
                                                 :short_name => 'r',
                                                 :cpp_type => 'bool',
                                                 :descr => 'If true reports rusage',
                                                 :default_value => false,
                                               },
                                               { 
                                                 :name => 'ticks',
                                                 :short_name => 't',
                                                 :cpp_type => 'bool',
                                                 :descr => 'If true reports clock ticks',
                                                 :default_value => false,
                                               },
                                              ],

                                })

app = Application.new(
                      { 
                        :name => 'timing_report',
                        :log_pantheios_fe => true,
                        :program_options => program_options,
                        :classes => [],
                        :namespace => [ 'fcs', 'app', ],
                        :app_includes => 
                        [ 
                         'fcs/orm/code_metrics/table/rusage_delta.hpp',
                         'fcs/orm/code_metrics/table/code_tick_timings.hpp',
                         'fcs/orm/code_metrics/query/rusage_delta_by_package_label.hpp',
                         'fcs/orm/code_metrics/query/code_tick_timings_by_package_label.hpp',
                         'fcs/orm/orm_to_string_table.hpp',
                         'fcs/utils/streamers/table/table.hpp',
                         'boost/foreach.hpp',
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


