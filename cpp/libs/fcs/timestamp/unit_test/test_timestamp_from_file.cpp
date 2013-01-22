/******************************************************************************
 * test_timestamp_from_file.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_timestamp_from_file.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/timestamp/timestamp_from_file.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <fstream>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_timestamp_from_file";

namespace {
  void test_timestamp_from_file() {

// custom <test-detail>

    using namespace fcs::timestamp;
    Timestamp_t now(current_time());
    boost::filesystem::path out_path("out.txt");
    {
      std::ofstream outfile(out_path.string().c_str());
      outfile << "." << std::endl;
    }

    Timestamp_t now_plus_epsilon(timestamp_from_file(out_path));
    std::cout << "Now => " << to_iso_string(now) << "\n";
    std::cout << "File => " << to_iso_string(now_plus_epsilon) << "\n";
    BOOST_CHECK_LE((now_plus_epsilon - now).total_seconds(), 1);

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_timestamp_from_file");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <timestamp_from_file>" );
  test->add( BOOST_TEST_CASE( &::test_timestamp_from_file ) );
  return test;
}




