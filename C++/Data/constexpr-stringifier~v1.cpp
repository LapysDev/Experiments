#include <cfloat>
#include <climits>
#include <cstdio>

#define MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH 500u /*17u*/

/* ... [Utilities] */
namespace {
  union null {
    union alias {
      union type;
    };

    template <typename base, typename...>
    union trait {
      template <typename...> union typed;
      template <base...> union untyped;
    };
  };

  // ...
  template <bool>
  union conditional;

  template <>
  union conditional<false> {
    template <typename = null::alias::type, typename base = null::alias::type> union alias { typedef base type; };
    template <typename base> union alias<base, null::alias::type>;

    template <typename base, typename... bases>
    union trait {
      template <template <typename...> class = null::trait<base, bases...>::typed, template <typename...> class base = null::trait<base, bases...>::typed> union typed { template <typename... parameters> using type = base<parameters...>; };
      template <template <typename...> class base> union typed<base, null::trait<base, bases...>::typed>;

      template <template <base...> class = null::trait<base, bases...>::untyped, template <base...> class base = null::trait<base, bases...>::untyped> union untyped { template <base... parameters> using type = base<parameters...>; };
      template <template <base...> class base> union untyped<base, null::trait<base, bases...>::untyped>;
    };
  };

  template <>
  union conditional<true> {
    template <typename base = null::alias::type, typename = null::alias::type> union alias { typedef base type; };
    template <typename base> union alias<null::alias::type, base>;

    template <typename base, typename... bases>
    union trait {
      template <template <typename...> class base = null::trait<base, bases...>::typed, template <typename...> class = null::trait<base, bases...>::typed> union typed { template <typename... parameters> using type = base<parameters...>; };
      template <template <typename...> class base> union typed<null::trait<base, bases...>::typed, base>;

      template <template <base...> class base = null::trait<base, bases...>::untyped, template <base...> class = null::trait<base, bases...>::untyped> union untyped { template <base... parameters> using type = base<parameters...>; };
      template <template <base...> class base> union untyped<null::trait<base, bases...>::untyped, base>;
    };
  };

