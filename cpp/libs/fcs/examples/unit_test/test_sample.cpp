/******************************************************************************
 * test_sample.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_sample.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/examples/sample.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/examples/sample.hpp"
#include "fcs/examples/goo.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_sample";

namespace {
  void test_sample() {

// custom <test-detail>

    boost::property_tree::ptree p;
    fcs::examples::goo g;
    g.s1("this is s1");
    g.s2("this is s2");
    g.s3(3331432.9938293);
    g.s4("another");
    g.d5(3331432.9938293);
    g.nameList().push_back("a");
    g.nameList().push_back("b");
    g.nameList().push_back("c");
//    g.nameListList().push_back(g.nameList());
//    g.nameListList().push_back(g.nameList());
//    g.nameListList().push_back(g.nameList());
    g.nameMap()["hey you"] = "dan";
    g.nameMap()["good"] = "boy";
    g.nameMapMap()["deeper"] = g.nameMap();
    fcs::examples::sample s;
    s.s1("wow - deep");
    s.s9("naughty number 9");
    s.nl(g.nameList());
    s.nm(g.nameMap());
//    g.embeddedSample(s);
    g.to_property_tree("top", p);
    boost::property_tree::json_parser::write_json(std::cout, p);
//    g.s1("overridden1");
//    g.s2("overridden2");
//    std::cout << g << std::endl;

    fcs::examples::goo g2;
    std::cout << "CHECK NEXT" << std::endl;
    g2.from_property_tree("top", p);
    std::cout << g2 << std::endl;
    std::cout << "Are they equal?" << ((g2 == g)? 't' : 'f') << std::endl;

    using namespace fcs::examples;
    {
      ApiHeaderFooEnum_Forward x(cls_fwd_za_xyz);
      std::cout << x << std::endl;
    }

    {
      int x(0);
      set_gooenum_forward(x, cls_fwd_a_xyz);
      set_gooenum_forward(x, cls_fwd_c);
      dump_gooenum_forward(std::cout, x);
    }

    {
      int x(0);
      sample::set_gooenum_cls(x, sample::cls_a_xyz);
      sample::set_gooenum_cls(x, sample::cls_c);
      sample::dump_gooenum_cls(std::cout, x);
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_sample");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <sample>" );
  test->add( BOOST_TEST_CASE( &::test_sample ) );
  return test;
}




