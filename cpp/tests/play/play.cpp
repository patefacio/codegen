#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "fcs/timestamp.hpp"

struct X_pod {
//  X() : a_(0), b_(0) {}
  int a_;
  int b_;

  struct X {
    X(X_pod &x) : x_(x) {}
    X_pod &x_;
    int a() const {
      return x_.a_;
    }
    int b() const {
      return x_.b_;
    }

  };

  operator X() {
    return X(*this);
  }
  
//  virtual void foo() {
//  }
};

struct X_D : virtual public X_pod {
  int c_;
};

struct X_C : public X_D, virtual public X_pod {
  int foo_;
};



typedef X_pod::X X;

int main(int argc, char** argv) {

  using namespace fcs::timestamp;

  boost::posix_time::ptime pt(boost::posix_time::microsec_clock::local_time());
  boost::posix_time::ptime const zero(boost::posix_time::ptime::time_rep_type(0LL));  
  long long all_ticks(ticks(pt));
  std::cout << all_ticks << std::endl;
  std::cout << std::hex << all_ticks << std::endl;
  std::cout << std::hex << (0xffffffff00000000LL & all_ticks) << std::endl;

  boost::posix_time::ptime const now(boost::posix_time::ptime::time_rep_type((pt - zero).ticks()));  
  std::cout << "now:" << now << std::endl;

  struct timeval tv;
  gettimeofday(&tv, 0);
  std::cout << tv.tv_sec << ", " << tv.tv_usec << std::endl;
  long long seconds(tv.tv_sec);
  std::cout << (seconds << 32) << std::endl;
  std::cout << std::hex << (seconds << 32) << std::endl;
//  std::cout << to_iso_string(zero + boost::posix_time::minutes(1)) << std::endl;

  typedef std::vector< boost::gregorian::date > dates_t;
  dates_t dates;
  dates.push_back(boost::gregorian::date(1400, 1, 1));
  dates.push_back(boost::gregorian::date(2010, 1, 1));
  dates.push_back(boost::gregorian::date(2011, 1, 1));
  dates.push_back(boost::gregorian::date(9999, 1, 1));
  BOOST_FOREACH(boost::gregorian::date const& d, dates) {
    std::cout << "Date: " << to_iso_string(d) 
//              << "\n => days: " << d.julian_day() 
              << "\n => julian_day: " << d.julian_day() 
              << "\n => modjulian_day: " << d.modjulian_day() << std::endl;
  }

//  std::cout << pt.as_number() << std::endl;

//  std::cout << pt - pt2 << std::endl;
  std::cout << offsetof(X_pod,a_) << std::endl;
  std::cout << offsetof(X_pod,b_) << std::endl;
  std::cout << offsetof(X_D,c_) << std::endl;
  std::cout << offsetof(X_C,foo_) << std::endl;

//  std::cout << offsetof(X,ptime_) << std::endl;

  return 0;
}

