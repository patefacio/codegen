part of dlang_meta;

String module([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
module ${_.name};

''');
 for(String i in _.publicImports) { 
  _buf.add('''
public ${_.importStatement(i)};
''');
 } 
 for(String i in _.imports) { 
  _buf.add('''
${_.importStatement(i)};
''');
 } 
 for(String i in _.debugImports) { 
  _buf.add('''
debug ${_.importStatement(i)};
''');
 } 
  _buf.add('''
${_.contents}

''');
  return _buf.join();
}