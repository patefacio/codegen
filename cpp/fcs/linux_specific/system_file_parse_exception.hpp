/******************************************************************************
 * system_file_parse_exception.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file system_file_parse_exception.hpp
 *
 * \brief Indicates parsing of system file failed
 * 
 */
#ifndef _FCS_LINUX_SPECIFIC_SYSTEM_FILE_PARSE_EXCEPTION_H_
#define _FCS_LINUX_SPECIFIC_SYSTEM_FILE_PARSE_EXCEPTION_H_

#include <boost/exception/all.hpp>
#include <exception>
#include <string>

namespace fcs {
namespace linux_specific {

  //! Indicates parsing of system file failed
  class System_file_parse_exception :
    public virtual boost::exception,
    public virtual std::exception 
  {
  public:

    // Class typedefs
    typedef boost::error_info< struct tag_filename_tag, std::string > filename_tag;

  };

} // namespace linux_specific
} // namespace fcs
#endif // _FCS_LINUX_SPECIFIC_SYSTEM_FILE_PARSE_EXCEPTION_H_
