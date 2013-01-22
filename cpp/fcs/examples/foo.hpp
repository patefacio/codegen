/******************************************************************************
 * foo.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file foo.hpp
 *
 * \brief Test performance of implementation of operator<
 * 
 */
#ifndef _FCS_EXAMPLES_FOO_H_
#define _FCS_EXAMPLES_FOO_H_

#include "fcs/examples/apiheader.hpp"
#include "sample.hpp"
#include <boost/pimpl/pimpl.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <string>

// Forward class declarations
namespace boost {  class regex;  }
class my_special_class;


// custom <foo global header section>
// end <foo global header section>
namespace fcs {
namespace examples {

  //! Test performance of implementation of operator<
  class SAMPLE_API foo :
    public pimpl< foo >::pointer_semantics 
  {
  public:

    // Class typedefs
    typedef boost::function< int (void)> BoostFunctorGoo;
    typedef std::shared_ptr< boost::filesystem::path > PathPtr;
    typedef std::vector< std::string > NameList;
    typedef std::vector< NameList > NameListList;
    typedef std::map< std::string, std::string > NameMap;
    typedef std::map< std::string, NameMap > NameMapMap;

    explicit foo(
      NameMapMap const& nameMapMap
    );

    foo();

    /////////////////////////////////////////////////////////////////
    // member accessors
    /////////////////////////////////////////////////////////////////
    std::string const& s1() const;

    void s1(std::string const& val);

    std::string & s1();

    std::string const& s2() const;

    void s2(std::string const& val);

    std::string & s2();

    int const& s3() const;

    void s3(int const& val);

    int & s3();

    std::string const& s4() const;

    void s4(std::string const& val);

    std::string & s4();

    double const& d5() const;

    void d5(double const& val);

    double & d5();

    NameList const& nameList() const;

    void nameList(NameList const& val);

    NameList & nameList();

    NameMap const& nameMap() const;

    void nameMap(NameMap const& val);

    NameMap & nameMap();

    NameMapMap const& nameMapMap() const;

    void nameMapMap(NameMapMap const& val);

    NameMapMap & nameMapMap();

    PathPtr const& aPath() const;

    void aPath(PathPtr const& val);

    PathPtr & aPath();

    PathPtr const& anotherPath() const;

    void anotherPath(PathPtr const& val);

    PathPtr & anotherPath();

  };

} // namespace examples
} // namespace fcs
#endif // _FCS_EXAMPLES_FOO_H_
