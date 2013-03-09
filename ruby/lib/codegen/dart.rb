#######################################################################
# Support for code generation of Dart
#######################################################################
require 'codegen'

module Codegen::Dart

  @@system_imports = 
    %w{  
       async chrome collection core crypto
       html indexed_db io isolate json math
       mirrors scalarlist svg uri utf web_audio
       web_sql 
    }.inject({ }) {|c,i| c[i.to_sym] = "dart:#{i}"; c }.merge(
    %w{
       args fixnum intl logging matcher meta mock scheduled_test serialization
       unittest
    }.inject({ }) {|c,i| c[i.to_sym] = "package:#{i}/#{i}.dart"; c })

  def clean_imports(imports)
    imports.each_index do |i|
      imp = imports[i]
      case imp
      when Symbol
        imports[i] = @@system_imports[imp]
      end
    end
    imports = imports.sort
  end

end

if __FILE__ == $0
  include Codegen::Dart
  print clean_imports([:web_audio, :unittest])
end
    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################


