part of xmi;

/// Build a UModel from json representation of XMI
class JsonUModelBuilder { 
  JsonUModelBuilder(
    this.srcJsonFile
  ) {
  }
  
  /// Path to json input file
  final String srcJsonFile;
  
  /// Data in Map format from parsed json
  Map _modelData;
  
  /// The current UML entry being built
  dynamic _current;
  
// custom <class JsonUModelBuilder>

  String xmiType(Map map) => map["xmi:type"];

  List asList(dynamic entry) => 
    (entry is Map)? [ entry ] :
    (entry is List)? entry :
    [];

  List filterPackagedElementsBy(Map elements, String type) {
    List results = [];
    if(elements.containsKey("packagedElement")) {
      results = asList(elements['packagedElement']).where((e) => xmiType(e) == type).toList();
    }
    return results;
  }

  List filterOwnedAttributesBy(Map owner, String type) {
    List results = [];
    if(owner.containsKey("ownedAttribute")) {
      results = asList(owner['ownedAttribute']).where((e) => xmiType(e) == type).toList();
    }
    return results;
  }

  addComment(dynamic target, Map map) {
    if(map.containsKey("ownedComment")) {
      Map comment = map["ownedComment"];
      target.comment = new UComment(comment["xmi:id"])..body = comment["body"];
    }
  }

  addProperties(dynamic target, Map map) {
    filterOwnedAttributesBy(map, "uml:Property").forEach((attribute) {
      print("Found property ${attribute['name']}");
      UProperty property = new UProperty(attribute['xmi:id'])..name = attribute['name'];
      addComment(property, attribute);
      property.visibility = attribute['visibility'];
      property.aggregation = attribute['aggregation'];
      target.properties.add(property);
    });
  }

  addPackages(dynamic target, Map map) {
    filterPackagedElementsBy(map, "uml:Package").forEach((element) {
      print("Found package ${element['name']} ${xmiType(element)} => ${element.keys.toList()}");
      UPackage pkg = new UPackage(element['xmi:id'])..name = element['name'];
      addComment(pkg, element);
      target.packages.add(pkg);
      addPackages(pkg, element);
    });
    filterPackagedElementsBy(map, "uml:Class").forEach((element) {
      print("Found class ${element['name']} ${xmiType(element)} => ${element.keys.toList()}");
      UClass klass = new UClass(element['xmi:id'])..name = element['name'];
      addComment(klass, element);
      addProperties(klass, element);
      target.classes.add(klass);
    });
    filterPackagedElementsBy(map, "uml:Enumeration").forEach((element) {
      print("Found enum ${element['name']} ${xmiType(element)} => ${element.keys.toList()}");
      UEnumeration enum_ = new UEnumeration(element['xmi:id'])..name = element['name'];
      addComment(enum_, element);
      addProperties(enum_, element);
      target.enums.add(enum_);
    });
  }

  UPackage buildPackage(Map map) {
    UPackage pkg = new UPackage(map["xmi:id"])..name = map["name"];
    addComment(pkg, map);
    addPackages(pkg, map);
    return pkg;
  }

  UModel buildModel() {

    final Map<String, dynamic> _handlers = {
      "uml:Class" : buildPackage,
      "uml:Package" : buildPackage
    };

    String contents = new File(srcJsonFile).readAsStringSync();
    Map contentMap = JSON.parse(contents);
    _modelData = contentMap["XMI"]["Model"];

    UModel model = new UModel();
    model.root = buildPackage(_modelData);

    print(prettyJsonMap(model.toJson()));
    return model;
  }

// end <class JsonUModelBuilder>


  Map toJson() { 
    return { 
    "srcJsonFile": EBISU_UTILS.toJson(srcJsonFile),
    "modelData": EBISU_UTILS.toJson(_modelData),
    "current": EBISU_UTILS.toJson(_current),
    };
  }
}

class UModel { 
  UPackage root;
  
  Map<String, dynamic> _itemMap = {};
  /// Map of items indexed by xmi:id
  Map<String, dynamic> get itemMap => _itemMap;
  
// custom <class UModel>

// end <class UModel>


  Map toJson() { 
    return { 
    "root": EBISU_UTILS.toJson(root),
    "itemMap": EBISU_UTILS.toJson(_itemMap),
    };
  }
}

