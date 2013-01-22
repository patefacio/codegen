/******************************************************************************
 * rusage_delta_by_package_label.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file rusage_delta_by_package_label.hpp
 *
 * \brief Record data associated with Rusage_delta_by_package_label
 * 
 */
#ifndef _FCS_ORM_CODE_METRICS_QUERY_RUSAGE_DELTA_BY_PACKAGE_LABEL_H_
#define _FCS_ORM_CODE_METRICS_QUERY_RUSAGE_DELTA_BY_PACKAGE_LABEL_H_

#include "fcs/utils/fixed_size_char_array.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/orm/code_metrics/connection_code_metrics.hpp"
#include "fcs/orm/otl_config.hpp"
#include "fcs/orm/otl_utils.hpp"
#include "fcs/utils/streamers/table/table.hpp"
#include <boost/cstdint.hpp>
#include <boost/format.hpp>
#include <iso646.h>
#include <iostream>
#include <list>
#include <string>

namespace fcs {
namespace orm {
namespace code_metrics {
namespace query {

  //! Record data associated with Rusage_delta_by_package_label
  /**
  Query that pulls rusage by code package or code location name 
  */
  struct Rusage_delta_by_package_label 
  {

    Rusage_delta_by_package_label() :
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
      user_time_sec_(otl_bigint()),
      user_time_usec_(otl_bigint()),
      system_time_sec_(otl_bigint()),
      system_time_usec_(otl_bigint()),
      ru_maxrss_(otl_bigint()),
      ru_ixrss_(otl_bigint()),
      ru_isrss_(otl_bigint()),
      ru_minflt_(otl_bigint()),
      ru_majflt_(otl_bigint()),
      ru_nswap_(otl_bigint()),
      ru_inblock_(otl_bigint()),
      ru_oublock_(otl_bigint()),
      ru_msgsnd_(otl_bigint()),
      ru_msgrcv_(otl_bigint()),
      ru_nsignals_(otl_bigint()),
      ru_nvcsw_(otl_bigint()),
      ru_nivcsw_(otl_bigint()) 
    {
    }

    bool operator==(Rusage_delta_by_package_label const& rhs) const {
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
            (user_time_sec_ == rhs.user_time_sec_) and
            (user_time_usec_ == rhs.user_time_usec_) and
            (system_time_sec_ == rhs.system_time_sec_) and
            (system_time_usec_ == rhs.system_time_usec_) and
            (ru_maxrss_ == rhs.ru_maxrss_) and
            (ru_ixrss_ == rhs.ru_ixrss_) and
            (ru_isrss_ == rhs.ru_isrss_) and
            (ru_minflt_ == rhs.ru_minflt_) and
            (ru_majflt_ == rhs.ru_majflt_) and
            (ru_nswap_ == rhs.ru_nswap_) and
            (ru_inblock_ == rhs.ru_inblock_) and
            (ru_oublock_ == rhs.ru_oublock_) and
            (ru_msgsnd_ == rhs.ru_msgsnd_) and
            (ru_msgrcv_ == rhs.ru_msgrcv_) and
            (ru_nsignals_ == rhs.ru_nsignals_) and
            (ru_nvcsw_ == rhs.ru_nvcsw_) and
            (ru_nivcsw_ == rhs.ru_nivcsw_)));
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
      out.push_back("user_time_sec_");
      out.push_back("user_time_usec_");
      out.push_back("system_time_sec_");
      out.push_back("system_time_usec_");
      out.push_back("ru_maxrss_");
      out.push_back("ru_ixrss_");
      out.push_back("ru_isrss_");
      out.push_back("ru_minflt_");
      out.push_back("ru_majflt_");
      out.push_back("ru_nswap_");
      out.push_back("ru_inblock_");
      out.push_back("ru_oublock_");
      out.push_back("ru_msgsnd_");
      out.push_back("ru_msgrcv_");
      out.push_back("ru_nsignals_");
      out.push_back("ru_nvcsw_");
      out.push_back("ru_nivcsw_");
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
      out.push_back(boost::lexical_cast< std::string >(user_time_sec_));
      out.push_back(boost::lexical_cast< std::string >(user_time_usec_));
      out.push_back(boost::lexical_cast< std::string >(system_time_sec_));
      out.push_back(boost::lexical_cast< std::string >(system_time_usec_));
      out.push_back(boost::lexical_cast< std::string >(ru_maxrss_));
      out.push_back(boost::lexical_cast< std::string >(ru_ixrss_));
      out.push_back(boost::lexical_cast< std::string >(ru_isrss_));
      out.push_back(boost::lexical_cast< std::string >(ru_minflt_));
      out.push_back(boost::lexical_cast< std::string >(ru_majflt_));
      out.push_back(boost::lexical_cast< std::string >(ru_nswap_));
      out.push_back(boost::lexical_cast< std::string >(ru_inblock_));
      out.push_back(boost::lexical_cast< std::string >(ru_oublock_));
      out.push_back(boost::lexical_cast< std::string >(ru_msgsnd_));
      out.push_back(boost::lexical_cast< std::string >(ru_msgrcv_));
      out.push_back(boost::lexical_cast< std::string >(ru_nsignals_));
      out.push_back(boost::lexical_cast< std::string >(ru_nvcsw_));
      out.push_back(boost::lexical_cast< std::string >(ru_nivcsw_));
    }
    friend std::ostream& operator<<(std::ostream& out, Rusage_delta_by_package_label const& item);

