/** ebisu */
part of ebisu;

class Context { 
  Map _data;

  Context(Map data) :
    _data = data 
  { 
  }

// custom <context impl>

  dynamic noSuchMethod(InvocationMirror msg) {
    String memberName = msg.memberName;
    if(! _data.containsKey(memberName)) {
      throw new ArgumentError("Context could not find key '$memberName' in data");
    }
    return _data[memberName];
  }

  dynamic operator[](dynamic index) {
    return _data[index];
  }

// end <context impl>
}


// custom <ebisu part top level>

Iterable asContexts(Iterable items) {
  return items.toList().map((i) => new Context(i));
}

String blockComment(String text, [String indent = '  ']) {
  String guts = text.split('\n').join("\n$indent");
  return "/**\n$indent$guts\n*/";
}

String indentBlock(String block, [String indent = '  ']) {
  return '$indent${block.split("\n").join("\n$indent")}';
}

const String _customBegin = r'//\s*custom';
const String _customEnd = r'//\s*end';
const String _customBlockText = '''
// ${'custom'} <TAG>
// ${'end'} <TAG>
''';

String customBlock(String tag) {
  return _customBlockText.replaceAll('TAG', tag);
}

final RegExp _trailingNewline = new RegExp(r'\n$');
String chomp(String s) {
  return s.replaceFirst(_trailingNewline, '');
}

String mergeWithFile(String generated, String destFilePath,
    [ String beginProtect, String endProtect ]) {

  if(!?beginProtect) beginProtect = _customBegin;
  if(!?endProtect) endProtect = _customEnd;

  File inFile = new File(destFilePath);

  if(inFile.existsSync()) {
    String currentText = inFile.readAsStringSync();

    Map<String, String> captures = {};
    Map<String, String> empties = {};

    RegExp block = 
      new RegExp(
          "\\n?[^\\S\\n]*?$_customBegin"             // Look for begin
          "\\s+<(.*?)>(?:.|\\n)*?"                   // Eat - non-greedy
          "$_customEnd\\s+<\\1>",                    // Require matching end
          multiLine: true);

    block.allMatches(currentText).forEach((m) 
        { captures[m.group(1)] = m.group(0); });
    block.allMatches(generated).forEach((m) 
        { empties[m.group(1)] = m.group(0); });

    captures.forEach((k,v) {
      if(!empties.containsKey(k)) {
        print("Warning: protect block <$k> removed");
      } else {
        generated = generated.replaceFirst(empties[k], captures[k]);
      }
    });

    if(generated == currentText) {
      print("No change: $destFilePath");
    } else {
      var out = inFile.openWrite();
      out.write(generated);
      print("Wrote: $destFilePath");
    }

  } else {
    new Directory(path.dirname(destFilePath))
      ..createSync(recursive: true);
    var out = inFile.openWrite();
    out.write(generated);
    print("Created $destFilePath");
  }
}

// end <ebisu part top level>

