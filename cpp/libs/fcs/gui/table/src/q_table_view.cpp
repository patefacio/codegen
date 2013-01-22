/******************************************************************************
 * q_table_view.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_table_view.cpp
 *
 * \brief 
 * 
 */

#include "fcs/gui/table/q_table_view.hpp"
#include <QHeaderView>


// custom <Q_table_view pre-namespace custom>
// end <Q_table_view pre-namespace custom>

namespace fcs {
namespace gui {
namespace table {

  
// custom <Q_table_view namespace custom>
// end <Q_table_view namespace custom>



  Q_table_view::~Q_table_view() {
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Destroyed Q_table_view(", 
                   pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                   pantheios::character(')'));
  
// custom <Q_table_view::~Q_table_view>
// end <Q_table_view::~Q_table_view>
  }


  void Q_table_view::ctor_member_init() {
    
// custom <Q_table_view::init>

    setModel(q_table_model_);

// end <Q_table_view::init>
  }


} // namespace table
} // namespace gui
} // namespace fcs


