/******************************************************************************
 * one_ring_base.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file one_ring_base.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_VGROUP_ONE_RING_BASE_H_
#define _FCS_EXAMPLES_VGROUP_ONE_RING_BASE_H_



namespace fcs {
namespace examples {
namespace vgroup {

  class One_ring_base 
  {
  public:

    virtual void
    observe(int i, char const * s) = 0;

    virtual void
    do_good(int i) = 0;

    virtual void
    do_bad(int i) = 0;
  };

} // namespace vgroup
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_VGROUP_ONE_RING_BASE_H_
