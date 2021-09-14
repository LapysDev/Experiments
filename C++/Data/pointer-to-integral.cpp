#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>
#include <type_traits>

#if defined(__cplusplus) && __cplusplus >= 201402L && false == defined(__INTEL_COMPILER)
  template <typename type>
  constexpr uintptr_t to_integral(type* const pointer, type* const, type* const, std::size_t const, unsigned char const) noexcept {
    type *current = pointer;
    std::size_t increment = 1u;
    unsigned char incremented = 0u;
    type *recent = NULL;
    uintptr_t value = 0u;

    while (incremented < 16u) {
      recent = current;
      current -= increment;

      if (static_cast<type*>(NULL) > current || current > pointer) {
        current = recent;
        increment = 1u;
        incremented += 2u;
      }

      else {
        value += increment;
        increment *= increment > SIZE_MAX / 10u ? 2u : 10u;
        incremented -= 0u != incremented;
      }
    }

    return value;
  }
#else
  template <typename type>
  constexpr uintptr_t to_integral(type* const pointer, type* const current, type* const recent, std::size_t const increment, unsigned char const incremented) noexcept {
    return incremented < 16u ? (
      static_cast<type*>(NULL) > (current - increment) || (current - increment) > pointer
      ? to_integral(pointer, recent, static_cast<type*>(NULL), 1u, incremented + 2u) - (increment / (increment > SIZE_MAX / 10u ? 2u : 10u))
      : to_integral(pointer, current - increment, current, increment * (increment > SIZE_MAX / 10u ? 2u : 10u), incremented - (0u != incremented)) + increment
    ) : 10u;
  }
#endif

template <typename type>
constexpr uintptr_t to_integral(type* const pointer) noexcept {
  return
    #if defined(__cplusplus) && __cplusplus >= 202002L
      std::is_constant_evaluated()
    #elif defined(__builtin_is_constant_evaluated)
      __builtin_is_constant_evaluated()
    #else
      false
    #endif
  ? sizeof(type) * to_integral(pointer, pointer, static_cast<type*>(NULL), 1u, 0u)
  : reinterpret_cast<uintptr_t>(pointer);
}

int main() {
  constexpr static char const string[] = "Hello, World!";
  static uintptr_t address = to_integral(string);

  std::printf("[=]: %lu\t 0x%p" "\r\n", static_cast<unsigned long>(reinterpret_cast<uintptr_t>(string)), static_cast<void const*>(string));
  std::printf("[~]: %lu\t 0x%p" "\r\n", static_cast<unsigned long>(address), reinterpret_cast<void*>(address));
}
