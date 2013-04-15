part of meta;

/// Access for member variable - ia - inaccessible, ro - read/only, rw read/write
class Access { 
  static const IA = const Access._(0);
  static const RO = const Access._(1);
  static const RW = const Access._(2);

  static get values => [
    IA,
    RO,
    RW
  ];

  final int value;

  const Access._(this.value);

  String toString() { 
    switch(this) { 
      case IA: return "IA";
      case RO: return "RO";
      case RW: return "RW";
    }
  }

  static Access fromString(String s) { 
    switch(s) { 
      case "IA":  return IA;
      case "RO":  return RO;
      case "RW":  return RW;
    }
  }

  int toJson() { 
    return this.value;
  }

  static Access fromJson(int v) { 
    switch(v) { 
      case IA.value: return IA;
      case RO.value: return RO;
      case RW.value: return RW;
    }
  }
}

/// Access in the D sense
class DAccess { 
  static const PUBLIC = const DAccess._(0);
  static const PRIVATE = const DAccess._(1);
  static const PACKAGE = const DAccess._(2);
  static const PROTECTED = const DAccess._(3);
  static const EXPORT = const DAccess._(4);

  static get values => [
    PUBLIC,
    PRIVATE,
    PACKAGE,
    PROTECTED,
    EXPORT
  ];

  final int value;

  const DAccess._(this.value);

  String toString() { 
    switch(this) { 
      case PUBLIC: return "PUBLIC";
      case PRIVATE: return "PRIVATE";
      case PACKAGE: return "PACKAGE";
      case PROTECTED: return "PROTECTED";
      case EXPORT: return "EXPORT";
    }
  }

  static DAccess fromString(String s) { 
    switch(s) { 
      case "PUBLIC":  return PUBLIC;
      case "PRIVATE":  return PRIVATE;
      case "PACKAGE":  return PACKAGE;
      case "PROTECTED":  return PROTECTED;
      case "EXPORT":  return EXPORT;
    }
  }

  int toJson() { 
    return this.value;
  }

  static DAccess fromJson(int v) { 
    switch(v) { 
      case PUBLIC.value: return PUBLIC;
      case PRIVATE.value: return PRIVATE;
      case PACKAGE.value: return PACKAGE;
      case PROTECTED.value: return PROTECTED;
      case EXPORT.value: return EXPORT;
    }
  }
}

/// User defined data type
class Udt { 
  static const ALIAS = const Udt._(0);
  static const ENUM = const Udt._(1);
  static const STRUCT = const Udt._(2);
  static const UNION = const Udt._(3);

  static get values => [
    ALIAS,
    ENUM,
    STRUCT,
    UNION
  ];

  final int value;

  const Udt._(this.value);

  String toString() { 
    switch(this) { 
      case ALIAS: return "ALIAS";
      case ENUM: return "ENUM";
      case STRUCT: return "STRUCT";
      case UNION: return "UNION";
    }
  }

  static Udt fromString(String s) { 
    switch(s) { 
      case "ALIAS":  return ALIAS;
      case "ENUM":  return ENUM;
      case "STRUCT":  return STRUCT;
      case "UNION":  return UNION;
    }
  }

  int toJson() { 
    return this.value;
  }

  static Udt fromJson(int v) { 
    switch(v) { 
      case ALIAS.value: return ALIAS;
      case ENUM.value: return ENUM;
      case STRUCT.value: return STRUCT;
      case UNION.value: return UNION;
    }
  }
}

class BasicType { 
  BasicType(
    this._name,
    this._init
  ) {
  }
  
  String _name;
  String get name => _name;
  
  dynamic _init;
  dynamic get init => _init;
  
// custom <class BasicType>

  String toString() => _name;

// end <class BasicType>


  Map toJson() { 
    return { 
    "name": EBISU_UTILS.toJson(_name),
    "init": EBISU_UTILS.toJson(_init),
    };
  }
}

