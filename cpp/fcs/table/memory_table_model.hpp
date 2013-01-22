/******************************************************************************
 * memory_table_model.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file memory_table_model.hpp
 *
 * \brief Table with only memory backing it up
 * 
 */
#ifndef _FCS_TABLE_MEMORY_TABLE_MODEL_H_
#define _FCS_TABLE_MEMORY_TABLE_MODEL_H_

#include "fcs/table/table.hpp"
#include "fcs/table/table_model.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <iostream>

namespace fcs {
namespace table {

  //! Table with only memory backing it up
  class Memory_table_model :
    public Table_model 
  {
  public:

    explicit Memory_table_model(
      Table_meta_data const& meta_data
    ) :
      Table_model(meta_data),
      table_contents_()
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Memory_table_model const& item);

  
// custom <Memory_table_model public header section>

    Index_t row_count() const {
      return table_contents_.size();
    }

    void add_row(Row_contents_ptr const& row) {
      validate_row(row);
      table_contents_.push_back(row);
    }

    void read_cell(Index_t row, Index_t column, Cell_contents_t & cell_contents) const {
      validate_cell_indices(row, column);
      Row_contents_ptr const& found_row(table_contents_[row]);
      Cell_contents_t const& found_cell((*found_row)[column]);
      cell_contents = found_cell;
    }

    void read_cell(Index_t row, Index_t column, std::string & cell_text) const {
      validate_row_at_index(row);
      Cell_contents_t cell_contents;
      read_cell(row, column, cell_contents);
    }

    void read_row(Index_t row, Row_contents_t & row_contents) const {
      validate_row_at_index(row);
      row_contents = *table_contents_[row];
    }

    void read_column(Index_t column, Column_contents_t & column_contents) const {

    }

    void validate_column_index(Index_t column) const { 
      assert(column < meta_data_.shape().size()); 
    }

    void validate_cell_indices(Index_t row, Index_t column) const { 
      validate_row_index(row); 
      validate_column_index(column); 
    }

    void validate_row_index(Index_t row) const { 
      assert(row < table_contents_.size()); 
    }

    void validate_row_at_index(Index_t row) const { 
      validate_row_index(row);
      validate_row(table_contents_[row]); 
    }

    void validate_row_size(Row_contents_ptr const& row) const { 
      assert(row->size() == meta_data_.header().size()); 
    }

    void validate_row(Row_contents_ptr const& row) const { 
      validate_row_size(row);
      assert(validate_row_types(row)); 
    }

    bool validate_row_types(Row_contents_ptr const& row) const {
      bool result(true);
      Row_contents_t const& row_contents(*row);
      int number_columns(row_contents.size());
      Table_shape_t shape(meta_data_.shape());
      for(int i(0); result && i<number_columns; ++i) {
        assert(result &= (row_contents[i].which() == shape[i]));
      }
      return result;
    }

// end <Memory_table_model public header section>

  private:
    //! Data of the table <I>inaccessible</I>
    Table_contents_t table_contents_;
  };

  // Support for streaming non-static streamable members of Memory_table_model
  inline
  std::ostream& operator<<(std::ostream& out, Memory_table_model const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Memory_table_model:(" << &item << "):{";
    out << '\n' << indent << "  base:" << static_cast<Table_model const&>(item);
    out << '\n' << indent << "  table_contents:" << item.table_contents_;
    out << indent << "}\n";
    return out;
  } 

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_MEMORY_TABLE_MODEL_H_
