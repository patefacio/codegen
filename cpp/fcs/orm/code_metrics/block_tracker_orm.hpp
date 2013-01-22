/******************************************************************************
 * block_tracker_orm.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file block_tracker_orm.hpp
 *
 * \brief Used to time code blocks
 * 
 */
#ifndef _FCS_ORM_CODE_METRICS_BLOCK_TRACKER_ORM_H_
#define _FCS_ORM_CODE_METRICS_BLOCK_TRACKER_ORM_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters/integer.hpp>
#include <pantheios/inserters/real.hpp>
#include "fcs/utils/performance/cycle.h"
#include "fcs/orm/code_metrics/table/rusage_delta.hpp"
#include "fcs/orm/code_metrics/table/code_tick_timings.hpp"
#include "fcs/orm/code_metrics/table/code_packages.hpp"
#include "fcs/orm/code_metrics/table/code_locations.hpp"
#include "fcs/linux_specific/cpu_info.hpp"
#include "fcs/utils/version_control_commit.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/special_functions/round.hpp>
#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>


// custom <Block_tracker_orm global header section>

#include "fcs/utils/streamers/vector.hpp"

// end <Block_tracker_orm global header section>
namespace fcs {
namespace orm {
namespace code_metrics {

  //! Used to time code blocks
  /**
  Supports both rusage timing and basic high res timing. 
  */
  class Block_tracker_orm 
  {
  public:

    // Class enumerations
    //! Which type of timing to track and store in the database
    enum Timing_type {
      TIMING_TICKS,
      TIMING_RUSAGE
    };

    // Number of entries in Timing_type
    enum { TIMING_TYPE_NUMBER_ENTRIES = 2 };

    friend inline char const* to_c_str(Block_tracker_orm::Timing_type e) {
      char const* values[] = {
        "TIMING_TICKS",
        "TIMING_RUSAGE"
      };
      size_t index(e);
      return ((index < TIMING_TYPE_NUMBER_ENTRIES)? values[index] : "INVALID_TIMING_TYPE");
    }

    friend inline std::ostream& operator<<(std::ostream &out, Block_tracker_orm::Timing_type e) {
      return out << to_c_str(e);
    }

    // Class typedefs
    typedef std::pair< char const*, char const* > Name_and_description_t;

    Block_tracker_orm(
      Name_and_description_t const& package_name_and_description,
      char const* label,
      char const* file_name,
      size_t line_number,
      Timing_type timing_type = TIMING_TICKS,
      int processor = -1
    ) :
      package_name_and_description_(package_name_and_description),
      label_(label),
      file_name_(file_name),
      line_number_(line_number),
      timing_type_(timing_type),
      processor_(processor),
      initial_rusage_(),
      initial_ticks_(0),
      cpu_mhz_(0),
      code_locations_id_()
    {
      ctor_member_init();
    }

  
// custom <Block_tracker_orm public header section>

