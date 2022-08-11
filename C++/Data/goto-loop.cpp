#include <cstddef>
#include <cstdio>

/* Main */
int main(int, char*[]) /* noexcept */ {
  // Loop
  { std::size_t iterator = 0u; iterate: if (iterator != 10u) {
    // ...
    std::printf("%1.9s%u\n\r", "[DEBUG]: ", iterator);

    // Continue
    ++iterator; goto iterate;
  } }
}
