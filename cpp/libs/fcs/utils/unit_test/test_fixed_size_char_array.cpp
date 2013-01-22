/******************************************************************************
 * test_fixed_size_char_array.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_fixed_size_char_array.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/fixed_size_char_array.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <iostream>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Fixed_size_char_array";

namespace {
  void test_fixed_size_char_array() {

// custom <test-detail>

    using namespace fcs::utils;
    std::string const s1("test");
    {
        Fixed_size_char_array< 2 > sample(s1.c_str());
        std::cout << ":" << sample.operator std::string() << ":" << std::endl;
        BOOST_REQUIRE( sample.operator std::string() == "t" );
    }
    {
        Fixed_size_char_array< 4 > sample(s1.c_str());
        BOOST_REQUIRE( sample.operator std::string() == "tes" );
    }
    {
        Fixed_size_char_array< 5 > sample(s1.c_str());
        BOOST_REQUIRE( sample.operator std::string() == "test" );
        for(size_t i(0); i < s1.size(); ++i) {
            BOOST_REQUIRE(s1[i] == sample[i]);
        }

        sample[0] = 'T';
        BOOST_REQUIRE( sample.operator std::string() == "Test" );        
        BOOST_REQUIRE( sample.str() == "Test" );        
        BOOST_REQUIRE( sample == "Test" );        
        BOOST_REQUIRE( !(sample == "Tester") );        
        BOOST_REQUIRE( !(sample == "Tes") );        
        BOOST_REQUIRE( sample[1] == 'e' );        
    }
    {
        Fixed_size_char_array< 50 > sample(s1.c_str());
        BOOST_REQUIRE( sample.operator std::string() == "test" );
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Fixed_size_char_array");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <fixed_size_char_array>" );
  test->add( BOOST_TEST_CASE( &::test_fixed_size_char_array ) );
  return test;
}




