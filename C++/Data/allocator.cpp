#include <cstddef>
#include <cstdio>
#include <new>

/* ... */
std::byte BUFFER[32u * 1024u] = {};

// ... ->> `0 != alignment + size`
void* allocate(std::size_t const size, std::size_t const alignment = alignof(std::max_align_t)) noexcept {
  typedef std::size_t header_t;
  std::byte *allocation = BUFFER;

  // Search for unreserved region
  while (true) {
    header_t *const header = std::launder(reinterpret_cast<header_t*>(allocation));
    std::size_t capacity = *reinterpret_cast<std::size_t*>(header) >> 1u;
    bool const reserved = *reinterpret_cast<std::size_t*>(header) & 1u;

    // Found un-committed region
    if (0u == capacity) {
      std::byte *buffer;

      allocation += sizeof(header_t);
      capacity = size;

      while (0u != (allocation - BUFFER) % alignment) {
        ++allocation;
        ++capacity;
      }

      // Overflow protection
      if (allocation + size >= BUFFER + (sizeof(BUFFER) / sizeof(*BUFFER)))
      return NULL;

      // Mark header for next region
      buffer = allocation + size;
      while (0u != (buffer - BUFFER) % alignof(header_t)) ++buffer;

      new (buffer) header_t(false | (0u << 1u));

      // Commit region
      *reinterpret_cast<std::size_t*>(header) = true | (capacity << 1u);
      break;
    }

    // Found unreserved region
    if (false == reserved) {
      std::byte *boundary = BUFFER + (sizeof(BUFFER) / sizeof(*BUFFER));
      std::byte *buffer = allocation;

      // Merge contiguous unreserved regions
      while (true) {
        header_t const *const bufferHeader = std::launder(reinterpret_cast<header_t*>(buffer));
        std::size_t const bufferCapacity = *reinterpret_cast<std::size_t const*>(bufferHeader) >> 1u;
        bool const bufferReserved = *reinterpret_cast<std::size_t const*>(bufferHeader) & 1u;

        // De-commit regions (found untouched region)
        if (0u == bufferCapacity) {
          capacity = 0u;
          break;
        }

        // Merge regions
        if (false != bufferReserved) {
          boundary = buffer;
          capacity = (buffer - allocation) - sizeof(header_t);
          break;
        }

        // ... next region
        buffer += bufferCapacity + sizeof(header_t);
        while (0u != (buffer - BUFFER) % alignof(header_t)) ++buffer;

        // De-commit regions (found the end)
        if (buffer >= (BUFFER + (sizeof(BUFFER) / sizeof(*BUFFER))) - sizeof(header_t)) {
          capacity = 0u;
          break;
        }
      }

      *reinterpret_cast<std::size_t*>(header) = false | (capacity << 1u);

      // ...
      if (0u == capacity)
      continue;

      if (capacity >= size) {
        std::byte *body = allocation + sizeof(header_t);

        // ...
        while (0u != (body - BUFFER) % alignment) ++body;

        buffer = body + size;
        while (0u != (buffer - BUFFER) % alignof(header_t)) ++buffer;

        // Possibly mark header for next region
        if (boundary <= buffer || static_cast<std::size_t>(boundary - buffer) <= sizeof(header_t)) buffer = boundary;
        else new (buffer) header_t(false | (((boundary - buffer) - sizeof(header_t)) << 1u));

        // Commit region
        *reinterpret_cast<std::size_t*>(header) = true | (((buffer - allocation) - sizeof(header_t)) << 1u);
        allocation = body;

        break;
      }
    }

    // ... next region
    allocation += capacity + sizeof(header_t);
    while (0u != (allocation - BUFFER) % alignof(header_t)) ++allocation;

    if (allocation >= (BUFFER + (sizeof(BUFFER) / sizeof(*BUFFER))) - sizeof(header_t))
    return NULL;
  }

  // ...
  return allocation;
}

// ... ->> `NULL != pointer && pointer in BUFFER`
void release(void* const pointer) noexcept {
  typedef std::size_t header_t;
  std::byte *buffer = BUFFER;

  for (std::byte *iterator = BUFFER; ; ) {
    header_t *header = std::launder(reinterpret_cast<header_t*>(iterator));
    std::size_t const capacity = *reinterpret_cast<std::size_t*>(header) >> 1u;

    // Found `pointer` within `BUFFER`
    if (iterator > pointer) {
      header = std::launder(reinterpret_cast<header_t*>(buffer));
      *reinterpret_cast<std::size_t*>(header) &= ~static_cast<std::size_t>(1u);

      break;
    }

    // ... next region
    buffer = iterator;
    iterator += capacity + sizeof(header_t);
    while (0u != (iterator - BUFFER) % alignof(header_t)) ++iterator;
  }
}

/* Main */
int main() {
  new (BUFFER) std::size_t(false | (0u << 1u));
}
