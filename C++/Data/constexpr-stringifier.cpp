/* ... */
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>

/* Namespace > Standard */
namespace std {
  template <std::size_t length, typename char_t = char>
  struct const_string {
    private:
      template <typename type, std::size_t capacity> // smaller
      constexpr const_string(type (&string)[capacity], std::byte (*const)[1 + false]) noexcept(true) {}

      template <typename type, std::size_t capacity> // bigger
      constexpr const_string(type (&string)[capacity], std::byte (*const)[1 + true]) noexcept(true) {}

    public:
      constexpr const_string() noexcept(noexcept(char_t{})) {}

      template <typename type, std::size_t capacity>
      constexpr const_string(type (&string)[capacity]) noexcept(true) :
        const_string<length, char_t>::const_string(string, static_cast<std::byte (*)[1 + (capacity > length)]>(NULL))
      {}
  };

  template <typename char_t>
  struct const_string<0u, char_t>;
}

/* Main */
int main() {}
