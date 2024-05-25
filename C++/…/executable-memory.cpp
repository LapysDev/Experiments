#include <cstdio>
#include <cstdlib>
#include <cstring>
#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# include <windows.h>
#   include <memoryapi.h>
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux)
# include <sys/mman.h>
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  int (*function)(int);
  unsigned char const code[] = {
    #if defined(__amd64) || defined(__amd64__) || defined(__i386) || defined(__i386__) || defined(__i386__) || defined(__i486__) || defined(__i486__) || defined(__i586__) || defined(__i586__) || defined(__i686__) || defined(__i686__) || defined(__I86__) || defined(__I86__) || defined(__INTEL__) || defined(__THW_INTEL__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_IX86) || defined(_M_X64) || defined(_X86_) || defined(i386)
      0x55u, 0x48u, 0x89u, 0xE5u, 0x89u, 0x7Du, 0xFCu, 0x8Bu, 0x45u, 0xFCu, 0x5Du, 0xC3u
    #else
    # error no code for environment architecture
      0x00u
    #endif
  };

  // ...
  #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    std::memcpy(&function, &static_cast<LPVOID const&>(::VirtualAlloc(NULL, sizeof(code) / sizeof(unsigned char), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)), sizeof(LPVOID));
    if (NULL == reinterpret_cast<void*>(function)) { std::puts("..."); return EXIT_FAILURE; }
    ::FlushInstructionCache(...);
  #else
    std::memcpy(&function, &static_cast<void* const&>(::mmap(NULL, sizeof(code) / sizeof(unsigned char), PROT_EXEC | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L)), sizeof(void*));
    if (MAP_FAILED == reinterpret_cast<void*>(function)) { std::puts("..."); return EXIT_FAILURE; }
  #endif

  std::memcpy(reinterpret_cast<void*>(function), code, sizeof(code) / sizeof(unsigned char));
  std::printf("%i", function(42));

  return
    #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
      FALSE == ::VirtualFree(function, sizeof(code) / sizeof(unsigned char), MEM_RELEASE)
    #else
      ::munmap(reinterpret_cast<void*>(function), sizeof(code) / sizeof(unsigned char)) == -1
    #endif
  ? EXIT_FAILURE : EXIT_SUCCESS;
}
