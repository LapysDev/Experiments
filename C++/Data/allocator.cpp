#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdbool.h>

/* ... */
unsigned char BUFFER[32/*32 * 1024*/] = {};

void debug() {
  unsigned char *iterator = BUFFER;

  for (unsigned char iterator = 0u; iterator != 50u; ++iterator)
  std::printf("%u ", BUFFER[iterator]);

  std::putchar('{');
  while (true) {
    std::size_t const capacity = *std::launder(reinterpret_cast<std::size_t*>(iterator));
    bool const reserved = *std::launder(reinterpret_cast<bool*>(iterator + sizeof(std::size_t)));

    if (0u == capacity) break;

    if (reserved) std::printf("%lu,  ", static_cast<unsigned long>(capacity));
    else std::printf("%lu*, ", static_cast<unsigned long>(capacity));

    iterator += capacity + sizeof(bool) + sizeof(std::size_t);
  }
  std::puts("0}");
}

// ...
void* allocate(std::size_t const size) noexcept {
  unsigned char *allocation = BUFFER;
  std::size_t capacity;
  std::size_t leftover = 0u;
  bool reserved;
  bool reused = false;

  // Overflow protection --- UPDATE (Lapys) -> This doesn't actually protect
  if (0u == size || allocation + size + sizeof(bool) + sizeof(std::size_t) > BUFFER + (sizeof(BUFFER) / sizeof(*BUFFER)))
  return NULL;

  // Search for unreserved region
  while (true) {
    capacity = *std::launder(reinterpret_cast<std::size_t*>(allocation));
    reserved = *std::launder(reinterpret_cast<bool*>(allocation + sizeof(std::size_t)));

    // Found untouched part of `BUFFER`
    if (0u == capacity)
    break;

    // Found recently unreserved region
    if (false == reserved) {
      std::size_t available = capacity;
      unsigned char *next = allocation;
      std::size_t nextCapacity = capacity;
      bool nextReserved = reserved;

      while (true) {
        if (0u == nextCapacity) break;
        if (nextReserved) { available = 0u; break; }

        if (available > size + sizeof(bool) + sizeof(std::size_t)) {
          leftover = available - size;
          break;
        }

        next += nextCapacity + sizeof(bool) + sizeof(std::size_t);
        nextCapacity = *std::launder(reinterpret_cast<std::size_t*>(next));
        nextReserved = *std::launder(reinterpret_cast<bool*>(next + sizeof(std::size_t)));
        available += nextCapacity;
      }

      if (0u != available) {
        reused = true;
        break;
      }
    }

    // Next region
    allocation += capacity + sizeof(bool) + sizeof(std::size_t);
  }

  // Imprint metadata in allocated region
  new (allocation) std::size_t(size);
  new (allocation + sizeof(std::size_t)) bool(true);

  // Instantiate metadata for next region
  if (false == (0u == leftover && reused)) {
    new (allocation + size + sizeof(bool) + sizeof(std::size_t)) std::size_t(leftover);
    new (allocation + size + sizeof(bool) + sizeof(std::size_t) + sizeof(std::size_t)) bool(false);
  }

  // ...
  return allocation + sizeof(bool) + sizeof(std::size_t);
}

void reallocate(void* const, std::size_t const) noexcept {}

void release(void* const pointer) noexcept {
  *std::launder(reinterpret_cast<bool*>(static_cast<unsigned char*>(pointer) - sizeof(bool))) = false;
}

/* Main */
int main() {
  new (BUFFER + 0)                   std::size_t(0u);
  new (BUFFER + sizeof(std::size_t)) bool(false);

  // ...
  constexpr unsigned char count = 10u;
  unsigned char *items[count] = {};

  for (unsigned char iterator = 0u; count != iterator; ++iterator) {
    items[iterator] = static_cast<unsigned char*>(allocate(13u));
    std::printf("[]: %i" "\r\n", items[iterator] - BUFFER);
  }
}
