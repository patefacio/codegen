/******************************************************************************
 * display_csv_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file display_csv_program_options.cpp
 *
 * \brief Wraps a model on a csv for display in Qt
 * 
 */

#include "apps/display_csv/display_csv_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <Display_csv_program_options pre-namespace custom>
// end <Display_csv_program_options pre-namespace custom>

namespace fcs {
namespace app {

  
// custom <Display_csv_program_options namespace custom>
// end <Display_csv_program_options namespace custom>


  // Support for streaming non-static streamable members of Display_csv_program_options
  std::ostream& operator<<(std::ostream& out, Display_csv_program_options const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Display_csv_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  csv_file:" << item.csv_file_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description display_csv_options_description_s(
      "Wraps a model on a csv for display in Qt\n"
      "\n"
      " \n"
      "Takes one or more csv files and for each wraps a view on it.\n"
      "\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_display_csv_options_description() {
    if(display_csv_options_description_s.options().empty()) {
      display_csv_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("csv_file,c", 
      value< std::vector< std::string > >(), 
      "Csv file path(s) to open <std::string>")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ;
    }
    return display_csv_options_description_s;
  }

  void read_parameters(Display_csv_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_display_csv_options_description();
    store(parse_command_line(argc, argv, display_csv_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("csv_file")) {
      results.csv_file_ = results.parsed_program_options_["csv_file"].as<
        Display_csv_program_options::Csv_file_list_t >();
    } else {
      // csv_file not present, but not required
    }
    if(results.parsed_program_options_.count("log_level")) {
      results.log_level_ = results.parsed_program_options_["log_level"].as<
        int >();
    } else {
      // log_level not present, but not required
    }
  }


} // namespace app
} // namespace fcs


