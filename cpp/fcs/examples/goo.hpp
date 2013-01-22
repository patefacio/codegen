/******************************************************************************
 * goo.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file goo.hpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */
#ifndef _FCS_EXAMPLES_GOO_H_
#define _FCS_EXAMPLES_GOO_H_

#include "fcs/examples/apiheader.hpp"
#include "sample.hpp"
#include "fcs/utils/serialize/property_tree_utils.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/operators.hpp>
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <string>
#include <iso646.h>
#include <iosfwd>

// Forward class declarations
namespace boost {  class regex;  }
class my_special_class;


// custom <goo global header section>
// end <goo global header section>
namespace fcs {
namespace examples {

  //! Test performance of implementation of operator<
  class SAMPLE_API goo :
    public boost::totally_ordered< goo > 
  {
  public:

    // Class typedefs
    typedef boost::function< int (void)> BoostFunctorGoo;
    typedef std::shared_ptr< boost::filesystem::path > PathPtr;
    typedef std::vector< std::string > NameList;
    typedef std::vector< NameList > NameListList;
    typedef std::map< std::string, std::string > NameMap;
    typedef std::map< std::string, NameMap > NameMapMap;

    explicit goo(
      NameMapMap const& nameMapMap
    ) :
      s1_(),
      s2_(),
      s3_(5),
      s4_(),
      d5_(3.145),
      nameList_(),
      nameMap_(),
      nameMapMap_(nameMapMap),
      aPath_(),
      anotherPath_()
    {
    }

    goo() :
      s1_(),
      s2_(),
      s3_(5),
      s4_(),
      d5_(3.145),
      nameList_(),
      nameMap_(),
      nameMapMap_(),
      aPath_(),
      anotherPath_() 
    {
    }

    bool operator<(goo const& rhs) const {
        return
            ((s1_ != rhs.s1_)? s1_ < rhs.s1_ : (
            ((s2_ != rhs.s2_)? s2_ < rhs.s2_ : (
            ((s3_ != rhs.s3_)? s3_ < rhs.s3_ : (
            ((s4_ != rhs.s4_)? s4_ < rhs.s4_ : (
            ((d5_ != rhs.d5_)? d5_ < rhs.d5_ : (
            ((nameList_ != rhs.nameList_)? nameList_ < rhs.nameList_ : (
            ((nameMap_ != rhs.nameMap_)? nameMap_ < rhs.nameMap_ : (
            ((nameMapMap_ != rhs.nameMapMap_)? nameMapMap_ < rhs.nameMapMap_ : (
            ((aPath_ != rhs.aPath_)? aPath_ < rhs.aPath_ : (
            ((anotherPath_ != rhs.anotherPath_)? anotherPath_ < rhs.anotherPath_ : (false
            ))))))))))))))))))));
    }

    bool operator==(goo const& rhs) const {
        return
            ((this==&rhs) or (
            (s1_ == rhs.s1_) and
            (s2_ == rhs.s2_) and
            (s3_ == rhs.s3_) and
            (s4_ == rhs.s4_) and
            (d5_ == rhs.d5_) and
            (nameList_ == rhs.nameList_) and
            (nameMap_ == rhs.nameMap_) and
            (nameMapMap_ == rhs.nameMapMap_) and
            (aPath_ == rhs.aPath_) and
            (anotherPath_ == rhs.anotherPath_)));
    }

    SAMPLE_API friend std::ostream& operator<<(std::ostream& out, goo const& item);

    /// Support for writing members as property tree
    void to_stream_as_property_tree(std::ostream &out) const;

    /// Support for reading members previously written as property tree
    void from_stream_as_property_tree(std::istream &in);

    /// Support for writing members to a property tree
    void to_property_tree(std::string const& path, boost::property_tree::ptree &out) const;

    /// Support for reading members previously written from property tree
    void from_property_tree(std::string const& path, boost::property_tree::ptree const& in);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    std::string const& s1() const {
      return s1_;
    }

    void s1(std::string const& val) {
      s1_ = val;
    }

    std::string & s1() {
      return s1_;
    }

    std::string const& s2() const {
      return s2_;
    }

    void s2(std::string const& val) {
      s2_ = val;
    }

    std::string & s2() {
      return s2_;
    }

    int const& s3() const {
      return s3_;
    }

    void s3(int const& val) {
      s3_ = val;
    }

    int & s3() {
      return s3_;
    }

    std::string const& s4() const {
      return s4_;
    }

    void s4(std::string const& val) {
      s4_ = val;
    }

    std::string & s4() {
      return s4_;
    }

    double const& d5() const {
      return d5_;
    }

    void d5(double const& val) {
      d5_ = val;
    }

    double & d5() {
      return d5_;
    }

    NameList const& nameList() const {
      return nameList_;
    }

    void nameList(NameList const& val) {
      nameList_ = val;
    }

    NameList & nameList() {
      return nameList_;
    }

    NameMap const& nameMap() const {
      return nameMap_;
    }

    void nameMap(NameMap const& val) {
      nameMap_ = val;
    }

    NameMap & nameMap() {
      return nameMap_;
    }

    NameMapMap const& nameMapMap() const {
      return nameMapMap_;
    }

    void nameMapMap(NameMapMap const& val) {
      nameMapMap_ = val;
    }

    NameMapMap & nameMapMap() {
      return nameMapMap_;
    }

    PathPtr const& aPath() const;

    void aPath(PathPtr const& val);

    PathPtr & aPath();

    PathPtr const& anotherPath() const {
      return anotherPath_;
    }

    void anotherPath(PathPtr const& val) {
      anotherPath_ = val;
    }

    PathPtr & anotherPath() {
      return anotherPath_;
    }

  private:
    std::string s1_;
    std::string s2_;
    int s3_;
    std::string s4_;
    double d5_;
    NameList nameList_;
    NameMap nameMap_;
    NameMapMap nameMapMap_;
    PathPtr aPath_;
    PathPtr anotherPath_;
  };

} // namespace examples
} // namespace fcs

namespace fcs {
namespace utils {
namespace serialize {

  template<>
  inline 
  void put_to_property_tree(std::string const& path, boost::property_tree::ptree & tree, 
                            fcs::examples::goo const& item_to_put) {
    item_to_put.to_property_tree(path, tree);
  }

  template<>
  inline 
  void get_from_property_tree(std::string const& path, boost::property_tree::ptree const& tree, 
                              fcs::examples::goo & item_to_get) {
    item_to_get.from_property_tree(path, tree);
  }

}
}
}

#endif // _FCS_EXAMPLES_GOO_H_
