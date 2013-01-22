/******************************************************************************
 * a_inl.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file a_inl.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_VGROUP_A_INL_H_
#define _FCS_EXAMPLES_VGROUP_A_INL_H_

#include <pantheios/pantheios.hpp>
#include "fcs/examples/vgroup/a.hpp"

namespace fcs {
namespace examples {
namespace vgroup {
  inline void
  A::observe(int i, char const * s) {
  
// custom <observe impl>

    total_chars_observed_ = strlen(s) + a1_.size() + a2_.size();

// end <observe impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "A::observe");
  }
  inline void
  A::do_good(int i) {
  
// custom <do_good impl>

    sum_log_do_good_ += log(i);
    sum_rand_log_do_good_ += log(rand());

// end <do_good impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "A::do_good");
  }
  inline void
  A::do_bad(int i) {
  
// custom <do_bad impl>

    sum_log_do_bad_ += log(i);
    sum_rand_log_do_bad_ += log(rand());

// end <do_bad impl>
    pantheios::log(PANTHEIOS_SEV_DEBUG, "A::do_bad");
  }



} // namespace vgroup
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_VGROUP_A_INL_H_
