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

// custom <id impl>

  static final RegExp _hasUpperRe = new RegExp("[A-Z]");

  String get emacs => _words.join('-');
  String get shout => _words.map((w) => w.toUpperCase()).join('_');
  String get title => _words.map((w) => "${w[0].toUpperCase()}${w.substring(1)}").join(' ');  
  String get squish => _words.join('');
  String get abbrev => _words.map((w) => w[0]).join();

  static Id pluralize(Id id, [ String suffix = 's' ]) => new Id(id._id + suffix);

// end <id impl>
}


// custom <id top level>
// end <id top level>

