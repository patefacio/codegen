/******************************************************************************
 * h5_meta_data.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_meta_data.hpp
 *
 * \brief Basic meta_data from hdf5 file
 * 
 */
#ifndef _FCS_H5_H5_META_DATA_H_
#define _FCS_H5_H5_META_DATA_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters/character.hpp>
#include <pantheios/inserters/integer.hpp>
#include "fcs/h5/h5_api.hpp"
#include "fcs/utils/streamers/vector.hpp"
#include "fcs/utils/streamers/map.hpp"
#include "H5public.h"
#include "H5PacketTable.h"
#include "H5Cpp.h"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/operators.hpp>
#include <exception>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iso646.h>

namespace fcs {
namespace h5 {


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

  //! Basic meta_data from hdf5 file
  class H5_meta_data 
  {
  public:

    // Nested classes
    //! Metadata of data_set member
      /**
      Metadata of the data_set member 
      */
    class Data_set_member_detail :
      public boost::equality_comparable< Data_set_member_detail > 
    {
    public:

      Data_set_member_detail() :
        parent_(Data_set_ptr()),
        name_(std::string()),
        h5_class_(H5T_class_t()),
        data_type_(hid_t()),
        offset_(hsize_t()),
        index_(hsize_t()),
        size_(0),
        cpp_type_(CPP_TYPE_UNMAPPED) 
      {
      }

      bool operator==(Data_set_member_detail const& rhs) const {
          return
              ((this==&rhs) or (
              (parent_ == rhs.parent_) and
              (name_ == rhs.name_) and
              (h5_class_ == rhs.h5_class_) and
              (data_type_ == rhs.data_type_) and
              (offset_ == rhs.offset_) and
              (index_ == rhs.index_) and
              (size_ == rhs.size_) and
              (cpp_type_ == rhs.cpp_type_)));
      }

      friend std::ostream& operator<<(std::ostream& out, Data_set_member_detail const& item);

      //! Data_set holding member <I>open</I>
      Data_set_ptr parent_;
      std::string name_;
      H5T_class_t h5_class_;
      hid_t data_type_;
      hsize_t offset_;
      hsize_t index_;
      //! Size of member type in bytes <I>open</I>
      size_t size_;
      //! Mapping to cpp type <I>open</I>
      Cpp_type cpp_type_;
    };
    typedef std::vector< Data_set_member_detail > Data_set_member_detail_list_t;

      /**
      Metadata of data_set 
      */
    class Data_set_detail 
    {
    public:

      Data_set_detail() :
        name_(std::string()),
        rank_(int()),
        dimensions_(Dimensions_t()),
        member_detail_(Data_set_member_detail_list_t()) 
      {
      }

      friend std::ostream& operator<<(std::ostream& out, Data_set_detail const& item);

      std::string name_;
      int rank_;
      Dimensions_t dimensions_;
      Data_set_member_detail_list_t member_detail_;
    };

    // Class typedefs
    typedef std::map< std::string, Data_set_detail > Data_set_detail_map_t;
    typedef std::map< hid_t, boost::filesystem::path > Object_id_to_path_t;

    explicit H5_meta_data(
      boost::filesystem::path const& file_path
    ) :
      file_path_(file_path),
      file_(),
      file_hid_(),
      root_group_hid_(),
      data_set_detail_map_(),
      log_stream_(),
      current_path_(),
      object_id_to_path_()
    {
      ctor_member_init();
    }

    friend std::ostream& operator<<(std::ostream& out, H5_meta_data const& item);

  public:
  
// custom <H5_meta_data public header section>

    void write_csv(std::string const& data_set_name) const {
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Writing csv for data_set_name:", data_set_name);
    }

    Data_set_detail get_data_set_detail(std::string const& data_set_name) const {
      Data_set_detail_map_t::const_iterator found(data_set_detail_map_.find(data_set_name));
      if(found != data_set_detail_map_.end()) {
        return found->second;
      } else {
        std::ostringstream msg;
        msg << "Could not find data_set_name: " << data_set_name << " in " << *this;
        throw std::runtime_error(msg.str());
      }
    }

    static inline void log_meta_data_load(bool value) {
      get_set_log_meta_data<bool>(&value);
    }

