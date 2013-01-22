/******************************************************************************
 * connection_system.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file connection_system.hpp
 *
 * \brief Holds the underlying database connection on per thread basis
 * 
 */
#ifndef _FCS_ORM_SYSTEM_CONNECTION_SYSTEM_H_
#define _FCS_ORM_SYSTEM_CONNECTION_SYSTEM_H_

#include <pantheios/inserters/hex_ptr.hpp>
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "fcs/orm/connection_registry.hpp"
#include "fcs/patterns/singleton.hpp"
#include <boost/thread/tss.hpp>

namespace fcs {
namespace orm {
namespace system {

  //! Holds the underlying database connection on per thread basis
  class Connection_system :
    public fcs::patterns::Singleton< Connection_system > 
  {
  protected:

    Connection_system() :
      tss_connection_() 
    {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Connection_system(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
    }

  public:

    ~Connection_system() {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Destroyed Connection_system(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
    }

    void reset() {
      otl_connect *result(tss_connection_.get());
      if(result) {
        tss_connection_.reset();
        pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Resetting otl_connect object for system: ",
                       pantheios::hex_ptr(result));
      }
    }

    otl_connect *get_connection() {
      std::string const dsn("system");
      otl_connect *result(tss_connection_.get());
      if(0 == result) {
        result = new otl_connect;
        Connection_info connection_info(Connection_registry<>::get_instance()->retrieve_connection_info(dsn));
        result->rlogon(connection_info.connection_string().c_str(), 0);
        tss_connection_.reset(result);
      }  

      pantheios::log(PANTHEIOS_SEV_DEBUG, "Retrieving otl_connect for system: ",
                     pantheios::hex_ptr(result));

      return result;
    }
  private:
    boost::thread_specific_ptr< otl_connect > tss_connection_;
    friend class fcs::patterns::Singleton_impl< Connection_system >;
  };

} // namespace system
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_SYSTEM_CONNECTION_SYSTEM_H_
