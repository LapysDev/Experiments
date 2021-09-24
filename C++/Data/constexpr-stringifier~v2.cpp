#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>

#define private public

/* ... [Utilities] */
namespace {
  namespace { union void_t; }

  template <typename> union assess_array;
  template <typename> union assess_function;
  template <typename> union assess_pointer;
  template <typename> union assess_reference;
  template <typename> union baseof;
  template <typename type, type...> struct collection;
  template <bool, typename = void_t, typename = void_t> union conditional_t;
  template <unsigned long long, unsigned long long> union countof;
  template <std::size_t, std::size_t...> struct index_sequence;
  template <std::size_t...> struct integer_collection;
  template <typename> union is_array;
  template <typename> union is_character;
  template <typename> union is_function;
  template <typename> union is_function_pointer;
  template <typename> union is_object_pointer;
  template <typename> union is_pointer;
  template <typename> union is_reference;
  template <typename...> union is_same;

  // ...
  template <typename base> union assess_array { typedef base type; enum { size = 0u, value = false }; };
  template <typename base> union assess_array<base []> { typedef base type; enum { size = 0u, value = true }; };
  template <typename base, std::size_t capacity> union assess_array<base [capacity]> { typedef base type; enum { size = static_cast<unsigned int>(capacity), value = true }; };

  // ... ->> argument `types...`, and variadic state not assessed
  template <typename base> union assess_function { typedef base type; enum { value = false }; };
  template <typename base, typename... types> union assess_function<base (types...)>      { typedef base type; enum { value = true }; };
  template <typename base, typename... types> union assess_function<base (types..., ...)> { typedef base type; enum { value = true }; };
  #if __cplusplus >= 201703L
    template <typename base, typename... types> union assess_function<base (types...) noexcept>      { typedef base type; enum { value = true }; };
    template <typename base, typename... types> union assess_function<base (types..., ...) noexcept> { typedef base type; enum { value = true }; };
  #endif

