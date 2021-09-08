// #include <cfloat>
// #include <climits>
// #include <cstddef>
// #include <cstdio>
// #include <new>
// #include <stdint.h>

// /* ... [Utilities] */
// namespace {
//   template <typename type, type...>
//   struct collection {};
//     template <std::size_t...>
//     struct integer_collection;

//     template <>
//     struct integer_collection<> : public collection<std::size_t> {
//       enum { total = 0u };
//     };

//     template <std::size_t integer, std::size_t... integers>
//     struct integer_collection<integer, integers...> : public collection<std::size_t, integer, integers...> {
//       enum { total = integer + integer_collection<integers...>::total };
//     };
//       template <std::size_t count, std::size_t... indexes>
//       struct index_sequence : public index_sequence<count - 1u, count - 1u, indexes...> {};

//       template <std::size_t... indexes>
//       struct index_sequence<0u, indexes...> : public integer_collection<0u, indexes...> {};

//   // ...
//   template <unsigned long long integer, unsigned long long radix>
//   union countof {
//     private:
//       template <unsigned long long current, unsigned char total>
//       union count {
//         friend union countof<integer, radix>;
//         private: enum { value = count<current / radix, 1u + total>::value };
//       };

//     public:
//       enum { value = count<integer, 0u>::value };
//   };

//   template <unsigned long long integer, unsigned long long radix>
//   template <unsigned char total>
//   union countof<integer, radix>::count<0uLL, total> {
//     friend union countof<integer, radix>;
//     private: enum { value = total };
//   };

//   // ...
//   template <typename> union is_character { enum { value = false }; };

//   template <typename type> union is_character<type const>          { enum { value = is_character<type>::value }; };
//   template <typename type> union is_character<type const volatile> { enum { value = is_character<type>::value }; };
//   template <typename type> union is_character<type volatile>       { enum { value = is_character<type>::value }; };

//   template <> union is_character<char>    { enum { value = true }; };
//   template <> union is_character<wchar_t> { enum { value = true }; };
//   #if defined(__cplusplus) && __cplusplus >= 202002L
//    template <> union is_character<char8_t> { enum { value = true }; };
//   #endif
//   #if defined(__cplusplus) && __cplusplus >= 201103L
//    template <> union is_character<char16_t> { enum { value = true }; };
//    template <> union is_character<char32_t> { enum { value = true }; };
//   #endif

//   // ...
//   template <typename> union is_function_pointer { enum { value = false }; };
//   template <typename base, typename... types> union is_function_pointer<base (*)(types...)>      { enum { value = true }; };
//   template <typename base, typename... types> union is_function_pointer<base (*)(types..., ...)> { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)>                     { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...)>                { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const>          { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const>          { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const volatile> { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const volatile> { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      volatile>       { enum { value = true }; };
//   template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) volatile>       { enum { value = true }; };
//   #if __cplusplus >= 201703L
//     template <typename base, typename... types> union is_function_pointer<base (*)(types...) noexcept>      { enum { value = true }; };
//     template <typename base, typename... types> union is_function_pointer<base (*)(types..., ...) noexcept> { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...) noexcept>                     { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) noexcept>                { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const noexcept>          { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const noexcept>          { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      const volatile noexcept> { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) const volatile noexcept> { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types...)      volatile noexcept>       { enum { value = true }; };
//     template <class object, typename base, typename... types> union is_function_pointer<base (object::*)(types..., ...) volatile noexcept>       { enum { value = true }; };
//   #endif

//   // ...
//   template <typename> union is_object_pointer { enum { value = false }; };
//   template <typename type> union is_object_pointer<type*>                { enum { value = false == is_function_pointer<type*>::value }; };
//   template <typename type> union is_object_pointer<type const*>          { enum { value = is_object_pointer<type*>::value }; };
//   template <typename type> union is_object_pointer<type const volatile*> { enum { value = is_object_pointer<type*>::value }; };
//   template <typename type> union is_object_pointer<type volatile*>       { enum { value = is_object_pointer<type*>::value }; };

