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

  Variable(Id id) :
    _id = id,
    type = 'var',
    isFinal = false,
    isConst = false,
    isStatic = false 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "doc" : doc,
       "type" : type,
       "init" : init,
       "isFinal" : isFinal,
       "isConst" : isConst,
       "isStatic" : isStatic
    };
  }

  static Variable fromJson(String json) {
    Map jsonMap = parse(json);
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
    type = jsonMap["type"];
    init = jsonMap["init"];
    isFinal = jsonMap["isFinal"];
    isConst = jsonMap["isConst"];
    isStatic = jsonMap["isStatic"];
  }


// custom <variable impl>
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

  /**
     The id's of the enums - Id being used to enforce consistency
  */
  List<Id> values;

  Enum(Id id) :
    _id = id,
    values = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "values" : values
    };
  }

  static Enum fromJson(String json) {
    Map jsonMap = parse(json);
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
    // values is good
  }


// custom <enum impl>
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
     The classes composing this part
  */
  List<DClass> classes;

  /**
     The enums associated with this part
  */
  List<Enum> enums;

  Part(Id id) :
    _id = id,
    classes = [],
    enums = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "classes" : classes,
       "enums" : enums
    };
  }

  static Part fromJson(String json) {
    Map jsonMap = parse(json);
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

  /**
     Documentation for the library
  */
  String doc;

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
    parts = [],
    variables = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "doc" : doc,
       "parts" : parts,
       "variables" : variables
    };
  }

  static Library fromJson(String json) {
    Map jsonMap = parse(json);
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
    doc = jsonMap["doc"];
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
    Map jsonMap = parse(json);
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
    Map jsonMap = parse(json);
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
     If true the class is public and named appropriately
  */
  bool isPublic;

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
    isPublic = true,
    members = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "isPublic" : isPublic,
       "doc" : doc,
       "members" : members
    };
  }

  static DClass fromJson(String json) {
    Map jsonMap = parse(json);
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
    isPublic = jsonMap["isPublic"];
    doc = jsonMap["doc"];
    members = new List<Member>();
    jsonMap["members"].forEach((v) { 
      members.add(Member.fromJsonMap(v));
    });
  }


// custom <d_class impl>
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
  bool isPublic;

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
     Name of variable for the member - varies depending on public/private
  */
  String _varName;

  Member(Id id) :
    _id = id,
    type = "String",
    isPublic = true,
    access = Access.RW,
    ctors = [],
    isFinal = false,
    isStatic = false 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "doc" : doc,
       "type" : type,
       "isPublic" : isPublic,
       "access" : access,
       "classInit" : classInit,
       "ctorInit" : ctorInit,
       "ctors" : ctors,
       "isFinal" : isFinal,
       "isStatic" : isStatic,
       "varName" : _varName
    };
  }

  static Member fromJson(String json) {
    Map jsonMap = parse(json);
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
    isPublic = jsonMap["isPublic"];
    access = Access.fromJson(jsonMap["access"]);
    classInit = jsonMap["classInit"];
    ctorInit = jsonMap["ctorInit"];
    // ctors is good
    isFinal = jsonMap["isFinal"];
    isStatic = jsonMap["isStatic"];
    _varName = jsonMap["varName"];
  }


// custom <member impl>
// end <member impl>
}


// custom <meta top level>

Id id(String _id) => new Id(_id);
Enum enum(String _id) => new Enum(id(_id));
System system(String _id) => new System(id(_id));
App app(String _id) => new App(id(_id));
Library library(String _id) => new Library(id(_id));
Variable variable(String _id) => new Variable(id(_id));
Part part(String _id) => new Part(id(_id));
DClass dclass(String _id) => new DClass(id(_id));
Member member(String _id) => new Member(id(_id));

// end <meta top level>