/// Holder for packages, apps, and the root path
class System { 
  System(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this system
  Id get id => _id;
  
  /// Documentation for this system
  String doc;
  
  /// Top level path to which code is generated
  String rootPath;
  
  /// List of apps in the system
  List<App> apps;
  
  /// List of apps in the system
  List<Package> packages;
  
  bool _finalized = false;
  /// Set to true when system is finalized
  bool get finalized => _finalized;
  
// custom <class System>

  void finalize() {
    if(!_finalized) {
      if(packages != null) packages.forEach((pkg) => pkg._finalize(this)); 
      if(apps != null) app.forEach((pkg) => app._finalize(this)); 
      _finalized = true;
    }
  }

  void generate() {
    finalize();
    packages.forEach((pkg) => pkg.generate());
  }

  dynamic get root => this;
  String get pkgPath => "${rootPath}";

// end <class System>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "rootPath": EBISU_UTILS.toJson(rootPath),
    "apps": EBISU_UTILS.toJson(apps),
    "packages": EBISU_UTILS.toJson(packages),
    "finalized": EBISU_UTILS.toJson(_finalized),
    };
  }
}

/// Meta data required for D package
class Package { 
  Package(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this D package
  Id get id => _id;
  
  /// Documentation for this D package
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this D package
  dynamic get parent => _parent;
  
  String _name;
  /// The generated name for enum
  String get name => _name;
  
  /// List of modules in the package
  List<Module> modules;
  
  /// List of packages in the package
  List<Package> packages;
  
// custom <class Package>

  void _finalize(dynamic parent) {
    if(modules != null) modules.forEach((module) => module._finalize(this)); 
    if(packages != null) packages.forEach((pkg) => pkg._finalize(this)); 
    _parent = parent;
  }

  void generate() {
    if(_parent == null) 
      throw new StateError("Finalize the system before generating Package ${_id}");
    if(null != modules)
      modules.forEach((module) => module.generate());
    if(null != packages)
      packages.forEach((pkg) => pkg.generate());
  }

  dynamic get root => _parent.root;
  String get pkgPath => "${_parent.pkgPath}/${_id.snake}";

// end <class Package>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "modules": EBISU_UTILS.toJson(modules),
    "packages": EBISU_UTILS.toJson(packages),
    };
  }
}

/// Meta data required for D module
class Module extends Decls { 
  Module(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this D package
  Id get id => _id;
  
  /// Documentation for this D package
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this D struct
  dynamic get parent => _parent;
  
  /// List of modules to import
  List<String> imports = [];
  
  /// List of modules to import publicly
  List<String> publicImports = [];
  
  /// List of modules to import under the debug
  List<String> debugImports = [];
  
// custom <class Module>

  String get name => _id.snake;

  void _finalize(Package parent) {
    finalizeDecls(this);
    _parent = parent;
    // prefix std imports
    imports = imports.map((i) => _standardImports.contains(i)? "std.${i}" : i).toList();
    imports.sort();
    imports = imports.where((i) => !i.contains('std.')).toList()..addAll(imports.where((i) => i.contains('std.')));
  }

  String get contents => decls();

  void generate() {
    if(_parent == null) 
      throw new StateError("Finalize the system before generating Module ${_id}");

    String targetFile = "${pkgPath}/${_id.snake}.d";
    mergeWithFile(META.module(this), targetFile);
  }

  dynamic get root => _parent.root;
  String get pkgPath => "${_parent.pkgPath}";

  String importStatement(String i) {
    if(_standardImports.contains(i)) {
      return "import std.${i}";
    } else {
      return "import ${i}";
    }
  }

// end <class Module>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "imports": EBISU_UTILS.toJson(imports),
    "publicImports": EBISU_UTILS.toJson(publicImports),
    "debugImports": EBISU_UTILS.toJson(debugImports),
    "Decls": super.toJson(),
    };
  }
}

/// An entry in an enum
class EnumValue { 
  EnumValue(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this enum value
  Id get id => _id;
  
  String _name;
  /// The generated name for enum value
  String get name => _name;
  
  /// Documentation for this enum value
  String doc;
  
  /// Set value of the enum value only if required
  String value;
  
// custom <class EnumValue>

  void _finalize() {
    _name = _id.capCamel;
  }

  String get decl {
    String result = (null != doc)? (blockComment(doc)+'\n') : '';
    if(null == value) {
      result += '$name';
    } else {
      result += '$name = $value';
    }
    return result;
  }

// end <class EnumValue>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(_name),
    "doc": EBISU_UTILS.toJson(doc),
    "value": EBISU_UTILS.toJson(value),
    };
  }
}

