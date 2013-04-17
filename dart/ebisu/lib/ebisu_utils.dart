library ebisu_utils;

import "dart:math";

main() {
  print("Main for library ebisu_utils");
}
// custom <library ebisu_utils>

bool _toJsonRequired(final object) {
  if (object is num) {
    return false;
  } else if (object is bool) {
    return false;
  } else if (object == null) {
    return false;
  } else if (object is String) {
    return false;
  } else if (object is List) {
    return false;
  } else if (object is Map) {
    return false;
  }

  return true;
}

dynamic toJson(final dynamic obj) {
  return _toJsonRequired(obj) ? obj.toJson() : obj;
}

dynamic randJson(Random generator, var obj, [ final dynamic type ]) {
  print("OBJ is $obj");
  if(obj is List) {
    List result = [];
    new List(generator.nextInt(6)+1).forEach((i) {
      result.add(type());
    });
    return result;
  } else if(obj is Map) {
    Map result = {};
    new List(generator.nextInt(4)+1).forEach((i) {
      result[generator.nextInt().toString()] = type;
    });
    return result;
  } else if(obj is Function) {
    return obj();
  } else {
    switch(obj) {
      case num: return generator.nextInt();
      case double: return generator.nextDouble();
      case int: return generator.nextInt();
      case String: return generator.nextInt().toString();
      case bool: return 0==(nextInt()%2);
      case null: return null;
      default: { 
        return obj.randJson();
      }
    }
  }
}

/*
dynamic fromJson(final dynamic obj) {
  dynamic result;
  if(obj is num || obj is bool || obj is String || obj == null) {
    result = obj;
  } else if(obj is List) {
    result = [];
    obj.forEach((e) => result.add(fromJson(e)));
  } else {
    if(obj is Map) {
      try {
        result = obj.fromJson(obj);
      } catch(e) {
        print("Caught ${e}: trying another fromJson");
        result = {};
        obj.forEach((k,v) => result[k] = fromJson(v));
      }
    } else {
      throw new UnsupportedError("Type ${obj.runtimeType} not supported by fromJson");
    }
  }
  return result;
}
*/

// end <library ebisu_utils>

