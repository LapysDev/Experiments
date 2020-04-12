/* Import */
#include <math.h> // Mathematics
#include <stdlib.h> // Standard Library
#include <string.h> // String

#include <iostream>

/* Class > Big Number */
class BigNumber {
    // [...]
    private:
        // Definition > ((Characteristics, Mantissa) Length, Signedness, State, Value (Size))
        size_t characteristicsLength;
        size_t mantissaLength;
        bool signedness;
        enum {DENORMALIZED, INFINITE, SAFE, UNCOMPUTABLE} state;
        char *value; // NOTE (Lapys) -> Keep the characteristics and mantissa co-joined in the same field.

        // Function > (Copy, Size)
        inline void copy(BigNumber const& number) noexcept { if (BigNumber::SAFE == (this -> state = number.state)) { this -> characteristicsLength = number.characteristicsLength; this -> mantissaLength = number.mantissaLength; this -> signedness = number.signedness; this -> value = (char*) ::malloc(BigNumber::size(number.characteristicsLength + number.mantissaLength) * sizeof(char)); ::strncpy(this -> value, number.value, number.characteristicsLength + number.mantissaLength); } }
        inline void copy(BigNumber&& number) noexcept { if (BigNumber::SAFE == (this -> state = number.state)) { number.value = NULL; this -> characteristicsLength = number.characteristicsLength; this -> mantissaLength = number.mantissaLength; this -> signedness = number.signedness; this -> value = number.value; } }
        inline size_t size(void) noexcept { return BigNumber::size(this -> characteristicsLength + this -> mantissaLength); }
        inline size_t size(size_t const size) noexcept { size_t evaluation; for (size_t former, iterator = 1u, recent = 0u; iterator <= size; ) { former = iterator; iterator += recent; recent = former; evaluation = iterator; } return evaluation; }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigNumber(void) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} {}
        inline BigNumber(double const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(float const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(int const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(long const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(long double const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(short const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(unsigned int const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(unsigned long const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(unsigned short const number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(BigNumber const& number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(number); }
        inline BigNumber(BigNumber&& number) : characteristicsLength{0u}, mantissaLength{0u}, signedness{false}, state{SAFE}, value{NULL} { BigNumber::copy(number); }

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

        bool isNormal(void) const noexcept;
        inline static bool isNormal(BigNumber const& number) noexcept { return number.isNormal(); }
        inline static bool isNormal(BigNumber&& number) noexcept { return BigNumber::isNormal(number); }

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

        void sign(void) noexcept;
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
    BigNumber& BigNumber::add(BigNumber const& number) noexcept { (void) number; return *this; }

    // Decrement
    BigNumber& BigNumber::decrement(void) noexcept { return *this; }

    // Divide
    BigNumber& BigNumber::divide(BigNumber const& number) noexcept { (void) number; return *this; }

    // Exponentiate
    BigNumber& BigNumber::exponentiate(BigNumber const& number) noexcept { (void) number; return *this; }

    // From Number
    BigNumber const BigNumber::fromNumber(long const number) noexcept { (void) number; return BigNumber {}; }
    BigNumber const BigNumber::fromNumber(long double const number) noexcept { (void) number; return BigNumber {}; }
    BigNumber const BigNumber::fromNumber(unsigned long const number) noexcept { (void) number; return BigNumber {}; }

    // Get Characteristics
    long double BigNumber::getCharacteristics(void) const { return 0.00L; }

    // Get Mantissa
    long double BigNumber::getMantissa(void) const { return 0.00L; }

    // Has Significant Characteristics
    bool BigNumber::hasSignificantCharacteristics(void) const noexcept { return false; }

    // Has Significant Mantissa
    bool BigNumber::hasSignificantMantissa(void) const noexcept { return false; }

    // Increment
    BigNumber& BigNumber::increment(void) noexcept { return *this; }

    // Is Computable
    bool BigNumber::isComputable(void) const noexcept { return false; }

    // Is Equal
    bool BigNumber::isEqual(BigNumber const& numberA, BigNumber const& numberB) noexcept { (void) numberA; (void) numberB; return false; }

    // Is Finite
    bool BigNumber::isFinite(void) const noexcept { return false; }

    // Is Greater
    bool BigNumber::isGreater(BigNumber const& numberA, BigNumber const& numberB) noexcept { (void) numberA; (void) numberB; return false; }

    // Is Infinite
    bool BigNumber::isInfinite(void) const noexcept { return false; }

    // Is Integral
    bool BigNumber::isIntegral(void) const noexcept { return false; }

    // Is Lesser
    bool BigNumber::isLesser(BigNumber const& numberA, BigNumber const& numberB) noexcept { (void) numberA; (void) numberB; return false; }

    // Is Normal
    bool BigNumber::isNormal(void) const noexcept { return false; }

    // Is Safe
    bool BigNumber::isSafe(void) const noexcept { return false; }

    // Is Zero
    bool BigNumber::isZero(void) const noexcept { return false; }

    // Modulo
    BigNumber& BigNumber::modulo(BigNumber const& number) noexcept { (void) number; return *this; }

    // Multiply
    BigNumber& BigNumber::multiply(BigNumber const& number) noexcept { (void) number; return *this; }

    // Sign
    void BigNumber::sign(void) noexcept {}

    // Subtract
    BigNumber& BigNumber::subtract(BigNumber const& number) noexcept { (void) number; return *this; }

    // To Number
    long double BigNumber::toNumber(BigNumber const& number) { (void) number; return 0.00L; }

    // To String
    char const* BigNumber::toString(void) const noexcept { return NULL; }

    // Unsign
    void BigNumber::unsign(void) noexcept {}

/* Main */
int main(void) {
    /* [Initiate] ... */
    std::cout << "[PROGRAM INITIATED]" << std::endl;

    /* [Terminate] ... */
    std::cout << "[PROGRAM TERMINATED]" << std::flush;

    // Return
    return EXIT_SUCCESS;
}
