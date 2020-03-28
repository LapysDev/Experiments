/* Import */
#include <fcntl.h> // File Control --- NOTE (Lapys) -> Output.
#include <float.h> // Floating-Point --- NOTE (Lapys) -> Conversion assertion.
#include <math.h> // Mathematics --- NOTE (Lapys) -> Data assertion.
#include <stdio.h> // Standard Input-Output --- NOTE (Lapys) -> Output.
#include <stdlib.h> // Standard Library --- NOTE (Lapys) -> Output.
#include <string.h> // String --- NOTE (Lapys) -> Textual conversion.

#include <iostream>

/* Polyfill > ... */
#if !defined(INFINITY) && defined(HUGE_VAL)
#  define INFINITY HUGE_VAL
#endif

/* Definition > ...  --- NOTE (Lapys) -> Decimals are interpreted with a precision of 8 digits. */
    /* [Convert] */
    double number_to_integer(double const) noexcept;
    float number_to_integer(float const) noexcept;
    constexpr int number_to_integer(int const) noexcept;
    constexpr long number_to_integer(long const) noexcept;
    long double number_to_integer(long double const) noexcept;
    constexpr short number_to_integer(short const) noexcept;
    constexpr unsigned int number_to_integer(unsigned int const) noexcept;
    constexpr unsigned long number_to_integer(unsigned long const) noexcept;
    constexpr unsigned short number_to_integer(unsigned short const) noexcept;

    char const* number_to_string(double const) noexcept;
    char const* number_to_string(float const) noexcept;
    char const* number_to_string(int const) noexcept;
    char const* number_to_string(long const) noexcept;
    char const* number_to_string(long double const) noexcept;
    char const* number_to_string(short const) noexcept;
    char const* number_to_string(unsigned int const) noexcept;
    char const* number_to_string(unsigned long const) noexcept;
    char const* number_to_string(unsigned short const) noexcept;

    template <typename type> char const* pointer_to_string(type* const) noexcept;

    constexpr long double string_to_number(char const) noexcept;
    long double string_to_number(char* const) noexcept;
    long double string_to_number(char const* const) noexcept;

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
    // Number to Integer
    inline double number_to_integer(double const number) noexcept { return number_to_integer((long double) number); }
    inline float number_to_integer(float const number) noexcept { return number_to_integer((long double) number); }
    constexpr inline int number_to_integer(int const number) noexcept { return number; }
    constexpr inline long number_to_integer(long const number) noexcept { return number; }
    inline long double number_to_integer(long double const number) noexcept { if (::isfinite(number) && false == ::isnan(number) && ::isnormal(number)) { if (number < 0.00) return -number_to_integer(-number); else { double evaluation = 0.00; for (unsigned long increment = 1uL, overflow = 0uL; increment; overflow = 0uL) { for (increment = 1uL; evaluation + increment <= number && increment > overflow; increment <<= 1uL) { overflow = increment; } increment = increment == 1uL || increment <= overflow ? 0uL : increment >> 1uL; evaluation += increment; } return evaluation; } } else return number; }
    constexpr inline short number_to_integer(short const number) noexcept { return number; }
    constexpr inline unsigned int number_to_integer(unsigned int const number) noexcept { return number; }
    constexpr inline unsigned long number_to_integer(unsigned long const number) noexcept { return number; }
    constexpr inline unsigned short number_to_integer(unsigned short const number) noexcept { return number; }

    // Number to String
    inline char const* number_to_string(double const number) noexcept { return number_to_string((long double) number); }
    inline char const* number_to_string(float const number) noexcept { return number_to_string((long double) number); }
    inline char const* number_to_string(int const number) noexcept { return number_to_string((long) number); }
    inline char const* number_to_string(long const number) noexcept { static char string[21] {0}; ::strncpy(string + (number < 0L), number_to_string((unsigned long) (number < 0L ? -number : number)), sizeof(string)); if (number < 0L) *string = '-'; return (char const*) string; }
    inline char const* number_to_string(long double const number) noexcept { static char string[LDBL_MANT_DIG + 28] {0}; ::memset(string, '\0', sizeof(string)); if (::isinf(number)) ::strncpy(string, "-Infinity" + (number >= 0.00), 8u + (number < 0.00)); else if (::isnan(number)) ::strncpy(string, "NaN", 3u); else if (number && false == ::isnormal(number)) ::strncpy(string, "Denormalized", 12u); else { long double const characteristics = number_to_integer(number); long double const mantissa = number - characteristics; ::strcpy(string, number_to_string((long) characteristics)); if (mantissa) ::strncpy(&(*(string + ::strlen(string)) = '.'), number_to_string((long) number_to_integer((mantissa * 1e8) * (mantissa * 10.0 < 0.00 ? -1.00 : 1.00))), 8u); } return (char const*) string; }
    inline char const* number_to_string(short const number) noexcept { return number_to_string((long) number); }
    inline char const* number_to_string(unsigned int const number) noexcept { return number_to_string((unsigned long) number); }
    inline char const* number_to_string(unsigned long const number) noexcept { static char string[21] {0}; ::memset(string, '\0', sizeof(string)); *string = '0'; for (unsigned long index = 0u, iterator = number; iterator; iterator /= 10u) { *(string + index++) = *("0123456789" + (iterator % 10u)); if (iterator < 10u) for ((--index, iterator = 0u); iterator < index; (--index, ++iterator)) { *(string + index) ^= *(string + iterator); *(string + iterator) ^= *(string + index); *(string + index) ^= *(string + iterator); } } return (char const*) string; }
    inline char const* number_to_string(unsigned short const number) noexcept { return number_to_string((unsigned long) number); }

    // Pointer To String
    template <typename type> inline char const* pointer_to_string(type* const pointer) noexcept { static char string[10] {0}; if (pointer) { ::strncpy(string, "0x", 2u); ::memset(string + 2, '\0', sizeof(string) - (2u * sizeof(char))); for (unsigned int index = 2u, iterator = (int) pointer; iterator; iterator >>= 4u) { *(string + index++) = *("0123456789ABCDEF" + (iterator % 16u)); if (iterator < 16u) for ((--index, iterator = 2u); iterator < index; (--index, ++iterator)) { *(string + index) ^= *(string + iterator); *(string + iterator) ^= *(string + index); *(string + index) ^= *(string + iterator); } } } else ::strncpy(string, "NULL", 5u); return (char const*) string; }

    // Print
    constexpr inline void print(void) noexcept {}
    inline void print(char const message) noexcept { ::write(STDOUT_FILENO, &message, 1u); }
    inline void print(char* const message) noexcept { print((char const*) message); }
    inline void print(char const* const message) noexcept { if (message) { for (char *iterator = (char*) message; *(iterator++); ) if ('\0' == *iterator) ::write(STDOUT_FILENO, message, (size_t) (iterator - message)); } }
    inline void print(double const message) noexcept { print((long double) message); }
    inline void print(float const message) noexcept { print((long double) message); }
    inline void print(int const message) noexcept { print((long) message); }
    inline void print(long const message) noexcept { if (message < 0L) print('-'); print((unsigned long) (message < 0L ? -message : message)); }
    inline void print(long double const message) noexcept { if (::isinf(message)) ::write(STDOUT_FILENO, "-Infinity" + (message >= 0.00), 8u + (message < 0.00)); else if (::isnan(message)) ::write(STDOUT_FILENO, "NaN", 3u); else if (message && false == ::isnormal(message)) ::write(STDOUT_FILENO, "Denormalized", 12u); else { long double const characteristics = number_to_integer(message); long double mantissa = message - characteristics; print((long) characteristics); if (mantissa) { print('.'); print((long) number_to_integer((mantissa * 1e8) * (mantissa * 10.0 < 0.00 ? -1.00 : 1.00))); } } }
    inline void print(short const message) noexcept { print((long) message); }
    inline void print(unsigned int const message) noexcept { print((unsigned long) message); }
    inline void print(unsigned long const message) noexcept { if (message > 1e9) print(number_to_string(message)); else if (message) { for (unsigned long iterator = 1e9, trailing = true; iterator; iterator /= 10u) { unsigned char const digit = (message % (iterator * 10u)) / iterator; if (digit || false == trailing) { print(*("0123456789" + digit)); trailing = false; } } } else print('0'); }
    inline void print(unsigned short const message) noexcept { print((unsigned long) message); }
    template <typename type> inline void print(type* const message) noexcept { print(pointer_to_string(message)); }
    template <typename type, typename... types> inline void print(type message, types... messages) noexcept { print(message); print(messages...); }

    inline void println(void) noexcept { ::write(STDOUT_FILENO, "\n\r", 2u); }
    inline void println(char* const message) noexcept { print(message); println(); }
    inline void println(char const* const message) noexcept { print(message); println(); }
    inline void println(double const message) noexcept { println((long double) message); }
    inline void println(float const message) noexcept { println((long double) message); }
    inline void println(int const message) noexcept { println((long) message); }
    inline void println(long const message) noexcept { if (message < 0L) print('-'); println((unsigned long) (message < 0L ? -message : message)); }
    inline void println(long double const message) noexcept { if (::isinf(message)) ::write(STDOUT_FILENO, "-Infinity\n\r" + (message >= 0.00), 10u + (message < 0.00)); else if (::isnan(message)) ::write(STDOUT_FILENO, "NaN\n\r", 5u); else if (message && false == ::isnormal(message)) ::write(STDOUT_FILENO, "Denormalized\n\r", 14u); else { long double const characteristics = number_to_integer(message); if (message - characteristics) { print(message); println(); } else println((long) characteristics); } }
    inline void println(short const message) noexcept { println((long) message); }
    inline void println(unsigned int const message) noexcept { println((unsigned long) message); }
    inline void println(unsigned long const message) noexcept { if (message > 1e9) { for (unsigned long iterator = message; iterator; iterator /= 10u) print(' '); for (unsigned long iterator = message; iterator; iterator /= 10u) { print('\b'); print(*("0123456789" + (iterator % 10u))); print('\b'); } } else print(message); println(); }
    inline void println(unsigned short const message) noexcept { println((unsigned long) message); }
    template <typename type> inline void println(type* const message) noexcept { if (message) { ::write(STDOUT_FILENO, "0x", 2u); for (unsigned int iterator = (int) message; iterator; iterator >>= 4u) print(' '); for (unsigned int iterator = (int) message; iterator; iterator >>= 4u) { print('\b'); print(*("0123456789ABCDEF" + (iterator % 16u))); print('\b'); } } else ::write(STDOUT_FILENO, "NULL", 4u); println(); }
    template <typename... types> inline void println(types... messages) noexcept { print(messages...); println(); }

    // String to Number --- NOTE (Lapys) -> Return type of `long double` for consistency.
    constexpr inline long double string_to_number(char const string) noexcept { switch (string) { case '0': return 0.00; case '1': return 1.00; case '2': return 2.00; case '3': return 3.00; case '4': return 4.00; case '5': return 5.00; case '6': return 6.00; case '7': return 7.00; case '8': return 8.00; case '9': return 9.00; } return NAN; }
    inline long double string_to_number(char* const string) noexcept { return string_to_number((char const*) string); }
    inline long double string_to_number(char const* const string) noexcept {
        if (string) {
            if (0 == ::strncmp(string, "nan", 3u) || 0 == ::strncmp(string, "NaN", 3u)) return NAN;
            else if (0 == ::strncmp(string, "inf", 3u) || 0 == ::strncmp(string, "infinity", 8u) || 0 == ::strncmp(string, "Infinity", 8u)) return INFINITY;
            else if ('-' == *string) return -string_to_number(string + 1);
            else if (' ' == *string || '\b' == *string || '\n' == *string || '\r' == *string || '\t' == *string || '\v' == *string) return string_to_number(string + 1);
            else if ('\0' == *string) return NAN;
            else {
                long double number = 0.00;

                char binaryCharacteristics[20] {0}, binaryMantissa[20] {0}; unsigned char binaryCharacteristicsLength = 0u, binaryMantissaLength = 0u;
                char decimalCharacteristics[20] {0}, decimalMantissa[20] {0}; unsigned char decimalCharacteristicsLength = 0u, decimalMantissaLength = 0u;
                char exponentCharacteristics[5] {0}; unsigned char exponentCharacteristicsLength = 0u;
                char hexadecimalCharacteristics[20] {0}, hexadecimalMantissa[20] {0}; unsigned char hexadecimalCharacteristicsLength = 0u, hexadecimalMantissaLength = 0u;
                char octalCharacteristics[20] {0}, octalMantissa[20] {0}; unsigned char octalCharacteristicsLength = 0u, octalMantissaLength = 0u;
                char suffixes[3] {0}; unsigned char suffixesLength = 0u;

                enum {
                    binary_characteristics, binary_mantissa,
                    decimal_characteristics, decimal_mantissa,
                    hexadecimal_characteristics, hexadecimal_mantissa,
                    octal_characteristics, octal_mantissa,
                    scientific_notation,
                    suffix
                } state = decimal_characteristics;

                for (unsigned char continueParsing = true, iterator = 0u; continueParsing && *(string + iterator); ++iterator) {
                    char const& character = *(string + iterator);

                    switch (state) {
                        case binary_characteristics: switch (character) {
                            case '0': case '1': *(binaryCharacteristics + binaryCharacteristicsLength++) = character; break;
                            default: continueParsing = false; break;
                        } break;
                        case binary_mantissa: {} break;
                        case decimal_characteristics: switch (character) {
                            case '.': state = decimal_mantissa; break;
                            case 'b': if (iterator && *(string + (iterator + 1u))) state = binary_characteristics; else continueParsing = false; break;
                            case 'e': if (iterator && *(string + (iterator + 1u))) state = scientific_notation; else continueParsing = false; break;
                            case 'f': case 'F': case 'l': case 'L': case 'n': case 'u': case 'U': if (iterator) { --iterator; state = suffix; } else continueParsing = false; break;
                            case 'x': if (iterator && *(string + (iterator + 1u))) state = hexadecimal_characteristics; else continueParsing = false; break;
                            case '0': {
                                if (iterator) *(decimalCharacteristics + decimalCharacteristicsLength++) = character;
                                else switch (*(string + (iterator + 1u))) {
                                    case '.': ++iterator; state = decimal_mantissa; break;
                                    case 'b': ++iterator; state = binary_characteristics; break;
                                    case 'e': ++iterator; state = scientific_notation; break;
                                    case 'f': case 'F': case 'l': case 'L': case 'n': case 'u': case 'U': state = suffix; break;
                                    case 'x': ++iterator; state = hexadecimal_characteristics; break;
                                    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': state = octal_characteristics; break;
                                    default: continueParsing = false; break;
                                }
                            } break;
                            case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': *(decimalCharacteristics + decimalCharacteristicsLength++) = character; break;
                            default: continueParsing = false; break;
                        } break;
                        case decimal_mantissa: switch (character) {
                            case 'e': if ('.' == *(string + (iterator - 1u))) continueParsing = false; else state = scientific_notation; break;
                            case 'f': case 'F': if ('.' == *(string + (iterator - 1u))) continueParsing = false; else { --iterator; state = suffix; } break;
                            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': *(decimalMantissa + decimalMantissaLength++) = character; break;
                            default: continueParsing = false; break;
                        } break;
                        case hexadecimal_characteristics: switch (character) {
                            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case 'A': case 'a': case 'B': case 'b': case 'C': case 'c': case 'D': case 'd': case 'E': case 'e': case 'F': case 'f': *(hexadecimalCharacteristics + hexadecimalCharacteristicsLength++) = character; break;
                            default: continueParsing = false; break;
                        } break;
                        case hexadecimal_mantissa: {} break;
                        case octal_characteristics: switch (character) {
                            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': *(octalCharacteristics + octalCharacteristicsLength++) = character; break;
                            default: continueParsing = false; break;
                        } break;
                        case octal_mantissa: {} break;
                        case scientific_notation: switch (character) {
                            case '-': if ('e' ^ *(string + (iterator - 1u))) continueParsing = false; break;
                            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': *(exponentCharacteristics + exponentCharacteristicsLength++) = character; break;
                        } break;
                        case suffix: {} break;
                    }

                    if (false == continueParsing)
                    number = NAN;
                }

                if (false == ::isnan(number)) {
                    unsigned char iterator;
                    size_t multiplier;

                    // -.4f
                    // 0x
                    // 0xDEADBEEF

                    // [Suffixes]
                    if (suffixesLength && false == (
                        0 == ::strncmp(suffixes, "F", suffixesLength) || 0 == ::strncmp(suffixes, "f", suffixesLength) ||
                        0 == ::strncmp(suffixes, "L", suffixesLength) || 0 == ::strncmp(suffixes, "l", suffixesLength) ||
                        0 == ::strncmp(suffixes, "LL", suffixesLength) || 0 == ::strncmp(suffixes, "ll", suffixesLength) ||
                        0 == ::strncmp(suffixes, "UL", suffixesLength) || 0 == ::strncmp(suffixes, "Ul", suffixesLength) ||
                        0 == ::strncmp(suffixes, "ULL", suffixesLength) || 0 == ::strncmp(suffixes, "Ull", suffixesLength) ||
                        0 == ::strncmp(suffixes, "uL", suffixesLength) || 0 == ::strncmp(suffixes, "ul", suffixesLength) ||
                        0 == ::strncmp(suffixes, "uLL", suffixesLength) || 0 == ::strncmp(suffixes, "ull", suffixesLength)
                    )) number = NAN;

                    else {
                        // [Binary]
                        for ((iterator = 0u, multiplier = 1u); iterator ^ binaryCharacteristicsLength; ++iterator) multiplier *= 2u;
                        for ((iterator = 0u, multiplier /= 2u); iterator ^ binaryCharacteristicsLength; (++iterator, multiplier /= 2u)) number += multiplier * (*(binaryCharacteristics + iterator) == '1');

                        for ((iterator = 0u, multiplier = 2u); iterator ^ binaryMantissaLength; (++iterator, multiplier *= 2u)) number += ((float) (*(binaryMantissa + iterator) == '1')) / (float) multiplier;

                        // [Decimal]
                        for ((iterator = 0u, multiplier = 1u); iterator ^ decimalCharacteristicsLength; ++iterator) multiplier *= 10u;
                        for ((iterator = 0u, multiplier /= 10u); iterator ^ decimalCharacteristicsLength; (++iterator, multiplier /= 10u)) number += multiplier * string_to_number(*(decimalCharacteristics + iterator));

                        for ((iterator = 0u, multiplier = 10u); iterator ^ decimalMantissaLength; (++iterator, multiplier *= 10u)) number += string_to_number(*(decimalMantissa + iterator)) / (long double) multiplier;

                        // [Hexadecimal]
                        for ((iterator = 0u, multiplier = 1u); iterator ^ hexadecimalCharacteristicsLength; ++iterator) multiplier *= 16u;
                        for ((iterator = 0u, multiplier /= 16u); iterator ^ hexadecimalCharacteristicsLength; (++iterator, multiplier /= 16u)) {
                            switch (*(hexadecimalCharacteristics + iterator)) {
                                case 'A': case 'a': number += multiplier * 10u; break;
                                case 'B': case 'b': number += multiplier * 11u; break;
                                case 'C': case 'c': number += multiplier * 12u; break;
                                case 'D': case 'd': number += multiplier * 13u; break;
                                case 'E': case 'e': number += multiplier * 14u; break;
                                case 'F': case 'f': number += multiplier * 15u; break;
                                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': number += multiplier * string_to_number(*(hexadecimalCharacteristics + iterator)); break;
                            }
                        }

                        for ((iterator = 0u, multiplier = 16u); iterator ^ hexadecimalMantissaLength; (++iterator, multiplier *= 16u)) {
                            switch (*(hexadecimalMantissa + iterator)) {
                                case 'A': case 'a': number += 10.00 / (long double) multiplier; break;
                                case 'B': case 'b': number += 11.00 / (long double) multiplier; break;
                                case 'C': case 'c': number += 12.00 / (long double) multiplier; break;
                                case 'D': case 'd': number += 13.00 / (long double) multiplier; break;
                                case 'E': case 'e': number += 14.00 / (long double) multiplier; break;
                                case 'F': case 'f': number += 15.00 / (long double) multiplier; break;
                                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': number += string_to_number(*(hexadecimalMantissa + iterator)) / (long double) multiplier; break;
                            }
                        }

                        // [Octal]
                        for ((iterator = 0u, multiplier = 1u); iterator ^ octalCharacteristicsLength; ++iterator) multiplier *= 8u;
                        for ((iterator = 0u, multiplier /= 8u); iterator ^ octalCharacteristicsLength; (++iterator, multiplier /= 8u)) number += multiplier * string_to_number(*(octalCharacteristics + iterator));

                        for ((iterator = 0u, multiplier = 8u); iterator ^ octalMantissaLength; (++iterator, multiplier *= 8u)) number += string_to_number(*(octalMantissa + iterator)) / (long double) multiplier;

                        // [Exponent]
                        if (exponentCharacteristicsLength) {
                            size_t exponent = 0u;

                            for ((iterator = ('-' == *exponentCharacteristics), multiplier = 1u); iterator ^ exponentCharacteristicsLength; ++iterator) multiplier *= 10u;
                            for ((iterator = ('-' == *exponentCharacteristics), multiplier /= 10u); iterator ^ exponentCharacteristicsLength; (++iterator, multiplier /= 10u)) exponent += multiplier * string_to_number(*(exponentCharacteristics + iterator));

                            if ('-' == *exponentCharacteristics) for (iterator = 0u; iterator ^ exponent; ++iterator) number /= 10.00;
                            else for (iterator = 0u; iterator ^ exponent; ++iterator) number *= 10.00;
                        }
                    }
                }

                return number;
            }
        } else return NAN;
    }

