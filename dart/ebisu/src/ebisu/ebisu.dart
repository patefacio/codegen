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


// custom <ebisu top level>

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

const String commentBegin = '//';
const String customBegin = '$commentBegin custom <([^>]+)>';
const String customEnd = '$commentBegin end <([^>]+)>';
final RegExp customBeginRe = new RegExp(customBegin);
final RegExp customEndRe = new RegExp(customEnd);

String mergeWithFile(String generated, String destFilePath,
    [ RegExp beginProtect, RegExp endProtect ]) {

  if(!?beginProtect) { beginProtect = customBeginRe; }
  if(!?endProtect) { endProtect = customEndRe; }

  File inFile = new File(destFilePath);
  List<String> results = [];
  if(inFile.existsSync()) {
    String currentText = inFile.readAsStringSync();

    Map<String, String> captures = {};
    Map<String, String> empties = {};

    RegExp block = new RegExp("\\n?[^\\S\\n]*?//\\s*custom\\s+<(.*?)>(?:.|\\n)*?end\\s+<\\1>", multiLine: true);
    for(Match match in block.allMatches(currentText)) {
      captures[match.group(1)] = match.group(0);
    }

    for(Match match in block.allMatches(generated)) {
      empties[match.group(1)] = match.group(0);
    }

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

// end <ebisu top level>

