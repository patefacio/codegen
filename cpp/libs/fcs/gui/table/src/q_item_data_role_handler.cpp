/******************************************************************************
 * q_item_data_role_handler.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_item_data_role_handler.cpp
 *
 * \brief 
 * 
 */

#include "fcs/gui/table/q_item_data_role_handler.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>


// custom <Q_item_data_role_handler pre-namespace custom>
// end <Q_item_data_role_handler pre-namespace custom>

namespace fcs {
namespace gui {
namespace table {

  
// custom <Q_item_data_role_handler namespace custom>
// end <Q_item_data_role_handler namespace custom>


  // Member init ctor
  Q_item_data_role_handler::Q_item_data_role_handler(
    int item_data_role_handler_function_mask
  ) :
    item_data_role_handler_function_mask_(item_data_role_handler_function_mask)
  {
  }

  // Support for streaming non-static streamable members of Q_item_data_role_handler
  std::ostream& operator<<(std::ostream& out, Q_item_data_role_handler const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Q_item_data_role_handler:(" << &item << "):{";
  
// custom <item_data_role_handler_function_mask custom streamer>

    out << '\n' << indent << "  item_data_role_handler_function_mask:";
    Q_item_data_role_handler::dump_item_data_role_handler_function(out, item.item_data_role_handler_function_mask_);

// end <item_data_role_handler_function_mask custom streamer>
    out << indent << "}\n";
    return out;
  }
  // Class enumerations
   void Q_item_data_role_handler::dump_item_data_role_handler_function(std::ostream &out, int e) {
    out << '(';
    if(test_item_data_role_handler_function(e, Q_item_data_role_handler::ROLE_FORMAT_DATA_FUNCTION)) {
      out << "ROLE_FORMAT_DATA_FUNCTION,";
    }
    if(test_item_data_role_handler_function(e, Q_item_data_role_handler::ROLE_OVERRIDE_DATA_FUNCTION)) {
      out << "ROLE_OVERRIDE_DATA_FUNCTION,";
    }
    out << ')';
  } 


} // namespace table
} // namespace gui
} // namespace fcs


