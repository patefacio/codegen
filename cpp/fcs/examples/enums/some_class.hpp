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
#ifndef _FCS_EXAMPLES_ENUMS_SOME_CLASS_H_
#define _FCS_EXAMPLES_ENUMS_SOME_CLASS_H_

#include "fcs/examples/enums/api_header.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

namespace fcs {
namespace examples {
namespace enums {

  //! An enum specific to FORWARD with name FORWARD_first
  enum FORWARD_first {
    FORWARD_first_0,
    FORWARD_first_1,
    FORWARD_first_2,
    FORWARD_first_3,
    FORWARD_first_4,
    FORWARD_first_5
  };

  // Number of entries in FORWARD_first
  enum { FORWARD_FIRST_NUMBER_ENTRIES = 6 };

  inline char const* to_c_str(FORWARD_first e) {
    char const* values[] = {
      "FORWARD_first_0",
      "FORWARD_first_1",
      "FORWARD_first_2",
      "FORWARD_first_3",
      "FORWARD_first_4",
      "FORWARD_first_5"
    };
    size_t index(e);
    return ((index < FORWARD_FIRST_NUMBER_ENTRIES)? values[index] : "INVALID_FORWARD_FIRST");
  }

  inline std::ostream& operator<<(std::ostream &out, FORWARD_first e) {
    return out << to_c_str(e);
  } 

  //! An enum specific to FORWARD with name FORWARD_second
  enum FORWARD_second {
    FORWARD_second_0,
    FORWARD_second_1,
    FORWARD_second_2,
    FORWARD_second_3,
    FORWARD_second_4,
    FORWARD_second_5,
    FORWARD_second_6
  };

  // Number of entries in FORWARD_second
  enum { FORWARD_SECOND_NUMBER_ENTRIES = 7 };

  inline void from_c_str(char const* txt, FORWARD_second &value) {
    if(0 == std::strcmp("FORWARD_second_0", txt)) {
      value = FORWARD_second_0;
      return;
    }
    if(0 == std::strcmp("FORWARD_second_1", txt)) {
      value = FORWARD_second_1;
      return;
    }
    if(0 == std::strcmp("FORWARD_second_2", txt)) {
      value = FORWARD_second_2;
      return;
    }
    if(0 == std::strcmp("FORWARD_second_3", txt)) {
      value = FORWARD_second_3;
      return;
    }
    if(0 == std::strcmp("FORWARD_second_4", txt)) {
      value = FORWARD_second_4;
      return;
    }
    if(0 == std::strcmp("FORWARD_second_5", txt)) {
      value = FORWARD_second_5;
      return;
    }
    if(0 == std::strcmp("FORWARD_second_6", txt)) {
      value = FORWARD_second_6;
      return;
    }
    std::string msg("No FORWARD_second value corresponding to: ");
    msg += txt;
    throw std::runtime_error(txt);
  }

  inline char const* to_c_str(FORWARD_second e) {
    char const* values[] = {
      "FORWARD_second_0",
      "FORWARD_second_1",
      "FORWARD_second_2",
      "FORWARD_second_3",
      "FORWARD_second_4",
      "FORWARD_second_5",
      "FORWARD_second_6"
    };
    size_t index(e);
    return ((index < FORWARD_SECOND_NUMBER_ENTRIES)? values[index] : "INVALID_FORWARD_SECOND");
  }

  inline std::ostream& operator<<(std::ostream &out, FORWARD_second e) {
    return out << to_c_str(e);
  } 

  //! An enum specific to FORWARD with name FORWARD_mask_first
  enum FORWARD_mask_first {
    FORWARD_masked_first_0 = 1,
    FORWARD_masked_first_1 = 2,
    FORWARD_masked_first_2 = 4,
    FORWARD_masked_first_3 = 8,
    FORWARD_masked_first_4 = 16,
    FORWARD_masked_first_5 = 32,
    FORWARD_masked_first_6 = 64
  };

  enum { FORWARD_MASK_FIRST_NUMBER_ENTRIES = 7 };

  inline bool test_forward_mask_first(int value, FORWARD_mask_first e) {
    return (e & value) == e;
  }

