/******************************************************************************
 * environment.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file environment.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_ENVIRONMENT_ENVIRONMENT_H_
#define _FCS_ENVIRONMENT_ENVIRONMENT_H_

#include <pantheios/pantheios.hpp>
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/patterns/singleton.hpp"
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <unistd.h>
#include <sstream>
#include <exception>
#include <list>
#include <map>
#include <string>
#include <set>
#include <iostream>

namespace fcs {
namespace environment {

  // Library typedefs
  typedef std::map< std::string, std::string > Environment_map_t;
  typedef std::set< std::string > Path_variable_set_t;
  typedef boost::filesystem::path Path_t;
  typedef std::list< Path_t > Path_list_t;
  typedef std::map< std::string, Path_list_t > Path_list_map_t;

  /**

  Singleton that when initialized churns through various environment variables
  like LD_LIBRARY_PATH, MANPATH, PATH, etc...
  The purpose is to make the paths those variables refer to available to code.

  */
  class Environment :
    public fcs::patterns::Singleton< Environment > 
  {
  protected:

    Environment() :
      environment_(),
      path_variable_map_() 
    {
      ctor_default_init();
    }

  public:

    friend std::ostream& operator<<(std::ostream& out, Environment const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    Environment_map_t const& environment() const {
      return environment_;
    }

    Path_list_map_t const& path_variable_map() const {
      return path_variable_map_;
    }

  private:

    //! Initialize the instance
    inline void ctor_default_init() {
      
// custom <Environment::ctor_default_init>

      char **env(environ);
      if(env) {
        if(!environment_.empty()) {
          std::ostringstream msg;
          msg << "Environment::parse_from_envp can only be called once on singleton";
          throw std::runtime_error(msg.str());
        } else {
          for(; env && *env; ++env) {
            std::string key_value(*env);
            size_t equal_pos(key_value.find_first_of('='));
            if(equal_pos != std::string::npos) {
              environment_[key_value.substr(0, equal_pos)] = key_value.substr(equal_pos+1);
            }
          }
        }
      }

      char const* common_paths[] = {
        "LD_LIBRARY_PATH",
        "MANPATH",
        "PATH",
        "PERLPATH",
        "PYTHONPATH",
        "RUBYLIB"
      };

      size_t end(sizeof(common_paths)/sizeof(char const*));
      boost::regex const path_split_regex(":");
      for(size_t i(0); i < end; ++i) {
        Environment_map_t::const_iterator found(environment_.find(common_paths[i]));
        if(environment_.end() != found) {
          std::string const& path_variable(found->first);
          std::string path_list_text(found->second);
          pantheios::log(PANTHEIOS_SEV_DEBUG, "Processing path var: ", path_variable.c_str(),
                         " with path\n\t", path_list_text.c_str());
          typedef std::vector< std::string > Tokens_t;
          Tokens_t tokens;
          boost::regex_split(std::back_inserter(tokens), path_list_text, path_split_regex);
          Tokens_t::const_iterator path_end(tokens.end());
          Path_list_t &path_list(path_variable_map_[path_variable]);
          for(Tokens_t::const_iterator path_it(tokens.begin()); path_it != path_end; ++path_it) { 
            path_list.push_back(*path_it);
          }
        }
      }

// end <Environment::ctor_default_init>
    }
    Environment_map_t environment_;
    Path_list_map_t path_variable_map_;
    friend class fcs::patterns::Singleton_impl< Environment >;
  };

  // Support for streaming non-static streamable members of Environment
  inline
  std::ostream& operator<<(std::ostream& out, Environment const& item) {
    using fcs::utils::streamers::operator<<;
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Environment:(" << &item << "):{";
    out << '\n' << indent << "  environment:" << item.environment_;
    out << '\n' << indent << "  path_variable_map:" << item.path_variable_map_;
    out << indent << "}\n";
    return out;
  } 


// custom <environment namespace end section>
// end <environment namespace end section>
} // namespace environment
} // namespace fcs
#endif // _FCS_ENVIRONMENT_ENVIRONMENT_H_
