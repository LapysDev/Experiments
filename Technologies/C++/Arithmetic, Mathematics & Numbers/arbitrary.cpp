/* Import */
    // [C Standard Library]
    #include <float.h> // Floating-Point
    #include <limits.h> // Limits
    #include <math.h> // Mathematics
    #include <stdlib.h> // Standard Library
    #include <string.h> // String

    // [C++ Standard Library]
    #include <iostream> // Input-Output Stream --- NOTE (Lapys) -> For testing.

/* Global > ... */
constexpr size_t const BIG_DIG = (SIZE_MAX / sizeof(size_t)) - (sizeof(bool) * 1u) - (sizeof(int) * 1u) - (sizeof(size_t) * 2u) - (sizeof(void*) * 1u);
constexpr size_t const RADIX_MAX = SIZE_MAX - 1u;

/* Definition > ... */
template <size_t> class BigFloat;
template <size_t> class BigSignedInteger;
template <size_t> class BigUnsignedInteger;

/* Class > Digit --- REDACT (Lapys) -> Digits are stored as denary values. */
class Digit { typedef size_t digit_t;
    private: digit_t value;
    public:
        constexpr inline Digit(digit_t const value) : value{value} {}

        constexpr inline static bool isEqual(Digit const digitA, Digit const digitB) noexcept { return digitA.value == digitB.value; }
        constexpr inline static bool isGreater(Digit const digitA, Digit const digitB) noexcept { return digitA.value > digitB.value; }
        template <size_t radix> constexpr inline static bool isHighestRank(Digit const digit) noexcept { return digit.value == radix - 1u; }
        constexpr inline static bool isLesser(Digit const digitA, Digit const digitB) noexcept { return digitA.value < digitB.value; }
        template <size_t radix> constexpr inline static bool isLowerRank(Digit const digit) noexcept { return digit.value < (radix / 2u); }
        template <size_t> constexpr inline static bool isLowestRank(Digit const digit) noexcept { return 0u == digit.value; }
        template <size_t radix> constexpr inline static bool isMeanRank(Digit const digit) noexcept { return digit.value == radix / 2u || ((radix & 1u) && (digit.value == (radix / 2u) + 1u)); }
        template <size_t radix> constexpr inline static bool isUpperRank(Digit const digit) noexcept { return digit.value > (radix / 2u) + (radix & 1u); }

        template <size_t radix> inline Digit const* add(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; if (Digit::isLowestRank<radix>(digitA)) { *evaluation = 0u; *(evaluation + 1) = digitB; } else if (Digit::isLowestRank<radix>(digitB)) { *evaluation = 0u; *(evaluation + 1) = digitA; } else if (Digit::isMeanRank<radix>(digitA) && Digit::isMeanRank<radix>(digitB)) { *evaluation = 1u; *(evaluation + 1) = 0u; } else if (Digit::isUpperRank<radix>(digitA)) { if (radix - digitA > digitB) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitB - (radix - digitA); } } else if (Digit::isUpperRank<radix>(digitB)) { if (radix - digitB > digitA) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitA - (radix - digitB); } } else { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } return &*evaluation; }
        template <size_t radix> inline Digit const* multiply(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; ::memset(evaluation, 0u, sizeof(evaluation)); for (digit_t iterator = digitB.value; false == Digit::isLowestRank<radix>(iterator); --iterator) for (digit_t subiterator = digitA.value; false == Digit::isLowestRank<radix>(subiterator); --subiterator) { if (Digit::isHighestRank<radix>(*(evaluation + 1))) { ++*evaluation; *(evaluation + 1) = 0u; } else ++*(evaluation + 1); } return &*evaluation; }
        template <size_t radix> inline Digit const* subtract(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; if (digitA == digitB) { *evaluation = 0u; *(evaluation + 1) = 0u; } else if (digitA < digitB) { *evaluation = 1u; *(evaluation + 1) = digitB - digitA; } else { *evaluation = 0u; *(evaluation + 1) = digitA - digitB; } return &*evaluation; }

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
};

/* Class > Big ...
        --- NOTE ---
            #Lapys:
                - Add, Decrement, Divide, Exponentiate, Increment, Multiply, Shift [Left, Right], Sign, Subtract, Unsign
                - From Number, To [Base, Number, String], Zero
                - Is [Big, Computable, Denormalized, Equal, Finite, Fraction, Greater, Infinite, Integer, Lesser, Negative, Non-Computable, Normalized, Positive, Safe, Significant, Zero]
*/

template <size_t radix>
class BigUnsignedInteger { typedef unsigned long primitive_t;
    /* ... */
    friend Digit;
    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    // [...]
    private:
        // Definition > (Length, Value)
        size_t length;
        Digit *value;

    // [...]
    protected:
        // Function > (Allocate, Copy, Move)
        inline void allocate(size_t const length) { void *allocation; bool assertion; allocation = NULL == this -> value ? ::malloc(length * sizeof(Digit)) : ::realloc(this -> value, length * sizeof(Digit)); assertion = NULL != allocation && BIG_DIG > length; if (assertion) this -> value = (Digit*) allocation; else { BigUnsignedInteger::zero(); length > BIG_DIG ? ::puts("\rUnable to increase length of arbitrary-precision number, not enough memory available") : ::puts("\rUnable to allocate memory to arbitrary-precision number"); ::abort(); } }
        template <size_t base> inline void copy(BigUnsignedInteger<base> const& number) { if (&number != this) { if (BigUnsignedInteger::isZero(number)) BigUnsignedInteger::zero(); else { BigUnsignedInteger::allocate(number.length); ::memcpy(this -> value, number.value, (this -> length = number.length) * sizeof(Digit)); } } }
        template <size_t base> constexpr inline void move(BigUnsignedInteger<base>&& number) noexcept { this -> length = number.length; this -> value = number.value; number.value = NULL; }

