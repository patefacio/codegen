/******************************************************************************
 * test_h5_data_model.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_h5_data_model.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/h5/data_model/h5_data_model.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>
// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_H5_data_model";

namespace {
  void test_h5_data_model() {

// custom <test-detail>

    using namespace fcs::h5::data_model;
    H5_data_model data_model;
    std::cout << data_model << std::endl;

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_H5_data_model");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <h5_data_model>" );
  test->add( BOOST_TEST_CASE( &::test_h5_data_model ) );
  return test;
}




