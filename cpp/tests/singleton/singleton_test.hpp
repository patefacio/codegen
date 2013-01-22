#ifndef _FCS_UTILS_SINGLETON_TEST_HPP_
#define _FCS_UTILS_SINGLETON_TEST_HPP_

#include "fcs/patterns/singleton.hpp"

class My_singleton : public fcs::patterns::Singleton< My_singleton > {
 public:
    My_singleton() {
        FCS_LOG_CTOR();
    }

    ~My_singleton() {
        FCS_LOG_DTOR();
    }

};

#endif