  inline void set_forward_mask_first(int &value, FORWARD_mask_first e) {
    value |= e;
  }

  inline void clear_forward_mask_first(int &value, FORWARD_mask_first e) {
    value &= ~e;
  }

  inline void dump_forward_mask_first(std::ostream &out, int e) {
    out << '(';
    if(test_forward_mask_first(e, FORWARD_masked_first_0)) {
      out << "FORWARD_masked_first_0,";
    }
    if(test_forward_mask_first(e, FORWARD_masked_first_1)) {
      out << "FORWARD_masked_first_1,";
    }
    if(test_forward_mask_first(e, FORWARD_masked_first_2)) {
      out << "FORWARD_masked_first_2,";
    }
    if(test_forward_mask_first(e, FORWARD_masked_first_3)) {
      out << "FORWARD_masked_first_3,";
    }
    if(test_forward_mask_first(e, FORWARD_masked_first_4)) {
      out << "FORWARD_masked_first_4,";
    }
    if(test_forward_mask_first(e, FORWARD_masked_first_5)) {
      out << "FORWARD_masked_first_5,";
    }
    if(test_forward_mask_first(e, FORWARD_masked_first_6)) {
      out << "FORWARD_masked_first_6,";
    }
    out << ')';
  } 

  //! An enum specific to FORWARD with name FORWARD_mask_second
  enum FORWARD_mask_second {
    FORWARD_masked_second_0 = 1,
    FORWARD_masked_second_1 = 2,
    FORWARD_masked_second_2 = 4,
    FORWARD_masked_second_3 = 8,
    FORWARD_masked_second_4 = 16,
    FORWARD_masked_second_5 = 32,
    FORWARD_masked_second_6 = 64
  };

  enum { FORWARD_MASK_SECOND_NUMBER_ENTRIES = 7 };

  inline bool test_forward_mask_second(int value, FORWARD_mask_second e) {
    return (e & value) == e;
  }

  inline void set_forward_mask_second(int &value, FORWARD_mask_second e) {
    value |= e;
  }

  inline void clear_forward_mask_second(int &value, FORWARD_mask_second e) {
    value &= ~e;
  }

  inline void dump_forward_mask_second(std::ostream &out, int e) {
    out << '(';
    if(test_forward_mask_second(e, FORWARD_masked_second_0)) {
      out << "FORWARD_masked_second_0,";
    }
    if(test_forward_mask_second(e, FORWARD_masked_second_1)) {
      out << "FORWARD_masked_second_1,";
    }
    if(test_forward_mask_second(e, FORWARD_masked_second_2)) {
      out << "FORWARD_masked_second_2,";
    }
    if(test_forward_mask_second(e, FORWARD_masked_second_3)) {
      out << "FORWARD_masked_second_3,";
    }
    if(test_forward_mask_second(e, FORWARD_masked_second_4)) {
      out << "FORWARD_masked_second_4,";
    }
    if(test_forward_mask_second(e, FORWARD_masked_second_5)) {
      out << "FORWARD_masked_second_5,";
    }
    if(test_forward_mask_second(e, FORWARD_masked_second_6)) {
      out << "FORWARD_masked_second_6,";
    }
    out << ')';
  } 

  //! An enum specific to FORWARD with name FORWARD_with_assignments
  enum FORWARD_with_assignments {
    FORWARD_wa_42 = 42,
    FORWARD_wa_77 = 77
  };

  // Number of entries in FORWARD_with_assignments
  enum { FORWARD_WITH_ASSIGNMENTS_NUMBER_ENTRIES = 2 };

  inline void from_c_str(char const* txt, FORWARD_with_assignments &value) {
    if(0 == std::strcmp("FORWARD_wa_42", txt)) {
      value = FORWARD_wa_42;
      return;
    }
    if(0 == std::strcmp("FORWARD_wa_77", txt)) {
      value = FORWARD_wa_77;
      return;
    }
    std::string msg("No FORWARD_with_assignments value corresponding to: ");
    msg += txt;
    throw std::runtime_error(txt);
  }

