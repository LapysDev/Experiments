/* Import */
#include <limits.h>
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
        /* Definition > ... */
        typedef radix_t digit_t;
        typedef unsigned length_t;
        typedef void primitive_t;

        /* Class > Digit ... Iterator --- REDACT (Lapys) */
        class DigitIterator { protected:
            constexpr inline DigitIterator(primitive_t) {}
            constexpr inline DigitIterator(DigitIterator const&) = delete;

            constexpr inline unsigned char count(void) const noexcept { return 0u; }
            constexpr inline bool done(void) const noexcept { return true; }
            constexpr inline digit_t iterate(void) const noexcept { return 0uL; }

            constexpr inline DigitIterator& operator =(DigitIterator const&) noexcept = delete;
        };

        class DigitForwardIterator { protected:
            constexpr inline DigitForwardIterator(primitive_t) {}
            constexpr inline DigitForwardIterator(BigNumber const&) {}
            constexpr inline DigitForwardIterator(DigitForwardIterator const&) = delete;

            constexpr inline DigitForwardIterator& operator =(BigNumber const&) noexcept = delete;
            constexpr inline DigitForwardIterator& operator =(DigitForwardIterator const&) noexcept = delete;
        };
        class DigitReverseIterator { protected:
            constexpr inline DigitReverseIterator(primitive_t) {}
            constexpr inline DigitReverseIterator(BigNumber const&) {}
            constexpr inline DigitReverseIterator(DigitReverseIterator const&) = delete;

            constexpr inline DigitReverseIterator& operator =(BigNumber const&) noexcept = delete;
            constexpr inline DigitReverseIterator& operator =(DigitReverseIterator const&) noexcept = delete;
        };

    // [...] > [Constructor]
    public: constexpr inline BigNumber(primitive_t) {}
};

/* Class */
/* : Big Unsigned Integer */
template <radix_t radix>
class BigUnsignedInteger : public BigNumber<radix>, BigUnsignedIntegerExtension<radix> {
    /* ...; Definition > ... */
    template <radix_t> friend class BigFloat;
    template <radix_t> friend class BigSignedInteger;
    template <radix_t> friend class BigUnsignedInteger;

    typedef typename BigNumber<radix>::digit_t digit_t;
    typedef typename BigNumber<radix>::length_t index_t, length_t;
    typedef unsigned long primitive_t;

    // [...]
    protected:
        /* Definition > Buffer */
        void *buffer;

        /* Class > Digit ... Iterator --- REDACT (Lapys) */
        class DigitIterator : public BigNumber<radix>::DigitIterator { protected:
            union iterable_v {
                digit_t *arbitrary[2];
                primitive_t primitive;

                constexpr inline iterable_v(digit_t const begin[], digit_t const end[]) : arbitrary{begin, end} {}
                constexpr inline iterable_v(primitive_t const value) : primitive{value} {}
            } iterable;
            enum iterable_t {ARBITRARY, PRIMITIVE} type;

            constexpr inline DigitIterator(primitive_t const iterable) : iterable{iterable}, type{PRIMITIVE} {}
            constexpr inline DigitIterator(BigUnsignedInteger const& iterable) : iterable{iterable.valueOf(), iterable.valueOf() + iterable.lengthOf()}, type{ARBITRARY} {}
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
            virtual inline digit_t iterate(void) noexcept { return BigNumber<radix>::DigitIterator::iterate(); }

            constexpr inline DigitIterator& operator =(primitive_t const) noexcept = delete;
            constexpr inline DigitIterator& operator =(BigUnsignedInteger const&) noexcept = delete;
            constexpr inline DigitIterator& operator =(DigitIterator const&) noexcept = delete;
        };

        class DigitForwardIterator : public BigNumber<radix>::DigitForwardIterator, public DigitIterator { typedef typename DigitIterator::iterable_t iterable_t;
            public: constexpr inline DigitForwardIterator(primitive_t const iterable) : DigitIterator(iterable) {}
            public: constexpr inline DigitForwardIterator(BigUnsignedInteger const& iterable) : DigitIterator(iterable) {}
            protected: constexpr inline DigitForwardIterator(DigitForwardIterator const&) = delete;

            constexpr inline digit_t iterate(void) noexcept override {
                switch (this -> type) {
                    case iterable_t::ARBITRARY: return this -> iterable.arbitrary[0]++ -> value;
                    case iterable_t::PRIMITIVE: primitive_t iterable = 0uL, length = 1uL; while (radix < this -> iterable.primitive / length) { iterable += (this -> iterable.primitive / length) % radix; length *= radix; } Digit const evaluation = {this -> iterable.primitive / length}; this -> iterable.primitive = iterable; return evaluation;
                } return DigitIterator::iterate();
            }

