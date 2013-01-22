module examples.nesting.outer;

import std.container;
import std.conv;
import std.datetime;
import std.stdio;
import std.typecons;
import std.typetuple;

class Outer { 
  /**
     Good stuff
     use it well
  */
  alias DateTime Date;
  alias double Rate;
  alias Tuple!(DateTime, Rate) DateRate;
  /**
     Dont forget,
     we support RGB formatting
  */
  enum ThisIsAColor { 
    Red,
    Green,
    Blue
  }

  /**
     This
     struct
     rocks
     	!!!
  */
  struct NestedStruct { 
    string nsTop = "ns_top";
    // custom <dstruct nested_struct public_section>
    // end <dstruct nested_struct public_section>
  }

  /**
     This is a nested class, owned by RateCurve
  */
  class NestedClass { 
    class DeeperNesting { 
      int nestingIndex = 25*3;
      string nestingText = "sweet";
      private {
        class CrazyNesting { 
        }
      }
    }
  }

  export {
    /**
       You can access
       me from a dll!!
    */
    alias Array!int ExportedContainerType;
    NestedStruct _Impl2;
  }

  package {
    int _Impl3;
  }

  private {
    int _Impl;
  }
}

export {
  /**
     This is my package class
  */
  class SomeExportedClass { 
  }
}

protected {
  /**
     This is my protected class
  */
  class SomeProtectedClass { 
  }
}

package {
  /**
     This is my package class
  */
  class SomePackageClass { 
  }
}

private {
  /**
     This is my private class
  */
  class SomePrivateClass { 
  }
}

/**
   License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
*/
