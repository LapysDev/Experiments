#include <cstdio>

/* ... */
void closure(unsigned const argument) noexcept {
  std::printf("%u" "\r\n", argument);
}

template <unsigned constant>
void function() noexcept {
  void closure(unsigned = constant) noexcept;
  return closure();
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  function<0u>();
  function<1u>();
}
