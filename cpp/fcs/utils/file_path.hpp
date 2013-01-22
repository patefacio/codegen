/******************************************************************************
 * file_path.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file file_path.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_FILE_PATH_H_
#define _FCS_UTILS_FILE_PATH_H_

#include <boost/filesystem/path.hpp>

namespace fcs {
namespace utils {

// custom <file_path namespace begin section>

  typedef boost::filesystem::path Path_t;

  inline std::string full_path(Path_t const& path) {
#if defined(BOOST_FILESYSTEM_VERSION) && BOOST_FILESYSTEM_VERSION == 2
    return path.file_string();
#else
    return path.string();
#endif
  }

  inline std::string basename(Path_t const& path) {
#if defined(BOOST_FILESYSTEM_VERSION) && BOOST_FILESYSTEM_VERSION == 2
    return path.filename();
#else
    return path.filename().string();
#endif
  }

// end <file_path namespace begin section>



} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_FILE_PATH_H_
