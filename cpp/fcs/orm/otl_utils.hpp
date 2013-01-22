/******************************************************************************
 * otl_utils.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file otl_utils.hpp
 *
 * \brief Some utility functions
 * 
 */
#ifndef _FCS_ORM_OTL_UTILS_H_
#define _FCS_ORM_OTL_UTILS_H_

#include "fcs/orm/orm.hpp"
#include "fcs/orm/otl_config.hpp"
#include "fcs/utils/fixed_size_char_array.hpp"
#include <boost/date_time/gregorian/formatters.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <string>


// custom <Otl_utils global header section>

inline std::ostream & operator<<(std::ostream &out, otl_time const& t) {
  out << t.hour << ':' << t.minute << ':' << t.second;
  return out;
}

inline std::ostream & operator<<(std::ostream &out, otl_datetime const& t) {
  out << t.month << '/' << t.day << '/' << t.year 
      << ' ' << t.hour << ':' << t.minute << ':' << t.second;
  return out;
}

inline bool operator<(otl_time const& lhs, otl_time const& rhs) {
  return
    ((lhs.year != rhs.year)? lhs.year < rhs.year : (
      ((lhs.month != rhs.month)? lhs.month < rhs.month : (
        ((lhs.day != rhs.day)? lhs.day < rhs.day : (
          ((lhs.hour != rhs.hour)? lhs.hour < rhs.hour : (
            ((lhs.minute != rhs.minute)? lhs.minute < rhs.minute : (
              ((lhs.second != rhs.second)? lhs.second < rhs.second : (
                ((lhs.fraction != rhs.fraction)? lhs.fraction < rhs.fraction : (false
                  ))))))))))))));
}

inline bool operator<(otl_datetime const& lhs, otl_datetime const& rhs) {
  return
    ((lhs.year != rhs.year)? lhs.year < rhs.year : (
      ((lhs.month != rhs.month)? lhs.month < rhs.month : (
        ((lhs.day != rhs.day)? lhs.day < rhs.day : (
          ((lhs.hour != rhs.hour)? lhs.hour < rhs.hour : (
            ((lhs.minute != rhs.minute)? lhs.minute < rhs.minute : (
              ((lhs.second != rhs.second)? lhs.second < rhs.second : (
                ((lhs.fraction != rhs.fraction)? lhs.fraction < rhs.fraction : (false
                  ))))))))))))));
}

inline bool operator==(otl_time const& lhs, otl_time const& rhs) {
  return
    ((&lhs==&rhs) or (
      (lhs.year == rhs.year) and
      (lhs.month == rhs.month) and
      (lhs.day == rhs.day) and
      (lhs.hour == rhs.hour) and
      (lhs.minute == rhs.minute) and
      (lhs.second == rhs.second) and
      (lhs.fraction == rhs.fraction)));
}

inline bool operator!=(otl_time const& lhs, otl_time const& rhs) {
  return !operator==(lhs, rhs);
}

inline bool operator==(otl_datetime const& lhs, otl_datetime const& rhs) {
  return
    ((&lhs==&rhs) or (
      (lhs.year == rhs.year) and
      (lhs.month == rhs.month) and
      (lhs.day == rhs.day) and
      (lhs.hour == rhs.hour) and
      (lhs.minute == rhs.minute) and
      (lhs.second == rhs.second) and
      (lhs.fraction == rhs.fraction)));
}

inline bool operator!=(otl_datetime const& lhs, otl_datetime const& rhs) {
  return !operator==(lhs, rhs);
}

inline std::ostream & operator<<(std::ostream &out, otl_long_string const& ls) {
  out << ls.v;
  return out;
}

inline bool operator==(otl_long_string const& lhs, otl_long_string const& rhs) {
  return
    ((&lhs==&rhs) or (0 == strcmp(reinterpret_cast< char const * >(lhs.v), 
                                  reinterpret_cast< char const * >(rhs.v))));
}

inline bool operator!=(otl_long_string const& lhs, otl_long_string const& rhs) {
  return !operator==(lhs, rhs);
}

inline bool operator<(otl_long_string const& lhs, otl_long_string const& rhs) {
  return strcmp(reinterpret_cast< char const* >(lhs.v), 
                reinterpret_cast< char const* >(rhs.v));
}

// end <Otl_utils global header section>
namespace fcs {
namespace orm {

// custom <Otl_utils pre class section>

