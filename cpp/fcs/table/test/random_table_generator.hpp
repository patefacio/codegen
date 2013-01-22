/******************************************************************************
 * random_table_generator.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file random_table_generator.hpp
 *
 * \brief Support for creating a table with random data
 * 
 */
#ifndef _FCS_TABLE_TEST_RANDOM_TABLE_GENERATOR_H_
#define _FCS_TABLE_TEST_RANDOM_TABLE_GENERATOR_H_

#include "fcs/table/test/random_cell_generator.hpp"
#include "fcs/table/memory_table_model.hpp"

namespace fcs {
namespace table {
namespace test {

  //! Support for creating a table with random data
  class Random_table_generator 
  {
  public:

    explicit Random_table_generator(
      Index_t num_columns = 10,
      Index_t num_rows = 1000
    ) :
      num_columns_(num_columns),
      num_rows_(num_rows)
    {
    }

  
// custom <Random_table_generator public header section>

    Table_model_ptr create_memory_table_model() {
      Table_shape_t shape;
      Table_header_t header;
      Random_cell_generator generator;
      for(Index_t i(0); i < num_columns_; ++i) {
        Table_cell_type table_cell_type(static_cast<Table_cell_type>(i%(CELL_TYPE_STRING+1)));
        shape.push_back(table_cell_type);
        std::ostringstream cell_type;
        cell_type << 'C' << i << '_' << table_cell_type;
        header.push_back(cell_type.str());
      }

      Table_meta_data meta_data(shape, header);
      Table_model_ptr result(new Memory_table_model(meta_data));
      {
        for(Index_t i(0); i < num_rows_; ++i) {
          Row_contents_ptr row(new Row_contents_t());
          for(Index_t j(0); j < num_columns_; ++j) {
            Table_cell_type table_cell_type(shape[j]);
            Cell_contents_t contents(generator.generate(table_cell_type));
            row->push_back(contents);
          }
          result->add_row(row);
        }
      }
      return result;
    }

// end <Random_table_generator public header section>

  private:
    Index_t num_columns_;
    Index_t num_rows_;
  };

} // namespace test
} // namespace table
} // namespace fcs
#endif // _FCS_TABLE_TEST_RANDOM_TABLE_GENERATOR_H_
