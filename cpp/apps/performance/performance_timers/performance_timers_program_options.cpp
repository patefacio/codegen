/******************************************************************************
 * performance_timers_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file performance_timers_program_options.cpp
 *
 * \brief Times how long it takes to time code
 * 
 */

#include "apps/performance/performance_timers/performance_timers_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <Performance_timers_program_options pre-namespace custom>
// end <Performance_timers_program_options pre-namespace custom>

namespace fcs {
namespace performance {

  
// custom <Performance_timers_program_options namespace custom>
// end <Performance_timers_program_options namespace custom>


  // Support for streaming non-static streamable members of Performance_timers_program_options
  std::ostream& operator<<(std::ostream& out, Performance_timers_program_options const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Performance_timers_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  iterations:" << item.iterations_;
    out << '\n' << indent << "  rusage_timing:" << item.rusage_timing_;
    out << '\n' << indent << "  clock_timing:" << item.clock_timing_;
    out << '\n' << indent << "  platformstl_timing:" << item.platformstl_timing_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description performance_timers_options_description_s(
      "Times how long it takes to time code\n"
      "\n"
      " \n"
      "Times over some number of iterations:\n"
      "- calling performance timer\n"
      "- calling clock tick timer\n"
      "- calling rusage timer (optional and alone)\n"
      "\n"
      "Then goes through the same set of timings with a few \n"
      "different functors in between start/stop calls to the\n"
      "timers.\n"
      "\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_performance_timers_options_description() {
    if(performance_timers_options_description_s.options().empty()) {
      performance_timers_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("iterations,i", 
      value< boost::int64_t >()->default_value(1LL<<23), 
      "How many iterations <boost::int64_t>")
      ("rusage_timing,r", "If true times rusage timer")
      ("clock_timing,c", "If true times clock timer")
      ("platformstl_timing,p", "If true times platformstl_timing")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ;
    }
    return performance_timers_options_description_s;
  }

  void read_parameters(Performance_timers_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_performance_timers_options_description();
    store(parse_command_line(argc, argv, performance_timers_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("iterations")) {
      results.iterations_ = results.parsed_program_options_["iterations"].as<
        boost::int64_t >();
    } else {
      // iterations not present, but not required
    }
    results.rusage_timing_ = results.parsed_program_options_.count("rusage_timing") > 0;
    results.clock_timing_ = results.parsed_program_options_.count("clock_timing") > 0;
    results.platformstl_timing_ = results.parsed_program_options_.count("platformstl_timing") > 0;
    if(results.parsed_program_options_.count("log_level")) {
      results.log_level_ = results.parsed_program_options_["log_level"].as<
        int >();
    } else {
      // log_level not present, but not required
    }
  }


} // namespace performance
} // namespace fcs