/* Main */
int main(int const argc, char const* argv[]) {
    // [Begin] ...
    println("[PROGRAM INITIATED]");

    // ...
    println("    [Number: ", -20.25, ", Integer: \"", number_to_integer(-20.25), "\"]");
    println("    [Number: ", 22.00 / 7.00, ", Integer: \"", number_to_integer(22.00 / 7.00), "\"]");
    println("    [Number: ", M_PI, ", Integer: \"", number_to_integer(M_PI), "\"]");
    println("    [Number: ", INFINITY, ", Integer: \"", number_to_integer(INFINITY), "\"]");
    println("    [Number: ", NAN, ", Integer: \"", number_to_integer(NAN), "\"]");
    println();

    println("    [Number: ", 0u, ", String: \"", number_to_string(0u), "\"]");
    println("    [Number: ", 2025u, ", String: \"", number_to_string(2025u), "\"]");
    println("    [Number: ", -2025, ", String: \"", number_to_string(-2025), "\"]");
    println("    [Number: ", -1u, ", String: \"", number_to_string(-1u), "\"]");
    println("    [Number: ", -20.25, ", String: \"", number_to_string(-20.25), "\"]");
    println("    [Number: ", 22.00 / 7.00, ", String: \"", number_to_string(22.00 / 7.00), "\"]");
    println("    [Number: ", M_PI, ", String: \"", number_to_string(M_PI), "\"]");
    println("    [Number: ", INFINITY, ", String: \"", number_to_string(INFINITY), "\"]");
    println("    [Number: ", NAN, ", String: \"", number_to_string(NAN), "\"]");
    println();

    println("    [Pointer: ", &argc, ", String: \"", pointer_to_string(&argc), "\"]");
    println("    [Pointer: ", &argv, ", String: \"", pointer_to_string(&argv), "\"]");
    println();

    println("    [String: '", '-', "', Number: ", string_to_number('-'), "]");
    println("    [String: '", 'f', "', Number: ", string_to_number('f'), "]");
    println("    [String: '", 'L', "', Number: ", string_to_number('L'), "]");
    println("    [String: '", '.', "', Number: ", string_to_number('.'), "]");
    println("    [String: '", '0', "', Number: ", string_to_number('0'), "]");
    println("    [String: '", '1', "', Number: ", string_to_number('1'), "]");
    println("    [String: \"", ".e1", "\", Number: ", string_to_number(".e1"), "]");
    println("    [String: \"", ".f", "\", Number: ", string_to_number(".f"), "]");
    println("    [String: \"", "-1", "\", Number: ", string_to_number("-1"), "]");
    println("    [String: \"", "-1f", "\", Number: ", string_to_number("-1f"), "]");
    println("    [String: \"", "--12u", "\", Number: ", string_to_number("--12u"), "]");
    println("    [String: \"", ".3", "\", Number: ", string_to_number(".3"), "]");
    println("    [String: \"", ".5f", "\", Number: ", string_to_number(".5f"), "]");
    println("    [String: \"", "3.141592653589793", "\", Number: ", string_to_number("3.141592653589793"), "]");
    println("    [String: \"", "3.142857142857143f", "\", Number: ", string_to_number("3.142857142857143f"), "]");
    println("    [String: \"", "-.4f", "\", Number: ", string_to_number("-.4f"), "]");
    println("    [String: \"", "0b0", "\", Number: ", string_to_number("0b0"), "]");
    println("    [String: \"", "b0", "\", Number: ", string_to_number("b0"), "]");
    println("    [String: \"", "0b2", "\", Number: ", string_to_number("0b2"), "]");
    println("    [String: \"", "0b10", "\", Number: ", string_to_number("0b10"), "]");
    println("    [String: \"", "0b1e3", "\", Number: ", string_to_number("0b1e3"), "]");
    println("    [String: \"", "0b1001001", "\", Number: ", string_to_number("0b1001001"), "]");
    println("    [String: \"", "0b1001001f", "\", Number: ", string_to_number("0b1001001f"), "]");
    println("    [String: \"", "0x0", "\", Number: ", string_to_number("0x0"), "]");
    println("    [String: \"", "0x", "\", Number: ", string_to_number("0x"), "]");
    println("    [String: \"", "-0xDEADBEEF", "\", Number: ", string_to_number("-0xDEADBEEF"), "]");
    println("    [String: \"", "0xLaP1S", "\", Number: ", string_to_number("0xLaP1S"), "]");
    println("    [String: \"", "0x37f", "\", Number: ", string_to_number("0x37f"), "]");
    println("    [String: \"", "0x37.0f", "\", Number: ", string_to_number("0x37.0f"), "]");
    println("    [String: \"", "0x37e3", "\", Number: ", string_to_number("0x37e3"), "]");
    println("    [String: \"", "0x00000001", "\", Number: ", string_to_number("0x00000001"), "]");
    println("    [String: \"", ".2e3", "\", Number: ", string_to_number(".2e3"), "]");
    println("    [String: \"", "2e2", "\", Number: ", string_to_number("2e2"), "]");
    println("    [String: \"", "25", "\", Number: ", string_to_number("25"), "]");
    println("    [String: \"", "025", "\", Number: ", string_to_number("025"), "]");
    println("    [String: \"", "0025", "\", Number: ", string_to_number("0025"), "]");
    println("    [String: \"", "Infinity", "\", Number: ", string_to_number("Infinity"), "]");
    println("    [String: \"", "NaN", "\", Number: ", string_to_number("NaN"), "]");

    // [End] ...
    print("[PROGRAM TERMINATED]");

    // Return
    return EXIT_SUCCESS;
}
