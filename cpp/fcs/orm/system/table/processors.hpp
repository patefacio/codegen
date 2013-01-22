/******************************************************************************
 * processors.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file processors.hpp
 *
 * \brief Database object relational model support for table <em>processors</em>
 * 
 */
#ifndef _FCS_ORM_SYSTEM_TABLE_PROCESSORS_H_
#define _FCS_ORM_SYSTEM_TABLE_PROCESSORS_H_

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


  //! Encapsulates fields not in primary key of table <em>processors</em>
  class Processors_value 
  {
  public:

    // Class enumerations
    enum Processors_value_fields {
      NAME_FIELD,
      VENDOR_ID_FIELD,
      CACHE_CONFIGURATION_ID_FIELD,
      NUM_CORES_FIELD,
      CPU_FAMILY_FIELD,
      BUS_SPEED_FIELD
    };

    // Number of entries in Processors_value_fields
    enum { PROCESSORS_VALUE_FIELDS_NUMBER_ENTRIES = 6 };

    friend inline char const* to_c_str(Processors_value::Processors_value_fields e) {
      char const* values[] = {
        "NAME_FIELD",
        "VENDOR_ID_FIELD",
        "CACHE_CONFIGURATION_ID_FIELD",
        "NUM_CORES_FIELD",
        "CPU_FAMILY_FIELD",
        "BUS_SPEED_FIELD"
      };
      size_t index(e);
      return ((index < PROCESSORS_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_PROCESSORS_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Processors_value::Processors_value_fields e) {
      return out << to_c_str(e);
    }

    Processors_value(
      fcs::utils::Fixed_size_char_array< 64 > const& name,
      boost::int32_t vendor_id,
      boost::int32_t cache_configuration_id,
      boost::int32_t num_cores,
      fcs::utils::Fixed_size_char_array< 16 > const& cpu_family,
      double bus_speed
    ) :
      name_(name),
      vendor_id_(vendor_id),
      cache_configuration_id_(cache_configuration_id),
      num_cores_(num_cores),
      cpu_family_(cpu_family),
      bus_speed_(bus_speed)
    {
    }

    Processors_value() :
      name_(fcs::utils::Fixed_size_char_array< 64 >()),
      vendor_id_(boost::int32_t()),
      cache_configuration_id_(boost::int32_t()),
      num_cores_(boost::int32_t()),
      cpu_family_(fcs::utils::Fixed_size_char_array< 16 >()),
      bus_speed_(double()) 
    {
    }

    bool operator<(Processors_value const& rhs) const {
        return
            ((name_ != rhs.name_)? name_ < rhs.name_ : (
            ((vendor_id_ != rhs.vendor_id_)? vendor_id_ < rhs.vendor_id_ : (
            ((cache_configuration_id_ != rhs.cache_configuration_id_)? cache_configuration_id_ < rhs.cache_configuration_id_ : (
            ((num_cores_ != rhs.num_cores_)? num_cores_ < rhs.num_cores_ : (
            ((cpu_family_ != rhs.cpu_family_)? cpu_family_ < rhs.cpu_family_ : (
            ((bus_speed_ != rhs.bus_speed_)? bus_speed_ < rhs.bus_speed_ : (false
            ))))))))))));
    }

    bool operator==(Processors_value const& rhs) const {
        return
            ((this==&rhs) or (
            (name_ == rhs.name_) and
            (vendor_id_ == rhs.vendor_id_) and
            (cache_configuration_id_ == rhs.cache_configuration_id_) and
            (num_cores_ == rhs.num_cores_) and
            (cpu_family_ == rhs.cpu_family_) and
            (bus_speed_ == rhs.bus_speed_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("name_");
      out.push_back("vendor_id_");
      out.push_back("cache_configuration_id_");
      out.push_back("num_cores_");
      out.push_back("cpu_family_");
      out.push_back("bus_speed_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(name_));
      out.push_back(boost::lexical_cast< std::string >(vendor_id_));
      out.push_back(boost::lexical_cast< std::string >(cache_configuration_id_));
      out.push_back(boost::lexical_cast< std::string >(num_cores_));
      out.push_back(boost::lexical_cast< std::string >(cpu_family_));
      out.push_back(boost::lexical_cast< std::string >(bus_speed_));
    }
    friend std::ostream& operator<<(std::ostream& out, Processors_value const& item);

    fcs::utils::Fixed_size_char_array< 64 > name_;
    boost::int32_t vendor_id_;
    boost::int32_t cache_configuration_id_;
    boost::int32_t num_cores_;
    fcs::utils::Fixed_size_char_array< 16 > cpu_family_;
    double bus_speed_;
  };

  // Support for streaming non-static streamable members of Processors_value
  inline
  std::ostream& operator<<(std::ostream& out, Processors_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Processors_value:(" << &item << "):{";
    out << '\n' << indent << "  name:" << item.name_;
    out << '\n' << indent << "  vendor_id:" << item.vendor_id_;
    out << '\n' << indent << "  cache_configuration_id:" << item.cache_configuration_id_;
    out << '\n' << indent << "  num_cores:" << item.num_cores_;
    out << '\n' << indent << "  cpu_family:" << item.cpu_family_;
    out << '\n' << indent << "  bus_speed:" << item.bus_speed_;
    out << indent << "}\n";
    return out;
  } 


  //! Encapsulates fields in primary key of table <em>processors</em>
  class Processors_pkey 
  {
  public:

    explicit Processors_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Processors_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Processors_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Processors_pkey const& rhs) const {
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
    friend std::ostream& operator<<(std::ostream& out, Processors_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Processors_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Processors_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Processors_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>processors</em>
  class Processors_value_update :
    public std::map< Processors_value::Processors_value_fields, boost::any > 
  {
  public:

    Processors_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Processors_value_update(Processors_value const& first, Processors_value const& second) {
      if(!(first.name_ == second.name_)) {
        name(second.name_);
      }
      if(!(first.vendor_id_ == second.vendor_id_)) {
        vendor_id(second.vendor_id_);
      }
      if(!(first.cache_configuration_id_ == second.cache_configuration_id_)) {
        cache_configuration_id(second.cache_configuration_id_);
      }
      if(!(first.num_cores_ == second.num_cores_)) {
        num_cores(second.num_cores_);
      }
      if(!(first.cpu_family_ == second.cpu_family_)) {
        cpu_family(second.cpu_family_);
      }
      if(!(first.bus_speed_ == second.bus_speed_)) {
        bus_speed(second.bus_speed_);
      }
    }

    void name(fcs::utils::Fixed_size_char_array< 64 > const& val) {
      this->operator[](Processors_value::NAME_FIELD) = val;  
    }
    void vendor_id(boost::int32_t const& val) {
      this->operator[](Processors_value::VENDOR_ID_FIELD) = val;  
    }
    void cache_configuration_id(boost::int32_t const& val) {
      this->operator[](Processors_value::CACHE_CONFIGURATION_ID_FIELD) = val;  
    }
    void num_cores(boost::int32_t const& val) {
      this->operator[](Processors_value::NUM_CORES_FIELD) = val;  
    }
    void cpu_family(fcs::utils::Fixed_size_char_array< 16 > const& val) {
      this->operator[](Processors_value::CPU_FAMILY_FIELD) = val;  
    }
    void bus_speed(double const& val) {
      this->operator[](Processors_value::BUS_SPEED_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Processors_value::Processors_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Processors_value::NAME_FIELD)) != this->end()) {
        out << "-- name => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 64 > const& >(found->second) << '\n';
      }
      if((found = this->find(Processors_value::VENDOR_ID_FIELD)) != this->end()) {
        out << "-- vendor_id => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Processors_value::CACHE_CONFIGURATION_ID_FIELD)) != this->end()) {
        out << "-- cache_configuration_id => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Processors_value::NUM_CORES_FIELD)) != this->end()) {
        out << "-- num_cores => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Processors_value::CPU_FAMILY_FIELD)) != this->end()) {
        out << "-- cpu_family => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 16 > const& >(found->second) << '\n';
      }
      if((found = this->find(Processors_value::BUS_SPEED_FIELD)) != this->end()) {
        out << "-- bus_speed => " << boost::any_cast< double const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>processors</em>
  template < typename PKEY_LIST_TYPE = std::list< Processors_pkey >,
             typename VALUE_LIST_TYPE = std::list< Processors_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Processors :
    public fcs::patterns::Singleton< Processors< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Processors_pkey Pkey_t;
    typedef Processors_value Value_t;
    typedef Processors_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Processors_pkey, Processors_value > Row_t;
    typedef std::list< Row_t > Row_list_t;

  protected:

    Processors() :
      connection_(Connection_system::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Processors public header section>
// end <Processors public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Processors >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Processors >(values, out);
    }

    static std::string table_name() {
      return std::string("processors");
    }

    static char const* value_field_name(Processors_value::Processors_value_fields field) {
      char const* value_field_names[] = {
        "name",
        "vendor_id",
        "cache_configuration_id",
        "num_cores",
        "cpu_family",
        "bus_speed"
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
      otl_stream stream(1, "SELECT COUNT(*) FROM processors", *connection_);
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
        "vendor_id, "
        "cache_configuration_id, "
        "num_cores, "
        "cpu_family, "
        "bus_speed "
        "FROM processors ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Processors_pkey & pkey(row.first);
        Processors_value & value(row.second);
        stream
          >> pkey.id_
          >> value.name_
          >> value.vendor_id_
          >> value.cache_configuration_id_
          >> value.num_cores_
          >> value.cpu_family_
          >> value.bus_speed_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Processors_pkey const& desideratum, Processors_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "name, "
        "vendor_id, "
        "cache_configuration_id, "
        "num_cores, "
        "cpu_family, "
        "bus_speed "
        "FROM processors "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << desideratum.id_
        ;

      while(!stream.eof()) {
        stream
          >> found.name_
          >> found.vendor_id_
          >> found.cache_configuration_id_
          >> found.num_cores_
          >> found.cpu_family_
          >> found.bus_speed_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Processors_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM processors "
        "WHERE "
        "name = :name<char[64]> AND " 
        "vendor_id = :vendor_id<int> AND " 
        "cache_configuration_id = :cache_configuration_id<int> AND " 
        "num_cores = :num_cores<int> AND " 
        "cpu_family = :cpu_family<char[16]> AND " 
        "bus_speed = :bus_speed<double>", *connection_);

      stream 
        << desideratum.second.name_
        << desideratum.second.vendor_id_
        << desideratum.second.cache_configuration_id_
        << desideratum.second.num_cores_
        << desideratum.second.cpu_family_
        << desideratum.second.bus_speed_
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
      otl_stream stream(50, "INSERT INTO processors (" 
        "name," 
        "vendor_id," 
        "cache_configuration_id," 
        "num_cores," 
        "cpu_family," 
        "bus_speed"
        ") VALUES ("
        ":name<char[64]>," 
        ":vendor_id<int>," 
        ":cache_configuration_id<int>," 
        ":num_cores<int>," 
        ":cpu_family<char[16]>," 
        ":bus_speed<double>)", *connection_);

      stream 
        << nascent.second.name_
        << nascent.second.vendor_id_
        << nascent.second.cache_configuration_id_
        << nascent.second.num_cores_
        << nascent.second.cpu_family_
        << nascent.second.bus_speed_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO processors (" 
        "id," 
        "name," 
        "vendor_id," 
        "cache_configuration_id," 
        "num_cores," 
        "cpu_family," 
        "bus_speed"
        ") VALUES ("
        ":id<char[3]>," 
        ":name<char[64]>," 
        ":vendor_id<int>," 
        ":cache_configuration_id<int>," 
        ":num_cores<int>," 
        ":cpu_family<char[16]>," 
        ":bus_speed<double>)", *connection_);

      Row_list_t::const_iterator it(nascent.begin());
      Row_list_t::const_iterator end(nascent.end());

      for(; it != end; ++it) {
        stream 
          << "" // auto_id - id leave blank
          << it->second.name_
          << it->second.vendor_id_
          << it->second.cache_configuration_id_
          << it->second.num_cores_
          << it->second.cpu_family_
          << it->second.bus_speed_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE processors SET " 
        "name=:name<char[64]>," 
        "vendor_id=:vendor_id<int>," 
        "cache_configuration_id=:cache_configuration_id<int>," 
        "num_cores=:num_cores<int>," 
        "cpu_family=:cpu_family<char[16]>," 
        "bus_speed=:bus_speed<double>"
        " WHERE "
        "id=:id<int>", *connection_);

      Row_list_t::const_iterator it(changing.begin());
      Row_list_t::const_iterator end(changing.end());

      for(; it != end; ++it) {
        stream 
          << it->second.name_
          << it->second.vendor_id_
          << it->second.cache_configuration_id_
          << it->second.num_cores_
          << it->second.cpu_family_
          << it->second.bus_speed_
          << it->first.id_
          ;
      }
    }

    inline void update(Processors_pkey const& changing, 
                       Processors_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE processors SET ";
        Processors_value_update::const_iterator begin(updates.begin());
        Processors_value_update::const_iterator it(updates.begin());
        Processors_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Processors_value::NAME_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 64 > const& >(it->second));
              break;
            }
            case Processors_value::VENDOR_ID_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Processors_value::CACHE_CONFIGURATION_ID_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Processors_value::NUM_CORES_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Processors_value::CPU_FAMILY_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 16 > const& >(it->second));
              break;
            }
            case Processors_value::BUS_SPEED_FIELD: {
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

    inline void delete_row(Processors_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM processors "
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
        std::string delete_statement("DELETE FROM processors ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM processors"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Processors >;
  };

} // namespace table
} // namespace system
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_SYSTEM_TABLE_PROCESSORS_H_
