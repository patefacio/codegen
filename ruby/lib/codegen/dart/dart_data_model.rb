require 'codegen'
require 'codegen/attributes'
require 'codegen/id'
require 'codegen/xmi/model'
require 'codegen/dart/cg'
require 'pathname'

include Codegen
include Codegen::Dart
include Codegen::Xmi

module Codegen::Dart

  class DataModel
    extend Attributes

    attr_reader :enums, :classes, :type_map, :primitives, \
    :seq_or_map

    attribute_defaults({ 
                         :model => nil, 
                         :lib_id => nil,
                         :packages => nil
                       })

    def initialize(opts={ })
      set_attributes(opts)
      @primitives = [ 'num', 'int', 'double', 'String', 'bool' ]
      @type_map = { }
    end

    def create_lib
      process_enums
      process_classes
      lib = Lib.new({ 
                      :id => make_id(lib_id),
                      :imports =>
                      [
                       :json,
                      ],
                      :namespace => ['plus',],
                      :parts => 
                      [
                       { 
                         :id => 'data_model',
                         :no_part_impl => true,
                         :classes => @dart_classes,
                         :enums => @dart_enums,
                       }
                      ],
                      :json_sample_test => true,
                    })
      lib.generate
      return lib
    end

    def process_enums
      @enums = model.enums.select {|e| packages_contains_item?(packages, e) }
      @dart_enums = []
      @enums.each do |e|
        @dart_enums << { 
          :id => e.name,
          :values => e.values.map{|v| patch_enum_name(v.name) }
        }
      end
    end

    def get_type(t)
      if t.class == Klass and t.is_templated_class?
        template_binding = model.items[t.template_binding]
        template_binding_signature = model.items[template_binding.signature]
        signature_owner = template_binding_signature.parent
        if signature_owner.name == 'j_map'
          referenced_type = model.items[template_binding.parameter_substitutions[0][:actual]]
          return "Map<String, #{make_id(referenced_type.name).cap_camel}>"
        elsif signature_owner.name == 'list'
          referenced_type = model.items[template_binding.parameter_substitutions[0][:actual]]
          return "List<#{make_id(referenced_type.name).cap_camel}>"
        end
        return t.to_s
      end

      t = t.name
      if (t == 'date') or (t =~ /^time$/i)
        return make_id(:date_time).cap_camel
      elsif (t =~ /(double\b|int\b)/i)
        return $1
      else
        return make_id(t.downcase).cap_camel
      end
    end

    def process_classes
      @classes = model.classes.select {|c| packages_contains_item?(packages, c) }
      non_generated = [:map, :sequence, :time_value, :date]
      @dart_classes = []
      @classes.each do |c|
        next if c.is_template_class? or c.is_templated_class?
        next if non_generated.include? c.name.to_sym

        data_class = { 
          :id => c.name, :members => [], :public => true,
          :ctor_named => true, :json => true, :descr => c.descr,
          #:no_class_impl => true,
        }

        # Add the members
        c.members.each do |m|
          begin
            type = get_type(m.type)
            init = nil
#            if m.type.class == Klass and m.type.is_templated_class?
            if !primitives.include? type and type != 'DateTime' and m.type.class != Enumeration
              init = "new #{type}()"
            end
            data_class[:members] << { 
              :id => m.name,
              :type => type,
              :init => init,
              :public => true,
              #:access => :ro,
              :descr => m.descr
            }
          rescue Exception => e
            warn "Failed to handle member #{m.name} of #{c.name}!"
            raise e
          end
        end

        @dart_classes << data_class

      end
    end
  end
end

