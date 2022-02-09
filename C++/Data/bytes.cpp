#include <cmath>
#include <cstddef>
#include <cstdio>

#if defined(_WIN32)
# include <windows.h>
#   include <memoryapi.h>
#elif defined(__unix__)
# include <sys/mman.h>
#endif

template <typename type, unsigned length>
constexpr void copy(std::byte destination[], type (&&source)[length]) noexcept {
  if (NULL != destination) {
    for (type &value : source)
    *(destination++) = static_cast<std::byte>(value);
  }
}

/* ... */
#ifdef _MSC_VER
  __declspec(noinline)
#else
  __attribute__((noinline))
#endif
static unsigned function() noexcept { return 1337u; }
static float const number  = 245850922.0f / 78256779.0f;
static char const string[] = "Hello, World!";

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::byte *function;
  std::byte *number;
  std::byte *string;

  #if defined(_WIN32)
    function = static_cast<std::byte*>(::VirtualAlloc(NULL, 6u * sizeof(std::byte), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
    number   = static_cast<std::byte*>(::HeapAlloc(::GetProcessHeap(), 0x0u, 16u * sizeof(std::byte)));
    string   = static_cast<std::byte*>(::HeapAlloc(::GetProcessHeap(), 0x0u, 14u * sizeof(std::byte)));
  #elif defined(__unix__)
    function = static_cast<std::byte*>(::mmap(NULL,  6u * sizeof(std::byte), PROT_EXEC | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L));
    number   = static_cast<std::byte*>(::mmap(NULL, 16u * sizeof(std::byte), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L));
    string   = static_cast<std::byte*>(::mmap(NULL, 14u * sizeof(std::byte), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L));

    if (MAP_FAILED == function) function = NULL;
    if (MAP_FAILED == number)   number   = NULL;
    if (MAP_FAILED == string)   string   = NULL;
  #endif

  copy(function, {0xB8u, 0x39u, 0x05u, 0x00u, 0x00u, 0xC3u});
  copy(number,   {0xDBu, 0x0Fu, 0x49u, 0x40u, 0x68u, 0x42u, 0xB6u, 0xCAu, 0xFDu, 0x7Fu, 0x00u, 0x00u, 0xD0u, 0x05u, 0x40u, 0x00u});
  copy(string,   {0x48u, 0x65u, 0x6Cu, 0x6Cu, 0x6Fu, 0x2Cu, 0x20u, 0x57u, 0x6Fu, 0x72u, 0x6Cu, 0x64u, 0x21u, 0x00u});

  std::printf("[function (native)]: %u"     "\r\n", ::function());
  std::printf("[function    (raw)]: %u"     "\r\n", NULL == function ? -1u : reinterpret_cast<unsigned (*)()>(function)());
  std::printf("[number   (native)]: %f"     "\r\n", ::number);
  std::printf("[number      (raw)]: %f"     "\r\n", NULL == number ? INFINITY : *reinterpret_cast<float*>(number));
  std::printf("[string   (native)]: \"%s\"" "\r\n", ::string);
  std::printf("[string      (raw)]: \"%s\"" "\r\n", NULL == string ? "" : reinterpret_cast<char const*>(string));

  // ...
  #if defined(_WIN32)
    if (NULL != function) ::VirtualFree(function, 6u * sizeof(std::byte), MEM_RELEASE);
    if (NULL != number)   ::HeapFree(::GetProcessHeap(), 0x0u, number);
    if (NULL != string)   ::HeapFree(::GetProcessHeap(), 0x0u, string);
  #elif defined(__unix__)
    if (NULL != function) ::munmap(function, 6u * sizeof(std::byte));
    if (NULL != number)   ::munmap(number,  16u * sizeof(std::byte));
    if (NULL != string)   ::munmap(string,  14u * sizeof(std::byte));
  #endif
}
