/******************************************************************************
 *
 * Copyright (c) vector.hpp by Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
#ifndef _FCS_UTILS_STREAMERS_PTR_VECTOR_HPP_
#define _FCS_UTILS_STREAMERS_PTR_VECTOR_HPP_

#include "fcs/utils/streamers/streamers.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <iosfwd>


namespace fcs {
namespace utils {
namespace streamers {

  //! Support for streaming std::vector
  template < typename T, typename ALLOC >
  inline std::ostream& operator<<(std::ostream& out, boost::ptr_vector< T, ALLOC > const& v) {
    return print_scalar_collection(out, v);
  }

}
}
}
#endif
