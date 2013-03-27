require 'codegen'
require 'codegen/attributes'
require 'codegen/id'
require 'codegen/xmi/model'
require 'codegen/dlang/package'

include Codegen
include Codegen::Dlang
include Codegen::Xmi

module Codegen::Dlang
  class DataModel
    extend Attributes
    attr_reader :type_map, :primitives, :seq_or_map

    attribute_defaults({ 
                         :model => nil, 
                         :package_id => nil,
                         :packages => nil,
                       })

    def initialize(opts={ })
      set_attributes(opts)
      @primitives = [ 'num', 'int', 'double', 'string', 'bool' ]
      @type_map = { }
      @seq_or_map = /(\w+)(_map|_sequence)$/
      @non_generated = [:map,:sequence,:time_value,:date]
    end

    def create_package
      process_enums
      process_classes

      mods = [
              { 
                :name => :model,
                :imports => [:datetime, 'opmix.mix', 'vibe.data.json'],
                :structs => @dlang_structs,
                :enums => @dlang_enums,
              }
             ]

      package = Package.new({ 
                              :name => @package_id,
                              :modules => mods,
                              :pkg_full => @pkg_full,
                            })
      package.generate

    end

    def process_enums
      @enums = model.enums.select {|e| packages_contains_item?(packages, e) }
      @dlang_enums = []
      @enums.each do |enum|
        @dlang_enums << { 
          :name => enum.name,
          :json_support => true,
          :values => enum.values.map{|v| { :name => patch_enum_name(v.name) } }
        }
      end
    end

    def process_classes
      @dlang_structs = []
      @classes = model.classes.select {|c| packages_contains_item?(packages, c) }
      @classes.each do |c|
        next if c.is_template_class? or c.is_templated_class?
        next if @non_generated.include? c.name.to_sym
        data_class = { 
          :name => c.name, :members => [], :protection => :public,
          :doc => c.descr,
          :mixins =>
          [
           { :t_arg => :op_equals },
          ],
        }
        c.members.each do |m|
          type = get_type(m.type)
          init = nil
          if @seq_or_map.match m.type.name
            init = "new #{type}()"
          end
          data_class[:members] << { 
            :name => m.name,
            :type => type,
            :protection => :public,
            :doc => m.descr
          }
        end
        @dlang_structs << data_class
      end
    end

    def get_type(t)
      if t.class == Klass and t.is_templated_class?
        template_binding = model.items[t.template_binding]
        template_binding_signature = model.items[template_binding.signature]
        signature_owner = template_binding_signature.parent
        if signature_owner.name == 'j_map'
          referenced_type = model.items[template_binding.parameter_substitutions[0][:actual]]
          return "#{make_id(referenced_type.name).cap_camel}[string]"
        elsif signature_owner.name == 'list'
          referenced_type = model.items[template_binding.parameter_substitutions[0][:actual]]
          return "#{make_id(referenced_type.name).cap_camel}[]"
        end
        return t.to_s
      end

      t = t.name
      if not @primitives.include? t
        if (t == 'date') or (t =~/^time$/i)
          found = make_id(:date_time).cap_camel
        else
          found = make_id(t.downcase).cap_camel
        end
      else
        found = t
      end

      return found
    end

  end
end


