#ifndef _FOO_HPP_
#define _FOO_HPP_

#include "swrapper.hpp"

template< typename T >
class Sample_class {
 public:
    static swrapper static_data_;
};

template < typename T > swrapper Sample_class< T >::static_data_("foo");


#endif
