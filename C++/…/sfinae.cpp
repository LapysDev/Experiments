template <class predicate, typename A = void, typename B = void, typename C = void /* , … */>
struct can {
  template <typename a, typename b, typename c /* , … */>
  static bool (&valueof(int, int))[sizeof(static_cast<void>(predicate::template value<a, b, c /* , … */>()), 0) + 1];

  template <typename, typename, typename /* , … */>
  static bool (&valueof(...))[false + 1];

  // …
  static bool const value = sizeof(bool[false + 1]) != sizeof valueof<A, B, C>(0, 0);
};

/* … */
#include <cstddef>
#include <cstdio>

// …
struct add {
  template <typename A, typename B, typename /* , … */>
  static void value(int = (static_cast<void>(*static_cast<A*>(NULL) + *static_cast<B*>(NULL)), 0));
};

struct non_addable {};

/* Main */
int main(int, char*[]) {
  std::puts(can<add, int, int>        ::value ? "true" : "false");
  std::puts(can<add, int, non_addable>::value ? "true" : "false");
}
