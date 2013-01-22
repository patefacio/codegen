/******************************************************************************
 * SaMpLe.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file SaMpLe.hpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */
#ifndef _FCS_EXAMPLES_SAMPLE_H_
#define _FCS_EXAMPLES_SAMPLE_H_

#include "fcs/examples/apiheader.hpp"
#include "fcs/utils/serialize/property_tree_utils.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/operators.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/version.hpp>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <iosfwd>
#include <iso646.h>

namespace fcs {
namespace examples {


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

  enum ApiHeaderFooEnum_Forward {
    cls_fwd_za_xyz,
    cls_fwd_zb_xyz
  };

  // Number of entries in ApiHeaderFooEnum_Forward
  enum { APIHEADERFOOENUM_FORWARD_NUMBER_ENTRIES = 2 };

  //! Returns char array correpsonding to value of ApiHeaderFooEnum_Forward
  extern  char const* to_c_str(ApiHeaderFooEnum_Forward e);

  //! Assigns to value the entry associated with text in char array or "INVALID_APIHEADERFOOENUM_FORWARD" if not valid
  extern  void from_c_str(char const* txt, ApiHeaderFooEnum_Forward &value);

  inline std::ostream& operator<<(std::ostream &out, ApiHeaderFooEnum_Forward e) {
    return out << to_c_str(e);
  } 

  enum GooEnum_Forward {
    cls_fwd_a_xyz = 1,
    cls_fwd_b_xyz = 2,
    cls_fwd_c = 4
  };

  enum { GOOENUM_FORWARD_NUMBER_ENTRIES = 3 };

  inline bool test_gooenum_forward(int value, GooEnum_Forward e) {
    return (e & value) == e;
  }

  inline void set_gooenum_forward(int &value, GooEnum_Forward e) {
    value |= e;
  }

  inline void clear_gooenum_forward(int &value, GooEnum_Forward e) {
    value &= ~e;
  }

  //! Fills ostream with comma separated list of mask entries set in GooEnum_Forward
  extern
  void dump_gooenum_forward(std::ostream &out, int e); 

