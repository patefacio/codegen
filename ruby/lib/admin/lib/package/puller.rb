require 'pathname'
require 'tempfile'
require 'uri'

module Package

  class AlreadyExistAction
    # If target has been pulled already - skip
    SKIP                          = :skip
    CLEAN_FIRST                   = :clean_first
    OVERWRITE                     = :overwrite
    COMPARE_AND_REPLACE           = :compare_and_replace
    COMPARE_AND_KEEP              = :compare_and_keep
  end

  class UrlPuller
    attr_reader :source_uri, :already_exist, :already_exist_action, :target_path
    attr_reader :target_cleaned_first
    
    def initialize(*args)
      args = args[0]
      @source_uri = URI.parse(args[:source_uri].to_s) if args[:source_uri]
      @already_exist_action = (args[:already_exist_action] or AlreadyExistAction::OVERWRITE)
      @target_path = Pathname.new(args[:target_path]) if args[:target_path]
    end

    def pulled_file
      return @temp_file.nil? ? target_path : Pathname.new(@temp_file.path)
    end

    def pull
      puts "Pulling #{target_path.to_s} with action #{already_exist_action}"

      if target_path and target_path.exist?
        @already_exist = true
        if already_exist_action == AlreadyExistAction::CLEAN_FIRST
          FileUtils.rm(target_path)
          @target_cleaned_first = true
          puts "Cleaned up pre-existing target #{target_path}"
        end
      end

      if target_path.exist? and 
          target_path.size > 0 and
          (already_exist_action == AlreadyExistAction::SKIP)
        puts "Puller returning existing target path #{target_path}"
        return target_path
      end

      pull_to_temp = (target_path.nil? or 
                      (target_path.exist? and 
                       [
                        AlreadyExistAction::COMPARE_AND_KEEP,
                        AlreadyExistAction::COMPARE_AND_REPLACE
                       ].include?(already_exist_action)))

      pull_to_path = 
        pull_to_temp ? (@temp_file = Tempfile.new("pull_wad")).path : @target_path

      command = "wget '#{source_uri.to_s}' -O #{pull_to_path}"
      puts "Running #{command}"
      output = `#{command}`
      if 0 == $?
        return pulled_file
      else
        raise "Unable to pull file #{source_uri}: web_get rc #{$?}"
      end
    end
  end

end
