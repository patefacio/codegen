/******************************************************************************
 * h5_data_set_to_csv_program_options.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_data_set_to_csv_program_options.cpp
 *
 * \brief converts data_sets in hdf5 files to csv
 * 
 */

#include "apps/h5data_set2csv/h5_data_set_to_csv_program_options.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <iostream>
#include <sstream>
#include <exception>


// custom <H5_data_set_to_csv_program_options pre-namespace custom>
// end <H5_data_set_to_csv_program_options pre-namespace custom>

namespace fcs {
namespace app {
namespace h5 {

  
// custom <H5_data_set_to_csv_program_options namespace custom>
// end <H5_data_set_to_csv_program_options namespace custom>


  // Support for streaming non-static streamable members of H5_data_set_to_csv_program_options
  std::ostream& operator<<(std::ostream& out, H5_data_set_to_csv_program_options const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "H5_data_set_to_csv_program_options:(" << &item << "):{";
    out << '\n' << indent << "  help:" << item.help_;
    out << '\n' << indent << "  data_set:" << item.data_set_;
    out << '\n' << indent << "  input_file:" << item.input_file_;
    out << '\n' << indent << "  output_file:" << item.output_file_;
    out << '\n' << indent << "  log_meta_data_load:" << item.log_meta_data_load_;
    out << '\n' << indent << "  log_level:" << item.log_level_;
    out << indent << "}\n";
    return out;
  }

  using namespace boost::program_options;

  namespace {

    options_description h5_data_set_to_csv_options_description_s(
      "converts data_sets in hdf5 files to csv\n"
      "\n"
      "converts data_sets in hdf5 files to csv\n"
      "\n"
      "Allowed Options");
  }

  options_description const& get_h5_data_set_to_csv_options_description() {
    if(h5_data_set_to_csv_options_description_s.options().empty()) {
      h5_data_set_to_csv_options_description_s.add_options()
      ("help,h", "Prints this help message")
      ("data_set,d", 
      value< std::vector< std::string > >(), 
      "Name of data_set to make into csv <std::string>")
      ("input_file,i", 
      value< std::vector< std::string > >(), 
      "Name of file containing data_set(s) <std::string>")
      ("output_file,o", 
      value< std::string >(), 
      "If specified each data_set is written to {output_file}_{input_file}_{data_set}.csv else written to stdout <std::string>")
      ("log_meta_data_load,l", "If set logs extra info on meta_data load")
      ("log_level", 
      value< int >()->default_value(3), 
      "Number in (EMERGENCY=0, ALERT=1, CRITICAL=2, ERROR=3, WARNING=4, NOTICE=5, INFO=6, DEBUG=7) <int>")
      ;
    }
    return h5_data_set_to_csv_options_description_s;
  }

  void read_parameters(H5_data_set_to_csv_program_options& results, int argc, char **argv) {
    // ensure it is initialized
    get_h5_data_set_to_csv_options_description();
    store(parse_command_line(argc, argv, h5_data_set_to_csv_options_description_s), results.parsed_program_options_);
    if(results.parsed_program_options_.count("help") > 0) {
      results.help_ = true;
      return;
    }

    notify(results.parsed_program_options_);
    results.help_ = results.parsed_program_options_.count("help") > 0;
    if(results.parsed_program_options_.count("data_set")) {
      results.data_set_ = results.parsed_program_options_["data_set"].as<
        H5_data_set_to_csv_program_options::Data_set_list_t >();
    } else {
      // data_set not present, but not required
    }
    if(results.parsed_program_options_.count("input_file")) {
      results.input_file_ = results.parsed_program_options_["input_file"].as<
        H5_data_set_to_csv_program_options::Input_file_list_t >();
    } else {
      std::ostringstream msg;
      msg << "List Error: H5_data_set_to_csv_program_options option input_file is required\n"
          << get_h5_data_set_to_csv_options_description();
      throw std::runtime_error(msg.str());
    }
    if(results.parsed_program_options_.count("output_file")) {
      results.output_file_ = results.parsed_program_options_["output_file"].as<
        std::string >();
    } else {
      // output_file not present, but not required
    }
    results.log_meta_data_load_ = results.parsed_program_options_.count("log_meta_data_load") > 0;
    if(results.parsed_program_options_.count("log_level")) {
      results.log_level_ = results.parsed_program_options_["log_level"].as<
        int >();
    } else {
      // log_level not present, but not required
    }
  }


} // namespace h5
} // namespace app
} // namespace fcs


