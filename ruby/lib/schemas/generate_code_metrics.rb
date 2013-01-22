require "rubygems"
require "sequel"
require "logger"
require 'yaml'
require 'odbc_ini'

# connect to an in-memory database

$connection = OdbcIni::ParsedEntries.instance.get_dsn_connection('test')
$connection.loggers << Logger.new(STDOUT)
dest_database = 'code_metrics'
databases = $connection["show databases"].collect { |db| db[:Database] }
$connection.execute("drop database #{dest_database}") if databases.include? dest_database
$connection.execute("create database #{dest_database}")
$connection.execute("use #{dest_database}")


def generate_db

  $connection.create_table! :code_packages do
    # Describes the library or app or general section for which timing will be
    # run
    primary_key :id
    String :name, :null => false, :size => 64, :unique => true
    String :descr, :null => false, :size => 256
  end

  $connection.create_table! :code_locations do
    # Location information on the timing
    primary_key :id
    int :code_packages_id, :null => false
    String :label, :null => false, :size => 256
    String :file_name, :null => false, :size => 256
    int :line_number, :null => false
    String :git_commit, :null => false, :size => 40
    unique [ :code_packages_id, :label, :file_name, :line_number ]
  end
  $connection.alter_table :code_locations do
    add_foreign_key [:code_packages_id], :code_packages, :null => false, :key => [:id]
  end

  $connection.create_table :rusage_delta do
    primary_key :id
    int :code_locations_id, :null => false
    DateTime :created, :null => false
    int :start_processor, :null => false
    int :end_processor, :null => false
    double :cpu_mhz, :null => false
    int :debug, :null => false
    BigInt :user_time_sec, :null => false
    BigInt :user_time_usec, :null => false
    BigInt :system_time_sec, :null => false
    BigInt :system_time_usec, :null => false
    BigInt :ru_maxrss, :null => false
    BigInt :ru_ixrss, :null => false
    BigInt :ru_idrss, :null => false
    BigInt :ru_isrss, :null => false
    BigInt :ru_minflt, :null => false
    BigInt :ru_majflt, :null => false
    BigInt :ru_nswap, :null => false
    BigInt :ru_inblock, :null => false
    BigInt :ru_oublock, :null => false
    BigInt :ru_msgsnd, :null => false
    BigInt :ru_msgrcv, :null => false
    BigInt :ru_nsignals, :null => false
    BigInt :ru_nvcsw, :null => false
    BigInt :ru_nivcsw, :null => false
  end
  $connection.alter_table :rusage_delta do
    add_foreign_key [:code_locations_id], :code_locations, :null => false, :key => [:id]
  end

  $connection.create_table! :code_tick_timings do
    primary_key :id
    int :code_locations_id, :null => false
    DateTime :created, :null => false
    int :start_processor, :null => false
    int :end_processor, :null => false
    double :cpu_mhz, :null => false
    int :debug, :null => false
    BigInt :ticks, :null => false
    BigInt :normalized_ns, :null => false
  end
  $connection.alter_table :code_tick_timings do
    add_foreign_key [:code_locations_id], :code_locations, :null => false, :key => [:id]
  end

  # (0..50).each do |i|
  #   $connection[:rusage_delta].insert(
  #                                     :ru_maxrss => rand,
  #                                     :ru_ixrss => rand,
  #                                     :ru_idrss => rand,
  #                                     :ru_isrss => rand,
  #                                     :ru_minflt => rand,
  #                                     :ru_majflt => rand,
  #                                     :ru_nswap => rand,
  #                                     :ru_inblock => rand,
  #                                     :ru_oublock => rand,
  #                                     :ru_msgsnd => rand,
  #                                     :ru_msgrcv => rand,
  #                                     :ru_nsignals => rand,
  #                                     :ru_nvcsw => rand,
  #                                     :ru_nivcsw => rand
  #                                     )
  # end
  
end

generate_db


# databases.each do |db|
#   connection.execute("use #{db[:Database]}")
#   puts "#{db[:Database]}"
#   connection["show tables;"].each do |tbl|
#      puts "\t#{tbl.keys} class => #{tbl.values}"
#   end
# end
