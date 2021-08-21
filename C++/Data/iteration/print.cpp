#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdbool.h>
#include <stdint.h>

/* ... */
namespace {
  template <bool, typename>
  union assertion;

  template <typename base>
  union assertion<true, base> { typedef base type; };

  // ...
  template <std::size_t...> struct sequence {};

  template <std::size_t count, std::size_t... indexes> struct index_sequence : index_sequence<count - 1u, count - 1u, indexes...> {};
  template <std::size_t... indexes> struct index_sequence<0u, indexes...> : sequence<0u, indexes...> {};

  // ... --- NOTE (Lapys) -> Feel free to adapt for other character formats: `char8_t`, `char16_t`, `char32_t`, `wchar_t`
  template <typename char_t, std::size_t length>
  struct string {
    template <typename subchar_t, std::size_t capacity>
    constexpr friend string<subchar_t, capacity> stringify(subchar_t const (&string)[capacity]);

    public:
      char_t const value[length];

      // ...
      constexpr string() :
        value{}
      {}

      constexpr string(string<char_t, 0u> const&) :
        value{}
      {}

      template <typename... types>
      constexpr string(char_t const character, types const... characters) :
        value{character, characters...}
      {}

      template <std::size_t capacity>
      constexpr string(char_t const (&string)[capacity]) :
        string<char_t, length>::string(string, index_sequence<(capacity < length ? capacity : length)>())
      {}

      template <std::size_t capacity>
      constexpr string(string<char_t, capacity> const& string) :
        string<char_t, length>::string(string.value)
      {}

      template <std::size_t capacity, std::size_t... indexes>
      constexpr string(char_t const (&string)[capacity], index_sequence<0u, indexes...> const) :
        value{string[indexes]...}
      {}
  };

  template <typename char_t>
  struct string<char_t, 0u> {
    public: template <typename, std::size_t> friend struct string;
    public: constexpr string(...) {}
  };

  // ...
  template <unsigned long long integer, unsigned long long radix, unsigned char width>
  struct lengthof { static unsigned char const value = lengthof<integer / radix, radix, width + 1u>::value; };

  template <unsigned long long radix, unsigned char width>
  struct lengthof<0uLL, radix, width> { static unsigned char const value = width; };
}

namespace {
  enum { PTR_DIG    = lengthof<PTRDIFF_MAX, 16uLL, 0u>::value };
  enum { UCHAR_DIG  = lengthof<UCHAR_MAX  , 10uLL, 0u>::value };
  enum { UINT_DIG   = lengthof<UINT_MAX   , 10uLL, 0u>::value };
  enum { ULONG_DIG  = lengthof<ULONG_MAX  , 10uLL, 0u>::value };
  enum { ULLONG_DIG = lengthof<ULLONG_MAX , 10uLL, 0u>::value };
  enum { USHRT_DIG  = lengthof<USHRT_MAX  , 10uLL, 0u>::value };
}

namespace {
  // ... --> clamp(...)
  constexpr long double clamp(long double const number, long double const maximum) {
    return number < maximum ? number : maximum;
  }

