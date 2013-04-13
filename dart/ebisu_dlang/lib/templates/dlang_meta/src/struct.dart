part of dlang_meta;

String struct([dynamic _]) {
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
struct ${_.name} { 
${chomp(indentBlock(_.decls()))}
}
''');
  return _buf.join();
}