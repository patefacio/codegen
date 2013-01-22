################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

delimiter_classes = [

                     CppClass.new({ 
                                    :name => 'Delimited_file_creator',
                                    :additional_ctor_parms => [],
                                    :bases_public => [],
                                    :streamed_bases => [],
                                    :public_typedefs => [ ],
                                    :members => [                                                  
                                                  { 
                                                    :cpp_type => 'boost::filesystem::path', 
                                                    :brief => 'Path to file csv to write',
                                                    :name => 'file_path', 
                                                    :pass_by_ref =>true,
                                                    :member_ctor =>true,
                                                  }, 
                                                  { 
                                                    :cpp_type => 'Table_model', 
                                                    :brief => 'Table to read from to write csv data',
                                                    :name => 'table_model', 
                                                    :pass_by_ref =>true,
                                                    :member_ctor =>true,
                                                    :store_by_cref =>true,
                                                  }, 
                                                  { 
                                                    :cpp_type => 'char', 
                                                    :brief => 'Column delimiter',
                                                    :name => 'column_delimiter', 
                                                    :pass_by_ref =>true,
                                                    :member_ctor_defaulted =>true,
                                                    :init => 'DELIMITER_COMMA',
                                                  }, 
                                                  { 
                                                    :cpp_type => 'char', 
                                                    :brief => 'End line delimiter',
                                                    :name => 'end_line_delimiter', 
                                                    :pass_by_ref =>true,
                                                    :member_ctor_defaulted =>true,
                                                    :init => 'DELIMITER_NEW_LINE',
                                                  }, 

                                                ],
                                    :public_header_section => true,
                                    :private_header_section => true,
                                    :streamable_inline => true,
                                    :header_only => true,
                                    :include_unit_test => true,
                                    :brief => 'Class that writes delimited (eg csv) files from data from Table_model',
                                    :header_includes => [ 'fcs/table/table_model.hpp', 
                                                           'boost/filesystem/path.hpp',
                                                           'fstream',
                                                         ],
                                  }),

                     CppClass.create_pod('Delimited_file_reader_options', 
                                         'Options for reading delimited file into table model', 
                                         [
                                          ['int', 'minimum_row_matches_to_accept_delimiter', 
                                           'Requires this many consistent matches to glean separator', 
                                           {:init => 5, :member_ctor_defaulted => true} ],
                                          ['int', 'minimum_row_matches_to_accept_column_type', 
                                           'Requires this many consistent matches of cell type to glean column cell type', 
                                           {:init => 5, :member_ctor_defaulted => true} ],
                                          ['char', 'column_delimiter', 
                                           'Delimiter to use as field separator when parsing rows', 
                                           {:init => 'DELIMITER_UNSPECIFIED', :member_ctor_defaulted => true}, ],
                                          ['Table_header_t', 'table_header', 
                                           'Optional user supplied header - only used if correctly sized', 
                                           { :member_ctor_defaulted => true }, ],

                                         ],
                                         { 
                                           :streamable_inline => true, 
                                           :streamers_included => true,
                                           :no_block_indenter => true,
                                           :public_header_section => true,
                                           :header_only => true,
                                           :ctor_default => false,
                                         }
                                         ),


                     Codegen::Cpp::CppClass.new({ 
                                                  :name => 'Delimited_file_reader',
                                                  :additional_ctor_parms => [],
                                                  :bases_public => [],
                                                  :header_only => true,
                                                  :streamable_inline => true,
                                                  :streamers_included => true,
                                                  :streamed_bases => [],
                                                  :public_typedefs => 
                                                  [ 
                                                   'typedef boost::escaped_list_separator< char > Escaped_list_separator_t',
                                                   'typedef boost::tokenizer< Escaped_list_separator_t > Tokenizer_t',
                                                  ],
                                                  :members => [                                                  
                                                                { 
                                                                  :cpp_type => 'boost::filesystem::path', 
                                                                  :brief => 'Path to file csv to read',
                                                                  :name => 'file_path', 
                                                                  :pass_by_ref =>true,
                                                                  :member_ctor =>true,
                                                                }, 
                                                                { 
                                                                  :cpp_type => 'Delimited_file_reader_options', 
                                                                  :brief => 'Options describing how to read and determine column types',
                                                                  :name => 'options', 
                                                                  :pass_by_ref =>true,
                                                                  :member_ctor_defaulted =>true,
                                                                  :init => 'Delimited_file_reader_options()',
                                                                }, 
                                                                { 
                                                                  :cpp_type => 'Ifstream_ptr', 
                                                                  :brief => 'File to read table data from',
                                                                  :name => 'input_stream', 
                                                                  :streamable => false,
                                                                  :pass_by_ref =>true,
                                                                }, 
                                                                { 
                                                                  :cpp_type => 'Line_list_t', 
                                                                  :brief => 'Sample of first <I>n</I> lines for delimiter and type determination',
                                                                  :name => 'table_sample_lines', 
                                                                  :init => 'options_.minimum_rows_to_sample()',
                                                                  :pass_by_ref =>true,
                                                                }, 
                                                                { 
                                                                  :cpp_type => 'String_table_t', 
                                                                  :brief => 'Values of fields in sample lines',
                                                                  :name => 'table_sample_fields', 
                                                                  :init => 'options_.minimum_rows_to_sample()',
                                                                  :pass_by_ref =>true,
                                                                },
                                                                { 
                                                                  :cpp_type => 'String_list_t', 
                                                                  :brief => 'Last line of fields read',
                                                                  :name => 'last_line_fields_read', 
                                                                  :pass_by_ref =>true,
                                                                },
                                                                { 
                                                                  :cpp_type => 'Escaped_list_separator_t', 
                                                                  :brief => 'Separator for tokenizing data',
                                                                  :name => 'escaped_list_separator', 
                                                                  :streamable => false,
                                                                  :pass_by_ref =>true,
                                                                },
                                                                { 
                                                                  :cpp_type => 'char', 
                                                                  :brief => 'Field delimiter',
                                                                  :name => 'delimiter', 
                                                                  :init => 'DELIMITER_UNSPECIFIED',
                                                                },
                                                                { 
                                                                  :cpp_type => 'size_t', 
                                                                  :brief => 'Number of columns',
                                                                  :name => 'num_columns', 
                                                                  :init => '0',
                                                                },
                                                                { 
                                                                  :cpp_type => 'Table_shape_t', 
                                                                  :brief => 'Shape determined by reading <I>sample rows</I>',
                                                                  :name => 'table_shape', 
                                                                  :pass_by_ref =>true,
                                                                },
                                                                { 
                                                                  :cpp_type => 'bool', 
                                                                  :brief => 'Field delimiter',
                                                                  :name => 'first_row_is_data', 
                                                                  :init => 'false',
                                                                },
                                                                { 
                                                                  :cpp_type => 'Table_model_ptr', 
                                                                  :brief => 'Table model created on read',
                                                                  :name => 'table_model', 
                                                                  :pass_by_ref =>true,
                                                                },
                                                               ],
                                                  :public_header_section => true,
                                                  :private_header_section => true,
                                                  # Tested in delimited_file_creator :include_unit_test => true,
                                                  :brief => 'Class that reads delimited (eg csv) files from data from Table_model',
                                                  :descr => "
Reads the specified <I>file_path</I> and parses it as a table.
If a delimiter is not specified it uses basic heuristic to
attempt to determine the separator.
",
                                                  :header_includes => [ 
                                                                       'fcs/table/table_model.hpp',
                                                                       'fcs/table/memory_table_model.hpp',
                                                                       'fcs/table/table_cell_string_conversion.hpp',
                                                                       'boost/filesystem/path.hpp',
                                                                       'boost/tokenizer.hpp',
                                                                       'boost/array.hpp',
                                                                       'fstream',
                                                                       ],
                                                }),


                    ]