//   // ...
//   template <typename...>
//   union is_same {
//     enum { value = false };
//   };

//   template <typename base>
//   union is_same<base> {
//     enum { value = true };
//   };

//   template <typename base, typename... types>
//   union is_same<base, base, types...> {
//     enum { value = is_same<base, types...>::value };
//   };
// }

// namespace {
//   constexpr long double clamp(long double const number, long double const maximum) noexcept {
//     return number < maximum ? number : maximum;
//   }

//   constexpr unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) noexcept {
//     return integer < maximum ? integer : maximum;
//   }

//   // ...
//   template <typename type>
//   constexpr type instanceof() noexcept;

//   // ...
//   #if __cplusplus >= 201402L
//     constexpr long double modulus(long double dividend, long double divisor) {
//       long double denominator = divisor;
//       bool signedness = false;

//       // ...
//       if (0.00L == dividend) return 0.00L;
//       if (ULLONG_MAX >= dividend / divisor) return dividend - (divisor * static_cast<unsigned long long>(dividend / divisor));

//       // ...
//       if (0.00L > dividend) { dividend = -dividend; signedness = true; }
//       if (0.00L > divisor) { denominator = -divisor; divisor = -divisor; }

//       while (true) {
//         if (dividend < divisor) {
//           if (denominator == divisor) break;

//           divisor = denominator;
//           continue;
//         }

//         if (dividend > divisor * divisor) divisor *= divisor;
//         else if (dividend > divisor * 10.00L ) divisor *= 10.00L;
//         else if (dividend > divisor + divisor) divisor += divisor;

//         dividend -= divisor;
//       }

//       return dividend * (signedness ? -1.00L : 1.00L);
//     }
//   #else
//     constexpr long double modulus(long double const dividend, long double const divisor, long double const denominator = 0.00L) {
//       return (
//         0.00L == dividend ? 0.00L :
//         0.00L > dividend ? -modulus(-dividend, divisor, denominator) :
//         0.00L > divisor  ? +modulus(dividend, -divisor, denominator) :
//         divisor > dividend && 0.00L == denominator ? dividend :

//         // ->> Conditionally split between (constrained) compile-time vs (recursive) runtime evaluation
//         #if defined(__cplusplus) && __cplusplus >= 202002L
//           std::is_constant_evaluated()
//         #elif defined(__builtin_is_constant_evaluated)
//           __builtin_is_constant_evaluated()
//         #else
//           true
//         #endif
//         ? (
//           dividend - (ULLONG_MAX < dividend / divisor ? 0.00L : divisor * static_cast<unsigned long long>(dividend / divisor))
//         ) : (
//           divisor > dividend && denominator != divisor ? modulus(dividend, denominator, 0.00L) :
//             dividend >= (divisor * divisor) ? modulus(dividend - (divisor * divisor), divisor * divisor, 0.00L == denominator ? divisor : denominator) :
//             dividend >= (divisor * 10.00L ) ? modulus(dividend - (divisor * 10.00L ), divisor * 10.00L , 0.00L == denominator ? divisor : denominator) :
//             dividend >= (divisor + divisor) ? modulus(dividend - (divisor + divisor), divisor + divisor, 0.00L == denominator ? divisor : denominator) :
//             dividend >= divisor             ? modulus(dividend - (divisor          ), divisor          , 0.00L == denominator ? divisor : denominator) :
//           dividend
//         )
//       );
//     }
//   #endif

//   constexpr unsigned long long modulus(unsigned long long const dividend, unsigned long long const divisor) {
//     return dividend % divisor;
//   }
// }

// /* ... [Types] */
// int main();
// namespace {
//   template <bool, typename> union assert_t;
//   union string;
//   template <typename, std::size_t> union string_t;

//   // ...
//   template <typename base>
//   union assert_t<true, base> {
//     typedef base type;
//   };

//   // ... ->> `string_t` manipulation utilities
//   union string {
//     friend int ::main();

