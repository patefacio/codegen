/******************************************************************************
 * test_delimited_file_creator.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_delimited_file_creator.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/table/delimited_file_table_model.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <boost/test/unit_test_log.hpp>
#include "fcs/table/test/random_table_generator.hpp"
#include "fcs/table/table_cell_string_conversion.hpp"
#include "fcs/table/table_compare.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Delimited_file_creator";

namespace {
  void test_delimited_file_creator() {

// custom <test-detail>

    using namespace fcs::table;
    using namespace fcs::table::test;
    Index_t const num_columns(20);
    Index_t const num_rows(2000);
    Random_table_generator random_table_generator(num_columns, num_rows);
    boost::filesystem::path write_csv_path("/tmp/delimited_file.csv");
    Table_model_ptr table_model(random_table_generator.create_memory_table_model());
    {
      Delimited_file_creator delimited_file_creator(write_csv_path, *table_model, '|');
      delimited_file_creator.create_delimited_file();
    }

    {
      Delimited_file_reader_options options;
      for(size_t i(0); (i < num_columns); ++i) {
        std::string s("C");
        s += ('A' + i);
        options.table_header_.push_back(s);
      }
      Delimited_file_reader delimited_file_reader(write_csv_path, options);
      Table_model_const_ptr read_table_model(delimited_file_reader.create_memory_table_model());

      {
        boost::filesystem::path carat_csv_path("/tmp/carat_delimited_file.txt");
        Delimited_file_creator delimited_file_creator(carat_csv_path, *read_table_model, '^');
        delimited_file_creator.create_delimited_file();
        BOOST_TEST_MESSAGE("Comparing original table to read table");
        BOOST_REQUIRE(table_compare_equal(*table_model, *read_table_model, false));
      }
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Delimited_file_creator");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <delimited_file_creator>" );
  test->add( BOOST_TEST_CASE( &::test_delimited_file_creator ) );
  return test;
}




