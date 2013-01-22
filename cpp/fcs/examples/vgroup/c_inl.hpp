/******************************************************************************
 * c_inl.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file c_inl.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_VGROUP_C_INL_H_
#define _FCS_EXAMPLES_VGROUP_C_INL_H_

#include <pantheios/pantheios.hpp>
#include "fcs/examples/vgroup/c.hpp"

namespace fcs {
namespace examples {
namespace vgroup {
  inline void
  C::observe(int i, char const * s) {
  
// custom <observe impl>
// end <observe impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "C::observe");
  }
  inline void
  C::do_good(int i) {
  
// custom <do_good impl>
// end <do_good impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "C::do_good");
  }
  inline void
  C::do_bad(int i) {
  
// custom <do_bad impl>
// end <do_bad impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "C::do_bad");
  }



} // namespace vgroup
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_VGROUP_C_INL_H_
