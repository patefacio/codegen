/******************************************************************************
 * b.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file b.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_GROUP_B_H_
#define _FCS_EXAMPLES_GROUP_B_H_

#include "fcs/utils/block_indenter.hpp"
#include <string>
#include <iostream>

namespace fcs {
namespace examples {
namespace group {

  class B 
  {
  public:

    // Public static consts
    static int const ONE_RING_ID = 1;
    explicit B(
      std::string const& b1 = "b1",
      std::string const& b2 = "b2",
      std::string const& b3 = "b3"
    ) :
      b1_(b1),
      b2_(b2),
      b3_(b3)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, B const& item);

    //! Observes the data
    void 
    observe(int i, char const * s);

    //! Does good
    void 
    do_good(int i);

    //! Does bad
    void 
    do_bad(int i);
  private:
    std::string b1_;
    std::string b2_;
    std::string b3_;
  };

  // Support for streaming non-static streamable members of B
  inline
  std::ostream& operator<<(std::ostream& out, B const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "B:(" << &item << "):{";
    out << '\n' << indent << "  b1:" << item.b1_;
    out << '\n' << indent << "  b2:" << item.b2_;
    out << '\n' << indent << "  b3:" << item.b3_;
    out << indent << "}\n";
    return out;
  } 

} // namespace group
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_GROUP_B_H_
