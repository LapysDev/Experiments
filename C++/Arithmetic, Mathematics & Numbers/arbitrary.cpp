/* Import */
#include <limits.h> // Limits
#include <stdlib.h> // Standard Library

/* Namespace > Big Mathematics */
namespace BigMathematics {
    /* Definition > ... */
    struct bigfloat_t;
    struct bigint_t;
    struct bignum_t;
    struct biguint_t;
}

/* ... Class --- REDACT (Lapys) */
namespace BigMathematics {
    /* Big ... */
    /* : Number */
    struct bignum_t { protected:
        typedef bool digit_t;
        typedef unsigned long index_t, length_t;
        typedef void primitive_t;

        typedef unsigned char digit_buffer;
        template <typename> struct digit_iterator;

        public:
            constexpr length_t& getLength(void) const noexcept;
            constexpr void setLength(length_t const) noexcept;
    };

    /* : Unsigned Integer */
    struct biguint_t : public bignum_t { friend int main(void); protected:
        typedef unsigned long primitive_t;
        template <typename = primitive_t> struct digit_iterator;

        private:
            void *buffer;

            void allocate(length_t const);
            void copy(biguint_t const&);
            void fromPrimitive(primitive_t);

            digit_t getDigit(index_t const) const noexcept;
            constexpr length_t getLength(void) const noexcept;

            void setDigit(index_t const, digit_t const) noexcept;
            constexpr void setLength(length_t const) noexcept;

        protected:
            char const* toString(unsigned long const = 10uL) const;

        public:
            biguint_t(primitive_t const = 0uL);
            biguint_t(biguint_t const&);
            constexpr biguint_t(biguint_t&&) noexcept;

            ~biguint_t(void);

            constexpr operator primitive_t(void) const noexcept;
    };

    /* : Signed Integer */
    struct bigint_t : public biguint_t { friend int main(void); protected:
        typedef signed long primitive_t;
        template <typename = primitive_t> struct digit_iterator;

        public:
            constexpr operator primitive_t(void) const noexcept;
    };

    /* : Floating-Point */
    struct bigfloat_t final : public bigint_t { friend int main(void); protected:
        typedef long double primitive_t;
        template <typename = primitive_t> struct digit_iterator;

        public:
            constexpr operator primitive_t(void) const noexcept;
    };

    /* Digit ... Iterator */
    /* : Number */
    template <typename primitive_t>
    struct bignum_t::digit_iterator {
        union iterable_t {
            typename bignum_t::index_t arbitrary;
            primitive_t primitive;

            constexpr iterable_t(typename bignum_t::index_t const);
            constexpr iterable_t(const primitive_t);
        } iterable;
        enum { ARBITRARY, PRIMITIVE } type : 1;

        constexpr digit_iterator(bignum_t const&);
        constexpr digit_iterator(primitive_t const);
    };

    /* : Unsigned Integer */
    template <typename primitive_t>
    struct biguint_t::digit_iterator : public bignum_t::digit_iterator<primitive_t> {
        constexpr typename bignum_t::length_t count(void) const;
        constexpr bool done(void) const;
        constexpr typename bignum_t::digit_t iterate(void);
    };

    /* : Signed Integer */
    template <typename primitive_t>
    struct bigint_t::digit_iterator : public biguint_t::digit_iterator<primitive_t> {
        constexpr digit_iterator(primitive_t const);
        constexpr typename bignum_t::digit_t iterate(void);
    };

    /* : Floating-Point  */
    template <typename primitive_t>
    struct bigfloat_t::digit_iterator final : public bigint_t::digit_iterator<primitive_t> {};
}

/* ... Modification */
namespace BigMathematics {
    /* Digit ... Iterator */
    /* : Floating-Point */
    /* : Number */
        // [Constructor]
        template <typename primitive_t> constexpr bignum_t::digit_iterator<primitive_t>::digit_iterator(bignum_t const& number) : iterable{number.getLength()}, type{bignum_t::digit_iterator<primitive_t>::ARBITRARY} {}
        template <typename primitive_t> constexpr bignum_t::digit_iterator<primitive_t>::digit_iterator(primitive_t const number) : iterable{number}, type{bignum_t::digit_iterator<primitive_t>::PRIMITIVE} {}

