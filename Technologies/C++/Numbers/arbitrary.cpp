/* Import */
#include <stdlib.h> // Standard Library
#include <string.h> // String

#include <iostream>

/* Class > Big Number */
class BigNumber {
    // [...]
    private:
        // Definition > (Characteristics ..., Mantissa ..., Signedness, State)
        char *characteristics; size_t characteristicsLength;
        char *mantissa; size_t mantissaLength;
        bool signedness;
        enum {DENORMALIZED, INFINITE, SAFE, UNCOMPUTABLE} state;

        // Definition > ...
        void add(BigNumber const&) noexcept;
        void decrement(void) noexcept;
        void divide(BigNumber const&) noexcept;
        void exponentiate(BigNumber const&) noexcept;
        void increment(void) noexcept;
        void modulo(BigNumber const&) noexcept;
        void multiply(BigNumber const&) noexcept;
        void subtract(BigNumber const&) noexcept;

        // Function
            // Allocate --- NOTE (Lapys) -> Add more memory to the characteristics & mantissa.
            inline void allocate(void) noexcept {
                // Initialization > ((Recent) (Characteristics, Mantissa)) Size
                static size_t characteristicsSize;
                static size_t mantissaSize;

                size_t recentCharacteristicsSize = characteristicsSize;
                size_t recentMantissaSize = mantissaSize;

                // ... Update > (Characteristics, Mantissa) Size --- NOTE (Lapys) -> Uses the Fibonacci sequence to determine allocable memory size.
                if (this -> characteristicsLength) for (size_t former, iterator = 1u, limit = this -> characteristicsLength, recent = 0u; iterator <= limit; ) { former = iterator; iterator += recent; recent = former; characteristicsSize = iterator; }
                else characteristicsSize = 1u;

                if (this -> mantissaLength) for (size_t former, iterator = 1u, limit = this -> mantissaLength, recent = 0u; iterator <= limit; ) { former = iterator; iterator += recent; recent = former; mantissaSize = iterator; }
                else mantissaSize = 1u;

                // Logic
                if (characteristicsSize > recentCharacteristicsSize) {
                    // Modification > Target > Characteristics; Update > Recent Characteristics Size
                    this -> characteristics = (char*) (NULL == this -> characteristics ? ::malloc(characteristicsSize * sizeof(char)) : ::realloc(this -> characteristics, characteristicsSize * sizeof(char)));
                    recentCharacteristicsSize = characteristicsSize;
                }

                if (mantissaSize > recentMantissaSize) {
                    // Modification > Target > Mantissa; Update > Recent Mantissa Size
                    this -> mantissa = (char*) (NULL == this -> mantissa ? ::malloc(mantissaSize * sizeof(char)) : ::realloc(this -> mantissa, mantissaSize * sizeof(char)));
                    recentMantissaSize = mantissaSize;
                }
            }

            // Copy --- NOTE (Lapys) -> Assignment.
            inline void copy(BigNumber const& number) noexcept {
                // Logic
                if (BigNumber::SAFE == (this -> state = number.state)) {
                    // Modification > Target > ((Characteristics, Mantissa) ...)
                    this -> characteristics = (char*) (NULL == this -> characteristics ? ::malloc(number.characteristicsLength * sizeof(char)) : ::realloc(this -> characteristics, number.characteristicsLength * sizeof(char)));
                    this -> characteristicsLength = number.characteristicsLength;

                    this -> mantissa = (char*) (NULL == this -> mantissa ? ::malloc(number.mantissaLength * sizeof(char)) : ::realloc(this -> mantissa, number.mantissaLength * sizeof(char)));
                    this -> mantissaLength = number.mantissaLength;

                    ::strncpy(this -> characteristics, number.characteristics, number.characteristicsLength);
                    ::strncpy(this -> mantissa, number.mantissa, number.mantissaLength);
                }

                else {
                    // Modification > Target > ((Characteristics, Mantissa) ...)
                    ::free(this -> characteristics); this -> characteristics = NULL;
                    this -> characteristicsLength = 0u;

                    ::free(this -> mantissa); this -> mantissa = NULL;
                    this -> mantissaLength = 0u;
                }

                // Modification > Target > Signedness
                this -> signedness = number.signedness;
            }

