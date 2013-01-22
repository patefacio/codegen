#!/usr/bin/env ruby
############################################################################
## Script for grepping files recursively through directories.  Files can be
## specified by type (-t), by place (-P), by regex on file name, etc...
############################################################################
require 'optparse'
require 'ostruct'
require 'find'
require 'pp'
require 'place'
require 'fileutils'
require 'set'

$cpp_src_re = /\.(?:cpp|cxx|hpp|hxx|h|inl|cc|c|hh|CC|C|tcc)$/
$cpp_bin_re = /\.(?:o|a|so)$/
$ruby_re = /\.rb|\.rspec$/
$config_re = /\.config$/
$go_re = /\.go$/
$dlang_re = /\.d|\.di$/
$proto_re = /\.proto$/
$python_re = /\.py$/
$html_re = /\.html$/
$xml_re = /\.xml$/
$hdf5_re = /\.(?:hf5|h5)$/
$build_re = /(?:[Mm]akefile|SConscript|SConstruct|CMakefile|Jamfile|Jamroot|\.jam)/
$project_re = /\.(?:vcproj|sln)$/
$org_re = /\.org$/
$el_re = /\.el$/
$docs_re = /\.(?:doc|pdf|ppt)/
$tmpl_re = /\.tmpl$/
$unwanted_re = /(?:~|\.ii|\.s|\.pyc|\.cache|#.*#|CMakeLists.txt)$/

#puts Place.place()
$allowed_types = %w{ cpp cpp_bin python ruby html xml hdf5 build project org docs tmpl go } 
def format_words(words)
  result = []
  while words.length>0
    result << "\t\t\t\t\t" + words.slice!(0..5).join(' ')
  end
  result.join("\n")
end

def resolve_type_shortcuts(t)
  case t
  when 'rb'
    'ruby'
  when 'py'
    'python'
  else
    t
  end
end

options = OpenStruct.new
options.paths = []
options.types = []
options.places = []
options.file_regex = []
options.file_basename_regex = []
options.file_not_regex = []
options.dir_regex = []
options.dir_not_regex = []
options.match_regex = []
options.replace_regex = false
options.replace_to = false
options.include_ignored = false
options.log_evaluation = false
options.join_delimiter = "\n"
optparse = OptionParser.new do |opts|
  opts.banner = """Script for grepping files recursively through directories.
Files can be specified by type (-t), by place (-P), by regex on file name, etc...

Usage: xgrep [options]
"""
  opts.separator ""
  opts.separator "Specific options:"
  opts.on('-h', '--help', 'Display this screen' ) do
    raise "Help Follows"
  end
  opts.on('-c', '--codegen', "Search codegen ruby and templates" ) do |p|
    options.codegen = true
  end
  opts.on('-p', '--path PATH', "Search PATH on all desired files. Default path is '.'" ) do |p|
    options.paths << p
  end
  opts.on('-P', '--place PLACE', "Search on common PLACE:\n#{format_words(['rgem', 'rpath'] + Place.place.keys.sort)}" ) do |p|
    options.places << p
  end
  opts.on('-t', '--type TYPE', "Search TYPE files:\n#{format_words($allowed_types)}" ) do |t|
    options.types << resolve_type_shortcuts(t)
  end
  opts.on('-f', '--file_regex FILE_REGEX', "Only search files matching FILE_REGEX" ) do |f|
    options.file_regex << /#{f}/
  end
  opts.on('-v', '--file_not_regex FILE_NOT_REGEX', "Skip files matching FILE_NOT_REGEX" ) do |v|
    options.file_not_regex << /#{v}/
  end
  opts.on('-b', '--file_basename_regex FILE_BASENAME_REGEX', "Only search files with basename matching FILE_BASENAME_REGEX" ) do |f|
    options.file_basename_regex << /#{f}/
  end
  opts.on('-D', '--dir_regex DIR_REGEX', "Only search directories matching DIR_REGEX" ) do |d|
    options.dir_regex << /#{d}/
  end
  opts.on('-V', '--dir_not_regex DIR_NOT_REGEX', "Skip directories matching DIR_NOT_REGEX" ) do |d|
    options.dir_not_regex << /#{d}/
  end
  opts.on('--include_ignored', "If true does not skip standard ignored files" ) do |m|
    options.include_ignored = true
  end
  opts.on('--shallow', "Do not recurse. If no paths specified the default is '.' and shallow" ) do |m|
    options.shallow = true
  end
  opts.on('-i', '--ignore_case', "Does grep -i" ) do |m|
    options.ignore_case = true
  end
  opts.on('-m', '--match_regex MATCH_REGEX', "What to mach - egrep format" ) do |m|
    options.match_regex << m
  end
  opts.on('-s', '--space_delimiter', "Output files with spaces" ) do |m|
    options.join_delimiter = ' '
  end
  opts.on('--replace_regex REPLACE_REGEX', "Regex to replace text in file all matches" ) do |m|
    options.replace_regex = /#{m}/
  end
  opts.on('--replace_to REPLACE_TO', "Text to replace to for replace_regex" ) do |m|
    options.replace_to = m
  end
  opts.on('--log_evaluation', "Text to replace to for replace_regex" ) do |log_evaluation|
    options.log_evaluation = log_evaluation
  end
end
begin
  optparse.parse!
rescue Exception => e
  puts e.message
  puts options
  puts optparse
  exit
end

class XGrep
  # List of paths to search
  attr_reader :paths
  # List of named places to search
  attr_reader :places
  # Optional regex matching entire path used for selecting desired files
  attr_reader :file_regex
  # Optional regex matching entire file basename used for selecting desired files
  attr_reader :file_basename_regex
  # Optional regex specifying which files to skip
  attr_reader :file_not_regex
  # Optional regex specifying which directories to include
  attr_reader :dir_regex
  # Optional regex specifying which directories to exclude
  attr_reader :dir_not_regex
  # Regex specifying what text to file
  attr_reader :match_regex
  # Generated list of files
  attr_reader :files
  # For debug purposes log's folders/files as they are examined
  attr_reader :log_evaluation
  # List of types to search, e.g. python, ruby, cpp
  attr_reader :types
  attr_reader :join_delimiter
  # If true the grep will be done with -i
  attr_reader :ignore_case
  # If set will not recurse into directories
  attr_reader :shallow

  def initialize(options)
    @paths = options.paths
    @places = options.places
    @types = options.types

    if places.select { |p| p =~ /rgem/ }.length > 0
      require 'rubygems'
      require 'sequel'
      @types << 'ruby'
      @paths += $:.select { |p| p =~/gems/  }
    end
    if places.select { |p| p =~ /rpath/ }.length > 0
      @types << 'ruby'
      @paths += $:
    end
    if options.codegen
      @paths << Place['ruby_lib']
      @types += [ 'ruby', 'tmpl' ]
      puts "#{places.inspect}"
      puts "#{types.inspect}"
    end
    @types = Set.new(@types).to_a
    @paths += options.places.select {|p| Place[p] }.collect { |p| Place[p] }
    @file_regex = options.file_regex
    @file_basename_regex = options.file_basename_regex
    @file_not_regex = options.file_not_regex
    @dir_regex = options.dir_regex
    @dir_not_regex = options.dir_not_regex
    if !options.include_ignored
      @file_not_regex << /~$/
      @dir_not_regex << /\.(?:svn|git)$/
    end
    @match_regex = options.match_regex
    @files = []
    @log_evaluation = options.log_evaluation
    @join_delimiter = options.join_delimiter
    @ignore_case = options.ignore_case
    @shallow = options.shallow
    if @paths.empty?
      @paths << Dir.pwd
      @shallow = true
    end

    find_files
  end

  # Finds files to grep on
  def find_files
    #puts @paths.join("\n")
    @paths.each do |p|
      Find.find(p.to_s) do |path|
        stop_shallow = ((p != path) and @shallow)
        if File.directory? path
          @dir_regex.each do |r|
            puts "Evaluating #{r} on dir #{path} gives => #{r.match(path)}" if log_evaluation
            Find.prune if !r.match(path) or stop_shallow
          end
          @dir_not_regex.each do |r|
            puts "Evaluating not_regex #{r} on dir #{path} gives => #{r.match(path)}" if log_evaluation
            Find.prune if r.match(path.to_s) or stop_shallow
          end
        else
          @file_regex.each do |r|
            puts "Evaluating #{r} on #{path} gives => #{r.match(path.to_s)}" if log_evaluation
            Find.prune if !r.match(path.to_s)
          end
          @file_not_regex.each do |r|
            puts "Evaluating not_regex #{r} on #{path} gives => #{r.match(path.to_s)}" if log_evaluation
            Find.prune if r.match(path.to_s)
          end
          @file_basename_regex.each do |r|
            basename = Pathname.new(path).basename
            puts "Evaluating #{r} on #{path} gives => #{r.match(basename)}" if log_evaluation
            Find.prune if !r.match(basename)
          end
          if types.length > 0
            matched = false
            @types.each do |type|
              case type
              when 'cpp'
                matched = $cpp_src_re.match(path.to_s)
              when 'cpp_bin'
                matched = $cpp_bin_re.match(path.to_s)
              when 'build'
                res = $build_re.match(path.to_s)
                #puts "Checking #{path} on #{$build_re} res #{res}" if res
                matched = res
              when 'project'
                matched = $project_re.match(path.to_s)
              when 'org'
                matched = $org_re.match(path.to_s)
              when 'el'
                matched = $el_re.match(path.to_s)
              when 'docs'
                matched = $docs_re.match(path.to_s)
              when 'ruby'
                matched = $ruby_re.match(path.to_s)
              when 'python'
                matched = $python_re.match(path.to_s)
              when 'go'
                matched = $go_re.match(path.to_s)
              when 'dlang'
                matched = $dlang_re.match(path.to_s)
              when 'proto'
                matched = $proto_re.match(path.to_s)
              when 'config'
                matched = $config_re.match(path.to_s)
              when 'xml'
                matched = $xml_re.match(path.to_s)
              when 'html'
                matched = $html_re.match(path.to_s)
              when 'hdf5'
                matched = $hdf5_re.match(path.to_s)
              when 'tmpl'
                matched = $tmpl_re.match(path.to_s)
              when 'unwanted'
                matched = $unwanted_re.match(path.to_s)
                #puts "Checking unwanted #{path} and #{matched}"
              else
                raise "Unknown type #{type}"
              end

              break if matched
            end
            puts "Pruning point #{path} => #{matched}" if !matched and log_evaluation
            Find.prune if !matched
          end
          puts "Adding #{path}" if log_evaluation
          @files << Pathname.new(path) if !File.directory? path
        end
#      rescue Exception => e
#        warn "Caught exception #{e}"
      end
    end
    puts @files.join(' ') if log_evaluation
  end

  # 
  def grep(desideratum = nil)
    desideratum = @match_regex if !desideratum
    desideratum = [ desideratum ] if desideratum.class != Array
    puts "desideratum #{desideratum}" if log_evaluation
    while @files.length>0
      more_files = @files.slice!(0..100)
      if @match_regex.length>0
        desideratum.each do | expression |
          grep_case = ' -i' if ignore_case
          cmd = "grep -Hn #{grep_case} '#{expression}' #{more_files.map { |f| "'#{f}'" }.join(' ')}"
          puts "Running #{cmd}" if log_evaluation
          print `#{cmd}`
        end
      else
        puts more_files.join(join_delimiter)
      end
    end
  end

end

# In specified file, *file_name*, replace *regex* with *to*
def replace_in_file(file_name, regex, to)
  reader = File.new(file_name, 'rb')
  txt = reader.read
  reader.close
  update = txt.gsub(regex, to)
  if update != txt
    backup_file = file_name.parent + (file_name.basename.to_s + '~')
    FileUtils::cp(file_name, backup_file)
    writer = File.new(file_name, 'w')
    writer.write(update)
    writer.close
    #puts file_name
  end
rescue Exception, e
  puts "Could not replace in file: #{file_name}"
  raise e
end

xgrep = XGrep.new(options)
if options.replace_regex
  if options.replace_to
    puts "Replacing #{options.replace_regex} to #{options.replace_to}"
    xgrep.files.each do |file_name|
      replace_in_file(file_name, options.replace_regex, options.replace_to)
    end
  else
    puts "Replacing --replace_to must be used with --replace_regex => #{options.replace_regex}"
  end
end
xgrep.grep
