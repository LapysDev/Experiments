#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdbool.h>
#include <stdint.h>

/* ... */
namespace {
  template <bool, typename>
  union assert_t;

  template <typename base>
  union assert_t<true, base> {
    typedef base type;
  };

  // ...
  template <typename type, type...>
  struct collection {};
    template <std::size_t...>
    struct integer_collection;

    template <>
    struct integer_collection<> : public collection<std::size_t> {
      enum { total = 0u };
    };

    template <std::size_t integer, std::size_t... integers>
    struct integer_collection<integer, integers...> : public collection<std::size_t, integer, integers...> {
      enum { total = integer + integer_collection<integers...>::total };
    };
      template <std::size_t count, std::size_t... indexes>
      struct index_sequence : public index_sequence<count - 1u, count - 1u, indexes...> {};

      template <std::size_t... indexes>
      struct index_sequence<0u, indexes...> : public integer_collection<0u, indexes...> {};

  // ...
  template <unsigned long long integer, unsigned long long radix, unsigned char length>
  union countof {
    enum { value = countof<integer / radix, radix, length + 1u>::value };
  };

  template <unsigned long long radix, unsigned char length>
  union countof<0uLL, radix, length> {
    enum { value = length };
  };

  // ...
  template <typename> union is_character { enum { value = false }; };

  template <typename type> union is_character<type const>          { enum { value = is_character<type>::value }; };
  template <typename type> union is_character<type const volatile> { enum { value = is_character<type>::value }; };
  template <typename type> union is_character<type volatile>       { enum { value = is_character<type>::value }; };

  template <> union is_character<char>    { enum { value = true }; };
  template <> union is_character<wchar_t> { enum { value = true }; };
  #if defined(__cplusplus) && __cplusplus >= 202002L
   template <> union is_character<char8_t> { enum { value = true }; };
  #endif
  #if defined(__cplusplus) && __cplusplus >= 201103L
   template <> union is_character<char16_t> { enum { value = true }; };
   template <> union is_character<char32_t> { enum { value = true }; };
  #endif

