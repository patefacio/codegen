/******************************************************************************
 * date_time_converter.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file date_time_converter.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontend.h>
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include "fcs/utils/pantheios_debug_log.hpp"
#include "apps/date_time_converter/date_time_converter_program_options.hpp"
#include <boost/foreach.hpp>
#include <boost/regex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/thread/mutex.hpp>

namespace fcs {
namespace app {

  
// custom <fcs::app::date_time_converter namespace custom>

  typedef boost::posix_time::ptime  Timestamp_t;
  typedef boost::gregorian::date Date_t;

  bool convert_to_timestamp_from_ticks(std::string const& timestamp, Timestamp_t &result) {
    boost::regex const timestamp_ticks_re("\\d+");
    try {
      if(boost::regex_match(timestamp, timestamp_ticks_re)) {
        long long ticks(boost::lexical_cast< long long >(timestamp));
        result = Timestamp_t(Timestamp_t::time_rep_type(ticks));
        pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Converted date_time from ticks:",
                       timestamp.c_str(), " to ", boost::posix_time::to_iso_string(result).c_str());
        return true;
      } else {
        pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Could not convert from ticks:",
                       timestamp.c_str(), " not a number");
      }
    } catch(std::exception const& excp) {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Could not convert from ticks:",
                     timestamp.c_str(), " excp=> ", excp.what());
    }
    return false;
  }

  bool convert_to_timestamp_from_iso(std::string const& timestamp, Timestamp_t &result) {
    boost::regex const timestamp_re("\\d+T[\\d\\.]+");
    std::string excp_text;
    if(boost::regex_match(timestamp, timestamp_re)) {    
      try {
        result = boost::posix_time::from_iso_string(timestamp);
        pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Converted date_time from iso string:",
                       timestamp.c_str(), " to ", boost::posix_time::to_iso_string(result).c_str());
        return true;
      } catch(std::exception const& excp) { 
        excp_text = excp.what();
      }
    } else {
      excp_text = "invalid format";
    }
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Could not convert from iso string:",
                   timestamp.c_str(), " excp=> ", excp_text.c_str());
    return false;
  }

  bool convert_to_date_from_undelimited_string(std::string const& timestamp, Date_t &result) {
    try {

      result = boost::gregorian::from_undelimited_string(timestamp);
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Converted date from iso string:",
                     timestamp.c_str(), " to ", boost::gregorian::to_iso_string(result).c_str());
      return true;
    } catch(std::exception const& excp) {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Could not convert date from iso string:",
                     timestamp.c_str(), " excp=> ", excp.what());
    }
    return false;
  }

  bool convert_to_date_from_julian(std::string const& timestamp, Date_t &result) {
    std::string excp_text;
    try {
      boost::regex const julian_re("\\d+");      
      if(boost::regex_match(timestamp, julian_re)) {
        Date_t d(2000, 1, 1);
        long d_julian(d.julian_day());
        long prospective_date(boost::lexical_cast< long >(timestamp));
        d += boost::gregorian::date_duration(prospective_date - d_julian);
        result = d;
        pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Converted date from julian:",
                       timestamp.c_str(), " to ", boost::gregorian::to_iso_string(result).c_str());
        return true;
      } else {
        excp_text = " does not match regex";
      }
    } catch(std::exception const& excp) {
      excp_text = excp.what();
    }
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Could not convert date from julian:",
                   timestamp.c_str(), " excp=> ", excp_text);
    return false;
  }

  bool convert_to_date_from_modjulian(std::string const& timestamp, Date_t &result) {
    std::string excp_text;
    try {
      boost::regex const modjulian_re("\\d+");      
      if(boost::regex_match(timestamp, modjulian_re)) {
        Date_t d(2000, 1, 1);
        long d_modjulian(d.modjulian_day());
        long prospective_date(boost::lexical_cast< long >(timestamp));
        d += boost::gregorian::date_duration(prospective_date - d_modjulian);
        result = d;
        pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Converted date from modjulian:",
                       timestamp.c_str(), " to ", boost::gregorian::to_iso_string(result).c_str());
        return true;
      } else {
        excp_text = " does not match regex";
      }
    } catch(std::exception const& excp) {
      excp_text = excp.what();
    }
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Could not convert date from modjulian:",
                   timestamp.c_str(), " excp=> ", excp_text);
    return false;
  }

// end <fcs::app::date_time_converter namespace custom>

} // namespace app
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

int main(int argc, char** argv, char** envp) {

  // Get the user supplied program options
  using namespace fcs::app;
  Date_time_converter_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_date_time_converter_options_description();
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

  pantheios::log(PANTHEIOS_SEV_DEBUG, "app date_time_converter run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  BOOST_FOREACH(std::string const& date_text, options.timestamp_) {
    std::cout << date_text << '\n';
    Timestamp_t timestamp;
    if(convert_to_timestamp_from_ticks(date_text, timestamp) or
       convert_to_timestamp_from_iso(date_text, timestamp)) {
      std::cout << '\t' << boost::posix_time::to_iso_string(timestamp) << '\n'
                << '\t' << timestamp << '\n';
    } else {
      Date_t date;
      if(convert_to_date_from_undelimited_string(date_text, date) or
         convert_to_date_from_julian(date_text, date) or 
         convert_to_date_from_modjulian(date_text, date)) {
        std::cout << '\t' << boost::gregorian::to_iso_string(date) << '\n'
                  << '\t' << date
                  << "\n\tjulian days:" << date.julian_day()
                  << "\n\tmodjulian days:" << date.modjulian_day()
                  << std::endl;
      } else {
        std::cout << "Could not figure out date or timestamp for " 
                  << date_text << std::endl;
      }
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
  return ("date_time_converter");
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



