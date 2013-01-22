################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen'
require 'codegen/cpp'
require 'codegen/cpp/cpp_lib'
require 'place'
require 'ostruct'
require 'tenjin'
require 'rubygems'
require 'sequel'
require "logger"
require 'yaml'
require 'pp'

include Codegen::Cpp

def augment_cpp_type(column)
  result = case column.db_type
           when /^enum\(([^\)]+)\)/i
             fields = $1.split(/,\s*/).map {|t| t.gsub("'",'') }
             size = fields.map { |f| f.length }.max + 1
             column.otl_type = "char[#{size}]"
             "fcs::utils::Fixed_size_char_array< #{size} >"                 
           when /^(?:int\((\d+)\)|int)$/i 
             column.otl_type = 'int'
             'boost::int32_t'
           when /^(?:bigint\((\d+)\)|bigint)$/i
             column.otl_type = 'bigint'
             'otl_bigint'
           when /(?:varchar|char)\((\d+)\)/i
             size = $1.to_i
             column.otl_type = "char[#{size}]"
             "fcs::utils::Fixed_size_char_array< #{size} >"
           when /(?:varchar|char)/i
             column.otl_type = "char[]"
             "otl_long_string"
           when /tinyint\(1\)|bool|bit/i
             column.otl_type = "short"
             "short"
           when /^time$/i
             column.otl_type = 'timestamp'
             "otl_time"
           when /^timestamp$/i
             column.otl_type = 'timestamp'
             "otl_datetime"
           when /^datetime$/i
             column.otl_type = 'timestamp'
             "otl_datetime"
           when /^date$/i
             column.otl_type = 'timestamp'
             "otl_datetime"
           when /(?:double|decimal)/i
             column.otl_type = "double"
             'double'
           when /text/i
             column.otl_type = "varchar_long"
             'otl_long_string'
           else "undefined_type<#{column.db_type}>"
           end
  column.cpp_type = result
end

def pass_by_ref_type? t
  result = case t
           when /Fixed_size_char_array/
             true
           when 'otl_datetime'
             true
           when 'otl_time'
             true
           when 'otl_date'
             true
           when 'otl_bigint'
             false
           when 'otl_long_string'
             true
           when /boost::int/
             false
           else
             false
           end
end