  // ...
  template <typename> union is_function_pointer { enum { value = false }; };
  template <typename base, typename... types> union is_function_pointer<base (*)(types...)>      { enum { value = true }; };
  template <typename base, typename... types> union is_function_pointer<base (*)(types..., ...)> { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)>                     { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...)>                { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const>          { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const>          { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const volatile> { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const volatile> { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      volatile>       { enum { value = true }; };
  template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) volatile>       { enum { value = true }; };
  #if __cplusplus >= 201703L
    template <typename base, typename... types> union is_function_pointer<base (*)(types...) noexcept>      { enum { value = true }; };
    template <typename base, typename... types> union is_function_pointer<base (*)(types..., ...) noexcept> { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...) noexcept>                     { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) noexcept>                { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const noexcept>          { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const noexcept>          { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const volatile noexcept> { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const volatile noexcept> { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      volatile noexcept>       { enum { value = true }; };
    template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) volatile noexcept>       { enum { value = true }; };
  #endif

  // ...
  template <typename> union is_object_pointer { enum { value = false }; };
  template <typename type> union is_object_pointer<type*>                { enum { value = false == is_function_pointer<type*>::value }; };
  template <typename type> union is_object_pointer<type const*>          { enum { value = is_object_pointer<type*>::value }; };
  template <typename type> union is_object_pointer<type const volatile*> { enum { value = is_object_pointer<type*>::value }; };
  template <typename type> union is_object_pointer<type volatile*>       { enum { value = is_object_pointer<type*>::value }; };

  // ...
  template <typename char_t, std::size_t length>
  struct string {
    char_t const value[length];

    // ...
    constexpr string() noexcept(noexcept(::string<char_t, length>(index_sequence<length>()))) :
      ::string<char_t, length>::string(index_sequence<length>())
    {}

    constexpr string(string<char_t, 0u> const&) noexcept(noexcept(::string<char_t, length>())) :
      ::string<char_t, length>::string()
    {}

    template <typename... types>
    constexpr string(char_t const character, types const... characters) noexcept(noexcept(::string<char_t, length>(index_sequence<length - sizeof...(characters) - 1u>(), character, characters...))) :
      ::string<char_t, length>::string(index_sequence<length - sizeof...(characters) - 1u>(), character, characters...)
    {}

    template <std::size_t capacity>
    constexpr string(char_t const (&string)[capacity]) noexcept(noexcept(::string<char_t, length>(string, index_sequence<(capacity < length) ? capacity : length>()))) :
      ::string<char_t, length>::string(string, index_sequence<(capacity < length) ? capacity : length>())
    {}

    template <std::size_t capacity>
    constexpr string(string<char_t, capacity> const& string) noexcept(noexcept(::string<char_t, length>(string.value))) :
      ::string<char_t, length>::string(string.value)
    {}

    template <std::size_t capacity, std::size_t... indexes>
    constexpr string(char_t const (&string)[capacity], index_sequence<0u, indexes...> const) noexcept(noexcept(char_t(*string))) :
      value{string[indexes]...}
    {}

    template <typename... chars_t, std::size_t... indexes>
    constexpr string(index_sequence<0u, indexes...> const, chars_t const... characters) noexcept(noexcept(char_t('\0'))) :
      value{characters..., "\0"[indexes - indexes]...}
    {}
  };

  template <typename char_t>
  struct string<char_t, 0u> {
    constexpr string(...) {}
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
  // ... --> clamp(…) ->> Converting numeric digits to string digits
  constexpr long double clamp(long double const number, long double const maximum) {
    return number < maximum ? number : maximum;
  }

  constexpr unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) {
    return integer < maximum ? integer : maximum;
  }

  // ... --> concatenate(…) ->> Compositing different strings together
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

  // ... --> lengthof(…) ->> Neatly formatting number strings
  constexpr unsigned char lengthof(unsigned long long const integer) {
    return 0uLL != integer ? 1u + lengthof(integer / 10uLL) : 0u;
  }

  constexpr unsigned char lengthof(signed long long const integer) {
    return lengthof(static_cast<unsigned long long>(0LL > integer ? -integer : integer));
  }

  // ... --> modulus(…) ->> Calculating number digits
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

  // ... --> resize(…)
  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr string<char_t, length> resize(string<char_t, capacity> const& string) {
    return {string};
  }

  // ... --> reverse(…)
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

  // ... --> shift(…)
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

  // ... --> stringify(…)
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

  #if __cplusplus >= 201402L // --> unsigned long long
    template <typename char_t, std::size_t... indexes>
    constexpr string<char_t, ULLONG_DIG> stringify(unsigned long long integer, unsigned long long const radix, index_sequence<0u, indexes...> const) {
      char_t string[ULLONG_DIG] = {"\0"[indexes - indexes]...};

      for (char_t *iterator = string + ULLONG_DIG; 0uLL != integer; integer /= 10uLL)
      *--iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)];

      return string;
    }

    template <typename char_t>
    constexpr string<char_t, ULLONG_DIG> stringify(unsigned long long const integer, unsigned long long const radix) {
      return stringify<char_t>(integer, radix, index_sequence<ULLONG_DIG>());
    }
  #else
    template <typename char_t, typename... types>
    constexpr typename assert_t<ULLONG_DIG == sizeof...(types), string<char_t, ULLONG_DIG> >::type stringify(unsigned long long const, unsigned long long const, types const... digits) {
      return {digits...};
    }

    template <typename char_t, typename... chars_t>
    constexpr typename assert_t<ULLONG_DIG != sizeof...(chars_t), string<char_t, ULLONG_DIG> >::type stringify(unsigned long long const integer, unsigned long long const radix, chars_t const... digits) {
      return stringify<char_t, char_t, chars_t...>(integer / radix, radix, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)], digits...);
    }
  #endif

  #if false && __cplusplus >= 201402L // --> long double
    template <typename char_t, std::size_t... characteristicsIndexes, std::size_t... mantissaIndexes>
    constexpr string<char_t, LDBL_DIG + LDBL_MANT_DIG + 1u> stringify(long double const number, unsigned long long const radix) {
      char_t string[] = {"\0"[characteristicsIndexes - characteristicsIndexes]..., '.', "\0"[mantissaIndexes - mantissaIndexes]...};
      return string;
    }

    template <typename char_t>
    constexpr string<char_t, LDBL_DIG + LDBL_MANT_DIG + 1u> stringify(long double const number, unsigned long long const radix) {
      return stringify<char_t>(number, radix, index_sequence<LDBL_DIG>(), index_sequence<LDBL_MANT_DIG>())
    }
  #else
    template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length>
    constexpr typename assert_t<length == LDBL_DIG      && (true == CHARACTERISTICS && false == MANTISSA), string<char_t, LDBL_DIG     > const&>::type stringify(long double const, unsigned long long const, string<char_t, length> const& string) {
      return string;
    }

    template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length>
    constexpr typename assert_t<length == LDBL_MANT_DIG && (false == CHARACTERISTICS && true == MANTISSA), string<char_t, LDBL_MANT_DIG> const&>::type stringify(long double const, unsigned long long const, string<char_t, length> const& string) {
      return string;
    }

    template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length>
    constexpr typename assert_t<length != LDBL_DIG      && (true == CHARACTERISTICS && false == MANTISSA), string<char_t, LDBL_DIG     > >::type stringify(long double const number, unsigned long long const radix, string<char_t, length> const& string) {
      return stringify<CHARACTERISTICS, MANTISSA, char_t, length + 1u>(
        number / static_cast<long double>(radix), radix,
        concatenate(stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number, static_cast<long double>(radix)), 36.00L))]), string)
      );
    }

    template <bool CHARACTERISTICS, bool MANTISSA, typename char_t, std::size_t length>
    constexpr typename assert_t<length != LDBL_MANT_DIG && (false == CHARACTERISTICS && true == MANTISSA), string<char_t, LDBL_MANT_DIG> >::type stringify(long double const number, unsigned long long const radix, string<char_t, length> const& string) {
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
  #endif

  template <typename char_t, std::size_t size, std::size_t capacity> // --> unsigned char[]
  constexpr typename assert_t<capacity == size * countof<UCHAR_MAX, 16uLL, 0u>::value, string<char_t, size * countof<UCHAR_MAX, 16uLL, 0u>::value> >::type stringify(unsigned char const[], unsigned char const[], string<char_t, capacity> const& string) {
    return string;
  }

  template <typename char_t, std::size_t size, std::size_t capacity>
  constexpr typename assert_t<capacity != size * countof<UCHAR_MAX, 16uLL, 0u>::value, string<char_t, size * countof<UCHAR_MAX, 16uLL, 0u>::value> >::type stringify(unsigned char const current[], unsigned char const end[], string<char_t, capacity> const& string) {
    return current != end ? stringify<char_t, size, capacity + countof<UCHAR_MAX, 16uLL, 0u>::value>(
      current - 1, end, concatenate<char_t>(string, resize<countof<UCHAR_MAX, 16uLL, 0u>::value>(
        shift(stringify<char_t>(static_cast<unsigned long long>(*current), 16uLL), ULLONG_DIG - countof<UCHAR_MAX, 16uLL, 0u>::value)
      ))
    ) : resize<size * countof<UCHAR_MAX, 16uLL, 0u>::value>(string);
  }

  template <typename char_t, std::size_t size>
  constexpr string<char_t, size * countof<UCHAR_MAX, 16uLL, 0u>::value> stringify(unsigned char const bytes[]) {
    return stringify<char_t, size, 0u>((bytes + size) - 1, bytes - 1, string<char_t, 0u>());
  }

  template <typename char_t> // --> void*
  constexpr string<char_t, UINTPTR_DIG + 3u> stringify(void* const pointer) {
    return concatenate(
      0 > static_cast<unsigned char*>(pointer) - static_cast<unsigned char*>(NULL) ?
        string<char_t, 3u>('-', '0', 'x') :
        string<char_t, 3u>('0', 'x', '0'),
      reverse(resize<UINTPTR_DIG>(reverse(stringify<char_t>(static_cast<unsigned long long>((static_cast<unsigned char*>(pointer) - static_cast<unsigned char*>(NULL)) / sizeof(unsigned char)), 16uLL))))
    );
  }

  template <typename char_t, std::size_t size> // --> void (*)(…)
  constexpr string<char_t, 2u + (size * countof<UCHAR_MAX, 16uLL, 0u>::value)> stringify(void const* const pointer) {
    return concatenate(string<char_t, 2u>('0', 'h'), stringify<char_t, size>(static_cast<unsigned char const*>(pointer)));
  }
}

