/** ebisu */
part of ebisu;

class Context { 
  Map _data;

  Context(Map data) :
    _data = data 
  { 
  }

// custom <context impl>

  dynamic noSuchMethod(InvocationMirror msg) {
    String memberName = msg.memberName;
    if(! _data.containsKey(memberName)) {
      throw new ArgumentError("Context could not find key '$memberName' in data");
    }
    return _data[memberName];
  }

  dynamic operator[](dynamic index) {
    return _data[index];
  }

// end <context impl>
}


// custom <ebisu top level>

Iterable asContexts(Iterable items) {
  return items.toList().map((i) => new Context(i));
}

String blockComment(String text, [String indent = '  ']) {
  String guts = text.split('\n').join("\n$indent");
  return "/**\n$indent$guts\n*/";
}

String indentBlock(String block, [String indent = '  ']) {
  return '$indent${block.split("\n").join("\n$indent")}';
}


// end <ebisu top level>

