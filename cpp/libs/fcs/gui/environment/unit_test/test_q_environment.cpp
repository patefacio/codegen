/******************************************************************************
 * test_q_environment.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_q_environment.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/gui/environment/q_environment.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <QApplication>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Q_environment";

namespace {
  void test_q_environment() {

// custom <test-detail>

    using namespace fcs::gui::environment;
    int argc(0);
    char *argv[0] = {};
    QApplication app(argc, argv);
    app.setStyleSheet("QTableWidget { background-color: lightyellow; color: blue; padding-top: 0.5px; padding-bottom: 0.5px }");
//    app.setStyleSheet("QTableWidgetItem { padding-top: 1x; padding-bottom: 1x }");
    Q_environment q_env(0);
    q_env.show();
    app.exec();

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Q_environment");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <q_environment>" );
  test->add( BOOST_TEST_CASE( &::test_q_environment ) );
  return test;
}