  // ... ->> additional data (such as `class` scope) not assessed
  template <typename base> union assess_pointer { typedef base type; enum { has_base = false }; enum { value = false }; };
  template <typename base> union assess_pointer<base*>                { typedef base                type; enum { has_base = true }; enum { value = true }; };
  template <typename base> union assess_pointer<base const*>          { typedef base const          type; enum { has_base = true }; enum { value = true }; };
  template <typename base> union assess_pointer<base const volatile*> { typedef base const volatile type; enum { has_base = true }; enum { value = true }; };
  template <typename base> union assess_pointer<base volatile*>       { typedef base volatile       type; enum { has_base = true }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)>                     { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...)>                { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const>          { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const>          { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const volatile> { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const volatile> { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      volatile>       { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) volatile>       { typedef base type; enum { has_base = false }; enum { value = true }; };
  #if __cplusplus >= 201703L
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...) noexcept>                     { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) noexcept>                { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const noexcept>          { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const noexcept>          { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const volatile noexcept> { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const volatile noexcept> { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      volatile noexcept>       { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) volatile noexcept>       { typedef base type; enum { has_base = false }; enum { value = true }; };
  #endif

  // ...
  template <typename base> union assess_reference { typedef base type; enum { value = false }; };
  template <typename base> union assess_reference<base&>  { typedef base type; enum { value = true }; };
  template <typename base> union assess_reference<base&&> { typedef base type; enum { value = true }; };

  // ... ->> `enum`s, derived `class`es, and derived `struct`s are ignored
  template <typename base>
  union baseof {
    typedef
      typename conditional_t<
        is_array<base>::value, typename assess_array<base>::type,
      typename conditional_t<
        is_function<base>::value, typename assess_function<base>::type,
      typename conditional_t<
        is_pointer<base>::value, typename assess_pointer<base>::type,
      typename conditional_t<
        is_reference<base>::value, typename assess_reference<base>::type,
      base >::type >::type >::type >::type
    type;
  };

  // ...
  template <typename type, type...>
  struct collection {};
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
  template <> union conditional_t<false> {};
  template <> union conditional_t<true > {};
  template <typename base> union conditional_t<false, base> {};
  template <typename base> union conditional_t<true , base> { typedef base type; };
  template <typename true_t, typename false_t> union conditional_t<false, true_t, false_t> { typedef false_t type; };
  template <typename true_t, typename false_t> union conditional_t<true , true_t, false_t> { typedef true_t  type; };

  // ...
  template <unsigned long long integer, unsigned long long radix>
  union countof {
    private:
      template <unsigned long long current, unsigned char total>
      union count {
        friend union countof<integer, radix>;
        private: enum { value = count<current / radix, 1u + total>::value };
      };

    public:
      enum { value = count<integer, 0u>::value };
  };
    template <unsigned long long integer, unsigned long long radix>
    template <unsigned char total>
    union countof<integer, radix>::count<0uLL, total> {
      friend union countof<integer, radix>;
      private: enum { value = total };
    };

  // ...
  template <typename type>
  union is_array {
    enum { value = assess_array<type>::value };
  };

  // ...
  template <typename> union is_character { enum { value = false }; };

  template <> union is_character<char>     { enum { value = true }; };
  template <> union is_character<char16_t> { enum { value = true }; };
  template <> union is_character<char32_t> { enum { value = true }; };
  template <> union is_character<wchar_t>  { enum { value = true }; };
  #if __cplusplus >= 202002L
    template <> union is_character<char8_t> { enum { value = true }; };
  #endif

  template <typename type> union is_character<type const>          { enum { value = is_character<type>::value }; };
  template <typename type> union is_character<type const volatile> { enum { value = is_character<type>::value }; };
  template <typename type> union is_character<type volatile>       { enum { value = is_character<type>::value }; };

  // ...
  template <typename type>
  union is_function {
    enum { value = assess_function<type>::value };
  };

  // ...
  template <typename type>
  union is_function_pointer {
    enum { value = assess_pointer<type>::value && (false == assess_pointer<type>::has_base || is_function<typename assess_pointer<type>::type>::value) };
  };

  // ...
  template <typename type>
  union is_object_pointer {
    enum { value = assess_pointer<type>::value && (assess_pointer<type>::has_base && false == is_function<typename assess_pointer<type>::type>::value) };
  };

  // ...
  template <typename type>
  union is_pointer {
    enum { value = assess_pointer<type>::value };
  };

  // ...
  template <typename type>
  union is_reference {
    enum { value = assess_reference<type>::value };
  };

  // ...
  template <typename...>
  union is_same {
    enum { value = false };
  };

  template <typename base>
  union is_same<base> {
    enum { value = true };
  };

  template <typename base, typename... types>
  union is_same<base, base, types...> {
    enum { value = is_same<base, types...>::value };
  };
}

namespace {
  constexpr long double clamp(long double const number, long double const maximum) noexcept {
    return number < maximum ? number : maximum;
  }

  constexpr unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) noexcept {
    return integer < maximum ? integer : maximum;
  }

  // ...
  template <typename type>
  constexpr type instanceof() noexcept;

  // ... --- UPDATE (Lapys) -> Must not hit `constexpr` depths or loop limits; test with `modulus(LDBL_MAX, 10.00L)`
  #if __cplusplus >= 201402L
    constexpr long double modulus(long double dividend, long double divisor, long double const = 0.00L) noexcept {
      long double denominator = divisor;
      bool signedness = false;

      // ...
      if (0.00L == dividend) return 0.00L;
      if (
        #if __cplusplus >= 202002L
          std::is_constant_evaluated()
        #elif defined(__builtin_is_constant_evaluated)
          __builtin_is_constant_evaluated()
        #else
          true
        #endif
        || ULLONG_MAX >= dividend / divisor
      ) return dividend - (divisor * static_cast<unsigned long long>(dividend / divisor));

      // ...
      if (0.00L > dividend) { dividend = -dividend; signedness = true; }
      if (0.00L > divisor) { denominator = -divisor; divisor = -divisor; }

      while (true) {
        if (dividend < divisor) {
          if (denominator == divisor) break;

          divisor = denominator;
          continue;
        }

        if (divisor < DBL_MAX && dividend > divisor * divisor) divisor *= divisor;
        else if (divisor < LDBL_MAX / 10.00L && dividend > divisor * 10.00L) divisor *= 10.00L;
        else if (divisor < LDBL_MAX / 2.00L  && dividend > divisor * 2.00L ) divisor *= 2.00L;

        dividend -= divisor;
      }

      return dividend * (signedness ? -1.00L : 1.00L);
    }
  #else
    constexpr long double modulus(long double dividend, long double divisor, long double const denominator = 0.00L) noexcept {
      return (
        0.00L == dividend ? 0.00L :
        0.00L > dividend ? -modulus(-dividend, divisor, denominator) :
        0.00L > divisor  ? +modulus(dividend, -divisor, denominator) :
        divisor > dividend && 0.00L == denominator ? dividend :

        #if __cplusplus >= 202002L
          std::is_constant_evaluated()
        #elif defined(__builtin_is_constant_evaluated)
          __builtin_is_constant_evaluated()
        #else
          true
        #endif
        || ULLONG_MAX >= dividend / divisor ? (
          dividend - (ULLONG_MAX < dividend / divisor ? 0.00L : divisor * static_cast<unsigned long long>(dividend / divisor))
        ) : (
          divisor > dividend && denominator != divisor ? modulus(dividend, denominator, 0.00L) :
            divisor < DBL_MAX           && dividend >= (divisor * divisor) ? modulus(dividend - (divisor * divisor), divisor * divisor, 0.00L == denominator ? divisor : denominator) :
            divisor < LDBL_MAX / 10.00L && dividend >= (divisor * 10.00L ) ? modulus(dividend - (divisor * 10.00L ), divisor * 10.00L , 0.00L == denominator ? divisor : denominator) :
            divisor < LDBL_MAX / 2.00L  && dividend >= (divisor * 2.00L  ) ? modulus(dividend - (divisor * 2.00L  ), divisor * 2.00L  , 0.00L == denominator ? divisor : denominator) :
            dividend >= divisor             ? modulus(dividend - (divisor          ), divisor          , 0.00L == denominator ? divisor : denominator) :
          dividend
        )
      );
    }
  #endif

  constexpr unsigned long long modulus(unsigned long long const dividend, unsigned long long const divisor) noexcept {
    return dividend % divisor;
  }
}

/* ... [Internals] */
namespace {
  union string;
  template <typename, std::size_t> union string_t;

  // ... ->> `string_t` formatting utils. namespace
  union string {
    template <typename, std::size_t>
    friend union string_t;

    private:
      template <typename...>
      union assess_types {
        friend union string;

        private:
          enum { value = 0x00u };
          enum { resolved = false };

          typedef char type;
      };

      // ...
      template <typename base, typename...>
      union resolve_t {
        typedef base type;
      };

      template <typename... types>
      union resolve_t<void, types...> {
        typedef typename conditional_t<
          0x00u == string::assess_types<types...>::value, // ->> no discernible built-in character type found
          char, typename conditional_t<
            false == string::assess_types<types...>::resolved, // ->> different built-in character type found
            void_t, typename string::assess_types<types...>::type // ->> single built-in character type found
          >::type
        >::type type;
      };

    private:
      template <typename char_t, std::size_t offsetA, std::size_t offsetB, std::size_t capacityA, std::size_t capacityB>
      constexpr static typename conditional_t<0u == capacityA || 0u == capacityB || (capacityA <= offsetA || capacityB <= offsetB), bool>::type compare(string_t<char_t, capacityA> const&, string_t<char_t, capacityB> const&) {
        return false;
      }

      template <typename char_t, std::size_t offsetA, std::size_t offsetB, std::size_t capacityA, std::size_t capacityB>
      constexpr static typename conditional_t<0u != capacityA && 0u != capacityB && (capacityA > offsetA && capacityB > offsetB), bool>::type compare(string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB) {
        return stringA.value[offsetA] == stringB.value[offsetB] && (
          (capacityA > offsetA || capacityB > offsetB) ||
          compare<char_t, capacityA, capacityB, offsetA + 1u, offsetB + 1u>(stringA, stringB)
        );
      }

      // ...
      template <typename char_t, std::size_t capacity>
      constexpr static string_t<char_t, capacity> const& concatenate(string_t<char_t, capacity> const& string) noexcept {
        return string;
      }

      template <typename char_t>
      constexpr static string_t<char_t, 0u> concatenate(string_t<char_t, 0u> const, string_t<char_t, 0u> const) noexcept {
        return {};
      }

      template <typename char_t, std::size_t capacity>
      constexpr static string_t<char_t, capacity> const& concatenate(string_t<char_t, 0u> const, string_t<char_t, capacity> const& string) noexcept {
        return string;
      }

      template <typename char_t, std::size_t capacity>
      constexpr static string_t<char_t, capacity> const& concatenate(string_t<char_t, capacity> const& string, string_t<char_t, 0u> const) noexcept {
        return string;
      }

      template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... indexesA, std::size_t... indexesB>
      constexpr static string_t<char_t, capacityA + capacityB> concatenate(index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const, string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB) noexcept {
        return {stringA.value[indexesA]..., stringB.value[indexesB]...};
      }

      template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
      constexpr static string_t<char_t, capacityA + capacityB + integer_collection<capacities...>::total> concatenate(string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB, string_t<char_t, capacities> const&... strings) noexcept {
        return concatenate(concatenate(index_sequence<capacityA>(), index_sequence<capacityB>(), stringA, stringB), strings...);
      }

      // ...
      template <typename char_t, std::size_t length, std::size_t capacity>
      constexpr static typename conditional_t<capacity == length, string_t<char_t, length> const&>::type resize(string_t<char_t, capacity> const& string) noexcept {
        return string;
      }

      template <typename char_t, std::size_t length, std::size_t capacity>
      constexpr static typename conditional_t<capacity != length, string_t<char_t, length> >::type resize(string_t<char_t, capacity> const& string) noexcept {
        return {string};
      }

      // ...
      template <typename char_t>
      constexpr static string_t<char_t, 0u> const reverse(string_t<char_t, 0u> const string) noexcept {
        return string;
      }

      template <typename char_t>
      constexpr static string_t<char_t, 1u> const& reverse(string_t<char_t, 1u> const& string) noexcept {
        return string;
      }

      template <typename char_t, std::size_t capacity, std::size_t... indexes>
      constexpr static string_t<char_t, capacity> reverse(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
        return {string.value[capacity - indexes - 1u]...};
      }

      template <typename char_t, std::size_t capacity>
      constexpr static string_t<char_t, capacity> reverse(string_t<char_t, capacity> const& string) noexcept {
        return reverse(index_sequence<capacity>(), string);
      }

      // ...
      template <typename char_t, std::size_t count, std::size_t capacity>
      constexpr static typename conditional_t<(count >= capacity), string_t<char_t, 0u> >::type slice_begin(string_t<char_t, capacity> const&) noexcept {
        return {};
      }

      template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
      constexpr static typename conditional_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_begin(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
        return {string.value[count + indexes]...};
      }

      template <typename char_t, std::size_t count, std::size_t capacity>
      constexpr static typename conditional_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_begin(string_t<char_t, capacity> const& string) noexcept {
        return slice_begin<char_t, count>(index_sequence<capacity - count>(), string);
      }

      // ...
      template <typename char_t, std::size_t count, std::size_t capacity>
      constexpr static typename conditional_t<(count >= capacity), string_t<char_t, 0u> >::type slice_end(string_t<char_t, capacity> const&) noexcept {
        return {};
      }

      template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
      constexpr static typename conditional_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_end(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
        return {string.value[indexes]...};
      }

      template <typename char_t, std::size_t count, std::size_t capacity>
      constexpr static typename conditional_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_end(string_t<char_t, capacity> const& string) noexcept {
        return slice_end<char_t, count>(index_sequence<capacity - count>(), string);
      }

      // ...
      template <typename char_t> // --> bool
      constexpr static string_t<char_t, 5u> stringify(bool const boolean) noexcept {
        return boolean ? string_t<char_t, 5u>('t', 'r', 'u', 'e', '\0') : string_t<char_t, 5u>('f', 'a', 'l', 's', 'e');
      }

      template <typename char_t> // --> char
      constexpr static string_t<char_t, 1u> stringify(char_t const& character) noexcept {
        return {character};
      }

      template <typename char_t, std::size_t capacity, std::size_t... indexes> // --> char []
      constexpr static string_t<char_t, capacity> stringify(index_sequence<0u, indexes...> const, char const string[]) noexcept {
        return {string[indexes]...};
      }

      template <typename char_t, std::size_t capacity, std::size_t... indexes>
      constexpr static string_t<char_t, capacity> stringify(index_sequence<0u, indexes...> const, char_t const (&string)[capacity]) noexcept {
        return {string[indexes]...};
      }

      template <typename char_t, std::size_t capacity>
      constexpr static string_t<char_t, capacity> stringify(char_t const (&string)[capacity]) noexcept {
        return stringify(index_sequence<capacity>(), string);
      }

      #if __cplusplus >= 201402L // --> unsigned long long
        template <typename char_t, unsigned long long radix, std::size_t... indexes>
        constexpr static string_t<char_t, countof<ULLONG_MAX, radix>::value> stringify(index_sequence<0u, indexes...> const, unsigned long long integer) noexcept {
          char string[] = {"\0"[indexes - indexes]...};

          for (char *iterator = string + (sizeof(string) / sizeof(char)); iterator != string; integer /= radix)
          *--iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)];

          return {string[indexes]...};
        }

        template <typename char_t, unsigned long long radix, unsigned char>
        constexpr static string_t<char_t, countof<ULLONG_MAX, radix>::value> stringify(unsigned long long const integer) noexcept {
          return stringify<char_t, radix>(index_sequence<countof<ULLONG_MAX, radix>::value>(), integer);
        }
      #else
        template <typename char_t, unsigned long long radix, unsigned char count>
        constexpr static typename conditional_t<count == countof<ULLONG_MAX, radix>::value, string_t<char_t, countof<ULLONG_MAX, radix>::value> >::type stringify(unsigned long long const, string_t<char_t, count> const& string = {}) noexcept {
          return string;
        }

        template <typename char_t, unsigned long long radix, unsigned char count>
        constexpr static typename conditional_t<count != countof<ULLONG_MAX, radix>::value, string_t<char_t, countof<ULLONG_MAX, radix>::value> >::type stringify(unsigned long long const integer, string_t<char_t, count> const& string = {}) noexcept {
          return stringify<char_t, radix, count + 1u>(integer / radix, concatenate<char_t>(stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)]), string));
        }
      #endif

      #if __cplusplus >= 201402L // --> long double
        template <typename char_t, unsigned long long radix, std::size_t... characteristicsIndexes, std::size_t... mantissaIndexes>
        constexpr static string_t<char_t, 2u + LDBL_DIG + LDBL_MANT_DIG> stringify(index_sequence<0u, characteristicsIndexes...> const, index_sequence<0u, mantissaIndexes...> const, long double characteristics, long double mantissa) noexcept {
          char characteristicsString[] = {"\0"[characteristicsIndexes - characteristicsIndexes]...};
          bool signedness = false;
          char mantissaString[] = {"\0"[mantissaIndexes - mantissaIndexes]...};

          if (0.00L > characteristics || 0.00L > mantissa) {
            characteristics = -characteristics;
            mantissa = -mantissa;
            signedness = true;
          }

          for (char *iterator = characteristicsString + (sizeof(characteristicsString) / sizeof(char)); iterator != characteristicsString; characteristics /= static_cast<long double>(radix))
          *--iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(characteristics, static_cast<long double>(radix)), 36.00L))];

          for (char *iterator = mantissaString + (sizeof(mantissaString) / sizeof(char)); iterator != mantissaString; mantissa = false == (
            #if __cplusplus >= 202002L
              std::is_constant_evaluated()
            #elif defined(__builtin_is_constant_evaluated)
              __builtin_is_constant_evaluated()
            #else
              true
            #endif
          ) || mantissa < ULLONG_MAX ? mantissa * static_cast<long double>(radix) : 0.00L)
          *--iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(mantissa, static_cast<long double>(radix)), 36.00L))];

          return {signedness ? '-' : '0', characteristicsString[characteristicsIndexes]..., '.', mantissaString[LDBL_MANT_DIG - mantissaIndexes - 1u]...};
        }

        template <typename char_t, unsigned long long radix, unsigned char, unsigned char>
        constexpr static string_t<char_t, 2u + LDBL_DIG + LDBL_MANT_DIG> stringify(long double const number) noexcept {
          return stringify<char_t, radix>(index_sequence<LDBL_DIG>(), index_sequence<LDBL_MANT_DIG>(), number, number < LDBL_MAX / static_cast<long double>(radix) ? number * static_cast<long double>(radix) : number);
        }
      #else
        template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
        constexpr static typename conditional_t<characteristicsCount == LDBL_DIG && mantissaCount == LDBL_MANT_DIG, string_t<char_t, LDBL_DIG> const&>::type stringify(long double const, string_t<char_t, LDBL_DIG> const& string) noexcept {
          return string;
        }

        template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
        constexpr static typename conditional_t<characteristicsCount == LDBL_DIG && mantissaCount == LDBL_MANT_DIG, string_t<char_t, LDBL_MANT_DIG> const&>::type stringify(long double const, string_t<char_t, LDBL_MANT_DIG> const& string) noexcept {
          return string;
        }

        template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
        constexpr static typename conditional_t<characteristicsCount != LDBL_DIG && mantissaCount == LDBL_MANT_DIG, string_t<char_t, LDBL_DIG> >::type stringify(long double const number, string_t<char_t, characteristicsCount> const& string = {}) noexcept {
          return stringify<char_t, radix, characteristicsCount + 1u, mantissaCount>(number / static_cast<long double>(radix), concatenate<char_t>(stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number, static_cast<long double>(radix)), 36.00L))]), string));
        }

        template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
        constexpr static typename conditional_t<characteristicsCount == LDBL_DIG && mantissaCount != LDBL_MANT_DIG, string_t<char_t, LDBL_MANT_DIG> >::type stringify(long double const number, string_t<char_t, mantissaCount> const& string = {}) noexcept {
          return stringify<char_t, radix, characteristicsCount, mantissaCount + 1u>(number < LDBL_MAX / static_cast<long double>(radix) ? number * static_cast<long double>(radix) : number, concatenate<char_t>(string, stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number, static_cast<long double>(radix)), 36.00L))])));
        }

        template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
        constexpr static typename conditional_t<characteristicsCount != LDBL_DIG && mantissaCount != LDBL_MANT_DIG, string_t<char_t, 2u + LDBL_DIG + LDBL_MANT_DIG> >::type stringify(long double const number) noexcept {
          return concatenate<char_t>(
            stringify<char_t>(0.00L > number ? '-' : '0'), resize<char_t, LDBL_DIG>(stringify<char_t, radix, characteristicsCount, LDBL_MANT_DIG>(0.00L > number ? -number : number)),
            stringify<char_t>('.'), resize<char_t, LDBL_MANT_DIG>(stringify<char_t, radix, LDBL_DIG, mantissaCount>((0.00L > number ? -number : number) < LDBL_MAX / static_cast<long double>(radix) ? (0.00L > number ? -number : number) * static_cast<long double>(radix) : (0.00L > number ? -number : number)))
          );
        }
      #endif

      #if __cplusplus >= 201402L // --> unsigned char[]
        template <typename char_t, std::size_t size, std::size_t... indexes>
        constexpr static string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> stringify(index_sequence<0u, indexes...> const, unsigned char const bytes[]) noexcept {
          char string[] = {"\0"[indexes - indexes]...};

          for (char *iterator = string + (sizeof(string) / sizeof(char)); iterator != string; bytes += 1) {
            char const *const byte = stringify<typename conditional_t<is_same<char_t>::value, char>::type, 16uLL, 0u>(static_cast<unsigned long long>(*bytes)).value + (countof<ULLONG_MAX, 16uLL>::value - countof<UCHAR_MAX, 16uLL>::value);

            for (char_t const *subiterator = byte + countof<UCHAR_MAX, 16uLL>::value; subiterator != byte; )
            *--iterator = *--subiterator;
          }

          return {string[indexes]...};
        }

        template <typename char_t, std::size_t size, std::size_t>
        constexpr static string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> stringify(unsigned char const bytes[]) noexcept {
          return stringify<char_t, size>(index_sequence<size * countof<UCHAR_MAX, 16uLL>::value>(), bytes);
        }
      #else
        template <typename char_t, std::size_t size, std::size_t count>
        constexpr static typename conditional_t<count == size, string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> >::type stringify(unsigned char const[], string_t<char_t, count * countof<UCHAR_MAX, 16uLL>::value> const& string = {}) noexcept {
          return string;
        }

        template <typename char_t, std::size_t size, std::size_t count>
        constexpr static typename conditional_t<count != size, string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> >::type stringify(unsigned char const bytes[], string_t<char_t, count * countof<UCHAR_MAX, 16uLL>::value> const& string = {}) noexcept {
          return stringify<char_t, size, count + 1u>(bytes + 1, concatenate<char_t>(slice_begin<char_t, countof<ULLONG_MAX, 16uLL>::value - countof<UCHAR_MAX, 16uLL>::value>(stringify<char_t, 16uLL, 0u>(static_cast<unsigned long long>(*bytes))), string));
        }
      #endif

      template <typename char_t, typename type> // --> void (*)(...)
      constexpr static typename conditional_t<is_function_pointer<type>::value, string_t<char_t, sizeof(type) * countof<UCHAR_MAX, 16uLL>::value> >::type stringify(type const pointer) noexcept {
        return stringify<char_t, sizeof(type), 0u>(static_cast<unsigned char const*>(static_cast<void const*>(&pointer)));
      }

      template <typename char_t, typename type> // --> void*
      constexpr static typename conditional_t<is_object_pointer<type>::value, string_t<char_t, countof<UINTPTR_MAX, 16uLL>::value> >::type stringify(type const pointer) noexcept {
        return slice_begin<char_t, countof<ULLONG_MAX, 16uLL>::value - countof<UINTPTR_MAX, 16uLL>::value>(stringify<char_t, 16uLL, 0u>(
          #if __cplusplus >= 202002L
            std::is_constant_evaluated()
          #elif defined(__builtin_is_constant_evaluated)
            __builtin_is_constant_evaluated()
          #else
            false
          #endif
          ? static_cast<uintptr_t>(sizeof(type) * (pointer - static_cast<type>(NULL)))
          : reinterpret_cast<uintptr_t>(pointer)
        ));
      }

      template <typename char_t, typename type, std::size_t capacity> // --> void (&)[]
      constexpr static string_t<char_t, 1u> stringify(type (&)[capacity]) noexcept = delete;

      template <typename char_t, typename type, typename... types> // --> void (&)(...)
      constexpr string_t<char_t, 1u> stringify(type (&)(types...)) noexcept = delete;

      template <typename char_t, typename type, typename... types>
      constexpr string_t<char_t, 1u> stringify(type (&)(types..., ...)) noexcept = delete;

      #if __cplusplus >= 201703L
        template <typename char_t, typename type, typename... types>
        constexpr string_t<char_t, 1u> stringify(type (&)(types...) noexcept) noexcept = delete;

        template <typename char_t, typename type, typename... types>
        constexpr string_t<char_t, 1u> stringify(type (&)(types..., ...) noexcept) noexcept = delete;
      #endif

      // ...
      template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
      constexpr static typename conditional_t<(capacity < searchCapacity || 0u == searchCapacity), string_t<char_t, capacity> const&>::type trim_begin(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const&) noexcept {
        return string;
      }

      template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
      constexpr static typename conditional_t<(capacity >= searchCapacity), string_t<char_t, capacity> >::type trim_begin(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
        return compare<char_t, 0u, 0u>(string, search) ? resize<char_t, capacity>(trim_begin<char_t, capacity - searchCapacity, searchCapacity>(slice_begin<char_t, searchCapacity>(string), search)) : string;
      }

      // ...
      template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
      constexpr static typename conditional_t<(capacity < searchCapacity || 0u == searchCapacity), string_t<char_t, capacity> const&>::type trim_end(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const&) noexcept {
        return string;
      }

      template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
      constexpr static typename conditional_t<(capacity >= searchCapacity), string_t<char_t, capacity> >::type trim_end(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
        return compare<char_t, capacity - searchCapacity, 0u>(string, search) ? resize<char_t, capacity>(trim_end<char_t, capacity - searchCapacity, searchCapacity>(slice_end<char_t, searchCapacity>(string), search)) : string;
      }
  };
    template <typename base, typename... types>
    union string::assess_types<base, types...> {
      friend union string;

      private:
        enum {
          value = (is_function<base>::value || is_function_pointer<base>::value ? 0x00u : (
            is_same<typename baseof<base>::type, char>::value                   ||
            is_same<typename baseof<base>::type, char const>::value             ||
            is_same<typename baseof<base>::type, char const volatile>::value    ||
            is_same<typename baseof<base>::type, char volatile>::value          ? 0x01u :

            is_same<typename baseof<base>::type, char16_t>::value                ||
            is_same<typename baseof<base>::type, char16_t const>::value          ||
            is_same<typename baseof<base>::type, char16_t const volatile>::value ||
            is_same<typename baseof<base>::type, char16_t volatile>::value       ? 0x08u :

            is_same<typename baseof<base>::type, char32_t>::value                ||
            is_same<typename baseof<base>::type, char32_t const>::value          ||
            is_same<typename baseof<base>::type, char32_t const volatile>::value ||
            is_same<typename baseof<base>::type, char32_t volatile>::value       ? 0x10u :

            is_same<typename baseof<base>::type, wchar_t>::value                ||
            is_same<typename baseof<base>::type, wchar_t const>::value          ||
            is_same<typename baseof<base>::type, wchar_t const volatile>::value ||
            is_same<typename baseof<base>::type, wchar_t volatile>::value       ? 0x02u :

            #if __cplusplus >= 202002L
              is_same<typename baseof<base>::type, char8_t>::value                 ||
              is_same<typename baseof<base>::type, char8_t const>::value           ||
              is_same<typename baseof<base>::type, char8_t const volatile>::value  ||
              is_same<typename baseof<base>::type, char8_t volatile>::value        ? 0x04u :
            #endif
            0x00u
          )) | static_cast<unsigned>(assess_types<types...>::value)
        };

        enum {
          resolved = (
            0x00u != assess_types<base, types...>::value &&
            0u == (assess_types<base, types...>::value & (assess_types<base, types...>::value - 1u))
          )
        };

        // ...
        typedef
          typename conditional_t<
            0x01u == (assess_types<base, types...>::value | assess_types<types...>::value), char,

          typename conditional_t<
            0x08u == (assess_types<base, types...>::value | assess_types<types...>::value), char16_t,

          typename conditional_t<
            0x10u == (assess_types<base, types...>::value | assess_types<types...>::value), char32_t,

          typename conditional_t<
            0x02u == (assess_types<base, types...>::value | assess_types<types...>::value), wchar_t,

          typename conditional_t<
            #if __cplusplus >= 202002L
              0x04u == (assess_types<base, types...>::value | assess_types<types...>::value), char8_t,
            #else
              false, void,
            #endif
          void >::type >::type >::type >::type >::type
        type;
    };

  // ... ->> `char_t` members copy/ value-initialized only once
  template <typename char_t, std::size_t length>
  union string_t {
    friend union string;

    template <typename, std::size_t>
    friend union string_t;

    private:
      typedef char_t const (type)[length];
      type const value;

      // ... ->> empty string
      template <std::size_t... indexes>
      constexpr string_t(index_sequence<0u, indexes...> const) noexcept(noexcept(char_t('\0'))) :
        value{"\0"[indexes - indexes]...}
      {}

      constexpr string_t() noexcept(noexcept(string_t<char_t, length>(index_sequence<length>()))) :
        string_t<char_t, length>::string_t(index_sequence<length>())
      {}

      // ... ->> null string
      constexpr string_t(string_t<char_t, 0u> const) noexcept(noexcept(string_t<char_t, length>())) :
        string_t<char_t, length>::string_t()
      {}

      // ... ->> equal string
      template <std::size_t... indexes>
      constexpr string_t(index_sequence<0u, indexes...> const, string_t<char_t, length> const& string) noexcept(noexcept(char_t(instanceof<char_t const&>()))) :
        value{string.value[indexes]...}
      {}

      // ... ->> bigger string
      template <std::size_t capacity>
      constexpr string_t(string_t<char_t, capacity> const& string, typename conditional_t<(capacity > length), unsigned char>::type const = 0x0u) noexcept(noexcept(string_t<char_t, length>(string::slice_end<char_t, capacity - length>(instanceof<string_t<char_t, capacity> const&>())))) :
        string_t<char_t, length>::string_t(string::slice_end<char_t, capacity - length>(string))
      {}

      // ... ->> smaller string
      template <std::size_t capacity, std::size_t... nulIndexes, std::size_t... indexes>
      constexpr string_t(index_sequence<0u, nulIndexes...> const, index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept(noexcept(char_t('\0')) && noexcept(char_t(instanceof<char_t const&>()))) :
        value{string.value[indexes]..., "\0"[nulIndexes - nulIndexes]...}
      {}

      template <std::size_t capacity>
      constexpr string_t(string_t<char_t, capacity> const& string, typename conditional_t<(capacity < length), unsigned char>::type const = 0x0u) noexcept(noexcept(string_t<char_t, length>(index_sequence<length - capacity>(), index_sequence<capacity>(), instanceof<string_t<char_t, capacity> const&>()))) :
        string_t<char_t, length>::string_t(index_sequence<length - capacity>(), index_sequence<capacity>(), string)
      {}

      // ... ->> equal character-by-character
      template <typename... chars_t>
      constexpr string_t(typename conditional_t<length == 1u + sizeof...(chars_t) && (is_same<char, chars_t...>::value || is_same<char_t, chars_t...>::value), char_t>::type const& character, chars_t const&... characters) noexcept(noexcept(char_t(instanceof<char_t const&>()))) :
        value{character, characters...}
      {}

      // ... ->> more/ less character-by-character
      template <typename... chars_t>
      constexpr string_t(typename conditional_t<length != 1u + sizeof...(chars_t) && (is_same<char, chars_t...>::value || is_same<char_t, chars_t...>::value), char_t>::type const& character, chars_t const&... characters) noexcept(noexcept(string_t<char_t, length>(instanceof<string_t<char_t, 1u + sizeof...(chars_t)> const&>()))) :
        string_t<char_t, length>::string_t(string_t<char_t, 1u + sizeof...(chars_t)>(character, characters...))
      {}

    public:
      constexpr string_t(string_t<char_t, length> const& string) noexcept(noexcept(string_t<char_t, length>(index_sequence<length>(), instanceof<string_t<char_t, length> const&>()))) :
        string_t<char_t, length>::string_t(index_sequence<length>(), string)
      {}

      // ...
      constexpr friend std::size_t flush(std::FILE *const stream, string_t<char_t, length> const& string) noexcept(noexcept(flush(instanceof<std::FILE*>(), instanceof<char_t const (&)[length]>()))) {
        return flush(stream, string.value);
      }

      // ...
      constexpr explicit operator type const&() const {
        return this -> value;
      }
  };

  template <typename char_t>
  union string_t<char_t, 0u> {
    friend union string;

    template <typename, std::size_t>
    friend union string_t;

    private:
      constexpr string_t(...) noexcept {}
  };
}

