/******************************************************************************
 * foo.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file foo.cpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */

#include "fcs/examples/foo.hpp"

["// Class exposed in the header for user consumption\ntypedef fcs::examples::foo User_exposed_type_t;\n\n\n// Hidden class containing the data fields and actual implementation\ntemplate <  > \nstruct pimpl< User_exposed_type_t >::implementation \n{\n\n  explicit implementation(\n    User_exposed_type_t::NameMapMap const& nameMapMap\n  ) :\n    s1_(),\n    s2_(),\n    s3_(5),\n    s4_(),\n    d5_(3.145),\n    nameList_(),\n    nameMap_(),\n    nameMapMap_(nameMapMap),\n    aPath_(),\n    anotherPath_()\n  {\n  // custom <implementation ctor member init>\n  // end <implementation ctor member init>\n  }\n\n  implementation() :\n    s1_(),\n    s2_(),\n    s3_(5),\n    s4_(),\n    d5_(3.145),\n    nameList_(),\n    nameMap_(),\n    nameMapMap_(),\n    aPath_(),\n    anotherPath_() \n  {\n  // custom <implementation ctor default init>\n  // end <implementation ctor default init>\n  }\n\n// custom < public header section>\n// end < public header section>\n\n  std::string s1_;\n  std::string s2_;\n  int s3_;\n  std::string s4_;\n  double d5_;\n  User_exposed_type_t::NameList nameList_;\n  User_exposed_type_t::NameMap nameMap_;\n  User_exposed_type_t::NameMapMap nameMapMap_;\n  User_exposed_type_t::PathPtr aPath_;\n  User_exposed_type_t::PathPtr anotherPath_;\n};\n\n"]


// custom <foo pre-namespace custom>
// end <foo pre-namespace custom>

namespace fcs {
namespace examples {

  
// custom <foo namespace custom>
// end <foo namespace custom>


  // Member init ctor
  foo::foo(
    NameMapMap const& nameMapMap
  ) :
    pimpl< foo >::pointer_semantics(nameMapMap)
  {
  
// custom <User_exposed_type_t ctor member init>
// end <User_exposed_type_t ctor member init>
  }

  // Default ctor
  foo::foo()
  {
  
// custom <User_exposed_type_t ctor default init>
// end <User_exposed_type_t ctor default init>
  }

  std::string const& foo::s1() const {
    return (*this)->s1_;
  }
  std::string const& foo::s2() const {
    return (*this)->s2_;
  }
  int const& foo::s3() const {
    return (*this)->s3_;
  }
  std::string const& foo::s4() const {
    return (*this)->s4_;
  }
  double const& foo::d5() const {
    return (*this)->d5_;
  }
  foo::NameList const& foo::nameList() const {
    return (*this)->nameList_;
  }
  foo::NameMap const& foo::nameMap() const {
    return (*this)->nameMap_;
  }
  foo::NameMapMap const& foo::nameMapMap() const {
    return (*this)->nameMapMap_;
  }
  foo::PathPtr const& foo::aPath() const {
    return (*this)->aPath_;
  }
  foo::PathPtr const& foo::anotherPath() const {
    return (*this)->anotherPath_;
  }
  void foo::s1(std::string const& val) {
    (*this)->s1_ = val;
  }
  void foo::s2(std::string const& val) {
    (*this)->s2_ = val;
  }
  void foo::s3(int const& val) {
    (*this)->s3_ = val;
  }
  void foo::s4(std::string const& val) {
    (*this)->s4_ = val;
  }
  void foo::d5(double const& val) {
    (*this)->d5_ = val;
  }
  void foo::nameList(NameList const& val) {
    (*this)->nameList_ = val;
  }
  void foo::nameMap(NameMap const& val) {
    (*this)->nameMap_ = val;
  }
  void foo::nameMapMap(NameMapMap const& val) {
    (*this)->nameMapMap_ = val;
  }
  void foo::aPath(PathPtr const& val) {
    (*this)->aPath_ = val;
  }
  void foo::anotherPath(PathPtr const& val) {
    (*this)->anotherPath_ = val;
  }
  std::string & foo::s1() {
    return (*this)->s1_;
  }
  std::string & foo::s2() {
    return (*this)->s2_;
  }
  int & foo::s3() {
    return (*this)->s3_;
  }
  std::string & foo::s4() {
    return (*this)->s4_;
  }
  double & foo::d5() {
    return (*this)->d5_;
  }
  foo::NameList & foo::nameList() {
    return (*this)->nameList_;
  }
  foo::NameMap & foo::nameMap() {
    return (*this)->nameMap_;
  }
  foo::NameMapMap & foo::nameMapMap() {
    return (*this)->nameMapMap_;
  }
  foo::PathPtr & foo::aPath() {
    return (*this)->aPath_;
  }
  foo::PathPtr & foo::anotherPath() {
    return (*this)->anotherPath_;
  }


} // namespace examples
} // namespace fcs


