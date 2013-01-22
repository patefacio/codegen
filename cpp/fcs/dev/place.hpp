/******************************************************************************
 * place.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file place.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_DEV_PLACE_H_
#define _FCS_DEV_PLACE_H_

#include "fcs/patterns/singleton.hpp"
#include "fcs/utils/block_indenter.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

namespace fcs {
namespace dev {

  class Place :
    public fcs::patterns::Singleton< Place > 
  {
  protected:

    Place() :
      top_("/home/dbdavidson/open_source/codegen"),
      ruby_lib_(top_ / "ruby/lib"),
      ruby_gems_(top_ / "../../../../usr/lib/ruby/gems/1.9.1/gems"),
      codegen_(top_ / "."),
      usr_lib_(top_ / "../../../../usr/lib"),
      usr_include_(top_ / "../../../../usr/include"),
      cpp_standard_lib_(top_ / "../../../../usr/include/c++/4.4"),
      ruby_scripts_(top_ / "ruby/lib/scripts"),
      elisp_(top_ / "myemacs/elisp"),
      doxygen_(top_ / "../doxygen"),
      websites_(top_ / "../../websites"),
      codegen_install_(top_ / "../codegen_install"),
      saved_out_(top_ / "../admin/saved_out"),
      pulled_source_(top_ / "../admin/pulled_source"),
      staged_source_(top_ / "../admin/staged_source"),
      stage_(top_ / "../staged"),
      install_(top_ / "../admin/install"),
      bin_(top_ / "../bin"),
      rb_codegen_(top_ / "ruby/lib/codegen"),
      rb_codegen_tmpl_(top_ / "ruby/lib/codegen/cpp/tmpl"),
      db_tmpl_(top_ / "ruby/lib/codegen/database/tmpl"),
      database_tmpl_(top_ / "ruby/lib/codegen/database/tmpl"),
      mongoid_tmpl_(top_ / "ruby/lib/codegen/mongoid/tmpl"),
      extjs_tmpl_(top_ / "ruby/lib/codegen/extjs/tmpl"),
      data_model_tmpl_(top_ / "ruby/lib/codegen/data_model/tmpl"),
      lookup_tmpl_(top_ / "ruby/lib/codegen/lookup/tmpl"),
      cpp_(top_ / "cpp"),
      headers_(top_ / "cpp/codegen"),
      data_(top_ / "data"),
      boost_build_(top_ / "../install/boost-build"),
      libs_(top_ / "cpp/libs"),
      apps_(top_ / "cpp/apps"),
      python_(top_ / "py"),
      dlang_(top_ / "dlang"),
      dlang_tmpl_(top_ / "ruby/lib/codegen/dlang/tmpl") 
    {
    }

  public:

    friend std::ostream& operator<<(std::ostream& out, Place const& item);

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    boost::filesystem::path top() const {
      return top_;
    }

    boost::filesystem::path const& ruby_lib() const {
      return ruby_lib_;
    }

    boost::filesystem::path const& ruby_gems() const {
      return ruby_gems_;
    }

    boost::filesystem::path const& codegen() const {
      return codegen_;
    }

    boost::filesystem::path const& usr_lib() const {
      return usr_lib_;
    }

    boost::filesystem::path const& usr_include() const {
      return usr_include_;
    }

    boost::filesystem::path const& cpp_standard_lib() const {
      return cpp_standard_lib_;
    }

    boost::filesystem::path const& ruby_scripts() const {
      return ruby_scripts_;
    }

    boost::filesystem::path const& elisp() const {
      return elisp_;
    }

    boost::filesystem::path const& doxygen() const {
      return doxygen_;
    }

    boost::filesystem::path const& websites() const {
      return websites_;
    }

    boost::filesystem::path const& codegen_install() const {
      return codegen_install_;
    }

    boost::filesystem::path const& saved_out() const {
      return saved_out_;
    }

    boost::filesystem::path const& pulled_source() const {
      return pulled_source_;
    }

    boost::filesystem::path const& staged_source() const {
      return staged_source_;
    }

    boost::filesystem::path const& stage() const {
      return stage_;
    }

    boost::filesystem::path const& install() const {
      return install_;
    }

    boost::filesystem::path const& bin() const {
      return bin_;
    }

    boost::filesystem::path const& rb_codegen() const {
      return rb_codegen_;
    }

    boost::filesystem::path const& rb_codegen_tmpl() const {
      return rb_codegen_tmpl_;
    }

    boost::filesystem::path const& db_tmpl() const {
      return db_tmpl_;
    }

    boost::filesystem::path const& database_tmpl() const {
      return database_tmpl_;
    }

    boost::filesystem::path const& mongoid_tmpl() const {
      return mongoid_tmpl_;
    }

    boost::filesystem::path const& extjs_tmpl() const {
      return extjs_tmpl_;
    }

    boost::filesystem::path const& data_model_tmpl() const {
      return data_model_tmpl_;
    }

    boost::filesystem::path const& lookup_tmpl() const {
      return lookup_tmpl_;
    }

    boost::filesystem::path const& cpp() const {
      return cpp_;
    }

    boost::filesystem::path const& headers() const {
      return headers_;
    }

    boost::filesystem::path const& data() const {
      return data_;
    }

    boost::filesystem::path const& boost_build() const {
      return boost_build_;
    }

    boost::filesystem::path const& libs() const {
      return libs_;
    }

    boost::filesystem::path const& apps() const {
      return apps_;
    }

    boost::filesystem::path const& python() const {
      return python_;
    }

    boost::filesystem::path const& dlang() const {
      return dlang_;
    }

    boost::filesystem::path const& dlang_tmpl() const {
      return dlang_tmpl_;
    }

  
// custom <Place public header section>
// end <Place public header section>

  private:
    boost::filesystem::path top_;
    boost::filesystem::path ruby_lib_;
    boost::filesystem::path ruby_gems_;
    boost::filesystem::path codegen_;
    boost::filesystem::path usr_lib_;
    boost::filesystem::path usr_include_;
    boost::filesystem::path cpp_standard_lib_;
    boost::filesystem::path ruby_scripts_;
    boost::filesystem::path elisp_;
    boost::filesystem::path doxygen_;
    boost::filesystem::path websites_;
    boost::filesystem::path codegen_install_;
    boost::filesystem::path saved_out_;
    boost::filesystem::path pulled_source_;
    boost::filesystem::path staged_source_;
    boost::filesystem::path stage_;
    boost::filesystem::path install_;
    boost::filesystem::path bin_;
    boost::filesystem::path rb_codegen_;
    boost::filesystem::path rb_codegen_tmpl_;
    boost::filesystem::path db_tmpl_;
    boost::filesystem::path database_tmpl_;
    boost::filesystem::path mongoid_tmpl_;
    boost::filesystem::path extjs_tmpl_;
    boost::filesystem::path data_model_tmpl_;
    boost::filesystem::path lookup_tmpl_;
    boost::filesystem::path cpp_;
    boost::filesystem::path headers_;
    boost::filesystem::path data_;
    boost::filesystem::path boost_build_;
    boost::filesystem::path libs_;
    boost::filesystem::path apps_;
    boost::filesystem::path python_;
    boost::filesystem::path dlang_;
    boost::filesystem::path dlang_tmpl_;
    friend class fcs::patterns::Singleton_impl< Place >;
  };

  // Support for streaming non-static streamable members of Place
  inline
  std::ostream& operator<<(std::ostream& out, Place const& item) {
    fcs::utils::Block_indenter indenter;
    char const* indent(indenter.current_indentation_text());
    out << '\n' << indent << "Place:(" << &item << "):{";
    out << '\n' << indent << "  top:" << item.top_;
    out << '\n' << indent << "  ruby_lib:" << item.ruby_lib_;
    out << '\n' << indent << "  ruby_gems:" << item.ruby_gems_;
    out << '\n' << indent << "  codegen:" << item.codegen_;
    out << '\n' << indent << "  usr_lib:" << item.usr_lib_;
    out << '\n' << indent << "  usr_include:" << item.usr_include_;
    out << '\n' << indent << "  cpp_standard_lib:" << item.cpp_standard_lib_;
    out << '\n' << indent << "  ruby_scripts:" << item.ruby_scripts_;
    out << '\n' << indent << "  elisp:" << item.elisp_;
    out << '\n' << indent << "  doxygen:" << item.doxygen_;
    out << '\n' << indent << "  websites:" << item.websites_;
    out << '\n' << indent << "  codegen_install:" << item.codegen_install_;
    out << '\n' << indent << "  saved_out:" << item.saved_out_;
    out << '\n' << indent << "  pulled_source:" << item.pulled_source_;
    out << '\n' << indent << "  staged_source:" << item.staged_source_;
    out << '\n' << indent << "  stage:" << item.stage_;
    out << '\n' << indent << "  install:" << item.install_;
    out << '\n' << indent << "  bin:" << item.bin_;
    out << '\n' << indent << "  rb_codegen:" << item.rb_codegen_;
    out << '\n' << indent << "  rb_codegen_tmpl:" << item.rb_codegen_tmpl_;
    out << '\n' << indent << "  db_tmpl:" << item.db_tmpl_;
    out << '\n' << indent << "  database_tmpl:" << item.database_tmpl_;
    out << '\n' << indent << "  mongoid_tmpl:" << item.mongoid_tmpl_;
    out << '\n' << indent << "  extjs_tmpl:" << item.extjs_tmpl_;
    out << '\n' << indent << "  data_model_tmpl:" << item.data_model_tmpl_;
    out << '\n' << indent << "  lookup_tmpl:" << item.lookup_tmpl_;
    out << '\n' << indent << "  cpp:" << item.cpp_;
    out << '\n' << indent << "  headers:" << item.headers_;
    out << '\n' << indent << "  data:" << item.data_;
    out << '\n' << indent << "  boost_build:" << item.boost_build_;
    out << '\n' << indent << "  libs:" << item.libs_;
    out << '\n' << indent << "  apps:" << item.apps_;
    out << '\n' << indent << "  python:" << item.python_;
    out << '\n' << indent << "  dlang:" << item.dlang_;
    out << '\n' << indent << "  dlang_tmpl:" << item.dlang_tmpl_;
    out << indent << "}\n";
    return out;
  } 

} // namespace dev
} // namespace fcs
#endif // _FCS_DEV_PLACE_H_
