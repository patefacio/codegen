/******************************************************************************
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
#ifndef _FCS_DEBUG_SUPPORT_HPP_
#define _FCS_DEBUG_SUPPORT_HPP_


#if defined(DEBUG_FCS_STARTUP)
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include <pantheios/trace.h>

#    define FCS_LOG_CTOR() \
    pantheios::log(PANTHEIOS_SEV_DEBUG, \
                   __FILE__ " (" PANTHEIOS_STRINGIZE(__LINE__), ") ", \
                   typeid(this).name(), " ctor (",                    \
                   pantheios::hex_ptr(reinterpret_cast<void*>(this)), \
                   pantheios::character(')'))

#    define FCS_LOG_DTOR(type) \
    pantheios::log(PANTHEIOS_SEV_DEBUG, \
                   __FILE__ " (" PANTHEIOS_STRINGIZE(__LINE__), ") ", \
                   typeid(this).name(), " dtor (",                    \
                   pantheios::hex_ptr(reinterpret_cast<void*>(this)), \
                   pantheios::character(')'))

#else
#    define FCS_LOG_CTOR(type)
#    define FCS_LOG_DTOR(type)
#endif

#if defined(DEBUG)
#  define DEBUG_DUMP_METHOD()   \
  bool debug_dump() {           \
    if(this) {                  \
      std::cout << *this;       \
      return true;              \
    }                           \
    return false;               \
  }

#  define DEFINE_DEBUG_DUMP(class_name)       \
  static bool include_debug_dump(static_cast< class_name * >(0)->debug_dump());
#else
#  define DEBUG_DUMP_METHOD() 
#  define DEFINE_DEBUG_DUMP(class_name)
#endif

namespace fcs {
namespace utils {

}
}

#endif
