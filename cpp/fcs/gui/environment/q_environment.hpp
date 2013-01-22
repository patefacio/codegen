/******************************************************************************
 * q_environment.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_environment.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_GUI_ENVIRONMENT_Q_ENVIRONMENT_H_
#define _FCS_GUI_ENVIRONMENT_Q_ENVIRONMENT_H_

#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <QSplitter>
#include <QTableWidget>
#include <QTreeView>
#include <QWidget>
#include <memory>
#include <iostream>

namespace fcs {
namespace gui {
namespace environment {


  // Forward typedefs
  typedef char const* Header_array_t[3];
  class Tree_data_item;
  typedef std::shared_ptr< Tree_data_item > Tree_data_item_ptr;

  class Tree_path_model :
    public QAbstractItemModel 
  {
    Q_OBJECT

  public:

    Tree_path_model();

  
// custom <Tree_path_model public header section>

    virtual QModelIndex index(int, int, const QModelIndex&) const;
    virtual QModelIndex parent(const QModelIndex&) const;
    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

// end <Tree_path_model public header section>

  private:

    //! Initialize the instance
    void ctor_default_init();

      
// custom <Tree_path_model::slots>
// end <Tree_path_model::slots>

    Tree_data_item_ptr root_;
    static Header_array_t column_headers_;
    static size_t column_count_;
  };

  class Q_environment :
    public QWidget 
  {
    Q_OBJECT

  public:

    explicit Q_environment(
      QWidget * parent
    ) :
      QWidget(parent),
      variable_list_table_(new QTableWidget()),
      splitter_(new QSplitter(this)),
      tree_path_model_(new Tree_path_model()),
      tree_path_view_(new QTreeView()),
      path_splitter_(new QSplitter(Qt::Vertical)),
      problem_table_(new QTableWidget())
    {
      ctor_member_init();
    }

  
// custom <Q_environment public header section>
// end <Q_environment public header section>

  private:

  
// custom <Q_environment private header section>

    void populate_variable_list();
    void populate_parsed_paths();
    void populate_problem_table();

// end <Q_environment private header section>

    //! Initialize the instance
    void ctor_member_init();

      
// custom <Q_environment::slots>
// end <Q_environment::slots>

    //! List of variables and values <I>inaccessible</I>
    QTableWidget * variable_list_table_;
    //! Main variables and the paths <I>inaccessible</I>
    QSplitter * splitter_;
    //! Model for paths parsed from path variables stored in tree <I>inaccessible</I>
    Tree_path_model * tree_path_model_;
    //! Tree view for the parsed paths <I>inaccessible</I>
    QTreeView * tree_path_view_;
    //! Horizontal splitter dividing parsed paths (top) and potential problems <I>inaccessible</I>
    QSplitter * path_splitter_;
    //! List of paths that could be a problem due to duplicates <I>inaccessible</I>
    QTableWidget * problem_table_;
  };

} // namespace environment
} // namespace gui
} // namespace fcs
#endif // _FCS_GUI_ENVIRONMENT_Q_ENVIRONMENT_H_
