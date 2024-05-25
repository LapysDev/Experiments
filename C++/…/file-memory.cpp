#include <cfloat>
#include <ciso646>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <new>

/* ... */
namespace fstd {
  static std::FILE  *fbuffer = NULL; //
  static std::FILE  *frecent = NULL; // ->> Recent allocation `std::FILE*` stream
  static std::size_t fsize   = 0u;   // ->> Number of bytes written to `fbuffer`

  /* ...
      --- NOTE ---
        #Lapys:
          - Allocations are stored within `fbuffer` as an array of non-padded `struct { std::FILE*; std::size_t; }`
          - No alignment concerns due to serialized object representations
  */
  extern "C" void* falloc(std::size_t const size) {
    std::FILE        *allocationFile                                            = NULL == fbuffer ? std::tmpfile() : frecent;
    std::size_t const allocationSize                                            = size;
    unsigned char     allocation[sizeof allocationFile + sizeof allocationSize] = {};
    std::size_t const offset                                                    = fsize % sizeof allocation;

    // ...
    if (NULL == fbuffer)
      return NULL;

    // ...
    if (0u == offset)
      allocationFile = std::tmpfile();

    else if (0 != std::fseek(fbuffer, static_cast<long>(fsize - offset), SEEK_SET))
      return NULL;

    // ...
    if (NULL != allocationFile) {
      if (allocationFile != frecent) {
        unsigned char fill[1024] = {};

        // ...
        (void) std::memset(fill, 0x00, sizeof fill / sizeof(unsigned char)); // ->> Same as `fill`
        while (size) {
          std::size_t const subcount = std::fwrite(fill, sizeof fill < size * sizeof(unsigned char) ? sizeof fill : (size * sizeof(unsigned char)), 1u, allocationFile);

          // ...
          size -= subcount; // ->> Overflows if more bytes were written than expected

          if (0u == subcount)
          while (size--) {
            if (EOF == std::fputc(static_cast<unsigned char>(0x00u), allocationFile)) {
              (void) std::fclose(allocationFile); // ->> Wasted file out of possible `TMP_MAX` files if `EOF` returned (analogous to a memory leak)
              return NULL;
            }
          }
        }
      }

      (void) std::memcpy(allocation + 0,                     &allocationFile, sizeof allocationFile);
      (void) std::memcpy(allocation + sizeof allocationFile, &allocationSize, sizeof allocationSize);

      /* ... */
      std::size_t const count = std::fwrite(allocation, sizeof allocation, 1u, fbuffer);

      // ...
      frecent = allocationFile;
      fsize  += count;

      if (count < sizeof allocation)
      return NULL;
    }

    return allocationFile;
  }

  extern "C" void ffree(void* const) /* TODO */ {}

  std::size_t fread(void* const buffer, std::size_t const size, std::size_t const count, std::FILE* stream) {
    if (NULL != fbuffer) {
      long index = 0L;

      // ...
      if (0u == count)
      return 0u;

      if (fbuffer != stream) {
        index = 0 == std::fseek(fbuffer, 0L, SEEK_END) ? std::ftell(fbuffer) : -1L;
        index = index != -1L ? (
          // --> std::less<void>
          std::less<void*>    ()(fbuffer, stream) and
          std::less<uintptr_t>()(reinterpret_cast<uintptr_t>(stream), reinterpret_cast<uintptr_t>(fbuffer) + index)
        ) ? index : -2L : -1L;
      }

      if (index == -1L)
      return 0u;

      std::rewind(fbuffer);

      if (index >= 0L and 0 == std::fseek(fbuffer, index, SEEK_SET))
      stream = fbuffer;
    }

    return std::fread(buffer, size, count, stream);
  }

  extern "C" void* frealloc(void* const address, std::size_t const size) /* TODO */ {
    if (0u == size)      return ffree(address), address;
    if (NULL == address) return falloc(size);

    return NULL;
  }

