/******************************************************************************
 * lock_and_guard_traits_tbb.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file lock_and_guard_traits_tbb.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_SYNCH_LOCK_AND_GUARD_TRAITS_TBB_H_
#define _FCS_UTILS_SYNCH_LOCK_AND_GUARD_TRAITS_TBB_H_

#include "tbb/spin_mutex.h"
#include "fcs/utils/synch/lock_and_guard_traits.hpp"

namespace fcs {
namespace utils {
namespace synch {


  template <  > 
  struct Lock_and_guard_traits< tbb::spin_mutex > 
  {

    // Class typedefs
    typedef tbb::spin_mutex Lock_t;
    typedef Lock_t::scoped_lock Guard_t;

  };


  struct Tbb_spin_mutex_lock_and_guard_traits_tag :
    public Lock_and_guard_traits< tbb::spin_mutex > 
  {

  };

} // namespace synch
} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_SYNCH_LOCK_AND_GUARD_TRAITS_TBB_H_
