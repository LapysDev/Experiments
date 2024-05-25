#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>
#include <version>

#if defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 181)
# pragma warning(disable: 1418)
#endif

/* ... */
#ifdef __cpp_user_defined_literals
  enum hash_t : uintmax_t {};

  // ...
  constexpr hash_t operator ""_hash(char const string[], std::size_t const length) noexcept {
    return static_cast<hash_t>(0u != length ? static_cast<unsigned char>(*string) + (operator ""_hash(string + 1, length - 1u) << CHAR_BIT) : 0u);
  }

  constexpr bool operator ==(hash_t const hash, char const string[]) noexcept {
    return 0u == static_cast<uintmax_t>(hash) ? '\0' == *string : '\0' == *string ? '\0' == static_cast<char>(hash & (((1u << CHAR_BIT) - 0u) + ((1u << CHAR_BIT) - 1u))) : static_cast<char>(hash & (((1u << CHAR_BIT) - 0u) + ((1u << CHAR_BIT) - 1u))) == *string && operator ==(static_cast<hash_t>(hash >> CHAR_BIT), string + 1);
  }

  constexpr bool operator ==(char const string[], hash_t const hash) noexcept {
    return operator ==(hash, string);
  }
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  constexpr hash_t tests[] = {"arithmetic"_hash, "custom"_hash, "limits"_hash};

  for (hash_t const test : tests)
  switch (test) {
    case tests[0]: /* → "arithmetic"_hash: */ std::printf("%ju"        "\r\n", "Lapys"_hash);                                         break;
    case tests[1]: /* → "custom"    _hash: */ std::printf("%ju == 1"   "\r\n", "B"_hash - "A"_hash);                                  break;
    case tests[2]: /* → "limits"    _hash: */ std::printf("%ju == %ju" "\r\n", "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"_hash, UINTMAX_MAX); break;
  }

  std::puts("Lapys" == "Lapys"_hash ? "true" : "false");
}