    ~Block_tracker_orm() {
      using namespace fcs::orm::code_metrics::table;
      if(TIMING_TICKS == timing_type_) {
        ticks final_ticks(getticks());
        ticks delta_ticks(final_ticks - initial_ticks_);
        ticks normalized_nanos(0);
        if(cpu_mhz_) {
          normalized_nanos = boost::math::round((1000 * delta_ticks) / double(cpu_mhz_));
        }

        try {
          Code_tick_timings<>::Row_t code_tick_timings_row; 
          Code_tick_timings<>::Value_t &code_tick_timings(code_tick_timings_row.second);
          boost::posix_time::ptime now(boost::posix_time::microsec_clock::universal_time());
          code_tick_timings.created_ = boost_ptime_to_otl_datetime(now);
          code_tick_timings.start_processor_ = processor_;
          code_tick_timings.end_processor_ = sched_getcpu();
          code_tick_timings.cpu_mhz_ = cpu_mhz_;
#if defined(DEBUG)
          code_tick_timings.debug_ = 1;
#else
          code_tick_timings.debug_ = 0;
#endif
          code_tick_timings.code_locations_id_ = code_locations_id_;
          code_tick_timings.ticks_ = delta_ticks;
          code_tick_timings.normalized_ns_ = normalized_nanos;
          Code_tick_timings<>::Pointer_t code_tick_timings_table(Code_tick_timings<>::get_instance());
          code_tick_timings_table->insert(code_tick_timings_row);
        } catch(std::exception const&) {
        }
      } else {
        rusage final_rusage;
        int rc(0);
        if(0 != (rc = getrusage(RUSAGE_THREAD, &final_rusage))) {
          std::ostringstream msg;
          msg << "Unable to track rusage - rc:" << rc << " errno:" << errno << std::endl;
          throw std::runtime_error(msg.str());
        } else {
          Rusage_delta<>::Row_t delta_rusage_row;
          Rusage_delta<>::Value_t &delta_rusage(delta_rusage_row.second);
          boost::posix_time::ptime now(boost::posix_time::microsec_clock::universal_time());
          delta_rusage.created_ = boost_ptime_to_otl_datetime(now);
          delta_rusage.start_processor_ = processor_;
          delta_rusage.end_processor_ = sched_getcpu();
          delta_rusage.cpu_mhz_ = cpu_mhz_;
#if defined(DEBUG)
          delta_rusage.debug_ = 1;
#else
          delta_rusage.debug_ = 0;
#endif
          delta_rusage.user_time_sec_ = final_rusage.ru_utime.tv_sec - initial_rusage_.ru_utime.tv_sec;
          delta_rusage.user_time_usec_ = final_rusage.ru_utime.tv_usec - initial_rusage_.ru_utime.tv_usec;

          delta_rusage.system_time_sec_ = final_rusage.ru_stime.tv_sec - initial_rusage_.ru_stime.tv_sec;
          delta_rusage.system_time_usec_ = final_rusage.ru_stime.tv_usec - initial_rusage_.ru_stime.tv_usec;

          delta_rusage.ru_maxrss_ = final_rusage.ru_maxrss - initial_rusage_.ru_maxrss;
          delta_rusage.ru_ixrss_ = final_rusage.ru_ixrss - initial_rusage_.ru_ixrss;
          delta_rusage.ru_idrss_ = final_rusage.ru_idrss - initial_rusage_.ru_idrss;
          delta_rusage.ru_isrss_ = final_rusage.ru_isrss - initial_rusage_.ru_isrss;
          delta_rusage.ru_minflt_ = final_rusage.ru_minflt - initial_rusage_.ru_minflt;
          delta_rusage.ru_majflt_ = final_rusage.ru_majflt - initial_rusage_.ru_majflt;
          delta_rusage.ru_nswap_ = final_rusage.ru_nswap - initial_rusage_.ru_nswap;
          delta_rusage.ru_inblock_ = final_rusage.ru_inblock - initial_rusage_.ru_inblock;
          delta_rusage.ru_oublock_ = final_rusage.ru_oublock - initial_rusage_.ru_oublock;
          delta_rusage.ru_msgsnd_ = final_rusage.ru_msgsnd - initial_rusage_.ru_msgsnd;
          delta_rusage.ru_msgrcv_ = final_rusage.ru_msgrcv - initial_rusage_.ru_msgrcv;
          delta_rusage.ru_nsignals_ = final_rusage.ru_nsignals - initial_rusage_.ru_nsignals;
          delta_rusage.ru_nvcsw_ = final_rusage.ru_nvcsw - initial_rusage_.ru_nvcsw;
          delta_rusage.ru_nivcsw_ = final_rusage.ru_nivcsw - initial_rusage_.ru_nivcsw;

          try {
            Rusage_delta<>::Pointer_t rusage_delta_table(Rusage_delta<>::get_instance());
            delta_rusage.code_locations_id_ = code_locations_id_;
            rusage_delta_table->insert(delta_rusage_row);
          } catch(std::exception const&) {
          }
        }
      }
    }

