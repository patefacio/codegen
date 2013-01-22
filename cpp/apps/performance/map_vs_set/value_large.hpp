/******************************************************************************
 * value_large.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file value_large.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_PERFORMANCE_VALUE_LARGE_H_
#define _FCS_PERFORMANCE_VALUE_LARGE_H_

#include <string>

namespace fcs {
namespace performance {

  class Value_large 
  {
  public:

    explicit Value_large(
      std::string const& embedded_key
    ) :
      embedded_key_(embedded_key),
      i_1_(0),
      i_2_(0),
      i_3_(0),
      i_4_(0),
      i_5_(0),
      i_6_(0),
      i_7_(0),
      i_8_(0),
      i_9_(0),
      i_10_(0),
      i_11_(0),
      i_12_(0),
      i_13_(0),
      i_14_(0),
      i_15_(0),
      i_16_(0),
      i_17_(0),
      i_18_(0),
      i_19_(0),
      i_20_(0),
      d_1_(0.0),
      d_2_(0.0),
      d_3_(0.0),
      d_4_(0.0),
      d_5_(0.0),
      d_6_(0.0),
      d_7_(0.0),
      d_8_(0.0),
      d_9_(0.0),
      d_10_(0.0),
      d_11_(0.0),
      d_12_(0.0),
      d_13_(0.0),
      d_14_(0.0),
      d_15_(0.0),
      d_16_(0.0),
      d_17_(0.0),
      d_18_(0.0),
      d_19_(0.0),
      d_20_(0.0)
    {
    }

  private:
    std::string embedded_key_;
    int i_1_;
    int i_2_;
    int i_3_;
    int i_4_;
    int i_5_;
    int i_6_;
    int i_7_;
    int i_8_;
    int i_9_;
    int i_10_;
    int i_11_;
    int i_12_;
    int i_13_;
    int i_14_;
    int i_15_;
    int i_16_;
    int i_17_;
    int i_18_;
    int i_19_;
    int i_20_;
    double d_1_;
    double d_2_;
    double d_3_;
    double d_4_;
    double d_5_;
    double d_6_;
    double d_7_;
    double d_8_;
    double d_9_;
    double d_10_;
    double d_11_;
    double d_12_;
    double d_13_;
    double d_14_;
    double d_15_;
    double d_16_;
    double d_17_;
    double d_18_;
    double d_19_;
    double d_20_;
  };

} // namespace performance
} // namespace fcs
#endif // _FCS_PERFORMANCE_VALUE_LARGE_H_