######################################################################
# "Parses" the select statement. Not a full parse, but more a lexical
# breakdown. Pulls out:
# 
#  - columns
#  - tables
#  - where_clause
#
# by splitting on the sql keywords. Then, preprocesses any 
# "column_return" calls. The "column_return" clauses look like:
# {column_return( :db_type => , :name => , :value => }
# The purpose is to provide enough information to get the appropriate
# data types to include in the query results. This is useful because
# sometimes columns do not refer to a table column but may refer to
# a function, formula, scalar, etc. For example, to include a count
# function on a column you might have:
#  {column_return(:db_type => 'int', :name => 'row_count', :value => "count(*)")},
# 
# After preprocessing "column_returns", the columns are split (/,/m).
# Each column is looked up in the schema to get the database type and
# corresponding c++ and otl types.
#
# Two other substitutes are possible:
# 
# <tt><substitute('table.column', :name)></tt>
#
# This is used to input data into the query for parameterizations.
#
# <tt>{presubstitute( :name => , :cpp_type =>, :no_sql_quote => )}</tt>
#
# This is used to perform substitutions before the query, that 
# are not parameterized in the query but text replaced up front.
# An example might be to use it to pass in data that is not
# statically known up front.
# e.g.
#
# <tt>
# select name from people where hometown not in
# {presubstitute(:name => 'not_in', :cpp_type => 'std::string')}
# </tt>
#
# Then <tt>not_in</tt> will be accepted in the query as a 
# <i>std::string</i> and substituted into the select.
#
class SelectParser

  attr_reader :tables, :columns, :table_aliases, :qualified_columns, :substitute_decls, \
  :substitute_parts, :names_in_code, :cpp_types_of_substitutes, \
  :select_statement, :substitute_statement_re, :select_statement_replaced, \
  :presubstitute_members, :presubstitute_members_re, :add_limit, :column_additions_by_value, \
  :column_return_re, :open, :close


  def column_return(rest)
    return rest
  end

  def substitute qualified_name, name = nil
    @substitute_parts << [qualified_name, name]
  end

  def presubstitute(rest)
    next_format = presubstitute_members.length + 1
    name = rest[:name]
    if rest[:no_sql_quote]
      quoted_name = "#{name}_"
    else
      quoted_name = case rest[:cpp_type]
                    when /char\s+const\s*\*/
                      "fcs::orm::sql_quote(#{name}_)"
                    when /const\s+char\s*\*/
                      "fcs::orm::sql_quote(#{name}_)"
                    when 'string' 
                      "fcs::orm::sql_quote(#{name}_)"
                    when 'std::string'
                      "fcs::orm::sql_quote(#{name}_)"
                    when /Fixed_size_char_array/
                      "fcs::orm::sql_quote(#{name}_)"
                    else
                      "#{name}_"
                    end
    end

    @presubstitute_members << { :cpp_type => rest[:cpp_type], :name => name, :quoted_name => quoted_name }
    "%#{next_format}%"
  end

  def find_schema_column qualified_name
    match = qualified_name =~ /(\w+)\.(\w+)/
    if match
      table_alias, column_name = $1, $2
      table_name = table_aliases[table_alias]
      if !table_name
        table_name = table_alias
      end
      schema_table = @schema_tables[table_name.to_sym]
      if schema_table.nil?
        pp @schema_tables
        raise "Cound not find schema table for #{table_name}"
      end
      found_column = schema_table.columns.select { |c| c.name == column_name }[0]
    else
      if @column_additions_by_value[qualified_name]
        column_hash = OpenStruct.new @column_additions_by_value[qualified_name].clone
        cpp_type = augment_cpp_type(column_hash)
        found_column = column_hash
      else
        warn "No match on schema column #{qualified_name}"
      end
    end
    found_column
  end

  def remove_special_chars txt
    txt.gsub(/[\{\}]/,'')
  end

  def initialize schema_tables, data
    @schema_tables = schema_tables
    @select_statement = data[:select_statement]
    @add_limit = data[:add_limit]
    @qualified_columns = []
    @presubstitute_members = []
    @open, @close = ['\\{', '\\}']
    @column_additions_by_value = {}
    @column_return_re = /(#{open}\s*column_return\([^#{close}]+?\)\s*#{close})/
    @substitute_statement_re = /(#{open}\s*substitute\([^#{close}]+?\)\s*#{close})/
    @presubstitute_members_re = /(#{open}\s*presubstitute\([^#{close}]+?\)\s*#{close})/

    @select_statement += " LIMIT {presubstitute(:name => 'limit', :cpp_type => 'int')}" if add_limit
    @select_statement_replaced = select_statement.clone    
    first_select_has_distinct = $1 if(select_statement_replaced =~ /^\s*select\s+distinct/im)
    @table_aliases = { }
    parsed = parse_outputs(select_statement.gsub(/\bdistinct\b/i, ''))
    @tables = parsed[:tables]
    @columns = parsed[:columns]
    @columns.each do |column, column_alias|
      entry = { }
      table_alias, column_name = column.split('.')
      entry[:qualified] = column
      if column_alias =~ /\./
        entry[:qualified_as_variable] = column_name
      else
        entry[:qualified_as_variable] = column_alias
      end
      entry[:table_alias] = table_alias
      entry[:table_name] = table_aliases[table_alias]
      entry[:name] = column_name
      @qualified_columns << entry
    end
    @substitute_parts = []
    @substitute_decls = []
    @names_in_code = []
    @cpp_types_of_substitutes = []

    temp = select_statement_replaced.split substitute_statement_re
    
    while temp.length > 1
      ignore, to_be_substituted = temp.shift 2
      eval remove_special_chars to_be_substituted
      substitute_decls << to_be_substituted
    end

    substitute_parts.each_index do | i |
      qualified_name, name_in_code = substitute_parts[i]
      substitute_decl = substitute_decls[i]
      qualified_column = qualified_columns.select {|qc| qc[:qualified] == qualified_name }[0]
      schema_column = find_schema_column qualified_name
      names_in_code << name_in_code
      cpp_types_of_substitutes << schema_column.cpp_type
      select_statement_replaced.gsub!(substitute_decl, ":#{name_in_code}<#{schema_column.otl_type}>")
    end

    direct_replacements = []
    temp = select_statement_replaced.split presubstitute_members_re
    while temp.length > 1
      ignore, to_be_substituted = temp.shift 2
      direct_replacements << [ to_be_substituted, eval(remove_special_chars to_be_substituted) ]
    end
    direct_replacements.each do |rep|
      from, to = rep
      select_statement_replaced.sub!(from, to)
    end
    if first_select_has_distinct
      select_statement_replaced.sub!(/^\s*select/im, first_select_has_distinct)
    end
  end

  def allow_for_as text
    if text =~ /^([\w\.]+)\s+as\s+(\w+)$/mi
      item, item_alias = $1, $2
    elsif text =~ /^([\w\.]+)\s+(\w+)$/mi
      item, item_alias = $1, $2
    elsif text =~ /^((\w+)\.(\w+))$/
      item, item_alias = $1, $3
    else
      item = item_alias = text
    end
    [item, item_alias]
  end

  def parse_outputs(stmt)

    parsed_columns, parsed_tables = stmt.scan(/^\s*\bselect\b\s+(.+?)\s*\bfrom\b\s+(.*)/mi)[0]

    if !parsed_tables
      raise "Could not parse select =>: #{stmt}"
    end

    temp = parsed_tables.split(/(\s+\bwhere\b\s+)/mi)
    if temp.length >= 2
      parsed_tables = temp[0..-3].join
      parsed_where_clause = temp[-1]
    end
    
    result = { :tables => [], :columns => [], :where => [] }
    
    parsed_tables.split(/,/m).each do |table|
      pair = allow_for_as(table.strip)
      result[:tables] << pair
      table_aliases[pair[1]] = pair[0]
    end

    temp = parsed_columns.split(column_return_re)
    if temp.length > 1
      #puts "TEMP => #{temp.inspect}"
      remaining = []
      while temp.length > 1
        keeper, to_be_substituted = temp.shift 2
        #puts "Keeper => #{keeper}"
        remaining << keeper
        column = eval(remove_special_chars to_be_substituted)
        @column_additions_by_value[column[:value]] = column
        remaining << column[:value]
      end
      remaining += temp
      parsed_columns = remaining.join('')
    end

    temp = parsed_columns.split(/,/m)
    parsed_columns = []
    
    glob_replacements = []
    glob_text_replacements = { }
    temp.each do |column_spec|
      column_spec.strip!
      if column_spec =~ /(\w+)\.(?:\*|\/([^\/]+)\/|!\/([^\/]+)\/)/
        table_alias = $1
        match_re = Regexp.new $2 if $2
        not_match_re = Regexp.new $3 if $3
        table = table_aliases[table_alias]
        columns_text = []
        @schema_tables[table.to_sym].columns.each do |column|
          next if match_re and column.name !~ match_re
          next if not_match_re and column.name =~ not_match_re
          column_text = "#{table_alias}.#{column.name}"
          glob_replacements << column_text
          columns_text << column_text
        end
        glob_text_replacements[column_spec] = columns_text
      else
        glob_replacements << column_spec
      end
    end

    temp = glob_replacements

    temp.each do |column|
      column.strip!
      if column_additions_by_value[column]
        result[:columns] << [ @column_additions_by_value[column][:value], @column_additions_by_value[column][:name] ]
      else
        result[:columns] << allow_for_as(column.strip)
      end
      parsed_columns << "#{result[:columns][-1].join(' as ')}"
    end
    parsed_columns = parsed_columns.join(",\n  ")
    new_select = 
      [
       "select\n  ", parsed_columns, 
       "\nfrom\n  ", parsed_tables.chomp,
      ]
    
    if parsed_where_clause
      new_select += [ "\nwhere\n  ", parsed_where_clause.chomp ]
    end

    @select_statement_replaced = new_select.join('')

    result
  end
end



module Codegen::Cpp

  ######################################################################
  # Generates the library of classes that support CRUD methods. 
  ######################################################################
  class TableLibrary < Library

    # Name of the database - schema
    attr_accessor :database_name

    # Template engine for generating code
    attr_accessor :engine

    # List of tables to generate code for
    attr_accessor :tables

    # Class containint the underlying connection
    attr_accessor :connection_singleton

    attr_accessor :table

    # Whether to create the connection with auto_commit on
    attr_reader :auto_commit

    # Collection of method support options
    attr_reader :support_options

    # If true generates select all (default is true)
    attr_reader :supports_select_all

    # If true generates select by primary key (default is true)
    attr_reader :supports_select_by_pkey

    # If true generates find_row_by_value
    attr_reader :supports_find_row_by_value

    # If true generates insert by primary key (default is true)
    attr_reader :supports_insert

    # If true generates insert by primary key [ table_names ] with ignore
    attr_reader :supports_insert_ignore

    # If true generates delete by primary key (default is true)
    attr_reader :supports_delete_by_pkey

    # If true generates delete all rows (default is false)
    attr_reader :supports_delete_all

    # If true generates update by pkey (default is true)
    attr_reader :supports_update_by_pkey

    # Additional classes to add to library
    attr_reader :additional_classes

    # If true includes unit test
    attr_reader :table_unit_tests

    def initialize(data={ })
      @engine = data[:engine]
      @database_name = data[:database_name]
      @tables = data[:tables]
      @additional_classes = (data[:additional_classes] or [])
      @table_unit_tests = data[:table_unit_tests]
      @connection_singleton = data[:connection_singleton]
      @auto_commit = data[:auto_commit]
      @namespace = data[:namespace] + ['table']
      @support_options = data[:support_options]
      @supports_select_all = Codegen.default_to_true_if_not_set(support_options, :supports_select_all)
      @supports_select_by_pkey = Codegen.default_to_true_if_not_set(support_options, :supports_select_by_pkey)
      @supports_find_row_by_value = Codegen.default_to_true_if_not_set(support_options, :find_row_by_value)
      @supports_insert = Codegen.default_to_true_if_not_set(support_options, :supports_insert)
      @supports_insert_ignore = (support_options[:supports_insert_ignore] or [])
      @supports_delete_by_pkey = Codegen.default_to_true_if_not_set(support_options, :supports_delete_by_pkey)
      @supports_update_by_pkey = Codegen.default_to_true_if_not_set(support_options, :supports_update_by_pkey)
      @supports_delete_all = (support_options[:supports_delete_all] or false)
      engine = Tenjin::Engine.new(:path => [ Place['rb_codegen_tmpl'].to_s, Place['database_tmpl'].to_s ])      
      context = { :lib => self }

      table_classes = []
      tables.each_pair do | table_name, table |
        @table = table
        @table.class_name = "#{table.name.capitalize}"
        @table.pkey_class = "#{table.name.capitalize}_pkey"
        @table.value_class = "#{table.name.capitalize}_value"

        classes = []
        members = []
        value_enum = []

        ##################################################
        # Iterate over columns - if any require
        # Fixed_size_char_array, pull in the header
        ##################################################
        fixed_size_char_array_required = false
        table.columns.each do | column |
          requires_fixed_size_char_array = column.cpp_type =~ /Fixed_size_char_array/
          fixed_size_char_array_required = true if requires_fixed_size_char_array
          if requires_fixed_size_char_array or column.cpp_type =~ /string/
            column.requires_quote = true
          end
        end

        ##################################################
        # Iterate over pk_columns collecting the members
        # and field entries for the enum
        ##################################################
        table.pk_columns.each do | column |
          members.push Member.new({ 
                                    :cpp_type =>column.cpp_type,
                                    :init => "#{column.cpp_type}()",
                                    :name =>column.name, 
                                    :member_ctor => true,
                                    :pass_by_ref => pass_by_ref_type?(column.cpp_type),
                                    :public =>true,
                                    :access => Codegen::Access::IA
                                  })
        end
        classes.push CppClass.new({
                                    :name => table.pkey_class,
                                    :ctor_default => true,
                                    :brief => "Encapsulates fields in primary key of table <em>#{table.name}</em>",
                                    :members => members,
                                    :op_equal => !members.empty?,
                                    :comparable => !members.empty?,
                                    :streamable_inline => true,
                                    :to_string_list => true,
                                    :header_only => true,
                                  })
        ##################################################
        # Iterate over value_columns collecting the 
        # members and field entries for the enum
        ##################################################
        members = []
        table.value_columns.each do | column |
          members.push Member.new({ 
                                    :cpp_type =>column.cpp_type,
                                    :init => "#{column.cpp_type}()",
                                    :name =>column.name, 
                                    :member_ctor => true,
                                    :pass_by_ref => pass_by_ref_type?(column.cpp_type),
                                    :public =>true,
                                    :access => Codegen::Access::IA
                                  })
          column.value_enum_name = "#{column.name.to_s.upcase}_FIELD"
          column.value_enum_scoped_name = "#{table.value_class}::#{column.name.to_s.upcase}_FIELD"
          value_enum.push column.value_enum_name
        end

        table.value_enum_name = table.name.capitalize + "_value_fields"
        table.value_enum_scoped_name = "#{table.value_class}::#{table.value_enum_name}"
        table.value_field_update_class = "#{table.value_class}_update"
        
        classes.push CppClass.new({
                                    :name => table.value_class,
                                    :ctor_default => true,
                                    :brief => "Encapsulates fields not in primary key of table <em>#{table.name}</em>",
                                    :members => members,
                                    :op_equal => true,
                                    :comparable => true,
                                    :streamable_inline => true,
                                    :to_string_list => true,
                                    :enums => 
                                    [ 
                                     { 
                                       :name => table.value_enum_name,
                                       :values => value_enum,
                                       :inline => true,
                                     }
                                    ],
                                    :header_only => true,
                                  })

        classes.reverse!
        header_includes = [ 
                           'fcs/orm/otl_config.hpp',
                           'fcs/orm/otl_utils.hpp',
                           'fcs/orm/orm_to_string_table.hpp',
                           'boost/thread/mutex.hpp',
                           'boost/thread/locks.hpp',
                           'pantheios/pantheios.hpp',
                           'boost/any.hpp',
                           "fcs/orm/#{database_name}/connection_#{database_name}.hpp"
                          ]
        header_includes.push 'fcs/utils/fixed_size_char_array.hpp' if fixed_size_char_array_required
        header_includes.push 'sstream'
        header_includes.push 'boost/any.hpp'
        inline_impl = engine.render("table_inline_impl.tmpl", { :me => self, :table => table })
        value_class_additions_public_header = engine.render("value_class_additions_public_header.tmpl", 
                                                            { :me => self, :table => table })
        class_definition = {
          :name => table.class_name,
          :brief => "Database object relational model support for table <em>#{table.name}</em>",
          :template_decls => 
          [ 
           "typename PKEY_LIST_TYPE = #{table.container_type}< #{table.pkey_class} >",
           "typename VALUE_LIST_TYPE = #{table.container_type}< #{table.value_class} >",
           'typename LOCK_TYPE = boost::mutex',
           'typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE >'
          ],
          :members => 
          [
           { 
             :cpp_type =>'otl_connect *',
             :name => 'connection', 
             :access => Codegen::Access::IA,
             :init => %Q/#{connection_singleton}::get_instance()->get_connection()/,
           },
          ],
          :ctor_default => true,
          :singleton => true,
          :singleton_base_template => "#{table.class_name}< PKEY_LIST_TYPE, VALUE_LIST_TYPE, LOCK_TYPE, GUARD_TYPE >",
          :additional_classes => classes,
          :additional_classes_come_first => true,
          :public_header_section => true,
          :public_typedefs => 
          [ 
           "typedef #{table.pkey_class} Pkey_t",
           "typedef #{table.value_class} Value_t",
           "typedef #{table.value_field_update_class} Value_update_t",
           'typedef PKEY_LIST_TYPE Pkey_list_t',
           'typedef VALUE_LIST_TYPE Value_list_t',
           "typedef std::pair< #{table.pkey_class}, #{table.value_class} > Row_t",
           "typedef #{table.container_type}< Row_t > Row_list_t",
          ],

          :additions_public_header => [
                                       inline_impl,
                                      ],
          :additions_pre_include_impl => [],
          :header_includes => header_includes,
          :header_only => true,
          :include_unit_test => table_unit_tests.include?(table.name.to_sym),
          :additions_namespace_forward_class => 
          [
           CppClass.new({
                          :name => table.value_field_update_class,
                          :brief => "Supports selective updates by value field id for <em>#{table.name}</em>",
                          :bases_public => [[ "std::map< #{table.value_enum_scoped_name}, boost::any >", "" ]],
                          :header_only => true,
                          :header_includes => [],
                          :additions_public_header => value_class_additions_public_header,
                        }).class_definition_wrapper ]

        }
        table_classes.push CppClass.new(class_definition)
      end
      
      super(
            {
              :classes => table_classes, 
              :name => database_name.to_s, 
              :header_only => true,
              :namespace => namespace,
              :build_cpp_includes => [ '$(OTL_INCLUDE_PATH)',],
              :jam_requirements => [ '/site-config//odbc', ],
            }
            )

    end
  end
end


module Codegen
  class Database
    # The database connection to get schema info on
    attr_reader :database_connection

    # The list of table names to generate code for
    attr_accessor :tables

    # The list of selects names to generate code for
    attr_reader :selects

    # Calculated: List of classes tied to the selects
    attr_accessor :query_classes

    # Hash of support options
    attr_reader :support_options

    # Additional classes
    attr_reader :additional_classes

    # List of tables to include unit tests for
    attr_reader :table_unit_tests

    # List of queries to include unit tests for
    attr_reader :query_unit_tests

    # Set of tables to use vector on - default is list
    attr_reader :use_vector_on

    def initialize(codegen_request={ })
      @database_connection = codegen_request[:database_connection]
      @database_name = @database_connection.opts[:database]
      @tables = (codegen_request[:tables] or [])
      @selects = (codegen_request[:selects] or [])
      @table_unit_tests = (codegen_request[:table_unit_tests] or [])
      @query_unit_tests = (codegen_request[:query_unit_tests] or [])
      @additional_classes = (codegen_request[:additional_classes] or [])
      @query_classes = []
      @support_options = (codegen_request[:support_options] or { })
      @use_vector_on = Set.new((codegen_request[:use_vector_on] or []))
      @schema = OpenStruct.new
      if tables.empty?
        @tables = database_connection.tables
      end
      @all_tables = database_connection.tables
      @schema.tables = { }

      # Get schema on all tables
      @all_tables.each do |table|
        @schema.tables[table] = OpenStruct.new
        @schema.tables[table].name = table.to_s
        @schema.tables[table].pk_columns = []
        @schema.tables[table].value_columns = []
        @schema.tables[table].columns = []
        @schema.tables[table].container_type = ((use_vector_on.include? table) ? "std::vector" : "std::list")
        database_connection.schema(table).each do |column, attributes|
          current_column = OpenStruct.new attributes
          current_column.name = column.to_s
          augment_cpp_type(current_column)
          @schema.tables[table].columns.push current_column
          if current_column.primary_key
            @schema.tables[table].pk_columns.push current_column
          else
            @schema.tables[table].value_columns.push current_column
          end
        end
      end

      begin
        @selects.each do |s|
          s[:parsed] = SelectParser.new @schema.tables, s
        end
      end


      engine = Tenjin::Engine.new(:path => [ Place['rb_codegen_tmpl'].to_s, 
                                             Place['database_tmpl'].to_s ])

      ############################################################
      # The table classes
      ############################################################
      namespace = ['fcs', 'orm', @database_name,]
      connection_singleton = "Connection_#{@database_name}"
      codegen_tables = Hash[@schema.tables.select {|k,v| tables.include? k }]
      db_library = TableLibrary.new({ 
                                      :namespace => namespace,
                                      :connection_singleton => connection_singleton,
                                      :engine => engine,
                                      :database_name => @database_name,
                                      :tables => codegen_tables,
                                      :support_options => support_options,
                                      :table_unit_tests => table_unit_tests,
                                      :additional_classes => additional_classes
                                    })


      connection_impl = engine.render("connection_inline_impl.tmpl", { :me => db_library })
      @connection_singleton_class =                      
        CppClass.new({
                       :name => connection_singleton,
                       :log_ctor => true,
                       :log_dtor => true,
                       :brief => 'Holds the underlying database connection on per thread basis',
                       :singleton => true,
                       :members => [
                                    { 
                                      :cpp_type =>'boost::thread_specific_ptr< otl_connect >',
                                      :name =>'tss_connection', 
                                      :access => Codegen::Access::IA
                                    }
                                   ],
                       :header_only => true,
                       :header_includes => [ 
                                            'fcs/orm/connection_registry.hpp',
                                            'pantheios/inserters/hex_ptr.hpp',
                                            'boost/thread/tss.hpp',
                                           ],
                       :additions_public_header => [
                                                    connection_impl,
                                                   ],

                     })

      top_classes = [ @connection_singleton_class ] + additional_classes

      ############################################################
      # First the top level folder with the connection class
      ############################################################
      db_library = Library.new({ 
                                 :namespace => namespace,
                                 :classes => top_classes,
                                 :header_only => true,
                                 :jam_requirements => [ '/site-config//otl',],
                               })

      ############################################################
      # Now for ad-hoc queries
      ############################################################
      selects.each do |select|
        #puts select.to_yaml
        parsed = select[:parsed]
        members = []
        parsed.qualified_columns.each do | qualified_column |
          table_name = qualified_column[:table_name]
          found_column = parsed.find_schema_column qualified_column[:qualified]
          if found_column.nil?
            raise "Could not find column #{qualified_column.inspect}"
          end
          member =  Member.new({ 
                                 :cpp_type =>found_column.cpp_type,
                                 :init => "#{found_column.cpp_type}()",
                                 :brief => "Column #{qualified_column[:qualified]} from table #{table_name}",
                                 :name => qualified_column[:qualified_as_variable], 
                                 :public => true,
                               })
          members.push member
        end
        query_business_name = select[:query_business_name].capitalize
        substituted_members = []        
        parsed.names_in_code.each_index do |j|
          #puts "member => #{parsed.names_in_code[j]} => #{parsed.names_in_code[j].class}"
          if substituted_members.select {|sm| sm.name == parsed.names_in_code[j].to_s }.empty?
            substituted_members << Member.new(
                                              { 
                                                :cpp_type => parsed.cpp_types_of_substitutes[j],
                                                :name => parsed.names_in_code[j].to_s,
                                                :member_ctor => true,
                                                :pass_by_ref => pass_by_ref_type?(parsed.cpp_types_of_substitutes[j]),
                                                :access => Codegen::Access::RO,
                                              }
                                              )
          end
        end

        parsed.presubstitute_members.each do | m |
          substituted_members.push << 
            Member.new({ 
                         :cpp_type => m[:cpp_type],
                         :init => "#{m[:cpp_type]}()",
                         :name => m[:name], 
                         :member_ctor => true,
                         :pass_by_ref => pass_by_ref_type?(m[:cpp_type]),
                         :access => Codegen::Access::RO,
                       })
        end

        substitute_order = (select[:substitute_order] or [])
        if !substitute_order.empty?
          ordered_members = []
          substitute_order.each do | name |
            found = substituted_members.find {|m| m.name == name.to_s }
            if !found
              raise "Could not find member #{name} in #{substituted_members.map {|s| s.name }.join(', ')}"
            end
            ordered_members << found
          end
          substituted_members.each do |m|
            ordered_members << m if !ordered_members.include? m
          end
          substituted_members = ordered_members
        end

        trouble_re = /((:\w+)(<[^>]+>))(.*?)(\1)/m
        match = parsed.select_statement_replaced.match trouble_re
        suffix = "_0"
        while match
          parsed.select_statement_replaced.sub!(trouble_re) {|m| "#{$1}#{$4}#{$2}#{suffix.next!}#{$3}"  }
          match = parsed.select_statement_replaced =~ trouble_re
        end

        header_includes = [
                           "fcs/orm/#{@database_name}/connection_#{@database_name}.hpp",
                           'fcs/orm/otl_config.hpp',
                           'fcs/orm/otl_utils.hpp',
                           'fcs/utils/streamers/table/table.hpp',
                          ]
        header_includes << 'boost/format.hpp' if !parsed.presubstitute_members.empty?
        query_requires_args = (!parsed.names_in_code.empty? or 
                               !parsed.presubstitute_members.empty?)

        query_class = 
          CppClass.new(
                       { 
                         :name => query_business_name,
                         :struct => true,
                         :descr => select[:descr],
                         :brief => "Record data associated with #{query_business_name}",
                         :op_equal => true,
                         :header_includes => [],
                         :ctor_default => true,
                         :to_string_list => true,
                         :members => members,
                         :streamable_inline => true,
                         :additional_classes => 
                         [
                          CppClass.new(
                                       { 
                                         :name => query_business_name + '_query',
                                         :streamable_inline => true,
                                         :include_unit_test => query_unit_tests.include?(select[:query_business_name]),
                                         :brief => "Query object for retrieving #{query_business_name} records",
                                         :ctor_default_init_inline_method => !query_requires_args,
                                         :ctor_member_init_inline_method => query_requires_args,
                                         :ctor_default => !query_requires_args,
                                         :ctor_member_init => query_requires_args,
                                         :public_header_section => select[:public_header_section],
                                         :additions_private_header => 
                                         engine.render("query_impl.tmpl", 
                                                       { :me => self, 
                                                         :database_name => @database_name,
                                                         :query_business_name => query_business_name,
                                                         :query_requires_args => query_requires_args,
                                                         :select => select }),
                                         :additions_public_header =>
                                         engine.render("print_query_results_as_table.tmpl", 
                                                       { :me => self, 
                                                         :database_name => @database_name,
                                                         :query_business_name => query_business_name,
                                                         :query_requires_args => query_requires_args,
                                                         :select => select }),
                                         :descr => "
Implements the following select
---------------------------------------------------
#{select[:select_statement]}
",

                                         :header_includes => header_includes,
                                         :public_typedefs =>
                                         [
                                          "typedef std::list< #{query_business_name} > Row_list_t",
                                         ],
                                         :members => 
                                         [
                                          { 
                                            :cpp_type => 'Row_list_t',
                                            :name => 'query_result', 
                                            :pass_by_ref => true,
                                            :brief => 'Results of the sql query',
                                            :access => Codegen::Access::RO,
                                          },
                                          { 
                                            :cpp_type => 'std::string',
                                            :name => 'query', 
                                            :brief => 'The run on construction',
                                            :init => Codegen::Cpp.make_c_string_literal(parsed.select_statement_replaced),
                                          },
                                         ] + substituted_members,
                                       }
                                       )

                         ]
                       }
                       )

        @query_classes << query_class


      end

      if query_classes.length > 0
        Library.new(
                    { 
                      :classes => query_classes,
                      :header_only => true,
                      :jam_requirements => 
                      [ 
                       '/site-config//odbc',
                       '/site-config//boost_date_time',
                      ],
                      :namespace => ['fcs', 'orm', @database_name, 'query',]
                    })
      end

    end
  end
end


