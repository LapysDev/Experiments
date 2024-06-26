#include <climits>
#include <cstdio>
#include <stdint.h>

#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 1418)
#endif

// ...
unsigned char get_utf32_codepoint_length(char32_t[]) {
  return 1u;
}

uint_least32_t get_utf32_codepoint_value(char32_t units[]) {
  return static_cast<uint_least32_t>(*units);
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  // char32_t units[] = U"$"; // --> U+00024
  // char32_t units[] = U"€"; // --> U+020AC
  // char32_t units[] = U"𐐷"; // --> U+10437
  // char32_t units[] = U"𤭢"; // --> U+24B62
  char32_t units[] = U"💙";

  // ...
  for (char32_t const *unit = units; unit != units + (sizeof(units) / sizeof(char32_t)); ++unit)
  std::printf("0x%.8lX" " ", static_cast<unsigned long>(*unit));

  std::printf("(%hhu)" "\r\n", get_utf32_codepoint_length(units));
  std::printf("0x%llX" "\r\n", static_cast<unsigned long long>(get_utf32_codepoint_value(units)));
}
