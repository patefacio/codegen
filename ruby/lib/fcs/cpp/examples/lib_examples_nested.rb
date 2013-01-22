require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

classes = [

           CppClass.new({ 
                          :name => 'outer',
                          :streamable => true,
                          :ctor_member_init_method => true,
                          :members => 
                          [
                           {
                             :name => 'a',
                             :cpp_type => 'int',
                             :init => 5,
                             :member_ctor => true,
                           }
                          ],
                          :nested_classes => 
                          [
                           CppClass.new({ 
                                          :name => 'inner',
                                          :streamable => true,
                                          # NOTE LIMITATION: ctor_member_init can only be inline
                                          :ctor_member_init_inline_method => true,
                                          :members => 
                                          [
                                           {
                                             :name => 'a',
                                             :cpp_type => 'int',
                                             :init => 3,
                                             :member_ctor => true,
                                           }
                                          ],
                                        })
                          ]
                                       
                        }),
           ]

lib = Codegen::Cpp::Library.new({ 
                                  :name =>'examples',
                                  :namespace => ['fcs', 'examples', 'nested'],
                                  :static_only => true,
                                  :classes => classes,
                                })
