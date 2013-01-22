/******************************************************************************
 * date_time_converter_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file date_time_converter_program_options.hpp
 *
 * \brief Given a date time converts to string and ticks
 * 
 */
#ifndef _FCS_APP_DATE_TIME_CONVERTER_PROGRAM_OPTIONS_H_
#define _FCS_APP_DATE_TIME_CONVERTER_PROGRAM_OPTIONS_H_

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

  //! Given a date time converts to string and ticks
  class Date_time_converter_program_options 
  {
  public:

    // Class typedefs
    typedef std::vector< std::string > Timestamp_list_t;

    Date_time_converter_program_options() :
      help_(bool()),
      timestamp_(Timestamp_list_t()),
      log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Date_time_converter_program_options const& item);

    bool help_;
    Timestamp_list_t timestamp_;
    int log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(Date_time_converter_program_options)

  boost::program_options::options_description const& get_date_time_converter_options_description();
  void read_parameters(Date_time_converter_program_options& results, int argc, char **argv);

} // namespace app
} // namespace fcs
#endif // _FCS_APP_DATE_TIME_CONVERTER_PROGRAM_OPTIONS_H_
