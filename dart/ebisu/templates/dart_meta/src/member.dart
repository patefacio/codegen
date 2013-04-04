part of dart_meta;

String member([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 if(_.doc != null) { 
  _buf.add('''
${blockComment(_.doc)}
''');
 } 
 if(_.classInit == null) { 
  _buf.add('''
${_.type} ${_.varName};
''');
 } else { 
  _buf.add('''
${_.type} ${_.varName} = ${_.init};
''');
 } 
  return _buf.join();
}
