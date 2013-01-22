/******************************************************************************
 * delimited_file_table_model.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file delimited_file_table_model.hpp
 *
 * \brief Class that writes delimited (eg csv) files from data from Table_model
 * 
 */
#ifndef _FCS_TABLE_DELIMITED_FILE_TABLE_MODEL_H_
#define _FCS_TABLE_DELIMITED_FILE_TABLE_MODEL_H_

#include "fcs/table/table.hpp"
#include "fcs/table/table_model.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/table/memory_table_model.hpp"
#include "fcs/table/table_cell_string_conversion.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/array.hpp>
#include <fstream>
#include <iostream>

namespace fcs {
namespace table {

  // Public constants
  char const DELIMITER_COMMA(',');
  char const DELIMITER_PIPE('|');
  char const DELIMITER_CARAT('^');
  char const DELIMITER_PERCENT('%');
  char const DELIMITER_NEW_LINE('\n');
  char const DELIMITER_UNSPECIFIED(0);


  //! Class that writes delimited (eg csv) files from data from Table_model
  class Delimited_file_creator 
  {
  public:

    Delimited_file_creator(
      boost::filesystem::path const& file_path,
      Table_model const& table_model,
      char const& column_delimiter = DELIMITER_COMMA,
      char const& end_line_delimiter = DELIMITER_NEW_LINE
    ) :
      file_path_(file_path),
      table_model_(table_model),
      column_delimiter_(column_delimiter),
      end_line_delimiter_(end_line_delimiter)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Delimited_file_creator const& item);

  
// custom <Delimited_file_creator public header section>

    void create_delimited_file() const {
      std::ofstream out(file_path_.string().c_str());
      write_table_header(out);
      write_table_data(out);
    }

// end <Delimited_file_creator public header section>

  private:

  
// custom <Delimited_file_creator private header section>

    void write_table_header(std::ostream &out) const {
      table_model_.write_header(out, column_delimiter_, end_line_delimiter_);
    }

    void write_table_data(std::ostream &out) const {
      table_model_.write_data(out, column_delimiter_, end_line_delimiter_);
    }

    void write_cell_data(Index_t row, Index_t column, Stream_out_visitor &stream_out_visitor) const {
      table_model_.write_cell_data(row, column, stream_out_visitor);
    }

// end <Delimited_file_creator private header section>

    //! Path to file csv to write <I>inaccessible</I>
    boost::filesystem::path file_path_;
    //! Table to read from to write csv data <I>inaccessible</I>
    Table_model const & table_model_;
    //! Column delimiter <I>inaccessible</I>
    char column_delimiter_;
    //! End line delimiter <I>inaccessible</I>
    char end_line_delimiter_;
  };

  // Support for streaming non-static streamable members of Delimited_file_creator
  inline
  std::ostream& operator<<(std::ostream& out, Delimited_file_creator const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Delimited_file_creator:(" << &item << "):{";
    out << '\n' << indent << "  file_path:" << item.file_path_;
    out << '\n' << indent << "  table_model:" << item.table_model_;
    out << '\n' << indent << "  column_delimiter:" << item.column_delimiter_;
    out << '\n' << indent << "  end_line_delimiter:" << item.end_line_delimiter_;
    out << indent << "}\n";
    return out;
  } 


  /**
  Options for reading delimited file into table model 
  */
  class Delimited_file_reader_options 
  {
  public:

    explicit Delimited_file_reader_options(
      int minimum_row_matches_to_accept_delimiter = 5,
      int minimum_row_matches_to_accept_column_type = 5,
      char column_delimiter = DELIMITER_UNSPECIFIED,
      Table_header_t table_header = Table_header_t()
    ) :
      minimum_row_matches_to_accept_delimiter_(minimum_row_matches_to_accept_delimiter),
      minimum_row_matches_to_accept_column_type_(minimum_row_matches_to_accept_column_type),
      column_delimiter_(column_delimiter),
      table_header_(table_header)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Delimited_file_reader_options const& item);

  
// custom <Delimited_file_reader_options public header section>

    int minimum_rows_to_sample() const {
      return std::max(minimum_row_matches_to_accept_column_type_, minimum_row_matches_to_accept_delimiter_);
    }

// end <Delimited_file_reader_options public header section>

    //! Requires this many consistent matches to glean separator <I>open</I>
    int minimum_row_matches_to_accept_delimiter_;
    //! Requires this many consistent matches of cell type to glean column cell type <I>open</I>
    int minimum_row_matches_to_accept_column_type_;
    //! Delimiter to use as field separator when parsing rows <I>open</I>
    char column_delimiter_;
    //! Optional user supplied header - only used if correctly sized <I>open</I>
    Table_header_t table_header_;
  };

