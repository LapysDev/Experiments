#include <cfloat>
#include <ciso646>
#include <climits>
#include <cstdarg>
#include <cstddef>
#include <cstring>
#include <stdint.h>
#if defined __STDC_IEC_559__
# define SUPPORTS_IEEE754_FLOAT true
#elif defined __GNUC__ or defined __GNUC_MINOR__ or defined __GNUC_PATCHLEVEL__
# ifdef __GCC_IEC_559
#   if __GCC_IEC_559
#     define SUPPORTS_IEEE754_FLOAT true
#   else
#     define SUPPORTS_IEEE754_FLOAT false
#   endif
# else
#   include <limits>
#   define SUPPORTS_IEEE754_FLOAT std::numeric_limits<long double>::is_iec559
# endif
#else
# include <limits>
# define SUPPORTS_IEEE754_FLOAT std::numeric_limits<long double>::is_iec559
#endif
#include <cstdio>

#define FLT_RADIX       __FLT_RADIX__
#define LDBL_EPSILON    __LDBL_EPSILON__
#define LDBL_MANT_DIG   __LDBL_MANT_DIG__
#define LDBL_MAX        __LDBL_MAX__
#define LDBL_MAX_10_EXP __LDBL_MAX_10_EXP__
#define LDBL_MAX_EXP    __LDBL_MAX_EXP__
#define LDBL_MIN        __LDBL_MIN__
#include <bitset>
#include <iostream>

/* …
    → Functions evaluate denary numbers (comprised of bits) and only handle values within their expected domains: edge cases like NaN are not considered unless otherwise
    → Functions that optionally evaluate the `representable`-ness of their result typically determine it to be `false` for repeating decimals that are infinitely computed e.g.: `compute_pi()` is only finitely `representable` unlike `ipow()`
    → `representable`-ness could be denoted by `FE_*` floating-point exception constants instead of a `bool` value
*/
namespace {
  template <typename base>
  union _ {
    base const _;

    inline operator base const&         () const          { return _; }
    inline operator base const volatile&() const volatile { return _; }
  };

  /* … */
  uintmax_t         abs                    (intmax_t);
  long double       abs                    (long double);
  uintmax_t         abs                    (uintmax_t);
  long double       acos                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       acosh                  (long double,              std::size_t = 0u, bool* = NULL);
  long double       acot                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       acoth                  (long double,              std::size_t = 0u, bool* = NULL);
  long double       acsc                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       acsch                  (long double,              std::size_t = 0u, bool* = NULL);
  intmax_t          add                    (intmax_t,    intmax_t,                      bool* = NULL);
  long double       add                    (long double, long double,                   bool* = NULL);
  uintmax_t         add                    (uintmax_t,   uintmax_t,                     bool* = NULL);
  long double       asec                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       asech                  (long double,              std::size_t = 0u, bool* = NULL);
  long double       asin                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       asinh                  (long double,              std::size_t = 0u, bool* = NULL);
  long double       atan                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       atan                   (long double, long double, std::size_t = 0u, bool* = NULL);
  long double       atanh                  (long double,              std::size_t = 0u, bool* = NULL);
  long double       bézier                 (std::size_t, long double, ...);
  long double       bézier_cubic           (long double, long double, long double, long double, long double);
  long double       bézier_linear          (long double, long double, long double);
  long double       bézier_quadratic       (long double, long double, long double, long double);
  intmax_t          bitceil                (intmax_t,         bool* = NULL);
  long double       bitceil                (long double,      bool* = NULL);
  uintmax_t         bitceil                (uintmax_t,        bool* = NULL);
  intmax_t          bitclear               (intmax_t,    std::size_t);
  long double       bitclear               (long double, std::size_t);
  uintmax_t         bitclear               (uintmax_t,   std::size_t);
  intmax_t          bitflip                (intmax_t);
  long double       bitflip                (long double);
  uintmax_t         bitflip                (uintmax_t);
  intmax_t          bitflip                (intmax_t,    std::size_t);
  long double       bitflip                (long double, std::size_t);
  uintmax_t         bitflip                (uintmax_t,   std::size_t);
  intmax_t          bitfloor               (intmax_t,         bool* = NULL);
  long double       bitfloor               (long double,      bool* = NULL);
  uintmax_t         bitfloor               (uintmax_t,        bool* = NULL);
  std::size_t       bitpopcount            (intmax_t);
  std::size_t       bitpopcount            (long double);
  std::size_t       bitpopcount            (uintmax_t);
  intmax_t          bitrotleft             (intmax_t,    std::size_t = 1u);
  long double       bitrotleft             (long double, std::size_t = 1u);
  uintmax_t         bitrotleft             (uintmax_t,   std::size_t = 1u);
  intmax_t          bitrotright            (intmax_t,    std::size_t = 1u);
  long double       bitrotright            (long double, std::size_t = 1u);
  uintmax_t         bitrotright            (uintmax_t,   std::size_t = 1u);
  intmax_t          bitset                 (intmax_t,    std::size_t);
  long double       bitset                 (long double, std::size_t);
  uintmax_t         bitset                 (uintmax_t,   std::size_t);
  intmax_t          bitshiftleft           (intmax_t,    std::size_t = 1u);
  long double       bitshiftleft           (long double, std::size_t = 1u);
  uintmax_t         bitshiftleft           (uintmax_t,   std::size_t = 1u);
  intmax_t          bitshiftright          (intmax_t,    std::size_t = 1u);
  long double       bitshiftright          (long double, std::size_t = 1u);
  uintmax_t         bitshiftright          (uintmax_t,   std::size_t = 1u);
  intmax_t          bitswap                (intmax_t);
  long double       bitswap                (long double);
  uintmax_t         bitswap                (uintmax_t);
  std::size_t       bitwidth               (uintmax_t);
  intmax_t          cbrt                   (intmax_t,         bool* = NULL);
  long double       cbrt                   (long double,      bool* = NULL);
  uintmax_t         cbrt                   (uintmax_t,        bool* = NULL);
  long double       ceil                   (long double);
  intmax_t          clamp                  (intmax_t,    intmax_t,    intmax_t);
  long double       clamp                  (long double, long double, long double);
  uintmax_t         clamp                  (uintmax_t,   uintmax_t,   uintmax_t);
  _<long double[2]> clerp                  (long double, long double const (&)[2], long double const (&)[2]);
  long double       compute_eta            (std::size_t = 0u, bool* = NULL);
  long double       compute_euler          (std::size_t = 0u, bool* = NULL);
  long double       compute_infinity       ();
  long double       compute_nan            ();
  long double       compute_pi             (std::size_t = 0u,              bool* = NULL);
  long double       compute_tau            (std::size_t = 0u,              bool* = NULL);
  long double       cos                    (long double, std::size_t = 0u, bool* = NULL);
  long double       cosh                   (long double, std::size_t = 0u, bool* = NULL);
  long double       cot                    (long double, std::size_t = 0u, bool* = NULL);
  std::size_t       countof                (intmax_t);
  std::size_t       countof                (long double);
  std::size_t       countof                (uintmax_t);
  long double       csc                    (long double, std::size_t = 0u, bool* = NULL);
  intmax_t          divide                 (intmax_t,    intmax_t,         bool* = NULL);
  long double       divide                 (long double, long double,      bool* = NULL);
  uintmax_t         divide                 (uintmax_t,   uintmax_t,        bool* = NULL);
  long double       ease                   (long double);
  long double       ease_in                (long double);
  long double       ease_in_back           (long double);
  long double       ease_in_bounce         (long double);
  long double       ease_in_circular       (long double);
  long double       ease_in_cubic          (long double);
  long double       ease_in_elastic        (long double);
  long double       ease_in_exponential    (long double);
  long double       ease_in_out            (long double);
  long double       ease_in_out_back       (long double);
  long double       ease_in_out_bounce     (long double);
  long double       ease_in_out_circular   (long double);
  long double       ease_in_out_cubic      (long double);
  long double       ease_in_out_elastic    (long double);
  long double       ease_in_out_exponential(long double);
  long double       ease_in_out_quadratic  (long double);
  long double       ease_in_out_quartic    (long double);
  long double       ease_in_out_quintic    (long double);
  long double       ease_in_out_sine       (long double);
  long double       ease_in_quadratic      (long double);
  long double       ease_in_quartic        (long double);
  long double       ease_in_quintic        (long double);
  long double       ease_in_sine           (long double);
  long double       ease_out               (long double);
  long double       ease_out_back          (long double);
  long double       ease_out_bounce        (long double);
  long double       ease_out_circular      (long double);
  long double       ease_out_cubic         (long double);
  long double       ease_out_elastic       (long double);
  long double       ease_out_exponential   (long double);
  long double       ease_out_quadratic     (long double);
  long double       ease_out_quartic       (long double);
  long double       ease_out_quintic       (long double);
  long double       ease_out_sine          (long double);
  long double       exp                    (long double, std::size_t = 0u, bool* = NULL);
  long double       floor                  (long double);
  _<long double[2]> fract                  (long double);
  intmax_t          gcd                    (intmax_t,    intmax_t);
  long double       gcd                    (long double, long double);
  uintmax_t         gcd                    (uintmax_t,   uintmax_t);
  intmax_t          icbrt                  (intmax_t,    bool* = NULL);
  long double       icbrt                  (long double, bool* = NULL);
  uintmax_t         icbrt                  (uintmax_t,   bool* = NULL);
  long double       ifactorial             (long double, bool* = NULL);
  uintmax_t         ifactorial             (uintmax_t,   bool* = NULL);
  long double       imaxof                 ();
  intmax_t          ipow                   (intmax_t,    intmax_t,    bool* = NULL);
  long double       ipow                   (long double, long double, bool* = NULL);
  uintmax_t         ipow                   (uintmax_t,   uintmax_t,   bool* = NULL);
  uintmax_t         iroot                  (intmax_t,    intmax_t,    bool* = NULL);
  long double       iroot                  (long double, long double, bool* = NULL);
  uintmax_t         iroot                  (uintmax_t,   uintmax_t,   bool* = NULL);
  intmax_t          isqrt                  (intmax_t,                 bool* = NULL);
  long double       isqrt                  (long double,              bool* = NULL);
  uintmax_t         isqrt                  (uintmax_t,                bool* = NULL);
  bool              is_denormal            (long double);
  bool              is_infinite            (long double);
  bool              is_integer             (long double);
  bool              is_nan                 (long double);
  bool              is_subnormal           (long double);
  _<uintmax_t[4]>   jsf                    (std::size_t, uintmax_t = 0xCAFE5EED00000001uLL);
  _<uintmax_t[4]>   jsf                    (std::size_t, uintmax_t const (&)[4]); // → Result in `_[3]`
  _<uintmax_t[4]>   jsf                    (std::size_t, uintmax_t const (&)[4], std::size_t, std::size_t, std::size_t);
  intmax_t          lcm                    (intmax_t,    intmax_t);
  long double       lcm                    (long double, long double);
  uintmax_t         lcm                    (uintmax_t,   uintmax_t);
  long double       lerp                   (long double, long double, long double);
  long double       ln                     (long double,              std::size_t = 0u, bool* = NULL);
  long double       log                    (long double, long double, std::size_t = 0u, bool* = NULL);
  long double       log2                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       log8                   (long double,              std::size_t = 0u, bool* = NULL);
  long double       log10                  (long double,              std::size_t = 0u, bool* = NULL);
  long double       log16                  (long double,              std::size_t = 0u, bool* = NULL);
  intmax_t          max                    (intmax_t,    intmax_t);
  long double       max                    (long double, long double);
  uintmax_t         max                    (uintmax_t,   uintmax_t);
  long double       maxprecof              (long double,              std::size_t = 0u, bool* = NULL);
  uintmax_t         maxwidthof             (std::size_t);
  intmax_t          min                    (intmax_t,    intmax_t);
  long double       min                    (long double, long double);
  uintmax_t         min                    (uintmax_t,   uintmax_t);
  intmax_t          modulus                (intmax_t,    intmax_t,    bool* = NULL);
  long double       modulus                (long double, long double, bool* = NULL);
  uintmax_t         modulus                (uintmax_t,   uintmax_t,   bool* = NULL);
  intmax_t          multiply               (intmax_t,    intmax_t,    bool* = NULL);
  long double       multiply               (long double, long double, bool* = NULL);
  uintmax_t         multiply               (uintmax_t,   uintmax_t,   bool* = NULL);
  long double       next                   (long double);
  bool              parity                 (intmax_t);
  bool              parity                 (long double);
  bool              parity                 (uintmax_t);
  intmax_t          pow                    (intmax_t,    intmax_t,    bool* = NULL);
  long double       pow                    (long double, long double, bool* = NULL);
  uintmax_t         pow                    (uintmax_t,   uintmax_t,   bool* = NULL);
  long double       prev                   (long double);
  intmax_t          remainder              (intmax_t,    intmax_t,    bool* = NULL);
  long double       remainder              (long double, long double, bool* = NULL);
  uintmax_t         remainder              (uintmax_t,   uintmax_t,   bool* = NULL);
  intmax_t          root                   (intmax_t,    intmax_t,    bool* = NULL);
  long double       root                   (long double, long double, bool* = NULL);
  uintmax_t         root                   (uintmax_t,   uintmax_t,   bool* = NULL);
  long double       round                  (long double);
  long double       sec                    (long double, std::size_t = 0u, bool* = NULL);
  long double       sech                   (long double, std::size_t = 0u, bool* = NULL);
  signed char       sign                   (intmax_t,    signed char = 0);
  signed char       sign                   (long double, signed char = 0);
  signed char       sign                   (uintmax_t,   signed char = 0);
  long double       sin                    (long double, std::size_t = 0u, bool* = NULL);
  long double       sinh                   (long double, std::size_t = 0u, bool* = NULL);
  long double       slerp                  (long double, long double, long double);
  intmax_t          sqrt                   (intmax_t,                      bool* = NULL);
  long double       sqrt                   (long double,                   bool* = NULL);
  uintmax_t         sqrt                   (uintmax_t,                     bool* = NULL);
  intmax_t          subtract               (intmax_t,    intmax_t,         bool* = NULL);
  long double       subtract               (long double, long double,      bool* = NULL);
  uintmax_t         subtract               (uintmax_t,   uintmax_t,        bool* = NULL);
  long double       tan                    (long double, std::size_t = 0u, bool* = NULL);
  long double       tanh                   (long double, std::size_t = 0u, bool* = NULL);
  long double       trunc                  (long double);
  intmax_t          wrap                   (intmax_t,    intmax_t,    intmax_t,    bool = false);
  long double       wrap                   (long double, long double, long double, bool = false);
  uintmax_t         wrap                   (uintmax_t,   uintmax_t,   uintmax_t,   bool = false);

