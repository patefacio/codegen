part of dlang_meta;

String decls([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


 for(var mixin in _.mixins) { 
  _buf.add('''
${mixin.decl};
''');
 } 
 for(var alias in _.aliases) { 
  _buf.add('''
${alias.decl};
''');
 } 
 for(var enum in _.enums) { 
  _buf.add('''
${chomp(enum.define())}
''');
 } 
 for(var constant in _.constants) { 
  _buf.add('''
${chomp(constant.define())}
''');
 } 
 for(var struct in _.structs) { 
  _buf.add('''
${chomp(struct.define())}
''');
 } 
 for(var union in _.unions) { 
  _buf.add('''
${chomp(union.define())}
''');
 } 
 for(var template in _.templates) { 
  _buf.add('''
template(${templates.id})
''');
 } 
 for(var codeBlock in _.codeBlocks) { 
  _buf.add('''
codeblock(${codeblock.text})
''');
 } 
 for(var member in _.members) { 
  _buf.add('''
${member.decl};
''');
 } 
  return _buf.join();
}