  // ...
  template <typename> union assess_array;
  template <typename> union assess_function;
  template <typename> union assess_pointer;
  template <typename> union assess_reference;
  template <typename> union baseof;
  template <bool...> union boolean_and;
  template <bool...> union boolean_or;
  template <typename type, type...> struct collection;
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
  template <typename> union remove_reference;
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
      typename conditional<is_array<base>::value>::alias<
        typename assess_array<base>::type,
      typename conditional<is_function<base>::value>::alias<
        typename assess_function<base>::type,
      typename conditional<is_pointer<base>::value>::alias<
        typename assess_pointer<base>::type,
      typename conditional<is_reference<base>::value>::alias<
        typename assess_reference<base>::type,
      base >::type >::type >::type >::type
    type;
  };

  // ...
  template <>
  union boolean_and<> {
    enum { value = true };
  };

  template <bool assertion, bool... assertions>
  union boolean_and<assertion, assertions...> {
    enum { value = assertion && boolean_and<assertions...>::value };
  };

  // ...
  template <>
  union boolean_or<> {
    enum { value = false };
  };

  template <bool assertion, bool... assertions>
  union boolean_or<assertion, assertions...> {
    enum { value = assertion || boolean_or<assertions...>::value };
  };

  // ...
  template <typename type, type...>
  struct collection {};
    template <>
    struct integer_collection<> : public collection<std::size_t> {};

    template <std::size_t integer, std::size_t... integers>
    struct integer_collection<integer, integers...> : public collection<std::size_t, integer, integers...> {};
      template <std::size_t count, std::size_t... indexes>
      struct index_sequence : public index_sequence<count - 1u, count - 1u, indexes...> {};

      template <std::size_t... indexes>
      struct index_sequence<0u, indexes...> : public integer_collection<0u, indexes...> {};

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
  union remove_reference {
    typedef typename assess_reference<base>::type type;
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

  // ... --> countof(…)
  template <unsigned long long radix>
  constexpr static unsigned char countof(unsigned long long const integer) noexcept {
    return 0uLL != integer ? 1u + countof<radix>(integer / radix) : 0u;
  }

  template <unsigned long long radix>
  constexpr static unsigned char countof(long long const integer) noexcept {
    return countof<radix>(static_cast<unsigned long long>(0LL > integer ? -integer : integer));
  }

  template <unsigned long long radix>
  constexpr static unsigned short countof(long double const number, unsigned long long base = radix, unsigned char const count = 1u) noexcept {
    return (
      0.0L > number ? countof<radix>(-number, base, count) :
      0.1L < number ? count + (
        base < ULLONG_MAX / ULONG_MAX && 1.0L < number / (base * base)
        ? countof<radix>(number / (base * base ), base * base , 2u * count) :

        base < ULLONG_MAX / radix     && 1.0L < number / (base * radix)
        ? countof<radix>(number / (base * radix), base * radix, 1u + count) :

        countof<radix>(number / radix, radix, 1u)
      ) : 0u
    );
  }

  template <unsigned long long radix> constexpr static unsigned short countof(double const number) noexcept { return countof<radix>(static_cast<long double>(number)); }
  template <unsigned long long radix> constexpr static unsigned short countof(float const number) noexcept { return countof<radix>(static_cast<long double>(number)); }
  template <unsigned long long radix> constexpr static unsigned char countof(int const integer) noexcept { return countof<radix>(static_cast<long long>(integer)); }
  template <unsigned long long radix> constexpr static unsigned char countof(long const integer) noexcept { return countof<radix>(static_cast<long long>(integer)); }
  template <unsigned long long radix> constexpr static unsigned char countof(short const integer) noexcept { return countof<radix>(static_cast<long long>(integer)); }
  template <unsigned long long radix> constexpr static unsigned char countof(signed char const integer) noexcept { return countof<radix>(static_cast<long long>(integer)); }
  template <unsigned long long radix> constexpr static unsigned char countof(unsigned char const integer) noexcept { return countof<radix>(static_cast<unsigned long long>(integer)); }
  template <unsigned long long radix> constexpr static unsigned char countof(unsigned int const integer) noexcept { return countof<radix>(static_cast<unsigned long long>(integer)); }
  template <unsigned long long radix> constexpr static unsigned char countof(unsigned long const integer) noexcept { return countof<radix>(static_cast<unsigned long long>(integer)); }
  template <unsigned long long radix> constexpr static unsigned char countof(unsigned short const integer) noexcept { return countof<radix>(static_cast<unsigned long long>(integer)); }

  // ... --> forward(…)
  template <typename type>
  constexpr static type&& forward(typename remove_reference<type>::type& reference) noexcept {
    return static_cast<type&&>(reference);
  }

  template <typename type>
  constexpr static type&& forward(typename remove_reference<type>::type&& reference) noexcept {
    return reference;
  }

  // ... --> instanceof()
  template <typename type>
  constexpr static type instanceof() noexcept;

  // ... --> sumof(…)
  constexpr static std::size_t sumof() noexcept {
    return 0u;
  }

  template <typename... types>
  constexpr static std::size_t sumof(std::size_t const integer, types&&... integers) noexcept {
    return integer + sumof(forward<types>(integers)...);
  }
}

/* ... [Interface] */
union string {
  private:
    template <bool> union constrained;
    template <typename...> union inspect_types;
    template <typename, typename...> union resolve_t;

  public:
    template <typename, std::size_t>
    union string_t;

  /* ... */
  private:
  public:

  /* ... */
  private:
    template <typename...>
    union inspect_types {
      friend union string;

      private:
        enum { value = 0x00u };
        enum { resolved = false };
    };