/* [Interface] */
// ... --> flush(...)
template <typename type>
constexpr std::size_t flush(type const& string) noexcept(noexcept(flush(instanceof<std::FILE*>(), string))) {
  return flush(stdout, string);
}

template <std::size_t capacity>
inline std::size_t flush(std::FILE *const stream, char const (&string)[capacity]) noexcept(noexcept(std::fprintf(instanceof<std::FILE*>(), instanceof<char const*>()))) {
  return static_cast<std::size_t>(capacity > INT_MAX ? std::fprintf(stream, "%s", string) : std::fprintf(stream, "%.*s", static_cast<int>(capacity), string));
}

template <std::size_t capacity>
inline std::size_t flush(std::FILE *const stream, wchar_t const (&string)[capacity]) noexcept(noexcept(std::fprintf(instanceof<std::FILE*>(), instanceof<char const*>()))) {
  return static_cast<std::size_t>(capacity > INT_MAX ? std::fprintf(stream, "%ls", string) : std::fprintf(stream, "%.*ls", static_cast<int>(capacity), string));
}

template <typename char_t, std::size_t capacity> // ->> permits non-character `char_t` types
inline std::size_t flush(std::FILE *const stream, char_t (&string)[capacity]) noexcept(noexcept(std::fwrite(instanceof<void*>(), instanceof<std::size_t>(), instanceof<std::size_t>(), instanceof<std::FILE*>()))) {
  return std::fwrite(string, sizeof(char_t), capacity, stream);
}

