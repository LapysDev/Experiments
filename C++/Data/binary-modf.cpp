/* Import > C Standard Library */
#include <cfloat>  // C Floating-point
#include <climits> // C Limits
#include <cstdio>  // C Standard Input/ Output

#include <cmath>
#include <iostream>

/* ... */
constexpr bool check_squared(long double const number, long double const compare, int const bit) noexcept {
  return bit < 13 ? number >= compare * compare : false;
}

constexpr int getexp_bits(long double const number, long double const compare, int const bit) noexcept {
  return false == check_squared(number, compare, bit) ? (
    number >= compare ? (1 << bit) | getexp_bits(number / compare, 2.0L, 0) : 0
  ) : getexp_bits(number, compare * compare, bit + 1);
}

constexpr int getexp(long double const number) {
  return getexp_bits(number, 2.0L, 0);
}

long double twos_power(unsigned long long exponent) noexcept {
  long double factor = 2.0L;
  long double result = 1.0L;

  while (exponent) {
    result *= exponent & 1u ? factor : 1.0L;

    exponent >>= 1u;
    factor *= factor;
  }

  return result;
}

long double binary_to_decimal() {}

// binary_to_decimal(m_binary, e_binary)
//   e_dec_full = e_binary*log(2)/log(10)
//   e_decimal = floor(e_dec_full)
//   m_decimal = m_binary*pow(10, e_dec_full-e_decimal)

/* Main */
int main() {
  // constexpr long double number = LDBL_MAX;
  // constexpr int characteristics = getexp(number);
  // constexpr long double mantissa = number / pow(2, characteristics);

  // std::fixed(std::cout);
  // std::cout << characteristics << '.' << mantissa;
  // std::fixed(std::cout);

  // for (unsigned char exponent = 0u; exponent <= 64u; ++exponent)
  // std::cout << '[' << static_cast<unsigned short>(exponent) << "]: " << power(2uLL, exponent) << ", " << ::pow(2.0, static_cast<double>(exponent)) << "\r\n";
}
