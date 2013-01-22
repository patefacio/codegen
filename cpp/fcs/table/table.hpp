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
 * \brief Basic Table functionality
 * 
 */
#ifndef _FCS_TABLE_TABLE_H_
#define _FCS_TABLE_TABLE_H_

#include <boost/variant.hpp>
#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

// Forward class declarations
namespace fcs { namespace table {  class Table_model;  } }
namespace fcs { namespace table {  class Table_search;  } }

namespace fcs {
namespace table {

  // Library enumerations
  //! Enumerates the datatypes supported by table
  enum Table_cell_type {
    CELL_TYPE_INT8,
    CELL_TYPE_INT32,
    CELL_TYPE_INT64,
    CELL_TYPE_UINT8,
    CELL_TYPE_UINT32,
    CELL_TYPE_UINT64,
    CELL_TYPE_FLOAT,
    CELL_TYPE_DOUBLE,
    CELL_TYPE_LONG_DOUBLE,
    CELL_TYPE_STRING
  };

  // Number of entries in Table_cell_type
  enum { TABLE_CELL_TYPE_NUMBER_ENTRIES = 10 };

  inline char const* to_c_str(Table_cell_type e) {
    char const* values[] = {
      "CELL_TYPE_INT8",
      "CELL_TYPE_INT32",
      "CELL_TYPE_INT64",
      "CELL_TYPE_UINT8",
      "CELL_TYPE_UINT32",
      "CELL_TYPE_UINT64",
      "CELL_TYPE_FLOAT",
      "CELL_TYPE_DOUBLE",
      "CELL_TYPE_LONG_DOUBLE",
      "CELL_TYPE_STRING"
    };
    size_t index(e);
    return ((index < TABLE_CELL_TYPE_NUMBER_ENTRIES)? values[index] : "INVALID_TABLE_CELL_TYPE");
  }

  inline std::ostream& operator<<(std::ostream &out, Table_cell_type e) {
    return out << to_c_str(e);
  }

  // Library typedefs
  typedef std::shared_ptr< Table_model > Table_model_ptr;
  typedef std::shared_ptr< Table_search > Table_search_ptr;
  typedef boost::variant<
    boost::int8_t, boost::int32_t, boost::int64_t, 
    boost::uint8_t, boost::uint32_t, boost::uint64_t, 
    float, double, long double, 
    std::string > Cell_contents_t;
  typedef size_t Index_t;
  typedef std::pair< Index_t, Index_t > Cell_location_t;
  typedef std::pair< Cell_location_t, Cell_location_t > Cell_location_range_t;
  typedef std::vector< Cell_location_t > Cell_location_list_t;
  typedef std::vector< Cell_contents_t > Row_contents_t;
  typedef std::vector< Cell_contents_t > Column_contents_t;
  typedef std::vector< Column_contents_t > Table_of_cell_contents_t;
  typedef std::vector< Table_cell_type > Table_shape_t;
  typedef std::shared_ptr< Row_contents_t > Row_contents_ptr;
  typedef std::vector< Row_contents_ptr > Table_contents_t;
  typedef std::vector< std::string > Table_header_t;
  typedef std::vector< std::string > Line_list_t;
  typedef std::vector< std::string > String_list_t;
  typedef std::vector< String_list_t > String_table_t;
  typedef boost::function< bool (Cell_contents_t) > Search_functor_t;
  typedef boost::posix_time::ptime Timestamp_t;
  typedef std::shared_ptr< std::ofstream > Ofstream_ptr;
  typedef std::shared_ptr< std::ifstream > Ifstream_ptr;

  //! Name of this api
  inline
  char const* api_name() {
    return "fcs::table::Table";
  }

  //! Description of this api
  inline
  char const* api_description() {
    return "Provides an abstraction for a table - a 2 dimensional matrix of data. Types\n"
  "of data supported are dictated by entries in Cell_contents_t boost::variant.";
  }

  inline
  std::pair< char const*, char const* >
  api_name_and_description() {
    return std::pair< char const*, char const* >(api_name(), api_description()); 
  }

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TABLE_H_
