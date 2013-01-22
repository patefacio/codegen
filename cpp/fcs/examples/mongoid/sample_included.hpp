/******************************************************************************
 * sample_included.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file sample_included.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_MONGOID_SAMPLE_INCLUDED_H_
#define _FCS_EXAMPLES_MONGOID_SAMPLE_INCLUDED_H_

#include "fcs/mongoid/mongoid.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <boost/operators.hpp>
#include <string>
#include <cstdint>
#include <iso646.h>
#include <iostream>

namespace fcs {
namespace examples {
namespace mongoid {


  struct SampleIncluded :
    public boost::totally_ordered< SampleIncluded > 
  {

    SampleIncluded(
      std::int32_t how_many,
      std::string const& some_text,
      std::int32_t this_many
    ) :
      how_many_(how_many),
      some_text_(some_text),
      this_many_(this_many)
    {
    }

    SampleIncluded() :
      how_many_(std::int32_t()),
      some_text_(std::string()),
      this_many_(std::int32_t()) 
    {
    }

    bool operator<(SampleIncluded const& rhs) const {
        return
            ((how_many_ != rhs.how_many_)? how_many_ < rhs.how_many_ : (
            ((some_text_ != rhs.some_text_)? some_text_ < rhs.some_text_ : (
            ((this_many_ != rhs.this_many_)? this_many_ < rhs.this_many_ : (false
            ))))));
    }

    bool operator==(SampleIncluded const& rhs) const {
        return
            ((this==&rhs) or (
            (how_many_ == rhs.how_many_) and
            (some_text_ == rhs.some_text_) and
            (this_many_ == rhs.this_many_)));
    }

    friend std::ostream& operator<<(std::ostream& out, SampleIncluded const& item);

    bson::bo to_bson(bool exclude_oid = false) const {
      bson::bob builder;
      to_bson(builder, exclude_oid);
      return builder.obj();
    }

    // Support for serializing non-static members of SampleIncluded to bson
    void to_bson(bson::bob &builder, bool exclude_oid = false) const {

      builder << "how_many" << how_many_;
      builder << "some_text" << some_text_;
      builder << "this_many" << this_many_;
    }

    std::string to_bson_text(bool exclude_oid = false) const {
      const int pretty(1);
      std::string result(to_bson(exclude_oid).jsonString(mongo::Strict, pretty));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Obj to_bson_text() : ", result.c_str());
      return result;
    }

    // Support for serializing non-static members of SampleIncluded to bson
    void from_bson(bson::bo const& bson_object) {
      bson::be bson_element;

      try {
        bson_element = bson_object.getField("how_many");
        if(bson_element.ok()) {
          bson_element.Val(how_many_);
        }

        bson_element = bson_object.getField("some_text");
        if(bson_element.ok()) {
          bson_element.Val(some_text_);
        }

        bson_element = bson_object.getField("this_many");
        if(bson_element.ok()) {
          bson_element.Val(this_many_);
        }

      } catch(std::exception const& excp) {
        pantheios::log(PANTHEIOS_SEV_ERROR,
                       "Failed to parse SampleIncluded with exception: ",
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
    std::int32_t how_many_;
    std::string some_text_;
    std::int32_t this_many_;
  };

  // Support for streaming non-static streamable members of SampleIncluded
  inline
  std::ostream& operator<<(std::ostream& out, SampleIncluded const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "SampleIncluded:(" << &item << "):{";
    out << '\n' << indent << "  how_many:" << item.how_many_;
    out << '\n' << indent << "  some_text:" << item.some_text_;
    out << '\n' << indent << "  this_many:" << item.this_many_;
    out << indent << "}\n";
    return out;
  } 

} // namespace mongoid
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_MONGOID_SAMPLE_INCLUDED_H_
