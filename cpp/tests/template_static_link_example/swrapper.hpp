#ifndef _SWRAPPER_HPP_
#define _SWRAPPER_HPP_

#include <string>
#include <iostream>

struct swrapper {
  swrapper(char const* s) : s_(s) {
    std::cout << "ctor for swrap:" << s_ << '(' << this << ')' << std::endl;
  }
  ~swrapper() {
    std::cout << "dtor for swrap:" << s_ << '(' << this << ')' << std::endl;
  }
  std::string s_;
};

inline std::ostream& operator<<(std::ostream& out, swrapper const& sw) {
  out << sw.s_;
  return out;
}

#endif
