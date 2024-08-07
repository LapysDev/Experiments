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
  template <unsigned long long integer, unsigned long long radix, unsigned char length>
  struct countof { static unsigned char const value = countof<integer / radix, radix, length + 1u>::value; };

  template <unsigned long long radix, unsigned char length>
  struct countof<0uLL, radix, length> { static unsigned char const value = length; };

  // ...
  template <typename> struct is_char_t { static bool const value = false; };
  template <typename type> struct is_char_t<type const>          { static bool const value = is_char_t<type>::value; };
  template <typename type> struct is_char_t<type const volatile> { static bool const value = is_char_t<type>::value; };
  template <typename type> struct is_char_t<type volatile>       { static bool const value = is_char_t<type>::value; };
  template <> struct is_char_t<char>    { static bool const value = true; };
  template <> struct is_char_t<wchar_t> { static bool const value = true; };
  #if defined(__cplusplus) && __cplusplus >= 202002L
   template <> struct is_char_t<char8_t> { static bool const value = true; };
  #endif
  #if defined(__cplusplus) && __cplusplus >= 201103L
   template <> struct is_char_t<char16_t> { static bool const value = true; };
   template <> struct is_char_t<char32_t> { static bool const value = true; };
  #endif

  template <typename> struct is_pointer { static bool const value = false; };
  template <typename type> struct is_pointer<type*>                { static bool const value = true; };
  template <typename type> struct is_pointer<type const*>          { static bool const value = true; };
  template <typename type> struct is_pointer<type const volatile*> { static bool const value = true; };
  template <typename type> struct is_pointer<type volatile*>       { static bool const value = true; };

  // ...
  template <typename type, type...>
  struct collection {};
    template <std::size_t integer = 0u, std::size_t... integers>
    struct integer_collection : collection<std::size_t, integer, integers...> {
      static std::size_t const total = integer + integer_collection<integers...>::total;
    };

    template <>
    struct integer_collection<0u> : collection<std::size_t, 0u> {
      static std::size_t const total = 0u;
    };
      template <std::size_t count, std::size_t... indexes>
      struct index_sequence : index_sequence<count - 1u, count - 1u, indexes...> {};

      template <std::size_t... indexes>
      struct index_sequence<0u, indexes...> : integer_collection<0u, indexes...> {};

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
        ::string<char_t, length>::string(string, index_sequence<(capacity < length ? capacity : length)>())
      {}

      template <std::size_t capacity>
      constexpr string(string<char_t, capacity> const& string) :
        ::string<char_t, length>::string(string.value)
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
}

namespace {
  enum { UCHAR_DIG   = countof<UCHAR_MAX  , 10uLL, 0u>::value };
  enum { UINT_DIG    = countof<UINT_MAX   , 10uLL, 0u>::value };
  enum { UINTPTR_DIG = countof<UINTPTR_MAX, 16uLL, 0u>::value };
  enum { ULONG_DIG   = countof<ULONG_MAX  , 10uLL, 0u>::value };
  enum { ULLONG_DIG  = countof<ULLONG_MAX , 10uLL, 0u>::value };
  enum { USHRT_DIG   = countof<USHRT_MAX  , 10uLL, 0u>::value };
}

namespace {
  // ... --> clamp(...) ->> Converting numeric digits to string digits
  constexpr long double clamp(long double const number, long double const maximum) {
    return number < maximum ? number : maximum;
  }

