#include <climits>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <new>

/* ... */
#ifdef __cpp_initializer_lists
  // ... ->> risks a segmentation fault via null pointer access
  unsigned const (&heaped())[2] {
    return *reinterpret_cast<unsigned const (*)[2]>(new (std::nothrow) unsigned[2] {1u, 2u});
  }
#else
  // ... ->> risks a segmentation fault via null pointer access
  unsigned const (&heaped())[2] {
    unsigned *const array = new (std::nothrow) unsigned[2];

    // ...
    array[0] = 1u;
    array[1] = 2u;

    return *reinterpret_cast<unsigned const (*)[2]>(array);
  }
#endif

#if defined(__cpp_initializer_lists) && false == defined(_MSC_VER)
  // ... ->> could be mutable as an 'rvalue'
  uint16_t const (&integral(uint16_t const (&array)[3] = {1u, 2u, 3u}))[3] {
    return array;
  }

  uint32_t const (&variable(uint32_t const (&array)[5] = {1u, 2u, 3u, 4u, 0x45u}))[5] {
    return array;
  }
#else
  // ... ->> Must be endian-aware, these examples are for little-endian systems
  //     --> sizeof(array) <= sizeof(uintmax_t) || sizeof(array) <= sizeof(std::max_scalar_t)
  uint16_t const (&integral(
    uint16_t const (&array)[3] = reinterpret_cast<uint16_t const (&)[3]>(static_cast<uintmax_t const&>(
      (static_cast<uintmax_t>(1u) << (0u * CHAR_BIT * sizeof(uint16_t))) |
      (static_cast<uintmax_t>(2u) << (1u * CHAR_BIT * sizeof(uint16_t))) |
      (static_cast<uintmax_t>(3u) << (2u * CHAR_BIT * sizeof(uint16_t)))
    ))
  ))[3] { return array; }

  // ... ->> the size of each substring has to be exactly `sizeof(uint32_t)`; the last `'\0'` in the string can be omitted
  uint32_t const (&variable(
    uint32_t const (&array)[5] = reinterpret_cast<uint32_t const (&)[5]>(
      "\1\0\0\0"
      "\2\0\0\0"
      "\3\0\0\0"
      "\4\0\0\0"
      "E\0\0\0" // … noice
    )
  ))[5] { return array; }
#endif

unsigned const (&persisted())[2] {
  static unsigned array[2] = {1u, 2u};
  return array;
}

char const (&string())[14] {
  return "Hello, World!";
}

/* Main */
int main() {
  std::printf("%12s", "[heaped]   : 1 2" "             / ");
    for (unsigned const (&elements)[2] = heaped(), *element = elements; element != elements + (sizeof(elements) / sizeof(unsigned)); ++element)
    std::printf("%u" " ", *element);
  std::puts("\r");

  std::printf("%12s", "[integral] : 1 2 3" "           / ");
    for (uint16_t const (&elements)[3] = integral(), *element = elements; element != elements + (sizeof(elements) / sizeof(uint16_t)); ++element)
    std::printf("%u" " ", *element);
  std::puts("\r");

  std::printf("%12s", "[persisted]: 1 2" "             / ");
    for (unsigned const (&elements)[2] = persisted(), *element = elements; element != elements + (sizeof(elements) / sizeof(unsigned)); ++element)
    std::printf("%u" " ", *element);
  std::puts("\r");

  std::printf("%12s" "\"%1.14s\"" "%2s", "[string]   : \"Hello, World!\"" " / ", string(), "\r\n");

  std::printf("%12s", "[variable] : 1 2 3 4 69" "      / ");
    for (uint32_t const (&elements)[5] = variable(), *element = elements; element != elements + (sizeof(elements) / sizeof(uint32_t)); ++element)
    std::printf("%u" " ", *element);
  std::puts("\r");
}
