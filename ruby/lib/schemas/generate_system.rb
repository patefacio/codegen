require "rubygems"
require "sequel"
require "logger"
require 'yaml'
require 'odbc_ini'
require 'pathname'

# connect to an in-memory database
DB = OdbcIni::ParsedEntries.instance.get_dsn_connection('test')
dest_database = 'system'
DB.loggers << Logger.new(STDOUT)
databases = DB["show databases"].collect { |db| db[:Database] }
DB.execute("drop database #{dest_database}") if databases.include? dest_database
DB.execute("create database #{dest_database}")
DB.execute("use #{dest_database}")

def generate_db()
  DB.create_table! :vendors do
    primary_key :id
    String :name, :null => false, :size => 32
  end

  DB.create_table! :foo do
    int :id
    String :doo, :size => 8
    int :foo
    String :goo, :size => 16
    String :moo, :size => 8
    String :name, :null => false, :size => 32
    DATE :date
    DATETIME :datetime
    TIME :time
    Text :text
  end
  DB.alter_table :foo do
    add_primary_key [:id, :doo, :foo]
  end

  DB.create_table! :network_cards do
    primary_key :id
    double :speed_mbps
    int :vendor_id
  end
  DB.alter_table :network_cards do
    add_foreign_key [:vendor_id], :vendors, :null => false, :key => [:id]
  end
  DB.create_table! :cache_configurations do
    primary_key :id
    int :size_kilobytes, :null => false
    double :speed
  end
  DB.create_table! :processors do
    primary_key :id
    String :name, :size => 64
    int :vendor_id
    int :cache_configuration_id
    int :num_cores, :null => false
    String :cpu_family, :size => 16
    double :bus_speed
  end
  DB.alter_table :processors do
    add_foreign_key [:vendor_id], :vendors, :null => false, :key => [:id]
    add_foreign_key [:cache_configuration_id], :cache_configurations, :null => false, :key => [:id]
  end
end

def seed_data()
  vendors = DB[:vendors]
  v = vendors.insert(:name => 'GenuineIntel')
  v = vendors.insert(:name => 'Cisco')
  cache_configurations = DB[:cache_configurations]
  c = cache_configurations.insert(:size_kilobytes => 2048, :speed => 200)
  processors = DB[:processors]
  (1..5).each do |i|
    processors.insert(:name => "Intel(R) Core(TM)2 Duo CPU     T7250 #{i}  @ 2.00GHz",
                      :vendor_id => v, :cache_configuration_id => c, 
                      :num_cores => 2, :cpu_family => '6', :bus_speed => 500*i)
  end

#  text = File.new(Pathname.new(File.expand_path(__FILE__)), 'r').read
  text = "this
is 
a test of the ebs"
  (1..100).each do |i|
    DB[:foo].insert(:id => i, :doo => "Foo"+i.to_s, :foo => -i, 
                    :goo => "Goo_"+i.to_s,
                    :moo => "Moo_"+i.to_s,
                    :text => text,
                    :date => Date.today,
                    :datetime => DateTime.civil(2010, 12, 16, 8, 33, 22),
                    :time => DateTime.civil(2010, 12, 16, 8, 33, 22),
                    :name => "nm-"+i.to_s)
  end

  #DB.execute('SELECT * from processors')
  #x = DB[:cache_configurations].filter('speed > ?').select(:size_kilobytes, :speed)
  #puts "#{x.class} => #{x.methods.sort.join(' ')}\n\n#{x.sql}"
  #print x.to_yaml
end

def dump_schema()
  DB.tables.each do |tbl|
    schema = DB.schema(tbl)
    puts schema
  end
end

generate_db()
seed_data()
#dump_schema()
