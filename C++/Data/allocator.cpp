/* Import */
#include <cstddef>
#include <cstdio>
#include <new>
#ifdef _MSVC_LANG
# if _MSVC_LANG >= 202002L
#   include <version>
# endif
#elif __cplusplus >= 202002L
# include <version>
#elif defined(__clang__) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER)
# include <version>
#endif

#if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
# include <alloca.h>  // --> ::alloca(...)
# include <pthread.h> // --> -pthread; ::pthread_self()
#elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
# include <malloc.h>  // --> ::_alloca(...)
# include <windows.h> // --> <processthreadsapi.h>; ::GetCurrentThreadId()
#endif

/* Definition > ... */
#undef allocate_
#undef heap
#undef namespace
#undef stack

#define combine(argument1, argument2) argument1 ## argument2
#define defer(function, ...) defer_parse(function, (__VA_ARGS__))
# define defer_parse(function, call) function call
#define second(argument1, argument2, ...) argument2

#define allocate(size, alignment, ...) defer(combine, allocate_, defer(second, allocate_ ## __VA_ARGS__, heap, ~))(__VA_ARGS__)(size, alignment)
#define STACK(...) applyControlParameter(__VA_ARGS__) ->* allocate_stack_parse
# define allocate_heap(...) applyControlParameter(__VA_ARGS__) ->* allocate_heap_parse
#   define allocate_heap_parse(size, alignment) Memory::allocate(size, alignment)
# define allocate_namespace template _<__LINE__>
# define allocate_stack(...) applyControlParameter(__VA_ARGS__) ->* allocate_stack_parse
#   define allocate_stack_parse(size, alignment) (static_cast<void>(static_cast<std::size_t>(size), static_cast<std::size_t>(alignment)), static_cast<void*>(NULL))
#   if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
#     undef  allocate_stack_parse
#     define allocate_stack_parse(size, alignment) ::alloca(static_cast<std::size_t>(size) + (static_cast<std::size_t>(alignment) - 1u))
#   elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
#     undef  allocate_stack_parse
#     define allocate_stack_parse(size, alignment) ::_alloca(static_cast<std::size_t>(size) + (static_cast<std::size_t>(alignment) - 1u))
#   endif
# define allocate_Memory ~, namespace
# define allocate_STACK  ~, stack

// `Memory::allocator`: `thread_local` allocator designated to current thread
// Memory::allocate(…) -> Memory::allocator.allocate(std::size_t size, std::size_t alignment)
// `std::size_t alignment` must be a power of two
::mmap();
::VirtualAllocEx();
1  allocation(s) => 4096  bytes overall [2 ** 1] + [2 ** 12] == [2 ** 13]
13 allocation(s) => 8192  bytes overall
26 allocation(s) => 16384 bytes overall

/* Class > Memory Buffer ->> Diagnostic representation of (memory) storage */
template <typename base = unsigned char>
class MemoryBuffer /* final */ {
  private:
    template <typename subbase> struct baseof                         /* final */ { typedef subbase type; };
    template <typename subbase> struct baseof<subbase const>          /* final */ { typedef subbase type; };
    template <typename subbase> struct baseof<subbase const volatile> /* final */ { typedef subbase type; };
    template <typename subbase> struct baseof<subbase       volatile> /* final */ { typedef subbase type; };

  public:
    typename baseof<base>::type *value;
    std::size_t                  size;

    /* constexpr */ static MemoryBuffer<base> const null;

    /* ... */
    /* constexpr */ inline operator typename baseof<base>::type               *() const /* volatile noexcept */ { return this -> value; }
    /* constexpr */ inline operator typename baseof<base>::type const         *() const /* volatile noexcept */ { return this -> value; }
    /* constexpr */ inline operator typename baseof<base>::type const volatile*() const /* volatile noexcept */ { return this -> value; }
    /* constexpr */ inline operator typename baseof<base>::type       volatile*() const /* volatile noexcept */ { return this -> value; }

    template <typename type>
    inline operator type*() const /* volatile noexcept */ {
      return reinterpret_cast<type*>(static_cast<void*>(this -> value));
    }
};
  template <typename base>
  MemoryBuffer<base> const MemoryBuffer<base>::null = {NULL, 0u};

/* Namespace > Memory */
class Memory /* final */ {
  public:
    enum ControlParameter /* : unsigned char */ {
      DYNAMIC,    // ->> `Memory::reallocate(...)` movable    storage
      EXECUTABLE, // ->> `Memory::  allocate(...)` executable storage
      STACK
    };

  /* ... */
  private:
    // ...
    class MemoryPool /* final */ {
      void       *value;
      std::size_t size;
      std::size_t capacity;
      std::size_t alignment;
    };

    // ... ->> Metadata information of `MemoryPool::value`
    class MemoryHeader /* final */ {
      std::size_t size;
      std::size_t offset;
    };

    // ... ->> Thread-specific storage manager
    class MemoryAllocator /* final */ {
      MemoryPool  pool;
      MemoryPool *pools;
      std::size_t capacity;
      std::size_t length;

      /* ... */
      inline static MemoryBuffer<> allocate  (std::size_t, std::size_t)        /* noexcept */;
      inline static MemoryBuffer<> reallocate(void*, std::size_t, std::size_t) /* noexcept */;
      inline static MemoryBuffer<> release   (void*)                           /* noexcept */;
    };

  public:
    #if __cpp_threadsafe_static_init // --> 200806L
      thread_local
    #endif
    static MemoryAllocator allocator;
};
  typedef Memory::ControlParameter MemoryControlParameter;

/* Main */
int main(int, char*[]) /* noexcept */ {
  Memory::allocate;                            // Memory::allocate
  Memory::STACK;                               // Memory::STACK
  Memory::allocate(1u, 2u);                    // Memory::                applyControlParameter()              ->* Memory::allocate(1u, 2u);
  Memory::allocate(1u, 2u, );                  // Memory::                applyControlParameter()              ->* Memory::allocate(1u, 2u);
  Memory::allocate(1u, 2u, A);                 // Memory::                applyControlParameter(A)             ->* Memory::allocate(1u, 2u);
  Memory::allocate(1u, 2u, B | STACK);         // Memory::applyControlParameter(B | STACK)         ->* Memory::allocate(1u, 2u);
  Memory::allocate(1u, 2u, B | Memory::STACK); // Memory::applyControlParameter(B | Memory::STACK) ->* Memory::allocate(1u, 2u);
  Memory::allocate(1u, 2u, STACK);             // Memory::                applyControlParameter(STACK)         ->* ::_alloca(static_cast<std::size_t>(1u) + (static_cast<std::size_t>(2u) - 1u));
  Memory::allocate(1u, 2u, Memory::STACK);     // Memory::template _<85>::applyControlParameter(Memory::STACK) ->* ::_alloca(static_cast<std::size_t>(1u) + (static_cast<std::size_t>(2u) - 1u));
  Memory::allocate(1u, 2u, STACK         | B); // Memory::allocate_stack        | B(STACK         | B)(1u, 2u);
  Memory::allocate(1u, 2u, Memory::STACK | B); // Memory::template _<87>::STACK | B(Memory::STACK | B)(1u, 2u);
}
