/* Import */
#include <stdlib.h> // Standard Library

/* Function --- MINIFY (Lapys) --- NOTE (Lapys) -> Maximum radix of 36. */
    // [Binary -> ...]
    inline char const* binary__to__decimal(char const* const digits) noexcept;
    inline char const* binary__to__hexadecimal(char const* const digits) noexcept;
    inline char const* binary__to__octal(char const* const digits) noexcept;
    inline char const* binary__to__radix(char const* const digits) noexcept;

    // [Decimal -> ...]
    inline char const* decimal__to__binary(char const* const digits) noexcept;
    inline char const* decimal__to__hexadecimal(char const* const digits) noexcept;
    inline char const* decimal__to__octal(char const* const digits) noexcept;
    inline char const* decimal__to__radix(char const* const digits) noexcept;

    // [Hexadecimal -> ...]
    inline char const* hexadecimal__to__binary(char const* const digits) noexcept;
    inline char const* hexadecimal__to__decimal(char const* const digits) noexcept;
    inline char const* hexadecimal__to__octal(char const* const digits) noexcept;
    inline char const* hexadecimal__to__radix(char const* const digits) noexcept;

    // [Octal -> ...]
    inline char const* octal__to__binary(char const* const digits) noexcept;
    inline char const* octal__to__decimal(char const* const digits) noexcept;
    inline char const* octal__to__hexadecimal(char const* const digits) noexcept;
    inline char const* octal__to__radix(char const* const digits) noexcept;

    // [[Radix] -> ...]
    inline char const* radix__to__binary(char const* const digits) noexcept;
    inline char const* radix__to__decimal(char const* const digits) noexcept;
    inline char const* radix__to__hexadecimal(char const* const digits) noexcept;
    inline char const* radix__to__octal(char const* const digits) noexcept;
    inline char const* radix__to__radix(char const* const digits) noexcept;

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
