#include <cstdio>
#include <cstdlib>

/* ... */
char* assemble(char destination[], char const* source) noexcept {
  (void) source;
  return destination;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  char assembly[256] = {'\0'};
  std::printf("%s", assemble((char*) assembly, "(-((1 + 5) * 2 % 3 - 2)) ^ 5 - 1"));
}
