#include <cstdio>

/* ... */
template <typename type>
bool check(type array[]) {
  bool (&assert(int[]))[true + 1];
  bool (&assert(...)) [false + 1];

  return sizeof(bool (&)[true + 1]) == sizeof(assert(array));
}

// ...
void function(char const message[]) {
  std::puts(message);
}

void wrap() {
  void function(char const[] = "Hello, World!");
  return function();
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::puts(check(static_cast<signed*>  (NULL)) ? "true" : "false");
  std::puts(check(static_cast<unsigned*>(NULL)) ? "true" : "false");

  wrap();
}
