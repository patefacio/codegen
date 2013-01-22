################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'tenjin'
require 'codegen/cpp'
require 'codegen'
require 'yaml'
require 'place'
$cpp = ::Codegen::Cpp
$klass = $cpp::CppClass

cpu_info = open('/proc/cpuinfo', 'r').read
processor_tags = cpu_info.split(/processor\s*:\s*/)
first_processor_data, rest = $1, $2 if processor_tags[1] =~ /(\d+)\s+(.*)/m
raise "bad parse cpu info" if !first_processor_data

processor_keys_original = []
processor_keys = []
rest.split("\n").each do |line|
  next if line =~ /^\s*$/
  key, value = $1, $2 if (line =~ /^([\w\s]+):(.*)$/)
  raise "bad parse cpu info (k,v pairs)" if !key and !value
  processor_keys_original << key  
  key, value = key.strip.gsub(' ', '_').downcase, value.strip
  processor_keys << key
end

map_key_normalalization = %q^

void ctor_default_init() { 

  boost::regex processor_split_regex("processor\\\\s*:\\\\s*");
  boost::regex split_line_regex("\\n");
  boost::regex line_entry_regex("\^([\\\\w\\\\s]+):\\\\s*(.*)$");
  boost::regex empty_line_regex("\^\\\\s*$");
  boost::regex just_whitespace_regex("\\\\s+");
  std::string const cpu_info_file("/proc/cpuinfo");
  std::ifstream cpu_info_stream(cpu_info_file.c_str());
  std::string text((std::istreambuf_iterator<char>(cpu_info_stream)), std::istreambuf_iterator<char>());

  // split the cpuinfo by processor entries 
  typedef std::vector< std::string > Tokens_t;
  Tokens_t tokens;
  boost::regex_split(std::back_inserter(tokens), text, processor_split_regex);
  Tokens_t::const_iterator processor_end(tokens.end());

  Processor empty_processor;
  processors_.assign(tokens.size(), empty_processor);
  size_t i(0);
  for(Tokens_t::const_iterator processor_it(tokens.begin()); processor_it != processor_end; ++processor_it, ++i) { 
    std::string processor_text(*processor_it);
    // first pull off the processor number
    size_t new_line_pos(processor_text.find_first_of('\\n'));
    if(new_line_pos != std::string::npos) { 
      std::string processor_id(processor_text.substr(0, new_line_pos));
      Processor &processor(processors_[i]);
      processor.processor_ = processor_id;
      processor_text.erase(0, new_line_pos);
      // split the lines by key/value
      Tokens_t lines;
      boost::regex_split(std::back_inserter(lines), processor_text, split_line_regex);
      Tokens_t::const_iterator lines_end(lines.end());
      for(Tokens_t::const_iterator lines_it(lines.begin()); lines_it != lines_end; ++lines_it) { 
         if(boost::regex_match(*lines_it, empty_line_regex)) { 
           continue;
         }

         boost::smatch matches;
         bool result(boost::regex_match(*lines_it, matches, line_entry_regex));
         if(result) { 

           std::string key(matches[1].first, matches[1].second);
           boost::trim(key);
           boost::to_lower(key);

           std::string key_no_whitespace(
             boost::regex_replace(key, just_whitespace_regex, "_"));

           processor.proc_key_to_value_[key_no_whitespace] = 
             std::string(matches[2].first, matches[2].second);

         } else { 
           throw fcs::utils::exception::make_exception< System_file_parse_exception >
             ("parsing_cpuinfo", __LINE__, __FILE__) 
             << System_file_parse_exception::filename_tag(cpu_info_file);
         }
      } 
    }

  }
}

^

cpu_info_dump = %q^
void dump(std::ostream &out) const { 
  out << "----- cpu_info -----\n";
  Processor_list_t::const_iterator it(processors_.begin());
  Processor_list_t::const_iterator end(processors_.end());
  for(; it != end; ++it) { 
    it->dump(out);
  }
}
^

map_key_accessors = %q^
////////////////////////////////////////////////////////////////////////////////
// Potentially useful keys that show up on Linux 2.6.32-24-generic
////////////////////////////////////////////////////////////////////////////////
<?rb @processor_keys.each do |k| ?>
std::string #{k}() const { 
  std::string result;
  Proc_key_to_value_t::const_iterator found(proc_key_to_value_.find("#{k}"));
  if(found != proc_key_to_value_.end()) { 
    result = found->second;
  }
  return result;
}

<?rb end ?>