// ... --> flush(…)
template <typename char_t, std::size_t capacity>
static std::size_t flush(FILE *const stream, string<char_t, capacity> const& string) {
  return std::fprintf(stream, "%.*s", static_cast<int>(capacity), string.value);
}

template <typename char_t, std::size_t capacity>
static std::size_t flush(string<char_t, capacity> const& string) {
  return flush(stdout, string);
}

// ... --> print(…)
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
constexpr string<char_t, 5u> print(bool const boolean) {
  return stringify<char_t>(boolean);
}

template <typename char_t>
constexpr string<char_t, 1u> print(char const character) {
  return stringify<char_t>(character);
}

template <typename char_t>
constexpr string<char_t, ULLONG_DIG + 1u> print(long long const integer) {
  return concatenate(
    stringify<char_t>(0LL > integer ? '-' : '0'),
    resize<ULLONG_DIG>(shift(stringify<char_t>(static_cast<unsigned long long>(0LL > integer ? -integer : integer), 10uLL), ULLONG_DIG - lengthof(static_cast<signed long long>(integer))))
  );
}

template <typename char_t>
constexpr string<char_t, ULLONG_DIG> print(unsigned long long const integer) {
  return shift(stringify<char_t>(static_cast<unsigned long long>(integer), 10uLL), ULLONG_DIG - lengthof(static_cast<unsigned long long>(integer)));
}

