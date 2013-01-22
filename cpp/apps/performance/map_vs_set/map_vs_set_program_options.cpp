/******************************************************************************
 * map_vs_set_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file map_vs_set_program_options.cpp
 *
 * \brief Which is faster, std::map< K, V > where K is embedded in V or std::set< V > with operator< a comparison on the embedded K in V
 * 
 */

#include "apps/performance/map_vs_set/map_vs_set_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <Map_vs_set_program_options pre-namespace custom>
// end <Map_vs_set_program_options pre-namespace custom>

namespace fcs {
namespace performance {

  
// custom <Map_vs_set_program_options namespace custom>
// end <Map_vs_set_program_options namespace custom>


  // Support for streaming non-static streamable members of Map_vs_set_program_options
  std::ostream& operator<<(std::ostream& out, Map_vs_set_program_options const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Map_vs_set_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  orders:" << item.orders_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description map_vs_set_options_description_s(
      "Which is faster, std::map< K, V > where K is embedded in V or std::set< V > with operator< a comparison on the embedded K in V\n"
      "\n"
      "\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_map_vs_set_options_description() {
    if(map_vs_set_options_description_s.options().empty()) {
      map_vs_set_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("orders,o", 
      value< int >()->default_value(1000000), 
      "Number of orders <int>")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ;
    }
    return map_vs_set_options_description_s;
  }

  void read_parameters(Map_vs_set_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_map_vs_set_options_description();
    store(parse_command_line(argc, argv, map_vs_set_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("orders")) {
      results.orders_ = results.parsed_program_options_["orders"].as<
        int >();
    } else {
      // orders not present, but not required
    }
    if(results.parsed_program_options_.count("log_level")) {
      results.log_level_ = results.parsed_program_options_["log_level"].as<
        int >();
    } else {
      // log_level not present, but not required
    }
  }


} // namespace performance
} // namespace fcs


