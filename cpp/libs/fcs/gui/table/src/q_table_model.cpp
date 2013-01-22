/******************************************************************************
 * q_table_model.cpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_table_model.cpp
 *
 * \brief 
 * 
 */

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "fcs/gui/table/q_table_model.hpp"
#include <boost/foreach.hpp>
#include <sstream>


// custom <Q_table_model pre-namespace custom>
// end <Q_table_model pre-namespace custom>

namespace fcs {
namespace gui {
namespace table {

  
// custom <Q_table_model namespace custom>

  QVariant Q_table_model::data(const QModelIndex& index, int role) const {
    QVariant result;

    switch(role) {
     case Qt::DisplayRole: {
       fcs::table::Cell_contents_t cell_contents;
       table_model_->read_cell(index.row(), index.column(), cell_contents);
       if(item_data_role_handler_ and
          item_data_role_handler_->test_handler_function_mask(Q_item_data_role_handler::ROLE_OVERRIDE_DATA_FUNCTION)) {
         result = item_data_role_handler_->override_data(index, role, cell_contents);
       } else {
         std::ostringstream contents;
         contents << cell_contents;
         result = QVariant(contents.str().c_str());
       }

       break;
     }
     case Qt::DecorationRole:
     case Qt::EditRole:
     case Qt::ToolTipRole:
     case Qt::StatusTipRole:
     case Qt::WhatsThisRole: {
       break;
     }

     case Qt::DecorationPropertyRole:
     case Qt::FontRole:
     case Qt::TextAlignmentRole:
     case Qt::BackgroundColorRole:
     case Qt::ForegroundRole:
     case Qt::CheckStateRole: {
       if(item_data_role_handler_ and
          item_data_role_handler_->test_handler_function_mask(Q_item_data_role_handler::ROLE_FORMAT_DATA_FUNCTION)) {
         fcs::table::Cell_contents_t cell_contents;
         table_model_->read_cell(index.row(), index.column(), cell_contents);
         result = item_data_role_handler_->format(index, role, cell_contents);
       }
       break;
     }

     case Qt::AccessibleTextRole:
     case Qt::AccessibleDescriptionRole:
     case Qt::SizeHintRole:
     case Qt::DisplayPropertyRole:
     case Qt::ToolTipPropertyRole:
     case Qt::StatusTipPropertyRole:
     case Qt::WhatsThisPropertyRole:
     case Qt::UserRole: {
       break;
     }
    }

    if(log_data_access_) {
      char *cell_data(result.toString().toLatin1().data());
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Read cell:(",
                     pantheios::integer(index.row()), pantheios::character(','),
                     pantheios::integer(index.column()), ") with value:", 
                     cell_data, " and role:", pantheios::integer(role));
    }

    return result;
  }

  QVariant Q_table_model::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if(section >= 0) {
      switch(orientation) {
       case Qt::Horizontal: {
        using namespace fcs::table;
        Table_meta_data const& meta_data(table_model_->meta_data());
        Table_header_t const& header(meta_data.header());
        if(size_t(section) < header.size()) {
          return QVariant(header[section].c_str());
        }
        break;
       }
       case Qt::Vertical: {
         return QVariant(section);
         break;
       }
      }
    }
    return QVariant();
  }

// end <Q_table_model namespace custom>


  // Member init ctor
  Q_table_model::Q_table_model(
    QObject * parent,
    fcs::table::Table_model_const_ptr const& table_model,
    Q_item_data_role_handler_ptr const& item_data_role_handler
  ) :
    QAbstractTableModel(parent),
    table_model_(table_model),
    item_data_role_handler_(item_data_role_handler),
    log_data_access_(false)
  {
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Q_table_model(", 
                   pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                   pantheios::character(')'));
    ctor_member_init();
  }


  Q_table_model::~Q_table_model() {
    pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Destroyed Q_table_model(", 
                   pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                   pantheios::character(')'));
  
// custom <Q_table_model::~Q_table_model>
// end <Q_table_model::~Q_table_model>
  }


  void Q_table_model::ctor_member_init() {
    
// custom <Q_table_model::init>
// end <Q_table_model::init>
  }


} // namespace table
} // namespace gui
} // namespace fcs


