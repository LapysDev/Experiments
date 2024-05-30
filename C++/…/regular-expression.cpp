#include <cstdio>

/* … */
struct regexp {};

// …
regexp diagnose(char const pattern[]) {
  regexp expression = {};

  // …
  (void) pattern;
  return expression;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  diagnose("");
}
