/******************************************************************************
 * display_csv.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file display_csv.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontend.h>
#include "fcs/table/delimited_file_table_model.hpp"
#include "fcs/gui/table/q_table_view.hpp"
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include "fcs/utils/pantheios_debug_log.hpp"
#include "apps/display_csv/display_csv_program_options.hpp"
#include <QApplication>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/thread/mutex.hpp>

namespace fcs {
namespace app {

  
// custom <fcs::app::display_csv namespace custom>

  template < typename T >
  void debug_print(T const& t) {
    std::cout << t;
  }

// end <fcs::app::display_csv namespace custom>

} // namespace app
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

int main(int argc, char** argv, char** envp) {

  // Get the user supplied program options
  using namespace fcs::app;
  Display_csv_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_display_csv_options_description();
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

  pantheios::log(PANTHEIOS_SEV_DEBUG, "app display_csv run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  if(options.csv_file_.size()) {
    QApplication app(argc, argv);

    using namespace fcs::table;
    using namespace fcs::gui::table;
    typedef boost::ptr_vector< Q_table_view > Table_view_list_t;
    typedef boost::ptr_vector< Q_table_model > Table_model_list_t;
    Table_view_list_t views;
    Table_model_list_t models;
    BOOST_FOREACH(std::string const& csv_path, options.csv_file_) {
      Delimited_file_reader delimited_file_reader(csv_path);
      Table_model_const_ptr table_model(delimited_file_reader.create_memory_table_model());
      Q_table_model *q_table_model(new Q_table_model(0, table_model));
      Q_table_view *q_table_view(new Q_table_view(0, q_table_model));
      views.push_back(q_table_view);
      models.push_back(q_table_model);
      q_table_view->setWindowTitle(csv_path.c_str());
      q_table_view->show();
    }
    app.exec();
  } else {
    std::cout << get_display_csv_options_description();
    std::cout.flush();
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
  return ("display_csv");
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