  long double lcg                    (long double, std::size_t = 16807u, std::size_t = 0u, std::size_t = 2147483647u);
  long double mt                     (long double);
  long double mt32                   (long double, std::size_t = 624u, std::size_t = 397u, std::size_t = 31u, std::size_t = 0x9908B0DFu,         std::size_t = 11u, std::size_t = 0xFFFFFFFFu,         std::size_t = 7u,  std::size_t = 0x9D2C5680u,         std::size_t = 15u, std::size_t = 0xEFC60000u,         std::size_t = 18u, std::size_t = 1812433253u);
  long double mt64                   (long double, std::size_t = 312u, std::size_t = 156u, std::size_t = 31u, std::size_t = 0xB5026F5AA96619E9u, std::size_t = 29u, std::size_t = 0x5555555555555555u, std::size_t = 17u, std::size_t = 0x71D67FFFEDA60000u, std::size_t = 37u, std::size_t = 0xFFF7EEE000000000u, std::size_t = 43u, std::size_t = 6364136223846793005u);
  long double mulberry               (long double);
  long double mulberry32             (long double);
  long double sfc32                  (long double);
  long double splitmix32             (long double);
  long double xorshift               (long double);
  long double xorshift_s             (long double);
  long double xorshift128            (long double);
  long double xorshift128_p          (long double);
  long double xorshift128_s          (long double);
  long double xorshift256_p          (long double);
  long double xorshift_p             (long double);
  long double xorshift128_p          (long double);
  long double xorshift_ss            (long double);
  long double xorshift256            (long double);
  long double xorshift256_ss         (long double);
  long double xorshiro128_ss         (long double);
  long double xorwow                 (long double);

  template <std::size_t size> long double knuth(long double);

  /* … */
  // … → abs(𝙭) - Absolute value of 𝙭
  uintmax_t abs(intmax_t const number) {
    // → `INTMAX_MIN` possibly not representable as positive `|number|` using `intmax_t`
    return sign(number) == -1 ? -number : +number;
  }

  long double abs(long double const number) {
    return -0.0L == number ? +0.0L : sign(number, +1) == -1 ? -number : +number;
  }

  uintmax_t abs(uintmax_t const number) {
    return number;
  }

  // … → acos(𝙭) - Arc cosine of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Relationships_among_the_inverse_trigonometric_functions`)
  long double acos(long double const number, std::size_t const iterationCount, bool* const representable) {
    return atan(number, sqrt((1.0L + number) * (1.0L - number), representable), iterationCount, representable);
  }

  // … → acosh(𝙭) → Area hyperbolic cosine of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions#Conversions`)
  long double acosh(long double const number, std::size_t const iterationCount, bool* const representable) {
    return abs(asinh(sqrt(ipow(number, 2.0L, representable) - 1.0L, representable), iterationCount, representable));
  }

  // … → acot(𝙭) - Arc cotangent of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Relationships_among_the_inverse_trigonometric_functions`)
  long double acot(long double const number, std::size_t const iterationCount, bool* const representable) {
    return atan(divide(1.0L, number, representable), iterationCount, representable);
  }

  // … → acoth(𝙭) → Area hyperbolic cotangent of 𝙭 (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Useful_relations`)
  long double acoth(long double const number, std::size_t const iterationCount, bool* const representable) {
    return atanh(divide(1.0L, number, representable), iterationCount, representable);
  }

  // … → acsc(𝙭) - Arc cosecant of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Relationships_among_the_inverse_trigonometric_functions`)
  long double acsc(long double const number, std::size_t const iterationCount, bool* const representable) {
    return asin(divide(1.0L, number, representable), iterationCount, representable);
  }

  // … → acsch(𝙭) → Area hyperbolic cosecant of 𝙭 (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Useful_relations`)
  long double acsch(long double const number, std::size_t const iterationCount, bool* const representable) {
    return asinh(divide(1.0L, number, representable), iterationCount, representable);
  }

  // … → add(𝙭, 𝙮) - Scalar addition of 𝙭 and 𝙮
  intmax_t add(intmax_t const numberA, intmax_t const numberB, bool* const representable) {
    if (representable and (sign(numberA) == sign(numberB) ? abs(numberA) > INTMAX_MAX - abs(numberB) : false)) {
      *representable = false;
      return 0;
    }

    return numberA + numberB;
  }

  long double add(long double const numberA, long double const numberB, bool* const representable) {
    if (representable and (sign(numberA) == sign(numberB) ? abs(numberA) > LDBL_MAX - abs(numberB) : false)) {
      *representable = false;
      return 0.0L;
    }

    return numberA + numberB;
  }

  uintmax_t add(uintmax_t const numberA, uintmax_t const numberB, bool* const representable) {
    if (representable and numberA > UINTMAX_MAX - numberB) {
      *representable = false;
      return 0u;
    }

    return numberA + numberB;
  }

  // … → asec(𝙭) - Arc secant of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Relationships_among_the_inverse_trigonometric_functions`)
  long double asec(long double const number, std::size_t const iterationCount, bool* const representable) {
    return acos(divide(1.0L, number, representable), iterationCount, representable);
  }

  // … → asech(𝙭) → Area hyperbolic secant of 𝙭 (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Useful_relations`)
  long double asech(long double const number, std::size_t const iterationCount, bool* const representable) {
    return acosh(divide(1.0L, number, representable), iterationCount, representable);
  }

  // … → asin(𝙭) - Arc sine of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Relationships_among_the_inverse_trigonometric_functions`)
  long double asin(long double const number, std::size_t const iterationCount, bool* const representable) {
    return atan(sqrt((1.0L + number) * (1.0L - number)), number, iterationCount, representable);
  }

  // … → asinh(𝙭) → Area hyperbolic sine of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions#Definitions_in_terms_of_logarithms`)
  long double asinh(long double const number, std::size_t const iterationCount, bool* const representable) {
    bool              subrepresentable = true;
    long double const ratio            = ipow(number, 2.0L, &subrepresentable);

    // …
    subrepresentable = subrepresentable and ratio > imaxof();

    if (not subrepresentable) {
      if (representable) *representable = false;
      if (iterationCount) return 0.0L;
    }

    return ln(number + sqrt(ratio + 1.0L, representable), iterationCount, representable);
  }

  // … → atan(𝙭) - Arc tangent of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Infinite_series`, `https://en.wikipedia.org/wiki/Atan2#Definition_and_computation`)
  long double atan(long double const number, std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double ratio = 0.0L; // → Adjacent ÷ Opposite

    // … → `Σₙ₌₀(2²ⁿ(n!)² ÷ (2n + 1)!)(𝙭²ⁿ⁺¹ ÷ (1 + 𝙭²)ⁿ⁺¹)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2][2]  = {{1.0L, 1.0L}, {1.0L, 1.0L}};
      long double preiteration     = ratio;
      bool        subrepresentable = index * 2.0L <= imaxof();

      // …
      iteration[0][0] = multiply  (ipow(2.0L, index * 2.0L, &subrepresentable), ipow(ifactorial(index, &subrepresentable), 2.0L, &subrepresentable), &subrepresentable);
      iteration[0][1] = ifactorial((index * 2.0L) + 1.0L,                                                                                            &subrepresentable);

      iteration[1][0] = ipow(number,                                       (index * 2.0L) + 1.0L, &subrepresentable);
      iteration[1][1] = ipow(ipow(number, 2.0L, &subrepresentable) + 1.0L, (index * 1.0L) + 1.0L, &subrepresentable);

      // …
      preiteration    += multiply(divide(iteration[0][0], iteration[0][1], &subrepresentable), divide(iteration[1][0], iteration[1][1], &subrepresentable), &subrepresentable);
      subrepresentable = subrepresentable and ratio != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      ratio = preiteration;
    }

