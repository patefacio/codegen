/******************************************************************************
 * test_place.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_place.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/dev/place.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <boost/filesystem/operations.hpp>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Place";

namespace {
  void test_place() {

// custom <test-detail>

    fcs::dev::Place::Pointer_t place(fcs::dev::Place::get_instance());
    std::cout << *place << std::endl;
    BOOST_REQUIRE(boost::filesystem::exists(place->install()));

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Place");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <place>" );
  test->add( BOOST_TEST_CASE( &::test_place ) );
  return test;
}




