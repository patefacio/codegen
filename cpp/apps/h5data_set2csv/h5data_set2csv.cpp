/******************************************************************************
 * h5data_set2csv.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5data_set2csv.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include <pantheios/frontends/stock.h>
#include "fcs/h5/h5_meta_data.hpp"
#include "data_set_csv_writer.hpp"
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include <iostream>

namespace fcs {
namespace app {
namespace h5 {

  
// custom <fcs::app::h5::h5data_set2csv namespace custom>
// end <fcs::app::h5::h5data_set2csv namespace custom>

} // namespace h5
} // namespace app
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

int main(int argc, char** argv, char** envp) {


  pantheios::log(PANTHEIOS_SEV_DEBUG, "app h5data_set2csv run with main(", 
    pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
  
// custom <main_body>

  using namespace fcs::app::h5;
  H5_data_set_to_csv_program_options options;
  try {
    read_parameters(options, argc, argv);
    if(options.help_) {
      std::cout << get_h5_data_set_to_csv_options_description();
      std::cout.flush();
      return 0;
    }
  } catch(std::exception const& excp) {
    std::cout << "Caught exception:" << excp.what() << std::endl;
    return -1;
  }

  try {
    fcs::h5::H5_meta_data::log_meta_data_load(options.log_meta_data_load_);
    Data_set_csv_writer data_set_csv_writer(options);
    data_set_csv_writer.write_csv();
  } catch(std::exception const& excp) {
    std::cerr << "Caught exception: " << excp.what() << std::endl;
    return -1;
  }

// end <main_body> 
  return 0;
}

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "h5data_set2csv";



