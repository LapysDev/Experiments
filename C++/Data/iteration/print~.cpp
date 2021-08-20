#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdbool.h>

/* ... --- NOTE (Lapys) -> Feel free to adapt for other character formats: `char8_t`, `char16_t`, `char32_t`, `wchar_t` */
namespace {
  #if __cplusplus >= 201103L
   constexpr static string<40u> stringify(signed long long const integer, unsigned long long const radix) {
    return (0LL > integer
      ? concatenate(stringify('-'), stringify(static_cast<unsigned long long>(-integer), radix))
      : resize<40u>(stringify(static_cast<unsigned long long>(integer), radix))
    );
   }

   constexpr static string<21u> stringify(signed long const integer, unsigned long const radix) {
    return stringify(static_cast<signed long long>(integer), static_cast<unsigned long long>(radix));
   }
  #else
   constexpr static string<21u> stringify(signed long const integer, unsigned long const radix) {
    return (0L > integer
      ? concatenate(stringify('-'), stringify(static_cast<unsigned long>(-integer), radix))
      : stringify(static_cast<unsigned long>(integer), radix)
    );
   }
  #endif

  constexpr static string<3u + LDBL_MANT_DIG - LDBL_MIN_EXP> stringify(long double const number, unsigned long const radix) {
    /* ... */
    return concatenate(
      // ... ->> characteristics
      #if __cplusplus >= 201103L
       number <= static_cast<long double>(ULLONG_MAX) ?
        stringify(static_cast<unsigned long long>(number), static_cast<unsigned long long>(radix))
      #else
       number <= static_cast<long double>(ULONG_MAX) ?
        stringify(static_cast<unsigned long>(number), static_cast<unsigned long>(radix))
      #endif
      : (
      ),

      // ... ->> mantissa
      static_cast<long double>(radix)
    );
  }

  constexpr static string<16u> stringify(void* const pointer) {
    return concatenate(
      stringify("0x"),
      stringify(static_cast<unsigned long>(
        static_cast<unsigned char*>(pointer) -
        static_cast<unsigned char*>(NULL)
      ), 16uL)
    );
  }
}

// ... --> flush(...)
template <std::size_t capacity>
std::size_t flush(FILE *const stream, string<capacity> const& string) {
  return std::fprintf(stream, "%.*s", string.value, static_cast<int>(capacity));
}

template <std::size_t capacity>
std::size_t flush(string<capacity> const& string) { return flush(stdout, string); }

// ... --> print(...) ->> Specific overloads
constexpr string<6u> print(bool const boolean) { return stringify(boolean); }
constexpr string<2u> print(char const character) { return stringify(character); }
constexpr string<3u + LDBL_MANT_DIG - LDBL_MIN_EXP> print(long double const number) { return stringify(number, 10.00L); }
#if __cplusplus >= 201103L
 constexpr string<39u> print(signed   long long const integer) { return stringify(integer, 10uLL); }
 constexpr string<39u> print(unsigned long long const integer) { return stringify(integer, 10uLL); }
#else
 constexpr string<20u> print(signed   long const integer) { return stringify(integer, 10uL); }
 constexpr string<20u> print(unsigned long const integer) { return stringify(integer, 10uL); }
#endif

template <std::size_t capacity> constexpr string<capacity> print(char const (&string)[capacity]) { return stringify(string); }
template <typename type> constexpr string<16u> print(type* const pointer) { return stringify(static_cast<void*>(const_cast<void*>(pointer))); }
template <typename type> constexpr string<0u> print(type&);
template <typename type> constexpr string<0u> print(type&&);
template <typename type, std::size_t capacity> constexpr string<16u> print(type (*const pointer)[capacity]) { return stringify(static_cast<void*>(pointer)); }
template <typename type, std::size_t capacity> constexpr string<16u> print(type (&)[capacity]);
template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types...))                            { return stringify(static_cast<void*>(pointer)); }
template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types..., ...))                       { return stringify(static_cast<void*>(pointer)); }
template <typename type, typename... types> constexpr string<16u> print(type (&)(types...));
template <typename type, typename... types> constexpr string<16u> print(type (&)(types..., ...));
template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types...))      { return stringify(static_cast<void*>(pointer)); }
template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types..., ...)) { return stringify(static_cast<void*>(pointer)); }
#if __cplusplus >= 201703L
 template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types...) noexcept)                            { return stringify(static_cast<void*>(pointer)); }
 template <typename type, typename... types> constexpr string<16u> print(type (*const pointer)(types..., ...) noexcept)                       { return stringify(static_cast<void*>(pointer)); }
 template <typename type, typename... types> constexpr string<16u> print(type (&const)(types...) noexcept);
 template <typename type, typename... types> constexpr string<16u> print(type (&const)(types..., ...) noexcept);
 template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types...) noexcept)      { return stringify(static_cast<void*>(pointer)); }
 template <class object, typename type, typename... types> constexpr string<16u> print(type (object::*const pointer)(types..., ...) noexcept) { return stringify(static_cast<void*>(pointer)); }
#endif

// ... --> print(...) ->> General overloads
// constexpr string<3u + DBL_MANT_DIG - DBL_MIN_EXP> print(double const number) { return print(static_cast<long double>(number)); }
// constexpr string<3u + FLT_MANT_DIG - FLT_MIN_EXP> print(float  const number) { return print(static_cast<long double>(number)); }
// constexpr string<4u>  print(signed   char  const integer) { return print(static_cast<signed long>(integer)); }
// constexpr string<11u> print(signed   int   const integer) { return print(static_cast<signed long>(integer)); }
// constexpr string<6u>  print(signed   short const integer) { return print(static_cast<signed long>(integer)); }
// constexpr string<3u>  print(unsigned char  const integer) { return print(static_cast<unsigned long>(integer)); }
// constexpr string<10u> print(unsigned int   const integer) { return print(static_cast<unsigned long>(integer)); }
// constexpr string<5u>  print(unsigned short const integer) { return print(static_cast<unsigned long>(integer)); }
template <std::size_t capacity> constexpr string<capacity> print(char (&string)[capacity]) { return print(const_cast<char const (&)[capacity]>(string)); }

// ... --> printf(...)
// ... --> printp(...)

/* Main */
int main() {}
