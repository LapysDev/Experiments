// Simulates when `realloc(...)` returns a new block of memory (address) as
// the store for both `malloc(...)` (or `calloc(...)`) allocated memory
#include <algorithm>
#include <cstring>

template <class type, class... types>
type* renew(type* const pointer, std::size_t const length, types... arguments) {
  // 📝
  // Somehow magically get the bookmarked size of the `pointer`.
  // Allocate enough to store both new data & the `pointer` data.
  #define __pointer_size__ 5u

  std::size_t const formerSize = __pointer_size__ * sizeof(type);
  type *const reallocation = new type[length] {arguments...};

  // 🗄️
  /* Would using `std::memcpy(...)` be risky here for shifting the location of data? */ {
    // Move the freshly constructed objects into their appropriate offset in the `reallocation`.
    std::memmove(reallocation + (formerSize / sizeof(type)), reallocation, sizeof(type) * 5u/*(length * sizeof(type)) - formerSize*/);

    // Copy the contents of the (old) `pointer` into the (new) `reallocation`.
    std::memcpy(reallocation, pointer, formerSize);
  }

  // 🧹 Cleanup and finish
  delete[] pointer;
  return reallocation;
}

// 🏃 Test it out!
#include <cstdlib>
#include <iostream>

int main(void) {
  int *array = nullptr, length = 0;

  // std::malloc(...)
  length = 5, array = new int[length] {0x9}; {
      std::cout.write("[ALLOCATED]\r\n", 13u);

      for (int index = 0; index != length; ++index)
      std::cout << '(' << array[index] << ')';
  } std::endl(std::cout);

  // std::realloc(...) : Needs a familiar interface with the `delete` & `new` operators.
  length = 10, array = renew(array, length, 0xF); {
      std::cout.write("[RE-ALLOCATED]\r\n", 16u);

      for (int index = 0; index != length; ++index)
      std::cout << '(' << array[index] << ')';
  } std::endl(std::cout);

  // std::free(...)
  delete[] array;
  std::cout.write("[DELETED]\r\n", 11u);

  return EXIT_SUCCESS;
}
