/******************************************************************************
 * q_search_request.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file q_search_request.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_GUI_SEARCH_Q_SEARCH_REQUEST_H_
#define _FCS_GUI_SEARCH_Q_SEARCH_REQUEST_H_

#include <QTableWidget>
#include <QWidget>

namespace fcs {
namespace gui {
namespace search {

  class Q_search_request :
    public QWidget 
  {
    Q_OBJECT

  public:

    explicit Q_search_request(
      QWidget * parent
    ) :
      QWidget(parent),
      variable_list_table_(new QTableWidget())
    {
    }

  
// custom <Q_search_request public header section>
// end <Q_search_request public header section>

  private:

  
// custom <Q_search_request private header section>
// end <Q_search_request private header section>

      
// custom <Q_search_request::slots>
// end <Q_search_request::slots>

    //! List of variables and values <I>inaccessible</I>
    QTableWidget * variable_list_table_;
  };

} // namespace search
} // namespace gui
} // namespace fcs
#endif // _FCS_GUI_SEARCH_Q_SEARCH_REQUEST_H_
