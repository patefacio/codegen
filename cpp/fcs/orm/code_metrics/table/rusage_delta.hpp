/******************************************************************************
 * rusage_delta.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file rusage_delta.hpp
 *
 * \brief Database object relational model support for table <em>rusage_delta</em>
 * 
 */
#ifndef _FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_H_
#define _FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_H_

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


  //! Encapsulates fields not in primary key of table <em>rusage_delta</em>
  class Rusage_delta_value 
  {
  public:

    // Class enumerations
    enum Rusage_delta_value_fields {
      CODE_LOCATIONS_ID_FIELD,
      CREATED_FIELD,
      START_PROCESSOR_FIELD,
      END_PROCESSOR_FIELD,
      CPU_MHZ_FIELD,
      DEBUG_FIELD,
      USER_TIME_SEC_FIELD,
      USER_TIME_USEC_FIELD,
      SYSTEM_TIME_SEC_FIELD,
      SYSTEM_TIME_USEC_FIELD,
      RU_MAXRSS_FIELD,
      RU_IXRSS_FIELD,
      RU_IDRSS_FIELD,
      RU_ISRSS_FIELD,
      RU_MINFLT_FIELD,
      RU_MAJFLT_FIELD,
      RU_NSWAP_FIELD,
      RU_INBLOCK_FIELD,
      RU_OUBLOCK_FIELD,
      RU_MSGSND_FIELD,
      RU_MSGRCV_FIELD,
      RU_NSIGNALS_FIELD,
      RU_NVCSW_FIELD,
      RU_NIVCSW_FIELD
    };

    // Number of entries in Rusage_delta_value_fields
    enum { RUSAGE_DELTA_VALUE_FIELDS_NUMBER_ENTRIES = 24 };

    friend inline char const* to_c_str(Rusage_delta_value::Rusage_delta_value_fields e) {
      char const* values[] = {
        "CODE_LOCATIONS_ID_FIELD",
        "CREATED_FIELD",
        "START_PROCESSOR_FIELD",
        "END_PROCESSOR_FIELD",
        "CPU_MHZ_FIELD",
        "DEBUG_FIELD",
        "USER_TIME_SEC_FIELD",
        "USER_TIME_USEC_FIELD",
        "SYSTEM_TIME_SEC_FIELD",
        "SYSTEM_TIME_USEC_FIELD",
        "RU_MAXRSS_FIELD",
        "RU_IXRSS_FIELD",
        "RU_IDRSS_FIELD",
        "RU_ISRSS_FIELD",
        "RU_MINFLT_FIELD",
        "RU_MAJFLT_FIELD",
        "RU_NSWAP_FIELD",
        "RU_INBLOCK_FIELD",
        "RU_OUBLOCK_FIELD",
        "RU_MSGSND_FIELD",
        "RU_MSGRCV_FIELD",
        "RU_NSIGNALS_FIELD",
        "RU_NVCSW_FIELD",
        "RU_NIVCSW_FIELD"
      };
      size_t index(e);
      return ((index < RUSAGE_DELTA_VALUE_FIELDS_NUMBER_ENTRIES)? values[index] : "INVALID_RUSAGE_DELTA_VALUE_FIELDS");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Rusage_delta_value::Rusage_delta_value_fields e) {
      return out << to_c_str(e);
    }

    Rusage_delta_value(
      boost::int32_t code_locations_id,
      otl_datetime const& created,
      boost::int32_t start_processor,
      boost::int32_t end_processor,
      double cpu_mhz,
      boost::int32_t debug,
      otl_bigint user_time_sec,
      otl_bigint user_time_usec,
      otl_bigint system_time_sec,
      otl_bigint system_time_usec,
      otl_bigint ru_maxrss,
      otl_bigint ru_ixrss,
      otl_bigint ru_idrss,
      otl_bigint ru_isrss,
      otl_bigint ru_minflt,
      otl_bigint ru_majflt,
      otl_bigint ru_nswap,
      otl_bigint ru_inblock,
      otl_bigint ru_oublock,
      otl_bigint ru_msgsnd,
      otl_bigint ru_msgrcv,
      otl_bigint ru_nsignals,
      otl_bigint ru_nvcsw,
      otl_bigint ru_nivcsw
    ) :
      code_locations_id_(code_locations_id),
      created_(created),
      start_processor_(start_processor),
      end_processor_(end_processor),
      cpu_mhz_(cpu_mhz),
      debug_(debug),
      user_time_sec_(user_time_sec),
      user_time_usec_(user_time_usec),
      system_time_sec_(system_time_sec),
      system_time_usec_(system_time_usec),
      ru_maxrss_(ru_maxrss),
      ru_ixrss_(ru_ixrss),
      ru_idrss_(ru_idrss),
      ru_isrss_(ru_isrss),
      ru_minflt_(ru_minflt),
      ru_majflt_(ru_majflt),
      ru_nswap_(ru_nswap),
      ru_inblock_(ru_inblock),
      ru_oublock_(ru_oublock),
      ru_msgsnd_(ru_msgsnd),
      ru_msgrcv_(ru_msgrcv),
      ru_nsignals_(ru_nsignals),
      ru_nvcsw_(ru_nvcsw),
      ru_nivcsw_(ru_nivcsw)
    {
    }

    Rusage_delta_value() :
      code_locations_id_(boost::int32_t()),
      created_(otl_datetime()),
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
      ru_idrss_(otl_bigint()),
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

    bool operator<(Rusage_delta_value const& rhs) const {
        return
            ((code_locations_id_ != rhs.code_locations_id_)? code_locations_id_ < rhs.code_locations_id_ : (
            ((created_ != rhs.created_)? created_ < rhs.created_ : (
            ((start_processor_ != rhs.start_processor_)? start_processor_ < rhs.start_processor_ : (
            ((end_processor_ != rhs.end_processor_)? end_processor_ < rhs.end_processor_ : (
            ((cpu_mhz_ != rhs.cpu_mhz_)? cpu_mhz_ < rhs.cpu_mhz_ : (
            ((debug_ != rhs.debug_)? debug_ < rhs.debug_ : (
            ((user_time_sec_ != rhs.user_time_sec_)? user_time_sec_ < rhs.user_time_sec_ : (
            ((user_time_usec_ != rhs.user_time_usec_)? user_time_usec_ < rhs.user_time_usec_ : (
            ((system_time_sec_ != rhs.system_time_sec_)? system_time_sec_ < rhs.system_time_sec_ : (
            ((system_time_usec_ != rhs.system_time_usec_)? system_time_usec_ < rhs.system_time_usec_ : (
            ((ru_maxrss_ != rhs.ru_maxrss_)? ru_maxrss_ < rhs.ru_maxrss_ : (
            ((ru_ixrss_ != rhs.ru_ixrss_)? ru_ixrss_ < rhs.ru_ixrss_ : (
            ((ru_idrss_ != rhs.ru_idrss_)? ru_idrss_ < rhs.ru_idrss_ : (
            ((ru_isrss_ != rhs.ru_isrss_)? ru_isrss_ < rhs.ru_isrss_ : (
            ((ru_minflt_ != rhs.ru_minflt_)? ru_minflt_ < rhs.ru_minflt_ : (
            ((ru_majflt_ != rhs.ru_majflt_)? ru_majflt_ < rhs.ru_majflt_ : (
            ((ru_nswap_ != rhs.ru_nswap_)? ru_nswap_ < rhs.ru_nswap_ : (
            ((ru_inblock_ != rhs.ru_inblock_)? ru_inblock_ < rhs.ru_inblock_ : (
            ((ru_oublock_ != rhs.ru_oublock_)? ru_oublock_ < rhs.ru_oublock_ : (
            ((ru_msgsnd_ != rhs.ru_msgsnd_)? ru_msgsnd_ < rhs.ru_msgsnd_ : (
            ((ru_msgrcv_ != rhs.ru_msgrcv_)? ru_msgrcv_ < rhs.ru_msgrcv_ : (
            ((ru_nsignals_ != rhs.ru_nsignals_)? ru_nsignals_ < rhs.ru_nsignals_ : (
            ((ru_nvcsw_ != rhs.ru_nvcsw_)? ru_nvcsw_ < rhs.ru_nvcsw_ : (
            ((ru_nivcsw_ != rhs.ru_nivcsw_)? ru_nivcsw_ < rhs.ru_nivcsw_ : (false
            ))))))))))))))))))))))))))))))))))))))))))))))));
    }

    bool operator==(Rusage_delta_value const& rhs) const {
        return
            ((this==&rhs) or (
            (code_locations_id_ == rhs.code_locations_id_) and
            (created_ == rhs.created_) and
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
            (ru_idrss_ == rhs.ru_idrss_) and
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
      out.push_back("code_locations_id_");
      out.push_back("created_");
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
      out.push_back("ru_idrss_");
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
      out.push_back(boost::lexical_cast< std::string >(code_locations_id_));
      out.push_back(boost::lexical_cast< std::string >(created_));
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
      out.push_back(boost::lexical_cast< std::string >(ru_idrss_));
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
    friend std::ostream& operator<<(std::ostream& out, Rusage_delta_value const& item);

    boost::int32_t code_locations_id_;
    otl_datetime created_;
    boost::int32_t start_processor_;
    boost::int32_t end_processor_;
    double cpu_mhz_;
    boost::int32_t debug_;
    otl_bigint user_time_sec_;
    otl_bigint user_time_usec_;
    otl_bigint system_time_sec_;
    otl_bigint system_time_usec_;
    otl_bigint ru_maxrss_;
    otl_bigint ru_ixrss_;
    otl_bigint ru_idrss_;
    otl_bigint ru_isrss_;
    otl_bigint ru_minflt_;
    otl_bigint ru_majflt_;
    otl_bigint ru_nswap_;
    otl_bigint ru_inblock_;
    otl_bigint ru_oublock_;
    otl_bigint ru_msgsnd_;
    otl_bigint ru_msgrcv_;
    otl_bigint ru_nsignals_;
    otl_bigint ru_nvcsw_;
    otl_bigint ru_nivcsw_;
  };

  // Support for streaming non-static streamable members of Rusage_delta_value
  inline
  std::ostream& operator<<(std::ostream& out, Rusage_delta_value const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Rusage_delta_value:(" << &item << "):{";
    out << '\n' << indent << "  code_locations_id:" << item.code_locations_id_;
    out << '\n' << indent << "  created:" << item.created_;
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
    out << '\n' << indent << "  ru_idrss:" << item.ru_idrss_;
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


  //! Encapsulates fields in primary key of table <em>rusage_delta</em>
  class Rusage_delta_pkey 
  {
  public:

    explicit Rusage_delta_pkey(
      boost::int32_t id
    ) :
      id_(id)
    {
    }

    Rusage_delta_pkey() :
      id_(boost::int32_t()) 
    {
    }

    bool operator<(Rusage_delta_pkey const& rhs) const {
        return
            ((id_ != rhs.id_)? id_ < rhs.id_ : (false
            ));
    }

    bool operator==(Rusage_delta_pkey const& rhs) const {
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
    friend std::ostream& operator<<(std::ostream& out, Rusage_delta_pkey const& item);

    boost::int32_t id_;
  };

  // Support for streaming non-static streamable members of Rusage_delta_pkey
  inline
  std::ostream& operator<<(std::ostream& out, Rusage_delta_pkey const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Rusage_delta_pkey:(" << &item << "):{";
    out << '\n' << indent << "  id:" << item.id_;
    out << indent << "}\n";
    return out;
  } 

  //! Supports selective updates by value field id for <em>rusage_delta</em>
  class Rusage_delta_value_update :
    public std::map< Rusage_delta_value::Rusage_delta_value_fields, boost::any > 
  {
  public:

    Rusage_delta_value_update() {
    }

    // Differencing ctor - provides value update which if applied to first yields second
    Rusage_delta_value_update(Rusage_delta_value const& first, Rusage_delta_value const& second) {
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
      if(!(first.user_time_sec_ == second.user_time_sec_)) {
        user_time_sec(second.user_time_sec_);
      }
      if(!(first.user_time_usec_ == second.user_time_usec_)) {
        user_time_usec(second.user_time_usec_);
      }
      if(!(first.system_time_sec_ == second.system_time_sec_)) {
        system_time_sec(second.system_time_sec_);
      }
      if(!(first.system_time_usec_ == second.system_time_usec_)) {
        system_time_usec(second.system_time_usec_);
      }
      if(!(first.ru_maxrss_ == second.ru_maxrss_)) {
        ru_maxrss(second.ru_maxrss_);
      }
      if(!(first.ru_ixrss_ == second.ru_ixrss_)) {
        ru_ixrss(second.ru_ixrss_);
      }
      if(!(first.ru_idrss_ == second.ru_idrss_)) {
        ru_idrss(second.ru_idrss_);
      }
      if(!(first.ru_isrss_ == second.ru_isrss_)) {
        ru_isrss(second.ru_isrss_);
      }
      if(!(first.ru_minflt_ == second.ru_minflt_)) {
        ru_minflt(second.ru_minflt_);
      }
      if(!(first.ru_majflt_ == second.ru_majflt_)) {
        ru_majflt(second.ru_majflt_);
      }
      if(!(first.ru_nswap_ == second.ru_nswap_)) {
        ru_nswap(second.ru_nswap_);
      }
      if(!(first.ru_inblock_ == second.ru_inblock_)) {
        ru_inblock(second.ru_inblock_);
      }
      if(!(first.ru_oublock_ == second.ru_oublock_)) {
        ru_oublock(second.ru_oublock_);
      }
      if(!(first.ru_msgsnd_ == second.ru_msgsnd_)) {
        ru_msgsnd(second.ru_msgsnd_);
      }
      if(!(first.ru_msgrcv_ == second.ru_msgrcv_)) {
        ru_msgrcv(second.ru_msgrcv_);
      }
      if(!(first.ru_nsignals_ == second.ru_nsignals_)) {
        ru_nsignals(second.ru_nsignals_);
      }
      if(!(first.ru_nvcsw_ == second.ru_nvcsw_)) {
        ru_nvcsw(second.ru_nvcsw_);
      }
      if(!(first.ru_nivcsw_ == second.ru_nivcsw_)) {
        ru_nivcsw(second.ru_nivcsw_);
      }
    }

    void code_locations_id(boost::int32_t const& val) {
      this->operator[](Rusage_delta_value::CODE_LOCATIONS_ID_FIELD) = val;  
    }
    void created(otl_datetime const& val) {
      this->operator[](Rusage_delta_value::CREATED_FIELD) = val;  
    }
    void start_processor(boost::int32_t const& val) {
      this->operator[](Rusage_delta_value::START_PROCESSOR_FIELD) = val;  
    }
    void end_processor(boost::int32_t const& val) {
      this->operator[](Rusage_delta_value::END_PROCESSOR_FIELD) = val;  
    }
    void cpu_mhz(double const& val) {
      this->operator[](Rusage_delta_value::CPU_MHZ_FIELD) = val;  
    }
    void debug(boost::int32_t const& val) {
      this->operator[](Rusage_delta_value::DEBUG_FIELD) = val;  
    }
    void user_time_sec(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::USER_TIME_SEC_FIELD) = val;  
    }
    void user_time_usec(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::USER_TIME_USEC_FIELD) = val;  
    }
    void system_time_sec(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::SYSTEM_TIME_SEC_FIELD) = val;  
    }
    void system_time_usec(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::SYSTEM_TIME_USEC_FIELD) = val;  
    }
    void ru_maxrss(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_MAXRSS_FIELD) = val;  
    }
    void ru_ixrss(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_IXRSS_FIELD) = val;  
    }
    void ru_idrss(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_IDRSS_FIELD) = val;  
    }
    void ru_isrss(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_ISRSS_FIELD) = val;  
    }
    void ru_minflt(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_MINFLT_FIELD) = val;  
    }
    void ru_majflt(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_MAJFLT_FIELD) = val;  
    }
    void ru_nswap(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_NSWAP_FIELD) = val;  
    }
    void ru_inblock(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_INBLOCK_FIELD) = val;  
    }
    void ru_oublock(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_OUBLOCK_FIELD) = val;  
    }
    void ru_msgsnd(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_MSGSND_FIELD) = val;  
    }
    void ru_msgrcv(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_MSGRCV_FIELD) = val;  
    }
    void ru_nsignals(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_NSIGNALS_FIELD) = val;  
    }
    void ru_nvcsw(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_NVCSW_FIELD) = val;  
    }
    void ru_nivcsw(otl_bigint const& val) {
      this->operator[](Rusage_delta_value::RU_NIVCSW_FIELD) = val;  
    }

    void dump(std::ostream &out) const {
      std::map< Rusage_delta_value::Rusage_delta_value_fields, boost::any >::const_iterator found;
      if((found = this->find(Rusage_delta_value::CODE_LOCATIONS_ID_FIELD)) != this->end()) {
        out << "-- code_locations_id => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::CREATED_FIELD)) != this->end()) {
        out << "-- created => " << boost::any_cast< otl_datetime const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::START_PROCESSOR_FIELD)) != this->end()) {
        out << "-- start_processor => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::END_PROCESSOR_FIELD)) != this->end()) {
        out << "-- end_processor => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::CPU_MHZ_FIELD)) != this->end()) {
        out << "-- cpu_mhz => " << boost::any_cast< double const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::DEBUG_FIELD)) != this->end()) {
        out << "-- debug => " << boost::any_cast< boost::int32_t const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::USER_TIME_SEC_FIELD)) != this->end()) {
        out << "-- user_time_sec => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::USER_TIME_USEC_FIELD)) != this->end()) {
        out << "-- user_time_usec => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::SYSTEM_TIME_SEC_FIELD)) != this->end()) {
        out << "-- system_time_sec => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::SYSTEM_TIME_USEC_FIELD)) != this->end()) {
        out << "-- system_time_usec => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_MAXRSS_FIELD)) != this->end()) {
        out << "-- ru_maxrss => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_IXRSS_FIELD)) != this->end()) {
        out << "-- ru_ixrss => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_IDRSS_FIELD)) != this->end()) {
        out << "-- ru_idrss => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_ISRSS_FIELD)) != this->end()) {
        out << "-- ru_isrss => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_MINFLT_FIELD)) != this->end()) {
        out << "-- ru_minflt => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_MAJFLT_FIELD)) != this->end()) {
        out << "-- ru_majflt => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_NSWAP_FIELD)) != this->end()) {
        out << "-- ru_nswap => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_INBLOCK_FIELD)) != this->end()) {
        out << "-- ru_inblock => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_OUBLOCK_FIELD)) != this->end()) {
        out << "-- ru_oublock => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_MSGSND_FIELD)) != this->end()) {
        out << "-- ru_msgsnd => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_MSGRCV_FIELD)) != this->end()) {
        out << "-- ru_msgrcv => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_NSIGNALS_FIELD)) != this->end()) {
        out << "-- ru_nsignals => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_NVCSW_FIELD)) != this->end()) {
        out << "-- ru_nvcsw => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
      if((found = this->find(Rusage_delta_value::RU_NIVCSW_FIELD)) != this->end()) {
        out << "-- ru_nivcsw => " << boost::any_cast< otl_bigint const& >(found->second) << '\n';
      }
    }
  };

  //! Database object relational model support for table <em>rusage_delta</em>
  template < typename PKEY_LIST_TYPE = std::list< Rusage_delta_pkey >,
             typename VALUE_LIST_TYPE = std::list< Rusage_delta_value >,
             typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Rusage_delta :
    public fcs::patterns::Singleton< Rusage_delta< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef Rusage_delta_pkey Pkey_t;
    typedef Rusage_delta_value Value_t;
    typedef Rusage_delta_value_update Value_update_t;
    typedef PKEY_LIST_TYPE Pkey_list_t;
    typedef VALUE_LIST_TYPE Value_list_t;
    typedef std::pair< Rusage_delta_pkey, Rusage_delta_value > Row_t;
    typedef std::list< Row_t > Row_list_t;

  protected:

    Rusage_delta() :
      connection_(Connection_code_metrics::get_instance()->get_connection()) 
    {
    }

  public:
  
