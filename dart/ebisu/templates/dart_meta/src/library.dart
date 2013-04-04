part of dart_meta;

String library([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
library ${_.name};

''');
 for(var i in _.imports) { 
 } 
 for(var part in _.parts) { 
  _buf.add('''
part "src/${_.name}/${part.name}.dart";
''');
 } 
  _buf.add('''

''');
 for(var v in _.variables) { 
  _buf.add('''
${v.define()}
''');
 } 
  _buf.add('''
main() {
  print("Main for library ${_.id.snake}");
}
''');
 if(_.includeCustom) { 
  _buf.add('''
${customBlock("library ${_.name}")}
''');
 } 
  return _buf.join();
}
