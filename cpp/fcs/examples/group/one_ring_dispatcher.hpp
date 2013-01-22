/******************************************************************************
 * one_ring_dispatcher.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file one_ring_dispatcher.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_GROUP_ONE_RING_DISPATCHER_H_
#define _FCS_EXAMPLES_GROUP_ONE_RING_DISPATCHER_H_



namespace fcs {
namespace examples {
namespace group {

  struct One_ring_dispatcher 
  {

    template < typename T >
    One_ring_dispatcher(T *t) : 
      id_(T::ONE_RING_ID), 
      object_(t) {
    }
    //! Id of the class type this dispatcher holds <I>open</I>
    int id_;
    //! Object to dispatch functions on <I>open</I>
    void * object_;
  };

} // namespace group
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_GROUP_ONE_RING_DISPATCHER_H_
