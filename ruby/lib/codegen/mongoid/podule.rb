require 'yaml'
require 'rubygems'
require 'json'
require 'codegen/cpp'
require 'codegen'
require 'set'

class Podule

  include Codegen::Cpp
  attr_reader :namespace, :database, :name, :header_includes

  @@mongo_int64_t = '::fcs::mongoid::Bson_int64_t'

  Valid_types = { 
    :Integer => 'std::int32_t',
    :Long => @@mongo_int64_t,
    :String => 'std::string',
    :Float => 'double',
    :Bool => 'bool',
  }

  From_bson_method = { 
    :Integer => 'Int()',
    :Long => 'Long()',
    :String => 'String()',
    :Float => 'numberDouble()',
    :Bool => 'Bool()',
  }

  def initialize(args = { })
    @namespace = args[:namespace]
    @name = (args[:name] or namespace.last)
    @database = args[:database]
    @header_includes = (args[:header_includes] or [])
    Pod.clear_data
    Enum.clear_data
  end

  def generate_code(header_name = nil)
    if Pod.pod_array.empty?
      raise "Will not generate empty pod library"
    end
    puts "Generating code in namespace #{namespace.inspect}"
    engine = Tenjin::Engine.new(:path => [ Place['mongoid_tmpl'].to_s])
    classes = []
    additional_classes = []
    Pod.pod_array.each do |pod|
      next if Pod.generated_pods.include? pod.name
      pod.database = @database
      members = []
      forward_typedefs = []
      pod.entries.each do |pod_entry|
        if pod_entry.is_array
          array_type = "#{pod_entry.type}_list_t"
          members << { 
            :name => pod_entry.name.to_s,
            :public => true,
            :cpp_type => array_type,
            :member_ctor => true,
            :pass_by_ref => true,
          }
          forward_typedefs << "typedef std::vector< #{pod_entry.cpp_type} > #{array_type}"
        else
          is_nested_pod = pod_entry.is_nested_pod
          is_oid = pod_entry.is_oid
          is_version = pod_entry.name == :version
          members << { 
            :name => pod_entry.name.to_s,
            :public => true,
            :cpp_type => pod_entry.cpp_type,
            :pass_by_ref => (is_nested_pod or is_oid),
            :mutable => is_oid,
            :member_ctor => (!is_oid and !is_version),
            :member_ctor_defaulted => is_oid,
            :comparable => pod_entry.name.to_s != "oid", 
            :init =>
            case
            when is_nested_pod
              nil
            when is_oid
              'mongo::OID()'
            when pod_entry.is_enum
              ''
            when is_version
              pod.version
            else
              "#{Valid_types[pod_entry.type]}()"
            end
          }
        end
      end
      pod_class = { 
        :name => pod.name,
        :boost_totally_ordered => true,
        :comparable => true,
        :op_equal => true,
        :ctor_default => true,
        :forward_typedefs => forward_typedefs,
        :struct => true,
        :streamable_inline => true,
        :streamers_included => !forward_typedefs.empty?,
        :members => members,
        :header_includes =>
        [
         'fcs/mongoid/mongoid.hpp',
        ] + header_includes,
      }

      context = { :pod => pod, :collection_support => pod.collection_support } 
      bson_support = engine.render("to_bson.tmpl", context)
      pod_class[:additions_public_header] = [ bson_support ]
      pod_class.merge! pod.additional_class_options
      
      additional_classes << CppClass.new(pod_class)

      if pod.collection_support
        collection_var_name = "#{pod.name.downcase}_collection_name"
        db_interface_class = { 
          :name => "#{pod.name}_database_access",
          :forward_typedefs =>
          [
           "typedef std::vector< #{pod.name} > #{pod.list_of_type}"
          ],
          :public_typedefs =>
          [
           "typedef #{pod.name} Access_t",
          ],
          :header_includes => 
          [
           'mongo/client/dbclient.h',
           'fcs/mongoid/connection_registry.hpp',
          ],
          :singleton => true,
          :log_ctor => true,
          :log_dtor => true,
          :members => [
                       { 
                         :name => 'connection',
                         :cpp_type => 'fcs::mongoid::Client_connection_ptr',
                         :init => %Q{fcs::mongoid::Connection_registry<>::get_instance()->get_client_connection("#{pod.database}")},
                       },
                       { 
                         :name => collection_var_name,
                         :cpp_type => 'std::string',
                         :init => %Q{"#{pod.database}.#{pod.name.downcase}"},
                         :access => Codegen::Access::RO,
                         :const => true,
                       },
                      ]
        }
        context[:collection_support] = pod.collection_support
        context[:collection_var_name] = collection_var_name
        db_interface_class[:additions_public_header] = [ engine.render("mongoid_db_access.tmpl", context) ]
        classes << CppClass.new(db_interface_class)
      end

      Pod.generated_pods.add(pod.name)
    end

    enums = []
    Enum.enum_array.each do |enum|
      enums << { 
        :name => enum.name.to_s,
        :values => enum.members.map { |m| m.to_s },
        :inline => true,
        :supports_picklist => true,
      }
      puts enums.inspect
    end

    classes << CppClass.new(
                            { 
                              :is_api_header => true,
                              :name => name,
                              :enums => enums,
                              :additional_classes => additional_classes
                            }
                            )

    Library.new({ 
                  :classes => classes,
                  :namespace => namespace,
                  :header_only => true,
                  :jam_requirements =>
                  [
                   '/site-config//boost_program_options',
                  ]
                })
  end

  class CollectionSupport
    attr_accessor :remove_all, :find_all, :insert, :include_oid
    def initialize(rest = {})
      defaults = { :remove_all => false, :find_all => true, :insert => true, :include_oid => true }
      merged = defaults.merge(rest)
      @remove_all = merged[:remove_all]
      @find_all = merged[:find_all]
      @insert = merged[:insert]
      @include_oid = merged[:include_oid]
    end
  end

  class Enum
    attr_reader :name, :members

    @enum_dictionary = { }
    class << self
      attr_reader :enum_dictionary
    end
    @enum_array = [ ]
    class << self
      attr_reader :enum_array
    end

    def initialize(data)
      @name = data[:name]
      @members = data[:members]
      Enum.enum_dictionary[name] = self
      Enum.enum_array << self
    end

    def Enum.clear_data()
      @enum_dictionary.clear
      @enum_array.clear
    end
  end

  class Pod

    attr_reader :name, :type_name, :entries, :additional_class_options, \
    :collection_support, :list_of_type, :oid_pod_entry, :version, \
    :version_pod_entry

    attr_accessor :database

    @pod_dictionary = { }
    class << self
      attr_reader :pod_dictionary
    end
    @pod_array = [ ]
    class << self
      attr_reader :pod_array
    end
    @generated_pods = Set.new
    class << self
      attr_reader :generated_pods
    end

    def Pod.clear_data()
      #@pod_dictionary.clear
      #@pod_array.clear
    end

    class PodEntry
      attr_reader :name, :bson_name, :type, :is_array, :is_enum, :cpp_type, \
      :is_oid, :is_version, :is_nested_pod, :version, :index, :unique_index
      def initialize(name, type, rest = { })
        @version = (rest[:version] or 0)
        @name = name
        @is_oid = (name == "oid")
        @is_version = (name == "version")
        if is_oid
          @bson_name = "_id"
        else
          @bson_name = name
        end
        @type = type
        @is_array = rest[:is_array]
        @is_enum = rest[:is_enum]
        @index = rest[:index]
        @unique_index = rest[:unique_index]
        @is_nested_pod = (!Valid_types[type] and !is_oid and !is_enum)
        @cpp_type = (Valid_types[type] or type.to_s)
      end
    end

    def add_entries(data_dev)
      for  type, name, rest in data_dev
        rest = { } if !rest
        type_as_string = type.to_s
        case
        when (Valid_types.include? type)
          @entries << PodEntry.new(name, type, rest)
        when type_as_string =~ /(\w+)_?Array$/i
          @entries << PodEntry.new(name, $1.to_sym, rest.merge({ :is_array => true }))
        when type_as_string =~ /(\w+)Enum$/
          @entries << PodEntry.new(name, $1.to_sym, rest.merge({ :is_enum => true }))
        when Pod.pod_dictionary.include?(type)
          @entries << PodEntry.new(name, type, rest)
        else
          puts "#{Pod.pod_dictionary.inspect}"
          raise "Do not know about type: #{type}"
        end
      end
      if collection_support and collection_support.include_oid
        @entries << PodEntry.new("oid", "mongo::OID")
        @oid_pod_entry = @entries[-1]
      end
    end

    def initialize(name, data_def, rest = { })
      @name = name.to_s
      @additional_class_options = (rest[:additional_class_options] or { })
      @list_of_type = "#{name}_list_t"
      @collection_support = rest[:collection_support]
      @entries = []
      @indices = (rest[:indices] or [])
      add_entries(data_def)
      @version = @entries.map {|e| e.version }.max
      if @version > 0
        @entries << PodEntry.new(:version, :Integer)
        @version_pod_entry = @entries[-1]
      end
      Pod.pod_dictionary[name] = self
      Pod.pod_array << self
    end
  end

end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
