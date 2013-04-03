part of dart_meta;

String dclass([Map _map]) {
  if(!?_map) {
    _map = new Map();
  }
  Context _ = new Context(_map);
  List<String> _buf = new List<String>();


  _buf.add('''
class ${_.name} { 
''');
 for(var member in asContexts(_.members)) { 
  _buf.add('''
${member['descr']==null ? 'foo' : 'bar'}
  // Support for ${member['name']};
  ${member.type} ${member.name};
''');
 } 
  _buf.add('''
}
// done it

''');
  print(_buf.join());
}
