#include <cstddef>
#include <cstdio>
#include <new>

/* ... */
std::byte BUFFER[32u * 1024u] = {};

// ... ->> `0 != alignment && 0 != size`
void* allocate(std::size_t const size, std::size_t const alignment = alignof(std::max_align_t)) noexcept {
  typedef std::size_t header_t;

  constexpr std::byte *BUFFER_END = BUFFER + (sizeof(BUFFER) / sizeof(*BUFFER));
  std::byte *allocation = BUFFER;

  // Search for unreserved region
  while (true) {
    header_t *const header = std::launder(reinterpret_cast<header_t*>(allocation));
    std::size_t capacity = *reinterpret_cast<std::size_t*>(header) >> 1u;
    bool const reserved = *reinterpret_cast<std::size_t*>(header) & 1u;

    // Found end of `BUFFER`
    if (BUFFER_END == allocation)
    return NULL;

    // Found uncommitted region
    if (0u == capacity) {
      if (sizeof(header_t) > static_cast<std::size_t>(BUFFER_END - allocation))
      return NULL; // not enough capacity for `header_t`

      allocation += sizeof(header_t);
      capacity = size;

      while (0u != (allocation - BUFFER) % alignment) {
        if (BUFFER_END == allocation)
        return NULL; // not enough capacity for alignment padding

        ++allocation;
        ++capacity;
      }

      if (size > static_cast<std::size_t>(BUFFER_END - allocation))
      return NULL; // not enough capacity for `size`

      // Mark header for next region
      for (std::byte *next = allocation + size; sizeof(header_t) <= static_cast<std::size_t>(BUFFER_END - next); ++next)
      if (0u == (next - BUFFER) % alignof(header_t)) {
        capacity += next - (allocation + size);
        new (next) header_t(false | (0u << 1u));

        break;
      }

      // Commit region
      *reinterpret_cast<std::size_t*>(header) = true | (capacity << 1u);
      break;
    }

    // Found unreserved region
    if (false == reserved) {
      std::byte *boundary = BUFFER_END;
      std::byte *buffer = allocation;

      // Merge contiguous unreserved regions
      while (true) {
        header_t const *const bufferHeader = std::launder(reinterpret_cast<header_t*>(buffer));
        std::size_t const bufferCapacity = *reinterpret_cast<std::size_t const*>(bufferHeader) >> 1u;
        bool const bufferReserved = *reinterpret_cast<std::size_t const*>(bufferHeader) & 1u;

        // De-commit regions (found uncommitted region)
        if (0u == bufferCapacity) {
          capacity = 0u;
          break;
        }

        // Merge regions (found reserved region)
        if (false != bufferReserved) {
          boundary = buffer;
          capacity = (buffer - allocation) - sizeof(header_t);

          break;
        }

        // ... next region
        buffer += bufferCapacity + sizeof(header_t);
      }

      *reinterpret_cast<std::size_t*>(header) = false | (capacity << 1u);

      // ... allocate as uncommitted region
      if (0u == capacity)
      continue;

      // ... allocate as unreserved region
      if (capacity >= size) {
        buffer = allocation + sizeof(header_t);

        while (0u != (buffer - BUFFER) % alignment)
        ++buffer;

        // ...
        if (boundary >= buffer + size) {
          // Bifurcate current region
          for (std::byte *next = buffer + size; sizeof(header_t) <= static_cast<std::size_t>(boundary - next); ++next)
          if (0u == (next - BUFFER) % alignof(header_t)) {
            capacity = (next - allocation) - sizeof(header_t);
            new (next) header_t(false | (((boundary - next) - sizeof(header_t)) << 1u));

            break;
          }

          // Commit region
          allocation = buffer;
          *reinterpret_cast<std::size_t*>(header) = true | (capacity << 1u);

          break;
        }
      }
    }

    // ... next region
    allocation += capacity + sizeof(header_t);
  }

  // ...
  return allocation;
}

// ... ->> `NULL != pointer && pointer in BUFFER`
void release(void* const pointer) noexcept {
  typedef std::size_t header_t;
  std::byte *buffer = BUFFER;

  for (std::byte *next = BUFFER; ; ) {
    header_t *header = std::launder(reinterpret_cast<header_t*>(next));
    std::size_t const capacity = *reinterpret_cast<std::size_t*>(header) >> 1u;

    // De-commit region (found `pointer` within `BUFFER`)
    if (next > pointer) {
      header = std::launder(reinterpret_cast<header_t*>(buffer));
      *reinterpret_cast<std::size_t*>(header) &= ~static_cast<std::size_t>(1u);

      break;
    }

    // ... next region
    buffer = next;
    next += capacity + sizeof(header_t);
  }
}

/* Main */
int main() /* noexcept */ {
  new (BUFFER) std::size_t(false | (0u << 1u));
}
