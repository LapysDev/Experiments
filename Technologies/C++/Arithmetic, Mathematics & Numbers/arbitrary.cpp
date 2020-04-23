/* Import */
#include <float.h> // Floating-Point
#include <math.h> // Mathematics
#include <stdlib.h> // Standard Library
#include <string.h> // String

#include <time.h>
#include <iostream>

/* Class > Big Number --- NOTE (Lapys) -> Arbitrary-precision natural-base numbers; code still applies for other bases. */
class BigNumber {
    // ...
    friend int main(void);

    // [...]
    private:
        // Definition > ((Characteristics, Mantissa) Length, Signedness, State, Value (Size))
        size_t characteristicsLength; // NOTE (Lapys) -> May be `0u` without `value` containing significant data.
        size_t mantissaLength;
        bool signedness;
        enum BigNumberState {DENORMALIZED, INFINITE, SAFE, UNCOMPUTABLE} state;
        char *value; // NOTE (Lapys) -> Keep the characteristics and mantissa co-joined in the same field.
        size_t valueSize; // NOTE (Lapys) -> Keep track of the dynamic size of the `value` member.

        // [Constructor]
        constexpr inline BigNumber(BigNumberState const state) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{state}, value{NULL}, valueSize{1u} {}

        // Function > (Allocate, Copy, Size, [Digit Manipulation] ...) --- MINIFY (Lapys)
        inline void allocate(void) noexcept { BigNumber::allocate(this -> characteristicsLength + this -> mantissaLength); }
        inline void allocate(size_t size) noexcept { size = BigNumber::size(size + 1u); size += (size & 1u); if (size > this -> valueSize) { this -> value = (char*) (NULL == this -> value ? ::malloc(size * sizeof(char)) : ::realloc(this -> value, size * sizeof(char))); this -> valueSize = size; } }
        inline void copy(BigNumber const& number)& noexcept { this -> signedness = number.signedness; this -> state = number.state; if (BigNumber::SAFE == number.state) { this -> characteristicsLength = number.characteristicsLength; this -> mantissaLength = number.mantissaLength; this -> valueSize = number.valueSize; if (BigNumber::isZero(number)) { std::free(this -> value); this -> value = NULL; } else { this -> value = (char*) (NULL == this -> value ? ::malloc(number.valueSize * sizeof(char)) : ::realloc(this -> value, number.valueSize * sizeof(char))); ::strncpy(this -> value, number.value, number.characteristicsLength + number.mantissaLength); } } }
        inline void copy(BigNumber const& number)&& noexcept { this -> characteristicsLength = number.characteristicsLength; this -> mantissaLength = number.mantissaLength; this -> signedness = number.signedness; this -> state = number.state; this -> value = number.value; this -> valueSize = number.valueSize; }
        inline size_t size(void) noexcept { return BigNumber::size(this -> characteristicsLength + this -> mantissaLength); }
        inline size_t size(size_t const size) noexcept { size_t evaluation; for (size_t former, iterator = 1u, recent = 0u; iterator <= size; ) { former = iterator; iterator += recent; recent = former; evaluation = iterator; } return evaluation; }