  constexpr unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) {
    return integer < maximum ? integer : maximum;
  }

  // ... --> concatenate(...) ->> Compositing different strings together
  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> const& concatenate(string<char_t, capacity> const& string) {
    return string;
  }

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

  template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
  constexpr string<char_t, capacityA + capacityB + integer_collection<capacities...>::total> concatenate(string<char_t, capacityA> const& stringA, string<char_t, capacityB> const& stringB, string<char_t, capacities> const&... strings) {
    return concatenate(concatenate(stringA, stringB, index_sequence<capacityA>(), index_sequence<capacityB>()), strings...);
  }

  // ... --> lengthof(...) ->> Neatly formatting number strings
  constexpr unsigned char lengthof(unsigned long long const integer) {
    return 0uLL != integer ? 1u + lengthof(integer / 10uLL) : 0u;
  }

  constexpr unsigned char lengthof(signed long long const integer) {
    return lengthof(static_cast<unsigned long long>(0LL > integer ? -integer : integer));
  }

  // ... --> modulus(...) ->> Calculating number digits
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
  constexpr string<char_t, capacity> shift(string<char_t, capacity> const&, std::size_t const, integer_collection<> const) {
    return string<char_t, 0u>();
  }

  template <typename char_t, std::size_t capacity, std::size_t index, std::size_t... indexes>
  constexpr string<char_t, capacity> shift(string<char_t, capacity> const& string, std::size_t const length, integer_collection<index, indexes...> const) {
    return 0u != length ? shift<char_t, capacity, indexes...>(string, length - 1u, integer_collection<indexes...>()) : ::string<char_t, capacity>(string.value[indexes]...);
  }

  template <typename char_t, std::size_t capacity, std::size_t... indexes>
  constexpr string<char_t, capacity> shift(string<char_t, capacity> const& string, std::size_t const length, index_sequence<0u, indexes...> const) {
    return shift<char_t, capacity, indexes...>(string, length, integer_collection<indexes...>());
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

  template <typename char_t, typename type, std::size_t length>  // --> byte [] ->> Works for little-endian machines only
  string<char_t, 64u> stringify(unsigned char const bytes[], std::size_t const size, string<char_t, length> const& string) {
    std::puts("bruh :v");
    return (0u != size
      ?
        stringify<char_t, type, length + countof<UCHAR_MAX, 16uLL, 0u>::value>(bytes + 1, size - 1u, concatenate(
          resize<countof<UCHAR_MAX, 16uLL, 0u>::value>(stringify<char_t>(static_cast<unsigned long long>(*bytes), 16uLL)),
          string
        ))
      : resize<64u>(string)
    );
  }

  template <typename char_t, typename type>
  string<char_t, 64u> stringify(unsigned char const bytes[], std::size_t const index, unsigned long long const value, unsigned long long const recent) {
    std::printf("[%u -> %u]: (%p)" "\r\n", index, sizeof(type), static_cast<void*>(static_cast<unsigned char*>(NULL) + value));
    return index != sizeof(type) ? (
      recent > value
        /* just use string representation */ ?
        stringify<char_t, type, 0u>(bytes - index, sizeof(type), string<char_t, 0u>())

        /* use number representation */ :
        stringify<char_t, type>(bytes + 1, index + 1u, value + (*bytes << (CHAR_BIT * index)), value)
    ) : /* stop */ resize<64u>(stringify<char_t>(value, 16uLL));
  }

  template <typename char_t, typename type>
  string<char_t, 64u> stringify(unsigned char const bytes[]) {
    return stringify<char_t, type>(bytes, 0u, 0uLL, 10uLL);
  }

  // int put(int integer) {
  //   int *const address = &integer;
  //   char *const endianness = (char*) address;
  //   size_t size = sizeof(int);
  //   uintptr_t value = 0u;

  //   for (unsigned char
  //     *iterator = (unsigned char*) (void*) address,
  //     *const end = iterator + size
  //   ; end != iterator; ++iterator) {
  //     value += *iterator << (CHAR_BIT * (
  //       '\x7' != *endianness ? sizeof(int) - --size - 1u : --size
  //     ));
  //   }

  //   return value;
  // }

  template <typename char_t> // --> void*
  constexpr string<char_t, UINTPTR_DIG + 3u> stringify(void* const pointer) {
    return concatenate(
      0 > static_cast<unsigned char*>(pointer) - static_cast<unsigned char*>(NULL) ?
        string<char_t, 3u>('-', '0', 'x') :
        string<char_t, 3u>('0', 'x', '0'),
      reverse(resize<UINTPTR_DIG>(reverse(stringify<char_t>(static_cast<signed long long>((static_cast<unsigned char*>(pointer) - static_cast<unsigned char*>(NULL)) / sizeof(unsigned char)), 16uLL))))
    );
  }

  template <typename char_t, typename type, typename... types> // --> void (*)(...)
  string<char_t, 64u> stringify(type (*const pointer)(types...)) {
    return concatenate(
      string<char_t, 2u>('0', 'h'),
      stringify<char_t, type (*)(types...)>(static_cast<unsigned char const*>(static_cast<void const*>(&pointer)))
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
template <std::size_t capacity>
constexpr string<char, capacity> print(char const (&string)[capacity]) {
  return stringify<char>(string);
}

#if defined(__cplusplus) && __cplusplus >= 202002L
 template <std::size_t capacity>
 constexpr string<char8_t, capacity> print(char8_t const (&string)[capacity]) {
  return stringify<char8_t>(string);
 }
#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
 template <std::size_t capacity>
 constexpr string<char16_t, capacity> print(char16_t const (&string)[capacity]) {
  return stringify<char16_t>(string);
 }

 template <std::size_t capacity>
 constexpr string<char32_t, capacity> print(char32_t const (&string)[capacity]) {
  return stringify<char32_t>(string);
 }
#endif

template <std::size_t capacity>
constexpr string<wchar_t, capacity> print(wchar_t const (&string)[capacity]) {
  return stringify<wchar_t>(string);
}

template <typename char_t>
string<char_t, ULLONG_DIG + 1u> print(long long const integer) {
  return (0LL > integer
    ? concatenate(stringify<char_t>('-'), resize<ULLONG_DIG>(shift(stringify<char_t>(static_cast<signed long long>(-integer), 10uLL), ULLONG_DIG - lengthof(static_cast<signed long long>(integer)) + 1u)))
    : shift(stringify<char_t>(static_cast<signed long long>(integer), 10uLL), ULLONG_DIG - lengthof(static_cast<signed long long>(integer)) + 1u)
  );
}

template <typename char_t>
constexpr string<char_t, ULLONG_DIG> print(unsigned long long const integer) {
  return shift(stringify<char_t>(static_cast<unsigned long long>(integer), 10uLL), ULLONG_DIG - lengthof(static_cast<unsigned long long>(integer)));
}

template <typename char_t, std::size_t capacity>
constexpr typename assertion<is_char_t<char_t>::value, string<char_t, capacity> >::type print(char_t const (&string)[capacity]) {
  return print<capacity>(string);
}

template <typename char_t, typename type>
constexpr typename assertion<is_pointer<type>::value, string<char_t, UINTPTR_DIG + 3u> >::type print(type const pointer) {
  return stringify<char_t>(const_cast<void*>(static_cast<void const*>(pointer)));
}

// ... --> print(...)
template <typename char_t>
constexpr string<char_t, UINT_DIG + 1u> print(int const integer) {
  return print<char_t>(static_cast<long long>(integer));
}

template <typename char_t>
constexpr string<char_t, ULONG_DIG + 1u> print(long const integer) {
  return print<char_t>(static_cast<long long>(integer));
}

template <typename char_t>
constexpr string<char_t, USHRT_DIG + 1u> print(short const integer) {
  return print<char_t>(static_cast<long long>(integer));
}

template <typename char_t>
constexpr string<char_t, UCHAR_DIG + 1u> print(signed char const integer) {
  return print<char_t>(static_cast<long long>(integer));
}

template <typename char_t>
constexpr string<char_t, UCHAR_DIG> print(unsigned char const integer) {
  return print<char_t>(static_cast<unsigned long long>(integer));
}

template <typename char_t>
constexpr string<char_t, UINT_DIG> print(unsigned int const integer) {
  return print<char_t>(static_cast<unsigned long long>(integer));
}

template <typename char_t>
constexpr string<char_t, ULONG_DIG> print(unsigned long const integer) {
  return print<char_t>(static_cast<unsigned long long>(integer));
}

template <typename char_t>
constexpr string<char_t, USHRT_DIG> print(unsigned short const integer) {
  return print<char_t>(static_cast<unsigned long long>(integer));
}

// template <typename char_t, typename type, typename... types>
// constexpr string<char_t, 2u + (countof<UCHAR_MAX, 16uLL, 0u>::value * sizeof(type (*)(types...)))> print(type (*const pointer)(types...)) {
//   return stringify<char_t>(pointer);
// }
// template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types...))                            { return stringify(static_cast<void*>(pointer)); }
// template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types..., ...))                       { return stringify(static_cast<void*>(pointer)); }
// template <typename type, typename... types> constexpr string<16u> print(type (&)(types...));
// template <typename type, typename... types> constexpr string<16u> print(type (&)(types..., ...));
// template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types...))      { return stringify(static_cast<void*>(pointer)); }
// template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types..., ...)) { return stringify(static_cast<void*>(pointer)); }
// #if __cplusplus >= 201703L
//  template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types...) noexcept)                            { return stringify(static_cast<void*>(pointer)); }
//  template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types..., ...) noexcept)                       { return stringify(static_cast<void*>(pointer)); }
//  template <typename type, typename... types> constexpr string<16u> print(type (&const)(types...) noexcept);
//  template <typename type, typename... types> constexpr string<16u> print(type (&const)(types..., ...) noexcept);
//  template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types...) noexcept)      { return stringify(static_cast<void*>(pointer)); }
//  template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types..., ...) noexcept) { return stringify(static_cast<void*>(pointer)); }
// #endif

/* Main */
static int const array[1] = {0};
static char const constant[] = "Hello, World!";
static void function() {}
static char modifiable[] = "Hello, World!";
static void const *const pointer = static_cast<void const*>("Hello, World!");

int main() {
  std::printf("[void (*)()]     : \"%p\" \"0u", reinterpret_cast<void*>(&function));
    constexpr void (*const address)() = &function;
    unsigned long long value = 0uLL;

    for (unsigned char const *iterator = static_cast<unsigned char const*>(static_cast<void const*>(&address)), *const end = iterator + sizeof(void (*)()); end != iterator; ++iterator)
    value += *iterator << (CHAR_BIT * (sizeof(void (*)()) - (end - iterator))); // 0...n
  std::printf("%p\" \"0s", static_cast<void*>(static_cast<unsigned char*>(NULL) + value));
    for (unsigned char const *const end = static_cast<unsigned char const*>(static_cast<void const*>(&address)), *iterator = end + sizeof(void (*)()); end != iterator--; ) {
      std::putchar("0123456789ABCDEF"[(*iterator / 0x10u) % 16u]);
      std::putchar("0123456789ABCDEF"[(*iterator / 0x01u) % 16u]);
    }
  std::printf("%c", '"');
  std::printf("\"%.*s\"" "\r\n", sizeof(stringify<char>(function).value), stringify<char>(function).value);

  // ...
  std::printf("[int const (*)[]]: \"%p\" \"%.*s\"" "\r\n", static_cast<void const*>(&array), UINTPTR_DIG + 3u, print<char>(&array).value);
  std::printf("[void const*]    : \"%p\" \"%.*s\"" "\r\n", pointer, UINTPTR_DIG + 3u, print<char>(pointer).value);
  std::printf("[char const []]  : \"%s\" \"%s\""   "\r\n", constant, print<char>(constant).value);
  std::printf("[char []]        : \"%s\" \"%s\""   "\r\n", modifiable, print<char>(modifiable).value);
}