  // Support for streaming non-static streamable members of Delimited_file_reader_options
  inline
  std::ostream& operator<<(std::ostream& out, Delimited_file_reader_options const& item) {
    using fcs::utils::streamers::operator<<;
    char const* indent("  ");
    out << '\n' << indent << "Delimited_file_reader_options:(" << &item << "):{";
    out << '\n' << indent << "  minimum_row_matches_to_accept_delimiter:" << item.minimum_row_matches_to_accept_delimiter_;
    out << '\n' << indent << "  minimum_row_matches_to_accept_column_type:" << item.minimum_row_matches_to_accept_column_type_;
    out << '\n' << indent << "  column_delimiter:" << item.column_delimiter_;
    out << '\n' << indent << "  table_header:" << item.table_header_;
    out << indent << "}\n";
    return out;
  } 


  //! Class that reads delimited (eg csv) files from data from Table_model
  /**

  Reads the specified <I>file_path</I> and parses it as a table.
  If a delimiter is not specified it uses basic heuristic to
  attempt to determine the separator.

  */
  class Delimited_file_reader 
  {
  public:

    // Class typedefs
    typedef boost::escaped_list_separator< char > Escaped_list_separator_t;
    typedef boost::tokenizer< Escaped_list_separator_t > Tokenizer_t;

    explicit Delimited_file_reader(
      boost::filesystem::path const& file_path,
      Delimited_file_reader_options const& options = Delimited_file_reader_options()
    ) :
      file_path_(file_path),
      options_(options),
      input_stream_(),
      table_sample_lines_(options_.minimum_rows_to_sample()),
      table_sample_fields_(options_.minimum_rows_to_sample()),
      last_line_fields_read_(),
      escaped_list_separator_(),
      delimiter_(DELIMITER_UNSPECIFIED),
      num_columns_(0),
      table_shape_(),
      first_row_is_data_(false),
      table_model_()
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Delimited_file_reader const& item);

  
// custom <Delimited_file_reader public header section>

    Table_model_const_ptr create_memory_table_model() {
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Attempting to read file:", file_path_.string().c_str());
      if(!table_model_) {
        open_file();
        read_sample_rows();
        if(DELIMITER_UNSPECIFIED == options_.column_delimiter_) {
          determine_column_delimiter();
        } else {
          tokenize_fields_sample_rows();
        }
        determine_shape();
        create_table_model();
        populate_data();
      }
      return table_model_;
    }

// end <Delimited_file_reader public header section>

  private:

  
// custom <Delimited_file_reader private header section>

    static 
    inline void add_table_type_suffix(std::ostream &out, Table_cell_type table_cell_type) {
      switch(table_cell_type) {
       case CELL_TYPE_INT8: {
         out << "(i8)";
         break;
       }
       case CELL_TYPE_INT32: {
         out << "(i32)";
         break;
       }
       case CELL_TYPE_INT64: {
         out << "(i64)";
         break;
       }
       case CELL_TYPE_UINT8: {
         out << "(u8)";
         break;
       }
       case CELL_TYPE_UINT32: {
         out << "(u32)";
         break;
       }
       case CELL_TYPE_UINT64: {
         out << "(u64)";
         break;
       }
       case CELL_TYPE_FLOAT: {
         out << "(f)";
         break;
       }
       case CELL_TYPE_DOUBLE: {
         out << "(d)";
         break;
       }
       case CELL_TYPE_LONG_DOUBLE: {
         out << "(ld)";
         break;
       }
       case CELL_TYPE_STRING: {
         out << "(s)";
         break;
       }
      }
    }

    static
    inline Table_header_t make_generic_table_header(Table_shape_t const& shape) {
      Table_header_t result;
      Table_shape_t::const_iterator it(shape.begin());
      Table_shape_t::const_iterator end(shape.end());
      size_t count(1);
      for(; (it != end); ++it) {
        std::ostringstream txt;
        txt << "C" << count++;
        add_table_type_suffix(txt, *it);
        result.push_back(txt.str());
      }
      return result;
    }

    inline void open_file() {
      input_stream_ = Ifstream_ptr(new std::ifstream(file_path_.string().c_str()));
    }

    inline void read_sample_rows() {
      size_t num_rows_to_read(table_sample_lines_.size());
      bool more_lines(true);
      size_t rows_read(0);
      for(; (rows_read < num_rows_to_read); ) {
        more_lines = std::getline(*input_stream_, table_sample_lines_[rows_read]);
        if(more_lines) {
          ++rows_read;
        } else {
          table_sample_lines_.resize(rows_read);
          table_sample_fields_.resize(rows_read);
          break;
        }
      }
      assert(table_sample_fields_.size() == table_sample_lines_.size());
    }

