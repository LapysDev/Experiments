//      [0]              [1]              [2]              [3]              [4]              [5]              [6]              [7]              [8]              [9]              [10]             [11]             [12]             [13]             [14]             [15]             [16]             [17]             [18]             [19]             [20]             [21]
// ...: AAAABBBB         CCCCDDDD         EEEEFFFF         GGGGHHHH         IIIIJJJJ         KKKKLLLL         MMMMNNNN         OOOOPPPP         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××
// 3B : AAA×××××         ABB×××××         BBC×××××         CCC×××××         DDD×××××         DEE×××××         EEF×××××         FFF×××××         GGG×××××         GHH×××××         HHI×××××         III×××××         JJJ×××××         JKK×××××         KKL×××××         LLL×××××         MMM×××××         MNN×××××         NNO×××××         OOO×××××         PPP×××××         P--×××××
// 3L : BBB×××××         AAB×××××         DAA×××××         DDD×××××         CCC×××××         FFC×××××         EFF×××××         EEE×××××         HHH×××××         GGH×××××         JGG×××××         JJJ×××××         III×××××         LLI×××××         KLL×××××         KKK×××××         NNN×××××         MMN×××××         PMM×××××         PPP×××××         OOO×××××         --O×××××
// 4B : AAAA××××         BBBB××××         CCCC××××         DDDD××××         EEEE××××         FFFF××××         GGGG××××         HHHH××××         IIII××××         JJJJ××××         KKKK××××         LLLL××××         MMMM××××         NNNN××××         OOOO××××         PPPP××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××
// 4L : BBBB××××         AAAA××××         DDDD××××         CCCC××××         FFFF××××         EEEE××××         HHHH××××         GGGG××××         JJJJ××××         IIII××××         LLLL××××         KKKK××××         NNNN××××         MMMM××××         PPPP××××         OOOO××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××
// 7B : AAAABBB×         BCCCCDD×         DDEEEEF×         FFFGGGG×         HHHHIII×         IJJJJKK×         KKLLLLM×         MMMNNNN×         OOOOPPP×         P------×         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××
// 7L : AAABBBB×         CCDDDDA×         EFFFFCC×         HHHHEEE×         JJJGGGG×         LLIIIIJ×         NKKKKLL×         MMMMNNN×         OOOOPPP×         ------P×         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××         ××××××××
// 9B : AAAABBBBC        CCCDDDDEE        EEFFFFGGG        GHHHHIIII        JJJJKKKKL        LLLMMMMNN        NNOOOOPPP        P--------        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××
// 9L : DAAAABBBB        FFCCCCDDD        HHHEEEEFF        JJJJGGGGH        KLLLLIIII        MMNNNNKKK        OOOPPPPMM        --------O        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××        ×××××××××
// 13B: AAAABBBBCCCCD    DDDEEEEFFFFGG    GGHHHHIIIIJJJ    JKKKKLLLLMMMM    NNNNOOOOPPPP-    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××
// 13L: CDDDDAAAABBBB    HHEEEEFFFFCCC    IIIJJJJGGGGHH    NNNNKKKKLLLLI    -OOOOPPPPMMMM    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××    ×××××××××××××
// 16B: AAAABBBBCCCCDDDD EEEEFFFFGGGGHHHH IIIIJJJJKKKKLLLL MMMMNNNNOOOOPPPP ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ××××××××××××××××
// 16L: CCCCDDDDAAAABBBB GGGGHHHHEEEEFFFF KKKKLLLLIIIIJJJJ OOOOPPPPMMMMNNNN ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ×××××××××××××××× ××××××××××××××××
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>

/* ... */
namespace integer {
  template <unsigned char radix>
  inline static char* to_radix(uintmax_t integer, char *source, std::size_t capacity) /* noexcept */ {
    int (&assertion())[0u != radix && radix < CHAR_BIT * sizeof(uintmax_t)];

    char       *iterator;
    static char string[CHAR_BIT * sizeof(uintmax_t) > 64u ? CHAR_BIT * sizeof(uintmax_t) : 64u];

    // ...
    if (0u == integer) {
      iterator    = NULL != source && capacity > 2u ? source : string;
      iterator[1] = '\0';
      iterator[0] = '0';

      return iterator;
    }

    for (iterator = string; ; integer /= radix) {
      if (0u == integer) {
        if (NULL != source && capacity > static_cast<std::size_t>(iterator - string)) {
          capacity = iterator - string;
          while (iterator != string) *(source++) = *--iterator;
          *source = '\0';

          return source - capacity;
        }

        *(iterator--) = '\0';
        source        = string;

        for (; iterator > source; --iterator, ++source) {
          *iterator ^= *source;
          *source   ^= *iterator;
          *iterator ^= *source;
        }

        return string;
      }

      *(iterator++) = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[integer % radix];
    }
  }

  template <unsigned char radix, std::size_t capacity>
  inline static char* to_radix(uintmax_t const integer, char (&source)[capacity]) /* noexcept(...) */ {
    return integer::to_radix<radix>(integer, source, capacity);
  }

