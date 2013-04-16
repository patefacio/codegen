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
  
  Map<String, dynamic> _itemMap = {};
  /// Map of items indexed by xmi:id
  Map<String, dynamic> get itemMap => _itemMap;
  
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
      _itemMap[target.id] = target;
    }
  }

  addProperties(dynamic target, Map map) {
    filterOwnedAttributesBy(map, "uml:Property").forEach((attribute) {
      UProperty property = new UProperty(attribute['xmi:id'])..name = attribute['name'];
      addComment(property, attribute);
      property.type = attribute['type'];
      property.visibility = attribute['visibility'];
      property.aggregation = attribute['aggregation'];
      target.properties.add(property);
      _itemMap[property.id] = property;
    });
  }

  addTemplBindings(dynamic target, Map map) {
    if(map.containsKey("templateBinding")) {
      Map bindingEntry = map['templateBinding'];
      UTemplBinding binding = new UTemplBinding(bindingEntry['xmi:id'])
        ..signatureId = bindingEntry['signature'];
      target.templBinding = binding;
      List substs = asList(bindingEntry["parameterSubstitution"]).where((e) => 
            xmiType(e) == "uml:TemplateParameterSubstitution").toList();
      substs.forEach((subst) {
        UTemplParmSubst ts = new UTemplParmSubst(subst['xmi:id'])
          ..formalId = subst['formal']
          ..actualId = subst['actual'];
        binding.templParmSubsts.add(ts);
        _itemMap[ts.id] = ts;
      });      
      _itemMap[binding.id] = binding;
    }
  }

  addTemplSig(dynamic target, Map map) {
    if(map.containsKey("ownedTemplateSignature")) {
      Map sigEntry = map['ownedTemplateSignature'];
      UTemplSig sig = new UTemplSig(sigEntry['xmi:id']);
      target.templSig = sig;

      if(sigEntry.containsKey("ownedParameter")) {
        List parms = asList(sigEntry["ownedParameter"]).where((e) => 
            xmiType(e) == "uml:ClassifierTemplateParameter").toList();
        parms.forEach((parmEntry) {
          UClassifierTemplParm tp = new UClassifierTemplParm(parmEntry['xmi:id'])
            ..name = parmEntry['ownedParameteredElement']['name']
            ..type = parmEntry['ownedParameteredElement']['xmi:type']
            ..allowSubstitutable = parmEntry['allowSubstitutable'] == 'true';
          sig.parms.add(tp);
          _itemMap[tp.id] = tp;
        });
      }

      _itemMap[sig.id] = sig;
    }
  }

  addPackages(dynamic target, Map map) {
    filterPackagedElementsBy(map, "uml:Package").forEach((element) {
      String pkgName = element['name'];
      UPackage pkg = new UPackage(element['xmi:id'])
        ..parentPackageId = target.id
        ..path = (new List.from(target.path)..add(pkgName))
        ..name = pkgName;
      addComment(pkg, element);
      target.packages.add(pkg);
      addPackages(pkg, element);
      _itemMap[pkg.id] = pkg;
    });
    filterPackagedElementsBy(map, "uml:Class").forEach((element) {
      UClass klass = new UClass(element['xmi:id'])..name = element['name'];
      addComment(klass, element);
      addProperties(klass, element);
      addTemplBindings(klass, element);
      addTemplSig(klass, element);
      target.classes.add(klass);
      _itemMap[klass.id] = klass;
    });
    filterPackagedElementsBy(map, "uml:Enumeration").forEach((element) {
      UEnumeration enum_ = new UEnumeration(element['xmi:id'])..name = element['name'];
      addComment(enum_, element);
      addProperties(enum_, element);
      target.enums.add(enum_);
      _itemMap[enum_.id] = enum_;
    });
  }

  UPackage buildRootPackage(Map map) {
    UPackage pkg = new UPackage(map["xmi:id"])..name = map["name"];
    addComment(pkg, map);
    addPackages(pkg, map);
    _itemMap[pkg.id] = pkg;
    return pkg;
  }

  UModel buildModel() {
    String contents = new File(srcJsonFile).readAsStringSync();
    Map contentMap = JSON.parse(contents);
    _modelData = contentMap["XMI"]["Model"];

    UModel model = new UModel();
    model.root = buildRootPackage(_modelData);
    model._itemMap = itemMap;
    print(prettyJsonMap(model.toJson()));
    print(model._itemMap);
    return model;
  }

// end <class JsonUModelBuilder>


  Map toJson() { 
    return { 
    "srcJsonFile": EBISU_UTILS.toJson(srcJsonFile),
    "modelData": EBISU_UTILS.toJson(_modelData),
    "itemMap": EBISU_UTILS.toJson(_itemMap),
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
  
  UTemplBinding templBinding;
  
  UTemplSig templSig;
  
// custom <class UClass>
// end <class UClass>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    "comment": EBISU_UTILS.toJson(comment),
    "properties": EBISU_UTILS.toJson(properties),
    "templBinding": EBISU_UTILS.toJson(templBinding),
    "templSig": EBISU_UTILS.toJson(templSig),
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
  
  String parentPackageId;
  
  /// Path to package as list of strings
  List<String> path = [];
  
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
    "parentPackageId": EBISU_UTILS.toJson(parentPackageId),
    "path": EBISU_UTILS.toJson(path),
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
  
  /// Id for the type of this property
  String type;
  
  String visibility;
  
  String aggregation;
  
// custom <class UProperty>
// end <class UProperty>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "name": EBISU_UTILS.toJson(name),
    "comment": EBISU_UTILS.toJson(comment),
    "type": EBISU_UTILS.toJson(type),
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
  UTemplBinding(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml template binding
  String get id => _id;
  
  /// Id of the signature of this template binding
  String signatureId;
  
  /// Parameter substitutions for this binding
  List<UTemplParmSubst> templParmSubsts = [];
  
// custom <class UTemplBinding>
// end <class UTemplBinding>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "signatureId": EBISU_UTILS.toJson(signatureId),
    "templParmSubsts": EBISU_UTILS.toJson(templParmSubsts),
    };
  }
}

class UTemplParmSubst { 
  UTemplParmSubst(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml template parameter substitution
  String get id => _id;
  
  /// Id of the formal type being substituted
  String formalId;
  
  /// Id of the actual type being substituted
  String actualId;
  
// custom <class UTemplParmSubst>
// end <class UTemplParmSubst>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "formalId": EBISU_UTILS.toJson(formalId),
    "actualId": EBISU_UTILS.toJson(actualId),
    };
  }
}

class UClassifierTemplParm { 
  UClassifierTemplParm(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml classifier template parameter
  String get id => _id;
  
  bool allowSubstitutable = false;
  
  String name;
  
  String type;
  
// custom <class UClassifierTemplParm>
// end <class UClassifierTemplParm>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "allowSubstitutable": EBISU_UTILS.toJson(allowSubstitutable),
    "name": EBISU_UTILS.toJson(name),
    "type": EBISU_UTILS.toJson(type),
    };
  }
}

class UTemplSig { 
  UTemplSig(
    this._id
  ) {
  }
  
  final String _id;
  /// Id for this uml template signature
  String get id => _id;
  
  List<UClassifierTemplParm> parms = [];
  
// custom <class UTemplSig>
// end <class UTemplSig>


  Map toJson() { 
    return { 
    "id": EBISU_UTILS.toJson(_id),
    "parms": EBISU_UTILS.toJson(parms),
    };
  }
}
// custom <part model>
// end <part model>

