/******************************************************************************
 * block_performance_counter_tracker.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file block_performance_counter_tracker.hpp
 *
 * \brief Block timer that uses stlsoft performance counter
 * 
 */
#ifndef _FCS_UTILS_PERFORMANCE_BLOCK_PERFORMANCE_COUNTER_TRACKER_H_
#define _FCS_UTILS_PERFORMANCE_BLOCK_PERFORMANCE_COUNTER_TRACKER_H_

#include "platformstl/performance/performance_counter.hpp"
#include <boost/cstdint.hpp>
#include <iostream>

namespace fcs {
namespace utils {
namespace performance {

  //! Block timer that uses stlsoft performance counter
  class Block_performance_counter_tracker 
  {
  public:

    explicit Block_performance_counter_tracker(
      std::ostream * outstream = &std::cout,
      char const * stream_label = 0,
      boost::int64_t iteration_count = 0
    ) :
      outstream_(outstream),
      stream_label_(stream_label),
      iteration_count_(iteration_count),
      performance_counter_()
    {
      ctor_member_init();
    }

  
// custom <Block_performance_counter_tracker public header section>

    ~Block_performance_counter_tracker() {
      performance_counter_.stop();
      if(outstream_) {
        *outstream_ << (stream_label_? stream_label_ : "Block performance_counter tracker:")
                    << "\n\tmicros:      " << performance_counter_.get_microseconds() << "\n";
        if(iteration_count_) {
          *outstream_ << "\titerations:  " << iteration_count_
                      << "\n\tavg micros:  " << double(performance_counter_.get_microseconds())/double(iteration_count_)
                      << "\n";
        }
      }
    }

// end <Block_performance_counter_tracker public header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <Block_performance_counter_tracker::init>

      performance_counter_.start();      

// end <Block_performance_counter_tracker::init>
    }
    std::ostream * outstream_;
    char const * stream_label_;
    boost::int64_t iteration_count_;
    stlsoft::platformstl_project::performance_counter performance_counter_;
  };

} // namespace performance
} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_PERFORMANCE_BLOCK_PERFORMANCE_COUNTER_TRACKER_H_
