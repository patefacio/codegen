part of dart_meta;

String enum([Map _map]) {
  if(!?_map) {
    _map = new Map();
  }
  Context _ = new Context(_map);
  List<String> _buf = new List<String>();


  _buf.add('''
enum ${_.name} { 
''');
 for(var member in _.members) { 
   if member.descr {            
  _buf.add('''
// ${member.descr}
''');
 } 
  _buf.add('''
${member.type} ${member.name}
''');
 } 
  _buf.add('''
}
''');
  print(_buf.join());
}
