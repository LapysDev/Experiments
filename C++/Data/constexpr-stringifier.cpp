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
  constexpr static long double clamp(long double const number, long double const maximum) noexcept {
    return number < maximum ? number : maximum;
  }

  constexpr static unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) noexcept {
    return integer < maximum ? integer : maximum;
  }

  // ...
  template <typename type>
  constexpr static type instanceof() noexcept;

  // ...
  constexpr static long double ipow(long double const number, unsigned long long exponent) noexcept {
    return 0uLL != exponent ? number * ipow(number, exponent - 1uLL) : 1.0L;
  }

  constexpr static unsigned long long ipow(unsigned long long const number, unsigned long long exponent) noexcept {
    return 0uLL != exponent ? number * ipow(number, exponent - 1uLL) : 1uLL;
  }

  // ...
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
namespace string {
  template <typename...>
  union assess_types;

  template <typename, typename...>
  union resolve_t;

  template <typename, std::size_t>
  union string_t;
}

namespace string {
  template <typename char_t, std::size_t offsetA, std::size_t offsetB, std::size_t capacityA, std::size_t capacityB>
  constexpr typename conditional_t<0u == capacityA || 0u == capacityB || (capacityA <= offsetA || capacityB <= offsetB), bool>::type compare(string_t<char_t, capacityA> const&, string_t<char_t, capacityB> const&) {
    return false;
  }

  template <typename char_t, std::size_t offsetA, std::size_t offsetB, std::size_t capacityA, std::size_t capacityB>
  constexpr typename conditional_t<0u != capacityA && 0u != capacityB && (capacityA > offsetA && capacityB > offsetB), bool>::type compare(string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB) {
    return stringA.value[offsetA] == stringB.value[offsetB] && (
      (capacityA > offsetA || capacityB > offsetB) ||
      compare<char_t, capacityA, capacityB, offsetA + 1u, offsetB + 1u>(stringA, stringB)
    );
  }

  // ...
  template <typename char_t, std::size_t capacity>
  constexpr string_t<char_t, capacity> const& concatenate(string_t<char_t, capacity> const& string) noexcept {
    return string;
  }

  template <typename char_t>
  constexpr string_t<char_t, 0u> concatenate(string_t<char_t, 0u> const, string_t<char_t, 0u> const) noexcept {
    return {};
  }

  template <typename char_t, std::size_t capacity>
  constexpr string_t<char_t, capacity> const& concatenate(string_t<char_t, 0u> const, string_t<char_t, capacity> const& string) noexcept {
    return string;
  }

  template <typename char_t, std::size_t capacity>
  constexpr string_t<char_t, capacity> const& concatenate(string_t<char_t, capacity> const& string, string_t<char_t, 0u> const) noexcept {
    return string;
  }

  template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... indexesA, std::size_t... indexesB>
  constexpr string_t<char_t, capacityA + capacityB> concatenate(index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const, string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB) noexcept {
    return {stringA.value[indexesA]..., stringB.value[indexesB]...};
  }

  template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
  constexpr string_t<char_t, capacityA + capacityB + integer_collection<capacities...>::total> concatenate(string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB, string_t<char_t, capacities> const&... strings) noexcept {
    return concatenate(concatenate(index_sequence<capacityA>(), index_sequence<capacityB>(), stringA, stringB), strings...);
  }

  // ...
  template <typename char_t, std::size_t length, std::size_t capacity>
  constexpr typename conditional_t<capacity == length, string_t<char_t, length> const&>::type resize(string_t<char_t, capacity> const& string) noexcept {
    return string;
  }

  template <typename char_t, std::size_t length, std::size_t capacity>
  constexpr typename conditional_t<capacity != length, string_t<char_t, length> >::type resize(string_t<char_t, capacity> const& string) noexcept {
    return {string};
  }

  // ...
  template <typename char_t>
  constexpr string_t<char_t, 0u> const reverse(string_t<char_t, 0u> const string) noexcept {
    return string;
  }

  template <typename char_t>
  constexpr string_t<char_t, 1u> const& reverse(string_t<char_t, 1u> const& string) noexcept {
    return string;
  }

  template <typename char_t, std::size_t capacity, std::size_t... indexes>
  constexpr string_t<char_t, capacity> reverse(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
    return {string.value[capacity - indexes - 1u]...};
  }

  template <typename char_t, std::size_t capacity>
  constexpr string_t<char_t, capacity> reverse(string_t<char_t, capacity> const& string) noexcept {
    return reverse(index_sequence<capacity>(), string);
  }

  // ...
  template <typename char_t, std::size_t count, std::size_t capacity>
  constexpr typename conditional_t<(capacity <= count), string_t<char_t, 0u> >::type slice_begin(string_t<char_t, capacity> const&) noexcept {
    return {};
  }

  template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
  constexpr typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_begin(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
    return {string.value[count + indexes]...};
  }

  template <typename char_t, std::size_t count, std::size_t capacity>
  constexpr typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_begin(string_t<char_t, capacity> const& string) noexcept {
    return slice_begin<char_t, count>(index_sequence<capacity - count>(), string);
  }

