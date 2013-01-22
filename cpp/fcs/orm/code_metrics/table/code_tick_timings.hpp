/******************************************************************************
 * code_tick_timings.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file code_tick_timings.hpp
 *
 * \brief Database object relational model support for table <em>code_tick_timings</em>
 * 
 */
#ifndef _FCS_ORM_CODE_METRICS_TABLE_CODE_TICK_TIMINGS_H_
#define _FCS_ORM_CODE_METRICS_TABLE_CODE_TICK_TIMINGS_H_

#include <pantheios/pantheios.hpp>
#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"
#include "fcs/orm/orm_to_string_table.hpp"
#include "fcs/orm/code_metrics/connection_code_metrics.hpp"
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
namespace code_metrics {
namespace table {


  //! Encapsulates fields not in primary key of table <em>code_tick_timings</em>
  class Code_tick_timings_value 
  {
  public:

    // Class enumerations
    enum Code_tick_timings_value_fields {
      CODE_LOCATIONS_ID_FIELD,
      CREATED_FIELD,
      START_PROCESSOR_FIELD,
      END_PROCESSOR_FIELD,
      CPU_MHZ_FIELD,
      DEBUG_FIELD,
      TICKS_FIELD,
      NORMALIZED_NS_FIELD
    };

    // Number of entries in Code_tick_timings_value_fields
    enum { CODE_TICK_TIMINGS_VALUE_FIELDS_NUMBER_ENTRIES = 8 };

