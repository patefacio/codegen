################################################################################
# To avoid hard-coding of paths, this file is a repository of places on the 
# disk that are important to the code
################################################################################
require 'pathname'
require 'pp'
require 'ostruct'
require 'rubygems'

class Place

  @@is_linux = RUBY_PLATFORM.downcase.include?("linux")
  @@place = { }

  def Place.is_linux?
    return @@is_linux
  end

  def Place.place
    return @@place
  end

  def Place.[] (index)
    return @@place[index]
  end

  @@place['ruby_lib'] = Pathname.new(File.expand_path(__FILE__)).parent

  # Find ruby gems
  @@place['ruby_gems'] = Pathname.new(ENV['GEM_PATH'].split(/:/).grep(/\/(?:ruby|\.rvm)\/gems/)[0].clone.gsub(/(.*gems\/).*/) { $1 })

  root_path = Place['ruby_lib'].parent.parent
  TOP = root_path.basename.to_s

  def Place.top
    return TOP
  end

  @@place[TOP] = root_path
  top = @@place[TOP].parent
  @@place['usr_lib'] = Pathname.new('/usr/lib')
  @@place['usr_include'] = Pathname.new('/usr/include')
  @@place['cpp_standard_lib'] = Pathname.new('/usr/include/c++/4.4')
  @@place['ruby_scripts'] = Place['ruby_lib'] + 'scripts'
  @@place['elisp'] = Place[TOP] + 'myemacs' + 'elisp'
  @@place['doxygen'] = top + 'doxygen'
  @@place['websites'] =  Pathname.new(ENV['HOME']) + 'websites'
  @@place["#{TOP}_install"] =  top + "#{TOP}_install"
  @@place['saved_out'] = top + 'admin' + 'saved_out'
  @@place['pulled_source'] = top + 'admin' + 'pulled_source'
  @@place['staged_source'] = top + 'admin' + 'staged_source'
  @@place['stage'] = top + 'staged'
  @@place['install'] =  top + 'admin' + 'install'
  @@place['bin'] = top + 'bin'
  @@place['rb_codegen'] = Place['ruby_lib'] + 'codegen'
  @@place['rb_codegen_tmpl'] = Place['rb_codegen'] + 'cpp' + 'tmpl'
  @@place['db_tmpl'] = Place['rb_codegen'] + 'database' + 'tmpl'
  @@place['database_tmpl'] = Place['rb_codegen'] + 'database' + 'tmpl'
  @@place['mongoid_tmpl'] = Place['rb_codegen'] + 'mongoid' + 'tmpl'
  @@place['extjs_tmpl'] = Place['rb_codegen'] + 'extjs' + 'tmpl'
  @@place['data_model_tmpl'] = Place['rb_codegen'] + 'data_model' + 'tmpl'
  @@place['lookup_tmpl'] = Place['rb_codegen'] + 'lookup' + 'tmpl'
  @@place['cpp'] = Place[TOP] + 'cpp'
  @@place['headers'] = @@place['cpp'] + TOP
  @@place['data'] = Place[TOP] + 'data'
  @@place['boost_build'] = Place[TOP].parent + 'install' + 'boost-build'
  @@place['libs'] = Place['cpp'] + 'libs'
  @@place['apps'] = Place['cpp'] + 'apps'
  @@place['python'] = root_path + 'py'
  @@place['dlang'] = Place[TOP] + 'dlang' 
  @@place['dlang_tmpl'] = @@place['rb_codegen'] + 'dlang' + 'tmpl'

  @@jam_place = { }
  def Place.jam_place
    @@jam_place
  end

end

if $0 == __FILE__
  require 'optparse'
  require 'yaml'
  options = {:path => [] }
  optparse = OptionParser.new do |opts|
    opts.banner = %Q{Usage: #{Pathname.new(__FILE__).basename}
    }
    opts.separator ""
    opts.separator "Specific options:"
    opts.on('-h', '--help', 'Display this screen' ) do
      raise "Help Follows"
    end
    opts.on('-p', '--path PATH_NAME', "Name of path to show fully qualified path of") do |path|
      options[:path] <<  path
    end
    opts.on('-a', '--all', "Shows all paths") do |all|
      options[:all] = all
    end
  end

  begin 
    optparse.parse!
    options[:path].each do |p|
      puts Place[p.to_sym]
    end
    if options[:all]
      Place.place.each do |k,v|
        if v.nil?
          warn "Found nil place #{k} => #{v}" 
        else
          puts "#{Pathname.new(v).exist? ? 'EXIST  :' : '!EXIST :'}#{k} => #{v}"
        end
      end
    end
  rescue RuntimeError => msg
    puts msg
    puts optparse
  end
end

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