  // ...
  template <typename char_t, std::size_t count, std::size_t capacity>
  constexpr typename conditional_t<(capacity <= count), string_t<char_t, 0u> >::type slice_end(string_t<char_t, capacity> const&) noexcept {
    return {};
  }

  template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
  constexpr typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_end(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
    return {string.value[indexes]...};
  }

  template <typename char_t, std::size_t count, std::size_t capacity>
  constexpr typename conditional_t<(capacity > count), string_t<char_t, capacity - count> >::type slice_end(string_t<char_t, capacity> const& string) noexcept {
    return slice_end<char_t, count>(index_sequence<capacity - count>(), string);
  }

  // ...
  template <typename char_t, std::size_t count, std::size_t capacity>
  constexpr typename conditional_t<(capacity <= count * 2u), string_t<char_t, 0u> >::type slice(string_t<char_t, capacity> const&) noexcept {
    return {};
  }

  template <typename char_t, std::size_t count, std::size_t capacity>
  constexpr typename conditional_t<(capacity > count * 2u), string_t<char_t, capacity - (count * 2u)> >::type slice(string_t<char_t, capacity> const& string) noexcept {
    return slice_begin<char_t, count, capacity - count>(slice_end<char_t, count, capacity>(string));
  }

  // ...
  template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
  constexpr typename conditional_t<(capacity < searchCapacity || 0u == searchCapacity), string_t<char_t, capacity> const&>::type trim_begin(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const&) noexcept {
    return string;
  }

  template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
  constexpr typename conditional_t<(capacity >= searchCapacity), string_t<char_t, capacity> >::type trim_begin(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
    return compare<char_t, 0u, 0u>(string, search) ? resize<char_t, capacity>(trim_begin<char_t, capacity - searchCapacity, searchCapacity>(slice_begin<char_t, searchCapacity>(string), search)) : string;
  }

  // ...
  template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
  constexpr typename conditional_t<(capacity < searchCapacity || 0u == searchCapacity), string_t<char_t, capacity> const&>::type trim_end(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const&) noexcept {
    return string;
  }

  template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
  constexpr typename conditional_t<(capacity >= searchCapacity), string_t<char_t, capacity> >::type trim_end(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
    return compare<char_t, capacity - searchCapacity, 0u>(string, search) ? resize<char_t, capacity>(trim_end<char_t, capacity - searchCapacity, searchCapacity>(slice_end<char_t, searchCapacity>(string), search)) : string;
  }

  // ...
  template <typename char_t, std::size_t capacity, std::size_t searchCapacity>
  constexpr string_t<char_t, capacity> trim(string_t<char_t, capacity> const& string, string_t<char_t, searchCapacity> const& search) noexcept {
    return trim_begin<char_t, capacity, searchCapacity>(trim_end<char_t, capacity, searchCapacity>(string, search), search);
  }
}

namespace string {
  template <typename char_t, std::size_t length>
  union string_t {
    template <typename, std::size_t>
    friend union string_t;

    private:
      typedef char_t const (&type)[length];
      char_t const value[length];

      // ... ->> empty string
      template <std::size_t... indexes>
      constexpr string_t(index_sequence<0u, indexes...> const) noexcept(noexcept(char_t('\0'))) :
        value{"\0"[indexes - indexes]...}
      {}

      // ... ->> equal string
      template <std::size_t... indexes>
      constexpr string_t(index_sequence<0u, indexes...> const, string_t<char_t, length> const& string) noexcept(noexcept(char_t(instanceof<char_t const&>()))) :
        value{string.value[indexes]...}
      {}

      // ... ->> smaller string
      template <std::size_t capacity, std::size_t... nulIndexes, std::size_t... indexes>
      constexpr string_t(index_sequence<0u, nulIndexes...> const, index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept(noexcept(char_t('\0')) && noexcept(char_t(instanceof<char_t const&>()))) :
        value{string.value[indexes]..., "\0"[nulIndexes - nulIndexes]...}
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
        value{character, characters...}
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
}

using string::string_t;


/* Main */
int main() noexcept {
  constexpr auto number  = string::trim<char>(string_t<char, 10u>('0', '0', '0', '0', '4', '2', '0', '0', '0', '0'), string_t<char, 1u>('0'));
  constexpr auto reverse = string::reverse<char>(string_t<char, 11u>('L', 'o', 'r', 'e', 'm', ' ', 'i', 'p', 's', 'u', 'm'));
  constexpr auto string  = string::concatenate<char>(string_t<char, 5u>('H', 'e', 'l', 'l', 'o'), string_t<char, 2u>(',', ' '), string_t<char, 7u>('W', 'o', 'r', 'l', 'd', '!'));

  // ...
  std::printf("[]: \"%1.*s\"" "\r\n", sizeof(number ) / sizeof(char), static_cast<char const*>(number));
  std::printf("[]: \"%1.*s\"" "\r\n", sizeof(reverse) / sizeof(char), static_cast<char const*>(reverse));
  std::printf("[]: \"%1.*s\"" "\r\n", sizeof(string ) / sizeof(char), static_cast<char const*>(string));
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
