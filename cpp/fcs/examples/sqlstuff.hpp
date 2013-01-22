/******************************************************************************
 * sqlstuff.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file sqlstuff.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_SQLSTUFF_H_
#define _FCS_EXAMPLES_SQLSTUFF_H_

#include "fcs/examples/apiheader.hpp"
#include <iso646.h>

namespace fcs {
namespace examples {

  /**

  Example of formulas:
   The distance between \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$ is 
    \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$.

   Here is an example of inserting a mathematical formula into the text:
   If we wanted to insert the formula centered on a separate line:
   \f$
   \sqrt{ (x_2-x_1)^2 + (y_2 - y_1)^2 }
   \f$

  And even more complex:

    \f[
      |I_2|=\left| \int_{0}^T \psi(t) 
               \left\{ 
                  u(a,t)-
                  \int_{\gamma(t)}^a 
                  \frac{d\theta}{k(\theta,t)}
                  \int_{a}^\theta c(\xi)u_t(\xi,t)\,d\xi
               \right\} dt
            \right|
    \f]

  */
  class sqlstuff :
    private boost::noncopyable 
  {
  public:

    bool operator<(sqlstuff const& rhs) const {
        return
            ((year_ != rhs.year_)? year_ < rhs.year_ : (
            ((month_ != rhs.month_)? month_ < rhs.month_ : (
            ((day_ != rhs.day_)? day_ < rhs.day_ : (
            ((hour_ != rhs.hour_)? hour_ < rhs.hour_ : (
            ((minute_ != rhs.minute_)? minute_ < rhs.minute_ : (
            ((second_ != rhs.second_)? second_ < rhs.second_ : (
            ((fraction_ != rhs.fraction_)? fraction_ < rhs.fraction_ : (false
            ))))))))))))));
    }

    bool operator==(sqlstuff const& rhs) const {
        return
            ((this==&rhs) or (
            (year_ == rhs.year_) and
            (month_ == rhs.month_) and
            (day_ == rhs.day_) and
            (hour_ == rhs.hour_) and
            (minute_ == rhs.minute_) and
            (second_ == rhs.second_) and
            (fraction_ == rhs.fraction_)));
    }

  private:
    int year_;
    int month_;
    int day_;
    int hour_;
    int minute_;
    int second_;
    int fraction_;
  };

} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_SQLSTUFF_H_
