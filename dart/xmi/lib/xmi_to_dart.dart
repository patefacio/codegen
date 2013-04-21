/// Support for creating a dart file from Altova UML class model (xmi file converted to json).
/// Only structure is generated with json support. Effectively this allows IDL type structure modeling from
/// UML with code generation to support Dart.
/// 
library xmi_to_dart;

import "dart:io";
import "dart:json" as JSON;
import "package:plus/pprint.dart";
import "package:pathos/path.dart" as path;
import "package:ebisu/ebisu_utils.dart" as EBISU_UTILS;
import "package:ebisu/ebisu_dart_meta.dart";
import "package:pathos/path.dart";
import "package:xmi/xmi.dart";

/// Pull in the model and generate dart
class Converter { 
  Converter(
    this.srcFile,
    this.outPath,
    [
      this.libraryName
    ]
  ) {
  }
  
  /// Path to json input file
  String srcFile;
  /// Path into which to generate the dart code (with json support) representing the model
  String outPath;
  /// Name of the library to create to support this model
  String libraryName;
// custom <class Converter>

  void convert() {
    JsonUModelBuilder builder = new JsonUModelBuilder(srcFile);
    UModel model = builder.buildModel();

    if(libraryName == null) {
      libraryName = path.basenameWithoutExtension(srcFile);
    }

    Library library = library(libraryName)
      ..imports = [
        'math', 
        'json',
        '"package:ebisu/ebisu_utils.dart" as EBISU_UTILS',
        '"package:plus/pprint.dart"',
      ]
      ..variables = [
        variable('random_json_generator')
        ..doc = 'Local random generator - seeded to (0) to allow reproducibility'
        ..type = 'Random'
        ..init = 'new Random(0)'
        ..isPublic = false
        ..isFinal = true
      ];
    
    System sys = system('domain_model')
      ..rootPath = outPath
      ..libraries = [ library ];

    final RegExp jMapRe = new RegExp(r"j_map_of_(.*)");
    final RegExp listRe = new RegExp(r"list_of_(.*)");

    model.itemMap.forEach((k,v) {
      if(v is UClass) {
        if(null == v.name) {
          return;
        }
        // No need to generate j_map_of... or list_of...
        if(v.templSig != null) {
          return;
        }

        if((jMapRe.firstMatch(v.name) != null) ||
            (listRe.firstMatch(v.name) != null)) {
          return;
        }

        Class klass = class_(v.name)
          ..jsonSupport = true
          ..doc = (v.comment != null)? v.comment.body : null;
      
        library.classes.add(klass);

        //////////////////////////////////////////////////////////////////////////
        /// Name types as follows: if type is primitive, just use the name
        /// otherwise type is reference to some class or enum, so go with
        /// capCamel, which is what dart meta does
        //////////////////////////////////////////////////////////////////////////
        String nameTypeByXmiId(String xmiId) {
          var type = model.itemMap[xmiId];
          if(type is UPrimitiveType) {
            switch(type.name) {
              case 'string': return 'String';
              default: return type.name;
            }
          } else {
            switch(type.name) {
              case 'date':
              case 'Date':
                return 'DateTime';
              default: return id(type.name).capCamel;
            }
          }
        }

        v.properties.forEach((property) {
          var propertyType = model.itemMap[property.type];
        
          ////////////////////////////////////////////////////////////////////////
          // * Tricky Handling of j_map and list* 
          //
          // To support lists and maps, intervene in searc of j_map_of... and
          // list_of...  and convert to List<...> and Map<String, ...>
          ////////////////////////////////////////////////////////////////////////
          Match m;
          //print("PT => ${property.name} ${property.type} ${propertyType}");
          if((m = jMapRe.firstMatch(propertyType.name)) != null) {
            String typeId = propertyType.templBinding.templParmSubsts[0].actualId;
            String typeName = nameTypeByXmiId(typeId);
            klass.members.add(member(property.name)
                ..type = 'Map<String, ${typeName}>'
                ..doc = (property.comment != null)? property.comment.body : null);
          } else if((m = listRe.firstMatch(propertyType.name)) != null) {
            String typeId = propertyType.templBinding.templParmSubsts[0].actualId;
            String typeName = nameTypeByXmiId(typeId);
            klass.members.add(member(property.name)
                ..type = 'List<${typeName}>'
                ..doc = (property.comment != null)? property.comment.body : null);
          } else {
            klass.members.add(member(property.name)
                ..type = nameTypeByXmiId(property.type)
                ..doc = (property.comment != null)? property.comment.body : null);
          }
        });
      } else if(v is UEnumeration) {
        Enum enum_ = enum_(v.name);
        library.enums.add(enum_);
        v.properties.forEach((property) {
          enum_.values.add(id(property.name));
        });
      }
    });

    print("---------------------");
    //print(prettyJsonMap(sys.toJson()));
    sys.generate();
  }

// end <class Converter>

}

main() {
  print("Main for library xmi_to_dart");
  // custom <main xmi_to_dart>

  Converter converter = 
    new Converter('/home/dbdavidson/plusauri/modeling/sample.xmi.json',
        '/tmp/uml_codegen_sample');
  converter.convert();

  // end <main xmi_to_dart>
  
}
// custom <library xmi_to_dart>
// end <library xmi_to_dart>

