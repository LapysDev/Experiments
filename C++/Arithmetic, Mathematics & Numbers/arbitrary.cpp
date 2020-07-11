/* Import */
    // [C Standard Library]
    #include <float.h> // Floating-Points
    #include <math.h> // Mathematics
    #include <stdio.h> // Standard Input-Output
    #include <stdint.h> // Standard Integer
    #include <stdlib.h> // Standard Library
    #include <time.h> // Time

    // [...]
    #include "~/logger.hpp" // Logger
    #include "~/random.h" // Random

/* Class */
    /* Big Unsigned Integer */
    template <size_t radix = 10u>
    class BigUnsignedInteger {
        /* ... */
        class Digit;
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef typename Digit::digit_t digit_t;
        typedef size_t length_t;
        typedef unsigned long primitive_t;

        // [...]
        protected:
            // Method > (Assert, ...)
            void assert(void) const;
            constexpr static unsigned char getMaximumLengthSize(void) noexcept;

        // [...]
        private:
            // Definition > (Length, Value)
            length_t length : BigUnsignedInteger::getMaximumLengthSize();
            Digit *value;

            // Method > (Allocate, Copy, Move)
            void allocate(size_t const);
            template <size_t base> void copy(BigUnsignedInteger<base> const&);
            template <size_t base> void move(BigUnsignedInteger<base>&&);

        // [...]
        public:
            // [Constructor]
            constexpr BigUnsignedInteger(void);
            constexpr BigUnsignedInteger(primitive_t const);
            constexpr BigUnsignedInteger(BigUnsignedInteger const&);
            template <size_t base> constexpr BigUnsignedInteger(BigUnsignedInteger<base> const&);
            template <size_t base> constexpr BigUnsignedInteger(BigUnsignedInteger<base>&&);

            // [Destructor]
            ~BigUnsignedInteger(void);

            // Method > (Add, Decrement, Divide, Exponentiate, From (Base, Number), Increment, Is ..., Modulo, Multiply, Subtract, To ..., Zero)
            template <size_t base> constexpr void add(BigUnsignedInteger<base> const& number);
            constexpr inline static BigUnsignedInteger add(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.add(numberB); return evaluation; }

            constexpr void decrement(void);
            constexpr inline static BigUnsignedInteger decrement(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.decrement(); return evaluation; }

            template <size_t base> constexpr void divide(BigUnsignedInteger<base> const& number);
            constexpr inline static BigUnsignedInteger divide(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.divide(numberB); return evaluation; }

            template <size_t base> constexpr void exponentiate(BigUnsignedInteger<base> const& number);
            constexpr inline static BigUnsignedInteger exponentiate(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.exponentiate(numberB); return evaluation; }

            template <size_t base> constexpr static BigUnsignedInteger<radix> fromBase(BigUnsignedInteger<base> const&);
            constexpr static BigUnsignedInteger fromNumber(primitive_t);

            constexpr void increment(void);
            constexpr inline static BigUnsignedInteger increment(BigUnsignedInteger const& number) { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }

            constexpr bool isBaseFactor(void) const noexcept;
            constexpr inline static bool isBaseFactor(BigUnsignedInteger const& number) noexcept { return number.isBaseFactor(); }
            constexpr bool isComputable(void) const noexcept;
            constexpr inline static bool isComputable(BigUnsignedInteger const& number) noexcept { return number.isComputable(); }
            template <size_t base> constexpr bool isEqual(BigUnsignedInteger<base> const&) const noexcept;
            constexpr inline static bool isEqual(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { return numberA.isEqual(numberB); }
            constexpr bool isFinite(void) const noexcept;
            constexpr inline static bool isFinite(BigUnsignedInteger const& number) noexcept { return number.isFinite(); }
            template <size_t base> constexpr bool isGreater(BigUnsignedInteger<base> const&) const noexcept;
            constexpr inline static bool isGreater(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { return numberA.isGreater(numberB); }
            constexpr bool isInfinite(void) const noexcept;
            constexpr inline static bool isInfinite(BigUnsignedInteger const& number) noexcept { return number.isInfinite(); }
            template <size_t base> constexpr bool isLesser(BigUnsignedInteger<base> const&) const noexcept;
            constexpr inline static bool isLesser(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { return numberA.isLesser(numberB); }
            constexpr bool isNegative(void) const noexcept;
            constexpr inline static bool isNegative(BigUnsignedInteger const& number) noexcept { return number.isNegative(); }
            constexpr bool isNonComputable(void) const noexcept;
            constexpr inline static bool isNonComputable(BigUnsignedInteger const& number) noexcept { return number.isNonComputable(); }
            constexpr bool isOne(void) const noexcept;
            constexpr inline static bool isOne(BigUnsignedInteger const& number) noexcept { return number.isOne(); }
            constexpr bool isPositive(void) const noexcept;
            constexpr inline static bool isPositive(BigUnsignedInteger const& number) noexcept { return number.isPositive(); }
            constexpr bool isSignificant(void) const noexcept;
            constexpr inline static bool isSignificant(BigUnsignedInteger const& number) noexcept { return number.isSignificant(); }
            constexpr bool isZero(void) const noexcept;
            constexpr inline static bool isZero(BigUnsignedInteger const& number) noexcept { return number.isZero(); }

            template <size_t base> constexpr void modulo(BigUnsignedInteger<base> const& number);
            constexpr inline static BigUnsignedInteger modulo(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.modulo(numberB); return evaluation; }

            template <size_t base> constexpr void multiply(BigUnsignedInteger<base> const& number);
            constexpr inline static BigUnsignedInteger multiply(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.multiply(numberB); return evaluation; }

            void shiftLeft(length_t const )

            template <size_t base> constexpr void subtract(BigUnsignedInteger<base> const& number);
            constexpr inline static BigUnsignedInteger subtract(BigUnsignedInteger const& numberA, BigUnsignedInteger const& numberB) { BigUnsignedInteger evaluation {}; evaluation.copy(numberA); evaluation.subtract(numberB); return evaluation; }

            template <size_t base> constexpr static BigUnsignedInteger<base> toBase(BigUnsignedInteger<radix> const&);
            constexpr static primitive_t toNumber(BigUnsignedInteger const&);
            constexpr char* toString(bool = false) const;

            constexpr void zero(void) noexcept;
            constexpr inline void zero(BigUnsignedInteger const& number) noexcept { number.zero(); }
    };

    /* Big Signed Integer */
    template <size_t radix = 10u>
    class BigSignedInteger : public BigUnsignedInteger<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef typename BigUnsignedInteger<radix>::Digit Digit;
        typedef typename BigUnsignedInteger<radix>::Digit::digit_t digit_t;
        typedef signed long primitive_t;
    };

    /* Big Float */
    template <size_t radix = 10u>
    class BigFloat : public BigSignedInteger<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef typename BigSignedInteger<radix>::Digit Digit;
        typedef typename BigSignedInteger<radix>::Digit::digit_t digit_t;
        typedef long double primitive_t;
    };

    /* Digit --- NOTE (Lapys) -> Fixed arithmetic integer value between `0u` and `radix`. Can and will not store any values beyond `radix`. */
    template <size_t radix>
    class BigUnsignedInteger<radix>::Digit {
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef size_t digit_t;

        protected:
            constexpr static digit_t align(digit_t const) noexcept;
            constexpr static unsigned char getLength(size_t) noexcept;
            constexpr static unsigned char getSize(size_t) noexcept;
            constexpr static bool isDenary(digit_t) noexcept;

        private:
            // NOTE (Lapys) -> Assumed to be a denary representation of the digit.
            digit_t value : Digit::getSize((radix * 2u) - 2u /* NOTE (Lapys) -> For arithmetic shenanigans e.g.: storing `10` inside a single base-10 `Digit`. */);

        public:
            constexpr inline Digit(void) : value{0u} {}
            constexpr inline Digit(digit_t const value) : value{Digit::align(value)} {}
            template <size_t base> constexpr inline Digit(typename BigUnsignedInteger<base>::Digit const& digit) : value{Digit::align(digit.value)} {}

            constexpr static bool isGreaterRank(digit_t const) noexcept;
            constexpr static bool isGreatestRank(digit_t const) noexcept;
            constexpr static bool isLowerRank(digit_t const) noexcept;
            constexpr static bool isLowestRank(digit_t const) noexcept;
            constexpr static bool isMeanRank(digit_t const) noexcept;

            // WARN (Lapys) -> Returns stack allocated pointer.
            static Digit* add(Digit const&, Digit const&) noexcept;
            static Digit* multiply(Digit const&, Digit const&) noexcept;

            char* toString(void) const noexcept;
            inline static char* toString(Digit const& digit) noexcept { return digit.toString(); }

            constexpr inline Digit& operator =(digit_t const value) noexcept { this -> value = Digit::align(value); return *this; }
            template <size_t base> constexpr inline Digit& operator =(typename BigUnsignedInteger<base>::Digit const& digit) noexcept { this -> value = Digit::align(digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator +=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value += digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator -=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value -= digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator *=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value *= digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator /=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value /= digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator %=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value %= digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator ^=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value ^= digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator &=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value &= digit.value); return *this; }
            template <size_t base> constexpr inline Digit& operator |=(typename BigUnsignedInteger<base>::Digit const& digit) const noexcept { this -> value = Digit::align(this -> value |= digit.value); return *this; }
            constexpr inline Digit operator ++(int const) const noexcept { Digit const evaluation {this -> value}; Digit::operator ++(); return evaluation; }
            constexpr inline Digit& operator ++(void) const noexcept { this -> value = Digit::align(++(this -> value)); return *this; }
            constexpr inline Digit operator --(int const) const noexcept { Digit const evaluation {this -> value}; Digit::operator --(); return evaluation; }
            constexpr inline Digit& operator --(void) const noexcept { this -> value = Digit::align(--(this -> value)); return *this; }
            constexpr inline operator digit_t(void) const noexcept { return this -> value; }
    };

/* Modification */
    /* Big Unsigned Integer */
        // [Constructor]
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(void) : length{0u}, value{NULL} {}
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(primitive_t const number) : length{0u}, value{NULL} { BigUnsignedInteger::move(BigUnsignedInteger::fromNumber(number)); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigUnsignedInteger const& number) : length{0u}, value{NULL} { if (&number != this) BigUnsignedInteger::copy(number); }
        template <size_t radix> template <size_t base> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigUnsignedInteger<base> const& number) : length{0u}, value{0u} { base == radix ? BigUnsignedInteger::copy(number) : BigUnsignedInteger::move(BigUnsignedInteger::fromBase<base>(number)); }
        template <size_t radix> template <size_t base> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigUnsignedInteger<base>&& number) : length{0u}, value{NULL} { base == radix ? BigUnsignedInteger::move((BigUnsignedInteger&&) number) : BigUnsignedInteger::move(BigUnsignedInteger::fromBase<base>(number)); }

        // [Destructor]
        template <size_t radix> inline BigUnsignedInteger<radix>::~BigUnsignedInteger(void) { ::free(this -> value); }

        // Add
        template <size_t radix> template <size_t base>
        constexpr inline void BigUnsignedInteger<radix>::add(BigUnsignedInteger<base> const& number) {
            // Logic
            if (base ^ radix) BigUnsignedInteger::add(BigUnsignedInteger::fromBase<base>(number));
            else if (BigUnsignedInteger::isZero()) BigUnsignedInteger::copy(number);
            else if (BigUnsignedInteger::isOne()) { BigUnsignedInteger::copy(number); BigUnsignedInteger::increment(); }
            else if (BigUnsignedInteger::isOne(number)) BigUnsignedInteger::increment();
            else if (BigUnsignedInteger::isSignificant(number)) {
                // Initialization > Iterator (A, B) --- NOTE (Lapys) -> Set the "counter" variables.
                Digit *iteratorA = this -> value + this -> length;
                Digit const *iteratorB = number.value + number.length;

                // Loop --- NOTE (Lapys) -> The algorithm used in the proceeding `for` loop only has defined behavior if the source number (`this`) has a greater or equal characteristics length to `number`.
                if (this -> length < number.length) {
                    // ...
                    BigUnsignedInteger::allocate(number.length);

                    iteratorA = this -> value + number.length;
                    this -> value += this -> length;

                    // Loop > Update > Iterator --- NOTE (Lapys) -> Shift the source number e.g.: `69 + 420` becomes `069 + 420`
                    while ((this -> length)--) (--iteratorA) -> value = (--(this -> value)) -> value;
                    while (this -> value != iteratorA--) iteratorA -> value = 0u;

                    // Modification > Target > Length
                    // : Update > Iterator A --- NOTE (Lapys) -> Reset the "counter" variable.
                    this -> length = number.length;
                    iteratorA = this -> value + this -> length;
                }

                // Loop --- NOTE (Lapys) -> Per-digit addition loop.
                for (Digit carry = 0u, *evaluation = NULL; this -> value != iteratorA-- && --iteratorB; ) {
                    // Logic
                    if (number.value > iteratorB) { // NOTE (Lapys) -> Exhausted `number`'s digits to add.
                        // Logic --- NOTE (Lapys) -> Round-up addition loop.
                        if (false == Digit::isLowestRank(carry)) {
                            // Update > (Evaluation, ...)
                            evaluation = Digit::add(*iteratorA, carry);
                            carry.value = 0u;
                        } else break;
                    }

                    else {
                        // Update > Evaluation
                        evaluation = Digit::add(*iteratorA, *iteratorB);

                        // Logic --- NOTE (Lapys) -> Add the `carry` to the `evaluation`.
                        if (false == Digit::isLowestRank(carry)) {
                            /* Update > (Carry, Evaluation)
                                --- NOTE ---
                                    #Lapys: Mutates the former values of `evaluation` via call to `Digit::add(...)`,
                                        fortunately the second element in `evaluation` is preserved through unwitting arithmetic
                                        and the first element is preserved through the initial statically parsed value of `evaluation -> value`.
                                --- WARN (Lapys) -> `evaluation -> value += ...` evaluates to undefined arithmetic.
                            */
                            evaluation -> value = evaluation -> value + (false == Digit::isLowestRank(Digit::add(carry, (evaluation + 1) -> value) -> value));
                            carry.value = 0u; // NOTE (Lapys) -> Reset the carry for the next addition.
                        }
                    }

                    // Update > Iterator A
                    iteratorA -> value = (evaluation + 1) -> value;

                    // Logic --- NOTE (Lapys) -> Handle multi-digit `evaluation`s as the carry and result.
                    if (false == Digit::isLowestRank(evaluation -> value)) {
                        /* Update > Carry --- NOTE (Lapys) -> Storing the carry would have been redundant
                                if the `Digit::add(...)` function was not utilized in the `BigUnsignedInteger::multiply(...)` method and
                                since the size of `Digit::value` was able to store `0` - `(radix * 2u) - 2u` digits for private arithmetic.
                        */
                        carry.value = evaluation -> value;

                        // Logic --- NOTE (Lapys) -> Expand the target number.
                        if (this -> value == iteratorA) {
                            // ...
                            BigUnsignedInteger::allocate(++(this -> length));

                            iteratorA = this -> value + this -> length;
                            while (this -> value != --iteratorA) iteratorA -> value = (iteratorA - 1) -> value;
                            iteratorA -> value = carry.value;

                            break;
                        }
                    }
                }
            }
        }

        // Allocate --- NOTE (Lapys) -> Implicitly frees memory if the specified length is zero. --- REDACT (Lapys)
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::allocate(size_t const length) {
            // Logic ... --- NOTE (Lapys) -> Utilizes C-style dynamic memory allocation because RAII is not a requisite to handling `Digit` objects.
            if (0u == length) { ::free(this -> value); this -> value = NULL; }
            else if (length >= SIZE_MAX / sizeof(Digit)) { ::print("\r[MemoryException]: Attempt to acquire additional memory (", length * sizeof(Digit), " of ", SIZE_MAX, " bytes) than is allocable for a pointer within arbitrary-precision number", '\0'); ::abort(); }
            else {
                void *const allocation = NULL == this -> value ? ::malloc(length * sizeof(Digit)) : ::realloc(this -> value, length * sizeof(Digit));

                if (NULL == allocation) { ::print("\r[MemoryException]: Attempt to acquire additional memory (", length * sizeof(Digit), " bytes) for arbitrary-precision number failed", '\0'); ::abort(); }
                else this -> value = (Digit*) allocation;
            }
        }

        // Assert --- NOTE (Lapys) -> Assert the arbitrary-precision number was initialized correctly.
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::assert(void) const {
            // Logic > Error
            if (SIZE_MAX /* -> RADIX_MAX */ == radix || 0u == radix || radix == 1u) {
                ::print("\r[LogicException]: Attempt to initialize arbitrary-precision number with invalid radix", '\0');
                ::abort();
            }
        }

        // Copy --- WARN (Lapys) -> Ignores differing numeral systems.
        template <size_t radix> template <size_t base>
        inline void BigUnsignedInteger<radix>::copy(BigUnsignedInteger<base> const& number) {
            // Logic > ...
            if (BigUnsignedInteger::isZero(number)) BigUnsignedInteger::zero();
            else {
                // ...
                BigUnsignedInteger::allocate(number.length);

                // (Loop > )Modification > Target > ...
                for (this -> length = 0u; this -> length ^ number.length; ++(this -> length)) *(this -> value++) = *(number.value + this -> length);
                this -> value -= this -> length;
            }
        }

        // Decrement
        template <size_t radix>
        constexpr inline void BigUnsignedInteger<radix>::decrement(void) {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // Initialization > Iterator
                Digit *iterator = this -> value + (this -> length - 1u);

                // Loop > Update > Iterator ...
                while (Digit::isLowestRank(iterator -> value)) iterator-- -> value = radix - 1u;
                --(iterator -> value);

                // Logic
                if (Digit::isLowestRank(this -> value -> value)) {
                    // ...
                    iterator = this -> value;
                    BigUnsignedInteger::allocate(--(this -> length));

                    this -> value += this -> length;
                    while (this -> value != iterator) iterator -> value = (iterator + 1) -> value;
                    this -> value -= this -> length;
                }
            }
        }

        // Divide --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline void BigUnsignedInteger<radix>::divide(BigUnsignedInteger<base> const& number) {}

        // Exponentiate --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline void BigUnsignedInteger<radix>::exponentiate(BigUnsignedInteger<base> const& number) {}

        // From Base --- CHECKPOINT (Lapys)
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<radix> BigUnsignedInteger<radix>::fromBase(BigUnsignedInteger<base> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<radix> evaluation {};

            // Logic > ...
            if (base == radix) evaluation.copy(number);

            // Return
            return evaluation;
        }

        // From Number
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix> BigUnsignedInteger<radix>::fromNumber(primitive_t number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<radix> evaluation {};

            // (Loop > )Modification > Evaluation > Length
            for (primitive_t iterator = number; iterator; iterator /= radix) ++evaluation.length;

            // ...
            evaluation.allocate(evaluation.length);
            evaluation.value += evaluation.length;

            // (Loop > )Modification > Evaluation > Value
            while (number) { *--evaluation.value = number % radix; number /= radix; }

            // Return
            return evaluation;
        }

        // Get Maximum Length Size --- WARN (Lapys) -> Slight code re-use.
        template <size_t radix> constexpr inline unsigned char BigUnsignedInteger<radix>::getMaximumLengthSize(void) noexcept { unsigned char length = 0u, size = 0u; for (size_t iterator = SIZE_MAX / sizeof(Digit); iterator; iterator /= 10u) ++length; while (length) { length >>= 1u; ++size; } return size ? size : 1u; }

        // Increment
        template <size_t radix>
        constexpr inline void BigUnsignedInteger<radix>::increment(void) {
            // Logic
            if (BigUnsignedInteger::isZero()) {
                // Modification > Target > Value
                BigUnsignedInteger::allocate((this -> length = 1u));
                (this -> value) -> value = 1u;
            }

            else {
                // Initialization > Iterator
                Digit *iterator = this -> value + (this -> length - 1u);

                // Modification > Target > Value
                // : Loop > Update > Iterator
                --(this -> value);
                while (iterator != this -> value && Digit::isGreatestRank(iterator -> value)) iterator-- -> value = 0u;

                // Logic > Modification > Target > Value ... --- REDACT (Lapys)
                if (iterator == this -> value) {
                    (++(this -> value)) -> value = 1u;
                    BigUnsignedInteger::allocate(++(this -> length));
                    (this -> value + (this -> length - 1u)) -> value = 0u;
                } else { ++(iterator -> value); ++(this -> value); }
            }
        }

        // Is ...
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isComputable(void) const noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isFinite(void) const noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isInfinite(void) const noexcept { return false; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isNegative(void) const noexcept { return false; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isNonComputable(void) const noexcept { return false; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isOne(void) const noexcept { return NULL != this -> value && (this -> length == 1u && this -> value -> value == 1u); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isPositive(void) const noexcept { return true; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isSignificant(void) const noexcept { return /*0x0 != */this -> length + this -> value; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isZero(void) const noexcept { return 0x0 == this -> length + this -> value; }

        // Is Base Factor --- NOTE (Lapys) -> Assert the number is a power of its radix; For decimals that would be 10, 100, 1000, 10000... and so on.
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isBaseFactor(void) const noexcept {
            // Evaluation > Evaluation
            bool evaluation = true;

            // Loop > Logic > Update > Evaluation ...
            for (Digit *iterator = this -> value + this -> length; iterator != this -> value; --iterator)
            if (0u != iterator -> value) { evaluation = false; break; }

            // Return
            return evaluation && 1u == *(this -> value);
        }

        // Is Equal
        template <size_t radix> template <size_t base>
        constexpr bool BigUnsignedInteger<radix>::isEqual(BigUnsignedInteger<base> const& number) const noexcept {
            // Evaluation > Evaluation
            bool evaluation = true;

            // Logic > ... --- REDACT (Lapys)
            if (base == radix) {
                if (this -> length ^ number.length) evaluation = false;
                else {
                    for (length_t iterator = 0u; iterator ^ this -> length; ++iterator)
                    if ((this -> value + iterator) -> value ^ (number.value + iterator) -> value) {
                        evaluation = false;
                        break;
                    }
                }
            } else evaluation = BigUnsignedInteger::isEqual(BigUnsignedInteger::fromBase<base>(number));

            // Return
            return evaluation;
        }

        // Is Greater
        template <size_t radix> template <size_t base>
        constexpr bool BigUnsignedInteger<radix>::isGreater(BigUnsignedInteger<base> const& number) const noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            // Logic > ... --- REDACT (Lapys)
            if (base == radix) {
                if (this -> length > number.length) evaluation = true;
                else if (this -> length == number.length) {
                    for (length_t iterator = 0u; iterator ^ this -> length; ++iterator) {
                        digit_t const& digitA = (this -> value + iterator) -> value;
                        digit_t const& digitB = (number.value + iterator) -> value;

                        if (digitA > digitB) { evaluation = true; break; }
                        else if (digitA < digitB) { evaluation = false; break; }
                    }
                }
            } else evaluation = BigUnsignedInteger::isGreater(BigUnsignedInteger::fromBase<base>(number));

            // Return
            return evaluation;
        }

        // Is Lesser
        template <size_t radix> template <size_t base>
        constexpr bool BigUnsignedInteger<radix>::isLesser(BigUnsignedInteger<base> const& number) const noexcept {
            // Evaluation > Evaluation
            bool evaluation = false;

            // Logic > ... --- REDACT (Lapys)
            if (base == radix) {
                if (this -> length < number.length) evaluation = true;
                else if (this -> length == number.length) {
                    for (length_t iterator = 0u; iterator ^ this -> length; ++iterator) {
                        digit_t const& digitA = (this -> value + iterator) -> value;
                        digit_t const& digitB = (number.value + iterator) -> value;

                        if (digitA < digitB) { evaluation = true; break; }
                        else if (digitA > digitB) { evaluation = false; break; }
                    }
                }
            } else evaluation = BigUnsignedInteger::isGreater(BigUnsignedInteger::fromBase<base>(number));

            // Return
            return evaluation;
        }

        // Modulo --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline void BigUnsignedInteger<radix>::modulo(BigUnsignedInteger<base> const& number) {}

        // Move --- WARN (Lapys) -> Ignores differing numeral systems.
        template <size_t radix> template <size_t base>
        inline void BigUnsignedInteger<radix>::move(BigUnsignedInteger<base>&& number) {
            // Modification > (Target, Number) > ...
            this -> length = number.length;
            this -> value = number.value;

            number.length = 0u;
            number.value = NULL;
        }

        // Multiply --- CHECKPOINT (Lapys)
        // template <size_t radix> template <size_t base>
        // constexpr inline void BigUnsignedInteger<radix>::multiply(BigUnsignedInteger<base> const& number) {}

        // Subtract
        template <size_t radix> template <size_t base>
        constexpr inline void BigUnsignedInteger<radix>::subtract(BigUnsignedInteger<base> const& number) {
            // Logic > ...
            if (base ^ radix) BigUnsignedInteger::subtract(BigUnsignedInteger::fromBase<base>(number));
            else if (BigUnsignedInteger::isLesser(number)) BigUnsignedInteger::zero();
            else if (BigUnsignedInteger::isOne(number)) BigUnsignedInteger::decrement();
            else if (BigUnsignedInteger::isSignificant() && BigUnsignedInteger::isSignificant(number)) {
                // Initialization > Iterator (A, B)
                Digit *iteratorA = this -> value + this -> length;
                Digit /* const */*iteratorB = number.value + number.length;

                // Loop > Logic --- NOTE (Lapys) -> Per-digit subtraction loop.
                while (this -> value != iteratorA-- && number.value != iteratorB--)
                if (iteratorB -> value) { // NOTE (Lapys) -> Because carry operations are calculated per iteration, there is no need to iterate over the `0` digits of `number`.
                    // Logic
                    if (iteratorA -> value < iteratorB -> value) {
                        // Initialization > Iterator
                        Digit *iterator = iteratorA;

                        // (Loop > )Update > Iterator --- NOTE (Lapys) -> Completely calculate carry operations for this sub-operation.
                        iterator-- -> value += radix; // WARN (Lapys) -> By-passes upper limit set by `radix` value.
                        while (Digit::isLowestRank(iterator -> value)) iterator-- -> value = radix - 1u;
                        --(iterator -> value);
                    }

                    // Update > Iterator A
                    iteratorA -> value -= iteratorB -> value;
                }

                // Logic --- NOTE (Lapys) -> Remove leading zeroes.
                if (Digit::isLowestRank(this -> value -> value)) {
                    // ... Update > Iterator (A, B) --- NOTE (Lapys) -> Get number of leading zeroes.
                    iteratorA = this -> value + this -> length;
                    iteratorB = this -> value;
                    while (iteratorA != iteratorB && Digit::isLowestRank(iteratorB -> value)) ++iteratorB;

                    // ...
                    iteratorA = this -> value;
                    this -> length -= iteratorB - this -> value;
                    while (this -> length ^ (iteratorA - (this -> value))) iteratorA++ -> value = iteratorB++ -> value;

                    BigUnsignedInteger::allocate(this -> length);
                }
            }
        }

        // To Base --- CHECKPOINT (Lapys)
        template <size_t radix> template <size_t base>
        constexpr inline BigUnsignedInteger<base> BigUnsignedInteger<radix>::toBase(BigUnsignedInteger<radix> const& number) {
            // Evaluation > Evaluation
            BigUnsignedInteger<base> evaluation {};

            // Logic > ...
            if (base == radix) evaluation.copy(number);

            // Return
            return evaluation;
        }

        // To Number
        template <size_t radix>
        constexpr inline typename BigUnsignedInteger<radix>::primitive_t BigUnsignedInteger<radix>::toNumber(BigUnsignedInteger const& number) {
            // Initialization > (Evaluation, ...)
            primitive_t evaluation {0u};
            length_t exponent = 0u;

            // Loop
            for (Digit const *indexer = number.value + number.length; indexer-- != number.value; ++exponent) {
                // Initialization > Unit
                // : ...
                primitive_t unit = *indexer;
                for (length_t iterator = 0u; exponent ^ iterator; ++iterator) unit *= radix;

                // Update > Evaluation
                evaluation += unit;
            }

            // Return
            return evaluation;
        }

        // To String
        template <size_t radix>
        constexpr inline char* BigUnsignedInteger<radix>::toString(bool delimit) const {
            // Evaluation > Evaluation
            char *evaluation = NULL;

            // Logic
            if (BigUnsignedInteger::isZero()) {
                // Update > Evaluation
                evaluation = (char*) ::malloc(2u * sizeof(char));

                // Logic > ...
                if (NULL == evaluation) evaluation = (char*) "";
                else {
                    // Update > Evaluation
                    *evaluation = '0';
                    *(evaluation + 1) = '\0';
                }
            }

            else {
                // Update > Evaluation
                evaluation = (char*) ::malloc(((delimit ? this -> length * 2u : 0u) + this -> length + 1u) * sizeof(char));

                // Logic > ...
                if (NULL == evaluation) evaluation = (char*) "";
                else {
                    // Initialization > ...
                    // : Loop
                    char *iterator = evaluation;
                    unsigned char length = 0u;

                    for (Digit *indexer = this -> value; (indexer - this -> value) ^ this -> length; ++indexer) {
                        // Logic
                        if (delimit) { // NOTE (Lapys) -> Parse each digit as bracket (`[]`) delimited denary.
                            // Logic
                            if (0u == indexer -> value) {
                                // Update > Iterator
                                *(iterator++) = '[';
                                *(iterator++) = '0';
                                *(iterator++) = ']';
                            }

                            else {
                                // Initialization > Current Length ...
                                unsigned char currentLength = 0u;
                                for (digit_t iterator = indexer -> value; iterator; iterator /= 10u) ++currentLength;

                                // Logic
                                if (currentLength > length) { // NOTE (Lapys) -> Acquire additional memory for `evaluation`.
                                    // Constant > Current Iterator
                                    int const currentIterator = iterator - evaluation;

                                    // Update > Evaluation
                                    evaluation = (char*) ::realloc(evaluation, ((this -> length * 2u) + (this -> length * currentLength) + 1u) * sizeof(char));

                                    // Logic --- NOTE (Lapys) -> Repeat the current iteration or terminate the loop.
                                    if (NULL == evaluation) { evaluation = (char*) ""; break; }
                                    else { --indexer; iterator = evaluation + currentIterator; length = currentLength; }
                                }

                                else {
                                    // (Loop > )Update > Iterator
                                    *(iterator++) = '[';
                                    for (digit_t subiterator = indexer -> value; subiterator; subiterator /= 10u) *(iterator++) = *("0123456789" + (subiterator % 10u));
                                    *(iterator++) = ']';
                                }
                            }
                        }

                        else { // NOTE (Lapys) -> Parse each digit as denary or uppercase alphabet.
                            // Logic
                            if (indexer -> value > 35u) {
                                // (Loop > )Update > (Length, Evaluation)
                                for (digit_t iterator = indexer -> value; iterator; iterator /= radix) ++length;
                                evaluation = (char*) ::realloc(evaluation, ((this -> length * 2u) + (this -> length * length) + 1u) * sizeof(char));

                                // Logic --- NOTE (Lapys) -> "Reset" or terminate the loop.
                                if (NULL == evaluation) { evaluation = (char*) ""; break; }
                                else { delimit = true; indexer = this -> value - 1; iterator = evaluation; }
                            }

                            else
                                // Update > Iterator
                                *(iterator++) = *("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" + (indexer -> value));
                        }
                    }

                    // Update > Iterator
                    *iterator = '\0';
                }
            }

            // Return
            return evaluation;
        }

        // Zero
        template <size_t radix> constexpr inline void BigUnsignedInteger<radix>::zero(void) noexcept { this -> length = 0u; ::free(this -> value); this -> value = NULL; }

    /* Big Signed Integer */
    /* Big Float */
    /* Digit */
        // Add --- REDACT (Lapys)
        template <size_t radix>
        inline typename BigUnsignedInteger<radix>::Digit* BigUnsignedInteger<radix>::Digit::add(Digit const& digitA, Digit const& digitB) noexcept {
            static Digit evaluation[2] {0u, 0u};

            if (Digit::isGreaterRank(digitA) || Digit::isMeanRank(digitA)) {
                if (Digit::isGreaterRank(digitB) || Digit::isMeanRank(digitB)) { evaluation -> value = 1u; (evaluation + 1) -> value = digitA.value - (radix - digitB.value); }
                else (evaluation + 1) -> value = (evaluation -> value = digitA.value >= radix - digitB.value) ? digitA.value - (radix - digitB.value) : digitA.value + digitB.value;
            }
            else if (Digit::isGreaterRank(digitB) || Digit::isMeanRank(digitB)) {
                if (Digit::isGreaterRank(digitA) || Digit::isMeanRank(digitA)) { evaluation -> value = 1u; (evaluation + 1) -> value = digitA.value - (radix - digitB.value); }
                else (evaluation + 1) -> value = (evaluation -> value = digitB.value >= radix - digitA.value) ? digitB.value - (radix - digitA.value) : digitA.value + digitB.value;
            }
            else { evaluation -> value = 0u; (evaluation + 1) -> value = digitA.value + digitB.value; }

            return evaluation;
        }

        // Is ... --- REDACT (Lapys)
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::Digit::isGreaterRank(digit_t const value) noexcept { return value > (radix & 1u) + (radix / 2u); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::Digit::isGreatestRank(digit_t const value) noexcept { return radix - 1u == value; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::Digit::isLowerRank(digit_t const value) noexcept { return value < (radix & 1u) + (radix / 2u); }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::Digit::isLowestRank(digit_t const value) noexcept { return 0u == value; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::Digit::isMeanRank(digit_t const value) noexcept { return value == (radix & 1u) + (radix / 2u); }

        // Multiply --- REDACT (Lapys)
        template <size_t radix>
        inline typename BigUnsignedInteger<radix>::Digit* BigUnsignedInteger<radix>::Digit::multiply(Digit const& digitA, Digit const& digitB) noexcept {
            static Digit evaluation[2] {0u, 0u};

            evaluation -> value = 0u;
            (evaluation + 1) -> value = 0u;

            for (digit_t iteratorA = 0u; digitA.value ^ iteratorA; ++iteratorA)
            for (digit_t iteratorB = 0u; digitB.value ^ iteratorB; ++iteratorB) {
                if (Digit::isGreatestRank((evaluation + 1) -> value)) { ++(evaluation -> value); (evaluation + 1) -> value = 0u; }
                else ++((evaluation + 1) -> value);
            }

            return evaluation;
        }

        // To String --- REDACT (Lapys)
        template <size_t radix>
        inline char* BigUnsignedInteger<radix>::Digit::toString(void) const noexcept {
            static char evaluation[Digit::getLength(radix) + (false == Digit::isDenary(radix))] {0};

            if (0u == this -> value) { *evaluation = '0'; *(evaluation + 1) = '\0'; }
            else { char *indexer = evaluation; for (digit_t iterator = this -> value; iterator; (++indexer, iterator /= 10u)) *indexer = *("0123456789" + (iterator % 10u)); *indexer-- = '\0'; for (char *subindexer = evaluation; indexer > subindexer; (--indexer, ++subindexer)) { *indexer ^= *subindexer; *subindexer ^= *indexer; *indexer ^= *subindexer; } }

            return evaluation;
        }

        /* ...
            : Align --- NOTE (Lapys) -> Correct arithmetic radix overflows due to size alignment.

            : Get Length --- NOTE (Lapys) -> Determine the length of the numeric value.
            : Get Size --- NOTE (Lapys) -> Determine how much memory (on the stack) is used per `Digit`.

            : Is Denary
        */
        template <size_t radix> constexpr inline typename BigUnsignedInteger<radix>::Digit::digit_t BigUnsignedInteger<radix>::Digit::align(digit_t const value) noexcept { return value < radix ? value : value - radix; }

        template <size_t radix> constexpr inline unsigned char BigUnsignedInteger<radix>::Digit::getLength(size_t value) noexcept { unsigned char length = 0u; while (value) { ++length; value /= 10u; } return length; }
        template <size_t radix> constexpr inline unsigned char BigUnsignedInteger<radix>::Digit::getSize(size_t value) noexcept { unsigned char size = 0u; while (value) { ++size; value >>= 1u; } return size ? size : 1u; }

        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::Digit::isDenary(digit_t value) noexcept { while (value) { if (value == 1u) return true; else if (value % 10u) return false; else value /= 10u; } return false; }

/* Main */
int main(void) {
    /* [Begin] ... */
    ::println("[PROGRAM INITIATED]");

    /* .... */ {
        // for (unsigned char iterator = 0u; iterator ^ 40u; ++iterator) {
        //     unsigned const numberA = ::randbool() ? 0u : ::randint(1e5);
        //     unsigned const numberB = ::randbool() && ::randbool() ? numberA : ::randint(1e3);

        //     BigUnsignedInteger<10> const bigNumberA = numberA;
        //     BigUnsignedInteger<10> const bigNumberB = numberB;

        //     ::println('[', bigNumberA.toString(), " (", numberA, ") + ", bigNumberB.toString(), " (", numberB, ")]: ", BigUnsignedInteger<10>::add(bigNumberA, bigNumberB).toString(), " (", numberA + numberB, ')');
        // }
    }

    /* [End] ... */
    ::print(println, "[PROGRAM TERMINATED]");

    // Return
    return EXIT_SUCCESS;
}
