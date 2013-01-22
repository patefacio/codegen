/******************************************************************************
 * mongoid_ini_parser.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file mongoid_ini_parser.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_MONGOID_MONGOID_INI_PARSER_H_
#define _FCS_MONGOID_MONGOID_INI_PARSER_H_

#include <pantheios/pantheios.hpp>
#include "fcs/mongoid/mongoid.hpp"
#include "fcs/utils/streamers/vector.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/foreach.hpp>
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275 4251)
#endif
#include <boost/program_options.hpp>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <string>

namespace fcs {
namespace mongoid {


  class Mongoid_database_config 
  {
  public:

    Mongoid_database_config(
      std::string const& server,
      std::string const& user,
      std::string const& password
    ) :
      server_(server),
      user_(user),
      password_(password)
    {
    }

    Mongoid_database_config() :
      server_(),
      user_(),
      password_() 
    {
    }

    friend std::ostream& operator<<(std::ostream& out, Mongoid_database_config const& item);

    //! Name of server followed by colon followed by port <I>open</I>
    std::string server_;
    std::string user_;
    std::string password_;
  };

  // Support for streaming non-static streamable members of Mongoid_database_config
  inline
  std::ostream& operator<<(std::ostream& out, Mongoid_database_config const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Mongoid_database_config:(" << &item << "):{";
    out << '\n' << indent << "  server:" << item.server_;
    out << '\n' << indent << "  user:" << item.user_;
    out << '\n' << indent << "  password:" << item.password_;
    out << indent << "}\n";
    return out;
  } 
  typedef std::map< std::string, Mongoid_database_config > Database_configuration_map_t;


  class Mongoid_ini_parser 
  {
  public:

    Mongoid_ini_parser() :
      mongoid_options_description_("Parses mongoid ini file"),
      database_configuration_map_() 
    {
      ctor_default_init();
    }

    friend std::ostream& operator<<(std::ostream& out, Mongoid_ini_parser const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Database_configuration_map_t const& database_configuration_map() const {
      return database_configuration_map_;
    }

  private:

    //! Initialize the instance
    inline void ctor_default_init() {
      
// custom <Mongoid_ini_parser::ctor_default_init>

      using namespace boost;
      using namespace boost::program_options;

      filesystem::path mongoid_ini_path(getenv("HOME"));
      mongoid_ini_path /= ".mongoid.ini";
      char const* override(getenv("MONGOID_INI"));
      if(override) {
        mongoid_ini_path = override;
      }

      std::vector< option > config = 
        parse_config_file<char>(mongoid_ini_path.string().c_str(), 
                                mongoid_options_description_, true).options;

      BOOST_FOREACH(option const& config_option, config) {
        if(config_option.value.empty()) {
          continue;
        }
        std::string key(config_option.string_key);
        boost::to_lower(key);
        size_t dot_position(key.find_first_of('.'));
        if(dot_position >= 0) {
          std::string database(key.substr(0, dot_position));
          key = key.substr(dot_position+1);
          if(key == "user") {
            database_configuration_map_[database].user_ = config_option.value[0];
          } else if(key == "password" or key == "pwd") {
            database_configuration_map_[database].password_ = config_option.value[0];
          } else if(key == "serverstring") {
            database_configuration_map_[database].server_ = config_option.value[0];
          }
        } else {
          pantheios::log(PANTHEIOS_SEV_NOTICE, 
                         "Have no interest in mongoid config key:", 
                         config_option.string_key.c_str());
        }
      }

// end <Mongoid_ini_parser::ctor_default_init>
    }
    boost::program_options::options_description mongoid_options_description_;
    Database_configuration_map_t database_configuration_map_;
  };

  // Support for streaming non-static streamable members of Mongoid_ini_parser
  inline
  std::ostream& operator<<(std::ostream& out, Mongoid_ini_parser const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Mongoid_ini_parser:(" << &item << "):{";
    out << '\n' << indent << "  mongoid_options_description:" << item.mongoid_options_description_;
    out << '\n' << indent << "  database_configuration_map:" << item.database_configuration_map_;
    out << indent << "}\n";
    return out;
  } 

} // namespace mongoid
} // namespace fcs
#endif // _FCS_MONGOID_MONGOID_INI_PARSER_H_
