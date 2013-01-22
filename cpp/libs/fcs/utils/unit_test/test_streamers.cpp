/******************************************************************************
 * test_place.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file test_streamers.cpp
 * 
 */

#include "fcs/utils/streamers/containers.hpp"
#include <string>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>


#undef BOOST_ALL_DYN_LINK
#include <boost/test/included/unit_test.hpp>

// custom <pre-test>

#include "fcs/utils/streamers/ptr_vector.hpp"
#include "fcs/utils/streamers/ptr_map.hpp"
#include "fcs/utils/streamers/ptr_set.hpp"
#include <memory>

struct Sample_type {
    Sample_type(std::string const& s) : s_(s) {
    }

    friend std::ostream& operator<<(std::ostream &out, Sample_type const& item);
    std::string s_;
};

std::ostream& operator<<(std::ostream &out, Sample_type const& item) {
    out << item.s_;
    return out;
}


// end <pre-test>

void test_streamers() {
// custom <test-detail>

    {
        typedef std::vector<int> Int_vector_t;
        typedef std::deque<int> Int_deque_t;
        typedef std::list<int> Int_list_t;
        typedef std::set<int> Int_set_t;

        Int_vector_t int_vector;
        Int_deque_t int_deque;
        Int_list_t int_list;
        Int_set_t int_set;

        for(int i(0); i<100; ++i) {
            int_vector.push_back(i);
            int_deque.push_back(i);
            int_list.push_back(i);
            int_set.insert(i);
        }

        using namespace fcs::utils::streamers;
        std::stringstream vector_out;
        vector_out << int_vector;

        std::stringstream deque_out;
        deque_out << int_deque;

        std::stringstream list_out;
        list_out << int_list;

        std::stringstream set_out;
        set_out << int_set;

        boost::regex r("\\[\\s*(?:(\\d+)\\s*,\\s*)+\\s*\\]\\s*");
        boost::cmatch matches;
        std::string output(vector_out.str());
        bool result(boost::regex_match(output.c_str(), matches, r));
        BOOST_REQUIRE(result && (std::string(matches[1].first, matches[1].second) == "99"));
        BOOST_REQUIRE(vector_out.str() == deque_out.str());
        BOOST_REQUIRE(deque_out.str() == list_out.str());
        BOOST_REQUIRE(list_out.str() == set_out.str());
    }

    {
        typedef std::map<int, int> Int_int_map_t;
        typedef std::multimap<int, int> Int_int_mmap_t;
        typedef std::list<Sample_type> Sample_type_list_t;

        Int_int_map_t int_int_map;
        Int_int_mmap_t int_int_mmap;
        using namespace fcs::utils::streamers;
        for(int i(0); i<100; ++i) {            
            int_int_map[i] = i*i;
            int_int_mmap.insert(Int_int_mmap_t::value_type(i, i*i));
        }

        boost::regex r("\\[\\s*(?:(\\(\\s*\\d+\\s*=>\\s*\\d+\\s*\\))\\s*,)*\\s*\\]\\s*");
        std::stringstream map_output;
        map_output << int_int_map << std::endl;
        std::stringstream mmap_output;
        mmap_output << int_int_mmap << std::endl;
        std::string output(map_output.str());
        boost::cmatch matches;
        bool result(boost::regex_match(output.c_str(), matches, r));
        BOOST_REQUIRE(result && (std::string(matches[1].first, matches[1].second) == "(99=>9801)"));
        BOOST_REQUIRE(map_output.str() == mmap_output.str());

        {
            typedef std::map< std::string, Sample_type_list_t > Id_to_sample_list_t;
            Id_to_sample_list_t id_to_sample_list;
            Sample_type_list_t sample1;
            Sample_type_list_t sample2;
            sample1.push_back(Sample_type("sample1:a"));
            sample1.push_back(Sample_type("sample1:b"));
            sample1.push_back(Sample_type("sample1:c"));
            sample2.push_back(Sample_type("sample2:a"));
            sample2.push_back(Sample_type("sample2:b"));
            sample2.push_back(Sample_type("sample2:c"));
            id_to_sample_list["sample1"] = sample1;
            id_to_sample_list["sample2"] = sample2;
            std::cout << "*** Map of std::string to Sample_list_t ***\n" << id_to_sample_list << std::endl;
        }
        {
            typedef std::shared_ptr< std::string > String_ptr;
            typedef std::list< String_ptr > String_list;
            String_list string_list;
            string_list.push_back(String_ptr(std::make_shared<std::string>("first")));
            string_list.push_back(String_ptr(std::make_shared<std::string>("second")));
            string_list.push_back(String_ptr(std::make_shared<std::string>("third")));
            std::cout << std::string("**** string_list **** \n") << string_list << std::endl;
        }
        {

            typedef std::pair< std::string, double > Name_age_t;
            std::cout << "Test:" << Name_age_t("foo", 3) << std::endl;
            typedef std::shared_ptr< Name_age_t > Name_age_ptr;
            
            typedef std::pair< int, int > X;
            typedef std::shared_ptr< X > X_ptr;
            X_ptr x_ptr(new X(2,3));
            std::cout << X(3,4) << std::endl;
            std::cout << "Test:" << x_ptr << std::endl;
            {
              std::cout << "Test:" << Name_age_ptr(std::make_shared<Name_age_t>("foo", 4)) << std::endl;
            }
            typedef std::deque< Name_age_ptr > Name_age_list_t;
            Name_age_list_t name_age_list;
            name_age_list.push_back(Name_age_ptr(std::make_shared<Name_age_t>("connor", 11)));
            name_age_list.push_back(Name_age_ptr(std::make_shared<Name_age_t>("ethan", 13)));
            name_age_list.push_back(Name_age_ptr(std::make_shared<Name_age_t>("jacob", 8)));
            name_age_list.push_back(Name_age_ptr(std::make_shared<Name_age_t>("olivia", 5)));
            name_age_list.push_back(Name_age_ptr(std::make_shared<Name_age_t>("elizabeth", 3)));
            name_age_list.push_back(Name_age_ptr(std::make_shared<Name_age_t>("sweet_pea", 0.05)));
            name_age_list.push_back(Name_age_ptr(std::make_shared<Name_age_t>("sadie", 0.4)));
            std::cout << name_age_list << std::endl;

            typedef std::map< X_ptr, Name_age_ptr > GoofyMap;
            GoofyMap goofyMap;
            goofyMap[ x_ptr ] = Name_age_ptr(new Name_age_t("connor", 11));
            std::cout << goofyMap << std::endl;
            
            typedef std::map< GoofyMap, GoofyMap > GoofyGoofyMap;
            typedef std::multimap< GoofyMap, GoofyMap > GoofyGoofyMultiMap;
            GoofyGoofyMap goofyGoofyMap;
            GoofyGoofyMultiMap goofyGoofyMultiMap;
            goofyGoofyMap[ goofyMap ] = goofyMap;
            goofyGoofyMultiMap.insert(GoofyGoofyMultiMap::value_type(goofyMap, goofyMap));
            goofyGoofyMultiMap.insert(GoofyGoofyMultiMap::value_type(goofyMap, goofyMap));
            goofyGoofyMultiMap.insert(GoofyGoofyMultiMap::value_type(goofyMap, goofyMap));
            std::cout << goofyGoofyMap << std::endl;
            std::cout << goofyGoofyMultiMap << std::endl;
            
        }
    }

    {
      using namespace fcs::utils::streamers;
      typedef boost::ptr_vector< int > Int_vec;
      Int_vec iv;
      iv.push_back(new int(1));
      iv.push_back(new int(2));
      iv.push_back(new int(3));
      std::cout << iv << std::endl;
    }

    {
      using namespace fcs::utils::streamers;
      typedef boost::ptr_map< std::string, int > Int_map;
      Int_map im;
      im["one"] = 2;
      im["one"] = 1;
      im["two"] = 2;
      im["three"] = 3;
      std::cout << im << std::endl;
    }


    {
      using namespace fcs::utils::streamers;
      typedef boost::ptr_multimap< std::string, int > Int_map;
      Int_map im;
      std::string one("one");
      std::string & another_one(one);
      im.insert(one, new int(2));
      im.insert(one, new int(3));
      im.insert(another_one, new int(3));
      std::cout << im << std::endl;
    }


    {
      using namespace fcs::utils::streamers;
      typedef boost::ptr_set< int > Int_set;
      Int_set is;
      is.insert(new int(2));
      is.insert(new int(2));
      is.insert(new int(3));
      std::cout << is << std::endl;
    }


// end <test-detail>
}

boost::unit_test::test_suite* init_unit_test_suite(int , char*[]) {
    using namespace boost::unit_test;
    test_suite* test= BOOST_TEST_SUITE( "Unit test <streamers>" );
    test->add( BOOST_TEST_CASE( &test_streamers ) );

    return test;
}




