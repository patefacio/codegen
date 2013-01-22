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
                                  :name => 'Date_time_converter',
                                  :standard_logging => true,
                                  :brief => 'Given a date time converts to string and ticks',
                                  :options => [
                                               { 
                                                 :name => 'timestamp',
                                                 :short_name => 't',
                                                 :cpp_type => 'std::string',
                                                 :descr => 'Some form of date or timestamp',
                                                 :is_multiple => true,
                                               },
                                              ],

                                })

app = Application.new(
                      { 
                        :name => 'date_time_converter',
                        :log_pantheios_fe => true,
                        :program_options => program_options,
                        :classes => [],
                        :namespace => [ 'fcs', 'app', ],
                        :app_includes => 
                        [ 
                         'boost/foreach.hpp',
                         'boost/regex.hpp',
                         'boost/date_time/posix_time/posix_time.hpp',
                         'boost/date_time/posix_time/time_formatters.hpp',
                        ],
                        :jam_requirements => [ 
                                              '/site-config//boost_program_options',
                                              '/site-config//boost_date_time',
                                              '/site-config//boost_regex',
                                              '$(PANTHEIOS_LIBS)',
                                             ],
                      }
                      )

