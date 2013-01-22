/******************************************************************************
 * table_cell_string_conversion.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file table_cell_string_conversion.hpp
 *
 * \brief Methods for converting between table cells and strings
 * 
 */
#ifndef _FCS_TABLE_TABLE_CELL_STRING_CONVERSION_H_
#define _FCS_TABLE_TABLE_CELL_STRING_CONVERSION_H_

#include <pantheios/inserters.hpp>
#include "fcs/table/table.hpp"
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace fcs {
namespace table {

  //! Methods for converting between table cells and strings
  class Table_cell_string_conversion 
  {
  public:
  
// custom <Table_cell_string_conversion public header section>

    static bool convert_to_cell(std::string const& s, Table_cell_type table_cell_type, Cell_contents_t & contents) {
      using boost::spirit::_1;
      using boost::phoenix::ref;
      using boost::spirit::double_;
      using boost::spirit::float_;
      using boost::spirit::long_double;
      using boost::spirit::int_;
      using boost::spirit::uint_;
      using boost::spirit::long_long;
      using boost::spirit::qi::phrase_parse;
      using boost::spirit::ascii::space;

      std::string::const_iterator begin(s.begin());
      std::string::const_iterator end(s.end());
      bool result(false);
      switch(table_cell_type) {
       case CELL_TYPE_INT8: {
         boost::int8_t value(0);
         result = phrase_parse(begin, end, ( int_[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_INT32: {
         boost::int32_t value(0);
         result = phrase_parse(begin, end, ( int_[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_INT64: {
         boost::int64_t value(0);
         result = phrase_parse(begin, end, ( long_long[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_UINT8: {
         boost::uint8_t value(0);
         result = phrase_parse(begin, end, ( uint_[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_UINT32: {
         boost::uint32_t value(0);
         result = phrase_parse(begin, end, ( uint_[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_UINT64: {
         boost::uint64_t value(0);
         result = phrase_parse(begin, end, ( long_long[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_FLOAT: {
         float value(0.0);
         result = phrase_parse(begin, end, ( float_[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_DOUBLE: {
         double value(0.0);
         result = phrase_parse(begin, end, ( double_[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_LONG_DOUBLE: {
         long double value(0.0);
         result = phrase_parse(begin, end, ( long_double[ ref(value) = _1 ] ), space);
         contents = value;
         break;
       }
       case CELL_TYPE_STRING: {
         result = true;
         contents = s;
         break;
       }
      }
      return result;
    }

    static void convert_to_cell(std::string const& s, Cell_contents_t & contents) {
      using boost::spirit::_1;
      using boost::phoenix::ref;
      using boost::spirit::double_;
      using boost::spirit::long_long;
      using boost::spirit::qi::phrase_parse;
      using boost::spirit::ascii::space;

      std::string::const_iterator begin(s.begin());
      std::string::const_iterator end(s.end());
      double d(0);
      bool result(phrase_parse(begin, end, ( double_[ ref(d) = _1 ] ), space));
      if(result) {
        if((s.find('.') == std::string::npos)) {
          double const max_int32_t(std::numeric_limits< boost::int32_t >::max());
          double const min_int32_t(std::numeric_limits< boost::int32_t >::min());
          if((max_int32_t < d) or (min_int32_t > d)) {
#if defined(BOOST_HAS_LONG_LONG)
            boost::int64_t big_int(0);
            begin = s.begin();
            bool result(phrase_parse(begin, end, ( long_long[ ref(big_int) = _1 ] ), space));
#  if 0 
            std::cout << "For: " << s << " compare d:" << d << " with:" 
                      << big_int << " sizeof:" << sizeof(long long) 
                      << " result:" << result <<std::endl;
#  endif
            if(result) {
              contents = boost::int64_t(big_int);
            } else {
              contents = boost::int64_t(d);
            }
#else
            contents = boost::int64_t(d);
#endif
          } else {
            contents = boost::int32_t(d);
          }
        } else {
          contents = d;
        }
      } else {
        contents = s;
      }
    }

// end <Table_cell_string_conversion public header section>

  };

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TABLE_CELL_STRING_CONVERSION_H_
