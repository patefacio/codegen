/******************************************************************************
 * cache_configurations.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file cache_configurations.hpp
 *
 * \brief Database object relational model support for table <em>cache_configurations</em>
 * 
 */
#ifndef _FCS_ORM_SYSTEM_TABLE_CACHE_CONFIGURATIONS_H_
#define _FCS_ORM_SYSTEM_TABLE_CACHE_CONFIGURATIONS_H_

#include <pantheios/pantheios.hpp>
#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/system/connection_system.hpp"
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


  //! Encapsulates fields not in primary key of table <em>cache_configurations</em>
  class Cache_configurations_value 
  {
  public:

    // Class enumerations
    enum Cache_configurations_value_fields {
      SIZE_KILOBYTES_FIELD,
      SPEED_FIELD
    };

    // Number of entries in Cache_configurations_value_fields
    enum { CACHE_CONFIGURATIONS_VALUE_FIELDS_NUMBER_ENTRIES = 2 };

    friend inline char const* to_c_str(Cache_configurations_value::Cache_configurations_value_fields e) {
      char const* values[] = {
        "SIZE_KILOBYTES_FIELD",
        "SPEED_FIELD"
      };
      size_t index(e);
      return ((index < CACHE_CONFIGURATIONS_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_CACHE_CONFIGURATIONS_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Cache_configurations_value::Cache_configurations_value_fields e) {
      return out << to_c_str(e);
    }

    Cache_configurations_value(
      boost::int32_t size_kilobytes,
      double speed
    ) :
      size_kilobytes_(size_kilobytes),
      speed_(speed)
    {
    }

    Cache_configurations_value() :
      size_kilobytes_(boost::int32_t()),
      speed_(double()) 
    {
    }

    bool operator<(Cache_configurations_value const& rhs) const {
        return
            ((size_kilobytes_ != rhs.size_kilobytes_)? size_kilobytes_ < rhs.size_kilobytes_ : (
            ((speed_ != rhs.speed_)? speed_ < rhs.speed_ : (false
            ))));
    }

    bool operator==(Cache_configurations_value const& rhs) const {
        return
            ((this==&rhs) or (
            (size_kilobytes_ == rhs.size_kilobytes_) and
            (speed_ == rhs.speed_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("size_kilobytes_");
      out.push_back("speed_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(size_kilobytes_));
      out.push_back(boost::lexical_cast< std::string >(speed_));
    }
    friend std::ostream& operator<<(std::ostream& out, Cache_configurations_value const& item);

    boost::int32_t size_kilobytes_;
    double speed_;
  };

  // Support for streaming non-static streamable members of Cache_configurations_value
  inline
  std::ostream& operator<<(std::ostream& out, Cache_configurations_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Cache_configurations_value:(" << &item << "):{";
    out << '\n' << indent << "  size_kilobytes:" << item.size_kilobytes_;
    out << '\n' << indent << "  speed:" << item.speed_;
    out << indent << "}\n";
    return out;
  } 


  //! Encapsulates fields in primary key of table <em>cache_configurations</em>
  class Cache_configurations_pkey 
  {
  public:

    explicit Cache_configurations_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Cache_configurations_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Cache_configurations_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Cache_configurations_pkey const& rhs) const {
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
    friend std::ostream& operator<<(std::ostream& out, Cache_configurations_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Cache_configurations_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Cache_configurations_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Cache_configurations_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>cache_configurations</em>
  class Cache_configurations_value_update :
    public std::map< Cache_configurations_value::Cache_configurations_value_fields, boost::any > 
  {
  public:

    Cache_configurations_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Cache_configurations_value_update(Cache_configurations_value const& first, Cache_configurations_value const& second) {
      if(!(first.size_kilobytes_ == second.size_kilobytes_)) {
        size_kilobytes(second.size_kilobytes_);
      }
      if(!(first.speed_ == second.speed_)) {
        speed(second.speed_);
      }
    }

    void size_kilobytes(boost::int32_t const& val) {
      this->operator[](Cache_configurations_value::SIZE_KILOBYTES_FIELD) = val;  
    }
    void speed(double const& val) {
      this->operator[](Cache_configurations_value::SPEED_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Cache_configurations_value::Cache_configurations_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Cache_configurations_value::SIZE_KILOBYTES_FIELD)) != this->end()) {
        out << "-- size_kilobytes => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Cache_configurations_value::SPEED_FIELD)) != this->end()) {
        out << "-- speed => " << boost::any_cast< double const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>cache_configurations</em>
  template < typename PKEY_LIST_TYPE = std::list< Cache_configurations_pkey >,
             typename VALUE_LIST_TYPE = std::list< Cache_configurations_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Cache_configurations :
    public fcs::patterns::Singleton< Cache_configurations< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Cache_configurations_pkey Pkey_t;
    typedef Cache_configurations_value Value_t;
    typedef Cache_configurations_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Cache_configurations_pkey, Cache_configurations_value > Row_t;
    typedef std::list< Row_t > Row_list_t;

  protected:

    Cache_configurations() :
      connection_(Connection_system::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Cache_configurations public header section>
// end <Cache_configurations public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Cache_configurations >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Cache_configurations >(values, out);
    }

    static std::string table_name() {
      return std::string("cache_configurations");
    }

    static char const* value_field_name(Cache_configurations_value::Cache_configurations_value_fields field) {
      char const* value_field_names[] = {
        "size_kilobytes",
        "speed"
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
      otl_stream stream(1, "SELECT COUNT(*) FROM cache_configurations", *connection_);
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
        "size_kilobytes, "
        "speed "
        "FROM cache_configurations ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Cache_configurations_pkey & pkey(row.first);
        Cache_configurations_value & value(row.second);
        stream
          >> pkey.id_
          >> value.size_kilobytes_
          >> value.speed_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Cache_configurations_pkey const& desideratum, Cache_configurations_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "size_kilobytes, "
        "speed "
        "FROM cache_configurations "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << desideratum.id_
        ;

      while(!stream.eof()) {
        stream
          >> found.size_kilobytes_
          >> found.speed_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Cache_configurations_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM cache_configurations "
        "WHERE "
        "size_kilobytes = :size_kilobytes<int> AND " 
        "speed = :speed<double>", *connection_);

      stream 
        << desideratum.second.size_kilobytes_
        << desideratum.second.speed_
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
      otl_stream stream(50, "INSERT INTO cache_configurations (" 
        "size_kilobytes," 
        "speed"
        ") VALUES ("
        ":size_kilobytes<int>," 
        ":speed<double>)", *connection_);

      stream 
        << nascent.second.size_kilobytes_
        << nascent.second.speed_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO cache_configurations (" 
        "id," 
        "size_kilobytes," 
        "speed"
        ") VALUES ("
        ":id<char[3]>," 
        ":size_kilobytes<int>," 
        ":speed<double>)", *connection_);

      Row_list_t::const_iterator it(nascent.begin());
      Row_list_t::const_iterator end(nascent.end());

      for(; it != end; ++it) {
        stream 
          << "" // auto_id - id leave blank
          << it->second.size_kilobytes_
          << it->second.speed_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE cache_configurations SET " 
        "size_kilobytes=:size_kilobytes<int>," 
        "speed=:speed<double>"
        " WHERE "
        "id=:id<int>", *connection_);

      Row_list_t::const_iterator it(changing.begin());
      Row_list_t::const_iterator end(changing.end());

      for(; it != end; ++it) {
        stream 
          << it->second.size_kilobytes_
          << it->second.speed_
          << it->first.id_
          ;
      }
    }

    inline void update(Cache_configurations_pkey const& changing, 
                       Cache_configurations_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE cache_configurations SET ";
        Cache_configurations_value_update::const_iterator begin(updates.begin());
        Cache_configurations_value_update::const_iterator it(updates.begin());
        Cache_configurations_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Cache_configurations_value::SIZE_KILOBYTES_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Cache_configurations_value::SPEED_FIELD: {
              sql_statement << boost::any_cast< double const& >(it->second);
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

    inline void delete_row(Cache_configurations_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM cache_configurations "
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
        std::string delete_statement("DELETE FROM cache_configurations ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM cache_configurations"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Cache_configurations >;
  };

} // namespace table
} // namespace system
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_SYSTEM_TABLE_CACHE_CONFIGURATIONS_H_
