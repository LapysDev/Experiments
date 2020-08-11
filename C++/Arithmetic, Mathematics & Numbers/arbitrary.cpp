#include <iostream>
/* Import */
#include <float.h> // Floating-Points
#include <limits.h> // Limits
#include <math.h> // Mathematics
#include <stdio.h> // Standard Input/ Output
#include <stdint.h> // Standard Integer
#include <stdlib.h> // Standard Library

/* Definition > ... */
template <size_t radix> class BigFloat;
template <size_t radix> class BigNumber;
template <size_t radix> class BigSignedInteger;
template <size_t radix> class BigUnsignedInteger;

typedef BigFloat<10u> big_float;
typedef BigSignedInteger<10u> big_int;
typedef BigUnsignedInteger<10u> big_uint;

/* Class */
    /* Big Number */
    template <size_t radix>
    class BigNumber {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigNumber;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef size_t length_t;

        // [...]
        protected:
            /* Definition > (Digit) (Buffer, Iterator) */
            class Digit; // NOTE (Lapys) -> Atomic unit of store.
            class DigitBuffer; // NOTE (Lapys) -> Persistent heap allocation of `BigNumber::Digit`.
            class DigitIterator; // NOTE (Lapys) -> For iterating each atomic unit of `BigNumber` or `primitive_t`.

        // [...]
        private:
            // Definition > Buffer --- NOTE (Lapys) -> Frees heap allocation of `DigitBuffer` interface.
            static class SmartDigitBuffer final : DigitBuffer { ~SmartDigitBuffer(void) { DigitBuffer::free(); } } const buffer;

            // [Constructor]
            constexpr inline BigNumber(void);

            // Declaration > (Allocate, Assert, Free)
            static void* allocate(Digit* const, length_t const);
            constexpr void assert(void);
            static void free(Digit* const) noexcept;

            // Function > Is (Significant, Zero)
            inline virtual bool isSignificant(void) const noexcept { return false; }
            constexpr inline static bool isSignificant(BigNumber const& number) noexcept { return number.isSignificant(); }

            inline virtual bool isZero(void) const noexcept { return false; }
            constexpr inline static bool isZero(BigNumber const& number) noexcept { return number.isZero(); }
    };

    /* Big Unsigned Integer */
    template <size_t radix>
    class BigUnsignedInteger : public BigNumber<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigNumber;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef typename BigNumber<radix>::Digit Digit;
        typedef typename BigNumber<radix>::DigitBuffer DigitBuffer;
        /*typedef */class DigitIterator/* DigitIterator*/;

        typedef typename BigNumber<radix>::length_t length_t;
        #if defined(__cplusplus) && (__cplusplus == 201103L)
            typedef unsigned long long primitive_t;
        #else
            typedef unsigned long primitive_t;
        #endif

        // [...]
        protected:
            // Declaration
            // : Add, Decrement, Increment, Is ..., Subtract, Zero
            void add(DigitIterator const&, bool const);
            void decrement(bool const) noexcept;
            void increment(bool const);

            constexpr bool isEqual(DigitIterator const&) const noexcept;
            constexpr bool isGreater(DigitIterator const&) const noexcept;
            constexpr bool isLesser(DigitIterator const&) const noexcept;

            void subtract(DigitIterator const&, bool const);
            void zero(bool const = true);

            // : From Primitive
            static void fromPrimitive(BigUnsignedInteger* const, primitive_t const, bool const = true);

        // [...]
        private:
            // Definition > (Length, Value)
            length_t length;
            Digit *value;

            // Function --- MINIFY (Lapys)
            // : Allocate, Free
            inline void allocate(length_t const length) { if (length) { this -> value = (Digit*) BigNumber<radix>::allocate(this -> value, length); } else BigUnsignedInteger::free(); }
            inline void free(void) noexcept { BigNumber<radix>::free(this -> value); this -> value = NULL; }

            // : Copy, Move
            inline void copy(BigUnsignedInteger const& number, bool const manageMemory = true) { if (manageMemory) BigUnsignedInteger::allocate((this -> length = number.length)); else { this -> length = number.length; } for (length_t iterator = 0u; iterator ^ number.length; ++iterator) (this -> value + iterator) -> value = (number.value + iterator) -> value; }
            constexpr inline void move(BigUnsignedInteger& number) noexcept { this -> length = number.length; this -> value = number.value; number.length = 0u; number.value = NULL; }

        // [...]
        public:
            // [Constructor]
            BigUnsignedInteger(void);
            BigUnsignedInteger(primitive_t const);
            BigUnsignedInteger(BigUnsignedInteger const&);
            constexpr BigUnsignedInteger(BigUnsignedInteger&&);

            // Function > ...
            inline void add(primitive_t number) { BigUnsignedInteger::add(&number, true); }
            inline void add(BigUnsignedInteger const& number) { BigUnsignedInteger::add(&number, true); }

            inline void decrement(void) noexcept { BigUnsignedInteger::decrement(true); }
            inline static BigUnsignedInteger decrement(BigUnsignedInteger const& number) noexcept { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.decrement(); return evaluation; }

            inline static BigUnsignedInteger fromPrimitive(primitive_t const number) { BigUnsignedInteger evaluation {}; BigUnsignedInteger::fromPrimitive(&evaluation, number, true); return evaluation; }

            inline void increment(void) { BigUnsignedInteger::increment(true); }
            inline static BigUnsignedInteger increment(BigUnsignedInteger const& number) noexcept { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }

            inline bool isEqual(primitive_t number) { return BigUnsignedInteger::isEqual(&number); }
            inline bool isEqual(BigUnsignedInteger const& number) { return BigUnsignedInteger::isEqual(&number); }
            inline bool isGreater(primitive_t number) { return BigUnsignedInteger::isGreater(&number); }
            inline bool isGreater(BigUnsignedInteger const& number) { return BigUnsignedInteger::isGreater(&number); }
            inline bool isLesser(primitive_t number) { return BigUnsignedInteger::isLesser(&number); }
            inline bool isLesser(BigUnsignedInteger const& number) { return BigUnsignedInteger::isLesser(&number); }
            constexpr bool isSignificant(void) const noexcept override;
            constexpr bool isZero(void) const noexcept override;

            inline void subtract(primitive_t number) { BigUnsignedInteger::subtract(&number, true); }
            inline void subtract(BigUnsignedInteger const& number) { BigUnsignedInteger::subtract(&number, true); }

            char* toString(bool = false) const;
            inline void zero(void) { BigUnsignedInteger::zero(true); }
    };

    /* Big Signed Integer */
    template <size_t radix>
    class BigSignedInteger : public BigUnsignedInteger<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigNumber;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef typename BigUnsignedInteger<radix>::Digit Digit;
        typedef typename BigUnsignedInteger<radix>::DigitBuffer DigitBuffer;
        /*typedef */class DigitIterator/* DigitIterator*/;

        typedef typename BigUnsignedInteger<radix>::length_t length_t;
        #if defined(__cplusplus) && (__cplusplus == 201103L)
            typedef signed long long primitive_t;
        #else
            typedef signed long primitive_t;
        #endif

        // [...]
        private:
            // Definition > Signedness
            bool signedness;
    };

    /* Big Float */
    template <size_t radix>
    class BigFloat final : public BigSignedInteger<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigNumber;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef typename BigSignedInteger<radix>::Digit Digit;
        typedef typename BigSignedInteger<radix>::DigitBuffer DigitBuffer;
        /*typedef */class DigitIterator/* DigitIterator*/;

        typedef typename BigSignedInteger<radix>::length_t length_t;
        typedef long double primitive_t;

        // [...]
        private:
            // Definition > (Mantissa Length, State)
            length_t mantissaLength;
            enum BigFloatState {DENORMALIZED, INFINITE, SAFE, UNCOMPUTABLE} state : 2;
    };