  template <unsigned char radix>
  inline static char* to_radix(uintmax_t const integer) /* noexcept(...) */ {
    return integer::to_radix<radix>(integer, NULL, 0u);
  }
}

namespace byte {
  enum endianness {
    big_endian,
    little_endian
  };

  /* ... ->> assume `bytes`, `destinationBytes`, `destinationLength`, `destinationWidth`, `length`, `sourceBytes`, `sourceLength`, `sourceWidth`, and `width` are non-nil */
  template <unsigned char width, enum endianness endian>
  inline static uintmax_t get_bits(unsigned char const* bytes, std::size_t const length, std::size_t const index) /* noexcept */ {
    // int (&assertion())[width < CHAR_BIT * sizeof(uintmax_t)];
    if (CHAR_BIT * length <= index * width) return 0x00u;        // ->> out of bounds
    if (CHAR_BIT == width)                  return bytes[index]; // ->> aligned indexing

    /* ... */
    std::size_t       bytesIndex  = (index * width) / CHAR_BIT;
    std::size_t const bytesOffset = (index * width) % CHAR_BIT;

    if (CHAR_BIT > width)
    switch (endian) {
      case byte::big_endian:
        return 0u != CHAR_BIT % width && CHAR_BIT - bytesOffset < width ?
          // ->> dual-byte indexing
          (length - 1u > bytesIndex
            ? bytes[(bytesIndex) + 1u] >> (CHAR_BIT - (width - (CHAR_BIT - bytesOffset))) // ->> succeeding byte
            : 0x00u                                                                       // ->> out of bounds
          ) | (bytes[bytesIndex] & ((1u << (CHAR_BIT - bytesOffset)) - 1u)) << (width - (CHAR_BIT - bytesOffset)) :

          // ->> single-byte indexing
          ((bytes[bytesIndex] >> (CHAR_BIT - width - bytesOffset)) & ((1u << width) - 1u));

      case byte::little_endian:
        return ((bytes[bytesIndex] >> bytesOffset) & ((1u << width) - 1u)) | (
          // ->> dual-byte indexing
          0u != CHAR_BIT % width && CHAR_BIT - bytesOffset < width && length - 1u > bytesIndex
          ? (bytes[bytesIndex + 1u] & ((1u << (width - (CHAR_BIT - bytesOffset))) - 1u)) << (CHAR_BIT - bytesOffset) // ->> succeeding byte
          : 0x00u                                                                                                    // ->> out of bounds | single-byte indexing
        );
    }

    // ...
    uintmax_t     bits  = *(bytes += bytesIndex); // ->> start byte
    unsigned char count = width - (CHAR_BIT - bytesOffset);

    // if (CHAR_BIT < width)
    switch (endian) {
      case byte::big_endian: {
        for (bits &= ((1u << (CHAR_BIT - bytesOffset)) - 1u); CHAR_BIT < count; count -= CHAR_BIT) {
          if (length == ++bytesIndex) return bits << count; // ->> out of bounds
          bits = (bits << CHAR_BIT) | *++bytes;             // ->> continuation byte
        }

        bits = (bits << count) | (length != ++bytesIndex ? *++bytes >> (CHAR_BIT - count) : 0x00u); // ->> end byte
      } break;

      case byte::little_endian: {
        unsigned char offset = CHAR_BIT - bytesOffset;

        // ...
        for (bits >>= bytesOffset; CHAR_BIT < count; count -= CHAR_BIT) {
          if (length == ++bytesIndex) return bits; // ->> out of bounds
          bits   |= *++bytes << offset;            // ->> continuation byte
          offset += CHAR_BIT;
        }

        bits |= (length != ++bytesIndex ? *++bytes & ((1u << count) - 1u) : 0x00u) << offset; // ->> end byte
      } break;
    }

    // ...
    return bits;
  }

