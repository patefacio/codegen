/******************************************************************************
 * test_table.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_table.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/utils/streamers/table/table.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <stdlib.h>
#include <iostream>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_table";

namespace {
  void test_table() {

// custom <test-detail>

    typedef std::vector< std::string > String_list_t;
    typedef std::vector< String_list_t > String_matrix_t;

    String_matrix_t m;
    String_list_t l;
    l.push_back("this");
    l.push_back("is");
    l.push_back("a");
    l.push_back("test");
    m.push_back(l);
    String_list_t l2;
    l2.push_back("wonder_bread");
    l2.push_back("is");
    l2.push_back("softer than most");
    l2.push_back("other types of bread");
    m.push_back(l2);
    m.push_back(l);
    m.push_back(l2);

    using fcs::utils::streamers::table::operator<<;
    std::cout << m;
    std::cout << "\nString Matrix as table\n";
    std::cout << fcs::utils::streamers::table::Table_streamer< String_matrix_t >(m) << std::endl;

    typedef std::vector< double > Double_list_t;
    typedef std::vector< Double_list_t > Double_matrix_t;

    Double_matrix_t d;

    for(int i(0); i<5; ++i) {
      Double_list_t dl;
      dl.push_back(1.2 * (rand()%100));
      dl.push_back(2.3 * (rand()%200));
      dl.push_back(12.3 * (rand()%300));
      dl.push_back(11.1 * (rand()%400));
      d.push_back(dl);
    }
    std::cout << d;
    std::cout << "\nMatrix as table\n";
    std::cout << fcs::utils::streamers::table::Table_streamer< Double_matrix_t >(d, l) << std::endl;

    typedef std::vector< bool > Bool_list_t;
    typedef std::vector< Bool_list_t > Bool_matrix_t;
    Bool_matrix_t bm;
    String_list_t bm_header;
    bm_header.push_back("first");
    bm_header.push_back("second");
    for(int i(0); i<5; ++i) {
      Bool_list_t bl;
      bl.push_back(rand()%2);
      bl.push_back(rand()%2);
      bm.push_back(bl);
    }
    std::cout << "\nMatrix of bool\n";
    std::cout << bm << std::endl;
    std::cout << "\nMatrix of bool as table\n";
    std::cout << fcs::utils::streamers::table::Table_streamer< Bool_matrix_t >(bm, bm_header) << std::endl;
    std::cout << fcs::utils::streamers::table::Table_streamer< Bool_matrix_t >(bm) << std::endl;

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_table");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <table>" );
  test->add( BOOST_TEST_CASE( &::test_table ) );
  return test;
}