    static inline bool log_meta_data_load() {
      return get_set_log_meta_data<bool>(0);
    }

// end <H5_meta_data public header section>

  private:

  
// custom <H5_meta_data private header section>

    void dump_type_details_class_type(hid_t id, hid_t class_type, std::ostream& out) {
      char const* output = "UNKNOWN CLASS";
      switch(class_type) {
       case H5T_TIME:
          output = "H5T_TIME";
          break;
       case H5T_INTEGER:
          output = "H5T_INTEGER";
          break;
       case H5T_FLOAT:
          output = "H5T_FLOAT";
          break;
       case H5T_STRING:
          output = "H5T_STRING";
          break;
       case H5T_BITFIELD:
          output = "H5T_BITFIELD";
          break;
       case H5T_OPAQUE:
          output = "H5T_OPAQUE";
          break;
       case H5T_COMPOUND:
          output = "H5T_COMPOUND";
          break;
       case H5T_REFERENCE:
          output = "H5T_REFERENCE";
          break;
       case H5T_ENUM:
          output = "H5T_ENUM";
          break;
       case H5T_VLEN:
          output = "H5T_VLEN";
          break;
       case H5T_ARRAY:
          output = "H5T_ARRAY";
          break;
       default:
          break;
      }
      out << "ClassOf(" << id << ") = " << output << std::endl;
    }

    void dump_type_details(hid_t id, std::ostream& out) {
      hid_t class_type(H5Tget_class(id));
      dump_type_details_class_type(id, class_type, out);
      size_t type_size(H5Tget_size(id));
      out << " size:" << type_size;
      if(H5T_COMPOUND == class_type) {
        int nmembers(H5Tget_nmembers(id));
        out << " members:" << nmembers;
      }
      out << std::endl;
    }

    typedef boost::tuple< size_t, Cpp_type > Cpp_type_mapping_t;

    inline Cpp_type_mapping_t get_cpp_type_mapping(hid_t id) {
      Cpp_type result_cpp_type(CPP_TYPE_UNMAPPED);
      hid_t class_type(H5Tget_class(id));
      size_t type_size(H5Tget_size(id));
      switch(class_type) {
       case H5T_TIME:
          break;
       case H5T_INTEGER:
          if(type_size <= 4) {
            result_cpp_type = CPP_TYPE_INT32;
          } else {
            result_cpp_type = CPP_TYPE_INT64;
          }
          break;
       case H5T_FLOAT:
          result_cpp_type = CPP_TYPE_DOUBLE;
          break;
       case H5T_STRING:
          result_cpp_type = CPP_TYPE_STRING;
          break;
       case H5T_BITFIELD:
          break;
       case H5T_OPAQUE:
          break;
       case H5T_COMPOUND:
          break;
       case H5T_REFERENCE:
          break;
       case H5T_ENUM:
          break;
       case H5T_VLEN:
          break;
       case H5T_ARRAY:
          break;
       default:
          break;
      }
      return boost::make_tuple(type_size, result_cpp_type);
    }

    static herr_t process_group(hid_t group, char const* name, void * instance) {
      H5_meta_data* meta_data(reinterpret_cast<H5_meta_data*>(instance));
      return meta_data->process_group(group, name);
    }

    herr_t process_group(hid_t group, char const* name) {
      std::ostream &out(log_stream_);
      current_path_ /= name;
      object_id_to_path_[group] = current_path_;
      if(log_meta_data_load()) {
        out << "Group:" << group << " name:" << name << std::endl;
      }
      H5O_info_t oinfo;
      if(H5Oget_info_by_name(group, name, &oinfo, H5P_DEFAULT) < 0) {
        std::ostringstream msg;
        msg << "Unable to get object info by name:" << name;
        throw std::runtime_error(msg.str());
      }

      switch(oinfo.type) {
       case H5O_TYPE_UNKNOWN: {
         std::ostringstream msg;
         msg << "Object info type unknown on:" << name;
         throw std::runtime_error(msg.str());
         break;
       }
       case H5O_TYPE_DATASET: {
         process_data_set(group, name, oinfo);
         break;
       }
       case H5O_TYPE_GROUP: {
         if(log_meta_data_load()) {
           out << "Processing sub-group:" << name << std::endl;
         }
         H5Giterate(group, name, 0, process_group, this);             
         break;
       }
       case H5O_TYPE_NAMED_DATATYPE: {
         if(log_meta_data_load()) {
           out << name << " is Named Datatype";
         }
         break;
       }
       default: {
         out << name << " is UNKNOWN-ERROR";
         break;
       }
      }

      current_path_ = current_path_.parent_path();
      return 0;
    }

