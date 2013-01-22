/******************************************************************************
 * test_block_tick_tracker.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_block_tick_tracker.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/performance/block_tick_tracker.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <stdlib.h>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Block_tick_tracker";

namespace {
  void test_block_tick_tracker() {

// custom <test-detail>

    using namespace fcs::utils::performance;
    size_t iteration_count(100000);
    Block_tick_tracker block_tick_tracker(&std::cout, "sample tick counter:", 0, iteration_count);
    long temp(0);
    for(size_t i(0); i<iteration_count; ++i) {
      temp = random() * random() / std::max(1L, random());
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Block_tick_tracker");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <block_tick_tracker>" );
  test->add( BOOST_TEST_CASE( &::test_block_tick_tracker ) );
  return test;
}




