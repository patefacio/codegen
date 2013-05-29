part of ebisu_web_ui;

/// Collection of components wrapped in a library (think http://pub.dartlang.org/packages/widget)
class ComponentLibrary { 
  ComponentLibrary(
    this.id
  ) {
  }
  
  /// Documentation for the component library
  String doc;
  /// Path in which to generate the component library
  String rootPath;
  /// Id of the component library
  final Id id;
  /// List of support libraries
  List<Library> libraries = [];
  /// List of components in the collection
  List<Component> components;
  bool _finalized = false;
  /// Set to true on finalize
  bool get finalized => _finalized;
  /// List of PubDependency for this component and supporting libraries
  List<PubDependency> dependencies = [];
// custom <class ComponentLibrary>

  void finalize() {
    if(!_finalized) {
      for(Component component in components) {
        component.finalize();
      }
      _finalized = true;
    }
  }

  void generate() {
    finalize();
    components.forEach((component) {
      var name = component.id.capCamel;
      var componentPath = "${rootPath}/${id.snake}/lib/components";
      var htmlFile = "${componentPath}/${component.id.snake}.html";
      htmlMergeWithFile(component.html, htmlFile);

      var definition = '''
import "dart:html";
import "package:web_ui/web_ui.dart";
${component.imports.map((comp) => Library.importStatement(comp)).join('\n')}

/// ${component.doc}
class ${name} extends WebComponent {
${indentBlock(customBlock(name))}
}

''';
      var dartFile = "${componentPath}/${component.id.snake}.dart";
      htmlMergeWithFile(definition, dartFile);

    });

    var cssFile = "${rootPath}/${id.snake}/lib/components/${id.snake}.css";
    List<String> cssEntries = [];
    components.forEach((component) {
      cssEntries.add('''
[is=x-${component.id.emacs}] {
${indentBlock(cssCustomBlock(component.id.emacs))}
}
''');
    });
    
    cssMergeWithFile(cssEntries.join('\n\n'), cssFile);

    System sys = new System(id)
      ..rootPath = "${rootPath}/${id.snake}"
      ..libraries = libraries
      ..pubSpec = (new PubSpec(id)
          ..addDependency(new PubDependency('browser'))
          ..addDependency(new PubDependency('pathos'))
          ..addDependency(new PubDependency('web_ui'))
          ..addDependencies(dependencies));
    sys.generate();
  }

// end <class ComponentLibrary>

}

/// Declaratively define component to generate its stubbed out support
class Component { 
  Component(
    this.id
  ) {
  }
  
  /// Id - used to generate name of component
  Id id;
  /// Description of the component
  String doc;
  /// Dom element or other component being extended
  String extendsElement = "div";
  /// How to construct the component (convention handles unless exceptional case)
  String constructor;
  /// If true styles from document apply to control
  bool applyAuthorStyles = true;
  /// The internals of template fragment that will be rendered when the component is initialized
  String templateFragment = "";
  /// Dart imports required by the component
  List<String> imports = [];
  /// Component imports required by the component
  List<String> htmlImports = [];
  String _name;
  /// Name as used in the html (i.e. words of name hyphenated
  String get name => _name;
  bool _finalized = false;
  /// Set to true on finalize
  bool get finalized => _finalized;
// custom <class Component>

  void finalize() {
    if(!_finalized) {
      _name = "x-${id.emacs}";
      _finalized = true;
    }
  }

  String get html {
    String htmlImportsBlock = indentBlock(htmlImports.map((i) => 
            '<link rel="import" href=${importUri(i)}>').toList().join('\n'));

    return '''<!DOCTYPE html>
<html>
  <head>
${htmlImportsBlock}
${htmlCustomBlock('${id} head')}
  </head>
  <body>
    <element name="${name}" extends="${new Id(extendsElement).emacs}" constructor="${id.capCamel}">
      <template>
${indentBlock(templateFragment, '      ')}
${htmlCustomBlock('${id} template')}
      </template>
      <script type="application/dart" src='${id.snake}.dart'></script>
    </element>
  </body>
</html>
''';
  }

// end <class Component>

}
// custom <part component>

Id id(String _id) => new Id(_id);
ComponentLibrary componentLibrary(String _id) => new ComponentLibrary(id(_id));
Component component(String _id) => new Component(id(_id));

// end <part component>

