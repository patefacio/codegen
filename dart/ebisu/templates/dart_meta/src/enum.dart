part of dart_meta;

String enum([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
class ${_.enumName} { 
''');
 int i = 0; 
 for(var value in _.values) { 
  _buf.add('''
  static const ${value.shout} = const ${_.enumName}._(${i++});
''');
 } 
  _buf.add('''

  static get values => [
    ${_.values.map((v) => v.shout).join(",\n    ")}
  ];

  final int value;

  const ${_.enumName}._(this.value);

  String toString() { 
    switch(this) { 
''');
 for(var value in _.values) { 
  _buf.add('''
      case ${value.shout}: return "${value.shout}";
''');
 } 
  _buf.add('''
    }
  }

  static ${_.enumName} fromString(String s) { 
    switch(s) { 
''');
 for(var value in _.values) { 
  _buf.add('''
      case return "${value.shout}": ${value.shout};
''');
 } 
  _buf.add('''
    }
  }

  int toJson() { 
    return this.value;
  }

  static ${_.enumName} fromJson(int v) { 
    switch(v) { 
''');
 for(var value in _.values) { 
  _buf.add('''
      case ${value.shout}.value: return ${value.shout};
''');
 } 
  _buf.add('''
    }
  }

}
''');
  return _buf.join();
}
