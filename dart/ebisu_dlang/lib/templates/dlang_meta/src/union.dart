part of dlang_meta;

String union([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
union ${_.name} { 
''');
 for(var member in _.members) { 
  _buf.add('''
${indentBlock(member.decl)};
''');
 } 
  _buf.add('''
}
''');
  return _buf.join();
}