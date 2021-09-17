#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>

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
  template <typename> union remove_const;
  template <typename> union remove_cv;
  template <typename> union remove_volatile;

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
  template <typename type>
  union is_character {
    enum {
      value = (
        is_same<char    , typename remove_cv<type>::type>::value ||
        is_same<char16_t, typename remove_cv<type>::type>::value ||
        is_same<char32_t, typename remove_cv<type>::type>::value ||
        is_same<wchar_t , typename remove_cv<type>::type>::value ||
        #if __cplusplus >= 202002L
          is_same<char8_t, typename remove_cv<type>::type>::value ||
        #endif

        false
      )
    };
  };

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

  // ...
  template <typename base>
  union remove_const { typedef base type; };

  template <typename base>
  union remove_const<base const> { typedef base type; };

  // ...
  template <typename base>
  union remove_cv {
    typedef typename remove_const<typename remove_volatile<base>::type>::type type;
  };

  // ...
  template <typename base>
  union remove_volatile { typedef base type; };

  template <typename base>
  union remove_volatile<base volatile> { typedef base type; };
}

namespace {
  // ... --> clamp(…)
  constexpr static long double clamp(long double const number, long double const maximum) noexcept {
    return number < maximum ? number : maximum;
  }

  constexpr static unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) noexcept {
    return integer < maximum ? integer : maximum;
  }

  // ... --> forward(…)
  template <typename type>
  constexpr static type& forward(type& reference) noexcept {
    return reference;
  }

  template <typename type>
  constexpr static type&& forward(type&& reference) noexcept {
    return reference;
  }

  // ... --> instanceof()
  template <typename type>
  constexpr static type instanceof() noexcept;

  // ... --> ipow(…)
  constexpr static long double ipow(long double const number, unsigned long long exponent) noexcept {
    return 0uLL != exponent ? number * ipow(number, exponent - 1uLL) : 1.0L;
  }

  constexpr static unsigned long long ipow(unsigned long long const number, unsigned long long exponent) noexcept {
    return 0uLL != exponent ? number * ipow(number, exponent - 1uLL) : 1uLL;
  }

  // ... --> lengthof(…)
  template <unsigned long long radix>
  constexpr static unsigned short lengthof(long double const number, unsigned long long base = radix, unsigned char const count = 1u) noexcept {
    return 0.1L < number ? count + (
      base < ULLONG_MAX / ULONG_MAX && 1.0L < number / (base * base)
      ? lengthof<radix>(number / (base * base ), base * base , 2u * count) :

      base < ULLONG_MAX / radix     && 1.0L < number / (base * radix)
      ? lengthof<radix>(number / (base * radix), base * radix, 1u + count) :

      lengthof<radix>(number / radix, radix, 1u)
    ) : 0u;
  }

  template <unsigned long long radix>
  constexpr static unsigned char lengthof(unsigned long long const integer) noexcept {
    return 0uLL != integer ? 1u + lengthof<radix>(integer / radix) : 0u;
  }
}

/* ... [Interface] */
union string {
  private:
    template <typename...> union assess_types;
    template <typename, typename...> union resolve_t;

  public:
    template <typename, std::size_t>
    union string_t;

  /* ... */
  private:
    // ... --> concatenate(…)
    template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... indexesA, std::size_t... indexesB>
    constexpr static string_t<char_t, capacityA + capacityB> concatenate(index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const, string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB) noexcept {
      return {stringA.value[indexesA]..., stringB.value[indexesB]...};
    }

    // ... --> convert(…)
    template <typename char_t> // --> bool
    constexpr static string_t<char_t, 5u> convert(bool const boolean) noexcept {
      return boolean ? string_t<char_t, 5u>('t', 'r', 'u', 'e', '\0') : string_t<char_t, 5u>('f', 'a', 'l', 's', 'e');
    }

    template <typename char_t> // --> char
    constexpr static string_t<char_t, 1u> convert(char_t const& character) noexcept {
      return {character};
    }

    template <typename char_t, std::size_t capacity, std::size_t... indexes> // --> char []
    constexpr static string_t<char_t, capacity> convert(index_sequence<0u, indexes...> const, char_t const (&string)[capacity]) noexcept {
      return {string[indexes]...};
    }

    #if __cplusplus >= 201402L // --> long double
    #else
    #endif

