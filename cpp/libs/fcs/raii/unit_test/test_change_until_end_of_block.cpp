/******************************************************************************
 * test_change_until_end_of_block.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_change_until_end_of_block.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/raii/change_until_end_of_block.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>
// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Change_until_end_of_block";

namespace {
  void test_change_until_end_of_block() {

// custom <test-detail>

    int x(1);
    {
      fcs::raii::Change_until_end_of_block<int> change_until_end_of_block(x, 3);
      BOOST_REQUIRE(x == 3);
    }
    BOOST_REQUIRE(x == 1);
    {
      int y(4);
      fcs::raii::Change_until_end_of_block<int> change_until_end_of_block(x, y);
      BOOST_REQUIRE(x == y);
    }
    BOOST_REQUIRE(x == 1);

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Change_until_end_of_block");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <change_until_end_of_block>" );
  test->add( BOOST_TEST_CASE( &::test_change_until_end_of_block ) );
  return test;
}




