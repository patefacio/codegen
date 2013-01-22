require 'codegen/mongoid'  
Pod = Podule::Pod
Enum = Podule::Enum

p = Podule.new(:database => 'trading', 
               :name => 'sample_included',
               :namespace => [ 'samples', 'examples', 'mongoid'])

Pod.new(:SampleIncluded,
        [
         [:Integer, :how_many],
         [:String, :some_text],
         [:Integer, :this_many],
        ]
        )

p.generate_code

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
