################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'tenjin'
require 'codegen/cpp'
require 'codegen'
require 'yaml'

$cpp = ::Codegen::Cpp
$klass = $cpp::CppClass

program_options = 
  $cpp::CppOptionParserGenerator.new( {
                                        :name => 'H5_data_set_to_csv',
                                        :standard_logging => true,
                                        :descr => 'converts data_sets in hdf5 files to csv',
                                        :options => [
                                                      { 
                                                        :name => 'data_set',
                                                        :short_name => 'd',
                                                        :cpp_type => 'std::string',
                                                        :is_multiple => true,
                                                        :descr => 'Name of data_set to make into csv',
                                                      },
                                                      { 
                                                        :name => 'input_file',
                                                        :short_name => 'i',
                                                        :cpp_type => 'std::string',
                                                        :descr => 'Name of file containing data_set(s)',
                                                        :is_multiple => true,
                                                        :opt_required => true,
                                                      },
                                                      { 
                                                        :name => 'output_file',
                                                        :short_name => 'o',
                                                        :cpp_type => 'std::string',
                                                        :descr => 'If specified each data_set is written to {output_file}_{input_file}_{data_set}.csv else written to stdout',
                                                      },
                                                      { 
                                                        :name => 'log_meta_data_load',
                                                        :short_name => 'l',
                                                        :cpp_type => 'bool',
                                                        :init => 'false',
                                                        :descr => 'If set logs extra info on meta_data load',
                                                      }

                                                     ],
                                        #:disable_windows_warnings => ['4251'],

                                      })

app = $cpp::Application.new(
                            { 
                              :name => 'h5data_set2csv',
                              :classes => [
                                            { 
                                              :name => 'Data_set_csv_writer',
                                              :members => [
                                                            { :cpp_type =>'H5_data_set_to_csv_program_options', 
                                                              :name =>'program_options', 
                                                              :member_ctor =>true,
                                                              :pass_by_ref =>true,
                                                            }, 
                                                           ],
                                              :streamable => true,
                                              :public_header_section => true,
                                              :header_includes => ['h5_data_set_to_csv_program_options.hpp'],
                                              :impl_includes => [
                                                                  "fcs/h5/h5_meta_data.hpp", 
                                                                  'boost/foreach.hpp',
                                                                  "pantheios/pantheios.hpp"
                                                                 ]
                                            },
                                            program_options.cpp_class,
                                           ],
                              :namespace => [ 'fcs', 'app', 'h5' ],
                              :app_includes => [ 
                                                 'fcs/h5/h5_meta_data.hpp', 
                                                 'data_set_csv_writer.hpp', 
                                                 'iostream', 
                                                 'pantheios/pantheios.hpp', 
                                                 'pantheios/frontends/stock.h' 
                                                ],
                              :jam_requirements => [ 
                                                     '/site-config//hdf5',
                                                     '/site-config//hdf5_cpp',
                                                     '/site-config//boost_program_options',
                                                     '/site-config//boost_filesystem',
                                                     '$(PANTHEIOS_LIBS)',
                                                    ],
                            }
                            )


