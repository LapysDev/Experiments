#include <climits>
#include <cstdio>
#include <stdint.h>
#if __cplusplus >= 202002L || _MSVC_LANG >= 202002L
# include <version>
#endif

/* ... */
uint_least8_t get_utf8_codepoint_length(char const unit[]) {
  unsigned char const value = static_cast<unsigned char>(*unit);

  // ...
  if (/* value >= 0x00u && */ value <= 0x7Fu) return 1u;
  else if  (value >= 0xC0u && value <= 0xDFu) return 2u;
  else if  (value >= 0xE0u && value <= 0xEFu) return 3u;
  else if  (value >= 0xF0u && value <= 0xF7u) return 4u;

  return -1;
}

// • a non-continuation byte before the end of the character
// • the string ending before the end of the character (which can happen in simple string truncation)
// • an overlong encoding
// • a sequence that decodes to an invalid code point

uint_least32_t get_utf8_codepoint_value(char const unit[]) {
  switch (get_utf8_codepoint_length(unit)) {
    (static_cast<unsigned char>(unit.next) & 0xC0u) == 0x80u

    case 1u: return static_cast<unsigned char>(*unit) & 0x7Fu;
    case 2u: return ((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 0u) | ((static_cast<unsigned char>(unit[0]) & 0x1Fu) << 6u);
    case 3u: return ((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 0u) | ((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 6u) | ((static_cast<unsigned char>(unit[0]) & 0x0Fu) << 12u);
    case 4u: return ((static_cast<unsigned char>(unit[3]) & 0x3Fu) << 0u) | ((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 6u) | ((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 12u) | ((static_cast<unsigned char>(unit[0]) & 0x07u) << 18u);
  }

  return -1;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  // char const unit[] = "$"; // --> U+0024
  // char const unit[] = "£"; // --> U+00A3
  // char const unit[] = "€"; // --> U+20AC
  // char const unit[] = "𐍈"; // --> U+10348
  char const unit[] = "💙";

  // ...
  for (char const *byte = unit; byte != unit + (sizeof(unit) / sizeof(char)); ++byte)
  std::printf("0x%.2X" " ", static_cast<unsigned char>(*byte));

  std::printf("(%hu)" "\r\n", get_utf8_codepoint_length(unit));
  std::printf("0x%lX" "\r\n", static_cast<unsigned long>(get_utf8_codepoint_value(unit)));
}
