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
        size_t characteristicsLength;
        size_t mantissaLength;
        bool signedness;
        enum {DENORMALIZED, INFINITE, SAFE, UNCOMPUTABLE} state;
        char *value; // NOTE (Lapys) -> Keep the characteristics and mantissa co-joined in the same field.
        size_t valueSize;

        // Function > (Allocate, Copy, Size, [Digit Manipulation] ...) --- MINIFY (Lapys)
        inline void allocate(void) noexcept { BigNumber::allocate(this -> characteristicsLength + this -> mantissaLength); }
        inline void allocate(size_t size) noexcept { size = BigNumber::size(size + 1u); size += (size & 1u); if (size > this -> valueSize) { this -> value = (char*) (NULL == this -> value ? ::malloc(size * sizeof(char)) : ::realloc(this -> value, size * sizeof(char))); this -> valueSize = size; } }
        inline void copy(BigNumber const& number) noexcept { this -> signedness = number.signedness; this -> state = number.state; if (BigNumber::SAFE == number.state) { this -> characteristicsLength = number.characteristicsLength; this -> mantissaLength = number.mantissaLength; this -> value = (char*) (NULL == this -> value ? ::malloc(number.valueSize * sizeof(char)) : ::realloc(this -> value, number.valueSize * sizeof(char))); ::strncpy(this -> value, number.value, number.characteristicsLength + number.mantissaLength); this -> valueSize = number.valueSize; } }
        inline size_t size(void) noexcept { return BigNumber::size(this -> characteristicsLength + this -> mantissaLength); }
        inline size_t size(size_t const size) noexcept { size_t evaluation; for (size_t former, iterator = 1u, recent = 0u; iterator <= size; ) { former = iterator; iterator += recent; recent = former; evaluation = iterator; } return evaluation; }

        inline static char const* add(char const digitA, char const digitB) noexcept { static char evaluation[3] {0}; if ('0' == digitA) { *evaluation = digitB; *(evaluation + 1) = '\0'; } else if ('0' == digitB) { *evaluation = digitA; *(evaluation + 1) = '\0'; } else switch (digitA) { case '1': switch (digitB) { case '1': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '0'; break; } break; case '2': switch (digitB) { case '1': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '1'; break; } break; case '3': switch (digitB) { case '1': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '2'; break; } break; case '4': switch (digitB) { case '1': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '3'; break; } break; case '5': switch (digitB) { case '1': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '4'; break; } break; case '6': switch (digitB) { case '1': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '5'; break; } break; case '7': switch (digitB) { case '1': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '5'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '6'; break; } break; case '8': switch (digitB) { case '1': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '5'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '6'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '7'; break; } break; case '9': switch (digitB) { case '1': *evaluation = '1'; *(evaluation + 1) = '0'; break; case '2': *evaluation = '1'; *(evaluation + 1) = '1'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '2'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '3'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '4'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '5'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '6'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '7'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '8'; break; } break; } return (char const*) evaluation; }
        inline static char const* decrement(char const digit) noexcept { static char evaluation[3] {0}; switch (digit) { case '0': *evaluation = '-'; *(evaluation + 1) = '1'; break; case '1': *evaluation = '0'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '9': *evaluation = '8'; *(evaluation + 1) = '\0'; break; } return (char const*) evaluation; }
        inline static char const* increment(char const digit) noexcept { static char evaluation[3] {0}; switch (digit) { case '0': *evaluation = '1'; *(evaluation + 1) = '\0'; break; case '1': *evaluation = '2'; *(evaluation + 1) = '\0'; break; case '2': *evaluation = '3'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '5'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '6': *evaluation = '7'; *(evaluation + 1) = '\0'; break; case '7': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '8': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '0'; break; } return (char const*) evaluation; }
        inline static char const* multiply(char const digitA, char const digitB) noexcept { static char evaluation[3] {0}; if ('0' == digitA || '0' == digitB) { *evaluation = '0'; *(evaluation + 1) = '\0'; } else if ('1' == digitA) { *evaluation = digitB; *(evaluation + 1) = '\0'; } else if ('1' == digitB) { *evaluation = digitA; *(evaluation + 1) = '\0'; } else switch (digitA) { case '2': switch (digitB) { case '2': *evaluation = '4'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '1'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '1'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; } break; case '3': switch (digitB) { case '2': *evaluation = '6'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '9'; *(evaluation + 1) = '\0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '1'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '2'; *(evaluation + 1) = '1'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '2'; *(evaluation + 1) = '7'; *(evaluation + 2) = '\0'; break; } break; case '4': switch (digitB) { case '2': *evaluation = '8'; *(evaluation + 1) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '1'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '2'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '2'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '3'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '3'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; } break; case '5': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '2'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '2'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '3'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '3'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '4'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '4'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; } break; case '6': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '3'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '3'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '4'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '4'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '5'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; } break; case '7': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '1'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '2'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '3'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '4'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '4'; *(evaluation + 1) = '9'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '5'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '6'; *(evaluation + 1) = '3'; *(evaluation + 2) = '\0'; break; } break; case '8': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '3'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '4'; *(evaluation + 1) = '0'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '4'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '5'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '6'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '7'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; } break; case '9': switch (digitB) { case '2': *evaluation = '1'; *(evaluation + 1) = '8'; *(evaluation + 2) = '\0'; break; case '3': *evaluation = '2'; *(evaluation + 1) = '7'; *(evaluation + 2) = '\0'; break; case '4': *evaluation = '3'; *(evaluation + 1) = '6'; *(evaluation + 2) = '\0'; break; case '5': *evaluation = '4'; *(evaluation + 1) = '5'; *(evaluation + 2) = '\0'; break; case '6': *evaluation = '5'; *(evaluation + 1) = '4'; *(evaluation + 2) = '\0'; break; case '7': *evaluation = '6'; *(evaluation + 1) = '3'; *(evaluation + 2) = '\0'; break; case '8': *evaluation = '7'; *(evaluation + 1) = '2'; *(evaluation + 2) = '\0'; break; case '9': *evaluation = '8'; *(evaluation + 1) = '1'; *(evaluation + 2) = '\0'; break; } break; } return (char const*) evaluation; }

    // [...]
    public:
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

        void sign(bool const = false) noexcept;
        inline static BigNumber const sign(BigNumber const& number) noexcept { BigNumber evaluation {number}; evaluation.sign(); return evaluation; }

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
        inline BigNumber const operator +(void) const noexcept { return BigNumber {*this}; }
        inline BigNumber const operator +(BigNumber const& number) const noexcept { return BigNumber::add(*this, number); }
        inline BigNumber const operator +(BigNumber&& number) const noexcept { return BigNumber::operator +(number); }
        inline BigNumber const operator -(void) const noexcept { return BigNumber::sign(*this); }
        inline BigNumber const operator -(BigNumber const& number) const noexcept { return BigNumber::subtract(*this, number); }
        inline BigNumber const operator -(BigNumber&& number) const noexcept { return BigNumber::operator -(number); }
        inline BigNumber const operator *(BigNumber const& number) const noexcept { return BigNumber::multiply(*this, number); }
        inline BigNumber const operator *(BigNumber&& number) const noexcept { return BigNumber::operator *(number); }
        inline BigNumber const operator /(BigNumber const& number) const noexcept { return BigNumber::divide(*this, number); }
        inline BigNumber const operator /(BigNumber&& number) const noexcept { return BigNumber::operator /(number); }
        inline BigNumber const operator %(BigNumber const& number) const noexcept { return BigNumber::modulo(*this, number); }
        inline BigNumber const operator %(BigNumber&& number) const noexcept { return BigNumber::operator %(number); }
        inline BigNumber& operator =(BigNumber const& number) noexcept { BigNumber::copy(number); return *this; }
        inline BigNumber& operator =(BigNumber&& number) noexcept { return BigNumber::operator =(number); }
        inline BigNumber& operator +=(BigNumber const& number) noexcept { return BigNumber::add(number); }
        inline BigNumber& operator +=(BigNumber&& number) noexcept { return BigNumber::operator +=(number); }
        inline BigNumber& operator -=(BigNumber const& number) noexcept { return BigNumber::subtract(number); }
        inline BigNumber& operator -=(BigNumber&& number) noexcept { return BigNumber::operator -=(number); }
        inline BigNumber& operator *=(BigNumber const& number) noexcept { return BigNumber::multiply(number); }
        inline BigNumber& operator *=(BigNumber&& number) noexcept { return BigNumber::operator *=(number); }
        inline BigNumber& operator /=(BigNumber const& number) noexcept { return BigNumber::divide(number); }
        inline BigNumber& operator /=(BigNumber&& number) noexcept { return BigNumber::operator /=(number); }
        inline BigNumber& operator %=(BigNumber const& number) noexcept { return BigNumber::modulo(number); }
        inline BigNumber& operator %=(BigNumber&& number) noexcept { return BigNumber::operator %=(number); }
        inline bool operator ==(BigNumber& number) noexcept { return BigNumber::isEqual(number); }
        inline bool operator ==(BigNumber&& number) noexcept { return BigNumber::operator ==(number); }
        inline bool operator !=(BigNumber& number) noexcept { return false == BigNumber::operator ==(number); }
        inline bool operator !=(BigNumber&& number) noexcept { return false == BigNumber::operator ==(number); }
        inline bool operator <(BigNumber& number) noexcept { return BigNumber::isLesser(number); }
        inline bool operator <(BigNumber&& number) noexcept { return BigNumber::operator <(number); }
        inline bool operator >(BigNumber& number) noexcept { return BigNumber::isGreater(number); }
        inline bool operator >(BigNumber&& number) noexcept { return BigNumber::operator >(number); }
        inline bool operator <=(BigNumber& number) noexcept { return BigNumber::operator ==(number) || BigNumber::operator <(number); }
        inline bool operator <=(BigNumber&& number) noexcept { return BigNumber::operator <=(number); }
        inline bool operator >=(BigNumber& number) noexcept { return BigNumber::operator ==(number) || BigNumber::operator >(number); }
        inline bool operator >=(BigNumber&& number) noexcept { return BigNumber::operator >=(number); }
        inline BigNumber operator ++(int const) noexcept { BigNumber const evaluation {*this}; BigNumber::operator ++(); return evaluation; }
        inline BigNumber& operator ++(void) noexcept { BigNumber::increment(); return *this; }
        inline BigNumber operator --(int const) noexcept { BigNumber const evaluation {*this}; BigNumber::operator --(); return evaluation; }
        inline BigNumber& operator --(void) noexcept { BigNumber::decrement(); return *this; }

        inline operator char const*(void) noexcept { return BigNumber::toString(); }
};

/* Modification > Big Number */
    // Add
    BigNumber& BigNumber::add(BigNumber const& number) noexcept {
        // Logic
        if (BigNumber::isComputable() || BigNumber::isFinite()) {
            // Logic
            if (BigNumber::isInfinite(number) || BigNumber::isNaN(number)) BigNumber::copy(number);
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
                                if ('\0' == *(evaluation + 1)) { if (carry) evaluation = (char*) BigNumber::increment(*evaluation); carry = '\0' ^ *(evaluation + 1); *iteratorA = carry ? *(evaluation + 1) : *evaluation; }
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

    // Divide
    BigNumber& BigNumber::divide(BigNumber const& number) noexcept { (void) number; return *this; }

    // Exponentiate
    BigNumber& BigNumber::exponentiate(BigNumber const& number) noexcept { (void) number; return *this; }

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
    long double BigNumber::getCharacteristics(void) const { return 0.00L; }

    // Get Mantissa
    long double BigNumber::getMantissa(void) const { return 0.00L; }

    // Has Significant Characteristics
    inline bool BigNumber::hasSignificantCharacteristics(void) const noexcept { return this -> characteristicsLength == 1u ? '0' ^ *(this -> value) : this -> characteristicsLength; }

    // Has Significant Mantissa
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
    bool BigNumber::isEqual(BigNumber const& numberA, BigNumber const& numberB) noexcept { (void) numberA; (void) numberB; return false; }

    // Is Finite
    bool BigNumber::isFinite(void) const noexcept { return BigNumber::INFINITE != this -> state; }

    // Is Greater
    bool BigNumber::isGreater(BigNumber const& numberA, BigNumber const& numberB) noexcept { (void) numberA; (void) numberB; return false; }

    // Is Infinite
    bool BigNumber::isInfinite(void) const noexcept { return BigNumber::INFINITE == this -> state; }

    // Is Integral
    inline bool BigNumber::isIntegral(void) const noexcept { return 0u == this -> mantissaLength; }

    // Is Lesser
    bool BigNumber::isLesser(BigNumber const& numberA, BigNumber const& numberB) noexcept { (void) numberA; (void) numberB; return false; }

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
    inline bool BigNumber::isZero(void) const noexcept { return BigNumber::isIntegral() && (this -> characteristicsLength ? this -> characteristicsLength : 1u) == 1u && '0' == *(NULL == this -> value ? (char*) "0" : this -> value); }

    // Modulo
    BigNumber& BigNumber::modulo(BigNumber const& number) noexcept { (void) number; return *this; }

    // Multiply --- NOTE (Lapys) -> Oddly enough, fractional multiplication (e.g.: `x * 0.5 -> x / 2`) can still be covered by long multiplication.
    BigNumber& BigNumber::multiply(BigNumber const& number) noexcept {
        // Logic
        if (BigNumber::isInfinite()) {
            // Logic > ...
            if (BigNumber::isNaN()) this -> state = BigNumber::UNCOMPUTABLE;
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

            else {
                // Logic > ...
                if (BigNumber::isNegative(number)) BigNumber::sign();

                // CHECKPOINT (Lapys)
                if (BigNumber::hasSignificantMantissa(number)) {}
                if (BigNumber::hasSignificantCharacteristics(number)) {}
            }
        }

        // Return
        return *this;
    }

    // Sign
    inline void BigNumber::sign(bool const strict) noexcept { this -> signedness = strict || !(this -> signedness); }

    // Subtract
    BigNumber& BigNumber::subtract(BigNumber const& number) noexcept { (void) number; return *this; }

    // To Number
    long double BigNumber::toNumber(BigNumber const& number) { (void) number; return 0.00L; }

    // To String
    inline char const* BigNumber::toString(void) const noexcept {
        // Evaluation > Evaluation
        char *evaluation = (char*) "";

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

/* Main */
int main(void) {
    /* [Initiate] ... */
    std::cout << "[PROGRAM INITIATED]" << std::endl;

    /* [Terminate] ... */
    std::cout << "[PROGRAM TERMINATED]" << std::flush;

    // Return
    return EXIT_SUCCESS;
}
