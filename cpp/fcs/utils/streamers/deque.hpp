/******************************************************************************
 *
 * Copyright (c) deque.hpp by Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
#ifndef _FCS_UTILS_STREAMERS_DEQUE_HPP_
#define _FCS_UTILS_STREAMERS_DEQUE_HPP_

#include "fcs/utils/streamers/streamers.hpp"
#include <iosfwd>
#include <deque>


namespace fcs {
namespace utils {
namespace streamers {

  //! Support for streaming std::deque
  template < typename T, typename ALLOC >
  inline std::ostream& operator<<(std::ostream& out, std::deque< T, ALLOC > const& d) {
    return print_scalar_collection(out, d);
  }

}
}
}
#endif
