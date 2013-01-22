/******************************************************************************
 * vendors.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file vendors.hpp
 *
 * \brief Database object relational model support for table <em>vendors</em>
 * 
 */
#ifndef _FCS_ORM_SYSTEM_TABLE_VENDORS_H_
#define _FCS_ORM_SYSTEM_TABLE_VENDORS_H_

#include <pantheios/pantheios.hpp>
#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/system/connection_system.hpp"
#include "fcs/utils/fixed_size_char_array.hpp"
#include "fcs/patterns/singleton.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/any.hpp>
#include <boost/cstdint.hpp>
#include <sstream>
#include <list>
#include <iostream>
#include <iso646.h>

namespace fcs {
namespace orm {
namespace system {
namespace table {


  //! Encapsulates fields not in primary key of table <em>vendors</em>
  class Vendors_value 
  {
  public:

    // Class enumerations
    enum Vendors_value_fields {
      NAME_FIELD
    };

    // Number of entries in Vendors_value_fields
    enum { VENDORS_VALUE_FIELDS_NUMBER_ENTRIES = 1 };

    friend inline char const* to_c_str(Vendors_value::Vendors_value_fields e) {
      char const* values[] = {
        "NAME_FIELD"
      };
      size_t index(e);
      return ((index < VENDORS_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_VENDORS_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Vendors_value::Vendors_value_fields e) {
      return out << to_c_str(e);
    }

    explicit Vendors_value(
      fcs::utils::Fixed_size_char_array< 32 > const& name
    ) :
      name_(name)
    {
    }

    Vendors_value() :
      name_(fcs::utils::Fixed_size_char_array< 32 >()) 
    {
    }

    bool operator<(Vendors_value const& rhs) const {
        return
            ((name_ != rhs.name_)? name_ < rhs.name_ : (false
            ));
    }

    bool operator==(Vendors_value const& rhs) const {
        return
            ((this==&rhs) or (
            (name_ == rhs.name_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("name_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(name_));
    }
    friend std::ostream& operator<<(std::ostream& out, Vendors_value const& item);

    fcs::utils::Fixed_size_char_array< 32 > name_;
  };

  // Support for streaming non-static streamable members of Vendors_value
  inline
  std::ostream& operator<<(std::ostream& out, Vendors_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Vendors_value:(" << &item << "):{";
    out << '\n' << indent << "  name:" << item.name_;
    out << indent << "}\n";
    return out;
  } 


  //! Encapsulates fields in primary key of table <em>vendors</em>
  class Vendors_pkey 
  {
  public:

    explicit Vendors_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Vendors_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Vendors_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Vendors_pkey const& rhs) const {
        return
            ((this==&rhs) or (
            (id_ == rhs.id_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("id_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(id_));
    }
    friend std::ostream& operator<<(std::ostream& out, Vendors_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Vendors_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Vendors_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Vendors_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>vendors</em>
  class Vendors_value_update :
    public std::map< Vendors_value::Vendors_value_fields, boost::any > 
  {
  public:

    Vendors_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Vendors_value_update(Vendors_value const& first, Vendors_value const& second) {
      if(!(first.name_ == second.name_)) {
        name(second.name_);
      }
    }

    void name(fcs::utils::Fixed_size_char_array< 32 > const& val) {
      this->operator[](Vendors_value::NAME_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Vendors_value::Vendors_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Vendors_value::NAME_FIELD)) != this->end()) {
        out << "-- name => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 32 > const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>vendors</em>
  template < typename PKEY_LIST_TYPE = std::list< Vendors_pkey >,
             typename VALUE_LIST_TYPE = std::list< Vendors_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Vendors :
    public fcs::patterns::Singleton< Vendors< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Vendors_pkey Pkey_t;
    typedef Vendors_value Value_t;
    typedef Vendors_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Vendors_pkey, Vendors_value > Row_t;
    typedef std::list< Row_t > Row_list_t;

  protected:

    Vendors() :
      connection_(Connection_system::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Vendors public header section>
// end <Vendors public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Vendors >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Vendors >(values, out);
    }

    static std::string table_name() {
      return std::string("vendors");
    }

    static char const* value_field_name(Vendors_value::Vendors_value_fields field) {
      char const* value_field_names[] = {
        "name"
      };
      return value_field_names[field];
    }

    static bool has_auto_id() {
      return true;
    }

    int select_last_insert_id() {
      int result(0);
      otl_stream stream(1, "SELECT LAST_INSERT_ID()", *connection_);
      if(!stream.eof()) {
        stream >> result;
      }
      return result;
    }

    int select_affected_row_count() {
      int result(0);
      otl_stream stream(1, "SELECT ROW_COUNT()", *connection_);
      if(!stream.eof()) {
        int signed_result(0);
        stream >> signed_result;
        result = (signed_result < 0)? 0 : signed_result;
      }
      return result;
    }

    int select_table_row_count() {
      int result(0);
      otl_stream stream(1, "SELECT COUNT(*) FROM vendors", *connection_);
      if(!stream.eof()) {
        stream >> result;
      }
      return result;
    }

    inline bool add_where_pkey_clause_max_additions(typename Pkey_list_t::const_iterator &begin,
                                                    typename Pkey_list_t::const_iterator end,
                                                    std::string &sql_stmt, 
                                                    size_t max_additions = 0) {
      bool result(false);
      std::ostringstream msg;
      size_t count(0);
      if(begin != end) {
        msg << "WHERE ";
        while(true) {
          msg << '('
              << "(id = " << begin->id_ << ')'
              << ')';

          ++count;
          ++begin;

          if(begin == end) {
            result = true;
            break;
          } else if(max_additions && (count == max_additions)) {
            result = false;
            break;
          } else {
            msg << " OR ";
          }
        }
      }
      sql_stmt += msg.str();
      return result;
    }

    inline void select_all_rows(Row_list_t &found, std::string const& where_clause = "") {

      std::string select_stmt("SELECT "
        "id, "
        "name "
        "FROM vendors ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Vendors_pkey & pkey(row.first);
        Vendors_value & value(row.second);
        stream
          >> pkey.id_
          >> value.name_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Vendors_pkey const& desideratum, Vendors_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "name "
        "FROM vendors "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << desideratum.id_
        ;

      while(!stream.eof()) {
        stream
          >> found.name_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Vendors_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM vendors "
        "WHERE "
        "name = :name<char[32]>", *connection_);

      stream 
        << desideratum.second.name_
        ;

      bool found(false);
      while(!stream.eof()) {
        found = true;
        stream
          >> desideratum.first.id_
          ;
      }
      return found;
    }

    inline void insert(Row_t const& nascent) {
      otl_stream stream(50, "INSERT INTO vendors (" 
        "name"
        ") VALUES ("
        ":name<char[32]>)", *connection_);

      stream 
        << nascent.second.name_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO vendors (" 
        "id," 
        "name"
        ") VALUES ("
        ":id<char[3]>," 
        ":name<char[32]>)", *connection_);

      Row_list_t::const_iterator it(nascent.begin());
      Row_list_t::const_iterator end(nascent.end());

      for(; it != end; ++it) {
        stream 
          << "" // auto_id - id leave blank
          << it->second.name_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE vendors SET " 
        "name=:name<char[32]>"
        " WHERE "
        "id=:id<int>", *connection_);

      Row_list_t::const_iterator it(changing.begin());
      Row_list_t::const_iterator end(changing.end());

      for(; it != end; ++it) {
        stream 
          << it->second.name_
          << it->first.id_
          ;
      }
    }

    inline void update(Vendors_pkey const& changing, 
                       Vendors_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE vendors SET ";
        Vendors_value_update::const_iterator begin(updates.begin());
        Vendors_value_update::const_iterator it(updates.begin());
        Vendors_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Vendors_value::NAME_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 32 > const& >(it->second));
              break;
            }
          }
        }
        sql_statement 
          << " WHERE "
          << " id = " << changing.id_;
        otl_stream stream(1, sql_statement.str().c_str(), *connection_);
      }
    }

    inline void delete_row(Vendors_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM vendors "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << moribund.id_
        ;
    }

    inline void delete_rows(Pkey_list_t const& moribund, size_t max_per_call = 0) {
      bool more_to_delete(!moribund.empty());
      typename Pkey_list_t::const_iterator it(moribund.begin());
      while(more_to_delete) {
        std::string delete_statement("DELETE FROM vendors ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM vendors"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Vendors >;
  };

} // namespace table
} // namespace system
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_SYSTEM_TABLE_VENDORS_H_
