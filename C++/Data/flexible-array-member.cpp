#include <cstddef>
#include <cstdio>

/* ... */
struct String {
  std::size_t length;
  char data[];
};

/* Main */
int main(void) {
  // Can't be nested within an array
  // C++11 and after initialization only
  // Must be explicitly allocated first
  // Must be `static` for some reason..?
  static String const stringA = {11u, 'L', 'o', 'r', 'e', 'm', ' ', 'i', 'p', 's', 'u', 'm'};
  static String const stringB = {13u, 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
  static String const stringC = {3u, 'A', 'B', 'C'};

  // ...
  String const *const strings[] = {&stringA, &stringB, &stringC};

  for (std::size_t iterator = sizeof(strings) / sizeof(String const*); iterator--; ) {
    String const *const string = strings[iterator];

    std::printf("[%zu]: \"", iterator);
      for (std::size_t subiterator = 0u; subiterator != string -> length; ++subiterator)
      std::putchar(string -> data[subiterator]);
    std::printf("%3s", "\"" "\r\n");
  }
}
