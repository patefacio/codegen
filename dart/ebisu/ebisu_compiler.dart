library ebisu_compiler;

import "dart:io";
import "ebisu.dart";
import "package:pathos/path.dart" as path;
part "src/ebisu_compiler/compiler.dart";
final RegExp CODE_RE = new RegExp("^#<(.*)>\s*");
final RegExp COMMENT_RE = new RegExp("^\s*#");

main() { 
  print("Main for lib ebisu_compiler");

// custom <ebisu_compiler main>

  TemplateFile templateFile = new TemplateFile('/home/dbdavidson/tmp/goo.tmpl');
  templateFile.compile();

  TemplateFolder templateFolder = new TemplateFolder('/home/dbdavidson/open_source/dart/templates/dart');
  templateFolder.compile();

// end <ebisu_compiler main>
}


// custom <ebisu_compiler lib top level>
// end <ebisu_compiler lib top level>

