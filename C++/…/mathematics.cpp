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

// #define DBL_MANT_DIG  __DBL_MANT_DIG__
// #define FLT_MANT_DIG  __FLT_MANT_DIG__
// #define FLT_MAX       __FLT_MAX__
// #define FLT_RADIX     __FLT_RADIX__
// #define LDBL_EPSILON  __LDBL_EPSILON__
// #define LDBL_MANT_DIG __LDBL_MANT_DIG__
// #define LDBL_MAX      __LDBL_MAX__
// #define LDBL_MIN      __LDBL_MIN__

/* … → Functions evaluate to numeral base 10 */
namespace {
  double             abs        (double);
  float              abs        (float);
  long double        abs        (long double);
  unsigned char      abs        (signed   char);
  unsigned int       abs        (signed   int);
  unsigned long      abs        (signed   long);
  unsigned long long abs        (signed   long long);
  unsigned short     abs        (signed   short);
  unsigned char      abs        (unsigned char);
  unsigned int       abs        (unsigned int);
  unsigned long      abs        (unsigned long);
  unsigned long long abs        (unsigned long long);
  unsigned short     abs        (unsigned short);
  long double        compute_nan();
  long double        fract      (long double);
  bool               is_infinite(long double);
  bool               is_nan     (long double);
  long double        next       (long double);
  long double        prev       (long double);
  signed char        sign       (intmax_t,    signed char = 0);
  signed char        sign       (long double, signed char = 0);
  signed char        sign       (uintmax_t,   signed char = 0);
  long double        trunc      (long double);

  template <typename type> std::size_t countof   (type);
  template <typename type> type        ifactorial(type, bool* = NULL);
  template <typename type> type        imaxof    ();
  template <typename type> type        ipow      (type, type, bool* = NULL);
  template <typename type> type        maxof     ();
  template <typename type> type        maxprecof (type);

  /* … */
  // … → abs(𝙭) - Absolute value of 𝙭
  long double abs(long double const number) {
    return -0.0L == number ? +0.0L : sign(number) == -1 ? -number : +number;
  }

  unsigned long long abs(signed long long const number) {
    // → `LLONG_MIN` not representable as positive `|number|` using `signed long long`
    return sign(number) == -1 ? -number : +number;
  }

  unsigned long long abs(unsigned long long const number) {
    return number;
  }

  double         abs(double         const number) { return abs(static_cast<long double>       (number)); }
  float          abs(float          const number) { return abs(static_cast<long double>       (number)); }
  unsigned char  abs(signed   char  const number) { return abs(static_cast<signed   long long>(number)); }
  unsigned int   abs(signed   int   const number) { return abs(static_cast<signed   long long>(number)); }
  unsigned long  abs(signed   long  const number) { return abs(static_cast<signed   long long>(number)); }
  unsigned short abs(signed   short const number) { return abs(static_cast<signed   long long>(number)); }
  unsigned char  abs(unsigned char  const number) { return abs(static_cast<unsigned long long>(number)); }
  unsigned int   abs(unsigned int   const number) { return abs(static_cast<unsigned long long>(number)); }
  unsigned long  abs(unsigned long  const number) { return abs(static_cast<unsigned long long>(number)); }
  unsigned short abs(unsigned short const number) { return abs(static_cast<unsigned long long>(number)); }

  // … → compute_nan() - Non-numeral floating-point representative
  long double compute_nan() {
    #if SUPPORTS_IEEE754_FLOAT
      if (SUPPORTS_IEEE754_FLOAT) {
        long double   nan;
        unsigned char nan_layout[sizeof(long double)];

        return *static_cast<long double*>(std::memcpy(&nan, std::memset(nan_layout, UCHAR_MAX, sizeof(long double)), sizeof(long double))); // → `nan` or `std::launder(…)`
      }
    #endif

    // … → Attempt to avoid a signaling NaN
    long double const volatile zero = 0.0L;
    return zero / zero;
  }

