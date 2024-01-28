/* ... ->> `union` because `final` is unavailable in C++98.
    --- CITE (Lapys) ->
        - http://www.codeproject.com/Tips/617214/UInt-Addition-Subtraction
        - http://www.codeproject.com/Tips/618570/UInt-Multiplication-Squaring
        - https://www.codeproject.com/Tips/784635/UInt-Bit-Operations
        - http://www.codeproject.com/Tips/785014/UInt-Division-Modulus
*/
#include <climits>
#include <csignal>
#include <cstdio>
#include <stdint.h>

/* ... */
template <typename type> union can_sizeof { static std::size_t const size = sizeof(type); };

template <bool, typename, typename> union conditional_t;
template <typename true_t, typename false_t> union conditional_t<false, true_t, false_t> { typedef false_t type; };
template <typename true_t, typename false_t> union conditional_t<true, true_t, false_t> { typedef true_t type; };

/* ... */
template <typename> struct uint_extended_t;
template <typename> union uint_next_t;
template <typename> union uint_prev_t;
template <typename uint_t, typename = uint_t> union uint_width_t;

// ...
template<typename, typename> union uint_width_t { typedef uint64_t type; };
template<typename uint_t> union uint_width_t<uint_t, can_sizeof<uint_t> > {
    typedef
        typename conditional_t<
            CHAR_BIT * sizeof(uint_t) <= 255u, uint8_t,
        typename conditional_t<
            CHAR_BIT * sizeof(uint_t) <= 65535u, uint16_t,
        typename conditional_t<
            CHAR_BIT * sizeof(uint_t) <= 4294967295uL, uint32_t,
            uint64_t
        >::type >::type >::type
    type;
};

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
    template <typename> struct is_extended_uint { static bool const value = false; };
    template <typename type> struct is_extended_uint<uint_extended_t<type> > { static bool const value = true; };

    template <typename> friend struct uint_extended_t;
    template <typename type> friend char const* stringify(uint_extended_t<type>);

    private:
        static typename uint_width_t<uint_t>::type const UINT_BIT_WIDTH = CHAR_BIT * sizeof(uint_t);
        /* constexpr */ inline static uint_t UINT_MAX_VALUE(void) { static uint_t maximum = 1u; if (1u == maximum) { typename uint_width_t<uint_t>::type width = UINT_BIT_WIDTH; while (--width) maximum <<= 1u; maximum += maximum--; } return maximum; }

        // ...
        uint_t high;
        uint_t low;

        void add(uint_extended_t<uint_t> const& number) {
            this -> high += number.high;
            this -> high += (
                ((this -> low & number.low) & 1u) +
                ((this -> low >> 1u) + (number.low >> 1u))
            ) >> (UINT_BIT_WIDTH - 1u);

            this -> low += number.low;
        }

        void bitwiseAND(uint_extended_t<uint_t> const& number) { this -> high &= number.high; this -> low &= number.low; }
        void bitwiseNOT(void) { this -> high = ~(this -> high); this -> low = ~(this -> low); }
        void bitwiseOR(uint_extended_t<uint_t> const& number) { this -> high |= number.high; this -> low |= number.low; }
        void bitwiseXOR(uint_extended_t<uint_t> const& number) { this -> high ^= number.high; this -> low ^= number.low; }
        void decrement(void) {
            uint_t const low = this -> low - 1u;

            // ...
            this -> low ^= low; this -> low &= low;
            this -> low >>= UINT_BIT_WIDTH - 1u;
            this -> high -= this -> low;

            this -> low = low;
        }

        void divide(uint_extended_t<uint_t> const& number) {
            /* NOTE (Lapys) --> Non-independent implementation. */
            uint_extended_t<uint_t>(this -> high, this -> low).remainder(number, this);
        }

        void increment(void) {
            uint_t const low = this -> low + 1u;

            // ...
            this -> low = (this -> low ^ low) & this -> low;
            this -> low >>= UINT_BIT_WIDTH - 1u;
            this -> high += this -> low;

            this -> low = low;
        }

        bool isEqual(uint_extended_t<uint_t> const& number) const { return this -> high == number.high && this -> low == number.low; }
        bool isGreater(uint_extended_t<uint_t> const& number) const { return this -> high > number.high || (this -> high == number.high && this -> low > number.low); }
        bool isLesser(uint_extended_t<uint_t> const& number) const { return this -> high < number.high || (this -> high == number.high && this -> low < number.low); }
        bool isZero(void) const { return 0u == this -> high && 0u == this -> low; }
        void modulo(uint_extended_t<uint_t> const& number) { this -> remainder(number); }
        void multiply(uint_extended_t<uint_t> const& number) {
            typename uint_width_t<typename uint_prev_t<uint_t>::type>::type const PREV_WIDTH = UINT_BIT_WIDTH >> 1u;
            typename uint_prev_t<uint_t>::type PREV_MAX_VALUE = 1u;
                for (typename uint_width_t<typename uint_prev_t<uint_t>::type>::type width = PREV_WIDTH; --width; ) PREV_MAX_VALUE <<= 1u;
                PREV_MAX_VALUE += PREV_MAX_VALUE--;

            uint_t lowMultiplication = (number.low & PREV_MAX_VALUE) * (this -> low & PREV_MAX_VALUE);
            uint_t numberLow = number.low;
            uint_t thisLow = this -> low;
            uint_t thisLowControl = lowMultiplication;
            uint_t thisHighControl = lowMultiplication >> PREV_WIDTH;

            // ...
            thisLow >>= PREV_WIDTH; {
                thisHighControl += thisLow * (number.low & PREV_MAX_VALUE);
                thisLowControl = thisHighControl;

                thisHighControl = thisLowControl & PREV_MAX_VALUE;
            }

            numberLow >>= PREV_WIDTH; {
                thisHighControl += numberLow * (this -> low & PREV_MAX_VALUE);
                thisLowControl = thisHighControl;

                thisHighControl = thisLowControl >> PREV_WIDTH;
            }

            // ...
            thisLowControl <<= PREV_WIDTH;
            thisLowControl += lowMultiplication & PREV_MAX_VALUE;
            this -> low = thisLowControl;

            lowMultiplication >>= PREV_WIDTH;
            numberLow *= thisLow;
            thisLow *= number.low & PREV_MAX_VALUE;
            thisLow += lowMultiplication;
            thisLow >>= PREV_WIDTH;
            thisHighControl += numberLow;
            thisHighControl += thisLow;
            this -> high *= number.low;
            this -> high += thisHighControl;
            this -> high += this -> low * number.high;
        }

        void remainder(uint_extended_t<uint_t> const& number, uint_extended_t<uint_t>* const quotient = NULL) {
            if (number.isZero()) {
                while (0x0 != std::raise(SIGFPE))
                continue;
            }

            else {
                uint_extended_t<uint_t> divisor = uint_extended_t<uint_t>(number.high, number.low);
                uint_extended_t<uint_t> increment = uint_extended_t<uint_t>(0u, 1u);

                if (NULL != quotient) quotient -> zero();

                while (0u == (divisor.high >> (UINT_BIT_WIDTH - 1u)) && false == this -> isLesser(divisor)) {
                    divisor.shiftLeft();
                    increment.shiftLeft();
                }

                while (false == this -> isLesser(number)) {
                    while (this -> isLesser(divisor) && false == divisor.isEqual(number)) {
                        divisor.shiftRight();
                        increment.shiftRight();
                    }

                    this -> subtract(divisor);
                    if (NULL != quotient) quotient -> add(increment);
                }
            }
        }

        void shiftLeft(void) {
            this -> high <<= 1u;
            this -> high |= this -> low >> (UINT_BIT_WIDTH - 1u);

            this -> low <<= 1u;
        }

        void shiftLeftBy(typename uint_width_t<typename uint_next_t<uint_t>::type>::type const count) {
            if (UINT_BIT_WIDTH > count) {
                this -> high <<= count;
                this -> high |= this -> low >> (UINT_BIT_WIDTH - count);

                this -> low <<= count;
            }

            else {
                this -> low <<= count - UINT_BIT_WIDTH;

                this -> high = this -> low;
                this -> low = 0u;
            }
        }

        void shiftRight(void) {
            this -> low >>= 1u;
            this -> low |= (this -> high & 1u) << (UINT_BIT_WIDTH - 1u);

            this -> high >>= 1u;
        }

        void shiftRightBy(typename uint_width_t<typename uint_next_t<uint_t>::type>::type const count) {
            if (UINT_BIT_WIDTH > count) {
                this -> low >>= count;
                this -> low |= (this -> high & ~((this -> high >> count) << count)) << (UINT_BIT_WIDTH - count);

                this -> high >>= count;
            }

            else {
                this -> high >>= count - UINT_BIT_WIDTH;

                this -> low = this -> high;
                this -> high = 0u;
            }
        }

        void subtract(uint_extended_t<uint_t> const& number) {
            this -> low -= number.low;

            this -> high -= number.high;
            this -> high -= (
                ((this -> low & number.low) & 1u) +
                ((this -> low >> 1u) + (number.low >> 1u))
            ) >> (UINT_BIT_WIDTH - 1u);
        }

        void zero(void) {
            this -> high = 0u;
            this -> low = 0u;
        }

    public:
        uint_extended_t(void) : high(0u), low(0u) {}
        uint_extended_t(uint_t const high, uint_t const low) : high(high), low(low) {}

        uint_extended_t(typename conditional_t<is_extended_uint<typename uint_next_t<uint_t>::type>::value, uintmax_t, typename uint_next_t<uint_t>::type>::type const number) {
            if (sizeof(number) > sizeof(uint_t)) {
                typename conditional_t<is_extended_uint<typename uint_next_t<uint_t>::type>::value, uintmax_t, typename uint_next_t<uint_t>::type>::type value = number;

                for (typename uint_width_t<uint_t>::type width = UINT_BIT_WIDTH; width; --width) value >>= 1u;
                this -> high = value;

                for (typename uint_width_t<uint_t>::type width = UINT_BIT_WIDTH; width; --width) value <<= 1u;
                this -> low = number & ~value;
            }

            else {
                this -> high = 0u;
                this -> low = number;
            }
        }

        template <typename type>
        uint_extended_t(uint_extended_t<type> const& number) {
            if (sizeof(type) == sizeof(uint_t)) {
                this -> high = number.high;
                this -> low = number.low;
            }

            else if (sizeof(type) > sizeof(uint_t)) {
                type low = type(number.low);
                low &= static_cast<type>(uint_extended_t<typename uint_next_t<uint_t>::type>::UINT_MAX_VALUE());

                // ...
                low >>= UINT_BIT_WIDTH;
                this -> high = low;

                this -> low = this -> high;
                this -> low <<= UINT_BIT_WIDTH;
                this -> low = this -> high & ~(this -> low);
            }

            else {
                this -> high = 0u;

                this -> low = static_cast<uint_t>(number.high);
                this -> low <<= uint_extended_t<type>::UINT_BIT_WIDTH;
                this -> low |= static_cast<uint_t>(number.low);
            }
        }

        // ...
        uint_extended_t<uint_t> operator +(void) const { return uint_extended_t<uint_t>(this -> high, this -> low); }
        uint_extended_t<uint_t> operator -(void) const { return uint_extended_t<uint_t>(UINT_MAX_VALUE(), UINT_MAX_VALUE()).subtract(*this); }
        friend uint_extended_t<uint_t> operator +(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator +=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator -(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator -=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator *(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator *=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator /(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator /=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator %(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator %=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator &(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator &=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator |(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator |=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator ^(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator ^=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator <<(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator <<=(numberB); return numberA; }
        friend uint_extended_t<uint_t> operator >>(uint_extended_t<uint_t> numberA, uint_extended_t<uint_t> const& numberB) { numberA.operator >>=(numberB); return numberA; }
        uint_extended_t<uint_t> operator ~(void) const { uint_extended_t<uint_t> complement = uint_extended_t<uint_t>(this -> high, this -> low); complement.bitwiseNOT(); return complement; }
        bool operator !(void) const { return this -> isZero(); }
        friend bool operator <(uint_extended_t<uint_t> const& numberA, uint_extended_t<uint_t> const& numberB) { return numberA.isLesser(numberB); }
        friend bool operator >(uint_extended_t<uint_t> const& numberA, uint_extended_t<uint_t> const& numberB) { return numberA.isGreater(numberB); }
        friend bool operator ==(uint_extended_t<uint_t> const& numberA, uint_extended_t<uint_t> const& numberB) { return numberA.isEqual(numberB); }
        friend bool operator !=(uint_extended_t<uint_t> const& numberA, uint_extended_t<uint_t> const& numberB) { return false == operator ==(numberA, numberB); }
        friend bool operator <=(uint_extended_t<uint_t> const& numberA, uint_extended_t<uint_t> const& numberB) { return operator ==(numberA, numberB) || operator <(numberA, numberB); }
        friend bool operator >=(uint_extended_t<uint_t> const& numberA, uint_extended_t<uint_t> const& numberB) { return operator ==(numberA, numberB) || operator >(numberA, numberB); }

        uint_extended_t& operator +=(uint_extended_t<uint_t> const& number) { this -> add(number); return *this; }
        uint_extended_t& operator -=(uint_extended_t<uint_t> const& number) { this -> subtract(number); return *this; }
        uint_extended_t& operator *=(uint_extended_t<uint_t> const& number) { this -> multiply(number); return *this; }
        uint_extended_t& operator /=(uint_extended_t<uint_t> const& number) { this -> divide(number); return *this; }
        uint_extended_t& operator %=(uint_extended_t<uint_t> const& number) { this -> modulo(number); return *this; }
        uint_extended_t& operator &=(uint_extended_t<uint_t> const& number) { this -> bitwiseAND(number); return *this; }
        uint_extended_t& operator |=(uint_extended_t<uint_t> const& number) { this -> bitwiseOR(number); return *this; }
        uint_extended_t& operator ^=(uint_extended_t<uint_t> const& number) { this -> bitwiseXOR(number); return *this; }
        uint_extended_t& operator <<=(typename uint_width_t<typename uint_next_t<uint_t>::type>::type const count) { this -> shiftLeftBy(count); return *this; }
        uint_extended_t& operator >>=(typename uint_width_t<typename uint_next_t<uint_t>::type>::type const count) { this -> shiftRightBy(count); return *this; }
        uint_extended_t& operator ++(void) { this -> increment(); return *this; }
        uint_extended_t operator ++(int const) { uint_extended_t<uint_t> const increment = uint_extended_t<uint_t>(this -> high, this -> low); this -> increment(); return increment; }
        uint_extended_t& operator --(void) { this -> decrement(); return *this; }
        uint_extended_t operator --(int const) { uint_extended_t<uint_t> const decrement = uint_extended_t<uint_t>(this -> high, this -> low); this -> decrement(); return decrement; }

        template <typename type> operator type(void) const {
            type number = type(0u);

            if (sizeof(type) <= sizeof(uint_t)) {
                number = this -> high;
                for (typename uint_width_t<uint_t>::type width = UINT_BIT_WIDTH; width; --width) number <<= 1u;
            }

            number |= static_cast<type>(this -> low);
            return number;
        }
};

// ...
template <typename uint_t>
char const* stringify(uint_t number) {
    static char string[21] = {0};
    char *iterator = string + 20;

    for (*--iterator = '0'; number; number /= 10u)
    *(iterator--) = "0123456789"[static_cast<unsigned char>(number % 10u)];

    return static_cast<char const*>(iterator + (20 != iterator - string));
}

template <typename uint_t>
char const* stringify(uint_extended_t<uint_t> number) {
    static char string[1025] = {0};

    char *iterator = string + (sizeof(string) / sizeof(char));
    uint_extended_t<uint_t> quotient;
    uint_extended_t<uint_t> const radix = uint_extended_t<uint_t>(0u, 10u);

    // ...
    for (*--iterator = '0'; false == number.isZero(); (number.high = quotient.high), number.low = quotient.low) {
        number.remainder(radix, &quotient);
        *(iterator--) = "0123456789"[static_cast<unsigned char>(number.low)];
    }

    return static_cast<char const*>(iterator + (1024 != iterator - string));
}

/* Main */
int main(void) {
    // 255
    uint8_t const UINT8_MAXIMUM = -1;
    std::printf("[1 << 8]: %s" "\r\n", stringify(UINT8_MAXIMUM));

    // 65535
    uint_extended_t<uint8_t> const UINT16_MAXIMUM = -1;
    std::printf("[1 << 16]: %s" "\r\n", stringify(UINT16_MAXIMUM));

    // 4294967295
    uint_extended_t<uint16_t> const UINT32_MAXIMUM = -1;
    std::printf("[1 << 32]: %s" "\r\n", stringify(UINT32_MAXIMUM));

    // 18446744073709551615
    uint_extended_t<uint32_t> const UINT64_MAXIMUM = -1;
    std::printf("[1 << 64]: %s" "\r\n", stringify(UINT64_MAXIMUM));

    // 340282366920938463463374607431768211455
    uint_extended_t<uint64_t> const UINT128_MAXIMUM = uint_extended_t<uint64_t>(-1, -1);
    std::printf("[1 << 128]: %s" "\r\n", stringify(UINT128_MAXIMUM));

    // 115792089237316195423570985008687907853269984665640564039457584007913129639935
    uint_extended_t<uint_extended_t<uint64_t> > const UINT256_MAXIMUM = uint_extended_t<uint_extended_t<uint64_t> >(
        uint_extended_t<uint64_t>(-1, -1),
        uint_extended_t<uint64_t>(-1, -1)
    );
    std::printf("[1 << 256]: %s" "\r\n", stringify(UINT256_MAXIMUM));

    // 13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095
    uint_extended_t<uint_extended_t<uint_extended_t<uint64_t> > > const UINT512_MAXIMUM = uint_extended_t<uint_extended_t<uint_extended_t<uint64_t> > >(
        uint_extended_t<uint_extended_t<uint64_t> >(uint_extended_t<uint64_t>(-1, -1), uint_extended_t<uint64_t>(-1, -1)),
        uint_extended_t<uint_extended_t<uint64_t> >(uint_extended_t<uint64_t>(-1, -1), uint_extended_t<uint64_t>(-1, -1))
    );
    std::printf("[1 << 512]: %s" "\r\n", stringify(UINT512_MAXIMUM));

    // 179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215
    uint_extended_t<uint_extended_t<uint_extended_t<uint_extended_t<uint64_t> > > > const UINT1024_MAXIMUM = uint_extended_t<uint_extended_t<uint_extended_t<uint_extended_t<uint64_t> > > >(
        uint_extended_t<uint_extended_t<uint_extended_t<uint64_t> > >(
            uint_extended_t<uint_extended_t<uint64_t> >(uint_extended_t<uint64_t>(-1, -1), uint_extended_t<uint64_t>(-1, -1)),
            uint_extended_t<uint_extended_t<uint64_t> >(uint_extended_t<uint64_t>(-1, -1), uint_extended_t<uint64_t>(-1, -1))
        ),

        uint_extended_t<uint_extended_t<uint_extended_t<uint64_t> > >(
            uint_extended_t<uint_extended_t<uint64_t> >(uint_extended_t<uint64_t>(-1, -1), uint_extended_t<uint64_t>(-1, -1)),
            uint_extended_t<uint_extended_t<uint64_t> >(uint_extended_t<uint64_t>(-1, -1), uint_extended_t<uint64_t>(-1, -1))
        )
    );
    std::printf("[1 << 1024]: %s" "\r\n", stringify(UINT1024_MAXIMUM));

    // ...
    return /* --> EXIT_SUCCESS */ 0x0;
}
