/* Import */
    // [C Standard Library]
    #include <float.h> // Floating-Points
    #include <limits.h> // Limits
    #include <math.h> // Mathematics
    #include <stdarg.h> // Standard Arguments
    #include <stdio.h> // Standard Input-Output
    #include <stdint.h> // Standard Integer
    #include <stdlib.h> // Standard Library

    // [C++ Standard Library]
    #include <iostream> // Input-Output Stream --- NOTE (Lapys) -> For testing.

/* Class > Big Integer */
class BigInteger {
    /* ... */
    typedef signed long long primitive_t;

    // [...]
    protected:
        /* Phase > Terminate */
        inline void terminate(void) noexcept { BigInteger::zero(); }
        inline void terminate(char const message[], ...) { va_list arguments; terminate(); ::putchar('\r'); va_start(arguments, message); for (char const *argument = message; NULL != argument; argument = va_arg(arguments, char const*)) for (char const *iterator = argument; '\0' ^ *iterator; ++iterator) ::putchar(*iterator); ::putchar('\n'); va_end(arguments); ::abort(); }

    // [...]
    private:
        // Definition > Value
        long double value;

        // Method > Copy
        inline void copy(BigInteger const& number) noexcept { this -> value = number.value; }

    // [...]
    public:
        // [Constructor]
        inline BigInteger(void) : value{0.00L} {}
        inline BigInteger(primitive_t const number) : value{0.00L} { BigInteger::copy(BigInteger::fromNumber(number)); }
        inline BigInteger(BigInteger const& number) : value{0.00L} { BigInteger::copy(number); }

        // [Destructor]
        inline ~BigInteger(void) { terminate(); }

        // Method > ...
            // [Conditional] Is (Base Factor, Big, Equal, Even, Finite, Greater, Infinite, Lesser, Negative, Odd, Positive, Significant, Zero)
            inline bool isBaseFactor(void) const noexcept { return BigInteger::isBaseFactor(*this); }
            static bool isBaseFactor(BigInteger const&) noexcept;
            inline bool isBig(void) const noexcept { return BigInteger::isBig(*this); }
            static bool isBig(BigInteger const&) noexcept;
            inline bool isEqual(BigInteger const& number) const noexcept { return BigInteger::isEqual(*this, number); }
            static bool isEqual(BigInteger const&, BigInteger const&) noexcept;
            inline bool isEven(void) const noexcept { return BigInteger::isEven(*this); }
            static bool isEven(BigInteger const&) noexcept;
            inline bool isGreater(BigInteger const& number) const noexcept { return BigInteger::isGreater(*this, number); }
            static bool isGreater(BigInteger const&, BigInteger const&) noexcept;
            inline bool isLesser(BigInteger const& number) const noexcept { return BigInteger::isLesser(*this, number); }
            static bool isLesser(BigInteger const&, BigInteger const&) noexcept;
            inline bool isNegative(void) const noexcept { return BigInteger::isNegative(*this); }
            static bool isNegative(BigInteger const&) noexcept;
            inline bool isOdd(void) const noexcept { return BigInteger::isOdd(*this); }
            static bool isOdd(BigInteger const&) noexcept;
            inline bool isPositive(void) const noexcept { return BigInteger::isPositive(*this); }
            static bool isPositive(BigInteger const&) noexcept;
            inline bool isSignificant(void) const noexcept { return BigInteger::isSignificant(*this); }
            static bool isSignificant(BigInteger const&) noexcept;
            inline bool isZero(void) const noexcept { return BigInteger::isZero(*this); }
            static bool isZero(BigInteger const&) noexcept;

            // [Miscellaneous] From (Base, Number), To (Base, Number, String), Zero
            static BigInteger fromNumber(primitive_t const number) noexcept;
            static primitive_t toNumber(BigInteger&);
            char* toString(void) const;
            inline void zero(void) noexcept { this -> value = 0.00L; }

