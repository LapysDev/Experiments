/* ... */
#include <cstddef>
#include <climits>
#include <cstdio>
#include <stdint.h>

/* ... */
template <unsigned char width>
uintmax_t at(unsigned char const bytes[], std::size_t const length, unsigned char index) /* noexcept */ {
  if (CHAR_BIT == width)
  return bytes[index];

  if (CHAR_BIT > width)
  return // ... ->>
    width <= CHAR_BIT - ((width * index) % CHAR_BIT)                    // is within memory unit?
    ? (                                                                 // get bits:
      bytes[(width * index) / CHAR_BIT] >>                              //   memory unit
      (CHAR_BIT - width - ((width * index) % CHAR_BIT))                 //   shifted to relevant partition
    ) & (static_cast<unsigned char>(1u << width) - 1u)                  //   trimmed to `width` bits
    : (                                                                 // get bits:
      ((                                                                //   get high bits:
        bytes[(width * (index + 0u)) / CHAR_BIT] &                      //     memory unit
        ((1u << (CHAR_BIT - ((width * (index + 0u)) % CHAR_BIT))) - 1u) //     trimmed to relevant high partition
      ) << ((width * (index + 1u)) % CHAR_BIT))                         //     shifted accordingly in place
      |                                                                 //   get low bits:
      (index + 1u != length ?                                           //     is last memory unit?
        bytes[(width * (index + 1u)) / CHAR_BIT] >>                     //     (adjacent) memory unit
        (CHAR_BIT - ((width * (index + 1u)) % CHAR_BIT))                //     shifted to relevant low partition
      : 0x00u)                                                          //     fallback to zeroes
    );

  if (CHAR_BIT < width) {
    index *= width;

    unsigned char subwidth = width;
    uintmax_t     byte     = bytes[index / CHAR_BIT] & (
      // --> (1u << (CHAR_BIT - (index % CHAR_BIT))) - 1u
      ((1u << ((CHAR_BIT - (index % CHAR_BIT)) - 1u)) - 0u) +
      ((1u << ((CHAR_BIT - (index % CHAR_BIT)) - 1u)) - 1u)
    );

    // ...
    subwidth -= CHAR_BIT - (index % CHAR_BIT);
    index    /= CHAR_BIT;

    while (true) {                                                                                       //
      if (CHAR_BIT >= subwidth)                                                                          // (final) memory unit
      return (byte << subwidth) | (index + 1u != length ? bytes[++index] >> (CHAR_BIT - subwidth) : 0u); //
                                                                                                         //
      byte      = (byte << CHAR_BIT) | bytes[++index];                                                   // (contiguous) memory unit
      subwidth -= CHAR_BIT;                                                                              //
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

    std::printf("  [%lu]: 0b%1.*s (%lu)" "\r\n", static_cast<unsigned long>(index), width, source, static_cast<unsigned long>(byte));
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  unsigned char const bytes[] = {0xF0u, 0xE0u, 0xD0u, 0xC0u, 0xB0u, 0xA0u, 0x90u, 0x80u, 0x70u, 0x60u, 0x50u};

  std::printf("{%u}" "\r\n", CHAR_BIT);      traverse     <CHAR_BIT>(bytes, (sizeof(bytes) / sizeof(unsigned char)));
  std::printf("{%u}" "\r\n", 1u);            traverse           <1u>(bytes, (sizeof(bytes) / sizeof(unsigned char)));
  std::printf("{%u}" "\r\n", CHAR_BIT / 2u); traverse<CHAR_BIT / 2u>(bytes, (sizeof(bytes) / sizeof(unsigned char)));
  std::printf("{%u}" "\r\n", CHAR_BIT * 2u); traverse<CHAR_BIT * 2u>(bytes, (sizeof(bytes) / sizeof(unsigned char)));
}
