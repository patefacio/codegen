import "../ebisu/templates/dart_meta.dart";
import "../ebisu/ebisu.dart";

main() {

  var context = {
    'name':'MyClass',
    'members': [ 
      { 
        'type' : 'int',
        'name' : 'foo',
      }
    ],
  };

  print(dclass(context));

}