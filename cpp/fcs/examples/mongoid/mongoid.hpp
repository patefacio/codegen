/******************************************************************************
 * mongoid.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file mongoid.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_MONGOID_MONGOID_H_
#define _FCS_EXAMPLES_MONGOID_MONGOID_H_

#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/mongoid/mongoid.hpp"
#include "fcs/examples/mongoid/sample_included.hpp"
#include <boost/operators.hpp>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdint>
#include <iso646.h>

namespace fcs {
namespace examples {
namespace mongoid {

  // Library enumerations
  enum MyChoices {
    a,
    b,
    c
  };

  // Number of entries in MyChoices
  enum { MYCHOICES_NUMBER_ENTRIES = 3 };

  inline void from_c_str(char const* txt, MyChoices &value) {
    if(0 == std::strcmp("a", txt)) {
      value = a;
      return;
    }
    if(0 == std::strcmp("b", txt)) {
      value = b;
      return;
    }
    if(0 == std::strcmp("c", txt)) {
      value = c;
      return;
    }
    std::string msg("No MyChoices value corresponding to: ");
    msg += txt;
    throw std::runtime_error(txt);
  }

  inline char const* to_c_str(MyChoices e) {
    char const* values[] = {
      "a",
      "b",
      "c"
    };
    size_t index(e);
    return ((index < MYCHOICES_NUMBER_ENTRIES)? values[index] : "INVALID_MYCHOICES");
  }

  inline std::ostream& operator<<(std::ostream &out, MyChoices e) {
    return out << to_c_str(e);
  }


  struct Address :
    public boost::totally_ordered< Address > 
  {

    Address(
      std::int32_t number,
      std::string const& street,
      std::string const& zipcode,
      std::string const& state,
      MyChoices myChoice
    ) :
      number_(number),
      street_(street),
      zipcode_(zipcode),
      state_(state),
      myChoice_(myChoice)
    {
    }

    Address() :
      number_(std::int32_t()),
      street_(std::string()),
      zipcode_(std::string()),
      state_(std::string()),
      myChoice_() 
    {
    }

    bool operator<(Address const& rhs) const {
        return
            ((number_ != rhs.number_)? number_ < rhs.number_ : (
            ((street_ != rhs.street_)? street_ < rhs.street_ : (
            ((zipcode_ != rhs.zipcode_)? zipcode_ < rhs.zipcode_ : (
            ((state_ != rhs.state_)? state_ < rhs.state_ : (
            ((myChoice_ != rhs.myChoice_)? myChoice_ < rhs.myChoice_ : (false
            ))))))))));
    }

    bool operator==(Address const& rhs) const {
        return
            ((this==&rhs) or (
            (number_ == rhs.number_) and
            (street_ == rhs.street_) and
            (zipcode_ == rhs.zipcode_) and
            (state_ == rhs.state_) and
            (myChoice_ == rhs.myChoice_)));
    }

    friend std::ostream& operator<<(std::ostream& out, Address const& item);

    bson::bo to_bson(bool exclude_oid = false) const {
      bson::bob builder;
      to_bson(builder, exclude_oid);
      return builder.obj();
    }

    // Support for serializing non-static members of Address to bson
    void to_bson(bson::bob &builder, bool exclude_oid = false) const {

      builder << "number" << number_;
      builder << "street" << street_;
      builder << "zipcode" << zipcode_;
      builder << "state" << state_;
      builder << "myChoice" << to_c_str(myChoice_);
    }

    std::string to_bson_text(bool exclude_oid = false) const {
      const int pretty(1);
      std::string result(to_bson(exclude_oid).jsonString(mongo::Strict, pretty));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Obj to_bson_text() : ", result.c_str());
      return result;
    }

    // Support for serializing non-static members of Address to bson
    void from_bson(bson::bo const& bson_object) {
      bson::be bson_element;

      try {
        bson_element = bson_object.getField("number");
        if(bson_element.ok()) {
          bson_element.Val(number_);
        }

        bson_element = bson_object.getField("street");
        if(bson_element.ok()) {
          bson_element.Val(street_);
        }

        bson_element = bson_object.getField("zipcode");
        if(bson_element.ok()) {
          bson_element.Val(zipcode_);
        }

        bson_element = bson_object.getField("state");
        if(bson_element.ok()) {
          bson_element.Val(state_);
        }

        bson_element = bson_object.getField("myChoice");
        if(bson_element.ok()) {
          std::string val;
          bson_element.Val(val);
          from_c_str(val.c_str(), myChoice_);
        }

      } catch(std::exception const& excp) {
        pantheios::log(PANTHEIOS_SEV_ERROR,
                       "Failed to parse Address with exception: ",
                       excp.what(),
                       "\nlast read bson_element:\n",
                       bson_element.jsonString(mongo::Strict, 1).c_str());
        throw;
      }
    }

    void from_bson_text(std::string const& text) {
      mongo::BSONObj obj(mongo::fromjson(text));
      from_bson(obj);
    }
    std::int32_t number_;
    std::string street_;
    std::string zipcode_;
    std::string state_;
    MyChoices myChoice_;
  };

  // Support for streaming non-static streamable members of Address
  inline
  std::ostream& operator<<(std::ostream& out, Address const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Address:(" << &item << "):{";
    out << '\n' << indent << "  number:" << item.number_;
    out << '\n' << indent << "  street:" << item.street_;
    out << '\n' << indent << "  zipcode:" << item.zipcode_;
    out << '\n' << indent << "  state:" << item.state_;
    out << '\n' << indent << "  myChoice:" << item.myChoice_;
    out << indent << "}\n";
    return out;
  } 


  struct Phone :
    public boost::totally_ordered< Phone > 
  {

    explicit Phone(
      std::string const& number
    ) :
      number_(number)
    {
    }

    Phone() :
      number_(std::string()) 
    {
    }

    bool operator<(Phone const& rhs) const {
        return
            ((number_ != rhs.number_)? number_ < rhs.number_ : (false
            ));
    }

    bool operator==(Phone const& rhs) const {
        return
            ((this==&rhs) or (
            (number_ == rhs.number_)));
    }

    friend std::ostream& operator<<(std::ostream& out, Phone const& item);

    bson::bo to_bson(bool exclude_oid = false) const {
      bson::bob builder;
      to_bson(builder, exclude_oid);
      return builder.obj();
    }

    // Support for serializing non-static members of Phone to bson
    void to_bson(bson::bob &builder, bool exclude_oid = false) const {

      builder << "number" << number_;
    }

    std::string to_bson_text(bool exclude_oid = false) const {
      const int pretty(1);
      std::string result(to_bson(exclude_oid).jsonString(mongo::Strict, pretty));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Obj to_bson_text() : ", result.c_str());
      return result;
    }

    // Support for serializing non-static members of Phone to bson
    void from_bson(bson::bo const& bson_object) {
      bson::be bson_element;

      try {
        bson_element = bson_object.getField("number");
        if(bson_element.ok()) {
          bson_element.Val(number_);
        }

      } catch(std::exception const& excp) {
        pantheios::log(PANTHEIOS_SEV_ERROR,
                       "Failed to parse Phone with exception: ",
                       excp.what(),
                       "\nlast read bson_element:\n",
                       bson_element.jsonString(mongo::Strict, 1).c_str());
        throw;
      }
    }

    void from_bson_text(std::string const& text) {
      mongo::BSONObj obj(mongo::fromjson(text));
      from_bson(obj);
    }
    std::string number_;
  };

  // Support for streaming non-static streamable members of Phone
  inline
  std::ostream& operator<<(std::ostream& out, Phone const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Phone:(" << &item << "):{";
    out << '\n' << indent << "  number:" << item.number_;
    out << indent << "}\n";
    return out;
  } 


  // Forward typedefs
  typedef std::vector< Phone > Phone_list_t;
  typedef std::vector< Address > Address_list_t;
  typedef std::vector< std::string > String_list_t;
  typedef std::vector< double > Float_list_t;
  typedef std::vector< std::int32_t > Integer_list_t;
  typedef std::vector< bool > Bool_list_t;

  struct Person :
    public boost::totally_ordered< Person > 
  {

    Person(
      ::fcs::mongoid::Bson_int64_t age,
      std::string const& name,
      double weight,
      SampleIncluded const& sample,
      Phone_list_t const& phones,
      Address_list_t const& addresses,
      String_list_t const& aliases,
      Float_list_t const& alphas,
      Integer_list_t const& lengths,
      Phone const& emergency_phone,
      Bool_list_t const& straight_a_list,
      mongo::OID const& oid = mongo::OID()
    ) :
      age_(age),
      name_(name),
      weight_(weight),
      sample_(sample),
      phones_(phones),
      addresses_(addresses),
      aliases_(aliases),
      alphas_(alphas),
      lengths_(lengths),
      emergency_phone_(emergency_phone),
      straight_a_list_(straight_a_list),
      oid_(oid),
      version_(3)
    {
    }

    Person() :
      age_(::fcs::mongoid::Bson_int64_t()),
      name_(std::string()),
      weight_(double()),
      sample_(),
      phones_(),
      addresses_(),
      aliases_(),
      alphas_(),
      lengths_(),
      emergency_phone_(),
      straight_a_list_(),
      oid_(mongo::OID()),
      version_(3) 
    {
    }

    bool operator<(Person const& rhs) const {
        return
            ((age_ != rhs.age_)? age_ < rhs.age_ : (
            ((name_ != rhs.name_)? name_ < rhs.name_ : (
            ((weight_ != rhs.weight_)? weight_ < rhs.weight_ : (
            ((sample_ != rhs.sample_)? sample_ < rhs.sample_ : (
            ((phones_ != rhs.phones_)? phones_ < rhs.phones_ : (
            ((addresses_ != rhs.addresses_)? addresses_ < rhs.addresses_ : (
            ((aliases_ != rhs.aliases_)? aliases_ < rhs.aliases_ : (
            ((alphas_ != rhs.alphas_)? alphas_ < rhs.alphas_ : (
            ((lengths_ != rhs.lengths_)? lengths_ < rhs.lengths_ : (
            ((emergency_phone_ != rhs.emergency_phone_)? emergency_phone_ < rhs.emergency_phone_ : (
            ((straight_a_list_ != rhs.straight_a_list_)? straight_a_list_ < rhs.straight_a_list_ : (
            ((version_ != rhs.version_)? version_ < rhs.version_ : (false
            ))))))))))))))))))))))));
    }

    bool operator==(Person const& rhs) const {
        return
            ((this==&rhs) or (
            (age_ == rhs.age_) and
            (name_ == rhs.name_) and
            (weight_ == rhs.weight_) and
            (sample_ == rhs.sample_) and
            (phones_ == rhs.phones_) and
            (addresses_ == rhs.addresses_) and
            (aliases_ == rhs.aliases_) and
            (alphas_ == rhs.alphas_) and
            (lengths_ == rhs.lengths_) and
            (emergency_phone_ == rhs.emergency_phone_) and
            (straight_a_list_ == rhs.straight_a_list_) and
            (version_ == rhs.version_)));
    }

    friend std::ostream& operator<<(std::ostream& out, Person const& item);

    bson::bo to_bson(bool exclude_oid = false) const {
      bson::bob builder;
      to_bson(builder, exclude_oid);
      return builder.obj();
    }

    // Support for serializing non-static members of Person to bson
    void to_bson(bson::bob &builder, bool exclude_oid = false) const {

      if(!exclude_oid) {
        if(!oid_.isSet()) {
          oid_.init();
        }
        builder << "_id" << oid_;
      }

      builder << "version" << version_;
      builder << "age" << age_;
      builder << "name" << name_;
      builder << "weight" << weight_;
      {
        bson::bob element_builder;
        sample_.to_bson(element_builder);
        builder.append("sample", element_builder.obj());
      }
      {
        Phone_list_t::const_iterator it(phones_.begin());
        Phone_list_t::const_iterator end(phones_.end());
        mongo::BSONArrayBuilder array_builder(builder.subarrayStart("phones"));
        for(; it != end; ++it) {
          bson::bob element_builder;
          it->to_bson(element_builder);
          array_builder.append(element_builder.obj());
        }
        array_builder.done();
      }
      {
        Address_list_t::const_iterator it(addresses_.begin());
        Address_list_t::const_iterator end(addresses_.end());
        mongo::BSONArrayBuilder array_builder(builder.subarrayStart("addresses"));
        for(; it != end; ++it) {
          bson::bob element_builder;
          it->to_bson(element_builder);
          array_builder.append(element_builder.obj());
        }
        array_builder.done();
      }
      {
        String_list_t::const_iterator it(aliases_.begin());
        String_list_t::const_iterator end(aliases_.end());
        mongo::BSONArrayBuilder array_builder(builder.subarrayStart("aliases"));
        for(; it != end; ++it) {
          array_builder.append(*it);
        }
        array_builder.done();
      }
      {
        Float_list_t::const_iterator it(alphas_.begin());
        Float_list_t::const_iterator end(alphas_.end());
        mongo::BSONArrayBuilder array_builder(builder.subarrayStart("alphas"));
        for(; it != end; ++it) {
          array_builder.append(*it);
        }
        array_builder.done();
      }
      {
        Integer_list_t::const_iterator it(lengths_.begin());
        Integer_list_t::const_iterator end(lengths_.end());
        mongo::BSONArrayBuilder array_builder(builder.subarrayStart("lengths"));
        for(; it != end; ++it) {
          array_builder.append(*it);
        }
        array_builder.done();
      }
      {
        bson::bob element_builder;
        emergency_phone_.to_bson(element_builder);
        builder.append("emergency_phone", element_builder.obj());
      }
      {
        Bool_list_t::const_iterator it(straight_a_list_.begin());
        Bool_list_t::const_iterator end(straight_a_list_.end());
        mongo::BSONArrayBuilder array_builder(builder.subarrayStart("straight_a_list"));
        for(; it != end; ++it) {
          array_builder.append(*it);
        }
        array_builder.done();
      }
      builder << "version" << version_;
    }

    std::string to_bson_text(bool exclude_oid = false) const {
      const int pretty(1);
      std::string result(to_bson(exclude_oid).jsonString(mongo::Strict, pretty));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Obj to_bson_text() : ", result.c_str());
      return result;
    }

    // Support for serializing non-static members of Person to bson
    void from_bson(bson::bo const& bson_object) {
      bson::be bson_element;

      try {
        bson_element = bson_object.getField("_id");
        if(bson_element.ok()) {
          bson_element.Val(oid_);
        }

        bson_element = bson_object.getField("version");
        if(bson_element.ok()) {
          bson_element.Val(version_);
        }

        bson_element = bson_object.getField("age");
        if(bson_element.ok()) {
          age_ = bson_element.numberLong();
        }

        bson_element = bson_object.getField("name");
        if(bson_element.ok()) {
          bson_element.Val(name_);
        }

        if(version_ >= 2) {
          bson_element = bson_object.getField("weight");
          if(bson_element.ok()) {
            weight_ = bson_element.numberDouble();
          }
        }

        bson_element = bson_object.getField("sample");
        {
          sample_.from_bson(bson_element.Obj());
        }

        {
          phones_.clear();
          bson_element = bson_object.getField("phones");
          std::vector< mongo::BSONElement > elements(bson_element.Array());
          std::vector< mongo::BSONElement >::const_iterator it(elements.begin());
          std::vector< mongo::BSONElement >::const_iterator end(elements.end());
          for(; it != end; ++it) {
            Phone_list_t::value_type element;
            element.from_bson(it->Obj());
            phones_.push_back(element);
          }
        }

        {
          addresses_.clear();
          bson_element = bson_object.getField("addresses");
          std::vector< mongo::BSONElement > elements(bson_element.Array());
          std::vector< mongo::BSONElement >::const_iterator it(elements.begin());
          std::vector< mongo::BSONElement >::const_iterator end(elements.end());
          for(; it != end; ++it) {
            Address_list_t::value_type element;
            element.from_bson(it->Obj());
            addresses_.push_back(element);
          }
        }

        if(version_ >= 3) {
          {
            aliases_.clear();
            bson_element = bson_object.getField("aliases");
            std::vector< mongo::BSONElement > elements(bson_element.Array());
            std::vector< mongo::BSONElement >::const_iterator it(elements.begin());
            std::vector< mongo::BSONElement >::const_iterator end(elements.end());
            for(; it != end; ++it) {
              aliases_.push_back(it->String());
            }
          }
        }

        {
          alphas_.clear();
          bson_element = bson_object.getField("alphas");
          std::vector< mongo::BSONElement > elements(bson_element.Array());
          std::vector< mongo::BSONElement >::const_iterator it(elements.begin());
          std::vector< mongo::BSONElement >::const_iterator end(elements.end());
          for(; it != end; ++it) {
            alphas_.push_back(it->numberDouble());
          }
        }

        {
          lengths_.clear();
          bson_element = bson_object.getField("lengths");
          std::vector< mongo::BSONElement > elements(bson_element.Array());
          std::vector< mongo::BSONElement >::const_iterator it(elements.begin());
          std::vector< mongo::BSONElement >::const_iterator end(elements.end());
          for(; it != end; ++it) {
            lengths_.push_back(it->Int());
          }
        }

        if(version_ >= 1) {
          bson_element = bson_object.getField("emergency_phone");
          {
            emergency_phone_.from_bson(bson_element.Obj());
          }
        }

        {
          straight_a_list_.clear();
          bson_element = bson_object.getField("straight_a_list");
          std::vector< mongo::BSONElement > elements(bson_element.Array());
          std::vector< mongo::BSONElement >::const_iterator it(elements.begin());
          std::vector< mongo::BSONElement >::const_iterator end(elements.end());
          for(; it != end; ++it) {
            straight_a_list_.push_back(it->Bool());
          }
        }

        bson_element = bson_object.getField("version");
        if(bson_element.ok()) {
          bson_element.Val(version_);
        }

      } catch(std::exception const& excp) {
        pantheios::log(PANTHEIOS_SEV_ERROR,
                       "Failed to parse Person with exception: ",
                       excp.what(),
                       "\nlast read bson_element:\n",
                       bson_element.jsonString(mongo::Strict, 1).c_str());
        throw;
      }
    }

    void from_bson_text(std::string const& text) {
      mongo::BSONObj obj(mongo::fromjson(text));
      from_bson(obj);
    }
    ::fcs::mongoid::Bson_int64_t age_;
    std::string name_;
    double weight_;
    SampleIncluded sample_;
    Phone_list_t phones_;
    Address_list_t addresses_;
    String_list_t aliases_;
    Float_list_t alphas_;
    Integer_list_t lengths_;
    Phone emergency_phone_;
    Bool_list_t straight_a_list_;
    mutable mongo::OID oid_;
    std::int32_t version_;
  };

  // Support for streaming non-static streamable members of Person
  inline
  std::ostream& operator<<(std::ostream& out, Person const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Person:(" << &item << "):{";
    out << '\n' << indent << "  age:" << item.age_;
    out << '\n' << indent << "  name:" << item.name_;
    out << '\n' << indent << "  weight:" << item.weight_;
    out << '\n' << indent << "  sample:" << item.sample_;
    out << '\n' << indent << "  phones:" << item.phones_;
    out << '\n' << indent << "  addresses:" << item.addresses_;
    out << '\n' << indent << "  aliases:" << item.aliases_;
    out << '\n' << indent << "  alphas:" << item.alphas_;
    out << '\n' << indent << "  lengths:" << item.lengths_;
    out << '\n' << indent << "  emergency_phone:" << item.emergency_phone_;
    out << '\n' << indent << "  straight_a_list:" << item.straight_a_list_;
    out << '\n' << indent << "  oid:" << item.oid_;
    out << '\n' << indent << "  version:" << item.version_;
    out << indent << "}\n";
    return out;
  } 


  // Forward typedefs
  typedef std::vector< Person > Person_list_t;

  struct Team :
    public boost::totally_ordered< Team > 
  {

    explicit Team(
      Person_list_t const& members
    ) :
      members_(members)
    {
    }

    Team() :
      members_() 
    {
    }

    bool operator<(Team const& rhs) const {
        return
            ((members_ != rhs.members_)? members_ < rhs.members_ : (false
            ));
    }

    bool operator==(Team const& rhs) const {
        return
            ((this==&rhs) or (
            (members_ == rhs.members_)));
    }

    friend std::ostream& operator<<(std::ostream& out, Team const& item);

    bson::bo to_bson(bool exclude_oid = false) const {
      bson::bob builder;
      to_bson(builder, exclude_oid);
      return builder.obj();
    }

    // Support for serializing non-static members of Team to bson
    void to_bson(bson::bob &builder, bool exclude_oid = false) const {

      {
        Person_list_t::const_iterator it(members_.begin());
        Person_list_t::const_iterator end(members_.end());
        mongo::BSONArrayBuilder array_builder(builder.subarrayStart("members"));
        for(; it != end; ++it) {
          bson::bob element_builder;
          it->to_bson(element_builder);
          array_builder.append(element_builder.obj());
        }
        array_builder.done();
      }
    }

    std::string to_bson_text(bool exclude_oid = false) const {
      const int pretty(1);
      std::string result(to_bson(exclude_oid).jsonString(mongo::Strict, pretty));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Obj to_bson_text() : ", result.c_str());
      return result;
    }

    // Support for serializing non-static members of Team to bson
    void from_bson(bson::bo const& bson_object) {
      bson::be bson_element;

      try {
        {
          members_.clear();
          bson_element = bson_object.getField("members");
          std::vector< mongo::BSONElement > elements(bson_element.Array());
          std::vector< mongo::BSONElement >::const_iterator it(elements.begin());
          std::vector< mongo::BSONElement >::const_iterator end(elements.end());
          for(; it != end; ++it) {
            Person_list_t::value_type element;
            element.from_bson(it->Obj());
            members_.push_back(element);
          }
        }

      } catch(std::exception const& excp) {
        pantheios::log(PANTHEIOS_SEV_ERROR,
                       "Failed to parse Team with exception: ",
                       excp.what(),
                       "\nlast read bson_element:\n",
                       bson_element.jsonString(mongo::Strict, 1).c_str());
        throw;
      }
    }

    void from_bson_text(std::string const& text) {
      mongo::BSONObj obj(mongo::fromjson(text));
      from_bson(obj);
    }
    Person_list_t members_;
  };

  // Support for streaming non-static streamable members of Team
  inline
  std::ostream& operator<<(std::ostream& out, Team const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Team:(" << &item << "):{";
    out << '\n' << indent << "  members:" << item.members_;
    out << indent << "}\n";
    return out;
  } 

} // namespace mongoid
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_MONGOID_MONGOID_H_