  // … → countof(𝙭) - Number of denary digits representing 𝙭
  std::size_t countof(long double const number) {
    long double characteristics = trunc(number); //
    std::size_t count           = 0u;            // → Number of significant digits
    long double mantissa        = fract(number); //
    std::size_t subcount        = 0u;            // → Number of significant/ trailing zero digits

    // → Unsure how to interpret the denary mantissa of `number`
    for (long double base = LDBL_MIN; base != base + LDBL_EPSILON; base *= 10.0L) {
      mantissa *= 10.0L;

      for (std::size_t digit = 0u; digit != 10u; ++digit)
      if (mantissa < digit + 1u) {
        if (0u == digit)
          ++subcount;

        else {
          count   += (0u != count ? subcount : 0u) + 1u;
          subcount = 0u;
        }

        // …
        mantissa -= digit;
        break;
      }
    }

    // → Unsure how to interpret the denary characteristics of `number`; See `countof(uintmax_t)`
    for (; characteristics >= 1.0L; characteristics /= 10.0L)
    ++count;

    return count + (0u == count);
  }

  std::size_t countof(signed long long const number) {
    return countof(abs(number));
  }

  std::size_t countof(unsigned long long number) {
    std::size_t count = 0u;

    // …
    for (; number; number /= 10uLL)
    ++count;

    return count + (0u == count);
  }

  std::size_t countof(double const);
  std::size_t countof(signed   char  const number) { return countof(static_cast<signed   long long>(number)); }
  std::size_t countof(signed   int   const number) { return countof(static_cast<signed   long long>(number)); }
  std::size_t countof(signed   long  const number) { return countof(static_cast<signed   long long>(number)); }
  std::size_t countof(signed   short const number) { return countof(static_cast<signed   long long>(number)); }
  std::size_t countof(unsigned char  const number) { return countof(static_cast<unsigned long long>(number)); }
  std::size_t countof(unsigned int   const number) { return countof(static_cast<unsigned long long>(number)); }
  std::size_t countof(unsigned long  const number) { return countof(static_cast<unsigned long long>(number)); }
  std::size_t countof(unsigned short const number) { return countof(static_cast<unsigned long long>(number)); }

  // … → fract(𝙭) - Fractional value of 𝙭 without its characteristics
  long double fract(long double const number) {
    return number - trunc(number);
  }

  // … → is_infinite(𝙭) - Determines if 𝙭 is a negative/ positive infinity floating-point value
  bool is_infinite(long double const number) {
    return number == (number + 0.0L) * (number + 1.0L);
  }

  // … → is_nan(𝙭) - Determines if 𝙭 is a NaN floating-point value
  bool is_nan(long double const number) {
    return number != number;
  }

  // … → next(𝙭) - Next normalized floating-point value after 𝙭
  long double next(long double const number) {
    long double next      = abs(number);
    long double precision = LDBL_EPSILON;

    // …
    while (next == next + precision)
      precision *= 2.0L;

    next += precision;
    return is_infinite(next) ? number : next;
  }

  // … → prev(𝙭) - Previous normalized floating-point value before 𝙭
  long double prev(long double const number) {
    long double precision = LDBL_EPSILON;
    long double previous  = abs(number);

    // …
    while (previous == previous - precision)
      precision *= 2.0L;

    previous -= precision;
    return is_infinite(previous) ? number : previous;
  }

  // … → sign(𝙭) - Signedness of 𝙭
  signed char sign(intmax_t const number, signed char const signedness) {
    return number > 0 ? +1 : number < 0 ? -1 : signedness;
  }

  signed char sign(long double const number, signed char const signedness) {
    #if SUPPORTS_IEEE754_FLOAT
      if (SUPPORTS_IEEE754_FLOAT) {
        unsigned char layout[sizeof(long double)];

        // …
        if (0.0L != number) {
          unsigned char const (&sublayout)[sizeof(long double)] = static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &static_cast<long double const&>(-0.0L), sizeof(long double)));

          // …
          if (0x00u != sublayout[0])
          return 0x00u != static_cast<unsigned char*>(std::memcpy(layout, &number, sizeof(long double)))[0] ? -1 : +1;

          if (0x00u != sublayout[sizeof(long double) - 1u])
          return 0x00u != static_cast<unsigned char*>(std::memcpy(layout, &number, sizeof(long double)))[sizeof(long double) - 1u] ? -1 : +1;
        }

