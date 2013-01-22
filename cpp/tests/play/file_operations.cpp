#include <iostream>
#include "fcs/utils/file_path.hpp"

int main(int argc, char** argv) {
  using namespace boost::filesystem;
  namespace fs = boost::filesystem;
  path p("/tmp/goo.txt");

  std::cout << "full_path: " << fcs::utils::full_path(p) << std::endl;
  std::cout << "basename: " << fcs::utils::basename(p) << std::endl;

#if 0
  std::cout << "stem: " << p.stem() << std::endl;
  std::cout << "filename: " << p.filename() << std::endl;
  std::cout << "string: " << p.string() << std::endl;
  std::cout << "file_string: " << p.file_string() << std::endl;
#endif
  return 0;
}