            constexpr inline DigitForwardIterator& operator =(DigitForwardIterator const&) noexcept = delete;
        };
        class DigitReverseIterator : public BigNumber<radix>::DigitReverseIterator, public DigitIterator { typedef typename DigitIterator::iterable_t iterable_t; protected:
            public: constexpr inline DigitReverseIterator(primitive_t const iterable) : DigitIterator(iterable) {}
            public: constexpr inline DigitReverseIterator(BigUnsignedInteger const& iterable) : DigitIterator(iterable) {}
            protected: constexpr inline DigitReverseIterator(DigitReverseIterator const&) = delete;

            constexpr inline digit_t iterate(void) noexcept override {
                switch (this -> type) {
                    case iterable_t::ARBITRARY: return (--(this -> iterable.arbitrary[1])) -> value;
                    case iterable_t::PRIMITIVE: digit_t const evaluation = {this -> iterable.primitive % radix}; this -> iterable.primitive /= radix; return evaluation;
                } return DigitIterator::iterate();
            }

            constexpr inline DigitReverseIterator& operator =(DigitReverseIterator const&) noexcept = delete;
        };

        // Function --- REDACT (Lapys)
        // : Allocate
        inline void allocate(length_t const length) {
            void *const allocation = ::realloc(this -> buffer, sizeof(length_t) + (length + sizeof(digit_t)));
            NULL == allocation ? ::exit(EXIT_FAILURE) : (void) this -> buffer = allocation;
        }

        // : ... Digit ...
        constexpr inline digit_t getDigitAt(index_t index) const noexcept {
            digit_t digitCollection = BigUnsignedInteger::getDigitCollectionAt(index);
            while (index--) digitCollection /= radix;
            return digitCollection % radix;
        }
        constexpr inline digit_t& getDigitCollectionAt(index_t const index) const noexcept {
            constexpr unsigned short const digitCollectionBitSize = CHAR_BIT * sizeof(digit_t);
            index_t digitCollectionIndex = 0u;

            for (
                unsigned short digitBitOffset = index * BigUnsignedInteger::getDigitBitWidth();
                digitBitOffset > digitCollectionBitSize;
                digitBitOffset -= digitCollectionBitSize
            ) ++digitCollectionIndex;

            return *(digitCollectionIndex + BigUnsignedInteger::valueOf());
        }
        constexpr inline static unsigned char getDigitBitWidth(void) noexcept {
            radix_t iterator = radix;
            unsigned char width = 0u;

            do ++width; while (iterator >>= 1uL);
            return width;
        }
        constexpr inline void setDigitAt(index_t index, digit_t const digit) noexcept {
            digit_t& digitCollection = BigUnsignedInteger::getDigitCollectionAt(index);
            digit_t digitCollectionDigits = 0uL;
            digit_t digitCollectionExponent = 1uL;

            ++index;
            for (digit_t digitCollectionIterator = digitCollection; index--; digitCollectionIterator /= radix) {
                digitCollectionDigits += digitCollectionExponent * (digitCollectionIterator % radix);
                digitCollectionExponent *= radix;
            }
            digitCollectionExponent /= radix;

            digitCollection -= digitCollectionDigits;
            digitCollection += digit * digitCollectionExponent;
            digitCollection += digitCollectionDigits - (digitCollectionExponent * (digitCollectionDigits / digitCollectionExponent));
        }

        // : (Length, Value) Of
        constexpr inline length_t& lengthOf(void) const noexcept { return *(length_t*) this -> buffer; }
        constexpr inline digit_t* valueOf(void) const noexcept { return 1 + (length_t*) this -> buffer; }

    // [...]
    private:
        // Function > Move
        constexpr inline void move(BigUnsignedInteger& number) noexcept { this -> buffer = number.buffer; number.buffer = NULL; }

    // [...]
    public:
        // [Constructor]
        constexpr inline BigUnsignedInteger(void) : buffer{NULL} {}
        inline BigUnsignedInteger(DigitReverseIterator const& number) : buffer{NULL} { BigUnsignedInteger::copy(number); }
        constexpr inline BigUnsignedInteger(BigUnsignedInteger&& number) : buffer{NULL} { BigUnsignedInteger::move(number); }

        inline ~BigUnsignedInteger(void) { ::free(this -> buffer); }

        // Definition > Copy
        inline void copy(DigitReverseIterator const&);

        // [Operator] > [=]
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

/* Modification */
    /* Big Float */
    /* Big Signed Integer */
    /* Big Unsigned Integer */
    template <radix_t radix>
    inline void BigUnsignedInteger<radix>::copy(DigitReverseIterator const& number) {}

/* Main */
#include <iostream>
int main(void) { (void) BigUnsignedInteger<10uL>(654321uL); }
