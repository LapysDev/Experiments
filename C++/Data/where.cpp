#include <cstdio>

/* ... */
template <bool, typename> struct enable_if;
template <typename base>  struct enable_if<true, base> { typedef base type; };

#define were(condition, base) typename enable_if<condition, base>::type

// ...
template <int count>
were(count < 8, void) function() { std::puts("less than 8"); }

template <int count>
were(count >= 8, void) function() { std::puts("8 or more"); }

/* Main */
int main(int, char*[]) /* noexcept */ {
  function<0>();
  function<8>();
}
