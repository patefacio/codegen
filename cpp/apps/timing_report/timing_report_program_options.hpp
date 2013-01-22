/******************************************************************************
 * timing_report_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file timing_report_program_options.hpp
 *
 * \brief Reports on rusage or clock timings
 * 
 */
#ifndef _FCS_APP_TIMING_REPORT_PROGRAM_OPTIONS_H_
#define _FCS_APP_TIMING_REPORT_PROGRAM_OPTIONS_H_

#include "fcs/utils/debug_support.hpp"
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275 4251)
#endif
#include <boost/program_options.hpp>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <string>
#include <iosfwd>

namespace fcs {
namespace app {

  //! Reports on rusage or clock timings
  /**

  Given package, location, or other filters will report on timings

  */
  class Timing_report_program_options 
  {
  public:

    Timing_report_program_options() :
      help_(bool()),
      package_(std::string()),
      location_label_(std::string()),
      rusage_(bool()),
      ticks_(bool()),
      log_level_(int()),
      otl_log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Timing_report_program_options const& item);

    bool help_;
    std::string package_;
    std::string location_label_;
    bool rusage_;
    bool ticks_;
    int log_level_;
    int otl_log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(Timing_report_program_options)

  boost::program_options::options_description const& get_timing_report_options_description();
  void read_parameters(Timing_report_program_options& results, int argc, char **argv);

} // namespace app
} // namespace fcs
#endif // _FCS_APP_TIMING_REPORT_PROGRAM_OPTIONS_H_
