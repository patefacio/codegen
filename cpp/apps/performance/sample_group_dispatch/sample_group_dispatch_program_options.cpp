/******************************************************************************
 * sample_group_dispatch_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file sample_group_dispatch_program_options.cpp
 *
 * \brief Dispatch with simple jump table and void* allowing inline
 * 
 */

#include "apps/performance/sample_group_dispatch/sample_group_dispatch_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <sample_group_dispatch_program_options pre-namespace custom>
// end <sample_group_dispatch_program_options pre-namespace custom>

namespace fcs {
namespace examples {

  
// custom <sample_group_dispatch_program_options namespace custom>
// end <sample_group_dispatch_program_options namespace custom>


  // Support for streaming non-static streamable members of sample_group_dispatch_program_options
  std::ostream& operator<<(std::ostream& out, sample_group_dispatch_program_options const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "sample_group_dispatch_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  iterations:" << item.iterations_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description sample_group_dispatch_options_description_s(
      "Dispatch with simple jump table and void* allowing inline\n"
      "\n"
      "\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_sample_group_dispatch_options_description() {
    if(sample_group_dispatch_options_description_s.options().empty()) {
      sample_group_dispatch_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("iterations,i", 
      value< int >()->default_value(1000000), 
      "Number of iterations on the loop <int>")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ;
    }
    return sample_group_dispatch_options_description_s;
  }

  void read_parameters(sample_group_dispatch_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_sample_group_dispatch_options_description();
    store(parse_command_line(argc, argv, sample_group_dispatch_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("iterations")) {
      results.iterations_ = results.parsed_program_options_["iterations"].as<
        int >();
    } else {
      // iterations not present, but not required
    }
    if(results.parsed_program_options_.count("log_level")) {
      results.log_level_ = results.parsed_program_options_["log_level"].as<
        int >();
    } else {
      // log_level not present, but not required
    }
  }


} // namespace examples
} // namespace fcs


