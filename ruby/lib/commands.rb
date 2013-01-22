################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'fileutils'

module Commands

  @@disable_commands = false
  
  def disable_commands
    @@disable_commands = true
  end

  def enable_commands
    @@disable_commands = false
  end

  @@dir_stack = []
  def pushd(d)
    @@dir_stack.unshift FileUtils.pwd
    FileUtils.cd d
  end

  def popd
    FileUtils.cd @@dir_stack.shift
  end

  def run(commands, rest)
    get_output = rest[:get_output].nil? ? false : rest[:get_output]
    put_output = rest[:put_output].nil? ? true : rest[:put_output]
    announce = rest[:announce].nil? ? true : rest[:announce]
    run_dir = rest[:run_dir]
    pushd(run_dir) if run_dir
    all_output = []
    commands.each do |cmd|
      if !@@disable_commands
        puts "Running => #{cmd}\n\trun from: #{FileUtils.pwd}" if announce
        if get_output
          output = `#{cmd}` 
        else
          puts `#{cmd}` if put_output
        end
        puts "Done running #{cmd} => #{$?}" if announce
      else
        puts "Skipping disabled command => #{cmd}\nfrom #{FileUtils.pwd}"
      end
      if get_output
        all_output << output
      end
    end
    popd if run_dir
    if get_output
      all_output
    end
  end

  def run_commands(commands, get_output = false, put_output = true, announce = true, run_dir = nil)
    run(commands, 
        :get_output => get_output,
        :put_output => put_output, 
        :announce => announce, 
        :run_dir => run_dir)
  end

end
