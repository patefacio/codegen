/******************************************************************************
 * all_types.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file all_types.hpp
 *
 * \brief Has all types
 * 
 */
#ifndef _FCS_CODEGEN_COVERAGE_ALL_TYPES_H_
#define _FCS_CODEGEN_COVERAGE_ALL_TYPES_H_

#include "fcs/utils/fixed_size_char_array.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <boost/cstdint.hpp>
#include <limits>
#include <iostream>

namespace fcs {
namespace codegen {
namespace coverage {

  class All_types_g1_data_set_specifier;
  class All_types_g2_data_set_specifier;
  class All_types_data_set_specifier;

  //! Has all types
  class All_types 
  {
  public:

    All_types() :
      int_m_(std::numeric_limits<int>::max()),
      double_m_(std::numeric_limits<double>::max()),
      long_m_(std::numeric_limits<long>::max()),
      long_double_m_(std::numeric_limits<long double>::max()),
      long_int_m_(std::numeric_limits<long int>::max()),
      long_long_m_(std::numeric_limits<long long>::max()),
      unsigned_int_m_(std::numeric_limits<unsigned int>::max()),
      unsigned_long_m_(std::numeric_limits<unsigned long>::max()),
      unsigned_long_long_m_(std::numeric_limits<unsigned long long>::max()),
      boost_int16_t_m_(std::numeric_limits<boost::int16_t>::max()),
      boost_int32_t_m_(std::numeric_limits<boost::int32_t>::max()),
      boost_int64_t_m_(std::numeric_limits<boost::int64_t>::max()),
      boost_uint16_t_m_(std::numeric_limits<boost::uint16_t>::max()),
      boost_uint32_t_m_(std::numeric_limits<boost::uint32_t>::max()),
      boost_uint64_t_m_(std::numeric_limits<boost::uint64_t>::max()),
      sample_string_() 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, All_types const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    int int_m() const {
      return int_m_;
    }

    void int_m(int val) {
      int_m_ = val;
    }

    double double_m() const {
      return double_m_;
    }

    void double_m(double val) {
      double_m_ = val;
    }

    long long_m() const {
      return long_m_;
    }

    void long_m(long val) {
      long_m_ = val;
    }

    long double long_double_m() const {
      return long_double_m_;
    }

    void long_double_m(long double val) {
      long_double_m_ = val;
    }

    long int long_int_m() const {
      return long_int_m_;
    }

    void long_int_m(long int val) {
      long_int_m_ = val;
    }

    long long long_long_m() const {
      return long_long_m_;
    }

    void long_long_m(long long val) {
      long_long_m_ = val;
    }

    unsigned int unsigned_int_m() const {
      return unsigned_int_m_;
    }

    void unsigned_int_m(unsigned int val) {
      unsigned_int_m_ = val;
    }

    unsigned long unsigned_long_m() const {
      return unsigned_long_m_;
    }

    void unsigned_long_m(unsigned long val) {
      unsigned_long_m_ = val;
    }

    unsigned long long unsigned_long_long_m() const {
      return unsigned_long_long_m_;
    }

    void unsigned_long_long_m(unsigned long long val) {
      unsigned_long_long_m_ = val;
    }

    boost::int16_t boost_int16_t_m() const {
      return boost_int16_t_m_;
    }

    void boost_int16_t_m(boost::int16_t val) {
      boost_int16_t_m_ = val;
    }

    boost::int32_t boost_int32_t_m() const {
      return boost_int32_t_m_;
    }

    void boost_int32_t_m(boost::int32_t val) {
      boost_int32_t_m_ = val;
    }

    boost::int64_t boost_int64_t_m() const {
      return boost_int64_t_m_;
    }

    void boost_int64_t_m(boost::int64_t val) {
      boost_int64_t_m_ = val;
    }

    boost::uint16_t boost_uint16_t_m() const {
      return boost_uint16_t_m_;
    }

    void boost_uint16_t_m(boost::uint16_t val) {
      boost_uint16_t_m_ = val;
    }

    boost::uint32_t boost_uint32_t_m() const {
      return boost_uint32_t_m_;
    }

    void boost_uint32_t_m(boost::uint32_t val) {
      boost_uint32_t_m_ = val;
    }

    boost::uint64_t boost_uint64_t_m() const {
      return boost_uint64_t_m_;
    }

