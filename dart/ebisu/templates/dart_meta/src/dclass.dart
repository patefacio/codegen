part of dart_meta;

String dclass([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
class ${_.id} { 
''');
 for(var member in _.members) { 
  _buf.add('''
${indentBlock(member.define())}
''');
 } 
  _buf.add('''
}


''');
  return _buf.join();
}
