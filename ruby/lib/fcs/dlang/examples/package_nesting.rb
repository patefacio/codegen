require 'pp'
require 'codegen/dlang/package'
include Codegen::Dlang

mods = 
  [
   { 
     :name => :outer,
     :open_source => true,
     :imports => ['std.stdio', 'std.conv', 'std.container', 'std.datetime', 'std.typetuple', 'std.typecons'],
     :classes =>
     [
      { 
        :name => :some_exported_class,
        :protection => :export,
        :doc => 'This is my package class',
      },
      Package({ 
        :name => :some_package_class,
        :doc => 'This is my package class',
      }),
      Protected({ 
        :name => :some_protected_class,
        :doc => 'This is my protected class',
      }),
      Private({ 
        :name => :some_private_class,
        :doc => 'This is my private class',
      }),
      { 
        :name => :outer,
        :enums =>
        [
         { 
           :name => :this_is_a_color, :doc => "Dont forget,\nwe support RGB formatting",
           :values =>
           [
            { :name => :red }, 
            { :name => :green },
            { :name => :blue },
           ]

         }
        ],
        :structs =>
        [
         { 
           :name => :nested_struct, :doc => "This\nstruct\nrocks\n\t!!!",
           :members =>
           [
            { :name => :ns_top, :type => :string, :init => '"ns_top"' }
           ]
         }
        ],
        :classes =>
        [
         { 
           :name => :nested_class,
           :doc => 'This is a nested class, owned by RateCurve',
           :classes => 
           [
            { 
              :name => :deeper_nesting, 
              :members => [
                           { :name => :nesting_index, :type => :int, :init => '25*3' },
                           { :name => :nesting_text, :type => :string, :init => '"sweet"' },
                          ],
              :classes => [{ :name => :crazy_nesting, :protection => :private }] }
           ]
         }
        ],
        :aliases =>
        [
         { :name => :date, :aliased => 'DateTime', :doc => "Good stuff\nuse it well" },
         { :name => :rate, :aliased => 'double' },
         { :name => :date_rate, :aliased => 'Tuple!(DateTime, Rate)' },
         Export({ :name => :exported_container_type, :aliased => 'Array!int', :doc => "You can access\nme from a dll!!" }),
        ],
        :members =>
        [
         Private({ 
                   :name => :_impl,
                   :type => :int,
         }),
         Export({ 
                   :name => :_impl2,
                   :type => :nested_struct,
         }),
         Package({ 
                   :name => :_impl3,
                   :type => :int,
         }),
        ],
      }
     ]
     
   }
  ]

Package.root_name(:examples)

pkg = Package.new(
                  :name => 'nesting',
                  :modules => mods,
              )

pkg.generate

