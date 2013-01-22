################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'singleton'
require 'rubygems'
require 'parseconfig'
require 'sequel'
require 'yaml'

module OdbcIni

  class ParsedEntries
    attr_reader :odbc_ini_config
    include Singleton
    def initialize
      @odbc_ini_config = ParseConfig.new "#{ENV['HOME']}/.odbc.ini"
    end

    def connection_parms(dsn_name)
      Hash[*odbc_ini_config.params[dsn_name].map{|k,v| [k.downcase, v]}.flatten ]
    end

    def get_dsn_connection(dsn_name)
      dsn_config = connection_parms(dsn_name)
      result = Sequel.mysql(dsn_name, 
                            :user => dsn_config['user'], 
                            :password => dsn_config['pwd'], 
                            :host => (dsn_config['server'] or 'localhost'))
      return result
    end
  end
  

end

if $0 == __FILE__
  require 'pp'
  require 'yaml'
  p = OdbcIni::ParsedEntries.instance
  p.get_dsn_connection('system')["show tables"].each do |rec|
    puts rec
  end
  puts "Done"
end
