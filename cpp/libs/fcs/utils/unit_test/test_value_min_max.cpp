/******************************************************************************
 * test_value_min_max.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_value_min_max.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/value_min_max.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>
// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Value_min_max";

namespace {
  void test_value_min_max() {

// custom <test-detail>

    using namespace fcs::utils;
    {
      Value_min_max< int > x;
      x(3);
      x(1);
      x(5);
      x(4);
      x(5);
      x(2);

      BOOST_REQUIRE(x.min_value_ == 1);
      BOOST_REQUIRE(x.max_value_ == 5);
    }

    {
      Value_min_max< double > x;
      x(3.14);
      x(1.23);
      x(5.23);
      x(4);
      x(5.23);
      x(2.1);

      BOOST_REQUIRE(x.min_value_ == 1.23);
      BOOST_REQUIRE(x.max_value_ == 5.23);
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Value_min_max");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <value_min_max>" );
  test->add( BOOST_TEST_CASE( &::test_value_min_max ) );
  return test;
}