//     template <typename, std::size_t>
//     friend union string_t;

//     private:
//       template <typename char_t, std::size_t capacity>
//       constexpr static string_t<char_t, capacity> const& concatenate(string_t<char_t, capacity> const& string) noexcept {
//         return string;
//       }

//       template <typename char_t>
//       constexpr static string_t<char_t, 0u> concatenate(string_t<char_t, 0u> const&, string_t<char_t, 0u> const&) noexcept {
//         return {};
//       }

//       template <typename char_t, std::size_t capacity>
//       constexpr static string_t<char_t, capacity> const& concatenate(string_t<char_t, 0u> const&, string_t<char_t, capacity> const& string) noexcept {
//         return string;
//       }

//       template <typename char_t, std::size_t capacity>
//       constexpr static string_t<char_t, capacity> const& concatenate(string_t<char_t, capacity> const& string, string_t<char_t, 0u> const&) noexcept {
//         return string;
//       }

//       template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... indexesA, std::size_t... indexesB>
//       constexpr static string_t<char_t, capacityA + capacityB> concatenate(index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const, string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB) noexcept {
//         return {stringA.value[indexesA]..., stringB.value[indexesB]...};
//       }

//       template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
//       constexpr static string_t<char_t, capacityA + capacityB + integer_collection<capacities...>::total> concatenate(string_t<char_t, capacityA> const& stringA, string_t<char_t, capacityB> const& stringB, string_t<char_t, capacities> const&... strings) noexcept {
//         return concatenate(concatenate(index_sequence<capacityA>(), index_sequence<capacityB>(), stringA, stringB), strings...);
//       }

//       // ...
//       template <std::size_t length, typename char_t, std::size_t capacity>
//       constexpr static typename assert_t<capacity == length, string_t<char_t, length> const&>::type resize(string_t<char_t, capacity> const& string) noexcept {
//         return string;
//       }

//       template <std::size_t length, typename char_t, std::size_t capacity>
//       constexpr static typename assert_t<capacity != length, string_t<char_t, length> >::type resize(string_t<char_t, capacity> const& string) noexcept {
//         return {string};
//       }

//       // ...
//       template <typename char_t>
//       constexpr static string_t<char_t, 0u> const& reverse(string_t<char_t, 0u> const& string) noexcept {
//         return string;
//       }

//       template <typename char_t>
//       constexpr static string_t<char_t, 1u> const& reverse(string_t<char_t, 1u> const& string) noexcept {
//         return string;
//       }

//       template <typename char_t, std::size_t capacity, std::size_t... indexes>
//       constexpr static string_t<char_t, capacity> reverse(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
//         return {string.value[capacity - indexes - 1u]...};
//       }

//       template <typename char_t, std::size_t capacity>
//       constexpr static string_t<char_t, capacity> reverse(string_t<char_t, capacity> const& string) noexcept {
//         return reverse(index_sequence<capacity>(), string);
//       }

//       // ...
//       template <typename char_t, std::size_t count, std::size_t capacity>
//       constexpr static typename assert_t<(count >= capacity), string_t<char_t, 0u> >::type slice_begin(string_t<char_t, capacity> const&) noexcept {
//         return {};
//       }

//       template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
//       constexpr static typename assert_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_begin(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
//         return {string.value[count + indexes]...};
//       }

//       template <typename char_t, std::size_t count, std::size_t capacity>
//       constexpr static typename assert_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_begin(string_t<char_t, capacity> const& string) noexcept {
//         return slice_begin<char_t, count>(index_sequence<capacity - count>(), string);
//       }

//       // ...
//       template <typename char_t, std::size_t count, std::size_t capacity>
//       constexpr static typename assert_t<(count >= capacity), string_t<char_t, 0u> >::type slice_end(string_t<char_t, capacity> const&) noexcept {
//         return {};
//       }

//       template <typename char_t, std::size_t count, std::size_t capacity, std::size_t... indexes>
//       constexpr static typename assert_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_end(index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept {
//         return {string.value[indexes]...};
//       }

