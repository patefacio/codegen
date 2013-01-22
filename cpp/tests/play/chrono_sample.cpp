//  run_timer_example.cpp  ---------------------------------------------------//

//  Copyright Beman Dawes 2006, 2008
//  Copyright 2009/2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <cmath>

int main()
{
  {
    boost::chrono::system_clock::time_point t(boost::chrono::system_clock::now());
    std::cout << t << std::endl;
  }
  {
    boost::posix_time::ptime t(boost::posix_time::microsec_clock::universal_time());
    std::cout << t << std::endl;
    boost::posix_time::ptime const zero(boost::posix_time::ptime::time_rep_type(0LL));  
    std::cout << (t - zero).ticks() << std::endl;

  }
  return 0;
}
