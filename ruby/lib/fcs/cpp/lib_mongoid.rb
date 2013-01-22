################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

classes = [

           CppClass.new({ 
                          :name => 'mongoid',
                          :is_api_header => true,
                          :brief => 'Support for storing basic data in mongoid database',
                          :public_typedefs => 
                          [ 
                           'typedef mongo::DBClientConnection * Client_connection_ptr',
                           'typedef fcs::utils::Fixed_size_char_array< 25 > Object_id_t',
                           'typedef long long Bson_int64_t',
                          ],
                          :forward_class_decls => [],
                          :include_unit_test => true,
                          :header_includes => 
                          [
                           'mongo/client/dbclient.h',
                           'fcs/utils/fixed_size_char_array.hpp',
                           'pantheios/pantheios.hpp',
                          ],
                        }),

           CppClass.new({ 
                          :name => 'Mongoid_ini_parser',
                          :ctor_default => true,
                          :ctor_default_init_inline_method => true,
                          :streamable_inline => true,
                          :streamers_included => true,
                          :header_includes => 
                          [
                           'fcs/utils/streamers/vector.hpp',
                           'boost/foreach.hpp',
                           'boost/program_options.hpp',
                           'boost/program_options/parsers.hpp',
                           'pantheios/pantheios.hpp',
                          ],
                          :members => 
                          [
                           { 
                             :name => 'mongoid_options_description',
                             :cpp_type => 'boost::program_options::options_description',
                             :init => '"Parses mongoid ini file"',
                           },                                           
                           { 
                             :name => 'database_configuration_map',
                             :cpp_type => 'Database_configuration_map_t',
                             :pass_by_ref => true,
                             :access => Codegen::Access::RO,
                           },

                          ],
                          :additional_classes_come_first => true,
                          :additional_classes =>
                          [
                           CppClass.new({ 
                                          :name => 'Mongoid_database_config',
                                          :post_class_typedefs =>
                                          [
                                           'typedef std::map< std::string, Mongoid_database_config > Database_configuration_map_t',
                                          ],
                                          :streamable_inline => true,
                                          :ctor_default => true,
                                          :members =>
                                          [
                                           { 
                                             :name => 'server',
                                             :brief => 'Name of server followed by colon followed by port',
                                             :cpp_type => 'std::string',
                                             :member_ctor => true,
                                             :public => true,
                                           },
                                           { 
                                             :name => 'user',
                                             :cpp_type => 'std::string',
                                             :member_ctor => true,
                                             :public => true,
                                           },
                                           { 
                                             :name => 'password',
                                             :cpp_type => 'std::string',
                                             :member_ctor => true,
                                             :public => true,
                                           },
                                          ]
                                        }),
                          ]
                        }),

           CppClass.new({ 
                          :name => 'Connection_registry',
                          :ctor_default_init_inline_method => true,
                          :members => [
                                        { :cpp_type =>'Database_configuration_map_t', 
                                          :brief => 'Maps name of connection to its configuration info',
                                          :name =>'database_configuration_map', 
                                          :pass_by_ref =>true,
                                          :access => Codegen::Access::RO}, 
                                        { 
                                          :cpp_type => 'LOCK_TYPE',
                                          :name => 'lock',
                                          :brief => 'For protecting the registry map',
                                        },
                                        { 
                                          :cpp_type => 'Thread_connection_map_t',
                                          :name => 'thread_connection_map',
                                          :pass_by_ref => true,
                                          :brief => 'Map of connections in tss (i.e. one per thread)'
                                        },
                                       ],
                          :template_decls => [ 
                                               'typename LOCK_TYPE = boost::mutex',
                                               'typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE >'
                                              ],
                          :singleton_base_template => 'Connection_registry< LOCK_TYPE, GUARD_TYPE >',
                          :public_header_section => true,
                          :singleton => true,
                          :public_typedefs => [ 
                                               'typedef boost::thread_specific_ptr< mongo::DBClientConnection > Tss_connection_t',
                                               typedef_shared_ptr_of('Tss_connection_t', 'Thread_connection_ptr'),
                                               'typedef std::map< std::string, Thread_connection_ptr > Thread_connection_map_t'
                                               ],
                          :brief => 'Place to get database connections',
                          :header_includes => [ 
                                                'fcs/mongoid/mongoid_ini_parser.hpp',
                                                'boost/thread/tss.hpp',
                                                'pantheios/pantheios.hpp',
                                               ],
                        }),
          ]

lib = Codegen::Cpp::Library.new({ 
                                  :classes => classes,
                                  :descr => "Api supporting mapping of data into mongodb",
                                  :header_only => true,
                                  :jam_requirements => [
                                                        '/site-config//boost_program_options',
                                                        '/site-config//boost_filesystem',
                                                        '/site-config//mongoclient',
                                                       ],
                                  :namespace => ['fcs', 'mongoid', ]
                                })

