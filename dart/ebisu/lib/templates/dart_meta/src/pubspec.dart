part of dart_meta;

String pubspec([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
name: ${_.name}
description: ${_.doc}
dependencies:
''');
 for(PubDependency pbdep in _.dependencies) { 
  _buf.add('''
  name: ${pbdep.name} ${pbdep.version}
''');
 } 
  _buf.add('''
// Are comments allowed here in pubspec
''');
  return _buf.join();
}
