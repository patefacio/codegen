/******************************************************************************
 * timing_report_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file timing_report_program_options.cpp
 *
 * \brief Reports on rusage or clock timings
 * 
 */

#include "apps/timing_report/timing_report_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <Timing_report_program_options pre-namespace custom>
// end <Timing_report_program_options pre-namespace custom>

namespace fcs {
namespace app {

  
// custom <Timing_report_program_options namespace custom>
// end <Timing_report_program_options namespace custom>


  // Support for streaming non-static streamable members of Timing_report_program_options
  std::ostream& operator<<(std::ostream& out, Timing_report_program_options const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Timing_report_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  package:" << item.package_;
    out << '\n' << indent << "  location_label:" << item.location_label_;
    out << '\n' << indent << "  rusage:" << item.rusage_;
    out << '\n' << indent << "  ticks:" << item.ticks_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << '\n' << indent << "  otl_log_level:" << item.otl_log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description timing_report_options_description_s(
      "Reports on rusage or clock timings\n"
      "\n"
      " \n"
      "Given package, location, or other filters will report on timings\n"
      "\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_timing_report_options_description() {
    if(timing_report_options_description_s.options().empty()) {
      timing_report_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("package,p", 
      value< std::string >()->default_value("%"), 
      "Package to report on <std::string>")
      ("location_label,l", 
      value< std::string >()->default_value("%"), 
      "Label to report on <std::string>")
      ("rusage,r", "If true reports rusage")
      ("ticks,t", "If true reports clock ticks")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ("otl_log_level", 
      value< int >(), 
      "Number in mask {Level_1=1 (connect/disconnect), Level_2=2, Level_3=4 (selects), Level_4=8 (selects + parms), Level_5=16 (parm streaming)} <int>")
      ;
    }
    return timing_report_options_description_s;
  }

  void read_parameters(Timing_report_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_timing_report_options_description();
    store(parse_command_line(argc, argv, timing_report_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("package")) {
      results.package_ = results.parsed_program_options_["package"].as<
        std::string >();
    } else {
      // package not present, but not required
    }
    if(results.parsed_program_options_.count("location_label")) {
      results.location_label_ = results.parsed_program_options_["location_label"].as<
        std::string >();
    } else {
      // location_label not present, but not required
    }
    results.rusage_ = results.parsed_program_options_.count("rusage") > 0;
    results.ticks_ = results.parsed_program_options_.count("ticks") > 0;
    if(results.parsed_program_options_.count("log_level")) {
      results.log_level_ = results.parsed_program_options_["log_level"].as<
        int >();
    } else {
      // log_level not present, but not required
    }
    if(results.parsed_program_options_.count("otl_log_level")) {
      results.otl_log_level_ = results.parsed_program_options_["otl_log_level"].as<
        int >();
    } else {
      // otl_log_level not present, but not required
    }
  }


} // namespace app
} // namespace fcs


