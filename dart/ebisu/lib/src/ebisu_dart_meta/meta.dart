part of ebisu_dart_meta;

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

class Variable { 
  final Id _id;
  /// Id for this variable
  Id get id => _id;
  
  /// Documentation for this variable
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this variable
  dynamic get parent => _parent;
  
  /// True if variable is public.
  /// Code generation support will prefix private variables appropriately
  bool isPublic = true;
  
  /// Type for the variable
  String type = "dynamic";
  
  /// Text used to initialize the variable
  /// (e.g. 'DateTime(1929, 10, 29)' for <DateTime crashDate = DateTime(1929, 10, 29)>
  /// 
  String init;
  
  /// True if the variable is final
  bool isFinal = false;
  
  /// True if the variable is const
  bool isConst = false;
  
  /// True if the variable is static
  bool isStatic = false;
  
  String _name;
  /// Name of the enum class generated sans access prefix
  String get name => _name;
  
  String _varName;
  /// Name of variable - varies depending on public/private
  String get varName => _varName;
  
// custom <class Variable>

  Variable(Id id) : _id = id {}

  void set parent(p) {
    _name = id.camel;
    _varName = isPublic? _name : "_${_name}";
    _parent = p;
  }

  String define() {
    return META.variable(this);
  }

// end <class Variable>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "isPublic": EBISU_UTILS.toJson(isPublic),
    "type": EBISU_UTILS.toJson(type),
    "init": EBISU_UTILS.toJson(init),
    "isFinal": EBISU_UTILS.toJson(isFinal),
    "isConst": EBISU_UTILS.toJson(isConst),
    "isStatic": EBISU_UTILS.toJson(isStatic),
    "name": EBISU_UTILS.toJson(_name),
    "varName": EBISU_UTILS.toJson(_varName),
    };
  }
}

/// Defines an enum - to be generated idiomatically as a class
/// See (http://stackoverflow.com/questions/13899928/does-dart-support-enumerations)
/// 
class Enum { 
  final Id _id;
  /// Id for this enum
  Id get id => _id;
  
  /// Documentation for this enum
  String doc;
  
  /// True if enum is public.
  /// Code generation support will prefix private variables appropriately
  bool isPublic = true;
  
  dynamic _parent;
  /// Reference to parent of this enum
  dynamic get parent => _parent;
  
  /// List of id's naming the values
  List<Id> values = [];
  
  String _name;
  /// Name of the enum class generated sans access prefix
  String get name => _name;
  
  String _enumName;
  /// Name of the enum class generated with access prefix
  String get enumName => _enumName;
  
// custom <class Enum>

  Enum(Id id) : _id = id {}

  set parent(p) {
    _name = _id.capCamel;
    _enumName = isPublic? _name : "_$_name";
    _parent = p;
  }

  String define() {
    return META.enum(this);
  }

// end <class Enum>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "isPublic": EBISU_UTILS.toJson(isPublic),
    "values": EBISU_UTILS.toJson(values),
    "name": EBISU_UTILS.toJson(_name),
    "enumName": EBISU_UTILS.toJson(_enumName),
    };
  }
}

/// A dependency of the system
class PubDependency { 
  /// Name of dependency
  String name;
  
  /// Required version for this dependency
  String version;
  
// custom <class PubDependency>

  PubDependency(String _name) : name = _name {
  }

// end <class PubDependency>

  Map toJson() { 
    return { 
    "name": EBISU_UTILS.toJson(name),
    "version": EBISU_UTILS.toJson(version),
    };
  }
}

/// Information for the pubspec of the system
class PubSpec { 
  final Id _id;
  /// Id for this pub spec
  Id get id => _id;
  
  /// Documentation for this pub spec
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this pub spec
  dynamic get parent => _parent;
  
  String _name;
  /// Name of the project described in spec - if not set, id of system is used to generate
  String get name => _name;
  
  List<PubDependency> dependencies;
  
// custom <class PubSpec>

  PubSpec(Id id) : _id = id { 
    _name = _id.camel;
  }

// end <class PubSpec>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "name": EBISU_UTILS.toJson(_name),
    "dependencies": EBISU_UTILS.toJson(dependencies),
    };
  }
}

/// Defines a dart system (collection of libraries and apps)
class System { 
  final Id _id;
  /// Id for this system
  Id get id => _id;
  
  /// Documentation for this system
  String doc;
  
  /// Path to which code is generated
  String rootPath;
  
  /// Apps in the system
  List<App> apps = [];
  
  /// Libraries in the system
  List<Library> libraries = [];
  
