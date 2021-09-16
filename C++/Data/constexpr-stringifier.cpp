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

#include <iostream>
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
  constexpr long double ipow(long double const number, unsigned long long exponent) noexcept {
    return 0uLL != exponent ? number * ipow(number, exponent - 1uLL) : 1.0L;
  }

  constexpr unsigned long long ipow(unsigned long long const number, unsigned long long exponent) noexcept {
    return 0uLL != exponent ? number * ipow(number, exponent - 1uLL) : 1uLL;
  }

  // ...
  template <unsigned long long radix>
  constexpr unsigned short lengthof(long double const number, unsigned long long base = radix, unsigned char const count = 1u) noexcept {
    return 0.1L < number ? count + (
      base < ULLONG_MAX / ULONG_MAX && 1.0L < number / (base * base)
      ? lengthof<radix>(number / (base * base ), base * base , 2u * count) :

      base < ULLONG_MAX / radix     && 1.0L < number / (base * radix)
      ? lengthof<radix>(number / (base * radix), base * radix, 1u + count) :

      lengthof<radix>(number / radix, radix, 1u)
    ) : 0u;
  }

  template <unsigned long long radix>
  constexpr unsigned char lengthof(unsigned long long const integer) noexcept {
    return 0uLL != integer ? 1u + lengthof<radix>(integer / radix) : 0u;
  }

  // ...
  template <unsigned long long radix>
  void print(long double const number, long double const factor) noexcept {
    if (0.1L < number) {
      std::putchar("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(number / factor, 36.0L))]);
      print<radix>(number - (
        factor * static_cast<unsigned char>(number / factor)
      ), factor / radix);
    }
  }

  template <unsigned long long radix>
  void print(long double const number) noexcept {
    return print<radix>(number, ipow(static_cast<long double>(radix), lengthof<radix>(number) - 2u));
  }
}

/* Main */
#include <ostream>

int main() noexcept {
  std::cout << std::fixed << "[]: " << LDBL_MAX << std::endl;

  std::printf("%5s", "[]: \"");
  print<10uLL>(LDBL_MAX);
  std::putchar('"');
}
