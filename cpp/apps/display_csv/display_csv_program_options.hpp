/******************************************************************************
 * display_csv_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file display_csv_program_options.hpp
 *
 * \brief Wraps a model on a csv for display in Qt
 * 
 */
#ifndef _FCS_APP_DISPLAY_CSV_PROGRAM_OPTIONS_H_
#define _FCS_APP_DISPLAY_CSV_PROGRAM_OPTIONS_H_

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

  //! Wraps a model on a csv for display in Qt
  /**

  Takes one or more csv files and for each wraps a view on it.

  */
  class Display_csv_program_options 
  {
  public:

    // Class typedefs
    typedef std::vector< std::string > Csv_file_list_t;

    Display_csv_program_options() :
      help_(bool()),
      csv_file_(Csv_file_list_t()),
      log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Display_csv_program_options const& item);

    bool help_;
    Csv_file_list_t csv_file_;
    int log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(Display_csv_program_options)

  boost::program_options::options_description const& get_display_csv_options_description();
  void read_parameters(Display_csv_program_options& results, int argc, char **argv);

} // namespace app
} // namespace fcs
#endif // _FCS_APP_DISPLAY_CSV_PROGRAM_OPTIONS_H_
