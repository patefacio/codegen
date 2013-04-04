part of dart_meta;

String dclass([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


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
  _buf.add('''
}
''');
  return _buf.join();
}
