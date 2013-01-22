/******************************************************************************
 * one_ring_dispatch.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file one_ring_dispatch.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_GROUP_ONE_RING_DISPATCH_H_
#define _FCS_EXAMPLES_GROUP_ONE_RING_DISPATCH_H_

#include "fcs/examples/group/a_inl.hpp"
#include "fcs/examples/group/b_inl.hpp"
#include "fcs/examples/group/c_inl.hpp"

namespace fcs {
namespace examples {
namespace group {

  inline void
  observe(One_ring_dispatcher &dispatcher, int i, char const * s) {
    switch(dispatcher.id_) {
      case A::ONE_RING_ID: {
        reinterpret_cast< A * >(dispatcher.object_)->observe(i, s);
        break;
      }
      case B::ONE_RING_ID: {
        reinterpret_cast< B * >(dispatcher.object_)->observe(i, s);
        break;
      }
      case C::ONE_RING_ID: {
        reinterpret_cast< C * >(dispatcher.object_)->observe(i, s);
        break;
      }
    }
  }

  inline void
  do_good(One_ring_dispatcher &dispatcher, int i) {
    switch(dispatcher.id_) {
      case A::ONE_RING_ID: {
        reinterpret_cast< A * >(dispatcher.object_)->do_good(i);
        break;
      }
      case B::ONE_RING_ID: {
        reinterpret_cast< B * >(dispatcher.object_)->do_good(i);
        break;
      }
      case C::ONE_RING_ID: {
        reinterpret_cast< C * >(dispatcher.object_)->do_good(i);
        break;
      }
    }
  }

  inline void
  do_bad(One_ring_dispatcher &dispatcher, int i) {
    switch(dispatcher.id_) {
      case A::ONE_RING_ID: {
        reinterpret_cast< A * >(dispatcher.object_)->do_bad(i);
        break;
      }
      case B::ONE_RING_ID: {
        reinterpret_cast< B * >(dispatcher.object_)->do_bad(i);
        break;
      }
      case C::ONE_RING_ID: {
        reinterpret_cast< C * >(dispatcher.object_)->do_bad(i);
        break;
      }
    }
  }



} // namespace group
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_GROUP_ONE_RING_DISPATCH_H_
