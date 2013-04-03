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
    _id = id 
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
    _id = id 
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
     The parts composing this library
  */
  List<Part> parts;

  Library(Id id) :
    _id = id 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "parts" : parts
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
    parts = new List<Part>();
    jsonMap["parts"].forEach((v) { 
      parts.add(Part.fromJsonMap(v));
    });
  }


// custom <library impl>
// end <library impl>
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
  bool public;

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
    public = true,
    members = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "public" : public,
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
    public = jsonMap["public"];
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
     If true the member is public and named appropriately
  */
  bool public;

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
     Name of variable for the member - varies depending on public/private
  */
  String _varName;

  Member(Id id) :
    _id = id,
    public = true,
    type = "String",
    access = Access.RW,
    ctors = [] 
  { 
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "doc" : doc,
       "public" : public,
       "type" : type,
       "access" : access,
       "classInit" : classInit,
       "ctorInit" : ctorInit,
       "ctors" : ctors,
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
    public = jsonMap["public"];
    type = jsonMap["type"];
    access = Access.fromJson(jsonMap["access"]);
    classInit = jsonMap["classInit"];
    ctorInit = jsonMap["ctorInit"];
    // ctors is good
    _varName = jsonMap["varName"];
  }


// custom <member impl>
// end <member impl>
}


// custom <meta top level>

Id id(String _id) => new Id(_id);
Enum enum(String _id) => new Enum(id(_id));
Library library(String _id) => new Library(id(_id));
Part part(String _id) => new Part(id(_id));
DClass dclass(String _id) => new DClass(id(_id));
Member member(String _id) => new Member(id(_id));

// end <meta top level>

