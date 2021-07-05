#include <cstdio>

/* ... */
#define count_macro_argument(...) count_macro_argument_select(__VA_ARGS__, 2u, 1u, 0u)
#define count_macro_argument_select(argument1, argument2, count, ...) count

unsigned char count_function_argument(void) { return 0u; }
template <typename type> unsigned char count_function_argument(type&&) { return 1u; }
template <typename type, typename... types> unsigned char count_function_argument(type&&, types&&... arguments) { return 1u + count_function_argument(static_cast<types&&>(arguments)...); }

// ...
namespace { union nonaccessible_t; }

template <typename = nonaccessible_t, typename... types> struct count_type_trait { static unsigned short const value = 1u + count_type_trait<types...>::value; };
template <> struct count_type_trait<> { static unsigned short const value = 0u; };

// ...
template <int... arguments> struct count_nontype_trait { template <int> union dummy_t; static unsigned short const value = count_type_trait<dummy_t<arguments>...>::value; };

/* Main */
int main(void) {
  // ...
  std::printf("[function argument]          : %hu" "\r\n", ::count_function_argument());
  std::printf("[function argument]          : %hu" "\r\n", ::count_function_argument(0));
  std::printf("[function argument]          : %hu" "\r\n", ::count_function_argument(0, 0));
  std::puts("");

  // ...
  std::printf("[macro argument]             : %hu" "\r\n", count_macro_argument());
  std::printf("[macro argument]             : %hu" "\r\n", count_macro_argument(0));
  std::printf("[macro argument]             : %hu" "\r\n", count_macro_argument(0, 0));
  std::puts("");

  // ... ->> also extends to templated template arguments
  std::printf("[template non-typed argument]: %hu" "\r\n", count_nontype_trait<>::value);
  std::printf("[template non-typed argument]: %hu" "\r\n", count_nontype_trait<0>::value);
  std::printf("[template non-typed argument]: %hu" "\r\n", count_nontype_trait<0, 0>::value);
  std::puts("");

  std::printf("[template typed argument]    : %hu" "\r\n", count_type_trait<>::value);
  std::printf("[template typed argument]    : %hu" "\r\n", count_type_trait<int>::value);
  std::printf("[template typed argument]    : %hu" "\r\n", count_type_trait<int, int>::value);
  std::puts("");
}
