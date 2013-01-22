/******************************************************************************
 *
 * Copyright (c) map.hpp by Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
#ifndef _FCS_UTILS_STREAMERS_PTR_SET_HPP_
#define _FCS_UTILS_STREAMERS_PTR_SET_HPP_

#include "fcs/utils/streamers/streamers.hpp"
#include <boost/ptr_container/ptr_set.hpp>
#include <iosfwd>


namespace fcs {
namespace utils {
namespace streamers {

  //! Support for streaming boost::ptr_map
  template < typename K, typename V, typename PR, typename ALLOC > 
  inline std::ostream& operator<<(std::ostream& out, boost::ptr_set< K,V,PR,ALLOC > const& s) {
    return print_scalar_collection(out, s);
  }
}
}
}
#endif
