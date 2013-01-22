/******************************************************************************
 * version_control_commit.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file version_control_commit.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_VERSION_CONTROL_COMMIT_H_
#define _FCS_UTILS_VERSION_CONTROL_COMMIT_H_

#include "fcs/patterns/singleton.hpp"

namespace fcs {
namespace utils {

  class Version_control_commit :
    public fcs::patterns::Singleton< Version_control_commit > 
  {
  protected:

    Version_control_commit() :
      git_commit_("93e35225d2026366fb26135556125c0bfb114219"),
      search_string_("git commit => 93e35225d2026366fb26135556125c0bfb114219") 
    {
    }

  public:

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    char const * git_commit() const {
      return git_commit_;
    }

    char const * search_string() const {
      return search_string_;
    }

  private:
    char const * const git_commit_;
    char const * const search_string_;
    friend class fcs::patterns::Singleton_impl< Version_control_commit >;
  };

} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_VERSION_CONTROL_COMMIT_H_