  inline std::string sql_quote(std::string const& value) {  
    std::string escaped;
    boost::replace_all_copy(back_inserter(escaped), value, "\"", "\\\"");
    std::string result("\"");
    result += escaped;
    result += '"';
    return result;
  }

  template< int ARRAY_SIZE >
  inline 
  std::string sql_quote(typename fcs::utils::Fixed_size_char_array< ARRAY_SIZE > const& value) {
    return sql_quote(std::string(value));
  }

  inline 
  std::string sql_quote(otl_long_string const& value) {
    return sql_quote(std::string(reinterpret_cast< char const* >(value.v)));
  }

  template < typename T >
  inline
  boost::posix_time::ptime otl_type_to_boost_ptime(T const& o) {
    return boost::posix_time::ptime
      (boost::gregorian::date(o.year, o.month, o.day), 
       boost::posix_time::hours(o.hour) + 
       boost::posix_time::minutes(o.minute) + 
       boost::posix_time::seconds(o.second));
  }

  inline
  boost::posix_time::ptime otl_datetime_to_boost_ptime(otl_datetime const& o) {
    return otl_type_to_boost_ptime< otl_datetime >(o);
  }

  inline
  boost::posix_time::ptime otl_time_to_boost_ptime(otl_time const& o) {
    return otl_type_to_boost_ptime< otl_time >(o);    
  }

  template < typename T >
  inline
  boost::posix_time::time_duration otl_type_to_boost_time_of_date(T const& o) {
    return boost::posix_time::time_duration
      (boost::posix_time::hours(o.hour) + 
       boost::posix_time::minutes(o.minute) + 
       boost::posix_time::seconds(o.second));
  }

  inline
  boost::posix_time::time_duration otl_datetime_to_boost_time_of_day(otl_datetime const& o) {
    return otl_type_to_boost_time_of_date< otl_datetime >(o);
  }

  inline
  boost::posix_time::time_duration otl_time_to_boost_time_of_day(otl_time const& o) {
    return otl_type_to_boost_time_of_date< otl_time >(o);
  }

  template < typename T >
  inline
  void boost_ptime_to_otl_type(boost::posix_time::ptime const& t, T &o) {
    boost::gregorian::date date(t.date());
    o.year = date.year();
    o.month = date.month();
    o.day = date.day();
    boost::posix_time::time_duration time_duration(t.time_of_day());
    o.hour = time_duration.hours();
    o.minute = time_duration.minutes();
    o.second = time_duration.seconds();
  }

  inline
  otl_datetime boost_ptime_to_otl_datetime(boost::posix_time::ptime const& t) {
    otl_datetime result;
    boost_ptime_to_otl_type(t, result);
    return result;
  }

  inline
  otl_time boost_ptime_to_otl_time(boost::posix_time::ptime const& t) {
    otl_time result;
    boost_ptime_to_otl_type(t, result);
    return result;
  }

  inline
  otl_datetime boost_date_to_otl_datetime(boost::gregorian::date const& d) {
    return boost_ptime_to_otl_datetime(boost::posix_time::ptime(d));
  }

  template < typename T >
  inline std::string sql_quote(T const& data) {
    return std::string(boost::lexical_cast< std::string >(data));
  }

  template <  >
  inline std::string sql_quote(std::string const& data) {
    return sql_quote(data);
  }

  template <  >
  inline std::string sql_quote(Date_t const& date) {
    std::ostringstream result;
    result << "date(" << sql_quote(boost::gregorian::to_sql_string(date)) << ')';
    return result.str();
  }

  template< typename INPUT_ITERATOR >
  inline
  std::string create_select_union(INPUT_ITERATOR begin, 
                                  INPUT_ITERATOR end,
                                  std::string const& name = "ignored",
                                  bool wrapped = true) {
    std::ostringstream result;
    if(begin != end) {
      if(wrapped) {
        result << '(';
      }
      result << "select "
             << sql_quote< typename INPUT_ITERATOR::value_type >(*begin) << " as " << name;
      for(++begin; begin != end; ++begin) {
        result << "\n  union select " << sql_quote< typename INPUT_ITERATOR::value_type >(*begin);
      }
      if(wrapped) {
        result << ')';
      }
    }
    return result.str();
  }

// end <Otl_utils pre class section>



} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_OTL_UTILS_H_