//       template <typename char_t, std::size_t count, std::size_t capacity>
//       constexpr static typename assert_t<(count < capacity), string_t<char_t, capacity - count> >::type slice_end(string_t<char_t, capacity> const& string) noexcept {
//         return slice_end<char_t, count>(index_sequence<capacity - count>(), string);
//       }

//       // ...
//       template <typename char_t> // --> bool
//       constexpr static string_t<char_t, 5u> stringify(bool const boolean) noexcept {
//         return boolean ? string_t<char_t, 5u>('t', 'r', 'u', 'e', '\0') : string_t<char_t, 5u>('f', 'a', 'l', 's', 'e');
//       }

//       template <typename char_t> // --> char
//       constexpr static string_t<char_t, 1u> stringify(char_t const& character) noexcept {
//         return {character};
//       }

//       template <typename char_t, std::size_t capacity, std::size_t... indexes> // --> char []
//       constexpr static string_t<char_t, capacity> stringify(index_sequence<0u, indexes...> const, char const string[]) noexcept {
//         return {string[indexes]...};
//       }

//       template <typename char_t, std::size_t capacity, std::size_t... indexes>
//       constexpr static string_t<char_t, capacity> stringify(index_sequence<0u, indexes...> const, char_t const (&string)[capacity]) noexcept {
//         return {string[indexes]...};
//       }

//       template <typename char_t, std::size_t capacity>
//       constexpr static string_t<char_t, capacity> stringify(char_t const (&string)[capacity]) noexcept {
//         return stringify(index_sequence<capacity>(), string);
//       }

//       #if __cplusplus >= 201402L // --> unsigned long long
//         template <typename char_t, unsigned long long radix, std::size_t... indexes>
//         constexpr static string_t<char_t, countof<ULLONG_MAX, radix>::value> stringify(index_sequence<0u, indexes...> const, unsigned long long integer) noexcept {
//           char string[] = {"\0"[indexes - indexes]...};

//           for (char *iterator = string + (sizeof(string) / sizeof(char)); iterator != string; integer /= radix)
//           *--iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)];

//           return {string[indexes]...};
//         }

//         template <typename char_t, unsigned long long radix, unsigned char>
//         constexpr static string_t<char_t, countof<ULLONG_MAX, radix>::value> stringify(unsigned long long const integer) noexcept {
//           return stringify<char_t, radix>(index_sequence<countof<ULLONG_MAX, radix>::value>(), integer);
//         }
//       #else
//         template <typename char_t, unsigned long long radix, unsigned char count>
//         constexpr static typename assert_t<count == countof<ULLONG_MAX, radix>::value, string_t<char_t, countof<ULLONG_MAX, radix>::value> >::type stringify(unsigned long long const, string_t<char_t, count> const& string = {}) noexcept {
//           return string;
//         }

//         template <typename char_t, unsigned long long radix, unsigned char count>
//         constexpr static typename assert_t<count != countof<ULLONG_MAX, radix>::value, string_t<char_t, countof<ULLONG_MAX, radix>::value> >::type stringify(unsigned long long const integer, string_t<char_t, count> const& string = {}) noexcept {
//           return stringify<char_t, radix, count + 1u>(integer / radix, concatenate<char_t>(stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)]), string));
//         }
//       #endif

//       #if __cplusplus >= 201402L // --> long double
//         template <typename char_t, unsigned long long radix, std::size_t... characteristicsIndexes, std::size_t... mantissaIndexes>
//         constexpr static string_t<char_t, 2u + LDBL_DIG + LDBL_MANT_DIG> stringify(index_sequence<0u, characteristicsIndexes...> const, index_sequence<0u, mantissaIndexes...> const, long double characteristics, long double mantissa) noexcept {
//           char characteristicsString[] = {"\0"[characteristicsIndexes - characteristicsIndexes]...};
//           bool signedness = false;
//           char mantissaString[] = {"\0"[mantissaIndexes - mantissaIndexes]...};