classes = [

           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Table',
                                        #:impl_filename => 'moo.cpp',
                                        #:header_filename => 'moo.hpp',
                                        :header_only => true,
                                        :is_api_header => true,
                                        :brief => 'Basic Table functionality',
                                        :public_typedefs => 
                                        [ 
                                         typedef_shared_ptr_of('Table_model'),
                                         typedef_shared_ptr_of('Table_search'),
                                         """typedef boost::variant<
  boost::int8_t, boost::int32_t, boost::int64_t, 
  boost::uint8_t, boost::uint32_t, boost::uint64_t, 
  float, double, long double, 
  std::string > Cell_contents_t""",
                                         'typedef size_t Index_t',
                                         typedef_pair_of('Index_t', :full_name => 'Cell_location_t'),
                                         typedef_pair_of('Cell_location_t', :full_name => 'Cell_location_range_t'),
                                         typedef_vector_of('Cell_location_t'),

                                         typedef_vector_of('Cell_contents_t', :full_name => 'Row_contents_t'),
                                         typedef_vector_of('Cell_contents_t', :full_name => 'Column_contents_t'),
                                         typedef_vector_of('Column_contents_t', :full_name => 'Table_of_cell_contents_t'),

                                         typedef_vector_of('Table_cell_type', :full_name => 'Table_shape_t'),
                                         typedef_shared_ptr_of('Row_contents_t'),
                                         typedef_vector_of('Row_contents_ptr', :full_name => 'Table_contents_t'),

                                         typedef_vector_of('std::string', :full_name => 'Table_header_t'),
                                         typedef_vector_of('std::string', :name => 'Line'),
                                         typedef_vector_of('std::string', :name => 'String'),
                                         typedef_vector_of('String_list_t', :full_name => 'String_table_t'),

                                         'typedef boost::function< bool (Cell_contents_t) > Search_functor_t',
                                         typedef_timestamp(),
                                         typedef_shared_ptr_of('std::ofstream'),
                                         typedef_shared_ptr_of('std::ifstream'),
                                        ],

                                        :forward_class_decls => ['fcs::table::Table_model', 'fcs::table::Table_search'],
                                        :header_includes => [ 'boost/variant.hpp', 
                                                               'boost/cstdint.hpp', 'vector', 'string', 'iosfwd',
                                                               'boost/date_time/posix_time/posix_time.hpp',
                                                             ],
                                        :enums => [ 
                                                   {
                                                     :name => 'Table_cell_type', 
                                                     :brief => 'Enumerates the datatypes supported by table',
                                                     :inline => true,
                                                     :values => [
                                                                  'CELL_TYPE_INT8', 
                                                                  'CELL_TYPE_INT32',
                                                                  'CELL_TYPE_INT64',
                                                                  'CELL_TYPE_UINT8', 
                                                                  'CELL_TYPE_UINT32',
                                                                  'CELL_TYPE_UINT64',
                                                                  'CELL_TYPE_FLOAT',
                                                                  'CELL_TYPE_DOUBLE',
                                                                  'CELL_TYPE_LONG_DOUBLE',
                                                                  'CELL_TYPE_STRING',
                                                                 ],
                                                   }, 
                                                  ],
                                      }),

           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Table_meta_data',
                                        :ctor_default => true,
                                        :members => [
                                                      { :cpp_type => 'Table_shape_t', 
                                                        :brief => 'Ordered list of datatypes for each column',
                                                        :name => 'shape', 
                                                        :member_ctor =>true,
                                                        :pass_by_ref =>true,
                                                        :protected =>true,
                                                        :access => Codegen::Access::RW}, 
                                                      { :cpp_type => 'Table_header_t', 
                                                        :brief => 'Ordered list of column header text',
                                                        :member_ctor_defaulted =>true,
                                                        :init => 'Table_header_t()',
                                                        :name => 'header', 
                                                        :protected =>true,
                                                        :pass_by_ref =>true,
                                                        :access => Codegen::Access::RW}, 
                                                      { :cpp_type => 'bool', 
                                                        :brief => 'If true indicates data_set may grow increase over time',
                                                        :member_ctor_defaulted =>true,
                                                        :init => 'false',
                                                        :name => 'may_grow', 
                                                        :protected =>true,
                                                        :access => Codegen::Access::RO}, 

                                                     ],
                                        :streamable_inline => true,
                                        :header_only => true,
                                        #:disable_windows_warnings => ['4251'],
                                        :brief => 'Metadata for a table - its shape and header',
                                        :header_includes => [  ],
                                        :impl_includes => [ 'fcs/utils/streamers/vector.hpp' ],
                                      }),

           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Table_cell_string_conversion',
                                        :members => [ ],
                                        :brief => 'Methods for converting between table cells and strings',
                                        :header_includes => [ ],
                                        :header_only => true,
                                        :public_header_section => true,
                                        :header_includes => [                                      
                                                              'pantheios/inserters.hpp',
                                                              'boost/spirit/include/qi_operator.hpp',
                                                              'boost/spirit/include/qi_numeric.hpp',
                                                              'boost/spirit/include/qi_char.hpp',
                                                              'boost/spirit/include/qi_parse.hpp',
                                                              'boost/spirit/include/qi_action.hpp',
                                                              'boost/spirit/include/phoenix_core.hpp',
                                                              'boost/spirit/include/phoenix_operator.hpp',
                                                             ],
                                      }),


           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Table_model',
                                        :header_only => true,
                                        :ctor_default => true,
                                        :log_ctor => true,
                                        :log_dtor => true,
                                        :members => [
                                                      { :cpp_type => 'Table_meta_data', 
                                                        :brief => 'Column type and header data associated with the table',
                                                        :name => 'meta_data', 
                                                        :member_ctor =>true,
                                                        :pass_by_ref =>true,
                                                        :protected =>true,
                                                        :access => Codegen::Access::RO}, 
                                                     ],
                                        :dtor_virtual_inline_noop => true,
                                        :typedef_ptr => true,
                                        :typedef_const_ptr => true,
                                        :public_header_section => true,
                                        :bases_public => [ ['boost::noncopyable', 'boost::noncopyable()'] ],
                                        :streamable_inline => true,
                                        #:ctor_member_init_inline_method => true,
                                        #:disable_windows_warnings => ['4251'],
                                        :brief => 'Basic table model interface',
                                        :header_includes => 
                                        [ 
                                         'fcs/table/stream_out_visitor.hpp',
                                         'fcs/table/table_meta_data.hpp',
                                         'boost/variant/apply_visitor.hpp',
                                        ],
                                        :impl_includes => [ 'sstream', ],
                                      }),


           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Memory_table_model',
                                        :header_only => true,
                                        :additional_ctor_parms => [[ 'Table_meta_data const&', 'meta_data' ]],
                                        :bases_public => [['Table_model', 'Table_model(meta_data)'],],
                                        :streamed_bases => ['Table_model'],
                                        :public_typedefs => [ ],
                                        :members => [ 
                                                      { 
                                                        :cpp_type => 'Table_contents_t', 
                                                        :brief => 'Data of the table',
                                                        :name => 'table_contents', 
                                                        :pass_by_ref =>true,
                                                      }, 
                                                     ],
                                        :header_only => true,
                                        :public_header_section => true,
                                        #:private_header_section => true,
                                        :streamable_inline => true,
                                        #:disable_windows_warnings => ['4251'],
                                        :brief => 'Table with only memory backing it up',
                                        :header_includes => [ 'fcs/table/table_model.hpp', ],
                                        :impl_includes => [ 'sstream', 'fcs/utils/streamers/vector.hpp' ],
                                      }),

           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Delimited_file_table_model',
                                        :no_class => true,
                                        :additional_ctor_parms => [],
                                        :bases_public => [],
                                        :streamed_bases => [],
                                        :streamable_inline => true,
                                        :streamers_included => true,
                                        :public_typedefs => [ ],
                                        :members => [                                                  

                                                     ],
                                        :public_header_section => true,
                                        :additional_classes => delimiter_classes,
                                        :header_only => true,
                                        :brief => 'Class that writes delimited (eg csv) files from data from Table_model',
                                        :header_includes => 
                                        [
                                         'fcs/table/table_model.hpp',
                                         'boost/filesystem/path.hpp',
                                         'fstream',
                                        ],
                                        :file_level_consts => [
                                                                'char const DELIMITER_COMMA(\',\')',
                                                                'char const DELIMITER_PIPE(\'|\')',
                                                                'char const DELIMITER_CARAT(\'^\')',
                                                                'char const DELIMITER_PERCENT(\'%\')',
                                                                'char const DELIMITER_NEW_LINE(\'\n\')',
                                                                'char const DELIMITER_UNSPECIFIED(0)',
                                                               ],
                                        
                                      }),


           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Table_search',
                                        :header_only => true,
                                        :members => [
                                                      { :cpp_type => 'Cell_location_range_t', 
                                                        :brief => 'Range for the search',
                                                        :name => 'search_range', 
                                                        :member_ctor => true,
                                                        :pass_by_ref =>true,
                                                        :access => Codegen::Access::RO}, 
                                                      { :cpp_type => 'Table_model_const_ptr', 
                                                        :brief => 'Table to search over the supplied range',
                                                        :name => 'target_table', 
                                                        :member_ctor => true,
                                                        :pass_by_ref =>true,
                                                        :streamable =>false,
                                                        :access => Codegen::Access::RO}, 
                                                      { :cpp_type => 'Search_functor_t', 
                                                        :brief => 'Search functor for finding matches in cells',
                                                        :name => 'search_functor', 
                                                        :member_ctor => true,
                                                        :pass_by_ref =>true,
                                                        :access => Codegen::Access::RO}, 

                                                     ],
                                        :typedef_ptr => true,
                                        :public_header_section => true,
                                        :streamable_inline => true,
                                        #:disable_windows_warnings => ['4251'],
                                        :header_includes => [ 'fcs/table/table_model.hpp', ],
                                        :brief => 'Basic search for rows in which cell matches',
                                        :impl_includes =>  [ 'fcs/utils/streamers/vector.hpp', ],
                                      }),

           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Table_compare',
                                        :no_class => true,
                                        :header_namespace_begin_section => true,
                                        :header_only => true,
                                        :members => [ ],
                                        :public_header_section => true,
                                        :brief => 'Basic comparison functionality',
                                        :header_includes => 
                                        [ 
                                         'fcs/table/stream_out_visitor.hpp', 
                                         'sstream' 
                                        ],
                                        :impl_includes => [ ],
                                      }),

           Codegen::Cpp::CppClass.new({ 
                                        :name => 'Stream_out_visitor',
                                        :header_only => true,
                                        :pass_by_ref => true,
                                        :bases_public =>
                                        [
                                         ['boost::static_visitor<>'],
                                        ],
                                        :members => 
                                        [
                                         { 
                                           :name => 'out',
                                           :store_by_ref => true,
                                           :cpp_type => 'std::ostream',
                                           :member_ctor => true,
                                           :pass_by_ref => true,
                                         }
                                        ],
                                        :public_header_section => true,
                                        :brief => 'Out table cell contents to stream',
                                        :header_includes => [ 'iosfwd' ],
                                      }),


          ]


lib = Codegen::Cpp::Library.new({ 
                                  :name => 'table',
                                  :header_only => true,
                                  :descr => 

'Provides an abstraction for a table - a 2 dimensional matrix of data. Types
of data supported are dictated by entries in Cell_contents_t boost::variant.',
                                  
                                  :classes => classes,
                                  :jam_requirements => [ 
                                                        ],
                                  :namespace => ['fcs', 'table']
                                })

