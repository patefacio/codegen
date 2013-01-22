/******************************************************************************
 * test_timestamp.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_timestamp.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/timestamp.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <boost/date_time/posix_time/ptime.hpp>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_timestamp";

namespace {
  void test_timestamp() {

// custom <test-detail>

    using namespace fcs::timestamp;

    {
      Timestamp_t now(boost::posix_time::microsec_clock::local_time());
      std::cout << "simple_string:       " << to_simple_string(now) << std::endl;
      std::cout << "iso_string:          " << to_iso_string(now) << std::endl;
      std::cout << "iso_extended_string: " << to_iso_extended_string(now) << std::endl;

      {
        using namespace boost::posix_time;
        std::cout << "boost:               " << now << std::endl;
      }
    }

    {
      Timestamp_t now(boost::posix_time::microsec_clock::universal_time());
      std::cout << " *** UTC *** " << std::endl;
      std::cout << "simple_string:       " << to_simple_string(now) << std::endl;
      std::cout << "iso_string:          " << to_iso_string(now) << std::endl;
      std::cout << "iso_extended_string: " << to_iso_extended_string(now) << std::endl;

      {
        using namespace boost::posix_time;
        std::cout << "boost:               " << now << std::endl;
      }

      std::cout << " *** Converted *** " << std::endl;
      std::cout << "simple_string:       " << to_simple_string(utc_to_local_time(now)) << std::endl;      

    }

    {
      Timestamp_t now(boost::posix_time::microsec_clock::universal_time());      
      std::cout << "UTC   => " << to_simple_string(now) << std::endl;
      std::cout << "Local => " << utc_to_local_time(now) << std::endl;
    }

    {
      std::cout << sizeof(time_t) << std::endl;
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_timestamp");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <timestamp>" );
  test->add( BOOST_TEST_CASE( &::test_timestamp ) );
  return test;
}




