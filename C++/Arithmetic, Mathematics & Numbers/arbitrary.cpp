/* Import */
#include <stdlib.h> // Standard Library
#include <string.h> // String

/* Definition > ... --- NOTE (Lapys) */
// -> Arbitrary-precision number interface.
typedef unsigned long radix_t;
template <radix_t> class BigFloat;
template <radix_t> class BigNumber;
template <radix_t> class BigSignedInteger;
template <radix_t> class BigUnsignedInteger;

// -> Template-specific optimization interface.
template <radix_t> struct BigFloatExtension { protected: constexpr inline BigFloatExtension(void) {} };
template <radix_t> struct BigNumberExtension { protected: constexpr inline BigNumberExtension(void) {} };
template <radix_t> struct BigSignedIntegerExtension { protected: constexpr inline BigSignedIntegerExtension(void) {} };
template <radix_t> struct BigUnsignedIntegerExtension { protected: constexpr inline BigUnsignedIntegerExtension(void) {} };

/* Class */
/* : Big Number */
template <radix_t radix>
class BigNumber : public BigNumberExtension<radix> {
    // [...]
    protected:
        /* Definition > (Digit ..., ...) --- REDACT (Lapys) */
        class DigitIterator;
        class DigitForwardIterator;
        class DigitReverseIterator;

        class Digit {
            template <radix_t> friend class BigFloat;
            template <radix_t> friend class BigNumber;
            template <radix_t> friend class BigSignedInteger;
            template <radix_t> friend class BigUnsignedInteger;

            typedef radix_t digit_t;

            private:
                constexpr inline static unsigned char widthOf(radix_t value) noexcept {
                    unsigned char width = 0u;
                    do ++width; while (value >>= 1uL);
                    return ((width >> 1u) << 1u) + 2u;
                }

            protected:
                digit_t value : Digit::widthOf(radix);
                constexpr inline Digit(digit_t const value = 0u) : value{value} {}
        };

        typedef typename Digit::digit_t digit_t;
        typedef unsigned length_t;
        typedef void primitive_t;

    // [...] > [Constructor]
    public: constexpr inline BigNumber(primitive_t) {}
};

/* : Digit ... Iterator --- REDACT (Lapys) */
template <radix_t radix>
class BigNumber<radix>::DigitIterator { typedef typename BigNumber<radix>::Digit Digit; protected:
    constexpr inline DigitIterator(primitive_t) {}
    constexpr inline DigitIterator(DigitIterator const&) = delete;

    constexpr inline unsigned char count(void) const noexcept { return 0u; }
    constexpr inline bool done(void) const noexcept { return true; }
    constexpr inline Digit iterate(void) const noexcept { return Digit(); }

    constexpr inline DigitIterator& operator =(DigitIterator const&) const noexcept = delete;
};

template <radix_t radix>
class BigNumber<radix>::DigitForwardIterator : public BigNumber<radix>::DigitIterator { typedef class BigNumber<radix> BigNumber; protected:
    constexpr inline DigitForwardIterator(primitive_t) {}
    constexpr inline DigitForwardIterator(BigNumber const&) {}
    constexpr inline DigitForwardIterator(DigitForwardIterator const&) = delete;

    constexpr inline DigitForwardIterator& operator =(BigNumber const&) const noexcept = delete;
    constexpr inline DigitForwardIterator& operator =(DigitForwardIterator const&) const noexcept = delete;
};
template <radix_t radix>
class BigNumber<radix>::DigitReverseIterator : public BigNumber<radix>::DigitIterator { typedef class BigNumber<radix> BigNumber; protected:
    constexpr inline DigitReverseIterator(primitive_t) {}
    constexpr inline DigitReverseIterator(BigNumber const&) {}
    constexpr inline DigitReverseIterator(DigitReverseIterator const&) = delete;

    constexpr inline DigitReverseIterator& operator =(BigNumber const&) const noexcept = delete;
    constexpr inline DigitReverseIterator& operator =(DigitReverseIterator const&) const noexcept = delete;
};

