#include <cstddef>
#include <cstdio>
#include <stdexcept>

/* ... */
#if defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 411)
# pragma warning(disable: 1418)
#endif

/* ... */
namespace literal_methods {
  struct at final {
    char const *const string;
    std::size_t const length;

    constexpr char operator ()(std::size_t const index) const /* throw(std::out_of_range) */ {
      return index < this -> length ? this -> string[index] : ((throw std::out_of_range("invalid string index")), '\0');
    }
  };

  struct find final {
    char const *const string;
    std::size_t const length;

    constexpr std::size_t operator ()(char const character) const noexcept {
      for (char const *iterator = this -> string; length != static_cast<std::size_t>(iterator - this -> string); ++iterator)
      if (character == *iterator) return iterator - this -> string;

      return static_cast<std::size_t>(-1);
    }
  };
}

constexpr literal_methods::at   operator ""_at  (char const string[], std::size_t const length) noexcept(false) { return {string, length}; }
constexpr literal_methods::find operator ""_find(char const string[], std::size_t const length) noexcept(true)  { return {string, length}; }

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::printf("%c"  "\r\n", "Hello, World!"_at(0u));
  std::printf("%zu" "\r\n", "Hello, World!"_find('H'));
}
