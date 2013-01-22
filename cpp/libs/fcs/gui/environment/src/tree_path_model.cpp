/******************************************************************************
 * tree_path_model.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file tree_path_model.cpp
 *
 * \brief 
 * 
 */

#include "fcs/gui/environment/q_environment.hpp"
#include "fcs/environment.hpp"
#include "fcs/utils/file_path.hpp"
#include "fcs/utils/streamers/streamers.hpp"
#include "fcs/timestamp.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/foreach.hpp>
#include <sstream>
#include <string>
#include <memory>
#include <iostream>


// custom <Tree_path_model pre-namespace custom>
// end <Tree_path_model pre-namespace custom>

namespace fcs {
namespace gui {
namespace environment {

  // Forward class declaration
  class Tree_data_item;
  typedef std::shared_ptr< Tree_data_item > Tree_data_item_ptr;

  // Forward typedefs
  typedef std::vector< Tree_data_item_ptr > Tree_data_item_list_t;
  typedef Tree_data_item* Tree_data_item_dumb_ptr;

  class Tree_data_item 
  {
  public:

    Tree_data_item(
      std::string const& data,
      int row,
      Tree_data_item_dumb_ptr parent = 0,
      std::string const& file_size = std::string(),
      std::string const& last_modified = std::string()
    ) :
      data_(data),
      row_(row),
      parent_(parent),
      file_size_(file_size),
      last_modified_(last_modified),
      children_()
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Tree_data_item const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    std::string const& data() const {
      return data_;
    }

    int row() const {
      return row_;
    }

    Tree_data_item_dumb_ptr parent() const {
      return parent_;
    }

    std::string const& file_size() const {
      return file_size_;
    }

    std::string const& last_modified() const {
      return last_modified_;
    }

  
// custom < public header section>

    Tree_data_item_ptr child(int i) {
      if((i >= 0) and (i < int(children_.size()))) {
        return children_[i];
      } else {
        return Tree_data_item_ptr();
      }
    } 

    int row_count() const {
      return children_.size();
    }

    void add_child(Tree_data_item_ptr const& child) {
      children_.push_back(child);
    }

// end < public header section>

  private:
    std::string const data_;
    int const row_;
    Tree_data_item_dumb_ptr const parent_;
    std::string const file_size_;
    std::string const last_modified_;
    Tree_data_item_list_t children_;
  }; 

