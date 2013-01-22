/******************************************************************************
 * all_types_data_set_specifier.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file all_types_data_set_specifier.hpp
 *
 * \brief Defines the location in the file and the data_set for writing
 * 
 */
#ifndef _FCS_CODEGEN_COVERAGE_ALL_TYPES_DATA_SET_SPECIFIER_H_
#define _FCS_CODEGEN_COVERAGE_ALL_TYPES_DATA_SET_SPECIFIER_H_

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
  class All_types_data_set_specifier :
    public fcs::patterns::Singleton< All_types_data_set_specifier > 
  {
  protected:

    All_types_data_set_specifier() :
      data_set_name_("/all_types"),
      compound_data_type_id_(-1),
      sample_string_hid_(-1) 
    {
      ctor_default_init();
    }

  public:

    static std::string const& data_set_name() { return get_instance()->data_set_name_; }
    static hid_t compound_data_type_id() { return get_instance()->compound_data_type_id_; } 

    ~All_types_data_set_specifier() {
      // Clean up created/openend h5 handles
      H5Tclose(sample_string_hid_);
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Closed All_types string data type sample_string_hid:", 
                     pantheios::integer(sample_string_hid_));
      H5Tclose(compound_data_type_id_);
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Closed All_types compound_data_type:", 
                     pantheios::integer(compound_data_type_id_));
    }
  private:

    void ctor_default_init() {
      compound_data_type_id_ = H5Tcreate( H5T_COMPOUND, sizeof(All_types) );
      // space for int
      H5Tinsert( compound_data_type_id_, "int_m", HOFFSET( All_types, int_m_ ), H5T_NATIVE_INT );
      // space for double
      H5Tinsert( compound_data_type_id_, "double_m", HOFFSET( All_types, double_m_ ), H5T_NATIVE_DOUBLE );
      // space for long
      H5Tinsert( compound_data_type_id_, "long_m", HOFFSET( All_types, long_m_ ), H5T_NATIVE_LONG );
      // space for long double
      H5Tinsert( compound_data_type_id_, "long_double_m", HOFFSET( All_types, long_double_m_ ), H5T_NATIVE_LDOUBLE );
      // space for long int
      H5Tinsert( compound_data_type_id_, "long_int_m", HOFFSET( All_types, long_int_m_ ), H5T_NATIVE_LONG );
      // space for long long
      H5Tinsert( compound_data_type_id_, "long_long_m", HOFFSET( All_types, long_long_m_ ), H5T_NATIVE_LLONG );
      // space for unsigned int
      H5Tinsert( compound_data_type_id_, "unsigned_int_m", HOFFSET( All_types, unsigned_int_m_ ), H5T_NATIVE_UINT32 );
      // space for unsigned long
      H5Tinsert( compound_data_type_id_, "unsigned_long_m", HOFFSET( All_types, unsigned_long_m_ ), H5T_NATIVE_ULONG );
      // space for unsigned long long
      H5Tinsert( compound_data_type_id_, "unsigned_long_long_m", HOFFSET( All_types, unsigned_long_long_m_ ), H5T_NATIVE_ULLONG );
      // space for boost::int16_t
      H5Tinsert( compound_data_type_id_, "boost_int16_t_m", HOFFSET( All_types, boost_int16_t_m_ ), H5T_NATIVE_SHORT );
      // space for boost::int32_t
      H5Tinsert( compound_data_type_id_, "boost_int32_t_m", HOFFSET( All_types, boost_int32_t_m_ ), H5T_NATIVE_INT32 );
      // space for boost::int64_t
      H5Tinsert( compound_data_type_id_, "boost_int64_t_m", HOFFSET( All_types, boost_int64_t_m_ ), H5T_NATIVE_INT64 );
      // space for boost::uint16_t
      H5Tinsert( compound_data_type_id_, "boost_uint16_t_m", HOFFSET( All_types, boost_uint16_t_m_ ), H5T_NATIVE_USHORT );
      // space for boost::uint32_t
      H5Tinsert( compound_data_type_id_, "boost_uint32_t_m", HOFFSET( All_types, boost_uint32_t_m_ ), H5T_NATIVE_UINT32 );
      // space for boost::uint64_t
      H5Tinsert( compound_data_type_id_, "boost_uint64_t_m", HOFFSET( All_types, boost_uint64_t_m_ ), H5T_NATIVE_UINT64 );

      // space for fcs::utils::Fixed_size_char_array< 32 >
      sample_string_hid_ = H5Tcopy(H5T_C_S1);
      H5Tset_size(sample_string_hid_, 32);
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Created All_types string data type sample_string:", pantheios::integer(sample_string_hid_));
      H5Tinsert( compound_data_type_id_, "sample_string", HOFFSET( All_types, sample_string_ ), sample_string_hid_);
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Created All_types compound_data_type:", pantheios::integer(compound_data_type_id_));

    }
    std::string data_set_name_;
    hid_t compound_data_type_id_;
    hid_t sample_string_hid_;
    friend class fcs::patterns::Singleton_impl< All_types_data_set_specifier >;
  };

} // namespace coverage
} // namespace codegen
} // namespace fcs
#endif // _FCS_CODEGEN_COVERAGE_ALL_TYPES_DATA_SET_SPECIFIER_H_
