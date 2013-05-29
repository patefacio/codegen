part of ebisu_dwt_project;

/// Named grouping of components - just for organization and potentially dependency management
class ComponentLibrary { 
  ComponentLibrary(
    this.id
  ) {
  }
  
  /// Id of the component library
  String id;
  /// Documentation for this library
  String doc;
  /// List of components in this library
  List<Component> components = [];
  bool _finalized = false;
  /// Set to true when finalized
  bool get finalized => _finalized;
// custom <class ComponentLibrary>

  void _finalize(dynamic owner) {
    if(!_finalized) {
      components.forEach((c) => c._finalize(this));
      _finalized = true;
    }
  }

  void generate() {
    print("Generating component library ${id}");
    components.forEach((c) => c.generate());    
  }

// end <class ComponentLibrary>

}

/// A project GUI component
class Component { 
  Component(
    this.id
  ) {
  }
  
  /// Id for this component
  Id id;
  /// Description of component
  String doc;
  Id _type;
  /// Type of DWT component
  Id get type => _type;
  /// Super class being extended by this component
  Id extendsSuper;
  /// List of this component implements
  List<Id> implementsInterfaces = [];
  ComponentLibrary _owner;
  /// Component library that owns the component
  ComponentLibrary get owner => _owner;
  bool _finalized = false;
  /// Set to true when finalized
  bool get finalized => _finalized;
// custom <class Component>

  void _finalize(ComponentLibrary owner) {
    if(!_finalized) {
      _owner = owner;
      _type = id;
      if(extendsSuper != null) {
        _type = new Id('${_type.snake}_${extendsSuper.snake}');
      }
      _finalized = true;
    }
  }

  Component generate() {
    print("\tGenerating component of type ${_type.capCamel}");
    return this;
  }

// end <class Component>

}

/// For generating the shell of a DWT web app
class Project { 
  Project(
    this.id
  ) {
  }
  
  /// Id for this project
  Id id;
  /// Project description
  String doc;
  /// Root path to the generated dwt project
  String rootPath;
  /// List of component libraries to generate
  List<ComponentLibrary> componentLibraries = [];
  /// List of additional libraries to generate
  Library libraries;
  bool _finalized = false;
  /// Set to true when finalized
  bool get finalized => _finalized;
  String _projectPath;
  /// Path to top of project directory
  String get projectPath => _projectPath;
  String _webPath;
  /// Path to web directory
  String get webPath => _webPath;
  String _indexFilePath;
  /// Path to generated index.html file
  String get indexFilePath => _indexFilePath;
  String _cssFilePath;
  /// Path to generated css.html file
  String get cssFilePath => _cssFilePath;
// custom <class Project>

  void _finalize() {
    if(!_finalized) {
      componentLibraries.forEach((cl) => cl._finalize(this));
      _projectPath = "${rootPath}/${id.snake}";
      _webPath = "${_projectPath}/web";
      _indexFilePath = "${_webPath}/index.html";
      _cssFilePath = "${_webPath}/${id}.css";
      _finalized = true;
    }
  }

  void _generateIndex() {
    String guts = '''<!DOCTYPE html>

<html>
  <head>
    <meta charset="utf-8">
    <title>${doc}</title>
    <link rel="stylesheet" href="${id}.css">
  </head>
  <body>
    <script type="application/dart" src="src/app.dart"></script>
    <script src="src/packages/browser/dart.js"></script>
  </body>
</html>
''';
    mergeWithFile(guts, _indexFilePath);
  }

  void _generateCss() {
    String guts = '''
html,body,div,dl,dt,dd,ul,ol,li,h1,h2,h3,h4,h5,h6,pre,code,form,fieldset,legend,input,textarea,p,blockquote,th,td {
  margin: 0;
  padding: 0;
}

body {
  font-family: 'Open Sans', sans-serif;
  font-size: 14px;
  font-weight: normal;
  line-height: 1.2em;
  margin: 15px;
}

p {
  color: #333;
}

.header-content {
  font-size: 14px;
  font-weight: bold;
  padding: 3px;
}

.style-chooser {
}

h2 {
  text-rendering: optimizeLegibility;
  text-shadow: rgba(255,255,255,0.8) 0 1px 1px;
}

''';
    mergeWithFile(guts, _cssFilePath);
  }

  void _generateApp() {
    print("Generating App");
  }

  void _generateComponentLibraries() {
    print("Generating Component Libraries");
    componentLibraries.forEach((cl) => cl.generate());
  }

  void generate() {
    _finalize();
    _generateIndex();
    _generateCss();
    _generateApp();
    _generateComponentLibraries();
    print("Generation Complete");
  }

// end <class Project>

}
// custom <part dwt_project>

Id id(String _id) => new Id(_id);
Component component(String _id) => new Component(id(_id));
Project project(String _id) => new Project(id(_id));

// end <part dwt_project>

