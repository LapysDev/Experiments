#include <climits>
#include <cstdio>
#include <stdint.h>
#if __cplusplus >= 202002L || _MSVC_LANG >= 202002L
# include <version>
#endif

/* ... */
uint_least8_t get_utf8_codepoint_length(char const units[]) {
  unsigned char const value = static_cast<unsigned char>(*units);

  // ...
  if (/* value >= 0x00u && */ value <= 0x7Fu) return 1u;
  else if  (value >= 0xC0u && value <= 0xDFu) return 2u;
  else if  (value >= 0xE0u && value <= 0xEFu) return 3u;
  else if  (value >= 0xF0u && value <= 0xF7u) return 4u;

  return -1;
}

uint_least32_t get_utf8_codepoint_value(char const units[]) {
  uint_fast8_t length = get_utf8_codepoint_length(units);
  if (length == 1u) return static_cast<unsigned char>(*units) & 0x7Fu;

  /* ... */
  uint_fast32_t value;

  // ...
  switch (length) {
    case 2u: {
      if ((static_cast<unsigned char>(*units) & 0xE0u) != 0xC0u) return -1;
      value = static_cast<unsigned char>(*units) & 0x1Fu;
    } break;

    case 3u: {
      if ((static_cast<unsigned char>(*units) & 0xF0u) != 0xE0u) return -1;
      value = static_cast<unsigned char>(*units) & 0x0Fu;
    } break;

    case 4u: {
      if ((static_cast<unsigned char>(*units) & 0xF8u) != 0xF0u) return -1;
      value = static_cast<unsigned char>(*units) & 0x07u;
    } break;

    default: return -1;
  }

  for (++units; --length; ++units) {
    if ((static_cast<unsigned char>(*units) & 0xC0u) != 0x80u) return -1;

    value <<= 6u;
    value |= static_cast<unsigned char>(*units) & 0x3Fu;
  }

  // ... ->> overlong?
  return value > 0x10FFFFuL ? -1 : value;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  // char const units[] = "$"; // --> U+0024
  // char const units[] = "£"; // --> U+00A3
  // char const units[] = "€"; // --> U+20AC
  // char const units[] = "𐍈"; // --> U+10348
  // char const units[] = "💙";
  // char const units[] = {static_cast<char>(0b11110000u), static_cast<char>(0b10000010u), static_cast<char>(0b10000010u), static_cast<char>(0b10101100u)};

  // ...
  for (char const *byte = units; byte != units + (sizeof(units) / sizeof(char)); ++byte)
  std::printf("0x%.2hX" " ", static_cast<unsigned char>(*byte));

  std::printf("(%hu)" "\r\n", get_utf8_codepoint_length(units));
  std::printf("0x%lX" "\r\n", static_cast<unsigned long>(get_utf8_codepoint_value(units)));
}
