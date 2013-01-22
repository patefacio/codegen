/******************************************************************************
 * h5_api.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_api.hpp
 *
 * \brief Basic support for interfacing with hdf5
 * 
 */
#ifndef _FCS_H5_H5_API_H_
#define _FCS_H5_H5_API_H_

#include "H5public.h"
#include <memory>
#include <vector>
#include <iostream>

// Forward class declarations
namespace H5 {  class DataSet;  }
namespace H5 {  class H5File;  }

namespace fcs {
namespace h5 {

  // Library enumerations
  //! Enumerates data type mappings
  enum Cpp_type {
    CPP_TYPE_INT8,
    CPP_TYPE_INT32,
    CPP_TYPE_INT64,
    CPP_TYPE_UINT8,
    CPP_TYPE_UINT32,
    CPP_TYPE_UINT64,
    CPP_TYPE_FLOAT,
    CPP_TYPE_DOUBLE,
    CPP_TYPE_LONG_DOUBLE,
    CPP_TYPE_STRING,
    CPP_TYPE_UNMAPPED
  };

  // Number of entries in Cpp_type
  enum { CPP_TYPE_NUMBER_ENTRIES = 11 };

  inline char const* to_c_str(Cpp_type e) {
    char const* values[] = {
      "CPP_TYPE_INT8",
      "CPP_TYPE_INT32",
      "CPP_TYPE_INT64",
      "CPP_TYPE_UINT8",
      "CPP_TYPE_UINT32",
      "CPP_TYPE_UINT64",
      "CPP_TYPE_FLOAT",
      "CPP_TYPE_DOUBLE",
      "CPP_TYPE_LONG_DOUBLE",
      "CPP_TYPE_STRING",
      "CPP_TYPE_UNMAPPED"
    };
    size_t index(e);
    return ((index < CPP_TYPE_NUMBER_ENTRIES)? values[index] : "INVALID_CPP_TYPE");
  }

  inline std::ostream& operator<<(std::ostream &out, Cpp_type e) {
    return out << to_c_str(e);
  }

  //! Create, open for read or open for read and write
  enum Store_open_type {
    OPEN_CREATE,
    OPEN_READ
  };

  // Number of entries in Store_open_type
  enum { STORE_OPEN_TYPE_NUMBER_ENTRIES = 2 };

  inline char const* to_c_str(Store_open_type e) {
    char const* values[] = {
      "OPEN_CREATE",
      "OPEN_READ"
    };
    size_t index(e);
    return ((index < STORE_OPEN_TYPE_NUMBER_ENTRIES)? values[index] : "INVALID_STORE_OPEN_TYPE");
  }

  inline std::ostream& operator<<(std::ostream &out, Store_open_type e) {
    return out << to_c_str(e);
  }

  // Library typedefs
  typedef std::shared_ptr< H5::DataSet > Data_set_ptr;
  typedef std::shared_ptr< H5::H5File > H5_file_ptr;
  typedef std::vector< hsize_t > Dimensions_t;

  //! Name of this api
  inline
  char const* api_name() {
    return "fcs::h5::H5_api";
  }

  //! Description of this api
  inline
  char const* api_description() {
    return "Api to support accessing hdf5 files, including reading the meta data\n"
  "associated with datasets in those files.";
  }

  inline
  std::pair< char const*, char const* >
  api_name_and_description() {
    return std::pair< char const*, char const* >(api_name(), api_description()); 
  }

} // namespace h5
} // namespace fcs
#endif // _FCS_H5_H5_API_H_
