/******************************************************************************
 * orm_to_string_table.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file orm_to_string_table.hpp
 *
 * \brief Functions to turn recordset lists into string lists
 * 
 */
#ifndef _FCS_ORM_ORM_TO_STRING_TABLE_H_
#define _FCS_ORM_ORM_TO_STRING_TABLE_H_

#include "fcs/orm/orm.hpp"
#include "fcs/utils/streamers/table/table.hpp"
#include <string>


// custom <Orm_to_string_table global header section>
// end <Orm_to_string_table global header section>
namespace fcs {
namespace orm {

// custom <Orm_to_string_table pre class section>

  template < typename Recordset > 
  inline void recordset_to_string_table(typename Recordset::Row_list_t const& recordset, String_list_t &header, String_table_t &data) {
    typedef typename Recordset::Pkey_t Pkey_t;
    typedef typename Recordset::Value_t Value_t;
    typename Recordset::Row_list_t::const_iterator it(recordset.begin());
    typename Recordset::Row_list_t::const_iterator end(recordset.end());
    Pkey_t::member_names_list(header);
    Value_t::member_names_list(header);
    for(; it != end; ++it) {
      String_list_t string_list;
      it->first.to_string_list(string_list);
      it->second.to_string_list(string_list);
      data.push_back(string_list);
    }
  }

  template < typename Recordset >
  inline void print_recordset_as_table(typename Recordset::Row_list_t const& recordset, std::ostream &out) {
    String_list_t header;
    String_table_t data;
    recordset_to_string_table< Recordset >(recordset, header, data);
    out << fcs::utils::streamers::table::Table_streamer< String_table_t >(data, header);
  }

  template < typename Recordset > 
  inline void values_to_string_table(typename Recordset::Value_list_t const& values, String_list_t &header, String_table_t &data) {
    typedef typename Recordset::Value_t Value_t;
    typename Recordset::Value_list_t::const_iterator it(values.begin());
    typename Recordset::Value_list_t::const_iterator end(values.end());
    Value_t::member_names_list(header);
    for(; it != end; ++it) {
      String_list_t string_list;
      it->to_string_list(string_list);
      data.push_back(string_list);
    }
  }

  template < typename Recordset >
  inline void print_values_as_table(typename Recordset::Value_list_t const& values, std::ostream &out) {
    String_list_t header;
    String_table_t data;
    values_to_string_table< Recordset >(values, header, data);
    out << fcs::utils::streamers::table::Table_streamer< String_table_t >(data, header);
  }

// end <Orm_to_string_table pre class section>



} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_ORM_TO_STRING_TABLE_H_