template <typename char_t, typename type>
constexpr typename assert_t<is_function_pointer<type>::value, string<char_t, 2u + (countof<UCHAR_MAX, 16uLL, 0u>::value * sizeof(type))> >::type print(type const pointer) {
  return stringify<char_t, sizeof(type)>(static_cast<void const*>(&pointer));
}

template <typename char_t, typename type>
constexpr typename assert_t<is_object_pointer<type>::value, string<char_t, UINTPTR_DIG + 3u> >::type print(type const pointer) {
  return stringify<char_t>(const_cast<void*>(static_cast<void const*>(pointer)));
}

template <typename char_t, typename type, typename... types> constexpr string<char_t, 1u> print(type (&)(types...)) = delete;
template <typename char_t, typename type, typename... types> constexpr string<char_t, 1u> print(type (&)(types..., ...)) = delete;
#if __cplusplus >= 201703L
  template <typename char_t, typename type, typename... types> constexpr string<char_t, 1u> print(type (&)(types...) noexcept) = delete;
  template <typename char_t, typename type, typename... types> constexpr string<char_t, 1u> print(type (&)(types..., ...) noexcept) = delete;
#endif

// ... --> print(…)
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

template <typename char_t, std::size_t capacity>
constexpr typename assert_t<is_character<char_t>::value, string<char_t, capacity> >::type print(char_t const (&string)[capacity]) {
  return print<capacity>(string);
}

/* Main ->> */
constexpr static int const      array[1] = {0};
constexpr static bool const     boolean = true;
constexpr static char const     character = 'L';
constexpr static char const     constant[] = "Hello, World!";
constexpr static int            function() { return 0x0; }
struct object { constexpr int   member() const volatile { return 0x0; } };
constexpr static char           modifiable[] = "Hello, World!";
constexpr static signed const   negative = -1337;
constexpr static void const    *pointer = static_cast<void const*>("Hello, World!");
constexpr static unsigned const positive = 1337u;

