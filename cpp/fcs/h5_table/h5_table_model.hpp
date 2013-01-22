/******************************************************************************
 * h5_table_model.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_table_model.hpp
 *
 * \brief Table model for hdf5 data_sets
 * 
 */
#ifndef _FCS_H5_TABLE_H5_TABLE_MODEL_H_
#define _FCS_H5_TABLE_H5_TABLE_MODEL_H_

#include "fcs/h5/h5_meta_data.hpp"
#include "fcs/h5/h5_file_repository.hpp"
#include "fcs/table/table_model.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>

namespace fcs {
namespace h5_table {


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

    // Forward typedefs
  using fcs::h5::H5_file_ptr;
  using fcs::h5::Data_set_ptr;

  //! Table model for hdf5 data_sets
  class H5_table_model :
    public fcs::table::Table_model 
  {
  public:

    H5_table_model(
      boost::filesystem::path const& h5_file_path,
      std::string const& data_set_name
    ) :
      fcs::table::Table_model(create_table_meta_data(h5_file_path, data_set_name)),
      h5_file_path_(h5_file_path),
      data_set_name_(data_set_name),
      file_(fcs::h5::H5_file_repository::get_instance()->open_file(h5_file_path.string().c_str())),
      data_set_(new H5::DataSet(file_->openDataSet(data_set_name)))
    {
      ctor_member_init();
    }

    friend std::ostream& operator<<(std::ostream& out, H5_table_model const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    boost::filesystem::path const& h5_file_path() const {
      return h5_file_path_;
    }

    std::string const& data_set_name() const {
      return data_set_name_;
    }

  
// custom <H5_table_model public header section>

    static inline fcs::table::Table_cell_type map_h5_type_to_table_type(fcs::h5::Cpp_type cpp_type) {
      switch(cpp_type) {
       case fcs::h5::CPP_TYPE_INT8: {
         return fcs::table::CELL_TYPE_INT8;
         break;
       }
       case fcs::h5::CPP_TYPE_INT32: {
         return fcs::table::CELL_TYPE_INT32;
         break;
       }
       case fcs::h5::CPP_TYPE_INT64: {
         return fcs::table::CELL_TYPE_INT64;
         break;
       }
       case fcs::h5::CPP_TYPE_UINT8: {
         return fcs::table::CELL_TYPE_UINT8;
         break;
       }
       case fcs::h5::CPP_TYPE_UINT32: {
         return fcs::table::CELL_TYPE_UINT32;
         break;
       }
       case fcs::h5::CPP_TYPE_UINT64: {
         return fcs::table::CELL_TYPE_UINT64;
         break;
       }
       case fcs::h5::CPP_TYPE_FLOAT: {
         return fcs::table::CELL_TYPE_FLOAT;
         break;
       }
       case fcs::h5::CPP_TYPE_DOUBLE: {
         return fcs::table::CELL_TYPE_DOUBLE;
         break;
       }
       case fcs::h5::CPP_TYPE_LONG_DOUBLE: {
         return fcs::table::CELL_TYPE_LONG_DOUBLE;
         break;
       }
       case fcs::h5::CPP_TYPE_STRING: {
         return fcs::table::CELL_TYPE_STRING;
         break;
       }
       case fcs::h5::CPP_TYPE_UNMAPPED: {
         throw std::runtime_error("CPP_TYPE_UNMAPPED does not map to a Table_cell_type");
         break;
       }
      }
      std::string msg("Could not map to a Table_cell_type: ");
      msg += to_c_str(cpp_type);
      throw std::runtime_error(msg);
    }

    static fcs::table::Table_meta_data create_table_meta_data(fcs::h5::H5_meta_data::Data_set_detail const& data_set_detail) {

      std::cout << "Creating Table_meta_data from H5_meta_data::Data_set_detail: " << data_set_detail;      

      using namespace fcs::h5;
      using namespace fcs::table;
      Table_shape_t shape;
      Table_header_t header;
      H5_meta_data::Data_set_member_detail_list_t::const_iterator it(data_set_detail.member_detail_.begin());
      H5_meta_data::Data_set_member_detail_list_t::const_iterator end(data_set_detail.member_detail_.end());
      for(; it != end; ++it) {
        if(CPP_TYPE_UNMAPPED != it->cpp_type_) {
          shape.push_back(H5_table_model::map_h5_type_to_table_type(it->cpp_type_));
          header.push_back(it->name_);
        }
      }
      Table_meta_data result(shape, header);
      return result;
    }

    static fcs::table::Table_meta_data create_table_meta_data(boost::filesystem::path const& path_to_h5_file,
                                                              std::string const& data_set_name) {
      using namespace fcs::h5;
      using namespace fcs::table;
      H5_meta_data const meta_data(path_to_h5_file);
      H5_meta_data::Data_set_detail data_set_detail(meta_data.get_data_set_detail(data_set_name));
      Table_meta_data result(create_table_meta_data(data_set_detail));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Created Table_meta_data for h5 file:", 
                     path_to_h5_file.string().c_str(), " on data_set:", data_set_name.c_str());
      return result;
    }

    virtual fcs::table::Index_t row_count() const { 
      // Get the dataspace of the dataset

      hid_t data_space_id(H5Dget_space(data_set_->getId()));

      if(data_space_id > 0) {
        hsize_t ndims(H5Sget_simple_extent_ndims(data_space_id));

        hsize_t *dims(new hsize_t[ndims]);
        hsize_t *max_dims(new hsize_t[ndims]);

        // Get the dimensions
        H5Sget_simple_extent_dims(data_space_id, dims, max_dims);
        hsize_t result(dims[ndims - 1]);

        delete [] dims;
        delete [] max_dims;
        return result;
      } else {
        std::ostringstream msg;
        msg << "Could not get number of rows!";
        throw std::runtime_error(msg.str());
      }
    }

    virtual ~H5_table_model() {}
    virtual void read_cell(fcs::table::Index_t row, fcs::table::Index_t column, fcs::table::Cell_contents_t & cell_contents) const {}
    virtual void read_cell(fcs::table::Index_t row, fcs::table::Index_t column, std::string & cell_text) const {}

    virtual void read_row(fcs::table::Index_t row, fcs::table::Row_contents_t & row_contents) const {

    }

    virtual void read_column(fcs::table::Index_t column, fcs::table::Column_contents_t & column_contents) const {}

    virtual void add_row(fcs::table::Row_contents_ptr const& row) {}

// end <H5_table_model public header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <H5_table_model::init>
// end <H5_table_model::init>
    }
  protected:
    //! Location of hdf5 file with data_sets <I>read only</I>
    boost::filesystem::path const h5_file_path_;
    //! Data_set name <I>read only</I>
    std::string data_set_name_;
    //! Pointer to the opened file <I>inaccessible</I>
    H5_file_ptr file_;
    //! Pointer to the data set vending the view <I>inaccessible</I>
    Data_set_ptr data_set_;
  };

  // Support for streaming non-static streamable members of H5_table_model
  inline
  std::ostream& operator<<(std::ostream& out, H5_table_model const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "H5_table_model:(" << &item << "):{";
    out << '\n' << indent << "  base:" << static_cast<fcs::table::Table_model const&>(item);
    out << '\n' << indent << "  h5_file_path:" << item.h5_file_path_;
    out << '\n' << indent << "  data_set_name:" << item.data_set_name_;
    out << indent << "}\n";
    return out;
  } 

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

} // namespace h5_table
} // namespace fcs
#endif // _FCS_H5_TABLE_H5_TABLE_MODEL_H_
