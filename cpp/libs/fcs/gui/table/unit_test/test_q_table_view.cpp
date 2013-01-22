/******************************************************************************
 * test_q_table_view.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_q_table_view.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/gui/table/q_table_view.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/table/test/random_table_generator.hpp"
#include <QApplication>

class Test_item_data_role_handler : public fcs::gui::table::Q_item_data_role_handler {

public:
  Test_item_data_role_handler() : Q_item_data_role_handler(Q_item_data_role_handler::ROLE_FORMAT_DATA_FUNCTION | 
                                                           Q_item_data_role_handler::ROLE_OVERRIDE_DATA_FUNCTION) {
  }

  virtual QVariant format(QModelIndex const& index, int role, fcs::table::Cell_contents_t const& cell_contents) {
    switch(role) {
     case Qt::TextAlignmentRole: {
       if(0 == (index.row() % 2)) {
         return QVariant(Qt::AlignRight | Qt::AlignVCenter);
       } else {
         return QVariant(Qt::AlignLeft);
       }
       break;
     }
     case Qt::BackgroundColorRole: {
       if(0 == (index.column() %2)) {
         QRadialGradient gradient(50, 50, 50, 50, 50);
         gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
         gradient.setColorAt(1, QColor::fromRgbF(0, 0, 1, 0));
         QBrush brush(gradient);
         return QVariant(brush);
       } else {
         return QVariant();
       }
     }
     case Qt::ForegroundRole: {
       if(0 == (index.row() %2)) {
         QBrush brush(Qt::red);
         return QVariant(brush);
       } else {
         return QVariant();
       }
     }
     case Qt::CheckStateRole: {
       if(0 == (index.row() % 3) or (index.column() == 3)) {
         return QVariant(Qt::Checked);
       } else if (index.column() == 5) {
         return QVariant(Qt::Unchecked);
       }
       break;
     }
    }
    return QVariant();
  }

  virtual QVariant override_data(QModelIndex const& index, int role, fcs::table::Cell_contents_t const& cell_contents) {
    std::ostringstream contents;
    contents << cell_contents;
    return QVariant(contents.str().c_str());
  }
};

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Q_table_view";

namespace {
  void test_q_table_view() {

// custom <test-detail>

    int argc(0);
    char *argv[0] = {};
    QApplication app(argc, argv);

    using namespace fcs::table;
    using namespace fcs::table::test;
    using namespace fcs::gui::table;
    Random_table_generator random_table_generator(35, 200000);
    Table_model_ptr table_model(random_table_generator.create_memory_table_model());
    fcs::gui::table::Q_item_data_role_handler_ptr role_handler(new Test_item_data_role_handler());

    std::cout << "Formatting with formatter:" << *role_handler << std::endl;

    Q_table_model q_table_model(0, table_model, role_handler);
    Q_table_view q_table_view(0, &q_table_model);
    q_table_view.show();

    Q_table_model q_table_model_2(0, table_model);
    Q_table_view q_table_view_2(0, &q_table_model_2);
    q_table_view_2.show();

    app.exec();

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Q_table_view");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <q_table_view>" );
  test->add( BOOST_TEST_CASE( &::test_q_table_view ) );
  return test;
}




