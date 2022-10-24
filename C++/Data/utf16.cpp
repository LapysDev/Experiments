#include <climits>
#include <cstdio>
#include <stdint.h>

#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 1418)
#endif

// ...
uint_least8_t get_utf16_codepoint_length(char16_t units[]) {
  return 1u + (static_cast<uint_fast16_t>(*units) > 0xD7FFu && static_cast<uint_fast16_t>(*units) < 0xE000u);
}

uint_least32_t get_utf16_codepoint_value(char16_t units[]) {
  uint_fast8_t const length = get_utf16_codepoint_length(units);
  if (length == 1u) return static_cast<uint_fast32_t>(*units);

  // ...
  uint_fast32_t const value = 0x10000uL + (
    ((static_cast<uint_fast16_t>(units[1]) - 0xDC00u)) +
    ((static_cast<uint_fast16_t>(units[0]) - 0xD800u) * 0x400u)
  );

  return value > 0x10FFFFuL ? static_cast<uint_least32_t>(-1) : value;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  // char16_t units[] = u"$"; // --> U+00024
  // char16_t units[] = u"€"; // --> U+020AC
  // char16_t units[] = u"𐐷"; // --> U+10437
  // char16_t units[] = u"𤭢"; // --> U+24B62
  char16_t units[] = u"💙";

  // ...
  for (char16_t const *unit = units; unit != units + (sizeof(units) / sizeof(char16_t)); ++unit)
  std::printf("0x%.4hX" " ", static_cast<unsigned short>(*unit));

  std::printf("(%hu)" "\r\n", get_utf16_codepoint_length(units));
  std::printf("0x%lX" "\r\n", static_cast<unsigned long>(get_utf16_codepoint_value(units)));
}
