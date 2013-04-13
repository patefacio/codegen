part of dlang_meta;

String constant([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 String staticTag = _.isStatic? 'static ' : ''; 
 if(null != _.init) { 
   if(_.hasStaticThis) { 
  _buf.add('''
${staticTag}const(${_.type}) ${_.name};
static this() {
  cast(${_.type})${_.name} = ${indentBlock(_.init).trim()};
}
''');
   } else { 
  _buf.add('''
${staticTag}const(${_.type}) ${_.name} = ${chomp(_.init)};
''');
   } 
 } else { 
  _buf.add('''
${staticTag}const(${_.type}) ${_.name};
''');
 } 
  return _buf.join();
}