void dump(std::ostream &out) const { 

  cpu_set_t mask;
  long affinity(sched_getaffinity(0, sizeof(mask), &mask));
  if(0 == affinity) { 
    out << "Running from process: " << getpid() 
        << "\n processor count: " << CPU_COUNT(&mask)
        << "\n processor 0 set: " << CPU_ISSET(0, &mask)
        << "\n processor 1 set: " << CPU_ISSET(1, &mask) << std::endl;
    out << "----- processor -----\\n";
  }
<?rb @processor_keys.each do |k| ?>
  out << "\\t#{k}:" << #{k}() << "\\n";
<?rb end ?>
}

^
template = Tenjin::Template.new
template.convert map_key_normalalization
map_key_normalalization = template.render({ :processor_keys => processor_keys })

template.convert map_key_accessors
map_key_accessors = template.render({ :processor_keys => processor_keys })

template.convert cpu_info_dump
cpu_info_dump = template.render({ :processor_keys => processor_keys })

classes = 
  [
   $klass.new( 
              { 
                :name => 'System_file_parse_exception',
                :brief => 'Indicates parsing of system file failed',
                :public_typedefs => 
                [
                 'typedef boost::error_info<struct tag_filename_tag, std::string > filename_tag'
                ],
                :boost_exception => true,
                :header_only => true,
              }),

   $klass.new( 
              { 
                :name => 'Umask_scoped_set',
                :brief => 'Sets umask to specified value until destruction and sets it back',
                :descr => '
A typical use of this is to set the umask for a process to
provide settings of system resources (files, mutexes, mappings,...)
to allow group members in. For instance, an app may create shared
memory, and therefore an entry in /dev/shm, but to share it
the permissions must work. umask settings play a role.
',
                :header_only => true,
                :public_header_section => true,
                :include_unit_test => true,
                :header_includes =>
                [
                 'sys/types.h',
                 'sys/stat.h'
                ],
                :additional_ctor_parms => [ [ 'mode_t', 'new_mode'], ],
                :members =>
                [
                 { 
                   :cpp_type => 'mode_t',
                   :brief => 'Original mode, restored to on destruction',
                   :name => 'previous_mode',
                   :init => 'umask(new_mode)',
                   :access => Codegen::Access::RO,
                 }
                ]
              }),

   $klass.new(
              { 
                :name => 'Cpu_info',
                :descr => '
Class to parse the cpuinfo file. This might be of use to interrogate
from code the stats of the machine for better enabling <apple to apple>
comparisons.
',
                :singleton => true,
                :streamable_inline => true,
                :header_includes => [ 
                                      'fcs/linux_specific/system_file_parse_exception.hpp',
                                      'fcs/utils/exception/make_exception.hpp',
                                      'fstream', 'iterator', 'boost/regex.hpp', 'boost/thread.hpp',
                                      'sys/types.h', 'unistd.h', 'boost/algorithm/string.hpp',
                                     ],
                :include_unit_test => true,
                :public_typedefs => [ 'typedef std::vector< Processor > Processor_list_t', ],
                :members => 
                [
                 { 
                   :name => 'processors',
                   :cpp_type => 'Processor_list_t',
                   :pass_by_ref => true,
                   :access => Codegen::Access::RO,                                 
                 },
                ],
                :ctor_default_init_method => true,
                :additions_private_header => map_key_normalalization,
                :additions_public_header => cpu_info_dump,
                :additional_classes_come_first => true,
                :additional_classes => 
                [
                 $klass.new(
                            { 
                              :struct => true,
                              :name => 'Processor',
                              :descr => '
Information stored on a processor basis in cpuinfo.
The fields in this class are dynamically generated from parsing
cpuinfo.
',

                              :streamable_inline => true,
                              :friend_decls => ['friend class Cpu_info'],
                              :additions_public_header => map_key_accessors,
                              :public_typedefs => 
                              [
                               'typedef std::map< std::string, std::string > Proc_key_to_value_t',
                              ],
                              :members => 
                              [
                               {
                                 :name => 'proc_key_to_value',
                                 :cpp_type => 'Proc_key_to_value_t',
                                 :pass_by_ref => true,
                                 :access => Codegen::Access::RO,                                 
                               },
                               { 
                                 :name => 'processor',
                                 :cpp_type => 'std::string',
                                 :access => Codegen::Access::RO,
                               },
                              ],
                            }
                            )
                ]
              }
              )
  ]

lib = $cpp::Library.new({ 
                          :classes => classes,
                          :header_only => true,
                          :static_only => true,
                          :namespace => ['fcs', 'linux_specific'],
                          :no_api_decl => true,
                        })
