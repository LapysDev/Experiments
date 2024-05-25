#include <cstdio>

int main(void) {
  char string[64];

  for (char const *const message = "Hello, World!", *iterator = message; ; ++iterator) {
    string[iterator - message] = *iterator;
    if ('\0' == *iterator) break;
  }

  std::printf("[]: \"%s\"", string);
}