        // Iterable > [Constructor]
        template <typename primitive_t> constexpr bignum_t::digit_iterator<primitive_t>::iterable_t::iterable_t(typename bignum_t::index_t const index) : arbitrary{index} {}
        template <typename primitive_t> constexpr bignum_t::digit_iterator<primitive_t>::iterable_t::iterable_t(const primitive_t number) : primitive{number} {}

    /* : Signed Integer */
    template <typename primitive_t> constexpr bigint_t::digit_iterator<primitive_t>::digit_iterator(primitive_t const) {}
    template <typename primitive_t> constexpr inline typename bignum_t::digit_t bigint_t::digit_iterator<primitive_t>::iterate(void) { return 0u; }

    /* : Unsigned Integer */
    template <typename primitive_t> constexpr inline typename bignum_t::length_t biguint_t::digit_iterator<primitive_t>::count(void) const { return 0u; }
    template <typename primitive_t> constexpr inline bool biguint_t::digit_iterator<primitive_t>::done(void) const { return false; }
    template <typename primitive_t> constexpr inline typename bignum_t::digit_t biguint_t::digit_iterator<primitive_t>::iterate(void) { return 0u; }

    /* Big ... */
    /* : Floating-Point */
    /* : Number */
    /* : Signed Integer */
    /* : Unsigned Integer */
        // [Constructor]
        biguint_t::biguint_t(primitive_t const number) : buffer{NULL} { biguint_t::fromPrimitive(number); }
        biguint_t::biguint_t(biguint_t const&) : buffer{NULL} {}
        constexpr biguint_t::biguint_t(biguint_t&& number) noexcept : buffer{number.buffer} { number.buffer = NULL; }

        // [Destructor]
        biguint_t::~biguint_t(void) { ::free(this -> buffer); }

        // ...
        inline void biguint_t::allocate(length_t const length) { this -> buffer = ::realloc(this -> buffer, sizeof(length_t) + (((length / CHAR_BIT) + (0u != length % CHAR_BIT)) * sizeof(digit_buffer))); }
        inline void biguint_t::fromPrimitive(primitive_t number) { unsigned char length = 0u; primitive_t iterator; for (iterator = number; iterator; iterator >>= 1uL) ++length; biguint_t::allocate(length); for (iterator = 0u; number; number >>= 1uL) biguint_t::setDigit(iterator++, number & 1uL); }

        inline biguint_t::digit_t biguint_t::getDigit(index_t const index) const noexcept { return (*((index / CHAR_BIT) + (digit_buffer*) (1 + (length_t*) this -> buffer)) >> (CHAR_BIT - (index % CHAR_BIT) - 1uL)) & 1uL; }
        constexpr inline biguint_t::length_t biguint_t::getLength(void) const noexcept { return NULL == this -> buffer ? 0u : *(length_t*) this -> buffer; }

        inline void biguint_t::setDigit(index_t const index, digit_t const digit) noexcept { 0u == digit ? *((index / CHAR_BIT) + (digit_buffer*) (1 + (length_t*) this -> buffer)) &= ~(1uL << (CHAR_BIT - (index % CHAR_BIT) - 1uL)) : *((index / CHAR_BIT) + (digit_buffer*) (1 + (length_t*) this -> buffer)) |= 1uL << (CHAR_BIT - (index % CHAR_BIT) - 1uL); }
        constexpr inline void biguint_t::setLength(length_t const length) noexcept { *(length_t*) this -> buffer = length; }

        // Copy
        inline void biguint_t::copy(biguint_t const& number) {
            // Constant > Length
            length_t const length = number.getLength() - 1uL;

            // ...; Loop > Update > Buffer
            biguint_t::allocate(length + 1uL);
            biguint_t::setLength(length + 1uL);

            for (
                digit_buffer *buffer = length + (digit_buffer*) (1 + (length_t*) this -> buffer), *iterator = length + (digit_buffer*) (1 + (length_t*) number.buffer);
                buffer != this -> buffer; --buffer, --iterator
            ) *buffer = *iterator;
        }

        // To String --- CHECKPOINT (Lapys)
        inline char const* biguint_t::toString(unsigned long const) const { return NULL; }
}

/* Main */
int main(void) {
    biguint_t number = {};
}
