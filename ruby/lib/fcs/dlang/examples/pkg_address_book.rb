require 'pp'
require 'codegen/dlang/package'
include Codegen::Dlang

mods = 
  [
   { 
     :name => :phone,
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
                  :name => 'phone',
                  :modules => mods,
                  :is_root => true,
              )

pkg.generate