    inline void determine_column_delimiter() {
      boost::array< char, 4 > potential_delimiters = { 
        {
          DELIMITER_COMMA,
          DELIMITER_PIPE,
          DELIMITER_CARAT,
          DELIMITER_PERCENT 
        }
      };

      for(size_t i(0); (i < potential_delimiters.size()); ++i) {
        char delimiter(potential_delimiters[i]);
        boost::escaped_list_separator< char > separator('\\', delimiter);
        size_t row(0);
        for(; (row < table_sample_lines_.size()); ++row) {
          Tokenizer_t tokens(table_sample_lines_[row], separator);
          size_t potential_num_columns(std::distance(tokens.begin(), tokens.end()));
          if(row) { 
            if(num_columns_ != potential_num_columns) {
              break;
            }
          } else if(num_columns_ > potential_num_columns) {
            break;
          } else {
            num_columns_ = potential_num_columns;
          }
          table_sample_fields_[row].clear();
          std::copy(tokens.begin(), tokens.end(), std::back_inserter(table_sample_fields_[row]));
        }

        if(row == table_sample_lines_.size()) {
          delimiter_ = delimiter;
          escaped_list_separator_ = Escaped_list_separator_t('\\', delimiter_);
          if(num_columns_ > 1) {
            break;
          }
        }
      }
    }

    inline void determine_shape() {
      Index_t const last_sample_data_row_end(table_sample_lines_.size());
      size_t const column_end(num_columns_);

      if(1 == last_sample_data_row_end) {
        // A file with only 1 line is assumed to be a header with no data
        for(size_t column(0); (column < column_end); ++column) {
          table_shape_.push_back(CELL_TYPE_STRING);
        }
      } else {
        Index_t const first_data_row_index(1);
        for(size_t column(0); (column < column_end); ++column) {
          Cell_contents_t cell_contents;
          Table_cell_string_conversion::convert_to_cell(table_sample_fields_[first_data_row_index][column], cell_contents);
          Table_cell_type table_cell_type(Table_cell_type(cell_contents.which()));
          while(not read_column_as_type(first_data_row_index, last_sample_data_row_end, column, table_cell_type)) {
            table_cell_type = downgrade_table_cell_type(table_cell_type);
          }
          table_shape_.push_back(table_cell_type);
        }
      }
    }

    inline void determine_first_row_is_data() {
      if(1 == table_sample_lines_.size()) {
        first_row_is_data_ = false; 
      } else {
        size_t column_end(num_columns_);
        size_t first_row_index(0);
        bool first_row_is_data(true);
        for(size_t column(0); first_row_is_data and (column < column_end); ++column) {
          Cell_contents_t cell_contents;
          first_row_is_data &= Table_cell_string_conversion::convert_to_cell
            (table_sample_fields_[first_row_index][column], table_shape_[column], cell_contents);
        }
        first_row_is_data_ = first_row_is_data;  
      }
    }

    inline Table_header_t determine_header() {
      determine_first_row_is_data();
      Table_header_t header;
      bool valid_user_specified_header(options_.table_header_.size() == table_shape_.size());
      if(valid_user_specified_header) {
        header = options_.table_header_;
      } else if(first_row_is_data_) {
        header = make_generic_table_header(table_shape_);
      } else {
        header = table_sample_fields_[0];
      }
      return header;
    }

    inline void tokenize_fields_from_line(std::string const& line, String_list_t &fields) {
      fields.erase(fields.begin(), fields.end());    
      Tokenizer_t tokens(line, escaped_list_separator_);
      std::copy(tokens.begin(), tokens.end(), std::back_inserter(fields));
    }

    inline void tokenize_fields_sample_rows() {
      for(size_t i(0); (i < table_sample_lines_.size()); ++i) {
        tokenize_fields_from_line(table_sample_lines_[i], table_sample_fields_[i]);
      }
    }

    inline void convert_and_append_data_row(fcs::table::String_list_t const& fields) {
      size_t num_fields(fields.size());
      if(num_fields == table_shape_.size()) {
        Row_contents_ptr row(new Row_contents_t(num_fields));
        for(size_t i(0); (i < num_fields); ++i) {
          Cell_contents_t cell_contents;
          Table_cell_string_conversion::convert_to_cell(fields[i], table_shape_[i], cell_contents);
          (*row)[i] = cell_contents;
        }
        table_model_->add_row(row);
      }
    }

    inline void populate_sample_data() {
      size_t first_data_row(first_row_is_data_? 0 : 1);
      for(size_t i(first_data_row); (i < table_sample_fields_.size()); ++i) {
        convert_and_append_data_row(table_sample_fields_[i]);
      }
    }

