require 'pp'

module Codegen

  def instantiate(klass, obj)
    if klass.class == Method
      return klass.call(obj)
    end

    case obj
    when Array
      result = []
      obj.each do |item|
        result << instantiate(klass, item)
      end
      return result
    when Hash
      return klass.new(obj)
    when NilClass
      return klass.new({ })
    when klass
      return obj
    else
      raise ArgumentError, "#{obj} of type #{obj.class} is not of type #{klass}"
    end
  end
  module_function :instantiate

  module AttributeSetter

    def set_attributes(opts={}, strict=true)
      start_with = self.class.get_attribute_defaults
      if strict
        invalid = opts.keys.find_all {|attr| not start_with.has_key? attr  }
        if not invalid.empty? 
          raise ArgumentError, "#{self.class} does not support option #{invalid}" 
        end
      end
      start_with.merge!(opts)
      start_with.each_pair do |k,v|
        attr_name = "@#{k}"
        if not instance_variable_defined?(attr_name) or opts.has_key? k
          instance_variable_set(attr_name, v) 
          opts.delete k
        end
      end
    end

    def required_attributes_any(required)
      if required.count {|a| not instance_variable_get("@#{a}").nil?} == 0
        raise ArgumentError, 
        "At least of #{required} must be set on '#{self.class}' have #{self.instance_variables}"
      end
    end

    def required_attributes(required)
      required.each do |attr| 
        if instance_variable_get("@#{attr}").nil?
          raise ArgumentError, 
          "Option '#{attr}' must be set on '#{self.class}' have #{self.instance_variables}"
        end
      end
    end

    def disallowed_attributes(required)
      required.each do |attr|
        if not instance_variable_get("@#{attr}").nil?
          raise ArgumentError, "Option '#{attr}' must not be set on #{self.class}"
        end
      end
    end

    def add_attributes(opts)
      opts.each_pair do |k,v|
        instance_variable_set("@#{k}", v)
      end
    end

    def attributes_hash
      result = { }
      instance_variables.each do |attr| 
        v = instance_variable_get(attr)
        result[attr[1..-1]] = v if not v.nil?
      end
      return result
    end

    def define_hash_from_object_list(attr, rest={})
      rest[:index] = :name if rest[:index].nil?
      rest[:prefix] = 'hash_' if rest[:prefix].nil?
      hash_attr_name = "@#{rest[:prefix]}#{attr}"
      new_hash = Codegen.hash_from_object_list(instance_variable_get("@#{attr}"),
                                               :index => rest[:index])
      instance_variable_set(hash_attr_name, new_hash)
    end

    def initialize_attribute(klass, attr, rest={ })
      value = instance_variable_get("@#{attr}")
      instantiated = Codegen.instantiate(klass, value)
      instance_variable_set("@#{attr}", instantiated)
      return value
    end
  end

  module Attributes

    def defaults
      return @attribute_defaults
    end

    def attribute_defaults(defaults)
      include AttributeSetter
      @attribute_defaults = defaults
      def get_attribute_defaults
        if @attribute_defaults.class == Proc
          @attribute_defaults.call
        else
          Marshal.load( Marshal.dump(@attribute_defaults) )
        end
      end

      if defaults.class == Proc
        attrs = defaults.call.keys
      else
        attrs = defaults.keys
      end

      attr_reader(*attrs)
    end
  end
end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
