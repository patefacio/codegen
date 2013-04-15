library meta;

import "dart:io";
import "dart:json" as JSON;
import "package:ebisu/ebisu.dart";
import "package:ebisu/ebisu_id.dart";
import "package:ebisu/ebisu_utils.dart" as EBISU_UTILS;
import "templates/dlang_meta.dart" as META;
part "src/meta/meta.dart";

final BasicType voidT = new BasicType('void', null);

final BasicType boolT = new BasicType('bool', false);

final BasicType byteT = new BasicType('byte', 0);

final BasicType ubyteT = new BasicType('ubyte', 0);

final BasicType shortT = new BasicType('short', 0);

final BasicType ushortT = new BasicType('ushort', 0);

final BasicType intT = new BasicType('int', 0);

final BasicType uintT = new BasicType('uint', 0);

final BasicType longT = new BasicType('long', 0);

final BasicType ulongT = new BasicType('ulong', 0);

final BasicType centT = new BasicType('cent', 0);

final BasicType ucentT = new BasicType('ucent', 0);

final BasicType floatT = new BasicType('float', 'float_nan');

final BasicType doubleT = new BasicType('double', 'double_nan');

final BasicType realT = new BasicType('real', 'real_nan');

final BasicType ifloatT = new BasicType('ifloat', 'ifloat_nan');

final BasicType idoubleT = new BasicType('idouble', 'idouble_nan');

final BasicType irealT = new BasicType('ireal', 'ireal_nan');

final BasicType cfloatT = new BasicType('cfloat', 'cfloat_nan');

final BasicType cdoubleT = new BasicType('cdouble', 'cdouble_nan');

final BasicType crealT = new BasicType('creal', 'creal_nan');

final BasicType charT = new BasicType('char', 'xff');

final BasicType wcharT = new BasicType('wchar', 'xffff');

final BasicType dcharT = new BasicType('dchar', 'x0000ffff');

main() {
  print("Main for library meta");
}
// custom <library meta>
// end <library meta>