// ...
template <std::size_t capacity>
constexpr std::size_t flush(std::FILE *const stream, char (&string)[capacity]) noexcept(noexcept(flush(instanceof<std::FILE*>(), instanceof<char const (&)[capacity]>()))) {
  return flush(stream, const_cast<char const (&)[capacity]>(string));
}

template <std::size_t capacity>
constexpr std::size_t flush(std::FILE *const stream, char const volatile (&string)[capacity]) noexcept(noexcept(flush(instanceof<std::FILE*>(), instanceof<char const (&)[capacity]>()))) {
  return flush(stream, const_cast<char const (&)[capacity]>(string));
}

template <std::size_t capacity>
constexpr std::size_t flush(std::FILE *const stream, char volatile (&string)[capacity]) noexcept(noexcept(flush(instanceof<std::FILE*>(), instanceof<char const (&)[capacity]>()))) {
  return flush(stream, const_cast<char const (&)[capacity]>(string));
}

template <std::size_t capacity>
constexpr std::size_t flush(std::FILE *const stream, wchar_t (&string)[capacity]) noexcept(noexcept(flush(instanceof<std::FILE*>(), instanceof<wchar_t const (&)[capacity]>()))) {
  return flush(stream, const_cast<wchar_t const (&)[capacity]>(string));
}

