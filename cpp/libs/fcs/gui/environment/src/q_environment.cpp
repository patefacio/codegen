/******************************************************************************
 * q_environment.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_environment.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters/character.hpp>
#include <pantheios/inserters/integer.hpp>
#include "fcs/gui/environment/q_environment.hpp"
#include "fcs/environment.hpp"
#include "fcs/utils/file_path.hpp"
#include "fcs/utils/streamers/streamers.hpp"
#include "fcs/timestamp.hpp"
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <boost/foreach.hpp>
#include <sstream>


// custom <Q_environment pre-namespace custom>
// end <Q_environment pre-namespace custom>

namespace fcs {
namespace gui {
namespace environment {

  
// custom <Q_environment namespace custom>

  using namespace fcs::environment;

  namespace {
    char const* headers[] = {
      "File",
      "Size",
      "Last Modified",
      "Full Path"
    };
    size_t column_count(sizeof(headers)/sizeof(char const*));
  }

  void Q_environment::populate_variable_list() {
    Environment::Pointer_t env(Environment::get_instance());
    {
      std::ostringstream msg;
      msg << "Current environment:\n" << *env;
      pantheios::log(PANTHEIOS_SEV_DEBUG, msg.str().c_str());
    }
    variable_list_table_->setColumnCount(2);
    variable_list_table_->setRowCount(env->environment().size());
    variable_list_table_->setSortingEnabled(true);    
    variable_list_table_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    variable_list_table_->setAutoFillBackground(true);
    QTableWidgetItem *variableColumnHeader(new QTableWidgetItem(QString("Variable")));
    variable_list_table_->setHorizontalHeaderItem(0, variableColumnHeader);
    variableColumnHeader->setTextAlignment(Qt::AlignLeft);
    QTableWidgetItem *valueColumnHeader(new QTableWidgetItem(QString("Value")));
    valueColumnHeader->setTextAlignment(Qt::AlignLeft);
    variable_list_table_->setHorizontalHeaderItem(1, valueColumnHeader);

    size_t index(0);
    BOOST_FOREACH(Environment_map_t::value_type const& vt, env->environment()) {
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Added Env Var: ", vt.first.c_str());
      variable_list_table_->setItem(index, 0, new QTableWidgetItem(QString(vt.first.c_str())));
      variable_list_table_->setItem(index, 1, new QTableWidgetItem(QString(vt.second.c_str())));
      ++index;
    }
    variable_list_table_->verticalHeader()->hide();
    variable_list_table_->verticalHeader()->setDefaultSectionSize(15);
    variable_list_table_->resizeColumnsToContents();
  }

  void Q_environment::populate_parsed_paths() {
    tree_path_view_->setModel(tree_path_model_);
    path_splitter_->addWidget(tree_path_view_);
    Environment::Pointer_t env(Environment::get_instance());
    using fcs::utils::streamers::operator<<;
    std::cout << *env << std::endl;
  }

  void Q_environment::populate_problem_table() {
    problem_table_->setColumnCount(column_count);
    problem_table_->setRowCount(5);
    problem_table_->setSortingEnabled(true);    
    problem_table_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    problem_table_->setAutoFillBackground(true);
    problem_table_->verticalHeader()->hide();
    problem_table_->verticalHeader()->setDefaultSectionSize(15);

    for(size_t index = 0; index < column_count; ++index) {
      QTableWidgetItem *columnHeader(new QTableWidgetItem(QString(headers[index])));
      columnHeader->setTextAlignment(Qt::AlignLeft);
      problem_table_->setHorizontalHeaderItem(index, columnHeader);
    }

    QBoxLayout *problem_table_box_layout(new QBoxLayout(QBoxLayout::TopToBottom));
    problem_table_box_layout->addWidget(new QLabel("Potential Problem Files in XXX"));
    problem_table_box_layout->addWidget(problem_table_);
    path_splitter_->setLayout(problem_table_box_layout);

  }

// end <Q_environment namespace custom>



  void Q_environment::ctor_member_init() {
    
// custom <Q_environment::init>

    pantheios::log(PANTHEIOS_SEV_DEBUG, "Q_environment ctor");
    Environment::Pointer_t env(Environment::get_instance());
    populate_variable_list();
    populate_parsed_paths();
    populate_problem_table();

    setWindowTitle("Environment variables");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    splitter_->addWidget(variable_list_table_);
    splitter_->addWidget(path_splitter_);
    mainLayout->addWidget(splitter_);
    setLayout(mainLayout);

// end <Q_environment::init>
  }


} // namespace environment
} // namespace gui
} // namespace fcs