/* Class */
/* : Big Unsigned Integer */
template <radix_t radix>
class BigUnsignedInteger : public BigNumber<radix>, BigUnsignedIntegerExtension<radix> {
    /* ...; Definition > ... */
    template <radix_t> friend class BigFloat;
    template <radix_t> friend class BigSignedInteger;
    template <radix_t> friend class BigUnsignedInteger;

    typedef class BigNumber<radix>::Digit Digit;
    typedef typename BigNumber<radix>::digit_t digit_t;
    typedef typename BigNumber<radix>::length_t length_t;
    typedef unsigned long primitive_t;

    // [...]
    protected:
        /* Definition > Buffer */
        void *buffer;

        /* Class > Digit ... Iterator --- REDACT (Lapys) */
        class DigitIterator : public BigNumber<radix>::DigitIterator { protected:
            union iterable_v {
                Digit *arbitrary[2];
                primitive_t primitive;

                constexpr inline iterable_v(BigUnsignedInteger const begin[], BigUnsignedInteger const end[]) : arbitrary{begin, end} {}
                constexpr inline iterable_v(primitive_t const value) : primitive{value} {}
            } iterable;
            enum iterable_t {ARBITRARY, PRIMITIVE} type;

            constexpr inline DigitIterator(primitive_t const iterable) : iterable{iterable}, type{PRIMITIVE} {}
            constexpr inline DigitIterator(BigUnsignedInteger const& iterable) : iterable{iterable.valueof(), iterable.valueof() + iterable.lengthof()}, type{ARBITRARY} {}
            constexpr inline DigitIterator(DigitIterator const&) = delete;

            constexpr inline unsigned char count(void) const noexcept {
                switch (this -> type) {
                    case ARBITRARY: return this -> iterable.arbitrary[1] - this -> iterable.arbitrary[0];
                    case PRIMITIVE: unsigned char count = 0u; for (primitive_t iterator = this -> iterable.primitive; iterator; iterator /= radix) ++count; return count;
                } return BigNumber<radix>::DigitIterator::count();
            }
            constexpr inline bool done(void) const noexcept {
                switch (this -> type) {
                    case ARBITRARY: return this -> iterable.arbitrary[1] == this -> iterable.arbitrary[0];
                    case PRIMITIVE: return 0uL == this -> iterable.primitive;
                } return BigNumber<radix>::DigitIterator::done();
            }
            virtual inline Digit iterate(void) noexcept { return BigNumber<radix>::DigitIterator::iterate(); }

            constexpr inline DigitIterator& operator =(primitive_t const) const noexcept = delete;
            constexpr inline DigitIterator& operator =(BigUnsignedInteger const&) const noexcept = delete;
            constexpr inline DigitIterator& operator =(DigitIterator const&) const noexcept = delete;
        };

        class DigitForwardIterator : public BigNumber<radix>::DigitForwardIterator, public DigitIterator { typedef typename DigitIterator::iterable_t iterable_t; protected:
            constexpr inline DigitForwardIterator(DigitForwardIterator const&) = delete;
            constexpr inline DigitForwardIterator& operator =(DigitForwardIterator const&) const noexcept = delete;

            constexpr inline Digit iterate(void) noexcept override {
                switch (this -> type) {
                    case iterable_t::ARBITRARY: return this -> iterable.arbitrary[0]++ -> value;
                    case iterable_t::PRIMITIVE: primitive_t iterable = 0uL, length = 1uL; while (radix < this -> iterable.primitive / length) { iterable += (this -> iterable.primitive / length) % radix; length *= radix; } Digit const evaluation = {this -> iterable.primitive / length}; this -> iterable.primitive = iterable; return evaluation;
                } return DigitIterator::iterate();
            }
        };
        class DigitReverseIterator : public BigNumber<radix>::DigitReverseIterator, public DigitIterator {
            typedef typename DigitIterator::iterable_t iterable_t;
            protected:
                constexpr inline DigitReverseIterator(DigitReverseIterator const&) = delete;
                constexpr inline DigitReverseIterator& operator =(DigitReverseIterator const&) const noexcept = delete;

