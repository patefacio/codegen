require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp


lib = Codegen::Cpp::Library.new({ 
                                  :header_only => true,
                                  :jam_requirements => [ 
                                                        '$(PANTHEIOS_LIBS)'
                                                       ],
                                  :namespace => ['samples', 'examples', 'typedef_of' ],
                                  :classes => 
                                  [
                                   { 
                                     :name => 'some_class',
                                     :include_unit_test => true,
                                     :forward_typedefs => 
                                     [
                                      Codegen::Cpp.typedef_vector_of('int'),
                                      Codegen::Cpp.typedef_set_of('char'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double'),

                                      Codegen::Cpp.typedef_vector_of('int', 'ages'),
                                      Codegen::Cpp.typedef_set_of('char', 'letters'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int', 'name_to_age'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double', 'attribute_to_measurements'),


                                      Codegen::Cpp.typedef_vector_of('int', 'int_name'),
                                      Codegen::Cpp.typedef_set_of('char', 'char_name'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int', 'string_int_name'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double', 'string_double_name'),

                                      Codegen::Cpp.typedef_vector_of('int', :full_name => 'Ages_full_name_t'),
                                      Codegen::Cpp.typedef_set_of('char', :full_name => 'Char_full_name_t'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int', :full_name => 'Name_to_age_full_name_t'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double', :full_name => 'Attribute_to_measurements_full_name_t'),

                                     ],
                                     :public_typedefs =>
                                     [
                                      Codegen::Cpp.typedef_vector_of('int'),
                                      Codegen::Cpp.typedef_set_of('char'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double'),

                                      Codegen::Cpp.typedef_vector_of('int', 'ages'),
                                      Codegen::Cpp.typedef_set_of('char', 'letters'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int', 'name_to_age'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double', 'attribute_to_measurements'),


                                      Codegen::Cpp.typedef_vector_of('int', 'int_name'),
                                      Codegen::Cpp.typedef_set_of('char', 'char_name'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int', 'string_int_name'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double', 'string_double_name'),

                                      Codegen::Cpp.typedef_vector_of('int', :full_name => 'Ages_full_name_t'),
                                      Codegen::Cpp.typedef_set_of('char', :full_name => 'Char_full_name_t'),
                                      Codegen::Cpp.typedef_map_of('std::string', 'int', :full_name => 'Name_to_age_full_name_t'),
                                      Codegen::Cpp.typedef_mmap_of('std::string', 'double', :full_name => 'Attribute_to_measurements_full_name_t'),                                     ],
                                   }
                                  ]
                                })
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
