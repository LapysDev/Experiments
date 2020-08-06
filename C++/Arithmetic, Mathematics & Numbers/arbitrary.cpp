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
template <size_t radix> class BigSignedInteger;
template <size_t radix> class BigUnsignedInteger;

typedef BigFloat<10u> big_float;
typedef BigSignedInteger<10u> big_int;
typedef BigUnsignedInteger<10u> big_uint;

/* Class */
    /* Big Float --- CHECKPOINT (Lapys) */
    /* Big Signed Integer --- CHECKPOINT (Lapys) */
    /* Big Unsigned Integer */
    template <size_t radix>
    class BigUnsignedInteger {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef size_t length_t;
        #if defined(__cplusplus) && (__cplusplus == 201103L)
            typedef unsigned long long primitive_t;
        #else
            typedef unsigned long primitive_t;
        #endif

        // [...]
        protected:
            /* Definition > (Digit, Iterator) */
            class Digit; // NOTE (Lapys) -> Atomic unit of store.
            class DigitBuffer; // NOTE (Lapys) -> Persistent heap allocation of `BigNumber::Digit`.
            class Iterator; // NOTE (Lapys) -> For iterating each atomic unit of `BigNumber` or `primitive_t`.

            // Declaration > (Add, From Number, Decrement, Increment, Zero)
            void add(Iterator const&, bool const);
            static void fromNumber(BigUnsignedInteger* const, primitive_t const, bool const = true);
            void decrement(bool const) noexcept;
            void increment(bool const);
            void zero(bool const = true);

        // [...]
        private:
            // Definition > (Buffer, Length, Value) --- REDACT (Lapys)
            static DigitBuffer buffer;
            length_t length;
            Digit *value;

            /* Declaration > (Allocate ..., Assert, Clear Buffer, Free) --- NOTE (Lapys) -> Memory management utilities.
                    Of course, it may be preferable to implement a slab allocator.
            */
            void allocate(length_t const);
            static void* allocate(Digit* const, length_t const);
            static void allocateBuffer(length_t const);

            constexpr void assert(void);

            static void clearBuffer(void) noexcept;
            void free(void) noexcept;
            static void free(Digit* const) noexcept;

            // Function > (Copy, Move) --- MINIFY (Lapys)
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

            inline static BigUnsignedInteger fromNumber(primitive_t const number) { BigUnsignedInteger evaluation {}; BigUnsignedInteger::fromNumber(&evaluation, number, true); return evaluation; }

            inline void increment(void) { BigUnsignedInteger::increment(true); }
            inline static BigUnsignedInteger increment(BigUnsignedInteger const& number) noexcept { BigUnsignedInteger evaluation {}; evaluation.copy(number); evaluation.increment(); return evaluation; }

            constexpr bool isSignificant(void) const noexcept;
            constexpr inline static bool isSignificant(BigUnsignedInteger const& number) noexcept { return number.isSignificant(); }
            constexpr bool isZero(void) const noexcept;
            constexpr inline static bool isZero(BigUnsignedInteger const& number) noexcept { return number.isZero(); }

            char* toString(bool = false) const;
            inline void zero(void) { BigUnsignedInteger::zero(true); }
    };

/* Class --- REDACT (Lapys) */
    /* Digit --- NOTE (Lapys) -> Denary-based value. */
    template <size_t radix>
    class BigUnsignedInteger<radix>::Digit final {
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;
        template <size_t subradix> friend class BigUnsignedInteger<subradix>::Iterator;

        typedef size_t digit_t;

        public:
            constexpr inline Digit(digit_t const value) : value{value} {}

            constexpr inline static unsigned char getSize(size_t number) noexcept { unsigned char size = 0u; while (number) { number >>= 1u; ++size; } return size ? size : 1u; }
            constexpr inline static bool isGreatestRank(digit_t const digit) noexcept { return digit == radix - 1u; }
            constexpr inline static bool isLowestRank(digit_t const digit) noexcept { return 0u == digit; }

        private: digit_t value : Digit::getSize(radix);
    };

    /* Digit Buffer */
    template <size_t radix>
    class BigUnsignedInteger<radix>::DigitBuffer final { friend BigUnsignedInteger;
        private: length_t length; Digit *value;
        public:
            inline DigitBuffer(void) : length{0u}, value{NULL} { BigUnsignedInteger::allocateBuffer(radix /* CONSIDER (Lapys) -> Pre-allocate memory for the buffer, but to what size? */); }
            inline ~DigitBuffer(void) { BigUnsignedInteger::clearBuffer(); }

            constexpr inline operator Digit*(void) const noexcept { return this -> value; }
    };

    /* Iterator */
    template <size_t radix>
    class BigUnsignedInteger<radix>::Iterator final {
        private:
            static Digit const *sentinel;

            static enum IteratorType {BIG, PRIMITIVE} type;
            static void const *value;

        public:
            constexpr inline Iterator(BigUnsignedInteger const* const number) { Iterator::sentinel = number -> value - 1; Iterator::type = Iterator::BIG; Iterator::value = number -> value + (number -> length - 1u); }
            constexpr inline Iterator(primitive_t* const number) { Iterator::type = Iterator::PRIMITIVE; Iterator::value = number; }

            constexpr inline typename BigUnsignedInteger::length_t count(void) const noexcept {
                switch (this -> type) {
                    case Iterator::BIG: return ((Digit*) Iterator::value) - Iterator::sentinel;
                    case Iterator::PRIMITIVE: { primitive_t value = *((primitive_t*) Iterator::value); if (value) { BigUnsignedInteger::length_t evaluation = 0u; while (value) { ++evaluation; value /= radix; } return evaluation; } else return 1u; }
                } return 0u;
            }
            constexpr inline bool done(void) const noexcept {
                switch (this -> type) {
                    case Iterator::BIG: return Iterator::sentinel != Iterator::value;
                    case Iterator::PRIMITIVE: return *((primitive_t*) Iterator::value);
                } return true;
            }
            constexpr inline BigUnsignedInteger::Digit next(void) const noexcept {
                switch (Iterator::type) {
                    case Iterator::BIG: { Digit const *const evaluation = (Digit const*) Iterator::value; Iterator::value = evaluation - 1; return evaluation -> value; }
                    case Iterator::PRIMITIVE: { primitive_t const evaluation = *((primitive_t*) Iterator::value); *((primitive_t*) Iterator::value) /= radix; return evaluation % radix; }
                } return 0u;
            }
    };

