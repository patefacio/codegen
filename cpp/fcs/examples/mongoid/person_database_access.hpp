/******************************************************************************
 * person_database_access.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file person_database_access.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_MONGOID_PERSON_DATABASE_ACCESS_H_
#define _FCS_EXAMPLES_MONGOID_PERSON_DATABASE_ACCESS_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "fcs/examples/mongoid/mongoid.hpp"
#include "mongo/client/dbclient.h"
#include "fcs/mongoid/connection_registry.hpp"
#include "fcs/patterns/singleton.hpp"
#include <string>

namespace fcs {
namespace examples {
namespace mongoid {

  // Forward typedefs
  typedef std::vector< Person > Person_list_t;

  class Person_database_access :
    public fcs::patterns::Singleton< Person_database_access > 
  {
  public:

    // Class typedefs
    typedef Person Access_t;

  protected:

    Person_database_access() :
      connection_(fcs::mongoid::Connection_registry<>::get_instance()->get_client_connection("trading")),
      person_collection_name_("trading.person") 
    {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Person_database_access(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
    }

  public:

    ~Person_database_access() {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Destroyed Person_database_access(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
    }

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    std::string const& person_collection_name() const {
      return person_collection_name_;
    }

    void insert(Person const& pod) {
      connection_->insert(person_collection_name_, pod.to_bson());
    }

    void remove_all() {
      mongo::BSONObj empty;
      connection_->remove(person_collection_name_, empty);
    }

    void find_all(Person_list_t &found) {
      mongo::BSONObj empty_where;
      find_all(found, empty_where);
    }

    void find_all(Person_list_t &found, mongo::BSONObj const& where) {
      std::auto_ptr< mongo::DBClientCursor > cursor(connection_->query(person_collection_name_, where));

      while(cursor->more()) {
        mongo::BSONObj next(cursor->next());
        try {
          Person pod;
          pod.from_bson(next);
          found.push_back(pod);
        } catch(std::exception const& excp) {
          pantheios::log(PANTHEIOS_SEV_ERROR, 
                         "ERROR: Skipping mongoid of type Person with error: ", 
                         excp.what(),
                         "\nand contents:\n",
                         next.jsonString().c_str());
        }
      }
    }
    bool ensure_index_on_age() {
      return connection_->ensureIndex(person_collection_name_, BSON( "age" << 1 ));
    }
    bool ensure_unique_index_on_name() {
      bool const unique(true);
      return connection_->ensureIndex(person_collection_name_, BSON( "name" << 1 ), unique);
    }
  private:
    fcs::mongoid::Client_connection_ptr connection_;
    std::string const person_collection_name_;
    friend class fcs::patterns::Singleton_impl< Person_database_access >;
  };

} // namespace mongoid
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_MONGOID_PERSON_DATABASE_ACCESS_H_
