/******************************************************************************
 * a.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file a.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_GROUP_A_H_
#define _FCS_EXAMPLES_GROUP_A_H_

#include "fcs/utils/block_indenter.hpp"
#include <boost/cstdint.hpp>
#include <string>
#include <iostream>

namespace fcs {
namespace examples {
namespace group {

  class A 
  {
  public:

    // Public static consts
    static int const ONE_RING_ID = 0;
    explicit A(
      std::string const& a1 = "a1",
      std::string const& a2 = "a2",
      std::string const& a3 = "a3",
      boost::int64_t total_chars_observed = 0,
      double sum_log_do_good = 0,
      double sum_rand_log_do_good = 0,
      double sum_log_do_bad = 0,
      double sum_rand_log_do_bad = 0
    ) :
      a1_(a1),
      a2_(a2),
      a3_(a3),
      total_chars_observed_(total_chars_observed),
      sum_log_do_good_(sum_log_do_good),
      sum_rand_log_do_good_(sum_rand_log_do_good),
      sum_log_do_bad_(sum_log_do_bad),
      sum_rand_log_do_bad_(sum_rand_log_do_bad)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, A const& item);

    //! Observes the data
    void 
    observe(int i, char const * s);

    //! Does good
    void 
    do_good(int i);

    //! Does bad
    void 
    do_bad(int i);
  private:
    std::string a1_;
    std::string a2_;
    std::string a3_;
    boost::int64_t total_chars_observed_;
    double sum_log_do_good_;
    double sum_rand_log_do_good_;
    double sum_log_do_bad_;
    double sum_rand_log_do_bad_;
  };

  // Support for streaming non-static streamable members of A
  inline
  std::ostream& operator<<(std::ostream& out, A const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "A:(" << &item << "):{";
    out << '\n' << indent << "  a1:" << item.a1_;
    out << '\n' << indent << "  a2:" << item.a2_;
    out << '\n' << indent << "  a3:" << item.a3_;
    out << '\n' << indent << "  total_chars_observed:" << item.total_chars_observed_;
    out << '\n' << indent << "  sum_log_do_good:" << item.sum_log_do_good_;
    out << '\n' << indent << "  sum_rand_log_do_good:" << item.sum_rand_log_do_good_;
    out << '\n' << indent << "  sum_log_do_bad:" << item.sum_log_do_bad_;
    out << '\n' << indent << "  sum_rand_log_do_bad:" << item.sum_rand_log_do_bad_;
    out << indent << "}\n";
    return out;
  } 

} // namespace group
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_GROUP_A_H_
