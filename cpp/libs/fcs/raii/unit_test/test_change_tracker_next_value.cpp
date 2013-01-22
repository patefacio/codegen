/******************************************************************************
 * test_change_tracker_next_value.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_change_tracker_next_value.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/raii/change_tracker.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>
// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Change_tracker_next_value";

namespace {
  void test_change_tracker_next_value() {

// custom <test-detail>

    using namespace fcs::raii;
    Change_tracker< int > change_tracker(1);
    BOOST_REQUIRE(change_tracker.current() == 1);
    {
      Change_tracker_next_value< int > next_value(change_tracker, 3);
      BOOST_REQUIRE(change_tracker.current() == 1);
      BOOST_REQUIRE(next_value.next_value() == 3);
    }
    BOOST_REQUIRE(change_tracker.previous() == 1);
    BOOST_REQUIRE(change_tracker.current() == 3);
    {
      Change_tracker_next_value< int > next_value(change_tracker, 4);
      BOOST_REQUIRE(next_value.next_value() == 4);
    }
    BOOST_REQUIRE(change_tracker.previous() == 3);
    BOOST_REQUIRE(change_tracker.current() == 4);

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Change_tracker_next_value");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <change_tracker_next_value>" );
  test->add( BOOST_TEST_CASE( &::test_change_tracker_next_value ) );
  return test;
}




