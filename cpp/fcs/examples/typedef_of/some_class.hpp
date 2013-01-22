/******************************************************************************
 * some_class.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file some_class.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_TYPEDEF_OF_SOME_CLASS_H_
#define _FCS_EXAMPLES_TYPEDEF_OF_SOME_CLASS_H_

#include <vector>
#include <map>
#include <string>
#include <set>

namespace fcs {
namespace examples {
namespace typedef_of {

  // Forward typedefs
  typedef std::vector< int > Int_list_t;
  typedef std::set< char > Char_set_t;
  typedef std::map< std::string, int > String_to_int_map_t;
  typedef std::multimap< std::string, double > String_to_double_mmap_t;
  typedef std::vector< int > Ages_list_t;
  typedef std::set< char > Letters_set_t;
  typedef std::map< std::string, int > Name_to_age_map_t;
  typedef std::multimap< std::string, double > Attribute_to_measurements_mmap_t;
  typedef std::vector< int > Int_name_list_t;
  typedef std::set< char > Char_name_set_t;
  typedef std::map< std::string, int > String_int_name_map_t;
  typedef std::multimap< std::string, double > String_double_name_mmap_t;
  typedef std::vector< int > Ages_full_name_t;
  typedef std::set< char > Char_full_name_t;
  typedef std::map< std::string, int > Name_to_age_full_name_t;
  typedef std::multimap< std::string, double > Attribute_to_measurements_full_name_t;

  class some_class 
  {
  public:

    // Class typedefs
    typedef std::vector< int > Int_list_t;
    typedef std::set< char > Char_set_t;
    typedef std::map< std::string, int > String_to_int_map_t;
    typedef std::multimap< std::string, double > String_to_double_mmap_t;
    typedef std::vector< int > Ages_list_t;
    typedef std::set< char > Letters_set_t;
    typedef std::map< std::string, int > Name_to_age_map_t;
    typedef std::multimap< std::string, double > Attribute_to_measurements_mmap_t;
    typedef std::vector< int > Int_name_list_t;
    typedef std::set< char > Char_name_set_t;
    typedef std::map< std::string, int > String_int_name_map_t;
    typedef std::multimap< std::string, double > String_double_name_mmap_t;
    typedef std::vector< int > Ages_full_name_t;
    typedef std::set< char > Char_full_name_t;
    typedef std::map< std::string, int > Name_to_age_full_name_t;
    typedef std::multimap< std::string, double > Attribute_to_measurements_full_name_t;

  };

} // namespace typedef_of
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_TYPEDEF_OF_SOME_CLASS_H_
