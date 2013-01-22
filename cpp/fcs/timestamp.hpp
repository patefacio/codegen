/******************************************************************************
 * timestamp.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file timestamp.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_TIMESTAMP_TIMESTAMP_H_
#define _FCS_TIMESTAMP_TIMESTAMP_H_

#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/local_time_adjustor.hpp>

namespace fcs {
namespace timestamp {

  // Library typedefs
  typedef boost::posix_time::ptime Timestamp_t;
  typedef boost::posix_time::time_duration Time_duration_t;


// custom <timestamp namespace end section>

  inline 
  Timestamp_t current_time() {
    return boost::posix_time::microsec_clock::universal_time();
  }

  inline
  Timestamp_t utc_to_local_time(Timestamp_t t) {
    typedef boost::date_time::c_local_adjustor< boost::posix_time::ptime > local_adj;
    return local_adj::utc_to_local(t);
  }

  inline 
  Time_duration_t::tick_type ticks(Timestamp_t t) {
    Timestamp_t const zero(Timestamp_t::time_rep_type(0LL));  
    return (t - zero).ticks();
  }

// end <timestamp namespace end section>
} // namespace timestamp
} // namespace fcs
#endif // _FCS_TIMESTAMP_TIMESTAMP_H_
