/******************************************************************************
 * test_block_tracker_orm.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_block_tracker_orm.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/orm/code_metrics/block_tracker_orm.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Block_tracker_orm";

namespace {
  void test_block_tracker_orm() {

// custom <test-detail>

    using namespace fcs::orm::code_metrics;
    typedef std::vector< Block_tracker_orm::Timing_type > Timing_type_list_t;
    Timing_type_list_t timing_types;
    timing_types.push_back(Block_tracker_orm::TIMING_TICKS);
    timing_types.push_back(Block_tracker_orm::TIMING_RUSAGE);
    typedef std::vector< int > Processor_list_t;
    Processor_list_t processor_list;
    processor_list.push_back(0);
    processor_list.push_back(1);
    processor_list.push_back(-1);
    std::vector< int > iv;
    BOOST_FOREACH(Block_tracker_orm::Timing_type timing_type, timing_types) {
      BOOST_FOREACH(int processor, processor_list) {

        std::string tag(Block_tracker_orm::TIMING_TICKS? "Tick Timing - proc:" : "Rusage Timing - proc:");
        tag += boost::lexical_cast< std::string >(processor);

        {
          Block_tracker_orm block_tracker_orm
            (fcs::orm::api_name_and_description(), 
             tag.c_str(), __FILE__, __LINE__, timing_type, processor);

          int x(0);
          for(int i(0); i<(1<<25); ++i) {
            iv.push_back(rand());
            x += iv.back();
          }
          iv.clear();
        }
        std::cout << "Finished type: " << timing_type << " on processor " << processor << std::endl;
      }
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Block_tracker_orm");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <block_tracker_orm>" );
  test->add( BOOST_TEST_CASE( &::test_block_tracker_orm ) );
  return test;
}




