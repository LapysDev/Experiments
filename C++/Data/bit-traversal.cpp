#include <cstddef>
#include <climits>
#include <cstdio>
#include <inttypes.h>
#include <stdint.h>

/* ... ->> Little-endian */
template <unsigned char width>
uintmax_t at(unsigned char const bytes[], std::size_t const length, unsigned char index) /* noexcept */ {
  if (CHAR_BIT == width)
  return bytes[index];

  if (CHAR_BIT > width)
  return (
    // ->> low bits
    (bytes[(width * index) / CHAR_BIT] >> ((width * index) % CHAR_BIT)) & ((1u << width) - 1u)
  ) | (width > CHAR_BIT - ((width * (index + 0u)) % CHAR_BIT) && CHAR_BIT * length > width * (index + 1u)
    // ->> high bits
    ? (bytes[(width * (index + 1u)) / CHAR_BIT] & ((1u << ((width * (index + 1u)) % CHAR_BIT)) - 1u)) << (CHAR_BIT - ((width * index) % CHAR_BIT))
    : 0x00u
  );

  if (CHAR_BIT < width) {
    unsigned char offset   = CHAR_BIT - ((width * index) % CHAR_BIT);
    unsigned char subwidth = width - offset;
    uintmax_t     byte     = bytes[(width * index) / CHAR_BIT] & (
      // --> (1u << (CHAR_BIT - ((width * index) % CHAR_BIT))) - 1u
      ((1u << ((CHAR_BIT - ((width * index) % CHAR_BIT)) - 1u)) - 0u) +
      ((1u << ((CHAR_BIT - ((width * index) % CHAR_BIT)) - 1u)) - 1u)
    );

    // ...
    for (index = ((width * index) / CHAR_BIT) + 1u; ; ++index) {
      if (CHAR_BIT >= subwidth)
      return byte | (index != length ? (bytes[index] >> (CHAR_BIT - subwidth)) << offset : 0x00u);

      byte     |= bytes[index] << offset;
      offset   += CHAR_BIT;
      subwidth -= CHAR_BIT;
    }
  }

  return 0x00u;
}

template <unsigned char width>
void traverse(unsigned char const bytes[], std::size_t const length) /* noexcept */ {
  for (std::size_t index = 0u; CHAR_BIT * length > index * width; ++index) {
    uintmax_t const byte          = at<width>(bytes, length, index);
    char            source[width] = {};

    // ...
    for (uintmax_t subbyte = byte, subindex = width; subindex; subbyte >>= 1u)
    source[--subindex] = subbyte & 0x1u ? '1' : '0';

    std::printf("%3s%lu%5s%1.*s%2s%lu", "  [", static_cast<unsigned long>(index), "]: 0b", width, source, " (", static_cast<unsigned long>(byte));
    #ifdef UINT8_MAX
      if (width == 8u) std::printf("%2s%" PRIu8, ", ", reinterpret_cast<uint8_t const*>(bytes)[index * sizeof(uint8_t)]);
    #endif
    #ifdef UINT16_MAX
      if (width == 16u) std::printf("%2s%" PRIu16, ", ", reinterpret_cast<uint16_t const*>(bytes)[index * sizeof(uint16_t)]);
    #endif
    #ifdef UINT32_MAX
      if (width == 32u) std::printf("%2s%" PRIu32, ", ", reinterpret_cast<uint32_t const*>(bytes)[index * sizeof(uint32_t)]);
    #endif
    #ifdef UINT64_MAX
      if (width == 64u) std::printf("%2s%" PRIu64, ", ", reinterpret_cast<uint64_t const*>(bytes)[index * sizeof(uint64_t)]);
    #endif
    std::printf("%3s", ")" "\r\n");
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  unsigned char const bytes[] = {0xF0u, 0xE0u, 0xD0u, 0xC0u, 0xB0u, 0xA0u, 0x90u, 0x80u, 0x70u, 0x60u, 0x50u};

  std::printf("{%u}" "\r\n", CHAR_BIT);      traverse     <CHAR_BIT>(bytes, sizeof(bytes) / sizeof(unsigned char));
  std::printf("{%u}" "\r\n", 1u);            traverse           <1u>(bytes, sizeof(bytes) / sizeof(unsigned char));
  std::printf("{%u}" "\r\n", CHAR_BIT / 2u); traverse<CHAR_BIT / 2u>(bytes, sizeof(bytes) / sizeof(unsigned char));
  std::printf("{%u}" "\r\n", CHAR_BIT * 2u); traverse<CHAR_BIT * 2u>(bytes, sizeof(bytes) / sizeof(unsigned char));
}
