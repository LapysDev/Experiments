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
