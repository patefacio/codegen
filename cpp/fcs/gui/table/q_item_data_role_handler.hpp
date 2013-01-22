/******************************************************************************
 * q_item_data_role_handler.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_item_data_role_handler.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_GUI_TABLE_Q_ITEM_DATA_ROLE_HANDLER_H_
#define _FCS_GUI_TABLE_Q_ITEM_DATA_ROLE_HANDLER_H_

#include "fcs/table/table.hpp"
#include <QAbstractTableModel>
#include <memory>
#include <iosfwd>

namespace fcs {
namespace gui {
namespace table {

  // Forward class declaration
  class Q_item_data_role_handler;
  typedef std::shared_ptr< Q_item_data_role_handler > Q_item_data_role_handler_ptr;

  /**

  Handler that satisfies the data method call on behalf of the view.
  Essentially, takes things that should be view related (formatting,
  data text override) and puts in base class allowing clients to
  override.

  */
  class Q_item_data_role_handler 
  {
  public:

    // Class enumerations
    enum Item_data_role_handler_function {
      ROLE_FORMAT_DATA_FUNCTION = 1,
      ROLE_OVERRIDE_DATA_FUNCTION = 2
    };

    enum { ITEM_DATA_ROLE_HANDLER_FUNCTION_NUMBER_ENTRIES = 2 };

    friend inline bool test_item_data_role_handler_function(int value, Item_data_role_handler_function e) {
      return (e & value) == e;
    }

    friend inline void set_item_data_role_handler_function(int &value, Item_data_role_handler_function e) {
      value |= e;
    }

    friend inline void clear_item_data_role_handler_function(int &value, Item_data_role_handler_function e) {
      value &= ~e;
    }

    //! Fills ostream with comma separated list of mask entries set in Item_data_role_handler_function
    static
    void dump_item_data_role_handler_function(std::ostream &out, int e);

    explicit Q_item_data_role_handler(
      int item_data_role_handler_function_mask
    );

    friend std::ostream& operator<<(std::ostream& out, Q_item_data_role_handler const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    int item_data_role_handler_function_mask() const {
      return item_data_role_handler_function_mask_;
    }

  
// custom <Q_item_data_role_handler public header section>

    inline bool test_handler_function_mask(Item_data_role_handler_function function) {
      return test_item_data_role_handler_function(item_data_role_handler_function_mask_, function);
    }

    virtual QVariant format(QModelIndex const& index, int role, fcs::table::Cell_contents_t const& cell_contents) = 0;

    virtual QVariant override_data(QModelIndex const& index, int role, fcs::table::Cell_contents_t const& cell_contents) = 0;    

// end <Q_item_data_role_handler public header section>

  private:
    //! Determines which functions should be called <I>read only</I>
    int item_data_role_handler_function_mask_;
  };

} // namespace table
} // namespace gui
} // namespace fcs
#endif // _FCS_GUI_TABLE_Q_ITEM_DATA_ROLE_HANDLER_H_
