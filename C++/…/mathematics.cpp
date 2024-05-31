#include <cfloat>
#include <ciso646>
#include <climits>
#include <cstddef>
#include <cstdio>

#if defined __STDC_IEC_559__
# include <cstring>
# define SUPPORTS_IEEE754_FLOAT true
#elif defined __GNUC__ or defined __GNUC_MINOR__ or defined __GNUC_PATCHLEVEL__
# ifdef __GCC_IEC_559
#   if __GCC_IEC_559
#     include <cstring>
#     define SUPPORTS_IEEE754_FLOAT true
#   else
#     define SUPPORTS_IEEE754_FLOAT false
#   endif
# else
#   define SUPPORTS_IEEE754_FLOAT false
# endif
#else
# include <cstring>
# include <limits>
# define SUPPORTS_IEEE754_FLOAT std::numeric_limits<long double>::is_iec559
#endif

/* … */
long double compute_nan() /* → Attempt to avoid a signaling NaN */ {
  if (SUPPORTS_IEEE754_FLOAT) {
    long double   nan;
    unsigned char nan_layout[sizeof(long double)];

    // …
    for (unsigned char *iterator = nan_layout + sizeof(long double); iterator != nan_layout; )
      *--iterator = UCHAR_MAX; // → Activate all bits in `nan_layout`

    return *static_cast<long double*>(std::memcpy(&nan, nan_layout, sizeof(long double))); // → `nan` or `std::launder(…)`
  }

  // …
  long double const volatile zero = 0.0L;
  return zero / zero;
}

// … → https://en.wikipedia.org/wiki/Chudnovsky_algorithm
long double compute_pi(std::size_t iterationCount = static_cast<std::size_t>(-1), bool* const representable = NULL) {
  long double const maximum          = imaxof<long double>();
  long double       pi               = 0.0L;
  bool              subrepresentable = true;

  // …
  for (std::size_t index = 0; iterationCount; ++index, iterationCount -= iterationCount != static_cast<std::size_t>(-1)) {
    long double iteration[] = {index % 2u ? +1.0L : -1.0L, 1.0L};
    long double term;

    // …
    iteration[0] *= term = ifactorial<long double>(index * 6.0L, &subrepresentable);
    if (representable and not subrepresentable) { *representable = false; return 0.0L; }

    iteration[0] *= term = 13591409.0L + (index * 545140134.0L);
    if (representable and term > maximum) { *representable = false; return 0.0L; }

    iteration[1] *= term = ifactorial<long double>(index * 3.0L, &subrepresentable);
    if (representable and not subrepresentable) { *representable = false; return 0.0L; }

    iteration[1] *= term = ipow<long double>(ifactorial<long double>(index, &subrepresentable), 3.0L, &subrepresentable);
    if (representable and not subrepresentable) { *representable = false; return 0.0L; }

    iteration[1] *= term = ipow<long double>(640320.0L, (index * 3.0L) + (3.0L / 2.0L), &subrepresentable); // → j-function of negated Heegner number
    if (representable and not subrepresentable) { *representable = false; return 0.0L; }

    // …
    pi += iteration[0] / iteration[1];
  }

  return 1.0L / (pi * 12.0L);
}

// …
template <typename type>
type ifactorial(type integer, bool* const representable = NULL) {
  type       factorial = 1;
  type const maximum   = imaxof<type>();

  // …
  while (integer) {
    if (representable and factorial > maximum / integer) {
      *representable = false;
      return 0;
    }

    factorial *= integer--;
  }

  return factorial;
}

// …
template <typename type>
type imaxof();

template <>
long double imaxof<long double>() {
  long double const maximum = pow(FLT_RADIX, LDBL_MANT_DIG - 1.0L);
  return (maximum - 0.0L) + (maximum - 1.0L);
}

template <>
std::size_t imaxof<std::size_t>() {
  return SIZE_MAX;
}

// …
template <typename type>
type ipow(type const base, type exponent, bool* const representable = NULL) {
  type const maximum = imaxof<type>();
  type       power   = 1;

  // …
  while (exponent--) {
    if (representable and power > maximum / base) {
      *representable = false;
      return 0;
    }

    power *= base;
  }

  return power;
}

/* Main */
int main(int, char*[]) /* noexcept */ {}
