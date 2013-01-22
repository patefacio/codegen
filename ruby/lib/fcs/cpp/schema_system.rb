################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/database/database'
require 'odbc_ini'

DB = OdbcIni::ParsedEntries.instance.get_dsn_connection('system')
#DB.loggers << Logger.new(STDOUT)

database = 
  Codegen::Database.new(
                        :database_connection => DB,
                        :support_options => { 
                          :supports_delete_all => true, 
                        },
                        :tables => [
                                    :vendors, 
                                    :processors, 
                                    :cache_configurations,
                                    :network_cards, 
                                    :foo,
                                   ]
                        )

