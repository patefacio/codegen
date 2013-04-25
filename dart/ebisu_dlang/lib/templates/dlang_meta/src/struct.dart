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
struct ${_.templateName} { 
''');
 if(null != _.ctor) { 
  _buf.add('''
${indentBlock(_.ctor.define())}
''');
 } 
  _buf.add('''
${indentBlock(chomp(_.decls()))}
''');
 if(_.unitTest) { 
  _buf.add('''
  static if(1) unittest { 
${indentBlock(chomp(customBlock("unittest ${_.name}")))}
  }
''');
 } 
  _buf.add('''
}
''');
  return _buf.join();
}