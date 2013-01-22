/******************************************************************************
 * map_vs_set.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file map_vs_set.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontends/stock.h>
#include "value_small.hpp"
#include "value_medium.hpp"
#include "value_large.hpp"
#include "apps/performance/map_vs_set/map_vs_set_program_options.hpp"

namespace fcs {
namespace performance {

  
// custom <fcs::performance::map_vs_set namespace custom>

  template < typename T > 
  std::vector< T > create_random_value_items(int num_items) {
    std::vector< T > result;
    for(size_t i(0); i<num_items; i++) {
      std::ostringstream msg;
      msg << random();
      result.emplace_back(key);
    }
    return result;
  }

  template < typename T >
  std::map< T > time_map_inserts(std::vector< T > const& items) {
    std::map< T > result;
    {
      boost::progress_timer pt;
      BOOST_FOREACH(T const& item, items) {
        result.insert(std::map< T >::value_type(item.embedded_key_, item));
      }
    }
    return result;
  }

  template < typename T >
  void run_timings(int num_items) {
    std::vector< T > items(create_random_value_items< T >(num_items));
    time_map_inserts(items);
  }

// end <fcs::performance::map_vs_set namespace custom>

} // namespace performance
} // namespace fcs

int main(int argc, char** argv, char** envp) {

  // Get the user supplied program options
  using namespace fcs::performance;
  Map_vs_set_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_map_vs_set_options_description();
      std::cout.flush();
      return 0;
    }
  } catch(std::exception const& excp) {
    std::cout << "Caught exception:" << excp.what() << std::endl;
    return -1;
  }

  if(options.parsed_program_options_.count("log_level")) {
    fcs::utils::set_log_level(options.log_level_);
  }

  pantheios::log(PANTHEIOS_SEV_DEBUG, "app map_vs_set run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  std::cout << "Running timings on small object\n";
  run_timings< Value_small >(options.orders_);

  std::cout << "Running timings on medium object\n";
  run_timings< Value_medium >(options.orders_);

  std::cout << "Running timings on large object\n";
  run_timings< Value_large >(options.orders_);

// end <main_body> 
  return 0;
}