            // Update --- NOTE (Lapys) -> Cleanup: Remove leading/ trailing zeros, correct signedness.
            inline void update(void) noexcept {
                // ...
                BigNumber::allocate();

                // Logic --- NOTE (Lapys) -> Clean the characteristics.
                if (this -> characteristicsLength) {
                    // Logic
                    if (1u ^ this -> characteristicsLength) {
                        // Initialization > Iterator
                        char *iterator = this -> characteristics;

                        // Logic
                        if ('0' == *iterator) {
                            // Loop > Update > Iterator
                            while ('0' == *iterator) ++iterator;

                            // Modification > Target > Characteristics (Length)
                            this -> characteristicsLength -= iterator - this -> characteristics;
                            ::memmove(this -> characteristics, iterator, this -> characteristicsLength * sizeof(char));
                        }
                    }
                }

                else {
                    // Modification > Target > Characteristics (Length)
                    *(this -> characteristics) = '0';
                    ++(this -> characteristicsLength);
                }

                // : Logic > Loop > Modification > Target > Mantissa Length --- NOTE (Lapys) -> Trim the mantissa.
                // : Logic > Modification > Target > Signedness --- NOTE (Lapys) -> Negative zero does not compute.
                if (this -> mantissaLength) for (char *iterator = this -> mantissa + (this -> mantissaLength - 1u); this -> mantissaLength && '0' == *iterator; --iterator) --(this -> mantissaLength);
                if (BigNumber::isZero()) this -> signedness = false;

                // ...
                BigNumber::allocate();
            }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigNumber(void) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} {}
        inline BigNumber(double const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(float const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(int const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(long const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(long double const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber(number)); }
        inline BigNumber(short const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(unsigned int const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(unsigned long const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(unsigned short const number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(BigNumber::fromNumber((long double) number)); }
        inline BigNumber(BigNumber const& number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(number); }
        inline BigNumber(BigNumber&& number) : characteristics{NULL}, characteristicsLength{0u}, mantissa{NULL}, mantissaLength{0u}, signedness{false}, state{BigNumber::SAFE} { BigNumber::copy(number); }

        // [Destructor]
        ~BigNumber(void) { ::free(this -> characteristics); ::free(this -> mantissa); }

        // (Definition, Function) > ...
        static BigNumber const fromNumber(long double const) noexcept;

        inline bool isComputable(void) const noexcept { return BigNumber::isComputable(*this); }
        static bool isComputable(BigNumber const&) noexcept;

        inline bool isEqual(BigNumber& number) noexcept { return BigNumber::isEqual(*this, number); }
        static bool isEqual(BigNumber&, BigNumber&) noexcept;

        inline bool isFinite(void) const noexcept { return BigNumber::isFinite(*this); }
        static bool isFinite(BigNumber const&) noexcept;

        inline bool isGreater(BigNumber& number) noexcept { return BigNumber::isGreater(*this, number); }
        static bool isGreater(BigNumber&, BigNumber&) noexcept;

        inline bool isInfinite(void) const noexcept { return BigNumber::isInfinite(*this); }
        static bool isInfinite(BigNumber const&) noexcept;

        inline bool isIntegral(void) const noexcept { return BigNumber::isIntegral(*this); }
        static bool isIntegral(BigNumber const&) noexcept;

        inline bool isLesser(BigNumber& number) noexcept { return BigNumber::isLesser(*this, number); }
        static bool isLesser(BigNumber&, BigNumber&) noexcept;

        inline bool isNaN(void) const noexcept { return BigNumber::isNaN(*this); }
        static bool isNaN(BigNumber const&) noexcept;

        inline bool isNormal(void) const noexcept { return BigNumber::isNormal(*this); }
        static bool isNormal(BigNumber const&) noexcept;

        inline bool isNegative(void) const noexcept { return BigNumber::isNegative(*this); }
        static bool isNegative(BigNumber const&) noexcept;

        inline bool isPositive(void) const noexcept { return BigNumber::isPositive(*this); }
        static bool isPositive(BigNumber const&) noexcept;

        inline bool isSafe(void) const noexcept { return BigNumber::isSafe(*this); }
        static bool isSafe(BigNumber const&) noexcept;

        inline bool isZero(void) const noexcept { return BigNumber::isZero(*this); }
        static bool isZero(BigNumber const&) noexcept;

        inline void sign(void) noexcept { this -> signedness = !(this -> signedness); }

        inline char const* toString(void) noexcept {
            // Evaluation > Evaluation
            static char *evaluation = NULL;

            // Deletion
            ::free(evaluation);

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

                    // Update
                    this -> update();

                    // Update > (Evaluation, Iterator)
                    evaluation = (char*) ::malloc((1u + this -> characteristicsLength + (this -> mantissaLength + 1u)) * sizeof(char));
                    iterator = evaluation;

                    // Logic > Update > Iterator --- MINIFY (Lapys)
                    if (this -> signedness) *iterator++ = '-';
                    ::strncpy(iterator, this -> characteristics, this -> characteristicsLength); iterator += this -> characteristicsLength;
                    if (this -> mantissaLength) { *iterator++ = '.'; ::strncpy(evaluation + (this -> characteristicsLength + this -> signedness), this -> mantissa, this -> mantissaLength); iterator += this -> mantissaLength; }

                    // Update > Iterator
                    *iterator++ = '\0';
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

        static long double toNumber(BigNumber&);
        static long double toNumber(BigNumber&&);

        inline void unsign(void) noexcept { this -> signedness = false; }

        // [Operator] > ...
        inline BigNumber operator +(void) const noexcept { return BigNumber{*this}; }
        inline BigNumber operator +(BigNumber const& number) const noexcept { BigNumber evaluation {*this}; evaluation.add(number); return evaluation; }
        inline BigNumber operator +(BigNumber&& number) const noexcept { return BigNumber::operator +(number); }
        inline BigNumber operator -(void) const noexcept { BigNumber evaluation {*this}; evaluation.signedness = !evaluation.signedness; return evaluation; }
        inline BigNumber operator -(BigNumber const& number) const noexcept { BigNumber evaluation {*this}; evaluation.subtract(number); return evaluation; }
        inline BigNumber operator -(BigNumber&& number) const noexcept { return BigNumber::operator -(number); }
        inline BigNumber operator *(BigNumber const& number) const noexcept { BigNumber evaluation {*this}; evaluation.multiply(number); return evaluation; }
        inline BigNumber operator *(BigNumber&& number) const noexcept { return BigNumber::operator *(number); }
        inline BigNumber operator /(BigNumber const& number) const noexcept { BigNumber evaluation {*this}; evaluation.divide(number); return evaluation; }
        inline BigNumber operator /(BigNumber&& number) const noexcept { return BigNumber::operator /(number); }
        inline BigNumber operator %(BigNumber const& number) const noexcept { BigNumber evaluation {*this}; evaluation.modulo(number); return evaluation; }
        inline BigNumber operator %(BigNumber&& number) const noexcept { return BigNumber::operator %(number); }
        inline BigNumber& operator =(BigNumber const& number) noexcept { BigNumber::copy(number); return *this; }
        inline BigNumber& operator =(BigNumber&& number) noexcept { return BigNumber::operator =(number); }
        inline BigNumber& operator +=(BigNumber const& number) noexcept { BigNumber::add(number); return *this; }
        inline BigNumber& operator +=(BigNumber&& number) noexcept { return BigNumber::operator +=(number); }
        inline BigNumber& operator -=(BigNumber const& number) noexcept { BigNumber::subtract(number); return *this; }
        inline BigNumber& operator -=(BigNumber&& number) noexcept { return BigNumber::operator -=(number); }
        inline BigNumber& operator *=(BigNumber const& number) noexcept { BigNumber::multiply(number); return *this; }
        inline BigNumber& operator *=(BigNumber&& number) noexcept { return BigNumber::operator *=(number); }
        inline BigNumber& operator /=(BigNumber const& number) noexcept { BigNumber::divide(number); return *this; }
        inline BigNumber& operator /=(BigNumber&& number) noexcept { return BigNumber::operator /=(number); }
        inline BigNumber& operator %=(BigNumber const& number) noexcept { BigNumber::modulo(number); return *this; }
        inline BigNumber& operator %=(BigNumber&& number) noexcept { return BigNumber::operator %=(number); }
        inline bool operator ==(BigNumber& number) noexcept { return BigNumber::isEqual(*this, number); }
        inline bool operator ==(BigNumber&& number) noexcept { return BigNumber::operator ==(number); }
        inline bool operator !=(BigNumber& number) noexcept { return false == BigNumber::operator ==(number); }
        inline bool operator !=(BigNumber&& number) noexcept { return false == BigNumber::operator ==(number); }
        inline bool operator <(BigNumber& number) noexcept { return BigNumber::isLesser(*this, number); }
        inline bool operator <(BigNumber&& number) noexcept { return BigNumber::operator <(number); }
        inline bool operator >(BigNumber& number) noexcept { return BigNumber::isGreater(*this, number); }
        inline bool operator >(BigNumber&& number) noexcept { return BigNumber::operator >(number); }
        inline bool operator <=(BigNumber& number) noexcept { return BigNumber::operator ==(number) || BigNumber::operator <(number); }
        inline bool operator <=(BigNumber&& number) noexcept { return BigNumber::operator <=(number); }
        inline bool operator >=(BigNumber& number) noexcept { return BigNumber::operator ==(number) || BigNumber::operator >(number); }
        inline bool operator >=(BigNumber&& number) noexcept { return BigNumber::operator >=(number); }
        inline BigNumber operator ++(int const) noexcept { BigNumber const evaluation {*this}; BigNumber::increment(); return evaluation; }
        inline BigNumber& operator ++(void) noexcept { BigNumber::increment(); return *this; }
        inline BigNumber operator --(int const) noexcept { BigNumber const evaluation {*this}; BigNumber::decrement(); return evaluation; }
        inline BigNumber& operator --(void) noexcept { BigNumber::decrement(); return *this; }

        inline operator char const*(void) noexcept { return BigNumber::toString(); }
};

/* Modification > Big Number */
    // Add --- CHECKPOINT (Lapys)
    inline void BigNumber::add(BigNumber const& number) noexcept {
        // ...
        this -> update();

        (void) number;
    }

    // Decrement
    inline void BigNumber::decrement(void) noexcept {
        // ...
        this -> update();

        // Logic > ... --- MINIFY (Lapys)
        if (1u == this -> characteristicsLength && '0' == *(this -> characteristics)) { *(this -> characteristics) = '1'; this -> signedness = true; }
        else if (BigNumber::isNegative()) { this -> signedness = false; BigNumber::increment(); this -> signedness = true; }
        else { this -> signedness = true; BigNumber::increment(); this -> signedness = false; }

        // ...
        this -> update();
    }

    // Divide
    inline void BigNumber::divide(BigNumber const& number) noexcept {
        this -> update();
        (void) number;
    }

    // Exponentiate
    inline void BigNumber::exponentiate(BigNumber const& number) noexcept {
        this -> update();
        (void) number;
    }

    // From Number
    inline BigNumber const BigNumber::fromNumber(long double const number) noexcept { (void) number; return BigNumber{}; }

    // Increment
    inline void BigNumber::increment(void) noexcept {
        // ...
        this -> update();

        // Logic
        if (1u == this -> characteristicsLength && '0' == *(this -> characteristics))
            // Modification > Target > Characteristics
            *(this -> characteristics) = '1';

        else {
            // Initialization > Iterator
            char *iterator = this -> characteristics + (this -> characteristicsLength - 1u);

            // Logic
            if (BigNumber::isNegative()) {
                // Loop > Update > Iterator
                // : Logic > Update > Iterator
                while (iterator != this -> characteristics && '0' == *iterator) { *iterator = '9'; --iterator; }
                switch (*iterator) { case '1': *iterator = '0'; break; case '2': *iterator = '1'; break; case '3': *iterator = '2'; break; case '4': *iterator = '3'; break; case '5': *iterator = '4'; break; case '6': *iterator = '5'; break; case '7': *iterator = '6'; break; case '8': *iterator = '7'; break; case '9': *iterator = '8'; break; }
            }

            else {
                // Loop > Update > Iterator
                while (iterator != this -> characteristics - 1 && '9' == *iterator) { *iterator = '0'; --iterator; }

                // Logic
                if (iterator == this -> characteristics - 1) {
                    // Modification > Target > Characteristics (Length)
                    this -> characteristics = (char*) ::realloc(this -> characteristics, (this -> characteristicsLength + 1u) * sizeof(char));
                    ::memmove(this -> characteristics + 1, this -> characteristics, this -> characteristicsLength * sizeof(char));
                    *(this -> characteristics) = '1';

                    ++(this -> characteristicsLength);
                }

                else
                    // Logic > Update > Iterator
                    switch (*iterator) { case '0': *iterator = '1'; break; case '1': *iterator = '2'; break; case '2': *iterator = '3'; break; case '3': *iterator = '4'; break; case '4': *iterator = '5'; break; case '5': *iterator = '6'; break; case '6': *iterator = '7'; break; case '7': *iterator = '8'; break; case '8': *iterator = '9'; break; }
            }
        }

        // ...
        this -> update();
    }

    // Is Computable
    inline bool BigNumber::isComputable(BigNumber const& number) noexcept { return BigNumber::UNCOMPUTABLE != number.state; }

    // Is Equal
    inline bool BigNumber::isEqual(BigNumber& numberA, BigNumber& numberB) noexcept {
        numberA.update();
        numberB.update();

        return false;
    }

    // Is Finite
    inline bool BigNumber::isFinite(BigNumber const& number) noexcept { return BigNumber::INFINITE != number.state; }

    // Is Greater
    inline bool BigNumber::isGreater(BigNumber& numberA, BigNumber& numberB) noexcept {
        numberA.update();
        numberB.update();

        return false;
    }

    // Is Infinite
    inline bool BigNumber::isInfinite(BigNumber const& number) noexcept { return BigNumber::INFINITE == number.state; }

    // Is Integral
    inline bool BigNumber::isIntegral(BigNumber const& number) noexcept { return 0u == number.mantissaLength; }

    // Is Lesser
    inline bool BigNumber::isLesser(BigNumber& numberA, BigNumber& numberB) noexcept {
        numberA.update();
        numberB.update();

        return false;
    }

    // Is Not-A-Number
    inline bool BigNumber::isNaN(BigNumber const& number) noexcept { return BigNumber::UNCOMPUTABLE == number.state; }

    // Is Negative
    inline bool BigNumber::isNegative(BigNumber const& number) noexcept { return number.signedness; }

    // Is Normal
    inline bool BigNumber::isNormal(BigNumber const& number) noexcept { return BigNumber::DENORMALIZED != number.state; }

    // Is Positive
    inline bool BigNumber::isPositive(BigNumber const& number) noexcept { return false == number.signedness; }

    // Is Safe
    inline bool BigNumber::isSafe(BigNumber const& number) noexcept { return BigNumber::isComputable(number) && BigNumber::isFinite(number) && BigNumber::isNormal(number); }

    // Is Zero
    inline bool BigNumber::isZero(BigNumber const& number) noexcept { return BigNumber::isIntegral(number) && (number.characteristicsLength == 1u && '0' == *(number.characteristics)); }

    // Modulo
    inline void BigNumber::modulo(BigNumber const& number) noexcept {
        this -> update();
        (void) number;
    }

    // Multiply
    inline void BigNumber::multiply(BigNumber const& number) noexcept {
        this -> update();
        (void) number;
    }

    // Subtract
    inline void BigNumber::subtract(BigNumber const& number) noexcept {
        this -> update();
        (void) number;
    }

    // To Number
    inline long double BigNumber::toNumber(BigNumber& number) {
        number.update();
        (void) number;
        return 0.00L;
    }
    inline long double BigNumber::toNumber(BigNumber&& number) { return BigNumber::toNumber(number); }

/* Main */
int main(void) {
    BigNumber number;

    for (unsigned short iterator = 0u; iterator ^ 256u; ++iterator) std::cout << "[number]: (" << number-- << ", " << -iterator << ')' << std::endl;
    number.unsign();
    for (unsigned short iterator = 256u; iterator ^ (unsigned short) -1; --iterator) std::cout << "[number]: (" << number-- << ", " << iterator << ')' << std::endl;

    // Return
    return EXIT_SUCCESS;
}
