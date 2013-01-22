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
                                  :name => 'Cpu_info_options',
                                  :standard_logging => true,
                                  :brief => 'Dump processor and cpu info to stdout',
                                  :options => [
                                              ],

                                })
app = Application.new(
                      { 
                        :name => 'cpu_info',
                        :log_pantheios_fe => true,
                        :program_options => program_options,
                        :classes => [],
                        :folder => 'cpu_info',
                        :namespace => [ 'fcs', 'linux_specific', ],
                        :app_includes => 
                        [ 
                         'fcs/linux_specific/cpu_info.hpp',
                        ],
                        :jam_requirements => [ 
                                              '$(PANTHEIOS_LIBS)',
                                              '/site-config//boost_program_options',
                                              '/site-config//boost_regex',
                                             ],
                      }
                      )

