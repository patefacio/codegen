library ebisu_utils;

import "dart:math";

main() {
  print("Main for library ebisu_utils");
  // custom <main ebisu_utils>
  // end <main ebisu_utils>
  
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

final _sourceChars = r'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*+;,.';
final _randGenerator = new Random(0);

String randString([Random generator, int maxLen = 10 ]) {
  if(!?generator) generator = _randGenerator;
  int numChars = generator.nextInt(maxLen)+1;
  var chars = new List<int>(numChars);
  for(var i=0; i<numChars; i++) {
    chars[i] = _sourceChars.codeUnitAt(generator.nextInt(_sourceChars.length));
  }
  return new String.fromCharCodes(chars);
}

dynamic randJsonMap([Random generator, dynamic valueBuilder, int maxLen = 10]) {
  Map result = {};
  if(!?generator) generator = _randGenerator;
  int numEntries = generator.nextInt(maxLen)+1;
  for(var i=0; i<numEntries; i++) {
    result[randString(generator)] = valueBuilder();
  }
  return result;
}

dynamic randJson(Random generator, var obj, [ final dynamic type ]) {
  if(obj is List) {
    List result = [];
    new List(generator.nextInt(6)+1).forEach((i) {
      result.add(type());
    });
    return result;
  } else if(obj is Map) {
    Map result = {};
    new List(generator.nextInt(4)+1).forEach((i) {
      result[generator.nextInt(1<<31).toString()] = type;
    });
    return result;
  } else if(obj is Function) {
    return obj();
  } else {
    switch(obj) {
      case num: return generator.nextInt(1<<31);
      case double: return generator.nextInt(1<<31) * generator.nextDouble();
      case int: return generator.nextInt(1<<31);
      case String: return generator.nextInt(1<<31).toString();
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

