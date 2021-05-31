#include <climits>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

/* ... */
template <typename> struct uint_extended_t;
template <typename> union uint_next_t;
template <typename> union uint_prev_t;
template <std::size_t> union uint_width_t;

/* ... --- CITE (Lapys) ->
    - http://www.codeproject.com/Tips/617214/UInt-Addition-Subtraction
    - http://www.codeproject.com/Tips/618570/UInt-Multiplication-Squaring
    - https://www.codeproject.com/Tips/784635/UInt-Bit-Operations
    - http://www.codeproject.com/Tips/785014/UInt-Division-Modulus
*/
namespace { union conditional_null_t; }
template <bool, typename = conditional_null_t, typename = conditional_null_t> struct conditional_alias;

template <> struct conditional_alias<false> {};
template <typename base> struct conditional_alias<false, base> {};
template <typename true_t, typename false_t> struct conditional_alias<false, true_t, false_t> { public: typedef bool enable; typedef false_t type; };

template <> struct conditional_alias<true> { public: typedef bool enable; };
template <typename base> struct conditional_alias<true, base> { public: typedef bool enable; typedef base type; };
template <typename true_t, typename false_t> struct conditional_alias<true, true_t, false_t> { public: typedef bool enable; typedef true_t type; };

template <std::size_t width>
union uint_width_t {
    typedef
        typename conditional_alias<
            (CHAR_BIT * width) <= 255u, uint8_t,
        typename conditional_alias<
            (CHAR_BIT * width) <= 65535u, uint16_t,
        typename conditional_alias<
            (CHAR_BIT * width) <= 4294967295uL, uint32_t,
            uint64_t
        >::enable
        >::enable
        >::enable
    type;
};

template <typename> union uint_prev_t;
template <typename uint_t> union uint_prev_t<uint_extended_t<uint_t> > { typedef uint_t type; };
template <> union uint_prev_t<uint8_t> { typedef uint8_t type; };
template <> union uint_prev_t<uint16_t> { typedef uint8_t type; };
template <> union uint_prev_t<uint32_t> { typedef uint16_t type; };
template <> union uint_prev_t<uint64_t> { typedef uint32_t type; };

template <typename uint_t> union uint_next_t { typedef uint_extended_t<uint_t> type; };
template <> union uint_next_t<uint8_t> { typedef uint16_t type; };
template <> union uint_next_t<uint16_t> { typedef uint32_t type; };
template <> union uint_next_t<uint32_t> { typedef uint64_t type; };

template <typename uint_t>
struct uint_extended_t {
    private:
        static typename uint_width_t<sizeof(uint_t)>::type const WIDTH = CHAR_BIT * sizeof(uint_t); // ->> of the high
        static uint_t const MAX_VALUE = ((1u << (WIDTH - 1u)) - 0u) + ((1u << (WIDTH - 1u)) - 1u); // ->> — and low ends.

        // ...
        void add(uint_extended_t<uint_t> const number) {
            this -> high += number.high + ((
                ((this -> low & number.low) & 1) +
                ((this -> low >> 1) + (number.low >> 1))
            ) >> (WIDTH - 1u));
            this -> low += number.low;
        }

        void bitwiseAND(uint_extended_t<uint_t> const number) {
            this -> high &= number.high;
            this -> low &= number.low;
        }

        void bitwiseNOT(void) {
            this -> high = ~(this -> high);
            this -> low = ~(this -> low);
        }

        void bitwiseOR(uint_extended_t<uint_t> const number) {
            this -> high |= number.high;
            this -> low |= number.low;
        }

        void bitwiseXOR(uint_extended_t<uint_t> const number) {
            this -> high ^= number.high;
            this -> low ^= number.low;
        }

        signed char compare(uint_extended_t<uint_t> const number) const {
            return (
                (((this -> high > number.high) || ((this -> high == number.high) && (this -> low > number.low))) ? 1 : 0) -
                (((this -> high < number.high) || ((this -> high == number.high) && (this -> low < number.low))) ? 1 : 0)
            );
        }