/// A template mixin
class TMixin { 
  TMixin(
    this.name
  ) {
  }
  
  /// Textual name of template mixin
  String name;
  
  /// D langauge access for this template mixin
  DAccess dAccess = DAccess.PUBLIC;
  
  /// List of template args
  List<String> tArgs = [];
  
// custom <class TMixin>

  String get argsDecl => 
    tArgs.length>1 ? "!(${tArgs.join(',')})" : 
    (tArgs.length==1 ? "!${tArgs[0]}" : '');

  String get decl => 'mixin ${name}${argsDecl}';

// end <class TMixin>


  Map toJson() { 
    return { 
    "name": EBISU_UTILS.toJson(name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "tArgs": EBISU_UTILS.toJson(tArgs),
    };
  }
}

class Enum { 
  Enum(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this enum
  Id get id => _id;
  
  /// Documentation for this enum
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this enum
  dynamic get parent => _parent;
  
  String _name;
  /// The generated name for enum
  String get name => _name;
  
  /// D langauge access for this enum
  DAccess dAccess = DAccess.PUBLIC;
  
  /// List if Id's that constitute the values
  List<EnumValue> values;
  
// custom <class Enum>

  String define() {
    return META.enum(this);
  }

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
    values.forEach((v) => v._finalize());
    _parent = parent;
  }

// end <class Enum>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "values": EBISU_UTILS.toJson(values),
    };
  }
}

class Constant { 
  Constant(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this constant
  Id get id => _id;
  
  /// Documentation for this constant
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this constant
  dynamic get parent => _parent;
  
  String _name;
  /// The generated name for constant
  String get name => _name;
  
  /// D langauge access for this constant
  DAccess dAccess = DAccess.PUBLIC;
  
  /// True if constant is static
  bool isStatic = false;
  
  /// True if constant is requires static this
  bool hasStaticThis = false;
  
  /// Type of the constant
  String type = "String";
  
  /// Value to initialize the constant with
  String init;
  
// custom <class Constant>

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
    _parent = parent;
  }

  String define() {
    return META.constant(this);
  }

// end <class Constant>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "isStatic": EBISU_UTILS.toJson(isStatic),
    "hasStaticThis": EBISU_UTILS.toJson(hasStaticThis),
    "type": EBISU_UTILS.toJson(type),
    "init": EBISU_UTILS.toJson(init),
    };
  }
}

class Union extends Decls { 
  Union(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this union
  Id get id => _id;
  
  /// Documentation for this union
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this union
  dynamic get parent => _parent;
  
  String _name;
  /// The generated name for union
  String get name => _name;
  
  /// D langauge access for this D struct
  DAccess dAccess = DAccess.PUBLIC;
  
  /// List of members of this class
  List<Member> members = [];
  
// custom <class Union>

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
    _parent = parent;
    finalizeDecls(this);
    members.forEach((member) => member._finalize(this));
  }

  String define() {
    return META.union(this);
  }

// end <class Union>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "members": EBISU_UTILS.toJson(members),
    "Decls": super.toJson(),
    };
  }
}

/// Declaration for an alias
class Alias { 
  Alias(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this alias
  Id get id => _id;
  
  /// Documentation for this alias
  String doc;
  
  String _name;
  /// The generated name for alias
  String get name => _name;
  
  /// D langauge access for this D struct
  DAccess dAccess = DAccess.PUBLIC;
  
  /// What the alias is aliased to
  String aliased;
  
// custom <class Alias>

  String get decl {
    String result = (null != doc)? (blockComment(doc)+'\n') : '';
    result += "alias ${aliased} ${name}";
    return result;
  }

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
  }

// end <class Alias>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "aliased": EBISU_UTILS.toJson(aliased),
    };
  }
}

