#include <iostream>
#include <boost/mem_fn.hpp>

template < typename T >
class Sample {

public:
  Sample() {
    method_requirements(0);
  }

  void moo(T const& t) {
    t.food(3);
  }

private:

  inline static void method_requirements(T const*) {
    using boost::mem_fn;
    mem_fn(& T::food);
  }

};

struct Goo {
  void foo(int i) const {
    std::cout << "Foo called with " << i << std::endl;
  }
  void food(int i) const {
    std::cout << "Food called with " << i << std::endl;
  }
};

int main(int argc, char** argv) {
  Goo g;
  g.foo(3);

  using boost::mem_fn;
  mem_fn(&Goo::foo);

  Sample< Goo > x;
  x.moo(g);

  return 0;
}