//           if (0.00L > characteristics || 0.00L > mantissa) {
//             characteristics = -characteristics;
//             mantissa = -mantissa;
//             signedness = true;
//           }

//           for (char *iterator = characteristicsString + (sizeof(characteristicsString) / sizeof(char)); iterator != characteristicsString; characteristics /= static_cast<long double>(radix))
//           *--iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(characteristics, static_cast<long double>(radix)), 36.00L))];

//           for (char *iterator = mantissaString + (sizeof(mantissaString) / sizeof(char)); iterator != mantissaString; mantissa *= static_cast<long double>(radix))
//           *--iterator = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(mantissa, static_cast<long double>(radix)), 36.00L))];

//           return {signedness ? '-' : '0', characteristicsString[characteristicsIndexes]..., '.', mantissaString[LDBL_MANT_DIG - mantissaIndexes - 1u]...};
//         }

//         template <typename char_t, unsigned long long radix, unsigned char, unsigned char>
//         constexpr static string_t<char_t, 2u + LDBL_DIG + LDBL_MANT_DIG> stringify(long double const number) noexcept {
//           return stringify<char_t, radix>(index_sequence<LDBL_DIG>(), index_sequence<LDBL_MANT_DIG>(), number, number * static_cast<long double>(radix));
//         }
//       #else
//         template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
//         constexpr static typename assert_t<characteristicsCount == LDBL_DIG && mantissaCount == LDBL_MANT_DIG, string_t<char_t, LDBL_DIG> const&>::type stringify(long double const, string_t<char_t, LDBL_DIG> const& string) noexcept {
//           return string;
//         }

//         template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
//         constexpr static typename assert_t<characteristicsCount == LDBL_DIG && mantissaCount == LDBL_MANT_DIG, string_t<char_t, LDBL_MANT_DIG> const&>::type stringify(long double const, string_t<char_t, LDBL_MANT_DIG> const& string) noexcept {
//           return string;
//         }

//         template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
//         constexpr static typename assert_t<characteristicsCount != LDBL_DIG && mantissaCount == LDBL_MANT_DIG, string_t<char_t, LDBL_DIG> >::type stringify(long double const number, string_t<char_t, characteristicsCount> const& string = {}) noexcept {
//           return stringify<char_t, radix, characteristicsCount + 1u, mantissaCount>(number / static_cast<long double>(radix), concatenate<char_t>(stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number, static_cast<long double>(radix)), 36.00L))]), string));
//         }

//         template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
//         constexpr static typename assert_t<characteristicsCount == LDBL_DIG && mantissaCount != LDBL_MANT_DIG, string_t<char_t, LDBL_MANT_DIG> >::type stringify(long double const number, string_t<char_t, mantissaCount> const& string = {}) noexcept {
//           return stringify<char_t, radix, characteristicsCount, mantissaCount + 1u>(number * static_cast<long double>(radix), concatenate<char_t>(string, stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number, static_cast<long double>(radix)), 36.00L))])));
//         }

//         template <typename char_t, unsigned long long radix, unsigned char characteristicsCount, unsigned char mantissaCount>
//         constexpr static typename assert_t<characteristicsCount != LDBL_DIG && mantissaCount != LDBL_MANT_DIG, string_t<char_t, 2u + LDBL_DIG + LDBL_MANT_DIG> >::type stringify(long double const number) noexcept {
//           return concatenate<char_t>(
//             stringify<char_t>(0.00L > number ? '-' : '0'), resize<LDBL_DIG>(stringify<char_t, radix, characteristicsCount, LDBL_MANT_DIG>(0.00L > number ? -number : number)),
//             stringify<char_t>('.'), resize<LDBL_MANT_DIG>(stringify<char_t, radix, LDBL_DIG, mantissaCount>(static_cast<long double>(radix) * (0.00L > number ? -number : number)))
//           );
//         }
//       #endif