class UClass { 
  UClass(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml class
  String get id => _id;
  
  /// Name for this uml class
  String name;
  
  /// Comment (ownedComment) of this uml class
  UComment comment;
  
  /// Properties of this uml class
  List<UProperty> properties = [];
  
// custom <class UClass>
// end <class UClass>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    "comment": EBISU_UTILS.toJson(comment),
    "properties": EBISU_UTILS.toJson(properties),
    };
  }
}

class UClassifierTemplParm { 
// custom <class UClassifierTemplParm>
// end <class UClassifierTemplParm>


  Map toJson() { 
    return { 
    };
  }
}

class UComment { 
  UComment(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml comment
  String get id => _id;
  
  /// Text of the comment
  String body;
  
// custom <class UComment>

  String toString() => body;

// end <class UComment>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "body": EBISU_UTILS.toJson(body),
    };
  }
}

class UDependency { 
  UDependency(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml dependency
  String get id => _id;
  
  String supplier;
  
  String client;
  
// custom <class UDependency>
// end <class UDependency>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "supplier": EBISU_UTILS.toJson(supplier),
    "client": EBISU_UTILS.toJson(client),
    };
  }
}

class UEnumeration { 
  UEnumeration(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml enumeration
  String get id => _id;
  
  /// Name for this uml enumeration
  String name;
  
  /// Properties of this uml enumeration
  List<UProperty> properties = [];
  
  /// Comment (ownedComment) of this uml enumeration
  UComment comment;
  
// custom <class UEnumeration>
// end <class UEnumeration>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    "properties": EBISU_UTILS.toJson(properties),
    "comment": EBISU_UTILS.toJson(comment),
    };
  }
}

class UPackage { 
  UPackage(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml package
  String get id => _id;
  
  /// Name for this uml package
  String name;
  
  /// Comment (ownedComment) of this uml package
  UComment comment;
  
  List<UClass> classes = [];
  
  List<UEnumeration> enums = [];
  
  List<UPackage> packages = [];
  
// custom <class UPackage>
// end <class UPackage>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    "comment": EBISU_UTILS.toJson(comment),
    "classes": EBISU_UTILS.toJson(classes),
    "enums": EBISU_UTILS.toJson(enums),
    "packages": EBISU_UTILS.toJson(packages),
    };
  }
}

class UPrimitiveType { 
  UPrimitiveType(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml primitive type
  String get id => _id;
  
  /// Name for this uml primitive type
  String name;
  
// custom <class UPrimitiveType>
// end <class UPrimitiveType>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    };
  }
}

class UProperty { 
  UProperty(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml property
  String get id => _id;
  
  /// Name for this uml property
  String name;
  
  /// Comment (ownedComment) of this uml property
  UComment comment;
  
  String visibility;
  
  String aggregation;
  
// custom <class UProperty>
// end <class UProperty>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    "comment": EBISU_UTILS.toJson(comment),
    "visibility": EBISU_UTILS.toJson(visibility),
    "aggregation": EBISU_UTILS.toJson(aggregation),
    };
  }
}

class UProfile { 
  UProfile(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml profile
  String get id => _id;
  
  /// Name for this uml profile
  String name;
  
// custom <class UProfile>
// end <class UProfile>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    };
  }
}

class UStereotype { 
  UStereotype(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml stereotype
  String get id => _id;
  
  /// Name for this uml stereotype
  String name;
  
  /// Properties of this uml class
  List<UProperty> properties = [];
  
// custom <class UStereotype>
// end <class UStereotype>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    "properties": EBISU_UTILS.toJson(properties),
    };
  }
}

class UTemplBinding { 
// custom <class UTemplBinding>
// end <class UTemplBinding>


  Map toJson() { 
    return { 
    };
  }
}

class UTemplParmSubst { 
// custom <class UTemplParmSubst>
// end <class UTemplParmSubst>


  Map toJson() { 
    return { 
    };
  }
}

class UTemplSig { 
// custom <class UTemplSig>
// end <class UTemplSig>


  Map toJson() { 
    return { 
    };
  }
}
// custom <part model>
// end <part model>

