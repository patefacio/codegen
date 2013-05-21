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
    ..pubSpec = (pubspec('xmi')
        ..doc = '''Support for basic Dart code generation from Altova UML Model.  The idea is UML
can be used to define the structure of data being passed between
client/server. Once stored in UML the XMI data can be parsed and used to
generate Dart code. Since Dart does not yet have an XML parser, the approach is
to pass the model through a XML to JSON converter (_xmi_to_json.rb_) first. 


Only a subset of the XMI meta data is defined - just enough to support basic
classes with properties. Meta data for templates are required for two uml
parameterized classes (list<E> and j_map<K>). This particular solution requires
all class names in the UML to be lower case with underscore separating
words. The reason for this is that the ebisu code generation itself is strict
about that as well.
'''
        ..dependencies = [
          pubdep('pathos'),
          pubdep('ebisu')
          ..path = '../ebisu',
        ]
                 )
    ..rootPath = _topDir
    ..libraries = [
      library('xmi')
      ..doc = 'Support for storing XMI meta data'
      ..imports = [
        'io',
        '"dart:json" as JSON', 
        '"package:pathos/path.dart" as path',
        '"package:ebisu/ebisu_utils.dart" as EBISU_UTILS',
      ]
      ..parts = [
        part('model')
        ..classes = [
          class_('json_u_model_builder')
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
            member('item_map')
            ..doc = 'Map of items indexed by xmi:id'
            ..type = 'Map<String, dynamic>'
            ..access = Access.RO
            ..classInit = '{}',
            member('sig_to_owner')
            ..doc = 'Map of id of signature to its owner'
            ..type = 'Map<String, String>'
            ..access = Access.RO
            ..classInit = '{}',
          ],
          class_('u_model')
          ..members = [
            member('root')..type = 'UPackage',
            member('item_map')
            ..doc = 'Map of items indexed by xmi:id'
            ..type = 'Map<String, dynamic>'
            ..access = Access.RO
            ..classInit = '{}',
          ],
          class_('u_class')
          ..members = [ 
            id_member('uml class'), 
            name_member('uml class'),
            comment_member('uml class'),
            properties_member('uml class'),
            member('templ_binding')..type = 'UTemplBinding',
            member('templ_sig')..type = 'UTemplSig',
          ],
          class_('u_comment')
          ..members = [
            id_member('uml comment'),
            member('body')
            ..doc = 'Text of the comment'
          ],
          class_('u_dependency')
          ..members = [
            id_member('uml dependency'),
            member('supplier'),
            member('client'),
          ],
          class_('u_enumeration')
          ..members = [
            id_member('uml enumeration'), 
            name_member('uml enumeration'),
            properties_member('uml enumeration'),
            comment_member('uml enumeration'),
          ],
          class_('u_package')
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
            member('primitive_types')
            ..type = 'List<UPrimitiveType>'
            ..classInit = '[]',
            member('packages')
            ..type = 'List<UPackage>'
            ..classInit = '[]',
            member('parent_package_id'),
            member('path')
            ..doc = 'Path to package as list of strings'
            ..type = 'List<String>'
            ..classInit = '[]'
          ],
          class_('u_primitive_type')
          ..members = [
            id_member('uml primitive type'), 
            name_member('uml primitive type'),
          ],
          class_('u_property')
          ..members = [
            id_member('uml property'), 
            name_member('uml property'),
            comment_member('uml property'),
            member('type')..doc = 'Id for the type of this property',
            member('visibility'),
            member('aggregation'),
          ],
          class_('u_profile')       
          ..members = [
            id_member('uml profile'), 
            name_member('uml profile'),
          ],
          class_('u_stereotype')
          ..members = [
            id_member('uml stereotype'), 
            name_member('uml stereotype'),
            properties_member('uml class'),
          ],
          class_('u_templ_binding')
          ..members = [
            id_member('uml template binding'),
            member('signature_id')
            ..doc = 'Id of the signature of this template binding',
            member('templ_parm_substs')
            ..doc = 'Parameter substitutions for this binding'
            ..type = 'List<UTemplParmSubst>'
            ..classInit = '[]',
          ],
          class_('u_templ_parm_subst')
          ..members = [
            id_member('uml template parameter substitution'),
            member('formal_id')..doc = 'Id of the formal type being substituted',            
            member('actual_id')..doc = 'Id of the actual type being substituted',            
          ],
          class_('u_classifier_templ_parm')
          ..members = [
            id_member('uml classifier template parameter'),
            member('allow_substitutable')..type = 'bool'..classInit = 'false',
            member('name'),
            member('type'),
          ],
          class_('u_templ_sig')
          ..members = [
            id_member('uml template signature'),
            member('parms')
            ..type = 'List<UClassifierTemplParm>'
            ..classInit = '[]',
          ],
        ]
      ],

      library('xmi_to_dart')
      ..doc = '''Support for creating a dart file from Altova UML class model (xmi file converted to json).
Only structure is generated with json support. Effectively this allows IDL type structure modeling from
UML with code generation to support Dart.
'''
      ..imports = [
        'io',
        '"dart:json" as JSON', 
        '"package:plus/pprint.dart"',
        '"package:pathos/path.dart" as path',
        '"package:ebisu/ebisu_utils.dart" as EBISU_UTILS',
        '"package:ebisu/ebisu_dart_meta.dart"',
        '"package:xmi/xmi.dart"',
      ]
      ..classes = [
        class_('converter')
        ..doc = 'Pull in the model and generate dart'
        ..members = [
          member('src_file')
          ..doc = 'Path to json input file'
          ..ctors = [''],
          member('out_path')
          ..doc = 'Path into which to generate the dart code (with json support) representing the model'
          ..ctors = [''],
          member('library_name')
          ..doc = 'Name of the library to create to support this model'
          ..ctorsOpt = ['']
        ]
      ]
    ];

  /*
  xmi.libraries.forEach((library) {
    library.parts.forEach((part) {
      part.classes.forEach((c) {
        c.toJsonSupport = true;
      });
    });
  });
  */

  xmi.generate();

}