    void boost_uint64_t_m(boost::uint64_t val) {
      boost_uint64_t_m_ = val;
    }

    fcs::utils::Fixed_size_char_array< 32 > const& sample_string() const {
      return sample_string_;
    }

    void sample_string(fcs::utils::Fixed_size_char_array< 32 > const& val) {
      sample_string_ = val;
    }

    fcs::utils::Fixed_size_char_array< 32 > & sample_string() {
      return sample_string_;
    }

  
// custom <All_types public header section>
// end <All_types public header section>

    static void check_sizes() {
       size_t actual(sizeof(All_types));
       size_t tally(0);
       tally += sizeof(int);
       tally += sizeof(double);
       tally += sizeof(long);
       tally += sizeof(long double);
       tally += sizeof(long int);
       tally += sizeof(long long);
       tally += sizeof(unsigned int);
       tally += sizeof(unsigned long);
       tally += sizeof(unsigned long long);
       tally += sizeof(boost::int16_t);
       tally += sizeof(boost::int32_t);
       tally += sizeof(boost::int64_t);
       tally += sizeof(boost::uint16_t);
       tally += sizeof(boost::uint32_t);
       tally += sizeof(boost::uint64_t);
       tally += sizeof(fcs::utils::Fixed_size_char_array< 32 >);
       std::cout << "Total:" << actual << " versus tally: " << tally << std::endl;
    }
  private:
    int int_m_;
    double double_m_;
    long long_m_;
    long double long_double_m_;
    long int long_int_m_;
    long long long_long_m_;
    unsigned int unsigned_int_m_;
    unsigned long unsigned_long_m_;
    unsigned long long unsigned_long_long_m_;
    boost::int16_t boost_int16_t_m_;
    boost::int32_t boost_int32_t_m_;
    boost::int64_t boost_int64_t_m_;
    boost::uint16_t boost_uint16_t_m_;
    boost::uint32_t boost_uint32_t_m_;
    boost::uint64_t boost_uint64_t_m_;
    fcs::utils::Fixed_size_char_array< 32 > sample_string_;

    friend class fcs::codegen::coverage::All_types_g1_data_set_specifier;
    typedef std::shared_ptr< All_types_g1_data_set_specifier > All_types_g1_data_set_specifier_ptr;

    friend class fcs::codegen::coverage::All_types_g2_data_set_specifier;
    typedef std::shared_ptr< All_types_g2_data_set_specifier > All_types_g2_data_set_specifier_ptr;

    friend class fcs::codegen::coverage::All_types_data_set_specifier;
    typedef std::shared_ptr< All_types_data_set_specifier > All_types_data_set_specifier_ptr;

  };

  // Support for streaming non-static streamable members of All_types
  inline
  std::ostream& operator<<(std::ostream& out, All_types const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "All_types:(" << &item << "):{";
    out << '\n' << indent << "  int_m:" << item.int_m_;
    out << '\n' << indent << "  double_m:" << item.double_m_;
    out << '\n' << indent << "  long_m:" << item.long_m_;
    out << '\n' << indent << "  long_double_m:" << item.long_double_m_;
    out << '\n' << indent << "  long_int_m:" << item.long_int_m_;
    out << '\n' << indent << "  long_long_m:" << item.long_long_m_;
    out << '\n' << indent << "  unsigned_int_m:" << item.unsigned_int_m_;
    out << '\n' << indent << "  unsigned_long_m:" << item.unsigned_long_m_;
    out << '\n' << indent << "  unsigned_long_long_m:" << item.unsigned_long_long_m_;
    out << '\n' << indent << "  boost_int16_t_m:" << item.boost_int16_t_m_;
    out << '\n' << indent << "  boost_int32_t_m:" << item.boost_int32_t_m_;
    out << '\n' << indent << "  boost_int64_t_m:" << item.boost_int64_t_m_;
    out << '\n' << indent << "  boost_uint16_t_m:" << item.boost_uint16_t_m_;
    out << '\n' << indent << "  boost_uint32_t_m:" << item.boost_uint32_t_m_;
    out << '\n' << indent << "  boost_uint64_t_m:" << item.boost_uint64_t_m_;
    out << '\n' << indent << "  sample_string:" << item.sample_string_;
    out << indent << "}\n";
    return out;
  } 

} // namespace coverage
} // namespace codegen
} // namespace fcs
#endif // _FCS_CODEGEN_COVERAGE_ALL_TYPES_H_
