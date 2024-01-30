#include <cstddef>
#include <cstdio>
#include <utility>

/* ... */
constexpr std::size_t function() noexcept { return 0u; } // sizeof...()
template <typename type>                    constexpr std::size_t function(type&&)                       noexcept { return 1u; }
template <typename type, typename... types> constexpr std::size_t function(type&&, types&&... arguments) noexcept { return 1u + function(std::forward<types>(arguments)...); }

// ...
#define concatenate(argument1, argument2) argument1 ## argument2
#define defer(function, ...) defer_parse(function, (__VA_ARGS__))
# define defer_parse(function, call) function call
#define first(argument, ...)              argument
#define second(argument1, argument2, ...) argument2

#define macro(...) macro_parse(defer(second, first(macro_rank __VA_ARGS__, ~)(~, ~, ~, ~, /* n */ macro_nil, ~), variadic, ~), __VA_ARGS__)
# define macro_nil ~, niladic
# define macro_parse(arity, ...) defer(concatenate, macro_, arity)(__VA_ARGS__, ~)
#   define macro_niladic(...)  0u
#   define macro_variadic(...) defer(macro_rank, __VA_ARGS__, 3u, 2u, 1u, 0u) /* n */
# define macro_rank(a, b, c, d, /* n */ count, ...) count

// ...
template <int...> union nontype_trait; // sizeof...()
template <>                                 union nontype_trait<>                         { enum { value = 0u }; };
template <int parameter, int... parameters> union nontype_trait<parameter, parameters...> { enum { value = 1u + nontype_trait<parameters...>::value }; };

// ...
template <typename...> union typed_trait; // sizeof...()
template <>                                           union typed_trait<>                         { enum { value = 0u }; };
template <typename parameter, typename... parameters> union typed_trait<parameter, parameters...> { enum { value = 1u + typed_trait<parameters...>::value }; };

/* Main */
int main() {
  std::printf("[function]       : %u" "\r\n", static_cast<unsigned>(::function()));
  std::printf("[function]       : %u" "\r\n", static_cast<unsigned>(::function(0)));
  std::printf("[function]       : %u" "\r\n", static_cast<unsigned>(::function(0, 0)));
  std::printf("[function]       : %u" "\r\n", static_cast<unsigned>(::function(0, 0, 0)));
  std::puts("");

  std::printf("[macro]          : %u" "\r\n", macro());
  std::printf("[macro]          : %u" "\r\n", macro(0));
  std::printf("[macro]          : %u" "\r\n", macro(0, 0));
  std::printf("[macro]          : %u" "\r\n", macro(0, 0, 0));
  std::puts("");

  std::printf("[non-typed trait]: %u" "\r\n", nontype_trait<>::value);
  std::printf("[non-typed trait]: %u" "\r\n", nontype_trait<0>::value);
  std::printf("[non-typed trait]: %u" "\r\n", nontype_trait<0, 0>::value);
  std::printf("[non-typed trait]: %u" "\r\n", nontype_trait<0, 0, 0>::value);
  std::puts("");

  std::printf("[typed trait]    : %u" "\r\n", typed_trait<>::value);
  std::printf("[typed trait]    : %u" "\r\n", typed_trait<int>::value);
  std::printf("[typed trait]    : %u" "\r\n", typed_trait<int, int>::value);
  std::printf("[typed trait]    : %u" "\r\n", typed_trait<int, int, int>::value);
}
