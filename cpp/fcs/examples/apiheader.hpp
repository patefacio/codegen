/******************************************************************************
 * apiheader.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file apiheader.hpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */
#ifndef _FCS_EXAMPLES_APIHEADER_H_
#define _FCS_EXAMPLES_APIHEADER_H_

#include <boost/lambda/lambda.hpp>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <map>
#include <set>
#include <memory>
#include <iosfwd>

/////// Standard windows approach for exposing symbols in a dll
#if defined(SAMPLE_API_STATIC_LIB) || defined(GLOBAL_STATIC_LINKAGE) || !defined(_MSC_VER_)
#define SAMPLE_API
#else
#ifdef SAMPLE_API_EXPORTS
#define SAMPLE_API __declspec(dllexport)
#else
#define SAMPLE_API __declspec(dllimport)
#endif
#endif

namespace fcs {
namespace examples {

  // Library enumerations
  enum ApiHeaderFooEnum {
    za_xyz,
    zb_xyz,
    zb_pdq
  };

  // Number of entries in ApiHeaderFooEnum
  enum { APIHEADERFOOENUM_NUMBER_ENTRIES = 3 };

  //! Returns char array correpsonding to value of ApiHeaderFooEnum
  extern SAMPLE_API char const* to_c_str(ApiHeaderFooEnum e);

  //! Assigns to value the entry associated with text in char array or "INVALID_APIHEADERFOOENUM" if not valid
  extern SAMPLE_API void from_c_str(char const* txt, ApiHeaderFooEnum &value);

  inline std::ostream& operator<<(std::ostream &out, ApiHeaderFooEnum e) {
    return out << to_c_str(e);
  }

  enum GooEnum {
    ga_xyz = 1,
    gb_xyz = 2,
    gc = 4
  };

  enum { GOOENUM_NUMBER_ENTRIES = 3 };

  inline bool test_gooenum(int value, GooEnum e) {
    return (e & value) == e;
  }

  inline void set_gooenum(int &value, GooEnum e) {
    value |= e;
  }

  inline void clear_gooenum(int &value, GooEnum e) {
    value &= ~e;
  }

  //! Fills ostream with comma separated list of mask entries set in GooEnum
  extern
  void dump_gooenum(std::ostream &out, int e);

  // Library typedefs
  typedef boost::function< int (void) > BoostFunctorGoo;
  typedef std::shared_ptr< boost::filesystem::path > PathPtr;

} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_APIHEADER_H_