/// Declaration for an alias to an array
class ArrAlias { 
  ArrAlias(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this array alias
  Id get id => _id;
  
  /// Documentation for this array alias
  String doc;
  
  String _name;
  /// The generated name for array alias
  String get name => _name;
  
  /// D langauge access for this array alias
  DAccess dAccess = DAccess.PUBLIC;
  
  /// Type which the list is of e.g. "Foo" means create alias "Foo[]".
  /// If this is not set, the id is used to form consistent alias.
  /// ArrAlias('foo') => "alias immutable(Foo)[] FooArr"
  /// ArrAlias('foo')..immutable = false => "alias Foo[] FooArr"
  /// 
  String aliased;
  
  /// If true aliased type will have an immutable e.g. "immutable(Foo)[]"
  bool immutable = true;
  
// custom <class ArrAlias>

  String get decl {
    if(immutable) {
      return "alias immutable(${aliased})[] ${name}Arr";
    } else {
      return "alias ${aliased}[] ${name}Arr";
    }
  }

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
    aliased = _name;
  }

// end <class ArrAlias>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "aliased": EBISU_UTILS.toJson(aliased),
    "immutable": EBISU_UTILS.toJson(immutable),
    };
  }
}

/// Declaration for an alias to an associative array
class AArrAlias { 
  AArrAlias(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this array alias
  Id get id => _id;
  
  /// Documentation for this array alias
  String doc;
  
  String _name;
  /// The generated name for array alias
  String get name => _name;
  
  /// D langauge access for this array alias
  DAccess dAccess = DAccess.PUBLIC;
  
  /// Type of the key
  String key;
  
  /// Type of the value
  String value;
  
// custom <class AArrAlias>

  String get decl {
    return "alias ${value}[${key}] ${name}Map";
  }

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
  }

// end <class AArrAlias>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "key": EBISU_UTILS.toJson(key),
    "value": EBISU_UTILS.toJson(value),
    };
  }
}

class TemplateParm { 
  TemplateParm(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this template parm
  Id get id => _id;
  
  /// Documentation for this template parm
  String doc;
  
  String _name;
  /// The generated name for template parm
  String get name => _name;
  
  /// Name of the type
  String typeName;
  
  /// A default value for the parameter
  String init;
  
// custom <class TemplateParm>

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
    _parent = parent;
  }

// end <class TemplateParm>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "typeName": EBISU_UTILS.toJson(typeName),
    "init": EBISU_UTILS.toJson(init),
    };
  }
}

/// Defines a D template
class Template extends Decls { 
  Template(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this template
  Id get id => _id;
  
  /// Documentation for this template
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this template
  dynamic get parent => _parent;
  
  String _name;
  /// The generated name for template
  String get name => _name;
  
  List<TemplateParm> templateParms;
  
  /// D langauge access for this D struct
  DAccess dAccess = DAccess.PUBLIC;
  
// custom <class Template>
// end <class Template>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "templateParms": EBISU_UTILS.toJson(templateParms),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "Decls": super.toJson(),
    };
  }
}

/// Container for generated code
class CodeBlock { 
  /// D langauge access for this code block
  DAccess dAccess = DAccess.PUBLIC;
  
  /// Block of code to be placed in a container
  String code;
  
// custom <class CodeBlock>

// end <class CodeBlock>


  Map toJson() { 
    return { 
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "code": EBISU_UTILS.toJson(code),
    };
  }
}

/// Container for declarations
class Decls { 
  List mixins = [];
  
  List<Alias> aliases = [];
  
  List<Constant> constants = [];
  
  List<Struct> structs = [];
  
  List<Enum> enums = [];
  
  List<Union> unions = [];
  
  List<Template> templates = [];
  
  List<CodeBlock> codeBlocks = [];
  
  List<Member> members = [];
  
  bool privateSection = false;
  
  bool publicSection = false;
  
  bool unitTest = false;
  
// custom <class Decls>

  Decls(){}

  bool empty() {
    return (
        mixins.length + aliases.length + constants.length+
        structs.length + enums.length + unions.length +
        templates.length + codeBlocks.length + members.length)==0;
  }

  Decls filter(DAccess access) {
    Decls result = new Decls();
    result.mixins = mixins.where((e) => e.dAccess == access).toList();
    result.aliases = aliases.where((e) => e.dAccess == access).toList();
    result.constants = constants.where((e) => e.dAccess == access).toList();
    result.structs = structs.where((e) => e.dAccess == access).toList();
    result.enums = enums.where((e) => e.dAccess == access).toList();
    result.unions = unions.where((e) => e.dAccess == access).toList();
    result.templates = templates.where((e) => e.dAccess == access).toList();
    result.codeBlocks = codeBlocks.where((e) => e.dAccess == access).toList();
    result.members = members.where((e) => e.dAccess == access).toList();
    return result;
  }

