/** meta */
part of edm;

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

  static Access fromString(String s) { 
    switch(s) { 
      case "IA": return IA;
      case "RO": return RO;
      case "RW": return RW;
    }
  }
}

/**
   Defines a variable
*/
class Variable { 

  /**
     Id of the variable
  */
  final Id _id;
  Id get id => _id;

  /**
     Documentation for the variable
  */
  String doc;

  /**
     Name of the variable, without consideration of access - (i.e. no leading '_')
  */
  String _name;
  String get name => _name;

  /**
     Name of the variable
  */
  String _varName;
  String get varName => _varName;
  dynamic _parent;
  dynamic get parent => _parent;

  /**
     The type of the variable
  */
  String type;

  /**
     Initialization code (e.g. 'DateTime(1929, 10, 29)' for <DateTime crashDate = DateTime(1929, 10, 29)>;
  */
  String init;

  /**
     True if the variable is final
  */
  bool isFinal;

  /**
     True if the variable is const
  */
  bool isConst;

  /**
     True if the variable is static
  */
  bool isStatic;

  /**
     If true the variable is public and named appropriately
  */
  bool isPublic;

  Variable(Id id) :
    _id = id,
    type = 'var',
    isFinal = false,
    isConst = false,
    isStatic = false,
    isPublic = true 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "doc" : doc,
       "name" : _name,
       "varName" : _varName,
       "type" : type,
       "init" : init,
       "isFinal" : isFinal,
       "isConst" : isConst,
       "isStatic" : isStatic,
       "isPublic" : isPublic
    };
  }

  static Variable fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    Variable result = new Variable();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static Variable fromJsonMap(Map jsonMap) {
    Variable result = new Variable();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    doc = jsonMap["doc"];
    _name = jsonMap["name"];
    _varName = jsonMap["varName"];
    type = jsonMap["type"];
    init = jsonMap["init"];
    isFinal = jsonMap["isFinal"];
    isConst = jsonMap["isConst"];
    isStatic = jsonMap["isStatic"];
    isPublic = jsonMap["isPublic"];
  }


// custom <variable impl>

  void set parent(p) {
    _name = id.camel;
    _varName = isPublic? _name : "_#{_name}";
    _parent = p;
  }

  String define() {
    return META.variable(this);
  }

// end <variable impl>
}

/**
   Defines an enum - to be generated as a class
*/
class Enum { 

  /**
     Id of the enum
  */
  final Id _id;
  Id get id => _id;
  dynamic _parent;
  dynamic get parent => _parent;

  /**
     If true the enum is public and named appropriately
  */
  bool isPublic;

  /**
     Name of the enum sans access qualifier
  */
  String _name;
  String get name => _name;

  /**
     Name of the enum with access qualifier
  */
  String _enumName;
  String get enumName => _enumName;

  /**
     The id's of the enums - Id being used to enforce consistency
  */
  List<Id> values;

  Enum(Id id) :
    _id = id,
    isPublic = true,
    values = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "isPublic" : isPublic,
       "name" : _name,
       "enumName" : _enumName,
       "values" : values
    };
  }

  static Enum fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    Enum result = new Enum();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static Enum fromJsonMap(Map jsonMap) {
    Enum result = new Enum();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    isPublic = jsonMap["isPublic"];
    _name = jsonMap["name"];
    _enumName = jsonMap["enumName"];
    // values is good
  }


// custom <enum impl>

  set parent(p) {
    _name = _id.capCamel;
    _enumName = isPublic? _name : "_$_name";
    _parent = p;
  }

  String define() {
    return META.enum(this);
  }

// end <enum impl>
}

/**
   Defines a dart part - as in 'part of' source file
*/
class Part { 

  /**
     Id of the part
  */
  final Id _id;
  Id get id => _id;

  /**
     If true include custom block
  */
  bool includeCustom;

  /**
     Name of the part - for use in naming the part file
  */
  String _name;
  String get name => _name;
  dynamic _parent;
  dynamic get parent => _parent;

  /**
     The classes composing this part
  */
  List<DClass> classes;

  /**
     The enums associated with this part
  */
  List<Enum> enums;

  Part(Id id) :
    _id = id,
    includeCustom = true,
    classes = [],
    enums = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "includeCustom" : includeCustom,
       "name" : _name,
       "classes" : classes,
       "enums" : enums
    };
  }

  static Part fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    Part result = new Part();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static Part fromJsonMap(Map jsonMap) {
    Part result = new Part();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    includeCustom = jsonMap["includeCustom"];
    _name = jsonMap["name"];
    classes = new List<DClass>();
    jsonMap["classes"].forEach((v) { 
      classes.add(DClass.fromJsonMap(v));
    });
    enums = new List<Enum>();
    jsonMap["enums"].forEach((v) { 
      enums.add(Enum.fromJsonMap(v));
    });
  }