    static int get_code_locations_id(Name_and_description_t const& package_name_and_description,
                                     char const* label, char const* file_name, int line_number) {
      using namespace fcs::orm::code_metrics::table;
      char const* api_name(package_name_and_description.first);
      char const* api_description(package_name_and_description.second);
      Code_packages<>::Row_t code_packages;
      code_packages.second.name_ = api_name;
      code_packages.second.descr_ = api_description;
      Code_packages<>::Pointer_t code_packages_table(Code_packages<>::get_instance());
      code_packages_table->insert_ignore(code_packages);
      code_packages_table->find_row_by_value(code_packages);
      Code_locations<>::Row_t code_locations;
      code_locations.second.code_packages_id_ = code_packages.first.id_;
      code_locations.second.label_ = label;
      code_locations.second.file_name_ = file_name;
      code_locations.second.line_number_ = line_number;
      code_locations.second.git_commit_ = fcs::utils::Version_control_commit::get_instance()->git_commit();
      Code_locations<>::Pointer_t code_locations_table(Code_locations<>::get_instance());
      code_locations_table->insert_ignore(code_locations);
      using fcs::utils::streamers::operator<<;
      code_locations_table->find_row_by_value(code_locations);
      return code_locations.first.id_;
    }

// end <Block_tracker_orm public header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <Block_tracker_orm::init>

      fcs::linux_specific::Cpu_info::Processor_list_t const& 
        processors(fcs::linux_specific::Cpu_info::get_instance()->processors());

      pantheios::log(PANTHEIOS_SEV_DEBUG, "Initializing block_tracker_orm");  

      size_t num_processors(processors.size());

      code_locations_id_ = 
        get_code_locations_id(package_name_and_description_, label_, 
                              file_name_, line_number_); 

      if(processor_ >= 0) {
        if(processor_ < int(num_processors)) {
          cpu_set_t mask;
          CPU_ZERO(&mask);
          CPU_SET(processor_, &mask);
          long rc(sched_setaffinity(0, sizeof(mask), &mask));
          if(0 == rc) {
            pantheios::log(PANTHEIOS_SEV_DEBUG, "Pinned to processor ", 
                           pantheios::integer(processor_),
                           " for timing of ", label_);  
          }
        } else {
          std::ostringstream msg;
          msg << "Invalid processor specified:" << processor_;
          throw std::logic_error(msg.str());
        }
      } else {
        processor_ = sched_getcpu();
      }

      if((processor_ >= 0) && (processor_ < int(num_processors))) {
        cpu_mhz_ = boost::lexical_cast< double >(processors[processor_].cpu_mhz());
        pantheios::log(PANTHEIOS_SEV_DEBUG, "cpu_mhz of processor ", 
                       pantheios::integer(processor_), " is ", 
                       pantheios::real(cpu_mhz_));  
      }

      if(TIMING_TICKS == timing_type_) {
        initial_ticks_ = getticks();        
      } else {
        int rc(0);
        if(0 != (rc = getrusage(RUSAGE_THREAD, &initial_rusage_))) {
          std::ostringstream msg;
          msg << "Unable to track rusage - rc:" << rc << " errno:" << errno << std::endl;
          throw std::runtime_error(msg.str());
        }
      }

// end <Block_tracker_orm::init>
    }
    //! Pair of fields tying this to a package <I>inaccessible</I>
    Name_and_description_t package_name_and_description_;
    //! Label for this code block being timed <I>inaccessible</I>
    char const* label_;
    char const* file_name_;
    size_t line_number_;
    Timing_type timing_type_;
    //! If maps to processor number pins the thread to that processor first <I>inaccessible</I>
    int processor_;
    rusage initial_rusage_;
    ticks initial_ticks_;
    double cpu_mhz_;
    int code_locations_id_;
  };

} // namespace code_metrics
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_CODE_METRICS_BLOCK_TRACKER_ORM_H_
