/******************************************************************************
 * timing_report.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file timing_report.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontend.h>
#include "fcs/orm/code_metrics/table/rusage_delta.hpp"
#include "fcs/orm/code_metrics/table/code_tick_timings.hpp"
#include "fcs/orm/code_metrics/query/rusage_delta_by_package_label.hpp"
#include "fcs/orm/code_metrics/query/code_tick_timings_by_package_label.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/utils/streamers/table/table.hpp"
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include "fcs/utils/pantheios_debug_log.hpp"
#include "apps/timing_report/timing_report_program_options.hpp"
#include <boost/foreach.hpp>
#include <boost/thread/mutex.hpp>

namespace fcs {
namespace app {

  
// custom <fcs::app::timing_report namespace custom>
// end <fcs::app::timing_report namespace custom>

} // namespace app
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

int main(int argc, char** argv, char** envp) {

  // Get the user supplied program options
  using namespace fcs::app;
  Timing_report_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_timing_report_options_description();
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
  if(options.parsed_program_options_.count("otl_log_level")) {
    fcs::orm::set_otl_log_level(options.otl_log_level_);
  }

  pantheios::log(PANTHEIOS_SEV_DEBUG, "app timing_report run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  using namespace fcs::orm::code_metrics::query;
  using namespace fcs::orm::code_metrics::table;
  using namespace fcs::orm;

  using fcs::utils::streamers::operator<<;
  if(!options.rusage_ && !options.ticks_) {
    options.rusage_ = options.ticks_ = true;
  }

  if(options.rusage_) {
    Rusage_delta_by_package_label_query 
      query(options.package_.c_str(), options.location_label_);
    query.print_query_results_as_table(std::cout);
  }

  if(options.ticks_) {
    Code_tick_timings_by_package_label_query 
      query(options.package_.c_str(), options.location_label_.c_str());
    query.print_query_results_as_table(std::cout);
  }

#if 0
  {
    using namespace fcs::orm::system;
    Connection_system::Pointer_t connection(Connection_system::get_instance());
    otl_stream stream(1, "select name from vendors where name in (select \"a\" as strings  union select \"Intel\"  union select \"Cisco\"  union select \"wow\" )", *connection->get_connection());
    while(!stream.eof()) {
      fcs::utils::Fixed_size_char_array< 32 > name;
      stream >> name;
      std::cout << "Found name:" << name << std::endl;
    }
  }

#endif

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
  return ("timing_report");
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



