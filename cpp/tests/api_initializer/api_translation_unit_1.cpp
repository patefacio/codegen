#include <pantheios/pantheios.hpp>
#include "fcs/patterns/api_initializer.hpp"

namespace test {

  void my_t1_init() {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "my_t1_init");
  }

  void my_t1_uninit() {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "my_t1_uninit");
  }


  typedef fcs::patterns::VOID_FUNC VFUNC;

  fcs::patterns::Api_initializer< VFUNC, VFUNC > 
  registry = fcs::patterns::Api_initializer< VFUNC,  VFUNC>
    (&my_t1_init, &my_t1_uninit);

}

int pull_in_translation_unit_1() {
  return 1;
}
