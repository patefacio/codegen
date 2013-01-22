/******************************************************************************
 * test_signaller_prioritized.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_signaller_prioritized.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/patterns/observer.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/utils/synch/lock_and_guard_traits_tbb.hpp"
#include "fcs/utils/performance/block_rusage_tracker.hpp"
#include "fcs/utils/performance/block_tick_tracker.hpp"

struct Foo {
  Foo() { std::cout << "Foo ctor" << std::endl; }
  ~Foo() { std::cout << "Foo dtor" << std::endl; }
};

struct Foo_observer {

  Foo_observer(int priority = 7) : priority_(priority) {
    std::cout << "Foo_observer ctor:" << std::endl;
  }

  ~Foo_observer() {
    std::cout << "Foo_observer dtor:" << std::endl;
  }

  void observe(Foo const& f) {
    std::cout << "Observing " << &f << " with priority " << priority_ << std::endl;
  }

  int priority_;
};

struct Other_foo_observer {

  Other_foo_observer() : observations_(0) { 
    std::cout << "Other_foo_observer ctor" << std::endl; 
  }

  ~Other_foo_observer() { 
    std::cout << "Goo dtor with " << observations_ << " observations" << std::endl; 
  }

  void observe(Foo const& f) {
    ++observations_;
  }

  int observations_;
};

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Signaller_prioritized";

namespace {
  void test_signaller_prioritized() {

// custom <test-detail>

    using namespace fcs::utils;
    using namespace fcs::utils::synch;
    using namespace fcs::utils::performance;
    using namespace fcs::patterns;

    Foo f1, f2;
    {
      Signaller_prioritized< Foo, Foo_observer, Foo_observer* > signaller;
      Foo_observer observer(151);
      Foo_observer observer2(10);
      Foo_observer observer3(250);
      signaller.attach(&observer, 151);
      signaller.attach(&observer2, 10);
      signaller.attach(&observer3, 250);
      signaller.signal(f1);
      signaller.signal(f2);
    }
    {
      typedef Signaller_prioritized< Foo, Foo_observer > Signaller_t;
      Signaller_t signaller;
      signaller.attach(Signaller_t::Observer_ptr_t(new Foo_observer(32)), 32);
      signaller.attach(Signaller_t::Observer_ptr_t(new Foo_observer(392)), 392);
      signaller.signal(f1);
      signaller.signal(f2);
    }

    {
      typedef std::shared_ptr< Foo_observer > Foo_observer_ptr;
      typedef Signaller_prioritized
        < Foo, Foo_observer, Foo_observer_ptr, Null_lock_and_guard_traits_tag > Signaller_t;
      Signaller_t signaller;
      signaller.attach(Signaller_t::Observer_ptr_t(new Foo_observer(32)), 32);
      signaller.attach(Signaller_t::Observer_ptr_t(new Foo_observer(23)), 23);
      signaller.signal(f1);
      signaller.signal(f2);
    }

    {
      typedef std::shared_ptr< Foo_observer > Foo_observer_ptr;
      typedef Signaller_prioritized
        < Foo, Foo_observer, Foo_observer_ptr, Tbb_spin_mutex_lock_and_guard_traits_tag > Signaller_t;
      Signaller_t signaller;
      signaller.attach(Signaller_t::Observer_ptr_t(new Foo_observer(32)), 32);
      signaller.attach(Signaller_t::Observer_ptr_t(new Foo_observer(23)), 23);
      signaller.signal(f1);
      signaller.signal(f2);
    }

    std::cout << "DONE" << std::endl;

    {
      typedef std::shared_ptr< Foo_observer > Foo_observer_ptr;

      typedef Signaller_prioritized
        < Foo, Other_foo_observer, 
        Other_foo_observer*, 
        Null_lock_and_guard_traits_tag > Signaller_prioritized_t;

      typedef Signaller
        < Foo, Other_foo_observer, 
        Other_foo_observer*, 
        Null_lock_and_guard_traits_tag > Signaller_t;

      const int num_signals(10000);
      const int num_observations(2*num_signals);
      {
        Signaller_t signaller;
        Other_foo_observer o1, o2, o3;
        signaller.attach(&o1);
        signaller.attach(&o2);
        signaller.attach(&o3);

        //Block_rusage_tracker tracker(&std::cout, "Signaller unprioritized");
        Block_tick_tracker tracker(&std::cout, "Signaller unprioritized");

        for(int i(0); i<num_signals; ++i) {
          signaller.signal(f1);
          signaller.signal(f2);
        }

        BOOST_REQUIRE(o1.observations_ == num_observations);
        BOOST_REQUIRE(o2.observations_ == num_observations);
        BOOST_REQUIRE(o3.observations_ == num_observations);

      }

      {
        Signaller_prioritized_t signaller;
        Other_foo_observer o1, o2, o3;
        signaller.attach(&o1, 1);
        signaller.attach(&o2, 3);
        signaller.attach(&o3, 2);

        //Block_rusage_tracker tracker(&std::cout, "Signaller prioritized");
        Block_tick_tracker tracker(&std::cout, "Signaller prioritized");

        for(int i(0); i<10000; ++i) {
          signaller.signal(f1);
          signaller.signal(f2);
        }

        BOOST_REQUIRE(o1.observations_ == num_observations);
        BOOST_REQUIRE(o2.observations_ == num_observations);
        BOOST_REQUIRE(o3.observations_ == num_observations);

      }

    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Signaller_prioritized");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <signaller_prioritized>" );
  test->add( BOOST_TEST_CASE( &::test_signaller_prioritized ) );
  return test;
}




