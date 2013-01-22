/******************************************************************************
 * sample.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file sample.cpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */

#include "fcs/examples/sample.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream>


// custom <sample pre-namespace custom>
// end <sample pre-namespace custom>

namespace fcs {
namespace examples {

  
// custom <sample namespace custom>
// end <sample namespace custom>


  /// Class static variable definitions
  std::string sample::sA_("");

  void sample::to_stream_as_property_tree(std::ostream &out) const {

  }

  void sample::from_stream_as_property_tree(std::istream &in) {

  }

  void sample::to_property_tree(std::string const& path, boost::property_tree::ptree & out) const {
    fcs::utils::serialize::put_to_property_tree(path + ".s1", out, s1_);
    fcs::utils::serialize::put_to_property_tree(path + ".s2", out, s2_);
    fcs::utils::serialize::put_to_property_tree(path + ".s3", out, s3_);
    fcs::utils::serialize::put_to_property_tree(path + ".s4", out, s4_);
    fcs::utils::serialize::put_to_property_tree(path + ".s5", out, s5_);
    fcs::utils::serialize::put_to_property_tree(path + ".s6", out, s6_);
    fcs::utils::serialize::put_to_property_tree(path + ".s7", out, s7_);
    fcs::utils::serialize::put_to_property_tree(path + ".s8", out, s8_);
    fcs::utils::serialize::put_to_property_tree(path + ".s9", out, s9_);
    fcs::utils::serialize::put_to_property_tree(path + ".i1", out, i1_);
    fcs::utils::serialize::put_to_property_tree(path + ".i2", out, i2_);
    fcs::utils::serialize::put_to_property_tree(path + ".i3", out, i3_);
    fcs::utils::serialize::put_to_property_tree(path + ".i4", out, i4_);
    fcs::utils::serialize::put_to_property_tree(path + ".i5", out, i5_);
    fcs::utils::serialize::put_to_property_tree(path + ".i6", out, i6_);
    fcs::utils::serialize::put_to_property_tree(path + ".i7", out, i7_);
    fcs::utils::serialize::put_to_property_tree(path + ".i8", out, i8_);
    fcs::utils::serialize::put_to_property_tree(path + ".i9", out, i9_);
    fcs::utils::serialize::put_to_property_tree(path + ".iA", out, iA_);
    fcs::utils::serialize::put_to_property_tree(path + ".nl", out, nl_);
    fcs::utils::serialize::put_to_property_tree(path + ".nm", out, nm_);
  }

  void sample::from_property_tree(std::string const& path, boost::property_tree::ptree const& in) {
    fcs::utils::serialize::get_from_property_tree(path + ".s1", in, s1_);
    fcs::utils::serialize::get_from_property_tree(path + ".s2", in, s2_);
    fcs::utils::serialize::get_from_property_tree(path + ".s3", in, s3_);
    fcs::utils::serialize::get_from_property_tree(path + ".s4", in, s4_);
    fcs::utils::serialize::get_from_property_tree(path + ".s5", in, s5_);
    fcs::utils::serialize::get_from_property_tree(path + ".s6", in, s6_);
    fcs::utils::serialize::get_from_property_tree(path + ".s7", in, s7_);
    fcs::utils::serialize::get_from_property_tree(path + ".s8", in, s8_);
    fcs::utils::serialize::get_from_property_tree(path + ".s9", in, s9_);
    fcs::utils::serialize::get_from_property_tree(path + ".i1", in, i1_);
    fcs::utils::serialize::get_from_property_tree(path + ".i2", in, i2_);
    fcs::utils::serialize::get_from_property_tree(path + ".i3", in, i3_);
    fcs::utils::serialize::get_from_property_tree(path + ".i4", in, i4_);
    fcs::utils::serialize::get_from_property_tree(path + ".i5", in, i5_);
    fcs::utils::serialize::get_from_property_tree(path + ".i6", in, i6_);
    fcs::utils::serialize::get_from_property_tree(path + ".i7", in, i7_);
    fcs::utils::serialize::get_from_property_tree(path + ".i8", in, i8_);
    fcs::utils::serialize::get_from_property_tree(path + ".i9", in, i9_);
    fcs::utils::serialize::get_from_property_tree(path + ".iA", in, iA_);
    fcs::utils::serialize::get_from_property_tree(path + ".nl", in, nl_);
    fcs::utils::serialize::get_from_property_tree(path + ".nm", in, nm_);
  }