/* Modification */
    // Big Unsigned Integer > Buffer
    template <size_t radix>
    typename BigUnsignedInteger<radix>::DigitBuffer BigUnsignedInteger<radix>::buffer {};

    // ... Iterator > (Sentinel, Type, Value)
    template <size_t radix> typename BigUnsignedInteger<radix>::Digit const *BigUnsignedInteger<radix>::Iterator::sentinel = NULL;
    template <size_t radix> typename BigUnsignedInteger<radix>::Iterator::IteratorType BigUnsignedInteger<radix>::Iterator::type {};
    template <size_t radix> void const *BigUnsignedInteger<radix>::Iterator::value = NULL;

/* Modification */
    /* Big Unsigned Integer */
        // [Constructor]
        template <size_t radix> inline BigUnsignedInteger<radix>::BigUnsignedInteger(void) : length{0u}, value{} {}
        template <size_t radix> inline BigUnsignedInteger<radix>::BigUnsignedInteger(primitive_t const number) : length{0u}, value{NULL} { BigUnsignedInteger::fromNumber(this, number); }
        template <size_t radix> inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigUnsignedInteger const& number) : length{0u}, value{NULL} { BigUnsignedInteger::copy(number); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigUnsignedInteger&& number) : length{0u}, value{NULL} { BigUnsignedInteger::move(number); }

        // Add --- CHECKPOINT (Lapys)
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::add(Iterator const& number, bool const manageMemory) {
        }

        /* Allocate ...
                --- CONSIDER (Lapys) -> Internally construct a region of memory instead of instantiating a set of `Digit` objects unto heap memory.
                --- NOTE (Lapys) -> Request sufficient memory for storing `Digit` instances. --- REDACT (Lapys)
        */
        template <size_t radix> inline void BigUnsignedInteger<radix>::allocateBuffer(length_t const length) { if (BigUnsignedInteger::Buffer.length < length) { BigUnsignedInteger::Buffer.length = length; BigUnsignedInteger::Buffer.value = (Digit*) BigUnsignedInteger::allocate(BigUnsignedInteger::Buffer.value, length); } }
        template <size_t radix> inline void BigUnsignedInteger<radix>::allocate(length_t const length) { if (length) { this -> value = (Digit*) BigUnsignedInteger::allocate(this -> value, length + 1u); (this -> value + length) -> value = radix; } else BigUnsignedInteger::free(); }

        template <size_t radix>
        inline void* BigUnsignedInteger<radix>::allocate(Digit* const buffer, length_t const length) {
            // Logic
            if (length > SIZE_MAX / sizeof(Digit)) { ::puts("\r[Error]: Attempt to allocate excess memory for `Digit` instances"); ::abort(); }
            else { void *const allocation = NULL == buffer ? ::malloc(length * sizeof(BigUnsignedInteger::Digit)) : ::realloc(buffer, length * sizeof(BigUnsignedInteger::Digit)); if (NULL == allocation) { ::puts("\r[Error]: Unable to allocate memory for additional `Digit` instances"); ::abort(); } return allocation; }

            // Return
            return NULL;
        }

        // Assert, Clear Buffer, Free --- MINIFY (Lapys)
        template <size_t radix> constexpr inline void BigUnsignedInteger<radix>::assert(void) { if (0u == radix || 1u == radix || SIZE_MAX == radix) { ::puts("\r[Error]: Attempt to instantiate `BigNumber` with non-representable radix"); ::abort(); } }
        template <size_t radix> inline void BigUnsignedInteger<radix>::clearBuffer(void) noexcept { BigUnsignedInteger::free(BigUnsignedInteger::Buffer.value); BigUnsignedInteger::Buffer.value = NULL; }

        template <size_t radix> inline void BigUnsignedInteger<radix>::free(Digit* const buffer) noexcept { ::free(buffer); }
        template <size_t radix> inline void BigUnsignedInteger<radix>::free(void) noexcept { BigUnsignedInteger::free(this -> value); this -> value = NULL; }

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

        // From Number
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::fromNumber(BigUnsignedInteger* const evaluation, primitive_t const number, bool const manageMemory) {
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
