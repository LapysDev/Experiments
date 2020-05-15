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
constexpr size_t const RADIX_MAX = SIZE_MAX;

/* Definition > ... */
template <size_t> class BigFloat;
template <size_t> class BigSignedInteger;
template <size_t> class BigUnsignedInteger;

/* Class > Digit --- NOTE (Lapys) -> Digits are stored as denary values. --- REDACT (Lapys) */
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

/* Class > Big ... */
template <size_t radix>
class BigUnsignedInteger { typedef unsigned long primitive_t;
    // [...]
    private:
        // Definition > (Length, Value)
        size_t length;
        Digit *value;

    // [...]
    protected:
        // Function > (Allocate, Copy)
        inline void allocate(size_t const length) { void *allocation; bool assertion; try { allocation = NULL == this -> value ? ::malloc(length * sizeof(Digit)) : ::realloc(this -> value, length * sizeof(Digit)); assertion = NULL != allocation && BIG_DIG > length; } catch (...) { assertion = false; } if (assertion) this -> value = (Digit*) allocation; else { BigUnsignedInteger::zero(); length > BIG_DIG ? ::puts("\rUnable to increase length of arbitrary-precision number, not enough memory available") : ::puts("\rUnable to allocate memory to arbitrary-precision number"); ::abort(); } }

        inline void copy(BigUnsignedInteger const& number) { if (&number != this) { BigUnsignedInteger::allocate(number.length); ::memcpy(this -> value, number.value, (this -> length = number.length) * sizeof(Digit)); } }
        constexpr inline void copy(BigUnsignedInteger&& number) noexcept { this -> length = number.length; this -> value = number.value; number.value = NULL; }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigUnsignedInteger(void) : length{0u}, value{NULL} {}
        constexpr inline BigUnsignedInteger(primitive_t const number) { BigUnsignedInteger::copy(BigUnsignedInteger::fromNumber(number)); }
        template <size_t base> inline BigUnsignedInteger(BigFloat<base> const& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base> const&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigFloat<base>&& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base>&&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> inline BigUnsignedInteger(BigSignedInteger<base> const& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base> const&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigSignedInteger<base>&& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base>&&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); }
        template <size_t base> inline BigUnsignedInteger(BigUnsignedInteger<base> const& number) { if (base == radix) BigUnsignedInteger::copy((BigUnsignedInteger const&) number); else BigUnsignedInteger::copy((BigUnsignedInteger const&) BigUnsignedInteger::toBase<radix>(number)); }
        template <size_t base> constexpr inline BigUnsignedInteger(BigUnsignedInteger<base>&& number) {if (base == radix) BigUnsignedInteger::copy((BigUnsignedInteger&&) number); else BigUnsignedInteger::copy((BigUnsignedInteger&&) BigUnsignedInteger::toBase<radix>(number));}

        // [Destructor]
        inline ~BigUnsignedInteger(void) { BigUnsignedInteger::zero(); }

        // Declaration > ...
            // [Conditional]
            constexpr inline bool isBig(void) const noexcept { return BigUnsignedInteger::isBig(*this); }
            constexpr static bool isBig(BigUnsignedInteger const&) noexcept;

            constexpr inline bool isComputable(void) const noexcept { return BigUnsignedInteger::isComputable(*this); }
            constexpr inline static bool isComputable(BigUnsignedInteger const&) noexcept { return true; }

            constexpr inline bool isDenormalized(void) const noexcept { return BigUnsignedInteger::isDenormalized(*this); }
            constexpr inline static bool isDenormalized(BigUnsignedInteger const&) noexcept { return false; }

