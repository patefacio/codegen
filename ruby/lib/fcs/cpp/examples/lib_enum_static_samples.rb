require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp
require 'fcs/examples/enum_common'
classes = [
           CppClass.new({ 
                          :name => 'api_header',
                          :api_decl => 'ENUM_SAMPLES',
                          :include_unit_test => true,
                          :header_includes => 
                          [
                           'iostream'
                          ],
                          :is_api_header => true,
                          :enums => $enum_samples.map { |e| make_enum_specific(e, 'API') } + 
                          [
                           {
                             :brief => "Dohh - clearly self explanatory",
                             :name => 'API_ANSWER_OF_UNIVERSE', 
                             :const_value => 42,
                           },
                          ],
                        }),
           CppClass.new($some_class),
           CppClass.new($some_other_class),
          ]

lib = Codegen::Cpp::Library.new({ 
                                  :name => 'enums_static',
                                  :jam_requirements => [ 
                                                        '$(PANTHEIOS_LIBS)'
                                                       ],
                                  :namespace => ['fcs', 'examples', 'enums_static' ],
                                  :classes => classes,
                                })
