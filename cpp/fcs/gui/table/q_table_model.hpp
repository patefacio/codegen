/******************************************************************************
 * q_table_model.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_table_model.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_GUI_TABLE_Q_TABLE_MODEL_H_
#define _FCS_GUI_TABLE_Q_TABLE_MODEL_H_

#include "fcs/table/table_model.hpp"
#include "fcs/gui/table/q_item_data_role_handler.hpp"
#include <QAbstractTableModel>

namespace fcs {
namespace gui {
namespace table {

  class Q_table_model :
    public QAbstractTableModel 
  {
  public:

    Q_table_model(
      QObject * parent,
      fcs::table::Table_model_const_ptr const& table_model,
      Q_item_data_role_handler_ptr const& item_data_role_handler = Q_item_data_role_handler_ptr()
    );

    ~Q_table_model();

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    bool log_data_access() const {
      return log_data_access_;
    }

    void log_data_access(bool val) {
      log_data_access_ = val;
    }

  
// custom <Q_table_model public header section>

    virtual int rowCount(const QModelIndex&) const {
      return table_model_->row_count();
    }

    virtual int columnCount(const QModelIndex&) const {
      return table_model_->column_count();
    }

    virtual QVariant data(const QModelIndex&, int) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

// end <Q_table_model public header section>

  private:

    //! Initialize the instance
    void ctor_member_init();
  protected:
    //! Data source (model) for the view <I>inaccessible</I>
    fcs::table::Table_model_const_ptr table_model_;
    //! User specified data override/formatting functor <I>inaccessible</I>
    Q_item_data_role_handler_ptr item_data_role_handler_;
  private:
    //! If true logs data access <I>read/write</I>
    bool log_data_access_;
  };

} // namespace table
} // namespace gui
} // namespace fcs
#endif // _FCS_GUI_TABLE_Q_TABLE_MODEL_H_
