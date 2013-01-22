require 'pp'
require 'codegen/dlang/package'
include Codegen::Dlang

mods = 
  [
   { 
     :name => :address_book,
     :imports => [],
     :unit_test => true,
     :structs =>
     [
      {
        :name => :address,
        :members =>
        [
         { :name => :street, :type => :string },
         { :name => :zip_code, :type => :string },
         { :name => :state, :type => :string },
         { :name => :country, :type => :string },
        ]
        
      },
      { 
        :name => :address_book,
        :aliases =>
        [
         aarr(:k => :string, :v => :address, :base_name => :email_address),
        ],
        :members => 
        Ia([
         { :name => :email_address_map },
        ])
      },
     ],
   }     
  ]

Package.root_name(:examples)

pkg = Package.new(
                  :name => 'samples',
                  :modules => mods,
                  :is_root => true,
              )

pkg.generate
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################

