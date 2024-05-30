#include <cstdio>

/* … */
struct regexp {
  struct group {
    std::size_t length;
    regexp     *expressions;
  };

  struct quantities {
    std::size_t begin;
    std::size_t end;
    std::size_t count;
  };

  struct alternatives {
    std::size_t length;
    regexp     *expressions;
  };
};

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
