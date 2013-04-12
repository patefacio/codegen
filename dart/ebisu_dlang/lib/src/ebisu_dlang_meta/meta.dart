part of ebisu_dlang_meta;

/**
  Access for member variable - ia - inaccessible, ro - read/only, rw read/write
*/
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

/**
  Access in the D sense
*/
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

/**
  Meta data required for D package
*/
class Package { 
  /**
    Id for this D package
  */
  final Id _id;
  Id get id => _id;
  
  /**
    Documentation for this D package
  */
  String doc;
  
  /**
    Reference to parent of this D struct
  */
  dynamic _parent;
  dynamic get parent => _parent;
  
  /**
    List of modules in the package
  */
  List<Module> modules;
  
  /**
    List of packages in the package
  */
  List<Package> packages;
  
// custom <class Package>
// end <class Package>

}

/**
  Meta data required for D module
*/
class Module { 
  /**
    Id for this D package
  */
  final Id _id;
  Id get id => _id;
  
  /**
    Documentation for this D package
  */
  String doc;
  
  /**
    Reference to parent of this D struct
  */
  dynamic _parent;
  dynamic get parent => _parent;
  
  /**
    List of structs owned by the module
  */
  List<Struct> structs;
  
// custom <class Module>
// end <class Module>

}

/**
  Meta data required for D struct
*/
class Struct { 
  /**
    Id for this D struct
  */
  final Id _id;
  Id get id => _id;
  
  /**
    Documentation for this D struct
  */
  String doc;
  
  /**
    Reference to parent of this D struct
  */
  dynamic _parent;
  dynamic get parent => _parent;
  
  /**
    D access for this D struct
  */
  DAccess dAccess;
  
  /**
    The generated name of the struct
  */
  String name;
  
  /**
    List of members of this class
  */
  List<Member> members;
  
// custom <class Struct>
// end <class Struct>

}

/**
  Meta data required for D member
*/
class Member { 
  /**
    Id for this D member
  */
  final Id _id;
  Id get id => _id;
  
  /**
    Documentation for this D member
  */
  String doc;
  
  /**
    Reference to parent of this D member
  */
  dynamic _parent;
  dynamic get parent => _parent;
  
  /**
    D access for this D member
  */
  DAccess dAccess;
  
  /**
    The generated name of the member
  */
  String name;
  
// custom <class Member>
// end <class Member>

}
// custom <part meta>
// end <part meta>

