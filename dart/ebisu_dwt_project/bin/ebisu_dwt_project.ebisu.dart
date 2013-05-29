import "dart:io";
import "package:pathos/path.dart" as path;
import "package:ebisu/ebisu.dart";
import "package:ebisu/ebisu_id.dart";
import "package:ebisu/ebisu_dart_meta.dart";

String _topDir = path.dirname(path.dirname(path.absolute(new Options().script)));

main() {
  print("Root => ${_topDir}");
  System ebisu_dwt_project = system('ebisu_dwt_project')
    ..rootPath = _topDir
    ..pubSpec = (pubspec('ebisu_dwt_project')
        ..dependencies = [
          pubdep('pathos'),
          pubdep('ebisu')
          ..path = ebisuPath,
          pubdep('dart_web_toolkit')
        ]
    )
    ..scripts = [
    ]
    ..libraries = [
      library('ebisu_dwt_project')
      ..imports = [
        '"package:ebisu/ebisu.dart"',
        '"package:ebisu/ebisu_id.dart"',
        'io',
      ]
      ..parts = [
        part('dwt_project')
        ..enums = [
            /*
          enum_('component_type')
          ..doc = 'DWT type associated with this component'
          ..values = [ 
            id('html_panel'),
            id('split_layout_panel'),  
            id('text_box'),
            id('text_area'),
          ]
            */
        ]
        ..classes = [
          class_('component_library')
          ..doc = 'Named grouping of components - just for organization and potentially dependency management'
          ..members = [
            member('id')
            ..doc = 'Id of the component library'
            ..ctors = [''],
            member('doc')
            ..doc = 'Documentation for this library',
            member('components')
            ..doc = 'List of components in this library'
            ..type = 'List<Component>'
            ..classInit = '[]',
            member('finalized')
            ..doc = 'Set to true when finalized'
            ..type = 'bool'
            ..classInit = 'false'
            ..access = Access.RO,
          ],
          class_('component')
          ..doc = 'A project GUI component'
          ..members = [
            member('id')
            ..doc = 'Id for this component'
            ..ctors = ['']
            ..type = 'Id',
            member('doc')
            ..doc = 'Description of component',
            member('type')
            ..doc = 'Type of DWT component'
            ..type = 'Id'
            ..access = Access.RO,
            member('extends_super')
            ..doc = 'Super class being extended by this component'
            ..type = 'Id',
            member('implements_interfaces')
            ..doc = 'List of this component implements'
            ..type = 'List<Id>'
            ..classInit = '[]',
            member('owner')
            ..doc = 'Component library that owns the component'
            ..type = 'ComponentLibrary'
            ..access = Access.RO,
            member('finalized')
            ..doc = 'Set to true when finalized'
            ..type = 'bool'
            ..classInit = 'false'
            ..access = Access.RO,
          ],
          class_('project')
          ..doc = 'For generating the shell of a DWT web app'
          ..members = [
            member('id')
            ..doc = 'Id for this project'
            ..ctors = ['']
            ..type = 'Id',
            member('doc')
            ..doc = 'Project description',
            member('root_path')
            ..doc = 'Root path to the generated dwt project',
            member('component_libraries')
            ..doc = 'List of component libraries to generate'
            ..type= 'List<ComponentLibrary>'
            ..classInit = '[]',
            member('libraries')
            ..doc = 'List of additional libraries to generate'
            ..type= 'Library',
            member('finalized')
            ..doc = 'Set to true when finalized'
            ..type = 'bool'
            ..classInit = 'false'
            ..access = Access.RO,
            member('project_path')
            ..doc = 'Path to top of project directory'
            ..access = Access.RO,
            member('web_path')
            ..doc = 'Path to web directory'
            ..access = Access.RO,
            member('index_file_path')
            ..doc = 'Path to generated index.html file'
            ..access = Access.RO,
            member('css_file_path')
            ..doc = 'Path to generated css.html file'
            ..access = Access.RO,

          ]
        ]
      ]
    ];

  ebisu_dwt_project.generate();
}

