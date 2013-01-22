################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
require 'place'
require 'pathname'
include Codegen::Cpp

members = []
Place.place.each_pair do |k,v|
  next if !v
  k = k.to_s.gsub(/-/, '_')
  members << { 
    :cpp_type => 'boost::filesystem::path',
    :pass_by_ref => true,
    :name => k,
    :init => "top_ / \"#{Pathname(v).relative_path_from(Place[Place.top])}\"",
    :access => Codegen::Access::RO,
  }
end
classes = [

           CppClass.new({ 
                          :name => 'Place',
                          :singleton => true,
                          :streamable_inline => true,
                          :header_includes => [ 'boost/filesystem/path.hpp', ],
                          :public_header_section => true,
                          :include_unit_test => true,
                          :members => [
                                       { 
                                         :cpp_type => 'boost::filesystem::path',
                                         :name => 'top',
                                         :init => "\"#{Place[Place.top]}\"",
                                         :access => Codegen::Access::RO,
                                       },
                                      ] + members,
                        }),

          ]

lib = Library.new({ 
                    :classes => classes,
                    :header_only => true,
                    :namespace => ['fcs', 'dev'],
                    :no_api_decl => true,
                  })


