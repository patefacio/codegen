part of dlang_meta;

String enum([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 if(null != _.doc) { 
  _buf.add('''
${blockComment(_.doc)}
''');
 } 
  _buf.add('''
enum ${_.name} { 
${indentBlock(_.values.map((v) => v.decl).join(',\n'))}
}
''');
  return _buf.join();
}