#include <climits>
#include <cstdio>
#include <stdint.h>

#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 1418)
#endif

/* ... */
uint_least8_t get_utf8_codepoint_length(char units[]) {
  unsigned char const value = static_cast<unsigned char>(*units - '\0');

  // ...
  if (/* value >= 0x00u && */ value <= 0x7Fu) return 1u;
  else if  (value >= 0xC0u && value <= 0xDFu) return 2u;
  else if  (value >= 0xE0u && value <= 0xEFu) return 3u;
  else if  (value >= 0xF0u && value <= 0xF7u) return 4u;

  return static_cast<uint_least8_t>(-1);
}

uint_least32_t get_utf8_codepoint_value(char* units) {
  uint_fast8_t length = get_utf8_codepoint_length(units);

  // ...
  if (length != 1u) {
    uint_fast32_t value;

    // ...
    switch (length) {
      case 2u: {
        if ((static_cast<unsigned char>(*units - '\0') & 0xE0u) != 0xC0u) return static_cast<uint_least32_t>(-1);
        value = static_cast<unsigned char>(*units - '\0') & 0x1Fu;
      } break;

      case 3u: {
        if ((static_cast<unsigned char>(*units - '\0') & 0xF0u) != 0xE0u) return static_cast<uint_least32_t>(-1);
        value = static_cast<unsigned char>(*units - '\0') & 0x0Fu;
      } break;

      case 4u: {
        if ((static_cast<unsigned char>(*units - '\0') & 0xF8u) != 0xF0u) return static_cast<uint_least32_t>(-1);
        value = static_cast<unsigned char>(*units - '\0') & 0x07u;
      } break;

      default:
        return static_cast<uint_least32_t>(-1);
    }

    for (++units; --length; ++units) { // ->> parse continuation bytes
      if ((static_cast<unsigned char>(*units - '\0') & 0xC0u) != 0x80u) return static_cast<uint_least32_t>(-1);

      value <<= 6u;
      value |= static_cast<unsigned char>(*units - '\0') & 0x3Fu;
    }

    if ( // ->> overlong-encoding protection (converts Unicode ID to bytes)
      value < 0x0800uL ?
        static_cast<unsigned char>(units[-2] - '\0') != (0xC0u | ((value & 0x7C0uL) >> 6u * 1u)) ||
        static_cast<unsigned char>(units[-1] - '\0') != (0x80u | ((value & 0x03FuL) >> 6u * 0u)) :
      value < 0x10000uL ?
        static_cast<unsigned char>(units[-3] - '\0') != (0xE0u | ((value & 0xF000uL) >> 6u * 2u)) ||
        static_cast<unsigned char>(units[-2] - '\0') != (0x80u | ((value & 0x0FC0uL) >> 6u * 1u)) ||
        static_cast<unsigned char>(units[-1] - '\0') != (0x80u | ((value & 0x003FuL) >> 6u * 0u)) :
      value < 0x110000uL ?
        static_cast<unsigned char>(units[-4] - '\0') != (0xF0u | ((value & 0x1C0000uL) >> 6u * 3u)) ||
        static_cast<unsigned char>(units[-3] - '\0') != (0x80u | ((value & 0x03F000uL) >> 6u * 2u)) ||
        static_cast<unsigned char>(units[-2] - '\0') != (0x80u | ((value & 0x000FC0uL) >> 6u * 1u)) ||
        static_cast<unsigned char>(units[-1] - '\0') != (0x80u | ((value & 0x00003FuL) >> 6u * 0u)) :
      true
    ) return static_cast<uint_least32_t>(-1);

    // ...
    return value;
  }

  return static_cast<unsigned char>(*units - '\0') & 0x7Fu;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  // char units[] = "$"; // --> U+00024
  // char units[] = "£"; // --> U+000A3
  // char units[] = "€"; // --> U+020AC
  // char units[] = "𐍈"; // --> U+10348
  char units[] = "💙";

  // ...
  for (char *unit = units; unit != units + (sizeof(units) / sizeof(char)); ++unit)
  std::printf("0x%.2hX" " ", static_cast<unsigned char>(*unit - '\0'));

  std::printf("(%hu)" "\r\n", get_utf8_codepoint_length(units));
  std::printf("0x%lX" "\r\n", static_cast<unsigned long>(get_utf8_codepoint_value(units)));
}