    #if __cplusplus >= 201402L // --> unsigned long long
      template <typename char_t, unsigned long long radix, unsigned char, std::size_t... indexes>
      constexpr static string_t<char_t, countof<ULLONG_MAX, radix>::value> convert(index_sequence<0u, indexes...> const, unsigned long long integer, unsigned long long factor) noexcept {
        char string[] = {"\0"[indexes - indexes]...};

        for (char *iterator = string; 0uLL != integer; ++iterator) {
          *iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(integer / factor, 36uLL)];
          integer -= factor * (integer / factor);
          factor /= radix;
        }

        return {string[indexes]...};
      }

      template <typename char_t, unsigned long long radix, unsigned char>
      constexpr static string_t<char_t, countof<ULLONG_MAX, radix>::value> convert(unsigned long long const integer, unsigned long long const factor) noexcept {
        return convert<char_t, radix, 0u>(index_sequence<countof<ULLONG_MAX, radix>::value>(), integer, factor);
      }
    #else
      template <typename char_t, unsigned long long radix, unsigned char count>
      constexpr static typename conditional_t<count == countof<ULLONG_MAX, radix>::value, string_t<char_t, countof<ULLONG_MAX, radix>::value> >::type convert(unsigned long long const, unsigned long long const, string_t<char_t, count> const& string = {}) noexcept {
        return string;
      }

      template <typename char_t, unsigned long long radix, unsigned char count>
      constexpr static typename conditional_t<count != countof<ULLONG_MAX, radix>::value, string_t<char_t, countof<ULLONG_MAX, radix>::value> >::type convert(unsigned long long const integer, unsigned long long const factor, string_t<char_t, count> const& string = {}) noexcept {
        return 0uLL == integer ? resize<char_t, countof<ULLONG_MAX, radix>::value>(string) : convert<char_t, radix, count + 1u>(
          integer - (factor * (integer / factor)), factor / radix,
          concatenate<char_t>(string, convert<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(integer / factor, 36uLL)]))
        );
      }
    #endif

    // ... --> reverse(…)
    template <typename char_t, std::size_t capacity, std::size_t... indexes>
    constexpr static string_t<char_t, capacity> reverse(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
      return {string.value[capacity - indexes - 1u]...};
    }

    // ... --> slice_begin(…)
    template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
    constexpr static typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_begin(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
      return {string.value[count + indexes]...};
    }

    // ... --> slice_end(…)
    template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
    constexpr static typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_end(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
      return {string.value[indexes]...};
    }

  public:
    // ... --> compare(…)
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

    // ... --> concatenate(…)
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

    template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
    constexpr static string_t<char_t, capacityA + capacityB + integer_collection<capacities...>::total> concatenate(string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB, string_t<char_t, capacities> const&... strings) noexcept {
      return concatenate(concatenate(index_sequence<capacityA>(), index_sequence<capacityB>(), stringA, stringB), strings...);
    }

    // ... --> resize(…)
    template <typename char_t, std::size_t length, std::size_t capacity>
    constexpr static typename conditional_t<capacity == length, string_t<char_t, length> const&>::type resize(string_t<char_t, capacity> const& string) noexcept {
      return string;
    }

    template <typename char_t, std::size_t length, std::size_t capacity>
    constexpr static typename conditional_t<capacity != length, string_t<char_t, length> >::type resize(string_t<char_t, capacity> const& string) noexcept {
      return {string};
    }

    // ... --> reverse(…)
    template <typename char_t>
    constexpr static string_t<char_t, 0u> const reverse(string_t<char_t, 0u> const string) noexcept {
      return string;
    }

    template <typename char_t>
    constexpr static string_t<char_t, 1u> const& reverse(string_t<char_t, 1u> const& string) noexcept {
      return string;
    }

    template <typename char_t, std::size_t capacity>
    constexpr static string_t<char_t, capacity> reverse(string_t<char_t, capacity> const& string) noexcept {
      return reverse(index_sequence<capacity>(), string);
    }

    // ... --> slice_begin(…)
    template <typename char_t, std::size_t count, std::size_t capacity>
    constexpr static typename conditional_t<(capacity <= count), string_t<char_t, 0u> >::type slice_begin(string_t<char_t, capacity> const&) noexcept {
      return {};
    }

    template <typename char_t, std::size_t count, std::size_t capacity>
    constexpr static typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_begin(string_t<char_t, capacity> const& string) noexcept {
      return slice_begin<char_t, count>(index_sequence<capacity - count>(), string);
    }

    // ... --> slice_end(…)
    template <typename char_t, std::size_t count, std::size_t capacity>
    constexpr static typename conditional_t<(capacity <= count), string_t<char_t, 0u> >::type slice_end(string_t<char_t, capacity> const&) noexcept {
      return {};
    }

    template <typename char_t, std::size_t count, std::size_t capacity>
    constexpr static typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_end(string_t<char_t, capacity> const& string) noexcept {
      return slice_end<char_t, count>(index_sequence<capacity - count>(), string);
    }

    // ... --> slice(…)
    template <typename char_t, std::size_t count, std::size_t capacity>
    constexpr static typename conditional_t<(capacity <= count * 2u), string_t<char_t, 0u> >::type slice(string_t<char_t, capacity> const&) noexcept {
      return {};
    }

    template <typename char_t, std::size_t count, std::size_t capacity>
    constexpr static typename conditional_t<(capacity > count * 2u), string_t<char_t, capacity - (count * 2u)> >::type slice(string_t<char_t, capacity> const& string) noexcept {
      return slice_begin<char_t, count, capacity - count>(slice_end<char_t, count, capacity>(string));
    }

    // ... --> stringify(…)
    template <typename char_t = void, unsigned long long = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, bool>::type, 5u> stringify(bool const boolean) noexcept {
      return convert<typename resolve_t<char_t, bool>::type>(boolean);
    }

    template <typename char_t = void, unsigned long long = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, char>::type, 1u> stringify(char const character) noexcept {
      return convert<typename resolve_t<char_t, char>::type>(character);
    }

    template <typename char_t = void, unsigned long long = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, char16_t>::type, 1u> stringify(char16_t const character) noexcept {
      return convert<typename resolve_t<char_t, char16_t>::type>(character);
    }

    template <typename char_t = void, unsigned long long = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, char32_t>::type, 1u> stringify(char32_t const character) noexcept {
      return convert<typename resolve_t<char_t, char32_t>::type>(character);
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, int>::type, 1u + countof<INT_MAX, radix>::value> stringify(int const integer) noexcept {
      return stringify<char_t, radix>(static_cast<long long>(integer));
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, long>::type, 1u + countof<LONG_MAX, radix>::value> stringify(long const integer) noexcept {
      return stringify<char_t, radix>(static_cast<long long>(integer));
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, long double>::type, 2u + LDBL_DIG + LDBL_MANT_DIG> stringify(long double const number) noexcept {
      return (
        0.0L == integer
        ? resize<typename resolve_t<char_t, long double>::type, 2u + LDBL_DIG + LDBL_MANT_DIG>(concatenate(
          convert<typename resolve_t<char_t, long double>::type>('0'),
          convert<typename resolve_t<char_t, long double>::type>('.'),
          convert<typename resolve_t<char_t, long double>::type>('0')
        ))
        : (
          0.0L < integer
          ? concatenate(stringify<typename resolve_t<char_t, long double>::type>('-'), convert<typename resolve_t<char_t, long double>::type, radix, 0u, 0u>(-number, ipow(static_cast<long double>(radix), lengthof<radix>(-number) - 1u))
          : concatenate(convert<typename resolve_t<char_t, long double>::type, radix, 0u, 0u>(+number, ipow(static_cast<long double>(radix), lengthof<radix>(+number) - 1u)), stringify<typename resolve_t<char_t, long long>::type>('\0'))
        ))
      )
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, long long>::type, 1u + countof<LLONG_MAX, radix>::value> stringify(long long const integer) noexcept {
      return (
        0LL > integer
        ? concatenate(stringify<typename resolve_t<char_t, long long>::type>('-'), stringify<char_t, radix>(static_cast<unsigned long long>(-integer)))
        : concatenate(stringify<char_t, radix>(static_cast<unsigned long long>(integer)), stringify<typename resolve_t<char_t, long long>::type>('\0'))
      );
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, short>::type, 1u + countof<SHRT_MAX, radix>::value> stringify(short const integer) noexcept {
      return stringify<char_t, radix>(static_cast<long long>(integer));
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, signed char>::type, 1u + countof<SCHAR_MAX, radix>::value> stringify(signed char const integer) noexcept {
      return stringify<char_t, radix>(static_cast<long long>(integer));
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, unsigned char>::type, countof<UCHAR_MAX, radix>::value> stringify(unsigned char const integer) noexcept {
      return resize<typename resolve_t<char_t, unsigned char>::type, countof<UCHAR_MAX, radix>::value>(stringify<char_t, radix>(static_cast<unsigned long long>(integer)));
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, unsigned int>::type, countof<UINT_MAX, radix>::value> stringify(unsigned int const integer) noexcept {
      return stringify<char_t, radix>(static_cast<unsigned long long>(integer));
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, unsigned long>::type, countof<ULONG_MAX, radix>::value> stringify(unsigned long const integer) noexcept {
      return stringify<char_t, radix>(static_cast<unsigned long long>(integer));
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, unsigned long long>::type, countof<ULLONG_MAX, radix>::value> stringify(unsigned long long const integer) noexcept {
      return (0uLL == integer
        ? resize<typename resolve_t<char_t, unsigned long long>::type, countof<ULLONG_MAX, radix>::value>(convert<typename resolve_t<char_t, unsigned long long>::type>('0'))
        : convert<typename resolve_t<char_t, unsigned long long>::type, radix, 0u>(integer, ipow(radix, lengthof<radix>(integer) - 1u))
      );
    }

    template <typename char_t = void, unsigned long long radix = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, unsigned short>::type, countof<USHRT_MAX, radix>::value> stringify(unsigned short const integer) noexcept {
      return stringify<char_t, radix>(static_cast<unsigned long long>(integer));
    }

    template <typename char_t = void, unsigned long long = 10uLL>
    constexpr static string_t<typename resolve_t<char_t, wchar_t>::type, 1u> stringify(wchar_t const character) noexcept {
      return convert<typename resolve_t<char_t, wchar_t>::type>(character);
    }

    template <typename char_t, unsigned long long = 10uLL, std::size_t capacity>
    constexpr static string_t<char_t, capacity> stringify(char_t (&string)[capacity]) noexcept {
      return convert<char_t>(index_sequence<capacity>(), const_cast<char_t const (&)[capacity]>(string));
    }

    template <typename char_t, unsigned long long = 10uLL, std::size_t capacity>
    constexpr static string_t<char_t, capacity> stringify(char_t const (&string)[capacity]) noexcept {
      return convert<char_t>(index_sequence<capacity>(), string);
    }

    template <typename char_t, unsigned long long = 10uLL, std::size_t capacity>
    constexpr static string_t<char_t, capacity> stringify(char_t const volatile (&string)[capacity]) noexcept {
      return convert<char_t>(index_sequence<capacity>(), string);
    }

    template <typename char_t, unsigned long long = 10uLL, std::size_t capacity>
    constexpr static string_t<char_t, capacity> stringify(char_t volatile (&string)[capacity]) noexcept {
      return convert<char_t>(index_sequence<capacity>(), const_cast<char_t const volatile (&)[capacity]>(string));
    }

    template <unsigned long long radix = 10uLL, typename typeA, typename typeB, typename... types>
    constexpr static string_t<typename resolve_t<void, typeA, typeB, types...>::type, sizeof(concatenate(
      stringify<typename resolve_t<void, typeA, typeB, types...>::type, radix>(instanceof<typeA const&>()),
      stringify<typename resolve_t<void, typeA, typeB, types...>::type, radix>(instanceof<typeB const&>()),
      stringify<typename resolve_t<void, typeA, typeB, types...>::type, radix>(instanceof<types&&>())...
    )) / sizeof(typename resolve_t<void, typeA, typeB, types...>::type)> stringify(typeA const& objectA, typeB const& objectB, types&&... objects) noexcept {
      return concatenate(
        stringify<typename resolve_t<void, typeA, typeB, types...>::type, radix>(objectA),
        stringify<typename resolve_t<void, typeA, typeB, types...>::type, radix>(objectB),
        stringify<typename resolve_t<void, typeA, typeB, types...>::type, radix>(forward<types>(objects))...
      );
    }

    #if __cplusplus >= 202002L
      template <typename char_t = void> // --> char8_t
      constexpr static string_t<typename resolve_t<char_t, char8_t>::type, 1u> stringify(char8_t const character) noexcept {
        return convert<typename resolve_t<char_t, char8_t>::type>(character);
      }
    #endif

    // ... --> trim(…)
    template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
    constexpr static string_t<char_t, capacity> trim(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
      return trim_begin<char_t, capacity, searchCapacity>(trim_end<char_t, capacity, searchCapacity>(string, search), search);
    }

    // ... --> trim_begin(…)
    template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
    constexpr static typename conditional_t<(capacity < searchCapacity || 0u == searchCapacity), string_t<char_t, capacity> const&>::type trim_begin(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const&) noexcept {
      return string;
    }

    template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
    constexpr static typename conditional_t<(capacity >= searchCapacity), string_t<char_t, capacity> >::type trim_begin(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
      return compare<char_t, 0u, 0u>(string, search) ? resize<char_t, capacity>(trim_begin<char_t, capacity - searchCapacity, searchCapacity>(slice_begin<char_t, searchCapacity>(string), search)) : string;
    }

    // ... --> trim_end(…)
    template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
    constexpr static typename conditional_t<(capacity < searchCapacity || 0u == searchCapacity), string_t<char_t, capacity> const&>::type trim_end(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const&) noexcept {
      return string;
    }

    template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
    constexpr static typename conditional_t<(capacity >= searchCapacity), string_t<char_t, capacity> >::type trim_end(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
      return compare<char_t, capacity - searchCapacity, 0u>(string, search) ? resize<char_t, capacity>(trim_end<char_t, capacity - searchCapacity, searchCapacity>(slice_end<char_t, searchCapacity>(string), search)) : string;
    }

  /* ... */
  private:
    template <typename...>
    union assess_types {
      friend union string;

      private:
        enum { value = 0x00u };
        enum { resolved = false };
    };

    template <typename base, typename... types>
    union assess_types<base, types...> {
      friend union string;

      private:
        enum {
          value = (is_function<base>::value || is_function_pointer<base>::value ? 0x00u : (
            is_same<typename remove_cv<typename baseof<typename baseof<typename baseof<base>::type>::type>::type>::type, char    >::value ? 0x01u :
            is_same<typename remove_cv<typename baseof<typename baseof<typename baseof<base>::type>::type>::type>::type, char16_t>::value ? 0x02u :
            is_same<typename remove_cv<typename baseof<typename baseof<typename baseof<base>::type>::type>::type>::type, char32_t>::value ? 0x04u :
            is_same<typename remove_cv<typename baseof<typename baseof<typename baseof<base>::type>::type>::type>::type, wchar_t >::value ? 0x08u :
            #if __cplusplus >= 202002L
              is_same<typename remove_cv<typename baseof<typename baseof<typename baseof<base>::type>::type>::type>::type, char8_t>::value ? 0x10u :
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
            0x02u == (assess_types<base, types...>::value | assess_types<types...>::value), char16_t,

          typename conditional_t<
            0x04u == (assess_types<base, types...>::value | assess_types<types...>::value), char32_t,

          typename conditional_t<
            0x08u == (assess_types<base, types...>::value | assess_types<types...>::value), wchar_t,

          typename conditional_t<
            #if __cplusplus >= 202002L
              0x10u == (assess_types<base, types...>::value | assess_types<types...>::value), char8_t,
            #else
              false, void,
            #endif
          void >::type >::type >::type >::type >::type
        type;
    };

    // ...
    template <typename base, typename...>
    union resolve_t {
      typedef base type;
    };

    template <typename... types>
    union resolve_t<void, types...> {
      typedef typename conditional_t<
        0x00u == assess_types<types...>::value, // ->> no discernible built-in character type found
        char, typename conditional_t<
          false == assess_types<types...>::resolved, // ->> different built-in character type found
          void_t, typename assess_types<types...>::type // ->> single built-in character type found
        >::type
      >::type type;
    };

  public:
    template <typename char_t, std::size_t length>
    union string_t {
      friend union string;

      template <typename, std::size_t>
      friend union string_t;

      private:
        typedef char_t const (&type)[length];
        char_t const value[length];

        // ... ->> empty string
        template <std::size_t... indexes>
        constexpr string_t(index_sequence<0u, indexes...> const) noexcept(noexcept(char_t('\0'))) :
          value{static_cast<char_t>("\0"[indexes - indexes])...}
        {}

        // ... ->> equal string
        template <std::size_t... indexes>
        constexpr string_t(index_sequence<0u, indexes...> const, string_t<char_t, length> const& string) noexcept(noexcept(char_t(instanceof<char_t const&>()))) :
          value{static_cast<char_t>(string.value[indexes])...}
        {}

        // ... ->> smaller string
        template <std::size_t capacity, std::size_t... nulIndexes, std::size_t... indexes>
        constexpr string_t(index_sequence<0u, nulIndexes...> const, index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept(noexcept(char_t('\0')) && noexcept(char_t(instanceof<char_t const&>()))) :
          value{static_cast<char_t>(string.value[indexes])..., static_cast<char_t>("\0"[nulIndexes - nulIndexes])...}
        {}

      public:
        // ... ->> empty string
        constexpr string_t() noexcept(noexcept(string_t<char_t, length>(index_sequence<length>()))) :
          string_t<char_t, length>::string_t(index_sequence<length>())
        {}

        // ... ->> null string
        constexpr string_t(string_t<char_t, 0u> const) noexcept(noexcept(string_t<char_t, length>())) :
          string_t<char_t, length>::string_t()
        {}

        // ... ->> equal string
        constexpr string_t(string_t<char_t, length> const& string) noexcept(noexcept(string_t<char_t, length>(index_sequence<length>(), instanceof<string_t<char_t, length> const&>()))) :
          string_t<char_t, length>::string_t(index_sequence<length>(), string)
        {}

        // ... ->> bigger string
        template <std::size_t capacity>
        constexpr string_t(string_t<char_t, capacity> const& string, typename conditional_t<(capacity > length), unsigned char>::type const = 0x0u) noexcept(noexcept(string_t<char_t, length>(string::slice_end<char_t, capacity - length>(instanceof<string_t<char_t, capacity> const&>())))) :
          string_t<char_t, length>::string_t(string::slice_end<char_t, capacity - length>(string))
        {}

        // ... ->> smaller string
        template <std::size_t capacity>
        constexpr string_t(string_t<char_t, capacity> const& string, typename conditional_t<(capacity < length), unsigned char>::type const = 0x0u) noexcept(noexcept(string_t<char_t, length>(index_sequence<length - capacity>(), index_sequence<capacity>(), instanceof<string_t<char_t, capacity> const&>()))) :
          string_t<char_t, length>::string_t(index_sequence<length - capacity>(), index_sequence<capacity>(), string)
        {}

        // ... ->> equal character-by-character
        template <typename... chars_t>
        constexpr string_t(typename conditional_t<length == 1u + sizeof...(chars_t) && (is_same<char, chars_t...>::value || is_same<char_t, chars_t...>::value), char_t>::type const& character, chars_t const&... characters) noexcept(noexcept(char_t(instanceof<char_t const&>()))) :
          value{static_cast<char_t>(character), static_cast<char_t>(characters)...}
        {}

        // ... ->> more/ less character-by-character
        template <typename... chars_t>
        constexpr string_t(typename conditional_t<length != 1u + sizeof...(chars_t) && (is_same<char, chars_t...>::value || is_same<char_t, chars_t...>::value), char_t>::type const& character, chars_t const&... characters) noexcept(noexcept(string_t<char_t, length>(instanceof<string_t<char_t, 1u + sizeof...(chars_t)> const&>()))) :
          string_t<char_t, length>::string_t(string_t<char_t, 1u + sizeof...(chars_t)>(character, characters...))
        {}

        // ...
        constexpr operator string_t<char_t, length>::type() const noexcept {
          return this -> value;
        }
    };

    template <typename char_t>
    union string_t<char_t, 0u> {
      template <typename, std::size_t>
      friend union string_t;

      public:
        constexpr string_t(...) noexcept {}
        constexpr explicit operator char_t const*() const = delete;
    };
};

/* Main */
int main() {
  constexpr auto string = string::stringify(false, '[', static_cast<unsigned char>(1u), static_cast<signed char>(-1), 1uLL, -1LL, "]" "Hello, World!");

  std::fprintf(stdout, "[]: (%u) \"", static_cast<unsigned>(sizeof(string) / sizeof(char const)));
  std::fwrite(static_cast<char const*>(string), sizeof(char const), sizeof(string) / sizeof(char const), stdout);
  std::fputc('"', stdout);
}

// template <unsigned long long radix>
// void print(long double const number, long double const factor) noexcept {
//   if (0.1L < number) {
//     std::putchar("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(number / factor, 36.0L))]);
//     print<radix>(number - (factor * static_cast<unsigned char>(number / factor)), factor / radix);
//   }
// }

// template <unsigned long long radix>
// void print(long double const number) noexcept {
//   return print<radix>(number, ipow(static_cast<long double>(radix), lengthof<radix>(number) - 2u));
// }