// custom <part impl>

  set parent(p) {
    _name = _id.snake;
    classes.forEach((dc) => dc.parent = this);
    enums.forEach((e) => e.parent = this);
    _parent = p;
  }

  void generate() {
    Library lib = _parent;
    String partName = _id.snake;
    String partStubPath = "${ROOT_PATH}/lib/src/${lib.name}/${partName}.dart";
    mergeWithFile(META.part(this), partStubPath);
  }

// end <part impl>
}

/**
   Defines a dart library - consisting of multiple parts
*/
class Library { 

  /**
     Id of the library
  */
  final Id _id;
  Id get id => _id;
  dynamic _parent;
  dynamic get parent => _parent;

  /**
     Name of the library - for use in library and part statements
  */
  String _name;
  String get name => _name;

  /**
     If true include custom block
  */
  bool includeCustom;

  /**
     Documentation for the library
  */
  String doc;

  /**
     Any additional imports - include text after the "import " directly
  */
  List<String> imports;

  /**
     The parts composing this library
  */
  List<Part> parts;

  /**
     Global variables for this library
  */
  List<Variable> variables;

  Library(Id id) :
    _id = id,
    includeCustom = true,
    imports = [],
    parts = [],
    variables = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "name" : _name,
       "includeCustom" : includeCustom,
       "doc" : doc,
       "imports" : imports,
       "parts" : parts,
       "variables" : variables
    };
  }

  static Library fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    Library result = new Library();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static Library fromJsonMap(Map jsonMap) {
    Library result = new Library();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    _name = jsonMap["name"];
    includeCustom = jsonMap["includeCustom"];
    doc = jsonMap["doc"];
    // imports is good
    parts = new List<Part>();
    jsonMap["parts"].forEach((v) { 
      parts.add(Part.fromJsonMap(v));
    });
    variables = new List<Variable>();
    jsonMap["variables"].forEach((v) { 
      variables.add(Variable.fromJsonMap(v));
    });
  }


// custom <library impl>

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

  set parent(p) {
    _name = _id.snake;
    parts.forEach((part) => part.parent = this);
    variables.forEach((v) => v.parent = this);
    _parent = p;
  }

  void generate() {
    String libStubPath = "${ROOT_PATH}/lib/${id.snake}.dart";
    mergeWithFile(META.library(this), libStubPath);
    parts.forEach((part) => part.generate());
  }

// end <library impl>
}

/**
   Defines a dart application
*/
class App { 

  /**
     Id of the app
  */
  final Id _id;
  Id get id => _id;
  dynamic _parent;
  dynamic get parent => _parent;

  /**
     Libraries defined by this app
  */
  List<Library> libraries;

  /**
     Any additional imports - include text after the "import " directly
  */
  List<String> _imports;

  /**
     Global variables for this app
  */
  List<Variable> variables;

  App(Id id) :
    _id = id,
    libraries = [],
    _imports = [],
    variables = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "libraries" : libraries,
       "imports" : _imports,
       "variables" : variables
    };
  }

  static App fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    App result = new App();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static App fromJsonMap(Map jsonMap) {
    App result = new App();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    libraries = new List<Library>();
    jsonMap["libraries"].forEach((v) { 
      libraries.add(Library.fromJsonMap(v));
    });
    // imports is good
    variables = new List<Variable>();
    jsonMap["variables"].forEach((v) { 
      variables.add(Variable.fromJsonMap(v));
    });
  }


// custom <app impl>

  set parent(p) {
    libraries.forEach((l) => l.parent = this);
    variables.forEach((v) => v.parent = this);
    _parent = p;
  }

  void generate() {
    libraries.forEach((lib) => lib.generate());
  }

// end <app impl>
}

/**
   Defines a dart system - collection of libs and apps
*/
class System { 

  /**
     Id of the system
  */
  final Id _id;
  Id get id => _id;

  /**
     Libraries defined by this app
  */
  List<Library> libraries;

  /**
     List of applications in the system
  */
  List<App> apps;

  System(
      Id id, { 
        List<App> this.apps
      }) :
    _id = id 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "libraries" : libraries,
       "apps" : apps
    };
  }

  static System fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    System result = new System();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static System fromJsonMap(Map jsonMap) {
    System result = new System();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    libraries = new List<Library>();
    jsonMap["libraries"].forEach((v) { 
      libraries.add(Library.fromJsonMap(v));
    });
    apps = new List<App>();
    jsonMap["apps"].forEach((v) { 
      apps.add(App.fromJsonMap(v));
    });
  }


// custom <system impl>

  void finalize() {
    libraries.forEach((l) => l.parent = this);
    apps.forEach((a) => a.parent = this);
  }

  void generate() {
    apps.forEach((app) => app.generate());
    libraries.forEach((lib) => lib.generate());
  }

// end <system impl>
}

