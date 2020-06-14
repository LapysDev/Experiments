/* Import */
#include <fcntl.h> // File Control --- NOTE (Lapys) -> Output.
#include <float.h> // Floating-Point --- NOTE (Lapys) -> Conversion assertion.
#include <limits.h> // Limits
#include <math.h> // Mathematics --- NOTE (Lapys) -> Data assertion.
#include <stdio.h> // Standard Input-Output --- NOTE (Lapys) -> Output.
#include <stdlib.h> // Standard Library --- NOTE (Lapys) -> Output.
#include <string.h> // String --- NOTE (Lapys) -> Textual conversion.

/* Polyfill > ... */
#if !defined(INFINITY) && defined(HUGE_VAL)
#  define INFINITY HUGE_VAL
#endif

/* Definition > ...  --- NOTE (Lapys) -> Decimals are interpreted with a precision of 8 digits. */
    /* [Conversion] */
    char const* number__to__string(double const) noexcept;
    char const* number__to__string(float const) noexcept;
    char const* number__to__string(int const) noexcept;
    char const* number__to__string(long const) noexcept;
    char const* number__to__string(long double const) noexcept;
    char const* number__to__string(short const) noexcept;
    char const* number__to__string(unsigned int const) noexcept;
    char const* number__to__string(unsigned long const) noexcept;
    char const* number__to__string(unsigned short const) noexcept;

    template <typename type> char const* pointer__to__string(type* const) noexcept;

    constexpr long double string__to__number(char const) noexcept;
    long double string__to__number(char*) noexcept;
    long double string__to__number(char const* const) noexcept;

    /* [Output] --- NOTE (Lapys) -> Textually converted data can be performance-optimized when only printing. */
    constexpr void print(void) noexcept;
    void print(char const) noexcept;
    void print(char* const) noexcept;
    void print(char const* const) noexcept;
    void print(double const) noexcept;
    void print(float const) noexcept;
    void print(int const) noexcept;
    void print(long const) noexcept;
    void print(long double const) noexcept;
    void print(short const) noexcept;
    void print(unsigned int const) noexcept;
    void print(unsigned long const) noexcept;
    void print(unsigned short const) noexcept;
    template <typename type> void print(type* const) noexcept;
    void println(void) noexcept;
    void println(double const) noexcept;
    void println(float const) noexcept;
    void println(int const) noexcept;
    void println(long const) noexcept;
    void println(long double const) noexcept;
    void println(short const) noexcept;
    void println(unsigned int const) noexcept;
    void println(unsigned long const) noexcept;
    void println(unsigned short const) noexcept;
    template <typename type> void println(type* const) noexcept;

