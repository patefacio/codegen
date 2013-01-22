/******************************************************************************
 * h5_random_access_store.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_random_access_store.hpp
 *
 * \brief Wrapper for packet table tailored to parameterized class
 * 
 */
#ifndef _FCS_H5_UTILS_H5_RANDOM_ACCESS_STORE_H_
#define _FCS_H5_UTILS_H5_RANDOM_ACCESS_STORE_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters/integer.hpp>
#include "fcs/utils/file_path.hpp"
#include "H5Cpp.h"
#include "H5File.h"
#include "H5PacketTable.h"
#include <boost/filesystem/path.hpp>
#include <sstream>
#include <exception>
#include <memory>
#include <vector>
#include <string>

namespace fcs {
namespace h5 {
namespace utils {

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

  // Forward typedefs
  typedef std::shared_ptr< H5::H5File > H5_file_ptr;

  //! Wrapper for packet table tailored to parameterized class
  /**

  Stores objects of type TYPE_STORED in an hdf5 data_set for basic random access
  whose hdf5 data_set type (when used for creation) is specified by
  H5_DATA_SET_SPECIFIER.

  */
  template < typename TYPE_STORED,
             typename H5_DATA_SET_SPECIFIER = TYPE_STORED > 
  class H5_random_access_store 
  {
  public:

    // Class typedefs
    typedef std::shared_ptr< FL_PacketTable > FL_PacketTable_ptr;
    typedef std::vector< hid_t > Group_id_list_t;

    H5_random_access_store(
      H5_file_ptr const& file,
      Store_open_type open_type,
      std::string const& group = std::string()
    ) :
      file_(file),
      open_type_(open_type),
      group_(group),
      packet_table_()
    {
      ctor_member_init();
    }

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    H5_file_ptr const& file() const {
      return file_;
    }

    FL_PacketTable_ptr const& packet_table() const {
      return packet_table_;
    }

  
// custom <H5_random_access_store public header section>

    hsize_t size() const {
      return packet_table_->GetPacketCount();
    }

    void get(hsize_t index, TYPE_STORED &result) {
      if(packet_table_->GetPacket(index, &result) < 0) {
        std::ostringstream msg;
        msg << "Failed call to GetPacket";
        throw std::runtime_error(msg.str());
      }
    }

    void append(TYPE_STORED const& additional) {
      if(packet_table_->AppendPacket(const_cast< TYPE_STORED *>(&additional)) < 0) {
        std::ostringstream msg;
        msg << "Failed call to AppendPacket";
        throw std::runtime_error(msg.str());
      }
    }

    inline void make_groups_in_path(std::string const& group_path) {
      hid_t current_group_id(file_->getId());
      Group_id_list_t group_ids;
      {
        boost::filesystem::path path(group_path);
        boost::filesystem::path::iterator it(path.begin());
        boost::filesystem::path::iterator end(path.end());
        ++it;
        for(; it != end; ++it) {
          std::string const& current_group(fcs::utils::full_path(*it));
          if(!H5Lexists(current_group_id, current_group.c_str(), H5P_DEFAULT)) {
            hid_t new_group_id(H5Gcreate(current_group_id, current_group.c_str(),  
                                         H5P_DEFAULT,  H5P_DEFAULT,  H5P_DEFAULT));
            pantheios::log(PANTHEIOS_SEV_DEBUG, "Creating group:", 
                           current_group.c_str(), " result gid:",
                           pantheios::integer(new_group_id));
            if(new_group_id > 0) {
              current_group_id = new_group_id;
            } else {
              std::ostringstream msg;
              msg << "Failed to create group: " << current_group;
              throw std::runtime_error(msg.str());
            }
          } else {
            hid_t existing_group_id(H5Gopen2(current_group_id, current_group.c_str(), H5P_DEFAULT));
            pantheios::log(PANTHEIOS_SEV_DEBUG, "Opening existing group:", 
                           current_group.c_str(), " opened gid:",
                           pantheios::integer(existing_group_id));
            if(existing_group_id > 0) {
              current_group_id = existing_group_id;
            } else {
              std::ostringstream msg;
              msg << "Failed to open group: " << current_group;
              throw std::runtime_error(msg.str());
            }
          }
          group_ids.push_back(current_group_id);
        }
      }

      if(group_ids.size() > 1) {
        Group_id_list_t::const_iterator it(group_ids.begin());
        Group_id_list_t::const_iterator end(group_ids.end());
        for(; it != end; ++it) {
          pantheios::log(PANTHEIOS_SEV_DEBUG, "Closing group:", pantheios::integer(*it));
          H5Gclose(*it);
        }
      }
    }

// end <H5_random_access_store public header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <H5_random_access_store::init>

      std::string const& data_set_name(H5_DATA_SET_SPECIFIER::data_set_name());
      std::string group(group_);
      group += data_set_name;

      switch(open_type_) {
       case OPEN_CREATE: {
         make_groups_in_path(group_);
         packet_table_ = FL_PacketTable_ptr
           (new FL_PacketTable(file_->getId(), 
                               const_cast< char * >(group.c_str()), 
                               H5_DATA_SET_SPECIFIER::compound_data_type_id(), 1<<8, 5));
         break;
       }
       case OPEN_READ: {
         packet_table_ = FL_PacketTable_ptr
           (new FL_PacketTable(file_->getId(), 
                               const_cast< char * >(group.c_str())));
         break;
       }
      }

// end <H5_random_access_store::init>
    }
    H5_file_ptr file_;
    Store_open_type open_type_;
    std::string group_;
    FL_PacketTable_ptr packet_table_;
  };

} // namespace utils
} // namespace h5
} // namespace fcs
#endif // _FCS_H5_UTILS_H5_RANDOM_ACCESS_STORE_H_
