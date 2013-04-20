part of dart_meta;

String library([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 if(_.doc != null) { 
  _buf.add('''
${docComment(_.doc)}
''');
 } 
  _buf.add('''
library ${_.name};

''');
 for(var i in _.imports) { 
  _buf.add('''
${Library.importStatement(i)}
''');
 } 
 for(var part in _.parts) { 
  _buf.add('''
part "src/${_.name}/${part.name}.dart";
''');
 } 
  _buf.add('''

''');
 for(var e in _.enums) { 
  _buf.add('''
${chomp(e.define())}

''');
 } 
 for(var c in _.classes) { 
  _buf.add('''
${chomp(c.define())}

''');
 } 
 for(var v in _.variables) { 
  _buf.add('''
${v.define()}
''');
 } 
  _buf.add('''
main() {
  print("Main for library ${_.id.snake}");
${indentBlock(customBlock("main ${_.name}"))}
}
''');
 if(_.includeCustom) { 
  _buf.add('''
${customBlock("library ${_.name}")}
''');
 } 
  return _buf.join();
}