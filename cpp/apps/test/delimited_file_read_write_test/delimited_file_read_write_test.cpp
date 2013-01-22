/******************************************************************************
 * delimited_file_read_write_test.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file delimited_file_read_write_test.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/frontend.h>
#include "fcs/table/delimited_file_table_model.hpp"
#include "fcs/app_sig_handler/application_signal_handler.hpp"
#include "fcs/utils/pantheios_debug_log.hpp"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/mutex.hpp>


#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


namespace fcs {
namespace test {

  
// custom <fcs::test::delimited_file_read_write_test namespace custom>

  using namespace boost::filesystem;
  using namespace fcs::table;

  struct Header_type_count {
    Header_type_count() : num_floats_(0), num_ints_(0),
                          num_strings_(0), num_uints_(0), num_columns_(0) {
    }
    size_t num_floats_;
    size_t num_ints_;
    size_t num_strings_;
    size_t num_uints_;
    size_t num_columns_;
    bool operator==(Header_type_count const& other) const {
      return 
        num_floats_ == other.num_floats_ and
        num_strings_ == other.num_strings_ and
        (num_ints_ + num_uints_) == (other.num_ints_ + other.num_uints_);
    }
    void total_num_columns() {
      num_columns_ = num_floats_ + num_ints_ +
        num_strings_ + num_uints_;
    }
  };

  inline std::ostream& operator<<(std::ostream& out, Header_type_count const& htc) {
    out << "\n\tnum_floats:" << htc.num_floats_
        << "\n\tnum_ints:" << htc.num_ints_
        << "\n\tnum_strings:" << htc.num_strings_
        << "\n\tnum_uints:" << htc.num_uints_ << "\n";
    return out;
  }

  inline Header_type_count get_header_type_counts(Table_shape_t const& table_shape) {
    Header_type_count result;
    for(size_t i(0); i < table_shape.size(); ++i) {
      result.num_columns_++;
      switch(table_shape[i]) {
       case CELL_TYPE_INT8: {
         result.num_ints_++;
         break;
       }
       case CELL_TYPE_INT32: {
         result.num_ints_++;
         break;
       }
       case CELL_TYPE_INT64: {
         result.num_ints_++;
         break;
       }
       case CELL_TYPE_UINT8: {
         result.num_uints_++;
         break;
       }
       case CELL_TYPE_UINT32: {
         result.num_uints_++;
         break;
       }
       case CELL_TYPE_UINT64: {
         result.num_uints_++;
         break;
       }
       case CELL_TYPE_FLOAT: {
         result.num_floats_++;
         break;
       }
       case CELL_TYPE_DOUBLE: {
         result.num_floats_++;
         break;
       }
       case CELL_TYPE_LONG_DOUBLE: {
         result.num_floats_++;
         break;
       }
       case CELL_TYPE_STRING: {
         result.num_strings_++;
         break;
       }
       default: {
         assert(!"Missing Table_cell_type");
       }
      }
    }
    return result;
  }

  void delimited_file_read_write_test() {

    boost::regex simple_table_re("simple_table_header_(t|f)_float_(\\d+)_int_(\\d+)_string_(\\d+)_uint_(\\d+)_rows_(\\d+)_(\\w+).csv");

    path test_file_folder_path("/home/dbdavidson/data/test/delimited_test_files");
    if (exists( test_file_folder_path )) {
      directory_iterator end_itr; 
      for (directory_iterator it(test_file_folder_path); it != end_itr; ++it) {
        std::string const file_path(it->path().string());
        boost::cmatch matches;
        if(boost::regex_match(it->path().filename().c_str(), matches, simple_table_re)) {
          Header_type_count counts_gleaned_from_filename;
          int i(1);
          bool header_included(std::string(matches[i].first, matches[i].second) == "t");
          ++i;
          counts_gleaned_from_filename.num_floats_ = boost::lexical_cast< size_t >(std::string(matches[i].first, matches[i].second));
          ++i;
          counts_gleaned_from_filename.num_ints_ = boost::lexical_cast< size_t >(std::string(matches[i].first, matches[i].second));
          ++i;
          counts_gleaned_from_filename.num_strings_ = boost::lexical_cast< size_t >(std::string(matches[i].first, matches[i].second));
          ++i;
          counts_gleaned_from_filename.num_uints_ = boost::lexical_cast< size_t >(std::string(matches[i].first, matches[i].second));
          ++i;
          counts_gleaned_from_filename.total_num_columns();
          size_t num_rows(boost::lexical_cast< size_t >(std::string(matches[i].first, matches[i].second)));
          std::cout 
            << "\n\tfile_path:" << file_path
            << "\n\theader_included:" << header_included
            << counts_gleaned_from_filename
            << "\n\tnum_rows:" << num_rows
            << std::endl;

          Delimited_file_reader delimited_file_reader(file_path);
          std::cout << "Read file" << std::endl;
          Table_model_const_ptr read_table_model(delimited_file_reader.create_memory_table_model());
          std::cout << "Read table_model" << std::endl;
          Table_meta_data read_table_meta_data(read_table_model->meta_data());
          std::cout << "Read table meta_data" << std::endl;
          Header_type_count counts_read_from_file(get_header_type_counts(read_table_meta_data.shape()));
          std::cout << "Comparing columns read from file:" << counts_read_from_file.num_columns_
                    << " vs from filename:" << counts_gleaned_from_filename.num_columns_ << std::endl;
          BOOST_REQUIRE((0 == num_rows) || (counts_read_from_file.num_columns_ == counts_gleaned_from_filename.num_columns_));
          std::cout << "\nrow_count:" << read_table_model->row_count() << std::endl;
          if((num_rows > 1) or ((num_rows == 1) and header_included)) {
            BOOST_REQUIRE_EQUAL(num_rows, read_table_model->row_count());
          } else {
            BOOST_REQUIRE_EQUAL(0u, read_table_model->row_count());
          }

          if(num_rows > 1) {
            BOOST_REQUIRE_EQUAL(counts_gleaned_from_filename, counts_read_from_file);
          }

          Delimited_file_creator delimited_file_creator(std::string(file_path) + ".2", *read_table_model, '^');
          delimited_file_creator.create_delimited_file();
        }
      }
    }
  }

// end <fcs::test::delimited_file_read_write_test namespace custom>

} // namespace test
} // namespace fcs

#if !defined(DEBUG)
fcs::app_sig_handler::Application_signal_handler<>::Pointer_t
app_sig_handler_s(fcs::app_sig_handler::Application_signal_handler<>::get_instance());
#endif

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Test: delimited_file_read_write_test ");
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "Test <delimited_file_read_write_test>" );
  test->add( BOOST_TEST_CASE( &fcs::test::delimited_file_read_write_test ) );
  return test;
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
  return ("delimited_file_read_write_test");
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