  //! Test performance of implementation of operator<
  class SAMPLE_API sample :
    public boost::totally_ordered< sample > 
  {
  public:

    // Class enumerations
    enum ApiHeaderFooEnum_Cls {
      cls_za_xyz,
      cls_zb_xyz
    };

    // Number of entries in ApiHeaderFooEnum_Cls
    enum { APIHEADERFOOENUM_CLS_NUMBER_ENTRIES = 2 };

    //! Returns char array correpsonding to value of ApiHeaderFooEnum_Cls
    friend char const* to_c_str(ApiHeaderFooEnum_Cls e);

    //! Assigns to value the entry associated with text in char array or "INVALID_APIHEADERFOOENUM_CLS" if not valid
    friend void from_c_str(char const* txt, ApiHeaderFooEnum_Cls &value);

    friend inline std::ostream& operator<<(std::ostream &out, sample::ApiHeaderFooEnum_Cls e) {
      return out << to_c_str(e);
    }

    enum GooEnum_Cls {
      cls_a_xyz = 1,
      cls_b_xyz = 2,
      cls_c = 4
    };

    enum { GOOENUM_CLS_NUMBER_ENTRIES = 3 };

    friend inline bool test_gooenum_cls(int value, GooEnum_Cls e) {
      return (e & value) == e;
    }

    friend inline void set_gooenum_cls(int &value, GooEnum_Cls e) {
      value |= e;
    }

    friend inline void clear_gooenum_cls(int &value, GooEnum_Cls e) {
      value &= ~e;
    }

    //! Fills ostream with comma separated list of mask entries set in GooEnum_Cls
    static
    void dump_gooenum_cls(std::ostream &out, int e);

    // Class typedefs
    typedef std::vector< std::string > NameList;
    typedef std::map< std::string, std::string > NameMap;

    sample() :
      s1_(),
      s2_(),
      s3_(),
      s4_(),
      s5_(),
      s6_(),
      s7_(),
      s8_(),
      s9_(),
      i1_(),
      i2_(),
      i3_(1234567),
      i4_(),
      i5_(),
      i6_(),
      i7_(),
      i8_(),
      i9_(),
      iA_(),
      nl_(),
      nm_() 
    {
    
// custom <sample ctor default init>
// end <sample ctor default init>
    }

    bool operator<(sample const& rhs) const {
        return
            ((s1_ != rhs.s1_)? s1_ < rhs.s1_ : (
            ((s2_ != rhs.s2_)? s2_ < rhs.s2_ : (
            ((s3_ != rhs.s3_)? s3_ < rhs.s3_ : (
            ((s4_ != rhs.s4_)? s4_ < rhs.s4_ : (
            ((s5_ != rhs.s5_)? s5_ < rhs.s5_ : (
            ((s6_ != rhs.s6_)? s6_ < rhs.s6_ : (
            ((s7_ != rhs.s7_)? s7_ < rhs.s7_ : (
            ((s8_ != rhs.s8_)? s8_ < rhs.s8_ : (
            ((s9_ != rhs.s9_)? s9_ < rhs.s9_ : (
            ((i1_ != rhs.i1_)? i1_ < rhs.i1_ : (
            ((i2_ != rhs.i2_)? i2_ < rhs.i2_ : (
            ((i3_ != rhs.i3_)? i3_ < rhs.i3_ : (
            ((i4_ != rhs.i4_)? i4_ < rhs.i4_ : (
            ((i5_ != rhs.i5_)? i5_ < rhs.i5_ : (
            ((i6_ != rhs.i6_)? i6_ < rhs.i6_ : (
            ((i7_ != rhs.i7_)? i7_ < rhs.i7_ : (
            ((i8_ != rhs.i8_)? i8_ < rhs.i8_ : (
            ((i9_ != rhs.i9_)? i9_ < rhs.i9_ : (
            ((iA_ != rhs.iA_)? iA_ < rhs.iA_ : (
            ((nl_ != rhs.nl_)? nl_ < rhs.nl_ : (
            ((nm_ != rhs.nm_)? nm_ < rhs.nm_ : (false
            ))))))))))))))))))))))))))))))))))))))))));
    }

    bool operator==(sample const& rhs) const {
        return
            ((this==&rhs) or (
            (s1_ == rhs.s1_) and
            (s2_ == rhs.s2_) and
            (s3_ == rhs.s3_) and
            (s4_ == rhs.s4_) and
            (s5_ == rhs.s5_) and
            (s6_ == rhs.s6_) and
            (s7_ == rhs.s7_) and
            (s8_ == rhs.s8_) and
            (s9_ == rhs.s9_) and
            (i1_ == rhs.i1_) and
            (i2_ == rhs.i2_) and
            (i3_ == rhs.i3_) and
            (i4_ == rhs.i4_) and
            (i5_ == rhs.i5_) and
            (i6_ == rhs.i6_) and
            (i7_ == rhs.i7_) and
            (i8_ == rhs.i8_) and
            (i9_ == rhs.i9_) and
            (iA_ == rhs.iA_) and
            (nl_ == rhs.nl_) and
            (nm_ == rhs.nm_)));
    }

    SAMPLE_API friend std::ostream& operator<<(std::ostream& out, sample const& item);

    /// Support for writing members as property tree
    void to_stream_as_property_tree(std::ostream &out) const;

    /// Support for reading members previously written as property tree
    void from_stream_as_property_tree(std::istream &in);

    /// Support for writing members to a property tree
    void to_property_tree(std::string const& path, boost::property_tree::ptree &out) const;

    /// Support for reading members previously written from property tree
    void from_property_tree(std::string const& path, boost::property_tree::ptree const& in);

    friend class boost::serialization::access;
    template< class Archive >
    void serialize(Archive & ar, const unsigned int version)
    {
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s1_, "sample::s1");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s1_), s1_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s2_, "sample::s2");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s2_), s2_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s3_, "sample::s3");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s3_), s3_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s4_, "sample::s4");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s4_), s4_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s5_, "sample::s5");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s5_), s5_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s6_, "sample::s6");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s6_), s6_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s7_, "sample::s7");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s7_), s7_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s8_, "sample::s8");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s8_), s8_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, s9_, "sample::s9");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(s9_), s9_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i1_, "sample::i1");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i1_), i1_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i2_, "sample::i2");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i2_), i2_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i3_, "sample::i3");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i3_), i3_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i4_, "sample::i4");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i4_), i4_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i5_, "sample::i5");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i5_), i5_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i6_, "sample::i6");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i6_), i6_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i7_, "sample::i7");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i7_), i7_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i8_, "sample::i8");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i8_), i8_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, i9_, "sample::i9");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(i9_), i9_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, iA_, "sample::iA");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(iA_), iA_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, nl_, "sample::nl");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(nl_), nl_);
      // TODO: LOGGING_BOOST_SERIALIZATION_NVP(ar, nm_, "sample::nm");
      ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(nm_), nm_);

    }

    template < typename T >
    void serializeTo(T &out_archive) const {
      out_archive << boost::serialization::make_nvp("sample", *this);
    }

    template < typename T >
    void serializeFrom(T &in_archive) {
      in_archive >> boost::serialization::make_nvp("sample", *this);
    }

    //! serialize instance as xml to an std::ostream 
    void serializeToXml(std::ostream &out) const {
      boost::archive::xml_oarchive out_archive(out);
      serializeTo(out_archive);
    }

    //! serialize instance as xml to named file 
    void serializeToXmlFile(std::string const& fileName) const {
      std::ofstream ofs(fileName.c_str());
      serializeToXml(ofs);
      ofs.close();
    }

    //! serialize instance in as xml from an std::istream
    void serializeFromXml(std::istream &in) {
      boost::archive::xml_iarchive in_archive(in);
      serializeFrom(in_archive);
    }

    //! serialize instance as xml from named file
    void serializeFromXmlFile(std::string const& fileName) {
      std::ifstream ifs(fileName.c_str());
      serializeFromXml(ifs);
      ifs.close();
    }

    //! serialize instance as text to an std::ostream 
    void serializeToText(std::ostream &out) const {
      boost::archive::text_oarchive out_archive(out);
      serializeTo(out_archive);
    }

    //! serialize instance as text to named file 
    void serializeToTextFile(std::string const& fileName) const {
      std::ofstream ofs(fileName.c_str());
      serializeToText(ofs);
      ofs.close();
    }

    //! serialize instance in as text from an std::istream
    void serializeFromText(std::istream &in) {
      boost::archive::text_iarchive in_archive(in);
      serializeFrom(in_archive);
    }

    //! serialize instance as text from named file
    void serializeFromTextFile(std::string const& fileName) {
      std::ifstream ifs(fileName.c_str());
      serializeFromText(ifs);
      ifs.close();
    }

    //! serialize instance as binary to an std::ostream 
    void serializeToBinary(std::ostream &out) const {
      boost::archive::binary_oarchive out_archive(out);
      serializeTo(out_archive);
    }

    //! serialize instance as binary to named file 
    void serializeToBinaryFile(std::string const& fileName) const {
      std::ofstream ofs(fileName.c_str());
      serializeToBinary(ofs);
      ofs.close();
    }

    //! serialize instance in as binary from an std::istream
    void serializeFromBinary(std::istream &in) {
      boost::archive::binary_iarchive in_archive(in);
      serializeFrom(in_archive);
    }

    //! serialize instance as binary from named file
    void serializeFromBinaryFile(std::string const& fileName) {
      std::ifstream ifs(fileName.c_str());
      serializeFromBinary(ifs);
      ifs.close();
    }

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

    std::string const& s3() const {
      return s3_;
    }

    void s3(std::string const& val) {
      s3_ = val;
    }

    std::string & s3() {
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

    std::string const& s5() const {
      return s5_;
    }

    void s5(std::string const& val) {
      s5_ = val;
    }

    std::string & s5() {
      return s5_;
    }

    std::string const& s6() const {
      return s6_;
    }

    void s6(std::string const& val) {
      s6_ = val;
    }

    std::string & s6() {
      return s6_;
    }

    std::string const& s7() const {
      return s7_;
    }

    void s7(std::string const& val) {
      s7_ = val;
    }

    std::string & s7() {
      return s7_;
    }

    std::string const& s8() const {
      return s8_;
    }

    void s8(std::string const& val) {
      s8_ = val;
    }

    std::string & s8() {
      return s8_;
    }

    std::string const& s9() const {
      return s9_;
    }

    void s9(std::string const& val) {
      s9_ = val;
    }

    std::string & s9() {
      return s9_;
    }

    int const& i1() const {
      return i1_;
    }

    void i1(int const& val) {
      i1_ = val;
    }

    int & i1() {
      return i1_;
    }

    int const& i2() const {
      return i2_;
    }

    void i2(int const& val) {
      i2_ = val;
    }

    int & i2() {
      return i2_;
    }

    int const& i3() const {
      return i3_;
    }

    void i3(int const& val) {
      i3_ = val;
    }

    int & i3() {
      return i3_;
    }

    int const& i4() const {
      return i4_;
    }

    void i4(int const& val) {
      i4_ = val;
    }

    int & i4() {
      return i4_;
    }

    NameList const& nl() const {
      return nl_;
    }

    void nl(NameList const& val) {
      nl_ = val;
    }

    NameList & nl() {
      return nl_;
    }

    NameMap const& nm() const {
      return nm_;
    }

    void nm(NameMap const& val) {
      nm_ = val;
    }

    NameMap & nm() {
      return nm_;
    }

  private:
    std::string s1_;
    std::string s2_;
    std::string s3_;
    std::string s4_;
    std::string s5_;
    std::string s6_;
    std::string s7_;
    std::string s8_;
    std::string s9_;
    static std::string sA_;
    int i1_;
    int i2_;
    int i3_;
    int i4_;
    int i5_;
    int i6_;
    int i7_;
    int i8_;
    int i9_;
    int iA_;
    NameList nl_;
    NameMap nm_;
  };

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

} // namespace examples
} // namespace fcs

namespace fcs {
namespace utils {
namespace serialize {

  template<>
  inline 
  void put_to_property_tree(std::string const& path, boost::property_tree::ptree & tree, 
                            fcs::examples::sample const& item_to_put) {
    item_to_put.to_property_tree(path, tree);
  }

  template<>
  inline 
  void get_from_property_tree(std::string const& path, boost::property_tree::ptree const& tree, 
                              fcs::examples::sample & item_to_get) {
    item_to_get.from_property_tree(path, tree);
  }

}
}
}

#endif // _FCS_EXAMPLES_SAMPLE_H_
