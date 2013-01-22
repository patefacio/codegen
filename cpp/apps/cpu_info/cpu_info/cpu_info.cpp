/******************************************************************************
 * cpu_info.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file cpu_info.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontend.h>
#include "fcs/linux_specific/cpu_info.hpp"
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include "fcs/utils/pantheios_debug_log.hpp"
#include "apps/cpu_info/cpu_info/cpu_info_options_program_options.hpp"
#include <boost/thread/mutex.hpp>

namespace fcs {
namespace linux_specific {

  
// custom <fcs::linux_specific::cpu_info namespace custom>
// end <fcs::linux_specific::cpu_info namespace custom>

} // namespace linux_specific
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

int main(int argc, char** argv, char** envp) {

  // Get the user supplied program options
  using namespace fcs::linux_specific;
  Cpu_info_options_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_cpu_info_options_options_description();
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

  pantheios::log(PANTHEIOS_SEV_DEBUG, "app cpu_info run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  using namespace fcs::linux_specific;
  Cpu_info::Pointer_t cpu_info(Cpu_info::get_instance());
  cpu_info->dump(std::cout);

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
  return ("cpu_info");
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



