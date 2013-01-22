require 'flare/flate_types'
require 'tempfile'
require 'tmpdir'
require 'fileutils'
require 'commands'
include Commands

module Flare
  class Deflater
    attr_reader :source_path, :flate_type, :target_path, :verbose, :output
    def initialize(*args)
      args = args[0]
      @source_path = Pathname.new args[:source_path]
      @flate_type = args[:flate_type]
      @target_path = (args[:target_path] and Pathname.new(args[:target_path]) or nil)
      @verbose = args[:verbose]
      if target_path
        puts "Checking target #{@target_path}"
        gleaned_type = determine_flate_type(@target_path)[1]
        warn "Mismatch on flate_types - requested #{flate_type} should be #{gleaned_type}" if gleaned_type != flate_type
      else
      end
    end

    def deflate
      if target_path.nil?
        @temp_file = Tempfile.new([source_path.basename.to_s, FlateExtensions[flate_type]])
        @target_path = Pathname.new temp_file.path
      end

      case flate_type
      when FlateTypes::TAR
        @output = Commands.run_commands(["cd #{source_path.parent}; tar cvf #{target_path} #{source_path.basename}"], 
                                        true, false, verbose)
      when FlateTypes::TAR_GZ
        @output = Commands.run_commands(["cd #{source_path.parent}; tar cvzf #{target_path} #{source_path.basename}"], 
                                        true, false, verbose)
      when FlateTypes::TAR_LZMA
        @output = Commands.run_commands(["cd #{source_path.parent}; tar --lzma -cvf #{target_path} #{source_path.basename}"], 
                                        true, false, verbose)
      when FlateTypes::SEVEN_ZIP
        FileUtils.rm(target_path) if target_path.exist?
        @output = Commands.run_commands(["cd #{source_path.parent}; 7z a #{target_path} #{source_path.basename}"], 
                                        true, false, verbose)
      when FlateTypes::TAR_SEVEN_ZIP
        FileUtils.rm(target_path) if target_path.exist?
        intermediate_tar = source_path.basename
        @output = Commands.run_commands(["cd #{source_path.parent}; tar cf - #{intermediate_tar} | 7z a -si #{target_path}"], 
                                        true, false, verbose)
      when FlateTypes::TAR_BZ2
        @output = Commands.run_commands(["cd #{source_path.parent}; tar cvjf #{target_path} #{source_path.basename}"], 
                                        true, false, verbose)
      else
      end
      @temp_file.close if @temp_file
    end
  end
end
