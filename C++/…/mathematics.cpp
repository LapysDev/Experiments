#include <cfloat>
#include <ciso646>
#include <climits>
#include <cstdarg>
#include <cstddef>
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
#include <cstdio>
#include <inttypes.h>

#define FLT_RADIX       __FLT_RADIX__
#define LDBL_EPSILON    __LDBL_EPSILON__
#define LDBL_MANT_DIG   __LDBL_MANT_DIG__
#define LDBL_MAX        __LDBL_MAX__
#define LDBL_MAX_10_EXP __LDBL_MAX_10_EXP__
#define LDBL_MAX_EXP    __LDBL_MAX_EXP__
#define LDBL_MIN        __LDBL_MIN__

/* …
    → Functions evaluate denary numbers (comprised of bits) and only handle values within their expected domains: edge cases like NaN are not considered unless otherwise
    → Functions that optionally evaluate the `representable`-ness of their result typically determine it to be `false` for repeating decimals that are infinitely computed e.g.: `compute_pi()` is only finitely `representable` unlike `ipow()`
*/
namespace {
  typedef struct _ {
    private:
      typedef long double const (type)[2];

    public:
      type const _;

      inline operator type const&         () const          { return _; }
      inline operator type const volatile&() const volatile { return _; }
  } division_t, fraction_t;

