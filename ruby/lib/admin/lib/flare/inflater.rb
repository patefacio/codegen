require 'flare/flate_types'
require 'fileutils'


module Flare
  class Inflater

    attr_reader :source_path, :target_path, :basename
    attr_reader :flate_type, :cleanup_source, :clean_target_first, :verbose, :output
    attr_reader :russian_doll

    def initialize(*args)
      args = args[0]
      @source_path = Pathname.new args[:source_path]
      @target_path = args[:target_path]
      @basename, @flate_type = determine_flate_type(source_path)
      @cleanup_source = args[:cleanup_source]
      @clean_target_first = args[:clean_target_first]
      @verbose = args[:verbose]
      # If russian doll - take the folder wrapped in the target and mv to the target
      @russian_doll = args[:russian_doll]
    end

    def inflate
      if @target_path.nil?
        @target_path = Pathname.new(Dir.mktmpdir(source_path.basename.to_s))
      else
        @target_path = Pathname.new(target_path)
        if target_path.exist? and clean_target_first
          puts "Removing target first #{target_path}"
          FileUtils.rm_r target_path.to_s, :verbose => true
        end
        if !target_path.exist?
          FileUtils.makedirs target_path.to_s
        end
      end

      # do the work

      current_dir = FileUtils.pwd
      FileUtils.cd target_path
      case flate_type
      when FlateTypes::BZ2
        output = Commands.run_commands(["bunzip2 #{source_path}"], true, false, verbose)
      when FlateTypes::TAR
        output = Commands.run_commands(["tar -xvf #{source_path}"], true, false, verbose)
      when FlateTypes::ZIP
        output = Commands.run_commands(["unzip -o #{source_path}"], true, false, verbose)
      when FlateTypes::SEVEN_ZIP
        output = Commands.run_commands(["7z x #{source_path}"], true, false, verbose)
      when FlateTypes::TAR_GZ
        output = Commands.run_commands(["tar -xvzf #{source_path}"], true, false, verbose)
      when FlateTypes::SEVEN_ZIP
        output = Commands.run_commands(["7z x #{source_path}"], true, false, verbose)
      when FlateTypes::TAR_SEVEN_ZIP
        tar_file = source_path.basename.to_s.gsub(/\.7z$/, '')
        output = Commands.run_commands(["7z x #{source_path}", "tar -xvf #{tar_file}"],
                                       true, false, verbose)
      when FlateTypes::TAR_BZ2
        output = Commands.run_commands(["tar -xvjf #{source_path}"], true, false, verbose)
      when FlateTypes::TAR_LZMA
        output = Commands.run_commands(["tar --lzma -xvf #{source_path}"], true, false, verbose)
      else
        raise "Unable to inflate #{target_path}"
      end

      FileUtils.cd current_dir

      if russian_doll
        contents = Dir["#{target_path}/*"]
        if contents.length == 1
          single_path = contents[0]
          temp_target = target_path.to_s + '.temp'
          if File.directory? single_path
            FileUtils.mv single_path, temp_target, :verbose => true
            FileUtils.rmdir target_path, :verbose => true
            FileUtils.mv temp_target, target_path, :verbose => true
          end
        end
      end

#      FileUtils.rmdir(target_path, :verbose => true)

    end
  end
end
