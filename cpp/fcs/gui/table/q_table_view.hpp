/******************************************************************************
 * q_table_view.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_table_view.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_GUI_TABLE_Q_TABLE_VIEW_H_
#define _FCS_GUI_TABLE_Q_TABLE_VIEW_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "fcs/gui/table/q_table_model.hpp"
#include "fcs/gui/table/q_item_data_role_handler.hpp"
#include <QTableView>

namespace fcs {
namespace gui {
namespace table {

  class Q_table_view :
    public QTableView 
  {
  public:

    Q_table_view(
      QWidget * parent,
      Q_table_model * const& q_table_model,
      Q_item_data_role_handler_ptr const& item_data_role_handler = Q_item_data_role_handler_ptr()
    ) :
      QTableView(parent),
      q_table_model_(q_table_model),
      item_data_role_handler_(item_data_role_handler)
    {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Q_table_view(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
      ctor_member_init();
    }

    ~Q_table_view();

  private:

    //! Initialize the instance
    void ctor_member_init();
  protected:
    //! Data source (model) for the view <I>inaccessible</I>
    Q_table_model * q_table_model_;
    //! User specified data override/formatting functor <I>inaccessible</I>
    Q_item_data_role_handler_ptr item_data_role_handler_;
  };

} // namespace table
} // namespace gui
} // namespace fcs
#endif // _FCS_GUI_TABLE_Q_TABLE_VIEW_H_