  /* … */
  uintmax_t   abs                    (intmax_t);
  long double abs                    (long double);
  uintmax_t   abs                    (uintmax_t);
  long double acos                   (long double,              std::size_t = 0u, bool* = NULL);
  long double atan                   (long double,              std::size_t = 0u, bool* = NULL);
  long double atan                   (long double, long double, std::size_t = 0u, bool* = NULL);
  long double bézier                 (std::size_t, long double, ...);
  long double bézier_cubic           (long double, long double, long double, long double, long double);
  long double bézier_linear          (long double, long double, long double);
  long double bézier_quadratic       (long double, long double, long double, long double);
  intmax_t    cbrt                   (intmax_t,         bool* = NULL);
  long double cbrt                   (long double,      bool* = NULL);
  uintmax_t   cbrt                   (uintmax_t,        bool* = NULL);
  long double compute_eta            (std::size_t = 0u, bool* = NULL);
  long double compute_euler          (std::size_t = 0u, bool* = NULL);
  long double compute_infinity       ();
  long double compute_nan            ();
  long double compute_pi             (std::size_t = 0u,              bool* = NULL);
  long double compute_tau            (std::size_t = 0u,              bool* = NULL);
  long double cos                    (long double, std::size_t = 0u, bool* = NULL);
  std::size_t countof                (intmax_t);
  std::size_t countof                (long double);
  std::size_t countof                (uintmax_t);
  intmax_t    divide                 (intmax_t,    intmax_t,    bool* = NULL);
  long double divide                 (long double, long double, bool* = NULL);
  uintmax_t   divide                 (uintmax_t,   uintmax_t,   bool* = NULL);
  long double ease                   (long double);
  long double ease_in                (long double);
  long double ease_in_back           (long double);
  long double ease_in_bounce         (long double);
  long double ease_in_circular       (long double);
  long double ease_in_cubic          (long double);
  long double ease_in_elastic        (long double);
  long double ease_in_exponential    (long double);
  long double ease_in_out            (long double);
  long double ease_in_out_back       (long double);
  long double ease_in_out_bounce     (long double);
  long double ease_in_out_circular   (long double);
  long double ease_in_out_cubic      (long double);
  long double ease_in_out_elastic    (long double);
  long double ease_in_out_exponential(long double);
  long double ease_in_out_quadratic  (long double);
  long double ease_in_out_quartic    (long double);
  long double ease_in_out_quintic    (long double);
  long double ease_in_out_sine       (long double);
  long double ease_in_quadratic      (long double);
  long double ease_in_quartic        (long double);
  long double ease_in_quintic        (long double);
  long double ease_in_sine           (long double);
  long double ease_out               (long double);
  long double ease_out_back          (long double);
  long double ease_out_bounce        (long double);
  long double ease_out_circular      (long double);
  long double ease_out_cubic         (long double);
  long double ease_out_elastic       (long double);
  long double ease_out_exponential   (long double);
  long double ease_out_quadratic     (long double);
  long double ease_out_quartic       (long double);
  long double ease_out_quintic       (long double);
  long double ease_out_sine          (long double);
  long double exp                    (long double, std::size_t = 0u, bool* = NULL);
  fraction_t  fract                  (long double);
  intmax_t    icbrt                  (intmax_t,    bool* = NULL);
  long double icbrt                  (long double, bool* = NULL);
  uintmax_t   icbrt                  (uintmax_t,   bool* = NULL);
  long double ifactorial             (long double, bool* = NULL);
  uintmax_t   ifactorial             (uintmax_t,   bool* = NULL);
  long double imaxof                 ();
  intmax_t    ipow                   (intmax_t,    intmax_t,    bool* = NULL);
  long double ipow                   (long double, long double, bool* = NULL);
  uintmax_t   ipow                   (uintmax_t,   uintmax_t,   bool* = NULL);
  uintmax_t   iroot                  (intmax_t,    intmax_t,    bool* = NULL);
  long double iroot                  (long double, long double, bool* = NULL);
  uintmax_t   iroot                  (uintmax_t,   uintmax_t,   bool* = NULL);
  intmax_t    isqrt                  (intmax_t,                 bool* = NULL);
  long double isqrt                  (long double,              bool* = NULL);
  uintmax_t   isqrt                  (uintmax_t,                bool* = NULL);
  bool        is_denormal            (long double);
  bool        is_infinite            (long double);
  bool        is_integer             (long double);
  bool        is_nan                 (long double);
  bool        is_subnormal           (long double);
  long double ln                     (long double,              std::size_t = 0u, bool* = NULL);
  long double log                    (long double, long double, std::size_t = 0u, bool* = NULL);
  long double log2                   (long double,              std::size_t = 0u, bool* = NULL);
  long double log8                   (long double,              std::size_t = 0u, bool* = NULL);
  long double log10                  (long double,              std::size_t = 0u, bool* = NULL);
  long double log16                  (long double,              std::size_t = 0u, bool* = NULL);
  long double maxprecof              (long double,              std::size_t = 0u, bool* = NULL);
  intmax_t    modulus                (intmax_t,    intmax_t);
  long double modulus                (long double, long double);
  uintmax_t   modulus                (uintmax_t,   uintmax_t);
  intmax_t    multiply               (intmax_t,    intmax_t,    bool* = NULL);
  long double multiply               (long double, long double, bool* = NULL);
  uintmax_t   multiply               (uintmax_t,   uintmax_t,   bool* = NULL);
  long double next                   (long double);
  bool        parity                 (intmax_t);
  bool        parity                 (long double);
  bool        parity                 (uintmax_t);
  intmax_t    pow                    (intmax_t,    intmax_t,    bool* = NULL);
  long double pow                    (long double, long double, bool* = NULL);
  uintmax_t   pow                    (uintmax_t,   uintmax_t,   bool* = NULL);
  long double prev                   (long double);
  intmax_t    remainder              (intmax_t,    intmax_t,    bool* = NULL);
  long double remainder              (long double, long double, bool* = NULL);
  uintmax_t   remainder              (uintmax_t,   uintmax_t,   bool* = NULL);
  intmax_t    root                   (intmax_t,    intmax_t,    bool* = NULL);
  long double root                   (long double, long double, bool* = NULL);
  uintmax_t   root                   (uintmax_t,   uintmax_t,   bool* = NULL);
  long double round                  (long double);
  signed char sign                   (intmax_t,    signed char = 0);
  signed char sign                   (long double, signed char = 0);
  signed char sign                   (uintmax_t,   signed char = 0);
  long double sin                    (long double, std::size_t = 0u, bool* = NULL);
  intmax_t    sqrt                   (intmax_t,                      bool* = NULL);
  long double sqrt                   (long double,                   bool* = NULL);
  uintmax_t   sqrt                   (uintmax_t,                     bool* = NULL);
  long double tan                    (long double, std::size_t = 0u, bool* = NULL);
  long double trunc                  (long double);