// custom <Rusage_delta public header section>
// end <Rusage_delta public header section>

    // Inline methods

    static void print_recordset_as_table(Row_list_t const& recordset, std::ostream &out) {
      fcs::orm::print_recordset_as_table< Rusage_delta >(recordset, out);
    }

    static void print_values_as_table(Value_list_t const& values, std::ostream &out) {
      fcs::orm::print_values_as_table< Rusage_delta >(values, out);
    }

    static std::string table_name() {
      return std::string("rusage_delta");
    }

    static char const* value_field_name(Rusage_delta_value::Rusage_delta_value_fields field) {
      char const* value_field_names[] = {
        "code_locations_id",
        "created",
        "start_processor",
        "end_processor",
        "cpu_mhz",
        "debug",
        "user_time_sec",
        "user_time_usec",
        "system_time_sec",
        "system_time_usec",
        "ru_maxrss",
        "ru_ixrss",
        "ru_idrss",
        "ru_isrss",
        "ru_minflt",
        "ru_majflt",
        "ru_nswap",
        "ru_inblock",
        "ru_oublock",
        "ru_msgsnd",
        "ru_msgrcv",
        "ru_nsignals",
        "ru_nvcsw",
        "ru_nivcsw"
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
      otl_stream stream(1, "SELECT COUNT(*) FROM rusage_delta", *connection_);
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
        "user_time_sec, "
        "user_time_usec, "
        "system_time_sec, "
        "system_time_usec, "
        "ru_maxrss, "
        "ru_ixrss, "
        "ru_idrss, "
        "ru_isrss, "
        "ru_minflt, "
        "ru_majflt, "
        "ru_nswap, "
        "ru_inblock, "
        "ru_oublock, "
        "ru_msgsnd, "
        "ru_msgrcv, "
        "ru_nsignals, "
        "ru_nvcsw, "
        "ru_nivcsw "
        "FROM rusage_delta ");

      if(!where_clause.empty()) {
        select_stmt += where_clause;
      }

      otl_stream stream(50, select_stmt.c_str(), *connection_);

      while(!stream.eof()) {
        Row_t row;
        Rusage_delta_pkey & pkey(row.first);
        Rusage_delta_value & value(row.second);
        stream
          >> pkey.id_
          >> value.code_locations_id_
          >> value.created_
          >> value.start_processor_
          >> value.end_processor_
          >> value.cpu_mhz_
          >> value.debug_
          >> value.user_time_sec_
          >> value.user_time_usec_
          >> value.system_time_sec_
          >> value.system_time_usec_
          >> value.ru_maxrss_
          >> value.ru_ixrss_
          >> value.ru_idrss_
          >> value.ru_isrss_
          >> value.ru_minflt_
          >> value.ru_majflt_
          >> value.ru_nswap_
          >> value.ru_inblock_
          >> value.ru_oublock_
          >> value.ru_msgsnd_
          >> value.ru_msgrcv_
          >> value.ru_nsignals_
          >> value.ru_nvcsw_
          >> value.ru_nivcsw_
          ;
        found.push_back(row);
      }
    }

    inline bool find_row(Rusage_delta_pkey const& desideratum, Rusage_delta_value & found) {
      bool result(false);
      otl_stream stream(50, "SELECT "
        "code_locations_id, "
        "created, "
        "start_processor, "
        "end_processor, "
        "cpu_mhz, "
        "debug, "
        "user_time_sec, "
        "user_time_usec, "
        "system_time_sec, "
        "system_time_usec, "
        "ru_maxrss, "
        "ru_ixrss, "
        "ru_idrss, "
        "ru_isrss, "
        "ru_minflt, "
        "ru_majflt, "
        "ru_nswap, "
        "ru_inblock, "
        "ru_oublock, "
        "ru_msgsnd, "
        "ru_msgrcv, "
        "ru_nsignals, "
        "ru_nvcsw, "
        "ru_nivcsw "
        "FROM rusage_delta "
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
          >> found.user_time_sec_
          >> found.user_time_usec_
          >> found.system_time_sec_
          >> found.system_time_usec_
          >> found.ru_maxrss_
          >> found.ru_ixrss_
          >> found.ru_idrss_
          >> found.ru_isrss_
          >> found.ru_minflt_
          >> found.ru_majflt_
          >> found.ru_nswap_
          >> found.ru_inblock_
          >> found.ru_oublock_
          >> found.ru_msgsnd_
          >> found.ru_msgrcv_
          >> found.ru_nsignals_
          >> found.ru_nvcsw_
          >> found.ru_nivcsw_
          ;
        result = true;
      }
      return result;
    }

    inline void find_rows(Pkey_list_t const& desideratum, Value_list_t & found) {
      typename Pkey_list_t::const_iterator end(desideratum.end());
      for(typename Pkey_list_t::const_iterator it(desideratum.begin()); it != end; ++it) {
        Rusage_delta_value value;
        if(find_row(*it, value)) {
          found.push_back(value);
        }
      }
    }

    inline bool find_row_by_value(Row_t & desideratum) {
      otl_stream stream(50, "SELECT "
        "id "
        "FROM rusage_delta "
        "WHERE "
        "code_locations_id = :code_locations_id<int> AND " 
        "created = :created<timestamp> AND " 
        "start_processor = :start_processor<int> AND " 
        "end_processor = :end_processor<int> AND " 
        "cpu_mhz = :cpu_mhz<double> AND " 
        "debug = :debug<int> AND " 
        "user_time_sec = :user_time_sec<bigint> AND " 
        "user_time_usec = :user_time_usec<bigint> AND " 
        "system_time_sec = :system_time_sec<bigint> AND " 
        "system_time_usec = :system_time_usec<bigint> AND " 
        "ru_maxrss = :ru_maxrss<bigint> AND " 
        "ru_ixrss = :ru_ixrss<bigint> AND " 
        "ru_idrss = :ru_idrss<bigint> AND " 
        "ru_isrss = :ru_isrss<bigint> AND " 
        "ru_minflt = :ru_minflt<bigint> AND " 
        "ru_majflt = :ru_majflt<bigint> AND " 
        "ru_nswap = :ru_nswap<bigint> AND " 
        "ru_inblock = :ru_inblock<bigint> AND " 
        "ru_oublock = :ru_oublock<bigint> AND " 
        "ru_msgsnd = :ru_msgsnd<bigint> AND " 
        "ru_msgrcv = :ru_msgrcv<bigint> AND " 
        "ru_nsignals = :ru_nsignals<bigint> AND " 
        "ru_nvcsw = :ru_nvcsw<bigint> AND " 
        "ru_nivcsw = :ru_nivcsw<bigint>", *connection_);

      stream 
        << desideratum.second.code_locations_id_
        << desideratum.second.created_
        << desideratum.second.start_processor_
        << desideratum.second.end_processor_
        << desideratum.second.cpu_mhz_
        << desideratum.second.debug_
        << desideratum.second.user_time_sec_
        << desideratum.second.user_time_usec_
        << desideratum.second.system_time_sec_
        << desideratum.second.system_time_usec_
        << desideratum.second.ru_maxrss_
        << desideratum.second.ru_ixrss_
        << desideratum.second.ru_idrss_
        << desideratum.second.ru_isrss_
        << desideratum.second.ru_minflt_
        << desideratum.second.ru_majflt_
        << desideratum.second.ru_nswap_
        << desideratum.second.ru_inblock_
        << desideratum.second.ru_oublock_
        << desideratum.second.ru_msgsnd_
        << desideratum.second.ru_msgrcv_
        << desideratum.second.ru_nsignals_
        << desideratum.second.ru_nvcsw_
        << desideratum.second.ru_nivcsw_
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
      otl_stream stream(50, "INSERT INTO rusage_delta (" 
        "code_locations_id," 
        "created," 
        "start_processor," 
        "end_processor," 
        "cpu_mhz," 
        "debug," 
        "user_time_sec," 
        "user_time_usec," 
        "system_time_sec," 
        "system_time_usec," 
        "ru_maxrss," 
        "ru_ixrss," 
        "ru_idrss," 
        "ru_isrss," 
        "ru_minflt," 
        "ru_majflt," 
        "ru_nswap," 
        "ru_inblock," 
        "ru_oublock," 
        "ru_msgsnd," 
        "ru_msgrcv," 
        "ru_nsignals," 
        "ru_nvcsw," 
        "ru_nivcsw"
        ") VALUES ("
        ":code_locations_id<int>," 
        ":created<timestamp>," 
        ":start_processor<int>," 
        ":end_processor<int>," 
        ":cpu_mhz<double>," 
        ":debug<int>," 
        ":user_time_sec<bigint>," 
        ":user_time_usec<bigint>," 
        ":system_time_sec<bigint>," 
        ":system_time_usec<bigint>," 
        ":ru_maxrss<bigint>," 
        ":ru_ixrss<bigint>," 
        ":ru_idrss<bigint>," 
        ":ru_isrss<bigint>," 
        ":ru_minflt<bigint>," 
        ":ru_majflt<bigint>," 
        ":ru_nswap<bigint>," 
        ":ru_inblock<bigint>," 
        ":ru_oublock<bigint>," 
        ":ru_msgsnd<bigint>," 
        ":ru_msgrcv<bigint>," 
        ":ru_nsignals<bigint>," 
        ":ru_nvcsw<bigint>," 
        ":ru_nivcsw<bigint>)", *connection_);

      stream 
        << nascent.second.code_locations_id_
        << nascent.second.created_
        << nascent.second.start_processor_
        << nascent.second.end_processor_
        << nascent.second.cpu_mhz_
        << nascent.second.debug_
        << nascent.second.user_time_sec_
        << nascent.second.user_time_usec_
        << nascent.second.system_time_sec_
        << nascent.second.system_time_usec_
        << nascent.second.ru_maxrss_
        << nascent.second.ru_ixrss_
        << nascent.second.ru_idrss_
        << nascent.second.ru_isrss_
        << nascent.second.ru_minflt_
        << nascent.second.ru_majflt_
        << nascent.second.ru_nswap_
        << nascent.second.ru_inblock_
        << nascent.second.ru_oublock_
        << nascent.second.ru_msgsnd_
        << nascent.second.ru_msgrcv_
        << nascent.second.ru_nsignals_
        << nascent.second.ru_nvcsw_
        << nascent.second.ru_nivcsw_
        ;

    }

    inline void insert(Row_list_t const& nascent, int stream_buffer_size = 1) {
      if(nascent.empty()) {
        return;
      }
      otl_stream stream(stream_buffer_size, "INSERT INTO rusage_delta (" 
        "id," 
        "code_locations_id," 
        "created," 
        "start_processor," 
        "end_processor," 
        "cpu_mhz," 
        "debug," 
        "user_time_sec," 
        "user_time_usec," 
        "system_time_sec," 
        "system_time_usec," 
        "ru_maxrss," 
        "ru_ixrss," 
        "ru_idrss," 
        "ru_isrss," 
        "ru_minflt," 
        "ru_majflt," 
        "ru_nswap," 
        "ru_inblock," 
        "ru_oublock," 
        "ru_msgsnd," 
        "ru_msgrcv," 
        "ru_nsignals," 
        "ru_nvcsw," 
        "ru_nivcsw"
        ") VALUES ("
        ":id<char[3]>," 
        ":code_locations_id<int>," 
        ":created<timestamp>," 
        ":start_processor<int>," 
        ":end_processor<int>," 
        ":cpu_mhz<double>," 
        ":debug<int>," 
        ":user_time_sec<bigint>," 
        ":user_time_usec<bigint>," 
        ":system_time_sec<bigint>," 
        ":system_time_usec<bigint>," 
        ":ru_maxrss<bigint>," 
        ":ru_ixrss<bigint>," 
        ":ru_idrss<bigint>," 
        ":ru_isrss<bigint>," 
        ":ru_minflt<bigint>," 
        ":ru_majflt<bigint>," 
        ":ru_nswap<bigint>," 
        ":ru_inblock<bigint>," 
        ":ru_oublock<bigint>," 
        ":ru_msgsnd<bigint>," 
        ":ru_msgrcv<bigint>," 
        ":ru_nsignals<bigint>," 
        ":ru_nvcsw<bigint>," 
        ":ru_nivcsw<bigint>)", *connection_);

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
          << it->second.user_time_sec_
          << it->second.user_time_usec_
          << it->second.system_time_sec_
          << it->second.system_time_usec_
          << it->second.ru_maxrss_
          << it->second.ru_ixrss_
          << it->second.ru_idrss_
          << it->second.ru_isrss_
          << it->second.ru_minflt_
          << it->second.ru_majflt_
          << it->second.ru_nswap_
          << it->second.ru_inblock_
          << it->second.ru_oublock_
          << it->second.ru_msgsnd_
          << it->second.ru_msgrcv_
          << it->second.ru_nsignals_
          << it->second.ru_nvcsw_
          << it->second.ru_nivcsw_
          ;
      }

    }

    inline void update(Row_list_t const& changing) {
      if(changing.empty()) {
        return;
      }
      otl_stream stream(1, "UPDATE rusage_delta SET " 
        "code_locations_id=:code_locations_id<int>," 
        "created=:created<timestamp>," 
        "start_processor=:start_processor<int>," 
        "end_processor=:end_processor<int>," 
        "cpu_mhz=:cpu_mhz<double>," 
        "debug=:debug<int>," 
        "user_time_sec=:user_time_sec<bigint>," 
        "user_time_usec=:user_time_usec<bigint>," 
        "system_time_sec=:system_time_sec<bigint>," 
        "system_time_usec=:system_time_usec<bigint>," 
        "ru_maxrss=:ru_maxrss<bigint>," 
        "ru_ixrss=:ru_ixrss<bigint>," 
        "ru_idrss=:ru_idrss<bigint>," 
        "ru_isrss=:ru_isrss<bigint>," 
        "ru_minflt=:ru_minflt<bigint>," 
        "ru_majflt=:ru_majflt<bigint>," 
        "ru_nswap=:ru_nswap<bigint>," 
        "ru_inblock=:ru_inblock<bigint>," 
        "ru_oublock=:ru_oublock<bigint>," 
        "ru_msgsnd=:ru_msgsnd<bigint>," 
        "ru_msgrcv=:ru_msgrcv<bigint>," 
        "ru_nsignals=:ru_nsignals<bigint>," 
        "ru_nvcsw=:ru_nvcsw<bigint>," 
        "ru_nivcsw=:ru_nivcsw<bigint>"
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
          << it->second.user_time_sec_
          << it->second.user_time_usec_
          << it->second.system_time_sec_
          << it->second.system_time_usec_
          << it->second.ru_maxrss_
          << it->second.ru_ixrss_
          << it->second.ru_idrss_
          << it->second.ru_isrss_
          << it->second.ru_minflt_
          << it->second.ru_majflt_
          << it->second.ru_nswap_
          << it->second.ru_inblock_
          << it->second.ru_oublock_
          << it->second.ru_msgsnd_
          << it->second.ru_msgrcv_
          << it->second.ru_nsignals_
          << it->second.ru_nvcsw_
          << it->second.ru_nivcsw_
          << it->first.id_
          ;
      }
    }

    inline void update(Rusage_delta_pkey const& changing, 
                       Rusage_delta_value_update const& updates) {
      if(!updates.empty()) {
        std::ostringstream sql_statement;
        sql_statement << "UPDATE rusage_delta SET ";
        Rusage_delta_value_update::const_iterator begin(updates.begin());
        Rusage_delta_value_update::const_iterator it(updates.begin());
        Rusage_delta_value_update::const_iterator end(updates.end());
        for(; it != end; ++it) {

          if(it != begin) {
            sql_statement << ',';
          }

          sql_statement << value_field_name(it->first) << '=';
          switch(it->first) {
            case Rusage_delta_value::CODE_LOCATIONS_ID_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Rusage_delta_value::CREATED_FIELD: {
              sql_statement << boost::any_cast< otl_datetime const& >(it->second);
              break;
            }
            case Rusage_delta_value::START_PROCESSOR_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Rusage_delta_value::END_PROCESSOR_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Rusage_delta_value::CPU_MHZ_FIELD: {
              sql_statement << boost::any_cast< double const& >(it->second);
              break;
            }
            case Rusage_delta_value::DEBUG_FIELD: {
              sql_statement << boost::any_cast< boost::int32_t const& >(it->second);
              break;
            }
            case Rusage_delta_value::USER_TIME_SEC_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::USER_TIME_USEC_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::SYSTEM_TIME_SEC_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::SYSTEM_TIME_USEC_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_MAXRSS_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_IXRSS_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_IDRSS_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_ISRSS_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_MINFLT_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_MAJFLT_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_NSWAP_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_INBLOCK_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_OUBLOCK_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_MSGSND_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_MSGRCV_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_NSIGNALS_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_NVCSW_FIELD: {
              sql_statement << boost::any_cast< otl_bigint const& >(it->second);
              break;
            }
            case Rusage_delta_value::RU_NIVCSW_FIELD: {
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

    inline void delete_row(Rusage_delta_pkey const& moribund) {
      otl_stream stream(50, "DELETE "
        "FROM rusage_delta "
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
        std::string delete_statement("DELETE FROM rusage_delta ");
        more_to_delete = !add_where_pkey_clause_max_additions(it, moribund.end(), delete_statement, max_per_call);
        otl_stream stream(1, delete_statement.c_str(), *connection_);
      }
    }

    inline size_t delete_all_rows() {
      long rows_deleted(otl_cursor::direct_exec(*connection_, "DELETE FROM rusage_delta"));
      return size_t(rows_deleted);
    }
  private:
    otl_connect * connection_;
    friend class fcs::patterns::Singleton_impl< Rusage_delta >;
  };

} // namespace table
} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_CODE_METRICS_TABLE_RUSAGE_DELTA_H_