//       #if __cplusplus >= 201402L // --> unsigned char[]
//         template <typename char_t, std::size_t size, std::size_t... indexes>
//         constexpr static string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> stringify(index_sequence<0u, indexes...> const, unsigned char const bytes[]) {
//           char string[] = {"\0"[indexes - indexes]...};

//           for (char *iterator = string + (sizeof(string) / sizeof(char)); iterator != string; bytes += 1) {
//             char const *const byte = stringify<typename assert_t<is_same<char_t>::value, char>::type, 16uLL, 0u>(static_cast<unsigned long long>(*bytes)).value + (countof<ULLONG_MAX, 16uLL>::value - countof<UCHAR_MAX, 16uLL>::value);

//             for (char_t const *subiterator = byte + countof<UCHAR_MAX, 16uLL>::value; subiterator != byte; )
//             *--iterator = *--subiterator;
//           }

//           return {string[indexes]...};
//         }

//         template <typename char_t, std::size_t size, std::size_t>
//         constexpr static string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> stringify(unsigned char const bytes[]) {
//           return stringify<char_t, size>(index_sequence<size * countof<UCHAR_MAX, 16uLL>::value>(), bytes);
//         }
//       #else
//         template <typename char_t, std::size_t size, std::size_t count>
//         constexpr static typename assert_t<count == size, string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> >::type stringify(unsigned char const[], string_t<char_t, count * countof<UCHAR_MAX, 16uLL>::value> const& string = {}) {
//           return string;
//         }

//         template <typename char_t, std::size_t size, std::size_t count>
//         constexpr static typename assert_t<count != size, string_t<char_t, size * countof<UCHAR_MAX, 16uLL>::value> >::type stringify(unsigned char const bytes[], string_t<char_t, count * countof<UCHAR_MAX, 16uLL>::value> const& string = {}) {
//           return stringify<char_t, size, count + 1u>(bytes + 1, concatenate<char_t>(slice_begin<char_t, countof<ULLONG_MAX, 16uLL>::value - countof<UCHAR_MAX, 16uLL>::value>(stringify<char_t, 16uLL, 0u>(static_cast<unsigned long long>(*bytes))), string));
//         }
//       #endif

//       // --> void*
//       template <typename char_t>
//       constexpr static string_t<char_t, countof<UINTPTR_MAX, 16uLL>::value> stringify(void* const pointer) {
//         return stringify<char_t, 16uLL, 0u>(
//           static_cast<unsigned char*>(pointer)
//         );
//       }
//   };

//   // ... ->> `char_t` members always copy/ value-initialized once
//   template <typename char_t, std::size_t length>
//   union string_t {
//     friend int ::main();

//     friend union string;

//     template <typename, std::size_t>
//     friend union string_t;

//     private:
//       char_t const value[length];

//       // ... ->> empty string
//       template <std::size_t... indexes>
//       constexpr string_t(index_sequence<0u, indexes...> const) noexcept(noexcept(char_t('\0'))) :
//         value{"\0"[indexes - indexes]...}
//       {}

//       constexpr string_t() noexcept(noexcept(string_t<char_t, length>(index_sequence<length>()))) :
//         string_t<char_t, length>::string_t(index_sequence<length>())
//       {}

//       // ... ->> null string
//       constexpr string_t(string_t<char_t, 0u> const&) noexcept(noexcept(string_t<char_t, length>())) :
//         string_t<char_t, length>::string_t()
//       {}

//       // ... ->> equal string
//       template <std::size_t... indexes>
//       constexpr string_t(index_sequence<0u, indexes...> const, string_t<char_t, length> const& string) noexcept(noexcept(char_t(instanceof<char_t const&>()))) :
//         value{string.value[indexes]...}
//       {}

//       constexpr string_t(string_t<char_t, length> const& string) noexcept(noexcept(string_t<char_t, length>(index_sequence<length>(), instanceof<string_t<char_t, length> const&>()))) :
//         string_t<char_t, length>::string_t(index_sequence<length>(), string)
//       {}