  long double acosh                  (long double);
  long double acot                   (long double);
  long double acoth                  (long double);
  long double acsc                   (long double);
  long double acsch                  (long double);
  intmax_t    add                    (intmax_t,    intmax_t);
  long double add                    (long double, long double);
  uintmax_t   add                    (uintmax_t,   uintmax_t);
  long double asec                   (long double);
  long double asech                  (long double);
  long double asin                   (long double);
  long double asinh                  (long double);
  long double atanh                  (long double);
  long double beta                   (long double);
  long double bitceil                (long double);
  uintmax_t   bitceil                (uintmax_t);
  intmax_t    bitclear               (intmax_t,    std::size_t);
  long double bitclear               (long double, std::size_t);
  uintmax_t   bitclear               (uintmax_t,   std::size_t);
  intmax_t    bitflip                (intmax_t,    std::size_t = 0u);
  long double bitflip                (long double, std::size_t = 0u);
  uintmax_t   bitflip                (uintmax_t);
  long double bitfloor               (long double);
  uintmax_t   bitfloor               (uintmax_t);
  std::size_t bitpopcount            (intmax_t);
  std::size_t bitpopcount            (long double);
  std::size_t bitpopcount            (uintmax_t);
  intmax_t    bitrotleft             (intmax_t,    std::size_t = 1u);
  long double bitrotleft             (long double, std::size_t = 1u);
  uintmax_t   bitrotleft             (uintmax_t,   std::size_t = 1u);
  intmax_t    bitrotright            (intmax_t,    std::size_t = 1u);
  long double bitrotright            (long double, std::size_t = 1u);
  uintmax_t   bitrotright            (uintmax_t,   std::size_t = 1u);
  intmax_t    bitset                 (intmax_t,    std::size_t);
  long double bitset                 (long double, std::size_t);
  uintmax_t   bitset                 (uintmax_t,   std::size_t);
  intmax_t    bitshiftleft           (intmax_t,    std::size_t = 1u);
  long double bitshiftleft           (long double, std::size_t = 1u);
  uintmax_t   bitshiftleft           (uintmax_t,   std::size_t = 1u);
  intmax_t    bitshiftright          (intmax_t,    std::size_t = 1u);
  long double bitshiftright          (long double, std::size_t = 1u);
  uintmax_t   bitshiftright          (uintmax_t,   std::size_t = 1u);
  intmax_t    bitswap                (intmax_t);
  long double bitswap                (long double);
  uintmax_t   bitswap                (uintmax_t);
  std::size_t bitwidth               (uintmax_t);
  intmax_t    ceil                   (intmax_t);
  long double ceil                   (long double);
  uintmax_t   ceil                   (uintmax_t);
  intmax_t    clamp                  (intmax_t,    intmax_t,    intmax_t);
  long double clamp                  (long double, long double, long double);
  uintmax_t   clamp                  (uintmax_t,   uintmax_t,   uintmax_t);
  long double cot                    (long double);
  long double coth                   (long double);
  long double csc                    (long double);
  long double csch                   (long double);
  long double cyl_bessel             (long double, long double, long double);
  long double cyl_neumann            (long double, long double);
  long double ellint                 (long double, long double, long double, bool);
  long double expint                 (long double);
  intmax_t    floor                  (intmax_t);
  long double floor                  (long double);
  uintmax_t   floor                  (uintmax_t);
  long double hermite                (long double, std::size_t);
  long double herp                   (long double, long double, long double);
  long double jsf                    (long double);
  long double laguerre               (long double, std::size_t, std::size_t, bool);
  long double lcg                    (long double, std::size_t = 16807u, std::size_t = 0u, std::size_t = 2147483647u);
  long double legendre               (long double, std::size_t, std::size_t, bool);
  long double lerp                   (long double, long double);
  intmax_t    max                    (intmax_t,    intmax_t);
  long double max                    (long double, long double);
  uintmax_t   max                    (uintmax_t,   uintmax_t);
  intmax_t    min                    (intmax_t,    intmax_t);
  long double min                    (long double, long double);
  uintmax_t   min                    (uintmax_t,   uintmax_t);
  long double mt                     (long double);
  long double mt32                   (long double, std::size_t = 624u, std::size_t = 397u, std::size_t = 31u, std::size_t = 0x9908B0DFu,         std::size_t = 11u, std::size_t = 0xFFFFFFFFu,         std::size_t = 7u,  std::size_t = 0x9D2C5680u,         std::size_t = 15u, std::size_t = 0xEFC60000u,         std::size_t = 18u, std::size_t = 1812433253u);
  long double mt64                   (long double, std::size_t = 312u, std::size_t = 156u, std::size_t = 31u, std::size_t = 0xB5026F5AA96619E9u, std::size_t = 29u, std::size_t = 0x5555555555555555u, std::size_t = 17u, std::size_t = 0x71D67FFFEDA60000u, std::size_t = 37u, std::size_t = 0xFFF7EEE000000000u, std::size_t = 43u, std::size_t = 6364136223846793005u);
  long double mulberry               (long double);
  long double mulberry32             (long double);
  long double riemann_zeta           (long double);
  long double sec                    (long double);
  long double sech                   (long double);
  long double sinh                   (long double);
  long double slerp                  (long double, long double);
  long double sph_bessel             (long double, std::size_t);
  long double sph_legendre           (long double, std::size_t, std::size_t);
  long double sph_neumann            (long double, std::size_t);
  intmax_t    subtract               (intmax_t,    intmax_t,    bool* = NULL);
  long double subtract               (long double, long double, bool* = NULL);
  uintmax_t   subtract               (uintmax_t,   uintmax_t,   bool* = NULL);
  long double tanh                   (long double);
  intmax_t    wrap                   (intmax_t,    intmax_t,    intmax_t);
  long double wrap                   (long double, long double, long double);
  uintmax_t   wrap                   (uintmax_t,   uintmax_t,   uintmax_t);
  long double xorshift               (long double);
  long double xorshift_s             (long double);
  long double xorshift128            (long double);
  long double xorshift128_s          (long double);
  long double xorshift256_p          (long double);
  long double xorshift_p             (long double);
  long double xorshift128_p          (long double);
  long double xorshift_ss            (long double);
  long double xorshift256            (long double);
  long double xorshift256_ss         (long double);
  long double xorwow                 (long double);

