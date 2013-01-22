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
                                  :name => 'Display_csv',
                                  :standard_logging => true,
                                  :brief => 'Wraps a model on a csv for display in Qt',
                                  :descr => " 
Takes one or more csv files and for each wraps a view on it.
",
                                  :options => [
                                               { 
                                                 :name => 'csv_file',
                                                 :short_name => 'c',
                                                 :cpp_type => 'std::string',
                                                 :descr => 'Csv file path(s) to open',
                                                 :is_multiple => true,
                                               },
                                              ],

                                })

app = Application.new(
                      { 
                        :name => 'display_csv',
                        :log_pantheios_fe => true,
                        :program_options => program_options,
                        :classes => [],
                        :namespace => [ 'fcs', 'app', ],
                        :app_includes => 
                        [ 
                         'fcs/table/delimited_file_table_model.hpp',
                         'fcs/gui/table/q_table_view.hpp',
                         'boost/foreach.hpp',
                         'boost/ptr_container/ptr_vector.hpp',
                         '<QApplication>',
                        ],
                        :jam_requirements => [ 
                                              '/site-config//boost_program_options',
                                              '/site-config//boost_filesystem',
                                              '/site-config//boost_date_time',
                                              '$(TOP)//fcs_gui_table',
                                              '$(TOP)//fcs_qt',
                                              '$(PANTHEIOS_LIBS)',
                                             ],
                        :uses_pantheios => true,
                      }
                      )

