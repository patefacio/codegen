/******************************************************************************
 * block_tick_tracker.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file block_tick_tracker.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_PERFORMANCE_BLOCK_TICK_TRACKER_H_
#define _FCS_UTILS_PERFORMANCE_BLOCK_TICK_TRACKER_H_

#include "fcs/linux_specific/cpu_info.hpp"
#include "cycle.h"
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

namespace fcs {
namespace utils {
namespace performance {

  class Block_tick_tracker 
  {
  public:

    explicit Block_tick_tracker(
      std::ostream * outstream = &std::cout,
      char const * stream_label = 0,
      ticks * saved_tick_count = 0,
      boost::int64_t iteration_count = 0
    ) :
      outstream_(outstream),
      stream_label_(stream_label),
      saved_tick_count_(saved_tick_count),
      iteration_count_(iteration_count),
      initial_ticks_(0),
      final_ticks_(0)
    {
      ctor_member_init();
    }

  
// custom <Block_tick_tracker public header section>

    ~Block_tick_tracker() {
      final_ticks_ = getticks();
      ticks delta_ticks(final_ticks_ - initial_ticks_);
      if(outstream_) {

        fcs::linux_specific::Cpu_info::Processor_list_t const& 
          processors(fcs::linux_specific::Cpu_info::get_instance()->processors());

        int processor(sched_getcpu());
        double cpu_mhz(0);
        if(processor >= 0) {
          cpu_mhz = boost::lexical_cast< double >(processors.at(processor).cpu_mhz());
        } else {
          throw std::runtime_error("Could not get processor using sched_getcpu");
        }

        *outstream_ << (stream_label_? stream_label_ : "Block tick tracker:")
                    << "\n\tinitial ticks:         " << initial_ticks_
                    << "\n\tfinal ticks:           " << final_ticks_
                    << "\n\telapsed ns:            " <<  elapsed(final_ticks_, initial_ticks_)
                    << "\n\telapsed norm ns:       " <<  elapsed(final_ticks_, initial_ticks_)/cpu_mhz << '\n';
        if(iteration_count_) {
          *outstream_ << "\titeration_count:       " << iteration_count_
                      << "\n\tcpu_mhz:               " << cpu_mhz
                      << "\n\tavg elapsed ns:        " 
                      << double(elapsed(final_ticks_, initial_ticks_))/iteration_count_
                      << "\n\tavg elapsed norm ns:   " 
                      << double(elapsed(final_ticks_, initial_ticks_))/(iteration_count_ * cpu_mhz) 
                      << "\n";
        }
      }

      if(saved_tick_count_) {
        *saved_tick_count_ = delta_ticks;
      }
    }

// end <Block_tick_tracker public header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <Block_tick_tracker::init>

      initial_ticks_ = getticks();

// end <Block_tick_tracker::init>
    }
    std::ostream * outstream_;
    char const * stream_label_;
    ticks * saved_tick_count_;
    boost::int64_t iteration_count_;
    ticks initial_ticks_;
    ticks final_ticks_;
  };

} // namespace performance
} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_PERFORMANCE_BLOCK_TICK_TRACKER_H_