/* Class */
    /* Digit --- NOTE (Lapys) -> Denary-based value. */
    template <size_t radix>
    class BigNumber<radix>::Digit final {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigNumber;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;
        typedef size_t digit_t;

        // [...]
        public:
            // [Constructor]
            constexpr inline Digit(digit_t const value) : value{value} {}

            // Function > (Add, Get Size, Is ...) --- MINIFY (Lapys)
            inline static Digit* add(digit_t const digitA, digit_t const digitB) noexcept { static Digit evaluation[2] = {0u, 0u}; if (Digit::isGreaterRank(digitA) || Digit::isMeanRank(digitA)) (evaluation + 1) -> value = (evaluation -> value = digitA >= radix - digitB || (Digit::isGreaterRank(digitB) || Digit::isMeanRank(digitB))) ? digitA - (radix - digitB) : digitA + digitB; else if (Digit::isGreaterRank(digitB) || Digit::isMeanRank(digitB)) Digit::add(digitB, digitA); else { evaluation -> value = 0u; (evaluation + 1) -> value = digitA + digitB; } return &*evaluation; }
            constexpr inline static unsigned char getSize(size_t number) noexcept { unsigned char size = 0u; while (number) { number >>= 1u; ++size; } return size ? size : 1u; }

            constexpr inline static bool isGreaterRank(digit_t const digit) noexcept { return digit > (radix >> 1u); }
            constexpr inline static bool isGreatestRank(digit_t const digit) noexcept { return digit == radix - 1u; }
            constexpr inline static bool isMeanRank(digit_t const digit) noexcept { return digit == (radix >> 1u); }
            constexpr inline static bool isLowerRank(digit_t const digit) noexcept { return digit < (radix >> 1u); }
            constexpr inline static bool isLowestRank(digit_t const digit) noexcept { return 0u == digit; }

        // [...] Definition > Value
        private: digit_t value : Digit::getSize(radix);
    };

    /* Digit Buffer */
    template <size_t radix>
    class BigNumber<radix>::DigitBuffer {
        // [...]
        private:
            // Definition > (Length, Value)
            static length_t length;
            static Digit *value;

        public:
            // [Constructor]
            inline DigitBuffer(length_t const length = radix) { DigitBuffer::allocate(length); }

            // Function > (Allocate, Free) --- MINIFY (Lapys)
            inline void allocate(length_t const length) const { if (length && DigitBuffer::length < length) { DigitBuffer::length = length; DigitBuffer::value = (Digit*) BigNumber::allocate(DigitBuffer::value, length); } }
            inline void free(void) const noexcept { BigNumber::free(DigitBuffer::value); DigitBuffer::value = NULL; }

            // [Operator] > [...]
            constexpr inline operator Digit*(void) const noexcept { return DigitBuffer::value; }
    };

    /* Digit Iterator */
    template <size_t radix>
    class BigNumber<radix>::DigitIterator {
        /* ... */
        template <size_t subradix> friend class BigUnsignedInteger<subradix>::DigitIterator;

        // [...]
        private:
            // Definition > (Data, Type)
            static void const *data;
            static enum type_t {BIG, PRIMITIVE} type;

        // [...]
        public:
            // [Constructor]
            constexpr inline DigitIterator(void) {}
            constexpr inline DigitIterator(BigNumber const* const number) {
                // Modification > Digit Iterator > (Data, Type)
                DigitIterator::data = BigNumber::isZero(*number) ? NULL : number;
                DigitIterator::type = DigitIterator::BIG;
            }

            // Function > (Is, To) (Big Number, Primitive)
            constexpr inline bool isBigNumber(void) const noexcept { return DigitIterator::BIG == DigitIterator::type; }
            constexpr inline bool isPrimitive(void) const noexcept { return DigitIterator::PRIMITIVE == DigitIterator::type; }

            constexpr inline BigNumber& toBigNumber(BigNumber* const evaluation) const noexcept { return *evaluation; }
            constexpr inline void* toPrimitive(...) const noexcept = delete;
    };

    template <size_t radix>
    class BigUnsignedInteger<radix>::DigitIterator : public BigNumber<radix>::DigitIterator {
        private: static BigUnsignedInteger::Digit *metadata;
        public:
            // [Constructor]
            constexpr inline DigitIterator(BigUnsignedInteger const* const number) : BigNumber<radix>::DigitIterator((BigNumber<radix> const* const) number) { DigitIterator::metadata = number -> value + number -> length; }
            constexpr inline DigitIterator(primitive_t* const number) : BigNumber<radix>::DigitIterator() { DigitIterator::data = 0 == *number ? NULL : number; DigitIterator::type = DigitIterator::PRIMITIVE; }

            // Function > (Count, Done, Next, To ...) --- REDACT (Lapys)
            constexpr inline length_t count(void) const noexcept {
                if (NULL != DigitIterator::data)
                switch (DigitIterator::type) {
                    case DigitIterator::BIG: return ((BigUnsignedInteger const*) DigitIterator::data) -> length;
                    case DigitIterator::PRIMITIVE: { length_t evaluation = 0u; for (primitive_t iterator = *((primitive_t*) DigitIterator::data); iterator; iterator /= radix) ++evaluation; return evaluation; }
                }

                return 0u;
            }

            constexpr inline bool done(void) const noexcept {
                if (NULL != DigitIterator::data)
                switch (DigitIterator::type) {
                    case DigitIterator::BIG: return DigitIterator::metadata == ((BigUnsignedInteger const*) DigitIterator::data) -> value;
                    case DigitIterator::PRIMITIVE: return 0u == *((primitive_t*) DigitIterator::data);
                }

                return true;
            }

            inline Digit& next(void) const noexcept {
                if (NULL != DigitIterator::data)
                switch (DigitIterator::type) {
                    case DigitIterator::BIG: return *--DigitIterator::metadata;
                    case DigitIterator::PRIMITIVE: { static Digit evaluation = {0u}; evaluation = *((primitive_t*) DigitIterator::data) % radix; *((primitive_t*) DigitIterator::data) /= radix; return evaluation; }
                }

                return (Digit&) *((Digit*) NULL);
            }

            inline BigUnsignedInteger& toBigUnsignedInteger(BigUnsignedInteger* const evaluation, bool const manageMemory = true) const noexcept {
                if (NULL != DigitIterator::data)
                switch (DigitIterator::type) {
                    case DigitIterator::BIG: evaluation -> copy(*(BigUnsignedInteger const*) DigitIterator::data, manageMemory); break;
                    case DigitIterator::PRIMITIVE: evaluation -> fromPrimitive(evaluation, *(primitive_t*) DigitIterator::data, manageMemory);
                }

                return *evaluation;
            }
    };

    template <size_t radix> class BigSignedInteger<radix>::DigitIterator : public BigUnsignedInteger<radix>::DigitIterator { constexpr inline BigSignedInteger& toBigSignedInteger(BigSignedInteger* const evaluation) const noexcept { return *evaluation; } };
    template <size_t radix> class BigFloat<radix>::DigitIterator final : public BigSignedInteger<radix>::DigitIterator { constexpr inline BigFloat& toBigFloat(BigFloat* const evaluation) const noexcept { return *evaluation; } };

