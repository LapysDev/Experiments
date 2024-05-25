// Clang: del python.exe && cls && clang++ -pedantic-errors -std=c++11 -Wall -Werror -Wextra -Wno-unused-function -Wno-unused-variable python.cpp -o python.exe && python.exe & del python.exe
// GCC  : del python.exe && cls && g++ -pedantic-errors -std=c++11 -Wall -Werror -Wextra -Wno-unused-variable python.cpp -o python.exe && python.exe & del python.exe
// ICC  : del python.exe python.obj && cls && icl -std=c++11 -w3 -Wall -wd177 -Werror python.cpp -o python.exe && python.exe & del python.exe python.obj
// MSVC : del python.exe python.obj && cls && cl /std:c++14 /W4 /wd4189 /wd4457 /Zc:preprocessor python.cpp && python.exe & del python.exe python.obj
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cuchar>
#include <cwchar>
#include <new>
#include <type_traits>
#include <version>
#include <utility>

/* ... */
namespace {
  template <typename base>
  constexpr char const* type(base&&) noexcept {
    typedef typename std::remove_reference<base>::type type;

    return std::is_array<type>::value ? (
      std::is_same<char, typename std::remove_cv<typename std::remove_extent<type>::type>::type>::value ?
      "<class 'str'>" :

      std::is_same<char16_t, typename std::remove_cv<typename std::remove_extent<type>::type>::type>::value ?
      "<class 'u16str'>" :

      std::is_same<char32_t, typename std::remove_cv<typename std::remove_extent<type>::type>::type>::value ?
      "<class 'u32str'>" :

      std::is_same<wchar_t, typename std::remove_cv<typename std::remove_extent<type>::type>::type>::value ?
      "<class 'wstr'>" :

      #ifdef __cpp_char8_t
        std::is_same<char8_t, typename std::remove_cv<typename std::remove_extent<type>::type>::type>::value ?
        "<class 'u8str'>" :
      #endif

      "<class 'list'>"
    ) :

    std::is_function<typename std::remove_pointer<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'function'>" :

    std::is_pointer<typename std::remove_reference<base>::type>::value ||
    std::is_same<std::nullptr_t, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'ptr'>" :

    std::is_same<bool, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'bool'>" :

    std::is_same<char, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'char'>" :

    std::is_same<char16_t, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'u16char'>" :

    std::is_same<char32_t, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'u32char'>" :

    std::is_same<double,      typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<float,       typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<long double, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'float'>" :

    std::is_same<signed char,      typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<signed int,       typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<signed long,      typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<signed long long, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<signed short,     typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'int'>" :

    std::is_same<unsigned char,      typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<unsigned int,       typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<unsigned long,      typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<unsigned long long, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ||
    std::is_same<unsigned short,     typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'uint'>" :

    std::is_same<wchar_t, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
    "<class 'wchar'>" :

    #ifdef __cpp_char8_t
      std::is_same<char8_t, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value ?
      "<class 'u8char'>" :
    #endif

    NULL;
  }
}

namespace {
  struct any final {
    std::size_t const extent;
    char const *const type;
    void       *const value;
    union {
      unsigned long long const integer;
      void              *const pointer;

      #ifdef __GNUC__
        double      const decimal;
      #else
        long double const decimal;
      #endif
    };