    friend inline char const* to_c_str(Code_tick_timings_value::Code_tick_timings_value_fields e) {
      char const* values[] = {
        "CODE_LOCATIONS_ID_FIELD",
        "CREATED_FIELD",
        "START_PROCESSOR_FIELD",
        "END_PROCESSOR_FIELD",
        "CPU_MHZ_FIELD",
        "DEBUG_FIELD",
        "TICKS_FIELD",
        "NORMALIZED_NS_FIELD"
      };
      size_t index(e);
      return ((index < CODE_TICK_TIMINGS_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_CODE_TICK_TIMINGS_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Code_tick_timings_value::Code_tick_timings_value_fields e) {
      return out << to_c_str(e);
    }

    Code_tick_timings_value(
      boost::int32_t code_locations_id,
      otl_datetime const& created,
      boost::int32_t start_processor,
      boost::int32_t end_processor,
      double cpu_mhz,
      boost::int32_t debug,
      otl_bigint ticks,
      otl_bigint normalized_ns
    ) :
      code_locations_id_(code_locations_id),
      created_(created),
      start_processor_(start_processor),
      end_processor_(end_processor),
      cpu_mhz_(cpu_mhz),
      debug_(debug),
      ticks_(ticks),
      normalized_ns_(normalized_ns)
    {
    }

    Code_tick_timings_value() :
      code_locations_id_(boost::int32_t()),
      created_(otl_datetime()),
      start_processor_(boost::int32_t()),
      end_processor_(boost::int32_t()),
      cpu_mhz_(double()),
      debug_(boost::int32_t()),
      ticks_(otl_bigint()),
      normalized_ns_(otl_bigint()) 
    {
    }

    bool operator<(Code_tick_timings_value const& rhs) const {
        return
            ((code_locations_id_ != rhs.code_locations_id_)? code_locations_id_ < rhs.code_locations_id_ : (
            ((created_ != rhs.created_)? created_ < rhs.created_ : (
            ((start_processor_ != rhs.start_processor_)? start_processor_ < rhs.start_processor_ : (
            ((end_processor_ != rhs.end_processor_)? end_processor_ < rhs.end_processor_ : (
            ((cpu_mhz_ != rhs.cpu_mhz_)? cpu_mhz_ < rhs.cpu_mhz_ : (
            ((debug_ != rhs.debug_)? debug_ < rhs.debug_ : (
            ((ticks_ != rhs.ticks_)? ticks_ < rhs.ticks_ : (
            ((normalized_ns_ != rhs.normalized_ns_)? normalized_ns_ < rhs.normalized_ns_ : (false
            ))))))))))))))));
    }

    bool operator==(Code_tick_timings_value const& rhs) const {
        return
            ((this==&rhs) or (
            (code_locations_id_ == rhs.code_locations_id_) and
            (created_ == rhs.created_) and
            (start_processor_ == rhs.start_processor_) and
            (end_processor_ == rhs.end_processor_) and
            (cpu_mhz_ == rhs.cpu_mhz_) and
            (debug_ == rhs.debug_) and
            (ticks_ == rhs.ticks_) and
            (normalized_ns_ == rhs.normalized_ns_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("code_locations_id_");
      out.push_back("created_");
      out.push_back("start_processor_");
      out.push_back("end_processor_");
      out.push_back("cpu_mhz_");
      out.push_back("debug_");
      out.push_back("ticks_");
      out.push_back("normalized_ns_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_locations_id_));
      out.push_back(boost::lexical_cast< std::string >(created_));
      out.push_back(boost::lexical_cast< std::string >(start_processor_));
      out.push_back(boost::lexical_cast< std::string >(end_processor_));
      out.push_back(boost::lexical_cast< std::string >(cpu_mhz_));
      out.push_back(boost::lexical_cast< std::string >(debug_));
      out.push_back(boost::lexical_cast< std::string >(ticks_));
      out.push_back(boost::lexical_cast< std::string >(normalized_ns_));
    }
    friend std::ostream& operator<<(std::ostream& out, Code_tick_timings_value const& item);

    boost::int32_t code_locations_id_;
    otl_datetime created_;
    boost::int32_t start_processor_;
    boost::int32_t end_processor_;
    double cpu_mhz_;
    boost::int32_t debug_;
    otl_bigint ticks_;
    otl_bigint normalized_ns_;
  };

  // Support for streaming non-static streamable members of Code_tick_timings_value
  inline
  std::ostream& operator<<(std::ostream& out, Code_tick_timings_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_tick_timings_value:(" << &item << "):{";
    out << '\n' << indent << "  code_locations_id:" << item.code_locations_id_;
    out << '\n' << indent << "  created:" << item.created_;
    out << '\n' << indent << "  start_processor:" << item.start_processor_;
    out << '\n' << indent << "  end_processor:" << item.end_processor_;
    out << '\n' << indent << "  cpu_mhz:" << item.cpu_mhz_;
    out << '\n' << indent << "  debug:" << item.debug_;
    out << '\n' << indent << "  ticks:" << item.ticks_;
    out << '\n' << indent << "  normalized_ns:" << item.normalized_ns_;
    out << indent << "}\n";
    return out;
  } 


  //! Encapsulates fields in primary key of table <em>code_tick_timings</em>
  class Code_tick_timings_pkey 
  {
  public:

    explicit Code_tick_timings_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Code_tick_timings_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Code_tick_timings_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Code_tick_timings_pkey const& rhs) const {
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
    friend std::ostream& operator<<(std::ostream& out, Code_tick_timings_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Code_tick_timings_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Code_tick_timings_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_tick_timings_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>code_tick_timings</em>
  class Code_tick_timings_value_update :
    public std::map< Code_tick_timings_value::Code_tick_timings_value_fields, boost::any > 
  {
  public:

    Code_tick_timings_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Code_tick_timings_value_update(Code_tick_timings_value const& first, Code_tick_timings_value const& second) {
      if(!(first.code_locations_id_ == second.code_locations_id_)) {
        code_locations_id(second.code_locations_id_);
      }
      if(!(first.created_ == second.created_)) {
        created(second.created_);
      }
      if(!(first.start_processor_ == second.start_processor_)) {
        start_processor(second.start_processor_);
      }
      if(!(first.end_processor_ == second.end_processor_)) {
        end_processor(second.end_processor_);
      }
      if(!(first.cpu_mhz_ == second.cpu_mhz_)) {
        cpu_mhz(second.cpu_mhz_);
      }
      if(!(first.debug_ == second.debug_)) {
        debug(second.debug_);
      }
      if(!(first.ticks_ == second.ticks_)) {
        ticks(second.ticks_);
      }
      if(!(first.normalized_ns_ == second.normalized_ns_)) {
        normalized_ns(second.normalized_ns_);
      }
    }

    void code_locations_id(boost::int32_t const& val) {
      this->operator[](Code_tick_timings_value::CODE_LOCATIONS_ID_FIELD) = val;  
    }
    void created(otl_datetime const& val) {
      this->operator[](Code_tick_timings_value::CREATED_FIELD) = val;  
    }
    void start_processor(boost::int32_t const& val) {
      this->operator[](Code_tick_timings_value::START_PROCESSOR_FIELD) = val;  
    }
    void end_processor(boost::int32_t const& val) {
      this->operator[](Code_tick_timings_value::END_PROCESSOR_FIELD) = val;  
    }
    void cpu_mhz(double const& val) {
      this->operator[](Code_tick_timings_value::CPU_MHZ_FIELD) = val;  
    }
    void debug(boost::int32_t const& val) {
      this->operator[](Code_tick_timings_value::DEBUG_FIELD) = val;  
    }
    void ticks(otl_bigint const& val) {
      this->operator[](Code_tick_timings_value::TICKS_FIELD) = val;  
    }
    void normalized_ns(otl_bigint const& val) {
      this->operator[](Code_tick_timings_value::NORMALIZED_NS_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Code_tick_timings_value::Code_tick_timings_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Code_tick_timings_value::CODE_LOCATIONS_ID_FIELD)) != this->end()) {
        out << "-- code_locations_id => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Code_tick_timings_value::CREATED_FIELD)) != this->end()) {
        out << "-- created => " << boost::any_cast< otl_datetime const& >(found->second) << '\n';
      }
      if((found = this->find(Code_tick_timings_value::START_PROCESSOR_FIELD)) != this->end()) {
        out << "-- start_processor => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Code_tick_timings_value::END_PROCESSOR_FIELD)) != this->end()) {
        out << "-- end_processor => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Code_tick_timings_value::CPU_MHZ_FIELD)) != this->end()) {
        out << "-- cpu_mhz => " << boost::any_cast< double const& >(found->second) << '\n';
      }
      if((found = this->find(Code_tick_timings_value::DEBUG_FIELD)) != this->end()) {
        out << "-- debug => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Code_tick_timings_value::TICKS_FIELD)) != this->end()) {
        out << "-- ticks => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Code_tick_timings_value::NORMALIZED_NS_FIELD)) != this->end()) {
        out << "-- normalized_ns => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>code_tick_timings</em>
  template < typename PKEY_LIST_TYPE = std::list< Code_tick_timings_pkey >,
             typename VALUE_LIST_TYPE = std::list< Code_tick_timings_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Code_tick_timings :
    public fcs::patterns::Singleton< Code_tick_timings< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Code_tick_timings_pkey Pkey_t;
    typedef Code_tick_timings_value Value_t;
    typedef Code_tick_timings_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Code_tick_timings_pkey, Code_tick_timings_value > Row_t;
    typedef std::list< Row_t > Row_list_t;

  protected:

    Code_tick_timings() :
      connection_(Connection_code_metrics::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Code_tick_timings public header section>
// end <Code_tick_timings public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Code_tick_timings >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Code_tick_timings >(values, out);
    }

    static std::string table_name() {
      return std::string("code_tick_timings");
    }

    static char const* value_field_name(Code_tick_timings_value::Code_tick_timings_value_fields field) {
      char const* value_field_names[] = {
        "code_locations_id",
        "created",
        "start_processor",
        "end_processor",
        "cpu_mhz",
        "debug",
        "ticks",
        "normalized_ns"
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
      otl_stream stream(1, "SELECT COUNT(*) FROM code_tick_timings", *connection_);
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
        "code_locations_id, "
        "created, "
        "start_processor, "
        "end_processor, "
        "cpu_mhz, "
        "debug, "
        "ticks, "
        "normalized_ns "
        "FROM code_tick_timings ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Code_tick_timings_pkey & pkey(row.first);
        Code_tick_timings_value & value(row.second);
        stream
          >> pkey.id_
          >> value.code_locations_id_
          >> value.created_
          >> value.start_processor_
          >> value.end_processor_
          >> value.cpu_mhz_
          >> value.debug_
          >> value.ticks_
          >> value.normalized_ns_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Code_tick_timings_pkey const& desideratum, Code_tick_timings_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "code_locations_id, "
        "created, "
        "start_processor, "
        "end_processor, "
        "cpu_mhz, "
        "debug, "
        "ticks, "
        "normalized_ns "
        "FROM code_tick_timings "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << desideratum.id_
        ;

      while(!stream.eof()) {
        stream
          >> found.code_locations_id_
          >> found.created_
          >> found.start_processor_
          >> found.end_processor_
          >> found.cpu_mhz_
          >> found.debug_
          >> found.ticks_
          >> found.normalized_ns_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Code_tick_timings_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM code_tick_timings "
        "WHERE "
        "code_locations_id = :code_locations_id<int> AND " 
        "created = :created<timestamp> AND " 
        "start_processor = :start_processor<int> AND " 
        "end_processor = :end_processor<int> AND " 
        "cpu_mhz = :cpu_mhz<double> AND " 
        "debug = :debug<int> AND " 
        "ticks = :ticks<bigint> AND " 
        "normalized_ns = :normalized_ns<bigint>", *connection_);

      stream 
        << desideratum.second.code_locations_id_
        << desideratum.second.created_
        << desideratum.second.start_processor_
        << desideratum.second.end_processor_
        << desideratum.second.cpu_mhz_
        << desideratum.second.debug_
        << desideratum.second.ticks_
        << desideratum.second.normalized_ns_
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
      otl_stream stream(50, "INSERT INTO code_tick_timings (" 
        "code_locations_id," 
        "created," 
        "start_processor," 
        "end_processor," 
        "cpu_mhz," 
        "debug," 
        "ticks," 
        "normalized_ns"
        ") VALUES ("
        ":code_locations_id<int>," 
        ":created<timestamp>," 
        ":start_processor<int>," 
        ":end_processor<int>," 
        ":cpu_mhz<double>," 
        ":debug<int>," 
        ":ticks<bigint>," 
        ":normalized_ns<bigint>)", *connection_);

      stream 
        << nascent.second.code_locations_id_
        << nascent.second.created_
        << nascent.second.start_processor_
        << nascent.second.end_processor_
        << nascent.second.cpu_mhz_
        << nascent.second.debug_
        << nascent.second.ticks_
        << nascent.second.normalized_ns_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO code_tick_timings (" 
        "id," 
        "code_locations_id," 
        "created," 
        "start_processor," 
        "end_processor," 
        "cpu_mhz," 
        "debug," 
        "ticks," 
        "normalized_ns"
        ") VALUES ("
        ":id<char[3]>," 
        ":code_locations_id<int>," 
        ":created<timestamp>," 
        ":start_processor<int>," 
        ":end_processor<int>," 
        ":cpu_mhz<double>," 
        ":debug<int>," 
        ":ticks<bigint>," 
        ":normalized_ns<bigint>)", *connection_);

      Row_list_t::const_iterator it(nascent.begin());
      Row_list_t::const_iterator end(nascent.end());

      for(; it != end; ++it) {
        stream 
          << "" // auto_id - id leave blank
          << it->second.code_locations_id_
          << it->second.created_
          << it->second.start_processor_
          << it->second.end_processor_
          << it->second.cpu_mhz_
          << it->second.debug_
          << it->second.ticks_
          << it->second.normalized_ns_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE code_tick_timings SET " 
        "code_locations_id=:code_locations_id<int>," 
        "created=:created<timestamp>," 
        "start_processor=:start_processor<int>," 
        "end_processor=:end_processor<int>," 
        "cpu_mhz=:cpu_mhz<double>," 
        "debug=:debug<int>," 
        "ticks=:ticks<bigint>," 
        "normalized_ns=:normalized_ns<bigint>"
        " WHERE "
        "id=:id<int>", *connection_);

      Row_list_t::const_iterator it(changing.begin());
      Row_list_t::const_iterator end(changing.end());

      for(; it != end; ++it) {
        stream 
          << it->second.code_locations_id_
          << it->second.created_
          << it->second.start_processor_
          << it->second.end_processor_
          << it->second.cpu_mhz_
          << it->second.debug_
          << it->second.ticks_
          << it->second.normalized_ns_
          << it->first.id_
          ;
      }
    }

    inline void update(Code_tick_timings_pkey const& changing, 
                       Code_tick_timings_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE code_tick_timings SET ";
        Code_tick_timings_value_update::const_iterator begin(updates.begin());
        Code_tick_timings_value_update::const_iterator it(updates.begin());
        Code_tick_timings_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Code_tick_timings_value::CODE_LOCATIONS_ID_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Code_tick_timings_value::CREATED_FIELD: {
              sql_statement << boost::any_cast< otl_datetime const& >(it->second);
              break;
            }
            case Code_tick_timings_value::START_PROCESSOR_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Code_tick_timings_value::END_PROCESSOR_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Code_tick_timings_value::CPU_MHZ_FIELD: {
              sql_statement << boost::any_cast< double const& >(it->second);
              break;
            }
            case Code_tick_timings_value::DEBUG_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Code_tick_timings_value::TICKS_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Code_tick_timings_value::NORMALIZED_NS_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
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

    inline void delete_row(Code_tick_timings_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM code_tick_timings "
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
        std::string delete_statement("DELETE FROM code_tick_timings ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM code_tick_timings"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Code_tick_timings >;
  };

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_CODE_METRICS_TABLE_CODE_TICK_TIMINGS_H_
