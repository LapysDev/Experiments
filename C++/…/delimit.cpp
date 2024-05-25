#include <cfloat>     // --> DBL_MAX
#include <climits>    // --> UCHAR_MAX
#include <cmath>      // --> HUGE_VALL, std::floor(…), std::fmod(…), std::modf(…)
#include <cstdio>     // --> …
#include <fenv.h>     // --> FENV_ACCESS, FE_ALL_EXCEPT, FE_INEXACT, feclearexcept(…), fetestexcept(…)
#include <stdexcept>  // --> std::domain_error, std::logic_error
#include <stdint.h>   // --> UINTMAX_MAX

/* ... */
#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 1419)
# pragma warning(disable: 1572)
#endif

#if false == defined(__GNUC__) && false == defined(_MSC_VER)
# pragma STDC FENV_ACCESS ON
#endif

/* ... */
static struct delimited {
  private:
    template <bool, typename = void>
    struct delimitable;

    template <typename dummy>
    struct delimitable<true, dummy> {
      typedef delimited type;
    };

    // ...
    template <typename, typename = void>
    struct is_integral {
      static bool const value = false;
    };

    template <typename dummy>
    struct is_integral<int /* --> decltype(0) */, dummy> {
      static bool const value = true;
    };

    // ...
    template <typename, typename = void>
    struct is_rational {
      static bool const value = false;
    };

    template <typename dummy>
    struct is_rational<double /* --> decltype(0.0) */, dummy> {
      static bool const value = true;
    };

  public:
    long double   value;
    unsigned char mantissaLength;
    unsigned char mantissaSequence;
    bool          signedness;

    /* ... */
    friend inline delimited operator +(::delimited const delimited) {
      return delimited;
    }

    friend inline delimited operator -(::delimited delimited) {
      delimited.signedness = false == delimited.signedness;
      return delimited;
    }

    friend inline delimited operator !(::delimited delimited) {
      delimited.value = 0.0L != delimited.value ? 1.0L : 0.0L;
      return delimited;
    }

    friend inline delimited operator ~(::delimited delimited) /* throw(std::logic_error) */ {
      if (0u != delimited.mantissaLength) throw std::logic_error("Bitwise complement `~` applied on decimal number");
      if (delimited.value > UINTMAX_MAX)  throw std::logic_error("Bitwise complement `~` applied on number greater than in-built integer types");

      delimited.value = static_cast<long double>(~static_cast<uintmax_t>(delimited.value));
      return delimited;
    }

    template <typename type>
    friend inline delimited operator ,(typename delimitable<is_integral<type>::value>::type delimited, type integer) /* throw(std::domain_error) */ {
      if (integer < 0)
      throw std::domain_error("Expected only digits in number, encountered `-` sign");

      if (integer > 999 || (delimited.mantissaSequence > 3u && UCHAR_MAX != delimited.mantissaSequence))
      throw std::domain_error("Expected sequences of 1-3 digits per `,` delimiter");

      // ...
      if (0u != delimited.mantissaLength || UCHAR_MAX == delimited.mantissaSequence) {
        long double number = integer;

        for (delimited.mantissaSequence = 0u; integer; ++delimited.mantissaSequence, integer /= 10) {
          if (number < DBL_MIN * 10.0)
          throw std::domain_error("Too many digits in number's decimal part");

          number /= 10.0L;
        }

        for (unsigned char count = delimited.mantissaLength; count; --count) {
          if (number < DBL_MIN * 10.0)
          throw std::domain_error("Too many digits in number's decimal part");

          number /= 10.0L;
        }

        delimited.mantissaLength += delimited.mantissaSequence;
        delimited.value          += number;
      }

      else for (signed char exponent = 100; exponent; exponent /= 10) {
        if (delimited.value > HUGE_VAL /* L */ / 10.0L)
        throw std::domain_error("Too many digits in number");

        delimited.value *= 10.0L;
        delimited.value += (integer / exponent) % 10;
      }

      // ...
      return delimited;
    }


    template <typename type>
    friend inline delimited operator ,(typename delimitable<is_rational<type>::value>::type delimited, type number) /* throw(std::domain_error) */ {
      double integer = 0.0;

      // ...
      if (number <  0.0)
      throw std::domain_error("Expected only digits in number, encountered `-` sign");

      if (number >= 1000.0)
      throw std::domain_error("Expected sequences of 1-3 digits per `,` delimiter");

      if (0u != delimited.mantissaLength || UCHAR_MAX == delimited.mantissaSequence)
      throw std::domain_error("Too many decimal points in number");

      // ...
      number                     = std::modf(number, &integer);
      delimited                  = operator ,(delimited, static_cast<int>(integer));
      delimited.mantissaSequence = UCHAR_MAX;
      delimited.value           += number;

      if (0.0 != number) {
        delimited.mantissaSequence = 0u;
        ::feclearexcept(FE_ALL_EXCEPT);

        while (true) {
          if (UCHAR_MAX == (++delimited.mantissaLength, ++delimited.mantissaSequence))
          throw std::domain_error("Too many digits in number's decimal part");

          number *= 10.0;
          if (number > DBL_MAX / 10.0 || number == std::floor(number)) break;
          if (::fetestexcept(FE_INEXACT)) break; // ->> `std::floor(…)` lost precision (failed)
        }
      }

      // ...
      return delimited;
    }

    template <typename type> // ->> only non-suffixed arithmetic literal types accepted
    friend delimited operator ,(typename delimitable<false == (is_integral<type>::value || is_rational<type>::value)>::type const, type const) /* throw(std::domain_error) */;

    // ...
    inline operator long double() const /* volatile */ {
      return this -> signedness ? -(this -> value) : +(this -> value);
    }

    template <typename type>
    inline operator type() const /* volatile */ {
      return static_cast<type>(this -> operator long double());
    }
} const D = {0.0L, 0u, 0u, false};
#define D D,

/* Main */
int main(int, char*[]) /* noexcept */ {
  // ->> expected behavior
  std::printf("[1]: %u" "\r\n", (unsigned) (D 1,000,000,000));

  // ->> odd behaviors
  std::printf("[2]: %i" "\r\n", (int) (-D 123,456,789));
  std::printf("[3]: %i" "\r\n", (int) -(D 123,456,789));

  std::printf("[4]: %u%i%i%i" "\r\n", (unsigned) D 123,456,789);

  std::printf("[5]: %f" "\r\n", (double) (D 01,234.5,678));
  std::printf("[6]: %f" "\r\n", (double) (D 1,  23,  456));
  std::printf("[7]: %f" "\r\n", (double) (D 1.0,23,  456));
  std::printf("[8]: %f" "\r\n", (double) (D 1,  23.0,456));
  std::printf("[9]: %f" "\r\n", (double) (D 1,  23,  456.0));
}