    //! Column CP.name from table code_packages <I>open</I>
    fcs::utils::Fixed_size_char_array< 64 > package_name_;
    //! Column CL.label from table code_locations <I>open</I>
    fcs::utils::Fixed_size_char_array< 256 > label_;
    //! Column CL.file_name from table code_locations <I>open</I>
    fcs::utils::Fixed_size_char_array< 256 > file_name_;
    //! Column RD.created from table rusage_delta <I>open</I>
    otl_datetime created_;
    //! Column CL.line_number from table code_locations <I>open</I>
    boost::int32_t line_number_;
    //! Column CL.git_commit from table code_locations <I>open</I>
    fcs::utils::Fixed_size_char_array< 40 > git_commit_;
    //! Column RD.start_processor from table rusage_delta <I>open</I>
    boost::int32_t start_processor_;
    //! Column RD.end_processor from table rusage_delta <I>open</I>
    boost::int32_t end_processor_;
    //! Column RD.cpu_mhz from table rusage_delta <I>open</I>
    double cpu_mhz_;
    //! Column RD.debug from table rusage_delta <I>open</I>
    boost::int32_t debug_;
    //! Column RD.user_time_sec from table rusage_delta <I>open</I>
    otl_bigint user_time_sec_;
    //! Column RD.user_time_usec from table rusage_delta <I>open</I>
    otl_bigint user_time_usec_;
    //! Column RD.system_time_sec from table rusage_delta <I>open</I>
    otl_bigint system_time_sec_;
    //! Column RD.system_time_usec from table rusage_delta <I>open</I>
    otl_bigint system_time_usec_;
    //! Column RD.ru_maxrss from table rusage_delta <I>open</I>
    otl_bigint ru_maxrss_;
    //! Column RD.ru_ixrss from table rusage_delta <I>open</I>
    otl_bigint ru_ixrss_;
    //! Column RD.ru_isrss from table rusage_delta <I>open</I>
    otl_bigint ru_isrss_;
    //! Column RD.ru_minflt from table rusage_delta <I>open</I>
    otl_bigint ru_minflt_;
    //! Column RD.ru_majflt from table rusage_delta <I>open</I>
    otl_bigint ru_majflt_;
    //! Column RD.ru_nswap from table rusage_delta <I>open</I>
    otl_bigint ru_nswap_;
    //! Column RD.ru_inblock from table rusage_delta <I>open</I>
    otl_bigint ru_inblock_;
    //! Column RD.ru_oublock from table rusage_delta <I>open</I>
    otl_bigint ru_oublock_;
    //! Column RD.ru_msgsnd from table rusage_delta <I>open</I>
    otl_bigint ru_msgsnd_;
    //! Column RD.ru_msgrcv from table rusage_delta <I>open</I>
    otl_bigint ru_msgrcv_;
    //! Column RD.ru_nsignals from table rusage_delta <I>open</I>
    otl_bigint ru_nsignals_;
    //! Column RD.ru_nvcsw from table rusage_delta <I>open</I>
    otl_bigint ru_nvcsw_;
    //! Column RD.ru_nivcsw from table rusage_delta <I>open</I>
    otl_bigint ru_nivcsw_;
  };