  void finalizeDecls(dynamic parent) {
    // mixins don't require finalize
    aliases.forEach((alias) => alias._finalize(this));
    constants.forEach((constant) => constant._finalize(this));
    structs.forEach((struct) => struct._finalize(this));
    enums.forEach((enum) => enum._finalize(this));
    unions.forEach((union) => union._finalize(this));
    templates.forEach((template) => template._finalize(this));
    // codeBlocks don't require finalize
    // members are finalized by their "owner"
  }

  String decls() {
    String publicCustomBlock = 
      (publicSection)? "\n${customBlock('public $name')}\n" : '';
    String privateCustomBlock = 
      (privateSection)? "\n${customBlock('private $name')}\n" : '';

    List<String> result = [ META.decls(this.filter(DAccess.PUBLIC)), publicCustomBlock ];
    Decls d = this.filter(DAccess.EXPORT);
    if(!d.empty()) {
      result.add('''
export {
${indentBlock(chomp(META.decls(d)))}
}
''');
    }
    d = this.filter(DAccess.PACKAGE);
    if(!d.empty()) {
      result.add('''
package {
${indentBlock(chomp(META.decls(d)))}
}
''');
    }

    d = this.filter(DAccess.PROTECTED);
    if(!d.empty()) {
      result.add('''
protected {
${indentBlock(chomp(META.decls(d)))}
}
''');
    }

    d = this.filter(DAccess.PRIVATE);
    if(!d.empty()) {
      result.add('''
private {
${indentBlock(chomp(META.decls(d)))}
$privateCustomBlock}
''');
    }

    return result.join('');
  }

// end <class Decls>


  Map toJson() { 
    return { 
    "mixins": EBISU_UTILS.toJson(mixins),
    "aliases": EBISU_UTILS.toJson(aliases),
    "constants": EBISU_UTILS.toJson(constants),
    "structs": EBISU_UTILS.toJson(structs),
    "enums": EBISU_UTILS.toJson(enums),
    "unions": EBISU_UTILS.toJson(unions),
    "templates": EBISU_UTILS.toJson(templates),
    "codeBlocks": EBISU_UTILS.toJson(codeBlocks),
    "members": EBISU_UTILS.toJson(members),
    "privateSection": EBISU_UTILS.toJson(privateSection),
    "publicSection": EBISU_UTILS.toJson(publicSection),
    "unitTest": EBISU_UTILS.toJson(unitTest),
    };
  }
}

/// Meta data required for D struct
class Struct extends Decls { 
  Struct(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this D struct
  Id get id => _id;
  
  /// Documentation for this D struct
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this D struct
  dynamic get parent => _parent;
  
  String _name;
  /// The generated name for D struct
  String get name => _name;
  
  /// D langauge access for this D struct
  DAccess dAccess = DAccess.PUBLIC;
  
  /// List of members of this class
  List<Member> members = [];
  
// custom <class Struct>

  void _finalize(dynamic parent) {
    _name = _id.capCamel;
    _parent = parent;
    finalizeDecls(this);
    members.forEach((member) => member._finalize(this));
  }

  String define() {
    return META.struct(this);
  }

// end <class Struct>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "members": EBISU_UTILS.toJson(members),
    "Decls": super.toJson(),
    };
  }
}

/// Meta data required for D member
class Member { 
  Member(
    this._id
  ) {
  }
  
  final Id _id;
  /// Id for this D member
  Id get id => _id;
  
  /// Documentation for this D member
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this D member
  dynamic get parent => _parent;
  
  String _name;
  /// The generated name for D member
  String get name => _name;
  
  /// D langauge access for this D struct
  DAccess dAccess = DAccess.PUBLIC;
  
  String _vName;
  /// Name of member as stored in struct/class/union
  String get vName => _vName;
  
  /// D developer access for this D member
  Access access = Access.IA;
  
  /// The type for this member
  dynamic type;
  