  // Support for streaming non-static streamable members of Tree_data_item
  std::ostream& operator<<(std::ostream& out, Tree_data_item const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Tree_data_item:(" << &item << "):{";
    out << '\n' << indent << "  data:" << item.data_;
    out << '\n' << indent << "  row:" << item.row_;
    out << '\n' << indent << "  parent:" << item.parent_;
    out << '\n' << indent << "  file_size:" << item.file_size_;
    out << '\n' << indent << "  last_modified:" << item.last_modified_;
    out << '\n' << indent << "  children:" << item.children_;
    out << indent << "}\n";
    return out;
  } 

  
// custom <Tree_path_model namespace custom>

  void Tree_path_model::ctor_default_init() {
    using namespace fcs::environment;
    using namespace fcs::utils::streamers;
    using namespace boost::filesystem;

    Path_list_map_t path_list_map
      (Environment::get_instance()->path_variable_map());

    root_ = Tree_data_item_ptr(new Tree_data_item("Foo", 0, 0));
    size_t num_env_vars(0);
    BOOST_FOREACH(Path_list_map_t::value_type const& vt, path_list_map) {
      Tree_data_item_ptr env_var_child(
        new Tree_data_item(vt.first, num_env_vars++, root_.get()));
      root_->add_child(env_var_child);
      size_t num_paths(0);
      BOOST_FOREACH(Path_t const& path, vt.second) {
        Tree_data_item_ptr path_child(
          new Tree_data_item(path.string(), num_paths++, env_var_child.get()));        
        env_var_child->add_child(path_child);

        if(is_directory(path)) {
          directory_iterator end_itr; 
          size_t num_files(0);
          for (directory_iterator dir_iter(path); dir_iter != end_itr; ++dir_iter) {
            Path_t file_path(dir_iter->path());
            bool file_is_directory(is_directory(file_path));
            bool file_is_symlink(is_symlink(file_path));
            std::cout << file_path << " " << file_is_symlink << " & " << file_is_directory << std::endl;
            bool read_file_size(!file_is_symlink and !file_is_directory);
            std::string last_write_time_string;
            if(read_file_size) {
              fcs::timestamp::Timestamp_t last_write_timestamp(
                boost::posix_time::from_time_t(last_write_time(file_path)));
              last_write_time_string = to_simple_string(last_write_timestamp);
            }
            Tree_data_item_ptr file_child(
              new Tree_data_item(fcs::utils::basename(file_path),
                                 num_files++, path_child.get(), 
                                 read_file_size? stream_to_string(file_size(file_path)) : std::string(), 
                                 last_write_time_string));
            path_child->add_child(file_child);            
          }
        }
      }
    }
  }

  QModelIndex Tree_path_model::index(int row, int column, const QModelIndex& parent) const {
    if(!hasIndex(row, column, parent)) {
      return QModelIndex();
    }
    Tree_data_item_dumb_ptr parent_item(parent.isValid()? 
                                        static_cast< Tree_data_item_dumb_ptr >(parent.internalPointer()) :
                                        root_.get());
    Tree_data_item_dumb_ptr child_item(parent_item->child(row).get());
    return child_item? createIndex(row, column, child_item) : QModelIndex();
  }

  QModelIndex Tree_path_model::parent(const QModelIndex& child) const {
    if(!child.isValid()) {
      return QModelIndex();
    } else {
      Tree_data_item_dumb_ptr child_item(static_cast< Tree_data_item_dumb_ptr >(child.internalPointer()));
      Tree_data_item_dumb_ptr parent(child_item->parent());
      if(parent and (parent != root_.get())) {
        return createIndex(parent->row(), 0, parent);
      } else {
        return QModelIndex();
      }
    }
  }

  int Tree_path_model::rowCount(const QModelIndex& parent) const {
    if(parent.column() > 0) {
      return 0;
    } else {
      Tree_data_item_dumb_ptr result_item(
        parent.isValid()? static_cast< Tree_data_item_dumb_ptr >(parent.internalPointer()) : root_.get());
      return result_item->row_count();
    }
  }

  int Tree_path_model::columnCount(const QModelIndex&) const {
    return column_count_;
  }

  QVariant Tree_path_model::data(const QModelIndex &index, int role) const {
    if(index.isValid()) {
      if (role == Qt::DisplayRole) {
        Tree_data_item_dumb_ptr item(static_cast< Tree_data_item_dumb_ptr >(index.internalPointer()));
        switch(index.column()) {
         case 0:
            return QVariant(item->data().c_str());
         case 1:
            return QVariant(item->file_size().c_str());
         case 2:
            return QVariant(item->last_modified().c_str());
         default:
            return QVariant("TODO");
        }
      } else if(role == Qt::TextAlignmentRole) {
        switch(index.column()) {
         case 1:
            return QVariant(Qt::AlignRight);
         default:
            return QVariant();
        }
      } else {
        return QVariant();
      }
    } else {
      return QVariant();
    }
  }

  QVariant Tree_path_model::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
      if(section < column_count_) {
        return QVariant(column_headers_[section]);
      }
    }
    return QVariant();
  }

// end <Tree_path_model namespace custom>


  /// Class static variable definitions
  Header_array_t Tree_path_model::column_headers_ = { 
        "Variable/Path/File",
        "Size",
        "Last Modified" 
  };
  size_t Tree_path_model::column_count_(sizeof(Header_array_t)/sizeof(char const*));

  // Default ctor
  Tree_path_model::Tree_path_model() :
    root_(Tree_data_item_ptr()) 
  {
    ctor_default_init();
  }


} // namespace environment
} // namespace gui
} // namespace fcs


