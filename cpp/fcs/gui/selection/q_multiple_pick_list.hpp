/******************************************************************************
 * q_multiple_pick_list.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_multiple_pick_list.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_GUI_SELECTION_Q_MULTIPLE_PICK_LIST_H_
#define _FCS_GUI_SELECTION_Q_MULTIPLE_PICK_LIST_H_

#include <QListWidget>
#include <QSplitter>
#include <QWidget>
#include <map>

namespace fcs {
namespace gui {
namespace selection {

  class Q_multiple_pick_list :
    public QWidget 
  {
    Q_OBJECT

  public:

    // Class typedefs
    typedef std::map< QString, bool > Selection_map_t;

    Q_multiple_pick_list(
      QWidget * parent,
      Selection_map_t const& selection_map
    );

    ~Q_multiple_pick_list();

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Selection_map_t const& selection_map() const;

  private:

  
// custom <Q_multiple_pick_list private header section>

    void user_chose_item(QListWidgetItem *);
    void user_rejected_item(QListWidgetItem *);

// end <Q_multiple_pick_list private header section>

    //! Initialize the instance
    void ctor_member_init();

      
// custom <Q_multiple_pick_list::slots>

  private slots:

    void choose_from_item_changed(QListWidgetItem *);
    void chosen_item_changed(QListWidgetItem *);

  private:
    void find_and_remove_chosen_item(QListWidgetItem * item);

// end <Q_multiple_pick_list::slots>

    //! Map of selection strings to corresponding values <I>read only</I>
    Selection_map_t selection_map_;
    //! Splitter for the (Choose From) (Chosen) listboxes <I>inaccessible</I>
    QSplitter * splitter_;
    //! List of items to choose from <I>inaccessible</I>
    QListWidget * choose_from_list_;
    //! List of chosen items <I>inaccessible</I>
    QListWidget * chosen_list_;
  };

} // namespace selection
} // namespace gui
} // namespace fcs
#endif // _FCS_GUI_SELECTION_Q_MULTIPLE_PICK_LIST_H_
