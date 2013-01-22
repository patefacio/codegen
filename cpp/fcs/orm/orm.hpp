/******************************************************************************
 * orm.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file orm.hpp
 *
 * \brief Api object relational mapping
 * 
 */
#ifndef _FCS_ORM_ORM_H_
#define _FCS_ORM_ORM_H_

#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>
#include <set>
#include <string>

namespace fcs {
namespace orm {

  // Library typedefs
  typedef std::vector< int > Id_list_t;
  typedef std::vector< std::string > String_list_t;
  typedef std::set< std::string > String_set_t;
  typedef std::vector< String_list_t > String_table_t;
  typedef boost::gregorian::date Date_t;
  typedef std::set< Date_t > Date_set_t;

  //! Name of this api
  inline
  char const* api_name() {
    return "fcs::orm::orm";
  }

  //! Description of this api
  inline
  char const* api_description() {
    return "Api supporting basic object relational mapping.";
  }

  inline
  std::pair< char const*, char const* >
  api_name_and_description() {
    return std::pair< char const*, char const* >(api_name(), api_description()); 
  }

} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_ORM_H_