    inline void populate_remaining_data() {
      while(not input_stream_->eof()) {
        std::string line;
        std::getline(*input_stream_, line);
        tokenize_fields_from_line(line, last_line_fields_read_);
        convert_and_append_data_row(last_line_fields_read_);
      }
    }

    inline void populate_data() {
      populate_sample_data();
      populate_remaining_data();
    }

    inline void create_table_model() {
      Table_header_t header(determine_header());
      Table_meta_data table_meta_data(table_shape_, header);
      table_model_ = Table_model_ptr(new Memory_table_model(table_meta_data));
    }

    inline Table_cell_type downgrade_table_cell_type(Table_cell_type table_cell_type) const {
      switch(table_cell_type) {
       case CELL_TYPE_INT8:
       case CELL_TYPE_UINT8: {
         return CELL_TYPE_INT32;
       }
       case CELL_TYPE_INT32:
       case CELL_TYPE_UINT32:
       case CELL_TYPE_INT64:
       case CELL_TYPE_UINT64:
       case CELL_TYPE_FLOAT: {  
         return CELL_TYPE_DOUBLE;
       }
       case CELL_TYPE_DOUBLE:
       case CELL_TYPE_LONG_DOUBLE: 
       case CELL_TYPE_STRING: {
         return CELL_TYPE_STRING;
       }
       default: {
         return CELL_TYPE_STRING;
       }
      }
    }

    inline bool read_column_as_type(Index_t row_start, Index_t row_end, 
                                    Index_t column, Table_cell_type table_cell_type) {
      Cell_contents_t cell_contents;
      for(Index_t row(row_start); (row < row_end); ++row) {
        if(not Table_cell_string_conversion::convert_to_cell(table_sample_fields_[row][column], 
                                                             table_cell_type, cell_contents)) {
          return false;
        }

        pantheios::log(PANTHEIOS_SEV_DEBUG, "Read cell(", 
                       pantheios::integer(row), pantheios::character(','), 
                       pantheios::integer(column), pantheios::character(','), 
                       table_sample_fields_[row][column].c_str(), ") as ", 
                       to_c_str(Table_cell_type(cell_contents.which())));

      }
      return true;
    }

// end <Delimited_file_reader private header section>

    //! Path to file csv to read <I>inaccessible</I>
    boost::filesystem::path file_path_;
    //! Options describing how to read and determine column types <I>inaccessible</I>
    Delimited_file_reader_options options_;
    //! File to read table data from <I>inaccessible</I>
    Ifstream_ptr input_stream_;
    //! Sample of first <I>n</I> lines for delimiter and type determination <I>inaccessible</I>
    Line_list_t table_sample_lines_;
    //! Values of fields in sample lines <I>inaccessible</I>
    String_table_t table_sample_fields_;
    //! Last line of fields read <I>inaccessible</I>
    String_list_t last_line_fields_read_;
    //! Separator for tokenizing data <I>inaccessible</I>
    Escaped_list_separator_t escaped_list_separator_;
    //! Field delimiter <I>inaccessible</I>
    char delimiter_;
    //! Number of columns <I>inaccessible</I>
    size_t num_columns_;
    //! Shape determined by reading <I>sample rows</I> <I>inaccessible</I>
    Table_shape_t table_shape_;
    //! Field delimiter <I>inaccessible</I>
    bool first_row_is_data_;
    //! Table model created on read <I>inaccessible</I>
    Table_model_ptr table_model_;
  };

  // Support for streaming non-static streamable members of Delimited_file_reader
  inline
  std::ostream& operator<<(std::ostream& out, Delimited_file_reader const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Delimited_file_reader:(" << &item << "):{";
    out << '\n' << indent << "  file_path:" << item.file_path_;
    out << '\n' << indent << "  options:" << item.options_;
    out << '\n' << indent << "  table_sample_lines:" << item.table_sample_lines_;
    out << '\n' << indent << "  table_sample_fields:" << item.table_sample_fields_;
    out << '\n' << indent << "  last_line_fields_read:" << item.last_line_fields_read_;
    out << '\n' << indent << "  delimiter:" << item.delimiter_;
    out << '\n' << indent << "  num_columns:" << item.num_columns_;
    out << '\n' << indent << "  table_shape:" << item.table_shape_;
    out << '\n' << indent << "  first_row_is_data:" << item.first_row_is_data_;
    out << '\n' << indent << "  table_model:" << item.table_model_;
    out << indent << "}\n";
    return out;
  } 

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_DELIMITED_FILE_TABLE_MODEL_H_
