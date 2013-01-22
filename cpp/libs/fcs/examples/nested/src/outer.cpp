/******************************************************************************
 * outer.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file outer.cpp
 *
 * \brief 
 * 
 */

#include "fcs/examples/nested/outer.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>


// custom <outer pre-namespace custom>
// end <outer pre-namespace custom>

namespace fcs {
namespace examples {
namespace nested {

  
// custom <outer namespace custom>
// end <outer namespace custom>


  // Support for streaming non-static streamable members of outer
  std::ostream& operator<<(std::ostream& out, outer const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "outer:(" << &item << "):{";
    out << '\n' << indent << "  a:" << item.a_;
    out << indent << "}\n";
    return out;
  }

  // Support for streaming non-static streamable members of inner
  std::ostream& operator<<(std::ostream& out, outer::inner const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "inner:(" << &item << "):{";
    out << '\n' << indent << "  a:" << item.a_;
    out << indent << "}\n";
    return out;
  }

  void outer::ctor_member_init() {
    
// custom <outer::init>
// end <outer::init>
  }


} // namespace nested
} // namespace examples
} // namespace fcs


