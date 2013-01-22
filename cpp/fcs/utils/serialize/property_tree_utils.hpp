/******************************************************************************
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef _FCS_UTILS_PROPERTY_TREE_H_
#define _FCS_UTILS_PROPERTY_TREE_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <exception>
#include <vector>
#include <map>
#include <string>
#include <iostream>


namespace fcs {
namespace utils {
namespace serialize {

  template < typename T >
  void put_to_property_tree(std::string const& path, boost::property_tree::ptree &tree, T const& value) {
    if(path.size()) {
      tree.put(path, value);
    } else {
      tree.push_back(std::make_pair(std::string(), 
                                    boost::lexical_cast< boost::property_tree::ptree::data_type >(value)));
    }
  }

  template < typename T, typename ALLOC >
  inline
  void put_to_property_tree(std::string const& path, boost::property_tree::ptree &tree, std::vector< T, ALLOC > const& value) {
    typename std::vector< T, ALLOC >::const_iterator it(value.begin());
    typename std::vector< T, ALLOC >::const_iterator end(value.end());
    boost::property_tree::ptree &child(tree.add_child(path, boost::property_tree::ptree()));
    for(; it != end; ++it) {
      put_to_property_tree(std::string(), child, *it);
    }
  }

  template < typename K, typename V, typename PR, typename ALLOC > 
  inline 
  void put_to_property_tree(std::string const& path, boost::property_tree::ptree &tree, std::map< K, V, PR, ALLOC > const& m) {
    typename std::map< K, V, PR, ALLOC >::const_iterator it(m.begin());
    typename std::map< K, V, PR, ALLOC >::const_iterator end(m.end());
    boost::property_tree::ptree &child(tree.add_child(path, boost::property_tree::ptree()));
    for(; it != end; ++it) {
      put_to_property_tree(it->first, child, it->second);
    }
  }

  template < typename T >
  inline
  void get_from_property_tree(std::string const& path, boost::property_tree::ptree const& tree, T & value) {
    if(path.size()) {
      value = tree.get(path, value);
    } else {
      value = boost::lexical_cast< T >(tree.data());
    }
  }


  template < typename T, typename ALLOC >
  inline
  void get_from_property_tree(std::string const& path, boost::property_tree::ptree const& tree, std::vector< T, ALLOC > & value) {
    boost::property_tree::ptree const& child(tree.get_child(path));
    boost::property_tree::ptree::const_iterator it(child.begin());
    boost::property_tree::ptree::const_iterator end(child.end());
    for(; it != end; ++it) {
      boost::property_tree::ptree const& data(it->second);
      T temp;
      get_from_property_tree(std::string(), data, temp);
      value.push_back(temp);
    }
  }


  template < typename K, typename V, typename PR, typename ALLOC > 
  inline 
  void get_from_property_tree(std::string const& path, boost::property_tree::ptree const& tree, std::map< K, V, PR, ALLOC > & m) {
    boost::property_tree::ptree const& child(tree.get_child(path));
    boost::property_tree::ptree::const_iterator it(child.begin());
    boost::property_tree::ptree::const_iterator end(child.end());
    for(; it != end; ++it) {
      boost::property_tree::ptree const& data(it->second);
      V temp;
      get_from_property_tree(std::string(), data, temp);
      m[it->first] = temp;
    }
  }

}
}
}



#endif
