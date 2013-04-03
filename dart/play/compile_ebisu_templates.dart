import "package:ebisu/ebisu_compiler.dart";

main() {
  TemplateFolder templateFolder = 
    new TemplateFolder(
        '../ebisu/templates/dart_meta', 
        'dart_meta');

  templateFolder.compile();
}