                constexpr inline Digit iterate(void) noexcept override {
                    switch (this -> type) {
                        case iterable_t::ARBITRARY: return (--(this -> iterable.arbitrary[1])) -> value;
                        case iterable_t::PRIMITIVE: Digit const evaluation = {this -> iterable.primitive % radix}; this -> iterable.primitive /= radix; return evaluation;
                    } return DigitIterator::iterate();
                }
            public: constexpr inline DigitReverseIterator(primitive_t const iterable) : DigitIterator(iterable) {}
        };

        // Function
        // : Allocate --- REDACT (Lapys) --- CONSIDER (Lapys) -> Is the `1.5` growth rate wasted memory?
        inline void allocate(length_t const length) {
            void *const allocation = ::realloc(this -> buffer, ((length * 3u) / 2u) + sizeof(length_t));
            NULL == allocation ? ::exit(EXIT_FAILURE) : (void) this -> buffer = allocation;
        }

        // : (Length, Value) Of
        constexpr inline length_t& lengthof(void) const noexcept { return *(length_t*) this -> buffer; }
        constexpr inline Digit* valueof(void) const noexcept { return 1 + (length_t*) this -> buffer; }

    // [...]
    private:
        // Function > Move
        constexpr inline void move(BigUnsignedInteger& number) noexcept { this -> buffer = number.buffer; number.buffer = NULL; }

    // [...]
    public:
        constexpr inline BigUnsignedInteger(void) : buffer{NULL} {}
        inline BigUnsignedInteger(DigitReverseIterator const& number) : buffer{NULL} { BigUnsignedInteger::copy(number); }
        constexpr inline BigUnsignedInteger(BigUnsignedInteger&& number) : buffer{NULL} { BigUnsignedInteger::move(number); }

        inline void copy(DigitIterator const&) {}

        inline BigUnsignedInteger& operator =(DigitReverseIterator const& number) noexcept { BigUnsignedInteger::copy(number); return *this; }
        constexpr inline BigUnsignedInteger& operator =(BigUnsignedInteger&& number) noexcept { BigUnsignedInteger::move(number); return *this; }
};

/* : Big Signed Integer */
template <radix_t radix>
class BigSignedInteger : public BigUnsignedInteger<radix>, BigSignedIntegerExtension<radix> {
    /* ...; Definition > ... */
    template <radix_t> friend class BigFloat;
    template <radix_t> friend class BigSignedInteger;
    template <radix_t> friend class BigUnsignedInteger;
};

/* : Big Float */
template <radix_t radix>
class BigFloat : public BigSignedInteger<radix>, BigFloatExtension<radix> {
    /* ...; Definition > ... */
    template <radix_t> friend class BigFloat;
    template <radix_t> friend class BigSignedInteger;
    template <radix_t> friend class BigUnsignedInteger;
};