    /* ... */
    constexpr any(double&                             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(double const&                       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(double const volatile&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(double volatile&                    object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(double&&                            object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(double const&&                      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(double const volatile&&             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(double volatile&&                   object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<double&>            (object)) {}
    constexpr any(float&                              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(float const&                        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(float const volatile&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(float volatile&                     object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(float&&                             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(float const&&                       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(float const volatile&&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(float volatile&&                    object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<float&>             (object)) {}
    constexpr any(long double&                        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(long double const&                  object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(long double const volatile&         object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(long double volatile&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(long double&&                       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(long double const&&                 object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(long double const volatile&&        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(long double volatile&&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), decimal(const_cast<long double&>       (object)) {}
    constexpr any(signed char&                        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed char const&                  object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed char const volatile&         object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed char volatile&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed char&&                       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed char const&&                 object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed char const volatile&&        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed char volatile&&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed char&>       (object)) {}
    constexpr any(signed int&                         object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed int const&                   object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed int const volatile&          object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed int volatile&                object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed int&&                        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed int const&&                  object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed int const volatile&&         object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed int volatile&&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed int&>        (object)) {}
    constexpr any(signed long&                        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long const&                  object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long const volatile&         object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long volatile&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long&&                       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long const&&                 object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long const volatile&&        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long volatile&&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long&>       (object)) {}
    constexpr any(signed long long&                   object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed long long const&             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed long long const volatile&    object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed long long volatile&          object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed long long&&                  object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed long long const&&            object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed long long const volatile&&   object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed long long volatile&&         object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed long long&>  (object)) {}
    constexpr any(signed short&                       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(signed short const&                 object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(signed short const volatile&        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(signed short volatile&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(signed short&&                      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(signed short const&&                object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(signed short const volatile&&       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(signed short volatile&&             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<signed short&>      (object)) {}
    constexpr any(unsigned char&                      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned char const&                object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned char const volatile&       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned char volatile&             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned char&&                     object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned char const&&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned char const volatile&&      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned char volatile&&            object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned char&>     (object)) {}
    constexpr any(unsigned int&                       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned int const&                 object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned int const volatile&        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned int volatile&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned int&&                      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned int const&&                object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned int const volatile&&       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned int volatile&&             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned int&>      (object)) {}
    constexpr any(unsigned long&                      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long const&                object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long const volatile&       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long volatile&             object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long&&                     object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long const&&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long const volatile&&      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long volatile&&            object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long&>     (object)) {}
    constexpr any(unsigned long long&                 object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned long long const&           object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned long long const volatile&  object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned long long volatile&        object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned long long&&                object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned long long const&&          object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned long long const volatile&& object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned long long volatile&&       object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned long long&>(object)) {}
    constexpr any(unsigned short&                     object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}
    constexpr any(unsigned short const&               object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}
    constexpr any(unsigned short const volatile&      object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}
    constexpr any(unsigned short volatile&            object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}
    constexpr any(unsigned short&&                    object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}
    constexpr any(unsigned short const&&              object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}
    constexpr any(unsigned short const volatile&&     object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}
    constexpr any(unsigned short volatile&&           object) noexcept : extent(0u), type(::type(object)), value((void*) &object), integer(const_cast<unsigned short&>    (object)) {}

    template <typename base>
    constexpr any(base&& object, typename std::enable_if<false != std::is_array<typename std::remove_reference<base>::type>::value, int>::type const = 0x0) noexcept :
      extent(std::extent<typename std::remove_reference<base>::type>::value),
      type(::type(std::forward<base>(object))),
      value((void*) object),
      pointer((void*) &static_cast<base const&>(object))
    {}

    template <typename base>
    inline any(base&& object, typename std::enable_if<false == std::is_array<typename std::remove_reference<base>::type>::value, int>::type const = 0x0) noexcept :
      extent(std::extent<typename std::remove_reference<base>::type>::value),
      type(::type(std::forward<base>(object))),
      value((void*) &reinterpret_cast<unsigned char const volatile&>(object)),
      pointer(std::is_pointer<typename std::remove_reference<base>::type>::value ? (void*&) reinterpret_cast<unsigned char const volatile&>(object) : NULL)
    {}

    /* ... */
    template <typename base>
    constexpr operator base() const noexcept {
      return *static_cast<typename std::remove_reference<base>::type*>(std::is_array<typename std::remove_reference<base>::type>::value ? this -> pointer : this -> value);
    }
  };

  struct ranged final {
    intmax_t first;
    intmax_t last;

    /* ... */
    constexpr ranged begin() const noexcept {
      return {this -> first, this -> last};
    }

    constexpr ranged end() const noexcept {
      return {this -> first, this -> last};
    }

    /* ... */
    constexpr bool operator !=(ranged const end) const noexcept {
      return this -> first != end.last;
    }

    constexpr intmax_t operator *() const noexcept {
      return this -> first;
    }

    inline void operator ++() noexcept {
      this -> first < this -> last ? ++(this -> first) : --(this -> last);
    }
  };

  struct str final {
    char       *value;
    std::size_t length;
  };

  #ifdef __cpp_char8_t
    struct u8str final {
      char8_t    *value;
      std::size_t length;
    };
  #endif

  struct u16str final {
    char16_t   *value;
    std::size_t length;
  };

  struct u32str final {
    char32_t   *value;
    std::size_t length;
  };

  struct wstr final {
    wchar_t    *value;
    std::size_t length;
  };
}

namespace {
  constexpr typename std::conditional<(__cplusplus >= 201103L), int, void>::type print() noexcept {
    return typename std::conditional<(__cplusplus >= 201103L), int, void>::type(0x0);
  }

  template <typename... bases> inline void print(str    object, bases&&... objects) noexcept { if (INT_MAX < object.length) std::fprintf(stdout, "%.*s",  static_cast<int>(object.length), object.value); else { for (char    const *iterator = object.value; object.length--; ++iterator) std::fputc(*iterator, stdout); }                                 print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(u16str object, bases&&... objects) noexcept { std::mbstate_t state; for (char16_t *character = object.value; object.length--; ++character) { char string[MB_LEN_MAX * 2u /* --> MB_CUR_MAX */]; std::size_t const length = std::c16rtomb(string, *character, &state); if (length == static_cast<std::size_t>(-1)) break; std::fprintf(stdout, "%.*s", static_cast<int>(length), string); } print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(u32str object, bases&&... objects) noexcept { std::mbstate_t state; for (char32_t *character = object.value; object.length--; ++character) { char string[MB_LEN_MAX * 2u /* --> MB_CUR_MAX */]; std::size_t const length = std::c32rtomb(string, *character, &state); if (length == static_cast<std::size_t>(-1)) break; std::fprintf(stdout, "%.*s", static_cast<int>(length), string); } print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(wstr   object, bases&&... objects) noexcept { if (INT_MAX < object.length) std::fprintf(stdout, "%.*ls", static_cast<int>(object.length), object.value); else { for (wchar_t const *iterator = object.value; object.length--; ++iterator) std::fprintf(stdout, "%lc", static_cast<unsigned>(*iterator)); } print(std::forward<bases>(objects)...); }
  #ifdef __cpp_char8_t
    template <typename... bases> inline void print(u8str  object, bases&&... objects) noexcept { std::mbstate_t state; for (char8_t  *character = object.value; object.length--; ++character) { char string[MB_LEN_MAX * 2u /* --> MB_CUR_MAX */]; std::size_t const length = std::c8rtomb (string, *character, &state); if (length == static_cast<std::size_t>(-1)) break; std::fprintf(stdout, "%.*s", static_cast<int>(length), string); } print(std::forward<bases>(objects)...); }
  #endif

  template <typename... bases> inline void print(bool const object, bases&&... objects) noexcept { std::fputs(object ? "True" : "False", stdout); print(std::forward<bases>(objects)...); }

  template <typename... bases> inline void print(char object, bases&&... objects) noexcept { print(str{&object, 1u}); print(std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char                (&object) [capacity], bases&&... objects) noexcept { print(str{object, capacity}); print(std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char                (&&object)[capacity], bases&&... objects) noexcept { print((char (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char const          (&object) [capacity], bases&&... objects) noexcept { print((char (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char const          (&&object)[capacity], bases&&... objects) noexcept { print((char (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char volatile       (&object) [capacity], bases&&... objects) noexcept { print((char (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char volatile       (&&object)[capacity], bases&&... objects) noexcept { print((char (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char const volatile (&object) [capacity], bases&&... objects) noexcept { print((char (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char const volatile (&&object)[capacity], bases&&... objects) noexcept { print((char (&)[capacity]) object, std::forward<bases>(objects)...); }

  #ifdef __cpp_char8_t
    template <typename... bases> inline void print(char8_t object, bases&&... objects) noexcept { print(u8str{&object, 1u}); print(std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t                (&object) [capacity], bases&&... objects) noexcept { print(u8str{object, capacity}, std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t                (&&object)[capacity], bases&&... objects) noexcept { print((char8_t (&)[capacity]) object, std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t const          (&object) [capacity], bases&&... objects) noexcept { print((char8_t (&)[capacity]) object, std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t const          (&&object)[capacity], bases&&... objects) noexcept { print((char8_t (&)[capacity]) object, std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t volatile       (&object) [capacity], bases&&... objects) noexcept { print((char8_t (&)[capacity]) object, std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t volatile       (&&object)[capacity], bases&&... objects) noexcept { print((char8_t (&)[capacity]) object, std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t const volatile (&object) [capacity], bases&&... objects) noexcept { print((char8_t (&)[capacity]) object, std::forward<bases>(objects)...); }
    template <std::size_t capacity, typename... bases> inline void print(char8_t const volatile (&&object)[capacity], bases&&... objects) noexcept { print((char8_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  #endif

  template <typename... bases> inline void print(char16_t object, bases&&... objects) noexcept { print(u16str{&object, 1u}); print(std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t                (&object) [capacity], bases&&... objects) noexcept { print(u16str{object, capacity}, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t                (&&object)[capacity], bases&&... objects) noexcept { print((char16_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t const          (&object) [capacity], bases&&... objects) noexcept { print((char16_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t const          (&&object)[capacity], bases&&... objects) noexcept { print((char16_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t volatile       (&object) [capacity], bases&&... objects) noexcept { print((char16_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t volatile       (&&object)[capacity], bases&&... objects) noexcept { print((char16_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t const volatile (&object) [capacity], bases&&... objects) noexcept { print((char16_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char16_t const volatile (&&object)[capacity], bases&&... objects) noexcept { print((char16_t (&)[capacity]) object, std::forward<bases>(objects)...); }

  template <typename... bases> inline void print(char32_t object, bases&&... objects) noexcept { print(u32str{&object, 1u}); print(std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t                (&object) [capacity], bases&&... objects) noexcept { print(u32str{object, capacity}, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t                (&&object)[capacity], bases&&... objects) noexcept { print((char32_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t const          (&object) [capacity], bases&&... objects) noexcept { print((char32_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t const          (&&object)[capacity], bases&&... objects) noexcept { print((char32_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t volatile       (&object) [capacity], bases&&... objects) noexcept { print((char32_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t volatile       (&&object)[capacity], bases&&... objects) noexcept { print((char32_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t const volatile (&object) [capacity], bases&&... objects) noexcept { print((char32_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(char32_t const volatile (&&object)[capacity], bases&&... objects) noexcept { print((char32_t (&)[capacity]) object, std::forward<bases>(objects)...); }

  template <typename... bases> inline void print(double      const object, bases&&... objects) noexcept { std::fprintf(stdout, "%lf", object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(float       const object, bases&&... objects) noexcept { std::fprintf(stdout, "%f",  object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(long double const object, bases&&... objects) noexcept { std::fprintf(stdout, "%Lf", object); print(std::forward<bases>(objects)...); }

  template <typename... bases> inline void print(signed char      const object, bases&&... objects) noexcept { std::fprintf(stdout, "%hhi", object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(signed int       const object, bases&&... objects) noexcept { std::fprintf(stdout, "%i",   object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(signed long      const object, bases&&... objects) noexcept { std::fprintf(stdout, "%li",  object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(signed long long const object, bases&&... objects) noexcept { std::fprintf(stdout, "%lli", object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(signed short     const object, bases&&... objects) noexcept { std::fprintf(stdout, "%hi",  object); print(std::forward<bases>(objects)...); }

  template <typename... bases> inline void print(unsigned char      const object, bases&&... objects) noexcept { std::fprintf(stdout, "%hhu", object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(unsigned int       const object, bases&&... objects) noexcept { std::fprintf(stdout, "%u",   object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(unsigned long      const object, bases&&... objects) noexcept { std::fprintf(stdout, "%lu",  object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(unsigned long long const object, bases&&... objects) noexcept { std::fprintf(stdout, "%llu", object); print(std::forward<bases>(objects)...); }
  template <typename... bases> inline void print(unsigned short     const object, bases&&... objects) noexcept { std::fprintf(stdout, "%hu",  object); print(std::forward<bases>(objects)...); }

  template <typename... bases> inline void print(wchar_t object, bases&&... objects) noexcept { print(wstr{&object, 1u}); print(std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t                (&object) [capacity], bases&&... objects) noexcept { print(wstr{object, capacity}); print(std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t                (&&object)[capacity], bases&&... objects) noexcept { print((wchar_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t const          (&object) [capacity], bases&&... objects) noexcept { print((wchar_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t const          (&&object)[capacity], bases&&... objects) noexcept { print((wchar_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t volatile       (&object) [capacity], bases&&... objects) noexcept { print((wchar_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t volatile       (&&object)[capacity], bases&&... objects) noexcept { print((wchar_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t const volatile (&object) [capacity], bases&&... objects) noexcept { print((wchar_t (&)[capacity]) object, std::forward<bases>(objects)...); }
  template <std::size_t capacity, typename... bases> inline void print(wchar_t const volatile (&&object)[capacity], bases&&... objects) noexcept { print((wchar_t (&)[capacity]) object, std::forward<bases>(objects)...); }

  template <typename... bases> inline void print(std::nullptr_t const, bases&&... objects) noexcept { std::fprintf(stdout, "%p", (void*) NULL); print(std::forward<bases>(objects)...); }

  template <typename base, std::size_t capacity, typename... bases> inline void print(base (&object) [capacity], bases&&... objects) noexcept { std::fputc('[', stdout); for (base *element = object; element != object + capacity; ++element) { print(*element); if (element != object + (capacity - 1u)) std::fputs(", ", stdout); } std::fputc(']', stdout); print(std::forward<bases>(objects)...); }
  template <typename base, std::size_t capacity, typename... bases> inline void print(base (&&object)[capacity], bases&&... objects) noexcept { print(static_cast<base (&)[capacity]>(object), std::forward<bases>(objects)...); }

  template <typename base, typename... subbase, typename... bases> inline void print(base (&object) (subbase...),      bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
  template <typename base, typename... subbase, typename... bases> inline void print(base (&object) (subbase..., ...), bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
  template <typename base, typename... subbase, typename... bases> inline void print(base (&&object)(subbase...),      bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
  template <typename base, typename... subbase, typename... bases> inline void print(base (&&object)(subbase..., ...), bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
  #ifdef __cpp_noexcept_function_type
    template <typename base, typename... subbase, typename... bases> inline void print(base (&object) (subbase...)      noexcept, bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
    template <typename base, typename... subbase, typename... bases> inline void print(base (&object) (subbase..., ...) noexcept, bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
    template <typename base, typename... subbase, typename... bases> inline void print(base (&&object)(subbase...)      noexcept, bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
    template <typename base, typename... subbase, typename... bases> inline void print(base (&&object)(subbase..., ...) noexcept, bases&&... objects) noexcept { std::fprintf(stdout, "%p", reinterpret_cast<void*>(&object)); print(std::forward<bases>(objects)...); }
  #endif

  template <typename base, typename... bases>
  inline void print(base&& object, bases&&... objects) noexcept {
    if (std::is_same<any, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value) {
      unsigned char     array[1];
      any const        &subobject = reinterpret_cast<any&>(const_cast<unsigned char&>(reinterpret_cast<unsigned char const volatile&>(object)));
      char const *const type      = subobject.type;

      // ...
      if (NULL == type) std::fputs("<object>", stdout);
      else if (type == ::type(array))             std::fputs("<list>", stdout);
      else if (type == ::type(false))             print(*static_cast<bool*>(subobject.value));
      else if (type == ::type(0.0))               print(subobject.decimal);
      else if (type == ::type(0))                 print(static_cast<signed long long>(subobject.integer));
      else if (type == ::type(0u))                print(subobject.integer);
      else if (type == ::type(nullptr))           print(subobject.pointer);
      else if (type == ::type(+[]() noexcept {})) print(reinterpret_cast<void*>(subobject.value));

      else if (type == ::type('\0')) print(*static_cast<char*>(subobject.value));
      else if (type == ::type("")) {
        for (char *iterator = *static_cast<char**>(subobject.value); ; ++iterator)
        if ('\0' == *iterator) { print(str{*static_cast<char**>(subobject.value), 0u != subobject.extent ? subobject.extent : static_cast<std::size_t>(iterator - *static_cast<char**>(subobject.value))}); break; }
      }

      else if (type == ::type(u'\0')) print(*static_cast<char16_t*>(subobject.value));
      else if (type == ::type(u"")) {
        for (char16_t *iterator = *static_cast<char16_t**>(subobject.value); ; ++iterator)
        if (u'\0' == *iterator) { print(u16str{*static_cast<char16_t**>(subobject.value), 0u != subobject.extent ? subobject.extent : static_cast<std::size_t>(iterator - *static_cast<char16_t**>(subobject.value))}); break; }
      }

      else if (type == ::type(U'\0')) print(*static_cast<char32_t*>(subobject.value));
      else if (type == ::type(U"")) {
        for (char32_t *iterator = *static_cast<char32_t**>(subobject.value); ; ++iterator)
        if (U'\0' == *iterator) { print(u32str{*static_cast<char32_t**>(subobject.value), 0u != subobject.extent ? subobject.extent : static_cast<std::size_t>(iterator - *static_cast<char32_t**>(subobject.value))}); break; }
      }

      else if (type == ::type(L'\0')) print(*static_cast<wchar_t*>(subobject.value));
      else if (type == ::type(L"")) {
        for (wchar_t *iterator = *static_cast<wchar_t**>(subobject.value); ; ++iterator)
        if (L'\0' == *iterator) { print(wstr{*static_cast<wchar_t**>(subobject.value), 0u != subobject.extent ? subobject.extent : static_cast<std::size_t>(iterator - *static_cast<wchar_t**>(subobject.value))}); break; }
      }

      #ifdef __cpp_char8_t
        else if (type == ::type(u8'\0')) print(*static_cast<char8_t*>(subobject.value));
        else if (type == ::type(u8"")) {
          for (char8_t *iterator = *static_cast<char8_t**>(subobject.value); ; ++iterator)
          if (u8'\0' == *iterator) { print(u8str{*static_cast<char8_t**>(subobject.value), 0u != subobject.extent ? subobject.extent : static_cast<std::size_t>(iterator - *static_cast<char8_t**>(subobject.value))}); break; }
        }
      #endif
    }

    else if (std::is_pointer<typename std::remove_reference<base>::type>::value)
      std::fprintf(stdout, "%p", *reinterpret_cast<void**>(&const_cast<unsigned char&>(reinterpret_cast<unsigned char const volatile&>(object))));

    print(std::forward<bases>(objects)...);
  }

  constexpr ranged range(intmax_t const count) noexcept {
    return {count < 0 ? count : 0, count < 0 ? 0 : count};
  }

  constexpr ranged range(intmax_t const begin, intmax_t const end) noexcept {
    return {begin, end};
  }

  /* ... */
  #ifdef __clang__
  # pragma clang diagnostic push
  # pragma clang diagnostic ignored "-Wkeyword-macro"
  #endif
  # define def any def_parameters(
  #   define def_parameters(...) __VA_ARGS__ {
  # define end ;}
  # define for ;for (intmax_t&& for_scope(
  #   define for_scope(...) __VA_ARGS__) {
  # define if ;if (if_scope(
  #   define if_scope(...) __VA_ARGS__)
  # define in  :
  # define is  ==
  # define let ;auto
  # define __main__ int main(int, char*[]) /* noexcept */ {
  #ifdef __clang__
  # pragma clang diagnostic pop
  #endif
}

/* ... */
def fibonacci(int term))
  let a = 0
  let b = 1

  if term <= 0)
    return "Input should be higher than `0`"
  if term is 1)
    return 0
  if term is 2)
    return 1

  for term in range(2, term))
    let sum = a + b;
    a = b;
    b = sum
  end

  return b
end

/* Main */
__main__
  typedef char const (&str)[32];

  print(fibonacci(0).operator str(), '\n'); // Input should be higher than `0`
  print(fibonacci(5),                '\n')  // 3
end