    void process_data_set(hid_t group_id, char const* name, H5O_info_t const& oinfo) {
      Data_set_ptr data_set(new H5::DataSet(file_->openDataSet(current_path_.string().c_str())));
      H5::DataSpace dataspace(data_set->getSpace());
      Data_set_detail & detail = data_set_detail_map_[current_path_.string()];
      detail.name_ = name;
      detail.rank_ = dataspace.getSimpleExtentNdims();

      if(detail.rank_) {
        detail.dimensions_.insert(detail.dimensions_.begin(), detail.rank_, 0);
        int ndims(dataspace.getSimpleExtentDims(&detail.dimensions_[0], NULL));
        static_cast<void>(ndims);
        assert(ndims == detail.rank_);
        H5T_class_t type_class(data_set->getTypeClass());
        if(log_meta_data_load()) {
          dump_type_details(data_set->getDataType().getId(), log_stream_);
        }
        if(H5T_COMPOUND == type_class) {
          H5::CompType comp_type(*data_set);
          int end(comp_type.getNmembers());
          detail.member_detail_.insert(detail.member_detail_.begin(), end, Data_set_member_detail());
          for(int i(0); i<end; ++i) {
            Data_set_member_detail &member_detail(detail.member_detail_[i]);
            std::string member_name(comp_type.getMemberName(i));
            H5::DataType data_type(comp_type.getMemberDataType(i));
            member_detail.parent_ = data_set;
            member_detail.name_ = member_name;
            member_detail.h5_class_ = data_type.getClass();
            member_detail.data_type_ = data_type.getId();
            member_detail.index_ = i;
            member_detail.offset_ = comp_type.getMemberOffset(i);
            Cpp_type_mapping_t type_mapping(get_cpp_type_mapping(member_detail.data_type_));
            member_detail.size_ = boost::get<0>(type_mapping);
            member_detail.cpp_type_ = boost::get<1>(type_mapping);

            if(log_meta_data_load()) {
              log_stream_ << "The CompType: " << member_name << std::endl;
              dump_type_details(member_detail.data_type_, log_stream_);
            }

          }
        } else {
          if(log_meta_data_load()) {
            log_stream_ << "vvvvv NEED TO HANDLE type_class in "
                        << file_path_ << ':' << name << " vvvvvv\n";
          }
        }
      }
    }

    template<typename T>
    static inline bool get_set_log_meta_data(T *value = 0) {
      static T value_s = T();
      if(value) {
        value_s = *value;
      }
      return value_s;
    }

// end <H5_meta_data private header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <H5_meta_data::init>

