/******************************************************************************
 * h5_data_model.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file h5_data_model.hpp
 *
 * \brief Data model associated with single HDF5 File
 * 
 */
#ifndef _FCS_H5_DATA_MODEL_H5_DATA_MODEL_H_
#define _FCS_H5_DATA_MODEL_H5_DATA_MODEL_H_

#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include <string>

// Forward class declarations
namespace fcs { namespace h5 { namespace data_model {  class Link_properties;  } } }
namespace fcs { namespace h5 { namespace data_model {  class Node_properties;  } } }

namespace fcs {
namespace h5 {
namespace data_model {


  class Link_properties 
  {
  public:

    explicit Link_properties(
      std::string const& name
    ) :
      name_(name)
    {
    }

    Link_properties() :
      name_() 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Link_properties const& item);

  private:
    std::string name_;
  };

  // Support for streaming non-static streamable members of Link_properties
  inline
  std::ostream& operator<<(std::ostream& out, Link_properties const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Link_properties:(" << &item << "):{";
    out << '\n' << indent << "  name:" << item.name_;
    out << indent << "}\n";
    return out;
  } 


  class Node_properties 
  {
  public:

    explicit Node_properties(
      std::string const& name
    ) :
      name_(name)
    {
    }

    Node_properties() :
      name_() 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Node_properties const& item);

    std::string name_;
  };

  // Support for streaming non-static streamable members of Node_properties
  inline
  std::ostream& operator<<(std::ostream& out, Node_properties const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Node_properties:(" << &item << "):{";
    out << '\n' << indent << "  name:" << item.name_;
    out << indent << "}\n";
    return out;
  } 

  // Forward typedefs
  typedef boost::adjacency_list< 
    boost::vecS,              // Node storage type
    boost::listS,             // Edge storage type
    boost::directedS,         // directed vs undirected
    Node_properties,          // Vertices are nodes
    Link_properties           // Edges are hdf5 links
  > Data_model_graph_t;

  //! Data model associated with single HDF5 File
  /**
  The structure of the data model of an hdf5 file.  Contains the tree structure
  of Groups, Datasets, Dataspaces, Datatypes, Attributes, PropertyLists and
  Links. 
  */
  class H5_data_model 
  {
  public:

    H5_data_model() :
      data_model_() 
    {
      ctor_default_init();
    }

    friend std::ostream& operator<<(std::ostream& out, H5_data_model const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Data_model_graph_t const& data_model() const {
      return data_model_;
    }

  
// custom <H5_data_model public header section>
// end <H5_data_model public header section>

  private:

    //! Initialize the instance
    inline void ctor_member_init() {
      
// custom <H5_data_model::init>

      data_model_ = Data_model_graph_t(5);

      using namespace boost;

      add_edge(vertex(0, data_model_), vertex(1, data_model_), Link_properties("joe"), data_model_);
      add_edge(vertex(1, data_model_), vertex(2, data_model_), Link_properties("curly"), data_model_);
      add_edge(vertex(1, data_model_), vertex(3, data_model_), Link_properties("dick"), data_model_);
      add_edge(vertex(2, data_model_), vertex(4, data_model_), Link_properties("tom"), data_model_);
      add_edge(vertex(3, data_model_), vertex(4, data_model_), Link_properties("harry"), data_model_);

      std::cout << *this;

// end <H5_data_model::init>
    }

    //! Initialize the instance
    inline void ctor_default_init() {
      
// custom <H5_data_model::ctor_default_init>

      data_model_ = Data_model_graph_t(5);

      using namespace boost;

      add_edge(vertex(0, data_model_), vertex(1, data_model_), Link_properties("joe"), data_model_);
      add_edge(vertex(1, data_model_), vertex(2, data_model_), Link_properties("curly"), data_model_);
      add_edge(vertex(1, data_model_), vertex(3, data_model_), Link_properties("dick"), data_model_);
      add_edge(vertex(2, data_model_), vertex(4, data_model_), Link_properties("tom"), data_model_);
      add_edge(vertex(3, data_model_), vertex(4, data_model_), Link_properties("harry"), data_model_);

      Node_properties & node(data_model_[vertex(0, data_model_)]);
      node.name_ = "Node Man!!";

      Node_properties & node_g(data_model_[vertex(1, data_model_)]);
      node_g.name_ = "Node Girl!!";

// end <H5_data_model::ctor_default_init>
    }
    Data_model_graph_t data_model_;
  };

  // Support for streaming non-static streamable members of H5_data_model
  inline
  std::ostream& operator<<(std::ostream& out, H5_data_model const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "H5_data_model:(" << &item << "):{";
  
// custom <data_model custom streamer>

    out << '\n' << indent << "  data_model => ";
    using namespace boost;
    graph_traits< Data_model_graph_t >::vertex_iterator i, end;
    graph_traits< Data_model_graph_t >::out_edge_iterator ei, edge_end;
    for(boost::tie(i,end) = vertices(item.data_model_); i != end; ++i) {
      Node_properties const& node(item.data_model_[*i]);
      out << "Node => " << node;
      for (boost::tie(ei, edge_end) = out_edges(*i, item.data_model_); ei != edge_end; ++ei) {
        Link_properties const& link(item.data_model_[*ei]);
        out << "Edge => " << link;
      }
    }

// end <data_model custom streamer>
    out << indent << "}\n";
    return out;
  } 

} // namespace data_model
} // namespace h5
} // namespace fcs
#endif // _FCS_H5_DATA_MODEL_H5_DATA_MODEL_H_
