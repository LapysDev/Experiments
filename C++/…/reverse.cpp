#include <climits>
#include <cstdio>
#include <inttypes.h>
#include <stdint.h>

/* … */
uint_least16_t reverse_bytes(uint_least16_t integer) {
  uint_least16_t value = 0u;

  // …
  for (unsigned char
    *destination = reinterpret_cast<unsigned char*>(&value),
    *source      = reinterpret_cast<unsigned char*>(&integer) + sizeof integer
  ; source != reinterpret_cast<unsigned char*>(&integer); )
  *(destination++) = *(--source);

  return value;
}

constexpr uint_least16_t reverse_endian(uint_least16_t integer) {
  uint_least16_t value = 0u;

  // …
  for (std::size_t count = sizeof(uint_least16_t); count--; ) {
    value = (integer & UCHAR_MAX) | (value << CHAR_BIT);
    integer >>= CHAR_BIT;
  }

  return value;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  uint_least16_t const integer = 42u;

  (void) std::printf("[bytes] : %" PRIuLEAST16 "\r\n", reverse_bytes (integer));
  (void) std::printf("[endian]: %" PRIuLEAST16 "\r\n", reverse_endian(integer));
}
