#include <climits>
#include <cstddef>

/* ... ->> features a bump allocator */
constexpr void parse(unsigned char *const buffer = NULL, std::size_t const bufferSize = 0u) noexcept {
  struct {
    unsigned char       *buffer;
    unsigned char *const bufferStart;
    unsigned char *const bufferEnd;

    /* ... */
    constexpr unsigned char* allocate(std::size_t size, std::size_t alignment = sizeof(unsigned char)) noexcept {
      unsigned char *allocation = buffer;

      // ...
      if (buffer == bufferEnd)
      return NULL;

      while (0u != (allocation - bufferStart) % sizeof(std::ptrdiff_t))
      if (++allocation == bufferEnd) return NULL;

      // ...
      allocation += sizeof(std::ptrdiff_t);
      size       += 0u != size % 2u;

      while (0u != size % alignment)
      ++alignment;

      while (0u != (allocation - bufferStart) % alignment)
      if (++allocation == bufferEnd) return NULL;

      if (static_cast<std::size_t>(bufferEnd - buffer) < static_cast<std::size_t>((allocation - buffer) + size))
      return NULL;

      for (unsigned char *offset = allocation - sizeof(std::ptrdiff_t); ; --offset)
      if (0u == (offset - bufferStart) % sizeof(std::ptrdiff_t)) {
        store(offset - buffer, offset, sizeof(std::ptrdiff_t));
        break;
      }

      // ...
      buffer = allocation + size;
      return allocation;
    }

    constexpr std::size_t load(unsigned char buffer[], std::size_t size) noexcept {
      std::size_t value = 0x00u;

      // ...
      for (buffer += size; size--; ) {
        value <<= CHAR_BIT * sizeof(unsigned char);
        value  |= *--buffer;
      }

      return value;
    }

    constexpr void grow(std::size_t const size) {
      buffer += size;
    }

    constexpr void release(std::size_t const size) noexcept {
      buffer -= size + sizeof(std::ptrdiff_t);
      while (0u != (buffer - bufferStart) % sizeof(std::ptrdiff_t)) --buffer;
      buffer -= load(buffer, sizeof(std::ptrdiff_t));
    }

    constexpr unsigned char store(std::size_t value, unsigned char buffer[], std::size_t size) noexcept {
      while (size--) {
        *(buffer++) = value & UCHAR_MAX;
        value     >>= CHAR_BIT * sizeof(unsigned char);
      }
    }
  } parser = {buffer, buffer + 0, buffer + bufferSize};

  static_cast<void>(parser);
}

/* Main */
int main(int, char*[]) /* noexcept */ {}
