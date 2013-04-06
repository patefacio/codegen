import "package:ebisu/ebisu.dart";
import "package:ebisu/ebisu_id.dart";
import "package:ebisu/ebisu_dart_meta.dart";
import "package:ebisu/ebisu_compiler.dart";
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
          ..access = Access.RO
        ],
        dclass('template_folder')
        ..doc = '''A class to process a folder full of templates, 
all of which get compiled into a single dart library'''
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
          ..classInit = '[]',
        ]
      ]
    ];

  Library ebisu_id = library('ebisu_id')
    ..doc = 'Support for consistent use of identifiers'
    ..imports = [
      '"ebisu_utils.dart" as EBISU_UTILS', 
    ]
    ..parts = [
      part('id')
      ..classes = [
        dclass('id')
        ..doc = '''Given an id (all lower case string of words separated by '_')
provides consistent representations'''
        ..jsonSupport = true
        ..members = [
          member('id')
          ..doc = "String containing the lower case words separated by '_'"
          ..access = Access.RO
          ..isFinal = true,
          member('words')
          ..doc = "Words comprising the id"
          ..type = 'List<String>'
          ..access = Access.RO
          ..isFinal = true
        ]
      ]
    ];

  Library ebisu_utils = library('ebisu_utils')
    ..doc = 'Support to be used by libraries generated with ebisu. Example (toJson)';


  // The following are commonly used members of the meta data classes
  Member doc_member(String owner) => member('doc')
    ..doc = "Documentation for this $owner";

  Member public_member(String owner) => member('is_public')
    ..doc = "True if $owner is public.\nCode generation support will prefix private variables appropriately"
    ..type = 'bool'
    ..classInit = 'false';

  Member id_member(String owner) => member('id')
    ..doc = "Id for this $owner"
    ..type = 'Id'
    ..access = Access.RO
    ..isFinal = true;

  Member parent_member(String owner) => member('parent')
    ..doc = "Reference to parent of this $owner"
    ..type = 'dynamic'
    ..jsonTransient = true
    ..access = Access.RO;

  Member custom_member(String owner) => member('include_custom')
    ..doc = "If true a custom section will be included for $owner"
    ..type = 'bool';

  Library ebisu_dart_meta = library('ebisu_dart_meta')
    ..doc = 'Support for storing dart meta data for purpose of generating code'
    ..imports = [
      'io', 'json', 
      '"ebisu.dart"', 
      '"ebisu_id.dart"', 
      '"ebisu_utils.dart" as EBISU_UTILS', 
      '"templates/dart_meta.dart" as META',
    ]
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
          id_member('variable'),
          doc_member('variable'),
          parent_member('variable'),
          public_member('variable'),
          member('type')
          ..doc = 'Type for the variable'
          ..classInit = '"dynamic"',
          member('init')
          ..doc = '''Text used to initialize the variable
(e.g. 'DateTime(1929, 10, 29)' for <DateTime crashDate = DateTime(1929, 10, 29)>
''',
          member('is_final')
          ..doc = 'True if the variable is final'
          ..type = 'bool'
          ..classInit = 'false',
          member('is_const')
          ..doc = 'True if the variable is const'
          ..type = 'bool'
          ..classInit = 'false',
          member('is_static')
          ..doc = 'True if the variable is static'
          ..type = 'bool'
          ..classInit = 'false',
          member('name')
          ..doc = "Name of the enum class generated sans access prefix"
          ..access = Access.RO,
          member('var_name')
          ..doc = 'Name of variable - varies depending on public/private'
          ..access = Access.RO,
        ],
        dclass('enum')
        ..doc = '''Defines an enum - to be generated idiomatically as a class
See (http://stackoverflow.com/questions/13899928/does-dart-support-enumerations)
'''
        ..members = [
          id_member('enum'),
          doc_member('enum'),
          public_member('enum'),
          parent_member('enum'),
          member('values')
          ..doc = "List of id's naming the values"
          ..type = 'List<Id>'
          ..classInit = '[]',
          member('name')
          ..doc = "Name of the enum class generated sans access prefix"
          ..access = Access.RO,
          member('enum_name')
          ..doc = "Name of the enum class generated with access prefix"
          ..access = Access.RO,
        ],
        dclass('system')
        ..doc = 'Defines a dart system (collection of libraries and apps)'
        ..members = [
          id_member('system'),
          doc_member('system'),
          member('apps')
          ..doc = 'Apps in the system'
          ..type = 'List<App>'
          ..classInit = '[]',
          member('libraries')
          ..doc = 'Libraries in the system'
          ..type = 'List<Library>'
          ..classInit = '[]'
        ],
        dclass('app')
        ..doc = 'Defines a dart application'
        ..members = [
          id_member('app'),
          doc_member('app'),
          parent_member('app'),
          custom_member('app'),
          member('classes')
          ..doc = 'Classes defined in this app'
          ..type = 'List<DClass>'
          ..classInit = '[]',
          member('libraries')
          ..doc = 'List of libraries of this app'
          ..type = 'List<Libraries>'
          ..classInit = '[]',          
        ],
        dclass('library')
        ..doc = "Defines a dart library - a collection of parts"
        ..members = [
          id_member('library'),
          doc_member('library'),
          parent_member('library'),
          custom_member('library'),
          member('imports')
          ..doc = 'List of imports to be included by this library'
          ..type = 'List<String>'
          ..classInit = '[]',
          member('parts')
          ..doc = 'List of parts in this library'
          ..type = 'List<Part>'
          ..classInit = '[]',
          member('variables')
          ..doc = 'List of global variables for this library'
          ..type = 'List<Variable>'
          ..classInit = '[]',
          member('name')
          ..doc = "Name of the library - for use in naming the library file, the 'library' and 'part of' statements"
          ..access = Access.RO,
        ],
        dclass('part')
        ..doc = "Defines a dart part - as in 'part of' source file"
        ..members = [
          id_member('part'),
          doc_member('part'),
          parent_member('part'),
          custom_member('app'),
          member('classes')
          ..doc = 'Classes defined in this part of the library'
          ..type = 'List<DClass>'
          ..classInit = '[]',
          member('enums')
          ..doc = 'Enums defined in this part of the library'
          ..type = 'List<Enum>'
          ..classInit = '[]',
          member('name')
          ..doc = "Name of the part - for use in naming the part file"
          ..access = Access.RO,
        ],
        dclass('d_class')
        ..doc = 'Metadata associated with a Dart class'
        ..members = [
          id_member('Dart class'),
          doc_member('Dart class'),
          parent_member('Dart class'),
          public_member('Dart class'),
          custom_member('app'),
          member('members')
          ..doc = 'List of members of this class'
          ..type = 'List<Member>',
          member('json_support')
          ..doc = "If true, generate toJson/fromJson on all members that are not jsonTransient"
          ..type = 'bool',
          member('name')
          ..doc = "Name of the class - sans any access prefix (i.e. no '_')"
          ..access = Access.RO,
          member('class_name')
          ..doc = "Name of the class, including access prefix"
          ..access = Access.RO,
        ],
        dclass('member')
        ..doc = 'Metadata associated with a member of a Dart class'
        ..members = [
          id_member('class member'),
          doc_member('class member'),
          parent_member('class member'),
          member('type')
          ..doc = 'Type of the member',
          member('access')
          ..doc = 'Access level supported for this member'
          ..type = 'Access',
          member('class_init')
          ..doc = "If provided the member will be initialized to this text in place of declaration of class",
          member('ctor_init')
          ..doc = "If provided the member will be initialized to this text in generated ctor initializers",
          member('ctors')
          ..doc = "List of ctor names to include this member in"
          ..type = 'List<String>'
          ..classInit = '[]',
          member('is_final')
          ..doc = 'True if the member is final'
          ..type = 'bool'
          ..classInit = 'false',
          member('is_const')
          ..doc = 'True if the member is const'
          ..type = 'bool'
          ..classInit = 'false',
          member('is_static')
          ..doc = 'True if the member is static'
          ..type = 'bool'
          ..classInit = 'false',
          member('json_transient')
          ..doc = 'True if the member should not be serialized if the parent class has jsonSupport'
          ..type = 'bool'
          ..classInit = 'false',
          member('name')
          ..doc = "Name of variable for the member, excluding access prefix (i.e. no '_')"
          ..access = Access.RO,
          member('var_name')
          ..doc = 'Name of variable for the member - varies depending on public/private'
          ..access = Access.RO,
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
            ..access = Access.RO
          ]
        ]
      ],
      ebisu_compiler,
      ebisu_id,
      ebisu_dart_meta,
      ebisu_utils
    ];

  ebisu_dart_meta.parts.forEach((part) {
    part.classes.forEach((c) {
      c.jsonSupport = true;
    });
  });
  ebisu.finalize();

  //print(prettyJsonMap(ebisu));

  ebisu.generate();
}