        typename uint_width_t<sizeof(uint_t)>::type countLeadingZeroes(void) const {
            typename uint_width_t<sizeof(uint_t)>::type count = WIDTH * (0u == this -> high);
            typename uint_width_t<sizeof(uint_t)>::type iterator;

            for (iterator = WIDTH - count; iterator--; ++count)
            if (0u != this -> high >> iterator) break;

            if (WIDTH == count) {
                count += WIDTH * (0u == this -> low);

                for (iterator = (WIDTH << 1u) - count; iterator--; ++count)
                if (0u != this -> low >> iterator) break;
            }

            return count;
        }

        void decrement(void) {
            uint_t const low = this -> low - 1u;

            this -> high -= ((low ^ this -> low) & low) >> (WIDTH - 1u);
            this -> low = low;
        }

        void divide(uint_extended_t<uint_t> number) {
            uint_t high = 0u;
            uint_t low = 0u;

            if (-1 != this -> compare(number)) {
                typename uint_width_t<sizeof(uint_t)>::type shift = number.countLeadingZeroes() - this -> countLeadingZeroes();

                number.shiftLeft(shift);
                do {
                    high = (high << 1u) | (0u != low >> (WIDTH - 1u));
                    low <<= 1u;

                    if (-1 != this -> compare(number)) { this -> subtract(number); low |= 1u; }
                    number.shiftRight(1u);
                } while (shift--);
            }

            this -> high = high;
            this -> low = low;
        }

        void increment(void) {
            uint_t const low = this -> low + 1u;

            this -> high += ((this -> low ^ low) & this -> low) >> (WIDTH - 1u);
            this -> low = low;
        }

        void modulo(uint_extended_t<uint_t> const number) { this -> remainder(number); }
        void multiply(uint_extended_t<uint_t> const number) {
            unsigned char const PREV_WIDTH = WIDTH >> 1u;
            typename uint_prev_t<uint_t>::type const PREV_MAX_VALUE = ((1u << (PREV_WIDTH - 1u)) - 0u) + ((1u << (PREV_WIDTH - 1u)) - 1u);

            uint_t const lowLowMultiplication = (number.low & PREV_MAX_VALUE) * (this -> low & PREV_MAX_VALUE);
            uint_t numberLow = number.low, thisLow = this -> low, thisLowControl = lowLowMultiplication, thisHighControl = lowLowMultiplication >> PREV_WIDTH;

            // ...
            thisLow >>= PREV_WIDTH; {
                thisLowControl = thisHighControl + (thisLow * (number.low & PREV_MAX_VALUE));
                thisHighControl = thisLowControl & PREV_MAX_VALUE;
            }

            numberLow >>= PREV_WIDTH; {
                thisLowControl = thisHighControl + (numberLow * (this -> low & PREV_MAX_VALUE));
                thisHighControl = thisLowControl >> PREV_WIDTH;
            }

            // ...
            this -> high = thisHighControl + (numberLow * thisLow) + ((this -> high * number.low) + (this -> low * number.high)) + (((lowLowMultiplication >> PREV_WIDTH) + (thisLow * (number.low & PREV_MAX_VALUE))) >> PREV_WIDTH);
            this -> low = (thisLowControl << PREV_WIDTH) + (lowLowMultiplication & PREV_MAX_VALUE);
        }

        void remainder(uint_extended_t<uint_t> number) {
            if (-1 == this -> compare(number)) {
                this -> high = 0u;
                this -> low = 0u;
            }

            else {
                typename uint_width_t<sizeof(uint_t)>::type shift = number.countLeadingZeroes() - this -> countLeadingZeroes();

                number.shiftLeft(shift);
                do {
                    if (-1 != this -> compare(number)) this -> subtract(number);
                    number.shiftRight(1u);
                } while (shift--);
            }
        }

