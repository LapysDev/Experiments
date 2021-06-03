#include <cstdio>

/* ... */
// since C++11
template <typename begin_t, typename end_t, typename return_t, typename... arguments_t>
constexpr void constexpr_foreach(begin_t begin, end_t end, return_t (*function)(arguments_t...)) {
  return begin == end ? static_cast<void>(/* NOP */ 0x0) : (function(begin), constexpr_foreach(++begin, end, function));
}

// after C++11
template <typename begin_t, typename end_t, typename return_t, typename... arguments_t>
constexpr void constexpr_foreach(begin_t begin, end_t end, return_t (*function)(arguments_t...)) {
  while (false == (begin == end)) { function(begin); ++begin; }
}

/* constexpr */ void print(char const string[]) { std::putchar(*string); }

/* Main */
int main(void) {
  char const string[] = "Hello, World!";

  constexpr_foreach(string, string + 14, &print);
  return /* EXIT_SUCCESS */ 0x0;
}
