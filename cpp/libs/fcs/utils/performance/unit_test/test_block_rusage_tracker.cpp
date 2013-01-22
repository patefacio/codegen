/******************************************************************************
 * test_block_rusage_tracker.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_block_rusage_tracker.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/performance/block_rusage_tracker.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <stdlib.h>

inline void show_priority() {
  errno = 0;
  int priority(getpriority(PRIO_PROCESS, 0));
  if(errno) {
    std::cerr << "Could not get priority" << std::endl;
  } else {
    std::cout << "Current priority:" << priority << std::endl;
  }
}

inline void show_quantum() {
  struct timespec tp;
  if(sched_rr_get_interval(0, &tp) != 0) {
    std::cerr << "Could not get the round robin time quantum" << std::endl;
  } else {
    std::cout << "Quantum " << tp.tv_sec << " (s) " << tp.tv_nsec << " (ns) " << std::endl;
  }
}

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Block_rusage_tracker";

namespace {
  void test_block_rusage_tracker() {

// custom <test-detail>

    using namespace fcs::utils::performance;
    size_t iteration_count(1<<26);
    Block_rusage_tracker block_rusage_tracker(&std::cout, "sample rusage counter:", 0, iteration_count);
    long temp(0);
    for(size_t i(0); i<iteration_count; ++i) {
      temp = random() * random() / std::max(1L, random());
      temp /= std::max(1L, (random() * random())/std::max(1L, random()));
    }

    typedef std::vector< int > Int_vec_t;
    Int_vec_t iv;
    show_priority();
    for(int i(-10); i < 10; i += 2) {
      errno = 0;
      int priority(setpriority(PRIO_PROCESS, 0, i));
      if(errno) {
        std::cerr << "Could not set priority" << std::endl;
        perror("setpriority");
      } else {
        std::cout << "Current priority:" << priority << std::endl;
      }
      show_priority();
      show_quantum();
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Block_rusage_tracker");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <block_rusage_tracker>" );
  test->add( BOOST_TEST_CASE( &::test_block_rusage_tracker ) );
  return test;
}