  template <std::size_t size> long double knuth(long double);

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

  // … → acos(𝙭) - Arc cosine of 𝙭 (`https://people.math.sc.edu/girardi/m142/handouts/10sTaylorPolySeries.pdf`)
  /* TODO */
  // long double acos(long double number, std::size_t const iterationCount, bool* const representable) {
  //   compute_eta(iterationCount) - asin();

  //   // asin(x) = atan2 (x, sqrt ((1.0 + x) * (1.0 - x)))
  //   // acos(x) = atan2 (sqrt ((1.0 + x) * (1.0 - x)), x)
  // }

  // … → atan(𝙭) - Arc tangent of 𝙭 (`https://people.math.sc.edu/girardi/m142/handouts/10sTaylorPolySeries.pdf`, `https://en.wikipedia.org/wiki/Atan2#Definition_and_computation`)
  long double atan(long double number, std::size_t const iterationCount, bool* const representable) {
    std::size_t       count      = iterationCount;
    signed char const signedness = number > +1.0L ? +1 : number < -1.0L ? -1 : 0;
    long double       ratio      = 0.0L; // → Adjacent ÷ Opposite

    // … → `Σₙ₌₀(-1)ⁿ(𝙭²ⁿ⁺¹ ÷ (2n + 1))`
    number = 0 != signedness ? 1.0L / number : number;

    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = ratio;
      bool        subrepresentable = index <= imaxof();

      // …
      iteration[1] *= multiply(index, 2.0L, &subrepresentable) + 1.0L;

      iteration[0] *= ipow(-1.0L,  index,        &subrepresentable);
      iteration[0] *= ipow(number, iteration[1], &subrepresentable);

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

    switch (signedness) {
      case +1: ratio = +compute_eta(iterationCount) - ratio; break;
      case -1: ratio = -compute_eta(iterationCount) + ratio; break;
    }

    return ratio;
  }

