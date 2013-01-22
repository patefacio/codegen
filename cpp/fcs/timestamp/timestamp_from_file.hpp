/******************************************************************************
 * timestamp_from_file.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file timestamp_from_file.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_TIMESTAMP_TIMESTAMP_FROM_FILE_H_
#define _FCS_TIMESTAMP_TIMESTAMP_FROM_FILE_H_

#include "fcs/timestamp.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace fcs {
namespace timestamp {




// custom <timestamp_from_file namespace end section>

  /**
   * Wow! Supercalifrag
   * \item Find $x^2 + y^2 + z^2$ if
   * \begin{eqnarray*}
   * x + y + z = 3 \                             \
   * 2x - y + z = 5 \                             \
   * 3x + 2y - z = 16
   * \end{eqnarray*}
   *
   */
  Timestamp_t timestamp_from_file(boost::filesystem::path const &path) {
    bool exists = boost::filesystem::exists(path);
    Timestamp_t result;
    if(exists) {
      struct stat file_stat;
      if(0 == stat(path.string().c_str(), &file_stat)) {
        timespec modified_time(file_stat.st_mtim);
        result = Timestamp_t(boost::posix_time::from_time_t(modified_time.tv_sec)) +
          boost::posix_time::milliseconds(modified_time.tv_nsec/1000000);
      }
    } else {
      std::ostringstream msg;
      msg << "File does not exist:" << path.string();
      throw std::runtime_error(msg.str());
    }
    return result;
  }

// end <timestamp_from_file namespace end section>
} // namespace timestamp
} // namespace fcs
#endif // _FCS_TIMESTAMP_TIMESTAMP_FROM_FILE_H_
