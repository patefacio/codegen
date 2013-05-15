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
  /// List of components in the collection
  List<Component> components;
  bool _finalized = false;
  /// Set to true on finalize
  bool get finalized => _finalized;
// custom <class ComponentLibrary>

  void finalize() {
    if(!_finalized) {
      for(Component component in components) {
        component.finalize();
      }
      _finalized = true;
    }
  }

  System get componentSystem {
    finalize();
    print("Generating ${id} in ${rootPath}");
    System sys = system('ignored')
      ..generatePubSpec = false
      ..rootPath = rootPath
      ..libraries = [
        library(id.snake)
      ];

    for(Component component in components) {
      print(component.html);
    }
    
    return sys;
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
  final Id id;
  /// Description of the component
  String doc;
  /// Dom element or other component being extended
  String extendsElement = "div";
  /// How to construct the component (convention handles unless exceptional case)
  String constructor;
  /// If true styles from document apply to control
  bool applyAuthorStyles = true;
  /// Template fragment that will be rendered when the component is initialized
  String templateFragment = "<template></template>";
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
    return '''<!DOCTYPE html>
<html>
  <head>
    <link rel="import" href="swap.html">
  </head>
  <body>
    <element name="${name}" extends="${extendsElement}">
${indentBlock(templateFragment, '      ')}
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

