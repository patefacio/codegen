/******************************************************************************
 * test_some_class.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_some_class.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/examples/typedef_of/some_class.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>
// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_some_class";

namespace {
  void test_some_class() {

// custom <test-detail>

    using namespace fcs::examples::typedef_of;

    BOOST_REQUIRE_EQUAL(sizeof(Int_list_t), sizeof(some_class::Int_list_t));
    BOOST_REQUIRE_EQUAL(sizeof(String_to_int_map_t), sizeof(some_class::String_to_int_map_t));

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_some_class");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <some_class>" );
  test->add( BOOST_TEST_CASE( &::test_some_class ) );
  return test;
}




