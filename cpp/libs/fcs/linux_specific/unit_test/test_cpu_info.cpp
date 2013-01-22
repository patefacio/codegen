/******************************************************************************
 * test_cpu_info.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_cpu_info.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/linux_specific/cpu_info.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <utmpx.h>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Cpu_info";

namespace {
  void test_cpu_info() {

// custom <test-detail>

    using namespace fcs::linux_specific;
    Cpu_info::Pointer_t cpu_info(Cpu_info::get_instance());
    std::cout << *cpu_info << std::endl;
    cpu_set_t mask;
    long affinity(sched_getaffinity(0, sizeof(mask), &mask));
    if(0 == affinity) { 
      std::cout << "Running from process: " << getpid() 
                << "\n processor count:        " << CPU_COUNT(&mask)
                << "\n processor 0 set:        " << CPU_ISSET(0, &mask)
                << "\n processor 1 set:        " << CPU_ISSET(1, &mask) 
                << "\n this thread running on: " << sched_getcpu()
                << std::endl;
    } else {
      std::cout << "sched_getaffinity rc: " << affinity << std::endl;
    }

    for(int i(0); i<10; ++i) {
      CPU_ZERO(&mask);
      int proc(i%2);
      CPU_SET(proc, &mask);
      std::cout << "\nSetting affinity to proc:" << proc << std::endl;
      long rc(sched_setaffinity(0, sizeof(mask), &mask));
      if(0 == rc) {
        std::cout << "\nSucceeded set affinity"
                  << "\n this thread running on: " << sched_getcpu() << "\n";
      } else {
        std::cout << "Unable to sched_setaffinity\n";
      }
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Cpu_info");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <cpu_info>" );
  test->add( BOOST_TEST_CASE( &::test_cpu_info ) );
  return test;
}




