#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ... */
int reverse(int number) {
  int evaluation = 0;
  while (number) {
    evaluation = (evaluation * 10) + (number % 10);
    number /= 10;
  }
  return evaluation;
}

/* Main */
int main(void) {
  ::srand(::time(NULL));

  for (int count = 10, dummy; ~count; --count) {
    dummy = ::rand() % 1000;
    ::printf("%i ^v %i\r\n", dummy, reverse(dummy));
  }
}
