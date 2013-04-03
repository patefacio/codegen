import "ebisu/ebisu_id.dart";
import "ebisu/ebisu_dart_meta.dart";
import "package:plus/pprint.dart";

void main() {
  showFormats() {
    Id i = new Id("goo_ber_doo");
    print(i.emacs);
    print(i.shout);
    print(i.title);
    print(i.squish);
    print(i.abbrev);
    print(Id.pluralize(i).title);
  }

  //showFormats();

  Member doc_member(String owner) => member('doc')
    ..doc = "Documentation for this $owner";

  Member public_member(String owner) => member('is_public')
    ..doc = "True if $owner is public.\nCode generation support will prefix private variables appropriately";

  Member id_member(String owner) => member('id')
    ..doc = "Id for this $owner";    

  Library ebisu_compiler = library('ebisu_compiler')
    ..doc = 'Supports generating dart code from template files'
    ..variables = [
      variable('code_re')
      ..doc = 'Regex to match a single line if dart code (i.e. in looks like #< ... >)'
      ..type = 'RegExp'
      ..isFinal = true
      ..init = r'new RegExp("^#<(.*)>\\s*")',
      variable('comment_re')
      ..doc = 'Regex to match the comment portion of a comment line (i.e. in looks like #<# ... >)'
      ..type = 'RegExp'
      ..isFinal = true
      ..init = r'new RegExp("^\\s*#")'
    ]
    ..parts = [
      part('compiler')
      ..classes = [
        dclass('template_file')
        ..doc = 'A file with ".tmpl" extension containing mixed dart code and text that can be "realized" by the template engine'
        ..members = [
          member('input_path')
          ..doc = 'Path to file containting template code'
          ..ctors = [ 'default' ],
          member('output_path')
          ..doc = 'Path to write the supporting dart file for the template',
          member('part_of')
          ..doc = 'Name of library this "part" is a part of',
          member('function_name')
          ..isPublic = false
        ],
        dclass('template_folder')
        ..doc = 'A folder full of templates, all of which get compiled into a single dart library'
        ..members = [
          member('input_path')
          ..doc = 'Path to folder of templates'
          ..ctors = [ 'default' ],
          member('output_path')
          ..doc = 'Path to write the supporting dart files for the template folder',
          member('lib_name')
          ..doc = 'Name of dart library to be generated',
          member('imports')
          ..doc = 'List of imports required by the generated dart library'
          ..type = 'List<Import>'
          ..ctorInit = '[]',
        ]
      ]
    ];

  Library ebisu_id = library('ebisu_id')
    ..doc = 'Support for consistent use of identifiers'
    ..parts = [
      part('id')
      ..classes = [
        dclass('id')
        ..doc = '''Given an id (all lower case string of words separated by '_')
provides consistent representations'''
        ..members = [
          member('id')
          ..doc = "String containing the lower case words separated by '_'"
          ..isFinal = true,
          member('words')
          ..doc = "Words comprising the id"
          ..access = Access.RO
          ..ctorInit = "id.split('_')"
          ..isFinal = true
        ]
      ]
    ];

  Library ebisu_dart_meta = library('ebisu_dart_meta')
    ..doc = 'Support for storing dart meta data for purpose of generating code'
    ..parts = [
      part('meta')
      ..enums = [
        enum('access')
        ..values = [
          id('ia'), id('ro'), id('rw')
        ]
      ]
      ..classes = [
        dclass('variable')
        ..members = [
          member('id')
          ..doc = 'Id for the variable - codegen will address naming of private'
          ..ctors = [ 'default' ],
          doc_member('variable'),
          member('type')
          ..doc = 'Type for the variable'
          ..ctorInit = 'dynamic',
          member('init')
          ..doc = '''Text used to initialize the variable
(e.g. 'DateTime(1929, 10, 29)' for <DateTime crashDate = DateTime(1929, 10, 29)>
''',
          member('is_final')
          ..doc = 'True if the variable is final'
          ..type = 'bool'
          ..ctorInit = 'false',
          member('is_const')
          ..doc = 'True if the variable is const'
          ..type = 'bool'
          ..ctorInit = 'false',
          member('is_static')
          ..doc = 'True if the variable is static'
          ..type = 'bool'
          ..ctorInit = 'false'
        ],
        dclass('enum')
        ..doc = '''Defines an enum - to be generated idiomatically as a class
See (http://stackoverflow.com/questions/13899928/does-dart-support-enumerations)
'''
        ..members = [
          id_member('enum'),
          doc_member('enum'),
          member('values')
          ..doc = "List of id's naming the values"
          ..type = 'List<Id>'
          ..ctorInit = '[]',
        ],
        dclass('app')
        ..doc = 'Defines a dart application'
        ..members = [
          id_member('app'),
          doc_member('app'),
          member('classes')
          ..doc = 'Classes defined in this app'
          ..type = 'List<DClass>'
          ..ctorInit = '[]',
          member('libraries')
          ..doc = 'List of libraries of this app'
          ..type = 'List<Libraries>'
          ..ctorInit = '[]',          
        ],
        dclass('library')
        ..doc = "Defines a dart library - a collection of parts"
        ..members = [
          id_member('library'),
          doc_member('library'),
          member('parts')
          ..doc = 'List of parts in this library'
          ..type = 'List<Part>'
          ..ctorInit = '[]',
          member('variables')
          ..doc = 'List of global variables for this library'
          ..type = 'List<Variable>'
          ..ctorInit = '[]',
        ],
        dclass('part')
        ..doc = "Defines a dart part - as in 'part of' source file"
        ..members = [
          id_member('part'),
          doc_member('part'),
          member('classes')
          ..doc = 'Classes defined in this part of the library'
          ..type = 'List<DClass>'
          ..ctorInit = '[]',
          member('enums')
          ..doc = 'Enums defined in this part of the library'
          ..type = 'List<Enum>'
          ..ctorInit = '[]'
        ],
        dclass('d_class')
        ..doc = 'Metadata associated with a Dart class'
        ..members = [
          id_member('Dart class'),
          doc_member('Dart class'),
          public_member('Dart class'),
          member('members')
          ..doc = 'List of members of this class'
          ..type = 'List<Member>'
        ],
        dclass('member')
        ..doc = 'Metadata associated with a member of a Dart class'
        ..members = [
          id_member('class member'),
          doc_member('class member'),
          member('type')
          ..doc = 'Type of the member',
          public_member('class member'),
          member('access')
          ..doc = 'Access level supported for this member'
          ..type = 'Access',
          member('class_init')
          ..doc = "If provided the member will be initialized in place of declaration of class",
          member('ctors')
          ..doc = "List of ctor names to include this member in"
          ..type = 'List<String>'
          ..ctorInit = '[]',
          member('is_final')
          ..doc = 'True if the member is final'
          ..type = 'bool'
          ..ctorInit = 'false',
          member('is_const')
          ..doc = 'True if the member is const'
          ..type = 'bool'
          ..ctorInit = 'false',
          member('is_static')
          ..doc = 'True if the member is static'
          ..type = 'bool'
          ..ctorInit = 'false',
          member('var_name')
          ..doc = 'Name of variablefor the member - varies depending on public/private'
        ]
      ]
    ];

  System ebisu = system('ebisu')
    ..apps = []
    ..libraries = [
      library('ebisu')
      ..doc = 'Primary library for client usage of ebisu'
      ..parts = [
        part('ebisu')
        ..classes = [
          dclass('context')
          ..doc = "Convenience wrapper for a map - passed into templates as variable '_'"
          ..members = [
            member('data')
            ..isFinal = true
            ..doc = "Data being wrapped"
            ..type = 'Map'
            ..isPublic = true
          ]
        ]
      ],
      ebisu_compiler,
      ebisu_id,
      ebisu_dart_meta
    ];

  print(prettyJsonMap(ebisu.toJson()));
}