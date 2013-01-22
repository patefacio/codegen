#include "sample_class.hpp"
#include <iostream>

int other() {
  std::cout << Sample_class< Sample_class<int> >::static_data_ << " at " 
            << &Sample_class< Sample_class<int> >::static_data_ << 
    " from other" << std::endl;
  return 0;
}

