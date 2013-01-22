/******************************************************************************
 * test_umask_scoped_set.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_umask_scoped_set.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/linux_specific/umask_scoped_set.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "fcs/linux_specific/umask_scoped_set.hpp"

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Umask_scoped_set";

namespace {
  void test_umask_scoped_set() {

// custom <test-detail>

    boost::filesystem::path test_file("/tmp/umask_test");
    std::string const test_string("test");
    const int flags(0777);
    const int ignore_execute_flags(0666);

    if(boost::filesystem::exists(test_file)) {
      boost::filesystem::remove(test_file);
    }

    mode_t original_permissions(0);
    {
      fcs::linux_specific::Umask_scoped_set set(flags);
      original_permissions = set.previous_mode();
      std::ofstream out(test_file.string().c_str());
      out << test_string << std::endl;
    }
    BOOST_REQUIRE(boost::filesystem::exists(test_file));
    try {
      struct stat buf;
      int rc(stat(test_file.string().c_str(), &buf));
      BOOST_CHECK_EQUAL(0, rc);
      std::ostringstream msg;
      msg << "File permissions are:" << std::hex << (flags & buf.st_mode);
      BOOST_MESSAGE(msg.str().c_str());
      BOOST_REQUIRE_EQUAL(0, (flags & buf.st_mode));
    } catch(std::exception const& e) {
      BOOST_MESSAGE("Expected and got exception reading file");
    }
    boost::filesystem::remove(test_file);
    {
      std::ofstream out(test_file.string().c_str());
      out << test_string << std::endl;
    }
    struct stat buf;
    int rc(stat(test_file.string().c_str(), &buf));
    BOOST_CHECK_EQUAL(0, rc);
    std::ostringstream msg;
    msg << "original: " << std::hex << (flags & ~original_permissions) << " current: " << (flags & buf.st_mode);
    BOOST_MESSAGE(msg.str().c_str());
    BOOST_CHECK_EQUAL((ignore_execute_flags & ~original_permissions), (ignore_execute_flags & buf.st_mode));
    BOOST_REQUIRE(boost::filesystem::exists(test_file));
    try {
      std::ifstream ifstream(test_file.string().c_str());
      std::string text;
      ifstream >> text;
      BOOST_MESSAGE("Read some text from the permissioned file");
      BOOST_REQUIRE_MESSAGE((test_string == text), "Text should match");
    } catch(std::exception const& e) {
      BOOST_REQUIRE_MESSAGE(false, "Got unexpected exception reading input file");
    }
    //boost::filesystem::remove(test_file);

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Umask_scoped_set");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <umask_scoped_set>" );
  test->add( BOOST_TEST_CASE( &::test_umask_scoped_set ) );
  return test;
}




