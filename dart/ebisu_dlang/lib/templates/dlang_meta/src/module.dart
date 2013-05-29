part of dlang_meta;

String module([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 if(_.doc != null) { 
  _buf.add('''
${blockComment(_.doc)}
''');
 } 
  _buf.add('''
module ${_.qualifiedName};

''');
 for(String i in _.publicImports) { 
  _buf.add('''
public ${D_META.importStatement(i)};
''');
 } 
 for(String i in _.imports) { 
  _buf.add('''
${D_META.importStatement(i)};
''');
 } 
 for(String i in _.debugImports) { 
  _buf.add('''
debug ${D_META.importStatement(i)};
''');
 } 
 if (_.anyImports) { 
  _buf.add('''

''');
 } 
  _buf.add('''
${chomp(_.contents)}
''');
 if(_.unitTest) { 
  _buf.add('''
static if(1) unittest { 
${indentBlock(chomp(customBlock("unittest ${_.name}")))}
}
''');
 } 
  return _buf.join();
}