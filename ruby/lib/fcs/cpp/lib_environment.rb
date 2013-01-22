################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
require 'place'
include Codegen::Cpp
classes = [

           CppClass.new({ 
                          :name => 'environment',
                          :header_only => true,
                          :is_namespace_header => true,
                          :header_namespace_end_section => true,
                          :header_includes => 
                          [
                           'boost/regex.hpp',
                           'unistd.h',
                           'sstream',
                           'exception',
                           'pantheios/pantheios.hpp',
                          ],
                          :public_typedefs => 
                          [
                           typedef_map_of('std::string', 'std::string', :full_name => 'Environment_map_t'),
                           typedef_set_of('std::string', :name => 'Path_variable'),
                           typedef_path,
                           typedef_list_of('Path_t'),
                           typedef_map_of('std::string', 'Path_list_t', 'Path_list'),
                          ],
                          :public_header_section => true,
                          :include_unit_test => true,
                          :additional_classes => 
                          [
                           CppClass.new(
                                        { 
                                          :name => 'Environment',
                                          :descr =>'
Singleton that when initialized churns through various environment variables
like LD_LIBRARY_PATH, MANPATH, PATH, etc...
The purpose is to make the paths those variables refer to available to code.
',
                                          :streamable_inline => true,
                                          :streamers_included => true,
                                          :ctor_default_init_inline_method => true,
                                          :singleton => true,
                                          :header_only => true,
                                          :members =>
                                          [
                                           { 
                                             :name => 'environment',
                                             :cpp_type => 'Environment_map_t',
                                             :pass_by_ref => true,
                                             :access => Codegen::Access::RO,
                                           },
                                           { 
                                             :name => 'path_variable_map',
                                             :cpp_type => 'Path_list_map_t',
                                             :pass_by_ref => true,
                                             :access => Codegen::Access::RO,
                                           },
                                          ]
                                        }
                                        )
                          ]
                        }),
          ]

lib = Library.new({ 
                    :classes => classes,
                    :header_only => true,
                    :namespace => ['fcs', 'environment'],
                    :jam_requirements => [ 
                                          '/site-config//boost_filesystem',
                                          '/site-config//boost_regex',
                                         ],
                    :no_api_decl => true,
                  })


