/******************************************************************************
 * block_rusage_tracker.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file block_rusage_tracker.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_PERFORMANCE_BLOCK_RUSAGE_TRACKER_H_
#define _FCS_UTILS_PERFORMANCE_BLOCK_RUSAGE_TRACKER_H_

#include "fcs/utils/block_indenter.hpp"
#include <boost/cstdint.hpp>
#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>


// custom <Block_rusage_tracker global header section>

inline
std::ostream& operator<<(std::ostream& out, rusage const& item) {
  fcs::utils::Block_indenter indenter;
  char const* indent(indenter.current_indentation_text());
  out << '\n' << indent << " total time:" << item.ru_utime.tv_sec << "(s) " << item.ru_utime.tv_usec << "(micro)";
  out << '\n' << indent << " maximum resident set size:" << item.ru_maxrss;       
  out << '\n' << indent << " integral shared memory size:" << item.ru_ixrss;        
  out << '\n' << indent << " integral unshared data size:" << item.ru_idrss;        
  out << '\n' << indent << " integral unshared stack size:" << item.ru_isrss;        
  out << '\n' << indent << " page reclaims:" << item.ru_minflt;       
  out << '\n' << indent << " page faults:" << item.ru_majflt;       
  out << '\n' << indent << " swaps:" << item.ru_nswap;        
  out << '\n' << indent << " block input operations:" << item.ru_inblock;      
  out << '\n' << indent << " block output operations:" << item.ru_oublock;      
  out << '\n' << indent << " messages sent:" << item.ru_msgsnd;       
  out << '\n' << indent << " messages received:" << item.ru_msgrcv;       
  out << '\n' << indent << " signals received:" << item.ru_nsignals;     
  out << '\n' << indent << " voluntary context switches:" << item.ru_nvcsw;        
  out << '\n' << indent << " involuntary context switches:" << item.ru_nivcsw;       
  return out;
}

// end <Block_rusage_tracker global header section>
namespace fcs {
namespace utils {
namespace performance {

  class Block_rusage_tracker 
  {
  public:

    explicit Block_rusage_tracker(
      std::ostream * outstream = &std::cout,
      char const * stream_label = 0,
      rusage * const& saved_rusage_delta = 0,
      boost::int64_t iteration_count = 0
    ) :
      initial_rusage_(),
      final_rusage_(),
      delta_rusage_(),
      outstream_(outstream),
      stream_label_(stream_label),
      saved_rusage_delta_(saved_rusage_delta),
      iteration_count_(iteration_count)
    {
      ctor_member_init();
    }

    friend std::ostream& operator<<(std::ostream& out, Block_rusage_tracker const& item);

  
// custom <Block_rusage_tracker public header section>

    void snapshot_delta() {
      int rc(0);
      if(0 != (rc = getrusage(RUSAGE_THREAD, &final_rusage_))) {
        std::ostringstream msg;
        msg << "Unable to track rusage - rc:" << rc << " errno:" << errno << std::endl;
        throw std::runtime_error(msg.str());
      } else {
        delta_rusage_.ru_utime.tv_sec = final_rusage_.ru_utime.tv_sec - initial_rusage_.ru_utime.tv_sec;
        delta_rusage_.ru_utime.tv_usec = final_rusage_.ru_utime.tv_usec - initial_rusage_.ru_utime.tv_usec;
        delta_rusage_.ru_stime.tv_sec = final_rusage_.ru_stime.tv_sec - initial_rusage_.ru_stime.tv_sec;
        delta_rusage_.ru_stime.tv_usec = final_rusage_.ru_stime.tv_usec - initial_rusage_.ru_stime.tv_usec;
        delta_rusage_.ru_maxrss = final_rusage_.ru_maxrss - initial_rusage_.ru_maxrss;
        delta_rusage_.ru_ixrss = final_rusage_.ru_ixrss - initial_rusage_.ru_ixrss;
        delta_rusage_.ru_idrss = final_rusage_.ru_idrss - initial_rusage_.ru_idrss;
        delta_rusage_.ru_isrss = final_rusage_.ru_isrss - initial_rusage_.ru_isrss;
        delta_rusage_.ru_minflt = final_rusage_.ru_minflt - initial_rusage_.ru_minflt;
        delta_rusage_.ru_majflt = final_rusage_.ru_majflt - initial_rusage_.ru_majflt;
        delta_rusage_.ru_nswap = final_rusage_.ru_nswap - initial_rusage_.ru_nswap;
        delta_rusage_.ru_inblock = final_rusage_.ru_inblock - initial_rusage_.ru_inblock;
        delta_rusage_.ru_oublock = final_rusage_.ru_oublock - initial_rusage_.ru_oublock;
        delta_rusage_.ru_msgsnd = final_rusage_.ru_msgsnd - initial_rusage_.ru_msgsnd;
        delta_rusage_.ru_msgrcv = final_rusage_.ru_msgrcv - initial_rusage_.ru_msgrcv;
        delta_rusage_.ru_nsignals = final_rusage_.ru_nsignals - initial_rusage_.ru_nsignals;
        delta_rusage_.ru_nvcsw = final_rusage_.ru_nvcsw - initial_rusage_.ru_nvcsw;
        delta_rusage_.ru_nivcsw = final_rusage_.ru_nivcsw - initial_rusage_.ru_nivcsw;

        if(saved_rusage_delta_) {
          *saved_rusage_delta_ = delta_rusage_;
        }

        if(outstream_) {
          *outstream_ << (stream_label_? stream_label_ : "Block rusage tracker:") 
                      << '\n' << *this << '\n';
        }
      }
    }

    ~Block_rusage_tracker() {
      snapshot_delta();
    }

// end <Block_rusage_tracker public header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <Block_rusage_tracker::init>

      int rc(0);
      if(0 != (rc = getrusage(RUSAGE_THREAD, &initial_rusage_))) {
        std::ostringstream msg;
        msg << "Unable to track rusage - rc:" << rc << " errno:" << errno << std::endl;
        throw std::runtime_error(msg.str());
      }

// end <Block_rusage_tracker::init>
    }
    rusage initial_rusage_;
    rusage final_rusage_;
    rusage delta_rusage_;
    std::ostream * outstream_;
    char const * stream_label_;
    rusage * saved_rusage_delta_;
    boost::int64_t iteration_count_;
  };

  // Support for streaming non-static streamable members of Block_rusage_tracker
  inline
  std::ostream& operator<<(std::ostream& out, Block_rusage_tracker const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Block_rusage_tracker:(" << &item << "):{";
    out << '\n' << indent << "  initial_rusage:" << item.initial_rusage_;
    out << '\n' << indent << "  final_rusage:" << item.final_rusage_;
    out << '\n' << indent << "  delta_rusage:" << item.delta_rusage_;
    out << '\n' << indent << "  iteration_count:" << item.iteration_count_;
    out << indent << "}\n";
    return out;
  } 

} // namespace performance
} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_PERFORMANCE_BLOCK_RUSAGE_TRACKER_H_
