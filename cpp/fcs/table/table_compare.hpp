/******************************************************************************
 * table_compare.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file table_compare.hpp
 *
 * \brief Basic comparison functionality
 * 
 */
#ifndef _FCS_TABLE_TABLE_COMPARE_H_
#define _FCS_TABLE_TABLE_COMPARE_H_

#include "fcs/table/table.hpp"
#include "fcs/table/stream_out_visitor.hpp"
#include <sstream>

namespace fcs {
namespace table {

// custom <Table_compare namespace begin section>

  template< typename T1, typename T2 >
  bool table_compare_equal(T1 const& table_1, T2 const& table_2, bool strict = true) {
    Index_t num_columns(table_1.column_count());
    Index_t num_rows(table_2.row_count());
    if(num_columns == table_2.column_count()) {
      if(num_rows == table_2.row_count()) {
        for(Index_t column(0); column < num_columns; ++column) {
          for(Index_t row(0); row < num_rows; ++row) {
            Cell_contents_t contents_1;
            Cell_contents_t contents_2;
            table_1.read_cell(row, column, contents_1);
            table_2.read_cell(row, column, contents_2);
            if(strict) {
              if(!(contents_1 == contents_2)) {
                return false;
              }
            } else {
              std::ostringstream s1;
              Stream_out_visitor v1(s1);
              boost::apply_visitor(v1, contents_1);
              std::ostringstream s2;
              Stream_out_visitor v2(s2);
              boost::apply_visitor(v2, contents_2);              
              if(s1.str() != s2.str()) {
                return false;
              }
            }
          }
        }
        return true;
      }
    }

    return false;
  }

// end <Table_compare namespace begin section>



} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TABLE_COMPARE_H_
