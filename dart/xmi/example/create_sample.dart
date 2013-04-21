import "dart:io";
import "package:pathos/path.dart" as path;
import "package:xmi/xmi.dart";

main() {

  JsonUModelBuilder builder = 
    new JsonUModelBuilder('./sample.xmi.json');

  UModel model = builder.buildModel();
  
}