        inline static char const* add(char const digitA, char const digitB) noexcept { static char evaluation[3] {0}; if ('0' == digitA) { *evaluation = digitB; *(evaluation + 1) = '\0'; } else if ('0' == digitB) { *evaluation = digitA; *(evaluation + 1) = '\0'; } else switch (digitA) { case '1': switch (digitB) { case '1': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '0'; break; } break; case '2': switch (digitB) { case '1': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '1'; break; } break; case '3': switch (digitB) { case '1': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '2'; break; } break; case '4': switch (digitB) { case '1': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '3'; break; } break; case '5': switch (digitB) { case '1': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '4'; break; } break; case '6': switch (digitB) { case '1': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '5'; break; } break; case '7': switch (digitB) { case '1': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '5'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '6'; break; } break; case '8': switch (digitB) { case '1': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '5'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '6'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '7'; break; } break; case '9': switch (digitB) { case '1': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '2': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '5'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '6'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '7'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '8'; break; } break; } return (char const*) evaluation; } // NOTE (Lapys) -> Does not note "optimize" with the `BigNumber::increment(char const)` method.
        inline static char const* decrement(char const digit) noexcept { static char evaluation[3] {0}; switch (digit) { case '0': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '1': *evaluation = '0'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '9': *evaluation = '8'; *(evaluation + 1) = '\0'; break; } return (char const*) evaluation; }
        inline static char const* increment(char const digit) noexcept { static char evaluation[3] {0}; switch (digit) { case '0': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '1': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '0'; break; } return (char const*) evaluation; }
        inline static bool isEqual(char const digitA, char const digitB) noexcept { return digitA == digitB; } // WARN (Lapys) -> Only used with the `BigNumber::isEqual(BigNumber const&, BigNumber const&)` method.
        inline static bool isGreater(char const digitA, char const digitB) noexcept { bool evaluation = false; switch (digitA) { case '1': evaluation = '0' == digitB; break; case '2': evaluation = '0' == digitB || '1' == digitB; break; case '3': evaluation = '0' == digitB || '1' == digitB || '2' == digitB; break; case '4': evaluation = '0' == digitB || '1' == digitB || '2' == digitB || '3' == digitB; break; case '5': evaluation = '0' == digitB || '1' == digitB || '2' == digitB || '3' == digitB || '4' == digitB; break; case '6': evaluation = '0' == digitB || '1' == digitB || '2' == digitB || '3' == digitB || '4' == digitB || '5' == digitB; break; case '7': evaluation = '0' == digitB || '1' == digitB || '2' == digitB || '3' == digitB || '4' == digitB || '5' == digitB || '6' == digitB; break; case '8': evaluation = '0' == digitB || '1' == digitB || '2' == digitB || '3' == digitB || '4' == digitB || '5' == digitB || '6' == digitB || '7' == digitB; break; case '9': evaluation = digitA ^ digitB; break; } return evaluation; }
        inline static bool isLesser(char const digitA, char const digitB) noexcept { bool evaluation = false; switch (digitA) { case '0': evaluation = digitA ^ digitB; break; case '1': evaluation = '2' == digitB || '3' == digitB || '4' == digitB || '5' == digitB || '6' == digitB || '7' == digitB || '8' == digitB || '9' == digitB; break; case '2': evaluation = '3' == digitB || '4' == digitB || '5' == digitB || '6' == digitB || '7' == digitB || '8' == digitB || '9' == digitB; break; case '3': evaluation = '4' == digitB || '5' == digitB || '6' == digitB || '7' == digitB || '8' == digitB || '9' == digitB; break; case '4': evaluation = '5' == digitB || '6' == digitB || '7' == digitB || '8' == digitB || '9' == digitB; break; case '5': evaluation = '6' == digitB || '7' == digitB || '8' == digitB || '9' == digitB; break; case '6': evaluation = '7' == digitB || '8' == digitB || '9' == digitB; break; case '7': evaluation = '8' == digitB || '9' == digitB; break; case '8': evaluation = '9' == digitB; break; } return evaluation; }
        inline static char const* multiply(char const digitA, char const digitB) noexcept { static char evaluation[3] {0}; if ('0' == digitA || '0' == digitB) { *evaluation = '0'; *(evaluation + 1) = '\0'; } else if ('1' == digitA) { *evaluation = digitB; *(evaluation + 1) = '\0'; } else if ('1' == digitB) { *evaluation = digitA; *(evaluation + 1) = '\0'; } else switch (digitA) { case '2': switch (digitB) { case '2': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; } break; case '3': switch (digitB) { case '2': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '2'; *(evaluation + 1) = '1'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '2'; *(evaluation + 1) = '7'; *(evaluation + 2) = '\0'; break; } break; case '4': switch (digitB) { case '2': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '2'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '2'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '3'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '3'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; } break; case '5': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '2'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '2'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '3'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '3'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '4'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '4'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; } break; case '6': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '3'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '3'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '4'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '4'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '5'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; } break; case '7': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '1'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '2'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '3'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '4'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '4'; *(evaluation + 1) = '9'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '5'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '6'; *(evaluation + 1) = '3'; *(evaluation + 2) = '\0'; break; } break; case '8': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '3'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '4'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '4'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '5'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '6'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '7'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; } break; case '9': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '7'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '3'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '4'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '5'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '6'; *(evaluation + 1) = '3'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '7'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '8'; *(evaluation + 1) = '1'; *(evaluation + 2) = '\0'; break; } break; } return (char const*) evaluation; }
        inline static char const* subtract(char const digitA, char const digitB) noexcept { static char evaluation[3] {0}; if (digitA == digitB) { *evaluation = '0'; *(evaluation + 1) = '\0'; } else if ('0' == digitA) { *evaluation = '-'; *(evaluation + 1) = digitB; } else if ('0' == digitB) { *evaluation = digitA; *(evaluation + 1) = '\0'; } else switch (digitA) { case '1': switch (digitB) { case '2': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '3': *evaluation = '-'; *(evaluation + 1) = '2'; break; case '4': *evaluation = '-'; *(evaluation + 1) = '3'; break; case '5': *evaluation = '-'; *(evaluation + 1) = '4'; break; case '6': *evaluation = '-'; *(evaluation + 1) = '5'; break; case '7': *evaluation = '-'; *(evaluation + 1) = '6'; break; case '8': *evaluation = '-'; *(evaluation + 1) = '7'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '8'; break; } break; case '2': switch (digitB) { case '1': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '4': *evaluation = '-'; *(evaluation + 1) = '2'; break; case '5': *evaluation = '-'; *(evaluation + 1) = '3'; break; case '6': *evaluation = '-'; *(evaluation + 1) = '4'; break; case '7': *evaluation = '-'; *(evaluation + 1) = '5'; break; case '8': *evaluation = '-'; *(evaluation + 1) = '6'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '7'; break; } break; case '3': switch (digitB) { case '1': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '5': *evaluation = '-'; *(evaluation + 1) = '2'; break; case '6': *evaluation = '-'; *(evaluation + 1) = '3'; break; case '7': *evaluation = '-'; *(evaluation + 1) = '4'; break; case '8': *evaluation = '-'; *(evaluation + 1) = '5'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '6'; break; } break; case '4': switch (digitB) { case '1': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '6': *evaluation = '-'; *(evaluation + 1) = '2'; break; case '7': *evaluation = '-'; *(evaluation + 1) = '3'; break; case '8': *evaluation = '-'; *(evaluation + 1) = '4'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '5'; break; } break; case '5': switch (digitB) { case '1': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '7': *evaluation = '-'; *(evaluation + 1) = '2'; break; case '8': *evaluation = '-'; *(evaluation + 1) = '3'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '4'; break; } break; case '6': switch (digitB) { case '1': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '8': *evaluation = '-'; *(evaluation + 1) = '2'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '3'; break; } break; case '7': switch (digitB) { case '1': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '2'; break; } break; case '8': switch (digitB) { case '1': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '9': *evaluation = '-'; *(evaluation + 1) = '1'; break; } break; case '9': switch (digitB) { case '1': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '\0'; break; } break; } return (char const*) evaluation; }  // NOTE (Lapys) -> Does not note "optimize" with the `BigNumber::decrement(char const)` method.
        inline static long double toNumber(char const digit) noexcept { long double evaluation; switch (digit) { case '0': evaluation = 0.00L; break; case '1': evaluation = 1.00L; break; case '2': evaluation = 2.00L; break; case '3': evaluation = 3.00L; break; case '4': evaluation = 4.00L; break; case '5': evaluation = 5.00L; break; case '6': evaluation = 6.00L; break; case '7': evaluation = 7.00L; break; case '8': evaluation = 8.00L; break; case '9': evaluation = 9.00L; break; } return evaluation; }

    // [...]
    public:
        // Definition > (Infinity, Not-A-Number)
        static BigNumber const Infinity;
        static BigNumber const NaN;

        // [Constructor]
        constexpr inline BigNumber(void) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} {}
        inline BigNumber(double const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(float const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(int const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(long const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(long double const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(short const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(unsigned int const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(unsigned long const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(unsigned short const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(BigNumber const& number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(number); }
        inline BigNumber(BigNumber&& number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL}, valueSize{1u} { BigNumber::copy(number); }

        // [Destructor]
        inline ~BigNumber(void) { ::free(this -> value); }

        // (Definition, Function) > (Add, Decrement, Divide, Exponentiate, From Number, Get ..., Has ..., Increment, Is ..., Modulo, Multiply, Sign, Subtract, To ..., Unsign)
        BigNumber& add(BigNumber const&) noexcept;
        inline static BigNumber const add(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation {numberA}; evaluation.add(numberB); return evaluation; }
        inline static BigNumber const add(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::add(numberA, numberB); }
        inline static BigNumber const add(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::add(numberA, numberB); }
        inline static BigNumber const add(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::add(numberA, numberB); }

        BigNumber& decrement(void) noexcept;
        inline static BigNumber& decrement(BigNumber& number) noexcept { return number.decrement(); }
        inline static BigNumber& decrement(BigNumber&& number) noexcept { return BigNumber::decrement(number); }

        BigNumber& divide(BigNumber const&) noexcept;
        inline static BigNumber const divide(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation {numberA}; evaluation.divide(numberB); return evaluation; }
        inline static BigNumber const divide(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::divide(numberA, numberB); }
        inline static BigNumber const divide(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::divide(numberA, numberB); }
        inline static BigNumber const divide(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::divide(numberA, numberB); }

        BigNumber& exponentiate(BigNumber const&) noexcept;
        inline static BigNumber const exponentiate(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation {numberA}; evaluation.exponentiate(numberB); return evaluation; }
        inline static BigNumber const exponentiate(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::exponentiate(numberA, numberB); }
        inline static BigNumber const exponentiate(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::exponentiate(numberA, numberB); }
        inline static BigNumber const exponentiate(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::exponentiate(numberA, numberB); }

        inline static BigNumber const fromNumber(double const number) noexcept { return BigNumber::fromNumber((long double) number); }
        inline static BigNumber const fromNumber(float const number) noexcept { return BigNumber::fromNumber((long double) number); }
        inline static BigNumber const fromNumber(int const number) noexcept { return BigNumber::fromNumber((long) number); }
        static BigNumber const fromNumber(long const) noexcept;
        static BigNumber const fromNumber(long double const) noexcept;
        inline static BigNumber const fromNumber(short const number) noexcept { return BigNumber::fromNumber((long) number); }
        inline static BigNumber const fromNumber(unsigned int const number) noexcept { return BigNumber::fromNumber((unsigned long) number); }
        static BigNumber const fromNumber(unsigned long const) noexcept;
        inline static BigNumber const fromNumber(unsigned short const number) noexcept { return BigNumber::fromNumber((unsigned long) number); }

        long double getCharacteristics(void) const;
        inline static long double getCharacteristics(BigNumber const& number) { return number.getCharacteristics(); }
        inline static long double getCharacteristics(BigNumber&& number) { return BigNumber::getCharacteristics(number); }

        long double getMantissa(void) const;
        inline static long double getMantissa(BigNumber const& number) { return number.getMantissa(); }
        inline static long double getMantissa(BigNumber&& number) { return BigNumber::getMantissa(number); }

        bool hasSignificantCharacteristics(void) const noexcept;
        inline static bool hasSignificantCharacteristics(BigNumber const& number) noexcept { return number.hasSignificantCharacteristics(); }
        inline static bool hasSignificantCharacteristics(BigNumber&& number) noexcept { return BigNumber::hasSignificantCharacteristics(number); }

        bool hasSignificantMantissa(void) const noexcept;
        inline static bool hasSignificantMantissa(BigNumber const& number) noexcept { return number.hasSignificantMantissa(); }
        inline static bool hasSignificantMantissa(BigNumber&& number) noexcept { return BigNumber::hasSignificantMantissa(number); }

        BigNumber& increment(void) noexcept;
        inline static BigNumber& increment(BigNumber& number) noexcept { number.increment(); return number; }
        inline static BigNumber& increment(BigNumber&& number) noexcept { return BigNumber::increment(number); }

        bool isComputable(void) const noexcept;
        inline static bool isComputable(BigNumber const& number) noexcept { return number.isComputable(); }
        inline static bool isComputable(BigNumber&& number) noexcept { return BigNumber::isComputable(number); }

        inline bool isEqual(BigNumber const& number) const noexcept { return BigNumber::isEqual(*this, number); }
        inline bool isEqual(BigNumber&& number) const noexcept { return BigNumber::isEqual(number); }
        static bool isEqual(BigNumber const&, BigNumber const&) noexcept;
        static bool isEqual(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::isEqual(numberA, numberB); }
        static bool isEqual(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::isEqual(numberA, numberB); }
        static bool isEqual(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::isEqual(numberA, numberB); }

        bool isFinite(void) const noexcept;
        inline static bool isFinite(BigNumber const& number) noexcept { return number.isFinite(); }
        inline static bool isFinite(BigNumber&& number) noexcept { return BigNumber::isFinite(number); }

        inline bool isGreater(BigNumber const& number) const noexcept { return BigNumber::isGreater(*this, number); }
        inline bool isGreater(BigNumber&& number) const noexcept { return BigNumber::isGreater(number); }
        static bool isGreater(BigNumber const&, BigNumber const&) noexcept;
        static bool isGreater(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::isGreater(numberA, numberB); }
        static bool isGreater(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::isGreater(numberA, numberB); }
        static bool isGreater(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::isGreater(numberA, numberB); }

        bool isInfinite(void) const noexcept;
        inline static bool isInfinite(BigNumber const& number) noexcept { return number.isInfinite(); }
        inline static bool isInfinite(BigNumber&& number) noexcept { return BigNumber::isInfinite(number); }

        bool isIntegral(void) const noexcept;
        inline static bool isIntegral(BigNumber const& number) noexcept { return number.isIntegral(); }
        inline static bool isIntegral(BigNumber&& number) noexcept { return BigNumber::isIntegral(number); }

        inline bool isLesser(BigNumber const& number) const noexcept { return BigNumber::isLesser(*this, number); }
        inline bool isLesser(BigNumber&& number) const noexcept { return BigNumber::isLesser(number); }
        static bool isLesser(BigNumber const&, BigNumber const&) noexcept;
        static bool isLesser(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::isLesser(numberA, numberB); }
        static bool isLesser(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::isLesser(numberA, numberB); }
        static bool isLesser(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::isLesser(numberA, numberB); }

        bool isNaN(void) const noexcept;
        inline static bool isNaN(BigNumber const& number) noexcept { return number.isNaN(); }
        inline static bool isNaN(BigNumber&& number) noexcept { return BigNumber::isNaN(number); }

        bool isNegative(void) const noexcept;
        inline static bool isNegative(BigNumber const& number) noexcept { return number.isNegative(); }
        inline static bool isNegative(BigNumber&& number) noexcept { return BigNumber::isNegative(number); }

        bool isNormal(void) const noexcept;
        inline static bool isNormal(BigNumber const& number) noexcept { return number.isNormal(); }
        inline static bool isNormal(BigNumber&& number) noexcept { return BigNumber::isNormal(number); }

        bool isPositive(void) const noexcept;
        inline static bool isPositive(BigNumber const& number) noexcept { return number.isPositive(); }
        inline static bool isPositive(BigNumber&& number) noexcept { return BigNumber::isPositive(number); }

        bool isSafe(void) const noexcept;
        inline static bool isSafe(BigNumber const& number) noexcept { return number.isSafe(); }
        inline static bool isSafe(BigNumber&& number) noexcept { return BigNumber::isSafe(number); }

        bool isZero(void) const noexcept;
        inline static bool isZero(BigNumber const& number) noexcept { return number.isZero(); }
        inline static bool isZero(BigNumber&& number) noexcept { return BigNumber::isZero(number); }

        BigNumber& logarithmize(BigNumber const&) noexcept;
        inline static BigNumber const logarithmize(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation {numberA}; evaluation.logarithmize(numberB); return evaluation; }
        inline static BigNumber const logarithmize(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::logarithmize(numberA, numberB); }
        inline static BigNumber const logarithmize(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::logarithmize(numberA, numberB); }
        inline static BigNumber const logarithmize(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::logarithmize(numberA, numberB); }

        BigNumber& modulo(BigNumber const&) noexcept;
        inline static BigNumber const modulo(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation {numberA}; evaluation.modulo(numberB); return evaluation; }
        inline static BigNumber const modulo(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::modulo(numberA, numberB); }
        inline static BigNumber const modulo(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::modulo(numberA, numberB); }
        inline static BigNumber const modulo(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::modulo(numberA, numberB); }

        BigNumber& multiply(BigNumber const&) noexcept;
        inline static BigNumber const multiply(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation {numberA}; evaluation.multiply(numberB); return evaluation; }
        inline static BigNumber const multiply(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::multiply(numberA, numberB); }
        inline static BigNumber const multiply(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::multiply(numberA, numberB); }
        inline static BigNumber const multiply(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::multiply(numberA, numberB); }

        void reciprocate(void) noexcept;
        inline static BigNumber const reciprocate(BigNumber const& number) noexcept { BigNumber evaluation {number}; evaluation.reciprocate(); return evaluation; }

        void sign(bool const = false) noexcept;
        inline static BigNumber const sign(BigNumber const& number, bool const strict = false) noexcept { BigNumber evaluation {number}; evaluation.sign(strict); return evaluation; }

        BigNumber& subtract(BigNumber const&) noexcept;
        inline static BigNumber const subtract(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation {numberA}; evaluation.subtract(numberB); return evaluation; }
        inline static BigNumber const subtract(BigNumber const& numberA, BigNumber&& numberB) noexcept { return BigNumber::subtract(numberA, numberB); }
        inline static BigNumber const subtract(BigNumber&& numberA, BigNumber const& numberB) noexcept { return BigNumber::subtract(numberA, numberB); }
        inline static BigNumber const subtract(BigNumber&& numberA, BigNumber&& numberB) noexcept { return BigNumber::subtract(numberA, numberB); }

        static long double toNumber(BigNumber const&);
        static long double toNumber(BigNumber&& number) { return BigNumber::toNumber(number); }

        char const* toString(void) const noexcept;

        void unsign(void) noexcept;
        inline static BigNumber const unsign(BigNumber const& number) noexcept { BigNumber evaluation {number}; evaluation.unsign(); return evaluation; }

        // [Operator] > ...
        inline BigNumber const operator +(void) const& noexcept { return BigNumber {*this}; }
        inline BigNumber& operator +(void)&& noexcept { return *this; }
        inline BigNumber const operator +(BigNumber const& number) const noexcept { return BigNumber::add(*this, number); }
        inline BigNumber const operator +(BigNumber&& number) const noexcept { return BigNumber::operator +(number); }
        inline BigNumber const operator -(void) const& noexcept { return BigNumber::sign(*this); }
        inline BigNumber& operator -(void)&& noexcept { BigNumber::sign(); return *this; }
        inline BigNumber const operator -(BigNumber const& number) const noexcept { return BigNumber::subtract(*this, number); }
        inline BigNumber const operator -(BigNumber&& number) const noexcept { return BigNumber::operator -(number); }
        inline BigNumber const operator *(BigNumber const& number) const noexcept { return BigNumber::multiply(*this, number); }
        inline BigNumber const operator *(BigNumber&& number) const noexcept { return BigNumber::operator *(number); }
        inline BigNumber const operator /(BigNumber const& number) const noexcept { return BigNumber::divide(*this, number); }
        inline BigNumber const operator /(BigNumber&& number) const noexcept { return BigNumber::operator /(number); }
        inline BigNumber const operator %(BigNumber const& number) const noexcept { return BigNumber::modulo(*this, number); }
        inline BigNumber const operator %(BigNumber&& number) const noexcept { return BigNumber::operator %(number); }
        inline BigNumber& operator =(BigNumber const& number)& noexcept { BigNumber::copy(number); return *this; }
        inline BigNumber& operator =(BigNumber&& number)& noexcept { return BigNumber::operator =(number); }
        inline BigNumber& operator +=(BigNumber const& number)& noexcept { return BigNumber::add(number); }
        inline BigNumber& operator +=(BigNumber&& number)& noexcept { return BigNumber::operator +=(number); }
        inline BigNumber& operator -=(BigNumber const& number)& noexcept { return BigNumber::subtract(number); }
        inline BigNumber& operator -=(BigNumber&& number)& noexcept { return BigNumber::operator -=(number); }
        inline BigNumber& operator *=(BigNumber const& number)& noexcept { return BigNumber::multiply(number); }
        inline BigNumber& operator *=(BigNumber&& number)& noexcept { return BigNumber::operator *=(number); }
        inline BigNumber& operator /=(BigNumber const& number)& noexcept { return BigNumber::divide(number); }
        inline BigNumber& operator /=(BigNumber&& number)& noexcept { return BigNumber::operator /=(number); }
        inline BigNumber& operator %=(BigNumber const& number)& noexcept { return BigNumber::modulo(number); }
        inline BigNumber& operator %=(BigNumber&& number)& noexcept { return BigNumber::operator %=(number); }
        inline bool operator ==(BigNumber const& number) const noexcept { return BigNumber::isEqual(number); }
        inline bool operator ==(BigNumber&& number) const noexcept { return BigNumber::operator ==(number); }
        inline bool operator !=(BigNumber const& number) const noexcept { return false == BigNumber::operator ==(number); }
        inline bool operator !=(BigNumber&& number) const noexcept { return false == BigNumber::operator ==(number); }
        inline bool operator <(BigNumber const& number) const noexcept { return BigNumber::isLesser(number); }
        inline bool operator <(BigNumber&& number) const noexcept { return BigNumber::operator <(number); }
        inline bool operator >(BigNumber const& number) const noexcept { return BigNumber::isGreater(number); }
        inline bool operator >(BigNumber&& number) const noexcept { return BigNumber::operator >(number); }
        inline bool operator <=(BigNumber const& number) const noexcept { return BigNumber::operator ==(number) || BigNumber::operator <(number); }
        inline bool operator <=(BigNumber&& number) const noexcept { return BigNumber::operator <=(number); }
        inline bool operator >=(BigNumber const& number) const noexcept { return BigNumber::operator ==(number) || BigNumber::operator >(number); }
        inline bool operator >=(BigNumber&& number) const noexcept { return BigNumber::operator >=(number); }
        inline BigNumber operator ++(int const)& noexcept { BigNumber const evaluation {*this}; BigNumber::operator ++(); return evaluation; }
        inline BigNumber& operator ++(int const)&& noexcept { return BigNumber::operator ++(); }
        inline BigNumber& operator ++(void) noexcept { BigNumber::increment(); return *this; }
        inline BigNumber operator --(int const)& noexcept { BigNumber const evaluation {*this}; BigNumber::operator --(); return evaluation; }
        inline BigNumber& operator --(int const)&& noexcept { return BigNumber::operator --(); }
        inline BigNumber& operator --(void) noexcept { BigNumber::decrement(); return *this; }

        inline operator char const*(void) const noexcept { return BigNumber::toString(); }
};

/* Modification > Big Number */
    // Add
    BigNumber& BigNumber::add(BigNumber const& number) noexcept {
        // Logic
        if (BigNumber::isSafe()) {
            // Logic
            if (BigNumber::isZero()) { if (false == BigNumber::isZero(number)) BigNumber::copy(number); }
            else if (BigNumber::isInfinite(number) || BigNumber::isNaN(number)) BigNumber::copy(number);
            else if (false == BigNumber::isZero(number)) {
                // Logic > ...
                if (BigNumber::isNegative() && BigNumber::isPositive(number)) BigNumber::copy(BigNumber::subtract(number, *this));
                else if (BigNumber::isPositive() && BigNumber::isNegative(number)) BigNumber::subtract(number);
                else {
                    // Initialization > (Carry, Iterator ...)
                    bool carry = false;
                    char *iteratorA, *iteratorB;

                    // ...
                    BigNumber::allocate((this -> characteristicsLength < number.characteristicsLength ? number.characteristicsLength : this -> characteristicsLength) + (this -> mantissaLength < number.mantissaLength ? number.mantissaLength : this -> mantissaLength) + 1u);

                    // Logic
                    if (BigNumber::hasSignificantMantissa(number)) {
                        // Logic
                        if (BigNumber::hasSignificantMantissa()) {
                            // Logic
                            if (this -> mantissaLength < number.mantissaLength) {
                                // Modification > Target > (Mantissa Length, Value)
                                ::memset(this -> value + this -> characteristicsLength + this -> mantissaLength, '0', (number.mantissaLength - this -> mantissaLength) * sizeof(char));
                                this -> mantissaLength = number.mantissaLength;
                            }

                            // Update > Iterator ...
                            iteratorA = this -> value + (this -> characteristicsLength + this -> mantissaLength);
                            iteratorB = number.value + (number.characteristicsLength + number.mantissaLength);

                            // Loop --- NOTE (Lapys) -> Add the digits of the mantissa.
                            for (size_t iterator = 0u, length = this -> mantissaLength - number.mantissaLength; iterator ^ (this -> mantissaLength); ++iterator) {
                                // Initialization > Evaluation
                                char *evaluation = (char*) BigNumber::add(*--iteratorA, iterator < length ? '0' : *--iteratorB);

                                // Logic > ...
                                if ('\0' == *(evaluation + 1)) { if (carry) { evaluation = (char*) BigNumber::increment(*evaluation); carry = '\0' ^ *(evaluation + 1); } *iteratorA = carry ? *(evaluation + 1) : *evaluation; }
                                else { if (carry) *(evaluation + 1) = *BigNumber::increment(*(evaluation + 1)); carry = true; *iteratorA = *(evaluation + 1); }
                            }
                        }

                        else {
                            // Modification > Target > (Mantissa Length, Value)
                            ::strncpy(this -> value + this -> characteristicsLength, number.value + number.characteristicsLength, number.mantissaLength);
                            this -> mantissaLength = number.mantissaLength;
                        }
                    }

                    // Logic > ...
                    if (carry) { BigNumber::isNegative() ? BigNumber::decrement() : BigNumber::increment(); carry = false; }

                    // Logic
                    if (BigNumber::hasSignificantCharacteristics(number)) {
                        // Logic
                        if (BigNumber::hasSignificantCharacteristics()) {
                            // Logic
                            if (this -> characteristicsLength < number.characteristicsLength) {
                                // Modification > Target > (Characteristics Length, Value)
                                ::memmove(this -> value + (number.characteristicsLength - this -> characteristicsLength), this -> value, (this -> characteristicsLength + this -> mantissaLength) * sizeof(char));
                                ::memset(this -> value, '0', (number.characteristicsLength - this -> characteristicsLength) * sizeof(char));

                                this -> characteristicsLength = number.characteristicsLength;
                            }

                            // Update > Iterator ...
                            iteratorA = this -> value + this -> characteristicsLength;
                            iteratorB = number.value + number.characteristicsLength;

                            // Loop --- NOTE (Lapys) -> Add the digits of the characteristics.
                            for (size_t iterator = 0u; iterator ^ (this -> characteristicsLength); ++iterator) {
                                // Initialization > Evaluation
                                char *evaluation = (char*) BigNumber::add(*--iteratorA, '0' == *(this -> value) ? *--iteratorB : (iterator < number.characteristicsLength ? *--iteratorB : '0'));

                                // Logic > ...
                                if ('\0' == *(evaluation + 1)) { if (carry) evaluation = (char*) BigNumber::increment(*evaluation); carry = '\0' ^ *(evaluation + 1); *iteratorA = carry ? *(evaluation + 1) : *evaluation; }
                                else { if (carry) *(evaluation + 1) = *BigNumber::increment(*(evaluation + 1)); carry = true; *iteratorA = *(evaluation + 1); }
                            }
                        }

                        else {
                            // Modification > Target > (Characteristics Length, Value)
                            ::memmove(this -> value + number.characteristicsLength, this -> value, (this -> characteristicsLength + this -> mantissaLength) * sizeof(char));
                            ::strncpy(this -> value, number.value, number.characteristicsLength);

                            this -> characteristicsLength = number.characteristicsLength;
                        }
                    }

                    // Logic
                    if (carry) {
                        // Modification > Target > (Characteristics Length, Value)
                        ::memmove(this -> value + 1, this -> value, (this -> characteristicsLength + this -> mantissaLength) * sizeof(char));

                        ++(this -> characteristicsLength);
                        *(this -> value) = '1';
                    }
                }
            }
        }

        // Return
        return *this;
    }

    // Decrement
    BigNumber& BigNumber::decrement(void) noexcept {
        // Logic
        if (BigNumber::isSafe()) {
            // ...
            BigNumber::allocate();

            // Logic
            if (false == BigNumber::hasSignificantCharacteristics() || (this -> characteristicsLength == 1u && '0' == *(this -> value))) { // NOTE (Lapys) -> Is zero?
                // Logic
                if (BigNumber::hasSignificantMantissa()) {
                    // ...; Modification > Target > Value
                    BigNumber::allocate(this -> characteristicsLength + this -> mantissaLength + 1u);
                    ::memmove(this -> value + (this -> characteristicsLength + 1u), this -> value + this -> characteristicsLength, this -> mantissaLength * sizeof(char));
                }

                // ...
                BigNumber::sign(true);

                // Modification > Target > (Characteristics Length)
                this -> characteristicsLength = 1u;
                *(this -> value) = '1';
            }

            else if (BigNumber::isNegative()) { // NOTE (Lapys) -> Increment characteristics when number is negative.
                // ...
                BigNumber::unsign();
                BigNumber::increment();
                BigNumber::sign();
            }

            else { // Decrement characteristics.
                // Initialization > Iterator
                char *iterator = this -> value + this -> characteristicsLength;

                // Loop > Update > Iterator
                while ('0' == *--iterator) *iterator = '9';

                // Logic
                if (*iterator == '1' && iterator == this -> value) {
                    // Modification > Target > (Characteristics Length)
                    --(this -> characteristicsLength);
                    ::memmove(this -> value, this -> value + 1, (this -> characteristicsLength + this -> mantissaLength) * sizeof(char));
                }

                else
                    // Update > Iterator
                    *iterator = *BigNumber::decrement(*iterator);
            }
        }

        // Return
        return *this;
    }

    // Divide --- CHECKPOINT (Lapys)
    BigNumber& BigNumber::divide(BigNumber const& number) noexcept { (void) number; return *this; }

    // Exponentiate --- CHECKPOINT (Lapys) --- NOTE (Lapys) -> Inadvertently, the reciprocal root of a number is not the arithmetic inverse/ reverse of a number but rather it is the number`s logarithm.
    BigNumber& BigNumber::exponentiate(BigNumber const& number) noexcept {
        // ...
        (void) number;
        // function decompose(number) {
        //     var iterator = 1;
        //     var precision = 1e7;
        //     var sum = 0;
        //     var summand;

        //     number = Math.abs(number);
        //     number = number - Number.parseInt(number);

        //     console.clear();
        //     console.group("[number]:", number);

        //     while (sum < number) {
        //         summand = iterator;
        //         while (
        //             summand < precision &&
        //             (1 / summand > number || sum + (1 / summand) > number)
        //         ) ++summand;
        //         if (iterator == summand) break;
        //         iterator = summand;
        //         sum += 1 / summand;

        //         console.log("[summand]:", iterator);
        //     }

        //     console.groupEnd();
        //     console.log("[sum]:", sum)
        // }

        // function pow(base, exponent) {
        //     var evaluation;

        //     if (exponent < 0)
        //         evaluation = 1 / pow(base, -exponent);

        //     else if (Math.abs(exponent) != exponent) {
        //         var exponentCharacteristics = Number.parseInt(exponent);
        //         var exponentMantissa = exponent - exponentCharacteristics;

        //         evaluation = pow(base, exponentCharacteristics);

        //         for (var rootExponent in decompose(exponentMantissa))
        //         evaluation *= root(base, rootExponent);
        //     }

        //     else {
        //         evaluation = base;

        //         for (var iterator = exponent; iterator ? --iterator : 0; )
        //         evaluation *= base
        //     }

        //     return evaluation
        // }

        // function root(base, exponent) {
        //     var baseFunction = function(number) { return pow(number, exponent) - base };
        //     var baseFunctionDerivative = function(number) { return exponent * pow(number, exponent - 1) };
        //     var evaluation = 1;
        //     var limit = 0.00000000000001;
        //     var precision = 0.0000001;
        //     var solutionFound = false;

        //     for (var iterator = 1, length = 20; iterator ^ length; ++iterator) {
        //         var approximation;
        //         var denominator = baseFunction(evaluation);
        //         var derivativeDenominator = baseFunctionDerivative(evaluation);

        //         if (Math.abs(derivativeDenominator) < limit) iterator = length - 1;
        //         else {
        //             approximation = evaluation - (denominator / derivativeDenominator);
        //             if (Math.abs(approximation - evaluation) <= precision) solutionFound = true;
        //             evaluation = approximation
        //         }
        //     }

        //     if (solutionFound) return evaluation;
        //     else return null
        // }


        // x0 = 1  # The initial guess
        // f(x) = x^2 - 2  # The function whose root we are trying to find
        // fprime(x) = 2 * x  # The derivative of the function
        // tolerance = 10^(-7)  # 7 digit accuracy is desired
        // epsilon = 10^(-14)  # Do not divide by a number smaller than this
        // maxIterations = 20  # Do not allow the iterations to continue indefinitely
        // solutionFound = false  # Have not converged to a solution yet

        // for i = 1:maxIterations
        //   y = f(x0)
        //   yprime = fprime(x0)

        //   if abs(yprime) < epsilon  # Stop if the denominator is too small
        //     break
        //   end

        //   global x1 = x0 - y/yprime  # Do Newton's computation

        //   if abs(x1 - x0) <= tolerance  # Stop when the result is within the desired tolerance
        //     global solutionFound = true
        //     break
        //   end

        //   global x0 = x1  # Update x0 to start the process again
        // end

        // if solutionFound
        //   println("Solution: ", x1)  # x1 is a solution within tolerance and maximum number of iterations
        // else
        //   println("Did not converge")  # Newton's method did not converge
        // end

        // Return
        return *this;
    }

    // From Number --- NOTE (Lapys) -> Convert the number to string and emplace within the returned `BigNumber` object.
    BigNumber const BigNumber::fromNumber(long const number) noexcept { return number < 0L ? -BigNumber::fromNumber((unsigned long) -number) : BigNumber::fromNumber((unsigned long) number); }
    BigNumber const BigNumber::fromNumber(long double const number) noexcept {
        // Evaluation > Evaluation
        BigNumber evaluation;

        // Logic
        if (::isinf(number)) {
            // ...; Modification > Evaluation > State
            if (number < 0.00L) evaluation.sign();
            evaluation.state = BigNumber::INFINITE;
        }

        else if (::isnan(number))
            // Modification > Evaluation > State
            evaluation.state = BigNumber::UNCOMPUTABLE;

        else if (number && false == ::isnormal(number))
            // Modification > Evaluation > State
            evaluation.state = BigNumber::DENORMALIZED;

        else if (number) {
            // Initialization > (Characteristics, Mantissa)
            long double characteristics, mantissa = ::modf(number < 0.00L ? -number : number, &characteristics);

            // ...
            evaluation.allocate((characteristics ? LDBL_DIG : 0u) + (mantissa ? LDBL_MANT_DIG : 0u));

            // Logic > ...
            if (number < 0.00L) evaluation.sign();

            // Logic
            if (characteristics) {
                // Initialization > Iterator
                char *iterator = evaluation.value;

                // Loop > ...
                // : Modification > Evaluation > Characteristics Length
                for (long double digit; characteristics && (iterator - evaluation.value) <= LDBL_DIG; *iterator++ = *("0123456789" + (unsigned char) ::round(digit))) digit = ::modf((characteristics /= 10.00L), &characteristics) * 10.00L;
                evaluation.characteristicsLength = iterator-- - evaluation.value;

                for (char *subiterator = evaluation.value; iterator > subiterator; (--iterator, ++subiterator)) { *iterator ^= *subiterator; *subiterator ^= *iterator; *iterator ^= *subiterator; }
            }

            // Logic
            if (mantissa) {
                // Initialization > Iterator
                char *iterator = evaluation.value + evaluation.characteristicsLength;

                // Loop > ...
                // : Modification > Evaluation > Mantissa Length
                for (
                    long double digit;
                    mantissa >= LDBL_EPSILON && (iterator - (evaluation.value + evaluation.characteristicsLength)) <= LDBL_MANT_DIG;
                    *iterator++ = *("0123456789" + (unsigned char) ::round(digit))
                ) mantissa = ::modf((mantissa *= 10.00L), &digit);
                evaluation.mantissaLength = iterator - (evaluation.value + evaluation.characteristicsLength);
            }
        }

        // Return
        return evaluation;
    }
    BigNumber const BigNumber::fromNumber(unsigned long const number) noexcept {
        // Evaluation > Evaluation
        BigNumber evaluation;

        // Logic
        if (number) {
            // ...
            evaluation.allocate(20u);

            // Loop
            for (unsigned long index = 0u, iterator = number; iterator; iterator /= 10u) {
                // Modification > Evaluation > Value
                *(evaluation.value + index++) = *("0123456789" + (iterator % 10u));

                // Logic
                if (iterator < 10u) {
                    // Modification > Evaluation > Characteristics Length
                    evaluation.characteristicsLength = index;

                    // Loop > ...
                    for ((--index, iterator = 0u); iterator < index; (--index, ++iterator)) {
                        *(evaluation.value + index) ^= *(evaluation.value + iterator);
                        *(evaluation.value + iterator) ^= *(evaluation.value + index);
                        *(evaluation.value + index) ^= *(evaluation.value + iterator);
                    }
                }
            }
        }

        // Return
        return evaluation;
    }

    // Get Characteristics
    inline long double BigNumber::getCharacteristics(void) const { return 0.00L; }

    // Get Mantissa
    inline long double BigNumber::getMantissa(void) const { return 0.00L; }

    // Has Significant Characteristics --- NOTE (Lapys) -> Characteristics is not zero.
    inline bool BigNumber::hasSignificantCharacteristics(void) const noexcept { return this -> characteristicsLength == 1u ? '0' ^ *(this -> value) : this -> characteristicsLength; }

    // Has Significant Mantissa --- NOTE (Lapys) -> Mantissa is not zero.
    inline bool BigNumber::hasSignificantMantissa(void) const noexcept { return this -> mantissaLength; }

    // Increment
    BigNumber& BigNumber::increment(void) noexcept {
        // Logic
        if (BigNumber::isSafe()) {
            // ...
            BigNumber::allocate();

            // Logic
            if (false == BigNumber::hasSignificantCharacteristics()) { // NOTE (Lapys) -> Is zero?
                // ...
                BigNumber::unsign();

                // Logic
                if (BigNumber::hasSignificantMantissa()) {
                    // ...; Modification > Target > Value
                    BigNumber::allocate(this -> characteristicsLength + this -> mantissaLength + 1u);
                    ::memmove(this -> value + (this -> characteristicsLength + 1u), this -> value + this -> characteristicsLength, this -> mantissaLength * sizeof(char));
                }

                // Modification > Target > (Characteristics Length, Value)
                this -> characteristicsLength = 1u;
                *(this -> value) = '1';
            }

            else if (BigNumber::isNegative()) { // NOTE (Lapys) -> Decrement characteristics when number is negative.
                // ...
                BigNumber::unsign();
                BigNumber::decrement();
                BigNumber::sign();
            }

            else { // NOTE (Lapys) -> Increment characteristics.
                // Initialization > Iterator
                char *iterator = this -> value + this -> characteristicsLength;

                // Loop > Update > Iterator
                while ('9' == *--iterator) *iterator = '0';

                // Logic
                if (iterator == this -> value - 1) {
                    // ...
                    BigNumber::allocate(this -> characteristicsLength + this -> mantissaLength + 1u);

                    // Modification > Target > (Characteristics Length, Value)
                    ::memmove(this -> value + 1, this -> value, (this -> characteristicsLength + this -> mantissaLength) * sizeof(char));
                    ++(this -> characteristicsLength);
                    *(this -> value) = '1';
                }

                else
                    // Update > Iterator
                    *iterator = *BigNumber::increment(*iterator);
            }
        }

        // Return
        return *this;
    }

    // Is Computable
    bool BigNumber::isComputable(void) const noexcept { return BigNumber::UNCOMPUTABLE != this -> state; }

    // Is Equal
    bool BigNumber::isEqual(BigNumber const& numberA, BigNumber const& numberB) noexcept {
        // Evaluation > Evaluation
        bool evaluation = true;

        // Logic
        if (BigNumber::isSafe(numberA) && BigNumber::isSafe(numberB)) {
            // Logic > ...
            if (BigNumber::isZero(numberA)) evaluation = BigNumber::isZero(numberB);
            else if (BigNumber::isZero(numberB)) evaluation = BigNumber::isZero(numberA);
            else if (
                (BigNumber::hasSignificantCharacteristics(numberA) && BigNumber::hasSignificantCharacteristics(numberB)) ||
                (BigNumber::hasSignificantMantissa(numberA) && BigNumber::hasSignificantMantissa(numberB)) ||

                (BigNumber::isNegative(numberA) && BigNumber::isNegative(numberB)) ||
                (BigNumber::isPositive(numberA) && BigNumber::isPositive(numberB))
            ) {
                // Logic --- NOTE (Lapys) -> Assert the characteristics.
                if (0u == numberA.characteristicsLength) evaluation = false == BigNumber::hasSignificantCharacteristics(numberB);
                else if (0u == numberB.characteristicsLength) evaluation = false == BigNumber::hasSignificantCharacteristics(numberA);
                else if (numberA.characteristicsLength ^ numberB.characteristicsLength) evaluation = false;
                else {
                    // Loop > Logic > Update > Evaluation
                    for (size_t iterator = 0u; evaluation && (iterator ^ numberA.characteristicsLength); ++iterator)
                    if (false == BigNumber::isEqual(*(numberA.value + iterator), *(numberB.value + iterator)))
                    evaluation = false;
                }

                // Logic --- NOTE (Lapys) -> Assert the mantissa.
                if (evaluation && numberA.mantissaLength == numberB.mantissaLength) {
                    // Initialization > Iterator (A, B)
                    char *iteratorA = numberA.value + numberA.characteristicsLength;
                    char *iteratorB = numberB.value + numberB.characteristicsLength;

                    // Loop > Logic > Update > Evaluation
                    for (size_t iterator = 0u; evaluation && (iterator ^ numberA.mantissaLength); ++iterator)
                    if (false == BigNumber::isEqual(*iteratorA++, *iteratorB++))
                    evaluation = false;
                }

                else
                    // Update > Evaluation
                    evaluation = false;
            }
        }

        else
            // Update > Evaluation
            evaluation = false;

        // Return
        return evaluation;
    }

    // Is Finite
    bool BigNumber::isFinite(void) const noexcept { return BigNumber::INFINITE != this -> state; }

    // Is Greater
    bool BigNumber::isGreater(BigNumber const& numberA, BigNumber const& numberB) noexcept {
        // Evaluation > Evaluation
        bool evaluation = false;

        // Logic
        if (
            (BigNumber::isInfinite(numberA) && BigNumber::isInfinite(numberB)) ||
            (false == BigNumber::isNormal(numberA) && false == BigNumber::isNormal(numberB))
        )
            // Update > Evaluation
            evaluation = BigNumber::isPositive(numberA) && BigNumber::isNegative(numberB);

        else if (BigNumber::isComputable(numberA) && BigNumber::isComputable(numberB)) {
            // Logic > ...
            if (BigNumber::isZero(numberA)) evaluation = BigNumber::isNegative(numberB) && false == BigNumber::isZero(numberB);
            else if (BigNumber::isZero(numberB)) evaluation = BigNumber::isPositive(numberA) && false == BigNumber::isZero(numberA);
            else if (BigNumber::isNegative(numberA)) evaluation = BigNumber::isNegative(numberB) && BigNumber::isGreater(-BigNumber(numberB), -BigNumber(numberA));
            else if (BigNumber::isNegative(numberB)) evaluation = BigNumber::isPositive(numberA) || BigNumber::isGreater(-BigNumber(numberB), -BigNumber(numberA));
            else if (numberA.characteristicsLength >= numberB.characteristicsLength) {
                // Initialization > Pending --- NOTE (Lapys) -> Valid if the compared components are yet equal.
                bool pending = true;

                // Logic > Logic > Update > (Evaluation, ...)
                if (0u == numberA.characteristicsLength) { if (BigNumber::hasSignificantCharacteristics(numberB)) { evaluation = false; pending = false; } }
                else if (0u == numberB.characteristicsLength) { if (BigNumber::hasSignificantCharacteristics(numberA)) { evaluation = true; pending = false; } }

                // Logic
                if (pending) {
                    // Initialization > Iterator (A, B)
                    char *iteratorA = numberA.value;
                    char *iteratorB = numberB.value;

                    // Loop
                    for (size_t iterator = 0u, length = numberA.characteristicsLength < numberB.characteristicsLength ? numberA.characteristicsLength : numberB.characteristicsLength; pending && (iterator ^ length); ++iterator) {
                        // Logic > Update > ...
                        if (BigNumber::isGreater(*iteratorA, *iteratorB)) { evaluation = true; pending = false; }
                        else pending = BigNumber::isEqual(*iteratorA, *iteratorB);

                        // Update > Iterator (A, B)
                        ++iteratorA;
                        ++iteratorB;
                    }

                    // Logic > Update > ...
                    if ((false == evaluation || pending) && numberA.characteristicsLength > numberB.characteristicsLength) {
                        evaluation = true;
                        pending = false;
                    }

                    // Logic
                    if (pending) {
                        // Initialization > Iterator (A, B)
                        char *iteratorA = numberA.value + numberA.characteristicsLength;
                        char *iteratorB = numberB.value + numberB.characteristicsLength;

                        // Loop
                        for (size_t iterator = 0u, length = numberA.mantissaLength < numberB.mantissaLength ? numberA.mantissaLength : numberB.mantissaLength; pending && (iterator ^ length); ++iterator) {
                            // Logic > Update > (Evaluation, ...)
                            if (BigNumber::isGreater(*iteratorA, *iteratorB)) { evaluation = true; pending = false; }
                            else pending = BigNumber::isEqual(*iteratorA, *iteratorB);

                            // Update > Iterator (A, B)
                            ++iteratorA;
                            ++iteratorB;
                        }

                        // Logic > Update > (Evaluation, ...)
                        if (pending && numberA.mantissaLength > numberB.mantissaLength) {
                            evaluation = true;
                            pending = false;
                        }
                    }
                }
            }
        }

        // Return
        return evaluation;
    }

    // Is Infinite
    bool BigNumber::isInfinite(void) const noexcept { return BigNumber::INFINITE == this -> state; }

    // Is Integral
    inline bool BigNumber::isIntegral(void) const noexcept { return 0u == this -> mantissaLength; }

    // Is Lesser
    bool BigNumber::isLesser(BigNumber const& numberA, BigNumber const& numberB) noexcept {
        // Evaluation > Evaluation
        bool evaluation = false;

        // Logic
        if (
            (BigNumber::isInfinite(numberA) && BigNumber::isInfinite(numberB)) ||
            (false == BigNumber::isNormal(numberA) && false == BigNumber::isNormal(numberB))
        )
            // Update > Evaluation
            evaluation = BigNumber::isNegative(numberA) && BigNumber::isPositive(numberB);

        else if (BigNumber::isComputable(numberA) && BigNumber::isComputable(numberB)) {
            // Logic > ...
            if (BigNumber::isZero(numberA)) evaluation = BigNumber::isPositive(numberB) && false == BigNumber::isZero(numberB);
            else if (BigNumber::isZero(numberB)) evaluation = BigNumber::isNegative(numberA) && false == BigNumber::isZero(numberA);
            else if (BigNumber::isNegative(numberA)) evaluation = BigNumber::isPositive(numberB) || BigNumber::isLesser(-BigNumber(numberB), -BigNumber(numberA));
            else if (BigNumber::isNegative(numberB)) evaluation = BigNumber::isNegative(numberA) && BigNumber::isLesser(-BigNumber(numberB), -BigNumber(numberA));
            else if (numberA.characteristicsLength <= numberB.characteristicsLength) {
                // Initialization > Pending --- NOTE (Lapys) -> Valid if the compared components are yet equal.
                bool pending = true;

                // Logic > Logic > Update > (Evaluation, ...)
                if (0u == numberA.characteristicsLength) { if (BigNumber::hasSignificantCharacteristics(numberB)) { evaluation = true; pending = false; } }
                else if (0u == numberB.characteristicsLength) { if (BigNumber::hasSignificantCharacteristics(numberA)) { evaluation = false; pending = false; } }

                // Logic
                if (pending) {
                    // Initialization > Iterator (A, B)
                    char *iteratorA = numberA.value;
                    char *iteratorB = numberB.value;

                    // Loop
                    for (size_t iterator = 0u, length = numberA.characteristicsLength < numberB.characteristicsLength ? numberA.characteristicsLength : numberB.characteristicsLength; pending && (iterator ^ length); ++iterator) {
                        // Logic > Update > ...
                        if (BigNumber::isLesser(*iteratorA, *iteratorB)) { evaluation = true; pending = false; }
                        else pending = BigNumber::isEqual(*iteratorA, *iteratorB);

                        // Update > Iterator (A, B)
                        ++iteratorA;
                        ++iteratorB;
                    }

                    // Logic > Update > ...
                    if ((false == evaluation || pending) && numberA.characteristicsLength < numberB.characteristicsLength) {
                        evaluation = true;
                        pending = false;
                    }

                    // Logic
                    if (pending) {
                        // Initialization > Iterator (A, B)
                        char *iteratorA = numberA.value + numberA.characteristicsLength;
                        char *iteratorB = numberB.value + numberB.characteristicsLength;

                        // Loop
                        for (size_t iterator = 0u, length = numberA.mantissaLength < numberB.mantissaLength ? numberA.mantissaLength : numberB.mantissaLength; pending && (iterator ^ length); ++iterator) {
                            // Logic > Update > (Evaluation, ...)
                            if (BigNumber::isLesser(*iteratorA, *iteratorB)) { evaluation = true; pending = false; }
                            else pending = BigNumber::isEqual(*iteratorA, *iteratorB);

                            // Update > Iterator (A, B)
                            ++iteratorA;
                            ++iteratorB;
                        }

                        // Logic > Update > (Evaluation, ...)
                        if (pending && numberA.mantissaLength < numberB.mantissaLength) {
                            evaluation = true;
                            pending = false;
                        }
                    }
                }
            }
        }

        // Return
        return evaluation;
    }

    // Is Not-A-Number
    bool BigNumber::isNaN(void) const noexcept { return BigNumber::UNCOMPUTABLE == this -> state; }

    // Is Negative
    inline bool BigNumber::isNegative(void) const noexcept { return this -> signedness; }

    // Is Normal
    inline bool BigNumber::isNormal(void) const noexcept { return BigNumber::DENORMALIZED != this -> state; }

    // Is Positive
    inline bool BigNumber::isPositive(void) const noexcept { return false == this -> signedness; }

    // Is Safe
    inline bool BigNumber::isSafe(void) const noexcept { return BigNumber::SAFE == this -> state; }

    // Is Zero
    inline bool BigNumber::isZero(void) const noexcept { return BigNumber::isIntegral() && false == BigNumber::hasSignificantCharacteristics(); }

    // Logarithmize --- CHECKPOINT (Lapys)
    BigNumber& BigNumber::logarithmize(BigNumber const& number) noexcept { (void) number; return *this; }

    // Modulo --- CHECKPOINT (Lapys)
    BigNumber& BigNumber::modulo(BigNumber const& number) noexcept { (void) number; return *this; }

    // Multiply --- NOTE (Lapys) -> Oddly enough, fractional multiplication (e.g.: `x * 0.5 -> x / 2`) can still be covered by long multiplication.
    BigNumber& BigNumber::multiply(BigNumber const& number) noexcept {
        // Logic
        if (BigNumber::isInfinite()) {
            // Logic > ...
            if (BigNumber::isNaN(number)) this -> state = BigNumber::UNCOMPUTABLE;
            else if (BigNumber::isNegative(number)) BigNumber::sign();
        }

        else if (BigNumber::isComputable()) {
            // Logic
            if (BigNumber::isZero() || BigNumber::isZero(number)) {
                // ...
                BigNumber::unsign();

                // Modification > Target > ((Characteristics, Mantissa) Length)
                this -> characteristicsLength = 0u;
                this -> mantissaLength = 0u;
                *(this -> value) = '0';
            }

            else if ((this -> characteristicsLength == 1u && '1' == *(this -> value)) && false == BigNumber::hasSignificantMantissa())
                // ...
                BigNumber::copy(number);

            else if (BigNumber::hasSignificantMantissa(number) || (number.characteristicsLength == 1u && '1' == *number.value ? false : BigNumber::hasSignificantCharacteristics(number))) {
                // Initialization > ...
                // : NOTE (Lapys) -> Store a persistent copy of the current value in variables to add the iterative results of long multiplication into the target (`this`) object.
                size_t const characteristicsLength = this -> characteristicsLength;
                size_t mantissaLength = this -> mantissaLength;
                bool const signedness = BigNumber::isNegative();
                char *value;

                // : NOTE (Lapys) -> Keep track of the states of sub-multiplication evaluations & operations.
                char carry = '0';
                char *iteratorA;
                char *iteratorB;
                BigNumber *products = new BigNumber[number.characteristicsLength + number.mantissaLength] {};

                // ...
                BigNumber::unsign();
                BigNumber::allocate((this -> characteristicsLength + number.characteristicsLength) + (this -> mantissaLength + number.mantissaLength));

                value = (char*) ::malloc(this -> valueSize * sizeof(char));
                ::strncpy(value, this -> value, characteristicsLength + mantissaLength);

                // Logic
                if (mantissaLength < number.mantissaLength) {
                    // Update > (Value, ...)
                    ::memset(value + (characteristicsLength + mantissaLength), '0', number.mantissaLength - mantissaLength);
                    mantissaLength = number.mantissaLength;
                }

                // Loop
                for (size_t index, iterator = 0u, length = number.characteristicsLength + number.mantissaLength; iterator ^ length; ++iterator) {
                    // Update > ...
                    carry = '0';
                    index = 0u;
                    iteratorA = value + (characteristicsLength + mantissaLength);
                    iteratorB = number.value + (length - iterator - 1u);

                    // Initialization > (Evaluation, Product, Multiplier)
                    char *evaluation;
                    char const multiplier = *iteratorB;
                    BigNumber& product = *(products + iterator);

                    // Logic
                    if ('0' ^ multiplier) {
                        // Loop
                        for (size_t subiterator = 0u, sublength = characteristicsLength + mantissaLength; subiterator ^ sublength; (++index, ++subiterator)) {
                            // Update > Evaluation
                            evaluation = (char*) BigNumber::multiply(*--iteratorA, multiplier);

                            // Logic
                            if ('\0' == *(evaluation + 1)) {
                                // Logic > Update > Evaluation
                                // : Modification > Target > Value
                                if ('0' ^ carry) { evaluation = (char*) BigNumber::add(carry, *evaluation); carry = '\0' == *(evaluation + 1) ? '0' : *evaluation; }
                                *(this -> value + index) = '0' == carry ? *evaluation : *(evaluation + 1);
                            }

                            else {
                                // Loop
                                while ('0' ^ carry) {
                                    // Update > Carry
                                    carry = *BigNumber::decrement(carry);

                                    // Logic > Update >  Evaluation
                                    if ('9' == *(evaluation + 1)) { *evaluation = *BigNumber::increment(*evaluation); *(evaluation + 1) = '0'; }
                                    else *(evaluation + 1) = *BigNumber::increment(*(evaluation + 1));
                                }

                                // Update > Carry
                                // : Modification > Target > Value
                                carry = *evaluation;
                                *(this -> value + index) = *(evaluation + 1);
                            }
                        }

                        // Logic > Modification > Target > Value
                        if ('0' ^ carry) *(this -> value + index++) = *evaluation;

                        // Modification > Product > (Characteristics Length, Value (Size))
                        product.characteristicsLength = index + iterator;
                        product.valueSize = index + iterator;
                        product.value = (char*) ::malloc(product.valueSize * sizeof(char));
                        ::strncpy(product.value, this -> value, index);
                        ::memset(product.value + index, '0', iterator * sizeof(char));

                        // Update > Index; Loop --- NOTE (Lapys) -> Reverse the significant digits of the product.
                        --index;
                        for (size_t subindex = 0u; subindex < index; (--index, ++subindex)) {
                            // Modification > Product > Value
                            *(product.value + index) ^= *(product.value + subindex);
                            *(product.value + subindex) ^= *(product.value + index);
                            *(product.value + index) ^= *(product.value + subindex);
                        }
                    }
                }

                // Modification > Target > (Characteristics, Mantissa) Length
                this -> characteristicsLength = 0u;
                this -> mantissaLength = 0u;

                // Loop > ...
                // : Logic > ...
                for (size_t iterator = 0u, length = number.characteristicsLength + number.mantissaLength; iterator ^ length; ++iterator)
                BigNumber::add(*(products + iterator));

                if (signedness) BigNumber::sign();
                if (BigNumber::isNegative(number)) BigNumber::sign();

                // Modification > Target > (Characteristics, Mantissa) Length
                this -> mantissaLength = mantissaLength + number.mantissaLength;
                this -> characteristicsLength -= this -> mantissaLength;

                // Deletion
                delete[] products;
                ::free(value);
            }
        }

        // Return
        return *this;
    }

    // Reciprocate --- CHECKPOINT (Lapys) --- NOTE (Lapys) -> Return the multiplicative inverse of the number.
    inline void BigNumber::reciprocate(void) noexcept {
        (void) this -> value;
    }

    // Sign
    inline void BigNumber::sign(bool const strict) noexcept { this -> signedness = strict || !(this -> signedness); }

    // Subtract
    BigNumber& BigNumber::subtract(BigNumber const& number) noexcept {
        // Logic
        if (BigNumber::isSafe()) {
            // Logic > ...
            if (BigNumber::isZero()) BigNumber::copy(-number);
            else if (BigNumber::isInfinite(number) || BigNumber::isNaN(number)) BigNumber::copy(number);
            else if (false == BigNumber::isZero(number)) {
                // Logic
                if (BigNumber::isPositive() && BigNumber::isNegative(number))
                    // ...
                    BigNumber::add(-number);

                else if (BigNumber::isNegative()) {
                    // ...
                    BigNumber::unsign();

                    // Logic > ...
                    if (BigNumber::isNegative(number)) BigNumber::copy(BigNumber::subtract(-number, *this));
                    else { BigNumber::add(number); BigNumber::sign(); }
                }

                else if (BigNumber::isLesser(number))
                    // ...
                    BigNumber::copy(-BigNumber::subtract(number, *this));

                else {
                    // Initialization > (Carry, Iterator (A, B))
                    bool carry = false;
                    char *iteratorA, *iteratorB;

                    // ...
                    BigNumber::allocate((this -> characteristicsLength > number.characteristicsLength ? this -> characteristicsLength : number.characteristicsLength) + (this -> mantissaLength > number.mantissaLength ? this -> mantissaLength : number.mantissaLength));

                    // Logic
                    if (this -> mantissaLength < number.mantissaLength) {
                        // Modification > Target > (Mantissa Length, Value)
                        ::memset(this -> value + (this -> characteristicsLength + this -> mantissaLength), '0', number.mantissaLength - (this -> mantissaLength));
                        this -> mantissaLength = number.mantissaLength;
                    }

                    // Update > Iterator (A, B)
                    iteratorA = this -> value + (this -> characteristicsLength + this -> mantissaLength);
                    iteratorB = number.value + (number.characteristicsLength + number.mantissaLength);

                    // Loop
                    for (size_t iterator = 0u, length = this -> characteristicsLength + this -> mantissaLength; (iterator ^ length) && (iteratorB != number.value); ) {
                        // Initialization > Evaluation
                        char *evaluation;

                        // Logic > Update > (Evaluation, ...)
                        if (carry) { carry = false; evaluation = (char*) BigNumber::add(*BigNumber::increment(*--iteratorA), *BigNumber::subtract('9', *--iteratorB)); }
                        else evaluation = (char*) BigNumber::subtract(*--iteratorA, *--iteratorB);

                        // Logic
                        if ('-' == *evaluation) {
                            // Initialization > Sub-Iterator
                            char *subiterator = iteratorA;

                            // : Update > (Carry, Iterator (A, B))
                            // : Loop > Update > Sub-Iterator
                            carry = true; ++iteratorA; ++iteratorB;

                            while ('0' == *--subiterator) *subiterator = '9';
                            *subiterator = *BigNumber::decrement(*subiterator);
                        } else { *iteratorA = *evaluation; ++iterator; }
                    }

                    // Loop > Modification > Target > Mantissa Length
                    while (this -> mantissaLength && '0' == *(this -> value + ((this -> characteristicsLength + this -> mantissaLength) - 1u)))
                    --(this -> mantissaLength);

                    // Logic
                    if (this -> characteristicsLength && '0' == *(this -> value)) {
                        // Initialization > Iterator
                        char *iterator = this -> value;

                        // Loop > Modification > Target > (Characteristics Length, ...)
                        while (this -> characteristicsLength && '0' == *iterator++) --(this -> characteristicsLength);
                        ::memmove(this -> value, iterator, (this -> characteristicsLength + this -> mantissaLength) * sizeof(char));
                    }
                }
            }
        }

        // Return
        return *this;
    }

    // To Number
    inline long double BigNumber::toNumber(BigNumber const& number) {
        // Evaluation > Evaluation
        long double evaluation = 0.00L;

        // Logic
        if (BigNumber::isInfinite(number))
            // Update > Evaluation
            evaluation = INFINITY;

        else if (BigNumber::isNaN(number))
            // Logic > Update > Evaluation
            #ifdef NANL
                evaluation = NANL;
            #else
                evaluation = NAN;
            #endif

        else {
            // Initialization > (Exponent, Iterator)
            long double exponent;
            size_t iterator;

            // Loop > Update > Evaluation
            exponent = 1.00L;
            for (iterator = 0u; iterator ^ number.characteristicsLength; ++iterator) exponent *= 10.00L;
            for (iterator = 0u; iterator ^ number.characteristicsLength; ++iterator) evaluation += BigNumber::toNumber(*(number.value + iterator)) * (exponent /= 10.00L);
            exponent = 1.00L;
            for (iterator = 0u; iterator ^ number.mantissaLength; ++iterator) evaluation += BigNumber::toNumber(*(number.value + number.characteristicsLength + iterator)) / (exponent *= 10.00L);

            if (BigNumber::isNegative(number)) evaluation = -evaluation;
        }

        // Return
        return evaluation;
    }

    // To String
    inline char const* BigNumber::toString(void) const noexcept {
        // Evaluation > Evaluation
        char *evaluation = NULL;

        // Logic
        switch (this -> state) {
            // [Denormalized]
            case BigNumber::DENORMALIZED: {
                // Update > Evaluation
                evaluation = (char*) ::malloc(13u * sizeof(char));
                ::strncpy(evaluation, "Denormalized", 13u);
            } break;

            // [Infinite]
            case BigNumber::INFINITE: {
                // Update > Evaluation
                evaluation = (char*) ::malloc(10u * sizeof(char));
                ::strncpy(evaluation, "-Infinity" + (false == this -> signedness), 9u + (this -> signedness));
            } break;

            // [Safe]
            case BigNumber::SAFE: {
                // Initialization > Iterator
                char *iterator;

                // Update > (Evaluation, ...)
                evaluation = (char*) ::malloc(((BigNumber::hasSignificantCharacteristics() ? this -> characteristicsLength : 1u) + (BigNumber::hasSignificantMantissa() ? this -> mantissaLength + 1u : 0u) + (BigNumber::isNegative() && (BigNumber::hasSignificantCharacteristics() || BigNumber::hasSignificantMantissa())) + 1u) * sizeof(char));
                iterator = evaluation;

                // Logic
                if (this -> characteristicsLength) {
                    // (Logic, Loop) > Update > Iterator
                    if (BigNumber::isNegative()) *iterator++ = '-';
                    for (size_t subiterator = 0u; subiterator ^ (this -> characteristicsLength); ++subiterator) *iterator++ = *(this -> value + subiterator);
                }

                else {
                    // (Logic > )Update > Iterator
                    if (BigNumber::isNegative() && this -> mantissaLength) *iterator++ = '-';
                    *iterator++ = '0';
                }

                // Logic
                if (this -> mantissaLength) {
                    // (Loop > )Update > (Iterator)
                    *iterator++ = '.';
                    for (size_t subiterator = 0u; subiterator ^ (this -> mantissaLength); ++subiterator) *iterator++ = *(this -> value + (this -> characteristicsLength + subiterator));
                }

                // Update > Iterator
                *iterator = '\0';
            } break;

            // [Uncomputable]
            case BigNumber::UNCOMPUTABLE: {
                // Update > Evaluation
                evaluation = (char*) ::malloc(4u * sizeof(char));
                ::strncpy(evaluation, "NaN", 4u);
            } break;
        }

        // Return
        return (char const*) evaluation;
    }

    // Unsign
    inline void BigNumber::unsign(void) noexcept { this -> signedness = false; }

/* Constant > ... */
BigNumber const BigNumber::Infinity {BigNumber::INFINITE};
BigNumber const BigNumber::NaN {BigNumber::UNCOMPUTABLE};

/* Utilization > ... */
BigNumber const& Infinity = BigNumber::Infinity;
BigNumber const& NaN = BigNumber::NaN;

/* Main */
int main(void) {
    /* [Initiate] ... */
    std::cout << "[PROGRAM INITIATED]" << std::endl;

    /* [Terminate] ... */
    std::cout << "[PROGRAM TERMINATED]" << std::flush;

    // Return
    return EXIT_SUCCESS;
}
