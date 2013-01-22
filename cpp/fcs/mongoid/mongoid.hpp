/******************************************************************************
 * mongoid.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file mongoid.hpp
 *
 * \brief Support for storing basic data in mongoid database
 * 
 */
#ifndef _FCS_MONGOID_MONGOID_H_
#define _FCS_MONGOID_MONGOID_H_

#include <pantheios/pantheios.hpp>
#include "mongo/client/dbclient.h"
#include "fcs/utils/fixed_size_char_array.hpp"

namespace fcs {
namespace mongoid {

  // Library typedefs
  typedef mongo::DBClientConnection * Client_connection_ptr;
  typedef fcs::utils::Fixed_size_char_array< 25 > Object_id_t;
  typedef long long Bson_int64_t;

  //! Name of this api
  inline
  char const* api_name() {
    return "fcs::mongoid::mongoid";
  }

  //! Description of this api
  inline
  char const* api_description() {
    return "Api supporting mapping of data into mongodb";
  }

  inline
  std::pair< char const*, char const* >
  api_name_and_description() {
    return std::pair< char const*, char const* >(api_name(), api_description()); 
  }

} // namespace mongoid
} // namespace fcs
#endif // _FCS_MONGOID_MONGOID_H_
