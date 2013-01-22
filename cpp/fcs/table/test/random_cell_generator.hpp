/******************************************************************************
 * random_cell_generator.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file random_cell_generator.hpp
 *
 * \brief Support for creating a cell with random data
 * 
 */
#ifndef _FCS_TABLE_TEST_RANDOM_CELL_GENERATOR_H_
#define _FCS_TABLE_TEST_RANDOM_CELL_GENERATOR_H_

#include "fcs/table/table.hpp"
#include <boost/random.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/cstdint.hpp>
#include <limits>

namespace fcs {
namespace table {
namespace test {

  //! Support for creating a cell with random data
  class Random_cell_generator 
  {
  public:

    Random_cell_generator() :
      uniform_real_(0, std::numeric_limits< long double >::max()),
      uniform_int_(0, std::numeric_limits< boost::int64_t >::max()),
      generator_(std::numeric_limits< boost::int64_t >::max()),
      real_generator_(generator_, uniform_real_),
      int_generator_(generator_, uniform_int_) 
    {
    }

  
// custom <Random_cell_generator public header section>

    bool random_sign() {
      return 0 == int_generator_()%2;
    }

    Cell_contents_t generate(Table_cell_type table_cell_type) {
      switch(table_cell_type) {
       case CELL_TYPE_INT8: {
         boost::int64_t temp(int_generator_());
         return Cell_contents_t(boost::int8_t(random_sign()?
                                                               -temp % std::numeric_limits< boost::int8_t >::max():
                                                               temp % std::numeric_limits< boost::int8_t >::max()));
         break;
       }
       case CELL_TYPE_INT32: {
         boost::int64_t temp(int_generator_());
         return Cell_contents_t(boost::int32_t(random_sign()?
                                                                -temp % std::numeric_limits< boost::int32_t >::max() :
                                                                temp % std::numeric_limits< boost::int32_t >::max()));
         break;
       }
       case CELL_TYPE_INT64: {
         boost::int64_t temp(int_generator_());
         return Cell_contents_t(boost::int64_t(random_sign()?
                                                                -temp % std::numeric_limits< boost::int64_t >::max():
                                                                temp % std::numeric_limits< boost::int64_t >::max()));
         break;
       }
       case CELL_TYPE_UINT8: {
         boost::int64_t temp(int_generator_());
         return Cell_contents_t(boost::uint8_t(temp % std::numeric_limits< boost::int8_t >::max()));
         break;
       }
       case CELL_TYPE_UINT32: {
         boost::int64_t temp(int_generator_());
         return Cell_contents_t(boost::uint32_t(temp % std::numeric_limits< boost::int32_t >::max()));
         break;
       }
       case CELL_TYPE_UINT64: {
         boost::int64_t temp(int_generator_());
         return Cell_contents_t(boost::uint64_t(temp % std::numeric_limits< boost::int64_t >::max()));
         break;
       }
       case CELL_TYPE_FLOAT: {
         return Cell_contents_t(
           static_cast< float >(random_sign()? 
                                -log(fmod(rand(), std::numeric_limits< float >::max())) : 
                                log(fmod(rand(), std::numeric_limits< float >::max()))));
         break;
       }
       case CELL_TYPE_DOUBLE: {
         return Cell_contents_t
           (static_cast<double>
            ((random_sign()? -rand() : rand()) + (static_cast<double>(rand())/RAND_MAX)));
         break;
       }
       case CELL_TYPE_LONG_DOUBLE: {
         return Cell_contents_t
           (static_cast<long double>
            ((random_sign()? -rand() : rand()) + (static_cast<double>(rand())/RAND_MAX)));
         break;
       }
       case CELL_TYPE_STRING: {
         return Cell_contents_t(std::string("make_random"));
         break;
       }
       default: {
         return Cell_contents_t(std::string("Oops"));
       }
      }
    }

// end <Random_cell_generator public header section>

  private:
    boost::uniform_real< long double > uniform_real_;
    boost::uniform_int< boost::int64_t > uniform_int_;
    boost::mt19937 generator_;
    boost::variate_generator< boost::mt19937, boost::uniform_real< long double > > real_generator_;
    boost::variate_generator< boost::mt19937, boost::uniform_int< boost::int64_t > > int_generator_;
  };

} // namespace test
} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TEST_RANDOM_CELL_GENERATOR_H_
