#include <climits>
#include <cstdio>

/* Main */
int main(int, char*[]) /* noexcept */ {
  enum { WIDTH = CHAR_BIT * sizeof(int) };
  unsigned char bytes[(WIDTH / CHAR_BIT) + (WIDTH % CHAR_BIT)];
  int           integer = -42;

  // ...
  for (std::size_t index = 0u; index < WIDTH; (index += CHAR_BIT), (integer >>= CHAR_BIT))
  bytes[index / CHAR_BIT] = static_cast<unsigned char>(integer & UCHAR_MAX);

  integer = 0x00u;

  for (std::size_t index = WIDTH; 0u != index; index -= CHAR_BIT <= index ? CHAR_BIT : index)
  integer = bytes[(index / CHAR_BIT) - (0u == WIDTH % CHAR_BIT)] | (integer << CHAR_BIT);

  std::printf("%i", integer);
}
