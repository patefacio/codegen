/******************************************************************************
 * h5_file_repository.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_file_repository.hpp
 *
 * \brief File path to hdf5 file
 * 
 */
#ifndef _FCS_H5_H5_FILE_REPOSITORY_H_
#define _FCS_H5_H5_FILE_REPOSITORY_H_

#include "fcs/h5/h5_api.hpp"
#include "H5Cpp.h"
#include "fcs/patterns/singleton.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <map>

namespace fcs {
namespace h5 {

  //! File path to hdf5 file
  /**
  Map of file path to open hdf5 file, with methods to add and retrieve files
  from the repository. Singleton providing a single point of file retrieval. 
  */
  class H5_file_repository :
    public fcs::patterns::Singleton< H5_file_repository > 
  {
  public:

    // Class typedefs
    typedef std::map< boost::filesystem::path, H5_file_ptr > H5_file_map_t;

  protected:

    H5_file_repository() :
      h5_file_map_() 
    {
    }

  public:

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    H5_file_map_t const& h5_file_map() const {
      return h5_file_map_;
    }

  
// custom <H5_file_repository public header section>

    H5_file_ptr retrieve_file(const char* file_path) {
      return H5_file_ptr();
    }

    H5_file_ptr create_file(const char* file_path) {
      H5_file_ptr result(new H5::H5File(file_path, H5F_ACC_TRUNC));
      return result;
    }

    H5_file_ptr open_file(const char* file_path) {
      H5_file_ptr result(new H5::H5File(file_path, H5F_ACC_RDONLY));
      return result;
    }

// end <H5_file_repository public header section>

  private:
    H5_file_map_t h5_file_map_;
    friend class fcs::patterns::Singleton_impl< H5_file_repository >;
  };

} // namespace h5
} // namespace fcs
#endif // _FCS_H5_H5_FILE_REPOSITORY_H_
