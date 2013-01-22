/******************************************************************************
 * outer.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file outer.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_EXAMPLES_NESTED_OUTER_H_
#define _FCS_EXAMPLES_NESTED_OUTER_H_

#include <iosfwd>

namespace fcs {
namespace examples {
namespace nested {

  class outer 
  {
  public:

    // Nested classes
    class inner 
    {
    public:

      explicit inner(
        int a
      ) :
        a_(a)
      {
        ctor_member_init();
      }

      friend std::ostream& operator<<(std::ostream& out, inner const& item);

    private:

      //! Initialize the instance
      inline void ctor_member_init() {
          
// custom <inner::init>
// end <inner::init>
      }
      int a_;
    };

    explicit outer(
      int a
    ) :
      a_(a)
    {
      ctor_member_init();
    }

    friend std::ostream& operator<<(std::ostream& out, outer const& item);

  private:

    //! Initialize the instance
    void ctor_member_init();
  private:
    int a_;
  };

} // namespace nested
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_NESTED_OUTER_H_
