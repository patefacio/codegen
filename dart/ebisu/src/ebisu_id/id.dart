/** id */
part of ebisu_id;

/**
   Given an id (all lower case string with words separated by '_') provides 
   various consistent representations.
*/
class Id { 

  /**
     String containing lower case words separated by '_'
  */
  final String _id;
  String get id => _id;

  /**
     Individual words in the id
  */
  final List<String> _words;
  List<String> get words => _words;

  Id(String id) :
    _id = id,
    _words = id.split('_') 
  { 

// custom <Id.default ctor>

    if(null != _hasUpperRe.firstMatch(id)) {
      throw new ArgumentError("Id must be lower case $id");
    }

// end <Id.default ctor>
  }

  Map toJson() { 
    return { 
       "id" : _id,
       "words" : _words
    };
  }

  static Id fromJson(String json) {
    Map jsonMap = parse(json);
    Id result = new Id();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  static Id fromJsonMap(Map jsonMap) {
    Id result = new Id();
    result._fromJsonMapImpl(jsonMap);
    return result;
  }

  void _fromJsonMapImpl(Map jsonMap) {
    _id = jsonMap["id"];
    // words is good
  }


// custom <id impl>

  static final RegExp _hasUpperRe = new RegExp("[A-Z]");

  static capitalize(String s) => "${s[0].toUpperCase()}${s.substring(1)}";
  static uncapitalize(String s) => "${s[0].toLowerCase()}${s.substring(1)}";

  String get snake => _id;
  String get emacs => _words.join('-');
  String get camel => uncapitalize(_words.map((w) => capitalize(w)).join(''));
  String get capCamel => _words.map((w) => capitalize(w)).join('');
  String get shout => _words.map((w) => w.toUpperCase()).join('_');
  String get title => _words.map((w) => capitalize(w)).join(' ');  
  String get squish => _words.join('');
  String get abbrev => _words.map((w) => w[0]).join();

  static Id pluralize(Id id, [ String suffix = 's' ]) => new Id(id._id + suffix);

  static Id fromString(String id) {
    return new Id(id);
  }

  String toString() => camel;

// end <id impl>
}


// custom <id part top level>
// end <id part top level>