  std::size_t fwrite(void const* const, std::size_t const, std::size_t const, std::FILE* const) /* TODO */ {
    return 0u;
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  void       *allocation = NULL;
  std::size_t capacity   = 0u;

  return EXIT_SUCCESS; /* TODO */

  // ... ->> Allocate some numbers — to test allocation, writing, reading, and deallocation
  std::srand(
    // ... --> std::time(static_cast<std::time_t*>(NULL))
    (__TIME__[0] | __TIME__[1] | __TIME__[3] | __TIME__[4] | __TIME__[6] | __TIME__[7]) != '?' ?
      ((__TIME__[0] - '0') << 0u)  |
      ((__TIME__[1] - '0') << 2u)  |
      ((__TIME__[3] - '0') << 4u)  |
      ((__TIME__[4] - '0') << 7u)  |
      ((__TIME__[6] - '0') << 11u) |
      ((__TIME__[7] - '0') << 14u) :
    __LINE__
  ); {
    unsigned char const count = ((std::rand() / static_cast<long double>(RAND_MAX)) * 3u) + 3u;

    // ...
    capacity   = count * (sizeof(float) + sizeof(char[FLT_DIG + 3]));
    allocation = fstd::falloc(capacity);

    if (NULL != allocation) {
      float *const numbers = ::new (allocation)      float[count];
      char  *const texts   = ::new (numbers + count) char [count * (FLT_DIG + 3)];

      // ...
      for (struct operation_t {
        float*    (*function)(float*);
        char const *message;

        static float* instantiate(float *const number) { return ::new (number) float(std::rand() / static_cast<float>(RAND_MAX)); }
        static float* normalize  (float *const number) { *number = 1.421337f;  return number; }
        static float* rank       (float *const number) { *number *= FLT_RADIX; return number; }
      } const operations[] = {
        {&operation_t::instantiate, "Instantiating random numbers" ""},
        {&operation_t::rank,        "Ranking the numbers" "         "},
        {&operation_t::normalize,   "Normalizing the numbers" "     "}
      }, *operation = operations; operation != operations + (sizeof operations / sizeof(operation_t)); ++operation) {
        if (std::printf("%1.2s%s%2s", "\r\n", operation -> message, ": ") < 5)
        break;

        for (unsigned char index = 0u; count != index; ++index) {
          float *const number = operation -> function(numbers + index);
          char  *const text   = texts + (index * sizeof(char[FLT_DIG + 3]));

          // ...
          if (std::sprintf(text, "%0.*f%c", static_cast<int>(FLT_DIG), *number, ' ') != FLT_DIG + 3) {
            text[0]           = '-';
            text[1]           = '.';
            text[FLT_DIG + 2] = ' ';

            for (unsigned count = FLT_DIG; count--; )
            text[count + 2] = '-';
          }
        }

        (void) std::printf("%.*s%1.3s", static_cast<int>(count * (FLT_DIG + 3) < INT_MAX ? count * (FLT_DIG + 3) : INT_MAX), texts, "...");
      }

      fstd::ffree(allocation);
    }
  }

  // ... ->> Allocate some text — to test reallocation, writing, reading, and deallocation
  if (std::printf("%1.17s", "\r\n" "Type any text:" " ") == 17) {
    std::size_t length = 0u;

    // ...
    capacity   = 0u;
    allocation = NULL;

    while (true) {
      std::size_t size         = capacity == length ? SIZE_MAX / 2u < capacity ? SIZE_MAX : capacity ? capacity * 2u : 1u : capacity;
      void *const reallocation = capacity == length ? fstd::frealloc(allocation, size) : allocation;
      std::size_t count        = 0u;

      // ...
      if (NULL == reallocation) {
        if (capacity != size) {
          size = SIZE_MAX - size > capacity ? (size + capacity) / 2u : ((capacity / 2u) + (size / 2u));
          continue;
        }

        std::perror("\r\n" "Truncating text");
        break;
      }

      count = std::fread(static_cast<char*>(reallocation) + length, sizeof(char), size - length, stdin);

      if (0 != std::ferror(stdin)) {
        errno = EIO;
        std::perror("\r\n" "Truncating text");
        break;
      }

      allocation = reallocation;
      capacity   = size;
      length    += count;

      if (0u == count or 0 != std::feof(stdin))
      break;
    }

    (void) std::printf("%1.26s", "\r\n" "Here is the typed text:" " ");
    (void) std::printf("%.*s%.*s", static_cast<int>(length < INT_MAX ? length : INT_MAX), static_cast<char*>(allocation), length < INT_MAX ? 0 : 3, "...");
    fstd::ffree(allocation);
  }
}
