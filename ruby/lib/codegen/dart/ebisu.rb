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
