/******************************************************************************
 * data_set_csv_writer.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file data_set_csv_writer.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_APP_H5_DATA_SET_CSV_WRITER_H_
#define _FCS_APP_H5_DATA_SET_CSV_WRITER_H_

#include "h5_data_set_to_csv_program_options.hpp"
#include <iosfwd>

namespace fcs {
namespace app {
namespace h5 {

  class Data_set_csv_writer 
  {
  public:

    explicit Data_set_csv_writer(
      H5_data_set_to_csv_program_options const& program_options
    ) :
      program_options_(program_options)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Data_set_csv_writer const& item);

  
// custom <Data_set_csv_writer public header section>

        void write_csv();

// end <Data_set_csv_writer public header section>

  private:
    H5_data_set_to_csv_program_options program_options_;
  };

} // namespace h5
} // namespace app
} // namespace fcs
#endif // _FCS_APP_H5_DATA_SET_CSV_WRITER_H_
