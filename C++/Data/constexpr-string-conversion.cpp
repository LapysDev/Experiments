#include <cstddef>
#include <cstdio>

/* ... */
namespace {
  template <std::size_t count, std::size_t... indexes> struct index_sequence : index_sequence<count - 1u, count - 1u, indexes...> {};
  template <std::size_t... indexes> struct index_sequence<0u, indexes...> {};

  template <std::size_t capacity>
  struct string {
    char value[capacity];

    constexpr string() : value{} {}
    constexpr string(string<capacity> const& copy) : string(copy.value, index_sequence<capacity>()) {}
    template <std::size_t... indexes> constexpr string(char const (&string)[capacity], index_sequence<0u, indexes...> const) : value{string[indexes]...} {}
    template <typename... types> constexpr string(char const character, types const... characters) : value{character, characters...} {}
  };

  // ...
  constexpr unsigned char len(unsigned const number) { return 0u != number ? 1u + len(number / 10u) : 0u; }

  template <std::size_t capacity> constexpr string<capacity> reverse(string<capacity> const& string) { return reverse<capacity>(string, index_sequence<capacity>()); }
  template <std::size_t capacity, std::size_t... indexes> constexpr string<capacity> reverse(string<capacity> const& string, index_sequence<0u, indexes...> const) { return ::string<capacity>(string.value[capacity - indexes - 1u]...); }

  template <std::size_t capacity> constexpr string<capacity> slice(unsigned char const) { return string<capacity>(); }
  template <std::size_t capacity, typename... types> constexpr string<capacity> slice(unsigned char const length, char const character, types const... characters) { return 0u != length ? slice<capacity>(length - 1u, characters...) : string<capacity>(character, characters...); }
  template <std::size_t capacity, std::size_t... indexes> constexpr string<capacity> slice(unsigned char const length, string<capacity> const& string, index_sequence<0u, indexes...> const) { return slice<capacity>(length, string.value[indexes]...); }
  template <std::size_t capacity> constexpr string<capacity> slice(unsigned char const length, string<capacity> const& string) { return slice(length, string, index_sequence<capacity>()); }
}

// ...
constexpr string<19u> str(unsigned const number, string<19u> string, unsigned char length) { return 0u != number ? ((string.value[19u - length - 1u] = "0123456789"[number % 10u]), str(number / 10u, string, length + 1u)) : string; }
constexpr string<19u> str(unsigned const number) { return slice(19u - len(number), str(number, string<19u>(), 0u)); }

/* Main */
int main() {
  std::printf("[]: \"%.19s\"" "\r\n", str(420u).value);
}