  inline char const* to_c_str(FORWARD_with_assignments e) {
    switch(e) {
      case FORWARD_wa_42: return "FORWARD_wa_42";
      case FORWARD_wa_77: return "FORWARD_wa_77";
    }
    return "INVALID_FORWARD_WITH_ASSIGNMENTS";
  }

  inline std::ostream& operator<<(std::ostream &out, FORWARD_with_assignments e) {
    return out << to_c_str(e);
  } 

  //! An enum specific to FORWARD with name FORWARD_shorten_long_name
  enum FORWARD_shorten_long_name {
    FORWARD_shorten_long_name_0,
    FORWARD_shorten_long_name_1,
    FORWARD_shorten_long_name_2,
    FORWARD_shorten_long_name_3,
    FORWARD_shorten_long_name_4,
    FORWARD_shorten_long_name_5
  };

  // Number of entries in FORWARD_shorten_long_name
  enum { FORWARD_SHORTEN_LONG_NAME_NUMBER_ENTRIES = 6 };

  inline char const* to_c_str(FORWARD_shorten_long_name e) {
    char const* values[] = {
      "FORWARD_sln_0",
      "FORWARD_sln_1",
      "FORWARD_sln_2",
      "FORWARD_sln_3",
      "FORWARD_sln_4",
      "FORWARD_sln_5"
    };
    size_t index(e);
    return ((index < FORWARD_SHORTEN_LONG_NAME_NUMBER_ENTRIES)? values[index] : "INVALID_FORWARD_SHORTEN_LONG_NAME");
  }

  inline std::ostream& operator<<(std::ostream &out, FORWARD_shorten_long_name e) {
    return out << to_c_str(e);
  } 

  //! Dohh - clearly self explanatory
  enum { FORWARD_ANSWER_OF_UNIVERSE = 42 }; 

  class some_class 
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

    friend inline char const* to_c_str(some_class::SCOPED_first e) {
      char const* values[] = {
        "SCOPED_first_0",
        "SCOPED_first_1",
        "SCOPED_first_2",
        "SCOPED_first_3",
        "SCOPED_first_4",
        "SCOPED_first_5"
      };
      size_t index(e);
      return ((index < SCOPED_FIRST_NUMBER_ENTRIES)? values[index] : "INVALID_SCOPED_FIRST");
    }

