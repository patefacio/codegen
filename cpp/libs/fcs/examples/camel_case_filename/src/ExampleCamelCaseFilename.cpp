/******************************************************************************
 * ExampleCamelCaseFilename.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file ExampleCamelCaseFilename.cpp
 *
 * \brief Place class in custom location - somewhere under top
 * 
 */

#include "fcs/examples/camel_case_filename/ExampleCamelCaseFilename.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <iostream>


// custom <example_camel_case_filename pre-namespace custom>
// end <example_camel_case_filename pre-namespace custom>

namespace fcs {
namespace examples {
namespace camel_case_filename {

  
// custom <example_camel_case_filename namespace custom>
// end <example_camel_case_filename namespace custom>


  // Support for streaming non-static streamable members of example_camel_case_filename
  std::ostream& operator<<(std::ostream& out, example_camel_case_filename const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "example_camel_case_filename:(" << &item << "):{";
    out << '\n' << indent << "  a:" << item.a_;
    out << indent << "}\n";
    return out;
  }


} // namespace camel_case_filename
} // namespace examples
} // namespace fcs


