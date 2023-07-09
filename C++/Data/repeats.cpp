#include <ciso646>
#include <cstddef>
#include <cstdio>

/* ... */
bool find_repeat(int const array[], std::size_t const length, std::size_t (*const repeat)[3] = NULL, bool const restricted = false) {
  if (length > 1u) {
    std::size_t (*indexes)[3]         = NULL == repeat or 0u == ((*repeat)[0] | (*repeat)[1] | (*repeat)[2]) ? NULL : repeat;
    std::size_t sequenceMaximumLength = (length / 2u) + (0u != length % 2u);

    // ... ->> Every nth element is a sequence of length `indexA <= sequenceLength <= sequenceMaximumLength`
    for (std::size_t indexA = NULL == indexes ? length - 1u : (*indexes)[0]; indexA; --indexA, indexes = NULL) {
      // ... ->> Search for repeated occurrences of each sequence in the `array`
      for (std::size_t sequenceLength = NULL == indexes ? indexA < sequenceMaximumLength ? indexA : sequenceMaximumLength : (*indexes)[2]; sequenceLength; --sequenceLength, indexes = NULL)
      for (std::size_t indexB = NULL == indexes ? indexA - 1u : (*indexes)[1]; indexB >= sequenceLength - 1u; --indexB, indexes = NULL) {
        bool repeated = true;

        // ...
        if (NULL != indexes) { if (0u == indexB) break; else continue; }
        if (restricted and sequenceLength > indexA - indexB) continue;

        for (std::size_t subindex = sequenceLength; repeated and subindex--; )
          repeated = array[indexA - subindex] == array[indexB - subindex];

        if (not repeated) { if (0u == indexB) break; else continue; }
        if (NULL != repeat) {
          if (indexA == (*repeat)[0] and indexB == (*repeat)[1] and sequenceLength == (*repeat)[2])
            continue;

          (*repeat)[0] = indexA;
          (*repeat)[1] = indexB;
          (*repeat)[2] = sequenceLength;
        }

        // ...
        return true;
      }
    }
  }

  return false;
}

// ...
std::size_t count_repeats(int const array[], std::size_t const length) {
  std::size_t count = 0u;

  // ...
  for (std::size_t repeat[3] = {0u, 0u, 0u}; find_repeat(array, length, &repeat); ++count)
  continue;

  return count;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  int         const array[] = {7, 9, 5, 4, 5, 4, 8, 6};
  std::size_t const length  = sizeof array / sizeof(int);

  /* ... ->> Check if repeated sequence exists within `array` */
  std::printf("[has   repeat(s)]: %4.5s" "\r\n", find_repeat(array, length /* , NULL */) ? "true" : "false");

  /* ... ->> Search for repeated sequence within `array` */ {
    std::size_t repeat[3] = {
      0u, 0u, // ->> Repeated sequence indexes
      0u      // ->> Length of repeated sequences
    }; // ->> Must be zeroed to begin search

    // ... ->> Changing the `if ...` condition to a `while ...` loop would find all repeated sequences within `array`
    if (find_repeat(array, length, &repeat)) {
      std::printf("[get   repeat]   :");

      for (unsigned char index = 0u; index != 2u; ++index) {
        std::size_t const offset = repeat[index] - (repeat[2] - 1u);

        // ... ->> The `array` is iterated in reverse; a forward-based algorithm would not need to correct the `repeat` indexes (ie: `offset`) for external use
        std::printf(" " "(%u) { ", (unsigned) repeat[index]);

        for (std::size_t subindex = 0u; subindex != repeat[2]; ++subindex)
          std::printf("%i" " ", array[offset + subindex]);

        std::printf("}");
      }

      std::printf("\r\n");
    }
  }

  /* ... ->> Count the number of repeated sequences within `array` */
  std::printf("[count repeats]  : %u", (unsigned) count_repeats(array, length));
}
