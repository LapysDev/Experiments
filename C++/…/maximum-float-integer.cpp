#include <cfloat>
#include <cmath>
#include <cstdio>

/* Main */
int main(int, char*[]) /* noexcept */ {
  long double const maximum = std::pow(FLT_RADIX, LDBL_MANT_DIG - 1.0L);
  std::printf("%Lf", (maximum - 0.0L) + (maximum - 1.0L));
}