template <std::size_t capacity>
constexpr std::size_t flush(std::FILE *const stream, wchar_t const volatile (&string)[capacity]) noexcept(noexcept(flush(instanceof<std::FILE*>(), instanceof<wchar_t const (&)[capacity]>()))) {
  return flush(stream, const_cast<wchar_t const (&)[capacity]>(string));
}

template <std::size_t capacity>
constexpr std::size_t flush(std::FILE *const stream, wchar_t volatile (&string)[capacity]) noexcept(noexcept(flush(instanceof<std::FILE*>(), instanceof<wchar_t const (&)[capacity]>()))) {
  return flush(stream, const_cast<wchar_t const (&)[capacity]>(string));
}

// ... --> print(...)
template <typename char_t = void, unsigned long long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t, char>::type, 2u> print(char const character) noexcept {
  return string::concatenate(string::stringify<typename string::resolve_t<char_t, char>::type>(character), string::stringify<typename string::resolve_t<char_t, char>::type>('\0'));
}

template <typename char_t = void, unsigned long long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t, char16_t>::type, 2u> print(char16_t const character) noexcept {
  return string::concatenate(string::stringify<typename string::resolve_t<char_t, char16_t>::type>(character), string::stringify<typename string::resolve_t<char_t, char16_t>::type>(u'\0'));
}

