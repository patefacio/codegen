/******************************************************************************
 * h5_data_set_to_csv_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_data_set_to_csv_program_options.hpp
 *
 * \brief converts data_sets in hdf5 files to csv
 * 
 */
#ifndef _FCS_APP_H5_H5_DATA_SET_TO_CSV_PROGRAM_OPTIONS_H_
#define _FCS_APP_H5_H5_DATA_SET_TO_CSV_PROGRAM_OPTIONS_H_

#include "fcs/utils/debug_support.hpp"
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275 4251)
#endif
#include <boost/program_options.hpp>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <vector>
#include <string>
#include <iosfwd>

namespace fcs {
namespace app {
namespace h5 {

  //! converts data_sets in hdf5 files to csv
  /**
  converts data_sets in hdf5 files to csv 
  */
  class H5_data_set_to_csv_program_options 
  {
  public:

    // Class typedefs
    typedef std::vector< std::string > Data_set_list_t;
    typedef std::vector< std::string > Input_file_list_t;

    H5_data_set_to_csv_program_options() :
      help_(bool()),
      data_set_(Data_set_list_t()),
      input_file_(Input_file_list_t()),
      output_file_(std::string()),
      log_meta_data_load_(bool()),
      log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, H5_data_set_to_csv_program_options const& item);

    bool help_;
    Data_set_list_t data_set_;
    Input_file_list_t input_file_;
    std::string output_file_;
    bool log_meta_data_load_;
    int log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(H5_data_set_to_csv_program_options)

  boost::program_options::options_description const& get_h5_data_set_to_csv_options_description();
  void read_parameters(H5_data_set_to_csv_program_options& results, int argc, char **argv);

} // namespace h5
} // namespace app
} // namespace fcs
#endif // _FCS_APP_H5_H5_DATA_SET_TO_CSV_PROGRAM_OPTIONS_H_
