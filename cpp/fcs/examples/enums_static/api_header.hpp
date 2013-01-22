/******************************************************************************
 * api_header.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file api_header.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_ENUMS_STATIC_API_HEADER_H_
#define _FCS_EXAMPLES_ENUMS_STATIC_API_HEADER_H_

#include <iostream>

/////// Standard windows approach for exposing symbols in a dll
#if defined(FCS_EXAMPLES_ENUMS_STATIC_API_STATIC_LIB) || defined(GLOBAL_STATIC_LINKAGE) || !defined(_MSC_VER_)
#define FCS_EXAMPLES_ENUMS_STATIC_API
#else
#ifdef FCS_EXAMPLES_ENUMS_STATIC_API_EXPORTS
#define FCS_EXAMPLES_ENUMS_STATIC_API __declspec(dllexport)
#else
#define FCS_EXAMPLES_ENUMS_STATIC_API __declspec(dllimport)
#endif
#endif

namespace fcs {
namespace examples {
namespace enums_static {

  // Library enumerations
  //! An enum specific to API with name API_first
  enum API_first {
    API_first_0,
    API_first_1,
    API_first_2,
    API_first_3,
    API_first_4,
    API_first_5
  };

  // Number of entries in API_first
  enum { API_FIRST_NUMBER_ENTRIES = 6 };

  //! Returns char array correpsonding to value of API_first
  extern FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(API_first e);

  //! Assigns to value the entry associated with text in char array or "INVALID_API_FIRST" if not valid
  extern FCS_EXAMPLES_ENUMS_STATIC_API void from_c_str(char const* txt, API_first &value);

  inline std::ostream& operator<<(std::ostream &out, API_first e) {
    return out << to_c_str(e);
  }

  //! An enum specific to API with name API_second
  enum API_second {
    API_second_0,
    API_second_1,
    API_second_2,
    API_second_3,
    API_second_4,
    API_second_5,
    API_second_6
  };

  // Number of entries in API_second
  enum { API_SECOND_NUMBER_ENTRIES = 7 };

  //! Returns char array correpsonding to value of API_second
  extern FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(API_second e);

  //! Assigns to value the entry associated with text in char array or "INVALID_API_SECOND" if not valid
  extern FCS_EXAMPLES_ENUMS_STATIC_API void from_c_str(char const* txt, API_second &value);

  inline std::ostream& operator<<(std::ostream &out, API_second e) {
    return out << to_c_str(e);
  }

  //! An enum specific to API with name API_mask_first
  enum API_mask_first {
    API_masked_first_0 = 1,
    API_masked_first_1 = 2,
    API_masked_first_2 = 4,
    API_masked_first_3 = 8,
    API_masked_first_4 = 16,
    API_masked_first_5 = 32,
    API_masked_first_6 = 64
  };

  enum { API_MASK_FIRST_NUMBER_ENTRIES = 7 };

  inline bool test_api_mask_first(int value, API_mask_first e) {
    return (e & value) == e;
  }

  inline void set_api_mask_first(int &value, API_mask_first e) {
    value |= e;
  }

  inline void clear_api_mask_first(int &value, API_mask_first e) {
    value &= ~e;
  }

  //! Fills ostream with comma separated list of mask entries set in API_mask_first
  extern
  void dump_api_mask_first(std::ostream &out, int e);

  //! An enum specific to API with name API_mask_second
  enum API_mask_second {
    API_masked_second_0 = 1,
    API_masked_second_1 = 2,
    API_masked_second_2 = 4,
    API_masked_second_3 = 8,
    API_masked_second_4 = 16,
    API_masked_second_5 = 32,
    API_masked_second_6 = 64
  };

  enum { API_MASK_SECOND_NUMBER_ENTRIES = 7 };

  inline bool test_api_mask_second(int value, API_mask_second e) {
    return (e & value) == e;
  }

  inline void set_api_mask_second(int &value, API_mask_second e) {
    value |= e;
  }

  inline void clear_api_mask_second(int &value, API_mask_second e) {
    value &= ~e;
  }

  //! Fills ostream with comma separated list of mask entries set in API_mask_second
  extern
  void dump_api_mask_second(std::ostream &out, int e);

  //! An enum specific to API with name API_with_assignments
  enum API_with_assignments {
    API_wa_42 = 42,
    API_wa_77 = 77
  };

  // Number of entries in API_with_assignments
  enum { API_WITH_ASSIGNMENTS_NUMBER_ENTRIES = 2 };

  //! Returns char array correpsonding to value of API_with_assignments
  extern FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(API_with_assignments e);

  //! Assigns to value the entry associated with text in char array or "INVALID_API_WITH_ASSIGNMENTS" if not valid
  extern FCS_EXAMPLES_ENUMS_STATIC_API void from_c_str(char const* txt, API_with_assignments &value);

  inline std::ostream& operator<<(std::ostream &out, API_with_assignments e) {
    return out << to_c_str(e);
  }

  //! An enum specific to API with name API_shorten_long_name
  enum API_shorten_long_name {
    API_shorten_long_name_0,
    API_shorten_long_name_1,
    API_shorten_long_name_2,
    API_shorten_long_name_3,
    API_shorten_long_name_4,
    API_shorten_long_name_5
  };

  // Number of entries in API_shorten_long_name
  enum { API_SHORTEN_LONG_NAME_NUMBER_ENTRIES = 6 };

  //! Returns char array correpsonding to value of API_shorten_long_name
  extern FCS_EXAMPLES_ENUMS_STATIC_API char const* to_c_str(API_shorten_long_name e);

  //! Assigns to value the entry associated with text in char array or "INVALID_API_SHORTEN_LONG_NAME" if not valid
  extern FCS_EXAMPLES_ENUMS_STATIC_API void from_c_str(char const* txt, API_shorten_long_name &value);

  inline std::ostream& operator<<(std::ostream &out, API_shorten_long_name e) {
    return out << to_c_str(e);
  }

  //! Dohh - clearly self explanatory
  enum { API_ANSWER_OF_UNIVERSE = 42 };

} // namespace enums_static
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_ENUMS_STATIC_API_HEADER_H_
