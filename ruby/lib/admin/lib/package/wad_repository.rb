#!/usr/bin/ruby
require 'package'
require 'yaml'
require 'tenjin'
require 'dump_trace'
require 'codegen'
require 'pp'

include Codegen

module Package
  include Package::Identifier

  SourceForge = 'http://sourceforge.net/projects'
  Repository = []

  require 'package/repository_vim.rb'
  VimPackages.each {|p| Repository << p }

  require 'package/repository_debian.rb'
  DebianPackages.each {|p| Repository << p }

  require 'package/repository_cpp_source.rb'
  CppSourcePackages.each {|p| Repository << p }

  require 'package/repository_cpp_header.rb'
  CppHeaderPackages.each {|p| Repository << p }

  def to_table
    require 'table_print'
    data = []
    Repository.each do |r|
      data << r.fields.map {|f| f.to_s.gsub(Place['install'].to_s, 'INST').gsub(Place['staged_source'].to_s, 'SRC') }
    end
    to_ascii_table(data, Repository[0].header.map {|f| f.to_s })
  end

end


if $0 == __FILE__
  require 'optparse'
  include Package
  options = OpenStruct.new()
  options.packages = []
  optparse = OptionParser.new do |opts|
    opts.banner = "Usage: wad_repository [options]"
    opts.separator ""
    opts.separator "Specific options:"
    opts.on('-h', '--help', 'Display this screen' ) do
      puts "Help Follows\n#{opts}"
      exit
    end
    opts.on('-p', '--package PACKAGE', "Package(s) to operate on" ) do |pkg|
      options.packages << pkg
    end
    opts.on('-P', '--pull_package', "" ) do |p|
      options.pull_package = true
    end
    opts.on('-i', '--install_package', "Install the c++ package(s)" ) do |i|
      options.install_package = true
    end
    opts.on('-l', '--list', "List the repository" ) do |l|
      options.list = true
    end
    opts.on('-L', '--list_verbose', "List the repository in yaml" ) do |l|
      options.list_verbose = true
    end
    opts.on('-c', '--list_cpp', "List the cpp installations" ) do |l|
      options.list_cpp = true
    end
    opts.on('-C', '--list_cpp_yaml', "List the cpp installations yaml" ) do |l|
      options.list_cpp_verbose = true
    end
    opts.on('-m', '--makefiles', "Create makefiles for cpp" ) do |l|
      options.makefiles = true
    end
    opts.on('', '--cpp_paths', "Generate paths for cpp" ) do |c|
      options.cpp_paths = true
    end
  end

  begin 
    optparse.parse!

    if options.list
      Repository.each do |r|
        puts r.to_s
      end
      puts to_table
    elsif options.list_verbose
      Repository.each do |r|
        puts r.to_yaml
      end
    elsif options.list_cpp_verbose
      Repository.select{|p| p.cpp_installation }.each do |r|
        puts r.to_yaml
      end
    elsif options.list_cpp
      Repository.select{|p| p.cpp_installation }.each do |r|
        puts "#{r}\n#{r.cpp_installation}"
      end
    elsif options.makefiles
      installations = Repository.select{|p| p.cpp_installation }
      fqpath = '/home/dbdavidson/fcs/admin/generated.makefile'
      engine = Tenjin::Engine.new(:path => [ Place['rb_codegen_tmpl'].to_s])
      output = engine.render('wad_generated_make.tmpl', { :installations => installations })
      Codegen.merge(output, fqpath, :protected_pair => BUILD_PROTECT_BLOCK_DELIMITERS)
    elsif options.cpp_paths
      installations = Repository.select{|p| p.cpp_installation }
      fqpath = Place[Place.top] + 'ruby/lib/cpp_paths.rb'
      engine = Tenjin::Engine.new(:path => [ Place['rb_codegen_tmpl'].to_s])
      pp(installations)
      output = engine.render('cpp_paths.tmpl', { :installations => installations })
      Codegen.merge(output, fqpath, :protected_pair => BUILD_PROTECT_BLOCK_DELIMITERS)
    elsif options.packages.empty?
      raise "You must specify at least one package"
    end

    options.packages.each do |pkg_name| 
      Repository.select {|pkg| pkg.name =~ /#{pkg_name}/ }.each do |pkg|
        begin
          if options.pull_package and ((pkg.wad_type == WadTypes::CPP_HEADER_LIB) or (pkg.wad_type == WadTypes::CPP_SOURCE_PACKAGE))
            puts "Pulling #{pkg}"
            pkg.pull_source :force => options.force
          end
          if options.install_package
            puts "Installing #{pkg}"
            pkg.install :force => options.force
          end
        rescue Exception => e
          warn "Failed on some aspect of #{pkg} due to: #{e}"
          raise e
        end
      end
    end
    
  rescue OptionParser::InvalidOption => e
    puts e.message
    puts optparse
    dump_trace
    exit(0)
  rescue SystemExit => e
  end

end
