#######################################################################
# Support for creating class groups (Experimental)
#######################################################################
require 'codegen'
require 'tenjin'
require 'place'
module Codegen::Cpp

  class ClassGroup
    
    attr_accessor :name, :namespace, :classes, :methods, :virtual

    def mark_prefix text
      if virtual
        "virtual #{text}"
      else
        text
      end
    end

    def initialize(data={ })
      @engine = Tenjin::Engine.new(:path => [ Place['rb_codegen_tmpl'].to_s])
      @virtual = data[:virtual]
      @name = data[:name]
      @namespace = data[:namespace]
      @classes = (data[:classes] or [])
      @methods = (data[:methods] or [])

      new_classes = []
      class_index = 0
      @classes.each do |klass|
        if virtual
          klass.bases_public << [ "#{name}_base", '' ]
        else
          klass.public_static_consts << "static int const #{name.upcase}_ID = #{class_index}"
        end
        class_index += 1
        method_stubbed_impls = []
        @methods.each do |method|
          return_type, name, arg_list, brief, descr = method[:return], method[:name], method[:args], method[:brief], method[:descr]
          method[:arg_types] = arg_list.map {|al| al[0] }
          method[:arg_names] = arg_list.map {|an| an[1] }
          method[:arg_typed_names] = arg_list.map {|atn| "#{atn[0]} #{atn[1]}" }
          klass.additions_public_header << %Q{ 
//! #{brief}
#{mark_prefix return_type} 
#{name}(#{method[:arg_typed_names].join(', ')});
}
          method_stubbed_impls << %Q{inline #{return_type}
#{klass.name}::#{name}(#{method[:arg_typed_names].join(', ')}) {
#{Codegen.protect_block("#{name} impl")}
  pantheios::log(PANTHEIOS_SEV_DEBUG, "#{klass.name}::#{name}");
}}
        end
        new_classes << CppClass.new({ 
                                      :name => klass.name + '_inl',
                                      :no_class => true,
                                      :additions_header_namespace => method_stubbed_impls,
                                      :header_includes =>
                                      [
                                       'pantheios/pantheios.hpp',
                                       lambda { klass.header_as_include },
                                      ]
                                    })
      end

      all_headers = new_classes.map {|c| lambda { c.header_as_include } }

      if virtual
        new_classes << 
          CppClass.new({ 
                         :name => "#{name}_base",
                         :additions_public_header => [@engine.render("cpp_class_group_base.tmpl", 
                                                                     { :me => self })]
                       })
      else
        new_classes << 
          CppClass.new({ 
                         :name => "#{name}_dispatch",
                         :no_class => true,
                         :header_includes => all_headers,
                         :additions_header_namespace => [@engine.render("cpp_class_group_dispatch.tmpl", 
                                                                        { :me => self })]
                       })

        new_classes << 
          CppClass.new({ 
                         :name => "#{name.capitalize}_dispatcher",
                         :struct => true,
                         :additions_public_header => 
                         [
                          "
template < typename T >
#{name.capitalize}_dispatcher(T *t) : 
  id_(T::#{name.upcase}_ID), 
  object_(t) {
}
"
                         ],
                         :members =>
                         [
                          { 
                            :name => 'id',
                            :brief => 'Id of the class type this dispatcher holds',
                            :cpp_type => 'int',
                            :member_init => true,
                            :public => true,
                          },
                          {
                            :name => 'object',
                            :brief => 'Object to dispatch functions on',
                            :cpp_type => 'void *',
                            :member_init => true,
                            :public => true,
                          }
                         ],
                       })

      end


      @classes += new_classes
    end

    

  end

end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
