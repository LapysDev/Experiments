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
      }
    }

    // ...
    return bits;
  }

  template <unsigned char destinationWidth, unsigned char sourceWidth, enum endianness endian>
  inline static void set_bits(unsigned char* destinationBytes, std::size_t const destinationLength, std::size_t const index, unsigned char const sourceBytes[], std::size_t const sourceLength) /* noexcept(noexcept(get_bits(...))) */ {
    // int (&assertion())[destinationWidth < CHAR_BIT * sizeof(uintmax_t) && sourceWidth < CHAR_BIT * sizeof(uintmax_t)];
    if (CHAR_BIT * destinationLength <= index * destinationWidth) return; // ->> out of bounds
    uintmax_t sourceValue = byte::get_bits<sourceWidth, endian>(sourceBytes, sourceLength, 0u) & (((1u << (destinationWidth - 1u)) - 0u) + ((1u << (destinationWidth - 1u)) - 1u));

    // ...
    if (CHAR_BIT == destinationWidth)
      destinationBytes[index] = sourceValue /* --> sourceValue & UCHAR_MAX */;

    else {
      std::size_t const destinationBytesIndex  = (destinationWidth * index) / CHAR_BIT;
      std::size_t const destinationBytesOffset = (destinationWidth * index) % CHAR_BIT;

      // ...
      destinationBytes += destinationBytesIndex;

      if (CHAR_BIT > destinationWidth)
      switch (endian) {
        case byte::big_endian: break;
        case byte::little_endian: break;
      }

      else /* if (CHAR_BIT < destinationWidth) */ {
        unsigned char count = destinationWidth - (CHAR_BIT - destinationBytesOffset);

        // ...
        *destinationBytes &= (1u << destinationBytesOffset) - 1u;
        *destinationBytes |= (sourceValue & ((1u << (CHAR_BIT - destinationBytesOffset)) - 1u)) << destinationBytesOffset;

        for (; CHAR_BIT < count; count -= CHAR_BIT) {
          *(destinationBytes++) = sourceValue;
          sourceValue         >>= CHAR_BIT;
        }

        *destinationBytes &= (1u << (CHAR_BIT - count)) - 1u;
        *destinationBytes |= sourceValue << (CHAR_BIT - count);
      }
    }
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  unsigned char destination[8] = {0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u};

  // byte::set_bits<CHAR_BIT, 17u, byte::little_endian>(reinterpret_cast<unsigned char*>(destination), sizeof(destination), 0u, reinterpret_cast<unsigned char const*>("Hello, World!"), 14u);

  for (unsigned char *byte = destination; byte != destination + (sizeof(destination) / sizeof(unsigned char)); ++byte)
  std::printf("[%lu]: %s" "\r\n", static_cast<unsigned long>(byte - destination), integer::to_radix<2u>(*byte));
}