  /// Information for the pubspec
  PubSpec pubSpec;
  
// custom <class System>


  /// Create system from the id
  System(Id id) : _id = id, pubSpec = new PubSpec(id) {}

  /// Finalize must be called before generate
  void finalize() {
    libraries.forEach((l) => l.parent = this);
    apps.forEach((a) => a.parent = this);
    pubSpec._parent = this;
  }

  /// Generate the code
  void generate() {
    apps.forEach((app) => app.generate());
    libraries.forEach((lib) => lib.generate());
    print(META.pubspec(pubSpec));
  }

// end <class System>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "rootPath": EBISU_UTILS.toJson(rootPath),
    "apps": EBISU_UTILS.toJson(apps),
    "libraries": EBISU_UTILS.toJson(libraries),
    "pubSpec": EBISU_UTILS.toJson(pubSpec),
    };
  }
}

/// Defines a dart application
class App { 
  final Id _id;
  /// Id for this app
  Id get id => _id;
  
  /// Documentation for this app
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this app
  dynamic get parent => _parent;
  
  /// If true a custom section will be included for app
  bool includeCustom = true;
  
  /// Classes defined in this app
  List<DClass> classes = [];
  
  /// List of libraries of this app
  List<Library> libraries = [];
  
  /// List of global variables for this library
  List<Variable> variables = [];
  
// custom <class App>

  App(Id id) : _id = id {}

  set parent(p) {
    libraries.forEach((l) => l.parent = this);
    variables.forEach((v) => v.parent = this);
    _parent = p;
  }

  void generate() {
    libraries.forEach((lib) => lib.generate());
  }

// end <class App>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "includeCustom": EBISU_UTILS.toJson(includeCustom),
    "classes": EBISU_UTILS.toJson(classes),
    "libraries": EBISU_UTILS.toJson(libraries),
    "variables": EBISU_UTILS.toJson(variables),
    };
  }
}

/// Defines a dart library - a collection of parts
class Library { 
  final Id _id;
  /// Id for this library
  Id get id => _id;
  
  /// Documentation for this library
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this library
  dynamic get parent => _parent;
  
  /// If true a custom section will be included for library
  bool includeCustom = true;
  
  /// List of imports to be included by this library
  List<String> imports = [];
  
  /// List of parts in this library
  List<Part> parts = [];
  
  /// List of global variables for this library
  List<Variable> variables = [];
  
  String _name;
  /// Name of the library - for use in naming the library file, the 'library' and 'part of' statements
  String get name => _name;
  
// custom <class Library>

  Library(Id id) : _id = id {}

  set parent(p) {
    _name = _id.snake;
    parts.forEach((part) => part.parent = this);
    variables.forEach((v) => v.parent = this);
    _parent = p;
  }

  void generate() {
    String libStubPath = "${_parent.rootPath}/lib/${id.snake}.dart";
    mergeWithFile(META.library(this), libStubPath);
    parts.forEach((part) => part.generate());
  }

  static final _standardImports = new Set.from([
    'async', 'chrome', 'collection', 'core', 'crypto',
    'html', 'indexed_db', 'io', 'isolate', 'json', 'math',
    'mirrors', 'scalarlist', 'svg', 'uri', 'utf', 'web_audio',
    'web_sql'
  ]);

  static final _standardPackageImports = new Set.from([
    'args', 'fixnum', 'intl', 'logging', 'matcher', 'meta',
    'mock', 'scheduled_test', 'serialization',
    'unittest'
  ]);

  static String importStatement(String i) {
    if(_standardImports.contains(i)) {
      return 'import "dart:$i";';
    } else if(_standardPackageImports.contains(i)) {
      return 'import "package:$i";';
    } else {
      return 'import $i;';
    }
  }

  String get rootPath => _parent.rootPath;

// end <class Library>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "includeCustom": EBISU_UTILS.toJson(includeCustom),
    "imports": EBISU_UTILS.toJson(imports),
    "parts": EBISU_UTILS.toJson(parts),
    "variables": EBISU_UTILS.toJson(variables),
    "name": EBISU_UTILS.toJson(_name),
    };
  }
}

/// Defines a dart part - as in 'part of' source file
class Part { 
  final Id _id;
  /// Id for this part
  Id get id => _id;
  
  /// Documentation for this part
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this part
  dynamic get parent => _parent;
  
  /// If true a custom section will be included for app
  bool includeCustom = true;
  
  /// Classes defined in this part of the library
  List<DClass> classes = [];
  
  /// Enums defined in this part of the library
  List<Enum> enums = [];
  
