/******************************************************************************
 * c.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file c.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_VGROUP_C_H_
#define _FCS_EXAMPLES_VGROUP_C_H_

#include "fcs/utils/block_indenter.hpp"
#include <string>
#include <iostream>

namespace fcs {
namespace examples {
namespace vgroup {

  class C :
    public One_ring_base 
  {
  public:

    explicit C(
      std::string const& c1 = "c1",
      std::string const& c2 = "c2",
      std::string const& c3 = "c3"
    ) :
      c1_(c1),
      c2_(c2),
      c3_(c3)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, C const& item);

    //! Observes the data
    virtual void 
    observe(int i, char const * s);

    //! Does good
    virtual void 
    do_good(int i);

    //! Does bad
    virtual void 
    do_bad(int i);
  private:
    std::string c1_;
    std::string c2_;
    std::string c3_;
  };

  // Support for streaming non-static streamable members of C
  inline
  std::ostream& operator<<(std::ostream& out, C const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "C:(" << &item << "):{";
    out << '\n' << indent << "  c1:" << item.c1_;
    out << '\n' << indent << "  c2:" << item.c2_;
    out << '\n' << indent << "  c3:" << item.c3_;
    out << indent << "}\n";
    return out;
  } 

} // namespace vgroup
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_VGROUP_C_H_
