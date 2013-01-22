/******************************************************************************
 * histogram.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file histogram.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_HISTOGRAM_H_
#define _FCS_UTILS_HISTOGRAM_H_

#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include <iostream>
#include <vector>

namespace fcs {
namespace utils {


  template < typename T = double > 
  class Histogram_statistical 
  {
  public:

    // Class typedefs
    typedef boost::accumulators::accumulator_set< 
      T, 
      boost::accumulators::features< boost::accumulators::tag::density > > Accumulator_t;
    typedef boost::iterator_range< typename std::vector< std::pair< T, T > >::iterator > Hist_results_t;

    explicit Histogram_statistical(
      int num_bins = 20,
      int cache_size = 10
    ) :
      num_bins_(num_bins),
      cache_size_(cache_size),
      accumulator_(boost::accumulators::tag::density::num_bins = num_bins_, boost::accumulators::tag::density::cache_size = cache_size_)
    {
    }

    template <typename T_FRIEND >
    friend std::ostream& operator<<(std::ostream& out, Histogram_statistical< T_FRIEND > const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    int num_bins() const {
      return num_bins_;
    }

    int cache_size() const {
      return cache_size_;
    }

    Accumulator_t accumulator() const {
      return accumulator_;
    }

  
// custom <Histogram_statistical public header section>

    void operator()(T item) {
      accumulator_(item);
    }

// end <Histogram_statistical public header section>

  private:
    int num_bins_;
    int cache_size_;
    Accumulator_t accumulator_;
  };

  // Support for streaming non-static streamable members of Histogram_statistical
  template < typename T >
  inline
  std::ostream& operator<<(std::ostream& out, Histogram_statistical< T > const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Histogram_statistical:(" << &item << "):{";
    out << '\n' << indent << "  num_bins:" << item.num_bins_;
    out << '\n' << indent << "  cache_size:" << item.cache_size_;
    out << '\n' << indent << "  accumulator:" << item.accumulator_;
    out << indent << "}\n";
    return out;
  } 


  template < typename T = double > 
  class Histogram 
  {
  public:

    // Class typedefs
    typedef std::vector< double > Result_vector_t;

    template < typename IT > 
    Histogram(
      IT begin,
      IT end,
      int num_bins = 20
    ) :
      num_bins_(num_bins),
      results_(num_bins)
    {
    
// custom <Histogram ctor member init>

      std::pair< IT, IT > min_and_max(boost::minmax_element(begin, end));
      T smallest(*min_and_max.first);
      T largest(*min_and_max.second);
      std::cout << "Smallest is: " << smallest << " largest is: " << largest << std::endl;

// end <Histogram ctor member init>
    }

    template <typename T_FRIEND >
    friend std::ostream& operator<<(std::ostream& out, Histogram< T_FRIEND > const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    int num_bins() const {
      return num_bins_;
    }

    Result_vector_t results() const {
      return results_;
    }

  
// custom <Histogram public header section>
// end <Histogram public header section>

  private:
    int num_bins_;
    Result_vector_t results_;
  };

  // Support for streaming non-static streamable members of Histogram
  template < typename T >
  inline
  std::ostream& operator<<(std::ostream& out, Histogram< T > const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Histogram:(" << &item << "):{";
    out << '\n' << indent << "  num_bins:" << item.num_bins_;
    out << '\n' << indent << "  results:" << item.results_;
    out << indent << "}\n";
    return out;
  } 

} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_HISTOGRAM_H_
