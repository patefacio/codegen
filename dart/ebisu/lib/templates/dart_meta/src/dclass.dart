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
 if(_.jsonSupport) { 
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
  _buf.add('''
}
''');
  return _buf.join();
}