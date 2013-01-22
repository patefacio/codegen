/******************************************************************************
 * table_meta_data.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file table_meta_data.hpp
 *
 * \brief Metadata for a table - its shape and header
 * 
 */
#ifndef _FCS_TABLE_TABLE_META_DATA_H_
#define _FCS_TABLE_TABLE_META_DATA_H_

#include "fcs/table/table.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <iostream>

namespace fcs {
namespace table {

  //! Metadata for a table - its shape and header
  class Table_meta_data 
  {
  public:

    explicit Table_meta_data(
      Table_shape_t const& shape,
      Table_header_t const& header = Table_header_t(),
      bool may_grow = false
    ) :
      shape_(shape),
      header_(header),
      may_grow_(may_grow)
    {
    }

    Table_meta_data() :
      shape_(),
      header_(Table_header_t()),
      may_grow_(false) 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Table_meta_data const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Table_shape_t const& shape() const {
      return shape_;
    }

    void shape(Table_shape_t const& val) {
      shape_ = val;
    }

    Table_shape_t & shape() {
      return shape_;
    }

    Table_header_t const& header() const {
      return header_;
    }

    void header(Table_header_t const& val) {
      header_ = val;
    }

    Table_header_t & header() {
      return header_;
    }

    bool may_grow() const {
      return may_grow_;
    }

  protected:
    //! Ordered list of datatypes for each column <I>read/write</I>
    Table_shape_t shape_;
    //! Ordered list of column header text <I>read/write</I>
    Table_header_t header_;
    //! If true indicates data_set may grow increase over time <I>read only</I>
    bool may_grow_;
  };

  // Support for streaming non-static streamable members of Table_meta_data
  inline
  std::ostream& operator<<(std::ostream& out, Table_meta_data const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Table_meta_data:(" << &item << "):{";
    out << '\n' << indent << "  shape:" << item.shape_;
    out << '\n' << indent << "  header:" << item.header_;
    out << '\n' << indent << "  may_grow:" << item.may_grow_;
    out << indent << "}\n";
    return out;
  } 

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TABLE_META_DATA_H_