//       // ... ->> bigger string
//       template <std::size_t capacity>
//       constexpr string_t(string_t<char_t, capacity> const& string, typename assert_t<(capacity > length), unsigned char>::type const = 0x0u) noexcept(noexcept(string_t<char_t, length>(string::slice_end<char_t, capacity - length>(instanceof<string_t<char_t, capacity> const&>())))) :
//         string_t<char_t, length>::string_t(string::slice_end<char_t, capacity - length>(string))
//       {}

//       // ... ->> smaller string
//       template <std::size_t capacity, std::size_t... nulIndexes, std::size_t... indexes>
//       constexpr string_t(index_sequence<0u, nulIndexes...> const, index_sequence<0u, indexes...> const, string_t<char_t, capacity> const& string) noexcept(noexcept(char_t('\0')) && noexcept(char_t(instanceof<char_t const&>()))) :
//         value{string.value[indexes]..., "\0"[nulIndexes - nulIndexes]...}
//       {}

//       template <std::size_t capacity>
//       constexpr string_t(string_t<char_t, capacity> const& string, typename assert_t<(capacity < length), unsigned char>::type const = 0x0u) noexcept(noexcept(string_t<char_t, length>(index_sequence<length - capacity>(), index_sequence<capacity>(), instanceof<string_t<char_t, capacity> const&>()))) :
//         string_t<char_t, length>::string_t(index_sequence<length - capacity>(), index_sequence<capacity>(), string)
//       {}

//       // ... ->> equal character-by-character
//       template <typename... chars_t>
//       constexpr string_t(typename assert_t<length == 1u + sizeof...(chars_t) && (is_same<char, chars_t...>::value || is_same<char_t, chars_t...>::value), char_t>::type const& character, chars_t const&... characters) noexcept(noexcept(char_t(instanceof<char_t const&>()))) :
//         value{character, characters...}
//       {}

//       // ... ->> more/ less character-by-character
//       template <typename... chars_t>
//       constexpr string_t(typename assert_t<length != 1u + sizeof...(chars_t) && (is_same<char, chars_t...>::value || is_same<char_t, chars_t...>::value), char_t>::type const& character, chars_t const&... characters) noexcept(noexcept(string_t<char_t, length>(instanceof<string_t<char_t, 1u + sizeof...(chars_t)> const&>()))) :
//         string_t<char_t, length>::string_t(string_t<char_t, 1u + sizeof...(chars_t)>(character, characters...))
//       {}
//   };

//   template <typename char_t>
//   union string_t<char_t, 0u> {
//     friend union string;

//     template <typename, std::size_t>
//     friend union string_t;

//     private:
//       constexpr string_t(...) noexcept {}
//   };
// }

// /* Main */
// struct object { void member() const {} };
// int main() {
//   union {
//     void (object::* address)() const;
//     unsigned char bytes[sizeof(void (object::*)() const)];
//   } function;
//   function.address = &object::member;
//   int const integer = 0x45;

//   std::printf("[]: \"%.*s\"" "\r\n", countof<ULLONG_MAX, 10uLL>::value, string::stringify<char, 10uLL, 0u>(42u).value);
//   std::printf("[]: \"%.*s\"" "\r\n", 2u + LDBL_DIG + LDBL_MANT_DIG, string::stringify<char, 10uLL, 0u, 0u>(1337.69L).value);

//   std::printf("[]: \"");
//     for (unsigned char const *destination = function.bytes + sizeof(void (object::*)() const); destination-- != function.bytes; )
//     std::printf("%c%c", "0123456789ABCDEF"[(*destination / 0x10u) % 0x10u], "0123456789ABCDEF"[(*destination / 0x01u) % 0x10u]);
//   std::printf("\" \"%.*s\"" "\r\n", sizeof(void (object::*)() const) * countof<UCHAR_MAX, 16uLL>::value, string::stringify<char, sizeof(void (object::*)() const), 0u>(function.bytes).value);

