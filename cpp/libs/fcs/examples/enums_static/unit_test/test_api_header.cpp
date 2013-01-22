/******************************************************************************
 * test_api_header.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_api_header.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/examples/enums_static/api_header.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/examples/enums_static/some_class.hpp"
#include "fcs/examples/enums_static/some_other_class.hpp"

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_api_header";

namespace {
  void test_api_header() {

// custom <test-detail>

    using namespace fcs::examples::enums_static;
    std::ostringstream out;
    { 
      BOOST_REQUIRE_EQUAL(API_ANSWER_OF_UNIVERSE, 42);
      BOOST_REQUIRE_EQUAL(FORWARD_ANSWER_OF_UNIVERSE, 42);
      BOOST_REQUIRE_EQUAL(some_class::ANSWER_OF_UNIVERSE, 42);
    } 
    {
      API_first v0(API_first_0);
      API_first v1(API_first_1);
      std::string str_0("API_first_0");
      std::string str_1("API_first_1");
      BOOST_REQUIRE_EQUAL(str_0, to_c_str(v0));
      BOOST_REQUIRE_NE(str_0, to_c_str(v1));
      BOOST_REQUIRE_EQUAL(str_1, to_c_str(v1));
      API_second v;
      from_c_str("API_second_0", v);
      BOOST_REQUIRE_EQUAL(v, API_second_0);
      from_c_str("API_second_4", v);
      BOOST_REQUIRE_EQUAL(v, API_second_4);
    }
    {
      BOOST_REQUIRE_EQUAL(API_wa_42, 42);
      BOOST_REQUIRE_EQUAL(API_wa_77, 77);
      BOOST_REQUIRE_EQUAL(std::string("API_wa_42"), to_c_str(API_wa_42));
      API_with_assignments v;
      from_c_str("API_wa_77", v);
      BOOST_REQUIRE_EQUAL(v, API_wa_77);
    }
    {
      int apimf(0);
      BOOST_REQUIRE_EQUAL(false, test_api_mask_first(apimf, API_masked_first_0));
      set_api_mask_first(apimf , API_masked_first_0);
      BOOST_REQUIRE_EQUAL(true, test_api_mask_first(apimf, API_masked_first_0));
      std::ostringstream s;
      dump_api_mask_first(s, apimf);
      BOOST_REQUIRE_EQUAL(s.str(), "(API_masked_first_0,)");
      clear_api_mask_first(apimf, API_masked_first_0);
      BOOST_REQUIRE_EQUAL(0, apimf);
      set_api_mask_first(apimf, API_masked_first_3);
      set_api_mask_first(apimf, API_masked_first_2);
      s.str("");
      dump_api_mask_first(s, apimf);
      BOOST_REQUIRE_EQUAL(s.str(), "(API_masked_first_2,API_masked_first_3,)");            
    }
    {
      FORWARD_first v0(FORWARD_first_0);
      FORWARD_first v1(FORWARD_first_1);
      std::string str_0("FORWARD_first_0");
      std::string str_1("FORWARD_first_1");
      BOOST_REQUIRE_EQUAL(str_0, to_c_str(v0));
      BOOST_REQUIRE_NE(str_0, to_c_str(v1));
      BOOST_REQUIRE_EQUAL(str_1, to_c_str(v1));
      FORWARD_second v;
      from_c_str("FORWARD_second_0", v);
      BOOST_REQUIRE_EQUAL(v, FORWARD_second_0);
      from_c_str("FORWARD_second_4", v);
      BOOST_REQUIRE_EQUAL(v, FORWARD_second_4);
    }
    {
      BOOST_REQUIRE_EQUAL(FORWARD_wa_42, 42);
      BOOST_REQUIRE_EQUAL(FORWARD_wa_77, 77);
      BOOST_REQUIRE_EQUAL(std::string("FORWARD_wa_42"), to_c_str(FORWARD_wa_42));
      FORWARD_with_assignments v;
      from_c_str("FORWARD_wa_77", v);
      BOOST_REQUIRE_EQUAL(v, FORWARD_wa_77);
    }
    {
      int forwardmf(0);
      BOOST_REQUIRE_EQUAL(false, test_forward_mask_first(forwardmf, FORWARD_masked_first_0));
      set_forward_mask_first(forwardmf , FORWARD_masked_first_0);
      BOOST_REQUIRE_EQUAL(true, test_forward_mask_first(forwardmf, FORWARD_masked_first_0));
      std::ostringstream s;
      dump_forward_mask_first(s, forwardmf);
      BOOST_REQUIRE_EQUAL(s.str(), "(FORWARD_masked_first_0,)");
      clear_forward_mask_first(forwardmf, FORWARD_masked_first_0);
      BOOST_REQUIRE_EQUAL(0, forwardmf);
      set_forward_mask_first(forwardmf, FORWARD_masked_first_3);
      set_forward_mask_first(forwardmf, FORWARD_masked_first_2);
      s.str("");
      dump_forward_mask_first(s, forwardmf);
      BOOST_REQUIRE_EQUAL(s.str(), "(FORWARD_masked_first_2,FORWARD_masked_first_3,)");            
    }
    {
      some_class::SCOPED_first v0(some_class::SCOPED_first_0);
      some_class::SCOPED_first v1(some_class::SCOPED_first_1);
      std::string s0("SCOPED_first_0");
      std::string s1("SCOPED_first_1");
      BOOST_REQUIRE_EQUAL(s0, to_c_str(v0));
      BOOST_REQUIRE_NE(s0, to_c_str(v1));
      BOOST_REQUIRE_EQUAL(s1, to_c_str(v1));
      std::ostringstream s;
      s << v0;
      BOOST_REQUIRE_EQUAL(s0, s.str());
      some_class::SCOPED_second v;
      from_c_str("SCOPED_second_0", v);
      BOOST_REQUIRE_EQUAL(v, some_class::SCOPED_second_0);
      from_c_str("SCOPED_second_4", v);
      BOOST_REQUIRE_EQUAL(v, some_class::SCOPED_second_4);
    }
    {
      BOOST_REQUIRE_EQUAL(some_class::SCOPED_wa_42, 42);
      BOOST_REQUIRE_EQUAL(some_class::SCOPED_wa_77, 77);
      BOOST_REQUIRE_EQUAL(std::string("SCOPED_wa_42"), to_c_str(some_class::SCOPED_wa_42));
      some_class::SCOPED_with_assignments v;
      from_c_str("SCOPED_wa_77", v);
      BOOST_REQUIRE_EQUAL(v, some_class::SCOPED_wa_77);
    }
    {
      int scmf(0);
      BOOST_REQUIRE_EQUAL(false, test_scoped_mask_first(scmf, some_class::SCOPED_masked_first_0));
      set_scoped_mask_first(scmf , some_class::SCOPED_masked_first_0);
      BOOST_REQUIRE_EQUAL(true, test_scoped_mask_first(scmf, some_class::SCOPED_masked_first_0));
      std::ostringstream s;
      some_class::dump_scoped_mask_first(s, scmf);
      BOOST_REQUIRE_EQUAL(s.str(), "(SCOPED_masked_first_0,)");
      clear_scoped_mask_first(scmf, some_class::SCOPED_masked_first_0);
      BOOST_REQUIRE_EQUAL(0, scmf);
      set_scoped_mask_first(scmf, some_class::SCOPED_masked_first_3);
      set_scoped_mask_first(scmf, some_class::SCOPED_masked_first_2);
      s.str("");
      some_class::dump_scoped_mask_first(s, scmf);
      BOOST_REQUIRE_EQUAL(s.str(), "(SCOPED_masked_first_2,SCOPED_masked_first_3,)");            
    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_api_header");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <api_header>" );
  test->add( BOOST_TEST_CASE( &::test_api_header ) );
  return test;
}




