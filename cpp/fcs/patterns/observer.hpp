/******************************************************************************
 * observer.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file observer.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_PATTERNS_OBSERVER_H_
#define _FCS_PATTERNS_OBSERVER_H_

#include "fcs/utils/synch/lock_and_guard_traits.hpp"
#include <boost/call_traits.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/bimap.hpp>
#include <set>

namespace fcs {
namespace patterns {


  //! Signalling piece of the subject/observer pattern
  /**
  Signalling entities create instances of this class
  in order to signal updates of type const& DATA to attached observers.

  */
  template < typename DATA,
             typename OBSERVER,
             typename OBSERVER_PTR = typename boost::add_pointer< OBSERVER >::type,
             typename LOCK_AND_GUARD_TRAITS = utils::synch::Boost_mutex_lock_and_guard_traits_tag > 
  class Signaller 
  {
  public:

    // Class typedefs
    typedef OBSERVER_PTR Observer_ptr_t;
    typedef typename LOCK_AND_GUARD_TRAITS::Lock_t Lock_t;
    typedef typename LOCK_AND_GUARD_TRAITS::Guard_t Guard_t;
    typedef std::set< Observer_ptr_t > Observer_set_t;

  
// custom <Signaller public header section>

    void attach(Observer_ptr_t observer) {
      Guard_t guard(lock_);
      observers_.insert(observer);
    }

    void detach(Observer_ptr_t observer) {
      Guard_t guard(lock_);
      observers_.erase(observer);
    }

    void signal(DATA const& message) {
      Guard_t guard(lock_);
      typename Observer_set_t::const_iterator it(observers_.begin());
      typename Observer_set_t::const_iterator end(observers_.end());
      for(; it != end; ++it) {
        (*it)->observe(message);
      }
    }

    void signal(DATA & message) {
      Guard_t guard(lock_);
      typename Observer_set_t::iterator it(observers_.begin());
      typename Observer_set_t::iterator end(observers_.end());
      for(; it != end; ++it) {
        (*it)->observe(message);
      }
    }

// end <Signaller public header section>

  private:
    //! Container for observers <I>inaccessible</I>
    Observer_set_t observers_;
    //! For protecting the observer container <I>inaccessible</I>
    Lock_t lock_;
  };


  //! Signalling piece of the subject/observer pattern
  /**
  Signalling entities create instances of this class
  in order to signal updates of type const& DATA to attached observers. The
  callbacks are ordered by priority passed in on the attach.

  */
  template < typename DATA,
             typename OBSERVER,
             typename OBSERVER_PTR = typename boost::add_pointer< OBSERVER >::type,
             typename LOCK_AND_GUARD_TRAITS = utils::synch::Boost_mutex_lock_and_guard_traits_tag > 
  class Signaller_prioritized 
  {
  public:

    // Class typedefs
    typedef OBSERVER_PTR Observer_ptr_t;
    typedef typename LOCK_AND_GUARD_TRAITS::Lock_t Lock_t;
    typedef typename LOCK_AND_GUARD_TRAITS::Guard_t Guard_t;
    typedef std::pair< int, Observer_ptr_t > Priority_and_observer_t;
    typedef boost::bimap< Priority_and_observer_t, Observer_ptr_t > Prioritized_observer_map_t;

  
// custom <Signaller_prioritized public header section>

    void attach(Observer_ptr_t observer, int priority) {
      Guard_t guard(lock_);
      prioritized_observer_map_.insert
        (typename Prioritized_observer_map_t::value_type
         (Priority_and_observer_t(priority, observer), observer));
    }

    void detach(Observer_ptr_t observer) {
      Guard_t guard(lock_);
      prioritized_observer_map_.right.erase(observer);
    }

    void signal(DATA const& message) {
      Guard_t guard(lock_);
      typename Prioritized_observer_map_t::iterator it(prioritized_observer_map_.begin());
      typename Prioritized_observer_map_t::iterator end(prioritized_observer_map_.end());
      for(; it != end; ++it) {
        it->right->observe(message);
      }
    }

// end <Signaller_prioritized public header section>

  private:
    //! Container for priority ordered observers <I>inaccessible</I>
    Prioritized_observer_map_t prioritized_observer_map_;
    //! For protecting the observer container <I>inaccessible</I>
    Lock_t lock_;
  };

} // namespace patterns
} // namespace fcs
#endif // _FCS_PATTERNS_OBSERVER_H_
