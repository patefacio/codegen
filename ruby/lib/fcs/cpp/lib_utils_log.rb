################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
require 'place'
include Codegen::Cpp

log_entries = 31
log_methods = []

log_methods << "

void set_log_level(::pantheios::pan_sev_t);

#if defined(DEBUG)
"
(0..log_entries).each do |i|
  log_methods << %Q{ 
template < #{(0..i).map {|i| "typename T#{i}" }.join(', ')} >
inline 
int debug_log(::pantheios::pan_sev_t severity, #{(0..i).map {|i| "T#{i} const& t#{i}" }.join(', ')}) {
  return ::pantheios::log(severity, #{(0..i).map {|i| "t#{i}" }.join(', ')});
}}
end
log_methods << "#else"
(0..log_entries).each do |i|
  log_methods << %Q{ 
template < #{(0..i).map {|i| "typename T#{i}" }.join(', ')} >
inline 
int debug_log(::pantheios::pan_sev_t severity, #{(0..i).map {|i| "T#{i} const&" }.join(', ')}) { return 0; }
}
end
log_methods << "#endif"

lib = 
  Library.new({ 
                :classes => 
                [

                 CppClass.new({ 
                                :name => 'pantheios_debug_log',
                                :no_class => true,
                                :additions_header_namespace => log_methods,
                                :additional_classes => 
                                [
                                ],
                                :header_includes => 
                                [
                                 'pantheios/pantheios.hpp',
                                ],
                              }),
                ],
                :descr => "
Support for log messages that can be conditionally compiled out.
",
                :header_only => true,
                :static_only => true,
                :namespace => ['fcs', 'utils',],
                :no_api_decl => true,
              })

