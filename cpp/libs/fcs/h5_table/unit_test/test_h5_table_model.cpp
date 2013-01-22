/******************************************************************************
 * test_h5_table_model.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_h5_table_model.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/h5_table/h5_table_model.hpp"



#include "fcs/h5/h5_meta_data.hpp"

#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/utils/streamers/containers.hpp"
#include "fcs/dev/place.hpp"
#include <boost/foreach.hpp>
#include <algorithm>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_H5_table_model";

namespace {
  void test_h5_table_model() {

// custom <test-detail>

    using namespace fcs::table;
    boost::debug::detect_memory_leaks(false);
    std::vector< boost::filesystem::path > all_paths;
    all_paths.push_back(fcs::dev::Place::get_instance()->data() / "sample" / "all_types_example.h5");
    fcs::h5::H5_meta_data::log_meta_data_load(false);

    BOOST_FOREACH(boost::filesystem::path const& target, all_paths) {
      try {
        {
          std::string data_set_name("/a/b/c/all_types");
          fcs::h5_table::H5_table_model example(target, data_set_name);
          std::cout << example << std::endl;
          Index_t const expected_rows(1<<19);
          Index_t const expected_columns(16);
          Index_t const num_rows(example.row_count());
          Index_t const num_columns(example.column_count());
          std::cout << num_columns << " by " << num_rows << std::endl;
          BOOST_REQUIRE_EQUAL(num_columns, expected_columns);
          BOOST_WARN_EQUAL(num_rows, expected_rows);
          BOOST_TEST_MESSAGE(data_set_name + " matched on column");
          size_t i(0);
          Index_t const rows_to_read(100);
          for(; i < expected_rows; ++i) {
            using namespace fcs::table;
            using fcs::utils::streamers::operator<<;
            Row_contents_t row_contents;
            if(0 == i) {
              BOOST_TEST_MESSAGE("TODO: Implement H5_table_model::read_row");
            }
            example.read_row(i, row_contents);
          }
        }
      } catch(std::exception const& e) {
        std::cerr << "Caught exception: " << e.what() << " opening target: " << target << std::endl;
      } 
      /* TODO
         catch(H5::Exception const& e) {
         std::cerr << "Caught an H5 exception:" << e.getDetailMsg() << std::endl;
         }
      */
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_H5_table_model");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <h5_table_model>" );
  test->add( BOOST_TEST_CASE( &::test_h5_table_model ) );
  return test;
}




