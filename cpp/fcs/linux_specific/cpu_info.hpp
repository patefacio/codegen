/******************************************************************************
 * cpu_info.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file cpu_info.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_LINUX_SPECIFIC_CPU_INFO_H_
#define _FCS_LINUX_SPECIFIC_CPU_INFO_H_

#include "fcs/linux_specific/system_file_parse_exception.hpp"
#include "fcs/utils/exception/make_exception.hpp"
#include "fcs/patterns/singleton.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iterator>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <map>
#include <string>

namespace fcs {
namespace linux_specific {


  /**

  Information stored on a processor basis in cpuinfo.
  The fields in this class are dynamically generated from parsing
  cpuinfo.

  */
  struct Processor 
  {

    // Class typedefs
    typedef std::map< std::string, std::string > Proc_key_to_value_t;

    friend std::ostream& operator<<(std::ostream& out, Processor const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Proc_key_to_value_t const& proc_key_to_value() const {
      return proc_key_to_value_;
    }

    std::string const& processor() const {
      return processor_;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Potentially useful keys that show up on Linux 2.6.32-24-generic
    ////////////////////////////////////////////////////////////////////////////////
    std::string vendor_id() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("vendor_id"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string cpu_family() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("cpu_family"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string model() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("model"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string model_name() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("model_name"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string stepping() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("stepping"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string microcode() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("microcode"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string cpu_mhz() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("cpu_mhz"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string cache_size() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("cache_size"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string physical_id() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("physical_id"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string siblings() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("siblings"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string core_id() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("core_id"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string cpu_cores() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("cpu_cores"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string apicid() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("apicid"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string initial_apicid() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("initial_apicid"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string fpu() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("fpu"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string fpu_exception() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("fpu_exception"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string cpuid_level() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("cpuid_level"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string wp() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("wp"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string flags() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("flags"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string bogomips() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("bogomips"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string clflush_size() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("clflush_size"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string cache_alignment() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("cache_alignment"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string address_sizes() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("address_sizes"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    std::string power_management() const { 
      std::string result;
      Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("power_management"));
      if(found != proc_key_to_value_.end()) { 
        result = found->second;
      }
      return result;
    }

    void dump(std::ostream &out) const { 

      cpu_set_t mask;
      long affinity(sched_getaffinity(0, sizeof(mask), &mask));
      if(0 == affinity) { 
        out << "Running from process: " << getpid() 
            << "\n processor count: " << CPU_COUNT(&mask)
            << "\n processor 0 set: " << CPU_ISSET(0, &mask)
            << "\n processor 1 set: " << CPU_ISSET(1, &mask) << std::endl;
        out << "----- processor -----\n";
      }
      out << "\tvendor_id:" << vendor_id() << "\n";
      out << "\tcpu_family:" << cpu_family() << "\n";
      out << "\tmodel:" << model() << "\n";
      out << "\tmodel_name:" << model_name() << "\n";
      out << "\tstepping:" << stepping() << "\n";
      out << "\tmicrocode:" << microcode() << "\n";
      out << "\tcpu_mhz:" << cpu_mhz() << "\n";
      out << "\tcache_size:" << cache_size() << "\n";
      out << "\tphysical_id:" << physical_id() << "\n";
      out << "\tsiblings:" << siblings() << "\n";
      out << "\tcore_id:" << core_id() << "\n";
      out << "\tcpu_cores:" << cpu_cores() << "\n";
      out << "\tapicid:" << apicid() << "\n";
      out << "\tinitial_apicid:" << initial_apicid() << "\n";
      out << "\tfpu:" << fpu() << "\n";
      out << "\tfpu_exception:" << fpu_exception() << "\n";
      out << "\tcpuid_level:" << cpuid_level() << "\n";
      out << "\twp:" << wp() << "\n";
      out << "\tflags:" << flags() << "\n";
      out << "\tbogomips:" << bogomips() << "\n";
      out << "\tclflush_size:" << clflush_size() << "\n";
      out << "\tcache_alignment:" << cache_alignment() << "\n";
      out << "\taddress_sizes:" << address_sizes() << "\n";
      out << "\tpower_management:" << power_management() << "\n";
    }
  private:
    Proc_key_to_value_t proc_key_to_value_;
    std::string processor_;
    friend class Cpu_info;
  };

  // Support for streaming non-static streamable members of Processor
  inline
  std::ostream& operator<<(std::ostream& out, Processor const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Processor:(" << &item << "):{";
    out << '\n' << indent << "  proc_key_to_value:" << item.proc_key_to_value_;
    out << '\n' << indent << "  processor:" << item.processor_;
    out << indent << "}\n";
    return out;
  } 

  /**

  Class to parse the cpuinfo file. This might be of use to interrogate
  from code the stats of the machine for better enabling <apple to apple>
  comparisons.

  */
  class Cpu_info :
    public fcs::patterns::Singleton< Cpu_info > 
  {
  public:

    // Class typedefs
    typedef std::vector< Processor > Processor_list_t;

  protected:

    Cpu_info() :
      processors_() 
    {
      ctor_default_init();
    }

  public:

    friend std::ostream& operator<<(std::ostream& out, Cpu_info const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Processor_list_t const& processors() const {
      return processors_;
    }

    void dump(std::ostream &out) const { 
      out << "----- cpu_info -----\n";
      Processor_list_t::const_iterator it(processors_.begin());
      Processor_list_t::const_iterator end(processors_.end());
      for(; it != end; ++it) { 
        it->dump(out);
      }
    }
  private:

    void ctor_default_init() { 

      boost::regex processor_split_regex("processor\\s*:\\s*");
      boost::regex split_line_regex("\n");
      boost::regex line_entry_regex("^([\\w\\s]+):\\s*(.*)$");
      boost::regex empty_line_regex("^\\s*$");
      boost::regex just_whitespace_regex("\\s+");
      std::string const cpu_info_file("/proc/cpuinfo");
      std::ifstream cpu_info_stream(cpu_info_file.c_str());
      std::string text((std::istreambuf_iterator<char>(cpu_info_stream)), std::istreambuf_iterator<char>());

      // split the cpuinfo by processor entries 
      typedef std::vector< std::string > Tokens_t;
      Tokens_t tokens;
      boost::regex_split(std::back_inserter(tokens), text, processor_split_regex);
      Tokens_t::const_iterator processor_end(tokens.end());

      Processor empty_processor;
      processors_.assign(tokens.size(), empty_processor);
      size_t i(0);
      for(Tokens_t::const_iterator processor_it(tokens.begin()); processor_it != processor_end; ++processor_it, ++i) { 
        std::string processor_text(*processor_it);
        // first pull off the processor number
        size_t new_line_pos(processor_text.find_first_of('\n'));
        if(new_line_pos != std::string::npos) { 
          std::string processor_id(processor_text.substr(0, new_line_pos));
          Processor &processor(processors_[i]);
          processor.processor_ = processor_id;
          processor_text.erase(0, new_line_pos);
          // split the lines by key/value
          Tokens_t lines;
          boost::regex_split(std::back_inserter(lines), processor_text, split_line_regex);
          Tokens_t::const_iterator lines_end(lines.end());
          for(Tokens_t::const_iterator lines_it(lines.begin()); lines_it != lines_end; ++lines_it) { 
             if(boost::regex_match(*lines_it, empty_line_regex)) { 
               continue;
             }

             boost::smatch matches;
             bool result(boost::regex_match(*lines_it, matches, line_entry_regex));
             if(result) { 

               std::string key(matches[1].first, matches[1].second);
               boost::trim(key);
               boost::to_lower(key);

               std::string key_no_whitespace(
                 boost::regex_replace(key, just_whitespace_regex, "_"));

               processor.proc_key_to_value_[key_no_whitespace] = 
                 std::string(matches[2].first, matches[2].second);

             } else { 
               throw fcs::utils::exception::make_exception< System_file_parse_exception >
                 ("parsing_cpuinfo", __LINE__, __FILE__) 
                 << System_file_parse_exception::filename_tag(cpu_info_file);
             }
          } 
        }

      }
    }
    Processor_list_t processors_;
    friend class fcs::patterns::Singleton_impl< Cpu_info >;
  };

  // Support for streaming non-static streamable members of Cpu_info
  inline
  std::ostream& operator<<(std::ostream& out, Cpu_info const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Cpu_info:(" << &item << "):{";
    out << '\n' << indent << "  processors:" << item.processors_;
    out << indent << "}\n";
    return out;
  } 

} // namespace linux_specific
} // namespace fcs
#endif // _FCS_LINUX_SPECIFIC_CPU_INFO_H_
