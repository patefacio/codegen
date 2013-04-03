/** compiler */
part of ebisu_compiler;

class TemplateFile { 
  String _inputPath;

  /**
     Path to write the dart file
  */
  String _outputPath;

  /**
     Library this function is part of
  */
  String _partOf;
  String _functionName;

  TemplateFile(
      String inputPath, { 
        String this._outputPath,
        String this._partOf
      }) :
    _inputPath = inputPath 
  { 
  }

// custom <template_file impl>

  bool compile() {
    _functionName = path.basenameWithoutExtension(this._inputPath); 

    if(_outputPath == null) {
      _outputPath = path.join(path.dirname(this._inputPath), 'src');

      new Directory(_outputPath)
        ..createSync(recursive: true);
    }

    _outputPath = path.join(_outputPath, _functionName+'.dart');

    DateTime inputModtime = new File(this._inputPath).lastModifiedSync();
    DateTime outputModtime;

    File outfile = new File(_outputPath);
    if(outfile.existsSync()) {
      outputModtime = outfile.lastModifiedSync();
    }

    if(null != outputModtime) {
      if(inputModtime > outputModtime) {
        compileImpl();
        return true;
      } 
    } else {
      compileImpl();
      return true;
    }
    return false;
  }

  void compileImpl() {
    bool inString = false;
    File inFile = new File(this._inputPath);
    var outFile = new File(this._outputPath).openWrite();

    if(null != _partOf) {
      outFile.writeln('part of $_partOf;');
    }

    outFile.writeln('''

String ${_functionName}([Map _map]) {
  if(!?_map) {
    _map = new Map();
  }
  Context _ = new Context(_map);
  List<String> _buf = new List<String>();

''');
    openString() {
      if(!inString) {
          outFile.writeln("  _buf.add('''");
          inString = true;
      }
    }
    closeString() {
      if(inString) {
          outFile.writeln("''');");
          inString = false;
      }
    }
    inFile.readAsLinesSync().forEach((line) {
      Match code_match = CODE_RE.firstMatch(line);
      if(code_match != null) {
        closeString();
        String code = code_match.group(1);
        if(null == COMMENT_RE.firstMatch(code)) {
          outFile.writeln("$code");
        }
      } else {
        openString();
        outFile.writeln(line);
      }
    });
    closeString();
    outFile.writeln('''  print(_buf.join());\n}''');
  }

// end <template_file impl>
}

class TemplateFolder { 

  /**
     Path to folder of templates to be compiled into a single library
  */
  String _inputPath;

  /**
     Name of the libarary associated with the template folder
  */
  String _libName;

  /**
     Path to where to generate the dart support library for the templates in the folder
  */
  String _outputPath;

  /**
     Any additional imports - include text after the "import " directly
  */
  List<String> _imports;

  TemplateFolder(
      String inputPath,
      String libName, { 
        String this._outputPath,
        List<String> this._imports
      }) :
    _inputPath = inputPath,
    _libName = libName 
  { 
  }

// custom <template_folder impl>

  void compile() {

    if(_outputPath == null) {
      _outputPath = path.join(this._inputPath, 'src');

      new Directory(_outputPath)
        ..createSync(recursive: true);
    }

    RegExp templateRe = new RegExp(r"\.tmpl$");
    Directory dir = new Directory(_inputPath);
    for(var file in dir.listSync()) {
      String p = file.path;
      if(null != templateRe.firstMatch(p)) {
        TemplateFile templateFile = 
          new TemplateFile(p, _outputPath: _outputPath, _partOf: _libName);
        bool compiled = templateFile.compile();
        if(compiled) {
          print("Compiled: $p => ${templateFile._outputPath}");
        } else {
          print("No change: $p => ${templateFile._outputPath}");
        }
      }
    }

    String libPath = path.join(path.dirname(this._inputPath), _libName + '.dart');
    var outFile = new File(libPath).openWrite();

    outFile.writeln("library $_libName;");

    outFile.writeln('import "package:ebisu/ebisu.dart";');

    if(null != _imports) {
      for(String imp in imports) {
        outFile.writeln('import $imp;');
      }
    }

    dir = new Directory(_outputPath);
    RegExp dartRe = new RegExp(r"\.dart$");
    for(var file in dir.listSync()) {
      String p = file.path;
      if(null != dartRe.firstMatch(p)) {
        print("$p and $libPath");
        String relPath = path.relative(p, from: path.dirname(libPath));
        outFile.writeln('part "$relPath";');
      }
    }

  }

// end <template_folder impl>
}


// custom <compiler top level>
// end <compiler top level>

