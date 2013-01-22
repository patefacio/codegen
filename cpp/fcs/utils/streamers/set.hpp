/******************************************************************************
 *
 * Copyright (c) set.hpp by Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
#ifndef _FCS_UTILS_STREAMERS_SET_HPP_
#define _FCS_UTILS_STREAMERS_SET_HPP_

#include "fcs/utils/streamers/streamers.hpp"
#include <iosfwd>
#include <set>


namespace fcs {
namespace utils {
namespace streamers {

  //! Support for streaming std::list
  template < typename T, typename PR, typename ALLOC > 
  inline std::ostream& operator<<(std::ostream& out, std::set< T, PR, ALLOC > const& l) {
    return print_scalar_collection(out, l);
  }

}
}
}
#endif
