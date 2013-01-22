require 'place'
require 'uri'
require 'rubygems'
require 'facets'
require 'flare'
include Flare

module Package
  module Identifier

    class CppInstallation
      attr_reader :stage_path, :package_name, :include_path, :lib_path, :header_only
      def initialize(rest)
        @package_name = rest[:package_name]
        @stage_path = rest[:stage_path]
        @include_path = rest[:include_path]
        @lib_path = rest[:lib_path]
        @header_only = rest[:header_only]
      end
      def to_s
        if header_only
          "#{package_name}\n\tinclude:   #{include_path}"
        else
          "#{package_name}\n\tstage: #{stage_path}\n\tinclude:   #{include_path}\n\tlib:   #{lib_path}"
        end
      end
    end

    class SourceTypes
      INSTALLER                    = :installer
      WEB_GET                      = :web_get
      SVN                          = :svn
      GIT                          = :git
    end

    class InstallTypes
      CPP_INSTALL                  = :cpp_install
      VIM_SCRIPT                   = :vim_script
      GEM_INSTALL                  = :gem_install
      DEBIAN                       = :debian
      RPM                          = :rpm
    end
    
    class WadTypes
      WEB_GET                      = :webget
      VIM_SCRIPT                   = :vim_script
      RUBY_GEM                     = :ruby_gem
      DEBIAN                       = :debian
      RPM                          = :rpm
      CPP_HEADER_LIB               = :cpp_header_lib
      CPP_SOURCE_PACKAGE           = :cpp_source_package
    end

    def Identifier.guess_source_type(uri)
      case uri.to_s
      when /(?:\bgit\b?|\.git$)/
        SourceTypes::GIT
      when /(?:\bsvn\b?)/
        SourceTypes::SVN
      else
        SourceTypes::WEB_GET
      end
    end

    def Identifier.normalize_name(n)
      n.gsub(/\./, '_').gsub(/-/, '_')
    end

    class WadIdentity
      attr_reader :name
      attr_reader :wad_type
      attr_reader :install_type
      attr_reader :source_uri
      attr_reader :source_type
      attr_reader :version
      attr_reader :versioned_name
      attr_reader :install_path
      attr_reader :stage_path
      attr_reader :pull_path
      attr_reader :pulled_source
      attr_reader :flate_type
      attr_reader :cpp_installation
      attr_reader :lib_path_basename

      Attrs = 
        [
         :name, :wad_type, :install_type, :source_type,
         :version, :versioned_name, :install_path, :stage_path
         #:source_uri, :cpp_installation,:pulled_source,:flate_type,:lib_path_basename
        ]
      
      def header
        Attrs
      end

      def fields
        Attrs.map {|a| eval("@#{a}") }
      end

      def standard_install_path
        @install_path = Place['install'] + versioned_name if !install_path
      end

      def standard_include_path
        @include_path = install_path + 'include' if !include_path
      end

      def standard_lib_path
        @lib_path = install_path + lib_path_basename if !lib_path
      end

      def standard_stage_path
        @stage_path = Place['staged_source'] + versioned_name if !stage_path
      end

      def standard_pull_path
        if !pull_path and source_uri
          path = Pathname.new(source_uri.path)
          flate_type = determine_flate_type((path.basename.to_s == 'download') ? 
                                            path.parent.basename : 
                                            path.basename)
          puts "vn => #{versioned_name} ft => #{flate_type}"
          if flate_type
            pull_path = Place['pulled_source'] + (versioned_name + flate_type[1])
          end
        end
        pull_path
      end

      def initialize(args)
        @name = args[:name].to_s
        @version = args[:version]
        @lib_path_basename = (args[:lib_path_basename] or 'lib')
        if args[:source_uri]
          uri = String.interpolate{ args[:source_uri] }
          @source_uri = URI.parse(uri)
        end
        @source_type = Identifier.guess_source_type(source_uri) if !source_type
        @versioned_name = Identifier.normalize_name((args[:versioned_name] or (version ? "#{name}_#{version}" : name)))
        @cpp_installation = args[:cpp_installation]
        standard_pull_path if source_type == SourceTypes::WEB_GET
      end

      def pull_source(rest = { })
        already_exist_action = (rest[:already_exist_action] or AlreadyExistAction::SKIP)
        already_exist_action = AlreadyExistAction::OVERWRITE if rest[:force]
        if source_uri
          target_path = (rest[:target_path] or standard_pull_path)                         

          puller = UrlPuller.new(:source_uri => source_uri, 
                                 :target_path => target_path,
                                 :already_exist_action => already_exist_action)
          @pulled_source = puller.pull
          @flate_type = determine_flate_type(@pulled_source)
        else
          puts "Pull unnnecessary for #{versioned_name} - no source_uri"
        end
      end

      def install_pulled_source(rest)
        target_path = rest[:target_path]
        puts "The target path is #{target_path}"
        if flate_type
          inflater = Inflater.new(:source_path => @pulled_source, :target_path => target_path, :verbose => true)
          inflater.inflate
        else
          FileUtils.mv(@pulled_source, target_path, :verbose => true, :force => true)
        end
      end
    end

    class CppHeaderLib < WadIdentity
      attr_reader :include_path
      def initialize(args)
        @wad_type = WadTypes::CPP_HEADER_LIB
        @install_type = InstallTypes::CPP_INSTALL
        super(args)
        standard_install_path
        standard_include_path
        @cpp_installation = CppInstallation.new(:include_path => include_path,
                                                :package_name => versioned_name,
                                                :header_only => true)
      end

      def to_s
        return "Header Lib #{versioned_name} - INCLUDE => #{include_path}"
      end
    end

    class CppSourcePackage < WadIdentity
      attr_reader :stage_path, :include_path, :lib_path
      def initialize(args)
        @wad_type = WadTypes::CPP_SOURCE_PACKAGE
        @install_type = InstallTypes::CPP_INSTALL
        super(args)
        standard_install_path
        standard_include_path
        standard_lib_path
        standard_stage_path
        @cpp_installation = CppInstallation.new(:stage_path => stage_path,
                                                :include_path => include_path,
                                                :lib_path => lib_path,
                                                :package_name => versioned_name)
      end

      def to_s
        return "CppSourcePackage #{name} => #{source_uri}"
      end
    end

    class VimScriptIdentity < WadIdentity

      @@install_path = Pathname.new "#{ENV['HOME']}/.vim"
      @@plugin_path = @@install_path + 'plugin'
      @@doc_path = @@install_path + 'doc'

      def initialize(args)
        raise "VimScriptIdentity requires name of download file" if !args[:name]
        @wad_type = WadTypes::VIM_SCRIPT
        @install_type = InstallTypes::VIM_SCRIPT
        @source_type = SourceTypes::INSTALLER
        super(args)
        raise "VimScriptIdentity requires a source uri" if !source_uri
      end

      def to_s
        return "Vim Script #{name} => #{source_uri}"
      end

      def pull_source(rest)
        rest[:target_path] = (Place['pulled_source'] + name)
        super( rest )
      end

      def install(rest)
        pull_source if pulled_source.nil? or !pulled_source.exist?
        FileUtils.makedirs(@@plugin_path, :verbose => true) if !@@plugin_path.exist?
        install_pulled_source(:target_path => @@plugin_path.parent)
        puts "Installing plugin to #{@@plugin_path}"
      end

    end

    class RubyGemIdentity < WadIdentity
      def initialize(args)
        raise "RubyGemIdentity requires name of gem" if !args[:name]
        @wad_type = WadTypes::RUBY_GEM
        @install_type = InstallTypes::GEM_INSTALL
        @source_type = SourceTypes::INSTALLER
        super(args)
      end
    end

    class WebGetIdentity < WadIdentity
      def initialize(*args)
        args = args[0]
        @wad_type = WadTypes::WEB_GET
        super(args)
      end
    end

    class DebianIdentity < WadIdentity
      def initialize(args)
        @wad_type = WadTypes::DEBIAN
        @install_type = InstallTypes::DEBIAN
        @source_type = SourceTypes::INSTALLER
        super(args)
      end
      def to_s
        return "Deb Pkg => #{name}"
      end
    end

  end
end
