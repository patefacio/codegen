/******************************************************************************
 *
 * Copyright (c) all_types.cpp by Daniel Davidson
 *
 * All Rights Reserved. 
 *******************************************************************************/
/*! 
 * \file all_types.cpp
 *
 * \brief Has all types
 * 
 */

#include "fcs/codegen/coverage/all_types.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <sstream>
#include <iostream>


// custom <All_types pre-namespace custom>
// end <All_types pre-namespace custom>

namespace fcs {
namespace codegen {
namespace coverage {

  
// custom <All_types namespace custom>
// end <All_types namespace custom>


  // Support for streaming non-static streamable members of all_types
  std::ostream& operator<<(std::ostream& out, all_types const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "all_types:(" << &item << "):{";
    out << '\n' << indent << "  int_m:" << item.int_m_;
    out << '\n' << indent << "  double_m:" << item.double_m_;
    out << '\n' << indent << "  long_m:" << item.long_m_;
    out << '\n' << indent << "  long_double_m:" << item.long_double_m_;
    out << '\n' << indent << "  long_int_m:" << item.long_int_m_;
    out << '\n' << indent << "  long_long_m:" << item.long_long_m_;
    out << '\n' << indent << "  unsigned_int_m:" << item.unsigned_int_m_;
    out << '\n' << indent << "  unsigned_long_m:" << item.unsigned_long_m_;
    out << '\n' << indent << "  unsigned_long_long_m:" << item.unsigned_long_long_m_;
    out << '\n' << indent << "  char_m:" << item.char_m_;
    out << '\n' << indent << "  signed_char_m:" << item.signed_char_m_;
    out << '\n' << indent << "  unsigned_char_m:" << item.unsigned_char_m_;
    out << '\n' << indent << "  std_string_m:" << item.std_string_m_;
    out << '\n' << indent << "  boost_int8_t_m:" << item.boost_int8_t_m_;
    out << '\n' << indent << "  boost_int16_t_m:" << item.boost_int16_t_m_;
    out << '\n' << indent << "  boost_int32_t_m:" << item.boost_int32_t_m_;
    out << '\n' << indent << "  boost_int64_t_m:" << item.boost_int64_t_m_;
    out << '\n' << indent << "  boost_int_fast8_t_m:" << item.boost_int_fast8_t_m_;
    out << '\n' << indent << "  boost_int_fast16_t_m:" << item.boost_int_fast16_t_m_;
    out << '\n' << indent << "  boost_int_fast32_t_m:" << item.boost_int_fast32_t_m_;
    out << '\n' << indent << "  boost_int_fast64_t_m:" << item.boost_int_fast64_t_m_;
    out << '\n' << indent << "  boost_int_least8_t_m:" << item.boost_int_least8_t_m_;
    out << '\n' << indent << "  boost_int_least16_t_m:" << item.boost_int_least16_t_m_;
    out << '\n' << indent << "  boost_int_least32_t_m:" << item.boost_int_least32_t_m_;
    out << '\n' << indent << "  boost_int_least64_t_m:" << item.boost_int_least64_t_m_;
    out << '\n' << indent << "  boost_uint8_t_m:" << item.boost_uint8_t_m_;
    out << '\n' << indent << "  boost_uint16_t_m:" << item.boost_uint16_t_m_;
    out << '\n' << indent << "  boost_uint32_t_m:" << item.boost_uint32_t_m_;
    out << '\n' << indent << "  boost_uint64_t_m:" << item.boost_uint64_t_m_;
    out << '\n' << indent << "  boost_uint_fast8_t_m:" << item.boost_uint_fast8_t_m_;
    out << '\n' << indent << "  boost_uint_fast16_t_m:" << item.boost_uint_fast16_t_m_;
    out << '\n' << indent << "  boost_uint_fast32_t_m:" << item.boost_uint_fast32_t_m_;
    out << '\n' << indent << "  boost_uint_fast64_t_m:" << item.boost_uint_fast64_t_m_;
    out << '\n' << indent << "  boost_uint_least8_t_m:" << item.boost_uint_least8_t_m_;
    out << '\n' << indent << "  boost_uint_least16_t_m:" << item.boost_uint_least16_t_m_;
    out << '\n' << indent << "  boost_uint_least32_t_m:" << item.boost_uint_least32_t_m_;
    out << '\n' << indent << "  boost_uint_least64_t_m:" << item.boost_uint_least64_t_m_;
    out << indent << "}\n";
    return out;
  }


} // namespace coverage
} // namespace codegen
} // namespace fcs


