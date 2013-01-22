/******************************************************************************
 * test_q_multiple_pick_list.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_q_multiple_pick_list.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/gui/selection/q_multiple_pick_list.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <QApplication>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Q_multiple_pick_list";

namespace {
  void test_q_multiple_pick_list() {

// custom <test-detail>

    using namespace fcs::gui::selection;
    int argc(0);
    char *argv[0] = {};
    QApplication app(argc, argv);
    //////////////////////////////////////////////////////////////////////
    // Create a lot of selection items, put them in the pick list and set a
    // small set of them as true
    //////////////////////////////////////////////////////////////////////
    Q_multiple_pick_list::Selection_map_t selection_map;
    for(int i(0); i<3000; ++i) {
      std::ostringstream s;
      s << "Item " << i;
      selection_map[QString(s.str().c_str())] = (0 == i%1000);
    }
    Q_multiple_pick_list qmpl(0, selection_map);
    qmpl.show();
    app.exec();

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Q_multiple_pick_list");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <q_multiple_pick_list>" );
  test->add( BOOST_TEST_CASE( &::test_q_multiple_pick_list ) );
  return test;
}