            // [Operational] Add, Decrement, Divide, Exponentiate, Increment, Multiply, Shift (Left, Right), Sign, Subtract, Unsign
            BigInteger& add(BigInteger const&);
            inline static BigInteger add(BigInteger const& numberA, BigInteger const& numberB) { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.add(numberB); return evaluation; }
            inline static BigInteger& add(BigInteger const& numberA, BigInteger&& numberB) { numberB.add(numberA); return numberB; }
            inline static BigInteger& add(BigInteger&& numberA, BigInteger const& numberB) { numberA.add(numberB); return numberA; }

            BigInteger& decrement(void);
            inline BigInteger decrement(BigInteger const& number) { BigInteger evaluation {}; evaluation.copy(number); evaluation.decrement(); return evaluation; }

            BigInteger& divide(BigInteger const&) noexcept;
            inline static BigInteger divide(BigInteger const& numberA, BigInteger const& numberB) noexcept { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.divide(numberB); return evaluation; }
            inline static BigInteger& divide(BigInteger&& numberA, BigInteger const& numberB) noexcept { numberA.divide(numberB); return numberA; }

            BigInteger& exponentiate(BigInteger const&);
            inline static BigInteger exponentiate(BigInteger const& numberA, BigInteger const& numberB) { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.exponentiate(numberB); return evaluation; }
            inline static BigInteger& exponentiate(BigInteger&& numberA, BigInteger const& numberB) { numberA.exponentiate(numberB); return numberA; }

            BigInteger& increment(void);
            inline BigInteger increment(BigInteger const& number) { BigInteger evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }

            BigInteger& modulo(BigInteger const&);
            inline static BigInteger modulo(BigInteger const& numberA, BigInteger const& numberB) { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.modulo(numberB); return evaluation; }
            inline static BigInteger& modulo(BigInteger&& numberA, BigInteger const& numberB) { numberA.modulo(numberB); return numberA; }

            BigInteger& multiply(BigInteger const&);
            inline static BigInteger multiply(BigInteger const& numberA, BigInteger const& numberB) { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.multiply(numberB); return evaluation; }
            inline static BigInteger& multiply(BigInteger const& numberA, BigInteger&& numberB) { numberB.multiply(numberA); return numberB; }
            inline static BigInteger& multiply(BigInteger&& numberA, BigInteger const& numberB) { numberA.multiply(numberB); return numberA; }

            BigInteger& shiftLeft(void);
            BigInteger& shiftLeft(primitive_t const);
            inline static BigInteger shiftLeft(BigInteger const& number) { BigInteger evaluation {}; evaluation.copy(number); evaluation.shiftLeft(); return evaluation; }
            inline static BigInteger shiftLeft(BigInteger const& numberA, primitive_t const numberB) { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.shiftLeft(numberB); return evaluation; }

            BigInteger& shiftRight(void);
            BigInteger& shiftRight(primitive_t const);
            inline static BigInteger shiftRight(BigInteger const& number) { BigInteger evaluation {}; evaluation.copy(number); evaluation.shiftRight(); return evaluation; }
            inline static BigInteger shiftRight(BigInteger const& numberA, primitive_t const numberB) { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.shiftRight(numberB); return evaluation; }

            BigInteger& sign(void) noexcept;
            BigInteger sign(BigInteger const& number) noexcept { BigInteger evaluation {}; evaluation.copy(number); evaluation.sign(); return evaluation; }

            BigInteger& subtract(BigInteger const&);
            inline static BigInteger subtract(BigInteger const& numberA, BigInteger const& numberB) { BigInteger evaluation {}; evaluation.copy(numberA); evaluation.subtract(numberB); return evaluation; }
            inline static BigInteger& subtract(BigInteger&& numberA, BigInteger const& numberB) { numberA.subtract(numberB); return numberA; }

            BigInteger& unsign(void) noexcept;
            BigInteger unsign(BigInteger const& number) noexcept { BigInteger evaluation {}; evaluation.copy(number); evaluation.unsign(); return evaluation; }
};

