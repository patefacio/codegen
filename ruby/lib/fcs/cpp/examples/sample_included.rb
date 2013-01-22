require 'codegen/mongoid'  
Pod = Podule::Pod
Enum = Podule::Enum

p = Podule.new(:database => 'trading', 
               :name => 'sample_included',
               :namespace => [ 'fcs', 'examples', 'mongoid'])

Pod.new(:SampleIncluded,
        [
         [:Integer, :how_many],
         [:String, :some_text],
         [:Integer, :this_many],
        ]
        )

p.generate_code