template <typename char_t = void, unsigned long long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t, char32_t>::type, 2u> print(char32_t const character) noexcept {
  return string::concatenate(string::stringify<typename string::resolve_t<char_t, char32_t>::type>(character), string::stringify<typename string::resolve_t<char_t, char32_t>::type>(U'\0'));
}

template <typename char_t = void, unsigned long long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t, long double>::type, 2u + LDBL_DIG + LDBL_MANT_DIG> print(long double const number) noexcept {
  return string::trim_begin(string::trim_end(string::trim_end(string::stringify<typename string::resolve_t<char_t, long double>::type, radix, 0u, 0u>(number), string::stringify<typename string::resolve_t<char_t, long double>::type>('*')), string::stringify<typename string::resolve_t<char_t, long double>::type>('*')), string::stringify<typename string::resolve_t<char_t, long double>::type>('0'));
}

template <typename char_t = void, unsigned long long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t, unsigned long long>::type, countof<ULLONG_MAX, radix>::value> print(unsigned long long const integer) noexcept {
  return string::trim_begin(string::stringify<typename string::resolve_t<char_t, unsigned long long>::type, radix, 0u>(integer), string::stringify<typename string::resolve_t<char_t, unsigned long long>::type>('0'));
}

template <typename char_t = void, unsigned long long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t, signed long long>::type, 1u + countof<ULLONG_MAX, radix>::value> print(signed long long const integer) noexcept {
  return 0LL > integer ? string::concatenate(string::stringify<typename string::resolve_t<char_t, signed long long>::type>('-'), print<char_t, radix>(static_cast<unsigned long long>(-integer))) : string::resize<typename string::resolve_t<char_t, signed long long>::type, 1u + countof<ULLONG_MAX, radix>::value>(print<char_t, radix>(static_cast<unsigned long long>(integer)));
}

