/******************************************************************************
 * table.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file table.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_STREAMERS_TABLE_TABLE_H_
#define _FCS_UTILS_STREAMERS_TABLE_TABLE_H_

#include "fcs/utils/streamers/containers.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/range.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

namespace fcs {
namespace utils {
namespace streamers {
namespace table {

// custom <table pre class section>

  typedef std::vector< std::string > String_list_t;
  typedef std::vector< String_list_t > String_matrix_t;
  typedef std::vector< size_t > Size_list_t;

  inline void grow_string_to(std::string &s, size_t len) {
    s += std::string(len-s.size(), ' ');
  }

  template < typename T >
  inline
  void to_string(T const& t, std::string &result) {
    result = boost::lexical_cast< std::string >(t);
  }

  template < >
  inline
  void to_string(bool const& t, std::string &result) {
    result = (t? "T" : "F");
  }

  template < >
  inline
  void to_string(std::string const& t, std::string &result) {
    result = t;
  }

  inline void print_string_row(std::ostream & out, String_list_t & row, 
                               Size_list_t const& size_list, 
                               char spacer = ' ', char sep = '|') {
    size_t const num_columns(row.size());
    if(num_columns) {
      size_t const last_index(num_columns - 1);
      out << sep << spacer;
      for(size_t column(0); column < num_columns; ++column) {
        grow_string_to(row[column], size_list[column]);
        out << row[column] << spacer << sep;
        if(column != last_index) {
          out << spacer;
        }
      }
      out << '\n';
    }
  }

  template < typename T, typename ALLOC, typename ALLOC_OUTER >
  inline void make_string_matrix(std::vector< std::vector< T, ALLOC >, ALLOC_OUTER > const& v,
                                 String_matrix_t &result) {
    result.clear();
    typename std::vector< std::vector< T, ALLOC >, ALLOC_OUTER >::const_iterator row_it(v.begin());
    typename std::vector< std::vector< T, ALLOC >, ALLOC_OUTER >::const_iterator row_end(v.end());
    for(; row_it != row_end; ++row_it) {
      String_list_t row;
      typename std::vector< T, ALLOC >::const_iterator cell_it(row_it->begin());
      typename std::vector< T, ALLOC >::const_iterator cell_end(row_it->end());
      for(; cell_it != cell_end; ++cell_it) {
        row.push_back(boost::lexical_cast< std::string >(*cell_it));
      }
      result.push_back(row);
    }
  }

  //! Support for streaming std::vector
  template < typename T, typename ALLOC, typename ALLOC_OUTER >
  inline std::ostream& operator<<(std::ostream& out, 
                                  std::vector< std::vector< T, ALLOC >, ALLOC_OUTER > const& matrix) {
    String_matrix_t string_matrix;
    make_string_matrix(matrix, string_matrix);
    out << string_matrix;
    return out;
  }

  template < typename ALLOC, typename ALLOC_OUTER >
  inline std::ostream& operator<<(std::ostream& out, 
                                  std::vector< std::vector< std::string, ALLOC >, ALLOC_OUTER > const& v) {
    typedef std::vector< std::string, ALLOC > Row_t;
    typedef std::vector< Row_t > Row_list_t;
    typedef std::vector< size_t > Size_list_t;
    if(v.size()) {
      size_t column_size(v[0].size());
      Size_list_t size_list(column_size, 0);
      typename Row_list_t::const_iterator row_it(v.begin());
      typename Row_list_t::const_iterator row_end(v.end());
      for( ; row_it != row_end; ++row_it) {
        size_t cell_index(0);
        typename Row_t::const_iterator cell_it(row_it->begin());
        typename Row_t::const_iterator cell_end(row_it->end());
        for( ; cell_it != cell_end; ++cell_it, ++cell_index) {
          size_list[cell_index] = std::max(size_list[cell_index], cell_it->size() + 1);
        }
      }

      row_it = v.begin();
      row_end = v.end();
      for( ; row_it != row_end; ++row_it) {
        Row_t row(*row_it);
        print_string_row(out, row, size_list);
      }        
    }

    return out;
  }

// end <table pre class section>


  // Forward typedefs
  typedef std::vector< std::string > String_list_t;

  //! Prints data in table - like output from database query
  /**

  Takes a table of data - which must be convertible to std::string with
  boost::lexical_cast. Takes an optional header.

  */
  template < typename MatrixContainer,
             typename T = typename MatrixContainer::value_type::value_type > 
  class Table_streamer 
  {
  public:

    // Class typedefs
    typedef typename MatrixContainer::value_type Row_container_t;

    explicit Table_streamer(
      MatrixContainer const& matrix_container,
      String_list_t const& header = String_list_t()
    ) :
      matrix_container_(matrix_container),
      header_(header)
    {
    }

    template <typename MatrixContainer_FRIEND, typename T_FRIEND >
    friend std::ostream& operator<<(std::ostream& out, Table_streamer< MatrixContainer_FRIEND, T_FRIEND > const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    MatrixContainer const& matrix_container() const {
      return matrix_container_;
    }

    String_list_t const& header() const {
      return header_;
    }

  
// custom <Table_streamer public header section>

    inline void print_string_table(std::ostream &out) const {
      String_matrix_t string_matrix;

      if(!matrix_container_.empty()) {
        Row_container_t const& first_row(matrix_container_[0]);
        size_t const num_columns(first_row.size());
        Size_list_t size_list;

        if(!header_.empty()) {
          string_matrix.push_back(header_);
          for(size_t i(0); i < header_.size(); ++i) {
            size_list.push_back(header_[i].size());
          }
        } else {
          size_list.assign(num_columns, 0);
        }

        typename MatrixContainer::const_iterator row_it(matrix_container_.begin());
        typename MatrixContainer::const_iterator row_end(matrix_container_.end());
        using fcs::utils::streamers::operator<<;
        for(; row_it != row_end; ++row_it) {
          String_list_t row;
          typename Row_container_t::const_iterator cell_it(row_it->begin());
          typename Row_container_t::const_iterator cell_end(row_it->end());
          for(size_t i(0); cell_it != cell_end; ++cell_it, ++i) {
            std::string cell_value_text;
            to_string(*cell_it, cell_value_text);
            row.push_back(cell_value_text);
            size_list[i] = std::max(size_list[i], row.back().size());
          }
          string_matrix.push_back(row);
        }

        size_t const num_rows(string_matrix.size());
        std::string const empty;
        String_list_t divider(num_columns, empty);
        for(size_t column(0); column < num_columns; ++column) {
          std::string dashed(size_list[column], '-');
          std::swap(divider[column], dashed);
        }
        print_string_row(out, divider, size_list, '-', '|');
        print_string_row(out, string_matrix[0], size_list);
        print_string_row(out, divider, size_list, '-', '|');
        for(size_t row(1); row < num_rows; ++row) {
          print_string_row(out, string_matrix[row], size_list);        
        }

      }
    }

// end <Table_streamer public header section>

  private:
    MatrixContainer const & matrix_container_;
    String_list_t const & header_;
  };

  // Support for streaming non-static streamable members of Table_streamer
  template < typename MatrixContainer, typename T >
  inline
  std::ostream& operator<<(std::ostream& out, Table_streamer< MatrixContainer, T > const& item) {
  
// custom <Table_streamer custom streamer>

    item.print_string_table(out);

// end <Table_streamer custom streamer>
    return out;
  } 

  
// custom <Table_streamer post class>
// end <Table_streamer post class>

} // namespace table
} // namespace streamers
} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_STREAMERS_TABLE_TABLE_H_
