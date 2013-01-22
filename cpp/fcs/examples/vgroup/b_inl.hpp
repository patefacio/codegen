/******************************************************************************
 * b_inl.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file b_inl.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_VGROUP_B_INL_H_
#define _FCS_EXAMPLES_VGROUP_B_INL_H_

#include <pantheios/pantheios.hpp>
#include "fcs/examples/vgroup/b.hpp"

namespace fcs {
namespace examples {
namespace vgroup {
  inline void
  B::observe(int i, char const * s) {
  
// custom <observe impl>
// end <observe impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "B::observe");
  }
  inline void
  B::do_good(int i) {
  
// custom <do_good impl>
// end <do_good impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "B::do_good");
  }
  inline void
  B::do_bad(int i) {
  
// custom <do_bad impl>
// end <do_bad impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "B::do_bad");
  }



} // namespace vgroup
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_VGROUP_B_INL_H_
