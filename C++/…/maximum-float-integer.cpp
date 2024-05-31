#include <cfloat>
#include <cmath>
#include <cstddef>
#include <cstdio>

/* Main */
int main(int, char*[]) /* noexcept */ {
  float max = std::pow(FLT_RADIX, FLT_MAX_EXP - 1.0f);

  // ...
  while (max == max - 1.0f || max == max + 1.0f)
    max /= 2.0f;

  max += max - 1.0f;
  std::printf("%f", (double) max);
}
