/******************************************************************************
 *
 * Copyright (c) streamers.hpp by Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
#ifndef _FCS_UTILS_STREAMERS_HPP_
#define _FCS_UTILS_STREAMERS_HPP_

#include "boost/shared_ptr.hpp"
#include <iostream>
#include <sstream>
#include <utility>
#include <memory>


namespace fcs {
namespace utils {
namespace streamers {

  template < typename T1, typename T2>
  inline std::ostream& operator<<(std::ostream& out, std::pair<T1, T2> const& p);
  template < typename T >
  inline std::ostream& operator<<(std::ostream &out, boost::shared_ptr<T> const& p);
  template < typename T >
  inline std::ostream& operator<<(std::ostream &out, std::shared_ptr<T> const& p);

  template < typename T1, typename T2 >
  inline std::ostream& print_key_value_pair(std::ostream &out,  std::pair< T1, T2 > const& p) {
    out << '(' << p.first << ',' << p.second << ")";
    return out;
  }

  //! Support for streaming std::pair
  template < typename T1, typename T2 >
  inline std::ostream& operator<<(std::ostream& out, std::pair<T1, T2> const& p) {
    return print_key_value_pair< T1, T2 >(out, p);
  }

  template < typename T >
  inline std::ostream& print_scalar_collection(std::ostream &out, T const& collection) {
    typename T::const_iterator current(collection.begin());
    typename T::const_iterator end(collection.end());
    out << '[';
    for(; current != end; ++current) {
      out << *current << ',';
    }
    out << "]";
    return out;
  }

  template < typename ForwardIterator, typename T >
  inline std::ostream& print_associative_collection(std::ostream &out, ForwardIterator begin, ForwardIterator end) {
    out << "[";
    for(; begin != end; ++begin) {
      T const& key_value(*begin);
      out << '(' << key_value.first << "=>" << key_value.second << "),";
    }
    out << "]";
    return out;
  }

  //! Support for streaming boost::shared_ptr
  template < typename T >
  inline std::ostream& operator<<(std::ostream &out, boost::shared_ptr<T> const& p) {
    T * item(p.get());
    if(item) {
      T const& i(*item);
      out << i;
    } else {
      out << "(null)";
    }
    return out;
  }

  //! Support for streaming std::shared_ptr
  template < typename T >
  inline std::ostream& operator<<(std::ostream &out, std::shared_ptr<T> const& p) {
    T * item(p.get());
    if(item) {
      T const& i(*item);
      out << i;
    } else {
      out << "(null)";
    }
    return out;
  }

  template < typename T >
  inline std::string stream_to_string(T const& t) {
    std::ostringstream out;
    out << t;
    return out.str();
  }

}
}
}
#endif
