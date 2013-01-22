/******************************************************************************
 * performance_timers.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file performance_timers.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontend.h>
#include "fcs/orm/code_metrics/table/rusage_delta.hpp"
#include "fcs/orm/code_metrics/table/code_tick_timings.hpp"
#include "fcs/utils/performance/block_tick_tracker.hpp"
#include "fcs/utils/performance/block_performance_counter_tracker.hpp"
#include "fcs/utils/performance/block_rusage_tracker.hpp"
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include "fcs/utils/pantheios_debug_log.hpp"
#include "apps/performance/performance_timers/performance_timers_program_options.hpp"
#include <boost/thread/mutex.hpp>

namespace fcs {
namespace performance {

  
// custom <fcs::performance::performance_timers namespace custom>

  namespace platformstl_timing {
    stlsoft::platformstl_project::performance_counter counter;
    inline void call_timing_pair() {
      counter.start();
      counter.stop();
    }
  }

  namespace clock_timing {
    ticks data;
    inline void call_timing_pair() {
      data = getticks();
      data = getticks();
    }
  }

  namespace rusage_timing {
    rusage data;
    inline void call_timing_pair() {
      if(0 != getrusage(RUSAGE_THREAD, &data)) {
        throw std::runtime_error("Could not get rusage");
      }
      if(0 != getrusage(RUSAGE_THREAD, &data)) {
        throw std::runtime_error("Could not get rusage");
      }
    }
  }

// end <fcs::performance::performance_timers namespace custom>

} // namespace performance
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

int main(int argc, char** argv, char** envp) {

  // Get the user supplied program options
  using namespace fcs::performance;
  Performance_timers_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_performance_timers_options_description();
      std::cout.flush();
      return 0;
    }
  } catch(std::exception const& excp) {
    std::cout << "Caught exception:" << excp.what() << std::endl;
    return -1;
  }

  if(options.parsed_program_options_.count("log_level")) {
    fcs::utils::set_log_level(options.log_level_);
  }

  pantheios::log(PANTHEIOS_SEV_DEBUG, "app performance_timers run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  using namespace fcs::utils::performance;

  if(!(options.rusage_timing_ || options.clock_timing_ || options.platformstl_timing_)) {
    options.clock_timing_ = true;
    options.platformstl_timing_ = true;
  }

  if(options.rusage_timing_) {
    for(size_t i(0); i < 50; ++i) {
      rusage_timing::call_timing_pair();
    }
    Block_performance_counter_tracker tracker(&std::cout, "rusage", options.iterations_);
    for(int i(0); i < options.iterations_; ++i) {
      rusage_timing::call_timing_pair();
    }
  }

  if(options.clock_timing_) {
    for(size_t i(0); i < 50; ++i) {
      clock_timing::call_timing_pair();
    }
    Block_performance_counter_tracker tracker(&std::cout, "clock", options.iterations_);
    for(int i(0); i < options.iterations_; ++i) {
      clock_timing::call_timing_pair();
    }
  }

  if(options.platformstl_timing_) {
    for(size_t i(0); i < 50; ++i) {
      platformstl_timing::call_timing_pair();
    }
    Block_performance_counter_tracker tracker(&std::cout, "platformstl", options.iterations_);
    for(int i(0); i < options.iterations_; ++i) {
      platformstl_timing::call_timing_pair();
    }
  }

// end <main_body> 
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// The following pantheios related functions provide basic selective
// logging support
////////////////////////////////////////////////////////////////////////////////
PANTHEIOS_CALL(int) pantheios_fe_init(void*, void** ptoken) { 
  *ptoken = NULL; 
  return 0; 
}

PANTHEIOS_CALL(void) pantheios_fe_uninit(void*) {}

PANTHEIOS_CALL(PAN_CHAR_T const*) pantheios_fe_getProcessIdentity(void*)
{
  return ("performance_timers");
}

::pantheios::pan_sev_t app_log_severity_s(::pantheios::SEV_ERROR);

namespace fcs { 
namespace utils {

namespace {
  boost::mutex protect_severity_s;
}

  void set_log_level(::pantheios::pan_sev_t new_severity) {
    boost::mutex::scoped_lock lock(protect_severity_s);
    app_log_severity_s = new_severity;
  }
}
}

PANTHEIOS_CALL(int) pantheios_fe_isSeverityLogged(void*, int severity, int)
{
  return severity <= app_log_severity_s;
}



