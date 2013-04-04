part of dart_meta;

String enum([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
enum ${_.id} { 
''');
 for(var value in _.values) { 
  _buf.add('''
${value.id}
''');
 } 
  _buf.add('''
}
''');
  return _buf.join();
}
