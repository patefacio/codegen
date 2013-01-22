/******************************************************************************
 * table_search.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file table_search.hpp
 *
 * \brief Basic search for rows in which cell matches
 * 
 */
#ifndef _FCS_TABLE_TABLE_SEARCH_H_
#define _FCS_TABLE_TABLE_SEARCH_H_

#include "fcs/table/table.hpp"
#include "fcs/table/table_model.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <memory>
#include <iostream>

namespace fcs {
namespace table {

  // Forward class declaration
  class Table_search;
  typedef std::shared_ptr< Table_search > Table_search_ptr;

  //! Basic search for rows in which cell matches
  class Table_search 
  {
  public:

    Table_search(
      Cell_location_range_t const& search_range,
      Table_model_const_ptr const& target_table,
      Search_functor_t const& search_functor
    ) :
      search_range_(search_range),
      target_table_(target_table),
      search_functor_(search_functor)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Table_search const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Cell_location_range_t const& search_range() const {
      return search_range_;
    }

    Table_model_const_ptr const& target_table() const {
      return target_table_;
    }

    Search_functor_t const& search_functor() const {
      return search_functor_;
    }

  
// custom <Table_search public header section>
// end <Table_search public header section>

  private:
    //! Range for the search <I>read only</I>
    Cell_location_range_t search_range_;
    //! Table to search over the supplied range <I>read only</I>
    Table_model_const_ptr target_table_;
    //! Search functor for finding matches in cells <I>read only</I>
    Search_functor_t search_functor_;
  };

  // Support for streaming non-static streamable members of Table_search
  inline
  std::ostream& operator<<(std::ostream& out, Table_search const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Table_search:(" << &item << "):{";
    out << '\n' << indent << "  search_range:" << item.search_range_;
    out << '\n' << indent << "  search_functor:" << item.search_functor_;
    out << indent << "}\n";
    return out;
  } 

} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TABLE_SEARCH_H_
