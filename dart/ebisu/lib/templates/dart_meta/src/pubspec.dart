part of dart_meta;

String pubspec([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
name: ${_.name}
version: ${_.version}
description: >
${indentBlock(_.doc)}
dependencies:
''');
 for(PubDependency pbdep in _.dependencies) { 
   if(pbdep.isHosted) {          
  _buf.add('''
  ${pbdep.name}:
''');
   } else {                      
  _buf.add('''
  ${pbdep.name}: '${pbdep.version}'
''');
   }                             
   if(pbdep.path == null) {      
   } else {                      
     if(pbdep.isHosted) {        
  _buf.add('''
      hosted: 
        name: ${pbdep.name}
        url: ${pbdep.path}
      version: '${pbdep.version}' 
''');
     } else if(pbdep.isGit) {    
       if(pbdep.gitRef != null) {
  _buf.add('''
      git: 
        url: ${pbdep.path}
        ref: ${pbdep.gitRef}
''');
       } else {                  
  _buf.add('''
      git: ${pbdep.path}
''');
       }                         
  _buf.add('''

''');
     } else {                    
  _buf.add('''
      path: ${pbdep.path}
''');
     }                           
   }                             
 } 
  return _buf.join();
}