/* Class > ... --- NOTE (Lapys) -> Slower, more intuitive interface for the arbitrary-precision classes. */
template <class BigNumber>
struct bignum_t : private BigNumber {
    // [Operator] > ...
    inline bignum_t operator +(void) const { bignum_t evaluation = {}; evaluation.copy(*this); return evaluation; }
    template <class type> friend inline bignum_t operator +(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.add(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator +(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.add(numberB); return evaluation; }
    inline bignum_t operator -(void) const { bignum_t evaluation = {}; evaluation.copy(*this); return evaluation.sign(), evaluation; }
    template <class type> friend inline bignum_t operator -(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.subtract(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator -(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.subtract(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator *(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.multiply(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator *(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.multiply(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator /(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.divide(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator /(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.divide(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator %(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.modulo(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator %(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.modulo(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator &(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseAND(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator &(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseAND(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator |(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseOR(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator |(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseOR(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator ^(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseXOR(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator ^(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseXOR(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator <<(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseLEFT_SHIFT(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator <<(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseLEFT_SHIFT(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator >>(bignum_t const& numberA, type numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseRIGHT_SHIFT(numberB); return evaluation; }
    template <class type> friend inline bignum_t operator >>(type numberA, bignum_t const& numberB) { bignum_t evaluation = {}; evaluation.copy(numberA), evaluation.bitwiseRIGHT_SHIFT(numberB); return evaluation; }
    inline bignum_t operator ~(void) const { bignum_t evaluation = {}; evaluation.copy(*this); return evaluation.bitwiseCOMPLEMENT(), evaluation; }
    constexpr inline bool operator !(void) const noexcept { return BigNumber::isZero(); }
    template <class type> friend constexpr inline bool operator <(bignum_t const& numberA, type numberB) noexcept { return numberA.lesserThan(numberB); }
    template <class type> friend constexpr inline bool operator <(type numberA, bignum_t const& numberB) noexcept { return false == numberB.lesserThan(numberA); }
    template <class type> friend constexpr inline bool operator <=(bignum_t const& numberA, type numberB) noexcept { return numberA.equals(numberB) || numberA.lesserThan(numberB); }
    template <class type> friend constexpr inline bool operator <=(type numberA, bignum_t const& numberB) noexcept { return numberB.greaterThan(numberA); }
    template <class type> friend constexpr inline bool operator >(bignum_t const& numberA, type numberB) noexcept { return numberA.greaterThan(numberB); }
    template <class type> friend constexpr inline bool operator >(type numberA, bignum_t const& numberB) noexcept { return false == numberB.greaterThan(numberA); }
    template <class type> friend constexpr inline bool operator >=(bignum_t const& numberA, type numberB) noexcept { return numberA.equals(numberB) || numberA.greaterThan(numberB); }
    template <class type> friend constexpr inline bool operator >=(type numberA, bignum_t const& numberB) noexcept { return numberB.lesserThan(numberA); }
    template <class type> inline bignum_t& operator =(type number) { return BigNumber::copy(number), *this; }
    template <class type> inline bignum_t& operator +=(type number) { return BigNumber::add(number), *this; }
    template <class type> inline bignum_t& operator -=(type number) { return BigNumber::subtract(number), *this; }
    template <class type> inline bignum_t& operator *=(type number) { return BigNumber::multiply(number), *this; }
    template <class type> inline bignum_t& operator /=(type number) { return BigNumber::divide(number), *this; }
    template <class type> inline bignum_t& operator %=(type number) { return BigNumber::modulo(number), *this; }
    template <class type> inline bignum_t& operator &=(type number) { return BigNumber::bitwiseAND(number), *this; }
    template <class type> inline bignum_t& operator |=(type number) { return BigNumber::bitwiseOR(number), *this; }
    template <class type> inline bignum_t& operator ^=(type number) { return BigNumber::bitwiseXOR(number), *this; }
    template <class type> inline bignum_t& operator <<=(type number) { return BigNumber::bitwiseLEFT_SHIFT(number), *this; }
    template <class type> inline bignum_t& operator >>=(type number) { return BigNumber::bitwiseRIGHT_SHIFT(number), *this; }
    template <class type> inline bignum_t& operator ++(void) { return BigNumber::increment(), *this; }
    template <class type> inline bignum_t operator ++(int) { bignum_t evaluation = {}; evaluation.copy(*this); return BigNumber::operator ++(), evaluation; }
    template <class type> inline bignum_t& operator --(void) { return BigNumber::decrement(), *this; }
    template <class type> inline bignum_t operator --(int) { bignum_t evaluation = {}; evaluation.copy(*this); return BigNumber::operator --(), evaluation; }
};

struct bigfloat_t final : public bignum_t<BigFloat<10uL>> {};
struct bigint_t final : public bignum_t<BigSignedInteger<10uL>> {};
struct biguint_t final : public bignum_t<BigUnsignedInteger<10uL>> {};

/* Modification > ... */

/* Main */
#include <iostream>
int main(void) { (void) BigUnsignedInteger<10uL>(654321uL); }
