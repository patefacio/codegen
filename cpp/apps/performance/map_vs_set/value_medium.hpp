/******************************************************************************
 * value_medium.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file value_medium.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_PERFORMANCE_VALUE_MEDIUM_H_
#define _FCS_PERFORMANCE_VALUE_MEDIUM_H_

#include <string>

namespace fcs {
namespace performance {

  class Value_medium 
  {
  public:

    explicit Value_medium(
      std::string const& embedded_key
    ) :
      embedded_key_(embedded_key),
      i1_(),
      d1_(),
      d2_(),
      i2_()
    {
    }

  private:
    std::string embedded_key_;
    int i1_;
    double d1_;
    double d2_;
    int i2_;
  };

} // namespace performance
} // namespace fcs
#endif // _FCS_PERFORMANCE_VALUE_MEDIUM_H_
