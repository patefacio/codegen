part of dart_meta;

String script([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
#!/usr/bin/env dart
''');
 if(_.doc != null) { 
  _buf.add('''
${docComment(_.doc)}
''');
 } 
  _buf.add('''

''');
 for(var i in _.imports) { 
  _buf.add('''
${Library.importStatement(i)}
''');
 } 
  _buf.add('''

ArgResults _parseArgs() { 
  var parser = new ArgParser();
''');
 for(var scriptArg in _.args) { 
  _buf.add('''
    print("${scriptArg.id}");
''');
 } 
  _buf.add('''
}

main() { 
  ArgResults argResults = _parseArgs();
${indentBlock(customBlock("${_.id} main"))}
}

${customBlock("${_.id} global")}

''');
  return _buf.join();
}