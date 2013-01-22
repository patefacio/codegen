/******************************************************************************
 * data_set_csv_writer.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file data_set_csv_writer.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "apps/h5data_set2csv/data_set_csv_writer.hpp"
#include "fcs/h5/h5_meta_data.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <boost/foreach.hpp>
#include <iostream>


// custom <Data_set_csv_writer pre-namespace custom>
// end <Data_set_csv_writer pre-namespace custom>

namespace fcs {
namespace app {
namespace h5 {

  
// custom <Data_set_csv_writer namespace custom>

    void Data_set_csv_writer::write_csv() {
        using namespace fcs::h5;
        BOOST_FOREACH(std::string const& target_path, program_options_.input_file_) {
            pantheios::log(PANTHEIOS_SEV_DEBUG, "Attempting file:", target_path.c_str());
            try {
                H5_meta_data target(target_path);
                BOOST_FOREACH(std::string const& data_set_name, program_options_.data_set_) {
                    target.write_csv(data_set_name);
                }
            } catch(H5::Exception const& excp) {
                pantheios::log(PANTHEIOS_SEV_DEBUG, "Failed write csv:", target_path.c_str(), excp.getDetailMsg());
            } catch(std::exception const& excp) {
                pantheios::log(PANTHEIOS_SEV_DEBUG, "Failed write csv:", target_path.c_str(), excp.what());
            }
        }

    }

// end <Data_set_csv_writer namespace custom>


  // Support for streaming non-static streamable members of Data_set_csv_writer
  std::ostream& operator<<(std::ostream& out, Data_set_csv_writer const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Data_set_csv_writer:(" << &item << "):{";
    out << '\n' << indent << "  program_options:" << item.program_options_;
    out << indent << "}\n";
    return out;
  }


} // namespace h5
} // namespace app
} // namespace fcs