template <typename char_t = void, unsigned long long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t, wchar_t>::type, 2u> print(wchar_t const character) noexcept {
  return string::concatenate(string::stringify<typename string::resolve_t<char_t, wchar_t>::type>(character), string::stringify<typename string::resolve_t<char_t, wchar_t>::type>(L'\0'));
}

#if __cplusplus >= 202002L
  template <typename char_t = void, unsigned long long radix = 10u>
  constexpr string_t<typename string::resolve_t<char_t, char8_t>::type, 2u> print(char8_t const character) noexcept {
    return string::concatenate(string::stringify<typename string::resolve_t<char_t, char8_t>::type>(character), string::stringify<typename string::resolve_t<char_t, char8_t>::type>(u8'\0'));
  }
#endif

// ...
template <typename char_t = void, unsigned int radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, 1u + countof<UINT_MAX, radix>::value> print(int const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, 1u + countof<UINT_MAX, radix>::value>(print<char_t, radix>(static_cast<signed long long>(integer)));
}

template <typename char_t = void, unsigned long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, 1u + countof<ULONG_MAX, radix>::value> print(long const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, 1u + countof<ULONG_MAX, radix>::value>(print<char_t, radix>(static_cast<signed long long>(integer)));
}

template <typename char_t = void, unsigned short radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, 1u + countof<USHRT_MAX, radix>::value> print(short const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, 1u + countof<USHRT_MAX, radix>::value>(print<char_t, radix>(static_cast<signed long long>(integer)));
}

template <typename char_t = void, unsigned char radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, 1u + countof<UCHAR_MAX, radix>::value> print(signed char const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, 1u + countof<UCHAR_MAX, radix>::value>(print<char_t, radix>(static_cast<signed long long>(integer)));
}

template <typename char_t = void, unsigned char radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, countof<UCHAR_MAX, radix>::value> print(unsigned char const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, countof<UCHAR_MAX, radix>::value>(print<char_t, radix>(static_cast<unsigned long long>(integer)));
}

template <typename char_t = void, unsigned int radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, countof<UINT_MAX, radix>::value> print(unsigned int const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, countof<UINT_MAX, radix>::value>(print<char_t, radix>(static_cast<unsigned long long>(integer)));
}

template <typename char_t = void, unsigned long radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, countof<ULONG_MAX, radix>::value> print(unsigned long const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, countof<ULONG_MAX, radix>::value>(print<char_t, radix>(static_cast<unsigned long long>(integer)));
}

template <typename char_t = void, unsigned short radix = 10u>
constexpr string_t<typename string::resolve_t<char_t>::type, countof<USHRT_MAX, radix>::value> print(unsigned short const integer) noexcept {
  return string::resize<typename string::resolve_t<char_t>::type, countof<USHRT_MAX, radix>::value>(print<char_t, radix>(static_cast<unsigned long long>(integer)));
}

