// This demonstrates how to define static data in templates. 
// You can just put in the header the definition:
// e.g.
// template < typename T > swrapper Sample_class< T >::static_data_("foo");
// And the linker will take care not to complain about duplicate definitions
// Additionally, there is only one copy of the static data
//

#include "sample_class.hpp"
#include <iostream>

extern int other();

int primary() {
  std::cout << Sample_class< Sample_class<int> >::static_data_ << " at " 
            << &Sample_class< Sample_class<int> >::static_data_ << 
    " from primary" << std::endl;
  return 0;
}

int main(int argc, char** argv) {
  primary();
  other();
  return 0;
}

