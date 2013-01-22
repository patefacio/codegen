#include <boost/function.hpp>
#include <iostream>
#include <functional>
#include <boost/array.hpp>
#include <algorithm>

struct X {
  int foo(int x) { std::cout << x << std::endl; return x; }
  int foo(int x, int y) { std::cout << x << ',' << y << std::endl; return x; }
};

int main()
{
  boost::function<int (int)> f;
  X x;
  f = std::bind1st(
    std::mem_fun(&X::foo), &x);
  f(5); 

  boost::function< bool (int) > g(std::bind1st(std::greater<int>(), 3)); 
  std::cout << g(2) << std::endl;
  g = std::bind1st(std::greater<int>(), 1);
  std::cout << g(2) << std::endl;

  g = std::bind2nd(std::greater<int>(), 1);
  std::cout << g(2) << std::endl;

  g = std::bind2nd(std::greater<int>(), 3);
  std::cout << g(2) << std::endl;

  boost::array< int, 5 > ar = {{ 1,2,3,4,5 }};
  int bigger(std::count_if(ar.begin(), ar.end(), std::bind2nd(std::greater<int>(), 4)));
  std::cout << "Count bigger than 4: " << bigger << std::endl;

  int bigger2(std::count_if(ar.begin(), ar.end(), std::bind1st(std::greater<int>(), 4)));
  std::cout << "Count less than 4: " << bigger2 << std::endl;

  return 0;
}
