/******************************************************************************
 * test_block_performance_counter_tracker.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_block_performance_counter_tracker.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/performance/block_performance_counter_tracker.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <stdlib.h>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Block_performance_counter_tracker";

namespace {
  void test_block_performance_counter_tracker() {

// custom <test-detail>

    using namespace fcs::utils::performance;
    size_t iterations(10000);
    Block_performance_counter_tracker block_performance_counter_tracker(&std::cout, "sample perf counter:", iterations);
    long temp(0);
    for(size_t i(0); i<iterations; ++i) {
      temp = random() * random() / std::max(1L, random());
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Block_performance_counter_tracker");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <block_performance_counter_tracker>" );
  test->add( BOOST_TEST_CASE( &::test_block_performance_counter_tracker ) );
  return test;
}




