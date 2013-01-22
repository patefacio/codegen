/******************************************************************************
 * value_small.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file value_small.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_PERFORMANCE_VALUE_SMALL_H_
#define _FCS_PERFORMANCE_VALUE_SMALL_H_

#include <string>

namespace fcs {
namespace performance {

  class Value_small 
  {
  public:

    explicit Value_small(
      std::string const& embedded_key
    ) :
      embedded_key_(embedded_key)
    {
    }

  private:
    std::string embedded_key_;
  };

} // namespace performance
} // namespace fcs
#endif // _FCS_PERFORMANCE_VALUE_SMALL_H_