  long double atan(long double const x, long double const y, std::size_t const iterationCount, bool* const representable) {
    // … → Adjacent ÷ Opposite
    switch (sign(x)) {
      case +1: {
        return atan(y / x, iterationCount, representable);
      } break;

      case -1: {
        bool              subrepresentable = true;
        long double const ratio            = atan(y / x, iterationCount, &subrepresentable);

        // …
        if (not iterationCount or subrepresentable)
        return ratio + (compute_pi(iterationCount) * sign(y, +1));
      } break;

      case 0: {
        if (sign(y))
        return 0.0L + (compute_eta(iterationCount) * sign(y, 0));
      } break;
    }

    if (representable)
    *representable = false;

    return 0.0L;
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
      bool        subrepresentable = index <= imaxof();

      // …
      iteration[1] *= ifactorial(index, &subrepresentable);

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

  // … → compute_pi(…) - Archimedes' constant (`https://en.wikipedia.org/wiki/Chudnovsky_algorithm`, or alternatively `https://en.wikipedia.org/wiki/Ramanujan–Sato_series` for a different formula)
  long double compute_pi(std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double pi    = 0.0L;

    // … → `Σₖ₌₀((-1)ᵏ(6k)!(545140134k + 13591409) ÷ (3k)!(k!)³(640320)³ᵏ⁺³ᐟ²)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = pi;
      bool        subrepresentable = index <= imaxof();

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
      bool        subrepresentable = index <= imaxof();

      // …
      iteration[0] *= ipow(-1.0L, index * 1.0L, &subrepresentable);
      iteration[0] *= ipow(angle, index * 2.0L, &subrepresentable);

      iteration[1] *= ifactorial(index * 2.0L, &subrepresentable);

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

  // … → countof(𝙭) - Number of denary digits representing 𝙭
  std::size_t countof(intmax_t const number) {
    return countof(abs(number));
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

  // … → fract(𝙭) - Split value of 𝙭 as its numerator and denominator
  fraction_t fract(long double const number) {
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

    fraction_t const fraction = {numerator, denominator};
    return fraction;
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
    uintmax_t      power      = 1u;
    intmax_t const signedness = not parity(exponent) and sign(base) == -1 ? -1 : +1;

    // …
    if (representable and (0 == base and sign(exponent) == -1)) {
      *representable = false;
      return 0;
    }

    power = ipow(abs(base), abs(exponent), representable);

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
        power    *= multiplier * (count == 1.0L and sign(base) == -1 ? -1.0L : +1.0L);
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

    root = iroot(abs(base), abs(exponent), representable);

    return root and sign(exponent) == -1 ? 1u / root : root;
  }

  long double iroot(long double const base, long double exponent, bool* const representable) {
    bool const  inverse = exponent and sign(exponent) == -1;
    long double root    = 0.0L;

    // …
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

  // … → ln(𝙭) - Natural logarithm of 𝙭 (`https://en.wikipedia.org/wiki/Natural_logarithm`)
  long double ln(long double const number, std::size_t const iterationCount, bool* const representable) {
    std::size_t count     = iterationCount;
    long double logarithm = 1.0L;

    // … → `Πₖ₌₁(2 ÷ (1 + 2ᵏ√𝙭))`
    for (long double index = 1.0L; count or not iterationCount; --count, ++index) {
      long double iteration        = 1.0L;
      long double preiteration     = logarithm;
      bool        subrepresentable = index <= imaxof();

      // …
      iteration *= iroot (number, ipow(2.0L, index, &subrepresentable), &subrepresentable) + 1.0L;
      iteration  = divide(2.0L,   iteration,                            &subrepresentable);

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

  // … → maxprecof(𝙭) - Maximum normalized floating-point value with precision 𝙭
  long double maxprecof(long double const precision) {
    long double maximum = LDBL_MAX;

    // …
    while (precision != maximum - (maximum - precision))
    maximum /= FLT_RADIX;

    return maximum;
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

  // … → sin(𝙭) - Sine of 𝙭 radians (`https://en.wikipedia.org/wiki/Sine_and_cosine`)
  long double sin(long double const angle, std::size_t const iterationCount, bool* const representable) {
    std::size_t count = iterationCount;
    long double ratio = 0.0L; // → Opposite ÷ Hypotenuse

    // … → `Σₙ₌₀((-1)ⁿ(𝙭²ⁿ⁺¹) ÷ (2n + 1)!)`
    for (long double index = 0.0L; count or not iterationCount; --count, ++index) {
      long double iteration[2]     = {1.0L, 1.0L};
      long double preiteration     = ratio;
      bool        subrepresentable = index <= imaxof();

      // …
      iteration[0] *= ipow(-1.0L, (index * 1.0L) + 0.0L, &subrepresentable);
      iteration[0] *= ipow(angle, (index * 2.0L) + 1.0L, &subrepresentable);

      iteration[1] *= ifactorial((index * 2.0L) + 1.0L, &subrepresentable);

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
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::printf("[]: %.64Lf" "\r\n", atan(-5.0L, 3.0L));
}
