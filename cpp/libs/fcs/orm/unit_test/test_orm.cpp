/******************************************************************************
 * test_orm.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_orm.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/orm/orm.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_orm";

namespace {
  void test_orm() {

// custom <test-detail>

    using namespace fcs::orm;
    String_set_t strings;
    strings.insert("a");
    strings.insert("b");
    strings.insert("c");
    strings.insert("wow, \"WOW!\"");

    Date_set_t dates;
    dates.insert(Date_t(2010, 1, 1));
    dates.insert(Date_t(2010, 1, 2));
    dates.insert(Date_t(2010, 1, 3));
    dates.insert(Date_t(2010, 12, 16));

    std::cout << "SQL Date:" << to_sql_string(*dates.begin()) << std::endl;
    boost::posix_time::ptime now(boost::posix_time::microsec_clock::local_time());

    typedef std::set< int > Int_set_t;
    Int_set_t ints;
    ints.insert(1);
    ints.insert(5);

    typedef std::set< double > Double_set_t;
    Double_set_t doubles;
    doubles.insert(1.3);
    doubles.insert(5.5);

    std::cout << "select * from "
              << create_select_union(doubles.begin(), doubles.end(), "doubles") << " as doubles,\n"
              << create_select_union(dates.begin(), dates.end(), "dates") << " as dates,\n"
              << create_select_union(strings.begin(), strings.end(), "strings") << " as strings" << std::endl;
    std::cout << to_iso_string(Date_t(2010, 1, 1)) << std::endl;

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_orm");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <orm>" );
  test->add( BOOST_TEST_CASE( &::test_orm ) );
  return test;
}




