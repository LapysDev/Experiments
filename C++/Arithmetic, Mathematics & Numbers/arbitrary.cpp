/* Import */
    // [C Standard Library]
    #include <float.h> // Floating-Point
    #include <limits.h> // Limits
    #include <math.h> // Mathematics
    #include <stdarg.h> // Standard Arguments
    #include <stdlib.h> // Standard Library
    #include <string.h> // String

    // [C++ Standard Library]
    #include <iostream> // Input-Output Stream --- NOTE (Lapys) -> For testing.

/* Definition > ... */
template <size_t> class BigFloat;
template <size_t> class BigSignedInteger;
template <size_t> class BigUnsignedInteger;

/* Class > Big ... --- WARN (Lapys) -> Avoid copy elision. */
template <size_t radix>
class BigUnsignedInteger { typedef unsigned long primitive_t; friend int main(void);
    /* ... */
    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    // [...]
    protected:
        /* Phase > (Initiate, Terminate) --- REDACT (Lapys) --- NOTE (Lapys) ->
                - Initiate: Assert construction of the `Big` object.
                - Terminate: Unsuccessful program logic encountered.
        */
        constexpr inline void initiate(void) { if (SIZE_MAX == radix || 0u == radix || 1u == radix) { char radixString[20] {'0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}; for (size_t index = 0u, iterator = radix; iterator; ++index) { *(radixString + index) = *("0123456789" + (iterator % 10u)); if (0u == (iterator /= 10u)) { for (iterator = 0u; iterator < index; (--index, ++iterator)) { *(radixString + index) ^= *(radixString + iterator); *(radixString + iterator) ^= *(radixString + index); *(radixString + index) ^= *(radixString + iterator); } iterator = 0u; } } terminate("[Syntax Error]: Invalid radix `", radixString, "` specified for `BigNumber` object", NULL); } }

        constexpr inline void terminate(void) noexcept { BigUnsignedInteger::zero(); }
        inline void terminate(char const message[], ...) { va_list arguments; BigUnsignedInteger::zero(); ::putchar('\r'); va_start(arguments, message); for (char const *argument = message; NULL != argument; argument = va_arg(arguments, char const*)) for (char const *iterator = argument; '\0' ^ *iterator; ++iterator) ::putchar(*iterator); ::puts(""); va_end(arguments); ::abort(); }

        /* Method > (Allocate, Copy, Move, Size) --- NOTE (Lapys) ->
                - Allocate: Relinquishes or requests memory used by the `Big` object.
                - Copy: Copies deep values of `Big` object.
                - Move: Copies shallow (or surface) values of `Big` object; and zeroes stated `Big` object.
                - Size: Determines width of `Digit` subclass value.
        */
        constexpr inline void allocate(size_t const length) { if (length > SIZE_MAX /* NOTE (Lapys) -> Maximum allocable byte size per main memory allocation interface function call. */ / sizeof(Digit)) terminate("[Memory Error]: Unable to allocate additional memory for `BigNumber` object; The byte size requested is greater than allowed capable", NULL); else { void *allocation = NULL == this -> value ? ::malloc(length * sizeof(Digit)) : ::realloc(this -> value, length * sizeof(Digit)); if (NULL == allocation) terminate("[Memory Error]: Unable to ", NULL == this -> value ? "allocate additional " : "modify ", "memory for `BigNumber` object", NULL); else this -> value = (Digit*) allocation; } }
        constexpr inline void copy(BigUnsignedInteger const& number) { if (&number != this) { if ((this -> length = number.length) && NULL != number.value) { BigUnsignedInteger::allocate(number.length); ::memcpy(this -> value, number.value, number.length * sizeof(Digit)); } else this -> value = NULL; } }
        template <size_t base> constexpr inline void copy(BigUnsignedInteger<base> const& number) { BigUnsignedInteger::move(BigUnsignedInteger::fromBase<base>(number)); }
        constexpr inline void move(BigUnsignedInteger&& number) noexcept { this -> length = number.length; this -> value = number.value; number.length = 0u; number.value = NULL; }
        constexpr inline static size_t size(void) noexcept { size_t size = 0u; for (size_t iterator = radix; iterator; iterator >>= 1u) ++size; return size ? size : 1u; }

    // [...]
    private:
        // Initialization > (Length, Value)
        size_t length;
        struct Digit { typedef size_t digit_t; // NOTE (Lapys) -> Digits are stored as denary `digit_t` values.
            private: digit_t value : BigUnsignedInteger::size();
            public:
                constexpr inline Digit(digit_t const value) : value{value} {}

                constexpr inline static bool isEqual(Digit const digitA, Digit const digitB) noexcept { return digitA.value == digitB.value; }
                constexpr inline static bool isGreater(Digit const digitA, Digit const digitB) noexcept { return digitA.value > digitB.value; }
                constexpr inline static bool isHighestRank(Digit const digit) noexcept { return digit.value == radix - 1u; }
                constexpr inline static bool isLesser(Digit const digitA, Digit const digitB) noexcept { return digitA.value < digitB.value; }
                constexpr inline static bool isLowerRank(Digit const digit) noexcept { return digit.value < (radix / 2u); }
                template <size_t> constexpr inline static bool isLowestRank(Digit const digit) noexcept { return 0u == digit.value; }
                constexpr inline static bool isMeanRank(Digit const digit) noexcept { return digit.value == radix / 2u || ((radix & 1u) && (digit.value == (radix / 2u) + 1u)); }
                constexpr inline static bool isUpperRank(Digit const digit) noexcept { return digit.value > (radix / 2u) + (radix & 1u); }

                inline Digit const* add(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; if (Digit::isLowestRank<radix>(digitA)) { *evaluation = 0u; *(evaluation + 1) = digitB; } else if (Digit::isLowestRank<radix>(digitB)) { *evaluation = 0u; *(evaluation + 1) = digitA; } else if (Digit::isMeanRank<radix>(digitA) && Digit::isMeanRank<radix>(digitB)) { *evaluation = 1u; *(evaluation + 1) = 0u; } else if (Digit::isUpperRank<radix>(digitA)) { if (radix - digitA > digitB) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitB - (radix - digitA); } } else if (Digit::isUpperRank<radix>(digitB)) { if (radix - digitB > digitA) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitA - (radix - digitB); } } else { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } return &*evaluation; }
                inline Digit const* multiply(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; ::memset(evaluation, 0u, sizeof(evaluation)); for (digit_t iterator = digitB.value; false == Digit::isLowestRank<radix>(iterator); --iterator) for (digit_t subiterator = digitA.value; false == Digit::isLowestRank<radix>(subiterator); --subiterator) { if (Digit::isHighestRank<radix>(*(evaluation + 1))) { ++*evaluation; *(evaluation + 1) = 0u; } else ++*(evaluation + 1); } return &*evaluation; }
                inline Digit const* subtract(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; if (digitA == digitB) { *evaluation = 0u; *(evaluation + 1) = 0u; } else if (digitA < digitB) { *evaluation = 1u; *(evaluation + 1) = digitB - digitA; } else { *evaluation = 0u; *(evaluation + 1) = digitA - digitB; } return &*evaluation; }

                constexpr inline Digit& operator =(digit_t const value) noexcept { this -> value = value; return *this; }
                constexpr inline Digit& operator +=(digit_t const value) noexcept { this -> value += value; return *this; }
                constexpr inline Digit& operator -=(digit_t const value) noexcept { this -> value -= value; return *this; }
                constexpr inline Digit& operator *=(digit_t const value) noexcept { this -> value *= value; return *this; }
                constexpr inline Digit& operator /=(digit_t const value) noexcept { this -> value /= value; return *this; }
                constexpr inline Digit& operator ^=(digit_t const value) noexcept { this -> value ^= value; return *this; }
                constexpr inline Digit& operator &=(digit_t const value) noexcept { this -> value &= value; return *this; }
                constexpr inline Digit& operator |=(digit_t const value) noexcept { this -> value |= value; return *this; }
                constexpr inline Digit& operator <<=(digit_t const value) noexcept { this -> value <<= value; return *this; }
                constexpr inline Digit& operator >>=(digit_t const value) noexcept { this -> value >>= value; return *this; }
                constexpr inline Digit operator ++(int const)& noexcept { Digit const evaluation {this -> value}; ++(this -> value); return evaluation; }
                constexpr inline Digit& operator ++(int const)&& noexcept { ++(this -> value); return *this; }
                constexpr inline Digit& operator ++(void) noexcept { ++(this -> value); return *this; }
                constexpr inline Digit operator --(int const)& noexcept { Digit const evaluation {this -> value}; --(this -> value); return evaluation; }
                constexpr inline Digit& operator --(int const)&& noexcept { --(this -> value); return *this; }
                constexpr inline Digit& operator --(void) noexcept { --(this -> value); return *this; }
                constexpr inline operator digit_t(void) const noexcept { return this -> value; }
        } *value;

    // [...]
    public:
        // [Constructor]
        constexpr inline BigUnsignedInteger(void) : length{0u}, value{NULL} { initiate(); }
        constexpr inline BigUnsignedInteger(primitive_t const number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::move(BigUnsignedInteger::fromNumber(number)); }

        constexpr inline BigUnsignedInteger(BigFloat<radix> const& number) : length{0u}, value{NULL} { initiate(); BigFloat<radix>::isSafe(number) ? BigUnsignedInteger::copy((BigUnsignedInteger const&) number) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigUnsignedInteger` object", NULL); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigFloat<base> const& number) : length{0u}, value{NULL} { initiate(); BigFloat<base>::isSafe(number) ? BigUnsignedInteger::move(BigUnsignedInteger::fromBase((BigUnsignedInteger<base> const&) number)) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigUnsignedInteger` object", NULL); }
        constexpr inline BigUnsignedInteger(BigFloat<radix>&& number) : length{0u}, value{NULL} { initiate(); BigFloat<radix>::isSafe(number) ? BigUnsignedInteger::move((BigUnsignedInteger&&) number) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigUnsignedInteger` object", NULL); }

        constexpr inline BigUnsignedInteger(BigSignedInteger<radix> const& number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::copy((BigUnsignedInteger const&) number); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigSignedInteger<base> const& number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::move(BigUnsignedInteger::fromBase((BigUnsignedInteger<base> const&) number)); }

        constexpr inline BigUnsignedInteger(BigUnsignedInteger const& number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::copy(number); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigUnsignedInteger<base> const& number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::move(BigUnsignedInteger::fromBase(number)); }

        inline ~BigUnsignedInteger(void) { terminate(); }

        // Method > ...
            // [Conditional] Is (Big, Computable, Denormalized, Equal, Finite, Fraction, Greater, Infinite, Integer, Lesser, Negative, Non-Computable, Normalized, Positive, Safe, Significant, Zero)
            constexpr inline bool isBig(void) const noexcept { return BigUnsignedInteger::isBig(*this); }
            constexpr static bool isBig(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isComputable(void) const noexcept { return BigUnsignedInteger::isComputable(*this); }
            constexpr static bool isComputable(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isDenormalized(void) const noexcept { return BigUnsignedInteger::isDenormalized(*this); }
            constexpr static bool isDenormalized(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isEqual(BigUnsignedInteger const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, number); }
            template <size_t base> constexpr inline bool isEqual(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, BigUnsignedInteger::fromBase<base>(number)); }
            constexpr static bool isEqual(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;
            constexpr inline bool isFinite(void) const noexcept { return BigUnsignedInteger::isFinite(*this); }
            constexpr static bool isFinite(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isFraction(void) const noexcept { return BigUnsignedInteger::isFraction(*this); }
            constexpr static bool isFraction(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isGreater(BigUnsignedInteger const& number) const noexcept { return BigUnsignedInteger::isGreater(*this, number); }
            template <size_t base> constexpr inline bool isGreater(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isGreater(*this, BigUnsignedInteger::fromBase<base>(number)); }
            constexpr static bool isGreater(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;
            constexpr inline bool isInfinite(void) const noexcept { return BigUnsignedInteger::isInfinite(*this); }
            constexpr static bool isInfinite(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isInteger(void) const noexcept { return BigUnsignedInteger::isInteger(*this); }
            constexpr static bool isInteger(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isLesser(BigUnsignedInteger const& number) const noexcept { return BigUnsignedInteger::isLesser(*this, number); }
            template <size_t base> constexpr inline bool isLesser(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isLesser(*this, BigUnsignedInteger::fromBase<base>(number)); }
            constexpr static bool isLesser(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;
            constexpr inline bool isNegative(void) const noexcept { return BigUnsignedInteger::isNegative(*this); }
            constexpr static bool isNegative(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isNonComputable(void) const noexcept { return BigUnsignedInteger::isNonComputable(*this); }
            constexpr static bool isNonComputable(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isNormalized(void) const noexcept { return BigUnsignedInteger::isNormalized(*this); }
            constexpr static bool isNormalized(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isPositive(void) const noexcept { return BigUnsignedInteger::isPositive(*this); }
            constexpr static bool isPositive(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isSafe(void) const noexcept { return BigUnsignedInteger::isSafe(*this); }
            constexpr static bool isSafe(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isSignificant(void) const noexcept { return BigUnsignedInteger::isSignificant(*this); }
            constexpr static bool isSignificant(BigUnsignedInteger const&) noexcept;
            constexpr inline bool isZero(void) const noexcept { return BigUnsignedInteger::isZero(*this); }
            constexpr static bool isZero(BigUnsignedInteger const&) noexcept;

            // [Miscellaneous] From (Base, Number), To (Base, Number, String), Zero
            template <size_t base> constexpr static BigUnsignedInteger fromBase(BigUnsignedInteger<base> const&);
            constexpr static BigUnsignedInteger fromNumber(primitive_t const number);
            template <size_t base> constexpr static BigUnsignedInteger<base> toBase(BigUnsignedInteger const&);
            constexpr static primitive_t toNumber(BigUnsignedInteger const&);
            constexpr char* toString(void) const;
            constexpr inline void zero(void) noexcept { this -> length = 0u; if (NULL != this -> value) { ::free(this -> value); this -> value = NULL; } }

            // [Operational] Add, Decrement, Divide, Exponentiate, Increment, Multiply, Shift (Left, Right), Sign, Subtract, Unsign
            constexpr BigUnsignedInteger& add(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& add(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::add(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger add(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.add(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& add(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { numberB.add(numberA); return numberB; }
            constexpr inline static BigUnsignedInteger& add(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.add(numberB); return numberA; }
            constexpr BigUnsignedInteger& decrement(void);
            constexpr inline BigUnsignedInteger decrement(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.decrement(); return evaluation; }
            constexpr BigUnsignedInteger& divide(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& divide(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::divide(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger divide(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.divide(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& divide(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.divide(numberB); return numberA; }
            constexpr BigUnsignedInteger& exponentiate(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& exponentiate(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::exponentiate(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger exponentiate(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.exponentiate(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& exponentiate(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.exponentiate(numberB); return numberA; }
            constexpr BigUnsignedInteger& increment(void);
            constexpr inline BigUnsignedInteger increment(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }
            constexpr BigUnsignedInteger& multiply(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& multiply(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::multiply(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger multiply(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.multiply(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& multiply(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { numberB.multiply(numberA); return numberB; }
            constexpr inline static BigUnsignedInteger& multiply(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.multiply(numberB); return numberA; }
            constexpr BigUnsignedInteger& shiftLeft(void);
            constexpr BigUnsignedInteger& shiftLeft(primitive_t const);
            constexpr inline static BigUnsignedInteger shiftLeft(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.shiftLeft(); return evaluation; }
            constexpr inline static BigUnsignedInteger shiftLeft(BigUnsignedInteger const& numberA, primitive_t const numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.shiftLeft(numberB); return evaluation; }
            constexpr BigUnsignedInteger& shiftRight(void);
            constexpr BigUnsignedInteger& shiftRight(primitive_t const);
            constexpr inline static BigUnsignedInteger shiftRight(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.shiftRight(); return evaluation; }
            constexpr inline static BigUnsignedInteger shiftRight(BigUnsignedInteger const& numberA, primitive_t const numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.shiftRight(numberB); return evaluation; }
            constexpr BigUnsignedInteger& sign(void);
            constexpr BigUnsignedInteger sign(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.sign(); return evaluation; }
            constexpr BigUnsignedInteger& subtract(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& subtract(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::subtract(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger subtract(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.subtract(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& subtract(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.subtract(numberB); return numberA; }
            constexpr BigUnsignedInteger& unsign(void);
            constexpr BigUnsignedInteger unsign(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.unsign(); return evaluation; }
};

template <size_t radix>
class BigSignedInteger : public BigUnsignedInteger<radix> { typedef signed long primitive_t; friend int main(void);
    /* ... */
    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    // [...]
    private:
        // Initialization > Signedness
        bool signedness;

    // [...]
    public:
        // [Constructor]
        constexpr inline BigSignedInteger(void) : BigUnsignedInteger<radix>(), signedness{false} {}
};

template <size_t radix>
class BigFloat : public BigSignedInteger<radix> { typedef long double primitive_t; friend int main(void);
    /* ... */
    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    // [...]
    public:
        size_t mantissaLength;
        enum State {INDETERMINABLE, INFINITE, SAFE, UNCOMPUTABLE} state;

    // [...]
    public:
        // [Constructor]
        constexpr inline BigFloat(void) : BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} { this -> length = 1u; }
        constexpr inline BigFloat(State const state) : BigSignedInteger<radix>(), mantissaLength{0u}, state{state} {}
};

/* Modification */
    /* Big Float --- CHECKPOINT (Lapys) */
    /* Big Signed Integer --- CHECKPOINT (Lapys) */
    /* Big Unsigned Integer */
        // From Base --- CHECKPOINT (Lapys)
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<radix> BigUnsignedInteger<radix>::fromBase(BigUnsignedInteger<base> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<radix> evaluation {};

            (void) number;

            // Return
            return evaluation;
        }

        // From Number --- CHECKPOINT (Lapys)
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix> BigUnsignedInteger<radix>::fromNumber(primitive_t const number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<radix> evaluation {};

            (void) number;

            // Return
            return evaluation;
        }

        // To Base --- CHECKPOINT (Lapys)
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<base> BigUnsignedInteger<radix>::toBase(BigUnsignedInteger<radix> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<base> evaluation {};

            (void) number;

            // Return
            return evaluation;
        }

        // To Number --- CHECKPOINT (Lapys)
        template <size_t radix>
        constexpr inline typename BigUnsignedInteger<radix>::primitive_t BigUnsignedInteger<radix>::toNumber(BigUnsignedInteger const& number) {
            // Evaluation > Evaluation
            primitive_t evaluation {0u};

            (void) number;

            // Return
            return evaluation;
        }

        // To String
        template <size_t radix>
        constexpr inline char* BigUnsignedInteger<radix>::toString(void) const {
            // Evaluation > Evaluation
            char evaluation[] {NULL};

            // Return
            return evaluation;
        }

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