/* Function --- MINIFY (Lapys) -> Minified due to the numerous amounts of overloads. */
    /* Number to String
            --- NOTE (Lapys) -> Parses the number to its fixed notation.
            --- WARN (Lapys) -> Formatting is terrible; Maximum of 18 digits of precision.
    */
    inline char const* number__to__string(double const number) noexcept { return number__to__string((long double) number); }
    inline char const* number__to__string(float const number) noexcept { return number__to__string((long double) number); }
    inline char const* number__to__string(int const number) noexcept { return number__to__string((long) number); }
    inline char const* number__to__string(long const number) noexcept { static char string[21] {0}; ::strncpy(string + (number < 0L), number__to__string((unsigned long) (number < 0L ? -number : number)), sizeof(string)); if (number < 0L) *string = '-'; return (char const*) string; }
    inline char const* number__to__string(long double const number) noexcept { if (::isinf(number)) return number < 0.00L ? "-Infinity" : "Infinity"; else if (::isnan(number)) return "NaN"; else if (number && false == ::isnormal(number)) return "Denormalized"; else { long double characteristics; char *iterator; long double mantissa; static char string[LDBL_MAX_10_EXP + 3u] {0}; ::memset(string, '\0', sizeof(string));  if (number < 0.00L) { iterator = string + 1; mantissa = ::modf(-number, &characteristics); *string = '-'; *(string + 1) = '0'; } else { iterator = string; mantissa = ::modf(number, &characteristics); *string = '0'; } if (characteristics) { for (long double digit; characteristics && (string - iterator) <= LDBL_DIG; *iterator++ = *("0123456789" + (unsigned char) ::round(digit))) digit = ::modf((characteristics /= 10.00L), &characteristics) * 10.00L; ::strrev(string + (number < 0.00L)); } else ++iterator; if (mantissa) { *iterator++ = '.'; for (long double digit; mantissa >= LDBL_EPSILON; *iterator++ = *("0123456789" + (unsigned char) ::round(digit))) mantissa = ::modf((mantissa *= 10.00L), &digit); } return (char const*) string; } }
    inline char const* number__to__string(short const number) noexcept { return number__to__string((long) number); }
    inline char const* number__to__string(unsigned int const number) noexcept { return number__to__string((unsigned long) number); }
    inline char const* number__to__string(unsigned long const number) noexcept { static char string[21] {0}; ::memset(string, '\0', sizeof(string)); *string = '0'; for (unsigned long index = 0u, iterator = number; iterator; iterator /= 10u) { *(string + index++) = *("0123456789" + (iterator % 10u)); if (iterator < 10u) for ((--index, iterator = 0u); iterator < index; (--index, ++iterator)) { *(string + index) ^= *(string + iterator); *(string + iterator) ^= *(string + index); *(string + index) ^= *(string + iterator); } } return (char const*) string; }
    inline char const* number__to__string(unsigned short const number) noexcept { return number__to__string((unsigned long) number); }

    // Pointer To String
    template <typename type> inline char const* pointer__to__string(type* const pointer) noexcept { static char string[10] {0}; if (pointer) { ::strncpy(string, "0x", 2u); ::memset(string + 2, '\0', sizeof(string) - (2u * sizeof(char))); for (unsigned int index = 2u, iterator = (int) pointer; iterator; iterator >>= 4u) { *(string + index++) = *("0123456789ABCDEF" + (iterator % 16u)); if (iterator < 16u) for ((--index, iterator = 2u); iterator < index; (--index, ++iterator)) { *(string + index) ^= *(string + iterator); *(string + iterator) ^= *(string + index); *(string + index) ^= *(string + iterator); } } } else ::strncpy(string, "NULL", 5u); return (char const*) string; }

    // Print
    constexpr inline void print(void) noexcept {}
    inline void print(char const message) noexcept { ::write(STDOUT_FILENO, &message, 1u); }
    inline void print(char* const message) noexcept { print((char const*) message); }
    inline void print(char const* const message) noexcept { if (message) { for (char *iterator = (char*) message; *(iterator++); ) if ('\0' == *iterator) ::write(STDOUT_FILENO, message, (size_t) (iterator - message)); } }
    inline void print(double const message) noexcept { print((long double) message); }
    inline void print(float const message) noexcept { print((long double) message); }
    inline void print(int const message) noexcept { print((long) message); }
    inline void print(long const message) noexcept { if (message < 0L) print('-'); print((unsigned long) (message < 0L ? -message : message)); }
    inline void print(long double const message) noexcept { print(number__to__string(message)); }
    inline void print(short const message) noexcept { print((long) message); }
    inline void print(unsigned int const message) noexcept { print((unsigned long) message); }
    inline void print(unsigned long const message) noexcept { if (message > 1e9) print(number__to__string(message)); else if (message) { for (unsigned long iterator = 1e9, trailing = true; iterator; iterator /= 10u) { unsigned char const digit = (message % (iterator * 10u)) / iterator; if (digit || false == trailing) { print(*("0123456789" + digit)); trailing = false; } } } else print('0'); }
    inline void print(unsigned short const message) noexcept { print((unsigned long) message); }
    template <typename type> inline void print(type* const message) noexcept { print(pointer__to__string(message)); }
    template <typename type, typename... types> inline void print(type message, types... messages) noexcept { print(message); print(messages...); }

    inline void println(void) noexcept { ::write(STDOUT_FILENO, "\n\r", 2u); }
    inline void println(char* const message) noexcept { print(message); println(); }
    inline void println(char const* const message) noexcept { print(message); println(); }
    inline void println(double const message) noexcept { println((long double) message); }
    inline void println(float const message) noexcept { println((long double) message); }
    inline void println(int const message) noexcept { println((long) message); }
    inline void println(long const message) noexcept { if (message < 0L) print('-'); println((unsigned long) (message < 0L ? -message : message)); }
    inline void println(long double const message) noexcept { print(message); println(); }
    inline void println(short const message) noexcept { println((long) message); }
    inline void println(unsigned int const message) noexcept { println((unsigned long) message); }
    inline void println(unsigned long const message) noexcept { if (message > 1e9) { for (unsigned long iterator = message; iterator; iterator /= 10u) print(' '); for (unsigned long iterator = message; iterator; iterator /= 10u) { print('\b'); print(*("0123456789" + (iterator % 10u))); print('\b'); } } else print(message); println(); }
    inline void println(unsigned short const message) noexcept { println((unsigned long) message); }
    template <typename type> inline void println(type* const message) noexcept { if (message) { ::write(STDOUT_FILENO, "0x", 2u); for (unsigned int iterator = (int) message; iterator; iterator >>= 4u) print(' '); for (unsigned int iterator = (int) message; iterator; iterator >>= 4u) { print('\b'); print(*("0123456789ABCDEF" + (iterator % 16u))); print('\b'); } } else ::write(STDOUT_FILENO, "NULL", 4u); println(); }
    template <typename... types> inline void println(types... messages) noexcept { print(messages...); println(); }

    /* String to Number
            --- NOTE ---
                #Lapys:
                    - Evaluates the exponent (in its standard form) with a natural base.
                    - Floating-point non-natural-base numbers are allowed e.g.: `2EF.F8`.
                    - Returns the type of `long double` for consistency.
                    - Suffices apply to all base forms.
    */
    constexpr inline long double string__to__number(char const string) noexcept { switch (string) { case '0': return 0.00; case '1': return 1.00; case '2': return 2.00; case '3': return 3.00; case '4': return 4.00; case '5': return 5.00; case '6': return 6.00; case '7': return 7.00; case '8': return 8.00; case '9': return 9.00; } return NAN; }
    inline long double string__to__number(char* string) noexcept { if (string && '\0' ^ *string) { if ('\0' == *string || 0 == ::strncmp(string, "nan", 4u) || 0 == ::strncmp(string, "NaN", 4u) || 0 == ::strncmp(string, "NAN", 4u)) return NAN; else if (0 == ::strncmp(string, "inf", 4u) || 0 == ::strncmp(string, "infinity", 9u) || 0 == ::strncmp(string, "Infinity", 9u) || 0 == ::strncmp(string, "INFINITY", 9u)) return INFINITY; else { char character = *string; long double number = 0.00L; char *numberBinaryCharacteristicsComponent = NULL, *numberBinaryMantissaComponent = NULL; unsigned short numberBinaryCharacteristicsLength = 0u, numberBinaryMantissaLength = 0u; static char numberComponents[SHRT_MAX] {0}; char *numberDecimalCharacteristicsComponent = NULL, *numberDecimalMantissaComponent = NULL; unsigned short numberDecimalCharacteristicsLength = 0u, numberDecimalMantissaLength = 0u; char *numberHexadecimalCharacteristicsComponent = NULL, *numberHexadecimalMantissaComponent = NULL; unsigned short numberHexadecimalCharacteristicsLength = 0u, numberHexadecimalMantissaLength = 0u; char *numberOctalCharacteristicsComponent = NULL, *numberOctalMantissaComponent = NULL; unsigned short numberOctalCharacteristicsLength = 0u, numberOctalMantissaLength = 0u; char *numberScientificExponentComponent = NULL; unsigned char numberScientificExponentLength = 0u; bool numberSignedness = false; static char numberSuffixComponent[3] {0}; unsigned char numberSuffixLength = 0u; bool parseContinue = true; enum {binary_characteristics, binary_mantissa, decimal_characteristics, decimal_mantissa, hexadecimal_characteristics, hexadecimal_mantissa, octal_characteristics, octal_mantissa, scientific_exponent, suffix, trailing} parseState = trailing; for (size_t iterator = 0u; parseContinue && ('\0' ^ character); character = *(string + ++iterator)) switch (parseState) { case binary_characteristics: switch (character) { case '.': numberBinaryMantissaComponent = numberBinaryCharacteristicsComponent + (numberBinaryCharacteristicsLength + 1u); parseContinue = '\0' ^ *(string + (iterator + 1u)); parseState = binary_mantissa; (string += iterator, iterator = 0u); break; case 'E': case 'e': numberScientificExponentComponent = numberBinaryCharacteristicsComponent + (numberBinaryCharacteristicsLength + 1u); parseContinue = (1u ^ iterator) && ('\0' ^ *(string + (iterator + 1u))); parseState = scientific_exponent; (string += iterator, iterator = 0u); break; case 'F': case 'f': case 'L': case 'l': case 'n': case 'U': case 'u': --iterator; parseContinue = 1u ^ iterator; parseState = suffix; break; case '0': case '1': *(numberBinaryCharacteristicsComponent + numberBinaryCharacteristicsLength++) = character; break; default: parseContinue = false; break; } break; case binary_mantissa: switch (character) { case 'E': case 'e': numberScientificExponentComponent = numberBinaryMantissaComponent + (numberBinaryMantissaLength + 1u); parseContinue = (1u ^ iterator) && ('\0' ^ *(string + (iterator + 1u))); parseState = scientific_exponent; (string += iterator, iterator = 0u); break; case 'F': case 'f': case 'L': case 'l': parseContinue = 1u ^ iterator--; parseState = suffix; break; case '0': case '1': *(numberBinaryMantissaComponent + numberBinaryMantissaLength++) = character; break; default: parseContinue = false; break; } break; case decimal_characteristics: switch (character) { case '.': numberDecimalMantissaComponent = numberDecimalCharacteristicsComponent + (numberDecimalCharacteristicsLength + 1u); parseContinue = '\0' ^ *(string + (iterator + 1u)); parseState = decimal_mantissa; (string += iterator, iterator = 0u); break; case 'B': case 'b': numberDecimalCharacteristicsLength = 0u; numberBinaryCharacteristicsComponent = numberComponents; parseContinue = 1u == iterator && '0' == *string && ('\0' ^ *(string + (iterator + 1u))); parseState = binary_characteristics; (string += iterator, iterator = 0u); break; case 'E': case 'e': numberScientificExponentComponent = numberDecimalCharacteristicsComponent + (numberDecimalCharacteristicsLength + 1u); parseContinue = '\0' ^ *(string + (iterator + 1u)); parseState = scientific_exponent; (string += iterator, iterator = 0u); break; case 'F': case 'f': case 'L': case 'l': case 'n': case 'U': case 'u': --iterator; parseState = suffix; break; case 'X': case 'x': numberDecimalCharacteristicsLength = 0u; numberHexadecimalCharacteristicsComponent = numberComponents; parseContinue = 1u == iterator && '0' == *string && ('\0' ^ *(string + (iterator + 1u))); parseState = hexadecimal_characteristics; (string += iterator, iterator = 0u); break; case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': if ('0' == *string) { numberDecimalCharacteristicsLength = 0u; numberOctalCharacteristicsComponent = numberComponents; parseState = octal_characteristics; (string += iterator - 1u, iterator = 0u); } else *(numberDecimalCharacteristicsComponent + numberDecimalCharacteristicsLength++) = character; break; default: parseContinue = false; break; } break; case decimal_mantissa: switch (character) { case 'E': case 'e': numberScientificExponentComponent = numberDecimalMantissaComponent + (numberDecimalMantissaLength + 1u); parseContinue = (1u ^ iterator) && ('\0' ^ *(string + (iterator + 1u))); parseState = scientific_exponent; (string += iterator, iterator = 0u); break; case 'F': case 'f': case 'L': case 'l': parseContinue = 1u ^ iterator--; parseState = suffix; break; case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': *(numberDecimalMantissaComponent + numberDecimalMantissaLength++) = character; break; default: parseContinue = false; break; } break; case hexadecimal_characteristics: switch (character) { case '.': numberHexadecimalMantissaComponent = numberHexadecimalCharacteristicsComponent + (numberHexadecimalCharacteristicsLength + 1u); parseContinue = '\0' ^ *(string + (iterator + 1u)); parseState = hexadecimal_mantissa; (string += iterator, iterator = 0u); break; case 'L': case 'l': case 'n': case 'U': case 'u': --iterator; parseContinue = 1u ^ iterator; parseState = suffix; break; case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case 'A': case 'a': case 'B': case 'b': case 'C': case 'c': case 'D': case 'd': case 'E': case 'e': case 'F': case 'f': *(numberHexadecimalCharacteristicsComponent + numberHexadecimalCharacteristicsLength++) = character; break; default: parseContinue = false; break; } break; case hexadecimal_mantissa: switch (character) { case 'L': case 'l': parseContinue = 1u ^ iterator--; parseState = suffix; break; case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case 'A': case 'a': case 'B': case 'b': case 'C': case 'c': case 'D': case 'd': case 'E': case 'e': case 'F': case 'f': *(numberHexadecimalMantissaComponent + numberHexadecimalMantissaLength++) = character; break; default: parseContinue = false; break; } break; case octal_characteristics: switch (character) { case '.': numberOctalMantissaComponent = numberOctalCharacteristicsComponent + (numberOctalCharacteristicsLength + 1u); parseContinue = '\0' ^ *(string + (iterator + 1u)); parseState = octal_mantissa; (string += iterator, iterator = 0u); break; case 'E': case 'e': numberScientificExponentComponent = numberOctalCharacteristicsComponent + (numberOctalCharacteristicsLength + 1u); parseContinue = (1u ^ iterator) && ('\0' ^ *(string + (iterator + 1u))); parseState = scientific_exponent; (string += iterator, iterator = 0u); break; case 'F': case 'f': case 'L': case 'l': case 'n': case 'U': case 'u': --iterator; parseContinue = 1u ^ iterator; parseState = suffix; break; case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': *(numberOctalCharacteristicsComponent + numberOctalCharacteristicsLength++) = character; break; default: parseContinue = false; break; } break; case octal_mantissa: switch (character) { case 'E': case 'e': numberScientificExponentComponent = numberOctalMantissaComponent + (numberOctalMantissaLength + 1u); parseContinue = (1u ^ iterator) && ('\0' ^ *(string + (iterator + 1u))); parseState = scientific_exponent; (string += iterator, iterator = 0u); break; case 'F': case 'f': case 'L': case 'l': parseContinue = 1u ^ iterator--; parseState = suffix; break; case '0': case '1': *(numberOctalMantissaComponent + numberOctalMantissaLength++) = character; break; default: parseContinue = false; break; } break; case scientific_exponent: switch (character) { case '-': parseContinue = 1u == iterator; *(numberScientificExponentComponent + numberScientificExponentLength++) = character; break; case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': *(numberScientificExponentComponent + numberScientificExponentLength++) = character; break; default: parseContinue = false; break; } break; case suffix: switch (character) { case 'F': case 'f': case 'L': case 'l': case 'n': case 'U': case 'u': parseContinue = numberSuffixLength ^ (sizeof(numberSuffixComponent) / sizeof(char)); *(numberSuffixComponent + numberSuffixLength++) = character; break; default: parseContinue = false; break; } break; case trailing: switch (character) { case '-': numberSignedness = !numberSignedness; break; case '.': numberDecimalMantissaComponent = numberComponents; parseContinue = '\0' ^ *(string + (iterator + 1u)); parseState = decimal_mantissa; (string += iterator, iterator = 0u); break; case '+': case ' ': case '\b': case '\n': case '\r': case '\t': case '\v': break; case '0': parseState = decimal_characteristics; (string += iterator, iterator = 0u); *((numberDecimalCharacteristicsComponent = numberComponents) + numberDecimalCharacteristicsLength++) = character; break; case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': parseState = decimal_characteristics; *((numberDecimalCharacteristicsComponent = numberComponents) + numberDecimalCharacteristicsLength++) = character; break; default: parseContinue = false; break; } break; } if (false == parseContinue || (1u == numberScientificExponentLength && '-' == *numberScientificExponentComponent) || (numberSuffixLength && ((numberBinaryMantissaLength || numberDecimalMantissaLength || numberHexadecimalMantissaLength || numberOctalMantissaLength) && (0 == ::strncmp(numberSuffixComponent, "LL", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "ll", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "n", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "u", 1u))))) number = NAN; else { long double component; long double multiplier; if (numberBinaryCharacteristicsLength) { component = 1.00L; for (int iterator = numberBinaryCharacteristicsLength - 1u; ~iterator; --iterator) { if ('1' == *(numberBinaryCharacteristicsComponent + iterator)) number += component; component *= 2.00L; } } if (numberBinaryMantissaLength) { component = 1.00L; for (char *iterator = numberBinaryMantissaComponent + (numberBinaryMantissaLength - 1u); '0' == *iterator; --iterator) --numberBinaryMantissaLength; for (unsigned short iterator = 0u; iterator ^ numberBinaryMantissaLength; ++iterator) { component /= 2.00L; if ('1' == *(numberBinaryMantissaComponent + iterator)) number += component; } } if (numberDecimalCharacteristicsLength) { multiplier = 1.00L; for (int iterator = numberDecimalCharacteristicsLength - 1u; ~iterator; --iterator) { component = string__to__number(*(numberDecimalCharacteristicsComponent + iterator)) * multiplier; multiplier *= 10.00L; number += component; } } if (numberDecimalMantissaLength) { multiplier = 1.00L; for (char *iterator = numberDecimalMantissaComponent + (numberDecimalMantissaLength - 1u); '0' == *iterator; --iterator) --numberDecimalMantissaLength; for (unsigned short iterator = 0u; iterator ^ numberDecimalMantissaLength; ++iterator) { multiplier /= 10.00L; component = string__to__number(*(numberDecimalMantissaComponent + iterator)) * multiplier; number += component; } } if (numberHexadecimalCharacteristicsLength) { multiplier = 1.00L; for (int iterator = numberHexadecimalCharacteristicsLength - 1u; ~iterator; --iterator) { switch (*(numberHexadecimalCharacteristicsComponent + iterator)) { case 'A': case 'a': component = 10.00L; break; case 'B': case 'b': component = 11.00L; break; case 'C': case 'c': component = 12.00L; break; case 'D': case 'd': component = 13.00L; break; case 'E': case 'e': component = 14.00L; break; case 'F': case 'f': component = 15.00L; break; default: component = string__to__number(*(numberHexadecimalCharacteristicsComponent + iterator)); break; } component *= multiplier; multiplier *= 16.00L; number += component; } } if (numberHexadecimalMantissaLength) { multiplier = 1.00L; for (char *iterator = numberHexadecimalMantissaComponent + (numberHexadecimalMantissaLength - 1u); '0' == *iterator; --iterator) --numberHexadecimalMantissaLength; for (unsigned short iterator = 0u; iterator ^ numberHexadecimalMantissaLength; ++iterator) { multiplier /= 16.00L; switch (*(numberHexadecimalMantissaComponent + iterator)) { case 'A': case 'a': component = 10.00L; break; case 'B': case 'b': component = 11.00L; break; case 'C': case 'c': component = 12.00L; break; case 'D': case 'd': component = 13.00L; break; case 'E': case 'e': component = 14.00L; break; case 'F': case 'f': component = 15.00L; break; default: component = string__to__number(*(numberHexadecimalMantissaComponent + iterator)); break; } component *= multiplier; number += component; } } if (numberOctalCharacteristicsLength) { multiplier = 1.00L; for (int iterator = numberOctalCharacteristicsLength - 1u; ~iterator; --iterator) { component = string__to__number(*(numberOctalCharacteristicsComponent + iterator)) * multiplier; multiplier *= 8.00L; number += component; } } if (numberOctalMantissaLength) { multiplier = 1.00L; for (char *iterator = numberOctalMantissaComponent + (numberOctalMantissaLength - 1u); '0' == *iterator; --iterator) --numberOctalMantissaLength; for (unsigned short iterator = 0u; iterator ^ numberOctalMantissaLength; ++iterator) { multiplier /= 8.00L; component = string__to__number(*(numberOctalMantissaComponent + iterator)) * multiplier; number += component; } } if (numberScientificExponentLength) { unsigned short exponent = 0u; bool exponentSignedness = false; multiplier = 1.00L; if ('-' == *numberScientificExponentComponent) { exponentSignedness = true; ++numberScientificExponentComponent; --numberScientificExponentLength; } for (int iterator = numberScientificExponentLength - 1u; ~iterator; --iterator) { component = string__to__number(*(numberScientificExponentComponent + iterator)) * multiplier; multiplier *= 10.00L; exponent += component; } if (exponentSignedness) for (unsigned short iterator = 0u; exponent ^ iterator; ++iterator) number /= 10.00; else for (unsigned short iterator = 0u; exponent ^ iterator; ++iterator) number *= 10.00; } if (numberSignedness) number = -number; switch (numberSuffixLength) { case 1u: if ('F' == *numberSuffixComponent || 'f' == *numberSuffixComponent) number = (float) number; else if ('U' == *numberSuffixComponent || 'u' == *numberSuffixComponent) number = (unsigned int) number; else if ('n' == *numberSuffixComponent) number = ::trunc(number); else if ('L' == *numberSuffixComponent || 'l' == *numberSuffixComponent) if (0u == numberBinaryMantissaLength + numberDecimalMantissaLength + numberHexadecimalMantissaLength + numberOctalMantissaLength) number = (signed long) number; break; case 2u: if (0 == ::strncmp(numberSuffixComponent, "LL", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "ll", numberSuffixLength)) number = (signed long long) number; else if (0 == ::strncmp(numberSuffixComponent, "UL", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "Ul", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "uL", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "ul", numberSuffixLength)) number = (unsigned long) number; break; case 3u: if (0 == ::strncmp(numberSuffixComponent, "ULL", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "Ull", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "uLL", numberSuffixLength) || 0 == ::strncmp(numberSuffixComponent, "ull", numberSuffixLength)) number = (unsigned long long) number; break; } } return number; } } else return NAN; }
    long double string__to__number(char const* const string) noexcept { return string__to__number((char*) string); }

/* Main */
int main(int const argc, char const* argv[]) {
    // [Begin] ...
    println("[PROGRAM INITIATED]");

    // ...
    println("    [Number: ", 2508u, ", String: \"", number__to__string(2508u), "\"]");
    println("    [Number: ", -2508, ", String: \"", number__to__string(-2508), "\"]");
    println("    [Number: ", -1u, ", String: \"", number__to__string(-1u), "\"]");
    println("    [Number: ", -25.08f, ", String: \"", number__to__string(-25.08f), "\"]");
    println("    [Number: ", .01, ", String: \"", number__to__string(.01), "\"]");
    println("    [Number: ", .012, ", String: \"", number__to__string(.012), "\"]");
    println("    [Number: ", .0123, ", String: \"", number__to__string(.0123), "\"]");
    println("    [Number: ", .01234, ", String: \"", number__to__string(.01234), "\"]");
    println("    [Number: ", .012345, ", String: \"", number__to__string(.012345), "\"]");
    println("    [Number: ", .0123456, ", String: \"", number__to__string(.0123456), "\"]");
    println("    [Number: ", .01234567, ", String: \"", number__to__string(.01234567), "\"]");
    println("    [Number: ", .012345678, ", String: \"", number__to__string(.012345678), "\"]");
    println("    [Number: ", .0123456789, ", String: \"", number__to__string(.0123456789), "\"]");
    println("    [Number: ", 22.00 / 7.00, ", String: \"", number__to__string(22.00 / 7.00), "\"]");
    println("    [Number: ", M_PI, ", String: \"", number__to__string(M_PI), "\"]");
    println("    [Number: ", INFINITY, ", String: \"", number__to__string(INFINITY), "\"]");
    println("    [Number: ", NAN, ", String: \"", number__to__string(NAN), "\"]");
    println("    [Number: ", FLT_MAX, ", String: \"", number__to__string(FLT_MAX), "\"]");
    println("    [Number: ", DBL_MAX, ", String: \"", number__to__string(DBL_MAX), "\"]");
    println("    [Number: ", LDBL_MAX, ", String: \"", number__to__string(LDBL_MAX), "\"]");
    println();

    println("    [Pointer: ", &argc, ", String: \"", pointer__to__string(&argc), "\"]");
    println("    [Pointer: ", &argv, ", String: \"", pointer__to__string(&argv), "\"]");
    println();

    println("    [String: '", '-', "', Number: ", string__to__number('-'), "]");
    println("    [String: '", 'f', "', Number: ", string__to__number('f'), "]");
    println("    [String: '", 'L', "', Number: ", string__to__number('L'), "]");
    println("    [String: '", '.', "', Number: ", string__to__number('.'), "]");
    println("    [String: '", '0', "', Number: ", string__to__number('0'), "]");
    println("    [String: '", '1', "', Number: ", string__to__number('1'), "]");
    println("    [String: \"", "0", "\", Number: ", string__to__number("0"), "]");
    println("    [String: \"", "1", "\", Number: ", string__to__number("1"), "]");
    println("    [String: \"", ".e1", "\", Number: ", string__to__number(".e1"), "]");
    println("    [String: \"", ".f", "\", Number: ", string__to__number(".f"), "]");
    println("    [String: \"", "-1", "\", Number: ", string__to__number("-1"), "]");
    println("    [String: \"", "-1f", "\", Number: ", string__to__number("-1f"), "]");
    println("    [String: \"", "12.5u", "\", Number: ", string__to__number("12.5u"), "]");
    println("    [String: \"", "-12u", "\", Number: ", string__to__number("-12u"), "]");
    println("    [String: \"", "--12u", "\", Number: ", string__to__number("--12u"), "]");
    println("    [String: \"", "-12uLLL", "\", Number: ", string__to__number("12uLLL"), "]");
    println("    [String: \"", "------------------------------------------------1", "\", Number: ", string__to__number("------------------------------------------------1"), "]");
    println("    [String: \"", "-------------------------------------------------1", "\", Number: ", string__to__number("-------------------------------------------------1"), "]");
    println("    [String: \"", ".3", "\", Number: ", string__to__number(".3"), "]");
    println("    [String: \"", ".5f", "\", Number: ", string__to__number(".5f"), "]");
    println("    [String: \"", ".55", "\", Number: ", string__to__number(".55"), "]");
    println("    [String: \"", ".555", "\", Number: ", string__to__number(".555"), "]");
    println("    [String: \"", "-25.08f", "\", Number: ", string__to__number("-25.08f"), "]");
    println("    [String: \"", "3.141592653589793", "\", Number: ", string__to__number("3.141592653589793"), "]");
    println("    [String: \"", "3.142857142857143f", "\", Number: ", string__to__number("3.142857142857143f"), "]");
    println("    [String: \"", "-.4f", "\", Number: ", string__to__number("-.4f"), "]");
    println("    [String: \"", "0b0", "\", Number: ", string__to__number("0b0"), "]");
    println("    [String: \"", "b0", "\", Number: ", string__to__number("b0"), "]");
    println("    [String: \"", "1b1", "\", Number: ", string__to__number("1b1"), "]");
    println("    [String: \"", "0b2", "\", Number: ", string__to__number("0b2"), "]");
    println("    [String: \"", "0b1", "\", Number: ", string__to__number("0b1"), "]");
    println("    [String: \"", "0b.101", "\", Number: ", string__to__number("0b.101"), "]");
    println("    [String: \"", "0be4", "\", Number: ", string__to__number("0be4"), "]");
    println("    [String: \"", "0b10", "\", Number: ", string__to__number("0b10"), "]");
    println("    [String: \"", "0b1e3", "\", Number: ", string__to__number("0b1e3"), "]");
    println("    [String: \"", "0b101.101", "\", Number: ", string__to__number("0b101.101"), "]");
    println("    [String: \"", "0b101.101e3", "\", Number: ", string__to__number("0b101.101e3"), "]");
    println("    [String: \"", "0b101.101LL", "\", Number: ", string__to__number("0b101.101LL"), "]");
    println("    [String: \"", "0b1001001", "\", Number: ", string__to__number("0b1001001"), "]");
    println("    [String: \"", "0b1001001f", "\", Number: ", string__to__number("0b1001001f"), "]");
    println("    [String: \"", "10b101", "\", Number: ", string__to__number("10b101"), "]");
    println("    [String: \"", "0x0", "\", Number: ", string__to__number("0x0"), "]");
    println("    [String: \"", "0x", "\", Number: ", string__to__number("0x"), "]");
    println("    [String: \"", "-0xDEADBEEF", "\", Number: ", string__to__number("-0xDEADBEEF"), "]");
    println("    [String: \"", "0xLaP1S", "\", Number: ", string__to__number("0xLaP1S"), "]");
    println("    [String: \"", "0x37f", "\", Number: ", string__to__number("0x37f"), "]");
    println("    [String: \"", "0x37.3f", "\", Number: ", string__to__number("0x37.3f"), "]");
    println("    [String: \"", "0x37e3", "\", Number: ", string__to__number("0x37e3"), "]");
    println("    [String: \"", "0x00000001", "\", Number: ", string__to__number("0x00000001"), "]");
    println("    [String: \"", "20x01", "\", Number: ", string__to__number("20x01"), "]");
    println("    [String: \"", ".2e3", "\", Number: ", string__to__number(".2e3"), "]");
    println("    [String: \"", "2e2", "\", Number: ", string__to__number("2e2"), "]");
    println("    [String: \"", "200000e-3", "\", Number: ", string__to__number("200000e-3"), "]");
    println("    [String: \"", "2e-", "\", Number: ", string__to__number("2e-"), "]");
    println("    [String: \"", "-.000002058e0011", "\", Number: ", string__to__number("-.000002058e0011"), "]");
    println("    [String: \"", "200000e-e-3", "\", Number: ", string__to__number("200000e-e-3"), "]");
    println("    [String: \"", "25", "\", Number: ", string__to__number("25"), "]");
    println("    [String: \"", "025", "\", Number: ", string__to__number("025"), "]");
    println("    [String: \"", "0025", "\", Number: ", string__to__number("0025"), "]");
    println("    [String: \"", "- - 41", "\", Number: ", string__to__number("- - 41"), "]");
    println("    [String: \"", "+ + 41", "\", Number: ", string__to__number("+ + 41"), "]");
    println("    [String: \"", "41fe3", "\", Number: ", string__to__number("41fe3"), "]");
    println("    [String: \"", "41e3f", "\", Number: ", string__to__number("41e3f"), "]");
    println("    [String: \"", "000000000000000001", "\", Number: ", string__to__number("000000000000000001"), "]");
    println("    [String: \"", "100000000000000001", "\", Number: ", string__to__number("100000000000000001"), "]");
    println("    [String: \"", "3n", "\", Number: ", string__to__number("3n"), "]");
    println("    [String: \"", "5.9n", "\", Number: ", string__to__number("5.9n"), "]");
    println("    [String: \"", "Infinity", "\", Number: ", string__to__number("Infinity"), "]");
    println("    [String: \"", "NaN", "\", Number: ", string__to__number("NaN"), "]");

    // [End] ...
    print("[PROGRAM TERMINATED]");

    // Return
    return EXIT_SUCCESS;
}
