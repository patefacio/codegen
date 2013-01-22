/******************************************************************************
 * performance_timers_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file performance_timers_program_options.hpp
 *
 * \brief Times how long it takes to time code
 * 
 */
#ifndef _FCS_PERFORMANCE_PERFORMANCE_TIMERS_PROGRAM_OPTIONS_H_
#define _FCS_PERFORMANCE_PERFORMANCE_TIMERS_PROGRAM_OPTIONS_H_

#include "fcs/utils/debug_support.hpp"
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275 4251)
#endif
#include <boost/program_options.hpp>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <boost/cstdint.hpp>
#include <iosfwd>

namespace fcs {
namespace performance {

  //! Times how long it takes to time code
  /**

  Times over some number of iterations:
  - calling performance timer
  - calling clock tick timer
  - calling rusage timer (optional and alone)

  Then goes through the same set of timings with a few 
  different functors in between start/stop calls to the
  timers.

  */
  class Performance_timers_program_options 
  {
  public:

    Performance_timers_program_options() :
      help_(bool()),
      iterations_(boost::int64_t()),
      rusage_timing_(bool()),
      clock_timing_(bool()),
      platformstl_timing_(bool()),
      log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Performance_timers_program_options const& item);

    bool help_;
    boost::int64_t iterations_;
    bool rusage_timing_;
    bool clock_timing_;
    bool platformstl_timing_;
    int log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(Performance_timers_program_options)

  boost::program_options::options_description const& get_performance_timers_options_description();
  void read_parameters(Performance_timers_program_options& results, int argc, char **argv);

} // namespace performance
} // namespace fcs
#endif // _FCS_PERFORMANCE_PERFORMANCE_TIMERS_PROGRAM_OPTIONS_H_