        // Phase > Initiate
        constexpr inline void initiate(void) const { if (radix > RADIX_MAX) { ::puts("\rThe radix specified is greater than `RADIX_MAX`"); ::abort(); } }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigUnsignedInteger(void) : length{0u}, value{NULL} { BigUnsignedInteger::initiate(); }
        constexpr inline BigUnsignedInteger(primitive_t const number) { BigUnsignedInteger::initiate(); BigUnsignedInteger::move(BigUnsignedInteger::fromNumber(number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigFloat<base> const& number) { BigUnsignedInteger::initiate(); BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigFloat<base>&& number) { BigUnsignedInteger::initiate(); BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigSignedInteger<base> const& number) { BigUnsignedInteger::initiate(); BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigSignedInteger<base>&& number) { BigUnsignedInteger::initiate(); BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigUnsignedInteger<base> const& number) { BigUnsignedInteger::initiate(); BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>(number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigUnsignedInteger<base>&& number) { BigUnsignedInteger::initiate(); BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>(number));}

        // [Destructor]
        inline ~BigUnsignedInteger(void) { BigUnsignedInteger::zero(); }

        // Declaration > ...
            // [Conditional]
            constexpr inline bool isBaseFactor(void) const noexcept { return BigUnsignedInteger::isBaseFactor(*this); }
            static constexpr bool isBaseFactor(BigUnsignedInteger const&) noexcept;

            inline bool isBig(void) const noexcept { return BigUnsignedInteger::isBig(*this); }
            static bool isBig(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isComputable(void) const noexcept { return BigUnsignedInteger::isComputable(*this); }
            constexpr inline static bool isComputable(BigUnsignedInteger const&) noexcept { return true; }

            constexpr inline bool isDenormalized(void) const noexcept { return BigUnsignedInteger::isDenormalized(*this); }
            constexpr inline static bool isDenormalized(BigUnsignedInteger const&) noexcept { return false; }

            template <size_t base> inline bool isEqual(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, BigUnsignedInteger::toBase<radix>(number)); }
            static bool isEqual(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;

            constexpr inline bool isFinite(void) const noexcept { return BigUnsignedInteger::isFinite(*this); }
            constexpr inline static bool isFinite(BigUnsignedInteger const&) noexcept { return true; }

            constexpr inline bool isFraction(void) const noexcept { return BigUnsignedInteger::isFraction(*this); }
            constexpr inline static bool isFraction(BigUnsignedInteger const&) noexcept { return false; }

            template <size_t base> constexpr inline bool isGreater(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isGreater(*this, BigUnsignedInteger::toBase<radix>(number)); }
            constexpr static bool isGreater(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;

            constexpr inline bool isInfinite(void) const noexcept { return BigUnsignedInteger::isInfinite(*this); }
            constexpr inline static bool isInfinite(BigUnsignedInteger const&) noexcept { return false; }

            constexpr inline bool isInteger(void) const noexcept { return BigUnsignedInteger::isInteger(*this); }
            constexpr inline static bool isInteger(BigUnsignedInteger const&) noexcept { return true; }

            template <size_t base> constexpr inline bool isLesser(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isLesser(*this, BigUnsignedInteger::toBase<radix>(number)); }
            constexpr static bool isLesser(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;

            constexpr inline bool isNegative(void) const noexcept { return BigUnsignedInteger::isNegative(*this); }
            constexpr inline static bool isNegative(BigUnsignedInteger const&) noexcept { return false; }

            constexpr inline bool isNonComputable(void) const noexcept { return BigUnsignedInteger::isNonComputable(*this); }
            constexpr inline static bool isNonComputable(BigUnsignedInteger const&) noexcept { return false; }

            constexpr inline bool isNormalized(void) const noexcept { return BigUnsignedInteger::isNormalized(*this); }
            constexpr inline static bool isNormalized(BigUnsignedInteger const&) noexcept { return true; }

            constexpr inline bool isPositive(void) const noexcept { return BigUnsignedInteger::isPositive(*this); }
            constexpr inline static bool isPositive(BigUnsignedInteger const&) noexcept { return true; }

            constexpr inline bool isSafe(void) const noexcept { return BigUnsignedInteger::isSafe(*this); }
            constexpr inline static bool isSafe(BigUnsignedInteger const&) noexcept { return true; }

            constexpr inline bool isSignificant(void) const noexcept { return BigUnsignedInteger::isSignificant(*this); }
            constexpr static bool isSignificant(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isZero(void) const noexcept { return BigUnsignedInteger::isZero(*this); }
            constexpr static bool isZero(BigUnsignedInteger const&) noexcept;

            // [Miscellaneous]
            constexpr static BigUnsignedInteger fromNumber(primitive_t const);
            template <size_t base> static BigUnsignedInteger<base> toBase(BigUnsignedInteger const&);
            constexpr static primitive_t toNumber(BigUnsignedInteger const&);
            char* toString(void) const noexcept;

            // [Operational]
            template <size_t base> BigUnsignedInteger& add(BigUnsignedInteger<base> const&);
            inline static BigUnsignedInteger add(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {numberA}; return evaluation.add(numberB); }
            inline static BigUnsignedInteger& add(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { return BigUnsignedInteger::add((BigUnsignedInteger&&) numberA, (BigUnsignedInteger&&) numberB); }
            inline static BigUnsignedInteger& add(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { return BigUnsignedInteger::add((BigUnsignedInteger&&) numberB, (BigUnsignedInteger&&) numberA); }
            inline static BigUnsignedInteger& add(BigUnsignedInteger&& numberA, BigUnsignedInteger&& numberB) { return numberA.add(numberB); }

            constexpr BigUnsignedInteger& decrement(void) noexcept;
            constexpr inline static BigUnsignedInteger& decrement(BigUnsignedInteger& number) noexcept { return number.decrement(); }

            template <size_t base> constexpr BigUnsignedInteger& divide(BigUnsignedInteger<base> const&);
            constexpr inline static BigUnsignedInteger divide(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {numberA}; return evaluation.divide(numberB); }
            constexpr inline static BigUnsignedInteger& divide(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { return BigUnsignedInteger::divide((BigUnsignedInteger&&) numberA, (BigUnsignedInteger&&) numberB); }
            constexpr inline static BigUnsignedInteger& divide(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { return BigUnsignedInteger::divide((BigUnsignedInteger const&) numberA, (BigUnsignedInteger const&) numberB); }
            constexpr inline static BigUnsignedInteger& divide(BigUnsignedInteger&& numberA, BigUnsignedInteger&& numberB) { return numberA.divide(numberB); }

            template <size_t base> constexpr BigUnsignedInteger& exponentiate(BigUnsignedInteger<base> const&);
            constexpr inline static BigUnsignedInteger exponentiate(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {numberA}; return evaluation.exponentiate(numberB); }
            constexpr inline static BigUnsignedInteger& exponentiate(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { return BigUnsignedInteger::exponentiate((BigUnsignedInteger&&) numberA, (BigUnsignedInteger&&) numberB); }
            constexpr inline static BigUnsignedInteger& exponentiate(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { return BigUnsignedInteger::exponentiate((BigUnsignedInteger const&) numberA, (BigUnsignedInteger const&) numberB); }
            constexpr inline static BigUnsignedInteger& exponentiate(BigUnsignedInteger&& numberA, BigUnsignedInteger&& numberB) { return numberA.exponentiate(numberB); }

            constexpr BigUnsignedInteger& increment(void);
            constexpr inline static BigUnsignedInteger& increment(BigUnsignedInteger& number) { return number.increment(); }

            template <size_t base> BigUnsignedInteger& multiply(BigUnsignedInteger<base> const&);
            inline static BigUnsignedInteger multiply(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {numberA}; return evaluation.multiply(numberB); }
            inline static BigUnsignedInteger& multiply(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { return BigUnsignedInteger::multiply((BigUnsignedInteger&&) numberA, (BigUnsignedInteger&&) numberB); }
            inline static BigUnsignedInteger& multiply(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { return BigUnsignedInteger::multiply((BigUnsignedInteger&&) numberB, (BigUnsignedInteger&&) numberA); }
            inline static BigUnsignedInteger& multiply(BigUnsignedInteger&& numberA, BigUnsignedInteger&& numberB) { return numberA.multiply(numberB); }

            constexpr BigUnsignedInteger& shiftLeft(void);
            constexpr BigUnsignedInteger& shiftLeft(primitive_t const);
            template <size_t base> constexpr inline BigUnsignedInteger& shiftLeft(BigUnsignedInteger<base> const& number) { if (BigUnsignedInteger<base>::isBig(number)) { ::puts("\rUnable to logically shift arbitrary-precision number leftward, not enough memory available"); ::abort(); } else BigUnsignedInteger::shiftLeft(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            constexpr inline static BigUnsignedInteger& shiftLeft(BigUnsignedInteger& number, primitive_t const exponent) { return number.shiftLeft(exponent); }
            template <size_t base> constexpr inline static BigUnsignedInteger& shiftLeft(BigUnsignedInteger& number, BigUnsignedInteger<base> const& exponent) { return number.shiftLeft(exponent); }

            constexpr BigUnsignedInteger& shiftRight(void) noexcept;
            constexpr BigUnsignedInteger& shiftRight(primitive_t const) noexcept;
            template <size_t base> constexpr inline BigUnsignedInteger& shiftRight(BigUnsignedInteger<base> const& number) noexcept { if (BigUnsignedInteger<base>::isBig(number)) BigUnsignedInteger::zero(); else BigUnsignedInteger::shiftRight(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            constexpr inline static BigUnsignedInteger& shiftRight(BigUnsignedInteger& number, primitive_t const exponent) noexcept { return number.shiftRight(exponent); }
            template <size_t base> constexpr inline static BigUnsignedInteger& shiftRight(BigUnsignedInteger& number, BigUnsignedInteger<base> const& exponent) noexcept { return number.shiftRight(exponent); }

            constexpr inline BigUnsignedInteger& sign(void) const noexcept;
            constexpr inline static BigUnsignedInteger& sign(BigUnsignedInteger& number) noexcept { return number.sign(); }

            template <size_t base> constexpr BigUnsignedInteger& subtract(BigUnsignedInteger<base> const&) noexcept;
            constexpr inline static BigUnsignedInteger subtract(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) noexcept { BigUnsignedInteger evaluation {numberA}; return evaluation.subtract(numberB); }
            constexpr inline static BigUnsignedInteger& subtract(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) noexcept { return BigUnsignedInteger::subtract((BigUnsignedInteger&&) numberA, (BigUnsignedInteger&&) numberB); }
            constexpr inline static BigUnsignedInteger& subtract(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) noexcept { return BigUnsignedInteger::subtract((BigUnsignedInteger const&) numberA, (BigUnsignedInteger const&) numberB); }
            constexpr inline static BigUnsignedInteger& subtract(BigUnsignedInteger&& numberA, BigUnsignedInteger&& numberB) noexcept { return numberA.subtract(numberB); }

            constexpr inline BigUnsignedInteger& unsign(void) const noexcept { return *this; }
            constexpr inline static BigUnsignedInteger& unsign(BigUnsignedInteger& number) noexcept { return number.unsign(); }

            constexpr inline void zero(void) noexcept { this -> length = 0u; if (NULL != this -> value) { ::free(this -> value); this -> value = NULL; } }

        // [Operator] > ...
        inline BigUnsignedInteger& operator =(primitive_t const number) { BigUnsignedInteger::move(BigUnsignedInteger::fromNumber(number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigFloat<base> const& number) { BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigFloat<base>&& number) { BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigSignedInteger<base> const& number) { BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigSignedInteger<base>&& number) { BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigUnsignedInteger<base> const& number) { BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigUnsignedInteger<base>&& number) { BigUnsignedInteger::move(BigUnsignedInteger::toBase<radix>(number)); return *this; }
};

template <size_t radix>
class BigSignedInteger : BigUnsignedInteger<radix> { typedef signed long primitive_t;
    /* ... */
    friend Digit;
    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    // [...]
    private:
        // Definition > Signedness
        bool signedness;

    // [...]
    protected:
        // Function > (Copy, Move)
        template <size_t base> inline void copy(BigSignedInteger<base> const& number) { if (&number != this) { this -> signedness = number.signedness; BigUnsignedInteger<radix>::copy(number); } }
        template <size_t base> constexpr inline void move(BigSignedInteger<base>&& number) noexcept { this -> signedness = number.signedness; BigUnsignedInteger<radix>::move(number); }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigSignedInteger(void) : BigUnsignedInteger<radix>(), signedness{false} {}
        constexpr inline BigSignedInteger(primitive_t const number) { BigSignedInteger::move(BigSignedInteger::fromNumber(number)); }
        template <size_t base> constexpr inline BigSignedInteger(BigFloat<base> const& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigSignedInteger(BigFloat<base>&& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigSignedInteger(BigSignedInteger<base> const& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>(number)); }
        template <size_t base> constexpr inline BigSignedInteger(BigSignedInteger<base>&& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>(number)); }
        template <size_t base> constexpr inline BigSignedInteger(BigUnsignedInteger<base> const& number) : signedness{false} { BigUnsignedInteger<radix>::copy(number); }
        template <size_t base> constexpr inline BigSignedInteger(BigUnsignedInteger<base>&& number) : signedness{false} { BigUnsignedInteger<radix>::move(number); }

        // Declaration > ...
            // [Conditional]
            constexpr inline bool isBaseFactor(void) const noexcept { return BigSignedInteger::isBaseFactor(*this); }
            constexpr inline static bool isBaseFactor(BigSignedInteger const& number) noexcept { return BigUnsignedInteger<radix>::isBaseFactor(number); }

            constexpr inline bool isBig(void) const noexcept { return BigSignedInteger::isBig(*this); }
            constexpr static bool isBig(BigSignedInteger const&) noexcept;

            template <size_t base> constexpr inline bool isEqual(BigSignedInteger<base> const& number) const noexcept { return BigSignedInteger::isEqual(*this, BigSignedInteger::toBase<radix>(number)); }
            constexpr static bool isEqual(BigSignedInteger const&, BigSignedInteger const&) noexcept;

            template <size_t base> constexpr inline bool isGreater(BigSignedInteger<base> const& number) const noexcept { return BigSignedInteger::isGreater(*this, BigSignedInteger::toBase<radix>(number)); }
            constexpr static bool isGreater(BigSignedInteger const&, BigSignedInteger const&) noexcept;

            template <size_t base> constexpr inline bool isLesser(BigSignedInteger<base> const& number) const noexcept { return BigSignedInteger::isLesser(*this, BigSignedInteger::toBase<radix>(number)); }
            constexpr static bool isLesser(BigSignedInteger const&, BigSignedInteger const&) noexcept;

            constexpr inline bool isNegative(void) const noexcept { return BigSignedInteger::isNegative(*this); }
            constexpr static bool isNegative(BigSignedInteger const&) noexcept;

            constexpr inline bool isPositive(void) const noexcept { return BigSignedInteger::isPositive(*this); }
            constexpr static bool isPositive(BigSignedInteger const&) noexcept;

            // [Miscellaneous]
            constexpr inline static BigSignedInteger fromNumber(primitive_t const);
            template <size_t base> inline static BigSignedInteger<base> toBase(BigSignedInteger const& number) { return BigUnsignedInteger<radix>::toBase<base>((BigUnsignedInteger<radix> const&) number); }
            constexpr static primitive_t toNumber(BigSignedInteger const&);
            constexpr inline char* toString(void) noexcept;

            // [Operational]
            template <size_t base> BigSignedInteger& add(BigSignedInteger<base> const&);
            inline static BigSignedInteger add(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {numberA}; return evaluation.add(numberB); }
            inline static BigSignedInteger& add(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { return BigSignedInteger::add((BigSignedInteger&&) numberA, (BigSignedInteger&&) numberB); }
            inline static BigSignedInteger& add(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { return BigSignedInteger::add((BigSignedInteger&&) numberB, (BigSignedInteger&&) numberA); }
            inline static BigSignedInteger& add(BigSignedInteger&& numberA, BigSignedInteger&& numberB) { return numberA.add(numberB); }

            constexpr BigSignedInteger& decrement(void) noexcept;
            constexpr inline static BigSignedInteger& decrement(BigSignedInteger& number) noexcept { return number.decrement(); }

            template <size_t base> constexpr BigSignedInteger& divide(BigSignedInteger<base> const&);
            constexpr inline static BigSignedInteger divide(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {numberA}; return evaluation.divide(numberB); }
            constexpr inline static BigSignedInteger& divide(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { return BigSignedInteger::divide((BigSignedInteger&&) numberA, (BigSignedInteger&&) numberB); }
            constexpr inline static BigSignedInteger& divide(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { return BigSignedInteger::divide((BigSignedInteger const&) numberA, (BigSignedInteger const&) numberB); }
            constexpr inline static BigSignedInteger& divide(BigSignedInteger&& numberA, BigSignedInteger&& numberB) { return numberA.divide(numberB); }

            template <size_t base> constexpr BigSignedInteger& exponentiate(BigSignedInteger<base> const&);
            constexpr inline static BigSignedInteger exponentiate(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {numberA}; return evaluation.exponentiate(numberB); }
            constexpr inline static BigSignedInteger& exponentiate(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { return BigSignedInteger::exponentiate((BigSignedInteger&&) numberA, (BigSignedInteger&&) numberB); }
            constexpr inline static BigSignedInteger& exponentiate(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { return BigSignedInteger::exponentiate((BigSignedInteger const&) numberA, (BigSignedInteger const&) numberB); }
            constexpr inline static BigSignedInteger& exponentiate(BigSignedInteger&& numberA, BigSignedInteger&& numberB) { return numberA.exponentiate(numberB); }

            constexpr BigSignedInteger& increment(void);
            constexpr inline static BigSignedInteger& increment(BigSignedInteger& number) { return number.increment(); }

            template <size_t base> BigSignedInteger& multiply(BigSignedInteger<base> const&);
            inline static BigSignedInteger multiply(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {numberA}; return evaluation.multiply(numberB); }
            inline static BigSignedInteger& multiply(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { return BigSignedInteger::multiply((BigSignedInteger&&) numberA, (BigSignedInteger&&) numberB); }
            inline static BigSignedInteger& multiply(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { return BigSignedInteger::multiply((BigSignedInteger&&) numberB, (BigSignedInteger&&) numberA); }
            inline static BigSignedInteger& multiply(BigSignedInteger&& numberA, BigSignedInteger&& numberB) { return numberA.multiply(numberB); }

            BigSignedInteger& shiftLeft(void);
            BigSignedInteger& shiftLeft(typename BigUnsignedInteger<radix>::primitive_t const);
            template <size_t base> inline BigSignedInteger& shiftLeft(BigUnsignedInteger<base> const& number) { if (BigUnsignedInteger<base>::isBig(number)) { ::puts("\rUnable to logically shift arbitrary-precision number leftward, not enough memory available"); ::abort(); } else BigUnsignedInteger<radix>::shiftLeft(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            inline static BigSignedInteger& shiftLeft(BigSignedInteger& number, primitive_t const exponent) { return number.shiftLeft(exponent); }
            template <size_t base> inline static BigSignedInteger& shiftLeft(BigSignedInteger& number, BigUnsignedInteger<base> const& exponent) { return number.shiftLeft(exponent); }

            BigSignedInteger& shiftRight(void) noexcept;
            BigSignedInteger& shiftRight(typename BigUnsignedInteger<radix>::primitive_t const) noexcept;
            template <size_t base> inline BigSignedInteger& shiftRight(BigUnsignedInteger<base> const& number) noexcept { if (BigUnsignedInteger<base>::isBig(number)) BigUnsignedInteger<radix>::zero(); else BigUnsignedInteger<radix>::shiftRight(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            inline static BigSignedInteger& shiftRight(BigSignedInteger& number, primitive_t const exponent) noexcept { return number.shiftRight(exponent); }
            template <size_t base> inline static BigSignedInteger& shiftRight(BigSignedInteger& number, BigUnsignedInteger<base> const& exponent) noexcept { return number.shiftRight(exponent); }

            constexpr BigSignedInteger& sign(void);
            constexpr inline static BigSignedInteger& sign(BigSignedInteger& number) { return number.sign(); }

            template <size_t base> constexpr BigSignedInteger& subtract(BigSignedInteger<base> const&) noexcept;
            constexpr inline static BigSignedInteger subtract(BigSignedInteger const& numberA, BigSignedInteger const& numberB) noexcept { BigSignedInteger evaluation {numberA}; return evaluation.subtract(numberB); }
            constexpr inline static BigSignedInteger& subtract(BigSignedInteger&& numberA, BigSignedInteger const& numberB) noexcept { return BigSignedInteger::subtract((BigSignedInteger&&) numberA, (BigSignedInteger&&) numberB); }
            constexpr inline static BigSignedInteger& subtract(BigSignedInteger const& numberA, BigSignedInteger&& numberB) noexcept { return BigSignedInteger::subtract((BigSignedInteger const&) numberA, (BigSignedInteger const&) numberB); }
            constexpr inline static BigSignedInteger& subtract(BigSignedInteger&& numberA, BigSignedInteger&& numberB) noexcept { return numberA.subtract(numberB); }

            constexpr BigSignedInteger& unsign(void);
            constexpr inline static BigSignedInteger& unsign(BigSignedInteger& number) { return number.unsign(); }

            constexpr inline void zero(void) noexcept { this -> signedness = false; BigSignedInteger<radix>::zero(); }

        // [Operator] > ...
        constexpr inline BigSignedInteger& operator =(primitive_t const number) { BigSignedInteger::move(BigSignedInteger::fromNumber(number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigFloat<base> const& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigFloat<base>&& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigSignedInteger<base> const& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigSignedInteger<base>&& number) { BigSignedInteger::move(BigSignedInteger::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigUnsignedInteger<base> const& number) { this -> signedness = false; BigUnsignedInteger<radix>::copy(number); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigUnsignedInteger<base>&& number) { this -> signedness = false; BigUnsignedInteger<radix>::move(number); return *this; }
};

template <size_t radix>
class BigFloat : BigSignedInteger<radix> { typedef long double primitive_t;
    /* ... */
    friend Digit;
    template <size_t> friend class BigFloat;
    template <size_t> friend class BigSignedInteger;
    template <size_t> friend class BigUnsignedInteger;

    // [...]
    private:
        // Definition > (Mantissa Length, State)
        size_t mantissaLength;
        enum BigFloatState {INDETERMINABLE, INFINITE, SAFE, UNCOMPUTABLE} state;

    // [...]
    protected:
        // Function > (Copy. Move)
        template <size_t base> inline void copy(BigFloat<base> const& number) { if (&number != this) { if (BigFloat::SAFE == (this -> state = number.state)) { this -> mantissaLength = number.mantissaLength; BigSignedInteger<radix>::copy(number); } else this -> signedness = number.signedness; } }
        template <size_t base> constexpr inline void move(BigFloat<base>&& number) noexcept { if (BigFloat::SAFE == (this -> state = number.state)) { this -> mantissaLength = number.mantissaLength; BigSignedInteger<radix>::move(number); } else this -> signedness = number.signedness; }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigFloat(void) : BigSignedInteger<radix>(), mantissaLength{0u}, state{SAFE} {}
        constexpr inline BigFloat(primitive_t const number) { BigFloat::copy(BigFloat::fromNumber(number)); }
        template <size_t base> inline BigFloat(BigFloat<base> const& number) { BigFloat::move(BigFloat::toBase<radix>(number)); }
        template <size_t base> constexpr inline BigFloat(BigFloat<base>&& number) { BigFloat::move(BigFloat::toBase<radix>(number)); }
        template <size_t base> inline BigFloat(BigSignedInteger<base> const& number) : mantissaLength{0u}, state{SAFE} { BigSignedInteger<radix>::copy(number); }
        template <size_t base> constexpr inline BigFloat(BigSignedInteger<base>&& number) : mantissaLength{0u}, state{SAFE} { BigSignedInteger<radix>::move(number); }
        template <size_t base> inline BigFloat(BigUnsignedInteger<base> const& number) : mantissaLength{0u}, state{SAFE} { BigUnsignedInteger<radix>::copy(number); }
        template <size_t base> constexpr inline BigFloat(BigUnsignedInteger<base>&& number) : mantissaLength{0u}, state{SAFE} { BigUnsignedInteger<radix>::move(number); }

        // Declaration > ...
            // [Conditional]
            constexpr inline bool isBaseFactor(void) const noexcept { return BigFloat::isBaseFactor(*this); }
            constexpr static bool isBaseFactor(BigFloat const&) noexcept;

            constexpr inline bool isBig(void) const noexcept { return BigFloat::isBig(*this); }
            constexpr static bool isBig(BigFloat const&) noexcept;

            constexpr inline bool isComputable(void) const noexcept { return BigFloat::isComputable(*this); }
            constexpr static bool isComputable(BigFloat const&) noexcept;

            constexpr inline bool isDenormalized(void) const noexcept { return BigFloat::isDenormalized(*this); }
            constexpr static bool isDenormalized(BigFloat const&) noexcept;

            template <size_t base> constexpr inline bool isEqual(BigFloat<base> const& number) const noexcept { return BigFloat::isEqual(*this, BigFloat::toBase<radix>(number)); }
            constexpr static bool isEqual(BigFloat const&, BigFloat const&) noexcept;

            constexpr inline bool isFinite(void) const noexcept { return BigFloat::isFinite(*this); }
            constexpr static bool isFinite(BigFloat const&) noexcept;

            constexpr inline bool isFraction(void) const noexcept { return BigFloat::isFraction(*this); }
            constexpr static bool isFraction(BigFloat const&) noexcept;

            template <size_t base> constexpr inline bool isGreater(BigFloat<base> const& number) const noexcept { return BigFloat::isGreater(*this, BigFloat::toBase<radix>(number)); }
            constexpr static bool isGreater(BigFloat const&, BigFloat const&) noexcept;

            constexpr inline bool isInfinite(void) const noexcept { return BigFloat::isInfinite(*this); }
            constexpr static bool isInfinite(BigFloat const&) noexcept;

            constexpr inline bool isInteger(void) const noexcept { return BigFloat::isInteger(*this); }
            constexpr static bool isInteger(BigFloat const&) noexcept;

            template <size_t base> constexpr inline bool isLesser(BigFloat<base> const& number) const noexcept { return BigFloat::isLesser(*this, BigFloat::toBase<radix>(number)); }
            constexpr static bool isLesser(BigFloat const&, BigFloat const&) noexcept;

            constexpr inline bool isNonComputable(void) const noexcept { return BigFloat::isNonComputable(*this); }
            constexpr static bool isNonComputable(BigFloat const&) noexcept;

            constexpr inline bool isNormalized(void) const noexcept { return BigFloat::isNormalized(*this); }
            constexpr static bool isNormalized(BigFloat const&) noexcept;

            constexpr inline bool isSafe(void) const noexcept { return BigFloat::isSafe(*this); }
            constexpr static bool isSafe(BigFloat const&) noexcept;

            constexpr inline bool isSignificant(void) const noexcept { return BigFloat::isSignificant(*this); }
            constexpr static bool isSignificant(BigFloat const&) noexcept;

            constexpr inline bool isZero(void) const noexcept { return BigFloat::isZero(*this); }
            constexpr static bool isZero(BigFloat const&) noexcept;

            // [Miscellaneous]
            constexpr inline static BigFloat fromNumber(primitive_t const);
            template <size_t base> inline static BigFloat<base> toBase(BigFloat const&);
            constexpr static primitive_t toNumber(BigFloat const&);
            constexpr inline char* toString(void) noexcept;

            // [Operational]
            template <size_t base> BigFloat& add(BigFloat<base> const&);
            inline static BigFloat add(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {numberA}; return evaluation.add(numberB); }
            inline static BigFloat& add(BigFloat&& numberA, BigFloat const& numberB) { return BigFloat::add((BigFloat&&) numberA, (BigFloat&&) numberB); }
            inline static BigFloat& add(BigFloat const& numberA, BigFloat&& numberB) { return BigFloat::add((BigFloat&&) numberB, (BigFloat&&) numberA); }
            inline static BigFloat& add(BigFloat&& numberA, BigFloat&& numberB) { return numberA.add(numberB); }

            constexpr BigFloat& decrement(void) noexcept;
            constexpr inline static BigFloat& decrement(BigFloat& number) noexcept { return number.decrement(); }

            template <size_t base> constexpr BigFloat& divide(BigFloat<base> const&);
            constexpr inline static BigFloat divide(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {numberA}; return evaluation.divide(numberB); }
            constexpr inline static BigFloat& divide(BigFloat&& numberA, BigFloat const& numberB) { return BigFloat::divide((BigFloat&&) numberA, (BigFloat&&) numberB); }
            constexpr inline static BigFloat& divide(BigFloat const& numberA, BigFloat&& numberB) { return BigFloat::divide((BigFloat const&) numberA, (BigFloat const&) numberB); }
            constexpr inline static BigFloat& divide(BigFloat&& numberA, BigFloat&& numberB) { return numberA.divide(numberB); }

            template <size_t base> constexpr BigFloat& exponentiate(BigFloat<base> const&);
            constexpr inline static BigFloat exponentiate(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {numberA}; return evaluation.exponentiate(numberB); }
            constexpr inline static BigFloat& exponentiate(BigFloat&& numberA, BigFloat const& numberB) { return BigFloat::exponentiate((BigFloat&&) numberA, (BigFloat&&) numberB); }
            constexpr inline static BigFloat& exponentiate(BigFloat const& numberA, BigFloat&& numberB) { return BigFloat::exponentiate((BigFloat const&) numberA, (BigFloat const&) numberB); }
            constexpr inline static BigFloat& exponentiate(BigFloat&& numberA, BigFloat&& numberB) { return numberA.exponentiate(numberB); }

            constexpr BigFloat& increment(void) noexcept;
            constexpr inline static BigFloat& increment(BigFloat& number) noexcept { return number.increment(); }

            template <size_t base> BigFloat& multiply(BigFloat<base> const&);
            inline static BigFloat multiply(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {numberA}; return evaluation.multiply(numberB); }
            inline static BigFloat& multiply(BigFloat&& numberA, BigFloat const& numberB) { return BigFloat::multiply((BigFloat&&) numberA, (BigFloat&&) numberB); }
            inline static BigFloat& multiply(BigFloat const& numberA, BigFloat&& numberB) { return BigFloat::multiply((BigFloat&&) numberB, (BigFloat&&) numberA); }
            inline static BigFloat& multiply(BigFloat&& numberA, BigFloat&& numberB) { return numberA.multiply(numberB); }

            BigFloat& shiftLeft(void);
            BigFloat& shiftLeft(typename BigUnsignedInteger<radix>::primitive_t const);
            template <size_t base> inline BigFloat& shiftLeft(BigUnsignedInteger<base> const& number) { if (BigUnsignedInteger<base>::isBig(number)) { ::puts("\rUnable to logically shift arbitrary-precision number leftward, not enough memory available"); ::abort(); } else BigUnsignedInteger<radix>::shiftLeft(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            inline static BigFloat& shiftLeft(BigFloat& number, primitive_t const exponent) { return number.shiftLeft(exponent); }
            template <size_t base> inline static BigFloat& shiftLeft(BigFloat& number, BigUnsignedInteger<base> const& exponent) { return number.shiftLeft(exponent); }

            BigFloat& shiftRight(void) noexcept;
            BigFloat& shiftRight(typename BigUnsignedInteger<radix>::primitive_t const) noexcept;
            template <size_t base> inline BigFloat& shiftRight(BigUnsignedInteger<base> const& number) noexcept { if (BigUnsignedInteger<base>::isBig(number)) BigUnsignedInteger<radix>::zero(); else BigUnsignedInteger<radix>::shiftRight(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            inline static BigFloat& shiftRight(BigFloat& number, primitive_t const exponent) noexcept { return number.shiftRight(exponent); }
            template <size_t base> inline static BigFloat& shiftRight(BigFloat& number, BigUnsignedInteger<base> const& exponent) noexcept { return number.shiftRight(exponent); }

            constexpr BigFloat& sign(void);
            constexpr inline static BigFloat& sign(BigFloat& number) { return number.sign(); }

            template <size_t base> constexpr BigFloat& subtract(BigFloat<base> const&) noexcept;
            constexpr inline static BigFloat subtract(BigFloat const& numberA, BigFloat const& numberB) noexcept { BigFloat evaluation {numberA}; return evaluation.subtract(numberB); }
            constexpr inline static BigFloat& subtract(BigFloat&& numberA, BigFloat const& numberB) noexcept { return BigFloat::subtract((BigFloat&&) numberA, (BigFloat&&) numberB); }
            constexpr inline static BigFloat& subtract(BigFloat const& numberA, BigFloat&& numberB) noexcept { return BigFloat::subtract((BigFloat const&) numberA, (BigFloat const&) numberB); }
            constexpr inline static BigFloat& subtract(BigFloat&& numberA, BigFloat&& numberB) noexcept { return numberA.subtract(numberB); }

            constexpr BigFloat& unsign(void);
            constexpr inline static BigFloat& unsign(BigFloat& number) { return number.unsign(); }

            constexpr inline void zero(void) noexcept { this -> mantissaLength = 0u; this -> state = BigFloat::SAFE; BigSignedInteger<radix>::zero(); }

        // [Operator] > ...
        constexpr inline BigFloat& operator =(primitive_t const number) { BigFloat::move(BigFloat::fromNumber(number)); return *this; }
        template <size_t base> inline BigFloat& operator =(BigFloat<base> const& number) { BigFloat::move(BigFloat::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigFloat& operator =(BigFloat<base>&& number) { BigFloat::move(BigFloat::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigFloat& operator =(BigSignedInteger<base> const& number) { BigSignedInteger<radix>::copy(number); return *this; }
        template <size_t base> inline BigFloat& operator =(BigSignedInteger<base>&& number) { BigSignedInteger<radix>::move(number); return *this; }
        template <size_t base> inline BigFloat& operator =(BigUnsignedInteger<base> const& number) { BigUnsignedInteger<radix>::copy(number); return *this; }
        template <size_t base> inline BigFloat& operator =(BigUnsignedInteger<base>&& number) { BigUnsignedInteger<radix>::move(number); return *this; }
};

/* Modification */
    /* Big Float --- CHECKPOINT (Lapys) */
    // template <size_t radix> template <size_t base> inline BigFloat<radix>& BigFloat<radix>::add(BigFloat<base> const& number);
    // template <size_t radix> template <size_t base> constexpr inline BigFloat<radix>& BigFloat<radix>::divide(BigFloat<base> const& number);
    // template <size_t radix> template <size_t base> constexpr inline BigFloat<radix>& BigFloat<radix>::exponentiate(BigFloat<base> const& number);
    // template <size_t radix> constexpr inline BigFloat<radix> BigFloat<radix>::fromNumber(BigFloat<radix>::primitive_t const number);
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isBig(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isComputable(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isDenormalized(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isEqual(BigFloat<radix> const& numberA, BigFloat<radix> const& numberB) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isFinite(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isFraction(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isGreater(BigFloat<radix> const& numberA, BigFloat<radix> const& numberB) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isInfinite(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isInteger(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isLesser(BigFloat<radix> const& numberA, BigFloat<radix> const& numberB) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isNonComputable(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isNormalized(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isSafe(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isSignificant(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline bool BigFloat<radix>::isZero(BigFloat<radix> const& number) noexcept;
    // template <size_t radix> template <size_t base> inline BigFloat<radix>& BigFloat<radix>::multiply(BigFloat<base> const& number);
    // template <size_t radix> template <size_t base> constexpr inline BigFloat<radix>& BigFloat<radix>::subtract(BigFloat<base> const& number) noexcept;
    // template <size_t radix> template <size_t base> inline BigFloat<base> BigFloat<radix>::toBase(BigFloat<radix> const& number);
    // template <size_t radix> constexpr inline char* BigFloat<radix>::toString(void) noexcept;

    /* Big Signed Integer --- CHECKPOINT (Lapys) */
    // template <size_t radix> template <size_t base> inline BigSignedInteger<radix>& BigSignedInteger<radix>::add(BigSignedInteger<base> const& number);
    // template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::decrement(void) noexcept;
    // template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::divide(BigSignedInteger<base> const& number);
    // template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::exponentiate(BigSignedInteger<base> const& number);
    // template <size_t radix> constexpr inline static BigSignedInteger<radix> BigSignedInteger<radix>::fromNumber(primitive_t const number);
    // template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::increment(void);
    // template <size_t radix> constexpr inline static bool BigSignedInteger<radix>::isBig(BigSignedInteger<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline static bool BigSignedInteger<radix>::isEqual(BigSignedInteger<radix> const& numberA, BigSignedInteger<radix> const& numberB) noexcept;
    // template <size_t radix> constexpr inline static bool BigSignedInteger<radix>::isGreater(BigSignedInteger<radix> const& numberA, BigSignedInteger<radix> const& numberB) noexcept;
    // template <size_t radix> constexpr inline static bool BigSignedInteger<radix>::isLesser(BigSignedInteger<radix> const& numberA, BigSignedInteger<radix> const& numberB) noexcept;
    // template <size_t radix> constexpr inline static bool BigSignedInteger<radix>::isNegative(BigSignedInteger<radix> const& number) noexcept;
    // template <size_t radix> constexpr inline static bool BigSignedInteger<radix>::isPositive(BigSignedInteger<radix> const& number) noexcept;
    // template <size_t radix> template <size_t base> inline BigSignedInteger<radix>& BigSignedInteger<radix>::multiply(BigSignedInteger<base> const& number);
    // template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::sign(void);
    // template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::subtract(BigSignedInteger<base> const& number) noexcept;
    // template <size_t radix> constexpr inline char* BigSignedInteger<radix>::toString(void) noexcept;
    // template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::unsign(void);

    /* Big Unsigned Integer */
        // Add
        template <size_t radix> template <size_t base>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::add(BigUnsignedInteger<base> const& number) {
            // Logic > ... --- REDACT (Lapys)
            if (BigUnsignedInteger::isZero()) BigUnsignedInteger::copy(number);
            else if (number.length == 1u && Digit::isEqual(*number.value, 1u)) BigUnsignedInteger::increment();
            else if (this -> length == 1u && Digit::isEqual(*(this -> value), 1u)) { BigUnsignedInteger::copy(number); BigUnsignedInteger::increment(); }
            else if (base ^ radix) return BigUnsignedInteger::add(BigUnsignedInteger::toBase<radix>(number));
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
                    if ((digit < number.value) || Digit::isLowestRank<radix>(*digit)) { *evaluation = 0u; *(evaluation + 1) = *iterator; }
                    else if (Digit::isLowestRank<radix>(*iterator)) { *evaluation = 0u; *(evaluation + 1) = *digit; }
                    else if (Digit::isMeanRank<radix>(*digit) || Digit::isUpperRank<radix>(*digit)) *(evaluation + 1) = (*evaluation = false == (radix - *digit > *iterator)) ? *iterator - (radix - *digit) : *iterator + *digit;
                    else if (Digit::isMeanRank<radix>(*iterator) || Digit::isUpperRank<radix>(*iterator)) *(evaluation + 1) = (*evaluation = false == (radix - *iterator > *digit)) ? *digit - (radix - *iterator) : *digit + *iterator;
                    else { *evaluation = 0u; *(evaluation + 1) = *digit + *iterator; }

                    // Logic
                    if (carry) {
                        // Logic > Update > Evaluation
                        if (Digit::isHighestRank<radix>(*(evaluation + 1))) { *evaluation = 1u; *(evaluation + 1) = 0u; }
                        else ++*(evaluation + 1);
                    }

                    // Update > (Carry, Iterator)
                    carry = false == Digit::isLowestRank<radix>(*evaluation);
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

        // Decrement --- WARN (Lapys) -> Memory should not be managed here due to the reference call in the `BigUnsignedInteger<size_t>::subtract` method.
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::decrement(void) noexcept {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // Logic
                if (this -> length == 1u && 1u == *(this -> value))
                    // ...
                    BigUnsignedInteger::zero();

                else {
                    // Loop
                    for (Digit *iterator = this -> value + (this -> length); iterator-- != this -> value; ) {
                        // Logic > Update > Iterator
                        if (Digit::isLowestRank<radix>(*iterator)) *iterator = radix - 1u;
                        else { --*iterator; iterator = this -> value; }
                    }

                    // Logic > Modification > Target > Value
                    if (Digit::isLowestRank<radix>(*(this -> value)))
                    ::memmove(this -> value, this -> value + 1, --(this -> length) * sizeof(Digit));
                }
            }

            // Return
            return *this;
        }

        // Divide --- CHECKPOINT (Lapys)
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::divide(BigUnsignedInteger<base> const& number) {
            (void) number;

            // Return
            return *this;
        }

        // Exponentiate --- CHECKPOINT (Lapys)
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::exponentiate(BigUnsignedInteger<base> const& number) {
            (void) number;
            return *this;
        }

        // From Number
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix> BigUnsignedInteger<radix>::fromNumber(primitive_t const number) {
            // Evaluation > Evaluation
            BigUnsignedInteger evaluation;

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
                    if (Digit::isHighestRank<radix>(*iterator)) *iterator = 0u;
                    else { ++*iterator; iterator = this -> value; }
                }

                // Logic
                if (Digit::isLowestRank<radix>(*(this -> value))) {
                    // Modification > Target > (Length, Value)
                    BigUnsignedInteger::allocate(++(this -> length));
                    ::memmove(this -> value + 1, this -> value, (this -> length - 1u) * sizeof(Digit));
                    *(this -> value) = 1u;
                }
            }

            // Return
            return *this;
        }

        // Is Base Factor
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isBaseFactor(BigUnsignedInteger<radix> const& number) noexcept {
            // Initialization > Evaluation
            // : Loop > Update > Evaluation
            size_t evaluation = number.length > 1u && Digit::isEqual(*(number.value), 1u);
            while (evaluation && evaluation < number.length) evaluation = Digit::isLowestRank<radix>(*(number.value + evaluation)) ? evaluation + 1u : 0;

            // Return
            return (bool) evaluation;
        }

        // Is Big
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isBig(BigUnsignedInteger<radix> const& number) noexcept { constexpr static BigUnsignedInteger const maximum {ULONG_MAX}; return BigUnsignedInteger::isGreater(maximum); }

        // Is Equal
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isEqual(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation;

            // Logic
            if (BigUnsignedInteger::isSignificant(numberA) && BigUnsignedInteger::isSignificant(numberB)) {
                // (Loop > Logic > )Update > Evaluation
                evaluation = numberA.length == numberB.length;

                for (size_t iterator = 0u; evaluation && (iterator ^ numberA.length); ++iterator)
                if (false == Digit::isEqual(*(numberA.value + iterator), *(numberB.value + iterator)))
                evaluation = false;
            }

            else
                // Update > Evaluation
                evaluation = BigUnsignedInteger::isZero(numberA) && BigUnsignedInteger::isZero(numberB);

            // Return
            return evaluation;
        }

        // Is Greater
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isGreater(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            // Logic
            if (BigUnsignedInteger::isZero(numberA) || numberA.length < numberB.length) evaluation = false;
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
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isLesser(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            if (BigUnsignedInteger::isZero(numberA)) evaluation = false == BigUnsignedInteger::isZero(numberB);
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

        // Is Significant
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isSignificant(BigUnsignedInteger<radix> const& number) noexcept { return number.length || NULL != number.value; }

        // Is Zero
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isZero(BigUnsignedInteger<radix> const& number) noexcept { return number.length == 0u && NULL == number.value; }

        // Multiply
        template <size_t radix> template <size_t base>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::multiply(BigUnsignedInteger<base> const& number) {
            // Logic > ... --- REDACT (Lapys)
            if (this -> length == 1u && Digit::isEqual(*(this -> value), 1u)) BigUnsignedInteger::copy(number);
            else if (BigUnsignedInteger::isZero(number)) BigUnsignedInteger::zero();
            else if (base != radix) return BigUnsignedInteger::multiply(BigUnsignedInteger::toBase<radix>(number));
            else if (BigUnsignedInteger::isBaseFactor(number)) BigUnsignedInteger::shiftLeft(number.length - 1u);
            else if (BigUnsignedInteger::isBaseFactor()) { size_t const length = this -> length; BigUnsignedInteger::copy(number); BigUnsignedInteger::shiftLeft(length - 1u); }
            else if (BigUnsignedInteger::isSignificant() && false == (number.length == 1u && Digit::isEqual(*number.value, 1u))) {
                // Initialization > (Carry, Evaluation)
                Digit carry = 0u;
                Digit evaluation[2] {0u, 0u};

                // Logic
                if (number.length == 1u) {
                    // Loop
                    for (Digit digit = *number.value, *iterator = this -> value + (this -> length); iterator-- != this -> value; ) {
                        // Update > Evaluation; Loop > Logic > Update > Evaluation --- NOTE (Lapys) -> Iteration count dependent on radix size with the maximum time taken being `radix * radix`.
                        ::memset(evaluation, 0u, sizeof(evaluation));

                        for (Digit multiplicand = 0u; false == Digit::isLowestRank<radix>(*iterator); --*iterator)
                        for (multiplicand = digit; false == Digit::isLowestRank<radix>(multiplicand); --multiplicand) {
                            if (Digit::isHighestRank<radix>(*(evaluation + 1))) { ++*evaluation; *(evaluation + 1) = 0u; }
                            else ++*(evaluation + 1);
                        }

                        // (Logic > )Update > Iterator; Update > Carry
                        *iterator = *(evaluation + 1);
                        if (false == Digit::isLowestRank<radix>(carry)) {
                            if (Digit::isMeanRank<radix>(carry) || Digit::isUpperRank<radix>(carry)) radix - carry > *iterator ? *iterator += carry : (++*evaluation, *iterator -= radix - carry);
                            else if (Digit::isMeanRank<radix>(*iterator) || Digit::isUpperRank<radix>(*iterator)) radix - *iterator > carry ? *iterator += carry : (++*evaluation, *iterator = carry - (radix - *(evaluation + 1)));
                            else *iterator += carry;
                        }
                        carry = *evaluation;
                    }

                    // Logic
                    if (false == Digit::isLowestRank<radix>(carry)) {
                        // ...; Modification > Target > (Length, Value)
                        BigUnsignedInteger::allocate(this -> length);

                        ::memmove(this -> value + 1, this -> value, (this -> length)++ * sizeof(Digit));
                        *(this -> value) = carry;
                    }
                }

                else {
                    // Initialization > (Product, Sum)
                    BigUnsignedInteger<radix> product;
                    BigUnsignedInteger<radix> sum;

                    product.allocate((product.length = this -> length + number.length));

                    // Loop
                    for (size_t iterator = 0u, subiterator; iterator ^ number.length; ++iterator) {
                        // Modification > Product > Value
                        carry = 0u;
                        ::memset(product.value + (product.length - iterator), 0u, iterator * sizeof(Digit));

                        // Loop
                        for (subiterator = 0u; subiterator ^ (this -> length); ++subiterator) {
                            // Update > Evaluation; Loop > Logic > Update > Evaluation --- NOTE (Lapys) -> Iteration count dependent on radix size with the maximum time taken being `radix * radix`.
                            ::memset(evaluation, 0u, sizeof(evaluation));

                            for (Digit multiplicands[2] {*(this -> value + (this -> length - subiterator - 1u)), 0u}; false == Digit::isLowestRank<radix>(*multiplicands); --*multiplicands)
                            for (*(multiplicands + 1) = *(number.value + (number.length - iterator - 1u)); false == Digit::isLowestRank<radix>(*(multiplicands + 1)); --*(multiplicands + 1)) {
                                if (Digit::isHighestRank<radix>(*(evaluation + 1))) { ++*evaluation; *(evaluation + 1) = 0u; }
                                else ++*(evaluation + 1);
                            }

                            // Logic > Update > Evaluation
                            if (false == Digit::isLowestRank<radix>(carry)) {
                                if (Digit::isMeanRank<radix>(carry) || Digit::isUpperRank<radix>(carry)) { if (radix - carry > *(evaluation + 1)) *(evaluation + 1) += carry; else { *evaluation += carry; *(evaluation + 1) -= radix - carry; } }
                                else if (Digit::isMeanRank<radix>(*(evaluation + 1)) || Digit::isUpperRank<radix>(*(evaluation + 1))) { if (radix - *(evaluation + 1) > carry) *(evaluation + 1) += carry; else { *evaluation += carry; *(evaluation + 1) = carry - (radix - *(evaluation + 1)); } }
                                else *(evaluation + 1) += carry;
                            }

                            // Modification > Product > Value; ...
                            *(product.value + (product.length - (iterator + subiterator) - 1u)) = *(evaluation + 1);
                            carry = *evaluation;
                        }

                        // Logic
                        if (false == Digit::isLowestRank<radix>(carry)) {
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
                    sum.length = 0u; sum.value = NULL;
                }
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
                *(this -> value + ++(this -> length)) = 0u;
            }

            // Return
            return *this;
        }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftLeft(primitive_t const number) {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
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
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftRight(void) noexcept {
            // Logic > ...
            if (this -> length)
            BigUnsignedInteger::allocate(--(this -> length));

            // Return
            return *this;
        }

        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftRight(primitive_t const number) noexcept {
            // Logic > ...
            if (number < this -> length) BigUnsignedInteger::allocate(this -> length -= number);
            else BigUnsignedInteger::zero();

            // Return
            return *this;
        }

        // Subtract --- WARN (Lapys) -> Must not manage memory, otherwise the `noexcept` qualifier is mute.
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::subtract(BigUnsignedInteger<base> const& number) noexcept {
            // Logic --- REDACT (Lapys)
            if (BigUnsignedInteger::isSignificant()) {
                // Logic > ...
                if (number.length == 1u && Digit::isEqual(*number.value, 1u)) BigUnsignedInteger::decrement();
                else if (BigUnsignedInteger::isSignificant(number)) {
                    // Logic > ...
                    if (base ^ radix) return BigUnsignedInteger::subtract(BigUnsignedInteger::toBase<radix>(number));
                    else if (BigUnsignedInteger::isLesser(number)) BigUnsignedInteger::zero();
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
                            if (false == Digit::isLowestRank<radix>(*subiterator)) { --*subiterator; subiterator = this -> value; }
                            else *subiterator = radix - 1u;

                            *iterator += Digit(radix) - *digit;
                        } else *iterator -= *digit;

                        // Logic > ...
                        if (Digit::isLowestRank<radix>(*(this -> value)))
                        ::memmove(this -> value, this -> value + 1, --(this -> length) * sizeof(Digit));
                    }
                }
            }

            // Return
            return *this;
        }

        // To Base
        template <size_t radix> template <size_t base>
        inline BigUnsignedInteger<base> BigUnsignedInteger<radix>::toBase(BigUnsignedInteger<radix> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<base> evaluation {};

            // Logic
            if (base == radix)
                // Update > Evaluation
                evaluation.copy(number);

            else {
                // Logic
                if (BigUnsignedInteger::isSignificant(number)) {
                    // Initialization > (Iterator, ...)
                    BigUnsignedInteger<radix> const incrementor {base};
                    BigUnsignedInteger<radix> iterator {1uL};

                    // ... --- REDACT (Lapys)
                    for (size_t weight = 0u; ; ++weight) {
                        iterator.multiply(incrementor);

                        if (BigUnsignedInteger::isGreater(iterator, number)) {
                            evaluation.shiftLeft(weight);
                            break;
                        }
                    }

                    if (false == BigUnsignedInteger::isEqual(iterator, number)) {
                        iterator.divide(incrementor);

                        while (true) {
                            iterator.add(incrementor);

                            if (false == BigUnsignedInteger::isGreater(iterator, number)) evaluation.add(incrementor);
                            else break;
                        }

                        if (false == BigUnsignedInteger::isEqual(iterator, number)) {
                            iterator.subtract(incrementor);
                            while (false == BigUnsignedInteger::isEqual(iterator, number)) { evaluation.increment(); iterator.increment(); }
                        }
                    }
                }
            }

            // Return
            return evaluation;
        }

        // To Number
        template <size_t radix>
        constexpr inline typename BigUnsignedInteger<radix>::primitive_t BigUnsignedInteger<radix>::toNumber(BigUnsignedInteger<radix> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<radix>::primitive_t evaluation {0uL};

            // Logic > ...
            if (BigUnsignedInteger::isBig(number)) { ::puts("\rUnable to convert arbitrary-precision number to fixed-width integer"); ::abort(); }
            else if (BigUnsignedInteger::isSignificant(number)) {
                // Initialization > Exponent
                // : Loop > Update > Evaluation
                BigUnsignedInteger<radix>::primitive_t exponent = 1uL;
                for (Digit *iterator = number.value + (number.length); iterator-- != number.value; exponent *= 10uL) evaluation += exponent * *iterator;
            }

            // Return
            return evaluation;
        }

        // To String --- NOTE (Lapys) -> Denary is the delimiting base.
        template <size_t radix>
        inline char* BigUnsignedInteger<radix>::toString(void) const noexcept {
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
                                    // Update > (Evaluation, Iterator, Length)
                                    evaluation = (char*) ::realloc(evaluation, (((currentDigitLength - 1u) * 3u) + 60u + 1u) * sizeof(char));
                                    iterator = NULL == evaluation ? this -> length - 1u : 0u;
                                    length = 0u;
                                }

                                else {
                                    // Loop > Update > Evaluation
                                    for (size_t sublength = length - 1u; subiterator < sublength; (++subiterator, ++sublength)) {
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
                            if (36u < (size_t) digit) {
                                // Deletion > Evaluation; Loop > Update > Digit Length
                                ::free(evaluation);
                                while (digit) { digit /= 10u; ++digitLength; }

                                // Update > (Delimit, Evaluation, Iterator, Length)
                                delimit = true;
                                evaluation = (char*) ::malloc((((digitLength - 1u) * 3u) + 60u + 1u) * sizeof(char));
                                iterator = NULL == evaluation ? this -> length - 1u : 0u;
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
