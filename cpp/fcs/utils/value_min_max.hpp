/******************************************************************************
 * value_min_max.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file value_min_max.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_VALUE_MIN_MAX_H_
#define _FCS_UTILS_VALUE_MIN_MAX_H_

#include <boost/call_traits.hpp>
#include <limits>

namespace fcs {
namespace utils {

  template < typename T > 
  struct Value_min_max 
  {

    // Class typedefs
    typedef typename boost::call_traits< T >::param_type Param_type;

    Value_min_max() :
      min_value_(std::numeric_limits< T >::max()),
      max_value_(std::numeric_limits< T >::min()) 
    {
    }

  
// custom <Value_min_max public header section>

    void operator()(Param_type update) {
      if(update < min_value_) {
        min_value_ = update;
      } else if(update > max_value_) {
        max_value_ = update;
      }
    }

// end <Value_min_max public header section>

    T min_value_;
    T max_value_;
  };

} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_VALUE_MIN_MAX_H_
