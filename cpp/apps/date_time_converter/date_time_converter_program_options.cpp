/******************************************************************************
 * date_time_converter_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file date_time_converter_program_options.cpp
 *
 * \brief Given a date time converts to string and ticks
 * 
 */

#include "apps/date_time_converter/date_time_converter_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <Date_time_converter_program_options pre-namespace custom>
// end <Date_time_converter_program_options pre-namespace custom>

namespace fcs {
namespace app {

  
// custom <Date_time_converter_program_options namespace custom>
// end <Date_time_converter_program_options namespace custom>


  // Support for streaming non-static streamable members of Date_time_converter_program_options
  std::ostream& operator<<(std::ostream& out, Date_time_converter_program_options const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Date_time_converter_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  timestamp:" << item.timestamp_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description date_time_converter_options_description_s(
      "Given a date time converts to string and ticks\n"
      "\n"
      "\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_date_time_converter_options_description() {
    if(date_time_converter_options_description_s.options().empty()) {
      date_time_converter_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("timestamp,t", 
      value< std::vector< std::string > >(), 
      "Some form of date or timestamp <std::string>")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ;
    }
    return date_time_converter_options_description_s;
  }

  void read_parameters(Date_time_converter_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_date_time_converter_options_description();
    store(parse_command_line(argc, argv, date_time_converter_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("timestamp")) {
      results.timestamp_ = results.parsed_program_options_["timestamp"].as<
        Date_time_converter_program_options::Timestamp_list_t >();
    } else {
      // timestamp not present, but not required
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