      namespace fs = boost::filesystem;
      try {
        file_ = H5_file_ptr(new H5::H5File(file_path_.string().c_str(), H5F_ACC_RDONLY));
        if(log_meta_data_load()) {
          pantheios::log(PANTHEIOS_SEV_DEBUG, 
                         "Is hdf5:",
                         pantheios::character(H5::H5File::isHdf5(file_path_.string().c_str())?'T':'F'),
                         " Filename:", file_->getFileName().c_str(),
                         " FreeSpace:", pantheios::integer(file_->getFreeSpace())
            );
        }
        if(fs::exists(file_path_)) {
          file_hid_ = H5Fopen(file_path_.string().c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
          if(file_hid_) {
            if((root_group_hid_ = H5Gopen2(file_hid_, "/", H5P_DEFAULT)) < 0) {
              std::ostringstream msg;
              msg << "Could not open root group \"/\" on file:" << file_path_;
              throw std::runtime_error(msg.str());
            } else {
              current_path_ = boost::filesystem::path("/");
              H5Giterate(root_group_hid_, "/", 0, process_group, this);
            }
            if(log_meta_data_load()) {
              log_stream_ << "Successfully Opened and Processed:" << file_path_ << std::endl;
            }
          } else {
            std::ostringstream msg;
            msg << "Could not open hdf5 file:" << file_path_ << " file does not exist";
            throw std::runtime_error(msg.str());
          }
        } else {
          std::ostringstream msg;
          msg << "Could not open file - does not exist:" << file_path_;
          throw std::runtime_error(msg.str());
        }
      } catch(H5::Exception const& excp) {
        std::ostringstream msg;
        msg << "Could not open init h5_meta_data:" << file_path_ 
            << "\n\tdetail:" << excp.getDetailMsg();
        throw std::runtime_error(msg.str());
      }

      if(log_meta_data_load()) {
        log_stream_ << "\n" << *this;
        pantheios::log(PANTHEIOS_SEV_DEBUG, file_path_.leaf().c_str(),
                       " LOG_STREAM_CONTENTS\n", log_stream_.str().c_str());
        static std::string const empty;
        log_stream_.str(empty);
      }

// end <H5_meta_data::init>
    }
  private:
    //! Path to an hdf5 file <I>inaccessible</I>
    boost::filesystem::path file_path_;
    //! The file wrapper <I>inaccessible</I>
    H5_file_ptr file_;
    //! The id for the opened file <I>inaccessible</I>
    hid_t file_hid_;
    //! The id for the group "/" <I>inaccessible</I>
    hid_t root_group_hid_;
    //! Map of data_set location to its details <I>inaccessible</I>
    Data_set_detail_map_t data_set_detail_map_;
    //! For internal logging <I>inaccessible</I>
    std::ostringstream log_stream_;
    //! Path to group currently being processed on iteration <I>inaccessible</I>
    boost::filesystem::path current_path_;
    //! Map of object id to path of object <I>inaccessible</I>
    Object_id_to_path_t object_id_to_path_;
  };

  // Support for streaming non-static streamable members of H5_meta_data
  inline
  std::ostream& operator<<(std::ostream& out, H5_meta_data const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "H5_meta_data:(" << &item << "):{";
    out << '\n' << indent << "  file_path:" << item.file_path_;
    out << '\n' << indent << "  file_hid:" << item.file_hid_;
    out << '\n' << indent << "  root_group_hid:" << item.root_group_hid_;
    out << '\n' << indent << "  data_set_detail_map:" << item.data_set_detail_map_;
    out << '\n' << indent << "  current_path:" << item.current_path_;
    out << '\n' << indent << "  object_id_to_path:" << item.object_id_to_path_;
    out << indent << "}\n";
    return out;
  } 

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

  // Nested class Data_set_member_detail streamer
  // Support for streaming non-static streamable members of Data_set_member_detail
  inline
  std::ostream& operator<<(std::ostream& out, H5_meta_data::Data_set_member_detail const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Data_set_member_detail:(" << &item << "):{";
    out << '\n' << indent << "  name:" << item.name_;
    out << '\n' << indent << "  h5_class:" << item.h5_class_;
    out << '\n' << indent << "  data_type:" << item.data_type_;
    out << '\n' << indent << "  offset:" << item.offset_;
    out << '\n' << indent << "  index:" << item.index_;
    out << '\n' << indent << "  size:" << item.size_;
    out << '\n' << indent << "  cpp_type:" << item.cpp_type_;
    out << indent << "}\n";
    return out;
  } 
  // Nested class Data_set_detail streamer
  // Support for streaming non-static streamable members of Data_set_detail
  inline
  std::ostream& operator<<(std::ostream& out, H5_meta_data::Data_set_detail const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Data_set_detail:(" << &item << "):{";
    out << '\n' << indent << "  name:" << item.name_;
    out << '\n' << indent << "  rank:" << item.rank_;
    out << '\n' << indent << "  dimensions:" << item.dimensions_;
    out << '\n' << indent << "  member_detail:" << item.member_detail_;
    out << indent << "}\n";
    return out;
  } 
} // namespace h5
} // namespace fcs
#endif // _FCS_H5_H5_META_DATA_H_
