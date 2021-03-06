/******************************************************************************
 * sample_group_vdispatch.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file sample_group_vdispatch.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontend.h>
#include "fcs/utils/streamers/vector.hpp"
#include "fcs/sample/vgroup/one_ring_base.hpp"
#include "fcs/sample/vgroup/a_inl.hpp"
#include "fcs/sample/vgroup/b_inl.hpp"
#include "fcs/sample/vgroup/c_inl.hpp"
#include "fcs/orm/code_metrics/block_tracker_orm.hpp"
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include "fcs/utils/pantheios_debug_log.hpp"
#include "apps/performance/sample_group_vdispatch/sample_group_vdispatch_program_options.hpp"
#include <boost/foreach.hpp>
#include <boost/thread/mutex.hpp>
#include <algorithm>

namespace fcs {
namespace examples {

  
// custom <fcs::examples::sample_group_vdispatch namespace custom>
// end <fcs::examples::sample_group_vdispatch namespace custom>

} // namespace examples
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

int main(int argc, char** argv, char** envp) {

  // Get the user supplied program options
  using namespace fcs::examples;
  sample_group_vdispatch_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_sample_group_vdispatch_options_description();
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

  pantheios::log(PANTHEIOS_SEV_DEBUG, "app sample_group_vdispatch run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  {
    using namespace fcs::sample::vgroup;
    A a;
    B b;
    C c;

    typedef std::vector< One_ring_base* > One_ring_dispatcher_list_t;
    One_ring_dispatcher_list_t l;
    l.push_back(&a);
    l.push_back(&b);
    l.push_back(&c);

    {
      using namespace fcs::orm::code_metrics;
      Block_tracker_orm block_tracker_orm
        (std::pair< char const*, char const* >("efficiency", "dispatch"), 
         "virtual", __FILE__, __LINE__, Block_tracker_orm::TIMING_TICKS, 0);

      for(int n(0); n < options.iterations_; ++n) {
        for(size_t i(0); i < l.size(); ++i) {
          int x(std::max(int(i*n), 100));
          l[i]->observe(x, "test");
          l[i]->do_good(x);
          l[i]->do_bad(x);
        }
      }
    }
    std::cout << "A\n--------\n" << a << std::endl;
  }

// end <main_body> 
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// The following pantheios related functions provide basic selective
// logging support
////////////////////////////////////////////////////////////////////////////////
PANTHEIOS_CALL(int) pantheios_fe_init(void*, void** ptoken) { 
  *ptoken = NULL; 
  return 0; 
}

PANTHEIOS_CALL(void) pantheios_fe_uninit(void*) {}

PANTHEIOS_CALL(PAN_CHAR_T const*) pantheios_fe_getProcessIdentity(void*)
{
  return ("sample_group_vdispatch");
}

::pantheios::pan_sev_t app_log_severity_s(::pantheios::SEV_ERROR);

namespace fcs { 
namespace utils {

namespace {
  boost::mutex protect_severity_s;
}

  void set_log_level(::pantheios::pan_sev_t new_severity) {
    boost::mutex::scoped_lock lock(protect_severity_s);
    app_log_severity_s = new_severity;
  }
}
}

PANTHEIOS_CALL(int) pantheios_fe_isSeverityLogged(void*, int severity, int)
{
  return severity <= app_log_severity_s;
}



