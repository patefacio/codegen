/******************************************************************************
 * test_all_types.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_all_types.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/codegen/coverage/all_types.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/dev/place.hpp"
#include "fcs/h5/utils/h5_random_access_store.hpp"
#include "fcs/codegen/coverage/all_types_data_set_specifier.hpp"
#include <boost/filesystem/operations.hpp>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_All_types";

namespace {
  void test_all_types() {

// custom <test-detail>

    using namespace fcs::codegen::coverage;
    using namespace fcs::h5;
    using namespace fcs::h5::utils;
    using namespace fcs::utils;

    All_types::check_sizes();
    std::string group_prefix("/a/b/c");
    std::string group_prefix2("/a/b/d");
    typedef H5_random_access_store< All_types, All_types_data_set_specifier > Store_t;
    boost::filesystem::path p(fcs::dev::Place::get_instance()->data() / "sample" / "all_types_example.h5");
    if(boost::filesystem::exists(p)) {      
      H5_file_ptr file(new H5::H5File(p.string().c_str(), H5F_ACC_RDONLY));
      Store_t store(file, OPEN_READ, group_prefix);
      hsize_t const num_records(store.size());
      for(hsize_t i(0); i<num_records; ++i) {
        All_types s;
        store.get(i, s);
        if(i == 5) {
          std::cout << "Sample: " << i << " is\n" << s << std::endl;
        }
      }
      std::cout << "Processed " << num_records << " records" << std::endl;
    } else {
      H5_file_ptr file(new H5::H5File(p.string().c_str(), H5F_ACC_TRUNC));
      hsize_t const num_records(1<<19);
      Store_t store(file, OPEN_CREATE, group_prefix);
      Store_t store_2(file, OPEN_CREATE, group_prefix2);
      for(hsize_t i(0); i<num_records; ++i) {
        All_types s;
        if(i > 3) {
          bool sign(i%2 == 0);
          s.int_m(sign*i);
          s.double_m(sign * i * i);
          s.sample_string(Fixed_size_char_array< 32 >("foobar"));
        }
        store.append(s);
        store_2.append(s);
      }
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_All_types");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <all_types>" );
  test->add( BOOST_TEST_CASE( &::test_all_types ) );
  return test;
}