/* Main -->
  --- WARN ---
    Decimal characteristic length must be constrained to `DBL_DIG`, `FLT_DIG`, & `LDBL_DIG` respectively at compile-time
*/
constexpr static char               character              = 'A';
constexpr static char16_t           largeUnicodeCharacter  = u'A';
constexpr static char32_t           largerUnicodeCharacter = U'A';
// constexpr static double             largeNumber            = 179769313486231570.81452742373170435679807056752584499659891747680315726;
// constexpr static float              number                 = 340282346638528859.81170418348451692544f;
constexpr static long double        largerNumber           = 118973149535723176.5021263853030970205169063322294624200440323733891737005522970722L;
constexpr static signed char        smallerNegativeInteger = -127;
constexpr static signed int         negativeInteger        = -127;
constexpr static signed long        largeNegativeInteger   = -127L;
constexpr static signed long long   largerNegativeInteger  = -127LL;
constexpr static signed short       smallNegativeInteger   = -127;
constexpr static unsigned char      smallerPositiveInteger = 127u;
constexpr static unsigned int       positiveInteger        = 127u;
constexpr static unsigned long      largePositiveInteger   = 127uL;
constexpr static unsigned long long largerPositiveInteger  = 127uLL;
constexpr static unsigned short     smallPositiveInteger   = 127u;
constexpr static wchar_t            wideCharacter          = L'A';
#if __cplusplus >= 202002L
  constexpr static char8_t unicodeCharacter = u8'A';
#endif

int main() noexcept {
  constexpr auto characterBuffer              = print(character);
  constexpr auto largeNegativeIntegerBuffer   = print(largeNegativeInteger);
  constexpr auto largePositiveIntegerBuffer   = print(largePositiveInteger);
  constexpr auto largeUnicodeCharacterBuffer  = print(largeUnicodeCharacter);
  constexpr auto largerNegativeIntegerBuffer  = print(largerNegativeInteger);
  constexpr auto largerNumberBuffer           = print(largerNumber);
  constexpr auto largerPositiveIntegerBuffer  = print(largerPositiveInteger);
  constexpr auto largerUnicodeCharacterBuffer = print(largerUnicodeCharacter);
  constexpr auto negativeIntegerBuffer        = print(negativeInteger);
  constexpr auto positiveIntegerBuffer        = print(positiveInteger);
  constexpr auto smallNegativeIntegerBuffer   = print(smallNegativeInteger);
  constexpr auto smallPositiveIntegerBuffer   = print(smallPositiveInteger);
  constexpr auto smallerNegativeIntegerBuffer = print(smallerNegativeInteger);
  constexpr auto smallerPositiveIntegerBuffer = print(smallerPositiveInteger);
  constexpr auto wideCharacterBuffer          = print(wideCharacter);
  #if __cplusplus >= 202002L
    constexpr auto unicodeCharacterBuffer = print(unicodeCharacter);
  #endif

  // ...
  std::setbuf(stdout, NULL);
  // std::printf("[]: %f" "\r\n", FLT_MAX);
  // std::printf("[]: %lf" "\r\n", DBL_MAX);
  // std::printf("[]: %Lf" "\r\n", LDBL_MAX);
  std::printf("[char]              : (%u) \"", static_cast<unsigned>(sizeof characterBuffer));              flush(characterBuffer);              std::printf("%3s", "\"" "\r\n");
  std::printf("[char16_t]          : (%u) \"", static_cast<unsigned>(sizeof largeUnicodeCharacterBuffer));  flush(largeUnicodeCharacterBuffer);  std::printf("%3s", "\"" "\r\n");
  std::printf("[char32_t]          : (%u) \"", static_cast<unsigned>(sizeof largerUnicodeCharacterBuffer)); flush(largerUnicodeCharacterBuffer); std::printf("%3s", "\"" "\r\n");
  std::printf("[long double]       : (%u) \"", static_cast<unsigned>(sizeof largerNumberBuffer));           flush(largerNumberBuffer);           std::printf("%3s", "\"" "\r\n");
  std::printf("[signed char]       : (%u) \"", static_cast<unsigned>(sizeof smallerNegativeIntegerBuffer)); flush(smallerNegativeIntegerBuffer); std::printf("%3s", "\"" "\r\n");
  std::printf("[signed int]        : (%u) \"", static_cast<unsigned>(sizeof negativeIntegerBuffer));        flush(negativeIntegerBuffer);        std::printf("%3s", "\"" "\r\n");
  std::printf("[signed long]       : (%u) \"", static_cast<unsigned>(sizeof largeNegativeIntegerBuffer));   flush(largeNegativeIntegerBuffer);   std::printf("%3s", "\"" "\r\n");
  std::printf("[signed long long]  : (%u) \"", static_cast<unsigned>(sizeof largerNegativeIntegerBuffer));  flush(largerNegativeIntegerBuffer);  std::printf("%3s", "\"" "\r\n");
  std::printf("[signed short]      : (%u) \"", static_cast<unsigned>(sizeof smallNegativeIntegerBuffer));   flush(smallNegativeIntegerBuffer);   std::printf("%3s", "\"" "\r\n");
  std::printf("[unsigned char]     : (%u) \"", static_cast<unsigned>(sizeof smallerPositiveIntegerBuffer)); flush(smallerPositiveIntegerBuffer); std::printf("%3s", "\"" "\r\n");
  std::printf("[unsigned int]      : (%u) \"", static_cast<unsigned>(sizeof positiveIntegerBuffer));        flush(positiveIntegerBuffer);        std::printf("%3s", "\"" "\r\n");
  std::printf("[unsigned long]     : (%u) \"", static_cast<unsigned>(sizeof largePositiveIntegerBuffer));   flush(largePositiveIntegerBuffer);   std::printf("%3s", "\"" "\r\n");
  std::printf("[unsigned long long]: (%u) \"", static_cast<unsigned>(sizeof largerPositiveIntegerBuffer));  flush(largerPositiveIntegerBuffer);  std::printf("%3s", "\"" "\r\n");
  std::printf("[unsigned short]    : (%u) \"", static_cast<unsigned>(sizeof smallPositiveIntegerBuffer));   flush(smallPositiveIntegerBuffer);   std::printf("%3s", "\"" "\r\n");
  std::printf("[wchar_t]           : (%u) \"", static_cast<unsigned>(sizeof wideCharacterBuffer));          flush(wideCharacterBuffer);          std::printf("%3s", "\"" "\r\n");
  #if __cplusplus >= 202002L
    std::printf("[char8_t]           : (%u) \"", static_cast<unsigned>(sizeof unicodeCharacterBuffer)); flush(unicodeCharacterBuffer); std::printf("%3s", "\"" "\r\n");
  #endif
}
