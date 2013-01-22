/******************************************************************************
 * code_tick_timings_by_package_label.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file code_tick_timings_by_package_label.hpp
 *
 * \brief Record data associated with Code_tick_timings_by_package_label
 * 
 */
#ifndef _FCS_ORM_CODE_METRICS_QUERY_CODE_TICK_TIMINGS_BY_PACKAGE_LABEL_H_
#define _FCS_ORM_CODE_METRICS_QUERY_CODE_TICK_TIMINGS_BY_PACKAGE_LABEL_H_

#include "fcs/utils/fixed_size_char_array.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/orm/code_metrics/connection_code_metrics.hpp"
#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"
#include "fcs/utils/streamers/table/table.hpp"
#include <boost/cstdint.hpp>
#include <iso646.h>
#include <iostream>
#include <list>
#include <string>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace query {

  //! Record data associated with Code_tick_timings_by_package_label
  /**
  Pulls clock ticks by code package name or code location name 
  */
  struct Code_tick_timings_by_package_label 
  {

    Code_tick_timings_by_package_label() :
      package_name_(fcs::utils::Fixed_size_char_array< 64 >()),
      label_(fcs::utils::Fixed_size_char_array< 256 >()),
      file_name_(fcs::utils::Fixed_size_char_array< 256 >()),
      created_(otl_datetime()),
      line_number_(boost::int32_t()),
      git_commit_(fcs::utils::Fixed_size_char_array< 40 >()),
      start_processor_(boost::int32_t()),
      end_processor_(boost::int32_t()),
      cpu_mhz_(double()),
      debug_(boost::int32_t()),
      ticks_(otl_bigint()),
      normalized_ns_(otl_bigint()) 
    {
    }

    bool operator==(Code_tick_timings_by_package_label const& rhs) const {
        return
            ((this==&rhs) or (
            (package_name_ == rhs.package_name_) and
            (label_ == rhs.label_) and
            (file_name_ == rhs.file_name_) and
            (created_ == rhs.created_) and
            (line_number_ == rhs.line_number_) and
            (git_commit_ == rhs.git_commit_) and
            (start_processor_ == rhs.start_processor_) and
            (end_processor_ == rhs.end_processor_) and
            (cpu_mhz_ == rhs.cpu_mhz_) and
            (debug_ == rhs.debug_) and
            (ticks_ == rhs.ticks_) and
            (normalized_ns_ == rhs.normalized_ns_)));
    }

    static inline
    void member_names_list(String_list_t &out) {
      out.push_back("package_name_");
      out.push_back("label_");
      out.push_back("file_name_");
      out.push_back("created_");
      out.push_back("line_number_");
      out.push_back("git_commit_");
      out.push_back("start_processor_");
      out.push_back("end_processor_");
      out.push_back("cpu_mhz_");
      out.push_back("debug_");
      out.push_back("ticks_");
      out.push_back("normalized_ns_");
    }

    inline 
    void to_string_list(String_list_t &out) const {
      out.push_back(boost::lexical_cast< std::string >(package_name_));
      out.push_back(boost::lexical_cast< std::string >(label_));
      out.push_back(boost::lexical_cast< std::string >(file_name_));
      out.push_back(boost::lexical_cast< std::string >(created_));
      out.push_back(boost::lexical_cast< std::string >(line_number_));
      out.push_back(boost::lexical_cast< std::string >(git_commit_));
      out.push_back(boost::lexical_cast< std::string >(start_processor_));
      out.push_back(boost::lexical_cast< std::string >(end_processor_));
      out.push_back(boost::lexical_cast< std::string >(cpu_mhz_));
      out.push_back(boost::lexical_cast< std::string >(debug_));
      out.push_back(boost::lexical_cast< std::string >(ticks_));
      out.push_back(boost::lexical_cast< std::string >(normalized_ns_));
    }
    friend std::ostream& operator<<(std::ostream& out, Code_tick_timings_by_package_label const& item);

    //! Column CP.name from table code_packages <I>open</I>
    fcs::utils::Fixed_size_char_array< 64 > package_name_;
    //! Column CL.label from table code_locations <I>open</I>
    fcs::utils::Fixed_size_char_array< 256 > label_;
    //! Column CL.file_name from table code_locations <I>open</I>
    fcs::utils::Fixed_size_char_array< 256 > file_name_;
    //! Column CTT.created from table code_tick_timings <I>open</I>
    otl_datetime created_;
    //! Column CL.line_number from table code_locations <I>open</I>
    boost::int32_t line_number_;
    //! Column CL.git_commit from table code_locations <I>open</I>
    fcs::utils::Fixed_size_char_array< 40 > git_commit_;
    //! Column CTT.start_processor from table code_tick_timings <I>open</I>
    boost::int32_t start_processor_;
    //! Column CTT.end_processor from table code_tick_timings <I>open</I>
    boost::int32_t end_processor_;
    //! Column CTT.cpu_mhz from table code_tick_timings <I>open</I>
    double cpu_mhz_;
    //! Column CTT.debug from table code_tick_timings <I>open</I>
    boost::int32_t debug_;
    //! Column CTT.ticks from table code_tick_timings <I>open</I>
    otl_bigint ticks_;
    //! Column CTT.normalized_ns from table code_tick_timings <I>open</I>
    otl_bigint normalized_ns_;
  };

  // Support for streaming non-static streamable members of Code_tick_timings_by_package_label
  inline
  std::ostream& operator<<(std::ostream& out, Code_tick_timings_by_package_label const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_tick_timings_by_package_label:(" << &item << "):{";
    out << '\n' << indent << "  package_name:" << item.package_name_;
    out << '\n' << indent << "  label:" << item.label_;
    out << '\n' << indent << "  file_name:" << item.file_name_;
    out << '\n' << indent << "  created:" << item.created_;
    out << '\n' << indent << "  line_number:" << item.line_number_;
    out << '\n' << indent << "  git_commit:" << item.git_commit_;
    out << '\n' << indent << "  start_processor:" << item.start_processor_;
    out << '\n' << indent << "  end_processor:" << item.end_processor_;
    out << '\n' << indent << "  cpu_mhz:" << item.cpu_mhz_;
    out << '\n' << indent << "  debug:" << item.debug_;
    out << '\n' << indent << "  ticks:" << item.ticks_;
    out << '\n' << indent << "  normalized_ns:" << item.normalized_ns_;
    out << indent << "}\n";
    return out;
  } 

  //! Query object for retrieving Code_tick_timings_by_package_label records
  /**

  Implements the following select
  ---------------------------------------------------

  select 
    CP.name as package_name,
    CL.label,
    CL.file_name,
    CTT.created,
    CL.line_number,
    CL.git_commit,
    CTT.!/id|created$/
  from 
    code_locations as CL, 
    code_packages as CP,
    code_tick_timings as CTT
  where  
    CL.label like {substitute('CL.label', :label)} and
    CP.name like {substitute('CP.name', :package_name)} and
    CTT.code_locations_id = CL.id and
    CL.code_packages_id = CP.id
  order by
    CP.name,
    CL.label,
    CTT.created

  */
  class Code_tick_timings_by_package_label_query 
  {
  public:

    // Class typedefs
    typedef std::list< Code_tick_timings_by_package_label > Row_list_t;

    Code_tick_timings_by_package_label_query(
      fcs::utils::Fixed_size_char_array< 64 > const& package_name,
      fcs::utils::Fixed_size_char_array< 256 > const& label
    ) :
      query_result_(),
      query_("select\n"
      "  CP.name as package_name,\n"
      "  CL.label as label,\n"
      "  CL.file_name as file_name,\n"
      "  CTT.created as created,\n"
      "  CL.line_number as line_number,\n"
      "  CL.git_commit as git_commit,\n"
      "  CTT.start_processor as start_processor,\n"
      "  CTT.end_processor as end_processor,\n"
      "  CTT.cpu_mhz as cpu_mhz,\n"
      "  CTT.debug as debug,\n"
      "  CTT.ticks as ticks,\n"
      "  CTT.normalized_ns as normalized_ns\n"
      "from\n"
      "  code_locations as CL, \n"
      "  code_packages as CP,\n"
      "  code_tick_timings as CTT\n"
      "where\n"
      "  CL.label like :label<char[256]> and\n"
      "  CP.name like :package_name<char[64]> and\n"
      "  CTT.code_locations_id = CL.id and\n"
      "  CL.code_packages_id = CP.id\n"
      "order by\n"
      "  CP.name,\n"
      "  CL.label,\n"
      "  CTT.created"),
      package_name_(package_name),
      label_(label)
    {
      ctor_member_init();
    }

    friend std::ostream& operator<<(std::ostream& out, Code_tick_timings_by_package_label_query const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Row_list_t const& query_result() const {
      return query_result_;
    }

    fcs::utils::Fixed_size_char_array< 64 > const& package_name() const {
      return package_name_;
    }

    fcs::utils::Fixed_size_char_array< 256 > const& label() const {
      return label_;
    }

    inline
    void print_query_results_as_table(std::ostream &out) const {
      String_table_t string_table;
      String_list_t header;
      Code_tick_timings_by_package_label::member_names_list(header);
      Row_list_t::const_iterator it(query_result_.begin());
      Row_list_t::const_iterator end(query_result_.end());
      for(; it != end; ++it) {
        String_list_t row_text;
        it->to_string_list(row_text);
        string_table.push_back(row_text);
      }
      out << fcs::utils::streamers::table::Table_streamer< String_table_t >(string_table, header);
    }
  private:

    void ctor_member_init() {
      otl_stream stream(50, query_.c_str(), *Connection_code_metrics::get_instance()->get_connection());
      stream 
        << label_
        << package_name_
      ;
      while(!stream.eof()) {
        Code_tick_timings_by_package_label code_tick_timings_by_package_label;
        stream
          >> code_tick_timings_by_package_label.package_name_
          >> code_tick_timings_by_package_label.label_
          >> code_tick_timings_by_package_label.file_name_
          >> code_tick_timings_by_package_label.created_
          >> code_tick_timings_by_package_label.line_number_
          >> code_tick_timings_by_package_label.git_commit_
          >> code_tick_timings_by_package_label.start_processor_
          >> code_tick_timings_by_package_label.end_processor_
          >> code_tick_timings_by_package_label.cpu_mhz_
          >> code_tick_timings_by_package_label.debug_
          >> code_tick_timings_by_package_label.ticks_
          >> code_tick_timings_by_package_label.normalized_ns_
        ;
        query_result_.push_back(code_tick_timings_by_package_label);
      }
    }
    //! Results of the sql query <I>read only</I>
    Row_list_t query_result_;
    //! The run on construction <I>inaccessible</I>
    std::string query_;
    fcs::utils::Fixed_size_char_array< 64 > package_name_;
    fcs::utils::Fixed_size_char_array< 256 > label_;
  };

  // Support for streaming non-static streamable members of Code_tick_timings_by_package_label_query
  inline
  std::ostream& operator<<(std::ostream& out, Code_tick_timings_by_package_label_query const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Code_tick_timings_by_package_label_query:(" << &item << "):{";
    out << '\n' << indent << "  query_result:" << item.query_result_;
    out << '\n' << indent << "  query:" << item.query_;
    out << '\n' << indent << "  package_name:" << item.package_name_;
    out << '\n' << indent << "  label:" << item.label_;
    out << indent << "}\n";
    return out;
  } 

} // namespace query
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_CODE_METRICS_QUERY_CODE_TICK_TIMINGS_BY_PACKAGE_LABEL_H_