/* Modification */
    // Big Number > Buffer
    template <size_t radix> typename BigNumber<radix>::SmartDigitBuffer const BigNumber<radix>::buffer = {};

    // Digit Buffer > ...
    template <size_t radix> typename BigNumber<radix>::length_t BigNumber<radix>::DigitBuffer::length = 0u;
    template <size_t radix> typename BigNumber<radix>::Digit *BigNumber<radix>::DigitBuffer::value = NULL;

    template <size_t radix> typename BigNumber<radix>::Digit *BigUnsignedInteger<radix>::DigitIterator::metadata = NULL;

    // Digit Iterator > (Data, Type)
    template <size_t radix> void const *BigNumber<radix>::DigitIterator::data = NULL;
    template <size_t radix> typename BigNumber<radix>::DigitIterator::type_t BigNumber<radix>::DigitIterator::type = {};

/* Modification */
    /* Big Number */
        // [Constructor]
        template <size_t radix>
        constexpr inline BigNumber<radix>::BigNumber(void) { BigNumber::assert(); }

        /* Allocate --- NOTE (Lapys) -> Request sufficient memory for storing `Digit` instances. --- REDACT (Lapys)
            --- CONSIDER (Lapys) -> Internally construct a region of memory instead of instantiating a set of `Digit` objects unto heap memory.
        */
        template <size_t radix>
        inline void* BigNumber<radix>::allocate(Digit* const buffer, length_t const length) {
            // Logic > ... --- REDACT (Lapys)
            if (length > SIZE_MAX / sizeof(Digit)) { ::puts("\r[Error]: Attempt to allocate excess memory for `Digit` instances"); ::abort(); }
            else {
                void *const allocation = NULL == buffer ? ::malloc(length * sizeof(Digit)) : ::realloc(buffer, length * sizeof(Digit));
                if (NULL == allocation) { ::puts("\r[Error]: Unable to allocate memory for additional `Digit` instances"); ::abort(); }

                return allocation;
            }

            // Return
            return NULL;
        }

        // Assert
        template <size_t radix>
        constexpr inline void BigNumber<radix>::assert(void) {
            // Logic > Error
            if (0u == radix || 1u == radix || SIZE_MAX == radix) {
                ::puts("\r[Error]: Attempt to instantiate `BigNumber` with non-representable radix");
                ::abort();
            }
        }

        // Free
        template <size_t radix>
        inline void BigNumber<radix>::free(Digit* const buffer) noexcept { ::free(buffer); }

    /* Big Unsigned Integer */
        // [Constructor]
        template <size_t radix> inline BigUnsignedInteger<radix>::BigUnsignedInteger(void) : BigNumber<radix>(), length{0u}, value{NULL} {}
        template <size_t radix> inline BigUnsignedInteger<radix>::BigUnsignedInteger(primitive_t const number) : BigNumber<radix>(), length{0u}, value{NULL} { BigUnsignedInteger::fromPrimitive(this, number); }
        template <size_t radix> inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigUnsignedInteger const& number) : BigNumber<radix>(), length{0u}, value{NULL} { BigUnsignedInteger::copy(number); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigUnsignedInteger&& number) : BigNumber<radix>(), length{0u}, value{NULL} { BigUnsignedInteger::move(number); }

        // Add
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::add(DigitIterator const& number, bool const manageMemory) {
            // Logic > ...
            if (BigUnsignedInteger::isZero()) number.toBigUnsignedInteger(this, manageMemory);
            else if (false == number.done()) {
                // Initialization > (Iterator, Length, Sub-Addition)
                Digit *iterator;
                length_t length = number.count();
                Digit *subaddition = NULL;

                // Logic --- EXAMPLE (Lapys) -> `7 + 69` -> `07 + 69`.
                if (length > this -> length) {
                    // Logic > ...
                    if (manageMemory) BigUnsignedInteger::allocate(length);

                    // : ... Update > Iterator;
                    // : Modification > Target > (Length, Value)
                    iterator = this -> value + length;
                    this -> value += this -> length;

                    while ((this -> length)--) (--iterator) -> value = (--(this -> value)) -> value;
                    while (iterator-- != this -> value) iterator -> value = 0u;

                    this -> length = length;
                }

                // Update > (Iterator, Length) --- NOTE (Lapys) -> `length` is used as a dummy variable to store the carry from this point.
                iterator = this -> value + (this -> length - 1u);
                length = 0u;

                // Loop --- NOTE (Lapys) -> Per-digit addition.
                while (true) {
                    // Update > Sub-Addition
                    // : ... Update > Length --- NOTE (Lapys) -> Update the resultant and the carry.
                    subaddition = Digit::add(iterator -> value, number.next().value);

                    if (length && radix == ++((subaddition + 1) -> value)) { subaddition -> value = 1u; (subaddition + 1) -> value = 0u; }
                    length = subaddition -> value;

                    // Update > Iterator --- NOTE (Lapys) -> Set the current digit value.
                    iterator -> value = (subaddition + 1) -> value;

                    // Logic > (Terminate | Continue)
                    if (number.done()) break;
                    else --iterator;
                }

                // Loop --- NOTE (Lapys) -> Continue per-digit addition if there's a carry.
                while (length && iterator-- != this -> value) {
                    // ... --- EXAMPLE (Lapys) -> `99 + 1` -> `...00`.
                    if ((length = (radix == ++(iterator -> value))))
                    iterator -> value = 0u;
                }

                // Logic --- EXAMPLE (Lapys) -> `99 + 1` -> ... -> `100`.
                if (length /* -> false == Digit::isLowestRank(length) */ && ++iterator == this -> value) {
                    // Logic > ...
                    ++(this -> length);
                    if (manageMemory) BigUnsignedInteger::allocate(this -> length);

                    // ... Update > Iterator --- NOTE (Lapys) -> Would've otherwise shifted `iterator` forwards by `this -> length` (`iterator += this -> length`) but `...::allocate(...)` may parse `this -> value` to a new address location.
                    iterator = this -> value + this -> length;
                    while (--iterator != this -> value) iterator -> value = (iterator - 1) -> value;

                    iterator -> value = length; // EXAMPLE (Lapys) -> `...00` -> `100`.
                }
            }
        }

        // Decrement
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::decrement(bool const manageMemory) noexcept {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // Initialization > Iterator
                Digit *iterator = this -> value + this -> length;

                // Loop > Update > Iterator
                while (Digit::isLowestRank((--iterator) -> value))
                iterator -> value = radix - 1u;

                // Logic --- NOTE (Lapys) -> Shrink the `BigNumber` instance.
                if (Digit::isLowestRank(--(iterator -> value)) && iterator == this -> value) {
                    // Loop > Update > Iterator
                    for (Digit const *const end = iterator + --(this -> length); end != iterator; ++iterator)
                    iterator -> value = (iterator + 1) -> value;

                    // Logic > ...
                    if (manageMemory)
                    BigUnsignedInteger::allocate(this -> length);
                }
            }
        }

        // From Primitive
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::fromPrimitive(BigUnsignedInteger* const evaluation, primitive_t const number, bool const manageMemory) {
            // Logic > ...
            if (number) {
                // Initialization > (Iterator, Length)
                primitive_t iterator;
                unsigned char length = 0u;

                // Loop > Update > Length --- NOTE (Lapys) -> Get the characteristic `length` of the `number`.
                for (iterator = number; iterator; iterator /= radix) ++length;

                // Logic > Modification > Evaluation > Length --- NOTE (Lapys) -> Modify the `evaluation` `length` to use as an indexer.
                if (manageMemory) evaluation -> allocate((evaluation -> length = length));
                else evaluation -> length = length;

                // Loop > Modification > Evaluation > (Length, Value)
                for (iterator = number; iterator; iterator /= radix)
                *(evaluation -> value + --(evaluation -> length)) = iterator % radix;

                evaluation -> length = length; // NOTE (Lapys) -> Reset the `length` to the correct value.
            } else evaluation -> zero(manageMemory);
        }

        // Increment
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::increment(bool const manageMemory) {
            // Logic
            if (BigUnsignedInteger::isZero()) {
                // Modification > Target > (Length, Value)
                BigUnsignedInteger::allocate((this -> length = 1u));
                this -> value -> value = 1u;
            }

            else {
                // Initialization > Iterator
                Digit *iterator = this -> value + this -> length;

                // Loop > Update > Iterator
                while (Digit::isGreatestRank((--iterator) -> value))
                iterator -> value = 0u;

                // Logic > ...
                if (iterator == this -> value - 1) { // NOTE (Lapys) -> Expand the `BigNumber` instance.
                    // ... Update > Iterator; Modification > Target > ...
                    iterator = this -> value + ++(this -> length);
                    if (manageMemory) BigUnsignedInteger::allocate(this -> length);

                    while (--iterator != this -> value - 1) iterator -> value = (iterator - 1) -> value;
                    this -> value -> value = 1u;
                } else ++(iterator -> value);
            }
        }

        // Is ... --- MINIFY (Lapys)
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isSignificant(void) const noexcept { return this -> length; }
        template <size_t radix> constexpr inline bool BigUnsignedInteger<radix>::isZero(void) const noexcept { return 0u == this -> length; }

        // Is Equal
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isEqual(DigitIterator const& number) const noexcept {
            // Logic > ...
            if (BigUnsignedInteger::isZero()) return number.done();
            else if (number.isBigNumber() && (this -> length ^ number.count())) return false;
            else { Digit *iterator = this -> value + this -> length; while (--iterator, true) {
                // Logic > Return
                // : NOTE (Lapys) -> Are they of equal length?
                if (iterator == this -> value - 1) return number.done();
                else if (number.done()) return iterator == this -> value - 1;

                // : NOTE (Lapys) -> Are the digits the same?
                if (iterator -> value ^ number.next().value) return false;
            } }

            // Return
            return false;
        }

        // Is Greater
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isGreater(DigitIterator const& number) const noexcept {
            // Initialization > ...
            length_t value = number.count();

            // Logic > ...
            if (BigUnsignedInteger::isZero()) return false == number.done();
            else if (this -> length ^ value) return this -> length > value;
            else { Digit *iterator = this -> value + this -> length; while (--iterator, true) {
                // Logic > Return
                if (iterator == this -> value - 1) return false;
                else if (number.done()) return iterator != this -> value - 1;
                else if (iterator -> value ^ (value = number.next().value)) return iterator -> value > value;
            } }

            // Return
            return false;
        }

        // Is Lesser
        template <size_t radix>
        constexpr inline bool BigUnsignedInteger<radix>::isLesser(DigitIterator const& number) const noexcept {
            // Initialization > ...
            length_t value = number.count();

            // Logic > ...
            if (BigUnsignedInteger::isZero()) return false == number.done();
            else if (this -> length ^ value) return this -> length < value;
            else { Digit *iterator = this -> value + this -> length; while (--iterator, true) {
                // Logic > Return
                if (iterator == this -> value - 1) return false == number.done();
                else if (number.done()) return iterator != this -> value - 1;
                else if (iterator -> value ^ (value = number.next().value)) return iterator -> value < value;
            } }

            // Return
            return false;
        }

        // Subtract --- CHECKPOINT (Lapys)
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::subtract(DigitIterator const& number, bool const manageMemory) {
            // Logic > ...
            if (BigUnsignedInteger::isLesser(number)) BigUnsignedInteger::zero(manageMemory);
            else if (BigUnsignedInteger::isSignificant()) {}
        }

        /* To String
                --- CONSIDER (Lapys) -> Request memory regions instead to dynamically handle varying sizes of each `Digit` in denary form.
                --- WARN (Lapys) -> Returns statically qualified data allocated on heap memory.
        */
        template <size_t radix>
        inline char* BigUnsignedInteger<radix>::toString(bool delimit) const {
            // Evaluation > Evaluation
            static char *evaluation = NULL;

            // Logic
            if (BigUnsignedInteger::isZero()) {
                // Deletion; Update > Evaluation
                ::free(evaluation);
                evaluation = (char*) ::calloc(2u * (delimit + 1u), sizeof(char));

                // Logic > ...
                if (NULL == evaluation) { ::puts("\r[Error]: Unable to represent `BigNumber` instance in string form (`char*`) due to insufficient memory"); ::abort(); }
                else { *(evaluation + delimit) = '0'; if (delimit) { *evaluation = '['; *(evaluation + 2) = ']'; } }
            }

            else {
                // Update > Evaluation
                // : Logic
                evaluation = (char*) (NULL == evaluation ?
                    ::malloc(((this -> length * (1u + (delimit * 2u))) + 1u) * sizeof(char)) :
                    ::realloc(evaluation, ((this -> length * (1u + (delimit * 2u))) + 1u) * sizeof(char))
                );
                if (NULL == evaluation) {
                    // Error
                    ::puts("\r[Error]: Unable to represent `BigNumber` instance in string form (`char*`) due to insufficient memory");
                    ::abort();
                }

                // Initialization > ...
                char *iterator = evaluation;
                unsigned char currentDigitLength = 0u;
                unsigned char recentDigitLength = 0u;

                // Definition > ...; Loop
                for (Digit *end = this -> value + this -> length, *start = this -> value; end != start; ++start) {
                    // Logic
                    if (delimit) {
                        // ... Update > Current Digit Length
                        currentDigitLength = 0u;
                        for (typename Digit::digit_t subiterator = start -> value; subiterator; subiterator /= radix) ++currentDigitLength;

                        // Logic --- NOTE (Lapys) -> Allocate more needed characters in memory for the string evaluation.
                        if (currentDigitLength > recentDigitLength) {
                            // Constant > Allocation
                            void *const allocation = ::realloc(evaluation, ((this -> length * 2u) + recentDigitLength + 1u) * sizeof(char));

                            // Logic
                            if (NULL == allocation) {
                                // Error
                                ::puts("\r[Error]: Unable to represent `BigNumber` instance in string form (`char*`) due to insufficient memory");
                                ::abort();
                            }

                            // Update > (Evaluation, Recent Digit Length)
                            evaluation = (char*) allocation;
                            recentDigitLength = currentDigitLength;
                        }

                        // Update > Iterator
                        *(iterator++) = '['; {
                            // Logic > ... Update > Iterator
                            if (start -> value) {
                                iterator += currentDigitLength;

                                for (typename Digit::digit_t subiterator = start -> value; subiterator; subiterator /= radix)
                                *--iterator = *("0123456789" + (subiterator % radix));

                                iterator += currentDigitLength;
                            } else *(iterator++) = '0';
                        } *(iterator++) = ']';
                    }

                    else {
                        // Logic > ... --- NOTE (Lapys) -> Begin delimiting the string form, or add to it.
                        if (start -> value > 36u) { delimit = true; start = this -> value - 1; }
                        else *(iterator++) = *("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" + start -> value);
                    }
                }

                // Update > Iterator
                *iterator = '\0';
            }

            // Return
            return evaluation;
        }

        // Zero --- MINIFY (Lapys)
        template <size_t radix> inline void BigUnsignedInteger<radix>::zero(bool const manageMemory) { this -> length = 0u; if (manageMemory) BigUnsignedInteger::free(); else if (NULL != this -> value) this -> value -> value = 0u; }

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
