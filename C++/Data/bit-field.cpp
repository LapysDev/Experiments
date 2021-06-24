#include <stdint.h>

#include <climits>
#include <cstdio>

/* ... */
namespace {
    template <bool, typename, typename> union uint_conditional_t;
    template <typename true_t, typename false_t> union uint_conditional_t<true , true_t, false_t> { typedef true_t  type; };
    template <typename true_t, typename false_t> union uint_conditional_t<false, true_t, false_t> { typedef false_t type; };
}

template <std::size_t> union bit;
typedef bit<8u> byte; // octet

template <std::size_t count>
union bit {
    private:
        typedef
          typename uint_conditional_t<
            count <= (CHAR_BIT * sizeof(uint8_t)), uint8_t,
          typename uint_conditional_t<
            count <= (CHAR_BIT * sizeof(uint16_t)), uint16_t,
          typename uint_conditional_t<
            count <= (CHAR_BIT * sizeof(uint32_t)), uint32_t,
          typename uint_conditional_t<
            count <= (CHAR_BIT * sizeof(uint64_t)), uint64_t,
            unsigned char [(count / CHAR_BIT) + (count % CHAR_BIT)]
          >::type >::type >::type >::type
        bit_t;

        bit_t value : count;

    public:
        bit(void) : value() {}
        bit(bit_t const value) : value(value) {}

        // ...
        // friend bit<count>& operator += (bit<count>& a, bit<count> const b);
        // friend bit<count>& operator -= (bit<count>& a, bit<count> const b);
        // friend bit<count>& operator *= (bit<count>& a, bit<count> const b);
        // friend bit<count>& operator /= (bit<count>& a, bit<count> const b);
        // friend bit<count>& operator %= (bit<count>& a, bit<count> const b);
        friend bit<count>& operator &= (bit<count>& a, bit<count> const b) { a.value &=  b.value; return a; }
        friend bit<count>& operator |= (bit<count>& a, bit<count> const b) { a.value |=  b.value; return a; }
        friend bit<count>& operator ^= (bit<count>& a, bit<count> const b) { a.value ^=  b.value; return a; }
        friend bit<count>& operator <<=(bit<count>& a, bit<count> const b) { a.value <<= b.value; return a; }
        friend bit<count>& operator >>=(bit<count>& a, bit<count> const b) { a.value >>= b.value; return a; }
        // friend bit<count>& operator ++ (bit<count>&)           ;
        // friend bit<count>  operator ++ (bit<count>&, int const);
        // friend bit<count>& operator -- (bit<count>&)           ;
        // friend bit<count>  operator -- (bit<count>&, int const);

        /* explicit */ operator bit_t(void) { return this -> value; }
        /* explicit */ operator bit_t(void) const { return this -> value; }
};

/* Main */
int main(void) {
    std::printf("[1]: %hu" "\r\n", static_cast<unsigned char>(bit<1u>(-1)));
    std::printf("[2]: %hu" "\r\n", static_cast<unsigned char>(bit<2u>(-1)));
    std::printf("[3]: %hu" "\r\n", static_cast<unsigned char>(bit<3u>(-1)));
    std::printf("[4]: %hu" "\r\n", static_cast<unsigned char>(bit<4u>(-1)));
    std::printf("[5]: %hu" "\r\n", static_cast<unsigned char>(bit<5u>(-1)));
    std::printf("[6]: %hu" "\r\n", static_cast<unsigned char>(bit<6u>(-1)));
    std::printf("[7]: %hu" "\r\n", static_cast<unsigned char>(bit<7u>(-1)));
    std::printf("[8]: %hu" "\r\n", static_cast<unsigned char>(bit<8u>(-1)));

    std::puts("");
    std::printf("[16]: %hu" "\r\n", static_cast<uint16_t>(bit<16u>(-1)));
    std::printf("[32]: %u " "\r\n", static_cast<uint32_t>(bit<32u>(-1)));
    std::printf("[64]: %lu" "\r\n", static_cast<uint64_t>(bit<64u>(-1)));
}
