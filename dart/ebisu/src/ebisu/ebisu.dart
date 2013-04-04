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

const String customBegin = r'//\s*custom';
const String customEnd = r'//\s*end';
const String customBlockText = '''
// ${'custom'} <TAG>
// ${'end'} <TAG>
''';

String customBlock(String tag) {
  return customBlockText.replaceAll('TAG', tag);
}

String mergeWithFile(String generated, String destFilePath,
    [ String beginProtect, String endProtect ]) {

  if(!?beginProtect) beginProtect = customBegin;
  if(!?endProtect) endProtect = customEnd;

  File inFile = new File(destFilePath);

  if(inFile.existsSync()) {
    String currentText = inFile.readAsStringSync();

    Map<String, String> captures = {};
    Map<String, String> empties = {};

    RegExp block = 
      new RegExp(
          "\\n?[^\\S\\n]*?$customBegin"             // Look for begin
          "\\s+<(.*?)>(?:.|\\n)*?"                  // Eat - non-greedy
          "$customEnd\\s+<\\1>",                    // Require matching end
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
    new Directory(path.directory(destFilePath))
      ..createSync(recursive: true);
    var out = inFile.openWrite();
    out.write(generated);
    print("Created $destFilePath");
  }
}

// end <ebisu part top level>

