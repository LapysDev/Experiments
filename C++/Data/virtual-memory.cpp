/* --> kernel32.lib */
#include <cstddef>
#include <cstdio>
#include <cstdlib>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# define PLATFORM_IS_POSIX   true
# define PLATFORM_IS_WINDOWS false

# include <sys/mman.h>
#endif

#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# define PLATFORM_IS_POSIX   false
# define PLATFORM_IS_WINDOWS true

# include <windows.h>
#endif

/* Main */
int main() {
  /* ... */
  typedef unsigned char byte_t;
  typedef unsigned char instruction_t;

  // ... [Memory]
  std::size_t const address = 0x5000BEEFu & ~0xFFFu;
  byte_t *pointer = static_cast<byte_t*>(NULL) + address;
  std::size_t const size = 6u * sizeof(instruction_t);

  // ... [Values]
  unsigned const value = 0x45u;
  instruction_t const instructions[size / sizeof(instruction_t)] = {
    0xB8u, // ->> Prologue
    (((value / 0x00000001uL) % 16u) << 0x0u) + (((value / 0x00000010uL) % 16u) << 0x4u),
    (((value / 0x00000100uL) % 16u) << 0x0u) + (((value / 0x00001000uL) % 16u) << 0x4u),
    (((value / 0x00010000uL) % 16u) << 0x0u) + (((value / 0x00100000uL) % 16u) << 0x4u),
    (((value / 0x01000000uL) % 16u) << 0x0u) + (((value / 0x10000000uL) % 16u) << 0x4u),
    0xC3u  // ->> Epilogue
  };

  /* ... ->> Specify `NULL` to receive a new memory region. */
  #if PLATFORM_IS_POSIX
    pointer = static_cast<byte_t*>(::mmap(static_cast<byte_t*>(NULL) + address, size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_FIXED | MAP_PRIVATE, -1, 0L));
    if (MAP_FAILED == pointer) {
      std::perror("Unable to manipulate memory");
      std::exit(EXIT_FAILURE);
    }
  #elif PLATFORM_IS_WINDOWS
    pointer = static_cast<byte_t*>(::VirtualAllocEx(::GetCurrentProcess(), static_cast<LPVOID>(pointer), static_cast<SIZE_T>(size), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
    if (NULL == pointer) {
      std::fputs("Unable to manipulate memory", stderr);
      std::exit(EXIT_FAILURE);
    }
  #endif

  // ...
  std::printf("Writing to  : %p" "\r\n", pointer);
  *reinterpret_cast<unsigned*>(pointer) = value;
  std::printf("Reading from: %u" "\r\n", *reinterpret_cast<unsigned*>(pointer));

  // ...
  for (instruction_t const *iterator = instructions + (size / sizeof(instruction_t)); instructions != iterator--; )
  pointer[iterator - instructions] = *iterator;

  std::printf("Executing %p: %u" "\r\n", pointer, reinterpret_cast<unsigned (*)()>(pointer)());

  /* ... */
  #if PLATFORM_IS_POSIX
    if (0 != ::munmap(static_cast<byte_t*>(NULL) + address, size)) {
      std::perror("Failed to release manipulated memory");
      std::exit(EXIT_FAILURE);
    }
  #elif PLATFORM_IS_WINDOWS
    if (FALSE == ::VirtualFreeEx(::GetCurrentProcess(), static_cast<LPVOID>(pointer), static_cast<SIZE_T>(0u), MEM_RELEASE)) {
      std::fputs("Failed to release manipulated memory", stderr);
      std::exit(EXIT_FAILURE);
    }
  #endif

  return EXIT_SUCCESS;
}
