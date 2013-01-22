/******************************************************************************
 * some_other_class.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file some_other_class.cpp
 *
 * \brief 
 * 
 */

#include "fcs/examples/enums_static/some_other_class.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream>


// custom <some_other_class pre-namespace custom>
// end <some_other_class pre-namespace custom>

namespace fcs {
namespace examples {
namespace enums_static {

  
// custom <some_other_class namespace custom>
// end <some_other_class namespace custom>


  // Class enumerations

  FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(some_other_class::SCOPED_first e) {
    char const* values[] = {
      "SCOPED_first_0",
      "SCOPED_first_1",
      "SCOPED_first_2",
      "SCOPED_first_3",
      "SCOPED_first_4",
      "SCOPED_first_5"
    };
    size_t index(e);
    return ((index < some_other_class::SCOPED_FIRST_NUMBER_ENTRIES)? values[index] : "INVALID_SCOPED_FIRST");
  } 
  FCS_EXAMPLES_ENUMS_STATIC_API void from_c_str(char const* txt, some_other_class::SCOPED_second &value) {
    if(0 == std::strcmp("SCOPED_second_0", txt)) {
      value = some_other_class::SCOPED_second_0;
      return;
    }
    if(0 == std::strcmp("SCOPED_second_1", txt)) {
      value = some_other_class::SCOPED_second_1;
      return;
    }
    if(0 == std::strcmp("SCOPED_second_2", txt)) {
      value = some_other_class::SCOPED_second_2;
      return;
    }
    if(0 == std::strcmp("SCOPED_second_3", txt)) {
      value = some_other_class::SCOPED_second_3;
      return;
    }
    if(0 == std::strcmp("SCOPED_second_4", txt)) {
      value = some_other_class::SCOPED_second_4;
      return;
    }
    if(0 == std::strcmp("SCOPED_second_5", txt)) {
      value = some_other_class::SCOPED_second_5;
      return;
    }
    if(0 == std::strcmp("SCOPED_second_6", txt)) {
      value = some_other_class::SCOPED_second_6;
      return;
    }
    std::string msg("No SCOPED_second value corresponding to: ");
    msg += txt;
    throw std::runtime_error(txt);
  }

  FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(some_other_class::SCOPED_second e) {
    char const* values[] = {
      "SCOPED_second_0",
      "SCOPED_second_1",
      "SCOPED_second_2",
      "SCOPED_second_3",
      "SCOPED_second_4",
      "SCOPED_second_5",
      "SCOPED_second_6"
    };
    size_t index(e);
    return ((index < some_other_class::SCOPED_SECOND_NUMBER_ENTRIES)? values[index] : "INVALID_SCOPED_SECOND");
  } 
  FCS_EXAMPLES_ENUMS_STATIC_API void some_other_class::dump_scoped_mask_first(std::ostream &out, int e) {
    out << '(';
    if(test_scoped_mask_first(e, some_other_class::SCOPED_masked_first_0)) {
      out << "SCOPED_masked_first_0,";
    }
    if(test_scoped_mask_first(e, some_other_class::SCOPED_masked_first_1)) {
      out << "SCOPED_masked_first_1,";
    }
    if(test_scoped_mask_first(e, some_other_class::SCOPED_masked_first_2)) {
      out << "SCOPED_masked_first_2,";
    }
    if(test_scoped_mask_first(e, some_other_class::SCOPED_masked_first_3)) {
      out << "SCOPED_masked_first_3,";
    }
    if(test_scoped_mask_first(e, some_other_class::SCOPED_masked_first_4)) {
      out << "SCOPED_masked_first_4,";
    }
    if(test_scoped_mask_first(e, some_other_class::SCOPED_masked_first_5)) {
      out << "SCOPED_masked_first_5,";
    }
    if(test_scoped_mask_first(e, some_other_class::SCOPED_masked_first_6)) {
      out << "SCOPED_masked_first_6,";
    }
    out << ')';
  } 
  FCS_EXAMPLES_ENUMS_STATIC_API void some_other_class::dump_scoped_mask_second(std::ostream &out, int e) {
    out << '(';
    if(test_scoped_mask_second(e, some_other_class::SCOPED_masked_second_0)) {
      out << "SCOPED_masked_second_0,";
    }
    if(test_scoped_mask_second(e, some_other_class::SCOPED_masked_second_1)) {
      out << "SCOPED_masked_second_1,";
    }
    if(test_scoped_mask_second(e, some_other_class::SCOPED_masked_second_2)) {
      out << "SCOPED_masked_second_2,";
    }
    if(test_scoped_mask_second(e, some_other_class::SCOPED_masked_second_3)) {
      out << "SCOPED_masked_second_3,";
    }
    if(test_scoped_mask_second(e, some_other_class::SCOPED_masked_second_4)) {
      out << "SCOPED_masked_second_4,";
    }
    if(test_scoped_mask_second(e, some_other_class::SCOPED_masked_second_5)) {
      out << "SCOPED_masked_second_5,";
    }
    if(test_scoped_mask_second(e, some_other_class::SCOPED_masked_second_6)) {
      out << "SCOPED_masked_second_6,";
    }
    out << ')';
  } 
  FCS_EXAMPLES_ENUMS_STATIC_API void from_c_str(char const* txt, some_other_class::SCOPED_with_assignments &value) {
    if(0 == std::strcmp("SCOPED_wa_42", txt)) {
      value = some_other_class::SCOPED_wa_42;
      return;
    }
    if(0 == std::strcmp("SCOPED_wa_77", txt)) {
      value = some_other_class::SCOPED_wa_77;
      return;
    }
    std::string msg("No SCOPED_with_assignments value corresponding to: ");
    msg += txt;
    throw std::runtime_error(txt);
  }

  FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(some_other_class::SCOPED_with_assignments e) {
    switch(e) {
      case some_other_class::SCOPED_wa_42: return "SCOPED_wa_42";
      case some_other_class::SCOPED_wa_77: return "SCOPED_wa_77";
    }
    return "INVALID_SCOPED_WITH_ASSIGNMENTS";
  } 

  FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(some_other_class::SCOPED_shorten_long_name e) {
    char const* values[] = {
      "SCOPED_sln_0",
      "SCOPED_sln_1",
      "SCOPED_sln_2",
      "SCOPED_sln_3",
      "SCOPED_sln_4",
      "SCOPED_sln_5"
    };
    size_t index(e);
    return ((index < some_other_class::SCOPED_SHORTEN_LONG_NAME_NUMBER_ENTRIES)? values[index] : "INVALID_SCOPED_SHORTEN_LONG_NAME");
  } 


} // namespace enums_static
} // namespace examples
} // namespace fcs


