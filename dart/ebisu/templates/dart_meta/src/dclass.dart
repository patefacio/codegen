part of dart_meta;

String dclass([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 if(_.doc != null) { 
  _buf.add('''
${blockComment(_.doc)}
''');
 } 
  _buf.add('''
class ${_.className} { 
''');
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