            template <size_t base> constexpr inline bool isEqual(BigUnsignedInteger<base> const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, BigUnsignedInteger::toBase<radix>(number)); }
            constexpr static bool isEqual(BigUnsignedInteger const&, BigUnsignedInteger const&) noexcept;

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
            template <size_t base> constexpr static BigUnsignedInteger<base> toBase(BigUnsignedInteger const&);
            constexpr static primitive_t toNumber(BigUnsignedInteger const&);
            constexpr char* toString(void) noexcept;

            // [Operational]
            template <size_t base> constexpr BigUnsignedInteger& add(BigUnsignedInteger<base> const&);
            constexpr inline static BigUnsignedInteger add(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {numberA}; return evaluation.add(numberB); }
            constexpr inline static BigUnsignedInteger& add(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { return BigUnsignedInteger::add((BigUnsignedInteger&&) numberA, (BigUnsignedInteger&&) numberB); }
            constexpr inline static BigUnsignedInteger& add(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { return BigUnsignedInteger::add((BigUnsignedInteger&&) numberB, (BigUnsignedInteger&&) numberA); }
            constexpr inline static BigUnsignedInteger& add(BigUnsignedInteger&& numberA, BigUnsignedInteger&& numberB) { return numberA.add(numberB); }

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

            template <size_t base> constexpr BigUnsignedInteger& multiply(BigUnsignedInteger<base> const&);
            constexpr inline static BigUnsignedInteger multiply(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {numberA}; return evaluation.multiply(numberB); }
            constexpr inline static BigUnsignedInteger& multiply(BigUnsignedInteger&& numberA, BigUnsignedInteger const& numberB) { return BigUnsignedInteger::multiply((BigUnsignedInteger&&) numberA, (BigUnsignedInteger&&) numberB); }
            constexpr inline static BigUnsignedInteger& multiply(BigUnsignedInteger const& numberA, BigUnsignedInteger&& numberB) { return BigUnsignedInteger::multiply((BigUnsignedInteger&&) numberB, (BigUnsignedInteger&&) numberA); }
            constexpr inline static BigUnsignedInteger& multiply(BigUnsignedInteger&& numberA, BigUnsignedInteger&& numberB) { return numberA.multiply(numberB); }

            constexpr BigUnsignedInteger& shiftLeft(primitive_t const);
            template <size_t base> constexpr inline BigUnsignedInteger& shiftLeft(BigUnsignedInteger<base> const& number) { if (BigUnsignedInteger<base>::isBig(number)) { ::puts("\rUnable to logically shift arbitrary-precision number leftward, not enough memory available"); ::abort(); } else BigUnsignedInteger::shiftLeft(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            constexpr inline static BigUnsignedInteger& shiftLeft(BigUnsignedInteger& number, primitive_t const exponent) { return number.shiftLeft(exponent); }
            template <size_t base> constexpr inline static BigUnsignedInteger& shiftLeft(BigUnsignedInteger& number, BigUnsignedInteger<base> const& exponent) { return number.shiftLeft(exponent); }

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
        inline BigUnsignedInteger& operator =(primitive_t const number) { BigUnsignedInteger::copy(BigUnsignedInteger::fromNumber(number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigFloat<base> const& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base> const&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigFloat<base>&& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base>&&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigSignedInteger<base> const& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base> const&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigSignedInteger<base>&& number) { BigUnsignedInteger::copy((BigUnsignedInteger<base>&&) BigUnsignedInteger::toBase<radix>((BigUnsignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigUnsignedInteger<base> const& number) { BigUnsignedInteger::copy((BigUnsignedInteger const&) BigUnsignedInteger::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigUnsignedInteger& operator =(BigUnsignedInteger<base>&& number) { BigUnsignedInteger::copy((BigUnsignedInteger&&) BigUnsignedInteger::toBase<radix>(number)); return *this; }
};

template <size_t radix>
class BigSignedInteger : BigUnsignedInteger<radix> { typedef signed long primitive_t;
    // [...]
    private:
        // Definition > Signedness
        bool signedness;

    // [...]
    protected:
        // Function > Copy
        inline void copy(BigSignedInteger const& number) { if (&number != this) { this -> signedness = number.signedness; BigUnsignedInteger<radix>::copy((BigUnsignedInteger<radix> const&) number); } }
        constexpr inline void copy(BigSignedInteger&& number) noexcept { this -> signedness = number.signedness; BigUnsignedInteger<radix>::copy((BigUnsignedInteger<radix>&&) number); }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigSignedInteger(void) : BigUnsignedInteger<radix>(), signedness{false} {}
        constexpr inline BigSignedInteger(primitive_t const number) { BigSignedInteger::copy(BigSignedInteger::fromNumber(number)); }
        template <size_t base> inline BigSignedInteger(BigFloat<base> const& number) { BigSignedInteger::copy((BigSignedInteger<base> const&) BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); }
        template <size_t base> constexpr inline BigSignedInteger(BigFloat<base>&& number) { BigSignedInteger::copy((BigSignedInteger<base>&&) BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); }
        template <size_t base> inline BigSignedInteger(BigSignedInteger<base> const& number) { if (base == radix) BigSignedInteger::copy((BigSignedInteger const&) number); else BigSignedInteger::copy((BigSignedInteger const&) BigSignedInteger::toBase<radix>(number)); }
        template <size_t base> constexpr inline BigSignedInteger(BigSignedInteger<base>&& number) { if (base == radix) BigSignedInteger::copy((BigSignedInteger&&) number); else BigSignedInteger::copy((BigSignedInteger&&) BigSignedInteger::toBase<radix>(number)); }
        template <size_t base> inline BigSignedInteger(BigUnsignedInteger<base> const& number) : signedness{false} { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base> const&) number); }
        template <size_t base> constexpr inline BigSignedInteger(BigUnsignedInteger<base>&& number) : signedness{false} { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base>&&) number); }

        // Declaration > ...
            // [Conditional]
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
            constexpr static primitive_t toNumber(BigSignedInteger const&);
            constexpr inline char* toString(void) noexcept;

            // [Operational]
            template <size_t base> constexpr BigSignedInteger& add(BigSignedInteger<base> const&);
            constexpr inline static BigSignedInteger add(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {numberA}; return evaluation.add(numberB); }
            constexpr inline static BigSignedInteger& add(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { return BigSignedInteger::add((BigSignedInteger&&) numberA, (BigSignedInteger&&) numberB); }
            constexpr inline static BigSignedInteger& add(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { return BigSignedInteger::add((BigSignedInteger&&) numberB, (BigSignedInteger&&) numberA); }
            constexpr inline static BigSignedInteger& add(BigSignedInteger&& numberA, BigSignedInteger&& numberB) { return numberA.add(numberB); }

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

            template <size_t base> constexpr BigSignedInteger& multiply(BigSignedInteger<base> const&);
            constexpr inline static BigSignedInteger multiply(BigSignedInteger const& numberA, BigSignedInteger const& numberB) { BigSignedInteger evaluation {numberA}; return evaluation.multiply(numberB); }
            constexpr inline static BigSignedInteger& multiply(BigSignedInteger&& numberA, BigSignedInteger const& numberB) { return BigSignedInteger::multiply((BigSignedInteger&&) numberA, (BigSignedInteger&&) numberB); }
            constexpr inline static BigSignedInteger& multiply(BigSignedInteger const& numberA, BigSignedInteger&& numberB) { return BigSignedInteger::multiply((BigSignedInteger&&) numberB, (BigSignedInteger&&) numberA); }
            constexpr inline static BigSignedInteger& multiply(BigSignedInteger&& numberA, BigSignedInteger&& numberB) { return numberA.multiply(numberB); }

            template <size_t radix> constexpr inline static BigSignedInteger<radix>& BigSignedInteger<radix>::shiftLeft(BigSignedInteger<radix>& number, primitive_t const exponent) { return number.shiftLeft(exponent); }
            template <size_t radix> template <size_t base> constexpr inline static BigSignedInteger<radix>& BigSignedInteger<radix>::shiftLeft(BigSignedInteger<radix>& number, BigUnsignedInteger<base> const& exponent) { return number.shiftLeft(exponent); }

            template <size_t radix> constexpr inline static BigSignedInteger<radix>& BigSignedInteger<radix>::shiftRight(BigSignedInteger<radix>& number, primitive_t const exponent) noexcept { return number.shiftRight(exponent); }
            template <size_t radix> template <size_t base> constexpr inline static BigSignedInteger<radix>& BigSignedInteger<radix>::shiftRight(BigSignedInteger<radix>& number, BigUnsignedInteger<base> const& exponent) noexcept { return number.shiftRight(exponent); }

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
        constexpr inline BigSignedInteger& operator =(primitive_t const number) { BigSignedInteger::copy(BigSignedInteger::fromNumber(number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigFloat<base> const& number) { BigSignedInteger::copy((BigSignedInteger<base> const&) BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigFloat<base>&& number) { BigSignedInteger::copy((BigSignedInteger<base>&&) BigSignedInteger::toBase<radix>((BigSignedInteger<base>) number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigSignedInteger<base> const& number) { BigSignedInteger::copy((BigSignedInteger const&) BigSignedInteger::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigSignedInteger<base>&& number) { BigSignedInteger::copy((BigSignedInteger&&) BigSignedInteger::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigUnsignedInteger<base> const& number) { this -> signedness = false; BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base> const&) number); return *this; }
        template <size_t base> inline BigSignedInteger& operator =(BigUnsignedInteger<base>&& number) { this -> signedness = false; BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base>&&) number); return *this; }
};

template <size_t radix>
class BigFloat : BigSignedInteger<radix> { typedef long double primitive_t;
    // [...]
    private:
        // Definition > (Mantissa Length, State)
        size_t mantissaLength;
        enum BigFloatState {INDETERMINABLE, INFINITE, SAFE, UNCOMPUTABLE} state;

    // [...]
    protected:
        // Function > Copy
        inline void copy(BigFloat const& number) { if (&number != this) { if (BigFloat::SAFE == (this -> state = number.state)) { this -> mantissaLength = number.mantissaLength; BigSignedInteger<radix>::copy((BigSignedInteger<radix> const&) number); } else this -> signedness = number.signedness; } }
        constexpr inline void copy(BigFloat&& number) noexcept { if (BigFloat::SAFE == (this -> state = number.state)) { this -> mantissaLength = number.mantissaLength; BigSignedInteger<radix>::copy((BigSignedInteger<radix>&&) number); } else this -> signedness = number.signedness; }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigFloat(void) : BigSignedInteger<radix>(), mantissaLength{0u}, state{SAFE} {}
        constexpr inline BigFloat(primitive_t const number) { BigFloat::copy(BigFloat::fromNumber(number)); }
        template <size_t base> inline BigFloat(BigFloat<base> const& number) { if (base == radix) BigFloat::copy((BigFloat const&) number); else BigFloat::copy((BigFloat const&) BigFloat::toBase<radix>(number)); }
        template <size_t base> constexpr inline BigFloat(BigFloat<base>&& number) { if (base == radix) BigFloat::copy((BigFloat&&) number); else BigFloat::copy((BigFloat&&) BigFloat::toBase<radix>(number)); }
        template <size_t base> inline BigFloat(BigSignedInteger<base> const& number) : mantissaLength{0u}, state{SAFE} { BigSignedInteger<radix>::copy((BigSignedInteger<base> const&) number); }
        template <size_t base> constexpr inline BigFloat(BigSignedInteger<base>&& number) : mantissaLength{0u}, state{SAFE} { BigSignedInteger<radix>::copy((BigSignedInteger<base> const&) number); }
        template <size_t base> inline BigFloat(BigUnsignedInteger<base> const& number) : mantissaLength{0u}, state{SAFE} { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base> const&) number); }
        template <size_t base> constexpr inline BigFloat(BigUnsignedInteger<base>&& number) : mantissaLength{0u}, state{SAFE} { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base>&&) number); }

        // Declaration > ...
            // [Conditional]
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
            template <size_t base> constexpr inline static BigFloat<base> toBase(BigFloat const&);
            constexpr static primitive_t toNumber(BigFloat const&);
            constexpr inline char* toString(void) noexcept;

            // [Operational]
            template <size_t base> constexpr BigFloat& add(BigFloat<base> const&);
            constexpr inline static BigFloat add(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {numberA}; return evaluation.add(numberB); }
            constexpr inline static BigFloat& add(BigFloat&& numberA, BigFloat const& numberB) { return BigFloat::add((BigFloat&&) numberA, (BigFloat&&) numberB); }
            constexpr inline static BigFloat& add(BigFloat const& numberA, BigFloat&& numberB) { return BigFloat::add((BigFloat&&) numberB, (BigFloat&&) numberA); }
            constexpr inline static BigFloat& add(BigFloat&& numberA, BigFloat&& numberB) { return numberA.add(numberB); }

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

            template <size_t base> constexpr BigFloat& multiply(BigFloat<base> const&);
            constexpr inline static BigFloat multiply(BigFloat const& numberA, BigFloat const& numberB) { BigFloat evaluation {numberA}; return evaluation.multiply(numberB); }
            constexpr inline static BigFloat& multiply(BigFloat&& numberA, BigFloat const& numberB) { return BigFloat::multiply((BigFloat&&) numberA, (BigFloat&&) numberB); }
            constexpr inline static BigFloat& multiply(BigFloat const& numberA, BigFloat&& numberB) { return BigFloat::multiply((BigFloat&&) numberB, (BigFloat&&) numberA); }
            constexpr inline static BigFloat& multiply(BigFloat&& numberA, BigFloat&& numberB) { return numberA.multiply(numberB); }

            constexpr BigFloat& shiftLeft(BigUnsignedInteger<radix>::primitive_t const);
            template <size_t base> constexpr inline BigFloat& shiftLeft(BigUnsignedInteger<base> const& number) { if (BigUnsignedInteger<base>::isBig(number)) { ::puts("\rUnable to logically shift arbitrary-precision number leftward, not enough memory available"); ::abort(); } else BigUnsignedInteger::shiftLeft(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            constexpr inline static BigFloat& shiftLeft(BigUnsignedInteger& number, primitive_t const exponent) { return number.shiftLeft(exponent); }
            template <size_t base> constexpr inline static BigFloat& shiftLeft(BigUnsignedInteger& number, BigUnsignedInteger<base> const& exponent) { return number.shiftLeft(exponent); }

            constexpr BigFloat& shiftRight(BigUnsignedInteger<radix>::primitive_t const) noexcept;
            template <size_t base> constexpr inline BigFloat& shiftRight(BigUnsignedInteger<base> const& number) noexcept { if (BigUnsignedInteger<base>::isBig(number)) BigUnsignedInteger::zero(); else BigUnsignedInteger::shiftRight(BigUnsignedInteger<base>::toNumber(number)); return *this; }
            constexpr inline static BigFloat& shiftRight(BigUnsignedInteger& number, primitive_t const exponent) noexcept { return number.shiftRight(exponent); }
            template <size_t base> constexpr inline static BigFloat& shiftRight(BigUnsignedInteger& number, BigUnsignedInteger<base> const& exponent) noexcept { return number.shiftRight(exponent); }

            template <size_t base> constexpr BigFloat& subtract(BigFloat<base> const&) noexcept;
            constexpr inline static BigFloat subtract(BigFloat const& numberA, BigFloat const& numberB) noexcept { BigFloat evaluation {numberA}; return evaluation.subtract(numberB); }
            constexpr inline static BigFloat& subtract(BigFloat&& numberA, BigFloat const& numberB) noexcept { return BigFloat::subtract((BigFloat&&) numberA, (BigFloat&&) numberB); }
            constexpr inline static BigFloat& subtract(BigFloat const& numberA, BigFloat&& numberB) noexcept { return BigFloat::subtract((BigFloat const&) numberA, (BigFloat const&) numberB); }
            constexpr inline static BigFloat& subtract(BigFloat&& numberA, BigFloat&& numberB) noexcept { return numberA.subtract(numberB); }

            constexpr inline void zero(void) noexcept { this -> mantissaLength = 0u; this -> state = BigFloat::SAFE; BigSignedInteger<radix>::zero(); }

        // [Operator] > ...
        constexpr inline BigFloat& operator =(primitive_t const number) { BigFloat::copy(BigFloat::fromNumber(number)); return *this; }
        template <size_t base> inline BigFloat& operator =(BigFloat<base> const& number) { BigFloat::copy((BigFloat const&) BigFloat::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigFloat& operator =(BigFloat<base>&& number) { BigFloat::copy((BigFloat const&) BigFloat::toBase<radix>(number)); return *this; }
        template <size_t base> inline BigFloat& operator =(BigSignedInteger<base> const& number) { BigSignedInteger<radix>::copy((BigSignedInteger<base> const&) number); return *this; }
        template <size_t base> inline BigFloat& operator =(BigSignedInteger<base>&& number) { BigSignedInteger<radix>::copy((BigSignedInteger<base> const&) number); return *this; }
        template <size_t base> inline BigFloat& operator =(BigUnsignedInteger<base> const& number) { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base> const&) number); return *this; }
        template <size_t base> inline BigFloat& operator =(BigUnsignedInteger<base>&& number) { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<base>&&) number); return *this; }
};

/* Modification */
    /* Big Float --- CHECKPOINT (Lapys) */
    // template <size_t radix> template <size_t base> constexpr inline BigFloat<radix>& BigFloat<radix>::add(BigFloat<base> const& number);
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
    // template <size_t radix> template <size_t base> constexpr inline BigFloat<radix>& BigFloat<radix>::multiply(BigFloat<base> const& number);
    // template <size_t radix> template <size_t base> constexpr inline BigFloat<radix>& BigFloat<radix>::subtract(BigFloat<base> const& number) noexcept;
    // template <size_t radix> template <size_t base> constexpr inline BigFloat<base> BigFloat<radix>::toBase(BigFloat<radix> const& number);
    // template <size_t radix> constexpr inline char* BigFloat<radix>::toString(void) noexcept;

    /* Big Signed Integer --- CHECKPOINT (Lapys) */
    // template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::add(BigSignedInteger<base> const& number);
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
    // template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::multiply(BigSignedInteger<base> const& number);
    // template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::sign(void);
    // template <size_t radix> template <size_t base> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::subtract(BigSignedInteger<base> const& number) noexcept;
    // template <size_t radix> constexpr inline char* BigSignedInteger<radix>::toString(void) noexcept;
    // template <size_t radix> constexpr inline BigSignedInteger<radix>& BigSignedInteger<radix>::unsign(void);

    /* Big Unsigned Integer */
        // Add --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::add(BigUnsignedInteger<base> const& number);

        // Decrement
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
                    if (Digit::isLowestRank<radix>(*(this -> value))) ::memmove(this -> value, this -> value + 1, --(this -> length) * sizeof(Digit));
                }
            }

            // Return
            return *this;
        }

        // Divide --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::divide(BigUnsignedInteger<base> const& number);

        // Exponentiate --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::exponentiate(BigUnsignedInteger<base> const& number);

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

        // Is Big --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline bool BigUnsignedInteger<radix>::isBig(BigUnsignedInteger<radix> const& number) noexcept;

        // Is Equal --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline bool BigUnsignedInteger<radix>::isEqual(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept;

        // Is Greater --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline bool BigUnsignedInteger<radix>::isGreater(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept;

        // Is Lesser --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline bool BigUnsignedInteger<radix>::isLesser(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept;

        // Is Significant
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isSignificant(BigUnsignedInteger<radix> const& number) noexcept { return number.length || NULL != number.value; }

        // Is Zero
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isZero(BigUnsignedInteger<radix> const& number) noexcept { return number.length == 0u && NULL == number.value; }

        // Multiply --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::multiply(BigUnsignedInteger<base> const&);

        // Sign --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::sign(void) const noexcept;

        // Subtract --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::subtract(BigUnsignedInteger<base> const&) noexcept;

        // To Base --- CHECKPOINT (Lapys)
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<base> BigUnsignedInteger<radix>::toBase(BigUnsignedInteger<radix> const& number) {
            // Logic
            if (base == radix)
                // Return
                return number;

            else {
                // Evaluation > Evaluation
                BigUnsignedInteger<base> evaluation;

                // Logic
                if (base > radix) {

                }

                else {
                    // MULTIPLY
                    // ADD
                    // INCREMENT
                }

                // for (BigUnsignedInteger<radix> iterator {number}; BigUnsignedInteger::isSignificant(iterator); BigUnsignedInteger::decrement(iterator))
                // BigUnsignedInteger<base>::increment(evaluation);

                // Return
                return evaluation;
            }
        }

        // To Number --- CHECKPOINT (Lapys)
        // template <size_t radix>
        // constexpr inline BigUnsignedInteger<radix>::primitive_t BigUnsignedInteger<radix>::toNumber(BigUnsignedInteger<radix> const& number);

        // To String
        template <size_t radix>
        constexpr inline char* BigUnsignedInteger<radix>::toString(void) noexcept {
            // Evaluation > Evaluation
            char *evaluation;

            // Logic
            if (BigUnsignedInteger::isZero()) {
                // (Logic > )Update > Evaluation
                evaluation = (char*) ::malloc(2u * sizeof(char));
                if (NULL != evaluation) { *evaluation = '0'; *(evaluation + 1) = '\0'; }
            }

            else {
                // Update > Evaluation; Logic
                evaluation = (char*) ::malloc(this -> length * sizeof(char));
                if (NULL != evaluation) {
                    // Initialization > (Delimit, (Digit) Length)
                    bool delimit = false;
                    unsigned char digitLength = 0u;
                    size_t length = 0u;

                    // Loop
                    for (size_t iterator = 0u; iterator ^ (this -> length); ++iterator) {
                        // Initialization
                        Digit digit = *(this -> value + iterator);

                        // Logic
                        if (delimit) {
                            // Update > Evaluation
                            *(evaluation + length++) = '[';

                            // Logic
                            if (digit) {
                                // Initialization > Sub-Digit Length
                                unsigned char subDigitLength = 0u;

                                // Loop > Update > Sub-Digit Length
                                // : Logic
                                for (Digit subiterator = digit; subiterator; subiterator /= 10u) ++subDigitLength;
                                if (subDigitLength > digitLength) {
                                    // Initialization > Allocation
                                    void *allocation = ::realloc(evaluation, (this -> length * (subDigitLength + 2u)) * sizeof(char));

                                    // Logic > Update > ...
                                    if (NULL == allocation) { ::free(evaluation); evaluation = NULL; iterator = this -> length - 1u; }
                                    else { digitLength = subDigitLength; evaluation = (char*) allocation; iterator = 0u; length = 0u; }
                                }

                                else
                                    // Loop > Update > ...
                                    while (digit) { *(evaluation + length++) = *("0123456789" + (digit % 10u)); digit /= 10u; }
                            }

                            else
                                // Update > Evaluation
                                *(evaluation + length++) = '0';

                            // Update > Evaluation
                            *(evaluation + length++) = ']';
                        }

                        else {
                            // Logic
                            if (digit > 35u) {
                                // Initialization > Allocation
                                void *allocation;

                                // (Loop > )Update > ...
                                for (Digit subiterator = digit; subiterator; subiterator /= 10u) ++digitLength;
                                allocation = ::realloc(evaluation, (this -> length * (digitLength + 2u)) * sizeof(char));

                                // Logic > ...
                                if (NULL == allocation) { ::free(evaluation); evaluation = NULL; iterator = this -> length - 1u; }
                                else { delimit = true; evaluation = (char*) allocation; iterator = 0u; length = 0u; }
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