  String _name;
  /// Name of the part - for use in naming the part file
  String get name => _name;
  
// custom <class Part>

  Part(Id id) : _id = id {}

  set parent(p) {
    _name = _id.snake;
    classes.forEach((dc) => dc.parent = this);
    enums.forEach((e) => e.parent = this);
    _parent = p;
  }

  void generate() {
    Library lib = _parent;
    String partName = _id.snake;
    String partStubPath = "${_parent.rootPath}/lib/src/${lib.name}/${partName}.dart";
    mergeWithFile(META.part(this), partStubPath);
  }

// end <class Part>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "includeCustom": EBISU_UTILS.toJson(includeCustom),
    "classes": EBISU_UTILS.toJson(classes),
    "enums": EBISU_UTILS.toJson(enums),
    "name": EBISU_UTILS.toJson(_name),
    };
  }
}

/// Mixin for extending classes
class Mixin { 
  Mixin(
    this.source,
    this.interfaces
  ) {
  }
  
  /// Source of the mixin - as in the "Source" in "class Foo extends Source with Mixin"
  String source;
  
  /// List of interaces being mixed in
  List<String> interfaces;
  
// custom <class Mixin>
// end <class Mixin>

  Map toJson() { 
    return { 
    "source": EBISU_UTILS.toJson(source),
    "interfaces": EBISU_UTILS.toJson(interfaces),
    };
  }
}

/// Metadata associated with a Dart class
class DClass { 
  final Id _id;
  /// Id for this Dart class
  Id get id => _id;
  
  /// Documentation for this Dart class
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this Dart class
  dynamic get parent => _parent;
  
  /// True if Dart class is public.
  /// Code generation support will prefix private variables appropriately
  bool isPublic = true;
  
  /// Any mixin declaration for the class
  Mixin mixin;
  
  /// Any extends (NOTE extend not extends) declaration for the class - conflicts with mixin
  String extend;
  
  /// If true a custom section will be included for Dart class
  bool includeCustom = true;
  
  /// List of members of this class
  List<Member> members = [];
  
  Map<String,Ctor> _ctors = {};
  /// List of ctors of this class
  Map<String,Ctor> get ctors => _ctors;
  
  /// If true, generate toJson/fromJson on all members that are not jsonTransient
  bool jsonSupport = false;
  
  String _name;
  /// Name of the class - sans any access prefix (i.e. no '_')
  String get name => _name;
  
  String _className;
  /// Name of the class, including access prefix
  String get className => _className;
  
// custom <class DClass>

  DClass(Id id) : _id = id {}

  set parent(p) {
    _name = id.capCamel;
    _className = isPublic? _name : "_$_name";
    // Iterate on all members and create the appropriate ctors
    members.forEach((m) {
      m.parent = this;
      m.ctors.forEach((ctorName) {
        Ctor ctor = _ctors.putIfAbsent(ctorName, () => new Ctor())
          ..name = ctorName
          ..className = _name
          ..members.add(m);
      });
      m.ctorsOpt.forEach((ctorName) {
        Ctor ctor = _ctors.putIfAbsent(ctorName, () => new Ctor())
          ..name = ctorName
          ..className = _name
          ..optMembers.add(m);
      });
      m.ctorsNamed.forEach((ctorName) {
        Ctor ctor = _ctors.putIfAbsent(ctorName, () => new Ctor())
          ..name = ctorName
          ..className = _name
          ..namedMembers.add(m);
      });
    });
    _parent = p;
  }

  String define() {
    return META.dclass(this);
  }

  dynamic noSuchMethod(InvocationMirror msg) {
    return null;
  }

// end <class DClass>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "isPublic": EBISU_UTILS.toJson(isPublic),
    "mixin": EBISU_UTILS.toJson(mixin),
    "extend": EBISU_UTILS.toJson(extend),
    "includeCustom": EBISU_UTILS.toJson(includeCustom),
    "members": EBISU_UTILS.toJson(members),
    "ctors": EBISU_UTILS.toJson(_ctors),
    "jsonSupport": EBISU_UTILS.toJson(jsonSupport),
    "name": EBISU_UTILS.toJson(_name),
    "className": EBISU_UTILS.toJson(_className),
    };
  }
}

/// Metadata associated with a constructor
class Ctor { 
  /// Name of the class of this ctor.
  String className;
  
  /// Name of the ctor. If 'default' generated as name of class, otherwise as CLASS.NAME()
  String name;
  
  /// List of members initialized in this ctor
  List<Member> members = [];
  
  /// List of optional members initialized in this ctor (i.e. those in [])
  List<Member> optMembers = [];
  
