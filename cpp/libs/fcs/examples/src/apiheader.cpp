/******************************************************************************
 * apiheader.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file apiheader.cpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include <pantheios/frontends/stock.h>
#include "fcs/examples/apiheader.hpp"
#include "fcs/patterns/api_initializer.hpp"
#include <iostream>

namespace fcs {
namespace examples {
  // Class enumerations

  SAMPLE_API char const* to_c_str(ApiHeaderFooEnum e) {
    char const* values[] = {
      "za_xz",
      "zb_xz",
      "zb_pdq"
    };
    size_t index(e);
    return ((index < APIHEADERFOOENUM_NUMBER_ENTRIES)? values[index] : "INVALID_APIHEADERFOOENUM");
  } 
  SAMPLE_API void dump_gooenum(std::ostream &out, int e) {
    out << '(';
    if(test_gooenum(e, ga_xyz)) {
      out << "ga_xyz,";
    }
    if(test_gooenum(e, gb_xyz)) {
      out << "gb_xyz,";
    }
    if(test_gooenum(e, gc)) {
      out << "gc,";
    }
    out << ')';
  } 
    
} // namespace fcs
} // namespace examples
#if defined(SAMPLE_API_EXPORTS)
extern  "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "apiheader_so";
#endif

namespace {
void apiheader_init() {
pantheios::log(PANTHEIOS_SEV_DEBUG, "Init api apiheader");
}

void apiheader_fini() {
pantheios::log(PANTHEIOS_SEV_DEBUG, "Fini api apiheader");
}

fcs::patterns::Api_initializer<> initializer_s(&apiheader_init, &apiheader_fini);

}
