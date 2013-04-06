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
${_.isFinal? 'final ':''}${_.type} ${_.varName};
''');
 } else { 
  _buf.add('''
${_.isFinal? 'final ':''}${_.type} ${_.varName} = ${_.classInit};
''');
 } 
 if(!_.isPublic) { 
   if(_.access == Access.RO || _.access == Access.RW) { 
  _buf.add('''
${_.type} get ${_.name} => ${_.varName};
''');
   } 
   if(_.access == Access.RW) { 
  _buf.add('''
set ${_.name}(${_.type} ${_.name}_) => ${_.varName} = ${_.name}_;
''');
   } 
 } 
  return _buf.join();
}
