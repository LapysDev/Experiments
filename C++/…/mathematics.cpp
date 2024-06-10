#include <cfloat>
#include <ciso646>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>

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

#define FLT_RADIX     __FLT_RADIX__
#define LDBL_EPSILON  __LDBL_EPSILON__
#define LDBL_MANT_DIG __LDBL_MANT_DIG__
#define LDBL_MAX      __LDBL_MAX__
#define LDBL_MAX_EXP  __LDBL_MAX_EXP__
#define LDBL_MIN      __LDBL_MIN__

/* … → Functions evaluate to numeral base 10 */
namespace {
  uintmax_t   abs             (intmax_t);
  long double abs             (long double);
  uintmax_t   abs             (uintmax_t);
  long double compute_infinity();
  long double compute_nan     ();
  long double compute_pi      (std::size_t = static_cast<std::size_t>(-1), bool* = NULL);
  std::size_t countof         (intmax_t);
  std::size_t countof         (long double);
  std::size_t countof         (uintmax_t);
  long double fract           (long double);
  long double ifactorial      (long double, bool* = NULL);
  uintmax_t   ifactorial      (uintmax_t,   bool* = NULL);
  long double imaxof          ();
  intmax_t    ipow            (intmax_t,    intmax_t,    bool* = NULL);
  long double ipow            (long double, long double, bool* = NULL);
  uintmax_t   ipow            (uintmax_t,   uintmax_t,   bool* = NULL);
  bool        is_denormal     (long double);
  bool        is_infinite     (long double);
  bool        is_nan          (long double);
  bool        is_subnormal    (long double);
  long double maxprecof       (long double);
  intmax_t    multiply        (intmax_t,    intmax_t,    bool* = NULL);
  long double multiply        (long double, long double, bool* = NULL);
  uintmax_t   multiply        (uintmax_t,   uintmax_t,   bool* = NULL);
  long double next            (long double);
  bool        parity          (intmax_t);
  bool        parity          (long double);
  bool        parity          (uintmax_t);
  long double prev            (long double);
  signed char sign            (intmax_t,    signed char = 0);
  signed char sign            (long double, signed char = 0);
  signed char sign            (uintmax_t,   signed char = 0);
  long double trunc           (long double);

  /* … */
  // … → abs(𝙭) - Absolute value of 𝙭
  uintmax_t abs(intmax_t const number) {
    // → `INTMAX_MIN` not representable as positive `|number|` using `intmax_t`
    return sign(number) == -1 ? -number : +number;
  }

  long double abs(long double const number) {
    return -0.0L == number ? +0.0L : sign(number, +1) == -1 ? -number : +number;
  }

  uintmax_t abs(uintmax_t const number) {
    return number;
  }

  // … → compute_infinity() - Infinity floating-point representative
  long double compute_infinity() {
    return 1.0L / 0.0L;
  }

  // … → compute_nan() - Non-numeral floating-point representative i.e. NaN
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

  // … → `https://en.wikipedia.org/wiki/Chudnovsky_algorithm` (or alternatively `https://en.wikipedia.org/wiki/Ramanujan–Sato_series` for a different formula)
  long double compute_pi(std::size_t iterationCount, bool* const representable) {
    long double pi = 0.0L;

    // …
    if (0u == iterationCount)
    return pi;

    // … → `Σₖ₌₀((-1)ᵏ(6k)!(545140134k + 13591409) ÷ (3k)!(k!)³(640320)³ᵏ⁺³ᐟ²)`
    for (long double index = 0.0L; iterationCount; ++index, iterationCount -= iterationCount != static_cast<std::size_t>(-1)) {
      long double iteration[2]     = {1.0L, 1.0L};
      bool        subrepresentable = index <= imaxof();
      long double term;

      // …
      iteration[0] *= term = ipow(-1.0L, index, &subrepresentable);
      iteration[0] *= term = ifactorial(index * 6.0L, &subrepresentable);
      iteration[0] *= term = multiply(545140134.0L, index, &subrepresentable) + 13591409.0L;

      iteration[1] *= term = ifactorial(index * 3.0L, &subrepresentable);
      iteration[1] *= term = ipow(ifactorial(index, &subrepresentable), 3.0L, &subrepresentable);
      iteration[1] *= term = multiply(512384047.996L /* → `640320³ᐟ²` */, ipow(640320.0L, index * 3.0L, &subrepresentable) /* → `640320³ᵏ` */); // → j-function of negated Heegner number

      if (not subrepresentable) {
        if (iterationCount == static_cast<std::size_t>(-1))
        break;

        if (representable) {
          *representable = false;
          return 0.0L;
        }
      }

      // …
      pi += iteration[0] / iteration[1];
    }

    return 1.0L / (pi * 12.0L);
  }

