require 'codegen/mongoid'  
require './sample_included'

#Pod = Podule::Pod
#Enum = Podule::Enum


p = Podule.new(:database => 'trading', 
               :namespace => [ 'samples', 'examples', 'mongoid'],
               :header_includes => ['samples/examples/mongoid/sample_included.hpp'])

Enum.new(:name => :MyChoices, :members => [ :a, :b, :c ])

Pod.new(:Address,
        [
         [:Integer, :number],
         [:String, :street],
         [:String, :zipcode],
         [:String, :state],
         [:MyChoicesEnum, :myChoice],
        ]
        )

Pod.new(:Phone,
        [
         [ :String, :number ],
        ]
        )

Pod.new(:Person,
        [
         [ :Long, :age, { :index => true } ],
         [ :String, :name, { :include_where_equal_find => true, :unique_index => true } ],
         [ :Float, :weight, { :version => 2 } ],
         [ :SampleIncluded, :sample ],
         [ :PhoneArray, :phones ],
         [ :AddressArray, :addresses ],
         [ :StringArray, :aliases, { :version => 3 }  ],
         [ :FloatArray, :alphas ],
         [ :IntegerArray, :lengths ],
         [ :Phone, :emergency_phone, { :version => 1 } ],
         [ :BoolArray, :straight_a_list ]
        ],
        :additional_class_options => { :include_unit_test => true, },
        :collection_support => Podule::CollectionSupport.new(:remove_all => true)
        )

Pod.new(:Team,
        [
         [ :PersonArray, :members ],
        ]
        )

p.generate_code

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
