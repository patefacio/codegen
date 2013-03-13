require 'codegen/id'
require 'xmlsimple'
require 'pp'
require 'set'

$modeled_types = { }
$all_types = Set.new

module Codegen

  module Xmi

    class ModelItem
      extend Attributes

      @@renames = { 
        "xmi:id" => :xmi_id, 
        "xmi:type" => :xmi_type,
        "xmi:uuid" => :xmi_uuid,
        "xmi:idref" => :xmi_idref,
      }

      attr_reader :data, :element_type, :xmi_id, :xmi_type, :name, :parent, :children

      def to_s
        "(#{self.class}, '#{name}', #{element_type}, #{xmi_type}, #{xmi_id})"
      end

      def initialize(item_data, parent = nil, element_type = nil)
        @data = item_data
        @parent = parent
        @element_type = element_type
        @children = { }
        item_data.each_pair do |k,v|
          case v
          when Array
            @children[k] = v.map { |i| create_item(i, self, k) }
          when Hash
            raise RuntimeError("Unexpected Hash Found at key: #{k}")
          else
            k = (@@renames[k] or k)
            instance_variable_set("@#{k}", v)
            if k == :xmi_type
              $all_types << self.xmi_type 
            end
          end
        end
        raise RuntimeError, "ModelItem has no parent: #{item_data}" if parent.nil? and @name.nil?
        if not xmi_id.nil?
          raise RuntimeError, "Found item twice: #{xmi_id}" if $modeled_types.has_key? xmi_id
          $modeled_types[xmi_id] = self
        else
          #puts "No xmi_id for #{name} => #{item_data}"
        end
      end
      
      def visit(functor)
        @children.each_pair do |k, v|
          v.each do |mi|
            mi.visit(functor)
          end
        end
        #puts "Visited #{self.name} elm_type => #{self.element_type}, class => #{self.class} type => #{self.xmi_type}"
        functor.call(self)
      end
    end

    class Klass < ModelItem

      def members
        return (children["ownedAttribute"] or [])
      end

      def descr
        if children["ownedComment"]
          return children["ownedComment"][0].data["body"].gsub('',"\n")
        else
          return nil
        end
      end

      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
        if !children["templateBinding"].nil?
          template_items = children["templateBinding"] 
          @template = template_items[0]
          if template_items.size > 1
            puts "WARNING: multiple templates for #{name}"
          end
        end
      end
    end

    class Member < ModelItem
      attr_reader :descr

      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
        @type = data['type']
        if children["ownedComment"]
          @descr =  children["ownedComment"][0].data["body"].gsub('',"\n") 
        else
          @descr = nil
        end
      end

      def type
        return $modeled_types[@type]
      end

    end

    class TemplateBinding < ModelItem
      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
        #@signature = children[""]
      end
    end

    class Association < ModelItem
      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
      end
    end

    class Enumeration < ModelItem
      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
      end
      def values
        return (children["ownedAttribute"] or [])
      end
    end

    class TemplateParameter < ModelItem
      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
      end
    end

    class TemplateSignature < ModelItem
      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
      end
    end

    class Property < ModelItem
      def initialize(data, parent, uml_key)
        super(data, parent, uml_key)
        @type = data['type']
      end
    end


    def create_item(data, parent, uml_key)
      result = nil
      case data["xmi:type"]
      when "uml:Class"
        if uml_key == "ownedParameteredElement"
          result = TemplateParameter.new(data, parent, uml_key)
        else
          result = Klass.new(data, parent, uml_key)
        end
      when "uml:Property"
        result = Member.new(data, parent, uml_key)
      when "uml:TemplateBinding"
        result = TemplateBinding.new(data, parent, uml_key)
      when "uml:TemplateSignature"
        result = TemplateSignature.new(data, parent, uml_key)
      when "uml:Association"
        result = Association.new(data, parent, uml_key)
      when "uml:Enumeration"
        result = Enumeration.new(data, parent, uml_key)
      else
        result = ModelItem.new(data, parent, uml_key)
      end
      
      return result
    end

    class Model
      extend Attributes

      attribute_defaults({ 
                           :file_path => nil,
                           :root_item => nil,
                           :items => { }
                         })

      def initialize(opts={ })
        set_attributes(opts)
        process_model
      end

      def process_node(node)
        data = node["packagedElement"]
        data = packaged_element(data) if data
      end

      def classes()
        items.select {|k,v| v.class == Klass }.map { |k,v| v }
      end

      def enums()
        items.select {|k,v| v.class == Enumeration }.map { |k,v| v }
      end

      def process_model
        xml_data = XmlSimple.xml_in(file_path)
        @root_item = ModelItem.new xml_data["Model"][0]
        @root_item.visit(lambda {|mi| items[mi.xmi_id] = mi })
      end
    end
  end
end