    template <typename base, typename... types>
    union inspect_types<base, types...> {
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
          )) | static_cast<unsigned>(inspect_types<types...>::value)
        };

        enum {
          resolved = (
            0x00u != inspect_types<base, types...>::value &&
            0u == (inspect_types<base, types...>::value & (inspect_types<base, types...>::value - 1u))
          )
        };

        // ...
        typedef
          typename conditional<
            0x01u == (inspect_types<base, types...>::value | inspect_types<types...>::value)>::alias<char,

          typename conditional<
            0x02u == (inspect_types<base, types...>::value | inspect_types<types...>::value)>::alias<char16_t,

          typename conditional<
            0x04u == (inspect_types<base, types...>::value | inspect_types<types...>::value)>::alias<char32_t,

          typename conditional<
            0x08u == (inspect_types<base, types...>::value | inspect_types<types...>::value)>::alias<wchar_t,

          typename conditional<
            #if __cplusplus >= 202002L
              0x10u == (inspect_types<base, types...>::value | inspect_types<types...>::value)>::alias<char8_t,
            #else
              false>::alias<void,
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
      typedef typename conditional<
        0x00u == inspect_types<types...>::value>::alias< // ->> no discernible built-in character type found
        char, typename conditional<
          false == inspect_types<types...>::resolved>::alias< // ->> different built-in character type found
          typename null::alias::type, typename inspect_types<types...>::type // ->> single built-in character type found
        >::type
      >::type type;
    };

  public:
    template <typename... types>
    static void print(std::size_t const integer) {
      std::printf("%u", integer);
    }

    template <typename... types>
    static void print(std::size_t const integer, std::size_t const other, types const... others) {
      std::printf("%u, ", integer);
      print(other, others...);
    }

    template <typename char_t, std::size_t length>
    union string_t {
      friend union string;

      template <typename, std::size_t>
      friend union string_t;

      private:
        typedef char_t const (&type)[length];
        char_t const value[length];

        // ...
        template <std::size_t capacity, std::size_t... indexes>
        constexpr string_t(string_t<char_t, capacity> const& string, integer_collection<indexes...> const) noexcept :
          value{string.value[indexes]...}
        {}

        template <std::size_t capacity, std::size_t... range, std::size_t... ranges, std::size_t... indexes>
        string_t(
          string_t<char_t, capacity> const& string,
          integer_collection<indexes...> const,
          index_sequence<0u, range...> const&,
          index_sequence<ranges> const&... sequences
        ) noexcept :
          string_t<char_t, length>::string_t(
            string, integer_collection<indexes..., (range + sizeof...(indexes))...>(), sequences...
          )
        {
          std::printf("%4s", "[]: ");
          print(range...);
          std::printf("%2s", "\r\n");
        }

        template <std::size_t capacity, std::size_t... indexes>
        constexpr string_t(
          typename conditional<false == (length > MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH * (1u + sizeof...(indexes)))>::alias<unsigned char>::type const,
          string_t<char_t, capacity> const& string,
          integer_collection<indexes> const&...
        ) noexcept :
          string_t<char_t, length>::string_t(
            string,
            integer_collection<>(),
            index_sequence<indexes>()...,
            index_sequence<length - (MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH * sizeof...(indexes))>()
          )
        {}

        template <std::size_t capacity, std::size_t... indexes>
        constexpr string_t(
          typename conditional<false != (length > MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH * (1u + sizeof...(indexes)))>::alias<unsigned char>::type const,
          string_t<char_t, capacity> const& string,
          integer_collection<indexes> const&... collections
        ) noexcept :
          string_t<char_t, length>::string_t(
            0x0u, string, collections...,
            integer_collection<MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH>()
          )
        {}

      public:
        template <std::size_t capacity> // ->> unequal string
        constexpr string_t(string_t<char_t, capacity> const& string) noexcept(
          noexcept(string_t<char_t, length>(0x0u, string))
        ) :
          string_t<char_t, length>::string_t(0x0u, string)
        {}

        template <typename... types> // ->> equal character-by-character
        constexpr string_t(
          typename conditional<length == 1u + sizeof...(types)>::alias<
            typename conditional<(MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH > sizeof...(types))>::trait<
              std::
            >::typed<is_same, constrain::is_same>::type<>
          >::type


          typename conditional::alias<length == 1u + sizeof...(types), typename conditional::alias<
          constrain<(MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH > sizeof...(types))>::typed<>::type<is_same, char_t, types...>::value,
          char, typename conditional::alias<
            constrain<(MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH > sizeof...(types))>::typed<>::type<is_same, char, types...>::value,
            char const&
          >::type
        >::type>::type const character, types&&... characters) noexcept(constrain<(MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH > sizeof...(types))>::untyped<bool>::<boolean_and, noexcept(char_t(character)), noexcept(char_t(characters))...>::value) :
          value{static_cast<char_t>(character), static_cast<char_t>(characters)...}
        {}

        template <typename... types> // ->> more/ less character-by-character
        constexpr string_t(typename conditional::alias<length != 1u + sizeof...(types), typename conditional::alias<constrain<(MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH > sizeof...(types))>::typed<>::type<is_same, char_t, types...>::value, char, typename conditional::alias<constrain<(MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH > sizeof...(types))>::typed<>::type<is_same, char, types...>::value, char const&>::type>::type>::type const character, types&&... characters) noexcept(noexcept(string_t<char_t, length>(string_t<char_t, 1u + sizeof...(types)>(character, forward<types>(characters)...)))) :
          string_t<char_t, length>::string_t(
            string_t<char_t, 1u + sizeof...(types)>(character, forward<types>(characters)...)
          )
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
  auto string = string::string_t<char, 13u>('H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!');
  // auto string = string::string_t<char, 1000u>('0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');

  std::fprintf(stdout, "%5s", "[]: \"");
  std::fwrite(static_cast<char const*>(string), sizeof(char const), sizeof(string) / sizeof(char const), stdout);
  std::fputc('"', stdout);
}
