/// Primary library for client usage of ebisu
library ebisu;

import "dart:io";
import "package:pathos/path.dart" as path;
part "src/ebisu/ebisu.dart";

// Path to this package - for use until this becomes a pub package
final dynamic ebisuPath = Platform.environment['EBISU_PATH'];

main() {
  print("Main for library ebisu");
  // custom <main ebisu>
  // end <main ebisu>
  
}
// custom <library ebisu>
// end <library ebisu>