        void shiftLeft(typename uint_width_t<sizeof(uint_t) + sizeof(uint_t)>::type count) {
            unsigned char MAX_SHIFT = 0u;

            uint_t controlA, controlB;
            uint_t const high = this -> high, low = this -> low;

            // ...
            while ((static_cast<std::size_t>(1u) << MAX_SHIFT) < WIDTH) ++MAX_SHIFT;

            count &= WIDTH + (WIDTH - 1u);
            controlA = ((((count + (WIDTH + (WIDTH - 1u))) | count) & WIDTH) >> MAX_SHIFT) - 1u;
            controlB = (count >> MAX_SHIFT) - 1u;

            count &= WIDTH - 1u;
            this -> high = (low << count) & ~controlB;
            this -> low = (low << count) & controlB;
            this -> high |= ((high << count) | ((low >> (WIDTH - count)) & controlA)) & controlB;
        }

        void shiftRight(typename uint_width_t<sizeof(uint_t) + sizeof(uint_t)>::type count) {
            unsigned char MAX_SHIFT = 0u;

            uint_t controlA, controlB;
            uint_t const high = this -> high, low = this -> low;

            // ...
            while ((static_cast<std::size_t>(1u) << MAX_SHIFT) < WIDTH) ++MAX_SHIFT;

            count &= WIDTH + (WIDTH - 1u);
            controlA = ((((count + (WIDTH + (WIDTH - 1u))) | count) & WIDTH) >> MAX_SHIFT) - 1u;
            controlB = (count >> MAX_SHIFT) - 1u;

            count &= WIDTH - 1u;
            this -> low = (high >> count) & ~controlB;
            this -> high = (high >> count) & controlB;
            this -> low |= ((low >> count) | ((high << (WIDTH - count)) & controlA)) & controlB;
        }

        void subtract(uint_extended_t<uint_t> const number) {
            this -> low -= number.low;
            this -> high -= number.high + ((
                ((this -> low & number.low) & 1u) +
                ((this -> low >> 1u) + (number.low >> 1u))
            ) >> (WIDTH - 1u));
        }

    public:
        uint_t high;
        uint_t low;

        // ...
        uint_extended_t(void) : high(0u), low(0u) {}
        uint_extended_t(uint_t const number) : high(0u), low(number) {}
        uint_extended_t(uint_t const high, uint_t const low) : high(high), low(low) {}

        template <typename next_uint_t /* = typename uint_next_t<uint_t>::type */> uint_extended_t(next_uint_t const number) : high(number >> WIDTH), low(number & ~((number >> WIDTH) << WIDTH)) {}

