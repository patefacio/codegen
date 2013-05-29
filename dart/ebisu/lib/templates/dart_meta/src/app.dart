part of dart_meta;

String app([dynamic _]) {
  if(_ is Map) {
    _ = new Context(_);
  }
  List<String> _buf = new List<String>();


  _buf.add('''
void main() { 
}
''');
  return _buf.join();
}