  // Support for streaming non-static streamable members of sample
  SAMPLE_API std::ostream& operator<<(std::ostream& out, sample const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "sample:(" << &item << "):{";
    out << '\n' << indent << "  s1:" << item.s1_;
    out << '\n' << indent << "  s2:" << item.s2_;
    out << '\n' << indent << "  s3:" << item.s3_;
    out << '\n' << indent << "  s4:" << item.s4_;
    out << '\n' << indent << "  s5:" << item.s5_;
    out << '\n' << indent << "  s6:" << item.s6_;
    out << '\n' << indent << "  s7:" << item.s7_;
    out << '\n' << indent << "  s8:" << item.s8_;
    out << '\n' << indent << "  s9:" << item.s9_;
    out << '\n' << indent << "  i1:" << item.i1_;
    out << '\n' << indent << "  i2:" << item.i2_;
    out << '\n' << indent << "  i3:" << item.i3_;
    out << '\n' << indent << "  i4:" << item.i4_;
    out << '\n' << indent << "  i5:" << item.i5_;
    out << '\n' << indent << "  i6:" << item.i6_;
    out << '\n' << indent << "  i7:" << item.i7_;
    out << '\n' << indent << "  i8:" << item.i8_;
    out << '\n' << indent << "  i9:" << item.i9_;
    out << '\n' << indent << "  iA:" << item.iA_;
    out << '\n' << indent << "  nl:" << item.nl_;
    out << '\n' << indent << "  nm:" << item.nm_;
    out << indent << "}\n";
    return out;
  }

   char const* to_c_str(ApiHeaderFooEnum_Forward e) {
    char const* values[] = {
      "cls_fwd_za_xz",
      "cls_fwd_zb_xz"
    };
    size_t index(e);
    return ((index < APIHEADERFOOENUM_FORWARD_NUMBER_ENTRIES)? values[index] : "INVALID_APIHEADERFOOENUM_FORWARD");
  } 
   void dump_gooenum_forward(std::ostream &out, int e) {
    out << '(';
    if(test_gooenum_forward(e, cls_fwd_a_xyz)) {
      out << "cls_fwd_a_xyz,";
    }
    if(test_gooenum_forward(e, cls_fwd_b_xyz)) {
      out << "cls_fwd_b_xyz,";
    }
    if(test_gooenum_forward(e, cls_fwd_c)) {
      out << "cls_fwd_c,";
    }
    out << ')';
  } 
   void from_c_str(char const* txt, ZoopEnum &value) {
    if(0 == std::strcmp("a_xyz", txt)) {
      value = a_xyz;
      return;
    }
    if(0 == std::strcmp("b_xyz", txt)) {
      value = b_xyz;
      return;
    }
    if(0 == std::strcmp("c", txt)) {
      value = c;
      return;
    }
    std::string msg("No ZoopEnum value corresponding to: ");
    msg += txt;
    throw std::runtime_error(txt);
  }

   char const* to_c_str(ZoopEnum e) {
    char const* values[] = {
      "a_xyz",
      "b_xyz",
      "c"
    };
    size_t index(e);
    return ((index < ZOOPENUM_NUMBER_ENTRIES)? values[index] : "INVALID_ZOOPENUM");
  } 
  // Class enumerations

  SAMPLE_API char const* to_c_str(sample::ApiHeaderFooEnum_Cls e) {
    char const* values[] = {
      "cls_za_xz",
      "cls_zb_xz"
    };
    size_t index(e);
    return ((index < sample::APIHEADERFOOENUM_CLS_NUMBER_ENTRIES)? values[index] : "INVALID_APIHEADERFOOENUM_CLS");
  } 
  SAMPLE_API void sample::dump_gooenum_cls(std::ostream &out, int e) {
    out << '(';
    if(test_gooenum_cls(e, sample::cls_a_xyz)) {
      out << "cls_a_xyz,";
    }
    if(test_gooenum_cls(e, sample::cls_b_xyz)) {
      out << "cls_b_xyz,";
    }
    if(test_gooenum_cls(e, sample::cls_c)) {
      out << "cls_c,";
    }
    out << ')';
  } 
  SAMPLE_API void from_c_str(char const* txt, sample::ZoopEnum &value) {
    if(0 == std::strcmp("za_xyz", txt)) {
      value = sample::za_xyz;
      return;
    }
    if(0 == std::strcmp("zb_xyz", txt)) {
      value = sample::zb_xyz;
      return;
    }
    if(0 == std::strcmp("zc", txt)) {
      value = sample::zc;
      return;
    }
    std::string msg("No ZoopEnum value corresponding to: ");
    msg += txt;
    throw std::runtime_error(txt);
  }

  SAMPLE_API char const* to_c_str(sample::ZoopEnum e) {
    char const* values[] = {
      "za_xyz",
      "zb_xyz",
      "zc"
    };
    size_t index(e);
    return ((index < sample::ZOOPENUM_NUMBER_ENTRIES)? values[index] : "INVALID_ZOOPENUM");
  } 



} // namespace examples
} // namespace fcs


