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
    return _data[msg.memberName];
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

// end <ebisu top level>

