require 'place'
require 'codegen/dart/cg'
require 'logger'
require 'pp'
include Codegen::Dart

ebisu = Place[Place.top] + 'dart' + 'ebisu'

lib = Lib.new({
                :id => 'ebisu',
                :root_path => ebisu,
                :public_finals =>
                [
                ],
                :imports =>
                [
                 :io,
                ],
                :public_typedefs =>
                [
                ],
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
                 :io,
                 'ebisu.dart',
                 'ebisu_id.dart',
                 'templates/dart_meta.dart as META',
                ],
                :public_finals => 
                [
                 [ 'String', :root_path, "'/home/dbdavidson/ebisu_bootstrap'" ]
                ],
                :public_typedefs =>
                [
                ],
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
                      :id => :variable,
                      :descr => "Defines a variable",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the variable",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :doc,
                         :descr => "Documentation for the variable",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :name,
                         :descr => "Name of the variable, without consideration of access - (i.e. no leading '_')",
                         :type => :String,
                         :access => :ro,
                       },
                       { 
                         :id => :var_name,
                         :descr => "Name of the variable",
                         :type => 'String',
                         :public => false,
                         :access => :ro
                       },
                       { 
                         :id => :parent,
                         :type => 'dynamic',
                         :access => :ro,
                       },
                       { 
                         :id => :type,
                         :type => 'String',
                         :descr => "The type of the variable",
                         :public => true,
                         :ctor_init => "'var'",
                       },
                       { 
                         :id => :init,
                         :descr => "Initialization code (e.g. 'DateTime(1929, 10, 29)' for <DateTime crashDate = DateTime(1929, 10, 29)>;",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :is_final,
                         :descr => "True if the variable is final",
                         :type => :bool,
                         :public => true,
                         :ctor_init => false,
                       },
                       { 
                         :id => :is_const,
                         :descr => "True if the variable is const",
                         :type => :bool,
                         :public => true,
                         :ctor_init => false,
                       },
                       { 
                         :id => :is_static,
                         :descr => "True if the variable is static",
                         :type => :bool,
                         :public => true,
                         :ctor_init => false,
                       },
                       { 
                         :id => :is_public,
                         :descr => "If true the variable is public and named appropriately",
                         :type => 'bool',
                         :public => true,
                         :ctor_init => true,
                       },

                      ]
                    },
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
                         :id => :parent,
                         :type => 'dynamic',
                         :access => :ro,
                       },
                       { 
                         :id => :is_public,
                         :descr => "If true the enum is public and named appropriately",
                         :type => 'bool',
                         :public => true,
                         :ctor_init => true,
                       },
                       { 
                         :id => :name,
                         :descr => "Name of the enum sans access qualifier",
                         :type => :String,
                         :access => :ro,
                       },
                       { 
                         :id => :enum_name,
                         :descr => "Name of the enum with access qualifier",
                         :type => :String,
                         :access => :ro,
                       },
                       { 
                         :id => :values,
                         :type => 'List<Id>',
                         :descr => "The id's of the enums - Id being used to enforce consistency",
                         :public => true,
                         :ctor_init => '[]',
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
                         :id => :include_custom,
                         :descr => "If true include custom block",
                         :type => 'bool',
                         :public => true,
                         :ctor_init => true,
                       },
                       { 
                         :id => :name,
                         :descr => "Name of the part - for use in naming the part file",
                         :type => :String,
                         :access => :ro,
                       },
                       { 
                         :id => :parent,
                         :type => 'dynamic',
                         :access => :ro,
                       },
                       { 
                         :id => :classes,
                         :type => 'List<DClass>',
                         :descr => 'The classes composing this part',
                         :public => true,
                         :ctor_init => '[]',
                       },
                       { 
                         :id => :enums,
                         :type => 'List<Enum>',
                         :descr => 'The enums associated with this part',
                         :public => true,
                         :ctor_init => '[]',
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
                         :id => :parent,
                         :type => 'dynamic',
                         :access => :ro,
                       },
                       { 
                         :id => :name,
                         :descr => "Name of the library - for use in library and part statements",
                         :type => :String,
                         :access => :ro,
                       },
                       { 
                         :id => :include_custom,
                         :descr => "If true include custom block",
                         :type => 'bool',
                         :public => true,
                         :ctor_init => true,
                       },
                       { 
                         :id => :doc,
                         :descr => "Documentation for the library",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :imports,
                         :type => 'List<String>',
                         :descr => 'Any additional imports - include text after the "import " directly',
                         :ctor_init => '[]',
                         :public => true,
                       },
                       { 
                         :id => :parts,
                         :type => 'List<Part>',
                         :descr => 'The parts composing this library',
                         :public => true,
                         :ctor_init => '[]',
                       },
                       { 
                         :id => :variables,
                         :type => 'List<Variable>',
                         :descr => 'Global variables for this library',
                         :public => true,
                         :ctor_init => '[]',
                       }
                      ]
                    },


                    { 
                      :id => :app,
                      :descr => "Defines a dart application",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the app",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :parent,
                         :type => 'dynamic',
                         :access => :ro,
                       },
                       { 
                         :id => :libraries,
                         :type => 'List<Library>',
                         :descr => "Libraries defined by this app",
                         :public => true,
                         :ctor_init => '[]',
                       },
                       { 
                         :id => :imports,
                         :type => 'List<String>',
                         :descr => 'Any additional imports - include text after the "import " directly',
                         :ctor_init => '[]',
                       },
                       { 
                         :id => :variables,
                         :type => 'List<Variable>',
                         :descr => 'Global variables for this app',
                         :public => true,
                         :ctor_init => '[]',
                       }
                      ]
                    },
                    { 
                      :id => :system,
                      :descr => "Defines a dart system - collection of libs and apps",
                      :public => true,
                      :json => true,
                      :members =>
                      [
                       { 
                         :id => :id,
                         :descr => "Id of the system",
                         :type => :Id,
                         :ctor => :default,
                         :access => :ro,
                         :final => true,
                       },
                       { 
                         :id => :libraries,
                         :type => 'List<Library>',
                         :descr => "Libraries defined by this app",
                         :public => true,
                       },
                       { 
                         :id => :apps,
                         :type => 'List<App>',
                         :descr => 'List of applications in the system',
                         :public => true,
                         :ctor_named => 'default',
                       },
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
                         :id => :include_custom,
                         :descr => "If true include custom block",
                         :type => 'bool',
                         :public => true,
                         :ctor_init => true,
                       },
                       { 
                         :id => :name,
                         :descr => "Name of the class, without access prefix",
                         :type => :String,
                         :access => :ro,
                       },
                       { 
                         :id => :class_name,
                         :descr => "Name of the class with access prefix",
                         :type => :String,
                         :access => :ro,
                       },
                       { 
                         :id => :parent,
                         :type => 'dynamic',
                         :access => :ro,
                       },
                       { 
                         :id => :is_public,
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
                         :id => :parent,
                         :type => 'dynamic',
                         :access => :ro,
                       },
                       { 
                         :id => :doc,
                         :descr => "Documentation for the class",
                         :type => 'String',
                         :public => true,
                       },
                       { 
                         :id => :type,
                         :descr => "Type of the member",
                         :public => true,
                         :type => 'String',
                         :ctor_init => '"String"',
                       },
                       { 
                         :id => :is_public,
                         :descr => "If true the member is public and named appropriately",
                         :public => true,
                         :type => 'bool',
                         :ctor_init => true,
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
                         :id => :is_final,
                         :descr => "True if the member is final",
                         :type => :bool,
                         :public => true,
                         :ctor_init => false,
                       },
                       { 
                         :id => :is_static,
                         :descr => "True if the member is static",
                         :type => :bool,
                         :public => true,
                         :ctor_init => false,
                       },
                       { 
                         :id => :name,
                         :descr => "Name of variable - excluding any access prefix",
                         :type => 'String',
                         :access => :ro,
                       },
                       { 
                         :id => :var_name,
                         :descr => "Name of variable for the member - varies depending on public/private",
                         :type => 'String',
                         :access => :ro,
                       },
                      ]
                    },
                   ]
                 },
                ]
              })


lib.generate
