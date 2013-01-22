/******************************************************************************
 * code_locations.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file code_locations.hpp
 *
 * \brief Database object relational model support for table <em>code_locations</em>
 * 
 */
#ifndef _FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_H_
#define _FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_H_

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
#include <list>
#include <iostream>
#include <iso646.h>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace table {


  //! Encapsulates fields not in primary key of table <em>code_locations</em>
  class Code_locations_value 
  {
  public:

    // Class enumerations
    enum Code_locations_value_fields {
      CODE_PACKAGES_ID_FIELD,
      LABEL_FIELD,
      FILE_NAME_FIELD,
      LINE_NUMBER_FIELD,
      GIT_COMMIT_FIELD
    };

    // Number of entries in Code_locations_value_fields
    enum { CODE_LOCATIONS_VALUE_FIELDS_NUMBER_ENTRIES = 5 };

    friend inline char const* to_c_str(Code_locations_value::Code_locations_value_fields e) {
      char const* values[] = {
        "CODE_PACKAGES_ID_FIELD",
        "LABEL_FIELD",
        "FILE_NAME_FIELD",
        "LINE_NUMBER_FIELD",
        "GIT_COMMIT_FIELD"
      };
      size_t index(e);
      return ((index < CODE_LOCATIONS_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_CODE_LOCATIONS_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Code_locations_value::Code_locations_value_fields e) {
      return out << to_c_str(e);
    }

    Code_locations_value(
      boost::int32_t code_packages_id,
      fcs::utils::Fixed_size_char_array< 256 > const& label,
      fcs::utils::Fixed_size_char_array< 256 > const& file_name,
      boost::int32_t line_number,
      fcs::utils::Fixed_size_char_array< 40 > const& git_commit
    ) :
      code_packages_id_(code_packages_id),
      label_(label),
      file_name_(file_name),
      line_number_(line_number),
      git_commit_(git_commit)
    {
    }

    Code_locations_value() :
      code_packages_id_(boost::int32_t()),
      label_(fcs::utils::Fixed_size_char_array< 256 >()),
      file_name_(fcs::utils::Fixed_size_char_array< 256 >()),
      line_number_(boost::int32_t()),
      git_commit_(fcs::utils::Fixed_size_char_array< 40 >()) 
    {
    }

    bool operator<(Code_locations_value const& rhs) const {
        return
            ((code_packages_id_ != rhs.code_packages_id_)? code_packages_id_ < rhs.code_packages_id_ : (
            ((label_ != rhs.label_)? label_ < rhs.label_ : (
            ((file_name_ != rhs.file_name_)? file_name_ < rhs.file_name_ : (
            ((line_number_ != rhs.line_number_)? line_number_ < rhs.line_number_ : (
            ((git_commit_ != rhs.git_commit_)? git_commit_ < rhs.git_commit_ : (false
            ))))))))));
    }

    bool operator==(Code_locations_value const& rhs) const {
        return
            ((this==&rhs) or (
            (code_packages_id_ == rhs.code_packages_id_) and
            (label_ == rhs.label_) and
            (file_name_ == rhs.file_name_) and
            (line_number_ == rhs.line_number_) and
            (git_commit_ == rhs.git_commit_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("code_packages_id_");
      out.push_back("label_");
      out.push_back("file_name_");
      out.push_back("line_number_");
      out.push_back("git_commit_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(code_packages_id_));
      out.push_back(boost::lexical_cast< std::string >(label_));
      out.push_back(boost::lexical_cast< std::string >(file_name_));
      out.push_back(boost::lexical_cast< std::string >(line_number_));
      out.push_back(boost::lexical_cast< std::string >(git_commit_));
    }
    friend std::ostream& operator<<(std::ostream& out, Code_locations_value const& item);

    boost::int32_t code_packages_id_;
    fcs::utils::Fixed_size_char_array< 256 > label_;
    fcs::utils::Fixed_size_char_array< 256 > file_name_;
    boost::int32_t line_number_;
    fcs::utils::Fixed_size_char_array< 40 > git_commit_;
  };

  // Support for streaming non-static streamable members of Code_locations_value
  inline
  std::ostream& operator<<(std::ostream& out, Code_locations_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_locations_value:(" << &item << "):{";
    out << '\n' << indent << "  code_packages_id:" << item.code_packages_id_;
    out << '\n' << indent << "  label:" << item.label_;
    out << '\n' << indent << "  file_name:" << item.file_name_;
    out << '\n' << indent << "  line_number:" << item.line_number_;
    out << '\n' << indent << "  git_commit:" << item.git_commit_;
    out << indent << "}\n";
    return out;
  } 


  //! Encapsulates fields in primary key of table <em>code_locations</em>
  class Code_locations_pkey 
  {
  public:

    explicit Code_locations_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Code_locations_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Code_locations_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Code_locations_pkey const& rhs) const {
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
    friend std::ostream& operator<<(std::ostream& out, Code_locations_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Code_locations_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Code_locations_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_locations_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>code_locations</em>
  class Code_locations_value_update :
    public std::map< Code_locations_value::Code_locations_value_fields, boost::any > 
  {
  public:

    Code_locations_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Code_locations_value_update(Code_locations_value const& first, Code_locations_value const& second) {
      if(!(first.code_packages_id_ == second.code_packages_id_)) {
        code_packages_id(second.code_packages_id_);
      }
      if(!(first.label_ == second.label_)) {
        label(second.label_);
      }
      if(!(first.file_name_ == second.file_name_)) {
        file_name(second.file_name_);
      }
      if(!(first.line_number_ == second.line_number_)) {
        line_number(second.line_number_);
      }
      if(!(first.git_commit_ == second.git_commit_)) {
        git_commit(second.git_commit_);
      }
    }

    void code_packages_id(boost::int32_t const& val) {
      this->operator[](Code_locations_value::CODE_PACKAGES_ID_FIELD) = val;  
    }
    void label(fcs::utils::Fixed_size_char_array< 256 > const& val) {
      this->operator[](Code_locations_value::LABEL_FIELD) = val;  
    }
    void file_name(fcs::utils::Fixed_size_char_array< 256 > const& val) {
      this->operator[](Code_locations_value::FILE_NAME_FIELD) = val;  
    }
    void line_number(boost::int32_t const& val) {
      this->operator[](Code_locations_value::LINE_NUMBER_FIELD) = val;  
    }
    void git_commit(fcs::utils::Fixed_size_char_array< 40 > const& val) {
      this->operator[](Code_locations_value::GIT_COMMIT_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Code_locations_value::Code_locations_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Code_locations_value::CODE_PACKAGES_ID_FIELD)) != this->end()) {
        out << "-- code_packages_id => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Code_locations_value::LABEL_FIELD)) != this->end()) {
        out << "-- label => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 256 > const& >(found->second) << '\n';
      }
      if((found = this->find(Code_locations_value::FILE_NAME_FIELD)) != this->end()) {
        out << "-- file_name => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 256 > const& >(found->second) << '\n';
      }
      if((found = this->find(Code_locations_value::LINE_NUMBER_FIELD)) != this->end()) {
        out << "-- line_number => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Code_locations_value::GIT_COMMIT_FIELD)) != this->end()) {
        out << "-- git_commit => " << boost::any_cast< fcs::utils::Fixed_size_char_array< 40 > const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>code_locations</em>
  template < typename PKEY_LIST_TYPE = std::list< Code_locations_pkey >,
             typename VALUE_LIST_TYPE = std::list< Code_locations_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Code_locations :
    public fcs::patterns::Singleton< Code_locations< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Code_locations_pkey Pkey_t;
    typedef Code_locations_value Value_t;
    typedef Code_locations_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Code_locations_pkey, Code_locations_value > Row_t;
    typedef std::list< Row_t > Row_list_t;

  protected:

    Code_locations() :
      connection_(Connection_code_metrics::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Code_locations public header section>
// end <Code_locations public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Code_locations >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Code_locations >(values, out);
    }

    static std::string table_name() {
      return std::string("code_locations");
    }

    static char const* value_field_name(Code_locations_value::Code_locations_value_fields field) {
      char const* value_field_names[] = {
        "code_packages_id",
        "label",
        "file_name",
        "line_number",
        "git_commit"
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
      otl_stream stream(1, "SELECT COUNT(*) FROM code_locations", *connection_);
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
        "code_packages_id, "
        "label, "
        "file_name, "
        "line_number, "
        "git_commit "
        "FROM code_locations ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Code_locations_pkey & pkey(row.first);
        Code_locations_value & value(row.second);
        stream
          >> pkey.id_
          >> value.code_packages_id_
          >> value.label_
          >> value.file_name_
          >> value.line_number_
          >> value.git_commit_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Code_locations_pkey const& desideratum, Code_locations_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "code_packages_id, "
        "label, "
        "file_name, "
        "line_number, "
        "git_commit "
        "FROM code_locations "
        "WHERE "
        "id=:id<int>", 
        *connection_);

      stream 
        << desideratum.id_
        ;

      while(!stream.eof()) {
        stream
          >> found.code_packages_id_
          >> found.label_
          >> found.file_name_
          >> found.line_number_
          >> found.git_commit_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Code_locations_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM code_locations "
        "WHERE "
        "code_packages_id = :code_packages_id<int> AND " 
        "label = :label<char[256]> AND " 
        "file_name = :file_name<char[256]> AND " 
        "line_number = :line_number<int> AND " 
        "git_commit = :git_commit<char[40]>", *connection_);

      stream 
        << desideratum.second.code_packages_id_
        << desideratum.second.label_
        << desideratum.second.file_name_
        << desideratum.second.line_number_
        << desideratum.second.git_commit_
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
      otl_stream stream(50, "INSERT INTO code_locations (" 
        "code_packages_id," 
        "label," 
        "file_name," 
        "line_number," 
        "git_commit"
        ") VALUES ("
        ":code_packages_id<int>," 
        ":label<char[256]>," 
        ":file_name<char[256]>," 
        ":line_number<int>," 
        ":git_commit<char[40]>)", *connection_);

      stream 
        << nascent.second.code_packages_id_
        << nascent.second.label_
        << nascent.second.file_name_
        << nascent.second.line_number_
        << nascent.second.git_commit_
        ;

    }

    inline void insert_ignore(Row_t const& nascent) {
      otl_stream stream(50, "INSERT IGNORE INTO code_locations (" 
        "code_packages_id," 
        "label," 
        "file_name," 
        "line_number," 
        "git_commit"
        ") VALUES ("
        ":code_packages_id<int>," 
        ":label<char[256]>," 
        ":file_name<char[256]>," 
        ":line_number<int>," 
        ":git_commit<char[40]>)", *connection_);

      stream 
        << nascent.second.code_packages_id_
        << nascent.second.label_
        << nascent.second.file_name_
        << nascent.second.line_number_
        << nascent.second.git_commit_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO code_locations (" 
        "id," 
        "code_packages_id," 
        "label," 
        "file_name," 
        "line_number," 
        "git_commit"
        ") VALUES ("
        ":id<char[3]>," 
        ":code_packages_id<int>," 
        ":label<char[256]>," 
        ":file_name<char[256]>," 
        ":line_number<int>," 
        ":git_commit<char[40]>)", *connection_);

      Row_list_t::const_iterator it(nascent.begin());
      Row_list_t::const_iterator end(nascent.end());

      for(; it != end; ++it) {
        stream 
          << "" // auto_id - id leave blank
          << it->second.code_packages_id_
          << it->second.label_
          << it->second.file_name_
          << it->second.line_number_
          << it->second.git_commit_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE code_locations SET " 
        "code_packages_id=:code_packages_id<int>," 
        "label=:label<char[256]>," 
        "file_name=:file_name<char[256]>," 
        "line_number=:line_number<int>," 
        "git_commit=:git_commit<char[40]>"
        " WHERE "
        "id=:id<int>", *connection_);

      Row_list_t::const_iterator it(changing.begin());
      Row_list_t::const_iterator end(changing.end());

      for(; it != end; ++it) {
        stream 
          << it->second.code_packages_id_
          << it->second.label_
          << it->second.file_name_
          << it->second.line_number_
          << it->second.git_commit_
          << it->first.id_
          ;
      }
    }

    inline void update(Code_locations_pkey const& changing, 
                       Code_locations_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE code_locations SET ";
        Code_locations_value_update::const_iterator begin(updates.begin());
        Code_locations_value_update::const_iterator it(updates.begin());
        Code_locations_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Code_locations_value::CODE_PACKAGES_ID_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Code_locations_value::LABEL_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 256 > const& >(it->second));
              break;
            }
            case Code_locations_value::FILE_NAME_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 256 > const& >(it->second));
              break;
            }
            case Code_locations_value::LINE_NUMBER_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Code_locations_value::GIT_COMMIT_FIELD: {
              sql_statement << fcs::orm::sql_quote(boost::any_cast< fcs::utils::Fixed_size_char_array< 40 > const& >(it->second));
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

    inline void delete_row(Code_locations_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM code_locations "
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
        std::string delete_statement("DELETE FROM code_locations ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM code_locations"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Code_locations >;
  };

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_CODE_METRICS_TABLE_CODE_LOCATIONS_H_