//   std::printf("[]: \"");
//     for (unsigned char const *destination = static_cast<unsigned char const*>(static_cast<void const*>(&integer)) + sizeof(int); destination-- != static_cast<void const*>(&integer); )
//     std::printf("%c%c", "0123456789ABCDEF"[(*destination / 0x10u) % 0x10u], "0123456789ABCDEF"[(*destination / 0x01u) % 0x10u]);
//   std::printf("\" \"%.*s\"" "\r\n", sizeof(int) * countof<UCHAR_MAX, 16uLL>::value, string::stringify<char, sizeof(int), 0u>(static_cast<unsigned char const*>(static_cast<void const*>(&integer))).value);
// }

#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>

// Square root of integer
constexpr std::size_t isqrt(std::size_t const s) {
  std::size_t x0 = s >> 1u;

  if (0u != x0) {
    std::size_t x1 = (x0 + (s / x0)) >> 1u;

    while (x1 < x0) {
      x0 = x1;
      x1 = (x0 + (s / x0)) >> 1u;
    }

    return x0;
  }

  return s;
}

template <typename type>
constexpr type* get(type* const pointer) {
  type *current = pointer;
  enum { DOUBLE, RADIX, SQUARE } factor = DOUBLE;
  std::size_t increment = 1u;
  type *recent = current;
  uintptr_t value = 0u;
  unsigned short count = 0u;

  while (count != 1uLL << 15uLL /* 18uLL */ && NULL != current) {
    ++count;
    // std::printf("[PROGRESS #%u]: (%s, %u) %u -> (%u, %u)" "\r\n", count, DOUBLE == factor ? "x 2" : RADIX == factor ? "x10" : "x N", increment, (uintptr_t) pointer, (uintptr_t) recent, (uintptr_t) current);
    increment = 4243524u;
    recent = current;
    current -= increment;
    if (NULL == current) return current;

    // if (static_cast<type*>(NULL) > current || current > pointer) {
    //   current = recent;
    //   increment >>= 2u;
    //   if (0u == increment) increment = 1u;
    //   // std::printf("[RESET    #%u]: (%s, %u) %u -> (%u, %u)" "\r\n", count, DOUBLE == factor ? "x 2" : RADIX == factor ? "x10" : "x N", increment, (uintptr_t) pointer, (uintptr_t) recent, (uintptr_t) current);
    //   factor = DOUBLE;
    //   continue;
    // }

    // switch (factor) {
    //   case DOUBLE: {
    //     if (increment < SIZE_MAX / 2u) {
    //       increment *= 2u;
    //       if (increment < SIZE_MAX / 10u) factor = RADIX;
    //     }
    //   } break;

    //   case RADIX: {
    //     if (increment < SIZE_MAX / 10u) {
    //       increment *= 10u;
    //       if (increment < (SIZE_MAX >> ((CHAR_BIT * sizeof(std::size_t)) / 2u))) factor = SQUARE;
    //     } else factor = DOUBLE;
    //   } break;

    //   case SQUARE: {
    //     if (increment < (SIZE_MAX >> ((CHAR_BIT * sizeof(std::size_t)) / 2u))) {
    //       increment *= increment;
    //     } else factor = DOUBLE;
    //   } break;
    // }
  }

  static_cast<void>(count);
  static_cast<void>(current);
  static_cast<void>(factor);
  static_cast<void>(increment);
  static_cast<void>(recent);
  static_cast<void>(value);

  return current;
}

int main() {
  constexpr static char const string[] = "Hello, World!";
  // constexpr uintptr_t address = get(string);
  constexpr static char const *address = get(string);

  std::printf("[+]: %u, [-]: %u" "\r\n", (uintptr_t) static_cast<void const*>(string), (uintptr_t) static_cast<void const*>(string - (2u * (string - static_cast<char const*>(NULL)))));
  std::printf("[+]: %u", (uintptr_t) address);
  // std::printf("[+]: %u", (uintptr_t) static_cast<unsigned char*>(NULL) + address);
}
