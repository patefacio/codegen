/******************************************************************************
 * map_vs_set_program_options.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file map_vs_set_program_options.hpp
 *
 * \brief Which is faster, std::map< K, V > where K is embedded in V or std::set< V > with operator< a comparison on the embedded K in V
 * 
 */
#ifndef _FCS_PERFORMANCE_MAP_VS_SET_PROGRAM_OPTIONS_H_
#define _FCS_PERFORMANCE_MAP_VS_SET_PROGRAM_OPTIONS_H_

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
namespace performance {

  //! Which is faster, std::map< K, V > where K is embedded in V or std::set< V > with operator< a comparison on the embedded K in V
  class Map_vs_set_program_options 
  {
  public:

    Map_vs_set_program_options() :
      help_(bool()),
      orders_(int()),
      log_level_(int()),
      parsed_program_options_(boost::program_options::variables_map()) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Map_vs_set_program_options const& item);

    bool help_;
    int orders_;
    int log_level_;
    //! allows access to program_options that were parsed <I>open</I>
    boost::program_options::variables_map parsed_program_options_;

    DEBUG_DUMP_METHOD()
  };

  DEFINE_DEBUG_DUMP(Map_vs_set_program_options)

  boost::program_options::options_description const& get_map_vs_set_options_description();
  void read_parameters(Map_vs_set_program_options& results, int argc, char **argv);

} // namespace performance
} // namespace fcs
#endif // _FCS_PERFORMANCE_MAP_VS_SET_PROGRAM_OPTIONS_H_
