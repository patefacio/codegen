/******************************************************************************
 * test_person.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_person.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include "fcs/examples/mongoid/mongoid.hpp"



#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>


// custom <pre-test>

#include "fcs/examples/mongoid/person_database_access.hpp"
#include "fcs/utils/performance/block_tick_tracker.hpp"
#include "algorithm"

// end <pre-test>

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test_Person";

namespace {
  void test_person() {

// custom <test-detail>

    using fcs::utils::streamers::operator<<;
    using namespace fcs::examples::mongoid;
    using namespace fcs::utils::performance;
    {
      Person_database_access::Pointer_t person_database_access(Person_database_access::get_instance());
      person_database_access->remove_all();
      Team team;
      Phone_list_t phone_list;
      int const num_people(5);
      int const num_addresses(3);
      String_list_t aliases;
      aliases.push_back("007");
      aliases.push_back("condor");
      Integer_list_t lengths;
      lengths.push_back(1);
      lengths.push_back(2);
      Float_list_t alphas;
      alphas.push_back(-0.5);
      alphas.push_back(-0.8);
      Phone emergency("911");
      Bool_list_t straight_a;
      straight_a.push_back(false);
      straight_a.push_back(false);
      straight_a.push_back(true);
      std::cout << "Ensure index 1: " << person_database_access->ensure_unique_index_on_name() << std::endl;
      std::cout << "Ensure index 2: " << person_database_access->ensure_unique_index_on_name() << std::endl;
      std::cout << "Ensure index 1: " << person_database_access->ensure_index_on_age() << std::endl;
      std::cout << "Ensure index 2: " << person_database_access->ensure_index_on_age() << std::endl;
      Person_list_t people_inserted;
      {
        Block_tick_tracker block_tick_tracker(&std::cout, "serialize people");
        for(int p(0); p < num_people; ++p) {
          phone_list.push_back(Phone("8675309"));
          Address_list_t address_list;
          for(int a(0); a < num_addresses; ++a) {
            address_list.push_back(Address(a, "s jackson ave", "60546", "IN", c));
          }
          SampleIncluded si;
          Person person(p, "Mr Bigger", (p*p+(p%2? 0.5 : 0)), si, phone_list, address_list,
                        aliases, alphas, lengths, emergency, straight_a);
          team.members_.push_back(person);

          BOOST_REQUIRE(!person.oid_.isSet());
          person_database_access->insert(person);
          BOOST_REQUIRE(person.oid_.isSet());
          people_inserted.push_back(person);
        }
      }

//      std::cout << "The team is:" << team << std::endl;
      Person_list_t people;
      {
        Block_tick_tracker block_tick_tracker(&std::cout, "find and deserialize");
        person_database_access->find_all(people);
      }
      std::cout << "The number of people found are: " << people.size() << std::endl;
      std::cout << "The first person is: " << people[0].to_bson_text() << std::endl;
      std::cout << "The number of people inserted are: " << people_inserted.size() << std::endl;

      {
        Person_list_t people_where;
        mongo::BSONObj where(BSON("age" << 0));
        person_database_access->find_all(people_where, where);
        BOOST_REQUIRE_EQUAL(people_where.size(), size_t(1));
        std::cout << "Found people with where clause: " 
                  << where.jsonString(mongo::Strict, 1)
                  << "\nwith value:\n" << people_where[0];
      }
      person_database_access->remove_all();

      std::sort(people_inserted.begin(), people_inserted.end());
      std::sort(people.begin(), people.end());
      bool are_equal(people == people_inserted);
      if(are_equal) {
        std::cout << "Pulled what was pushed" << std::endl;
      } else {
        std::cout << "************** First ************* count => " << people_inserted.size() << "\n" << people_inserted;
        std::cout << "************** Second ************* count => " << people.size() << "\n" << people;
      }
      BOOST_REQUIRE(are_equal);

      people.clear();
      person_database_access->find_all(people);
      std::cout << people << std::endl;
      std::cout << "After removal:" << people << std::endl;

      person_database_access->insert(people_inserted[0]);
      Person p1(people_inserted[0]);
      Person p2;
      p2.from_bson_text(p1.to_bson_text());
      BOOST_REQUIRE_EQUAL(p1, p2);
      person_database_access->insert(p2);
      people.clear();
      person_database_access->find_all(people);
      BOOST_REQUIRE_EQUAL(people.size(), size_t(1));
      person_database_access->remove_all();

    }

// end <test-detail>
  }
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Running Unit Test: test_Person");
  using namespace boost::unit_test;
  unit_test_log.set_threshold_level( log_messages );
  test_suite* test= BOOST_TEST_SUITE( "Unit test <person>" );
  test->add( BOOST_TEST_CASE( &::test_person ) );
  return test;
}




