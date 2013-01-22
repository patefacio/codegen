/******************************************************************************
 * ExampleCamelCaseFilename.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file ExampleCamelCaseFilename.hpp
 *
 * \brief Place class in custom location - somewhere under top
 * 
 */
#ifndef _FCS_EXAMPLES_CAMEL_CASE_FILENAME_EXAMPLE_CAMEL_CASE_FILENAME_H_
#define _FCS_EXAMPLES_CAMEL_CASE_FILENAME_EXAMPLE_CAMEL_CASE_FILENAME_H_

#include <iosfwd>

namespace fcs {
namespace examples {
namespace camel_case_filename {

  //! Place class in custom location - somewhere under top
  class example_camel_case_filename 
  {
  public:

    friend std::ostream& operator<<(std::ostream& out, example_camel_case_filename const& item);

  private:
    int a_;
  };

} // namespace camel_case_filename
} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_CAMEL_CASE_FILENAME_EXAMPLE_CAMEL_CASE_FILENAME_H_
