import "dart:io";
import "package:pathos/path.dart" as path;
import "package:ebisu/ebisu.dart";
import "package:ebisu/ebisu_id.dart";
import "package:ebisu/ebisu_dart_meta.dart";

String _topDir = path.dirname(path.dirname(path.absolute(new Options().script)));

main() {

  Member id_member(String owner) => member('id')
    ..doc = "Id for this $owner"
    ..access = Access.RO
    ..ctors = ['']
    ..isFinal = true;

  Member name_member(String owner) => member('name')
    ..doc = "Name for this $owner";

  Member properties_member(String owner) => member('properties')
    ..doc = 'Properties of this $owner'
    ..type = 'List<UProperty>'
    ..classInit = '[]';

  Member comment_member(String owner) => member('comment')
    ..doc = 'Comment (ownedComment) of this $owner'
    ..type = 'UComment';

  System xmi = system('xmi')
    ..rootPath = _topDir
    ..libraries = [
      library('xmi')
      ..doc = 'Support for storing XMI meta data'
      ..imports = [
        'io',
        '"dart:json" as JSON', 
        '"package:plus/pprint.dart"',
        '"package:pathos/path.dart" as path',
        '"package:ebisu/ebisu_utils.dart" as EBISU_UTILS',
      ]
      ..parts = [
        part('model')
        ..classes = [
          dclass('json_u_model_builder')
          ..doc = 'Build a UModel from json representation of XMI'
          ..members = [
            member('src_json_file')
            ..doc = 'Path to json input file'
            ..isFinal = true
            ..ctors = [''],
            member('model_data')
            ..doc = 'Data in Map format from parsed json'
            ..access = Access.IA
            ..type = 'Map',
            member('current')
            ..doc = 'The current UML entry being built'
            ..access = Access.IA
            ..type = 'dynamic',
          ],
          dclass('u_model')
          ..members = [
            member('root')..type = 'UPackage',
            member('item_map')
            ..doc = 'Map of items indexed by xmi:id'
            ..type = 'Map<String, dynamic>'
            ..access = Access.RO
            ..classInit = '{}',
          ],
          dclass('u_class')
          ..members = [ 
            id_member('uml class'), 
            name_member('uml class'),
            comment_member('uml class'),
            properties_member('uml class'),
          ],
          dclass('u_classifier_templ_parm'),
          dclass('u_comment')
          ..members = [
            id_member('uml comment'),
            member('body')
            ..doc = 'Text of the comment'
          ],
          dclass('u_dependency')
          ..members = [
            id_member('uml dependency'),
            member('supplier'),
            member('client'),
          ],
          dclass('u_enumeration')
          ..members = [
            id_member('uml enumeration'), 
            name_member('uml enumeration'),
            properties_member('uml enumeration'),
            comment_member('uml enumeration'),
          ],
          dclass('u_package')
          ..members = [
            id_member('uml package'), 
            name_member('uml package'),
            comment_member('uml package'),
            member('classes')
            ..type = 'List<UClass>'
            ..classInit = '[]',
            member('enums')
            ..type = 'List<UEnumeration>'
            ..classInit = '[]',
            member('packages')
            ..type = 'List<UPackage>'
            ..classInit = '[]'
          ],
          dclass('u_primitive_type')
          ..members = [
            id_member('uml primitive type'), 
            name_member('uml primitive type'),
          ],
          dclass('u_property')
          ..members = [
            id_member('uml property'), 
            name_member('uml property'),
            comment_member('uml property'),
            member('visibility'),
            member('aggregation'),
          ],
          dclass('u_profile')       
          ..members = [
            id_member('uml profile'), 
            name_member('uml profile'),
          ],
          dclass('u_stereotype')
          ..members = [
            id_member('uml stereotype'), 
            name_member('uml stereotype'),
            properties_member('uml class'),
          ],
          dclass('u_templ_binding'),
          dclass('u_templ_parm_subst'),
          dclass('u_templ_sig'),
        ]
      ]
    ];

  xmi.libraries.forEach((library) {
    library.parts.forEach((part) {
      part.classes.forEach((c) {
        c.toJsonSupport = true;
      });
    });
  });

  xmi.generate();
}