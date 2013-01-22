################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

classes = [

           CppClass.new({ 
                          :name => 'H5_data_model',
                          :forward_class_decls =>
                          [
                           'fcs::h5::data_model::Link_properties',
                           'fcs::h5::data_model::Node_properties',
                          ],
                          :forward_typedefs =>
                          [
                           'typedef boost::adjacency_list< 
  boost::vecS,              // Node storage type
  boost::listS,             // Edge storage type
  boost::directedS,         // directed vs undirected
  Node_properties,          // Vertices are nodes
  Link_properties           // Edges are hdf5 links
> Data_model_graph_t'
                          ],
                          :descr => 

"The structure of the data model of an hdf5 file.  Contains the tree structure
of Groups, Datasets, Dataspaces, Datatypes, Attributes, PropertyLists and
Links.",
                          :streamable_inline => true,
                          :members => [
                                       { :cpp_type =>'Data_model_graph_t', 
                                         :name =>'data_model',
                                         :pass_by_ref =>true,
                                         :streamable_custom =>true,
                                         :access => Codegen::Access::RO,
                                       }, 
                                      ],
                          :brief => 'Data model associated with single HDF5 File',
                          :header_only => true,
                          :header_includes => 
                          [ 
#                           'H5public.h',
#                           'H5File.h',
                           'boost/graph/adjacency_list.hpp',
                           'boost/graph/graph_utility.hpp',
                           'boost/filesystem/path.hpp',
                          ],
                          :public_header_section => true,
                          :include_unit_test => true,
                          :ctor_member_init_inline_method => true,
                          :ctor_default_init_inline_method => true,
                          :additional_classes =>
                          [
                           CppClass.new({ 
                                          :name => 'Link_properties',
                                          :streamable_inline => true,
                                          :ctor_default => true,
                                          :members =>
                                          [
                                           { 
                                             :cpp_type => 'std::string',
                                             :name => 'name',
                                             :member_ctor => true,
                                           }
                                          ]
                                        }),

                           CppClass.new({ 
                                          :name => 'Node_properties',
                                          :streamable_inline => true,
                                          :ctor_default => true,
                                          :members =>
                                          [
                                           { 
                                             :cpp_type => 'std::string',
                                             :name => 'name',
                                             :member_ctor => true,
                                             :public => true,
                                           }
                                          ]
                                        }),
                          ],
                          :additional_classes_come_first => true,
                        }),

          ]

lib = Library.new({ 
                    :descr =>

"Api to support accessing the data model ojbects in an hdf5 file",

                    :classes => classes,
                    :header_only => true,
                    :jam_requirements => [ 
                                          '/site-config//hdf5',
                                          '/site-config//boost_filesystem',
                                         ],
                    :namespace => ['fcs', 'h5', 'data_model']
                  })

