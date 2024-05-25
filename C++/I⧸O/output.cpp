#include <cstdio>
#include <cstdlib>

/* Main */
int main(int, char*[]) /* noexcept */ {
  /* ... */
  return 13 == std::printf("%1.13s", "Hello, World!") ? EXIT_SUCCESS : EXIT_FAILURE;
}
