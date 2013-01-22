/******************************************************************************
 * code_packages.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file code_packages.hpp
 *
 * \brief Database object relational model support for table <em>code_packages</em>
 * 
 */
#ifndef _FCS_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_H_
#define _FCS_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_H_

#include <pantheios/pantheios.hpp>
#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/code_metrics/connection_code_metrics.hpp"
#include "fcs/utils/fixed_size_char_array.hpp"
#include "fcs/patterns/singleton.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/any.hpp>
#include <boost/cstdint.hpp>
#include <sstream>
#include <vector>
#include <iostream>
#include <iso646.h>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {


  //! Encapsulates fields not in primary key of table <em>code_packages</em>
  class Code_packages_value 
  {
  public:

    // Class enumerations
    enum Code_packages_value_fields {
      NAME_FIELD,
      DESCR_FIELD
    };

    // Number of entries in Code_packages_value_fields
    enum { CODE_PACKAGES_VALUE_FIELDS_NUMBER_ENTRIES = 2 };

    friend inline char const* to_c_str(Code_packages_value::Code_packages_value_fields e) {
      char const* values[] = {
        "NAME_FIELD",
        "DESCR_FIELD"
      };
      size_t index(e);
      return ((index < CODE_PACKAGES_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_CODE_PACKAGES_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Code_packages_value::Code_packages_value_fields e) {
      return out << to_c_str(e);
    }

    Code_packages_value(
      fcs::utils::Fixed_size_char_array< 64 > const& name,
      fcs::utils::Fixed_size_char_array< 256 > const& descr
    ) :
      name_(name),
      descr_(descr)
    {
    }

    Code_packages_value() :
      name_(fcs::utils::Fixed_size_char_array< 64 >()),
      descr_(fcs::utils::Fixed_size_char_array< 256 >()) 
    {
    }

    bool operator<(Code_packages_value const& rhs) const {
        return
            ((name_ != rhs.name_)? name_ < rhs.name_ : (
            ((descr_ != rhs.descr_)? descr_ < rhs.descr_ : (false
            ))));
    }

    bool operator==(Code_packages_value const& rhs) const {
        return
            ((this==&rhs) or (
            (name_ == rhs.name_) and
            (descr_ == rhs.descr_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("name_");
      out.push_back("descr_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(name_));
      out.push_back(boost::lexical_cast< std::string >(descr_));
    }
    friend std::ostream& operator<<(std::ostream& out, Code_packages_value const& item);

    fcs::utils::Fixed_size_char_array< 64 > name_;
    fcs::utils::Fixed_size_char_array< 256 > descr_;
  };

  // Support for streaming non-static streamable members of Code_packages_value
  inline
  std::ostream& operator<<(std::ostream& out, Code_packages_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_packages_value:(" << &item << "):{";
    out << '\n' << indent << "  name:" << item.name_;
    out << '\n' << indent << "  descr:" << item.descr_;
    out << indent << "}\n";
    return out;
  } 


  //! Encapsulates fields in primary key of table <em>code_packages</em>
  class Code_packages_pkey 
  {
  public:

    explicit Code_packages_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Code_packages_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Code_packages_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Code_packages_pkey const& rhs) const {
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
    friend std::ostream& operator<<(std::ostream& out, Code_packages_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Code_packages_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Code_packages_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_packages_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>code_packages</em>
  class Code_packages_value_update :
    public std::map< Code_packages_value::Code_packages_value_fields, boost::any > 
  {
  public:

    Code_packages_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Code_packages_value_update(Code_packages_value const& first, Code_packages_value const& second) {
      if(!(first.name_ == second.name_)) {
        name(second.name_);
      }
      if(!(first.descr_ == second.descr_)) {
        descr(second.descr_);
      }
    }

    void name(fcs::utils::Fixed_size_char_array< 64 > const& val) {
      this->operator[](Code_packages_value::NAME_FIELD) = val;  
    }
    void descr(fcs::utils::Fixed_size_char_array< 256 > const& val) {
      this->operator[](Code_packages_value::DESCR_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Code_packages_value::Code_packages_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Code_packages_value::NAME_FIELD)) != this->end()) {
        out << "-- name => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 64 > const& >(found->second) << '\n';
      }
      if((found = this->find(Code_packages_value::DESCR_FIELD)) != this->end()) {
        out << "-- descr => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 256 > const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>code_packages</em>
  template < typename PKEY_LIST_TYPE = std::vector< Code_packages_pkey >,
             typename VALUE_LIST_TYPE = std::vector< Code_packages_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Code_packages :
    public fcs::patterns::Singleton< Code_packages< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Code_packages_pkey Pkey_t;
    typedef Code_packages_value Value_t;
    typedef Code_packages_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Code_packages_pkey, Code_packages_value > Row_t;
    typedef std::vector< Row_t > Row_list_t;

  protected:

    Code_packages() :
      connection_(Connection_code_metrics::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Code_packages public header section>
// end <Code_packages public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Code_packages >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Code_packages >(values, out);
    }

    static std::string table_name() {
      return std::string("code_packages");
    }

    static char const* value_field_name(Code_packages_value::Code_packages_value_fields field) {
      char const* value_field_names[] = {
        "name",
        "descr"
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
      otl_stream stream(1, "SELECT COUNT(*) FROM code_packages", *connection_);
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
        "name, "
        "descr "
        "FROM code_packages ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Code_packages_pkey & pkey(row.first);
        Code_packages_value & value(row.second);
        stream
          >> pkey.id_
          >> value.name_
          >> value.descr_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Code_packages_pkey const& desideratum, Code_packages_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "name, "
        "descr "
        "FROM code_packages "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << desideratum.id_
        ;

      while(!stream.eof()) {
        stream
          >> found.name_
          >> found.descr_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Code_packages_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM code_packages "
        "WHERE "
        "name = :name<char[64]> AND " 
        "descr = :descr<char[256]>", *connection_);

      stream 
        << desideratum.second.name_
        << desideratum.second.descr_
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
      otl_stream stream(50, "INSERT INTO code_packages (" 
        "name," 
        "descr"
        ") VALUES ("
        ":name<char[64]>," 
        ":descr<char[256]>)", *connection_);

      stream 
        << nascent.second.name_
        << nascent.second.descr_
        ;

    }

    inline void insert_ignore(Row_t const& nascent) {
      otl_stream stream(50, "INSERT IGNORE INTO code_packages (" 
        "name," 
        "descr"
        ") VALUES ("
        ":name<char[64]>," 
        ":descr<char[256]>)", *connection_);

      stream 
        << nascent.second.name_
        << nascent.second.descr_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO code_packages (" 
        "id," 
        "name," 
        "descr"
        ") VALUES ("
        ":id<char[3]>," 
        ":name<char[64]>," 
        ":descr<char[256]>)", *connection_);

      Row_list_t::const_iterator it(nascent.begin());
      Row_list_t::const_iterator end(nascent.end());

      for(; it != end; ++it) {
        stream 
          << "" // auto_id - id leave blank
          << it->second.name_
          << it->second.descr_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE code_packages SET " 
        "name=:name<char[64]>," 
        "descr=:descr<char[256]>"
        " WHERE "
        "id=:id<int>", *connection_);

      Row_list_t::const_iterator it(changing.begin());
      Row_list_t::const_iterator end(changing.end());

      for(; it != end; ++it) {
        stream 
          << it->second.name_
          << it->second.descr_
          << it->first.id_
          ;
      }
    }

    inline void update(Code_packages_pkey const& changing, 
                       Code_packages_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE code_packages SET ";
        Code_packages_value_update::const_iterator begin(updates.begin());
        Code_packages_value_update::const_iterator it(updates.begin());
        Code_packages_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Code_packages_value::NAME_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 64 > const& >(it->second));
              break;
            }
            case Code_packages_value::DESCR_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 256 > const& >(it->second));
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

    inline void delete_row(Code_packages_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM code_packages "
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
        std::string delete_statement("DELETE FROM code_packages ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM code_packages"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Code_packages >;
  };

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_CODE_METRICS_TABLE_CODE_PACKAGES_H_
