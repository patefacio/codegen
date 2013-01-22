#include <sys/time.h>
#include <iostream>

double foo(double x, double y, double c) {
  return x*x + x*y + c*x*y;
}

int main(int argc, char** argv) {
  hrtime_t start, end;
  start = gethrtime();
  {
    double x(3), y(2), z(1);
    for(int i(0); i<100000; ++i) {
      x = foo(x, y, z);
    }
  }
  end = gethrtime();
  printf("%lld nsec\n on average", (end - start) / 10);
  return 0;
}
