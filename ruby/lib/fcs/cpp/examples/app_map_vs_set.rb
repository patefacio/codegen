require 'tenjin'
require 'codegen/cpp'
require 'codegen'
require 'yaml'
include Codegen::Cpp

program_options = 
  CppOptionParserGenerator.new( {
                                  :name => 'Map_vs_set',
                                  :standard_logging => true,
                                  :brief => 'Which is faster, std::map< K, V > where K is embedded in V or std::set< V > with operator< a comparison on the embedded K in V',
                                  :options => [
                                               { 
                                                 :name => 'orders',
                                                 :short_name => 'o',
                                                 :cpp_type => 'int',
                                                 :descr => 'Number of orders',
                                                 :default_value => '1000000',
                                               },
                                              ],

                                })

app = Application.new(
                      { 
                        :name => 'map_vs_set',
                        :program_options => program_options,
                        :app_sig_handler => false,
                        :folder => 'performance',
                        :classes => 
                        [
                         CppClass.new(
                                      { 
                                        :name => 'Value_small',
                                        :header_only => true,
                                        :members =>
                                        [
                                         { 
                                           :name => 'embedded_key',
                                           :member_ctor => true,
                                         },
                                        ],
                                      }),
                         CppClass.new(
                                      { 
                                        :name => 'Value_medium',
                                        :header_only => true,
                                        :members =>
                                        [
                                         { 
                                           :name => 'embedded_key',
                                           :member_ctor => true,
                                         },
                                         { 
                                           :name => 'i1',
                                           :cpp_type => 'int',
                                         },
                                         { 
                                           :name => 'd1',
                                           :cpp_type => 'double',
                                         },
                                         { 
                                           :name => 'd2',
                                           :cpp_type => 'double',
                                         },
                                         { 
                                           :name => 'i2',
                                           :cpp_type => 'int',
                                         },

                                        ],
                                      }),
                         CppClass.new(
                                      { 
                                        :name => 'Value_large',
                                        :header_only => true,
                                        :members =>
                                        [
                                         { 
                                           :name => 'embedded_key',
                                           :member_ctor => true,
                                         },
                                        ] + 
                                        (1..20).map {|i| {:name => "i_#{i}", :cpp_type => 'int', :init => '0' } } + 
                                        (1..20).map {|d| {:name => "d_#{d}", :cpp_type => 'double', :init => '0.0' } },
                                      }),
                        ],
                        :namespace => [ 'fcs', 'performance', ],
                        :app_includes => 
                        [ 
                         'value_small.hpp',
                         'value_medium.hpp',
                         'value_large.hpp',
                        ],
                        :jam_requirements => [ 
                                             ],
                      }
                      )