  /// What to initialize member to
  dynamic init;
  
  /// If set preferred pass type is by ref
  bool byRef = false;
  
  /// If set this member is included in the ctor
  bool ctor = false;
  
  /// If set this member is included in the ctor with `init` member as the default.
  /// It only makes sense to use either `ctor` or `ctor_defaulted` and if using
  /// `ctor_defaulted` init should be set.
  bool ctorDefaulted = false;
  
// custom <class Member>

  void _finalize(dynamic parent) {
    if(_parent != null) {
      throw new StateError("Finalize must be called only once on $this => $id");
    }
    _name = _id.camel;
    _parent = parent;
    if(access == Access.RO) {
      _vName = '_$_name';
      dAccess = DAccess.PRIVATE;
      parent.mixins.add(new TMixin('ReadOnly')..tArgs = [ _vName ]);
    } else {
      if(access == Access.RW) {
        dAccess = DAccess.PUBLIC;
      } else {
        dAccess = DAccess.PRIVATE;
      }
      _vName = _name;
    }
    if(null == type) {
      type = _id.capCamel;
    }
  }

  String get decl {
    String result = '';
    if(null != doc) {
      result += (blockComment(doc) + '\n');
    }
    if(null != init) {
      result += '${type} ${_vName} = ${init}';
    } else {
      result += '${type} ${_vName}';
    }
    return result;
  }

// end <class Member>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dAccess": EBISU_UTILS.toJson(dAccess),
    "vName": EBISU_UTILS.toJson(_vName),
    "access": EBISU_UTILS.toJson(access),
    "type": EBISU_UTILS.toJson(type),
    "init": EBISU_UTILS.toJson(init),
    "byRef": EBISU_UTILS.toJson(byRef),
    "ctor": EBISU_UTILS.toJson(ctor),
    "ctorDefaulted": EBISU_UTILS.toJson(ctorDefaulted),
    };
  }
}
// custom <part meta>

Id id(String _id) => new Id(_id);
System system(String _id) => new System(id(_id));
Package package(String _id) => new Package(id(_id));
Module module(String _id) => new Module(id(_id));
Struct struct(String _id) => new Struct(id(_id));
Member member(String _id) => new Member(id(_id));
Alias alias(String _id) => new Alias(id(_id));
ArrAlias arrAlias(String _id) => new ArrAlias(id(_id));
AArrAlias aArrAlias(String _id, String key, String value) => 
  new AArrAlias(id(_id))..key = key..value = value;
Constant constant(String _id) => new Constant(id(_id));
Union union(String _id) => new Union(id(_id));
Enum enum(String _id) => new Enum(id(_id));
EnumValue ev(String _id) => new EnumValue(id(_id));
TMixin tmixin(String mixinName) => new TMixin(mixinName);


Alias arr(String type) {
  Id aliasId = id(type+'_arr');
  String aliased = "${aliasId.capCamel}[]";
  Alias result = new Alias(aliasId)..aliased = aliased;
  return result;
}

Set _standardImports = new Set.from([
  'algorithm', 'array', 'ascii', 'base64', 'bigint', 'bitmanip', 'compiler',
  'complex', 'concurrency', 'container', 'conv', 'cpuid', 'cstream', 'csv',
  'ctype', 'datetime', 'demangle', 'encoding', 'exception', 'file', 'format',
  'functional', 'getopt', 'json', 'math', 'mathspecial', 'md5', 'metastrings',
  'mmfile', 'numeric', 'outbuffer', 'parallelism', 'path', 'perf', 'process',
  'random', 'range', 'regex', 'regexp', 'signals', 'socket', 'socketstream',
  'stdint', 'stdiobase', 'stdio', 'stream', 'string', 'syserror', 'system',
  'traits', 'typecons', 'typetuple', 'uni', 'uri', 'utf', 'uuid', 'variant',
  'xml', 'zip', 'zlib',
]);

final Access ia = Access.IA;
final Access ro = Access.RO;
final Access rw = Access.RW;

final DAccess public = DAccess.PUBLIC;
final DAccess private = DAccess.PRIVATE;
final DAccess protected = DAccess.PROTECTED;
final DAccess export = DAccess.EXPORT;

// end <part meta>