    return ratio;
  }

  long double atan(long double const x, long double const y, std::size_t const iterationCount, bool* const representable) {
    // … → Adjacent ÷ Opposite
    switch (0.0L == x ? 0 : sign(x)) {
      case +1:
        return atan(y / x, iterationCount, representable);

      case -1: {
        bool              subrepresentable = true;
        long double const ratio            = atan(y / x, iterationCount, &subrepresentable);

        // …
        if (not iterationCount or subrepresentable)
        return ratio + (compute_pi(iterationCount) * sign(y, +1));
      } break;

      case 0:
        if (0.0L != y and sign(y))
        return 0.0L + (compute_eta(iterationCount) * sign(y, 0));
    }

    if (representable)
    *representable = false;

    return 0.0L;
  }

  // … → atanh(𝙭) → Area hyperbolic tangent of 𝙭 (`https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions#Conversions`)
  long double atanh(long double const number, std::size_t const iterationCount, bool* const representable) {
    return asinh(divide(number, sqrt(1.0L - ipow(number, 2.0L, representable), representable), representable), iterationCount, representable);
  }

  // … → bézier(𝙩, 𝙥0, …, 𝙥n) - Point 𝙩 on parametric multi-point curve, where all points lie between 0.0 and 1.0 (`https://en.wikipedia.org/wiki/Bézier_curve`)
  long double bézier(std::size_t const order, long double const percent, ...) {
    long double  point = 0.0L;
    std::va_list points;

    // …
    va_start(points, percent);

    for (std::size_t index = 0u; index <= order; ++index) {
      long double iteration = 1.0L;

      // … → `Σᵢ₌₀bᵢ,ₙ(𝙩)𝙋ᵢ where 0 ≤ 𝙩 ≤1`
      iteration *= ifactorial(static_cast<long double>(order)) / (ifactorial(static_cast<long double>(index)) * ifactorial(static_cast<long double>(order - index)));
      iteration *= ipow      (1.0L - percent, static_cast<long double>(order - index));
      iteration *= ipow      (percent,        static_cast<long double>(index));
      iteration *= va_arg    (points,         long double);

      point += iteration;
    }

    va_end(points);

    // …
    return point;
  }

  // … → bézier_cubic(𝙩, 𝙥0, 𝙥1, 𝙥2, 𝙥n) - Point 𝙩 on parametric 4-point curve i.e. bézier(3, 𝙩, 𝙥0, 𝙥1, 𝙥2, 𝙥n)
  long double bézier_cubic(long double const percent, long double const pointBegin, long double const midpointA, long double const midpointB, long double const pointEnd) {
    return (
      (pointBegin *                           ipow(1.0L - percent, 3.0L)) +
      (midpointA  * percent          * 3.0L * ipow(1.0L - percent, 2.0L)) +
      (midpointB  * (1.0L - percent) * 3.0L * ipow(percent,        2.0L)) +
      (pointEnd   *                           ipow(percent,        3.0L))
    );
  }

  // … → bézier_linear(𝙩, 𝙥0, 𝙥n) - Point 𝙩 on parametric 2-point curve (line) i.e. bézier(1, 𝙩, 𝙥0, 𝙥n)
  long double bézier_linear(long double const percent, long double const pointBegin, long double const pointEnd) {
    return (
      (pointBegin * ipow(1.0L - percent, 1.0L)) +
      (pointEnd   * ipow(percent,        1.0L))
    );
  }

  // … → bézier_quadratic(𝙩, 𝙥0, 𝙥1, 𝙥n) - Point 𝙩 on parametric 3-point curve i.e. bézier(2, 𝙩, 𝙥0, 𝙥1, 𝙥n)
  long double bézier_quadratic(long double const percent, long double const pointBegin, long double const midpoint, long double const pointEnd) {
    return (
      (pointBegin *                  ipow(1.0L - percent, 2.0L)) +
      (midpoint   * percent * 2.0L * ipow(1.0L - percent, 1.0L)) +
      (pointEnd   *                  ipow(percent,        2.0L))
    );
  }

  // … → bitceil(𝙭) - Next square of 𝙭
  intmax_t bitceil(intmax_t const number, bool* const representable) {
    intmax_t   ceiling    = sign(number, +1);
    bool const signedness = ceiling == +1;

    // …
    for (; signedness ? (ceiling < number) : (ceiling > number); ceiling <<= 1)
    if (signedness ? (ceiling > INTMAX_MAX >> 1) : (ceiling < INTMAX_MIN >> 1)) {
      if (representable) {
        *representable = false;
        return 0;
      }

      break;
    }

    return ceiling;
  }

  long double bitceil(long double number, bool* const representable) {
    long double       ceiling    = 1.0L;
    signed char const signedness = sign(number, +1);

    // …
    for (number = abs(number); ceiling < number; ceiling *= 2.0L)
    if (ceiling > LDBL_MAX / 2.0L) {
      if (representable) {
        *representable = false;
        return 0.0L;
      }

      break;
    }

    return ceiling * signedness;
  }

  uintmax_t bitceil(uintmax_t const number, bool* const representable) {
    uintmax_t ceiling = 1u;

    // …
    for (; ceiling < number; ceiling <<= 1u)
    if (ceiling > UINTMAX_MAX >> 1u) {
      if (representable) {
        *representable = false;
        return 0u;
      }

      break;
    }

    return ceiling;
  }

  // … → bitclear(𝙭, 𝙣) - Zeroed 𝙣th bit of 𝙭
  intmax_t bitclear(intmax_t const number, std::size_t const index) {
    return number & ~(1u << index);
  }

  long double bitclear(long double number, std::size_t const index) {
    unsigned char layout[sizeof(long double)];

    // …
    (*static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))))[index / CHAR_BIT] &= ~(1u << (index % CHAR_BIT));
    return *static_cast<long double*>(std::memcpy(&number, layout, sizeof(long double))); // → `number` or `*std::launder(…)`
  }

  uintmax_t bitclear(uintmax_t const number, std::size_t const index) {
    return number & ~(1u << index);
  }

  // … → bitflip(𝙭) - Toggled bits of 𝙭
  intmax_t bitflip(intmax_t const number) {
    return ~number;
  }

  long double bitflip(long double number) {
    unsigned char layout[sizeof(long double)];

    // …
    for (unsigned char *iterator = *static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))), *const end = iterator + sizeof(long double); end != iterator; ++iterator)
    *iterator = ~*iterator;

    return *static_cast<long double*>(std::memcpy(&number, layout, sizeof(long double))); // → `number` or `*std::launder(…)`
  }

  uintmax_t bitflip(uintmax_t const number) {
    return ~number;
  }

  // … → bitflip(𝙭, 𝙣) - Toggled 𝙣th bit of 𝙭
  intmax_t bitflip(intmax_t const number, std::size_t const index) {
    return number ^ (1u << index);
  }

  long double bitflip(long double number, std::size_t const index) {
    unsigned char layout[sizeof(long double)];

    // …
    (*static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))))[index / CHAR_BIT] ^= ~(1u << (index % CHAR_BIT));
    return *static_cast<long double*>(std::memcpy(&number, layout, sizeof(long double))); // → `number` or `*std::launder(…)`
  }

  uintmax_t bitflip(uintmax_t const number, std::size_t const index) {
    return number ^ (1u << index);
  }

  // … → bitfloor(𝙭) - Previous square of 𝙭
  intmax_t bitfloor(intmax_t const number, bool* const representable) {
    return static_cast<intmax_t>(bitfloor(static_cast<uintmax_t>(abs(number)), representable)) * sign(number, +1);
  }

  long double bitfloor(long double number, bool* const) {
    long double       floor      = 0.0L != number;
    signed char const signedness = sign(number, +1);

    // …
    for (number = abs(number) / 2.0L; floor < number; floor *= 2.0L)
    continue;

    return floor * signedness;
  }

  uintmax_t bitfloor(uintmax_t number, bool* const) {
    uintmax_t floor = 0u != number;

    // …
    for (number >>= 1u; floor < number; floor <<= 1u)
    continue;

    return floor;
  }

  // … → bitpopcount(𝙭) - Number of bits of 𝙭 set active to 1
  std::size_t bitpopcount(intmax_t number) {
    std::size_t count = 0u;

    // … → Two's complement representation standardized since C++11
    #if __cplusplus >= 201103L
      for (; number; number >>= 1)
      count += number & 1 ? 1u : 0u;
    #else
      for (unsigned char width = CHAR_BIT * sizeof number; width; --width, number >>= 1)
      count += number & 1 ? 1u : 0u;
    #endif

    return count;
  }

  std::size_t bitpopcount(long double number) {
    std::size_t   count = 0u;
    unsigned char layout[sizeof(long double)];

    // …
    for (unsigned char *iterator = *static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))), *const end = iterator + sizeof(long double); end != iterator; ++iterator) {
      for (; *iterator; *iterator >>= 1u)
      count += *iterator & 1u ? 1u : 0u;
    }

    return count;
  }

  std::size_t bitpopcount(uintmax_t number) {
    std::size_t count = 0u;

    // … → Assumed representation is base -2, offset binary, one's complement, sign–magnitude, or two's complement
    for (; number; number >>= 1u)
    count += number & 1u ? 1u : 0u;

    return count;
  }

  // … → bitset(𝙭, 𝙣) - Zeroed 𝙣th bit of 𝙭
  intmax_t bitset(intmax_t const number, std::size_t const index) {
    return number | (1u << index);
  }

  long double bitset(long double number, std::size_t const index) {
    unsigned char layout[sizeof(long double)];

    // …
    (*static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))))[index / CHAR_BIT] |= 1u << (index % CHAR_BIT);
    return *static_cast<long double*>(std::memcpy(&number, layout, sizeof(long double))); // → `number` or `*std::launder(…)`
  }

  uintmax_t bitset(uintmax_t const number, std::size_t const index) {
    return number | (1u << index);
  }

  // intmax_t    bitrotleft   (intmax_t,    std::size_t = 1u);
  // long double bitrotleft   (long double, std::size_t = 1u);
  // uintmax_t   bitrotleft   (uintmax_t,   std::size_t = 1u);
  // intmax_t    bitrotright  (intmax_t,    std::size_t = 1u);
  // long double bitrotright  (long double, std::size_t = 1u);

  // … → bitrotright(𝙭, 𝙣) - Rightward bitwise rotation of 𝙭
  intmax_t bitrotright(intmax_t const number, std::size_t const count) {
    return bitshiftright(number) | ((number & maxwidthof(count)) << ((CHAR_BIT * sizeof(intmax_t)) - count));
  }

  long double bitrotright(long double number, std::size_t const count) {
    unsigned char layout[sizeof(long double)];

    // …
    (void) layout;
    (void) number;
    (void) count;
    return 0.0L;
    // layout[count / CHAR_BIT]
    // std::memcpy(std::memcpy(layout, &static_cast<long double const&>(bitshiftright(number, count)), sizeof(long double)), )
  }

  uintmax_t bitrotright(uintmax_t const number, std::size_t const count) {
    return bitshiftright(number) | ((number & maxwidthof(count)) << ((CHAR_BIT * sizeof(uintmax_t)) - count));
  }

  // … → bitshiftleft(𝙭, 𝙣) - Leftward bitwise shift of 𝙭
  intmax_t bitshiftleft(intmax_t const number, std::size_t const count) {
    return number << count;
  }

  long double bitshiftleft(long double number, std::size_t const count) {
    unsigned char     layout[sizeof(long double)];
    std::size_t const offset    = count / CHAR_BIT;
    std::size_t const suboffset = count % CHAR_BIT;

    // …
    if (count >= CHAR_BIT * sizeof(long double))
    return 0.0L;

    for (unsigned char *iterators[2] = {
      *static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))),
      static_cast<unsigned char*>(std::memset(static_cast<unsigned char*>(std::memmove(*iterators, *iterators + offset, sizeof(long double) - offset)) + (sizeof(long double) - offset), 0x00u, offset)) - (sizeof(long double) - offset)
    }; ; ) {
      *(iterators[1]++) <<= suboffset;

      if (iterators[1] == iterators[0] + sizeof(long double))
      break;

      *(iterators[1] + 0) |= *(iterators[1] + 1) & (maxwidthof(suboffset) << (CHAR_BIT - suboffset));
    }

    return *static_cast<long double*>(std::memcpy(&number, layout, sizeof(long double))); // → `number` or `*std::launder(…)`
  }

  uintmax_t bitshiftleft(uintmax_t const number, std::size_t const count) {
    return number << count;
  }

  // … → bitshiftright(𝙭, 𝙣) - Rightward bitwise shift of 𝙭
  intmax_t bitshiftright(intmax_t const number, std::size_t const count) {
    return number >> count;
  }

  long double bitshiftright(long double number, std::size_t const count) {
    unsigned char     layout[sizeof(long double)];
    std::size_t const offset    = count / CHAR_BIT;
    std::size_t const suboffset = count % CHAR_BIT;

    // …
    if (count >= CHAR_BIT * sizeof(long double))
    return 0.0L;

    for (unsigned char *iterators[2] = {
      *static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))),
      static_cast<unsigned char*>(std::memset(static_cast<unsigned char*>(std::memmove(*iterators + offset, *iterators, sizeof(long double) - offset)) - offset, 0x00u, offset)) + sizeof(long double)
    }; ; ) {
      *--iterators[1] >>= suboffset;

      if (iterators[1] == iterators[0])
      break;

      *(iterators[1] - 0) |= (*(iterators[1] - 1) & maxwidthof(CHAR_BIT - suboffset)) << (CHAR_BIT - suboffset);
    }

    return *static_cast<long double*>(std::memcpy(&number, layout, sizeof(long double))); // → `number` or `*std::launder(…)`
  }

  uintmax_t bitshiftright(uintmax_t const number, std::size_t const count) {
    return number >> count;
  }

  // … → bitswap(𝙭) - Reversed bits of 𝙭
  intmax_t bitswap(intmax_t number) {
    intmax_t swapped = 0;

    // …
    for (std::size_t width = CHAR_BIT * sizeof(intmax_t); width--; number >>= 1u)
    swapped = (number & 1u) | (swapped << 1u);

    return swapped;
  }

  long double bitswap(long double number) {
    unsigned char layout[sizeof(long double)];

    // …
    for (unsigned char *iterators[2] = {
      *static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))),
      *iterators + (sizeof(long double) - 1u)
    }; iterators[0] <= iterators[1]; ++iterators[0], iterators[1] -= layout != iterators[1]) {
      unsigned char swapped[2] = {0x00u, 0x00u};

      // …
      for (unsigned char index = 2u - (iterators[0] == iterators[1]); index-- != 0u; ) {
        for (unsigned char width = CHAR_BIT; width--; *(iterators[index]) >>= 1u)
        swapped[2u - index - 1u] = (*(iterators[index]) & 1u) | (swapped[2u - index - 1u] << 1u);
      }

      for (unsigned char index = 0u + (iterators[0] == iterators[1]); index != 2u; ++index)
      *(iterators[index]) = swapped[index];
    }

    return *static_cast<long double*>(std::memcpy(&number, layout, sizeof(long double))); // → `number` or `*std::launder(…)`
  }

  uintmax_t bitswap(uintmax_t number) {
    uintmax_t swapped = 0u;

    // …
    for (std::size_t width = CHAR_BIT * sizeof(uintmax_t); width--; number >>= 1u)
    swapped = (number & 1u) | (swapped << 1u);

    return swapped;
  }

  // … → bitwidth(𝙭) - Number of complete representational bits of 𝙭 (remiss to parse the versions for `intmax_t` and `long double`)
  std::size_t bitwidth(uintmax_t number) {
    std::size_t count = 0u;

    // …
    for (; number; number >>= 1u)
    ++count;

    return count;
  }

  // … → cbrt(𝙭) - Cubed root of 𝙭
  intmax_t cbrt(intmax_t const number, bool* const representable) {
    return root(number, 3, representable);
  }

  long double cbrt(long double const number, bool* const representable) {
    return root(number, 3.0L, representable);
  }

  uintmax_t cbrt(uintmax_t const number, bool* const representable) {
    return root(number, 3u, representable);
  }

  // … → ceil(𝙭) - Rounded-up value of 𝙭
  long double ceil(long double const number) {
    long double const truncation = trunc(number);
    return truncation + (number > truncation);
  }

  // … → clamp(𝙭, 𝙖, 𝙗) - Constrained value of 𝙭 between an 𝙖–𝙗 number line
  intmax_t clamp(intmax_t const number, intmax_t const begin, intmax_t const end) {
    return number < begin ? begin : number > end ? end : number;
  }

  long double clamp(long double const number, long double const begin, long double const end) {
    return number <= begin ? begin : number >= end ? end : number;
  }

  uintmax_t clamp(uintmax_t const number, uintmax_t const begin, uintmax_t const end) {
    return number < begin ? begin : number > end ? end : number;
  }

  // … → clerp(𝙩, 𝙖, 𝙗) - Circular linearly-interpolated value 𝙩 between 𝙖 and 𝙗
  _<long double[2]> clerp(long double const percent, long double const (&begin)[2], long double const (&end)[2]) {
    long double       const size    []    = {(end[0] / 2.0L) - (begin[0] / 2.0L), (end[1] / 2.0L) - (begin[1] / 2.0L)};
    long double       const midpoint[]    = {(end[0] / 2.0L) + (begin[0] / 2.0L), (end[1] / 2.0L) + (begin[1] / 2.0L)};
    long double       const angle   []    = {atan(begin[0] - midpoint[0], begin[1] - midpoint[1]), atan(end[0] - midpoint[0], end[1] - midpoint[1])};
    long double       const interpolation = angle[0] + (percent * (angle[1] - angle[0]));
    _<long double[2]> const value         = {midpoint[0] + (size[0] * cos(interpolation)), midpoint[1] + (size[1] * sin(interpolation))};

    return value;
  }

  // … → compute_eta(…)
  long double compute_eta(std::size_t const iterationCount, bool* const representable) {
    return compute_pi(iterationCount, representable) / 2.00L;
  }

  // … → compute_euler(…) - Napier's constant (`https://en.wikipedia.org/wiki/E_(mathematical_constant)`)
  long double compute_euler(std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double euler = 0.0L;

    // … → `Σₙ₌₀(1 ÷ n!)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = euler;
      bool        subrepresentable = true;

      // …
      iteration[1] = ifactorial(index, &subrepresentable);

      // …
      preiteration    += divide(iteration[0], iteration[1], &subrepresentable);
      subrepresentable = subrepresentable and euler != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      euler = preiteration;
    }

    return euler;
  }

  // … → compute_infinity() - Infinity floating-point representative
  long double compute_infinity() {
    return 1.0L / 0.0L;
  }

  // … → compute_nan() - Non-numeral floating-point representative i.e. NaN
  long double compute_nan() {
    if (SUPPORTS_IEEE754_FLOAT) {
      unsigned char layout[sizeof(long double)];
      long double   nan = 0.0L;

      return *static_cast<long double*>(std::memcpy(&nan, std::memset(layout, UCHAR_MAX, sizeof(long double)), sizeof(long double))); // → `nan` or `*std::launder(…)`
    }

    // … → Attempt to avoid a signaling NaN
    long double const volatile zero = 0.0L;
    return zero / zero;
  }

  // … → compute_pi(…) - Archimedes' constant (`https://en.wikipedia.org/wiki/Chudnovsky_algorithm`, or alternatively `https://en.wikipedia.org/wiki/Ramanujan–Sato_series` for a different formula)
  long double compute_pi(std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double pi    = 0.0L;

    // … → `Σₖ₌₀((-1)ᵏ(6k)!(545140134k + 13591409) ÷ (3k)!(k!)³(640320)³ᵏ⁺³ᐟ²)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = pi;
      bool        subrepresentable = true;

      // …
      iteration[0] *= ifactorial(index * 6.0L,        &subrepresentable);
      iteration[0] *= ipow      (-1.0L,        index, &subrepresentable);
      iteration[0] *= multiply  (545140134.0L, index, &subrepresentable) + 13591409.0L;

      iteration[1] *= ifactorial(index * 3.0L,                                                       &subrepresentable);
      iteration[1] *= ipow      (ifactorial(index, &subrepresentable), 3.0L,                         &subrepresentable);
      iteration[1] *= multiply  (512384047.996L /* → `640320³ᐟ²` */,   ipow(640320.0L, index * 3.0L, &subrepresentable) /* → `640320³ᵏ` */); // → j-function of negated Heegner number

      // …
      preiteration    += divide(iteration[0], iteration[1], &subrepresentable);
      subrepresentable = subrepresentable and pi != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      pi = preiteration;
    }

    return 1.0L / (pi * 12.0L);
  }

  // … → compute_tau(…) - Circle constant
  long double compute_tau(std::size_t const iterationCount, bool* const representable) {
    return compute_pi(iterationCount, representable) * 2.00L;
  }

  // … → cos(𝙭) - Cosine of 𝙭 radians (`https://en.wikipedia.org/wiki/Sine_and_cosine`)
  long double cos(long double const angle, std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double ratio = 0.0L; // → Adjacent ÷ Hypotenuse

    // … → `Σₙ₌₀((-1)ⁿ(𝙭²ⁿ) ÷ (2n)!)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = ratio;
      bool        subrepresentable = true;

      // …
      iteration[0] = ipow(-1.0L, index) * ipow(angle, index * 2.0L, &subrepresentable);
      iteration[1] = ifactorial(index * 2.0L, &subrepresentable);

      // …
      preiteration    += divide(iteration[0], iteration[1], &subrepresentable);
      subrepresentable = subrepresentable and ratio != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      ratio = preiteration;
    }

    return ratio;
  }

  // … → cosh(𝙭) - Hyperbolic cosine of 𝙭 radians (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Taylor_series_expressions`)
  long double cosh(long double const angle, std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double ratio = 0.0L; // → Opposite ÷ Hypotenuse

    // … → `Σₙ₌₀(𝙭²ⁿ ÷ (2n)!)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = ratio;
      bool        subrepresentable = true;

      // …
      iteration[0] = ipow(angle, index * 2.0L, &subrepresentable);
      iteration[1] = ifactorial(index * 2.0L, &subrepresentable);

      // …
      preiteration    += divide(iteration[0], iteration[1], &subrepresentable);
      subrepresentable = subrepresentable and ratio != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      ratio = preiteration;
    }

    return ratio;
  }

  // … → cot(𝙭) - Cotangent of 𝙭 radians (`https://en.wikipedia.org/wiki/Trigonometric_functions`)
  long double cot(long double const angle, std::size_t const iterationCount, bool* const representable) {
    return divide(1.0L, tan(angle, iterationCount, representable), representable);
  }

  // … → coth(𝙭) - Hyperbolic cotangent of 𝙭 radians (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Exponential_definitions`)
  long double coth(long double const angle, std::size_t const iterationCount, bool* const representable) {
    return divide(1.0L, tanh(angle, iterationCount, representable), representable);
  }

  // … → countof(𝙭) - Number of denary digits representing 𝙭
  std::size_t countof(intmax_t const number) {
    return countof(static_cast<uintmax_t>(abs(number)));
  }

  std::size_t countof(long double const number) {
    long double characteristics = trunc(number);          //
    std::size_t count           = 0u;                     // → Number of significant digits
    long double mantissa        = number - trunc(number); //
    std::size_t subcount        = 0u;                     // → Number of significant/ trailing zero digits

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

  // … → csc(𝙭) - Cosecant of 𝙭 radians (`https://en.wikipedia.org/wiki/Cosecant_(trigonometry)`)
  long double csc(long double const angle, std::size_t const iterationCount, bool* const representable) {
    return divide(1.0L, sin(angle, iterationCount, representable), representable);
  }

  // … → csch(𝙭) - Hyperbolic cosecant of 𝙭 radians (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Exponential_definitions`)
  long double csch(long double const angle, std::size_t const iterationCount, bool* const representable) {
    return divide(1.0L, sinh(angle, iterationCount, representable), representable);
  }

  // … → divide(𝙭, 𝙮) - Scalar division of 𝙭 and 𝙮
  intmax_t divide(intmax_t const numberA, intmax_t const numberB, bool* const representable) {
    if (0 == numberB) {
      *representable = false;
      return 0;
    }

    return numberA / numberB;
  }

  long double divide(long double const numberA, long double const numberB, bool* const representable) {
    if (0.0L == numberB) {
      if (representable)
      *representable = false;

      return 0.0L;
    }

    return numberA / numberB;
  }

  uintmax_t divide(uintmax_t const numberA, uintmax_t const numberB, bool* const representable) {
    if (0u == numberB) {
      *representable = false;
      return 0u;
    }

    return numberA / numberB;
  }

  // … → ease(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.25, 0.10, 0.25, 1.00)
  long double ease(long double const time) {
    return bézier_cubic(time, 0.25L, 0.10L, 0.25L, 1.00L);
  }

  // … → ease_in(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.42, 0.00, 1.00, 1.00)
  long double ease_in(long double const time) {
    return bézier_cubic(time, 0.42L, 0.00L, 1.00L, 1.00L);
  }

  // … → ease_in_back(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.36, 0.00, 0.66, -0.56)
  long double ease_in_back(long double const time) {
    return (ipow(time, 3.00000L) * 2.70158L) - (ipow(time, 2.00000L) * 1.70158L);
  }

  // … → ease_in_bounce(𝙩) - Easing animation function at relative time 𝙩
  long double ease_in_bounce(long double const time) {
    return 1.0L - ease_out_bounce(1.0L - time);
  }

  // … → ease_in_circular(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.55, 0.00, 1.00, 0.45)
  long double ease_in_circular(long double const time) {
    return 1.0L - sqrt(1.0L - ipow(time, 2.0L));
  }

  // … → ease_in_cubic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.32, 0.00, 0.67, 0.00)
  long double ease_in_cubic(long double const time) {
    return ipow(time, 3.0L);
  }

  // … → ease_in_elastic(𝙩) - Easing animation function at relative time 𝙩
  long double ease_in_elastic(long double const time) {
    return 0.00L != time and time != 1.00L ? -pow(2.00L, (time * 10.00L) - 10.00L) * sin(((time * 10.00L) - 10.75L) * (compute_tau() / 3.00L)) : time;
  }

  // … → ease_in_exponential(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.70, 0.00, 0.84, 0.00)
  long double ease_in_exponential(long double const time) {
    return 0.0L != time ? pow(2.0L, (time * 10.0L) - 10.0L) : 0.0L;
  }

  // … → ease_in_quadratic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.11, 0.00, 0.50, 0.00)
  long double ease_in_quadratic(long double const time) {
    return ipow(time, 2.0L);
  }

  // … → ease_in_quartic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.50, 0.00, 0.75, 0.00)
  long double ease_in_quartic(long double const time) {
    return ipow(time, 4.0L);
  }

  // … → ease_in_quintic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.64, 0.00, 0.78, 0.00)
  long double ease_in_quintic(long double const time) {
    return ipow(time, 5.0L);
  }

  // … → ease_in_sine(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.12, 0.00, 0.39, 0.00)
  long double ease_in_sine(long double const time) {
    return 1.0L - cos((compute_pi() * time) / 2.0L);
  }

  // … → ease_in_out(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.42, 0.00, 0.58, 1.00)
  long double ease_in_out(long double const time) {
    return bézier_cubic(time, 0.42L, 0.00L, 0.58L, 1.00L);
  }

  // … → ease_in_out_back(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.68, -0.60, 0.32, 1.60)
  long double ease_in_out_back(long double const time) {
    return (time < 0.5000000L ? ipow(time * 2.00000000L, 2.0000000L) * ((time * 7.1898190L) - 2.5949095L) : ((ipow((time * 2.0000000L) - 2.0000000L, 2.0000000L) * ((((time * 2.0000000L) - 2.0000000L) * 3.5949095L) + 2.5949095L)) + 2.0000000L)) / 2.0000000L;
  }

  // … → ease_in_out_bounce(𝙩) - Easing animation function at relative time 𝙩
  long double ease_in_out_bounce(long double const time) {
    return (time < 0.5L ? 1.0L - ease_out_bounce(1.0L - (time * 2.0L)) : (1.0L + ease_out_bounce((time * 2.0L) - 1.0L))) / 2.0L;
  }

  // … → ease_in_out_circular(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.85, 0.00, 0.15, 1.00)
  long double ease_in_out_circular(long double const time) {
    return (time < 0.5L ? 1.0L - sqrt(1.0L - ipow(time * 2.0L, 2.0L)) : (1.0L + sqrt(1.0L - ipow((time * -2.0L) + 2.0L, 2.0L)))) / 2.0L;
  }

  // … → ease_in_out_cubic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.65, 0.00, 0.35, 1.00)
  long double ease_in_out_cubic(long double const time) {
    return time < 0.5L ? ipow(time, 3.0L) * 4.0L : (1.0L - (ipow((time * -2.0L) + 2.0L, 3.0L) / 2.0L));
  }

  // … → ease_in_out_elastic(𝙩) - Easing animation function at relative time 𝙩
  long double ease_in_out_elastic(long double const time) {
    return 0.000L != time and time != 1.000L ? time < 0.500L ? -(pow(2.000L, (time * 20.000L) - 10.000L) * sin(((time * 20.000L) - 11.125L) * (compute_tau() / 4.500L))) / 2.000L : ((pow(2.000L, (time * -20.000L) + 10.000L) * sin(((time * 20.000L) - 11.125L) * (compute_tau() / 4.500L))) / 2.000L + 1.000L) : time;
  }

  // … → ease_in_out_exponential(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.87, 0.00, 0.13, 1.00)
  long double ease_in_out_exponential(long double const time) {
    return 0.0L != time and time != 1.0L ? (time < 0.5L ? pow(2.0L, (time * 20.0L) - 10.0L) : (2.0L - pow(2.0L, (time * -20.0L) + 10.0L))) / 2.0L : time;
  }

  // … → ease_in_out_quadratic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.45, 0.00, 0.55, 1.00)
  long double ease_in_out_quadratic(long double const time) {
    return time < 0.5L ? ipow(time, 2.0L) * 2.0L : (1.0L - (ipow((time * -2.0L) + 2.0L, 2.0L) / 2.0L));
  }

  // … → ease_in_out_quartic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.76, 0.00, 0.24, 1.00)
  long double ease_in_out_quartic(long double const time) {
    return time < 0.5L ? ipow(time, 4.0L) * 8.0L : (1.0L - (ipow((time * -2.0L) + 2.0L, 4.0L) / 2.0L));
  }

  // … → ease_in_out_quintic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.83, 0.00, 0.17, 1.00)
  long double ease_in_out_quintic(long double const time) {
    return time < 0.5L ? ipow(time, 5.0L) * 16.0L : (1.0L - (ipow((time * -2.0L) + 2.0L, 5.0L) / 2.0L));
  }

  // … → ease_in_out_sine(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.37, 0.00, 0.63, 1.00)
  long double ease_in_out_sine(long double const time) {
    return -(cos(compute_pi() * time) - 1.0L) / 2.0L;
  }

  // … → ease_out(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.00, 0.00, 0.58, 1.00)
  long double ease_out(long double const time) {
    return bézier_cubic(time, 0.00L, 0.00L, 0.58L, 1.00L);
  }

  // … → ease_out_back(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.34, 1.56, 0.64, 1.00)
  long double ease_out_back(long double const time) {
    return 1.00000L + (2.70158L * ipow(time - 1.00000L, 3.00000L)) + (1.70158L * ipow(time - 1.00000L, 2.00000L));
  }

  // … → ease_out_bounce(𝙩) - Easing animation function at relative time 𝙩
  long double ease_out_bounce(long double const time) {
    return time < 1.000000L / 2.750000L ? 7.562500L * pow(time, 2.000000L) : time < 2.000000L / 2.750000L ? (7.562500L * ipow(time - (1.500000L / 2.750000L), 2.000000L)) + 0.750000L : time < 2.500000L / 2.750000L ? (7.562500L * ipow(time - (2.250000L / 2.750000L), 2.000000L)) + 0.937500L : (7.562500L * ipow(time - (2.625000L / 2.750000L), 2.000000L)) + 0.984375L;
  }

  // … → ease_out_circular(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.00, 0.55, 0.45, 1.00)
  long double ease_out_circular(long double const time) {
    return sqrt(1.0L - ipow(time - 1.0L, 2.0L));
  }

  // … → ease_out_cubic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.33, 1.00, 0.68, 1.00)
  long double ease_out_cubic(long double const time) {
    return 1.0L - ipow(1.0L - time, 3.0L);
  }

  // … → ease_out_elastic(𝙩) - Easing animation function at relative time 𝙩
  long double ease_out_elastic(long double const time) {
    return 0.00L != time and time != 1.00L ? (pow(2.00L, time * -10.00L) * sin(((time * 10.00L) - 0.75L) * (compute_tau() / 3.00L))) + 1.00L : time;
  }

  // … → ease_out_exponential(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.16, 1.00, 0.30, 1.00)
  long double ease_out_exponential(long double const time) {
    return time != 1.0L ? 1.0L - pow(2.0L, time * -10.0L) : 1.0L;
  }

  // … → ease_out_quadratic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.50, 1.00, 0.89, 1.00)
  long double ease_out_quadratic(long double const time) {
    return 1.0L - ipow(1.0L - time, 2.0L);
  }

  // … → ease_out_quartic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.25, 1.00, 0.5, 1.00)
  long double ease_out_quartic(long double const time) {
    return 1.0L - ipow(1.0L - time, 4.0L);
  }

  // … → ease_out_quintic(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.22, 1.00, 0.36, 1.00)
  long double ease_out_quintic(long double const time) {
    return 1.0L - ipow(1.0L - time, 5.0L);
  }

  // … → ease_out_sine(𝙩) - Easing animation function at relative time 𝙩 i.e. bézier_cubic(𝙩, 0.61, 1.00, 0.88, 1.00)
  long double ease_out_sine(long double const time) {
    return sin((compute_pi() * time) / 2.0L);
  }

  // … → exp(𝙭) - 𝙭th power of Euler’s number
  long double exp(long double const number, std::size_t const iterationCount, bool* const representable) {
    return pow(compute_euler(iterationCount, representable), number, representable);
  }

  // … → floor(𝙭) - Rounded-down value of 𝙭
  long double floor(long double const number) {
    long double const truncation = trunc(number);
    return truncation - (number <= truncation);
  }

  // … → fract(𝙭) - Split value of 𝙭 as its numerator and denominator
  _<long double[2]> fract(long double const number) {
    long double const characteristics = trunc(number);
    long double       denominator     = 1.0L;
    long double const mantissa        = number - characteristics;
    long double       numerator       = characteristics;

    // …
    if (0.0L != mantissa) {
      long double       divisor   = 1.0L;
      long double const precision = ipow(10.0L, static_cast<long double>(LDBL_MAX_10_EXP));

      // …
      for (long double term[2] = {precision, round(precision * mantissa)}; 0.0L != term[0] and 0.0L != term[1]; ) {
        term[term[0] < term[1]] = remainder(term[term[0] < term[1]], term[term[0] >= term[1]]); // → `term[term[0] < term[1]] %= term[term[0] >= term[1]]`
        divisor                 = term[0.0L == term[0]];
      }

      denominator = precision / divisor;
      numerator   = round(denominator * mantissa) + (denominator * characteristics);
    }

    _<long double[2]> const fraction = {numerator, denominator};
    return fraction;
  }

  // … → gcd(𝙭, 𝙮) - Greatest common divisor of 𝙭 and 𝙮 (`https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations`)
  intmax_t gcd(intmax_t integerA, intmax_t integerB) {
    while (integerB) {
      intmax_t const value = integerB;

      // …
      integerB = modulus(integerA, integerB);
      integerA = value;
    }

    return integerA;
  }

  long double gcd(long double integerA, long double integerB) {
    while (integerB) {
      long double const value = integerB;

      // …
      integerB = modulus(integerA, integerB);
      integerA = value;
    }

    return integerA;
  }

  uintmax_t gcd(uintmax_t integerA, uintmax_t integerB) {
    while (integerB) {
      uintmax_t const value = integerB;

      // …
      integerB = modulus(integerA, integerB);
      integerA = value;
    }

    return integerA;
  }

  // … → icbrt(𝙭) - Integer cubed root of 𝙭
  intmax_t icbrt(intmax_t const number, bool* const representable) {
    return root(number, 3, representable);
  }

  long double icbrt(long double const number, bool* const representable) {
    return root(number, 3.0L, representable);
  }

  uintmax_t icbrt(uintmax_t const number, bool* const representable) {
    return root(number, 3u, representable);
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

  // … → imaxof() - Maximum integer value of floating-point type with complete integer precision i.e. maxprecof(1)
  long double imaxof() {
    long double maximum = 1.0L;

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
    uintmax_t      power      = 1u;
    intmax_t const signedness = parity(exponent) and sign(base) == -1 ? -1 : +1;

    // …
    if (representable and (0 == base and sign(exponent) == -1)) {
      *representable = false;
      return 0;
    }

    power = ipow(static_cast<uintmax_t>(abs(base)), static_cast<uintmax_t>(abs(exponent)), representable);

    if (power > abs(signedness ? INTMAX_MIN : INTMAX_MAX)) {
      if (representable)
      *representable = false;

      return 0;
    }

    return static_cast<intmax_t>(power) * signedness;
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

        if (power > LDBL_MAX / multiplier) {
          if (representable)
          *representable = false;

          return 0.0L;
        }

        exponent -= count;
        power    *= multiplier * (count == 1.0L and sign(base, +1) != -1 ? +1.0L : -1.0L);
      }
    }

    return inverse ? 1.0L / power : power;
  }

  uintmax_t ipow(uintmax_t const base, uintmax_t exponent, bool* const representable) {
    uintmax_t multiplier = base;
    uintmax_t power      = 1u;

    // …
    while (exponent) {
      if (exponent % 2u) {
        if (power > UINTMAX_MAX / multiplier) {
          if (representable)
          *representable = false;

          return 0u;
        }

        power *= multiplier;
      }

      exponent   /= 2u;
      multiplier *= multiplier;
    }

    return power;
  }

  // … → ipow(𝙭, 𝙣) - Integer 𝙣th root of 𝙭
  uintmax_t iroot(intmax_t const base, intmax_t const exponent, bool* const representable) {
    uintmax_t root = 0u;

    // …
    if (0 == exponent or sign(base) == -1) {
      if (representable)
      *representable = false;

      return 0;
    }

    root = iroot(static_cast<uintmax_t>(abs(base)), static_cast<uintmax_t>(abs(exponent)), representable);

    return root and sign(exponent) == -1 ? 1u / root : root;
  }

  long double iroot(long double const base, long double exponent, bool* const representable) {
    bool const  inverse = exponent and sign(exponent) == -1;
    long double root    = 0.0L;

    // …
    if (0.0L == base)
    return 0.0L;

    if (0.0L == exponent or sign(base) == -1) {
      if (representable)
      *representable = false;

      return 0.0L;
    }

    exponent = abs(exponent);

    for (long double next = 1.0L; ; next = root) {
      root = ((next * (exponent - 1.0L)) + (base / ipow(next, exponent - 1.0L))) / exponent;

      if (LDBL_EPSILON >= abs(root - next))
      break;
    }

    return inverse ? 1.0L / root : root;
  }

  uintmax_t iroot(uintmax_t const base, uintmax_t const exponent, bool* const representable) {
    uintmax_t root = 0u;

    // …
    if (0u == exponent) {
      if (representable)
      *representable = false;

      return 0u;
    }

    for (uintmax_t next = 1u; ; next = root) {
      root = ((next * (exponent - 1u)) + (base / ipow(next, exponent - 1u))) / exponent;

      if (0u == root - next)
      break;
    }

    return root;
  }

  // … → isqrt(𝙭) - Integer squared root of 𝙭
  intmax_t isqrt(intmax_t const number, bool* const representable) {
    return root(number, 3, representable);
  }

  long double isqrt(long double const number, bool* const representable) {
    return root(number, 3.0L, representable);
  }

  uintmax_t isqrt(uintmax_t const number, bool* const representable) {
    return root(number, 3u, representable);
  }

  // … → is_denormal(𝙭) - Determines if 𝙭 is a denormalized floating-point value
  bool is_denormal(long double const number) {
    // → All subnormals are denormals, but not all denormals are subnormals
    return is_subnormal(number) or false;
  }

  // … → is_infinite(𝙭) - Determines if 𝙭 is a negative/ positive infinity floating-point value
  bool is_infinite(long double const number) {
    return number and number == (number + 0.0L) * (number + 1.0L);
  }

  // … → is_integer(𝙭) - Determines if 𝙭 is an integer value
  bool is_integer(long double const number) {
    return number == trunc(number);
  }

  // … → is_nan(𝙭) - Determines if 𝙭 is a NaN floating-point value
  bool is_nan(long double const number) {
    return number != number;
  }

  // … → is_subnormal(𝙭) - Determines if 𝙭 is a subnormal floating-point value
  bool is_subnormal(long double const number) {
    #ifdef LDBL_HAS_SUBNORM
    # if LDBL_HAS_SUBNORM+0 == 1
      return not is_nan(number) and number < LDBL_MIN;
    # endif
    #endif

    (void) number;
    return false;
  }

  // … → jsf(𝙭) - Jenkins' Small Fast pseudo-random number generator with seed 𝙭 (FLEA++ or Fast Little Encryption Algorithm, `http://burtleburtle.net/bob/rand/smallprng.html`)
  _<uintmax_t[4]> jsf(std::size_t const width, uintmax_t const (&seeded)[4]) {
    switch (width) {
      case 8u : return jsf(width, seeded, 1u,  4u,  0u);  //
      case 16u: return jsf(width, seeded, 13u, 8u,  0u);  //
      case 32u: return jsf(width, seeded, 27u, 17u, 0u);  // → (3u,  14u, 24u), (3u, 25u, 15u), (4u, 15u, 24u), (6u, 16u, 28u), (7u, 16u, 27u), (8u, 14u, 3u), (9u, 16u, 0u), (9u, 24u, 0u), (10u, 16u, 0u), (10u, 24u, 0u), (11u, 16u, 0u), (11u, 16u, 23u), (11u, 24u, 0u), (12u, 16u, 22u), (12u, 17u, 23u), (13u, 16u, 22u), (15u, 25u, 3u), (16u, 9u, 3u), (17u, 27u, 7u), (17u, 9u, 3u), (19u, 7u, 3u), (23u, 15u, 11u), (23u, 16u, 11u), (23u, 17u, 11u), (24u, 3u, 16u), (24u, 4u, 16u), (25u, 14u, 3u), (25u, 16u, 0u), (25u, 8u, 0u), (26u, 16u, 0u), (26u, 17u, 0u), (26u, 8u, 0u), (27u, 16u, 0u), (27u, 16u, 6u), (27u, 16u, 7u)
      case 64u: return jsf(width, seeded, 7u,  13u, 37u); // → (39u, 11u, 0u)
    }

    _<uintmax_t[4]> const state = {};
    return state;
  }

  _<uintmax_t[4]> jsf(std::size_t const width, uintmax_t const (&seeded)[4], std::size_t const shiftA, std::size_t const shiftB, std::size_t const shiftC) {
    uintmax_t  const value = seeded[0] - ((seeded[1] << shiftA) | (seeded[1] >> (width - shiftA)));
    _<uintmax_t[4]> const state = {
      seeded [1] ^ ((seeded[2] << shiftB) | (seeded[2] >> (width - shiftB))),
      seeded [2] + ((seeded[3] << shiftC) | (seeded[3] >> (width - shiftC))),
      seeded [3] + value,
      state._[0] + value
    };

    return state;
  }

  _<uintmax_t[4]> jsf(std::size_t const width, uintmax_t const seed) {
    uintmax_t const mask        = maxwidthof(width);
    uintmax_t       substate[4] = {0xF1EA5EEDu, seed, seed, seed};

    // …
    for (unsigned char index = 0u; index != 4u; ++index)
    substate[index] &= mask; // → `uint16_t seed` and `0x5EEDu` constant for `width == 16u`

    for (unsigned char count = 0u; count != 20u; ++count) {
      uintmax_t const (&next)[4] = jsf(width, substate);

      substate[0] = next[0];
      substate[1] = next[1];
      substate[2] = next[2];
      substate[3] = next[3];
    }

    // …
    _<uintmax_t[4]> const state = {substate[0], substate[1], substate[2], substate[3]};
    return state;
  }

  // … → lcm(𝙭, 𝙮) - Least common multiple of 𝙭 and 𝙮 (`https://en.wikipedia.org/wiki/Least_common_multiple#Calculation`)
  intmax_t lcm(intmax_t const integerA, intmax_t const integerB) {
    return integerA + integerB ? min(static_cast<uintmax_t>(abs(integerA)), static_cast<uintmax_t>(abs(integerB))) * (max(static_cast<uintmax_t>(abs(integerA)), static_cast<uintmax_t>(abs(integerB))) / gcd(integerA, integerB)) : 0;
  }

  long double lcm(long double const integerA, long double const integerB) {
    return integerA + integerB ? abs(integerA) * (abs(integerB) / gcd(integerA, integerB)) : 0.0L;
  }

  uintmax_t lcm(uintmax_t const integerA, uintmax_t const integerB) {
    return integerA + integerB ? min(integerA, integerB) * (max(integerA, integerB) / gcd(integerA, integerB)) : 0u;
  }

  // … → lerp(𝙩, 𝙖, 𝙗) - Linearly-interpolated value 𝙩 between 𝙖 and 𝙗
  long double lerp(long double const percent, long double const begin, long double const end) {
    return begin + (percent * (end - begin));
  }

  // … → ln(𝙭) - Natural logarithm of 𝙭 (`https://en.wikipedia.org/wiki/Natural_logarithm`)
  long double ln(long double const number, std::size_t const iterationCount, bool* const representable) {
    std::size_t count     = iterationCount;
    long double logarithm = 1.0L;

    // …
    if (0.0L == number) {
      if (representable) *representable = false;
      if (iterationCount) return 0.0L;
    }

    // … → `Πₖ₌₁(2 ÷ (1 + 2ᵏ√𝙭))`
    for (long double index = 1.0L; count or not iterationCount; --count, ++index) {
      long double iteration        = 1.0L;
      long double preiteration     = logarithm;
      bool        subrepresentable = true;

      // …
      iteration = iroot (number, ipow(2.0L, index, &subrepresentable), &subrepresentable) + 1.0L;
      iteration = divide(2.0L,   iteration,                            &subrepresentable);

      // …
      preiteration     = multiply(preiteration, iteration, &subrepresentable); // → preiteration *= iteration;
      subrepresentable = subrepresentable and logarithm != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      logarithm = preiteration;
    }

    return logarithm * (number - 1.0L);
  }

  // … → log(𝙭, 𝙣) - 𝙣-radix logarithm of 𝙭
  long double log(long double const number, long double const base, std::size_t const iterationCount, bool* const representable) {
    return divide(ln(number, iterationCount, representable), ln(base, iterationCount, representable), representable);
  }

  // … → log2(𝙭) - Binary logarithm of 𝙭
  long double log2(long double const number, std::size_t const iterationCount, bool* const representable) {
    return log(number, 2.0L, iterationCount, representable);
  }

  // … → log8(𝙭) - Octonary logarithm of 𝙭
  long double log8(long double const number, std::size_t const iterationCount, bool* const representable) {
    return log(number, 8.0L, iterationCount, representable);
  }

  // … → log10(𝙭) - Common (decimal) logarithm of 𝙭
  long double log10(long double const number, std::size_t const iterationCount, bool* const representable) {
    return log(number, 10.0L, iterationCount, representable);
  }

  // … → log16(𝙭) - Hexadecimal logarithm of 𝙭
  long double log16(long double const number, std::size_t const iterationCount, bool* const representable) {
    return log(number, 16.0L, iterationCount, representable);
  }

  // … → max(𝙭, 𝙮) - Greatest-valued number of 𝙭 and 𝙮
  intmax_t max(intmax_t const numberA, intmax_t const numberB) {
    return numberA > numberB ? numberA : numberB;
  }

  long double max(long double const numberA, long double const numberB) {
    // → Fails to correctly evaluate `max(-0.0L, +0.0L)`
    return numberA >= numberB ? numberA : numberB;
  }

  uintmax_t max(uintmax_t const numberA, uintmax_t const numberB) {
    return numberA > numberB ? numberA : numberB;
  }

  // … → maxprecof(𝙭) - Maximum normalized floating-point value of precision 𝙭
  long double maxprecof(long double const precision) {
    long double maximum = LDBL_MAX;

    // …
    while (precision != maximum - (maximum - precision))
    maximum /= FLT_RADIX;

    return maximum;
  }

  // … → maxwidthof(𝙭) - Completely set bitwise value of width 𝙭 where 𝙭 = 0 is non-representable
  uintmax_t maxwidthof(std::size_t const width) {
    return (((1u << (width - 1u)) - 1u) << 1u) + 1u;
  }

  // … → min(𝙭, 𝙮) - Least-valued number of 𝙭 and 𝙮
  intmax_t min(intmax_t const numberA, intmax_t const numberB) {
    return numberA < numberB ? numberA : numberB;
  }

  long double min(long double const numberA, long double const numberB) {
    // → Fails to correctly evaluate `min(+0.0L, -0.0L)`
    return numberA <= numberB ? numberA : numberB;
  }

  uintmax_t min(uintmax_t const numberA, uintmax_t const numberB) {
    return numberA < numberB ? numberA : numberB;
  }

  // … → modulus(𝙭) - Modulus of 𝙭 and 𝙮 ¯\_(ツ)_/¯
  intmax_t modulus(intmax_t const dividend, intmax_t const divisor, bool* const representable) {
    return remainder(dividend, divisor, representable);
  }

  long double modulus(long double const dividend, long double const divisor, bool* const representable) {
    return remainder(dividend, divisor, representable);
  }

  uintmax_t modulus(uintmax_t const dividend, uintmax_t const divisor, bool* const representable) {
    return remainder(dividend, divisor, representable);
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
    if (abs(numberA) > LDBL_MAX / abs(numberB)) {
      if (representable)
      *representable = false;

      return 0.0L;
    }

    return numberA * numberB;
  }

  uintmax_t multiply(uintmax_t const numberA, uintmax_t const numberB, bool* const representable) {
    if (numberA > UINTMAX_MAX / numberB) {
      if (representable)
      *representable = false;

      return 0u;
    }

    return numberA * numberB;
  }

  // … → next(𝙭) - Absolute next (normalized) floating-point value after 𝙭
  long double next(long double number) {
    if (not (is_infinite(number) or is_nan(number))) {
      long double       precision  = LDBL_EPSILON; // → Ideally can be multiplied by `2` toward `LDBL_MAX` without `FE_OVERFLOW`
      long double const signedness = sign(number, +1);

      // …
      number = abs(number);

      while (number == number + precision)
      precision *= 2.0L;

      // …
      return (number + (number > LDBL_MAX - precision ? 0.0L : precision)) * signedness;
    }

    return number;
  }

  // … → parity(𝙭) - Parity (oddness) of integer 𝙭
  bool parity(intmax_t const integer) {
    return 0 != integer % 2;
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
    return integer - truncation >= 1.0L;
  }

  bool parity(uintmax_t const integer) {
    return 0u != integer % 2u;
  }

  // … → pow(𝙭, 𝙣) - 𝙣th power of 𝙭 where 𝙣 ≥ 0 is a positive integer
  intmax_t pow(intmax_t const base, intmax_t const exponent, bool* const representable) {
    return ipow(base, exponent, representable);
  }

  long double pow(long double const base, long double const exponent, bool* const representable) {
    return is_integer(exponent) ? ipow(base, exponent, representable) : root(base, 1.0L / exponent, representable);
  }

  uintmax_t pow(uintmax_t const base, uintmax_t const exponent, bool* const representable) {
    return ipow(base, exponent, representable);
  }

  // … → prev(𝙭) - Absolute previous (normalized) floating-point value before 𝙭
  long double prev(long double number) {
    if (not (is_infinite(number) or is_nan(number))) {
      long double       precision  = LDBL_EPSILON; // → Ideally can be multiplied by `2` toward `LDBL_MAX` without `FE_OVERFLOW`
      long double const signedness = sign(number, +1);

      // …
      number = abs(number);

      while (number == number - precision)
      precision *= 2.0L;

      // …
      return (number + (number > LDBL_MAX - precision ? 0.0L : precision)) * signedness;
    }

    return number;
  }

  // … → remainder(𝙭, 𝙮) - Remainder of 𝙭 divided by 𝙮
  intmax_t remainder(intmax_t const dividend, intmax_t const divisor, bool* const representable) {
    if (0 == divisor) {
      if (representable)
      *representable = false;

      return 0;
    }

    return dividend % divisor;
  }

  long double remainder(long double dividend, long double divisor, bool* const representable) {
    long double const signedness = sign(dividend, +1);

    // …
    if (0.0L == divisor) {
      if (representable)
      *representable = false;

      return 0.0L;
    }

    dividend = abs(dividend);
    divisor  = abs(divisor);

    if (dividend >= divisor) {
      for (enum _ /* : unsigned char */ { EXPONENTIAL, MULTIPLICATIVE, LOGARITHMIC, ADDITIVE } operation = EXPONENTIAL; operation <= ADDITIVE; ) {
        long double subdivisor = 0.0L;

        // …
        for (long double value = divisor; value and value <= dividend; ) {
          subdivisor = value;

          switch (operation) {
            case ADDITIVE      : value = value <= LDBL_MAX - divisor ? value + divisor : 0.0L; break;
            case EXPONENTIAL   : value = value <= LDBL_MAX / value   ? value * value   : 0.0L; break;
            case LOGARITHMIC   : value = value <= LDBL_MAX / divisor ? value * divisor : 0.0L; break;
            case MULTIPLICATIVE: value = value <= LDBL_MAX - value   ? value + value   : 0.0L; break;
          }

          subdivisor *= 0.0L != value;
        }

        dividend -= subdivisor;
        operation = static_cast<enum _>(operation + (0.0L == subdivisor));
      }

      while (dividend >= divisor)
      dividend -= divisor;
    }

    return dividend * signedness;
  }

  uintmax_t remainder(uintmax_t const dividend, uintmax_t const divisor, bool* const representable) {
    if (0 == divisor) {
      if (representable)
      *representable = false;

      return 0;
    }

    return dividend % divisor;
  }

  // … → root(𝙭, 𝙣) - 𝙣th root of 𝙭 where 𝙣 ≥ 0 is a positive integer
  intmax_t root(intmax_t const base, intmax_t const exponent, bool* const representable) {
    return iroot(base, exponent, representable);
  }

  long double root(long double const base, long double exponent, bool* const representable) {
    if (is_integer(1.0L / exponent))
    return ipow(base, 1.0L / exponent, representable);

    if (is_integer(exponent))
    return iroot(base, exponent, representable);

    /* … */
    bool                subrepresentable = true;
    long double const (&subexponent)[2]  = fract(exponent);
    long double const   root             = iroot(ipow(base, subexponent[1], &subrepresentable), subexponent[0], &subrepresentable);

    // …
    if (not subrepresentable) {
      if (representable)
      *representable = false;

      return 0.0L;
    }

    return root;
  }

  uintmax_t root(uintmax_t const base, uintmax_t const exponent, bool* const representable) {
    return iroot(base, exponent, representable);
  }

  // … → round(𝙭) - Rounded value of 𝙭
  long double round(long double const number) {
    long double const characteristics = trunc(number);
    long double const mantissa        = number - characteristics;

    // …
    if (mantissa >= 0.5L) return characteristics + 1.0L;
    if (mantissa < -0.5L) return characteristics - 1.0L;

    return characteristics;
  }

  // … → sign(𝙭) - Signedness of 𝙭
  signed char sign(intmax_t const number, signed char const signedness) {
    return number > 0 ? +1 : number < 0 ? -1 : signedness;
  }

  signed char sign(long double const number, signed char const signedness) {
    if (SUPPORTS_IEEE754_FLOAT) {
      std::ptrdiff_t    index = 0;
      unsigned char     layout[sizeof(long double)];
      unsigned char     mask          = 0x00u;
      long double const signs     [2] = {+1.0L, -1.0L};
      unsigned char     sublayouts[2][sizeof(long double)];

      // … -> Assume only a single bit represents signedness
      if (0.0L == number and 0 != signedness)
      return signedness;

      for (unsigned char const *iterators[2] = {
        *static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(sublayouts[0], signs + 0, sizeof(long double))) + sizeof(long double),
        *static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(sublayouts[1], signs + 1, sizeof(long double))) + sizeof(long double)
      }; iterators[0] != sublayouts[0] and iterators[1] != sublayouts[1]; )
      if (*--iterators[0] != *--iterators[1]) {
        index = (iterators[0] - sublayouts[0]) | (iterators[1] - sublayouts[1]);
        mask  = *(iterators[0]) ^ *(iterators[1]);

        break;
      }

      return (*static_cast<unsigned char (*)[sizeof(long double)]>(std::memcpy(layout, &number, sizeof(long double))))[index] & mask ? -1 : +1;
    }

    return is_nan(number) ? signedness : number > -0.0L ? +1 : number < +0.0L ? -1 : signedness;
  }

  signed char sign(uintmax_t const number, signed char const signedness) {
    return number > 0u ? 1 : signedness;
  }

  // … → sec(𝙭) - Secant of 𝙭 radians (`https://en.wikipedia.org/wiki/Secant_(trigonometry)`)
  long double sec(long double const angle, std::size_t const iterationCount, bool* const representable) {
    return divide(1.0L, cos(angle, iterationCount, representable), representable);
  }

  // … → sech(𝙭) - Hyperbolic secant of 𝙭 radians (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Exponential_definitions`)
  long double sech(long double const angle, std::size_t const iterationCount, bool* const representable) {
    return divide(1.0L, cosh(angle, iterationCount, representable), representable);
  }

  // … → sin(𝙭) - Sine of 𝙭 radians (`https://en.wikipedia.org/wiki/Sine_and_cosine`)
  long double sin(long double const angle, std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double ratio = 0.0L; // → Opposite ÷ Hypotenuse

    // … → `Σₙ₌₀((-1)ⁿ(𝙭²ⁿ⁺¹) ÷ (2n + 1)!)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = ratio;
      bool        subrepresentable = true;

      // …
      iteration[0] = ipow(-1.0L, index) * ipow(angle, (index * 2.0L) + 1.0L, &subrepresentable);
      iteration[1] = ifactorial((index * 2.0L) + 1.0L, &subrepresentable);

      // …
      preiteration    += divide(iteration[0], iteration[1], &subrepresentable);
      subrepresentable = subrepresentable and ratio != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      ratio = preiteration;
    }

    return ratio;
  }

  // … → sinh(𝙭) - Hyperbolic sine of 𝙭 radians (`https://en.wikipedia.org/wiki/Hyperbolic_functions#Taylor_series_expressions`)
  long double sinh(long double const angle, std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double ratio = 0.0L; // → Opposite ÷ Hypotenuse

    // … → `Σₙ₌₀(𝙭²ⁿ⁺¹ ÷ (2n + 1)!)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = ratio;
      bool        subrepresentable = index * 2.0L <= imaxof();

      // …
      iteration[0] = ipow(angle, (index * 2.0L) + 1.0L, &subrepresentable);
      iteration[1] = ifactorial((index * 2.0L) + 1.0L, &subrepresentable);

      // …
      preiteration    += divide(iteration[0], iteration[1], &subrepresentable);
      subrepresentable = subrepresentable and ratio != preiteration;

      if (not subrepresentable) {
        if (representable)
        *representable = false;

        if (not iterationCount) break;
        if (representable)      return 0.0L;
      }

      ratio = preiteration;
    }

    return ratio;
  }

  // … → slerp(𝙩, 𝙖, 𝙗) - Spherical linearly-interpolated value 𝙩 between 𝙖 and 𝙗
  long double slerp(long double const percent, long double const begin, long double const end) {
    return begin * pow(begin ? end / begin : 0.0L, percent);
  }

  // … → sqrt(𝙭) - Squared root of 𝙭
  intmax_t sqrt(intmax_t const number, bool* const representable) {
    return root(number, 2, representable);
  }

  long double sqrt(long double const number, bool* const representable) {
    return root(number, 2.0L, representable);
  }

  uintmax_t sqrt(uintmax_t const number, bool* const representable) {
    return root(number, 2u, representable);
  }

  // … → subtract(𝙭, 𝙮) - Scalar addition of 𝙭 and 𝙮
  intmax_t subtract(intmax_t const numberA, intmax_t const numberB, bool* const representable) {
    if (representable and (sign(numberA) == sign(numberB) ? abs(numberA) < INTMAX_MAX - abs(numberB) : false)) {
      *representable = false;
      return 0;
    }

    return numberA + numberB;
  }

  long double subtract(long double const numberA, long double const numberB, bool* const representable) {
    if (representable and (sign(numberA) == sign(numberB) ? abs(numberA) < LDBL_MAX - abs(numberB) : false)) {
      *representable = false;
      return 0.0L;
    }

    return numberA + numberB;
  }

  uintmax_t subtract(uintmax_t const numberA, uintmax_t const numberB, bool* const representable) {
    if (representable and numberB > numberA) {
      *representable = false;
      return 0u;
    }

    return numberA + numberB;
  }

  // … → tan(𝙭) - Tangent of 𝙭 radians
  long double tan(long double const angle, std::size_t const iterationCount, bool* const representable) {
    bool              subrepresentable = true;
    long double const ratio[2]         = {sin(angle, iterationCount, &subrepresentable), cos(angle, iterationCount, &subrepresentable)}; // → Opposite ÷ Adjacent

    // …
    if (not subrepresentable) {
      if (representable) *representable = false;
      if (iterationCount) return 0.0L;
    }

    return divide(ratio[0], ratio[1], representable);
  }

  // … → tanh(𝙭) - Hyperbolic tangent of 𝙭 radians
  long double tanh(long double const angle, std::size_t const iterationCount, bool* const representable) {
    bool              subrepresentable = true;
    long double const ratio[2]         = {sinh(angle, iterationCount, &subrepresentable), cosh(angle, iterationCount, &subrepresentable)}; // → Opposite ÷ Adjacent

    // …
    if (not subrepresentable) {
      if (representable) *representable = false;
      if (iterationCount) return 0.0L;
    }

    return divide(ratio[0], ratio[1], representable);
  }

  // … → trunc(𝙭) - Truncated value of 𝙭 without its mantissa
  long double trunc(long double number) {
    long double const signedness = sign(number, +1);

    // …
    number = abs(number);

    if (next(number) < 1.0L) {
      long double counter    = 1.0L;
      long double truncation = 0.0L;

      // … → Aggregate sum of `number`'s characteristics using powers of `2`, which normally matches the base of its floating-point type `FLT_RADIX`
      while (counter < number)
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

  // … → wrap(𝙭, 𝙖, 𝙗) - Modularized value of 𝙭 between an 𝙖–𝙗 number line (`https://stackoverflow.com/a/3057774/7364573`)
  intmax_t wrap(intmax_t const number, intmax_t const begin, intmax_t const end, bool const inclusive) {
    intmax_t interval = end - begin;
    intmax_t value    = number;

    // …
    if (0 == interval)
    return begin;

    if (not inclusive) {
      value = (value - begin) % ++interval;
      return value + begin + (interval * (value < 0));
    }

    if (value < begin or value > end) {
      value %= interval;
      value += interval * (value < begin ? +1 : value > end ? -1 : 0);
    }

    if (value < begin) value = end   - (value + begin);
    if (value > end)   value = begin + (value - end);

    return value;
  }

  long double wrap(long double const number, long double const begin, long double const end, bool const inclusive) {
    long double interval = end - begin;
    long double value    = number;

    // …
    if (0.0L == interval)
    return begin;

    if (not inclusive) {
      value = remainder(value - begin, ++interval);
      return value + begin + (interval * (sign(value, +1) == -1));
    }

    if (value < begin or value > end) {
      value  = remainder(value, interval);
      value += interval * (value < begin ? +1.0L : value > end ? -1.0L : 0.0L);
    }

    if (value < begin) value = end   - (value + begin);
    if (value > end)   value = begin + (value - end);

    return value;
  }

  uintmax_t wrap(uintmax_t const number, uintmax_t const begin, uintmax_t const end, bool const inclusive) {
    uintmax_t interval = end - begin;
    uintmax_t value    = number;

    // …
    if (not inclusive) {
      value = (value - begin) % ++interval;
      return value + begin + (interval * (value < 0u));
    }

    return (value % end) + begin;
  }

  /* ... */
  _<unsigned char[sizeof(long double)]> bytesof(long double const number) {
    // frexp?
    (void) number;

    // …
    _<unsigned char[sizeof(long double)]> const bytes = {};
    return bytes;
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  /* TODO - Consider special functions and other mathematics constants (like an optimized √2), also bytesof(long double) */
}
