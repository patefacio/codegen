/******************************************************************************
 * stream_out_visitor.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file stream_out_visitor.hpp
 *
 * \brief Out table cell contents to stream
 * 
 */
#ifndef _FCS_TABLE_STREAM_OUT_VISITOR_H_
#define _FCS_TABLE_STREAM_OUT_VISITOR_H_

#include "fcs/table/table.hpp"
#include <iosfwd>

namespace fcs {
namespace table {

  //! Out table cell contents to stream
  class Stream_out_visitor :
    public boost::static_visitor<> 
  {
  public:

    explicit Stream_out_visitor(
      std::ostream & out
    ) :
      out_(out)
    {
    }

  
// custom <Stream_out_visitor public header section>

    void operator()(boost::int8_t const& v) { 
      out_ << int(v); 
    }

    void operator()(boost::uint8_t const& v) { 
      out_ << static_cast< unsigned int >(v); 
    }

    void operator()(boost::int32_t const& v) { out_ << v; }
    void operator()(boost::int64_t const& v) { out_ << v; }
    void operator()(boost::uint32_t const& v) { out_ << v; }
    void operator()(boost::uint64_t const& v) { out_ << v; }
    void operator()(float const& v) { out_ << std::setiosflags(std::ios::fixed) << std::setprecision(4) << v; }
    void operator()(double const& v) { out_ << std::setiosflags(std::ios::fixed) << std::setprecision(4) << v; }
    void operator()(long double const& v) { out_ << std::setiosflags(std::ios::fixed) << std::setprecision(4) << v; }
    void operator()(std::string const& v) { out_ << v; }

// end <Stream_out_visitor public header section>

  private:
    std::ostream & out_;
  };

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_STREAM_OUT_VISITOR_H_