  template <unsigned char destinationWidth, enum endianness destinationEndian, unsigned char sourceWidth, enum endianness sourceEndian>
  inline static void set_bits(unsigned char* destinationBytes, std::size_t const destinationLength, std::size_t const index, unsigned char const sourceBytes[], std::size_t const sourceLength) /* noexcept(noexcept(get_bits(...))) */ {
    // int (&assertion())[destinationWidth < CHAR_BIT * sizeof(uintmax_t) && sourceWidth < CHAR_BIT * sizeof(uintmax_t)];
    if (CHAR_BIT * destinationLength <= index * destinationWidth) return; // ->> out of bounds
    uintmax_t sourceValue = byte::get_bits<sourceWidth, sourceEndian>(sourceBytes, sourceLength, 0u) & (((1u << (destinationWidth - 1u)) - 0u) + ((1u << (destinationWidth - 1u)) - 1u));

    // ...
    if (CHAR_BIT == destinationWidth)
      destinationBytes[index] = sourceValue; // --> sourceValue & UCHAR_MAX

    else {
      std::size_t       destinationBytesIndex  = (destinationWidth * index) / CHAR_BIT;
      std::size_t const destinationBytesOffset = (destinationWidth * index) % CHAR_BIT;

      // ...
      destinationBytes += destinationBytesIndex;

      if (CHAR_BIT > destinationWidth)
      switch (destinationEndian) {
        case byte::big_endian: {
          destinationBytes[0] &= (((1u << destinationBytesOffset) - 1u) << (CHAR_BIT - destinationBytesOffset)) | (((1u << (CHAR_BIT - destinationBytesOffset)) - 1u) >> destinationWidth);
          destinationBytes[0] |= sourceValue << (CHAR_BIT - destinationWidth - destinationBytesOffset); // --> (sourceValue << ...) & UCHAR_MAX

          if (0u != CHAR_BIT % destinationWidth && CHAR_BIT - destinationBytesOffset < destinationWidth) {
            destinationBytes[0] |= sourceValue >> (destinationBytesOffset - CHAR_BIT - destinationWidth);

            destinationBytes[1] &= (1u << (CHAR_BIT - (destinationWidth - (CHAR_BIT - destinationBytesOffset)))) - 1u;
            destinationBytes[1] |= sourceValue << (CHAR_BIT - (destinationWidth - (CHAR_BIT - destinationBytesOffset)));
          }
        } break;

        case byte::little_endian: {
          destinationBytes[0] &= ((1u << destinationBytesOffset) - 1u) | (((1u << (CHAR_BIT - destinationWidth)) - 1u) << (destinationBytesOffset + destinationWidth));
          destinationBytes[0] |= sourceValue << destinationBytesOffset; // --> (sourceValue << ...) & UCHAR_MAX

          if (0u != CHAR_BIT % destinationWidth && CHAR_BIT - destinationBytesOffset < destinationWidth && destinationLength - 1u > destinationBytesIndex) {
            destinationBytes[1] &= ((1u << (CHAR_BIT - (destinationWidth - (CHAR_BIT - destinationBytesOffset)))) - 1u) << (destinationWidth - (CHAR_BIT - destinationBytesOffset));
            destinationBytes[1] |= sourceValue >> (CHAR_BIT - destinationBytesOffset);
          }
        } break;
      }

      else /* if (CHAR_BIT < destinationWidth) */ {
        unsigned char count = destinationWidth - (CHAR_BIT - destinationBytesOffset);

        // ...
        switch (destinationEndian) {
          case byte::big_endian: {
            *destinationBytes &= ((1u << destinationBytesOffset) - 1u) << (CHAR_BIT - destinationBytesOffset);
            *destinationBytes |= sourceValue & ((1u << (CHAR_BIT - destinationBytesOffset)) - 1u);
          } break;

          case byte::little_endian: {
            *destinationBytes &= (1u << destinationBytesOffset) - 1u;
            *destinationBytes |= (sourceValue & ((1u << (CHAR_BIT - destinationBytesOffset)) - 1u)) << destinationBytesOffset;
          } break;
        }

        for (++destinationBytes, sourceValue >>= CHAR_BIT - destinationBytesOffset; CHAR_BIT < count; ++destinationBytes, count -= CHAR_BIT) {
          if (destinationLength == ++destinationBytesIndex) return; // ->> out-of-bounds
          *destinationBytes = sourceValue;                          // --> sourceValue & UCHAR_MAX
          sourceValue     >>= CHAR_BIT;
        }

        if (destinationLength == ++destinationBytesIndex) return; // ->> out-of-bounds
        switch (destinationEndian) {
          case byte::big_endian: {
            *destinationBytes &= (1u << (CHAR_BIT - count)) - 1u;
            *destinationBytes |= sourceValue /* --> sourceValue & count */ << (CHAR_BIT - count);
          } break;

          case byte::little_endian: {
            *destinationBytes &= ((1u << (CHAR_BIT - count)) - 1u) << count;
            *destinationBytes |= sourceValue; // --> sourceValue & count
          } break;
        }
      }
    }
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  for (std::size_t index = 0u; index != 7u; ++index) {
    unsigned char destination[8] = {0b11111111u, 0b11111111u, 0b11111111u, 0b11111111u, 0b11111111u, 0b11111111u, 0b11111111u, 0b11111111u};
    // unsigned char destination[8] = {0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u};

    // ...
    // byte::set_bits<3u, byte::little_endian, 8u, byte::little_endian>(destination, sizeof(destination) / sizeof(unsigned char), index, &static_cast<unsigned char const&>(0b1111111111111111111111111111111111111111111111111111111111111111uLL), sizeof(unsigned char));
    byte::set_bits<3u, byte::big_endian, 8u, byte::little_endian>(destination, sizeof(destination) / sizeof(unsigned char), index, &static_cast<unsigned char const&>(0b0000000000000000000000000000000000000000000000000000000000000000uLL), sizeof(unsigned char));

    std::printf("\r\n" "%lu" "\r\n", static_cast<unsigned long>(index));

    for (unsigned char *byte = destination; byte != destination + (sizeof(destination) / sizeof(unsigned char)); ++byte)
    std::printf("  [%lu]: %s" "\r\n", static_cast<unsigned long>(byte - destination), integer::to_radix<2u>(*byte));
  }
}
