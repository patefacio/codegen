/******************************************************************************
 * goo.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file goo.cpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */

#include "fcs/examples/goo.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <iostream>


// custom <goo pre-namespace custom>
// end <goo pre-namespace custom>

namespace fcs {
namespace examples {

  
// custom <goo namespace custom>
// end <goo namespace custom>


  void goo::to_stream_as_property_tree(std::ostream &out) const {

  }

  void goo::from_stream_as_property_tree(std::istream &in) {

  }

  void goo::to_property_tree(std::string const& path, boost::property_tree::ptree & out) const {
    fcs::utils::serialize::put_to_property_tree(path + ".s1", out, s1_);
    fcs::utils::serialize::put_to_property_tree(path + ".s2", out, s2_);
    fcs::utils::serialize::put_to_property_tree(path + ".s3", out, s3_);
    fcs::utils::serialize::put_to_property_tree(path + ".s4", out, s4_);
    fcs::utils::serialize::put_to_property_tree(path + ".d5", out, d5_);
    fcs::utils::serialize::put_to_property_tree(path + ".nameList", out, nameList_);
    fcs::utils::serialize::put_to_property_tree(path + ".nameMap", out, nameMap_);
    fcs::utils::serialize::put_to_property_tree(path + ".nameMapMap", out, nameMapMap_);
  }

  void goo::from_property_tree(std::string const& path, boost::property_tree::ptree const& in) {
    fcs::utils::serialize::get_from_property_tree(path + ".s1", in, s1_);
    fcs::utils::serialize::get_from_property_tree(path + ".s2", in, s2_);
    fcs::utils::serialize::get_from_property_tree(path + ".s3", in, s3_);
    fcs::utils::serialize::get_from_property_tree(path + ".s4", in, s4_);
    fcs::utils::serialize::get_from_property_tree(path + ".d5", in, d5_);
    fcs::utils::serialize::get_from_property_tree(path + ".nameList", in, nameList_);
    fcs::utils::serialize::get_from_property_tree(path + ".nameMap", in, nameMap_);
    fcs::utils::serialize::get_from_property_tree(path + ".nameMapMap", in, nameMapMap_);
  }


  goo::PathPtr const& goo::aPath() const {
    return aPath_;
  }
  void goo::aPath(PathPtr const& val) {
    aPath_ = val;
  }
  goo::PathPtr & goo::aPath() {
    return aPath_;
  }
  // Support for streaming non-static streamable members of goo
  SAMPLE_API std::ostream& operator<<(std::ostream& out, goo const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "goo:(" << &item << "):{";
    out << '\n' << indent << "  s1:" << item.s1_;
    out << '\n' << indent << "  s2:" << item.s2_;
    out << '\n' << indent << "  s3:" << item.s3_;
    out << '\n' << indent << "  s4:" << item.s4_;
    out << '\n' << indent << "  d5:" << item.d5_;
    out << '\n' << indent << "  nameList:" << item.nameList_;
    out << '\n' << indent << "  nameMap:" << item.nameMap_;
    out << '\n' << indent << "  nameMapMap:" << item.nameMapMap_;
    out << '\n' << indent << "  aPath:";
    if(item.aPath_) { 
      out << *item.aPath_;
    } else { 
      out << "(null)";
    } 
    out << '\n' << indent << "  anotherPath:(" << item.anotherPath_ << ") ";
    if(item.anotherPath_) { 
      out << *item.anotherPath_;
    } else { 
      out << "(null)";
    } 
    out << indent << "}\n";
    return out;
  }


} // namespace examples
} // namespace fcs