/**
   Meta data associated with a dart class
*/
class DClass { 

  /**
     Id of the class
  */
  final Id _id;
  Id get id => _id;

  /**
     If true include custom block
  */
  bool includeCustom;

  /**
     Name of the class, without access prefix
  */
  String _name;
  String get name => _name;

  /**
     Name of the class with access prefix
  */
  String _className;
  String get className => _className;
  dynamic _parent;
  dynamic get parent => _parent;

  /**
     If true the class is public and named appropriately
  */
  bool isPublic;

  /**
     If true adds to/from json
  */
  bool jsonSupport;

  /**
     Documentation for the class
  */
  String doc;

  /**
     Data members of the class
  */
  List<Member> members;

  DClass(Id id) :
    _id = id,
    includeCustom = true,
    isPublic = true,
    jsonSupport = false,
    members = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "includeCustom" : includeCustom,
       "name" : _name,
       "className" : _className,
       "isPublic" : isPublic,
       "jsonSupport" : jsonSupport,
       "doc" : doc,
       "members" : members
    };
  }

  static DClass fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    DClass result = new DClass();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static DClass fromJsonMap(Map jsonMap) {
    DClass result = new DClass();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    includeCustom = jsonMap["includeCustom"];
    _name = jsonMap["name"];
    _className = jsonMap["className"];
    isPublic = jsonMap["isPublic"];
    jsonSupport = jsonMap["jsonSupport"];
    doc = jsonMap["doc"];
    members = new List<Member>();
    jsonMap["members"].forEach((v) { 
      members.add(Member.fromJsonMap(v));
    });
  }


// custom <d_class impl>

  set parent(p) {
    _name = id.capCamel;
    _className = isPublic? _name : "_$_name";
    members.forEach((m) => m.parent = this);
    _parent = p;
  }

  void generate() {
    members.forEach((m) => m.generate());
  }

  String define() {
    return META.dclass(this);
  }

// end <d_class impl>
}

/**
   Meta data associated with class member
*/
class Member { 

  /**
     Id of the member
  */
  final Id _id;
  Id get id => _id;
  dynamic _parent;
  dynamic get parent => _parent;

  /**
     Documentation for the class
  */
  String doc;

  /**
     Type of the member
  */
  String type;

  /**
     If true the member is public and named appropriately
  */
  Access access;

  /**
     If provided the member will be initialized in place of declaration of class
  */
  String classInit;

  /**
     If provided the member will be initialized in all ctor member initializer lists
  */
  String ctorInit;

  /**
     List of ctors to include this member in
  */
  List<String> ctors;

  /**
     True if the member is final
  */
  bool isFinal;

  /**
     True if the member is static
  */
  bool isStatic;

  /**
     Name of variable - excluding any access prefix
  */
  String _name;
  String get name => _name;

  /**
     Name of variable for the member - varies depending on public/private
  */
  String _varName;
  String get varName => _varName;

  /**
     If true will not be serialized to JSON
  */
  bool jsonTransient;

  Member(Id id) :
    _id = id,
    type = "String",
    access = Access.RW,
    ctors = [],
    isFinal = false,
    isStatic = false,
    jsonTransient = false 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "doc" : doc,
       "type" : type,
       "access" : access,
       "classInit" : classInit,
       "ctorInit" : ctorInit,
       "ctors" : ctors,
       "isFinal" : isFinal,
       "isStatic" : isStatic,
       "name" : _name,
       "varName" : _varName,
       "jsonTransient" : jsonTransient
    };
  }

  static Member fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    Member result = new Member();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static Member fromJsonMap(Map jsonMap) {
    Member result = new Member();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    doc = jsonMap["doc"];
    type = jsonMap["type"];
    access = Access.fromJson(jsonMap["access"]);
    classInit = jsonMap["classInit"];
    ctorInit = jsonMap["ctorInit"];
    // ctors is good
    isFinal = jsonMap["isFinal"];
    isStatic = jsonMap["isStatic"];
    _name = jsonMap["name"];
    _varName = jsonMap["varName"];
    jsonTransient = jsonMap["jsonTransient"];
  }


// custom <member impl>

  bool get isPublic => access == Access.RW;

  set parent(p) {
    _name = id.camel;
    _varName = isPublic? _name : "_$_name";
    _parent = p;
  }

  String define() {
    return META.member(this);
  }

// end <member impl>
}


// custom <meta part top level>

Id id(String _id) => new Id(_id);
Enum enum(String _id) => new Enum(id(_id));
System system(String _id) => new System(id(_id));
App app(String _id) => new App(id(_id));
Library library(String _id) => new Library(id(_id));
Variable variable(String _id) => new Variable(id(_id));
Part part(String _id) => new Part(id(_id));
DClass dclass(String _id) => new DClass(id(_id));
Member member(String _id) => new Member(id(_id));

// end <meta part top level>

