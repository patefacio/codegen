/******************************************************************************
 * test_histogram.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_histogram.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/histogram.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/utils/streamers/streamers.hpp"

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_histogram";

namespace {
  void test_histogram() {

// custom <test-detail>

    using namespace fcs::utils;

    typedef std::vector< double > Data_t;
    Data_t data;
    Histogram_statistical<> h;
    for(int i(0); i<20000; ++i) {
      double element(abs(rand()%100 - 100));
      data.push_back(element);
      h(element);
    }

    using fcs::utils::streamers::operator<<;
    typedef Histogram_statistical<>::Accumulator_t::result_type Hist_results_t;
    Histogram_statistical<>::Hist_results_t hist = boost::accumulators::density(h.accumulator());
    double total(0);
    for(int i(0); i < hist.size(); ++i) {
      std::cout << "Bin lower bound: " << hist[i].first << ", Value: " << hist[i].second << std::endl; 
      total += hist[i].second;
    }

    std::cout << "Total: " << total << std::endl;
    std::cout << "\nDATA:\n" << data << std::endl;
    Histogram<> two_pass(data.begin(), data.end(), 20);
    std::cout << two_pass << std::endl;

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_histogram");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <histogram>" );
  test->add( BOOST_TEST_CASE( &::test_histogram ) );
  return test;
}