  constexpr unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) {
    return integer < maximum ? integer : maximum;
  }

  // ... --> concatenate(...)
  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> const& concatenate(::string<char_t, 0u> const&, string<char_t, capacity> const& string) {
    return string;
  }

  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> const& concatenate(string<char_t, capacity> const& string, ::string<char_t, 0u> const&) {
    return string;
  }

  template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... indexesA, std::size_t... indexesB>
  constexpr string<char_t, capacityA + capacityB> concatenate(string<char_t, capacityA> const& stringA, string<char_t, capacityB> const& stringB, index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const) {
    return {stringA.value[indexesA]..., stringB.value[indexesB]...};
  }

  template <typename char_t, std::size_t capacityA, std::size_t capacityB>
  constexpr string<char_t, capacityA + capacityB> concatenate(string<char_t, capacityA> const& stringA, string<char_t, capacityB> const& stringB) {
    return concatenate(stringA, stringB, index_sequence<capacityA>(), index_sequence<capacityB>());
  }

  // ... --> modulus(...)
  constexpr long double modulus(long double const dividend, long double const divisor, long double const denominator = 0.00L) {
    return (
      0.00L == dividend ? 0.00L :                                                                  // ->> `dividend` was initially zero
      divisor > dividend && 0.00L   == denominator ? dividend :                                    // ->> `divisor` was initially greater than `dividend`
      divisor > dividend && divisor != denominator ? modulus(dividend, denominator, denominator) : // ->> `divisor` too big a factor, return it to original value
        0.00L > dividend ? -modulus(-dividend, divisor) :
        0.00L > divisor  ? +modulus(dividend, -divisor) :

        dividend >= (divisor * divisor) ? modulus(dividend - (divisor * divisor), divisor * divisor, 0.00L == denominator ? divisor : denominator) :
        dividend >= (divisor * 10.00L ) ? modulus(dividend - (divisor * 10.00L ), divisor * 10.00L , 0.00L == denominator ? divisor : denominator) :
        dividend >= (divisor + divisor) ? modulus(dividend - (divisor + divisor), divisor + divisor, 0.00L == denominator ? divisor : denominator) :
        dividend >= divisor             ? modulus(dividend - (divisor          ), divisor          , 0.00L == denominator ? divisor : denominator) :
      dividend
    );
  }

  constexpr unsigned long long modulus(unsigned long long const dividend, unsigned long long const divisor) {
    return dividend % divisor;
  }

  // ... --> repeat(...)
  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr typename assertion<0u == length, string<char_t, 0u> >::type repeat(string<char_t, capacity> const&) {
    return {};
  }

  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr typename assertion<1u == length, string<char_t, capacity> >::type repeat(string<char_t, capacity> const& string) {
    return string;
  }

  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr typename assertion<1u != length, string<char_t, capacity * length> >::type repeat(string<char_t, capacity> const& string) {
    return concatenate(string, repeat<length - 1u>(string));
  }

  // ... --> resize(...)
  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr string<char_t, length> resize(string<char_t, capacity> const& string) {
    return {string};
  }

  // ... --> reverse(...)
  template <typename char_t>
  constexpr string<char_t, 0u> const& reverse(string<char_t, 0u> const& string) {
    return string;
  }

  template <typename char_t, std::size_t capacity, std::size_t... indexes>
  constexpr string<char_t, capacity> reverse(string<char_t, capacity> const& string, index_sequence<0u, indexes...> const) {
    return {string.value[capacity - indexes - 1u]...};
  }

  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> reverse(string<char_t, capacity> const& string) {
    return reverse(string, index_sequence<capacity>());
  }

  // ... --> shift(...)
  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> shift(string<char_t, capacity> const&, std::size_t const, sequence<> const) {
    return string<char_t, 0u>();
  }

  template <typename char_t, std::size_t capacity, std::size_t index, std::size_t... indexes>
  constexpr string<char_t, capacity> shift(string<char_t, capacity> const& string, std::size_t const length, sequence<index, indexes...> const) {
    return 0u != length ? shift<char_t, capacity, indexes...>(string, length - 1u, sequence<indexes...>()) : ::string<char_t, capacity>(string.value[indexes]...);
  }

  template <typename char_t, std::size_t capacity, std::size_t... indexes>
  constexpr string<char_t, capacity> shift(string<char_t, capacity> const& string, std::size_t const length, index_sequence<0u, indexes...> const) {
    return shift<char_t, capacity, indexes...>(string, length, sequence<indexes...>());
  }

  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> shift(string<char_t, capacity> const& string, std::size_t const length) {
    return 0u != length ? shift<char_t, capacity>(string, length - 1u, index_sequence<capacity>()) : string;
  }

  // ... --> stringify(...)
  template <typename char_t> // --> NUL
  constexpr string<char_t, 0u> stringify() {
    return {};
  }

  template <typename char_t> // --> bool
  constexpr string<char_t, 5u> stringify(bool const boolean) {
    return boolean ? string<char_t, 5u>('t', 'r', 'u', 'e', '\0') : string<char_t, 5u>('f', 'a', 'l', 's', 'e');
  }

  template <typename char_t> // --> char
  constexpr string<char_t, 1u> stringify(char_t const character) {
    return {character};
  }

  template <typename char_t, std::size_t capacity> // --> char []
  constexpr string<char_t, capacity> stringify(char_t const (&string)[capacity]) {
    return {string};
  }

  template <typename char_t, typename... types> // --> unsigned long long
  constexpr typename assertion<ULLONG_DIG == sizeof...(types), string<char_t, ULLONG_DIG> >::type stringify(unsigned long long const, unsigned long long const, types const... digits) {
    return {digits...};
  }

  template <typename char_t, typename... types>
  constexpr typename assertion<ULLONG_DIG != sizeof...(types), string<char_t, ULLONG_DIG> >::type stringify(unsigned long long const integer, unsigned long long const radix, types const... digits) {
    return stringify<char_t, char_t, types...>(integer / radix, radix, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)], digits...);
  }

  template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length> // --> long double
  constexpr typename assertion<length == LDBL_DIG      && (true == CHARACTERISTICS && false == MANTISSA), string<char_t, LDBL_DIG     > const&>::type stringify(long double const, unsigned long long const, string<char_t, length> const& string) {
    return string;
  }

  template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length> // --> long double
  constexpr typename assertion<length == LDBL_MANT_DIG && (false == CHARACTERISTICS && true == MANTISSA), string<char_t, LDBL_MANT_DIG> const&>::type stringify(long double const, unsigned long long const, string<char_t, length> const& string) {
    return string;
  }

  template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length>
  constexpr typename assertion<length != LDBL_DIG      && (true == CHARACTERISTICS && false == MANTISSA), string<char_t, LDBL_DIG     > >::type stringify(long double const number, unsigned long long const radix, string<char_t, length> const& string) {
    return stringify<CHARACTERISTICS, MANTISSA, char_t, length + 1u>(
      number / static_cast<long double>(radix), radix,
      concatenate(stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number, static_cast<long double>(radix)), 36.00L))]), string)
    );
  }

  template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length>
  constexpr typename assertion<length != LDBL_MANT_DIG && (false == CHARACTERISTICS && true == MANTISSA), string<char_t, LDBL_MANT_DIG> >::type stringify(long double const number, unsigned long long const radix, string<char_t, length> const& string) {
    return stringify<CHARACTERISTICS, MANTISSA, char_t, length + 1u>(
      number * static_cast<long double>(radix), radix,
      concatenate(string, stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number * static_cast<long double>(radix), static_cast<long double>(radix)), 36.00L))]))
    );
  }

  template <typename char_t>
  constexpr string<char_t, LDBL_DIG + LDBL_MANT_DIG + 1u> stringify(long double const number, unsigned long long const radix) {
    return (0.00L > number
      ? concatenate(
        concatenate(stringify<char_t>('-'), stringify<true, false>(-number, radix, stringify<char_t>())),
        concatenate(stringify<char_t>('.'), stringify<false, true>(-number, radix, stringify<char_t>()))
      )

      : concatenate(
        concatenate(stringify<char_t>('0'), stringify<true, false>(+number, radix, stringify<char_t>())),
        concatenate(stringify<char_t>('.'), stringify<false, true>(+number, radix, stringify<char_t>()))
      )
    );
  }

  template <typename char_t> // --> signed long long
  constexpr string<char_t, ULLONG_DIG + 1u> stringify(long long const integer, unsigned long long const radix) {
    return (0LL > integer
      ? concatenate(stringify<char_t>('-'), stringify<char_t>(static_cast<unsigned long long>(-integer), radix))
      : concatenate(stringify<char_t>('0'), stringify<char_t>(static_cast<unsigned long long>(+integer), radix))
    );
  }

  template <typename char_t> // --> void*
  string<char_t, PTR_DIG + 2u> stringify(void* const pointer) {
    return concatenate(
      string<char_t, 2u>('0', 'x'),
      reverse(resize<PTR_DIG>(reverse(stringify<char_t>(static_cast<unsigned long long>(static_cast<unsigned char*>(pointer) - static_cast<unsigned char*>(NULL)), 16uLL))))
    );
  }
}

// ... --> flush(...)
template <typename char_t, std::size_t capacity>
static std::size_t flush(FILE *const stream, string<char_t, capacity> const& string) {
  return std::fprintf(stream, "%.*s", string.value, static_cast<int>(capacity));
}

template <typename char_t, std::size_t capacity>
static std::size_t flush(string<char_t, capacity> const& string) {
  return flush(stdout, string);
}

// ... --> print(...)
template <typename char_t, std::size_t capacity>
constexpr string<char_t, capacity> print(char_t (&string)[capacity]) {
  return stringify(string);
}

/* Main */
int main() {}
