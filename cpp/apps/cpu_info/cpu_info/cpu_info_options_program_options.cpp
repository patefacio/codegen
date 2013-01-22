/******************************************************************************
 * cpu_info_options_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file cpu_info_options_program_options.cpp
 *
 * \brief Dump processor and cpu info to stdout
 * 
 */

#include "apps/cpu_info/cpu_info/cpu_info_options_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <Cpu_info_options_program_options pre-namespace custom>
// end <Cpu_info_options_program_options pre-namespace custom>

namespace fcs {
namespace linux_specific {

  
// custom <Cpu_info_options_program_options namespace custom>
// end <Cpu_info_options_program_options namespace custom>


  // Support for streaming non-static streamable members of Cpu_info_options_program_options
  std::ostream& operator<<(std::ostream& out, Cpu_info_options_program_options const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Cpu_info_options_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description cpu_info_options_options_description_s(
      "Dump processor and cpu info to stdout\n"
      "\n"
      "\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_cpu_info_options_options_description() {
    if(cpu_info_options_options_description_s.options().empty()) {
      cpu_info_options_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ;
    }
    return cpu_info_options_options_description_s;
  }

  void read_parameters(Cpu_info_options_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_cpu_info_options_options_description();
    store(parse_command_line(argc, argv, cpu_info_options_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("log_level")) {
      results.log_level_ = results.parsed_program_options_["log_level"].as<
        int >();
    } else {
      // log_level not present, but not required
    }
  }


} // namespace linux_specific
} // namespace fcs


