library ebisu_utils;


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

dynamic toJson(dynamic obj) {
  return _toJsonRequired(obj) ? obj.toJson() : obj;
}

// end <library ebisu_utils>

