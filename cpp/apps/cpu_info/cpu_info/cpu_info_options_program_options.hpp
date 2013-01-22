/******************************************************************************
 * cpu_info_options_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file cpu_info_options_program_options.hpp
 *
 * \brief Dump processor and cpu info to stdout
 * 
 */
#ifndef _FCS_LINUX_SPECIFIC_CPU_INFO_OPTIONS_PROGRAM_OPTIONS_H_
#define _FCS_LINUX_SPECIFIC_CPU_INFO_OPTIONS_PROGRAM_OPTIONS_H_

#include "fcs/utils/debug_support.hpp"
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275 4251)
#endif
#include <boost/program_options.hpp>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <iosfwd>

namespace fcs {
namespace linux_specific {

  //! Dump processor and cpu info to stdout
  class Cpu_info_options_program_options 
  {
  public:

    Cpu_info_options_program_options() :
      help_(bool()),
      log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Cpu_info_options_program_options const& item);

    bool help_;
    int log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(Cpu_info_options_program_options)

  boost::program_options::options_description const& get_cpu_info_options_options_description();
  void read_parameters(Cpu_info_options_program_options& results, int argc, char **argv);

} // namespace linux_specific
} // namespace fcs
#endif // _FCS_LINUX_SPECIFIC_CPU_INFO_OPTIONS_PROGRAM_OPTIONS_H_
