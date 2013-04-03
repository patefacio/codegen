require 'place'
require 'codegen/dart/cg'
require 'logger'
require 'pp'
include Codegen::Dart

ebisu = Place[Place.top] + 'dart' + 'ebisu'

lib = Lib.new({
                :id => 'ebisu',
                :root_path => ebisu,
                :imports =>
                [
                ],
                :public_finals => 
                [
                ],
                :public_typedefs =>
                [
                ],
                :namespace => [],
                :parts =>
                [
                 { 
                   :id => 'ebisu',
                   :classes =>
                   [
                    { 
                      :id => :context,
                      :public => true,
                      :ctor => true,
                      :members =>
                      [
                       { 
                         :id => :data,
                         :type => 'Map',
                       }
                      ]
                    },
                   ]
                 },
                ]
              })

lib.generate

lib = Lib.new({
                :id => 'ebisu_compiler',
                :root_path => ebisu,
                :imports =>
                [
                 :io,
                 'package:pathos/path.dart as path',
                 'ebisu.dart',
                ],
                :public_finals => 
                [
                 [ 'RegExp', :code_re, 'new RegExp("^#<(.*)>\\s*")' ],
                 [ 'RegExp', :comment_re, 'new RegExp("^\\s*#")' ],
                ],
                :public_typedefs =>
                [
                ],
                :namespace => [],
                :parts =>
                [
                 { 
                   :id => 'compiler',
                   :classes =>
                   [
                    { 
                      :id => :template_file,
                      :public => true,
                      :members =>
                      [
                       { 
                         :id => :input_path,
                         :type => 'String',
                         :ctor => 'default',
                       },
                       { 
                         :id => :output_path,
                         :type => 'String',
                         :descr => 'Path to write the dart file',
                         :ctor_named => 'default',
                       },
                       { 
                         :id => :part_of,
                         :type => 'String',
                         :descr => 'Library this function is part of',
                         :ctor_named => 'default',
                       },
                       { 
                         :id => :function_name,
                         :type => 'String',
                       },
                      ]
                    },
                    { 
                      :id => :template_folder,
                      :public => true,
                      :members =>
                      [
                       { 
                         :id => :input_path,
                         :descr => 'Path to folder of templates to be compiled into a single library',
                         :type => 'String',
                         :ctor => 'default',
                       },
                       { 
                         :id => :lib_name,
                         :type => 'String',
                         :descr => 'Name of the libarary associated with the template folder',
                         :ctor => 'default',
                       },
                       { 
                         :id => :output_path,
                         :descr => 'Path to where to generate the dart support library for the templates in the folder',
                         :type => 'String',
                         :ctor_named => 'default',
                       },
                       { 
                         :id => :imports,
                         :type => 'List<String>',
                         :descr => 'Any additional imports - include text after the "import " directly',
                         :ctor_named => 'default',
                       },

                      ]
                    }

                   ]
                 },
                ]
              })


lib.generate


lib = Lib.new({
                :id => 'ebisu_id',
                :root_path => ebisu,
                :imports =>
                [
                ],
                :public_finals => 
                [
                ],
                :public_typedefs =>
                [
                ],
                :namespace => [],
                :parts =>
                [
                 { 
                   :id => :id,
                   :classes =>
                   [
                    { 
                      :id => :id,
                      :json => true,
                      :descr => "Given an id (all lower case string with words separated by '_') provides 
various consistent representations.",
                      :public => true,
                      :custom_ctors => [:default],
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "String containing lower case words separated by '_'",
                         :type => :String,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :words,
                         :descr => "Individual words in the id",
                         :type => 'List<String>',
                         :access => :ro,
                         :ctor_init => "id.split('_')",
                         :final => true,
                       },
                      ]
                    },
                   ]
                 },
                ]
              })


lib.generate


lib = Lib.new({
                :id => 'ebisu_dart_meta',
                :root_path => ebisu,
                :imports =>
                [
                 'ebisu_id.dart',
                ],
                :public_finals => 
                [
                ],
                :public_typedefs =>
                [
                ],
                :namespace => [],
                :parts =>
                [
                 { 
                   :id => :meta,
                   :enums =>
                   [
                    { 
                      :id => :access,
                      :values =>
                      [
                       :ia, :ro, :rw
                      ]
                    }
                   ],
                   :classes =>
                   [
                    { 
                      :id => :enum,
                      :descr => "Defines an enum - to be generated as a class",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the enum",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :values,
                         :type => 'List<Id>',
                         :descr => "The id's of the enums - Id being used to enforce consistency",
                         :public => true,
                       }
                      ]
                    },
                    { 
                      :id => :part,
                      :descr => "Defines a dart part - as in 'part of' source file",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the part",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :classes,
                         :type => 'List<DClass>',
                         :descr => 'The classes composing this part',
                         :public => true,
                       },
                       { 
                         :id => :enums,
                         :type => 'List<Enum>',
                         :descr => 'The enums associated with this part',
                         :public => true,
                       }
                      ]
                    },
                    { 
                      :id => :library,
                      :descr => "Defines a dart library - consisting of multiple parts",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the library",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :parts,
                         :type => 'List<Part>',
                         :descr => 'The parts composing this library',
                         :public => true,
                       }
                      ]
                    },
                    { 
                      :id => :d_class,
                      :descr => "Meta data associated with a dart class",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the class",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :public,
                         :descr => "If true the class is public and named appropriately",
                         :type => 'bool',
                         :public => true,
                         :ctor_init => true,
                       },
                       { 
                         :id => :doc,
                         :descr => "Documentation for the class",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :members,
                         :descr => "Data members of the class",
                         :type => 'List<Member>',
                         :public => true,
                         :ctor_init => '[]',
                       },
                      ]
                    },
                    { 
                      :id => :member,
                      :descr => "Meta data associated with class member",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the member",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :doc,
                         :descr => "Documentation for the class",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :public,
                         :descr => "If true the member is public and named appropriately",
                         :public => true,
                         :type => 'bool',
                         :ctor_init => true,
                       },
                       { 
                         :id => :type,
                         :descr => "Type of the member",
                         :public => true,
                         :type => 'String',
                         :ctor_init => '"String"',
                       },
                       { 
                         :id => :access,
                         :descr => "If true the member is public and named appropriately",
                         :type => 'Access',
                         :public => true,
                         :ctor_init => 'Access.RW',
                       },
                       { 
                         :id => :class_init,
                         :descr => "If provided the member will be initialized in place of declaration of class",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :ctor_init,
                         :descr => "If provided the member will be initialized in all ctor member initializer lists",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :ctors,
                         :descr => "List of ctors to include this member in",
                         :type => 'List<String>',
                         :public => true,
                         :ctor_init => '[]',
                       },
                       { 
                         :id => :var_name,
                         :descr => "Name of variable for the member - varies depending on public/private",
                         :type => 'String',
                       },
                      ]
                    },
                   ]
                 },
                ]
              })


lib.generate
