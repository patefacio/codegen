/******************************************************************************
 * sample_group_vdispatch_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file sample_group_vdispatch_program_options.hpp
 *
 * \brief Dispatch with simple jump table and void* allowing inline
 * 
 */
#ifndef _FCS_EXAMPLES_SAMPLE_GROUP_VDISPATCH_PROGRAM_OPTIONS_H_
#define _FCS_EXAMPLES_SAMPLE_GROUP_VDISPATCH_PROGRAM_OPTIONS_H_

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
namespace examples {

  //! Dispatch with simple jump table and void* allowing inline
  class sample_group_vdispatch_program_options 
  {
  public:

    sample_group_vdispatch_program_options() :
      help_(bool()),
      iterations_(int()),
      log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, sample_group_vdispatch_program_options const& item);

    bool help_;
    int iterations_;
    int log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(sample_group_vdispatch_program_options)

  boost::program_options::options_description const& get_sample_group_vdispatch_options_description();
  void read_parameters(sample_group_vdispatch_program_options& results, int argc, char **argv);

} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_SAMPLE_GROUP_VDISPATCH_PROGRAM_OPTIONS_H_
