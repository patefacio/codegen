/******************************************************************************
 * change_tracker.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file change_tracker.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_RAII_CHANGE_TRACKER_H_
#define _FCS_RAII_CHANGE_TRACKER_H_

#include <boost/call_traits.hpp>

namespace fcs {
namespace raii {

  template < typename T > 
  class Change_tracker 
  {
  public:

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    T current() const {
      return current_;
    }

    T previous() const {
      return previous_;
    }

  
// custom <Change_tracker public header section>

    Change_tracker(T current) : current_(current), previous_(T()) {
    }

    void next_value(T next_value) {
      previous_ = current_;
      current_ = next_value;
    }

// end <Change_tracker public header section>

  private:
    T current_;
    T previous_;
  };

  template < typename T > 
  class Change_tracker_next_value 
  {
  public:

    // Class typedefs
    typedef Change_tracker< T > Change_tracker_t;

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Change_tracker_t tracker() const {
      return tracker_;
    }

    T next_value() const {
      return next_value_;
    }

  
// custom <Change_tracker_next_value public header section>

    Change_tracker_next_value(Change_tracker_t &tracker, T next_value) : 
      tracker_(tracker),
      next_value_(next_value) {
    }

    ~Change_tracker_next_value() {
      tracker_.next_value(next_value_);
    }

// end <Change_tracker_next_value public header section>

  private:
    Change_tracker_t & tracker_;
    T const next_value_;
  };

} // namespace raii
} // namespace fcs
#endif // _FCS_RAII_CHANGE_TRACKER_H_
