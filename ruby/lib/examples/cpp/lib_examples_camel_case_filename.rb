require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

classes = [

           CppClass.new({ 
                          :name => 'example_camel_case_filename',
                          :brief => 'Place class in custom location - somewhere under top',
                          :header_filename => 'ExampleCamelCaseFilename.hpp',
                          :impl_filename => 'ExampleCamelCaseFilename.cpp',
                          :streamable => true,
                          :members => 
                          [
                           {
                             :name => 'a',
                             :cpp_type => 'int'
                           }
                          ]
                                       
                        }),
           ]

lib = Codegen::Cpp::Library.new({ 
                                  :name =>'examples',
                                  :namespace => ['samples', 'examples', 'camel_case_filename'],
                                  :static_only => true,
                                  :classes => classes,
                                })
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
