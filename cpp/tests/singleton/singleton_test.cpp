#include <pantheios/pantheios.hpp>
#include <pantheios/assert.h>
#include "singleton_test.hpp"
#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>
extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_singleton";
extern My_singleton* get_singleton();

My_singleton* my_singleton_1(My_singleton::get_instance().get());

void test_singleton() {
    My_singleton* my_singleton_2(My_singleton::get_instance().get());
    BOOST_REQUIRE(my_singleton_1 == my_singleton_2);
    BOOST_REQUIRE(my_singleton_1 == get_singleton());
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_singleton");
    using namespace boost::unit_test;
    test_suite* test= BOOST_TEST_SUITE( "Unit test <singleton>" );
    test->add( BOOST_TEST_CASE( &test_singleton ) );
    return test;
}
