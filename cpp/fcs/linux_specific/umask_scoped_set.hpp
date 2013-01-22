/******************************************************************************
 * umask_scoped_set.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file umask_scoped_set.hpp
 *
 * \brief Sets umask to specified value until destruction and sets it back
 * 
 */
#ifndef _FCS_LINUX_SPECIFIC_UMASK_SCOPED_SET_H_
#define _FCS_LINUX_SPECIFIC_UMASK_SCOPED_SET_H_

#include <sys/types.h>
#include <sys/stat.h>

namespace fcs {
namespace linux_specific {

  //! Sets umask to specified value until destruction and sets it back
  /**

  A typical use of this is to set the umask for a process to
  provide settings of system resources (files, mutexes, mappings,...)
  to allow group members in. For instance, an app may create shared
  memory, and therefore an entry in /dev/shm, but to share it
  the permissions must work. umask settings play a role.

  */
  class Umask_scoped_set 
  {
  public:

    explicit Umask_scoped_set(
      mode_t new_mode
    ) :
      previous_mode_(umask(new_mode))
    {
    }

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    mode_t previous_mode() const {
      return previous_mode_;
    }

  
// custom <Umask_scoped_set public header section>

    ~Umask_scoped_set() {
      umask(previous_mode_);
    }

// end <Umask_scoped_set public header section>

  private:
    //! Original mode, restored to on destruction <I>read only</I>
    mode_t previous_mode_;
  };

} // namespace linux_specific
} // namespace fcs
#endif // _FCS_LINUX_SPECIFIC_UMASK_SCOPED_SET_H_
