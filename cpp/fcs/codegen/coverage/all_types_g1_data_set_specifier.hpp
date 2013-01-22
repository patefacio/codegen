/******************************************************************************
 * all_types_g1_data_set_specifier.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file all_types_g1_data_set_specifier.hpp
 *
 * \brief Defines the location in the file and the data_set for writing
 * 
 */
#ifndef _FCS_CODEGEN_COVERAGE_ALL_TYPES_G1_DATA_SET_SPECIFIER_H_
#define _FCS_CODEGEN_COVERAGE_ALL_TYPES_G1_DATA_SET_SPECIFIER_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters/integer.hpp>
#include "fcs/codegen/coverage/all_types.hpp"
#include "hdf5.h"
#include "fcs/patterns/singleton.hpp"
#include <string>

namespace fcs {
namespace codegen {
namespace coverage {

  //! Defines the location in the file and the data_set for writing
  class All_types_g1_data_set_specifier :
    public fcs::patterns::Singleton< All_types_g1_data_set_specifier > 
  {
  protected:

    All_types_g1_data_set_specifier() :
      data_set_name_("/all_types"),
      compound_data_type_id_(-1) 
    {
      ctor_default_init();
    }

  public:

    static std::string const& data_set_name() { return get_instance()->data_set_name_; }
    static hid_t compound_data_type_id() { return get_instance()->compound_data_type_id_; } 

    ~All_types_g1_data_set_specifier() {
      // Clean up created/openend h5 handles
      H5Tclose(compound_data_type_id_);
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Closed All_types compound_data_type:", 
                     pantheios::integer(compound_data_type_id_));
    }
  private:

    void ctor_default_init() {
      compound_data_type_id_ = H5Tcreate( H5T_COMPOUND, sizeof(All_types) );
      // space for int
      H5Tinsert( compound_data_type_id_, "int_m", HOFFSET( All_types, int_m_ ), H5T_NATIVE_INT );
      // space for boost::int32_t
      H5Tinsert( compound_data_type_id_, "boost_int32_t_m", HOFFSET( All_types, boost_int32_t_m_ ), H5T_NATIVE_INT32 );
    }
    std::string data_set_name_;
    hid_t compound_data_type_id_;
    friend class fcs::patterns::Singleton_impl< All_types_g1_data_set_specifier >;
  };

} // namespace coverage
} // namespace codegen
} // namespace fcs
#endif // _FCS_CODEGEN_COVERAGE_ALL_TYPES_G1_DATA_SET_SPECIFIER_H_
