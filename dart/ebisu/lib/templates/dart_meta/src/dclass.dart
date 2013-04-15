part of dart_meta;

String dclass([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 if(_.doc != null) { 
  _buf.add('''
${docComment(_.doc)}
''');
 } 
 if(null != _.extend) { 
  _buf.add('''
class ${_.className} extends ${_.extend} { 
''');
 } else if(null != _.mixin) { 
  _buf.add('''
class ${_.className} extends ${_.mixin.source} with ${_.mixin.interfaces.join(',')} { 
''');
 } else { 
  _buf.add('''
class ${_.className} { 
''');
 } 
 _.ctors.forEach((ctorName, ctor) { 
  _buf.add('''
${indentBlock(ctor.ctorText)}
''');
 }); 
 for(var member in _.members) { 
  _buf.add('''
${indentBlock(member.define())}
''');
 } 
 if(_.includeCustom) { 
  _buf.add('''
${customBlock("class ${_.name}")}
''');
 } 
 if(_.toJsonSupport) { 
  _buf.add('''

  Map toJson() { 
    return { 
''');
   for(Member member in _.members.where((m) => !m.jsonTransient)) { 
  _buf.add('''
    "${member.name}": EBISU_UTILS.toJson(${member.varName}),
''');
   } 
   if(null != _.extend) { 
  _buf.add('''
    "${_.extend}": super.toJson(),
''');
   } else if(null != _.mixin) { 
  _buf.add('''
    // TODO: "${_.className}": super.toJson(),
''');
   } 
  _buf.add('''
    };
  }
''');
   } 
 if(_.jsonSupport) { 
  _buf.add('''

  static ${_.name} fromJson(String json) {
    Map jsonMap = JSON.parse(json);
    ${_.name} result = new ${_.name}._json();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static ${_.name} fromJsonMap(Map jsonMap) {
    ${_.name} result = new ${_.name}._json();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
''');
   for(Member m in _.members.where((m) => !m.jsonTransient)) { 
     if(_.isClassJsonable(m.type)) { 
  _buf.add('''
    ${m.varName} = EBISU_UTILS.fromJsonMap(jsonMap["${m.name}"]);
''');
     } else if(isMapType(m.type)) { 
       String valType = jsonMapValueType(m.type);  
       if(valType != null) { 
  _buf.add('''
    // ${m.name} map of <String, ${valType}>
    jsonMap["${m.name}"].forEach((k,v) { 
       ${m.varName}[k] = ${valType}.fromJsonMap(v);
    });
''');
       } 
     } else if(isListType(m.type)) { 
       String valType = jsonListValueType(m.type);  
       if(valType != null) { 
  _buf.add('''
    // ${m.name} list of ${valType}
    ${m.varName} = new ${m.type}();
    jsonMap["${m.name}"].forEach((v) { 
       ${m.varName}.add(${valType}.fromJsonMap(v));
    });
''');
       } 
     } else { 
  _buf.add('''
    ${m.varName} = jsonMap["${m.name}"];
''');
     } 
   } 
  _buf.add('''
  }

''');
 } 
  _buf.add('''
}
''');
  return _buf.join();
}