library ebisu_compiler;

import "dart:io";
import "ebisu.dart";
import "package:pathos/path.dart" as path;
part "src/ebisu_compiler/compiler.dart";

// Regex to match a single line if dart code (i.e. in looks like #< ... >)
final RegExp codeRe = new RegExp("^#<(.*)>\\s*");

// Regex to match the comment portion of a comment line (i.e. in looks like #<# ... >)
final RegExp commentRe = new RegExp("^\\s*#");

main() {
  print("Main for library ebisu_compiler");
  // custom <main ebisu_compiler>
  // end <main ebisu_compiler>
  
}
// custom <library ebisu_compiler>
// end <library ebisu_compiler>

