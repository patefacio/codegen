import "dart:io";
import "package:pathos/path.dart" as path;
import "package:ebisu/ebisu.dart";
import "package:ebisu/ebisu_id.dart";
import "package:ebisu/ebisu_compiler.dart";
import "package:ebisu/ebisu_dart_meta.dart";

String _topDir;

void main() {
  Options options = new Options();
  String here = path.absolute(options.script);
  bool noCompile = options.arguments.contains('--no_compile');
  bool compileOnly = options.arguments.contains('--compile_only');
  _topDir = path.dirname(path.dirname(here));
  String templateFolderPath = 
    path.join(_topDir, 'lib', 'templates', 'dlang_meta');
  if(! (new Directory(templateFolderPath).existsSync())) {
    throw new StateError(
        "Could not find ebisu dlang templates in $templateFolderPath");
  }

  if(!noCompile) {
    TemplateFolder templateFolder = new TemplateFolder(templateFolderPath);
    int filesUpdated = templateFolder.compile();
    if(filesUpdated>0) {
      if(!noCompile && !compileOnly) {
        // Files were updated, since Dart does not have eval, call again to same
        // script using updated templates
        print("$filesUpdated files updated...rerunning");
        List<String> args = [ options.script, '--no_compile' ]
          ..addAll(options.arguments);
        Process.run('dart', args).then((ProcessResult results) {
          print(results.stdout);
          print(results.stderr);
        });
      }
    } else {
      if(!compileOnly)
        generate();
    }
  } else {
    generate();
  }
}

 generate() {

   Member doc_member(String owner) => member('doc')
     ..doc = "Documentation for this $owner";

   Member static_member(String owner) => member('is_static')
     ..type = 'bool'
     ..doc = "True if $owner is static"
     ..classInit = 'false';

   Member static_this_member(String owner) => member('has_static_this')
     ..type = 'bool'
     ..doc = "True if $owner is requires static this"
     ..classInit = 'false';

   Member parent_member(String owner) => member('parent')
     ..doc = "Reference to parent of this $owner"
     ..type = 'dynamic'
     ..jsonTransient = true
     ..access = Access.RO;

   Member id_member(String owner) => member('id')
     ..doc = "Id for this $owner"
     ..type = 'Id'
     ..access = Access.RO
     ..ctors = [ '' ]
     ..isFinal = true;

  Member name_member(String owner) => member('name')
    ..doc = "The generated name for $owner"
    ..access = Access.RO
    ..type = 'String';

  Member d_access_member(String owner) => member('d_access')
    ..doc = "D langauge access for this $owner"
    ..type = 'DAccess'
    ..classInit = 'DAccess.PUBLIC';

  Member access_member(String owner) => member('access')
    ..doc = "D developer access for this $owner"
    ..type = 'Access'
    ..classInit = 'Access.RW';

  System ebisu = system('ebisu_dlang')
    ..rootPath = '$_topDir'
    ..pubSpec = (pubspec('ebisu_dlang')
        ..doc = 'A library that supports code generation of dart and others'
        ..dependencies = [
          pubdep('pathos'),
          pubdep('ebisu')
          ..path = '../ebisu',
        ]
                 )
    ..libraries = [
      library('meta')
      ..doc = 'Support for storing dlang meta data for purpose of generating code'
      ..imports = [
        'io', 
        '"dart:json" as JSON', 
        '"package:ebisu/ebisu.dart"', 
        '"package:ebisu/ebisu_id.dart"', 
        '"package:ebisu/ebisu_utils.dart" as EBISU_UTILS', 
        '"templates/dlang_meta.dart" as META',
        '"package:pathos/path.dart" as path',
      ]
      ..variables = [
        variable('void_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('void', null)",
        variable('bool_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('bool', false)",
        variable('byte_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('byte', 0)",
        variable('ubyte_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('ubyte', 0)",
        variable('short_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('short', 0)",
        variable('ushort_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('ushort', 0)",
        variable('int_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('int', 0)",
        variable('uint_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('uint', 0)",
        variable('long_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('long', 0)",
        variable('ulong_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('ulong', 0)",
        variable('cent_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('cent', 0)",
        variable('ucent_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('ucent', 0)",
        variable('float_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('float', 'float_nan')",
        variable('double_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('double', 'double_nan')",
        variable('real_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('real', 'real_nan')",
        variable('ifloat_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('ifloat', 'ifloat_nan')",
        variable('idouble_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('idouble', 'idouble_nan')",
        variable('ireal_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('ireal', 'ireal_nan')",
        variable('cfloat_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('cfloat', 'cfloat_nan')",
        variable('cdouble_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('cdouble', 'cdouble_nan')",
        variable('creal_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('creal', 'creal_nan')",
        variable('char_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('char', 'xff')",
        variable('wchar_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('wchar', 'xffff')",
        variable('dchar_t')..type = 'BasicType'..isFinal = true..init = "new BasicType('dchar', 'x0000ffff')",
      ]
      ..parts = [
        part('meta')
        ..enums = [
          enum_('access')
          ..doc = 'Access for member variable - ia - inaccessible, ro - read/only, rw read/write'
          ..values = [
            id('ia'), id('ro'), id('rw')
          ],
          enum_('d_access')
          ..doc = 'Access in the D sense'
          ..values = [
            id('public'), id('private'), id('package'), id('protected'), id('export')
          ],
          enum_('udt')
          ..doc = 'User defined data type'
          ..values = [
            id('alias'), id('enum'), id('struct'), id('union'),
          ]
        ]
        ..classes = [
          class_('basic_type')
          ..members = [
            member('name')
            ..access = Access.RO
            ..ctors = [''],
            member('init')
            ..type = 'dynamic'
            ..access = Access.RO
            ..ctors = [''],
          ],
          class_('system')
          ..doc = 'Holder for packages, apps, and the root path'
          ..members = [
            id_member('system'),
            doc_member('system'),
            member('root_path')
            ..doc = 'Top level path to which code is generated',
            member('apps')
            ..doc = 'List of apps in the system'
            ..type = 'List<App>',
            member('packages')
            ..doc = 'List of apps in the system'
            ..type = 'List<Package>',
            member('finalized')
            ..doc = 'Set to true when system is finalized'
            ..type = 'bool'
            ..classInit = 'false'
            ..access = Access.RO,
          ],
          class_('package')
          ..doc = 'Meta data required for D package'
          ..members = [
            id_member('D package'),
            doc_member('D package'),
            parent_member('D package'),
            name_member('enum'),
            member('modules')
            ..doc = 'List of modules in the package'
            ..type = 'List<Module>',
            member('packages')
            ..doc = 'List of packages in the package'
            ..type = 'List<Package>',
          ],
          class_('module')
          ..extend = 'Decls'
          ..doc = 'Meta data required for D module'
          ..members = [
            id_member('D package'),
            doc_member('D package'),
            parent_member('D struct'),
            member('imports')
            ..doc = 'List of modules to import'
            ..type = 'List<String>'
            ..classInit = '[]',
            member('public_imports')
            ..doc = 'List of modules to import publicly'
            ..type = 'List<String>'
            ..classInit = '[]',
            member('debug_imports')
            ..doc = 'List of modules to import under the debug'
            ..type = 'List<String>'
            ..classInit = '[]',
          ],
          class_('enum_value')
          ..doc = 'An entry in an enum'
          ..members = [
            id_member('enum value'),
            name_member('enum value'),
            doc_member('enum value'),
            member('value')
            ..doc = 'Set value of the enum value only if required'
          ],
          class_('t_mixin')
          ..doc = 'A template mixin'
          ..members = [
            member('name')
            ..doc = 'Textual name of template mixin'
            ..ctors = [''],
            d_access_member('template mixin'),
            member('t_args')
            ..doc = 'List of template args'
            ..type = 'List<String>'
            ..classInit = '[]'
          ],
          class_('enum')
          ..members = [
            id_member('enum'),
            doc_member('enum'),
            parent_member('enum'),
            name_member('enum'),
            d_access_member('enum'),
            member('values')
            ..doc = "List if Id's that constitute the values"
            ..type = 'List<EnumValue>'
          ],
          class_('constant')
          ..members = [
            id_member('constant'),
            doc_member('constant'),
            parent_member('constant'),
            name_member('constant'),
            d_access_member('constant'),
            static_member('constant'),
            static_this_member('constant'),
            member('type')
            ..doc = 'Type of the constant'
            ..classInit = 'String',
            member('init')..doc = 'Value to initialize the constant with'..type='dynamic',
          ],
          class_('union')
          ..extend = 'Decls'
          ..members = [
            id_member('union'),
            doc_member('union'),
            parent_member('union'),
            name_member('union'),
            d_access_member('D struct'),
            member('members')
            ..doc = 'List of members of this class'
            ..type = 'List<Member>'
            ..classInit = '[]',
          ],
          class_('alias')
          ..doc = 'Declaration for an alias'
          ..members = [
            id_member('alias'),
            doc_member('alias'),
            name_member('alias'),
            d_access_member('D struct'),
            member('aliased')..doc = 'What the alias is aliased to',
          ],
          class_('arr_alias')
          ..doc = 'Declaration for an alias to an array'
          ..members = [
            id_member('array alias'),
            doc_member('array alias'),
            name_member('array alias'),
            d_access_member('array alias'),
            member('aliased')..doc = '''Type which the list is of e.g. "Foo" means create alias "Foo[]".
If this is not set, the id is used to form consistent alias.
ArrAlias('foo') => "alias immutable(Foo)[] FooArr"
ArrAlias('foo')..immutable = false => "alias Foo[] FooArr"
''',
            member('immutable')
            ..doc = 'If true aliased type will have an immutable e.g. "immutable(Foo)[]"'
            ..type = 'bool'
            ..classInit = 'true',
          ],
          class_('a_arr_alias')
          ..doc = 'Declaration for an alias to an associative array'
          ..members = [
            id_member('array alias'),
            doc_member('array alias'),
            name_member('array alias'),
            d_access_member('array alias'),
            member('key')..doc = 'Type of the key',
            member('value')..doc = 'Type of the value',
          ],
          class_('template_parm')
          ..members = [
            id_member('template parm'),
            doc_member('template parm'),
            parent_member('template parm'),            
            name_member('template parm'),
            member('type_name')..doc = 'Name of the type',
            member('is_alias')..doc = 'True if template parm is an alias'..type = 'bool'..classInit = 'false',
            member('init')..doc = 'A default value for the parameter',
          ],
          class_('template')
          ..extend = 'Decls'
          ..doc = 'Defines a D template'
          ..members = [
            id_member('template'),
            doc_member('template'),
            parent_member('template'),
            name_member('template'),
            member('template_parms')..type = 'List<TemplateParm>',
            d_access_member('D struct'),
          ],
          class_('code_block')
          ..doc = 'Container for generated code'
          ..members = [
            d_access_member('code block'),
            member('code')
            ..doc = 'Block of code to be placed in a container'
            ..ctors = ['']
          ],
          class_('decls')
          ..doc = 'Container for declarations'
          ..members = [
            member('mixins')..type = 'List'..classInit = '[]',
            member('aliases')..type = 'List<Alias>'..classInit = '[]',
            member('constants')..type = 'List<Constant>'..classInit = '[]',
            member('structs')..type = 'List<Struct>'..classInit = '[]',
            member('enums')..type = 'List<Enum>'..classInit = '[]',
            member('unions')..type = 'List<Union>'..classInit = '[]',
            member('templates')..type = 'List<Template>'..classInit = '[]',
            member('code_blocks')..type = 'List<CodeBlock>'..classInit = '[]',
            member('members')..type = 'List<Member>'..classInit = '[]',
            member('private_section')..type = 'bool'..classInit = 'false',
            member('public_section')..type = 'bool'..classInit = 'false',
            member('unit_test')..type = 'bool'..classInit = 'false',
          ],
          class_('filtered_decls')
          ..doc = '''The set of decls of given access from specific instance of
item extending Decls (e.g. Module, Union, Template, Struct)'''
          ..extend = 'Decls'
          ..members = [
            name_member('filtered decls'),
            d_access_member('filtered decls'),
          ],
          class_('ctor')
          ..doc = 'What is required to know how to generate a constructor'
          ..members = [
            member('name')
            ..doc = 'Name of struct being constructed'
            ..ctors = [''],
            member('members')
            ..doc = 'Ordered list of members either included directly, etiher as is or with default init'
            ..type = 'List<Member>'
            ..classInit = '[]'
          ],
          class_('struct')
          ..extend = 'Decls'
          ..doc = 'Meta data required for D struct'
          ..members = [
            id_member('D struct'),
            doc_member('D struct'),
            parent_member('D struct'),
            name_member('D struct'),
            d_access_member('D struct'),
            member('ctor')
            ..doc = 'Constructor for this struct'
            ..type = 'Ctor',
            member('template_parms')
            ..doc = '''
List of template parms for this struct.
Existance of any _tParms_ implies this struct is a template struct.
'''
            ..type = 'List<TemplateParm>'
            ..classInit = '[]',
            member('members')
            ..doc = 'List of members of this class'
            ..type = 'List<Member>'
            ..classInit = '[]',
          ],
          class_('member')
          ..doc = 'Meta data required for D member'
          ..members = [
            id_member('D member'),
            doc_member('D member'),
            parent_member('D member'),
            name_member('D member'),
            d_access_member('D struct'),
            member('v_name')
            ..doc = 'Name of member as stored in struct/class/union'
            ..access = Access.RO,
            access_member('D member'),
            member('type')..doc = 'The type for this member'..type = 'dynamic',
            member('init')..doc = 'What to initialize member to'..type = 'dynamic',
            member('by_ref')
            ..doc = 'If set preferred pass type is by ref'
            ..type = 'bool'
            ..classInit = 'false',
            member('by_const')
            ..doc = 'If set preferred pass type is by const (the default)'
            ..type = 'bool'
            ..classInit = 'true',
            member('cast_dup')
            ..doc = '''If set and dup is perform an const cast is provided.
 This allows duping things like maps from const into non-const since safel'''
            ..type = 'bool'
            ..classInit = 'false',
            member('ctor')
            ..doc = 'If set this member is included in the ctor'
            ..type = 'bool'
            ..classInit = 'false',
            member('ctor_defaulted')
            ..doc = '''If set this member is included in the ctor with `init` member as the default.
It only makes sense to use either `ctor` or `ctor_defaulted` and if using
`ctor_defaulted` init should be set.'''
            ..type = 'bool'
            ..classInit = 'false'
          ]
        ]
      ]
    ];

  ebisu.libraries.forEach((library) {
    library.parts.forEach((part) {
      part.classes.forEach((c) {
        c.toJsonSupport = true;
      });
    });
  });

  ebisu.generate();
}