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
class BigUnsignedInteger { friend int main(void);
    /* ... */
    typedef unsigned long primitive_t;

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
        inline void terminate(char const message[], ...) { va_list arguments; BigUnsignedInteger::zero(); ::putchar('\r'); va_start(arguments, message); for (char const *argument = message; NULL != argument; argument = va_arg(arguments, char const*)) for (char const *iterator = argument; '\0' ^ *iterator; ++iterator) ::putchar(*iterator); ::putchar('\n'); va_end(arguments); ::abort(); }

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
                constexpr inline static bool isLowestRank(Digit const digit) noexcept { return 0u == digit.value; }
                constexpr inline static bool isMeanRank(Digit const digit) noexcept { return digit.value == radix / 2u || ((radix & 1u) && (digit.value == (radix / 2u) + 1u)); }
                constexpr inline static bool isUpperRank(Digit const digit) noexcept { return digit.value > (radix / 2u) + (radix & 1u); }

                inline Digit const* add(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; if (Digit::isLowestRank(digitA)) { *evaluation = 0u; *(evaluation + 1) = digitB; } else if (Digit::isLowestRank(digitB)) { *evaluation = 0u; *(evaluation + 1) = digitA; } else if (Digit::isMeanRank(digitA) && Digit::isMeanRank(digitB)) { *evaluation = 1u; *(evaluation + 1) = 0u; } else if (Digit::isUpperRank(digitA)) { if (radix - digitA > digitB) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitB - (radix - digitA); } } else if (Digit::isUpperRank(digitB)) { if (radix - digitB > digitA) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitA - (radix - digitB); } } else { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } return &*evaluation; }
                inline Digit const* multiply(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; ::memset(evaluation, 0u, sizeof(evaluation)); for (digit_t iterator = digitB.value; false == Digit::isLowestRank(iterator); --iterator) for (digit_t subiterator = digitA.value; false == Digit::isLowestRank(subiterator); --subiterator) { if (Digit::isHighestRank(*(evaluation + 1))) { ++*evaluation; *(evaluation + 1) = 0u; } else ++*(evaluation + 1); } return &*evaluation; }
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
        template <size_t base> constexpr inline BigUnsignedInteger(BigFloat<base> const& number) : length{0u}, value{NULL} { initiate(); BigFloat<base>::isSafe(number) ? BigUnsignedInteger::move(BigUnsignedInteger::fromBase<base>((BigUnsignedInteger<base> const&) number)) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigUnsignedInteger` object", NULL); }
        constexpr inline BigUnsignedInteger(BigFloat<radix>&& number) : length{0u}, value{NULL} { initiate(); BigFloat<radix>::isSafe(number) ? BigUnsignedInteger::move((BigUnsignedInteger&&) number) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigUnsignedInteger` object", NULL); }
        constexpr inline BigUnsignedInteger(BigSignedInteger<radix> const& number) : length{0u}, value{NULL} { initiate(); if (BigSignedInteger<radix>::isPositive(number)) BigUnsignedInteger::copy((BigUnsignedInteger const&) number); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigSignedInteger<base> const& number) : length{0u}, value{NULL} { initiate(); if (BigSignedInteger<radix>::isPositive(number)) BigUnsignedInteger::move(BigUnsignedInteger::fromBase<base>((BigUnsignedInteger<base> const&) number)); }
        constexpr inline BigUnsignedInteger(BigSignedInteger<radix>&& number) : length{0u}, value{NULL} { initiate(); if (BigSignedInteger<radix>::isPositive(number)) BigUnsignedInteger::move((BigUnsignedInteger&&) number); }
        constexpr inline BigUnsignedInteger(BigUnsignedInteger const& number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::copy(number); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigUnsignedInteger<base> const& number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::move((BigUnsignedInteger&&) BigUnsignedInteger::fromBase<base>(number)); }
        constexpr inline BigUnsignedInteger(BigUnsignedInteger&& number) : length{0u}, value{NULL} { initiate(); BigUnsignedInteger::move((BigUnsignedInteger&&) number); }

        // [Destructor]
        inline ~BigUnsignedInteger(void) { terminate(); }

        // Method > ...
            // [Conditional] Is (Base Factor, Big, Computable, Denormalized, Equal, Even, Finite, Fraction, Greater, Infinite, Integer, Lesser, Negative, Non-Computable, Normalized, Odd, Positive, Safe, Significant, Zero)
            constexpr inline bool isBaseFactor(void) const noexcept { return BigUnsignedInteger::isBaseFactor(*this); }
            constexpr static bool isBaseFactor(BigUnsignedInteger const&) noexcept;

            inline bool isBig(void) const noexcept { return BigUnsignedInteger::isBig(*this); }
            static bool isBig(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isComputable(void) const noexcept { return BigUnsignedInteger::isComputable(*this); }
            constexpr static bool isComputable(BigUnsignedInteger const&) noexcept;

            constexpr bool isEqual(BigFloat<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isEqual(BigFloat<base> const& number) const noexcept { return BigUnsignedInteger::isEqual(BigFloat<radix>::fromBase<base>(number)); }
            constexpr bool isEqual(BigSignedInteger<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isEqual(BigSignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isEqual(BigSignedInteger<radix>::fromBase<base>(number)); }
            constexpr inline bool isEqual(BigUnsignedInteger const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, number); }
            template <size_t base> constexpr inline bool isEqual(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, BigUnsignedInteger::fromBase<base>(number)); }
            constexpr static bool isEqual(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;

            constexpr inline bool isEven(void) const noexcept { return BigUnsignedInteger::isEven(*this); }
            constexpr static bool isEven(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isFinite(void) const noexcept { return BigUnsignedInteger::isFinite(*this); }
            constexpr static bool isFinite(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isFraction(void) const noexcept { return BigUnsignedInteger::isFraction(*this); }
            constexpr static bool isFraction(BigUnsignedInteger const&) noexcept;

            constexpr bool isGreater(BigFloat<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isGreater(BigFloat<base> const& number) const noexcept { return BigUnsignedInteger::isGreater(BigFloat<radix>::fromBase<base>(number)); }
            constexpr bool isGreater(BigSignedInteger<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isGreater(BigSignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isGreater(BigSignedInteger<radix>::fromBase<base>(number)); }
            constexpr inline bool isGreater(BigUnsignedInteger const& number) const noexcept { return BigUnsignedInteger::isGreater(*this, number); }
            template <size_t base> constexpr inline bool isGreater(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isGreater(*this, BigUnsignedInteger::fromBase<base>(number)); }
            constexpr static bool isGreater(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;

            constexpr inline bool isInfinite(void) const noexcept { return BigUnsignedInteger::isInfinite(*this); }
            constexpr static bool isInfinite(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isInteger(void) const noexcept { return BigUnsignedInteger::isInteger(*this); }
            constexpr static bool isInteger(BigUnsignedInteger const&) noexcept;

            constexpr bool isLesser(BigFloat<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isLesser(BigFloat<base> const& number) const noexcept { return BigUnsignedInteger::isLesser(BigFloat<radix>::fromBase<base>(number)); }
            constexpr bool isLesser(BigSignedInteger<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isLesser(BigSignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isLesser(BigSignedInteger<radix>::fromBase<base>(number)); }
            constexpr inline bool isLesser(BigUnsignedInteger const& number) const noexcept { return BigUnsignedInteger::isLesser(*this, number); }
            template <size_t base> constexpr inline bool isLesser(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isLesser(*this, BigUnsignedInteger::fromBase<base>(number)); }
            constexpr static bool isLesser(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;

            constexpr inline bool isNegative(void) const noexcept { return BigUnsignedInteger::isNegative(*this); }
            constexpr static bool isNegative(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isNonComputable(void) const noexcept { return BigUnsignedInteger::isNonComputable(*this); }
            constexpr static bool isNonComputable(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isOdd(void) const noexcept { return BigUnsignedInteger::isOdd(*this); }
            constexpr static bool isOdd(BigUnsignedInteger const&) noexcept;

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
            constexpr static primitive_t toNumber(BigUnsignedInteger&);
            constexpr char* toString(void) const;
            constexpr inline void zero(void) noexcept { this -> length = 0u; if (NULL != this -> value) { ::free(this -> value); this -> value = NULL; } }

            // [Operational] Add, Decrement, Divide, Exponentiate, Increment, Multiply, Shift (Left, Right), Sign, Subtract, Unsign
            constexpr BigUnsignedInteger& add(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& add(BigFloat<radix> const& number) { return BigUnsignedInteger::add(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& add(BigSignedInteger<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& add(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::add(BigSignedInteger<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& add(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& add(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::add(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger add(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.add(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& add(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { numberB.add(numberA); return numberB; }
            constexpr inline static BigUnsignedInteger& add(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.add(numberB); return numberA; }

            constexpr BigUnsignedInteger& decrement(void);
            constexpr inline BigUnsignedInteger decrement(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.decrement(); return evaluation; }

            constexpr BigUnsignedInteger& divide(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& divide(BigFloat<radix> const& number) { return BigUnsignedInteger::divide(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& divide(BigSignedInteger<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& divide(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::divide(BigSignedInteger<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& divide(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& divide(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::divide(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger divide(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.divide(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& divide(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.divide(numberB); return numberA; }

            constexpr BigUnsignedInteger& exponentiate(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& exponentiate(BigFloat<radix> const& number) { return BigUnsignedInteger::exponentiate(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& exponentiate(BigSignedInteger<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& exponentiate(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::exponentiate(BigSignedInteger<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& exponentiate(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& exponentiate(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::exponentiate(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger exponentiate(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.exponentiate(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& exponentiate(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.exponentiate(numberB); return numberA; }

            constexpr BigUnsignedInteger& increment(void);
            constexpr inline BigUnsignedInteger increment(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }

            constexpr BigUnsignedInteger& multiply(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& multiply(BigFloat<radix> const& number) { return BigUnsignedInteger::multiply(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& multiply(BigSignedInteger<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& multiply(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::multiply(BigSignedInteger<radix>::fromBase<base>(number)); }
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

            constexpr BigUnsignedInteger& sign(void) const noexcept;
            constexpr BigUnsignedInteger sign(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.sign(); return evaluation; }

            constexpr BigUnsignedInteger& subtract(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& subtract(BigFloat<radix> const& number) { return BigUnsignedInteger::subtract(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& subtract(BigSignedInteger<radix> const&);
            template <size_t base> constexpr inline BigUnsignedInteger& subtract(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::subtract(BigSignedInteger<radix>::fromBase<base>(number)); }
            constexpr BigUnsignedInteger& subtract(BigUnsignedInteger const&);
            template <size_t base> constexpr inline BigUnsignedInteger& subtract(BigUnsignedInteger<base> const& number) { return BigUnsignedInteger::subtract(BigUnsignedInteger::fromBase<base>(number)); }
            constexpr inline static BigUnsignedInteger subtract(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.subtract(numberB); return evaluation; }
            constexpr inline static BigUnsignedInteger& subtract(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { numberA.subtract(numberB); return numberA; }

            constexpr BigUnsignedInteger& unsign(void) const noexcept;
            constexpr BigUnsignedInteger unsign(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.unsign(); return evaluation; }
};

template <size_t radix>
class BigSignedInteger : public BigUnsignedInteger<radix> { friend int main(void);
    /* ... */
    typedef typename BigUnsignedInteger<radix>::Digit Digit;
    typedef signed long primitive_t;

    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    using BigUnsignedInteger<radix>::initiate;
    using BigUnsignedInteger<radix>::terminate;

    // [...]
    private:
        // Initialization > Signedness
        bool signedness;

    // [...]
    protected:
        // Method > (Copy, Move)
        constexpr inline void copy(BigSignedInteger const& number) noexcept { this -> signedness = number.signedness; BigUnsignedInteger<radix>::copy((BigUnsignedInteger<radix> const&) number); }
        constexpr inline void move(BigSignedInteger&& number) noexcept { this -> signedness = number.signedness; BigUnsignedInteger<radix>::move((BigUnsignedInteger<radix>&&) number); }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigSignedInteger(void) : BigUnsignedInteger<radix>(), signedness{false} {}
        constexpr inline BigSignedInteger(primitive_t const number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::move(BigSignedInteger::fromNumber(number)); }
        constexpr inline BigSignedInteger(BigFloat<radix> const& number) : BigUnsignedInteger<radix>(), signedness{false} { BigFloat<radix>::isSafe(number) ? BigSignedInteger::copy((BigSignedInteger const&) number) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigSignedInteger` object", NULL); }
        template <size_t base> constexpr inline BigSignedInteger(BigFloat<base> const& number) : BigUnsignedInteger<radix>(), signedness{false} { BigFloat<base>::isSafe(number) ? BigSignedInteger::move(BigSignedInteger::fromBase<base>((BigSignedInteger<base> const&) number)) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigSignedInteger` object", NULL); }
        constexpr inline BigSignedInteger(BigFloat<radix>&& number) : BigUnsignedInteger<radix>(), signedness{false} { BigFloat<radix>::isSafe(number) ? BigSignedInteger::move((BigSignedInteger&&) number) : terminate("[Syntax Error]: Unable to represent `BigFloat` as `BigSignedInteger` object", NULL); }
        constexpr inline BigSignedInteger(BigSignedInteger const& number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy(number); }
        template <size_t base> constexpr inline BigSignedInteger(BigSignedInteger<base> const& number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy(BigSignedInteger::fromBase<base>(number)); }
        constexpr inline BigSignedInteger(BigSignedInteger&& number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::move((BigSignedInteger&&) number); }
        template <size_t base> constexpr inline BigSignedInteger(BigUnsignedInteger<base> const& number) : BigUnsignedInteger<radix>(number), signedness{false} {}
        constexpr inline BigSignedInteger(BigUnsignedInteger<radix>&& number) : BigUnsignedInteger<radix>((BigUnsignedInteger<radix>&&) number), signedness{false} {}

        // Method > ...
            // [Conditional] Is (Big, Equal, Greater, Lesser, Negative, Positive)
            inline bool isBig(void) const noexcept { return BigSignedInteger::isBig(*this); }
            static bool isBig(BigSignedInteger const&) noexcept;

            constexpr bool isEqual(BigFloat<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isEqual(BigFloat<base> const& number) const noexcept { return BigSignedInteger::isEqual(BigFloat<radix>::fromBase<base>(number)); }
            constexpr inline bool isEqual(BigSignedInteger const& number) const noexcept { return BigSignedInteger::isEqual(*this, number); }
            constexpr bool isEqual(BigUnsignedInteger<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isEqual(BigUnsignedInteger<base> const& number) const noexcept { return BigSignedInteger::isEqual(BigUnsignedInteger<radix>::fromBase<base>(number)); }
            template <size_t base> constexpr inline bool isEqual(BigSignedInteger<base> const& number) const noexcept { return BigSignedInteger::isEqual(*this, BigSignedInteger::fromBase<base>(number)); }
            constexpr static bool isEqual(BigSignedInteger const&, BigSignedInteger const&) noexcept;

            constexpr bool isGreater(BigFloat<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isGreater(BigFloat<base> const& number) const noexcept { return BigSignedInteger::isGreater(BigFloat<radix>::fromBase<base>(number)); }
            constexpr inline bool isGreater(BigSignedInteger const& number) const noexcept { return BigSignedInteger::isGreater(*this, number); }
            constexpr bool isGreater(BigUnsignedInteger<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isGreater(BigUnsignedInteger<base> const& number) const noexcept { return BigSignedInteger::isGreater(BigUnsignedInteger<radix>::fromBase<base>(number)); }
            template <size_t base> constexpr inline bool isGreater(BigSignedInteger<base> const& number) const noexcept { return BigSignedInteger::isGreater(*this, BigSignedInteger::fromBase<base>(number)); }
            constexpr static bool isGreater(BigSignedInteger const&, BigSignedInteger const&) noexcept;

            constexpr bool isLesser(BigFloat<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isLesser(BigFloat<base> const& number) const noexcept { return BigSignedInteger::isLesser(BigFloat<radix>::fromBase<base>(number)); }
            constexpr inline bool isLesser(BigSignedInteger const& number) const noexcept { return BigSignedInteger::isLesser(*this, number); }
            constexpr bool isLesser(BigUnsignedInteger<radix> const&) const noexcept;
            template <size_t base> constexpr inline bool isLesser(BigUnsignedInteger<base> const& number) const noexcept { return BigSignedInteger::isLesser(BigUnsignedInteger<radix>::fromBase<base>(number)); }
            template <size_t base> constexpr inline bool isLesser(BigSignedInteger<base> const& number) const noexcept { return BigSignedInteger::isLesser(*this, BigSignedInteger::fromBase<base>(number)); }
            constexpr static bool isLesser(BigSignedInteger const&, BigSignedInteger const&) noexcept;

            constexpr inline bool isNegative(void) const noexcept { return BigSignedInteger::isNegative(*this); }
            constexpr static bool isNegative(BigSignedInteger const&) noexcept;

            constexpr inline bool isPositive(void) const noexcept { return BigSignedInteger::isPositive(*this); }
            constexpr static bool isPositive(BigSignedInteger const&) noexcept;

            // [Miscellaneous] From (Base, Number), To (Base, Number, String), Zero
            template <size_t base> constexpr static BigSignedInteger fromBase(BigSignedInteger<base> const&);
            constexpr static BigSignedInteger fromNumber(primitive_t const number);
            template <size_t base> constexpr static BigSignedInteger<base> toBase(BigSignedInteger const&);
            constexpr static primitive_t toNumber(BigSignedInteger const&);
            constexpr char* toString(void) const;
            constexpr inline void zero(void) noexcept { BigSignedInteger::unsign(); BigUnsignedInteger<radix>::zero(); }

            // [Operational] Add, Decrement, Divide, Exponentiate, Increment, Multiply, Sign, Subtract, Unsign
            constexpr BigSignedInteger& add(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& add(BigFloat<base> const& number) { return BigSignedInteger::add(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigSignedInteger& add(BigSignedInteger const&);
            template <size_t base> constexpr inline BigSignedInteger& add(BigSignedInteger<base> const& number) { return BigSignedInteger::add(BigSignedInteger::fromBase<base>(number)); }
            constexpr inline static BigSignedInteger add(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {}; evaluation.copy(numberA); evaluation.add(numberB); return evaluation; }
            constexpr inline static BigSignedInteger& add(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { numberB.add(numberA); return numberB; }
            constexpr inline static BigSignedInteger& add(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { numberA.add(numberB); return numberA; }
            constexpr BigSignedInteger& add(BigUnsignedInteger<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& add(BigUnsignedInteger<base> const& number) { return BigSignedInteger::add(BigUnsignedInteger<radix>::fromBase<base>(number)); }

            constexpr BigSignedInteger& decrement(void);
            constexpr inline BigSignedInteger decrement(BigSignedInteger const& number) { BigSignedInteger evaluation {}; evaluation.copy(number); evaluation.decrement(); return evaluation; }

            constexpr BigSignedInteger& divide(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& divide(BigFloat<base> const& number) { return BigSignedInteger::divide(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigSignedInteger& divide(BigSignedInteger const&);
            template <size_t base> constexpr inline BigSignedInteger& divide(BigSignedInteger<base> const& number) { return BigSignedInteger::divide(BigSignedInteger::fromBase<base>(number)); }
            constexpr inline static BigSignedInteger divide(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {}; evaluation.copy(numberA); evaluation.divide(numberB); return evaluation; }
            constexpr inline static BigSignedInteger& divide(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { numberA.divide(numberB); return numberA; }
            constexpr BigSignedInteger& divide(BigUnsignedInteger<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& divide(BigUnsignedInteger<base> const& number) { return BigSignedInteger::divide(BigUnsignedInteger<radix>::fromBase<base>(number)); }

            constexpr BigSignedInteger& exponentiate(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& exponentiate(BigFloat<base> const& number) { return BigSignedInteger::exponentiate(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigSignedInteger& exponentiate(BigSignedInteger const&);
            template <size_t base> constexpr inline BigSignedInteger& exponentiate(BigSignedInteger<base> const& number) { return BigSignedInteger::exponentiate(BigSignedInteger::fromBase<base>(number)); }
            constexpr inline static BigSignedInteger exponentiate(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {}; evaluation.copy(numberA); evaluation.exponentiate(numberB); return evaluation; }
            constexpr inline static BigSignedInteger& exponentiate(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { numberA.exponentiate(numberB); return numberA; }
            constexpr BigSignedInteger& exponentiate(BigUnsignedInteger<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& exponentiate(BigUnsignedInteger<base> const& number) { return BigSignedInteger::exponentiate(BigUnsignedInteger<radix>::fromBase<base>(number)); }

            constexpr BigSignedInteger& increment(void);
            constexpr inline BigSignedInteger increment(BigSignedInteger const& number) { BigSignedInteger evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }

            constexpr BigSignedInteger& multiply(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& multiply(BigFloat<base> const& number) { return BigSignedInteger::multiply(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigSignedInteger& multiply(BigSignedInteger const&);
            template <size_t base> constexpr inline BigSignedInteger& multiply(BigSignedInteger<base> const& number) { return BigSignedInteger::multiply(BigSignedInteger::fromBase<base>(number)); }
            constexpr inline static BigSignedInteger multiply(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {}; evaluation.copy(numberA); evaluation.multiply(numberB); return evaluation; }
            constexpr inline static BigSignedInteger& multiply(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { numberB.multiply(numberA); return numberB; }
            constexpr inline static BigSignedInteger& multiply(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { numberA.multiply(numberB); return numberA; }
            constexpr BigSignedInteger& multiply(BigUnsignedInteger<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& multiply(BigUnsignedInteger<base> const& number) { return BigSignedInteger::multiply(BigUnsignedInteger<radix>::fromBase<base>(number)); }

            constexpr BigSignedInteger& sign(void) noexcept;
            constexpr BigSignedInteger sign(BigSignedInteger const& number) { BigSignedInteger evaluation {}; evaluation.copy(number); evaluation.sign(); return evaluation; }

            constexpr BigSignedInteger& subtract(BigFloat<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& subtract(BigFloat<base> const& number) { return BigSignedInteger::subtract(BigFloat<radix>::fromBase<base>(number)); }
            constexpr BigSignedInteger& subtract(BigSignedInteger const&);
            template <size_t base> constexpr inline BigSignedInteger& subtract(BigSignedInteger<base> const& number) { return BigSignedInteger::subtract(BigSignedInteger::fromBase<base>(number)); }
            constexpr inline static BigSignedInteger subtract(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {}; evaluation.copy(numberA); evaluation.subtract(numberB); return evaluation; }
            constexpr inline static BigSignedInteger& subtract(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { numberA.subtract(numberB); return numberA; }
            constexpr BigSignedInteger& subtract(BigUnsignedInteger<radix> const&);
            template <size_t base> constexpr inline BigSignedInteger& subtract(BigUnsignedInteger<base> const& number) { return BigSignedInteger::subtract(BigUnsignedInteger<radix>::fromBase<base>(number)); }

            constexpr BigSignedInteger& unsign(void) noexcept;
            constexpr BigSignedInteger unsign(BigSignedInteger const& number) { BigSignedInteger evaluation {}; evaluation.copy(number); evaluation.unsign(); return evaluation; }
};

template <size_t radix>
class BigFloat : public BigSignedInteger<radix> { friend int main(void);
    /* ... */
    typedef long double primitive_t;
    typedef typename BigSignedInteger<radix>::Digit Digit;

    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    using BigSignedInteger<radix>::initiate;
    using BigSignedInteger<radix>::terminate;

    // [...]
    public:
        // Initialization > (Mantissa Length, State)
        size_t mantissaLength;
        enum State {INFINITE, SAFE, UNCOMPUTABLE} state : 2;

    // [...]
    public:
        // [Constructor]
        constexpr inline BigFloat(void) : BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} { this -> length = 1u; }
        constexpr inline BigFloat(primitive_t const number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} { BigFloat::move(BigFloat::fromNumber(number)); }
        constexpr inline BigFloat(State const state) : BigSignedInteger<radix>(), mantissaLength{0u}, state{state} {}
        constexpr inline BigFloat(BigFloat const& number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} { BigFloat::copy(number); }
        template <size_t base> constexpr inline BigFloat(BigFloat<base> const& number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} { BigFloat::move(BigFloat::fromBase<base>(number)); }
        constexpr inline BigFloat(BigFloat&& number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} { BigFloat::move(number); }
        template <size_t base> constexpr inline BigFloat(BigSignedInteger<base> const& number) : BigSignedInteger<radix>(number), mantissaLength{0u}, state{State::SAFE} {}
        constexpr inline BigFloat(BigSignedInteger<radix>&& number) : BigSignedInteger<radix>((BigSignedInteger<radix>&&) number), mantissaLength{0u}, state{State::SAFE} {}
        template <size_t base> constexpr inline BigFloat(BigUnsignedInteger<base> const& number) : BigUnsignedInteger<radix>(number), BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} {}
        constexpr inline BigFloat(BigUnsignedInteger<radix>&& number) : BigUnsignedInteger<radix>((BigUnsignedInteger<radix>&&) number), BigSignedInteger<radix>(), mantissaLength{0u}, state{State::SAFE} {}

        // Method > ...
            // [Conditional] Is (Base Factor, Big, Computable, Equal, Finite, Fraction, Greater, Infinite, Integer, Lesser, Non-Computable, Safe, Significant, Zero)
            constexpr inline bool isBaseFactor(void) const noexcept { return BigFloat::isBaseFactor(*this); }
            constexpr static bool isBaseFactor(BigFloat const&) noexcept;

            inline bool isBig(void) const noexcept { return BigFloat::isBig(*this); }
            static bool isBig(BigFloat const&) noexcept;

            constexpr inline bool isComputable(void) const noexcept { return BigFloat::isComputable(*this); }
            constexpr static bool isComputable(BigFloat const&) noexcept;

            constexpr inline bool isEqual(BigFloat const& number) const noexcept { return BigFloat::isEqual(*this, number); }
            template <size_t base> constexpr inline bool isEqual(BigFloat<base> const& number) const noexcept { return BigFloat::isEqual(*this, BigFloat::fromBase<base>(number)); }
            constexpr static bool isEqual(BigFloat const&, BigFloat const&) noexcept;

            constexpr inline bool isEven(void) const noexcept { return BigFloat::isEven(*this); }
            constexpr static bool isEven(BigFloat const&) noexcept;

            constexpr inline bool isFinite(void) const noexcept { return BigFloat::isFinite(*this); }
            constexpr static bool isFinite(BigFloat const&) noexcept;

            constexpr inline bool isFraction(void) const noexcept { return BigFloat::isFraction(*this); }
            constexpr static bool isFraction(BigFloat const&) noexcept;

            constexpr inline bool isGreater(BigFloat const& number) const noexcept { return BigFloat::isGreater(*this, number); }
            template <size_t base> constexpr inline bool isGreater(BigFloat<base> const& number) const noexcept { return BigFloat::isGreater(*this, BigFloat::fromBase<base>(number)); }
            constexpr static bool isGreater(BigFloat const&, BigFloat const&) noexcept;

            constexpr inline bool isInfinite(void) const noexcept { return BigFloat::isInfinite(*this); }
            constexpr static bool isInfinite(BigFloat const&) noexcept;

            constexpr inline bool isInteger(void) const noexcept { return BigFloat::isInteger(*this); }
            constexpr static bool isInteger(BigFloat const&) noexcept;

            constexpr inline bool isLesser(BigFloat const& number) const noexcept { return BigFloat::isLesser(*this, number); }
            template <size_t base> constexpr inline bool isLesser(BigFloat<base> const& number) const noexcept { return BigFloat::isLesser(*this, BigFloat::fromBase<base>(number)); }
            constexpr static bool isLesser(BigFloat const&, BigFloat const&) noexcept;

            constexpr inline bool isNonComputable(void) const noexcept { return BigFloat::isNonComputable(*this); }
            constexpr static bool isNonComputable(BigFloat const&) noexcept;

            constexpr inline bool isOdd(void) const noexcept { return BigFloat::isOdd(*this); }
            constexpr static bool isOdd(BigFloat const&) noexcept;

            constexpr inline bool isSafe(void) const noexcept { return BigFloat::isSafe(*this); }
            constexpr static bool isSafe(BigFloat const&) noexcept;

            constexpr inline bool isSignificant(void) const noexcept { return BigFloat::isSignificant(*this); }
            constexpr static bool isSignificant(BigFloat const&) noexcept;

            constexpr inline bool isZero(void) const noexcept { return BigFloat::isZero(*this); }
            constexpr static bool isZero(BigFloat const&) noexcept;

            // [Miscellaneous]
            template <size_t base> constexpr static BigFloat fromBase(BigFloat<base> const&);
            constexpr static BigFloat fromNumber(primitive_t const number);
            template <size_t base> constexpr static BigFloat<base> toBase(BigFloat const&);
            constexpr static primitive_t toNumber(BigFloat const&);
            constexpr char* toString(void) const;
            constexpr inline void zero(void) noexcept { this -> mantissaLength = 0u; this -> state = State::SAFE; BigSignedInteger<radix>::zero(); }

            // [Operational]
            constexpr BigFloat& add(BigFloat const&);
            template <size_t base> constexpr inline BigFloat& add(BigFloat<base> const& number) { return BigFloat::add(BigFloat::fromBase<base>(number)); }
            constexpr inline static BigFloat add(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {}; evaluation.copy(numberA); evaluation.add(numberB); return evaluation; }
            constexpr inline static BigFloat& add(BigFloat const& numberA, BigFloat&& numberB) { numberB.add(numberA); return numberB; }
            constexpr inline static BigFloat& add(BigFloat&& numberA, BigFloat const& numberB) { numberA.add(numberB); return numberA; }

            constexpr BigFloat& decrement(void);
            constexpr inline BigFloat decrement(BigFloat const& number) { BigFloat evaluation {}; evaluation.copy(number); evaluation.decrement(); return evaluation; }

            constexpr BigFloat& divide(BigFloat const&);
            template <size_t base> constexpr inline BigFloat& divide(BigFloat<base> const& number) { return BigFloat::divide(BigFloat::fromBase<base>(number)); }
            constexpr inline static BigFloat divide(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {}; evaluation.copy(numberA); evaluation.divide(numberB); return evaluation; }
            constexpr inline static BigFloat& divide(BigFloat&& numberA, BigFloat const& numberB) { numberA.divide(numberB); return numberA; }

            constexpr BigFloat& exponentiate(BigFloat const&);
            template <size_t base> constexpr inline BigFloat& exponentiate(BigFloat<base> const& number) { return BigFloat::exponentiate(BigFloat::fromBase<base>(number)); }
            constexpr inline static BigFloat exponentiate(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {}; evaluation.copy(numberA); evaluation.exponentiate(numberB); return evaluation; }
            constexpr inline static BigFloat& exponentiate(BigFloat&& numberA, BigFloat const& numberB) { numberA.exponentiate(numberB); return numberA; }

            constexpr BigFloat& increment(void);
            constexpr inline BigFloat increment(BigFloat const& number) { BigFloat evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }

            constexpr BigFloat& multiply(BigFloat const&);
            template <size_t base> constexpr inline BigFloat& multiply(BigFloat<base> const& number) { return BigFloat::multiply(BigFloat::fromBase<base>(number)); }
            constexpr inline static BigFloat multiply(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {}; evaluation.copy(numberA); evaluation.multiply(numberB); return evaluation; }
            constexpr inline static BigFloat& multiply(BigFloat const& numberA, BigFloat&& numberB) { numberB.multiply(numberA); return numberB; }
            constexpr inline static BigFloat& multiply(BigFloat&& numberA, BigFloat const& numberB) { numberA.multiply(numberB); return numberA; }

            constexpr BigFloat& shiftLeft(void);
            constexpr BigFloat& shiftLeft(typename BigUnsignedInteger<radix>::primitive_t const);
            constexpr inline static BigFloat shiftLeft(BigFloat const& number) { BigFloat evaluation {}; evaluation.copy(number); evaluation.shiftLeft(); return evaluation; }
            constexpr inline static BigFloat shiftLeft(BigFloat const& numberA, primitive_t const numberB) { BigFloat evaluation {}; evaluation.copy(numberA); evaluation.shiftLeft(numberB); return evaluation; }

            constexpr BigFloat& shiftRight(void);
            constexpr BigFloat& shiftRight(typename BigUnsignedInteger<radix>::primitive_t const);
            constexpr inline static BigFloat shiftRight(BigFloat const& number) { BigFloat evaluation {}; evaluation.copy(number); evaluation.shiftRight(); return evaluation; }
            constexpr inline static BigFloat shiftRight(BigFloat const& numberA, primitive_t const numberB) { BigFloat evaluation {}; evaluation.copy(numberA); evaluation.shiftRight(numberB); return evaluation; }

            constexpr BigFloat& subtract(BigFloat const&);
            template <size_t base> constexpr inline BigFloat& subtract(BigFloat<base> const& number) { return BigFloat::subtract(BigFloat::fromBase<base>(number)); }
            constexpr inline static BigFloat subtract(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {}; evaluation.copy(numberA); evaluation.subtract(numberB); return evaluation; }
            constexpr inline static BigFloat& subtract(BigFloat&& numberA, BigFloat const& numberB) { numberA.subtract(numberB); return numberA; }
};

/* Modification */
    /* Big Float */
        // Add --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::add(BigFloat const& number) {}

        // Decrement --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr BigFloat<radix>& BigFloat<radix>::decrement(void) {}

        // Divide --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::divide(BigFloat const& number) {}

        // Exponentiate --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::exponentiate(BigFloat const& number) {}

        // From Base --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline BigFloat<radix> BigFloat<radix>::fromBase(BigFloat<base> const& number) {}

        // From Number --- CHECKPOINT (Lapys)
        template <size_t radix>
        constexpr inline BigFloat<radix> BigFloat<radix>::fromNumber(primitive_t const number) {
            // Evaluation > Evaluation
            BigFloat evaluation {};

            // Logic
            if (number) {
if (::isinf(number)) return number < 0.00L ? "-Infinity" : "Infinity"; else if (::isnan(number)) return "NaN"; else if (number && false == ::isnormal(number)) return "Denormalized"; else { long double characteristics; char *iterator; long double mantissa; static char string[LDBL_DIG + 28] {0}; ::memset(string, '\0', sizeof(string));  if (number < 0.00L) { iterator = string + 1; mantissa = ::modf(-number, &characteristics); *string = '-'; *(string + 1) = '0'; } else { iterator = string; mantissa = ::modf(number, &characteristics); *string = '0'; } if (characteristics) { for (long double digit; characteristics && (string - iterator) <= LDBL_DIG; *iterator++ = *("0123456789" + (unsigned char) ::round(digit))) digit = ::modf((characteristics /= 10.00L), &characteristics) * 10.00L; ::strrev(string + (number < 0.00L)); } else ++iterator; if (mantissa) { *iterator++ = '.'; for (long double digit; mantissa >= LDBL_EPSILON; *iterator++ = *("0123456789" + (unsigned char) ::round(digit))) mantissa = ::modf((mantissa *= 10.00L), &digit); } return (char const*) string; }
            }

            // Return
            return evaluation;
        }

        // Increment --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::increment(void) {}

        // Is ...
        template <size_t radix> constexpr inline bool BigFloat<radix>::isBaseFactor(BigFloat const& number) noexcept { return BigFloat::isInteger() && BigUnsignedInteger<radix>::isBaseFactor(number); }
        template <size_t radix> inline bool BigFloat<radix>::isBig(BigFloat const& number) noexcept { static BigFloat const PRIMITIVE_MAX {LDBL_MAX}; return BigFloat::isGreater(number, PRIMITIVE_MAX); }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isComputable(BigFloat const& number) noexcept { return State::UNCOMPUTABLE != number.state; }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isEven(BigFloat const& number) noexcept { return BigFloat::isInteger(number) && BigSignedInteger<radix>::isEven((BigSignedInteger<radix> const&) number); }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isFinite(BigFloat const& number) noexcept { return State::INFINITE != number.state; }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isFraction(BigFloat const& number) noexcept { return number.mantissaLength; }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isInfinite(BigFloat const& number) noexcept { return State::INFINITE == number.state; }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isInteger(BigFloat const& number) noexcept { return 0u == number.mantissaLength; }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isNonComputable(BigFloat const& number) noexcept { return State::UNCOMPUTABLE == number.state; }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isOdd(BigFloat const& number) noexcept { return BigFloat::isInteger(number) && BigSignedInteger<radix>::isOdd((BigSignedInteger<radix> const&) number); }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isSafe(BigFloat const& number) noexcept { return BigFloat::isComputable(number) && BigFloat::isFinite(number); }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isSignificant(BigFloat const& number) noexcept { return (number.length || number.mantissaLength) && NULL != number.value; }
        template <size_t radix> constexpr inline bool BigFloat<radix>::isZero(BigFloat const& number) noexcept { return (0u == number.length && 0u == number.mantissaLength) && NULL == number.value; }

        // Is Equal
        template <size_t radix>
        constexpr inline bool BigFloat<radix>::isEqual(BigFloat const& numberA, BigFloat const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            // Logic
            if (BigFloat::isSafe(numberA) && BigFloat::isSafe(numberB)) {
                BigSignedInteger<radix> subnumberA, subnumberB;

                // Update > (Evaluation, Sub Number (A, B))
                ::memcpy(&subnumberA, &numberA, sizeof(BigSignedInteger<radix>)); subnumberA.length += numberA.mantissaLength;
                ::memcpy(&subnumberB, &numberB, sizeof(BigSignedInteger<radix>)); subnumberB.length += numberB.mantissaLength;


                return BigSignedInteger<radix>::isEqual(subnumberA, subnumberB);
            }

            // Return
            return evaluation;
        }

        // Is Greater --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline bool BigFloat<radix>::isGreater(BigFloat const& numberA, BigFloat const& numberB) noexcept {}

        // Is Lesser --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline bool BigFloat<radix>::isLesser(BigFloat const& numberA, BigFloat const& numberB) noexcept {}

        // Multiply --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::multiply(BigFloat const& number) {}

        // Shift Left --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::shiftLeft(void) {}

        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::shiftLeft(typename BigUnsignedInteger<radix>::primitive_t const number) {}

        // Shift Right --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::shiftRight(void) {}

        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::shiftRight(typename BigUnsignedInteger<radix>::primitive_t const number) {}

        // Subtract --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigFloat<radix>& BigFloat<radix>::subtract(BigFloat const& number) {}

        // To Base --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline BigFloat<base> BigFloat<radix>::toBase(BigFloat const& number) {}

        // To Number --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline primitive_t BigFloat<radix>::toNumber(BigFloat const& number) {}

        // To String --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline char* BigFloat<radix>::toString(void) const {}

    /* Big Signed Integer */
        // Add
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::add(BigFloat<radix> const& number) { return BigSignedInteger::add(BigSignedInteger(number)); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::add(BigUnsignedInteger<radix> const& number) { return BigSignedInteger::add(BigSignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::add(BigSignedInteger const& number) {
            // Logic
            if (BigSignedInteger::isSignificant(number)) {
                // Logic > ...
                if (BigSignedInteger::isNegative(number)) { BigSignedInteger evaluation; evaluation.length = number.length; evaluation.value = number.value; evaluation.unsign(); BigSignedInteger::subtract(evaluation); evaluation.length = 0u; evaluation.value = NULL; }
                else if (BigSignedInteger::isNegative()) { BigSignedInteger evaluation; evaluation.copy(number); this -> unsign(); evaluation.subtract(*this); this -> move((BigSignedInteger&&) evaluation); }
                else BigUnsignedInteger<radix>::add((BigUnsignedInteger<radix> const&) number);
            }

            // Logic > ...; Return
            if (BigSignedInteger::isNegative() && BigSignedInteger::isZero()) BigSignedInteger::unsign();
            return *this;
        }

        // Decrement
        template <size_t radix>
        constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::decrement(void) {
            // Logic > Update > ...
            if (BigSignedInteger::isZero()) { BigSignedInteger::allocate((this -> length = 1u)); BigSignedInteger::sign(); *(this -> value) = 1u; }
            else if (BigSignedInteger::isNegative()) { BigSignedInteger::unsign(); BigSignedInteger::increment(); BigSignedInteger::sign(); }
            else BigUnsignedInteger<radix>::decrement();

            // Return
            return *this;
        }

        // Divide
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::divide(BigFloat<radix> const& number) { return BigSignedInteger::divide(BigSignedInteger(number)); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::divide(BigUnsignedInteger<radix> const& number) { return BigSignedInteger::divide(BigSignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::divide(BigSignedInteger const& number) {
            // ...Update > ...
            BigUnsignedInteger<radix>::divide((BigUnsignedInteger<radix> const&) number);
            if (BigSignedInteger::isNegative(number)) BigSignedInteger::sign();

            // Logic > ...; Return
            if (BigSignedInteger::isNegative() && BigSignedInteger::isZero()) BigSignedInteger::unsign();
            return *this;
        }

        // Exponentiate
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::exponentiate(BigFloat<radix> const& number) { return BigSignedInteger::exponentiate(BigSignedInteger(number)); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::exponentiate(BigUnsignedInteger<radix> const& number) { return BigSignedInteger::exponentiate(BigSignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::exponentiate(BigSignedInteger const& number) {
            // Logic
            if (BigSignedInteger::isNegative(number))
                // Update > Target
                BigSignedInteger::zero();

            else {
                // ...Update > Target
                BigUnsignedInteger<radix>::exponentiate((BigUnsignedInteger<radix> const&) number);
                if (BigSignedInteger::isNegative() && BigSignedInteger::isEven(number) && false == (number.length == 1u && Digit::isEqual(*number.value, 1u))) BigSignedInteger::unsign();
            }

            // Logic > ...; Return
            if (BigSignedInteger::isNegative() && BigSignedInteger::isZero()) BigSignedInteger::unsign();
            return *this;
        }

        // From Base
        template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<radix> BigSignedInteger<radix>::fromBase(BigSignedInteger<base> const& number) { return BigSignedInteger(BigUnsignedInteger<radix>::template fromBase<base>((BigUnsignedInteger<base> const&) number)); }

        // From Number
        template <size_t radix>
        constexpr inline BigSignedInteger<radix> BigSignedInteger<radix>::fromNumber(primitive_t const number) {
            // Evaluation > Evaluation
            BigSignedInteger evaluation {};

            // Update > Evaluation
            evaluation.BigUnsignedInteger<radix>::move(BigUnsignedInteger<radix>::fromNumber((typename BigUnsignedInteger<radix>::primitive_t) (number < 0L ? -number : number)));
            evaluation.signedness = number < 0L;

            // Return
            return evaluation;
        }

        // Increment
        template <size_t radix>
        constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::increment(void) {
            // Logic > Update > Target
            if (BigSignedInteger::isNegative()) { BigSignedInteger::unsign(); BigSignedInteger::decrement(); BigSignedInteger::sign(); }
            else BigUnsignedInteger<radix>::increment();

            // Return
            return *this;
        }

        // Is ...
        template <size_t radix> inline bool BigSignedInteger<radix>::isBig(BigSignedInteger const& number) noexcept { static BigSignedInteger const PRIMITIVE_MAX {LONG_MAX}; return BigSignedInteger::isGreater(number, PRIMITIVE_MAX); }
        template <size_t radix> constexpr inline bool BigSignedInteger<radix>::isEqual(BigSignedInteger const& numberA, BigSignedInteger const& numberB) noexcept { return numberA.signedness == numberB.signedness && BigUnsignedInteger<radix>::isEqual((BigUnsignedInteger<radix> const&) numberA, (BigUnsignedInteger<radix> const&) numberB); }
        template <size_t radix> constexpr inline bool BigSignedInteger<radix>::isGreater(BigSignedInteger const& numberA, BigSignedInteger const& numberB) noexcept { return numberA.signedness == numberB.signedness ? BigUnsignedInteger<radix>::isGreater((BigUnsignedInteger<radix> const&) numberA, (BigUnsignedInteger<radix> const&) numberB) : (numberA.signedness && false == numberB.signedness); }
        template <size_t radix> constexpr inline bool BigSignedInteger<radix>::isLesser(BigSignedInteger const& numberA, BigSignedInteger const& numberB) noexcept { return numberA.signedness == numberB.signedness ? BigUnsignedInteger<radix>::isLesser((BigUnsignedInteger<radix> const&) numberA, (BigUnsignedInteger<radix> const&) numberB) : (false == numberA.signedness && numberB.signedness); }
        template <size_t radix> constexpr inline bool BigSignedInteger<radix>::isNegative(BigSignedInteger const& number) noexcept { return number.signedness; }
        template <size_t radix> constexpr inline bool BigSignedInteger<radix>::isPositive(BigSignedInteger const& number) noexcept { return false == number.signedness; }

        // Multiply
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::multiply(BigFloat<radix> const& number) { return BigSignedInteger::multiply(BigSignedInteger(number)); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::multiply(BigUnsignedInteger<radix> const& number) { return BigSignedInteger::multiply(BigSignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::multiply(BigSignedInteger const& number) {
            // ...Update > ...
            BigUnsignedInteger<radix>::multiply((BigUnsignedInteger<radix> const&) number);
            if (BigSignedInteger::isNegative(number)) BigSignedInteger::sign();

            // Logic > ...; Return
            if (BigSignedInteger::isNegative() && BigSignedInteger::isZero()) BigSignedInteger::unsign();
            return *this;
        }

        // Subtract
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::subtract(BigFloat<radix> const& number) { return BigSignedInteger::subtract(BigSignedInteger(number)); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::subtract(BigUnsignedInteger<radix> const& number) { return BigSignedInteger::subtract(BigSignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::subtract(BigSignedInteger const& number) {
            // Logic > ...
            if (BigSignedInteger::isSignificant(number)) {
                // Logic > ...
                if (this == &number || BigSignedInteger::isEqual(number)) BigSignedInteger::zero();
                else if (BigSignedInteger::isNegative(number)) { BigSignedInteger evaluation; evaluation.copy(number); evaluation.unsign(); BigSignedInteger::add(evaluation); }
                else if (BigSignedInteger::isNegative()) { BigSignedInteger::unsign(); BigSignedInteger::add(number); BigSignedInteger::sign(); }
                else if (false == BigSignedInteger::isLesser(number)) BigUnsignedInteger<radix>::subtract((BigUnsignedInteger<radix> const&) number);
                else { BigSignedInteger evaluation; evaluation.copy(number); evaluation.subtract(*this); BigSignedInteger::move((BigSignedInteger&&) evaluation); BigSignedInteger::sign(); }
            }

            // Logic > ...; Return
            if (BigSignedInteger::isNegative() && BigSignedInteger::isZero()) BigSignedInteger::unsign();
            return *this;
        }

        // To Base
        template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<base> BigSignedInteger<radix>::toBase(BigSignedInteger const& number) { return BigSignedInteger<base>(BigUnsignedInteger<radix>::template toBase<base>((BigUnsignedInteger<radix> const&) number)); }

        // To Number
        template <size_t radix>
        constexpr inline typename BigSignedInteger<radix>::primitive_t BigSignedInteger<radix>::toNumber(BigSignedInteger const& number) {
            // Evaluation > Evaluation
            primitive_t evaluation {0L};

            // Logic > ...
            if (BigSignedInteger::isBig(number)) number.terminate("[Arithmetic Overflow Error]: Unable to convert arbitrary-precision number to fixed-width integer");
            else if (BigSignedInteger::isSignificant(number)) evaluation = (primitive_t) (BigUnsignedInteger<radix>::toNumber((BigUnsignedInteger<radix> const&) number) * (BigSignedInteger::isNegative() ? -1L : 1L));

            // Return
            return evaluation;
        }

        // To String
        template <size_t radix>
        constexpr inline char* BigSignedInteger<radix>::toString(void) const {
            // Evaluation > String
            char *string = BigUnsignedInteger<radix>::toString();

            // Logic
            if (NULL != string && this -> signedness) {
                // Constant > (Delimited, Length)
                bool const delimited = '[' == *string;
                size_t const length = ::strlen(string);

                // Update > String
                string = (char*) ::realloc(string, (length + (delimited ? 3u : 1u) + 1u) * sizeof(char));

                // Logic
                if (NULL != string) {
                    // (Logic > )Update > String --- NOTE (Lapys) -> `strncpy` function is not overlap safe.
                    ::memmove(string + (delimited ? 3 : 1), string, (length + 1u) * sizeof(char));

                    if (delimited) { *string = '['; *(string + 1) = '-'; *(string + 2) = ']'; }
                    else *string = '-';
                }
            }

            // Return
            return string;
        }

        // (Un)Sign
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::sign(void) noexcept { this -> signedness = false == this -> signedness; return *this; }
        template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::unsign(void) noexcept { this -> signedness = false; return *this; }

    /* Big Unsigned Integer */
        // Add
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::add(BigFloat<radix> const& number) { return BigUnsignedInteger::add(BigUnsignedInteger(number)); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::add(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::add(BigUnsignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::add(BigUnsignedInteger const& number) {
            // Logic > ... --- REDACT (Lapys)
            if (BigUnsignedInteger::isZero()) BigUnsignedInteger::copy(number);
            else if (number.length == 1u && Digit::isEqual(*number.value, 1u)) BigUnsignedInteger::increment();
            else if (this -> length == 1u && Digit::isEqual(*(this -> value), 1u)) { BigUnsignedInteger::copy(number); BigUnsignedInteger::increment(); }
            else if (this == &number) { BigUnsignedInteger evaluation; evaluation.copy(number); return BigUnsignedInteger::add(evaluation); }
            else if (BigUnsignedInteger::isSignificant(number)) {
                // Initialization > (Carry, Evaluation)
                bool carry = false;
                Digit evaluation[2] {0u, 0u};

                // Logic
                if (this -> length < number.length) {
                    // ...; Modification > Target > (Length, Value)
                    BigUnsignedInteger::allocate(number.length);

                    ::memcpy(this -> value + (number.length - this -> length), this -> value, this -> length * sizeof(Digit));
                    ::memset(this -> value, 0u, (number.length - this -> length) * sizeof(Digit));
                    this -> length = number.length;
                }

                // Loop
                for (Digit *digit = number.value + (number.length - 1u), *iterator = this -> value + this -> length; iterator-- != (this -> value); --digit) {
                    // Logic > Update > Evaluation
                    if ((digit < number.value) || Digit::isLowestRank(*digit)) { *evaluation = 0u; *(evaluation + 1) = *iterator; }
                    else if (Digit::isLowestRank(*iterator)) { *evaluation = 0u; *(evaluation + 1) = *digit; }
                    else if (Digit::isMeanRank(*digit) || Digit::isUpperRank(*digit)) *(evaluation + 1) = (*evaluation = false == (radix - *digit > *iterator)) ? *iterator - (radix - *digit) : *iterator + *digit;
                    else if (Digit::isMeanRank(*iterator) || Digit::isUpperRank(*iterator)) *(evaluation + 1) = (*evaluation = false == (radix - *iterator > *digit)) ? *digit - (radix - *iterator) : *digit + *iterator;
                    else { *evaluation = 0u; *(evaluation + 1) = *digit + *iterator; }

                    // Logic
                    if (carry) {
                        // Logic > Update > Evaluation
                        if (Digit::isHighestRank(*(evaluation + 1))) { *evaluation = 1u; *(evaluation + 1) = 0u; }
                        else ++*(evaluation + 1);
                    }

                    // Update > (Carry, Iterator)
                    carry = false == Digit::isLowestRank(*evaluation);
                    *iterator = *(evaluation + 1);
                }

                // Logic
                if (carry) {
                    // ...; Modification > Target > Value
                    BigUnsignedInteger::allocate(this -> length + 1u);

                    ::memmove(this -> value + 1, this -> value, (this -> length)++ * sizeof(Digit));
                    *(this -> value) = 1u;
                }
            }

            // Return
            return *this;
        }

        // Decrement
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::decrement(void) {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // Logic
                if (this -> length == 1u && Digit::isEqual(*(this -> value), 1u))
                    // ...
                    BigUnsignedInteger::zero();

                else {
                    // Loop
                    for (Digit *iterator = this -> value + (this -> length); iterator-- != this -> value; ) {
                        // Logic > Update > Iterator
                        if (Digit::isLowestRank(*iterator)) *iterator = radix - 1u;
                        else { --*iterator; iterator = this -> value; }
                    }

                    // Logic > Modification > Target > Value
                    if (Digit::isLowestRank(*(this -> value)))
                    ::memmove(this -> value, this -> value + 1, --(this -> length) * sizeof(Digit));
                }
            }

            // Return
            return *this;
        }

        // Divide
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::divide(BigFloat<radix> const& number) { return BigUnsignedInteger::divide(BigUnsignedInteger(number)); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::divide(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::divide(BigUnsignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::divide(BigUnsignedInteger const& number) {
            // Logic > ...
            if (BigUnsignedInteger::isZero(number)) { terminate("[Syntax Error]: Attempt to divide by zero", NULL); }
            else if (BigUnsignedInteger::isSignificant() && false == (number.length == 1u && Digit::isEqual(*(number.value), 1u))) {
                // Logic > ...
                if (BigUnsignedInteger::isBaseFactor(number)) BigUnsignedInteger::shiftRight(number.length - 1u);
                else if (BigUnsignedInteger::isLesser(number)) BigUnsignedInteger::zero();
                else if (BigUnsignedInteger::isEqual(number) && false == (this -> length == 1u && Digit::isEqual(*(this -> value), 1u))) { BigUnsignedInteger::allocate((this -> length = 1u)); *(this -> value) = 1u; }
                else if (this == &number) { BigUnsignedInteger evaluation; evaluation.copy(number); return BigUnsignedInteger::divide(evaluation); }
                else {
                    // Initialization > (Dividend, Factor, Quotient)
                    BigUnsignedInteger<radix> dividend, factor; // NOTE (Lapys) -> Dividend: Numerator for each sub-division; Factor: Denominator for each sub-division.
                    BigUnsignedInteger<radix> quotient;

                    // Update > (Dividend, Factor, Quotient)
                    dividend.allocate(this -> length); dividend.length = 1u; *dividend.value = *(this -> value);
                    factor.copy(number);
                    quotient.allocate(this -> length);

                    // Loop
                    for (size_t count = 1u, index = 0u; index < this -> length; ) {
                        // Loop
                        while (index < this -> length && BigUnsignedInteger::isGreater(factor, dividend)) {
                            // (Logic > )Modification > (Dividend, Quotient) > Value
                            if (quotient.length) *(quotient.value + quotient.length++) = 0u;

                            *(dividend.value + dividend.length++) = *(this -> value + ++index);
                            if (Digit::isLowestRank(*dividend.value)) dividend.length = 0u;
                        }

                        // Logic
                        if (index < this -> length) {
                            // Loop > Update > (Count, Factor); Update > Quotient
                            while (BigUnsignedInteger::isGreater(dividend, factor)) { ++count; factor.add(number); }
                            if (BigUnsignedInteger::isGreater(factor, dividend)) { --count; factor.subtract(number); }

                            *(quotient.value + quotient.length++) = count;
                        }

                        // Logic
                        if (++index < this -> length) {
                            // Update > (Count, Dividend, Factor)
                            count = 1u;

                            dividend.subtract(factor); if (BigUnsignedInteger::isZero(dividend)) dividend.allocate(this -> length - index);
                            *(dividend.value + dividend.length++) = *(this -> value + index); if (Digit::isLowestRank(*dividend.value)) dividend.length = 0u;

                            ::memcpy(factor.value, number.value, (factor.length = number.length) * sizeof(Digit));
                        }
                    }

                    // ...
                    BigUnsignedInteger::zero();
                    BigUnsignedInteger::move((BigUnsignedInteger<radix>&&) quotient);
                }
            }

            // Return
            return *this;
        }

        // Exponentiate --- CONSIDER (Lapys) -> Optimize algorithmically.
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::exponentiate(BigFloat<radix> const& number) { return BigUnsignedInteger::exponentiate(BigUnsignedInteger(number)); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::exponentiate(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::exponentiate(BigUnsignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::exponentiate(BigUnsignedInteger const& number) {
            // Logic > ...
            if (BigUnsignedInteger::isZero(number)) { BigUnsignedInteger::allocate((this -> length = 1u)); *(this -> value) = 1u; }
            else if (
                (false == (number.length == 1u && Digit::isEqual(*(number.value), 1u))) &&
                (false == (this -> length == 1u && Digit::isEqual(*(this -> value), 1u)) && BigUnsignedInteger::isSignificant())
            ) {
                // Initialization > Iterator; ...
                BigUnsignedInteger iterator;
                iterator.copy(number);

                // Logic
                if (BigUnsignedInteger::isBaseFactor()) {
                    // Initialization > Length
                    // : Loop > ...
                    size_t length;

                    for (length = 0u; BigUnsignedInteger::isSignificant(iterator); iterator.decrement())
                    if (++length * (number.length - 1u) > (SIZE_MAX / sizeof(Digit))) BigUnsignedInteger::allocate((SIZE_MAX / sizeof(Digit)) + 1u);

                    // ...
                    BigUnsignedInteger::shiftLeft(length * (number.length - 1u));
                }

                else {
                    // Initialization > Incrementor
                    // : Loop > ...
                    BigUnsignedInteger incrementor;

                    for (incrementor.copy(*this), iterator.decrement(); BigUnsignedInteger::isSignificant(iterator); iterator.decrement())
                    BigUnsignedInteger::multiply(incrementor);
                }
            }

            // Return
            return *this;
        }

        // From Base
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<radix> BigUnsignedInteger<radix>::fromBase(BigUnsignedInteger<base> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger evaluation {};

            // Logic
            if (BigUnsignedInteger<base>::isSignificant(number)) {
                // Initialization > (Incrementor, Iterator)
                BigUnsignedInteger<base> const incrementor {radix};
                BigUnsignedInteger<base> iterator {1uL};

                // Modification > Evaluation > (Length, Value)
                evaluation.allocate((evaluation.length = 1u));
                *evaluation.value = 1u;

                // Loop > ...
                for (primitive_t size = 1uL; size; ) {
                    if (BigUnsignedInteger<base>::isLesser(iterator, number)) {
                        iterator.multiply(incrementor);
                        if (ULONG_MAX == size) { evaluation.shiftLeft(size); size = 1uL; } else ++size;
                    } else { if (1uL ^ size) { evaluation.shiftLeft(size - 2uL); } size = 0uL; }
                }

                // Logic > ...
                if (BigUnsignedInteger<base>::isGreater(iterator, number)) {
                    // Constant > ... Incrementor
                    BigUnsignedInteger const radixIncrementor {radix};

                    iterator.divide(incrementor);

                    while (BigUnsignedInteger<base>::isLesser(iterator, number)) { evaluation.add(radixIncrementor); iterator.add(incrementor); }
                    if (BigUnsignedInteger<base>::isGreater(iterator, number)) {
                        evaluation.subtract(radixIncrementor); iterator.subtract(incrementor);
                        while (false == BigUnsignedInteger<base>::isEqual(iterator, number)) { evaluation.increment(); iterator.increment(); }
                    }
                }
            }

            // Return
            return evaluation;
        }

        // From Number
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix> BigUnsignedInteger<radix>::fromNumber(primitive_t const number) {
            // Evaluation > Evaluation
            BigUnsignedInteger evaluation {};

            // Logic
            if (number) {
                // Initialization > Length
                unsigned char length = 0u;

                // ...
                evaluation.allocate(20u);
                for (primitive_t iterator = number; iterator; iterator /= radix) *(evaluation.value + length++) = iterator % radix;
                for (--length; evaluation.value + length > evaluation.value + evaluation.length; (++evaluation.length, --length)) { *(evaluation.value + evaluation.length) ^= *(evaluation.value + length); *(evaluation.value + length) ^= *(evaluation.value + evaluation.length); *(evaluation.value + evaluation.length) ^= *(evaluation.value + length); }
                evaluation.allocate((evaluation.length += length + 1u));
            }

            // Return
            return evaluation;
        }

        // Increment
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::increment(void) {
            // Logic
            if (BigUnsignedInteger::isZero()) {
                // ...; Modification > Target > (Length, Value)
                BigUnsignedInteger::allocate(1u);
                this -> length = 1u; *(this -> value) = 1u;
            }

            else {
                // Loop
                for (Digit *iterator = this -> value + (this -> length); iterator-- != this -> value; ) {
                    // Logic > Update > Iterator
                    if (Digit::isHighestRank(*iterator)) *iterator = 0u;
                    else { ++*iterator; iterator = this -> value; }
                }

                // Logic
                if (Digit::isLowestRank(*(this -> value))) {
                    // Modification > Target > (Length, Value)
                    BigUnsignedInteger::allocate(++(this -> length));
                    ::memmove(this -> value + 1, this -> value, (this -> length - 1u) * sizeof(Digit));
                    *(this -> value) = 1u;
                }
            }

            // Return
            return *this;
        }

        // Is ...
        template <size_t radix> inline bool BigUnsignedInteger<radix>::isBig(BigUnsignedInteger const& number) noexcept { static BigUnsignedInteger const PRIMITIVE_MAX {ULONG_MAX}; return BigUnsignedInteger::isGreater(number, PRIMITIVE_MAX); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isComputable(BigUnsignedInteger const&) noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isEven(BigUnsignedInteger const& number) noexcept { return NULL != number.value && 0u == (*(number.value + (number.length - 1u)) & 1u); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isFinite(BigUnsignedInteger const&) noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isFraction(BigUnsignedInteger const&) noexcept { return false; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isInfinite(BigUnsignedInteger const&) noexcept { return false; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isInteger(BigUnsignedInteger const&) noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isNegative(BigUnsignedInteger const&) noexcept { return false; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isNonComputable(BigUnsignedInteger const&) noexcept { return false; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isOdd(BigUnsignedInteger const& number) noexcept { return NULL != number.value && (*(number.value + (number.length - 1u)) & 1u); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isPositive(BigUnsignedInteger const&) noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isSafe(BigUnsignedInteger const&) noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isSignificant(BigUnsignedInteger const& number) noexcept { return number.length && NULL != number.value; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isZero(BigUnsignedInteger const& number) noexcept { return 0u == number.length && NULL == number.value; }

        // Is Base Factor
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isBaseFactor(BigUnsignedInteger<radix> const& number) noexcept {
            // Initialization > Evaluation
            // : Loop > Update > Evaluation
            size_t evaluation = number.length > 1u && Digit::isEqual(*(number.value), 1u);
            while (evaluation && evaluation < number.length) evaluation = Digit::isLowestRank(*(number.value + evaluation)) ? evaluation + 1u : 0;

            // Return
            return (bool) evaluation;
        }

        // Is Equal
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isEqual(BigFloat<radix> const& number) const noexcept { return BigFloat<radix>::isEqual(BigFloat<radix>(*this), number); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isEqual(BigSignedInteger<radix> const& number) const noexcept { return BigSignedInteger<radix>::isEqual(BigSignedInteger<radix>(*this), number); }

        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isEqual(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            // Logic > ...
            if (&numberA == &numberB) evaluation = true;
            else if (BigUnsignedInteger::isSignificant(numberA) && BigUnsignedInteger::isSignificant(numberB)) {
                // (Loop > Logic > )Update > Evaluation
                evaluation = numberA.length == numberB.length;

                for (size_t iterator = 0u; evaluation && (iterator ^ numberA.length); ++iterator)
                if (false == Digit::isEqual(*(numberA.value + iterator), *(numberB.value + iterator)))
                evaluation = false;
            }
            else evaluation = BigUnsignedInteger::isZero(numberA) && BigUnsignedInteger::isZero(numberB);

            // Return
            return evaluation;
        }

        // Is Greater
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isGreater(BigFloat<radix> const& number) const noexcept { return BigFloat<radix>::isGreater(BigFloat<radix>(*this), number); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isGreater(BigSignedInteger<radix> const& number) const noexcept { return BigSignedInteger<radix>::isGreater(BigSignedInteger<radix>(*this), number); }

        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isGreater(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            // Logic > ...
            if (&numberA == &numberB || BigUnsignedInteger::isZero(numberA) || numberA.length < numberB.length) evaluation = false;
            else if (BigUnsignedInteger::isZero(numberB)) evaluation = BigUnsignedInteger::isSignificant(numberA);
            else if (numberA.length > numberB.length) evaluation = true;
            else {
                // Initialization > Pending
                bool pending = true;

                // Loop > Logic > Update > Evaluation
                for (size_t iterator = 0u; pending && (iterator ^ numberA.length); ++iterator)
                if (Digit::isGreater(*(numberA.value + iterator), *(numberB.value + iterator))) { evaluation = true; pending = false; }
                else if (false == Digit::isEqual(*(numberA.value + iterator), *(numberB.value + iterator)))  { pending = false; }
            }

            // Return
            return evaluation;
        }

        // Is Lesser
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isLesser(BigFloat<radix> const& number) const noexcept { return BigFloat<radix>::isLesser(BigFloat<radix>(*this), number); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isLesser(BigSignedInteger<radix> const& number) const noexcept { return BigSignedInteger<radix>::isLesser(BigSignedInteger<radix>(*this), number); }

        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isLesser(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            // Logic > ...
            if (&numberA == &numberB) evaluation = false;
            else if (BigUnsignedInteger::isZero(numberA)) evaluation = false == BigUnsignedInteger::isZero(numberB);
            else if (BigUnsignedInteger::isZero(numberB)) evaluation = BigUnsignedInteger::isSignificant(numberA);
            else if (numberA.length > numberB.length) evaluation = false;
            else if (numberA.length < numberB.length) evaluation = true;
            else {
                // Initialization > Pending
                bool pending = true;

                // Loop > Logic > Update > Evaluation
                for (size_t iterator = 0u; pending && (iterator ^ numberA.length); ++iterator)
                if (Digit::isLesser(*(numberA.value + iterator), *(numberB.value + iterator))) { evaluation = true; pending = false; }
                else if (false == Digit::isEqual(*(numberA.value + iterator), *(numberB.value + iterator)))  { pending = false; }
            }

            // Return
            return evaluation;
        }

        // Multiply
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::multiply(BigFloat<radix> const& number) { return BigUnsignedInteger::multiply(BigUnsignedInteger(number)); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::multiply(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::multiply(BigUnsignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::multiply(BigUnsignedInteger const& number) {
            // Logic > ... --- REDACT (Lapys)
            if (this -> length == 1u && Digit::isEqual(*(this -> value), 1u)) BigUnsignedInteger::copy(number);
            else if (BigUnsignedInteger::isZero(number)) BigUnsignedInteger::zero();
            else if (BigUnsignedInteger::isBaseFactor(number)) BigUnsignedInteger::shiftLeft(number.length - 1u);
            else if (BigUnsignedInteger::isBaseFactor()) { size_t const length = this -> length; BigUnsignedInteger::copy(number); BigUnsignedInteger::shiftLeft(length - 1u); }
            else if (BigUnsignedInteger::isSignificant() && false == (number.length == 1u && Digit::isEqual(*number.value, 1u))) {
                // Initialization > (Carry, Evaluation, Product, Sum) --- NOTE (Lapys) -> Product is needless for single-digit multiplication.
                Digit carry = 0u, evaluation[2] {0u, 0u};
                BigUnsignedInteger<radix> product, sum;

                // ...
                product.allocate((product.length = this -> length + number.length));

                // Loop > Logic
                for (size_t iterator = 0u, subiterator; iterator ^ number.length; ++iterator)
                if (false == Digit::isLowestRank(*(number.value + (number.length - iterator - 1u)))) { // NOTE (Lapys) -> Prevent redundant sub-multiplication by zero.
                    // ...; Modification > Product > Value
                    carry = 0u;
                    ::memset(product.value + (product.length - iterator), 0u, iterator * sizeof(Digit));

                    // Loop
                    for (subiterator = 0u; subiterator ^ (this -> length); ++subiterator) {
                        // Update > Evaluation; Loop > Logic > Update > Evaluation --- NOTE (Lapys) -> Iteration count dependent on radix size with the maximum time taken being `radix * radix`.
                        ::memset(evaluation, 0u, sizeof(evaluation));

                        for (Digit multiplicands[2] {*(this -> value + (this -> length - subiterator - 1u)), 0u}; false == Digit::isLowestRank(*multiplicands); --*multiplicands)
                        for (*(multiplicands + 1) = *(number.value + (number.length - iterator - 1u)); false == Digit::isLowestRank(*(multiplicands + 1)); --*(multiplicands + 1)) {
                            if (Digit::isHighestRank(*(evaluation + 1))) { ++*evaluation; *(evaluation + 1) = 0u; }
                            else ++*(evaluation + 1);
                        }

                        // Logic > Update > Evaluation
                        if (false == Digit::isLowestRank(carry)) {
                            if (Digit::isMeanRank(carry) || Digit::isUpperRank(carry)) { if (radix - carry > *(evaluation + 1)) *(evaluation + 1) += carry; else { ++*evaluation; *(evaluation + 1) -= radix - carry; } }
                            else if (Digit::isMeanRank(*(evaluation + 1)) || Digit::isUpperRank(*(evaluation + 1))) { if (radix - *(evaluation + 1) > carry) *(evaluation + 1) += carry; else { ++*evaluation; *(evaluation + 1) = carry - (radix - *(evaluation + 1)); } }
                            else *(evaluation + 1) += carry;
                        }

                        // Modification > Product > Value; ...
                        *(product.value + (product.length - (iterator + subiterator) - 1u)) = *(evaluation + 1);
                        carry = *evaluation;
                    }

                    // Logic
                    if (false == Digit::isLowestRank(carry)) {
                        // Modification > Product > Value; Update > Carry
                        *(product.value + (product.length - (iterator + this -> length) - 1u)) = carry;
                        carry = true;
                    }

                    // Modification > Product > (Length, Value); Update > (Sum, ...)
                    *evaluation = (product.value + (product.length - (this -> length + carry + iterator))) - product.value;

                    product.value += product.length - (this -> length + carry + iterator); product.length -= *evaluation;
                    sum.add(product);
                    product.length += *evaluation; product.value -= product.length - (this -> length + carry + iterator);
                }

                // ...
                BigUnsignedInteger::zero();
                BigUnsignedInteger::move((BigUnsignedInteger<radix>&&) sum);
            }

            // Return
            return *this;
        }

        // Shift Left
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftLeft(void) {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // ...; Modification > Target > Value
                BigUnsignedInteger::allocate(this -> length + 1u);
                *(this -> value + (this -> length)++) = 0u;
            }

            // Return
            return *this;
        }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftLeft(primitive_t const number) {
            // Logic
            if (this -> length + number > SIZE_MAX / sizeof(Digit))
                // Error
                terminate("[Syntax Error]: Unable to logically forward-shift arbitrary-precision integer by specified number of digits", NULL);

            else if (BigUnsignedInteger::isSignificant()) {
                // ...; Modification > Target > (Length, Value)
                BigUnsignedInteger::allocate(this -> length + number);

                ::memset(this -> value + this -> length, 0u, number * sizeof(Digit));
                this -> length += number;
            }

            // Return
            return *this;
        }

        // Shift Right
        template <size_t radix> // NOTE (Lapys) -> Memory is managed here for functional consistency.
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftRight(void) {
            // Logic > ...
            if (this -> length)
            BigUnsignedInteger::allocate(--(this -> length));

            // Return
            return *this;
        }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftRight(primitive_t const number) {
            // Logic > ...
            if (number < this -> length) BigUnsignedInteger::allocate(this -> length -= number);
            else BigUnsignedInteger::zero();

            // Return
            return *this;
        }

        // Subtract
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::subtract(BigFloat<radix> const& number) { return BigUnsignedInteger::subtract(BigUnsignedInteger(number)); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::subtract(BigSignedInteger<radix> const& number) { return BigUnsignedInteger::subtract(BigUnsignedInteger(number)); }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::subtract(BigUnsignedInteger const& number) {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // Logic > ...
                if (number.length == 1u && Digit::isEqual(*number.value, 1u)) BigUnsignedInteger::decrement();
                else if (BigUnsignedInteger::isSignificant(number)) {
                    // Logic > ...
                    if (BigUnsignedInteger::isLesser(number)) BigUnsignedInteger::zero();
                    else if (this == &number) { BigUnsignedInteger evaluation; evaluation.copy(number); return BigUnsignedInteger::subtract(evaluation); }
                    else if (BigUnsignedInteger::isBaseFactor(number)) {
                        // Modification > Target > Length
                        // : Logic > ... --- MINIFY (Lapys)
                        this -> length -= number.length;

                        if (this -> value == (this -> value + this -> length) && Digit::isEqual(*(this -> value + (this -> length)), 1u)) ::memmove(this -> value, this -> value + 1, (this -> length += number.length - 1u) * sizeof(Digit));
                        else { size_t const index = ++(this -> length); BigUnsignedInteger::decrement(); ::memmove(this -> value + (this -> length), this -> value + index, (number.length - 1u) * sizeof(Digit)); this -> length += number.length - 1u; }
                    }

                    else {
                        // Loop > Logic > ...
                        for (Digit *digit = number.value + (number.length), *iterator = this -> value + (this -> length - 1u); digit-- != number.value; --iterator)
                        if (Digit::isGreater(*digit, *iterator)) {
                            // Loop > Logic > ...; ...
                            for (Digit *subiterator = iterator; subiterator-- != this -> value; )
                            if (false == Digit::isLowestRank(*subiterator)) { --*subiterator; subiterator = this -> value; }
                            else *subiterator = radix - 1u;

                            *iterator += Digit(radix) - *digit;
                        } else *iterator -= *digit;

                        // Logic --- NOTE (Lapys) -> Remove leading zero, or correct zeroed value.
                        if (Digit::isLowestRank(*(this -> value))) {
                            // Initialization > Length
                            size_t length = 1u;

                            // Loop > Update > Length
                            // : Logic > ...
                            while ((length ^ this -> length) && Digit::isLowestRank(*(this -> value + length))) ++length;

                            if (length == this -> length) BigUnsignedInteger::zero();
                            else ::memmove(this -> value, this -> value + length, (this -> length -= length) * sizeof(Digit));
                        }
                    }
                }
            }

            // Return
            return *this;
        }

        // (Un)Sign
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::sign(void) const noexcept { return *this; }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::unsign(void) const noexcept { return *this; }

        // To Base
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<base> BigUnsignedInteger<radix>::toBase(BigUnsignedInteger<radix> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<base> evaluation {};

            // Logic
            if (BigUnsignedInteger::isSignificant(number)) {
                // Initialization > (Incrementor, Iterator)
                BigUnsignedInteger const incrementor {base};
                BigUnsignedInteger iterator {1uL};

                // Modification > Evaluation > (Length, Value)
                evaluation.allocate((evaluation.length = 1u));
                *evaluation.value = 1u;

                // Loop > ...
                for (primitive_t size = 1uL; size; ) {
                    if (BigUnsignedInteger::isLesser(iterator, number)) {
                        iterator.multiply(incrementor);
                        if (ULONG_MAX == size) { evaluation.shiftLeft(size); size = 1uL; } else ++size;
                    } else { if (1uL ^ size) { evaluation.shiftLeft(size - 2uL); size = 0uL; } }
                }

                // Logic > ...
                if (BigUnsignedInteger::isGreater(iterator, number)) {
                    BigUnsignedInteger<base> const baseIncrementor {base};

                    iterator.divide(incrementor);

                    while (BigUnsignedInteger::isLesser(iterator, number)) { evaluation.add(baseIncrementor); iterator.add(incrementor); }
                    if (BigUnsignedInteger::isGreater(iterator, number)) {
                        evaluation.subtract(baseIncrementor); iterator.subtract(incrementor);
                        while (false == BigUnsignedInteger::isEqual(iterator, number)) { evaluation.increment(); iterator.increment(); }
                    }
                }
            }

            // Return
            return evaluation;
        }

        // To Number
        template <size_t radix>
        constexpr inline typename BigUnsignedInteger<radix>::primitive_t BigUnsignedInteger<radix>::toNumber(BigUnsignedInteger& number) {
            // Evaluation > Evaluation
            primitive_t evaluation {0uL};

            // Logic > ...
            if (BigUnsignedInteger::isBig(number)) number.terminate("[Arithmetic Overflow Error]: Unable to convert arbitrary-precision number to fixed-width integer");
            else if (BigUnsignedInteger::isSignificant(number)) {
                // Initialization > Exponent
                // : Loop > Update > Evaluation
                BigUnsignedInteger<radix>::primitive_t exponent = 1uL;
                for (Digit *iterator = number.value + (number.length); iterator-- != number.value; exponent *= 10uL) evaluation += exponent * *iterator;
            }

            // Return
            return evaluation;
        }

        // To String
        template <size_t radix>
        constexpr inline char* BigUnsignedInteger<radix>::toString(void) const {
            // Evaluation > Evaluation
            char *evaluation = NULL;

            // Logic > ...
            if (BigUnsignedInteger::isZero()) {
                // (Logic > )Update > Evaluation
                evaluation = (char*) ::malloc(2u * sizeof(char));
                if (NULL != evaluation) { *evaluation = '0'; *(evaluation + 1) = '\0'; }
            }

            else {
                // Initialization > (Delimit, (Digit) Length)
                bool delimit = false;
                size_t digitLength = 0u;
                size_t length = 0u;

                // Update > Evaluation
                evaluation = (char*) ::malloc((this -> length + 1u) * sizeof(char));

                // Logic
                if (NULL != evaluation) {
                    // Loop
                    for (size_t iterator = 0u; iterator ^ this -> length; ++iterator) {
                        // Initialization > Digit
                        Digit digit = *(this -> value + iterator);

                        // Logic
                        if (delimit) {
                            // [Start] Update > Evaluation
                            *(evaluation + length++) = '[';

                            // Logic
                            if (digit) {
                                // Initialization > (Current Digit Length, Sub-Iterator)
                                size_t currentDigitLength = 0u;
                                size_t subiterator = length;

                                // Loop > Update > (Current Digit Length, Evaluation)
                                for (; digit; digit /= 10u) { ++currentDigitLength; *(evaluation + length++) = *("0123456789" + (digit % 10u)); }

                                // Logic
                                if (currentDigitLength > digitLength) {
                                    // Update > (Digit Length, Evaluation, Iterator, Length)
                                    digitLength = currentDigitLength;
                                    evaluation = (char*) ::realloc(evaluation, ((digitLength * length) + (this -> length * 2u) + 1u) * sizeof(char));
                                    iterator = NULL == evaluation ? this -> length - 1u : 0u;
                                    length = 0u;
                                }

                                else {
                                    // Loop > Update > Evaluation
                                    for (size_t sublength = length - 1u; subiterator < sublength; (++subiterator, --sublength)) {
                                        *(evaluation + subiterator) ^= *(evaluation + sublength);
                                        *(evaluation + sublength) ^= *(evaluation + subiterator);
                                        *(evaluation + subiterator) ^= *(evaluation + sublength);
                                    }
                                }
                            }

                            else
                                // Update > Evaluation
                                *(evaluation + length++) = '0';

                            // [End] Update > Evaluation
                            *(evaluation + length++) = ']';
                        }

                        else {
                            // Logic
                            if (35u < (size_t) digit) {
                                // Deletion > Evaluation; Loop > Update > Digit Length
                                ::free(evaluation);
                                while (digit) { digit /= 10u; ++digitLength; }

                                // Update > (Delimit, Evaluation, Iterator, Length)
                                delimit = true;
                                evaluation = (char*) ::malloc(((digitLength * length) + (this -> length * 2u) + 1u) * sizeof(char));
                                iterator = NULL == evaluation ? this -> length - 1u : -1u;
                                length = 0u;
                            }

                            else
                                // Update > Evaluation
                                *(evaluation + length++) = *("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" + digit);
                        }
                    }

                    // Logic > Update > Evaluation
                    if (NULL != evaluation) *(evaluation + length) = '\0';
                }
            }

            // Return
            return evaluation;
        }

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
