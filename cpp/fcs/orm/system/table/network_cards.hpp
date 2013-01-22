/******************************************************************************
 * network_cards.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file network_cards.hpp
 *
 * \brief Database object relational model support for table <em>network_cards</em>
 * 
 */
#ifndef _FCS_ORM_SYSTEM_TABLE_NETWORK_CARDS_H_
#define _FCS_ORM_SYSTEM_TABLE_NETWORK_CARDS_H_

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


  //! Encapsulates fields not in primary key of table <em>network_cards</em>
  class Network_cards_value 
  {
  public:

    // Class enumerations
    enum Network_cards_value_fields {
      SPEED_MBPS_FIELD,
      VENDOR_ID_FIELD
    };

    // Number of entries in Network_cards_value_fields
    enum { NETWORK_CARDS_VALUE_FIELDS_NUMBER_ENTRIES = 2 };

    friend inline char const* to_c_str(Network_cards_value::Network_cards_value_fields e) {
      char const* values[] = {
        "SPEED_MBPS_FIELD",
        "VENDOR_ID_FIELD"
      };
      size_t index(e);
      return ((index < NETWORK_CARDS_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_NETWORK_CARDS_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Network_cards_value::Network_cards_value_fields e) {
      return out << to_c_str(e);
    }

    Network_cards_value(
      double speed_mbps,
      boost::int32_t vendor_id
    ) :
      speed_mbps_(speed_mbps),
      vendor_id_(vendor_id)
    {
    }

    Network_cards_value() :
      speed_mbps_(double()),
      vendor_id_(boost::int32_t()) 
    {
    }

    bool operator<(Network_cards_value const& rhs) const {
        return
            ((speed_mbps_ != rhs.speed_mbps_)? speed_mbps_ < rhs.speed_mbps_ : (
            ((vendor_id_ != rhs.vendor_id_)? vendor_id_ < rhs.vendor_id_ : (false
            ))));
    }

    bool operator==(Network_cards_value const& rhs) const {
        return
            ((this==&rhs) or (
            (speed_mbps_ == rhs.speed_mbps_) and
            (vendor_id_ == rhs.vendor_id_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("speed_mbps_");
      out.push_back("vendor_id_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(speed_mbps_));
      out.push_back(boost::lexical_cast< std::string >(vendor_id_));
    }
    friend std::ostream& operator<<(std::ostream& out, Network_cards_value const& item);

    double speed_mbps_;
    boost::int32_t vendor_id_;
  };

  // Support for streaming non-static streamable members of Network_cards_value
  inline
  std::ostream& operator<<(std::ostream& out, Network_cards_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Network_cards_value:(" << &item << "):{";
    out << '\n' << indent << "  speed_mbps:" << item.speed_mbps_;
    out << '\n' << indent << "  vendor_id:" << item.vendor_id_;
    out << indent << "}\n";
    return out;
  } 


  //! Encapsulates fields in primary key of table <em>network_cards</em>
  class Network_cards_pkey 
  {
  public:

    explicit Network_cards_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Network_cards_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Network_cards_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Network_cards_pkey const& rhs) const {
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
    friend std::ostream& operator<<(std::ostream& out, Network_cards_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Network_cards_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Network_cards_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Network_cards_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>network_cards</em>
  class Network_cards_value_update :
    public std::map< Network_cards_value::Network_cards_value_fields, boost::any > 
  {
  public:

    Network_cards_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Network_cards_value_update(Network_cards_value const& first, Network_cards_value const& second) {
      if(!(first.speed_mbps_ == second.speed_mbps_)) {
        speed_mbps(second.speed_mbps_);
      }
      if(!(first.vendor_id_ == second.vendor_id_)) {
        vendor_id(second.vendor_id_);
      }
    }

    void speed_mbps(double const& val) {
      this->operator[](Network_cards_value::SPEED_MBPS_FIELD) = val;  
    }
    void vendor_id(boost::int32_t const& val) {
      this->operator[](Network_cards_value::VENDOR_ID_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Network_cards_value::Network_cards_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Network_cards_value::SPEED_MBPS_FIELD)) != this->end()) {
        out << "-- speed_mbps => " << boost::any_cast< double const& >(found->second) << '\n';
      }
      if((found = this->find(Network_cards_value::VENDOR_ID_FIELD)) != this->end()) {
        out << "-- vendor_id => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>network_cards</em>
  template < typename PKEY_LIST_TYPE = std::list< Network_cards_pkey >,
             typename VALUE_LIST_TYPE = std::list< Network_cards_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Network_cards :
    public fcs::patterns::Singleton< Network_cards< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Network_cards_pkey Pkey_t;
    typedef Network_cards_value Value_t;
    typedef Network_cards_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Network_cards_pkey, Network_cards_value > Row_t;
    typedef std::list< Row_t > Row_list_t;

  protected:

    Network_cards() :
      connection_(Connection_system::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Network_cards public header section>
// end <Network_cards public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Network_cards >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Network_cards >(values, out);
    }

    static std::string table_name() {
      return std::string("network_cards");
    }

    static char const* value_field_name(Network_cards_value::Network_cards_value_fields field) {
      char const* value_field_names[] = {
        "speed_mbps",
        "vendor_id"
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
      otl_stream stream(1, "SELECT COUNT(*) FROM network_cards", *connection_);
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
        "speed_mbps, "
        "vendor_id "
        "FROM network_cards ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Network_cards_pkey & pkey(row.first);
        Network_cards_value & value(row.second);
        stream
          >> pkey.id_
          >> value.speed_mbps_
          >> value.vendor_id_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Network_cards_pkey const& desideratum, Network_cards_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "speed_mbps, "
        "vendor_id "
        "FROM network_cards "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << desideratum.id_
        ;

      while(!stream.eof()) {
        stream
          >> found.speed_mbps_
          >> found.vendor_id_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Network_cards_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM network_cards "
        "WHERE "
        "speed_mbps = :speed_mbps<double> AND " 
        "vendor_id = :vendor_id<int>", *connection_);

      stream 
        << desideratum.second.speed_mbps_
        << desideratum.second.vendor_id_
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
      otl_stream stream(50, "INSERT INTO network_cards (" 
        "speed_mbps," 
        "vendor_id"
        ") VALUES ("
        ":speed_mbps<double>," 
        ":vendor_id<int>)", *connection_);

      stream 
        << nascent.second.speed_mbps_
        << nascent.second.vendor_id_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO network_cards (" 
        "id," 
        "speed_mbps," 
        "vendor_id"
        ") VALUES ("
        ":id<char[3]>," 
        ":speed_mbps<double>," 
        ":vendor_id<int>)", *connection_);

      Row_list_t::const_iterator it(nascent.begin());
      Row_list_t::const_iterator end(nascent.end());

      for(; it != end; ++it) {
        stream 
          << "" // auto_id - id leave blank
          << it->second.speed_mbps_
          << it->second.vendor_id_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE network_cards SET " 
        "speed_mbps=:speed_mbps<double>," 
        "vendor_id=:vendor_id<int>"
        " WHERE "
        "id=:id<int>", *connection_);

      Row_list_t::const_iterator it(changing.begin());
      Row_list_t::const_iterator end(changing.end());

      for(; it != end; ++it) {
        stream 
          << it->second.speed_mbps_
          << it->second.vendor_id_
          << it->first.id_
          ;
      }
    }

    inline void update(Network_cards_pkey const& changing, 
                       Network_cards_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE network_cards SET ";
        Network_cards_value_update::const_iterator begin(updates.begin());
        Network_cards_value_update::const_iterator it(updates.begin());
        Network_cards_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Network_cards_value::SPEED_MBPS_FIELD: {
              sql_statement << boost::any_cast< double const& >(it->second);
              break;
            }
            case Network_cards_value::VENDOR_ID_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
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

    inline void delete_row(Network_cards_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM network_cards "
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
        std::string delete_statement("DELETE FROM network_cards ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM network_cards"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Network_cards >;
  };

} // namespace table
} // namespace system
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_SYSTEM_TABLE_NETWORK_CARDS_H_
