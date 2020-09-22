/* Import */
#include <float.h> // Floating-Point
#include <limits.h> // Limits
#include <stdarg.h> // Standard Arguments
#include <stdint.h> // Standard Integer
#include <stdio.h> // Standard Input/ Output --- NOTE (Lapys) -> For testing.
#include <stdlib.h> // Standard Library
#include <string.h> // String

/* Definition > Big ... --- NOTE (Lapys) -> The extensions are for `radix` specific optimizations e.g.: binary optimizations. */
template <size_t> class BigFloat;
template <size_t> class BigNumber;
template <size_t> class BigSignedInteger;
template <size_t> class BigUnsignedInteger;

template <size_t radix> class BigFloatExtension { protected: constexpr inline BigFloatExtension(BigFloat<radix> *const) {} };
template <size_t radix> class BigNumberExtension { protected: constexpr inline BigNumberExtension(BigNumber<radix> *const) {} };
template <size_t radix> class BigSignedIntegerExtension { protected: constexpr inline BigSignedIntegerExtension(BigSignedInteger<radix> *const) {} };
template <size_t radix> class BigUnsignedIntegerExtension { protected: constexpr inline BigUnsignedIntegerExtension(BigUnsignedInteger<radix> *const) {} };

typedef BigFloat<10u> big_float;
typedef BigSignedInteger<10u> big_int;
typedef BigUnsignedInteger<10u> big_uint;

/* Function > Terminate --- NOTE (Lapys) -> For testing. */
int Terminate(void) throw() { ::fflush(stdout); ::exit(EXIT_SUCCESS); return EXIT_SUCCESS; }
int Terminate(char const message[], ...) throw() { va_list arguments; ::fputs("\r\n", stderr); va_start(arguments, message); ::vfprintf(stderr, message, arguments); va_end(arguments); ::fputc('\0', stderr); ::fflush(stdout); ::exit(EXIT_FAILURE); return EXIT_FAILURE; }

/* Global > Radix Maximum */
constexpr size_t const RADIX_MAX = SIZE_MAX - 1u;

