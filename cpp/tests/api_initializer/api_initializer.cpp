#include <pantheios/pantheios.hpp>
#include <pantheios/assert.h>
#include <pantheios/backends/bec.fprintf.h> 
#include "fcs/patterns/api_initializer.hpp"

#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>

inline int message(char const* msg) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Message:", msg);
  return 0;
}

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_api_initializer";

namespace test {

  void my_init() {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "my_init");
  }
  void my_uninit() {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "my_uninit");
  }

  void foobar() {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "foobar");
  }

  namespace {
    typedef fcs::patterns::VOID_FUNC VFUNC;

    fcs::patterns::Api_initializer< VFUNC, VFUNC > 
    registry = fcs::patterns::Api_initializer< VFUNC,  VFUNC>
      (&my_init, &foobar);

    int m1(message("M1"));

    fcs::patterns::Api_initializer< VFUNC, VFUNC > 
    registry2 = fcs::patterns::Api_initializer< VFUNC,  VFUNC>
      (&my_init, &foobar);

    int m2(message("M2"));

    fcs::patterns::Api_initializer< VFUNC, VFUNC > 
    registry3 = fcs::patterns::Api_initializer< VFUNC,  VFUNC>
      (&my_uninit, &my_init);

    int m3(message("M3"));

    fcs::patterns::Api_initializer< VFUNC, VFUNC > 
    registry4 = fcs::patterns::Api_initializer< VFUNC,  VFUNC>
      (0, &my_uninit);

    int m4(message("M4"));
  }
}


void test_api_initializer() {
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_api_initializer");
  using namespace boost::unit_test;
  test_suite* test= BOOST_TEST_SUITE( "Unit test <api_initializer>" );
  test->add( BOOST_TEST_CASE( &test_api_initializer ) );
  return test;
}
