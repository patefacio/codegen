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

app = Application.new(
                      { 
                        :name => 'delimited_file_read_write_test',
                        :log_pantheios_fe => true,
                        :classes => [],
                        :folder => 'test',
                        :unit_test => true,
                        :namespace => [ 'fcs', 'test', ],
                        :app_includes => 
                        [ 
                         'fcs/table/delimited_file_table_model.hpp',
                         'boost/filesystem.hpp',
                         'boost/regex.hpp',
                         'boost/lexical_cast.hpp',
                        ],
                        :jam_requirements => [ 
                                              '/site-config//boost_filesystem',
                                              '/site-config//boost_regex',
                                              '$(PANTHEIOS_LIBS)',
                                             ],
                        :uses_pantheios => true,
                        
                      }
                      )