  // Support for streaming non-static streamable members of Rusage_delta_by_package_label
  inline
  std::ostream& operator<<(std::ostream& out, Rusage_delta_by_package_label const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Rusage_delta_by_package_label:(" << &item << "):{";
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
    out << '\n' << indent << "  user_time_sec:" << item.user_time_sec_;
    out << '\n' << indent << "  user_time_usec:" << item.user_time_usec_;
    out << '\n' << indent << "  system_time_sec:" << item.system_time_sec_;
    out << '\n' << indent << "  system_time_usec:" << item.system_time_usec_;
    out << '\n' << indent << "  ru_maxrss:" << item.ru_maxrss_;
    out << '\n' << indent << "  ru_ixrss:" << item.ru_ixrss_;
    out << '\n' << indent << "  ru_isrss:" << item.ru_isrss_;
    out << '\n' << indent << "  ru_minflt:" << item.ru_minflt_;
    out << '\n' << indent << "  ru_majflt:" << item.ru_majflt_;
    out << '\n' << indent << "  ru_nswap:" << item.ru_nswap_;
    out << '\n' << indent << "  ru_inblock:" << item.ru_inblock_;
    out << '\n' << indent << "  ru_oublock:" << item.ru_oublock_;
    out << '\n' << indent << "  ru_msgsnd:" << item.ru_msgsnd_;
    out << '\n' << indent << "  ru_msgrcv:" << item.ru_msgrcv_;
    out << '\n' << indent << "  ru_nsignals:" << item.ru_nsignals_;
    out << '\n' << indent << "  ru_nvcsw:" << item.ru_nvcsw_;
    out << '\n' << indent << "  ru_nivcsw:" << item.ru_nivcsw_;
    out << indent << "}\n";
    return out;
  } 

  //! Query object for retrieving Rusage_delta_by_package_label records
  /**

  Implements the following select
  ---------------------------------------------------

  select 
    CP.name as package_name,
    CL.label,
    CL.file_name,
    RD.created,
    CL.line_number,
    CL.git_commit,
    RD.!/id|created$/
  from 
    code_locations as CL, 
    code_packages as CP,
    rusage_delta as RD
  where  
    CL.label like {presubstitute(:cpp_type => 'std::string', :name => 'label')} and
    CP.name like {substitute('CP.name', :package_name)} and
    RD.code_locations_id = CL.id and
    CL.code_packages_id = CP.id
  order by
    CP.name,
    CL.label,
    RD.created

  */
  class Rusage_delta_by_package_label_query 
  {
  public:

    // Class typedefs
    typedef std::list< Rusage_delta_by_package_label > Row_list_t;

    Rusage_delta_by_package_label_query(
      fcs::utils::Fixed_size_char_array< 64 > const& package_name,
      std::string const& label
    ) :
      query_result_(),
      query_("select\n"
      "  CP.name as package_name,\n"
      "  CL.label as label,\n"
      "  CL.file_name as file_name,\n"
      "  RD.created as created,\n"
      "  CL.line_number as line_number,\n"
      "  CL.git_commit as git_commit,\n"
      "  RD.start_processor as start_processor,\n"
      "  RD.end_processor as end_processor,\n"
      "  RD.cpu_mhz as cpu_mhz,\n"
      "  RD.debug as debug,\n"
      "  RD.user_time_sec as user_time_sec,\n"
      "  RD.user_time_usec as user_time_usec,\n"
      "  RD.system_time_sec as system_time_sec,\n"
      "  RD.system_time_usec as system_time_usec,\n"
      "  RD.ru_maxrss as ru_maxrss,\n"
      "  RD.ru_ixrss as ru_ixrss,\n"
      "  RD.ru_isrss as ru_isrss,\n"
      "  RD.ru_minflt as ru_minflt,\n"
      "  RD.ru_majflt as ru_majflt,\n"
      "  RD.ru_nswap as ru_nswap,\n"
      "  RD.ru_inblock as ru_inblock,\n"
      "  RD.ru_oublock as ru_oublock,\n"
      "  RD.ru_msgsnd as ru_msgsnd,\n"
      "  RD.ru_msgrcv as ru_msgrcv,\n"
      "  RD.ru_nsignals as ru_nsignals,\n"
      "  RD.ru_nvcsw as ru_nvcsw,\n"
      "  RD.ru_nivcsw as ru_nivcsw\n"
      "from\n"
      "  code_locations as CL, \n"
      "  code_packages as CP,\n"
      "  rusage_delta as RD\n"
      "where\n"
      "  CL.label like %1% and\n"
      "  CP.name like :package_name<char[64]> and\n"
      "  RD.code_locations_id = CL.id and\n"
      "  CL.code_packages_id = CP.id\n"
      "order by\n"
      "  CP.name,\n"
      "  CL.label,\n"
      "  RD.created"),
      package_name_(package_name),
      label_(label)
    {
      ctor_member_init();
    }

    friend std::ostream& operator<<(std::ostream& out, Rusage_delta_by_package_label_query const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Row_list_t const& query_result() const {
      return query_result_;
    }

    fcs::utils::Fixed_size_char_array< 64 > const& package_name() const {
      return package_name_;
    }

    std::string const& label() const {
      return label_;
    }

    inline
    void print_query_results_as_table(std::ostream &out) const {
      String_table_t string_table;
      String_list_t header;
      Rusage_delta_by_package_label::member_names_list(header);
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
      using boost::format;
      using boost::io::group;
      std::ostringstream query_text;
      query_text << format(query_.c_str()) % fcs::orm::sql_quote(label_);
      otl_stream stream(
        50, query_text.str().c_str(),
        *Connection_code_metrics::get_instance()->get_connection());
      stream 
        << package_name_
      ;
      while(!stream.eof()) {
        Rusage_delta_by_package_label rusage_delta_by_package_label;
        stream
          >> rusage_delta_by_package_label.package_name_
          >> rusage_delta_by_package_label.label_
          >> rusage_delta_by_package_label.file_name_
          >> rusage_delta_by_package_label.created_
          >> rusage_delta_by_package_label.line_number_
          >> rusage_delta_by_package_label.git_commit_
          >> rusage_delta_by_package_label.start_processor_
          >> rusage_delta_by_package_label.end_processor_
          >> rusage_delta_by_package_label.cpu_mhz_
          >> rusage_delta_by_package_label.debug_
          >> rusage_delta_by_package_label.user_time_sec_
          >> rusage_delta_by_package_label.user_time_usec_
          >> rusage_delta_by_package_label.system_time_sec_
          >> rusage_delta_by_package_label.system_time_usec_
          >> rusage_delta_by_package_label.ru_maxrss_
          >> rusage_delta_by_package_label.ru_ixrss_
          >> rusage_delta_by_package_label.ru_isrss_
          >> rusage_delta_by_package_label.ru_minflt_
          >> rusage_delta_by_package_label.ru_majflt_
          >> rusage_delta_by_package_label.ru_nswap_
          >> rusage_delta_by_package_label.ru_inblock_
          >> rusage_delta_by_package_label.ru_oublock_
          >> rusage_delta_by_package_label.ru_msgsnd_
          >> rusage_delta_by_package_label.ru_msgrcv_
          >> rusage_delta_by_package_label.ru_nsignals_
          >> rusage_delta_by_package_label.ru_nvcsw_
          >> rusage_delta_by_package_label.ru_nivcsw_
        ;
        query_result_.push_back(rusage_delta_by_package_label);
      }
    }
    //! Results of the sql query <I>read only</I>
    Row_list_t query_result_;
    //! The run on construction <I>inaccessible</I>
    std::string query_;
    fcs::utils::Fixed_size_char_array< 64 > package_name_;
    std::string label_;
  };

  // Support for streaming non-static streamable members of Rusage_delta_by_package_label_query
  inline
  std::ostream& operator<<(std::ostream& out, Rusage_delta_by_package_label_query const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Rusage_delta_by_package_label_query:(" << &item << "):{";
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
#endif // _FCS_ORM_CODE_METRICS_QUERY_RUSAGE_DELTA_BY_PACKAGE_LABEL_H_
