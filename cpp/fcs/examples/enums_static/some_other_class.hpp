/******************************************************************************
 * some_other_class.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file some_other_class.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_ENUMS_STATIC_SOME_OTHER_CLASS_H_
#define _FCS_EXAMPLES_ENUMS_STATIC_SOME_OTHER_CLASS_H_

#include "fcs/examples/enums_static/api_header.hpp"
#include <iostream>
#include <string>

namespace fcs {
namespace examples {
namespace enums_static {

  class FCS_EXAMPLES_ENUMS_STATIC_API some_other_class 
  {
  public:

    // Class enumerations
    //! An enum specific to SCOPED with name SCOPED_first
    enum SCOPED_first {
      SCOPED_first_0,
      SCOPED_first_1,
      SCOPED_first_2,
      SCOPED_first_3,
      SCOPED_first_4,
      SCOPED_first_5
    };

    // Number of entries in SCOPED_first
    enum { SCOPED_FIRST_NUMBER_ENTRIES = 6 };

    //! Returns char array correpsonding to value of SCOPED_first
    friend char const* to_c_str(SCOPED_first e);

    //! Assigns to value the entry associated with text in char array or "INVALID_SCOPED_FIRST" if not valid
    friend void from_c_str(char const* txt, SCOPED_first &value);

    friend inline std::ostream& operator<<(std::ostream &out, some_other_class::SCOPED_first e) {
      return out << to_c_str(e);
    }

    //! An enum specific to SCOPED with name SCOPED_second
    enum SCOPED_second {
      SCOPED_second_0,
      SCOPED_second_1,
      SCOPED_second_2,
      SCOPED_second_3,
      SCOPED_second_4,
      SCOPED_second_5,
      SCOPED_second_6
    };

    // Number of entries in SCOPED_second
    enum { SCOPED_SECOND_NUMBER_ENTRIES = 7 };

    //! Returns char array correpsonding to value of SCOPED_second
    friend char const* to_c_str(SCOPED_second e);

    //! Assigns to value the entry associated with text in char array or "INVALID_SCOPED_SECOND" if not valid
    friend void from_c_str(char const* txt, SCOPED_second &value);

    friend inline std::ostream& operator<<(std::ostream &out, some_other_class::SCOPED_second e) {
      return out << to_c_str(e);
    }

    //! An enum specific to SCOPED with name SCOPED_mask_first
    enum SCOPED_mask_first {
      SCOPED_masked_first_0 = 1,
      SCOPED_masked_first_1 = 2,
      SCOPED_masked_first_2 = 4,
      SCOPED_masked_first_3 = 8,
      SCOPED_masked_first_4 = 16,
      SCOPED_masked_first_5 = 32,
      SCOPED_masked_first_6 = 64
    };

    enum { SCOPED_MASK_FIRST_NUMBER_ENTRIES = 7 };

    friend inline bool test_scoped_mask_first(int value, SCOPED_mask_first e) {
      return (e & value) == e;
    }

    friend inline void set_scoped_mask_first(int &value, SCOPED_mask_first e) {
      value |= e;
    }

    friend inline void clear_scoped_mask_first(int &value, SCOPED_mask_first e) {
      value &= ~e;
    }

    //! Fills ostream with comma separated list of mask entries set in SCOPED_mask_first
    static
    void dump_scoped_mask_first(std::ostream &out, int e);

    //! An enum specific to SCOPED with name SCOPED_mask_second
    enum SCOPED_mask_second {
      SCOPED_masked_second_0 = 1,
      SCOPED_masked_second_1 = 2,
      SCOPED_masked_second_2 = 4,
      SCOPED_masked_second_3 = 8,
      SCOPED_masked_second_4 = 16,
      SCOPED_masked_second_5 = 32,
      SCOPED_masked_second_6 = 64
    };

    enum { SCOPED_MASK_SECOND_NUMBER_ENTRIES = 7 };

    friend inline bool test_scoped_mask_second(int value, SCOPED_mask_second e) {
      return (e & value) == e;
    }

    friend inline void set_scoped_mask_second(int &value, SCOPED_mask_second e) {
      value |= e;
    }

    friend inline void clear_scoped_mask_second(int &value, SCOPED_mask_second e) {
      value &= ~e;
    }

    //! Fills ostream with comma separated list of mask entries set in SCOPED_mask_second
    static
    void dump_scoped_mask_second(std::ostream &out, int e);

    //! An enum specific to SCOPED with name SCOPED_with_assignments
    enum SCOPED_with_assignments {
      SCOPED_wa_42 = 42,
      SCOPED_wa_77 = 77
    };

    // Number of entries in SCOPED_with_assignments
    enum { SCOPED_WITH_ASSIGNMENTS_NUMBER_ENTRIES = 2 };

    //! Returns char array correpsonding to value of SCOPED_with_assignments
    friend char const* to_c_str(SCOPED_with_assignments e);

    //! Assigns to value the entry associated with text in char array or "INVALID_SCOPED_WITH_ASSIGNMENTS" if not valid
    friend void from_c_str(char const* txt, SCOPED_with_assignments &value);

    friend inline std::ostream& operator<<(std::ostream &out, some_other_class::SCOPED_with_assignments e) {
      return out << to_c_str(e);
    }

    //! An enum specific to SCOPED with name SCOPED_shorten_long_name
    enum SCOPED_shorten_long_name {
      SCOPED_shorten_long_name_0,
      SCOPED_shorten_long_name_1,
      SCOPED_shorten_long_name_2,
      SCOPED_shorten_long_name_3,
      SCOPED_shorten_long_name_4,
      SCOPED_shorten_long_name_5
    };

    // Number of entries in SCOPED_shorten_long_name
    enum { SCOPED_SHORTEN_LONG_NAME_NUMBER_ENTRIES = 6 };

    //! Returns char array correpsonding to value of SCOPED_shorten_long_name
    friend char const* to_c_str(SCOPED_shorten_long_name e);

    //! Assigns to value the entry associated with text in char array or "INVALID_SCOPED_SHORTEN_LONG_NAME" if not valid
    friend void from_c_str(char const* txt, SCOPED_shorten_long_name &value);

    friend inline std::ostream& operator<<(std::ostream &out, some_other_class::SCOPED_shorten_long_name e) {
      return out << to_c_str(e);
    }

  
// custom <some_other_class public header section>
// end <some_other_class public header section>

  private:
    std::string s_;
  };

} // namespace enums_static
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_ENUMS_STATIC_SOME_OTHER_CLASS_H_
