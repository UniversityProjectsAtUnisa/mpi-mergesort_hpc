#include <stddef.h>
#include <stdio.h>
#include <math.h>


int main(int argc, char const *argv[]) {
  size_t a = __LONG_MAX__*2-3;
  size_t b = a / 2;
  size_t c = (long double) a / 2;
  long double z = (double) a / 2;
  size_t d = ceill(z);


  printf("%lu\n%lu\n%lu\n%Lf\n%lu\n", a, b, c, z, d);
  int n;
  scanf("%d\n", n);
  return 0;
}