  // … → countof(𝙭) - Number of denary digits representing 𝙭
  std::size_t countof(intmax_t const number) {
    return countof(abs(number));
  }

  std::size_t countof(long double const number) {
    long double characteristics = trunc(number); //
    std::size_t count           = 0u;            // → Number of significant digits
    long double mantissa        = fract(number); //
    std::size_t subcount        = 0u;            // → Number of significant/ trailing zero digits

    // → Unsure how to interpret the denary mantissa of `number`
    for (long double base = LDBL_MIN; base != base + LDBL_EPSILON; base *= 10.0L) {
      mantissa *= 10.0L;

      for (std::size_t digit = 0u; /* digit != 10u */; ++digit)
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

  std::size_t countof(uintmax_t number) {
    std::size_t count = 0u;

    // …
    for (; number; number /= 10u)
    ++count;

    return count + (0u == count);
  }

  // … → fract(𝙭) - Fractional value of 𝙭 without its characteristics
  long double fract(long double const number) {
    return number - trunc(number);
  }

  // … → ifactorial(𝙭) - Factorial of integer 𝙭
  long double ifactorial(long double integer, bool* const representable) {
    long double factorial = 1.0L;

    // …
    while (integer >= 1.0L) {
      if (representable and factorial > LDBL_MAX / integer) {
        *representable = false;
        return 0.0L;
      }

      factorial *= integer--;
    }

    return factorial;
  }

  uintmax_t ifactorial(uintmax_t integer, bool* const representable) {
    uintmax_t factorial = 1u;

    // …
    while (integer) {
      if (representable and factorial > UINTMAX_MAX / integer) {
        *representable = false;
        return 0u;
      }

      factorial *= integer--;
    }

    return factorial;
  }

  // … → imaxof() - Maximum integer value of floating-point type with complete integer precision; Equivalent to `maxprecof(1.0L)`
  long double imaxof() {
    long double maximum = 1;

    // … → Simplified form of `maximum = ipow(FLT_RADIX, LDBL_MANT_DIG - 1.0L)`
    for (struct { unsigned count, exponent; long double multiplier; } iteration = {1u, LDBL_MANT_DIG - 1u, FLT_RADIX}; iteration.exponent; ) {
      if (iteration.count > iteration.exponent) {
        iteration.count      = 1u;
        iteration.multiplier = FLT_RADIX;
      }

      maximum              *= iteration.multiplier;
      iteration.multiplier *= iteration.multiplier;
      iteration.exponent   -= iteration.count;
      iteration.count      *= 2u;
    }

    return (maximum - 0.0L) + (maximum - 1.0L);
  }

  // … → ipow(𝙭, 𝙣) - Integer 𝙣th power of 𝙭
  intmax_t ipow(intmax_t const base, intmax_t const exponent, bool* const representable) {
    if (representable and (0 == base and sign(exponent) == -1)) {
      *representable = false;
      return 0;
    }

    return ipow(abs(base), abs(exponent), representable) * (not parity(exponent) and sign(base) == -1 ? -1 : +1);
  }

  long double ipow(long double const base, long double exponent, bool* const representable) {
    bool const  inverse = exponent and sign(exponent) == -1;
    long double power   = 1.0L;

    // …
    if (exponent) {
      exponent = abs(exponent);

      for (struct { long double count; struct { long double values[LDBL_MAX_EXP]; std::size_t length; } multipliers; } iteration = {1.0L, {{abs(base)}, 1u}}; exponent; ) {
        long double &count      = iteration.count;
        long double  multiplier = iteration.multipliers.values[iteration.multipliers.length - 1u];

        // …
        if (count < exponent and multiplier < LDBL_MAX / multiplier) {
          count      *= 2.0L;
          multiplier *= multiplier;

          iteration.multipliers.values[iteration.multipliers.length++] = multiplier; // → Memoize `multiplier` since `isqrt(…)` could otherwise be slower
        }

        while (count > exponent) {
          count     /= 2.0L;                                                              // → Could also be memoized with a `.counts` list analogous to `.multipliers`
          multiplier = iteration.multipliers.values[--iteration.multipliers.length - 1u]; // → `isqrt(multiplier)`
        }

        if (representable and power > LDBL_MAX / multiplier) {
          *representable = false;
          return 0.0L;
        }

        exponent -= count;
        power    *= multiplier * (count == 1.0L and sign(base) == -1 ? -1.0L : +1.0L);
      }
    }

    return inverse ? 1.0L / power : power;
  }

  uintmax_t ipow(uintmax_t const base, uintmax_t exponent, bool* const representable) {
    uintmax_t power = 1u;

    // …
    for (struct { uintmax_t count; struct { uintmax_t values[CHAR_BIT * sizeof(uintmax_t)]; std::size_t length; } multipliers; } iteration = {1u, {{base}, 1u}}; exponent; ) {
      uintmax_t &count      = iteration.count;
      uintmax_t  multiplier = iteration.multipliers.values[iteration.multipliers.length - 1u];

      // …
      if (count < exponent and multiplier < UINTMAX_MAX / multiplier) {
        count      *= 2u;
        multiplier *= multiplier;

        iteration.multipliers.values[iteration.multipliers.length++] = multiplier; // → Memoize `multiplier` since `isqrt(…)` could otherwise be slower
      }

      while (count > exponent) {
        count     /= 2u;                                                                // → Could also be memoized with a `.counts` list analogous to `.multipliers`
        multiplier = iteration.multipliers.values[--iteration.multipliers.length - 1u]; // → `isqrt(multiplier)`
      }

      if (representable and power > UINTMAX_MAX / multiplier) {
        *representable = false;
        return 0.0L;
      }

      exponent -= count;
      power    *= multiplier;
    }

    return power;
  }

  // … → is_denormal(𝙭) - Determines if 𝙭 is a denormalized floating-point value
  bool is_denormal(long double const number) {
    // → All subnormals are denormals, but not all denormals are subnormals
    return is_subnormal(number) or false;
  }

  // … → is_infinite(𝙭) - Determines if 𝙭 is a negative/ positive infinity floating-point value
  bool is_infinite(long double const number) {
    return number == (number + 0.0L) * (number + 1.0L);
  }

  // … → is_nan(𝙭) - Determines if 𝙭 is a NaN floating-point value
  bool is_nan(long double const number) {
    return number != number;
  }

  // … → is_subnormal(𝙭) - Determines if 𝙭 is a subnormal floating-point value
  bool is_subnormal(long double const number) {
    #ifdef LDBL_HAS_SUBNORM
      return not is_nan(number) and number < LDBL_MIN;
    #endif

    (void) number;
    return false;
  }

  // … → maxprecof(𝙭) - Maximum normalized floating-point value with precision 𝙭
  long double maxprecof(long double const precision) {
    if (is_infinite(precision) or is_nan(precision)) {
      long double maximum = LDBL_MAX;

      // …
      while (precision != maximum - (maximum - precision))
      maximum /= FLT_RADIX;

      return maximum;
    }

    return precision;
  }

  // … → multiply(𝙭, 𝙮) - Scalar multiplication of 𝙭 and 𝙮
  intmax_t multiply(intmax_t const numberA, intmax_t const numberB, bool* const representable) {
    if (representable and abs(numberA) > INTMAX_MAX / abs(numberB)) {
      *representable = false;
      return 0;
    }

    return numberA * numberB;
  }

  long double multiply(long double const numberA, long double const numberB, bool* const representable) {
    if (representable and abs(numberA) > LDBL_MAX / abs(numberB)) {
      *representable = false;
      return 0.0L;
    }

    return numberA * numberB;
  }

  uintmax_t multiply(uintmax_t const numberA, uintmax_t const numberB, bool* const representable) {
    if (representable and numberA > UINTMAX_MAX / numberB) {
      *representable = false;
      return 0u;
    }

    return numberA * numberB;
  }

  // … → next(𝙭) - Next normalized floating-point value after 𝙭
  long double next(long double const number) {
    if (not is_infinite(number) and not is_nan(number)) {
      long double       next      = abs(number);
      long double const maximum   = LDBL_MAX;
      long double       precision = LDBL_EPSILON;

      // …
      for (; next == next + precision; precision *= 2.0L) {
        if (maximum != maximum - precision)
        return number;
      }

      return next + precision;
    }

    return number;
  }

  // … → parity(𝙭) - Parity (evenness) of integer 𝙭
  bool parity(intmax_t const integer) {
    return integer % 2 == 0;
  }

  bool parity(long double integer) {
    long double counter    = 1.0L;
    long double truncation = 0.0L;

    // …
    integer = abs(integer);

    while (integer > counter)
      counter *= 2.0L;

    while (counter != 1.0L) {
      truncation += counter * (integer >= counter + truncation);
      counter    /= 2.0L;
    }

    // …
    return integer - truncation < 1.0L;
  }

  bool parity(uintmax_t const integer) {
    return integer % 2u == 0;
  }

  // … → prev(𝙭) - Previous normalized floating-point value before 𝙭
  long double prev(long double const number) {
    if (not is_infinite(number) and not is_nan(number)) {
      long double const maximum   = LDBL_MAX;
      long double       precision = LDBL_EPSILON;
      long double       previous  = abs(number);

      // …
      for (; previous == previous - precision; precision *= 2.0L) {
        if (maximum != maximum - precision)
        return number;
      }

      return previous - precision;
    }

    return number;
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
          unsigned char const (&sublayout)[sizeof(long double)] = static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &static_cast<long double const&>(-1.0L), sizeof(long double)));

          // …
          if (0x00u != sublayout[0])
          return 0x00u != static_cast<unsigned char*>(std::memcpy(layout, &number, sizeof(long double)))[0] ? -1 : +1;

          if (0x00u != sublayout[sizeof(long double) - 1u])
          return 0x00u != static_cast<unsigned char*>(std::memcpy(layout, &number, sizeof(long double)))[sizeof(long double) - 1u] ? -1 : +1;
        }

        return signedness;
      }
    #endif

    return is_nan(number) ? signedness : number > -0.0L ? +1 : number < +0.0L ? -1 : signedness;
  }

  signed char sign(uintmax_t const number, signed char const signedness) {
    return number > 0u ? 1 : signedness;
  }

  // … → trunc(𝙭) - Truncated value of 𝙭 without its mantissa
  long double trunc(long double number) {
    if (is_infinite(number) or is_nan(number)) {
      long double       counter    = 1.0L;
      long double const signedness = sign(number, +1);
      long double       truncation = 0.0L;

      // … → Aggregate sum of `number`'s characteristics using powers of `2`, which normally matches the base of its floating-point type `FLT_RADIX`
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

    return number;
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::printf("[...]: %Lf", compute_pi());
}