/* Modification > Big Integer */
    // ...
    inline BigInteger& BigInteger::add(BigInteger const& number) { if (LDBL_MAX == (this -> value += number.value)) terminate("[Arithmetic Error]: Unable to operate on fixed-width integer", NULL); return *this; }
    inline BigInteger& BigInteger::decrement(void) { if (LDBL_MIN == --(this -> value)) terminate("[Arithmetic Error]: Unable to operate on fixed-width integer", NULL); return *this; }
    inline BigInteger& BigInteger::divide(BigInteger const& number) { this -> value /= number.value; return *this; }
    inline BigInteger& BigInteger::increment(void) { if (LDBL_MAX == ++(this -> value)) terminate("[Arithmetic Error]: Unable to operate on fixed-width integer", NULL); return *this; }
    inline BigInteger& BigInteger::multiply(BigInteger const& number) { if (LDBL_MAX == (this -> value *= number.value)) terminate("[Arithmetic Error]: Unable to operate on fixed-width integer", NULL); return *this; }
    inline BigInteger& BigInteger::subtract(BigInteger const& number) { if (LDBL_MIN == (this -> value -= number.value)) terminate("[Arithmetic Error]: Unable to operate on fixed-width integer", NULL); return *this; }

    // Exponentiate
    inline BigInteger& BigInteger::exponentiate(BigInteger const& number) {
        // Logic
        #if defined(__cplusplus) && __cplusplus >= 199711L
            // Modification > Target > Value; Logic > Error
            this -> value = ::powl(this -> value, number.value);
            if (::isinf(this -> value) || ::isnan(this -> value)) terminate("[Arithmetic Error]: Unable to operate on fixed-width integer", NULL);
        #else
            // Logic > ...
            if (BigInteger::isNegative(number)) BigInteger::zero();
            else { BigInteger incrementor, iterator; incrementor.copy(this -> value); iterator.copy(number.value); if (iterator.isSignificant()) while (iterator.decrement().isSignificant()) BigInteger::multiply(incrementor); }
        #endif

        // Return
        return *this;
    }

    // From Number
    inline BigInteger BigInteger::fromNumber(primitive_t const number) { BigInteger evaluation {}; evaluation.value = (long double) number; return evaluation; }

    // Is ...
    inline bool BigInteger::isBig(BigInteger const& number) noexcept { static BigInteger const PRIMITIVE_MAX {LLONG_MAX}; return BigInteger::isGreater(number, PRIMITIVE_MAX); }
    inline bool BigInteger::isEqual(BigInteger const& numberA, BigInteger const& numberB) noexcept { return numberA.value == numberB.value; }
    inline bool BigInteger::isEven(BigInteger const& number) noexcept { long double evaluation = number.value; while (evaluation >= 10.00L) evaluation /= 10.00L; if ((evaluation >= 2.00L && evaluation < 3.00L) || (evaluation >= 4.00L && evaluation < 5.00L) || (evaluation >= 6.00L && evaluation < 7.00L) || (evaluation >= 8.00L && evaluation < 9.00L)) return true; return false; }
    inline bool BigInteger::isGreater(BigInteger const& numberA, BigInteger const& numberB) noexcept { return numberA.value > numberB.value; }
    inline bool BigInteger::isLesser(BigInteger const& numberA, BigInteger const& numberB) noexcept { return numberA.value < numberB.value; }
    inline bool BigInteger::isNegative(BigInteger const& number) noexcept { return number.value < 0.00L; }
    inline bool BigInteger::isOdd(BigInteger const& number) noexcept { long double evaluation = number.value; while (evaluation >= 10.00L) evaluation /= 10.00L; if ((evaluation >= 1.00L && evaluation < 2.00L) || (evaluation >= 3.00L && evaluation < 4.00L) || (evaluation >= 5.00L && evaluation < 6.00L) || (evaluation >= 7.00L && evaluation < 8.00L) || (evaluation >= 9.00L/* && evaluation < 10.00L*/)) return true; return false; }
    inline bool BigInteger::isPositive(BigInteger const& number) noexcept { return number.value >= 0.00L; }
    inline bool BigInteger::isSignificant(BigInteger const& number) noexcept { return 0.00L != number.value; }
    inline bool BigInteger::isZero(BigInteger const& number) noexcept { return 0.00L == number.value; }

    // Is Base Factor
    inline bool BigInteger::isBaseFactor(BigInteger const& number) noexcept {
        // Initialization > Evaluation
        bool evaluation = false;

        // Loop > Logic > Update > (Evaluation, Iterator)
        for (long double iterator = 1.00L; iterator; ) {
            if (LDBL_MAX == iterator) { evaluation = false; iterator = 0.00L; }
            else if (iterator == number.value) { evaluation = true; iterator = 0.00L; }
            else iterator *= 10.00L;
        }

        // Return
        return evaluation;
    }

    // Modulo
    inline BigInteger& BigInteger::modulo(BigInteger const& number) {
        // Logic
        #if defined(__cplusplus) && __cplusplus >= 199711L
            // Modification > Target > Value; Logic > Error
            this -> value = ::fmodl(this -> value, number.value);
            if (::isnan(this -> value)) terminate("[Arithmetic Error]: Unable to operate on fixed-width integer", NULL);
        #else
            // Logic
            if (BigInteger::isNegative(numberB)) {
                // Initialization > Sub-Number
                BigInteger subnumber;

                // ...
                subnumber.copy(number); subnumber.sign();
                BigInteger::modulo();
            }

            else {
                // Initialization > Evaluation
                BigInteger evaluation;

                // ...; (Logic, Loop) > Update > Evaluation
                evaluation.copy(*this);

                if (BigInteger::isNegative(evaluation)) evaluation.sign();
                while (false == BigInteger::isLesser(evaluation, numberB)) evaluation.subtract(numberB);
                if (BigInteger::isNegative(evaluation)) evaluation.sign();

                // Update > ...
                BigInteger::copy(evaluation);
            }
        #endif

        // Return
        return *this;
    }

    // Shift Left --- CHECKPOINT (Lapys)
    // inline BigInteger& BigInteger::shiftLeft(void);

    // inline BigInteger& BigInteger::shiftLeft(primitive_t const);

    // Shift Right --- CHECKPOINT (Lapys)
    // inline BigInteger& BigInteger::shiftRight(void);

    // inline BigInteger& BigInteger::shiftRight(primitive_t const);

    // To Number
    inline primitive_t BigInteger::toNumber(BigInteger& number) { if (number.value > LLONG_MAX) number.terminate("[Arithmetic Error]: Unable to convert arbitrary-precision number to fixed-width integer"); return (primitive_t) number.value; }

    // To String
    inline char* BigInteger::toString(void) const {
        // Evaluation > Evaluation
        char *evaluation = NULL;

        // Logic
        if (number) {
            evaluation = (char*) ::malloc(20u /* -> ULLONG_MAX_10_EXP */ * sizeof(char));

            if (NULL != evaluation) {
                long double characteristics = 0.00L;
                char *iterator = evaluation;
                long double mantissa = 0.00L;

                if (BigInteger::isNegative()) { *iterator++ = '-'; *iterator = '0'; mantissa = ::modf(-(this -> value), &characteristics); }
                else { *iterator = '0'; mantissa = ::modf(this -> value, &characteristics); }
            }

            if (characteristics) {
                for (long double digit; characteristics; *iterator++ = *("0123456789" + (unsigned char) ::round(digit))) digit = ::modf((characteristics /= 10.00L), &characteristics) * 10.00L;
                for (char *index = iterator, *subindex = evaluation + BigInteger::isNegative(); index > subindex; (--index, --subindex)) { *index ^= *subindex; *subindex ^= *index; *index ^= *subindex; }
            }

            if (mantissa) {
                *iterator++ = '.';
                for (long double digit; mantissa >= LDBL_EPSILON; *iterator++ = *("0123456789" + (unsigned char) ::round(digit))) mantissa = ::modf((mantissa *= 10.00L), &digit);
            }
        }

        else {
            // (Logic > )Update > Evaluation
            evaluation = (char*) ::malloc(2u * sizeof(char));
            if (NULL != evaluation) { *evaluation = '0'; *(evaluation + 1) = '\0'; }
        }

        // Return
        return evaluation;
    }

    // (Un)Sign
    inline BigInteger& BigInteger::sign(void) noexcept;
    inline BigInteger& BigInteger::unsign(void) noexcept;

/* Main */
int main(void) {
    BigInteger number {M_PI};
    std::cout << "[EVAL]: " << number.toString() << std::flush;

    // Return
    return EXIT_SUCCESS;
}