    friend inline std::ostream& operator<<(std::ostream &out, some_class::SCOPED_first e) {
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

    friend inline void from_c_str(char const* txt, SCOPED_second &value) {
      if(0 == std::strcmp("SCOPED_second_0", txt)) {
        value = SCOPED_second_0;
        return;
      }
      if(0 == std::strcmp("SCOPED_second_1", txt)) {
        value = SCOPED_second_1;
        return;
      }
      if(0 == std::strcmp("SCOPED_second_2", txt)) {
        value = SCOPED_second_2;
        return;
      }
      if(0 == std::strcmp("SCOPED_second_3", txt)) {
        value = SCOPED_second_3;
        return;
      }
      if(0 == std::strcmp("SCOPED_second_4", txt)) {
        value = SCOPED_second_4;
        return;
      }
      if(0 == std::strcmp("SCOPED_second_5", txt)) {
        value = SCOPED_second_5;
        return;
      }
      if(0 == std::strcmp("SCOPED_second_6", txt)) {
        value = SCOPED_second_6;
        return;
      }
      std::string msg("No SCOPED_second value corresponding to: ");
      msg += txt;
      throw std::runtime_error(txt);
    }

    friend inline char const* to_c_str(some_class::SCOPED_second e) {
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
      return ((index < SCOPED_SECOND_NUMBER_ENTRIES)? values[index] : "INVALID_SCOPED_SECOND");
    }

    friend inline std::ostream& operator<<(std::ostream &out, some_class::SCOPED_second e) {
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

    static inline void dump_scoped_mask_first(std::ostream &out, int e) {
      out << '(';
      if(test_scoped_mask_first(e, SCOPED_masked_first_0)) {
        out << "SCOPED_masked_first_0,";
      }
      if(test_scoped_mask_first(e, SCOPED_masked_first_1)) {
        out << "SCOPED_masked_first_1,";
      }
      if(test_scoped_mask_first(e, SCOPED_masked_first_2)) {
        out << "SCOPED_masked_first_2,";
      }
      if(test_scoped_mask_first(e, SCOPED_masked_first_3)) {
        out << "SCOPED_masked_first_3,";
      }
      if(test_scoped_mask_first(e, SCOPED_masked_first_4)) {
        out << "SCOPED_masked_first_4,";
      }
      if(test_scoped_mask_first(e, SCOPED_masked_first_5)) {
        out << "SCOPED_masked_first_5,";
      }
      if(test_scoped_mask_first(e, SCOPED_masked_first_6)) {
        out << "SCOPED_masked_first_6,";
      }
      out << ')';
    }

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

    static inline void dump_scoped_mask_second(std::ostream &out, int e) {
      out << '(';
      if(test_scoped_mask_second(e, SCOPED_masked_second_0)) {
        out << "SCOPED_masked_second_0,";
      }
      if(test_scoped_mask_second(e, SCOPED_masked_second_1)) {
        out << "SCOPED_masked_second_1,";
      }
      if(test_scoped_mask_second(e, SCOPED_masked_second_2)) {
        out << "SCOPED_masked_second_2,";
      }
      if(test_scoped_mask_second(e, SCOPED_masked_second_3)) {
        out << "SCOPED_masked_second_3,";
      }
      if(test_scoped_mask_second(e, SCOPED_masked_second_4)) {
        out << "SCOPED_masked_second_4,";
      }
      if(test_scoped_mask_second(e, SCOPED_masked_second_5)) {
        out << "SCOPED_masked_second_5,";
      }
      if(test_scoped_mask_second(e, SCOPED_masked_second_6)) {
        out << "SCOPED_masked_second_6,";
      }
      out << ')';
    }

    //! An enum specific to SCOPED with name SCOPED_with_assignments
    enum SCOPED_with_assignments {
      SCOPED_wa_42 = 42,
      SCOPED_wa_77 = 77
    };

    // Number of entries in SCOPED_with_assignments
    enum { SCOPED_WITH_ASSIGNMENTS_NUMBER_ENTRIES = 2 };

    friend inline void from_c_str(char const* txt, SCOPED_with_assignments &value) {
      if(0 == std::strcmp("SCOPED_wa_42", txt)) {
        value = SCOPED_wa_42;
        return;
      }
      if(0 == std::strcmp("SCOPED_wa_77", txt)) {
        value = SCOPED_wa_77;
        return;
      }
      std::string msg("No SCOPED_with_assignments value corresponding to: ");
      msg += txt;
      throw std::runtime_error(txt);
    }

    friend inline char const* to_c_str(some_class::SCOPED_with_assignments e) {
      switch(e) {
        case SCOPED_wa_42: return "SCOPED_wa_42";
        case SCOPED_wa_77: return "SCOPED_wa_77";
      }
      return "INVALID_SCOPED_WITH_ASSIGNMENTS";
    }

    friend inline std::ostream& operator<<(std::ostream &out, some_class::SCOPED_with_assignments e) {
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

    friend inline char const* to_c_str(some_class::SCOPED_shorten_long_name e) {
      char const* values[] = {
        "SCOPED_sln_0",
        "SCOPED_sln_1",
        "SCOPED_sln_2",
        "SCOPED_sln_3",
        "SCOPED_sln_4",
        "SCOPED_sln_5"
      };
      size_t index(e);
      return ((index < SCOPED_SHORTEN_LONG_NAME_NUMBER_ENTRIES)? values[index] : "INVALID_SCOPED_SHORTEN_LONG_NAME");
    }

    friend inline std::ostream& operator<<(std::ostream &out, some_class::SCOPED_shorten_long_name e) {
      return out << to_c_str(e);
    }

    //! Dohh - clearly self explanatory
    enum { ANSWER_OF_UNIVERSE = 42 };

  
// custom <some_class public header section>

    void foo() {
      int x(0);
      set_scoped_mask_second(x, SCOPED_masked_second_6);
      test_scoped_mask_second(x, SCOPED_masked_second_6);
    }

// end <some_class public header section>

  private:
    std::string s_;
  };

} // namespace enums
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_ENUMS_SOME_CLASS_H_
