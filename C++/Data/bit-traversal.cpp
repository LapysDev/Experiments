#include <cstddef>
#include <climits>
#include <cstdio>
#include <inttypes.h>
#include <stdint.h>

/* ... */
enum endianness {
  big_endian,
  little_endian
};

// ...
template <unsigned char width, enum endianness endian /* = little_endian */, std::size_t capacity>
/* constexpr */ uintmax_t at(unsigned char const (&bytes)[capacity], unsigned char index) /* noexcept */ {
  if (CHAR_BIT == width)
  return bytes[index];

  if (CHAR_BIT > width)
  switch (endian) {
    case big_endian:
      return width <= CHAR_BIT - ((width * index) % CHAR_BIT) ? (
        // ->> single byte partition
        bytes[(width * index) / CHAR_BIT] >>
        (CHAR_BIT - width - ((width * index) % CHAR_BIT))
      ) & (static_cast<unsigned char>(1u << width) - 1u) : (
        // ->> low bits (multi-byte partition)
        (index + 1u != capacity ? bytes[(width * (index + 1u)) / CHAR_BIT] >> (CHAR_BIT - ((width * (index + 1u)) % CHAR_BIT)) : 0x00u) |

        // ->> high bits (multi-byte partition)
        ((bytes[(width * (index + 0u)) / CHAR_BIT] & ((1u << (CHAR_BIT - ((width * (index + 0u)) % CHAR_BIT))) - 1u)) << ((width * (index + 1u)) % CHAR_BIT))
      );

    case little_endian:
      return (
        // ->> low bits
        (bytes[(width * index) / CHAR_BIT] >> ((width * index) % CHAR_BIT)) & ((1u << width) - 1u)
      ) | (width > CHAR_BIT - ((width * (index + 0u)) % CHAR_BIT) && CHAR_BIT * capacity > width * (index + 1u)
        // ->> high bits (multi-byte partition)
        ? (bytes[(width * (index + 1u)) / CHAR_BIT] & ((1u << ((width * (index + 1u)) % CHAR_BIT)) - 1u)) << (CHAR_BIT - ((width * index) % CHAR_BIT))
        : 0x00u
      );
  }

  if (CHAR_BIT < width) {
    unsigned char offset   = CHAR_BIT - ((width * index) % CHAR_BIT);
    unsigned char subwidth = width - offset;
    uintmax_t     byte     = bytes[(width * index) / CHAR_BIT] & (
      // --> (1u << (CHAR_BIT - ((width * index) % CHAR_BIT))) - 1u
      ((1u << ((CHAR_BIT - ((width * index) % CHAR_BIT)) - 1u)) - 0u) +
      ((1u << ((CHAR_BIT - ((width * index) % CHAR_BIT)) - 1u)) - 1u)
    );

    // ...
    for (index = ((width * index) / CHAR_BIT) + 1u; ; ++index, subwidth -= CHAR_BIT)
    switch (endian) {
      case big_endian:
        if (CHAR_BIT >= subwidth)
        return (byte << subwidth) | (capacity != index ? bytes[index] >> (CHAR_BIT - subwidth) : 0x00u);

        byte = (byte << CHAR_BIT) | bytes[index];
        break;

      case little_endian:
        if (CHAR_BIT >= subwidth)
        return byte | (capacity != index ? (bytes[index] >> (CHAR_BIT - subwidth)) << offset : 0x00u);

        byte    |= bytes[index] << offset;
        offset  += CHAR_BIT;
    }
  }

  return 0x00u;
}

template <unsigned char width, std::size_t capacity>
/* constexpr */ uintmax_t at(unsigned char const (&bytes)[capacity], unsigned char const index) /* noexcept(noexcept(at<width, little_endian, capacity>(bytes, index))) */ {
  return at<width, little_endian, capacity>(bytes, index);
}

// ...
template <unsigned char width, enum endianness endian /* = little_endian */, std::size_t capacity>
void traverse(unsigned char const (&bytes)[capacity]) /* noexcept */ {
  for (std::size_t index = 0u; CHAR_BIT * capacity > index * width; ++index) {
    uintmax_t const byte          = at<width, endian>(bytes, index);
    char            source[width] = {};

    // ...
    for (uintmax_t subbyte = byte, subindex = width; subindex; subbyte >>= 1u)
    source[--subindex] = subbyte & 0x1u ? '1' : '0';

    std::printf("%3s%lu%5s%1.*s%2s%lu", "  [", static_cast<unsigned long>(index), "]: 0b", width, source, " (", static_cast<unsigned long>(byte));
    #ifdef UINT8_MAX // ->> risk invalid pointer dereference
      if (width == 8u) std::printf("%2s%" PRIu8, ", ", reinterpret_cast<uint8_t const*>(bytes)[index]);
    #endif
    #ifdef UINT16_MAX
      if (width == 16u) std::printf("%2s%" PRIu16, ", ", reinterpret_cast<uint16_t const*>(bytes)[index]);
    #endif
    #ifdef UINT32_MAX
      if (width == 32u) std::printf("%2s%" PRIu32, ", ", reinterpret_cast<uint32_t const*>(bytes)[index]);
    #endif
    #ifdef UINT64_MAX
      if (width == 64u) std::printf("%2s%" PRIu64, ", ", reinterpret_cast<uint64_t const*>(bytes)[index]);
    #endif
    std::printf("%3s", ")" "\r\n");
  }
}

template <unsigned char width, std::size_t capacity>
void traverse(unsigned char const (&bytes)[capacity]) /* noexcept(noexcept(traverse<width, little_endian, capacity>(bytes))) */ {
  return traverse<width, little_endian, capacity>(bytes);
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  unsigned char const bytes[] = {0xF0u, 0xE0u, 0xD0u, 0xC0u, 0xB0u, 0xA0u, 0x90u, 0x80u, 0x70u, 0x60u, 0x50u};

  std::printf("{%u}" "\r\n", CHAR_BIT);      traverse     <CHAR_BIT>(bytes);
  std::printf("{%u}" "\r\n", 1u);            traverse           <1u>(bytes);
  std::printf("{%u}" "\r\n", CHAR_BIT / 2u); traverse<CHAR_BIT / 2u>(bytes);
  std::printf("{%u}" "\r\n", CHAR_BIT * 2u); traverse<CHAR_BIT * 2u>(bytes);
}
