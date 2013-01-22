/******************************************************************************
 * test_h5_meta_data.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_h5_meta_data.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/h5/h5_meta_data.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <boost/foreach.hpp>
#include "fcs/dev/place.hpp"

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_H5_meta_data";

namespace {
  void test_h5_meta_data() {

// custom <test-detail>

    using namespace fcs::h5;
    boost::debug::detect_memory_leaks(false);
    std::vector< boost::filesystem::path > all_paths;
    all_paths.push_back(fcs::dev::Place::get_instance()->data() / "sample" / "all_types_example.h5");
    H5_meta_data::log_meta_data_load(true);
    BOOST_FOREACH(boost::filesystem::path const& target, all_paths) {
        try {
            pantheios::log(PANTHEIOS_SEV_DEBUG, "Opening target:", target.string().c_str());
            H5_meta_data h5m2(target);
        } catch(std::exception const& e) {
            pantheios::log(PANTHEIOS_SEV_ERROR, "Caught exception:", e.what(), " opening target ",
                           target.string().c_str());
            throw;
        } catch(H5::Exception const& e) {
            pantheios::log(PANTHEIOS_SEV_ERROR, "Caught H5 exception:", e.getDetailMsg(), " opening target ",
                           target.string().c_str());
            throw;
        }
    }

    H5close();

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_H5_meta_data");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <h5_meta_data>" );
  test->add( BOOST_TEST_CASE( &::test_h5_meta_data ) );
  return test;
}




