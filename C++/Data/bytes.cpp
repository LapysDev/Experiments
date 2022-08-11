#include <cmath>
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <version>

#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# include <windows.h>
#   include <memoryapi.h>
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux)
# include <sys/mman.h>
#endif

/* ... */
#ifdef __cpp_lib_launder
  using std::launder;
#else
  template <typename type>
  inline type* launder(type* const address) noexcept {
    return address;
  }
#endif

template <typename type>
constexpr typename std::conditional<(__cplusplus >= 201103L), int, void>::type copy(unsigned char destination[], type source[], std::size_t length) noexcept {
  return 0u != length ? static_cast<void>(*destination = static_cast<unsigned char>(*launder(source))), copy(++destination, ++source, --length) : typename std::conditional<(__cplusplus >= 201103L), int, void>::type(0x0);
}

template <typename type, std::size_t capacity>
constexpr decltype(copy(static_cast<unsigned char*>(NULL), static_cast<type*>(NULL), capacity)) copy(unsigned char destination[], type (&&source)[capacity]) noexcept(noexcept(copy(static_cast<unsigned char*>(NULL), static_cast<type*>(NULL), capacity))) {
  return copy(destination, source, capacity);
}

/* ... */
#ifdef _MSC_VER
  __declspec(noinline)
#else
  __attribute__((noinline))
#endif
static unsigned function() noexcept { return 1337u; }
static float const number   = 245850922.0f / 78256779.0f;
static char const  string[] = "Hello, World!";

/* Main */
int main(int, char*[]) /* noexcept */ {
  unsigned char
  #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    *function = static_cast<unsigned char*>(::VirtualAlloc(NULL, 6u * sizeof(unsigned char), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)),
    *number   = static_cast<unsigned char*>(::HeapAlloc(::GetProcessHeap(), 0x0u, 16u * sizeof(unsigned char))),
    *string   = static_cast<unsigned char*>(::HeapAlloc(::GetProcessHeap(), 0x0u, 14u * sizeof(unsigned char)));
  #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux)
    *function = static_cast<unsigned char*>(::mmap(NULL,  6u * sizeof(unsigned char), PROT_EXEC | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L)),
    *number   = static_cast<unsigned char*>(::mmap(NULL, 16u * sizeof(unsigned char), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L)),
    *string   = static_cast<unsigned char*>(::mmap(NULL, 14u * sizeof(unsigned char), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L));

    if (MAP_FAILED == function) function = NULL;
    if (MAP_FAILED == number)   number   = NULL;
    if (MAP_FAILED == string)   string   = NULL;
  #endif

  copy(function, {0xB8u, 0x39u, 0x05u, 0x00u, 0x00u, 0xC3u});                                                                       // ->> vendor-specific Assembly instructions
  copy(number,   {0xDBu, 0x0Fu, 0x49u, 0x40u, 0x68u, 0x42u, 0xB6u, 0xCAu, 0xFDu, 0x7Fu, 0x00u, 0x00u, 0xD0u, 0x05u, 0x40u, 0x00u}); // ->> endian-specific integer representation
  copy(string,   {0x48u, 0x65u, 0x6Cu, 0x6Cu, 0x6Fu, 0x2Cu, 0x20u, 0x57u, 0x6Fu, 0x72u, 0x6Cu, 0x64u, 0x21u, 0x00u});               // ->> encoding-specific string representation

  // ...
  std::printf("[function (native)]: %u"     "\r\n", ::function());
  std::printf("[function    (raw)]: %u"     "\r\n", NULL == function ? -1u : reinterpret_cast<unsigned (*)()>(function)());
  std::printf("[number   (native)]: %f"     "\r\n", ::number);
  std::printf("[number      (raw)]: %f"     "\r\n", NULL == number ? INFINITY : *launder(reinterpret_cast<float*>(number)));
  std::printf("[string   (native)]: \"%s\"" "\r\n", ::string);
  std::printf("[string      (raw)]: \"%s\"" "\r\n", NULL == string ? "" : reinterpret_cast<char const*>(string));

  // ...
  #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    if (NULL != function) ::VirtualFree(function, 6u * sizeof(unsigned char), MEM_RELEASE);
    if (NULL != number)   ::HeapFree(::GetProcessHeap(), 0x0u, number);
    if (NULL != string)   ::HeapFree(::GetProcessHeap(), 0x0u, string);
  #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux)
    if (NULL != function) ::munmap(function, 6u * sizeof(unsigned char));
    if (NULL != number)   ::munmap(number,  16u * sizeof(unsigned char));
    if (NULL != string)   ::munmap(string,  14u * sizeof(unsigned char));
  #endif
}