/* Class */
    /* Big Number ... */
    template <size_t radix>
    class BigNumber : public BigNumberExtension<radix> {
        /* Definition > ... */
        class Digit;
        class DigitIterator;
        class DigitIteratorImplementation;
        template <bool> class DigitForwardIterator;
        template <bool> class DigitReverseIterator;

        typedef size_t length_t;
        typedef void primitive_t;

        // [...]
        private:
            // Function > Assert
            constexpr inline void assert(void) const noexcept {
                // Logic > Error
                if (0u == radix || radix > RADIX_MAX)
                Terminate("[Error]: Unable to instantiate invalid `BigNumber` of `radix` %zu", radix);
            }

        // [...]
        public:
            // [Constructor]
            constexpr inline BigNumber(void) : BigNumberExtension<radix>{this} { BigNumber::assert(); }
            template <size_t subradix> constexpr inline BigNumber(BigNumber<subradix> const&) : BigNumberExtension<radix>{this} {}

            // [Operator] > [...]
            inline virtual BigNumber operator +(void) const noexcept { return *this; }
            inline virtual BigNumber operator -(void) const noexcept { return *this; }
            template <size_t subradix> inline BigNumber operator *(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber operator /(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber operator %(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber operator &(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber operator |(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber operator ^(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber operator <<(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber operator >>(BigNumber<subradix> const&) const noexcept;
            constexpr inline bool operator !(void) const noexcept;
            template <size_t subradix> inline BigNumber& operator =(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator +=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator -=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator *=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator /=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator %=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator &=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator |=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator ^=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator <<=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator >>=(BigNumber<subradix> const&) const noexcept;
            template <size_t subradix> inline BigNumber& operator ++(void) const noexcept;
            template <size_t subradix> inline BigNumber operator ++(int const) const noexcept;
            template <size_t subradix> inline BigNumber& operator --(void) const noexcept;
            template <size_t subradix> inline BigNumber operator --(int const) const noexcept;
    };

    template <> class BigNumberExtension<2u> {
        protected: BigNumber<2u> *self; constexpr inline BigNumberExtension(BigNumber<2u> *const self) : self{self} {}
        public: inline virtual BigNumber<2u> operator ~(void) const noexcept { return *self; }
    };

    /* Digit */
    template <size_t radix>
    class BigNumber<radix>::Digit final {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef size_t digit_t;

        // Function > Get Minimum Size
        constexpr inline static unsigned char getMinimumSize(void) noexcept { unsigned char size = 0u; for (size_t iterator = radix; iterator; iterator >>= 1u) ++size; return size; }

        // [...]
        private: digit_t value : Digit::getMinimumSize();
        protected: constexpr inline Digit(digit_t const value) : value{value} {}
    };

    /* ... Iterator */
    template <size_t radix>
    class BigNumber<radix>::DigitIteratorImplementation { protected:
        // [Constructor]
        template <bool state> constexpr inline DigitIterator(DigitIterator<state> const&);

        // [Operator] > [=]
        template <bool state> constexpr inline DigitIterator<state>& operator =(BigNumber const&) noexcept;
        template <bool state> constexpr inline DigitIterator<state>& operator =(DigitIterator<state> const&) noexcept;

        // Function > ...
        constexpr inline typename BigNumber<radix>::length_t count(void) const noexcept;
        constexpr inline bool done(void) const noexcept;
        constexpr inline Digit iterate(void) const noexcept;
    };

    template <size_t radix> template <> class BigNumber<radix>::DigitIterator<false> : public BigNumber<radix>::DigitIteratorImplementation { protected: void *const object; constexpr inline DigitIterator(BigNumber const& number) : object{&number} {} };
    template <size_t radix> template <> class BigNumber<radix>::DigitIterator<true>  : public BigNumber<radix>::DigitIteratorImplementation { protected: constexpr inline DigitIterator(void) {} constexpr inline DigitIterator(BigNumber const& number); };

    template <size_t radix> class BigNumber<radix>::Digit::DigitForwardIterator : public BigNumber<radix>::DigitIterator {};
    template <size_t radix> class BigNumber<radix>::Digit::DigitReverseIterator : public BigNumber<radix>::DigitIterator {};

/* Class */
    /* Big Unsigned Integer ... */
    template <size_t radix>
    class BigUnsignedInteger : public BigNumber<radix>, public BigUnsignedIntegerExtension<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        typedef typename BigNumber<radix>::Digit Digit;
        typedef typename BigNumber<radix>::Digit::digit_t digit_t;
        typedef typename BigNumber<radix>::length_t length_t;
        #if defined(__cplusplus) && __cplusplus >= 201103L
            typedef unsigned long long primitive_t;
        #else
            typedef unsigned long primitive_t;
        #endif
        typedef DigitIterator<primitive_t> DigitIterator;

        /* Class > ... Digit Iterator --- REDACT (Lapys) */
        template <class primitive_t>
        class DigitIterator : public BigNumber<radix>::DigitIterator<true> { protected:
            union iterable_t { public:
                void *arbitrary; // NOTE (Lapys) -> Represents both `BigNumber*` and `Digit[]` types.
                primitive_t plain;

                constexpr inline iterable_t(primitive_t const iterable) : plain{iterble} {}
                constexpr inline iterable_t(void *const iterable) : arbitrary{iterable} {}
            } const object;
            enum {ARBITRARY, PLAIN} const type : 2;
            iterable_t value;

            constexpr inline DigitIterator(DigitIterator const&);

            constexpr inline DigitIterator& operator =(BigUnsignedInteger* const) noexcept;
            constexpr inline DigitIterator& operator =(primitive_t const) noexcept;
            constexpr inline DigitIterator& operator =(DigitIterator const&) noexcept;

            constexpr inline typename BigUnsignedInteger::length_t count(void) const noexcept {
                switch (this -> type) {
                    case ARBITRARY: return ((BigUnsignedInteger*) this -> object.arbitrary) -> length;
                    case PLAIN: unsigned char length = 0u; for (primitive_t iterator = this -> object.plain; iterator; iterator /= radix) ++length; return length;
                } return 0u;
            }

            constexpr inline bool done(void) const noexcept { return bool(); }
            constexpr inline Digit iterate(void) const noexcept { return Digit(); }
        };

        template <class primitive_t>
        class DigitForwardIterator : public DigitIterator<primitive_t> {
            protected:
                constexpr inline bool done(void) const noexcept {
                    switch (this -> type) {
                        case ARBITRARY: return ((BigUnsignedInteger*) this -> object.arbitrary) -> length == this -> value.arbitrary - ((BigUnsignedInteger*) this -> object.arbitrary) -> value;
                        case PLAIN: return this -> value.plain;
                    } return DigitIterator<primitive_t>::done();
                }

                constexpr inline Digit iterate(void) const noexcept {
                    switch (this -> type) {
                        case ARBITRARY: return ((Digit*&) this -> value.arbitrary)++ -> value;
                        case PLAIN: Digit const iteration = {this -> value.plain % radix}; this -> value.plain /= radix; return iteration;
                    } return DigitIterator<primitive_t>::iterate();
                }

            public:
                constexpr inline DigitIterator(BigUnsignedInteger const& number) : BigNumber<radix>::DigitIterator(), object{&number}, type{ARBITRARY}, value{number.value} {}
                constexpr inline DigitIterator(primitive_t const number) : BigNumber<radix>::DigitIterator(), object{number}, type{PLAIN}, value{number} {}
        };

        template <class primitive_t>
        class DigitReverseIterator : public DigitIterator<primitive_t> {
            protected:
                constexpr inline bool done(void) const noexcept {
                    switch (this -> type) {
                        case ARBITRARY: return (Digit*) this -> value + 1 == ((BigUnsignedInteger*) this -> object.arbitrary) -> value;
                        case PLAIN: return this -> value.plain;
                    } return DigitIterator<primitive_t>::done();
                }

                constexpr inline Digit iterate(void) const noexcept {
                    switch (this -> type) {
                        case ARBITRARY: return (--((Digit*&) this -> value.arbitrary)) -> value;
                        case PLAIN: Digit const iteration = {this -> object.plain / this -> value.plain} % radix; this -> value.plain /= radix; return iteration;
                    } return DigitIterator<primitive_t>::iterate();
                }

            public:
                constexpr inline DigitIterator(BigUnsignedInteger const& number) : BigNumber<radix>::DigitIterator(), object{&number}, type{ARBITRARY}, value{number.length + number.value} {}
                constexpr inline DigitIterator(primitive_t const number) : BigNumber<radix>::DigitIterator(), object{number}, type{PLAIN}, value{1u} {
                    unsigned char iterator = DigitIterator<primitive_t>::count();

                    if (iterator) { while (--iterator) this -> value.plain *= radix; }
                    else this -> value.plain = 0u;
                }
        };

        // [...]
        private:
            // Definition > (Length, String, Value)
            length_t length;
            char *string;
            Digit *value;

        // [...]
        protected:
            // [Constructor]
            constexpr inline BigUnsignedInteger(length_t const length) : length{length}, value{NULL} { BigUnsignedInteger::allocate(length); }
            constexpr inline BigUnsignedInteger(Digit const value[]) : length{0u}, value{value} {}
            constexpr inline BigUnsignedInteger(length_t const length, Digit const value[]) : length{length}, value{value} {}

            // Definition > ...
            inline void allocate(size_t const) noexcept;
            inline void copy(BigUnsignedInteger const&) noexcept;
            template <size_t subradix> inline void copy(BigUnsignedInteger<subradix> const&) noexcept;
            constexpr inline void move(BigUnsignedInteger const&) noexcept;
            inline void free(void) noexcept;
            inline void fromPrimitive(DigitReverseIterator const&) noexcept;

        // [...]
        public:
            // [Constructor]
            inline BigUnsignedInteger(primitive_t const number = 0u) : length{0u}, string{NULL}, value{NULL} { BigUnsignedInteger::fromPrimitive(number); }
            template <size_t subradix> inline BigUnsignedInteger(BigUnsignedInteger<subradix> const& number) : length{0u}, string{NULL}, value{NULL} { BigUnsignedInteger::copy(number); }
            constexpr inline BigUnsignedInteger(BigUnsignedInteger&& number) : length{0u}, string{NULL}, value{NULL} { BigUnsignedInteger::move(number); }

            // [Destructor]
            inline ~BigUnsignedInteger(void) noexcept { BigUnsignedInteger::free(); ::free(this -> string); }

            // Definition > ...
            inline char* toString(void) const noexcept;
    };

    /* Big Signed Integer ... */
    template <size_t radix>
    class BigSignedInteger : public BigUnsignedInteger<radix>, public BigSignedIntegerExtension<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        template <size_t subradix> using Digit = typename BigNumber<subradix>::Digit;
        typedef typename BigNumber<radix>::Digit::digit_t digit_t;
        typedef typename BigNumber<radix>::length_t length_t;
        #if defined(__cplusplus) && __cplusplus >= 201103L
            typedef signed long long primitive_t;
        #else
            typedef signed long primitive_t;
        #endif
    };

    /* Big Float ... */
    template <size_t radix>
    class BigFloat final : public BigSignedInteger<radix>, public BigFloatExtension<radix> {
        /* ... */
        template <size_t> friend class BigFloat;
        template <size_t> friend class BigSignedInteger;
        template <size_t> friend class BigUnsignedInteger;

        template <size_t subradix> using Digit = typename BigNumber<subradix>::Digit;
        typedef typename BigNumber<radix>::Digit::digit_t digit_t;
        typedef typename BigNumber<radix>::length_t length_t;
        typedef long double primitive_t;
    };

/* Modification */
    /* Big Unsigned Integer */
        // Allocate, Free
        template <size_t radix> inline void BigUnsignedInteger<radix>::free(void) noexcept { ::free(this -> value); }
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::allocate(size_t const length) noexcept {
            // Logic > ... Modification > Target > Value
            if (NULL == this -> value) this -> value = (Digit*) ::malloc(length * sizeof(Digit));
            else if (length > this -> length) {
                void *const allocation = ::realloc(this -> value, length * sizeof(Digit));

                if (NULL == allocation) { BigUnsignedInteger::free(); this -> value = NULL; }
                else this -> value = (Digit*) allocation;
            }

            // Logic > Error
            if (NULL == this -> value)
            Terminate("[Error]: Unable to acquire additional resources (%zu bytes) for `BigNumber` instance", (length > this -> length ? length - this -> length : this -> length - length) * sizeof(Digit));
        }

        // Copy
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::copy(BigUnsignedInteger const& number) noexcept {
            // Modification > Target > (Length, Value)
            BigUnsignedInteger::allocate(this -> length = number.length);
            ::memcpy(this -> value, number.value, number.length * sizeof(Digit));
        }

        template <size_t radix> template <size_t subradix>
        inline void BigUnsignedInteger<radix>::copy(BigUnsignedInteger<subradix> const&) noexcept {
            /* CHECKPOINT (Lapys) -> Convert from `subradix` to `radix` numeral base. */
        }

        // Move
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::move(BigUnsignedInteger const& number) noexcept {
            // Modification > Target > (Length, Value)
            this -> length = number.length;
            this -> value = number.value;

            // Modification > Number > (Length, Value)
            number.length = 0u;
            number.value = NULL;
        }

        // From Primitive
        template <size_t radix>
        inline void BigUnsignedInteger<radix>::fromPrimitive(DigitReverseIterator const& number) noexcept {
            // Logic
            if (false == number.done()) {
                // ... Modification > Target > Value
                BigUnsignedInteger::allocate(this -> length = number.count());

                for (Digit *iterator = this -> value; false == number.done(); ++iterator)
                iterator -> value = number.iterate();
            }
        }

        // To String
        template <size_t radix>
        inline char* BigUnsignedInteger<radix>::toString(bool delimit = false) noexcept {
            // Initialization > (Allocation, Length)
            void *allocation;
            size_t length = this -> length + 1u;

            // Update > Allocation
            allocation = ::realloc(this -> string, length * sizeof(char));
            if (NULL == allocation) goto terminate;
            else {
                // Initialization > (Digits, ... Width, ... Iterator)
                char const digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                size_t recentWidth = 0u;
                char *stringIterator = this -> string;

                // ...; Loop
                this -> string = (char*) allocation;
                for (Digit *iterator = this -> value, *const end = this -> length + iterator; end != iterator; ++iterator) {
                    // Logic > ...
                    if (false == delimit && iterator -> value < sizeof(digits) / sizeof(char)) // NOTE (Lapys) -> Alphanumeric digit representation.
                    *stringIterator++ = digits[iterator -> value % radix];

                    else {
                        // Initialization > Width
                        size_t width = 0u;

                        // Logic > ... Update > Width
                        if (0u == iterator -> value) width = 1u;
                        else for (digit_t subiterator = iterator -> value; subiterator; subiterator /= radix) ++width;

                        // Logic > ...
                        if (delimit) {
                            // Logic > ...
                            if (recentWidth < width) goto reallocate;
                            else { // NOTE (Lapys) -> Delimited decimal number representation.
                                // Update > String ...
                                *stringIterator++ = '['; {
                                    if (0u == iterator -> value) *stringIterator++ = '0';
                                    else {
                                        stringIterator += width;

                                        for (digit_t digit = iterator -> value; digit; digit /= radix)
                                        *--stringIterator = digits[digit % radix];

                                        stringIterator += width;
                                    }
                                } *stringIterator++ = ']';
                            }
                        } else goto reallocate;

                        // Continue; [Reallocate]
                        continue;
                        reallocate: {
                            // Update > (Length, Allocation, ...)
                            length = ((this -> length * (width + 2u)) + 1u) * sizeof(char);
                            allocation = ::realloc(this -> string, length * sizeof(char));

                            delimit = true;
                            iterator = this -> value;
                            recentWidth = width;

                            // Logic > ...
                            if (NULL == allocation) goto terminate;
                            else { this -> string = (char*) allocation; stringIterator = this -> string; }
                        }
                    }
                }

                // Update > String Iterator
                *stringIterator = '\0';
            }

            // Return; [Terminate] ...
            return this -> string;
            terminate: {
                Terminate("[Error]: Unable to acquire additional resources (%zu bytes) for `BigNumber` instance", length * sizeof(char));
            } return NULL;
        }

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
