/******************************************************************************
 * q_multiple_pick_list.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_multiple_pick_list.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "fcs/gui/selection/q_multiple_pick_list.hpp"
#include <QToolBar>
#include <QVBoxLayout>
#include <boost/foreach.hpp>


// custom <Q_multiple_pick_list pre-namespace custom>

#include <QAction>

// end <Q_multiple_pick_list pre-namespace custom>

namespace fcs {
namespace gui {
namespace selection {

  
// custom <Q_multiple_pick_list namespace custom>

  void Q_multiple_pick_list::user_chose_item(QListWidgetItem * item) {
    // WARNING: Cant leave sorting enabled on all the time due to crashes in
    // QListModel::ensureSorted (it does not ensure start > stop)
    chosen_list_->setSortingEnabled(true);    
    chosen_list_->addItem(new QListWidgetItem(*item));
    chosen_list_->setSortingEnabled(false);    
    Selection_map_t::iterator found(selection_map_.find(item->data(Qt::DisplayRole).toString()));
    if(found == selection_map_.end()) {
      found->second = true;
    }
  }

  void Q_multiple_pick_list::find_and_remove_chosen_item(QListWidgetItem * item) {
    QString item_text(item->data(Qt::DisplayRole).toString());
    QList< QListWidgetItem * > foundItems(chosen_list_->findItems(item_text, Qt::MatchExactly));
    if(1 == foundItems.size()) {
      assert(1 == foundItems.size());
      QListWidgetItem *foundItem(foundItems.at(0));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Found item to remove:",
                     item->data(Qt::DisplayRole).toString().toLatin1().constData(),
                     " in list of size:", pantheios::integer(chosen_list_->count()));
      int row(chosen_list_->row(foundItem));
      chosen_list_->takeItem(row);
      delete foundItem;
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Size after removal:", pantheios::integer(chosen_list_->count()));
    }
  }

  void Q_multiple_pick_list::user_rejected_item(QListWidgetItem * item) {
    assert(Qt::Unchecked == item->data(Qt::CheckStateRole));
    Selection_map_t::iterator found(selection_map_.find(item->data(Qt::DisplayRole).toString()));    
    if(found != selection_map_.end()) {
      found->second = false;
    }
  }

  void Q_multiple_pick_list::choose_from_item_changed(QListWidgetItem *item) {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "Choose_from_item_changed:",
                   item->data(Qt::DisplayRole).toString().toLatin1().constData(),
                   " check state:",
                   static_cast< char const * > ((Qt::Checked == item->data(Qt::CheckStateRole))? "True" : "False"));

    assert(Qt::PartiallyChecked != item->data(Qt::CheckStateRole));
    if(Qt::Checked == item->data(Qt::CheckStateRole)) {
      user_chose_item(item);
    } else {
      user_rejected_item(item);
      find_and_remove_chosen_item(item);
    }
  }

  void Q_multiple_pick_list::chosen_item_changed(QListWidgetItem *item) {
    pantheios::log(PANTHEIOS_SEV_DEBUG, "Choosen_item_changed:",
                   item->data(Qt::DisplayRole).toString().toLatin1().constData(),
                   " check state:",
                   static_cast< char const * > ((Qt::Checked == item->data(Qt::CheckStateRole))? "True" : "False"));

    assert(Qt::Unchecked == item->data(Qt::CheckStateRole));

    QString item_text(item->data(Qt::DisplayRole).toString());
    QList< QListWidgetItem * > foundItems(choose_from_list_->findItems(item_text, Qt::MatchExactly));
    assert(1 == foundItems.size());
    if(1 == foundItems.size()) {
      QListWidgetItem *foundItem(foundItems.at(0));
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Found choose from item:",
                     item->data(Qt::DisplayRole).toString().toLatin1().constData(),
                     " in list of size:", pantheios::integer(choose_from_list_->count()));
      foundItem->setData(Qt::CheckStateRole, item->data(Qt::CheckStateRole));
    }

    pantheios::log(PANTHEIOS_SEV_DEBUG, "Chosen_item_changed: Complete");
  }

// end <Q_multiple_pick_list namespace custom>


  // Member init ctor
  Q_multiple_pick_list::Q_multiple_pick_list(
    QWidget * parent,
    Selection_map_t const& selection_map
  ) :
    QWidget(parent),
    selection_map_(selection_map),
    splitter_(new QSplitter(this)),
    choose_from_list_(new QListWidget()),
    chosen_list_(new QListWidget())
  {
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Q_multiple_pick_list(", 
                   pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                   pantheios::character(')'));
    ctor_member_init();
  }


  Q_multiple_pick_list::~Q_multiple_pick_list() {
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Destroyed Q_multiple_pick_list(", 
                   pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                   pantheios::character(')'));
  
// custom <Q_multiple_pick_list::~Q_multiple_pick_list>
// end <Q_multiple_pick_list::~Q_multiple_pick_list>
  }

  Q_multiple_pick_list::Selection_map_t const& Q_multiple_pick_list::selection_map() const {
    return selection_map_;
  }

  void Q_multiple_pick_list::ctor_member_init() {
    
// custom <Q_multiple_pick_list::init>

    pantheios::log(PANTHEIOS_SEV_DEBUG, "Q_multiple_pick_list ctor");

    choose_from_list_->setSortingEnabled(true);    
    choose_from_list_->setSelectionMode(QAbstractItemView::ExtendedSelection);

    BOOST_FOREACH(Selection_map_t::value_type const& value_type, selection_map_) {
      choose_from_list_->addItem(value_type.first);
      QListWidgetItem *current(choose_from_list_->item(choose_from_list_->count()-1));
      bool is_chosen(value_type.second);
      current->setCheckState(is_chosen? Qt::Checked:Qt::Unchecked);
      if(is_chosen) {
        user_chose_item(current);
      }
    }

    splitter_->addWidget(choose_from_list_);
    splitter_->addWidget(chosen_list_);
    splitter_->setAutoFillBackground(true);
    splitter_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter_->setFocusPolicy(Qt::StrongFocus);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QToolBar *toolbar(new QToolBar(tr("Goo")));
    QPalette palette(toolbar->palette());
    palette.setColor(QPalette::Background, Qt::blue);
    toolbar->setPalette(palette);
    QAction action(QString("boo"), 0);
//    action.setPalette(palette);
//    toolbar->addAction(action);
    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(splitter_);
    setLayout(mainLayout);

    connect(choose_from_list_, SIGNAL(itemChanged(QListWidgetItem *)),
            this, SLOT(choose_from_item_changed(QListWidgetItem *)));

    connect(chosen_list_, SIGNAL(itemChanged(QListWidgetItem *)),
            this, SLOT(chosen_item_changed(QListWidgetItem *)));

// end <Q_multiple_pick_list::init>
  }


} // namespace selection
} // namespace gui
} // namespace fcs


