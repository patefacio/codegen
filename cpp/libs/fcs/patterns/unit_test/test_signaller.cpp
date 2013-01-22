/******************************************************************************
 * test_signaller.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_signaller.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/patterns/observer.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

struct Sample {
  Sample() {
    std::cout << "created Sample(" << this << ')' << std::endl;
  }
  ~Sample() {
    std::cout << "destroyed Sample(" << this << ')' << std::endl;
  }
};

struct SampleObserver {
  SampleObserver() {
    std::cout << "created SampleObserver(" << this << ')' << std::endl;
  }
  virtual ~SampleObserver() {
    std::cout << "destroyed SampleObserver(" << this << ')' << std::endl;
  }

  virtual void observe(Sample const& s) {
    std::cout << "SampleObserver " << this << " observed:" << &s << std::endl;
  }
};

template< typename T = int >
struct DerivedObserver : public SampleObserver {
  DerivedObserver() : count_(0) {
    std::cout << "created DerivedObserver(" << this << ')' << std::endl;
  }
  virtual ~DerivedObserver() {
    std::cout << "destroyed DerivedObserver(" << this << ") with count => " << count_ << std::endl;
  }

  virtual void observe(Sample const& s) {
    std::cout << "DerivedObserver " << this << " observed:" << &s << std::endl;
    ++count_;
  }
  T count_;
};

template < typename VIRTUAL_OBSERVER > 
class Virtual_observer_wrapper {
public:
  Virtual_observer_wrapper(VIRTUAL_OBSERVER *observer) : observer_(observer) {}
  inline void observe(Sample const& sample) {
    observer_->observe(sample);
  }
private:
  SampleObserver *observer_;
};

struct Foo {
  Foo() { std::cout << "Foo ctor" << std::endl; }
  ~Foo() { std::cout << "Foo dtor" << std::endl; }
};

struct Goo {
  Goo() { std::cout << "Goo ctor" << std::endl; }
  ~Goo() { std::cout << "Goo dtor" << std::endl; }
};

struct FooObserver {
  FooObserver(int priority = 1) : priority_(priority) {
    std::cout << "FooObserver ctor:" << std::endl;
  }

  ~FooObserver() {
    std::cout << "FooObserver dtor:" << std::endl;
  }

  void observe(Foo const& f) {
    std::cout << "Observing " << &f << " with pty: " << priority_ << std::endl;
  }

  int priority_;

};

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Signaller";

namespace {
  void test_signaller() {

// custom <test-detail>

    using namespace fcs::patterns;
    Signaller< Sample, Virtual_observer_wrapper< SampleObserver > > signaller;

    SampleObserver so1, so2, so3, so4;
    DerivedObserver<> do1, do2, do3, do4;

    Virtual_observer_wrapper< SampleObserver > vo1(&so1);
    Virtual_observer_wrapper< SampleObserver > vo2(&so2);
    Virtual_observer_wrapper< SampleObserver > vo3(&so3);
    Virtual_observer_wrapper< SampleObserver > vo4(&so4);

    Virtual_observer_wrapper< SampleObserver > vo5(&do1);
    Virtual_observer_wrapper< SampleObserver > vo6(&do2);
    Virtual_observer_wrapper< SampleObserver > vo7(&do3);
    Virtual_observer_wrapper< SampleObserver > vo8(&do4);
    signaller.attach(&vo1);
    signaller.attach(&vo2);

    signaller.attach(&vo3);
    signaller.attach(&vo4);

    signaller.attach(&vo5);
    signaller.attach(&vo6);

    signaller.attach(&vo7);
    signaller.attach(&vo8);

    Sample s1;
    signaller.signal(s1);
    signaller.signal(s1);

    std::cout << "Alternate " << std::endl;
    Signaller< Sample, SampleObserver > signaller2;
    signaller2.attach(&so1);
    signaller2.attach(&do1);
    signaller2.attach(&so2);
    signaller2.attach(&do2);
    signaller2.signal(s1);
    signaller2.signal(s1);

    {
      Foo f1, f2;
      {
        fcs::patterns::Signaller< Foo, FooObserver, FooObserver* > signaller;
        FooObserver observer(151);
        FooObserver observer2(10);
        FooObserver observer3(250);
        signaller.attach(&observer);
        signaller.attach(&observer2);
        signaller.attach(&observer3);
        signaller.signal(f1);
        signaller.signal(f2);
        signaller.detach(&observer3);
        signaller.signal(f2);
      }
      {
        typedef fcs::patterns::Signaller< Foo, FooObserver > Signaller_t;
        Signaller_t signaller;
        signaller.attach(Signaller_t::Observer_ptr_t(new FooObserver(3)));
        signaller.attach(Signaller_t::Observer_ptr_t(new FooObserver(392)));
        signaller.signal(f1);
        signaller.signal(f2);
      }

      {
        typedef std::shared_ptr< FooObserver > FooObserverPtr;
        typedef fcs::patterns::Signaller< Foo, FooObserver, FooObserverPtr, 
          fcs::utils::synch::Null_lock_and_guard_traits_tag > Signaller_t;
        Signaller_t signaller;
        signaller.attach(Signaller_t::Observer_ptr_t(new FooObserver(32)));
        signaller.attach(Signaller_t::Observer_ptr_t(new FooObserver(23)));
        signaller.signal(f1);
        signaller.signal(f2);
      }

      std::cout << "DONE" << std::endl;

    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Signaller");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <signaller>" );
  test->add( BOOST_TEST_CASE( &::test_signaller ) );
  return test;
}