  /// List of optional members initialized in this ctor (i.e. those in {})
  List<Member> namedMembers = [];
  
// custom <class Ctor>

  String get qualifiedName => (name == 'default' || name == '')? 
    className : '$className.name';

  String get ctorText {
    List<String> result = [];
    if(members.length > 0) {
      List<String> required = [];
      members.forEach((m) => required.add('  this.${m.varName}'));
      result.add("${required.join(',\n')}");
    }
    if(optMembers.length > 0) {
      List<String> optional = [];
      optMembers.forEach((m) => optional.add('    this.${m.varName}'));
      result.add("  [\n${optional.join(',\n')}\n  ]");
    }
    if(namedMembers.length > 0) {
      List<String> named = [];
      namedMembers.forEach((m) => named.add('    this.${m.varName}'));
      result.add("  {\n${named.join(',\n')}\n  }");
    }
    String guts = result.join(',\n');
    return '''
${qualifiedName}(
${guts}
) {
}
''';
  }

// end <class Ctor>

  Map toJson() { 
    return { 
    "className": EBISU_UTILS.toJson(className),
    "name": EBISU_UTILS.toJson(name),
    "members": EBISU_UTILS.toJson(members),
    "optMembers": EBISU_UTILS.toJson(optMembers),
    "namedMembers": EBISU_UTILS.toJson(namedMembers),
    };
  }
}

/// Metadata associated with a member of a Dart class
class Member { 
  final Id _id;
  /// Id for this class member
  Id get id => _id;
  
  /// Documentation for this class member
  String doc;
  
  dynamic _parent;
  /// Reference to parent of this class member
  dynamic get parent => _parent;
  
  /// Type of the member
  String type = "String";
  
  /// Access level supported for this member
  Access access = Access.RW;
  
  /// If provided the member will be initialized to this text in place of declaration of class
  String classInit;
  
  /// If provided the member will be initialized to this text in generated ctor initializers
  String ctorInit;
  
  /// List of ctor names to include this member in
  List<String> ctors = [];
  
  /// List of ctor names to include this member in as optional parameter
  List<String> ctorsOpt = [];
  
  /// List of ctor names to include this member in as named optional parameter
  List<String> ctorsNamed = [];
  
  /// True if the member is final
  bool isFinal = false;
  
  /// True if the member is const
  bool isConst = false;
  
  /// True if the member is static
  bool isStatic = false;
  
  /// True if the member should not be serialized if the parent class has jsonSupport
  bool jsonTransient = false;
  
  String _name;
  /// Name of variable for the member, excluding access prefix (i.e. no '_')
  String get name => _name;
  
  String _varName;
  /// Name of variable for the member - varies depending on public/private
  String get varName => _varName;
  
// custom <class Member>

  Member(Id id) : _id = id {}

  bool get isPublic => access == Access.RW;

  set parent(p) {
    _name = id.camel;
    _varName = isPublic? _name : "_$_name";
    _parent = p;
  }

  String define() {
    return META.member(this);
  }

// end <class Member>

  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "doc": EBISU_UTILS.toJson(doc),
    "type": EBISU_UTILS.toJson(type),
    "access": EBISU_UTILS.toJson(access),
    "classInit": EBISU_UTILS.toJson(classInit),
    "ctorInit": EBISU_UTILS.toJson(ctorInit),
    "ctors": EBISU_UTILS.toJson(ctors),
    "ctorsOpt": EBISU_UTILS.toJson(ctorsOpt),
    "ctorsNamed": EBISU_UTILS.toJson(ctorsNamed),
    "isFinal": EBISU_UTILS.toJson(isFinal),
    "isConst": EBISU_UTILS.toJson(isConst),
    "isStatic": EBISU_UTILS.toJson(isStatic),
    "jsonTransient": EBISU_UTILS.toJson(jsonTransient),
    "name": EBISU_UTILS.toJson(_name),
    "varName": EBISU_UTILS.toJson(_varName),
    };
  }
}
// custom <part meta>

Id id(String _id) => new Id(_id);
Enum enum(String _id) => new Enum(id(_id));
System system(String _id) => new System(id(_id));
App app(String _id) => new App(id(_id));
Library library(String _id) => new Library(id(_id));
Variable variable(String _id) => new Variable(id(_id));
Part part(String _id) => new Part(id(_id));
DClass dclass(String _id) => new DClass(id(_id));
Member member(String _id) => new Member(id(_id));
PubSpec pubspec(String _id)=> new PubSpec(id(_id));
PubDependency pubdep(String name)=> new PubDependency(name);

// end <part meta>
