/******************************************************************************
 * table_model.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file table_model.hpp
 *
 * \brief Basic table model interface
 * 
 */
#ifndef _FCS_TABLE_TABLE_MODEL_H_
#define _FCS_TABLE_TABLE_MODEL_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "fcs/table/table.hpp"
#include "fcs/table/stream_out_visitor.hpp"
#include "fcs/table/table_meta_data.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <boost/variant/apply_visitor.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <iostream>

namespace fcs {
namespace table {


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275)
#endif

  // Forward class declaration
  class Table_model;
  typedef std::shared_ptr< Table_model > Table_model_ptr;
  typedef std::shared_ptr< const Table_model > Table_model_const_ptr;

  //! Basic table model interface
  class Table_model :
    public boost::noncopyable 
  {
  public:

    explicit Table_model(
      Table_meta_data const& meta_data
    ) :
      boost::noncopyable(),
      meta_data_(meta_data)
    {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Table_model(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
    }

    Table_model() :
      meta_data_() 
    {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Table_model(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
    }

    virtual ~Table_model() = 0;

    friend std::ostream& operator<<(std::ostream& out, Table_model const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Table_meta_data const& meta_data() const {
      return meta_data_;
    }

  
// custom <Table_model public header section>

    // \return number of rows
    virtual Index_t row_count() const = 0;

    Index_t column_count() const {
      return meta_data_.header().size();
    }
    virtual void read_cell(Index_t row, Index_t column, Cell_contents_t & cell_contents) const = 0;
    virtual void read_cell(Index_t row, Index_t column, std::string & cell_text) const = 0;

    virtual void read_row(Index_t row, Row_contents_t & row_contents) const = 0;
    virtual void read_column(Index_t column, Column_contents_t & column_contents) const = 0;

    virtual void add_row(Row_contents_ptr const& row) = 0;

    void write_header(std::ostream &out, char column_delimiter = '|', char end_line_delimiter = '\n') const {
      if(column_count()) {
        Table_header_t const& header(meta_data_.header());
        Table_header_t::const_iterator it(header.begin());
        Table_header_t::const_iterator end(--header.end());
        for(; it != end; ++it) {
          out << *it << column_delimiter;
        }
        out << *it << end_line_delimiter;
      }
    }

    void write_data(std::ostream &out, char column_delimiter = '|', char end_line_delimiter = '\n') const {
      Index_t const row_count(this->row_count());
      Index_t const column_count(this->column_count());
      if(row_count && column_count) {
        Index_t const last_row_index(row_count - 1);
        Index_t const last_column_index(column_count - 1);
        Stream_out_visitor stream_out_visitor(out);
        for(Index_t row(0); row < row_count; ++row) {
          for(Index_t column(0); column < column_count; ++column) {
            write_cell_data(row, column, stream_out_visitor);
            write_delimiter_unless_last(column, last_column_index, out, column_delimiter);
          }
          write_delimiter_unless_last(row, last_row_index, out, end_line_delimiter);
        }
      }
    }

    void write_cell_data(Index_t row, Index_t column, Stream_out_visitor &stream_out_visitor) const {
      Cell_contents_t cell_contents;
      read_cell(row, column, cell_contents);
      try {
        boost::apply_visitor(stream_out_visitor, cell_contents);
      } catch(...) {
        // TODO: exception policy
      }
    }

    void write_delimiter_unless_last(Index_t index, Index_t last, std::ostream &out, char delimiter) const {
      if(index != last) {
        out << delimiter;
      }
    }

// end <Table_model public header section>

  protected:
    //! Column type and header data associated with the table <I>read only</I>
    Table_meta_data meta_data_;
  };

  inline Table_model::~Table_model() {
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Destroyed Table_model(",
                   pantheios::hex_ptr(reinterpret_cast< void * >(this)),
                   pantheios::character(')'));
  }

  // Support for streaming non-static streamable members of Table_model
  inline
  std::ostream& operator<<(std::ostream& out, Table_model const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Table_model:(" << &item << "):{";
    out << '\n' << indent << "  meta_data:" << item.meta_data_;
    out << indent << "}\n";
    return out;
  } 

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TABLE_MODEL_H_
