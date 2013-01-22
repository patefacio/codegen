/******************************************************************************
 * test_table_operations.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_table_operations.hpp
 *
 * \brief Test basic methods on database table class
 * 
 */
#ifndef _FCS_ORM_TEST_TEST_TABLE_OPERATIONS_H_
#define _FCS_ORM_TEST_TEST_TABLE_OPERATIONS_H_

#include "fcs/utils/streamers/containers.hpp"
#include <boost/test/test_tools.hpp>
#include <algorithm>
#include <set>
#include <iterator>

namespace fcs {
namespace orm {
namespace test {

  //! Test basic methods on database table class
  template < typename TABLE_CLASS > 
  class Test_table_operations 
  {
  public:

    // Class typedefs
    typedef typename TABLE_CLASS::Pointer_t Pointer_t;
    typedef typename TABLE_CLASS::Row_list_t Row_list_t;
    typedef typename TABLE_CLASS::Pkey_list_t Pkey_list_t;
    typedef typename TABLE_CLASS::Value_list_t Value_list_t;
    typedef typename TABLE_CLASS::Row_t Row_t;

    explicit Test_table_operations(
      Pointer_t const& table_class
    ) :
      table_class_(table_class),
      initial_select_all_results_()
    {
      ctor_member_init();
    }

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Pointer_t const& table_class() const {
      return table_class_;
    }

    Row_list_t const& initial_select_all_results() const {
      return initial_select_all_results_;
    }

  private:

  
// custom <Test_table_operations private header section>
// end <Test_table_operations private header section>

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <Test_table_operations::init>
// end <Test_table_operations::init>
    }
    //! Class front-ending the database table <I>read only</I>
    Pointer_t table_class_;
    //! Results of initial select <I>read only</I>
    Row_list_t initial_select_all_results_;
  };

} // namespace test
} // namespace orm
} // namespace fcs
#endif // _FCS_ORM_TEST_TEST_TABLE_OPERATIONS_H_