        // ...
        uint_extended_t<uint_t> operator +(void) const { return uint_extended_t<uint_t>(this -> high, this -> low); }
        uint_extended_t<uint_t> operator -(void) const { return uint_extended_t<uint_t>(MAX_VALUE, MAX_VALUE).subtract(*this); }
        friend uint_extended_t<uint_t> operator +(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.add(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator -(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.subtract(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator *(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.multiply(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator /(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.divide(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator %(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.modulo(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator &(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.bitwiseAND(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator |(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.bitwiseOR(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator ^(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.bitwiseXOR(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator <<(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.shiftLeft(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator >>(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const numberB) { numberA.shiftRight(numberB); return numberA; }
        uint_extended_t<uint_t> operator ~(void) const { uint_extended_t<uint_t> complement = uint_extended_t<uint_t>(this -> high, this -> low); complement.bitwiseNOT(); return complement; }
        bool operator !(void) const { return this -> high && this -> low; }
        friend bool operator <(uint_extended_t<uint_t> const numberA, uint_extended_t<uint_t> const numberB) { return -1 == numberA.compare(numberB); }
        friend bool operator >(uint_extended_t<uint_t> const numberA, uint_extended_t<uint_t> const numberB) { return +1 == numberA.compare(numberB); }
        friend bool operator ==(uint_extended_t<uint_t> const numberA, uint_extended_t<uint_t> const numberB) { return 0 == numberA.compare(numberB); }
        friend bool operator !=(uint_extended_t<uint_t> const numberA, uint_extended_t<uint_t> const numberB) { return false == (numberA == numberB); }
        friend bool operator <=(uint_extended_t<uint_t> const numberA, uint_extended_t<uint_t> const numberB) { return numberA == numberB || numberA < numberB; }
        friend bool operator >=(uint_extended_t<uint_t> const numberA, uint_extended_t<uint_t> const numberB) { return numberA == numberB || numberA > numberB; }

        uint_extended_t& operator +=(uint_extended_t<uint_t> const number) { this -> add(number); return *this; }
        uint_extended_t& operator -=(uint_extended_t<uint_t> const number) { this -> subtract(number); return *this; }
        uint_extended_t& operator *=(uint_extended_t<uint_t> const number) { this -> multiply(number); return *this; }
        uint_extended_t& operator /=(uint_extended_t<uint_t> const number) { this -> divide(number); return *this; }
        uint_extended_t& operator %=(uint_extended_t<uint_t> const number) { this -> modulo(number); return *this; }
        uint_extended_t& operator &=(uint_extended_t<uint_t> const number) { this -> bitwiseAND(number); return *this; }
        uint_extended_t& operator |=(uint_extended_t<uint_t> const number) { this -> bitwiseOR(number); return *this; }
        uint_extended_t& operator ^=(uint_extended_t<uint_t> const number) { this -> bitwiseXOR(number); return *this; }
        uint_extended_t& operator <<=(typename uint_width_t<sizeof(uint_t) + sizeof(uint_t)>::type const count) { this -> shiftLeft(count); return *this; }
        uint_extended_t& operator >>=(typename uint_width_t<sizeof(uint_t) + sizeof(uint_t)>::type const count) { this -> shiftRight(count); return *this; }
        uint_extended_t& operator ++(void) { this -> increment(); return *this; }
        uint_extended_t& operator --(void) { this -> decrement(); return *this; }

        /* explicit */ operator uint_t(void) const { return this -> low; }
        operator typename uint_next_t<uint_t>::type(void) const { return this -> low | (this -> high << ((WIDTH << 1u) - 1u)); }
};

// ...
template <typename uint_t>
char const* stringify(uint_t number) {
    static char string[(CHAR_BIT * sizeof(uint_t)) + 1] = {0};
    char *iterator = string + (sizeof(string) / sizeof(char));

    for (*--iterator = '0'; number; number >>= 1u) *(iterator--) = number & 1u ? '1' : '0';
    iterator += iterator - string != (sizeof(string) / sizeof(char)) - 1;

    return static_cast<char const*>(iterator);
}

template <typename uint_t>
char const* stringify(uint_extended_t<uint_t> number) {
    static char string[(2u * CHAR_BIT * sizeof(uint_t)) + 1] = {0};
    char *iterator = string + (sizeof(string) / sizeof(char));

    if (0u == number.high) {
        for (*--iterator = '0'; number.low; number.low >>= 1u) *(iterator--) = number.low & 1u ? '1' : '0';
        iterator += iterator - string != (sizeof(string) / sizeof(char)) - 1;
    }

    else {
        for (unsigned char subiterator = CHAR_BIT * sizeof(uint_t); subiterator; --subiterator) { *--iterator = number.low & 1u ? '1' : '0'; number.low >>= 1u; }
        while (number.high) { *--iterator = number.high & 1u ? '1' : '0'; number.high >>= 1u; }
    }

    return static_cast<char const*>(iterator);
}

/* Main */
int main(void) {
    uint32_t composited = 4294967295u; // ->> Maximum for C++98.
    uint_extended_t<uint32_t> segmented = 4294967295u;

    // ... ->> Do some arithmetic testing on 'em!
    static_cast<void>(composited);
    static_cast<void>(segmented);

    // ...
    return EXIT_SUCCESS;
}
