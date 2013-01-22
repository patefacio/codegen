#include <pantheios/pantheios.hpp>
#include <pantheios/assert.h>
#include "singleton_test.hpp"

namespace {
    My_singleton* my_singleton_1(My_singleton::get_instance().get());
}

My_singleton* get_singleton() {
    return my_singleton_1;
}
