/******************************************************************************
 * change_until_end_of_block.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file change_until_end_of_block.hpp
 *
 * \brief Changes the value of a variable to a new value and replaces it with original on exit of block
 * 
 */
#ifndef _FCS_RAII_CHANGE_UNTIL_END_OF_BLOCK_H_
#define _FCS_RAII_CHANGE_UNTIL_END_OF_BLOCK_H_

#include <boost/call_traits.hpp>

namespace fcs {
namespace raii {

  //! Changes the value of a variable to a new value and replaces it with original on exit of block
  template < typename T > 
  class Change_until_end_of_block 
  {
  public:

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    T saved_value() const {
      return saved_value_;
    }

    T target() const {
      return target_;
    }

  
// custom <Change_until_end_of_block public header section>

    Change_until_end_of_block(T &target, typename boost::call_traits< T >::param_type new_value) : 
      saved_value_(target),
      target_(target) {
      target_ = new_value;
    }

    ~Change_until_end_of_block() {
      target_ = saved_value_;
    }

// end <Change_until_end_of_block public header section>

  private:
    //! The original value, which is saved until block exit <I>read only</I>
    T saved_value_;
    //! A reference to the variable - required to set the original back <I>read only</I>
    T & target_;
  };

} // namespace raii
} // namespace fcs
#endif // _FCS_RAII_CHANGE_UNTIL_END_OF_BLOCK_H_
