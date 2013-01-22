/******************************************************************************
 * connection_registry.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file connection_registry.hpp
 *
 * \brief Place to get database connections
 * 
 */
#ifndef _FCS_MONGOID_CONNECTION_REGISTRY_H_
#define _FCS_MONGOID_CONNECTION_REGISTRY_H_

#include <pantheios/pantheios.hpp>
#include "fcs/mongoid/mongoid.hpp"
#include "fcs/mongoid/mongoid_ini_parser.hpp"
#include "fcs/patterns/singleton.hpp"
#include <boost/thread/tss.hpp>
#include <memory>
#include <map>
#include <string>

namespace fcs {
namespace mongoid {

  //! Place to get database connections
  template < typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Connection_registry :
    public fcs::patterns::Singleton< Connection_registry< LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef boost::thread_specific_ptr< mongo::DBClientConnection > Tss_connection_t;
    typedef std::shared_ptr< Tss_connection_t > Thread_connection_ptr;
    typedef std::map< std::string, Thread_connection_ptr > Thread_connection_map_t;

  protected:

    Connection_registry() :
      database_configuration_map_(),
      lock_(),
      thread_connection_map_() 
    {
      ctor_default_init();
    }

  public:

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Database_configuration_map_t const& database_configuration_map() const {
      return database_configuration_map_;
    }

  
// custom <Connection_registry public header section>

    void register_connection_info(std::string const& connection_name,
                                  Mongoid_database_config const& mongoid_database_configuration) {
      GUARD_TYPE guard(lock_);
      typedef std::pair< Database_configuration_map_t::iterator, bool > Insert_result_t;
      Insert_result_t insert_result
        (database_configuration_map_.insert
         (Database_configuration_map_t::value_type(connection_name, mongoid_database_configuration)));

      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Registered connection_info: ", 
                     connection_name.c_str(), " with server string:",
                     mongoid_database_configuration.server_.c_str());

    }

    Mongoid_database_config retrieve_connection_info(std::string const& connection_name) {
      GUARD_TYPE guard(lock_);
      typedef std::pair< Database_configuration_map_t::iterator, bool > Insert_result_t;
      Mongoid_database_config empty;
      Insert_result_t insert_result(
        database_configuration_map_.insert
        (Database_configuration_map_t::value_type(connection_name, empty)));

      pantheios::log(PANTHEIOS_SEV_DEBUG, "Retrieved connection_info: ", 
                     connection_name.c_str());

      return insert_result.first->second;
    }

    Client_connection_ptr get_client_connection(std::string const& database_name) {
      Thread_connection_map_t::iterator found_connnection(thread_connection_map_.find(database_name));
      if(found_connnection != thread_connection_map_.end()) {
        return found_connnection->second->get();
      } else {
        Database_configuration_map_t::const_iterator found(database_configuration_map_.find(database_name));
        if(found != database_configuration_map_.end()) {
          Mongoid_database_config const& mongoid_database_configuration(found->second);
          mongo::DBClientConnection *client_connection(new mongo::DBClientConnection());
          Thread_connection_ptr thread_connection(new Tss_connection_t());
          thread_connection_map_[database_name] = thread_connection;

          if(0 == thread_connection->get()) {
            std::string errmsg;
            if(!client_connection->connect(mongoid_database_configuration.server_, errmsg)) {
              std::ostringstream msg;
              msg << "Could not connect to database: " << mongoid_database_configuration
                  << "\n\tError: " << errmsg;
              delete client_connection;
              throw std::runtime_error(msg.str());
            } else {
              thread_connection->reset(client_connection);
              pantheios::log(PANTHEIOS_SEV_NOTICE, "Connected to database: ", 
                             database_name.c_str());
            }
          } else {
            // TODO: Fail
          }

          return client_connection;
        } else {
          std::ostringstream msg;
          msg << "Could not find configuration information to get connection for: " << database_name;
          throw std::runtime_error(msg.str());
        }
      }
    }

// end <Connection_registry public header section>

  private:

    //! Initialize the instance
    inline void ctor_default_init() {
      
// custom <Connection_registry::ctor_default_init>

      Mongoid_ini_parser parser;
      BOOST_FOREACH(Database_configuration_map_t::value_type const& vt, 
                    parser.database_configuration_map()) {
        register_connection_info(vt.first, vt.second);
      }

// end <Connection_registry::ctor_default_init>
    }
    //! Maps name of connection to its configuration info <I>read only</I>
    Database_configuration_map_t database_configuration_map_;
    //! For protecting the registry map <I>inaccessible</I>
    LOCK_TYPE lock_;
    //! Map of connections in tss (i.e. one per thread) <I>inaccessible</I>
    Thread_connection_map_t thread_connection_map_;
    friend class fcs::patterns::Singleton_impl< Connection_registry >;
  };

} // namespace mongoid
} // namespace fcs
#endif // _FCS_MONGOID_CONNECTION_REGISTRY_H_
