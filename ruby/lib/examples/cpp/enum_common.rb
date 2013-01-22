def make_enum_values(prefix, count)
  (0..count).map {|i| "#{prefix}_#{i}"}
end

$enum_samples = [
                 {
                   :name => 'first', 
                   :values => make_enum_values('first', 5),
                 },
                 {
                   :name => 'second', 
                   :values => make_enum_values('second', 6),
                   :supports_picklist => true,
                 },
                 {
                   :name => 'mask_first', 
                   :values => make_enum_values('masked_first', 6),
                   :mask => true,
                 },
                 {
                   :name => 'mask_second', 
                   :values => make_enum_values('masked_second', 6),
                   :mask => true
                 },
                 {
                   :name => 'with_assignments', 
                   :values => [ 'wa_42', 'wa_77' ],
                   :assigned_values => [ 42, 77 ],
                   :supports_picklist => true,
                 },
                 {
                   :name => 'shorten_long_name', 
                   :values => make_enum_values('shorten_long_name', 5),
                   :pick_list_text_proc => proc {|x| x.gsub(/shorten_long_name/, 'sln')}
                 },
                ]

def make_enum_specific(enum, prefix)
  result = enum.clone
  result[:name] = "#{prefix}_#{result[:name]}"
  result[:values] = result[:values].map { |v| "#{prefix}_#{v}" }
  result[:brief] = "An enum specific to #{prefix} with name #{result[:name]}"
  return result
end

$some_class = { 
  :name => 'some_class',
  :public_header_section => true,
  :header_includes => 
  [
   'iostream'
  ],
  :forward_enums => $enum_samples.map { |e| make_enum_specific(e, 'FORWARD') } + 
  [
   {
     :brief => "Dohh - clearly self explanatory",
     :name => 'FORWARD_ANSWER_OF_UNIVERSE', 
     :const_value => 42,
   },
  ],
  :enums => $enum_samples.map { |e| make_enum_specific(e, 'SCOPED') } + 
  [
   {
     :brief => "Dohh - clearly self explanatory",
     :name => 'ANSWER_OF_UNIVERSE', 
     :const_value => 42,
   },
  ],
  :members =>
  [
   { 
     :name => 's'
   }
  ]  
}

$some_other_class = { 
  :name => 'some_other_class',
  :public_header_section => true,
  :header_includes => 
  [
   'iostream'
  ],
  :enums => $enum_samples.map { |e| make_enum_specific(e, 'SCOPED') },
  :members =>
  [
   { 
     :name => 's'
   }
  ]  
}