int main() {
  // ❌ array ->> conversion from `void*` and null pointer arithmetic disallowed
  auto const arrayPointerString = print<char>(&array);
  std::printf("[int const (*)[]]  : \"%p\" -> \"%.*s\"" "\r\n", static_cast<void const*>(&array), static_cast<int>(UINTPTR_DIG + 3u), arrayPointerString.value);

  // ✅ boolean
  constexpr auto const booleanString = print<char>(boolean);
  std::printf("[int const (*)[]]  : \"%4.5s\" -> \"%.*s\"" "\r\n", boolean ? "true" : "false", 5u, booleanString.value);

  // ✅ character
  constexpr auto const characterString = print<char>(character);
  std::printf("[int const (*)[]]  : \"%c\" -> \"%.*s\"" "\r\n", character, 1u, characterString.value);

  // ✅ constant
  constexpr auto constantString = print<char>(constant);
  std::printf("[char const []]    : \"%s\" -> \"%s\"" "\r\n", constant, constantString.value);

  // ❌ function ->> conversion from `void*` and null pointer arithmetic disallowed
  auto const functionPointerString = print<char>(&function);

  std::printf("[int (*)()]        : \"%p\"" " ", reinterpret_cast<void*>(&function));
  std::printf("\"0n");
    constexpr int (*const functionAddress)() = &function;
    unsigned long long functionAddressValue = 0uLL;

    for (unsigned char const *iterator = static_cast<unsigned char const*>(static_cast<void const*>(&functionAddress)), *const end = iterator + sizeof(int (*)()); end != iterator; ++iterator)
    functionAddressValue += *iterator << (CHAR_BIT * (sizeof(int (*)()) - (end - iterator))); // 0..n
  std::printf("%p\"" " ", reinterpret_cast<void*>(functionAddressValue));
  std::printf("\"0n");
    for (unsigned char const *const end = static_cast<unsigned char const*>(static_cast<void const*>(&functionAddress)), *iterator = end + sizeof(int (*)()); end != iterator--; ) {
      std::putchar("0123456789ABCDEF"[(*iterator / 0x10u) % 16u]);
      std::putchar("0123456789ABCDEF"[(*iterator / 0x01u) % 16u]);
    }
  std::printf("\"" " ");
  std::printf("-> \"%.*s\"" "\r\n", static_cast<int>(sizeof(functionPointerString)), functionPointerString.value);

  // ❌ member ->> conversion from `void*` and null pointer arithmetic disallowed
  auto const memberPointerString = print<char>(&object::member);
  std::printf("[int (object::*)()]: \"");
    union {
      int (object::* member)() const volatile;
      unsigned char bytes[sizeof(int (object::*)() const volatile)];
    } memberAddressBytes;
    memberAddressBytes.member = &object::member;

    for (unsigned char const *const end = memberAddressBytes.bytes, *iterator = end + sizeof(int (object::*)()); end != iterator--; ) {
      std::putchar("0123456789ABCDEF"[(*iterator / 0x10u) % 16u]);
      std::putchar("0123456789ABCDEF"[(*iterator / 0x01u) % 16u]);
    }
  std::printf("\"" " ");
  std::printf("\"0n");
    constexpr int (object::*const memberAddress)() const volatile = &object::member;
    unsigned long long memberAddressValue = 0uLL;

    for (unsigned char const *iterator = static_cast<unsigned char const*>(static_cast<void const*>(&memberAddress)), *const end = iterator + sizeof(int (object::*)() const volatile); end != iterator; ++iterator)
    memberAddressValue += *iterator << (CHAR_BIT * (sizeof(int (object::*)() const volatile) - (end - iterator))); // 0..n
  std::printf("%p\"" " ", reinterpret_cast<void*>(memberAddressValue));
  std::printf("\"0n");
    for (unsigned char const *const end = static_cast<unsigned char const*>(static_cast<void const*>(&memberAddress)), *iterator = end + sizeof(int (object::*)() const volatile); end != iterator--; ) {
      std::putchar("0123456789ABCDEF"[(*iterator / 0x10u) % 16u]);
      std::putchar("0123456789ABCDEF"[(*iterator / 0x01u) % 16u]);
    }
  std::printf("\"" " ");
  std::printf("-> \"%.*s\"" "\r\n", static_cast<int>(sizeof(memberPointerString)), memberPointerString.value);

  // ✅ modifiable
  constexpr auto modifiableString = print<char>(const_cast<char (&)[14]>(modifiable));
  std::printf("[char []]          : \"%s\" -> \"%s\"" "\r\n", modifiable, modifiableString.value);

  // ✅ negative
  constexpr auto const negativeString = print<char>(negative);
  std::printf("[signed int]       : \"%i\" -> \"%.*s\"" "\r\n", negative, static_cast<int>(UINT_DIG + 1u), negativeString.value);

  // ❌ pointer ->> conversion from `void*` and null pointer arithmetic disallowed
  auto const pointerString = print<char>(pointer);
  std::printf("[void const*]      : \"%p\" -> \"%.*s\"" "\r\n", pointer, static_cast<int>(UINTPTR_DIG + 3u), pointerString.value);

  // ✅ positive
  constexpr auto const positiveString = print<char>(positive);
  std::printf("[unsigned int]     : \"%u\" -> \"%.*s\"" "\r\n", positive, static_cast<int>(UINT_DIG), positiveString.value);
}
