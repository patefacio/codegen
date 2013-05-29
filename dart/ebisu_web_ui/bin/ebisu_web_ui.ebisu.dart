import "dart:io";
import "package:pathos/path.dart" as path;
import "package:ebisu/ebisu.dart";
import "package:ebisu/ebisu_id.dart";
import "package:ebisu/ebisu_dart_meta.dart";

String _topDir = path.dirname(path.dirname(path.absolute(new Options().script)));

main() {

  System ebisu_web_ui = system('ebisu_web_ui')
    ..rootPath = _topDir
    ..pubSpec = (pubspec('ebisu_web_ui')
        ..dependencies = [
          pubdep('pathos'),
          pubdep('ebisu')
          ..path = ebisuPath,
        ]
    )
    ..scripts = [
    ]
    ..libraries = [
      library('ebisu_web_ui')
      ..doc = 'Support for generating shell for web components per http://www.dartlang.org/articles/web-ui/spec.html'
      ..imports = [
        '"package:ebisu/ebisu.dart"',
        '"package:ebisu/ebisu_id.dart"',
        '"package:ebisu/ebisu_dart_meta.dart"',
      ]
      ..parts = [
        part('component')
        ..doc = 'Support for stubbing out components'
        ..classes = [
          class_('component_library')
          ..doc = 'Collection of components wrapped in a library (think http://pub.dartlang.org/packages/widget)'
          ..members = [
            member('doc')
            ..doc = 'Documentation for the component library',
            member('root_path')
            ..doc = 'Path in which to generate the component library',
            member('id')
            ..doc = 'Id of the component library'
            ..type = 'Id'
            ..isFinal = true
            ..ctors = [''],
            member('libraries')
            ..doc = 'List of support libraries'
            ..type = 'List<Library>'
            ..classInit = '[]',
            member('components')
            ..doc = 'List of components in the collection'
            ..type = 'List<Component>',
            member('finalized')
            ..doc = 'Set to true on finalize'
            ..access = Access.RO
            ..type = 'bool'
            ..classInit = 'false',
            member('dependencies')
            ..doc = 'List of PubDependency for this component and supporting libraries'
            ..type = 'List<PubDependency>'
            ..classInit = '[]',
          ],
          class_('component')
          ..doc = 'Declaratively define component to generate its stubbed out support'
          ..members = [
            member('id')
            ..doc = 'Id - used to generate name of component'
            ..type = 'Id'
            ..ctors = [''],
            member('doc')
            ..doc = 'Description of the component',
            member('extends_element')
            ..doc = 'Dom element or other component being extended'
            ..classInit = 'div',
            member('constructor')
            ..doc = 'How to construct the component (convention handles unless exceptional case)',
            member('apply_author_styles')
            ..doc = 'If true styles from document apply to control'
            ..type = 'bool'
            ..classInit = 'true',
            member('template_fragment')
            ..doc = 'The internals of template fragment that will be rendered when the component is initialized'
            ..classInit = '',
            member('imports')
            ..doc = 'Dart imports required by the component'
            ..type = 'List<String>'
            ..classInit = '[]',
            member('html_imports')
            ..doc = 'Component imports required by the component'
            ..type = 'List<String>'
            ..classInit = '[]',
            member('name')
            ..doc = 'Name as used in the html (i.e. words of name hyphenated'
            ..access = Access.RO,
            member('finalized')
            ..doc = 'Set to true on finalize'
            ..access = Access.RO
            ..type = 'bool'
            ..classInit = 'false',
          ]
        ]
      ]
      
    ];

  ebisu_web_ui.generate();
}