        return signedness;
      }
    #endif

    return number > -0.0L ? +1 : number < +0.0L ? -1 : signedness;
  }

  signed char sign(uintmax_t const number, signed char const signedness) {
    return number > 0u ? 1 : signedness;
  }

  // … → trunc(𝙭) - Truncated value of 𝙭 without its mantissa
  long double trunc(long double number) {
    long double       counter    = 1.0L;
    long double const signedness = sign(number, +1);
    long double       truncation = 0.0L;

    // … → Aggregate sum of `number`'s characteristics using powers of two, which normally matches the base of its floating-point type `FLT_RADIX`
    number *= signedness;

    while (number > counter)
      counter *= 2.0L;

    while (counter >= 1.0L) {
      truncation += counter * (number >= counter + truncation);
      counter    /= 2.0L;
    }

    // …
    return truncation * signedness;
  }

  // … → ifactorial<T>(𝙭) - Factorial of integer 𝙭
  template <typename type>
  type ifactorial(type integer, bool* const representable) {
    type       factorial = 1;
    type const maximum   = maxof<type>();

    // …
    while (integer >= 1) {
      if (representable and factorial > maximum / integer) {
        *representable = false;
        return 0;
      }

      factorial *= integer--;
    }

    return factorial;
  }

  // … → imaxof<T>() - Maximum integer value of `T` with complete integer precision; Equivalent to `maxprecof<T>(1)`
  template <typename type> // → double | float | long double
  type imaxof() {
    type maximum = 1;

    // … → Simplified form of `maximum = ipow<type>(FLT_RADIX, *_MANT_DIG - 1.0L)`
    for (struct { unsigned count, exponent; type multiplier; } iteration = {1u, (sizeof(type) == sizeof(double) ? DBL_MANT_DIG : sizeof(type) == sizeof(float) ? FLT_MANT_DIG : sizeof(type) == sizeof(long double) ? LDBL_MANT_DIG : 0u) - 1u, FLT_RADIX}; iteration.exponent; ) {
      if (iteration.count > iteration.exponent) {
        iteration.count      = 1u;
        iteration.multiplier = FLT_RADIX;
      }

      maximum              *= iteration.multiplier;
      iteration.multiplier *= iteration.multiplier;
      iteration.exponent   -= iteration.count;
      iteration.count      *= 2u;
    }

    return (maximum - 0) + (maximum - 1);
  }

  template <>
  intmax_t imaxof() {
    return INTMAX_MAX;
  }

  template <>
  uintmax_t imaxof() {
    return UINTMAX_MAX;
  }

  // … → ipow(𝙭, 𝙣) - Integer 𝙣th power of 𝙭
  template <typename type>
  type ipow(type const base, type exponent, bool* const representable) {
    bool const inverse = sign(static_cast<long double>(exponent)) == -1;
    type       power   = 1;

    // …
    exponent = abs(static_cast<long double>(exponent));

    for (struct iterator { type count; struct types { enum { maximum = 32u }; type values[maximum]; std::size_t length; } multipliers; } iteration = {1, {{base}, 1u}}; exponent; ) {
      type            &count       = iteration.count;
      typename iterator::types &multipliers = iteration.multipliers;
      type             multiplier  = multipliers.values[multipliers.length - 1u];

      // …
      if (count != exponent) {
        if (multipliers.length != multipliers.maximum and not is_infinite(count * 2) and not is_infinite(multiplier * multiplier)) {
          count      *= 2;
          multiplier *= multiplier;

          multipliers.values[multipliers.length++] = multiplier;
        }

        while (count > exponent /* and multipliers.length != 1u */) {
          count     /= 2; // → Could also be memoized with some `counts` list analogous to the `multipliers` list
          multiplier = multipliers.values[multipliers.length - 2u];

          multipliers.length -= 1u;
        }
      }

      if (representable and is_infinite(power * multiplier)) {
        *representable = false;
        return 0;
      }

      exponent -= count;
      power    *= multiplier;
    }

    return inverse ? static_cast<type>(1) / power : power;
  }

  // … → maxof(𝙭) - Previous floating-point value before 𝙭
  template <>
  float maxof() {
    return FLT_MAX;
  }

  template <>
  intmax_t maxof() {
    return imaxof<intmax_t>();
  }

  template <>
  long double maxof() {
    return LDBL_MAX;
  }

  template <>
  uintmax_t maxof() {
    return imaxof<uintmax_t>();
  }

  // … → maxprecof(𝙭) - Maximum normalized floating-point value with precision 𝙭
  template <typename type>
  type maxprecof(type const precision) {
    type maximum = maxof<type>();

    // …
    while (precision != maximum - (maximum - precision))
    maximum /= FLT_RADIX;

    return maximum;
  }

  // … → `https://en.wikipedia.org/wiki/Chudnovsky_algorithm`
  float compute_pi(std::size_t iterationCount, bool* const representable) {
    float const maximum          = FLT_MAX; // maxprecof<float>(1.0L);
    float       pi               = 0.0f;
    bool        subrepresentable = true;

    // … → `Σₖ₌₀((-1)ᵏ(6k)!(545140134k + 13591409) ÷ (3k)!(k!)³(640320)³ᵏ⁺³ᐟ²)`
    for (std::size_t index = 0u; iterationCount; ++index, iterationCount -= iterationCount != static_cast<std::size_t>(-1)) {
      float iteration[2] = {1.0f, 1.0f};
      float term;

      // …
      iteration[0] *= term = ipow<float>(-1.0f, index, &subrepresentable);
      std::printf("[{%zu}]: %f <= %f == %4.5s" "\r\n", index, term, maximum, subrepresentable ? "true" : "false");
      iteration[0] *= term = ifactorial<float>(index * 6.0L, &subrepresentable);
      std::printf("[{%zu}]: %f <= %f == %4.5s" "\r\n", index, term, maximum, subrepresentable ? "true" : "false");
      iteration[0] *= term = 13591409.0f + (index * 545140134.0f);
      subrepresentable = subrepresentable and term <= maximum;
      std::printf("[{%zu}]: %f <= %f == %4.5s" "\r\n", index, term, maximum, subrepresentable ? "true" : "false");

      iteration[1] *= term = ifactorial<float>(index * 3.0f, &subrepresentable);
      std::printf("[{%zu}]: %f <= %f == %4.5s" "\r\n", index, term, maximum, subrepresentable ? "true" : "false");
      iteration[1] *= term = ipow<float>(ifactorial<float>(index, &subrepresentable), 3.0f, &subrepresentable);
      std::printf("[{%zu}]: %f <= %f == %4.5s" "\r\n", index, term, maximum, subrepresentable ? "true" : "false");
      iteration[1] *= term = /* → `640320³ᐟ²` */ 512384047.996f * /* → 640320³ᵏ */ ipow<float>(640320.0f, index * 3.0f, &subrepresentable); // → j-function of negated Heegner number
      subrepresentable = subrepresentable and term <= maximum;
      std::printf("[{%zu}]: %f <= %f == %4.5s" "\r\n", index, term, maximum, subrepresentable ? "true" : "false");

      subrepresentable = subrepresentable and iteration[0] <= maximum and iteration[1] <= maximum;
      std::printf("[{%zu}]: %f <= %f == %4.5s" "\r\n", index, term, maximum, subrepresentable ? "true" : "false");

      if (representable and not subrepresentable) {
        *representable = false;
        // return iterationCount != static_cast<std::size_t>(-1) ? 0.0L : pi;
      }

      // …
      pi += iteration[0] / iteration[1];
      std::printf("[...]: %f / %f => %f" "\r\n\n", iteration[0], iteration[1], pi);
    }

    return 1.0f / (pi * 12.0f);
  }
}

/* Main */
#include <csignal>
#include <cstdlib>

int main(int, char*[]) /* noexcept */ {
  // struct program { static void exit(int) { std::perror("Segmentation Fault"); std::exit(EXIT_SUCCESS); } };
  bool representable = true;

  // …
  // (void) std::signal(SIGSEGV, &program::exit);

  std::printf("%f"    "\r\n", compute_pi(2u, &representable));
  std::printf("%4.5s" "\r\n", representable ? "true" : "false");
}
