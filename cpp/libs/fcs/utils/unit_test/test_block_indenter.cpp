/******************************************************************************
 * test_block_indenter.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_block_indenter.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/block_indenter.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>
// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Block_indenter";

namespace {
  void test_block_indenter() {

// custom <test-detail>

    {
        using namespace fcs::utils;
        Block_indenter indenter;
        char const* current_indentation(indenter.current_indentation_text());
        BOOST_REQUIRE(std::string(current_indentation) == "  ");
        std::cout << '.' << current_indentation << '.' << std::endl;
        {
            Block_indenter indenter;
            char const* current_indentation(indenter.current_indentation_text());
            std::cout << '.' << current_indentation << '.' << std::endl;
            BOOST_REQUIRE(std::string(current_indentation) == "    ");
            {
                Block_indenter indenter;
                char const* current_indentation(indenter.current_indentation_text());
                std::cout << '.' << current_indentation << '.' << std::endl;
                BOOST_REQUIRE(std::string(current_indentation) == "      ");
            }
        }
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Block_indenter");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <block_indenter>" );
  test->add( BOOST_TEST_CASE( &::test_block_indenter ) );
  return test;
}




