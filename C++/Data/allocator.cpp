/* Import */
#if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
# include <alloca.h>  // --> ::alloca(...)
# include <pthread.h> // --> -pthread; ::pthread_self()
# include <unistd.h>  // --> ::sysconf(...)
#elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
# define _WIN32_WINNT 0x0501
#
# include <malloc.h>  // --> ::_alloca(...)
# include <windows.h> // --> <processthreadsapi.h>, <sysinfoapi.h>; ::GetCurrentThreadId()
#endif

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

/* Definition > ... */
#undef allocate_
#undef heap
#undef namespace
#undef stack

#define allocate(size, alignment, ...) defer(combine, allocate_, defer(second, allocate_ ## __VA_ARGS__, heap, ~))(__VA_ARGS__)(size, alignment)
# define allocate_heap(...) applyControlParameter(__VA_ARGS__) ->* allocate_heap_parse   // --> allocate(..., not ::Memory::STACK)
#   define allocate_heap_parse(size, alignment) Memory::allocate(size, alignment)        //
# define allocate_Memory     ~, namespace                                                // --> allocate(..., Memory::...)
# define allocate_namespace  template _<__LINE__>                                        // --> allocate(..., ::Memory::STACK)
# define allocate_STACK      ~, stack                                                    // --> allocate(..., STACK)
# define allocate_stack(...) applyControlParameter(__VA_ARGS__) ->* allocate_stack_parse //
#   define allocate_stack_parse(size, alignment) (static_cast<void>(static_cast<std::size_t>(size), static_cast<std::size_t>(alignment)), static_cast<void*>(NULL))
#   if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
#     undef  allocate_stack_parse
#     define allocate_stack_parse(size, alignment) ::alloca(static_cast<std::size_t>(size) + (static_cast<std::size_t>(alignment) - 1u))
#   elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
#     undef  allocate_stack_parse
#     define allocate_stack_parse(size, alignment) ::_alloca(static_cast<std::size_t>(size) + (static_cast<std::size_t>(alignment) - 1u))
#   endif
#define combine(argument1, argument2) argument1 ## argument2
#define defer(function, ...) defer_parse(function, (__VA_ARGS__))
# define defer_parse(function, call) function call
#define second(argument1, argument2, ...) argument2
#define STACK(...) applyControlParameter(__VA_ARGS__) ->* allocate_stack_parse // --> allocate(..., Memory::STACK)

// ...
class Memory;
class MemoryAllocator;

template <typename = unsigned char>
class MemoryBuffer;

/* Class */
// : Memory Buffer ->> Diagnostic unit representation of (memory) storage
template <typename base>
class MemoryBuffer /* final */ {
  private:
    template <typename subbase> struct baseof                         /* final */ { typedef subbase type; };
    template <typename subbase> struct baseof<subbase const>          /* final */ { typedef subbase type; };
    template <typename subbase> struct baseof<subbase const volatile> /* final */ { typedef subbase type; };
    template <typename subbase> struct baseof<subbase       volatile> /* final */ { typedef subbase type; };

  public:
    typedef base *type;

    /* ... */
    typename baseof<base>::type *value;
    std::size_t                  size;

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

// : Memory ->> Namespace for base memory manipulation
class Memory /* final */ {
  private:
    class MemoryHeader /* final */ {
      std::size_t size;
      std::size_t offset;
    };

  public:
    enum ControlParameter /* : unsigned char */ {
      AUTOMATIC,  // ->> Manipulate storage the default way; Overridden by other `Memory::ControlParameter`s
      CLEAR,      // ->> `Memory::  allocate(...)` or `Memory::reallocate(...)` zeroed storage
      DYNAMIC,    // ->> `Memory::reallocate(...)` movable storage
      EXECUTABLE, // ->> `Memory::  allocate(...)` executable storage; Can not re-register storage with different attributes
      EXTENDED,   // ->> Instantiate `MemoryAllocator` with additional attributes; such as extensible storage
      STACK       // ->> `Memory::allocate(...)` automatic storage -- whose lifetime depends on the stack frame it was allocated from; Mutually exclusive with other `Memory::ControlParameter`s
    };

    /* ... */
    #if __cplusplus >= 201103L && defined(__cpp_threadsafe_static_init) // --> 200806L
      thread_local
    #endif
    static MemoryAllocator allocator;

    /* ... */
    /* constexpr */ inline static MemoryBuffer<> (allocate)  (                      std::size_t, std::size_t = /* --> alignof(unsigned char) */ sizeof(unsigned char), ControlParameter = Memory::AUTOMATIC) /* noexcept */;
    /* constexpr */ inline static bool           (deallocate)(void const volatile*)                                                                                                                          /* noexcept */;
    /* constexpr */ inline static MemoryBuffer<> (reallocate)(void const volatile*, std::size_t, std::size_t = /* --> alignof(unsigned char) */ sizeof(unsigned char), ControlParameter = Memory::AUTOMATIC) /* noexcept */;

    // ...
    inline static std::size_t getAllocatorAlignment() /* noexcept */ {
      #if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__NT__) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__TOS_WIN__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
        return Memory::getAllocatorGranularity();
      #endif

      return 1u; // --> alignof(unsigned char)
    }

    inline static std::size_t getAllocatorGranularity() /* noexcept */ {
      #if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
        static std::size_t const granularity = ::sysconf(_SC_PAGESIZE); // --> long
      #elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
        static std::size_t granularity = 0u;

        // ...
        if (0u == granularity) {
          HMODULE const kernel32 = ::LoadLibraryExW(L"kernel32.dll", static_cast<HANDLE>(NULL), 0x00u);
            void (*const GetSystemInfo)  (LPSYSTEM_INFO)            = reinterpret_cast<void (*const&)(LPSYSTEM_INFO)>           (static_cast<FARPROC const&>(NULL != kernel32                          ? ::GetProcAddress(kernel32, "GetSystemInfo")   : NULL));
            BOOL (*const IsWow64Process2)(HANDLE, USHORT*, USHORT*) = reinterpret_cast<BOOL (*const&)(HANDLE, USHORT*, USHORT*)>(static_cast<FARPROC const&>(NULL != kernel32 && NULL != GetSystemInfo ? ::GetProcAddress(kernel32, "IsWow64Process2") : NULL));
          USHORT      processArchitecture = IMAGE_FILE_MACHINE_UNKNOWN;
          SYSTEM_INFO systemInformation   = {};

          // ...
          ((NULL == GetSystemInfo) || (NULL != IsWow64Process2 && FALSE != IsWow64Process2(::GetCurrentProcess(), &processArchitecture, static_cast<USHORT*>(NULL)) && IMAGE_FILE_MACHINE_UNKNOWN != processArchitecture) ? ::GetNativeSystemInfo : GetSystemInfo)(&systemInformation);
          granularity = systemInformation.dwAllocationGranularity; // --> DWORD
        }
      #else
        static std::size_t const granularity = 1u;
      #endif

      // ...
      return granularity;
    }
};

// : Memory Control Parameter
typedef Memory::ControlParameter MemoryControlParameter;

// : Memory Allocator ->> Thread-specific (memory) storage manager
class MemoryAllocator /* final */ {
  friend class Memory;

  private:
    template <typename>
    struct buffer_cast;

    template <typename base>
    struct buffer_cast<base*> {
      private:
        base *const value;

      public:
        /* constexpr */          inline buffer_cast(base*                const buffer) /* noexcept */ : value(buffer)                                                                           {}
        /* constexpr */          inline buffer_cast(base const*          const buffer) /* noexcept */ : value(const_cast<base*>(buffer))                                                        {}
        /* constexpr */          inline buffer_cast(base const volatile* const buffer) /* noexcept */ : value(const_cast<base*>(buffer))                                                        {}
        /* constexpr */          inline buffer_cast(base       volatile* const buffer) /* noexcept */ : value(const_cast<base*>(buffer))                                                        {}
        template <typename type> inline buffer_cast(type*                const buffer) /* noexcept */ : value(static_cast<base*>(const_cast<void*>(static_cast<void const volatile*>(buffer)))) {}

        /* ... */
        /* constexpr */ inline operator base*() const /* noexcept */ {
          return this -> value;
        }
    };

    template <typename base> struct buffer_cast<base*                const>          : public buffer_cast<base*>                {                                                                                                       };
    template <typename base> struct buffer_cast<base*                const volatile> : public buffer_cast<base*>                {                                                                                                       };
    template <typename base> struct buffer_cast<base*                      volatile> : public buffer_cast<base*>                {                                                                                                       };
    template <typename base> struct buffer_cast<base const*>                         : public buffer_cast<base*>                { /* constexpr */ inline operator base const*         () const /* noexcept */ { return this -> value; } };
    template <typename base> struct buffer_cast<base const*          const>          : public buffer_cast<base const*>          {                                                                                                       };
    template <typename base> struct buffer_cast<base const*          const volatile> : public buffer_cast<base const*>          {                                                                                                       };
    template <typename base> struct buffer_cast<base const*                volatile> : public buffer_cast<base const*>          {                                                                                                       };
    template <typename base> struct buffer_cast<base const volatile*>                : public buffer_cast<base*>                { /* constexpr */ inline operator base const volatile*() const /* noexcept */ { return this -> value; } };
    template <typename base> struct buffer_cast<base const volatile* const>          : public buffer_cast<base const volatile*> {                                                                                                       };
    template <typename base> struct buffer_cast<base const volatile* const volatile> : public buffer_cast<base const volatile*> {                                                                                                       };
    template <typename base> struct buffer_cast<base const volatile*       volatile> : public buffer_cast<base const volatile*> {                                                                                                       };
    template <typename base> struct buffer_cast<base       volatile*>                : public buffer_cast<base*>                { /* constexpr */ inline operator base       volatile*() const /* noexcept */ { return this -> value; } };
    template <typename base> struct buffer_cast<base       volatile* const>          : public buffer_cast<base       volatile*> {                                                                                                       };
    template <typename base> struct buffer_cast<base       volatile* const volatile> : public buffer_cast<base       volatile*> {                                                                                                       };
    template <typename base> struct buffer_cast<base       volatile*       volatile> : public buffer_cast<base       volatile*> {                                                                                                       };

    // ...
    template <typename base>
    struct function_cast /* final */ {
      private:
        base &value;

      public:
        /* constexpr */          inline function_cast(base& function) /* noexcept */ : value(function)                                                              {}
        template <typename type> inline function_cast(type& function) /* noexcept */ : value(*reinterpret_cast<base* const&>(static_cast<type* const&>(&function))) {}

        /* ... */
        /* constexpr */ inline operator base&() const /* noexcept */ {
          return this -> value;
        }
    };

    /* ... */
    // : Memory Function Kind ->> Qualification specifications of parameter/ return type(s) of `MemoryFunction`
    enum MemoryFunctionTypeQualifier /* : unsigned char */ {
      // Presuming a type `byte` for example, these qualifications will be accounted for -->
      ARRAY_BASED           = 0x01u, // byte [const] [volatile] (&)[]
      CONSTANT              = 0x02u, // byte [const]
      OBJECT_BASED          = 0x04u, // byte [const] [volatile]
      POINTER_BASED         = 0x08u, // byte [const] [volatile]* [const] [volatile]
      REFERENCE_BASED       = 0x10u, // byte&
      TEMPORARY_ARRAY_BASED = 0x20u, // byte [const] [volatile] (&&)[]
      VOLATILE              = 0x40u, // byte [volatile]

      CONSTANT_VOLATILE = CONSTANT | VOLATILE
    };

    // : Memory Function Base            ->> Return type of `MemoryFunction`
    // : Memory Function Base Terminator ->> Default `MemoryFunctionBase`
    template <typename, MemoryFunctionTypeQualifier> class MemoryFunctionBase;
    typedef MemoryFunctionBase<void, MemoryAllocator::OBJECT_BASED> MemoryFunctionBaseDefault;

    // : Memory Function Parameter            ->> Parameter type of `MemoryFunction`
    // : Memory Function Parameter Terminator ->> End of `MemoryFunction` parameter list
    template <typename, MemoryFunctionTypeQualifier> class MemoryFunctionParameter /* final */ {};
    typedef MemoryFunctionParameter<void, static_cast<MemoryFunctionTypeQualifier>(0x00u)> MemoryFunctionParameterTerminator;

    // : Memory Function (Traits) --- NOTE  (Lapys) -> Handles all variations of a function signature eg: `void ()` may have `void const ()`, `void* ()`, and `void (&)[]` variations
    //                            --- RULES (Lapys) -> Maximum arity of 3 parameters
    //                            --- WARN  (Lapys) -> Does not handle function signatures with compatible/ similar types eg: `typeid signed () != typeid unsigned ()`; Requires type storage which C++ does not support
    template <class, class = MemoryFunctionParameterTerminator, class = MemoryFunctionParameterTerminator, class = MemoryFunctionParameterTerminator>
    class MemoryFunction;

    class MemoryFunctionTraits {
      public:
        template <typename, typename> struct is_same             /* final */ { static bool const value = false; };
        template <typename base>      struct is_same<base, base> /* final */ { static bool const value = true;  };

        // ...
        template <typename, typename baseA = MemoryFunctionParameterTerminator, typename baseB = MemoryFunctionParameterTerminator, typename baseC = MemoryFunctionParameterTerminator, bool = is_same<baseA const volatile, void const volatile>::value || is_same<baseB const volatile, void const volatile>::value || is_same<baseC const volatile, void const volatile>::value> struct parameterize;
        template <typename base>                                                 struct parameterize<base, MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator, false> /* final */ { typedef base (type)();                    };
        template <typename base, typename baseA>                                 struct parameterize<base, baseA,                             MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator, false> /* final */ { typedef base (type)(baseA);               };
        template <typename base, typename baseA, typename baseB>                 struct parameterize<base, baseA,                             baseB,                             MemoryFunctionParameterTerminator, false> /* final */ { typedef base (type)(baseA, baseB);        };
        template <typename base, typename baseA, typename baseB, typename baseC> struct parameterize<base, baseA,                             baseB,                             baseC,                             false> /* final */ { typedef base (type)(baseA, baseB, baseC); };
        template <typename base, typename baseA, typename baseB, typename baseC> struct parameterize<base, baseA,                             baseB,                             baseC,                             true>  /* final */ { typedef base (type)(...);                 };

        // ... ->> Determines const-volatile and reference qualifiers of specified `base` type
        template <typename base> struct qualifiersof                       /* final */ { typedef base                              type; static MemoryFunctionTypeQualifier const cv = static_cast<MemoryFunctionTypeQualifier>(0x00u); static MemoryFunctionTypeQualifier const value = MemoryAllocator::OBJECT_BASED;                                                                                                                                                                                                                                                                                                                            };
        template <typename base> struct qualifiersof<base const>           /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = MemoryAllocator::CONSTANT;                       static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::OBJECT_BASED)  | static_cast<unsigned char>(MemoryAllocator::CONSTANT));                                                                                                                                                                                             };
        template <typename base> struct qualifiersof<base const volatile>  /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = MemoryAllocator::CONSTANT_VOLATILE;              static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::OBJECT_BASED)  | static_cast<unsigned char>(MemoryAllocator::CONSTANT)                                                                   | static_cast<unsigned char>(MemoryAllocator::VOLATILE));                                                                   };
        template <typename base> struct qualifiersof<base       volatile>  /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = MemoryAllocator::VOLATILE;                       static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::OBJECT_BASED)  |                                                                                                                           static_cast<unsigned char>(MemoryAllocator::VOLATILE));                                                                   };
        template <typename base> struct qualifiersof<base*>                /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = static_cast<MemoryFunctionTypeQualifier>(0x00u); static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | (qualifiersof<base>::value & MemoryAllocator::CONSTANT ? static_cast<unsigned char>(MemoryAllocator::CONSTANT) : 0x00u) | (qualifiersof<base>::value & MemoryAllocator::VOLATILE ? static_cast<unsigned char>(MemoryAllocator::VOLATILE) : 0x00u)); };
        template <typename base> struct qualifiersof<base* const>          /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = MemoryAllocator::CONSTANT;                       static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | (qualifiersof<base>::value & MemoryAllocator::CONSTANT ? static_cast<unsigned char>(MemoryAllocator::CONSTANT) : 0x00u) | (qualifiersof<base>::value & MemoryAllocator::VOLATILE ? static_cast<unsigned char>(MemoryAllocator::VOLATILE) : 0x00u)); };
        template <typename base> struct qualifiersof<base* const volatile> /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = MemoryAllocator::CONSTANT_VOLATILE;              static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | (qualifiersof<base>::value & MemoryAllocator::CONSTANT ? static_cast<unsigned char>(MemoryAllocator::CONSTANT) : 0x00u) | (qualifiersof<base>::value & MemoryAllocator::VOLATILE ? static_cast<unsigned char>(MemoryAllocator::VOLATILE) : 0x00u)); };
        template <typename base> struct qualifiersof<base*       volatile> /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = MemoryAllocator::VOLATILE;                       static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | (qualifiersof<base>::value & MemoryAllocator::CONSTANT ? static_cast<unsigned char>(MemoryAllocator::CONSTANT) : 0x00u) | (qualifiersof<base>::value & MemoryAllocator::VOLATILE ? static_cast<unsigned char>(MemoryAllocator::VOLATILE) : 0x00u)); };
        template <typename base> struct qualifiersof<base (&)[]>           /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = static_cast<MemoryFunctionTypeQualifier>(0x00u); static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED)   | (qualifiersof<base>::value & MemoryAllocator::CONSTANT ? static_cast<unsigned char>(MemoryAllocator::CONSTANT) : 0x00u) | (qualifiersof<base>::value & MemoryAllocator::VOLATILE ? static_cast<unsigned char>(MemoryAllocator::VOLATILE) : 0x00u)); };
        #ifdef __cpp_rvalue_references // --> 200610L
          template <typename base> struct qualifiersof<base (&&)[]> /* final */ { typedef typename qualifiersof<base>::type type; static MemoryFunctionTypeQualifier const cv = static_cast<MemoryFunctionTypeQualifier>(0x00u); static MemoryFunctionTypeQualifier const value = static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED) | (qualifiersof<base>::value & MemoryAllocator::CONSTANT ? static_cast<unsigned char>(MemoryAllocator::CONSTANT) : 0x00u) | (qualifiersof<base>::value & MemoryAllocator::VOLATILE ? static_cast<unsigned char>(MemoryAllocator::VOLATILE) : 0x00u)); };
        #endif

        // ... ->> Const-volatile-/ reference-qualifies specified `base` type
        template <typename base, MemoryFunctionTypeQualifier, unsigned char = 0x00u> struct qualify;
        template <typename base, unsigned char specialization> struct qualify<base,                MemoryAllocator::ARRAY_BASED,           specialization> /* final */ { typedef base              (&type)[]; };
        template <unsigned char specialization>                struct qualify<void,                MemoryAllocator::ARRAY_BASED,           specialization> /* final */ { typedef void                type;    };
        template <unsigned char specialization>                struct qualify<void const,          MemoryAllocator::ARRAY_BASED,           specialization> /* final */ { typedef void const          type;    };
        template <unsigned char specialization>                struct qualify<void const volatile, MemoryAllocator::ARRAY_BASED,           specialization> /* final */ { typedef void const volatile type;    };
        template <unsigned char specialization>                struct qualify<void       volatile, MemoryAllocator::ARRAY_BASED,           specialization> /* final */ { typedef void       volatile type;    };
        template <typename base, unsigned char specialization> struct qualify<base,                MemoryAllocator::CONSTANT,              specialization> /* final */ { typedef base const          type;    };
        template <typename base, unsigned char specialization> struct qualify<base,                MemoryAllocator::CONSTANT_VOLATILE,     specialization> /* final */ { typedef base const volatile type;    };
        template <typename base, unsigned char specialization> struct qualify<base,                MemoryAllocator::OBJECT_BASED,          specialization> /* final */ { typedef base                type;    };
        template <typename base, unsigned char specialization> struct qualify<base,                MemoryAllocator::POINTER_BASED,         specialization> /* final */ { typedef base               *type;    };
        template <unsigned char specialization>                struct qualify<void,                MemoryAllocator::REFERENCE_BASED,       specialization> /* final */ { typedef void                type;    };
        template <unsigned char specialization>                struct qualify<void const,          MemoryAllocator::REFERENCE_BASED,       specialization> /* final */ { typedef void const          type;    };
        template <unsigned char specialization>                struct qualify<void const volatile, MemoryAllocator::REFERENCE_BASED,       specialization> /* final */ { typedef void const volatile type;    };
        template <unsigned char specialization>                struct qualify<void       volatile, MemoryAllocator::REFERENCE_BASED,       specialization> /* final */ { typedef void       volatile type;    };
        template <typename base, unsigned char specialization> struct qualify<base,                MemoryAllocator::REFERENCE_BASED,       specialization> /* final */ { typedef base               &type;    };
        template <typename base, unsigned char specialization> struct qualify<base&,               MemoryAllocator::REFERENCE_BASED,       specialization> /* final */ { typedef base               &type;    };
        template <unsigned char specialization>                struct qualify<void,                MemoryAllocator::TEMPORARY_ARRAY_BASED, specialization> /* final */ { typedef void                type;    };
        template <unsigned char specialization>                struct qualify<void const,          MemoryAllocator::TEMPORARY_ARRAY_BASED, specialization> /* final */ { typedef void const          type;    };
        template <unsigned char specialization>                struct qualify<void const volatile, MemoryAllocator::TEMPORARY_ARRAY_BASED, specialization> /* final */ { typedef void const volatile type;    };
        template <unsigned char specialization>                struct qualify<void       volatile, MemoryAllocator::TEMPORARY_ARRAY_BASED, specialization> /* final */ { typedef void       volatile type;    };
        template <typename base, unsigned char specialization> struct qualify<base,                MemoryAllocator::VOLATILE,              specialization> /* final */ { typedef base volatile       type;    };
        #ifdef __cpp_rvalue_references // --> 200610L
          template <typename base, unsigned char specialization> struct qualify<base, MemoryAllocator::TEMPORARY_ARRAY_BASED, specialization> /* final */ { typedef base (&&type)[]; };
        #else
          template <typename base, unsigned char specialization> struct qualify<base, MemoryAllocator::TEMPORARY_ARRAY_BASED, specialization> /* final */ { typedef base type; };
        #endif

        // ... ->> Const-volatile-/ reference-qualifies indexed parameter within specified function type
        template <std::size_t index, MemoryFunctionTypeQualifier qualifier, typename baseA = MemoryFunctionParameterTerminator, typename baseB = MemoryFunctionParameterTerminator, typename baseC = MemoryFunctionParameterTerminator>
        struct qualifyat /* final */ {
          template <std::size_t subindex, bool = index == subindex, unsigned char = 0x00u> struct at;
          template <unsigned char specialization>                                          struct at<0u, false, specialization> /* final */ { typedef baseA                                    type; };
          template <unsigned char specialization>                                          struct at<0u, true,  specialization> /* final */ { typedef typename qualify<baseA, qualifier>::type type; };
          template <unsigned char specialization>                                          struct at<1u, false, specialization> /* final */ { typedef baseB                                    type; };
          template <unsigned char specialization>                                          struct at<1u, true,  specialization> /* final */ { typedef typename qualify<baseB, qualifier>::type type; };
          template <unsigned char specialization>                                          struct at<2u, false, specialization> /* final */ { typedef baseC                                    type; };
          template <unsigned char specialization>                                          struct at<2u, true,  specialization> /* final */ { typedef typename qualify<baseC, qualifier>::type type; };
        };
    };

    template <typename base, MemoryFunctionTypeQualifier baseQualifiers, typename baseA, MemoryFunctionTypeQualifier baseAQualifiers, typename baseB, MemoryFunctionTypeQualifier baseBQualifiers, typename baseC, MemoryFunctionTypeQualifier baseCQualifiers>
    class MemoryFunction<MemoryFunctionBase<base, baseQualifiers>, MemoryFunctionParameter<baseA, baseAQualifiers>, MemoryFunctionParameter<baseB, baseBQualifiers>, MemoryFunctionParameter<baseC, baseCQualifiers> > /* final */ : public MemoryFunctionTraits {
      private:
        template <typename subbase, typename subbaseA, typename subbaseB, typename subbaseC>
        struct assert /* final */ {
          static bool const value = (
            is_same<base,  typename qualifiersof<subbase> ::type>::value && (baseQualifiers  == qualifiersof<subbase>::value                    || (qualifiersof<subbase> ::value & baseQualifiers))  &&
            is_same<baseA, typename qualifiersof<subbaseA>::type>::value && (baseAQualifiers == static_cast<MemoryFunctionTypeQualifier>(0x00u) || (qualifiersof<subbaseA>::value & baseAQualifiers)) &&
            is_same<baseB, typename qualifiersof<subbaseB>::type>::value && (baseBQualifiers == static_cast<MemoryFunctionTypeQualifier>(0x00u) || (qualifiersof<subbaseB>::value & baseBQualifiers)) &&
            is_same<baseC, typename qualifiersof<subbaseC>::type>::value && (baseCQualifiers == static_cast<MemoryFunctionTypeQualifier>(0x00u) || (qualifiersof<subbaseC>::value & baseCQualifiers))
          );
        };

        /* ... */
        template <typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), typeA const argumentA, typeB const argumentB, typeC const argumentC, unsigned char const (*const)[false == is_same<functionType const volatile, void const volatile>::value] = NULL) {
          if (false == is_same<functionTypeC, MemoryFunctionParameterTerminator>::value) return MemoryFunction::cast<type>(function_cast<functionType (functionTypeA, functionTypeB, functionTypeC)>(function)(MemoryFunction::cast<functionTypeA>(static_cast<typeA>(argumentA)), MemoryFunction::cast<functionTypeB>(static_cast<typeB>(argumentB)), MemoryFunction::cast<functionTypeC>(static_cast<typeC>(argumentC))));
          if (false == is_same<functionTypeB, MemoryFunctionParameterTerminator>::value) return MemoryFunction::cast<type>(function_cast<functionType (functionTypeA, functionTypeB)>               (function)(MemoryFunction::cast<functionTypeA>(static_cast<typeA>(argumentA)), MemoryFunction::cast<functionTypeB>(static_cast<typeB>(argumentB))));
          if (false == is_same<functionTypeA, MemoryFunctionParameterTerminator>::value) return MemoryFunction::cast<type>(function_cast<functionType (functionTypeA)>                              (function)(MemoryFunction::cast<functionTypeA>(static_cast<typeA>(argumentA))));

          return MemoryFunction::cast<type>(function_cast<functionType ()>(function)());
        }

        template <typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), typeA const argumentA, typeB const argumentB, typeC const argumentC, unsigned char const (*const)[false != is_same<functionType const volatile, void const volatile>::value] = NULL) {
          static functionType (*subfunction)(functionTypeA, functionTypeB, functionTypeC);
          struct callback /* final */ {
            static type value()                                                                          { return function_cast<functionType ()>                                           (*subfunction)(),                                                                                                                    type(); }
            static type value(functionTypeA argumentA)                                                   { return function_cast<functionType (functionTypeA)>                              (*subfunction)(static_cast<functionTypeA>(argumentA)),                                                                               type(); }
            static type value(functionTypeA argumentA, functionTypeB argumentB)                          { return function_cast<functionType (functionTypeA, functionTypeB)>               (*subfunction)(static_cast<functionTypeA>(argumentA), static_cast<functionTypeB>(argumentB)),                                        type(); }
            static type value(functionTypeA argumentA, functionTypeB argumentB, functionTypeC argumentC) { return function_cast<functionType (functionTypeA, functionTypeB, functionTypeC)>(*subfunction)(static_cast<functionTypeA>(argumentA), static_cast<functionTypeB>(argumentB), static_cast<functionTypeC>(argumentC)), type(); }
          };

          subfunction = &static_cast<functionType (&)(functionTypeA, functionTypeB, functionTypeC)>(function_cast<functionType (functionTypeA, functionTypeB, functionTypeC)>(function));
          return MemoryFunction::call<type, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(
            false == is_same<functionTypeC, MemoryFunctionParameterTerminator>::value ? function_cast<void (...)>(static_cast<type (&)(functionTypeA, functionTypeB, functionTypeC)>(callback::value)) :
            false == is_same<functionTypeB, MemoryFunctionParameterTerminator>::value ? function_cast<void (...)>(static_cast<type (&)(functionTypeA, functionTypeB)>               (callback::value)) :
            false == is_same<functionTypeA, MemoryFunctionParameterTerminator>::value ? function_cast<void (...)>(static_cast<type (&)(functionTypeA)>                              (callback::value)) :
            function_cast<void (...)>(static_cast<type (&)()>(callback::value)), static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC)
          );
        }

        template <std::size_t arity, typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), MemoryFunctionTypeQualifier const (&)[3], typeA const argumentA, typeB const argumentB, typeC const argumentC, unsigned char const (*const)[0u == arity && false == (
          is_same<functionTypeA const volatile, void const volatile>::value ||
          is_same<functionTypeB const volatile, void const volatile>::value ||
          is_same<functionTypeC const volatile, void const volatile>::value
        )] = NULL) { return MemoryFunction::call<functionType, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC)); }

        template <std::size_t arity, typename, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        static type call(void (&)(...), MemoryFunctionTypeQualifier const (&)[3], typeA const, typeB const, typeC const, unsigned char const (*const)[0u == arity && false != (
          is_same<functionTypeA const volatile, void const volatile>::value ||
          is_same<functionTypeB const volatile, void const volatile>::value ||
          is_same<functionTypeC const volatile, void const volatile>::value
        )] = NULL);

        template <std::size_t arity, typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), MemoryFunctionTypeQualifier const (&qualifiers)[3], typeA const argumentA, typeB const argumentB, typeC const argumentC, unsigned char const (*const)[0u != arity] = NULL) {
          if (qualifiers[arity - 1u] & MemoryAllocator::CONSTANT_VOLATILE) return MemoryFunction::call<arity - 1u, functionType, typename qualifyat<arity - 1u, MemoryAllocator::CONSTANT_VOLATILE, functionTypeA, functionTypeB, functionTypeC>::template at<0u>::type, typename qualifyat<arity - 1u, MemoryAllocator::CONSTANT_VOLATILE, functionTypeA, functionTypeB, functionTypeC>::template at<1u>::type, typename qualifyat<arity - 1u, MemoryAllocator::CONSTANT_VOLATILE, functionTypeA, functionTypeB, functionTypeC>::template at<2u>::type, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifiers[arity - 1u] & MemoryAllocator::CONSTANT)          return MemoryFunction::call<arity - 1u, functionType, typename qualifyat<arity - 1u, MemoryAllocator::CONSTANT,          functionTypeA, functionTypeB, functionTypeC>::template at<0u>::type, typename qualifyat<arity - 1u, MemoryAllocator::CONSTANT,          functionTypeA, functionTypeB, functionTypeC>::template at<1u>::type, typename qualifyat<arity - 1u, MemoryAllocator::CONSTANT,          functionTypeA, functionTypeB, functionTypeC>::template at<2u>::type, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifiers[arity - 1u] & MemoryAllocator::VOLATILE)          return MemoryFunction::call<arity - 1u, functionType, typename qualifyat<arity - 1u, MemoryAllocator::VOLATILE,          functionTypeA, functionTypeB, functionTypeC>::template at<0u>::type, typename qualifyat<arity - 1u, MemoryAllocator::VOLATILE,          functionTypeA, functionTypeB, functionTypeC>::template at<1u>::type, typename qualifyat<arity - 1u, MemoryAllocator::VOLATILE,          functionTypeA, functionTypeB, functionTypeC>::template at<2u>::type, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));

          return MemoryFunction::call<arity, functionType, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC), static_cast<unsigned char const (*)[2u]>(NULL));
        }

        template <std::size_t arity, typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), MemoryFunctionTypeQualifier const (&qualifiers)[3], typeA const argumentA, typeB const argumentB, typeC const argumentC, unsigned char const (*const)[2u]) {
          if (qualifiers[arity - 1u] & MemoryAllocator::ARRAY_BASED)           return MemoryFunction::call<arity - 1u, functionType, typename qualifyat<arity - 1u, MemoryAllocator::ARRAY_BASED,           functionTypeA, functionTypeB, functionTypeC>::template at<0u>::type, typename qualifyat<arity - 1u, MemoryAllocator::ARRAY_BASED,           functionTypeA, functionTypeB, functionTypeC>::template at<1u>::type, typename qualifyat<arity - 1u, MemoryAllocator::ARRAY_BASED,           functionTypeA, functionTypeB, functionTypeC>::template at<2u>::type, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifiers[arity - 1u] & MemoryAllocator::OBJECT_BASED)          return MemoryFunction::call<arity - 1u, functionType, typename qualifyat<arity - 1u, MemoryAllocator::OBJECT_BASED,          functionTypeA, functionTypeB, functionTypeC>::template at<0u>::type, typename qualifyat<arity - 1u, MemoryAllocator::OBJECT_BASED,          functionTypeA, functionTypeB, functionTypeC>::template at<1u>::type, typename qualifyat<arity - 1u, MemoryAllocator::OBJECT_BASED,          functionTypeA, functionTypeB, functionTypeC>::template at<2u>::type, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifiers[arity - 1u] & MemoryAllocator::POINTER_BASED)         return MemoryFunction::call<arity - 1u, functionType, typename qualifyat<arity - 1u, MemoryAllocator::POINTER_BASED,         functionTypeA, functionTypeB, functionTypeC>::template at<0u>::type, typename qualifyat<arity - 1u, MemoryAllocator::POINTER_BASED,         functionTypeA, functionTypeB, functionTypeC>::template at<1u>::type, typename qualifyat<arity - 1u, MemoryAllocator::POINTER_BASED,         functionTypeA, functionTypeB, functionTypeC>::template at<2u>::type, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifiers[arity - 1u] & MemoryAllocator::TEMPORARY_ARRAY_BASED) return MemoryFunction::call<arity - 1u, functionType, typename qualifyat<arity - 1u, MemoryAllocator::TEMPORARY_ARRAY_BASED, functionTypeA, functionTypeB, functionTypeC>::template at<0u>::type, typename qualifyat<arity - 1u, MemoryAllocator::TEMPORARY_ARRAY_BASED, functionTypeA, functionTypeB, functionTypeC>::template at<1u>::type, typename qualifyat<arity - 1u, MemoryAllocator::TEMPORARY_ARRAY_BASED, functionTypeA, functionTypeB, functionTypeC>::template at<2u>::type, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));

          return MemoryFunction::call<arity - 1u, functionType, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
        }

        template <std::size_t arity, typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), MemoryFunctionTypeQualifier const cv, MemoryFunctionTypeQualifier const (&qualifiers)[3], typeA const argumentA, typeB const argumentB, typeC const argumentC) {
          if (cv & MemoryAllocator::CONSTANT_VOLATILE) return MemoryFunction::call<arity, functionType const volatile, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (cv & MemoryAllocator::CONSTANT)          return MemoryFunction::call<arity, functionType const,          functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (cv & MemoryAllocator::VOLATILE)          return MemoryFunction::call<arity, functionType       volatile, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));

          return MemoryFunction::call<arity, functionType, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
        }

        template <std::size_t arity, typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), MemoryFunctionTypeQualifier const qualifier, MemoryFunctionTypeQualifier const cv, MemoryFunctionTypeQualifier const (&qualifiers)[3], typeA const argumentA, typeB const argumentB, typeC const argumentC, unsigned char const (*const)[1u] = NULL) {
          if (qualifier & MemoryAllocator::CONSTANT_VOLATILE) return MemoryFunction::call<arity, functionType const volatile, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifier, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC), static_cast<unsigned char const (*)[2u]>(NULL));
          if (qualifier & MemoryAllocator::CONSTANT)          return MemoryFunction::call<arity, functionType const,          functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifier, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC), static_cast<unsigned char const (*)[2u]>(NULL));
          if (qualifier & MemoryAllocator::VOLATILE)          return MemoryFunction::call<arity, functionType       volatile, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifier, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC), static_cast<unsigned char const (*)[2u]>(NULL));

          return MemoryFunction::call<arity, functionType, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, qualifier, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC), static_cast<unsigned char const (*)[2u]>(NULL));
        }

        template <std::size_t arity, typename functionType, typename functionTypeA, typename functionTypeB, typename functionTypeC, typename type, typename typeA, typename typeB, typename typeC>
        inline static type call(void (&function)(...), MemoryFunctionTypeQualifier const qualifier, MemoryFunctionTypeQualifier const cv, MemoryFunctionTypeQualifier const (&qualifiers)[3], typeA const argumentA, typeB const argumentB, typeC const argumentC, unsigned char const (*const)[2u]) {
          if (qualifier & MemoryAllocator::ARRAY_BASED)           return MemoryFunction::call<arity, typename qualify<functionType, MemoryAllocator::ARRAY_BASED>          ::type, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifier & MemoryAllocator::OBJECT_BASED)          return MemoryFunction::call<arity, typename qualify<functionType, MemoryAllocator::OBJECT_BASED>         ::type, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifier & MemoryAllocator::POINTER_BASED)         return MemoryFunction::call<arity, typename qualify<functionType, MemoryAllocator::POINTER_BASED>        ::type, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
          if (qualifier & MemoryAllocator::TEMPORARY_ARRAY_BASED) return MemoryFunction::call<arity, typename qualify<functionType, MemoryAllocator::TEMPORARY_ARRAY_BASED>::type, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));

          return MemoryFunction::call<arity, functionType, functionTypeA, functionTypeB, functionTypeC, type, typeA, typeB, typeC>(function, cv, qualifiers, static_cast<typeA>(argumentA), static_cast<typeB>(argumentB), static_cast<typeC>(argumentC));
        }

        // ...
        template <typename type, typename functionType>
        /* constexpr */ inline static type cast(functionType const value) /* noexcept(...) */ {
          return MemoryFunction::cast<type, functionType>(static_cast<functionType>(value), static_cast<bool const (*)[true]>(NULL));
        }

        template <typename type, typename functionType>
        static type cast(functionType const, void const* const, bool const (*const)[false != (is_same<functionType, typename qualify<functionType, MemoryAllocator::REFERENCE_BASED>::type>::value ^ is_same<type, typename qualify<type, MemoryAllocator::REFERENCE_BASED>::type>::value)] = NULL) /* noexcept */;

        template <typename type, typename functionType>
        inline static type cast(functionType const value, void const* const, bool const (*const)[false == (is_same<functionType, typename qualify<functionType, MemoryAllocator::REFERENCE_BASED>::type>::value ^ is_same<type, typename qualify<type, MemoryAllocator::REFERENCE_BASED>::type>::value)] = NULL) /* noexcept(...) */ {
          union byte { unsigned char value; }; // ->> Unsafe
          return static_cast<type>(/* --> std::launder(...) */ (reinterpret_cast<typename qualify<type, MemoryAllocator::REFERENCE_BASED>::type>(const_cast<byte&>(reinterpret_cast<byte const volatile&>(value)))));
        }

        template <typename type, typename functionType>
        /* constexpr */ inline static type cast(functionType const, bool const (*const)[false != is_same<type const volatile, void const volatile>::value]) /* noexcept */ {}

        template <typename type, typename functionType>
        /* constexpr */ inline static type cast(functionType const value, bool const (*const)[false == is_same<type const volatile, void const volatile>::value && sizeof(static_cast<type>(static_cast<functionType>(value)))]) /* noexcept(...) */ {
          return static_cast<type>(static_cast<functionType>(value));
        }

        // ...
        static void (nil)(...) {}

      public:
        void                                  (&function)(...);
        MemoryFunctionTypeQualifier const       cv;
        MemoryFunctionTypeQualifier const       qualifier;
        MemoryFunctionTypeQualifier /* const */ qualifiers[3];

        /* ... */
        /* constexpr */                                                          inline MemoryFunction()                                                                                                            /* noexcept */ : function(MemoryFunction::nil),                 cv(static_cast<MemoryFunctionTypeQualifier>(0x00u)), qualifier(MemoryAllocator::OBJECT_BASED), qualifiers() { this -> qualifiers[0] = baseAQualifiers;            this -> qualifiers[1] = baseBQualifiers;            this -> qualifiers[2] = baseCQualifiers;            }
        template <typename type>                                                 inline MemoryFunction(type (&function)(),                    bool const (*const)[assert<type, baseA, baseB, baseC>::value] = NULL) /* noexcept */ : function(function_cast<void (...)>(function)), cv(qualifiersof<type>::cv),                          qualifier(qualifiersof<type>::value),     qualifiers() { this -> qualifiers[0] = baseAQualifiers;            this -> qualifiers[1] = baseBQualifiers;            this -> qualifiers[2] = baseCQualifiers;            }
        template <typename type, typename typeA>                                 inline MemoryFunction(type (&function)(typeA),               bool const (*const)[assert<type, typeA, baseB, baseC>::value] = NULL) /* noexcept */ : function(function_cast<void (...)>(function)), cv(qualifiersof<type>::cv),                          qualifier(qualifiersof<type>::value),     qualifiers() { this -> qualifiers[0] = qualifiersof<typeA>::value; this -> qualifiers[1] = baseBQualifiers;            this -> qualifiers[2] = baseCQualifiers;            }
        template <typename type, typename typeA, typename typeB>                 inline MemoryFunction(type (&function)(typeA, typeB),        bool const (*const)[assert<type, typeA, typeB, baseC>::value] = NULL) /* noexcept */ : function(function_cast<void (...)>(function)), cv(qualifiersof<type>::cv),                          qualifier(qualifiersof<type>::value),     qualifiers() { this -> qualifiers[0] = qualifiersof<typeA>::value; this -> qualifiers[1] = qualifiersof<typeB>::value; this -> qualifiers[2] = baseCQualifiers;            }
        template <typename type, typename typeA, typename typeB, typename typeC> inline MemoryFunction(type (&function)(typeA, typeB, typeC), bool const (*const)[assert<type, typeA, typeB, typeC>::value] = NULL) /* noexcept */ : function(function_cast<void (...)>(function)), cv(qualifiersof<type>::cv),                          qualifier(qualifiersof<type>::value),     qualifiers() { this -> qualifiers[0] = qualifiersof<typeA>::value; this -> qualifiers[1] = qualifiersof<typeB>::value; this -> qualifiers[2] = qualifiersof<typeC>::value; }

        /* ... */
        template <typename type>                                                 inline type operator ()()                                                                    const { return (type) MemoryFunction::call<0u, base, MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator, type, MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator>(this -> function, this -> qualifier, this -> cv, this -> qualifiers, MemoryFunctionParameterTerminator(), MemoryFunctionParameterTerminator(), MemoryFunctionParameterTerminator()); }
        template <typename type, typename typeA>                                 inline type operator ()(typeA const argumentA)                                               const { return (type) MemoryFunction::call<1u, base, baseA,                             MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator, type, typeA,                             MemoryFunctionParameterTerminator, MemoryFunctionParameterTerminator>(this -> function, this -> qualifier, this -> cv, this -> qualifiers, static_cast<typeA>(argumentA),       MemoryFunctionParameterTerminator(), MemoryFunctionParameterTerminator()); }
        template <typename type, typename typeA, typename typeB>                 inline type operator ()(typeA const argumentA, typeB const argumentB)                        const { return (type) MemoryFunction::call<2u, base, baseA,                             baseB,                             MemoryFunctionParameterTerminator, type, typeA,                             typeB,                             MemoryFunctionParameterTerminator>(this -> function, this -> qualifier, this -> cv, this -> qualifiers, static_cast<typeA>(argumentA),       static_cast<typeB>(argumentB),       MemoryFunctionParameterTerminator()); }
        template <typename type, typename typeA, typename typeB, typename typeC> inline type operator ()(typeA const argumentA, typeB const argumentB, typeC const argumentC) const { return (type) MemoryFunction::call<3u, base, baseA,                             baseB,                             baseC,                             type, typeA,                             typeB,                             typeC>                            (this -> function, this -> qualifier, this -> cv, this -> qualifiers, static_cast<typeA>(argumentA),       static_cast<typeB>(argumentB),       static_cast<typeC>(argumentC));       }
    };

    // : Memory Pool ->> Object-alignment and -size-specific (memory) storage manager
    class MemoryPool /* final */ {
      void       *value;
      std::size_t size;
      std::size_t capacity;
      std::size_t alignment;
    };

    /* ... */
    MemoryPool     pool;             //
    MemoryPool    *pools;            //
    std::size_t    poolsCapacity;    //
    std::size_t    poolsLength;      //
                                     //
    unsigned char *buffer;           // ->> User-provided quasi-`MemoryPool`
    std::size_t    bufferCapacity;   //
    bool           bufferExtendable; //
                                     //
    std::size_t    baseReserveSize;  // --> Memory::getAllocatorGranularity()

    class AllocatorFunction /* final */ : public MemoryFunctionTraits {
      private:
        typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type1u;
        typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type2u;
        typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type3u;
        typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type4u;
        typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type5u;
        typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type6u;
        #ifdef __cpp_lib_byte // --> 201603L
          typedef MemoryFunction<MemoryFunctionBase<std::byte, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type7u;
          typedef MemoryFunction<MemoryFunctionBase<std::byte, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type8u;
        #endif

        unsigned char id : 4u;
        unsigned char storage[sizeof(MemoryFunction<MemoryFunctionBaseDefault>)];
        void         *value;

      public:
        /* constexpr */                                          inline AllocatorFunction()                                                                                                                              /* noexcept */ : id(0u), storage(), value(NULL)                                         {}
        template <typename type, typename typeA>                 inline AllocatorFunction(type (&allocator)(typeA),        bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(1u), storage(), value(::new (&(this -> storage)) type1u(allocator)) {}
        template <typename type, typename typeA>                 inline AllocatorFunction(type (&allocator)(typeA),        bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(3u), storage(), value(::new (&(this -> storage)) type3u(allocator)) {}
        template <typename type, typename typeA>                 inline AllocatorFunction(type (&allocator)(typeA),        bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(5u), storage(), value(::new (&(this -> storage)) type5u(allocator)) {}
        template <typename type, typename typeA, typename typeB> inline AllocatorFunction(type (&allocator)(typeA, typeB), bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(2u), storage(), value(::new (&(this -> storage)) type2u(allocator)) {}
        template <typename type, typename typeA, typename typeB> inline AllocatorFunction(type (&allocator)(typeA, typeB), bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(4u), storage(), value(::new (&(this -> storage)) type4u(allocator)) {}
        template <typename type, typename typeA, typename typeB> inline AllocatorFunction(type (&allocator)(typeA, typeB), bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(6u), storage(), value(::new (&(this -> storage)) type6u(allocator)) {}
        #ifdef __cpp_lib_byte // --> 201603L
          template <typename type, typename typeA>                 inline AllocatorFunction(type (&allocator)(typeA),        bool const (*const)[is_same<std::byte, typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(7u), storage(), value(::new (&(this -> storage)) type7u(allocator)) {}
          template <typename type, typename typeA, typename typeB> inline AllocatorFunction(type (&allocator)(typeA, typeB), bool const (*const)[is_same<std::byte, typename qualifiersof<type>::type>::value] = NULL) /* noexcept */ : id(8u), storage(), value(::new (&(this -> storage)) type8u(allocator)) {}
        #endif

        /* ... */
        inline MemoryBuffer<>::type operator ()(std::size_t const size, std::size_t const alignment) const {
          switch (this -> id) {
            case 1u: return static_cast<MemoryBuffer<>::type>(static_cast<type1u*>(this -> value) -> operator ()<void*>(size + (alignment - 1u)));
            case 2u: return static_cast<MemoryBuffer<>::type>(static_cast<type2u*>(this -> value) -> operator ()<void*>(size, alignment));
            case 3u: return static_cast<MemoryBuffer<>::type>(static_cast<type3u*>(this -> value) -> operator ()<void*>(size + (alignment - 1u)));
            case 4u: return static_cast<MemoryBuffer<>::type>(static_cast<type4u*>(this -> value) -> operator ()<void*>(size, alignment));
            case 5u: return static_cast<MemoryBuffer<>::type>(static_cast<type5u*>(this -> value) -> operator ()<void*>(size + (alignment - 1u)));
            case 6u: return static_cast<MemoryBuffer<>::type>(static_cast<type6u*>(this -> value) -> operator ()<void*>(size, alignment));
            #ifdef __cpp_lib_byte // --> 201603L
              case 7u: return static_cast<MemoryBuffer<>::type>(static_cast<type7u*>(this -> value) -> operator ()<void*>(size + (alignment - 1u)));
              case 8u: return static_cast<MemoryBuffer<>::type>(static_cast<type8u*>(this -> value) -> operator ()<void*>(size, alignment));
            #endif
          }

          return NULL;
        }
    } allocator;

    class DeallocatorFunction /* final */ : public MemoryFunctionTraits {
      private:
        typedef MemoryFunction<MemoryFunctionBase<bool, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))> > type1u;
        typedef MemoryFunction<MemoryFunctionBase<bool, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))> > type2u;
        typedef MemoryFunction<MemoryFunctionBase<bool, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED))> >                                                                                                                                 type3u;
        typedef MemoryFunction<MemoryFunctionBase<void, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))> > type4u;
        typedef MemoryFunction<MemoryFunctionBase<void, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))> > type5u;
        typedef MemoryFunction<MemoryFunctionBase<void, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED))> >                                                                                                                                 type6u;
        #ifdef __cpp_lib_byte // --> 201603L
          typedef MemoryFunction<MemoryFunctionBase<bool, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::byte, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))> > type7u;
          typedef MemoryFunction<MemoryFunctionBase<void, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::byte, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT_VOLATILE) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))> > type8u;
        #endif

        unsigned char id : 4u;
        unsigned char storage[sizeof(MemoryFunction<MemoryFunctionBaseDefault>)];
        void         *value;

      public:
        /* constexpr */                          inline DeallocatorFunction()                                                                                                                                                                                     /* noexcept */ : id(0u), storage(), value(NULL)                                           {}
        template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<bool, typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(1u), storage(), value(::new (&(this -> storage)) type1u(deallocator)) {}
        template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<bool, typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(2u), storage(), value(::new (&(this -> storage)) type2u(deallocator)) {}
        template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<bool, typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(3u), storage(), value(::new (&(this -> storage)) type3u(deallocator)) {}
        template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<void, typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(4u), storage(), value(::new (&(this -> storage)) type4u(deallocator)) {}
        template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<void, typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(5u), storage(), value(::new (&(this -> storage)) type5u(deallocator)) {}
        template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<void, typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(6u), storage(), value(::new (&(this -> storage)) type6u(deallocator)) {}
        #ifdef __cpp_lib_byte // --> 201603L
          template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<bool, typename qualifiersof<type>::type>::value && is_same<std::byte, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(7u), storage(), value(::new (&(this -> storage)) type7u(deallocator)) {}
          template <typename type, typename typeA> inline DeallocatorFunction(type (&deallocator)(typeA), bool const (*const)[is_same<void, typename qualifiersof<type>::type>::value && is_same<std::byte, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(8u), storage(), value(::new (&(this -> storage)) type8u(deallocator)) {}
        #endif

        /* ... */
        /* constexpr */ inline bool operator ()(void* const address) /* noexcept(false) */ {
          switch (this -> id) {
            case 1u: return (static_cast<type1u*>(this -> value) -> qualifiers[0] & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? static_cast<type1u*>(this -> value) -> operator ()<bool>(*static_cast<char*>         (address)) : static_cast<type1u*>(this -> value) -> operator ()<bool>(static_cast<char*>         (address)));
            case 2u: return (static_cast<type1u*>(this -> value) -> qualifiers[0] & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? static_cast<type2u*>(this -> value) -> operator ()<bool>(*static_cast<unsigned char*>(address)) : static_cast<type2u*>(this -> value) -> operator ()<bool>(static_cast<unsigned char*>(address)));
            case 3u: return                                                                                                                                                                                                                                     static_cast<type3u*>(this -> value) -> operator ()<bool>(static_cast<void*>         (address));
            case 4u: return (static_cast<type1u*>(this -> value) -> qualifiers[0] & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? static_cast<type4u*>(this -> value) -> operator ()<void>(*static_cast<char*>         (address)) : static_cast<type4u*>(this -> value) -> operator ()<void>(static_cast<char*>         (address))), true;
            case 5u: return (static_cast<type1u*>(this -> value) -> qualifiers[0] & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? static_cast<type5u*>(this -> value) -> operator ()<void>(*static_cast<unsigned char*>(address)) : static_cast<type5u*>(this -> value) -> operator ()<void>(static_cast<unsigned char*>(address))), true;
            case 6u: return                                                                                                                                                                                                                                     static_cast<type6u*>(this -> value) -> operator ()<void>(static_cast<void*>         (address)),  true;
            #ifdef __cpp_lib_byte // --> 201603L
              case 7u: return (static_cast<type1u*>(this -> value).qualifiers[0] & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? static_cast<type7u*>(this -> value) -> operator ()<bool>(*static_cast<std::byte*>(address)) : static_cast<type7u*>(this -> value) -> operator ()<bool>(static_cast<std::byte*>(address)));
              case 8u: return (static_cast<type1u*>(this -> value).qualifiers[0] & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? static_cast<type8u*>(this -> value) -> operator ()<void>(*static_cast<std::byte*>(address)) : static_cast<type8u*>(this -> value) -> operator ()<void>(static_cast<std::byte*>(address))), true;
            #endif
          }

          return false;
        }
    } deallocator;

    unsigned char reallocator;
    // class ReallocatorFunction /* final */ : public MemoryFunctionTraits {
    //   private:
    //     typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type1u;
    //     typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type2u;
    //     typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type3u;
    //     typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type4u;
    //     typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type5u;
    //     typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type6u;
    //     typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type7u;
    //     typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type8u;
    //     typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type9u;
    //     typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type10u;
    //     typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type11u;
    //     typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type12u;
    //     typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type13u;
    //     typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type14u;
    //     typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type15u;
    //     typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type16u;
    //     typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type17u;
    //     typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type18u;
    //     #ifdef __cpp_lib_byte // --> 201603L
    //       typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type19u;
    //       typedef MemoryFunction<MemoryFunctionBase<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type20u;
    //       typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type21u;
    //       typedef MemoryFunction<MemoryFunctionBase<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type22u;
    //       typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type23u;
    //       typedef MemoryFunction<MemoryFunctionBase<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type24u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type25u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<char,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type26u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type27u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<unsigned char, static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type28u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type29u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<void,          static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE))>,                                                                                                                                 MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type30u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> >                                                                      type31u;
    //       typedef MemoryFunction<MemoryFunctionBase<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::byte,     static_cast<MemoryFunctionTypeQualifier>(static_cast<unsigned char>(MemoryAllocator::CONSTANT) | static_cast<unsigned char>(MemoryAllocator::POINTER_BASED) | static_cast<unsigned char>(MemoryAllocator::VOLATILE) | static_cast<unsigned char>(MemoryAllocator::ARRAY_BASED) | static_cast<unsigned char>(MemoryAllocator::TEMPORARY_ARRAY_BASED))>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED>, MemoryFunctionParameter<std::size_t, MemoryAllocator::OBJECT_BASED> > type32u;
    //     #endif

    //     unsigned char  id : 6u;
    //     unsigned char  storage[sizeof(MemoryFunction<MemoryFunctionBaseDefault>)];
    //     unsigned char *value;

    //   public:
    //     /* constexpr */                                                          inline ReallocatorFunction()                                                                                                                                                                                                            /* noexcept */ : id(0u),  storage(), value(NULL)                                            {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(1u),  storage(), value(::new (&(this -> storage)) type1u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(2u),  storage(), value(::new (&(this -> storage)) type2u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(3u),  storage(), value(::new (&(this -> storage)) type3u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(4u),  storage(), value(::new (&(this -> storage)) type4u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(5u),  storage(), value(::new (&(this -> storage)) type5u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(6u),  storage(), value(::new (&(this -> storage)) type6u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(7u),  storage(), value(::new (&(this -> storage)) type7u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(8u),  storage(), value(::new (&(this -> storage)) type8u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(9u),  storage(), value(::new (&(this -> storage)) type9u (reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(10u), storage(), value(::new (&(this -> storage)) type10u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(11u), storage(), value(::new (&(this -> storage)) type11u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(12u), storage(), value(::new (&(this -> storage)) type12u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(13u), storage(), value(::new (&(this -> storage)) type13u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(14u), storage(), value(::new (&(this -> storage)) type14u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(15u), storage(), value(::new (&(this -> storage)) type15u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(16u), storage(), value(::new (&(this -> storage)) type16u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(17u), storage(), value(::new (&(this -> storage)) type17u(reallocator)) {}
    //     template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(18u), storage(), value(::new (&(this -> storage)) type18u(reallocator)) {}
    //     #ifdef __cpp_lib_byte // --> 201603L
    //       template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(19u), storage(), value(::new (&(this -> storage)) type19u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<char,          typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(20u), storage(), value(::new (&(this -> storage)) type20u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(21u), storage(), value(::new (&(this -> storage)) type21u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<unsigned char, typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(22u), storage(), value(::new (&(this -> storage)) type22u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(23u), storage(), value(::new (&(this -> storage)) type23u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<void,          typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(24u), storage(), value(::new (&(this -> storage)) type24u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(25u), storage(), value(::new (&(this -> storage)) type25u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<char,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(26u), storage(), value(::new (&(this -> storage)) type26u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(27u), storage(), value(::new (&(this -> storage)) type27u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<unsigned char, typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(28u), storage(), value(::new (&(this -> storage)) type28u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(29u), storage(), value(::new (&(this -> storage)) type29u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<void,          typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(30u), storage(), value(::new (&(this -> storage)) type30u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB>                 inline ReallocatorFunction(type (&reallocator)(typeA, typeB),        bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(31u), storage(), value(::new (&(this -> storage)) type31u(reallocator)) {}
    //       template <typename type, typename typeA, typename typeB, typename typeC> inline ReallocatorFunction(type (&reallocator)(typeA, typeB, typeC), bool const (*const)[is_same<std::byte,     typename qualifiersof<type>::type>::value && is_same<std::byte,     typename qualifiersof<typeA>::type>::value] = NULL) /* noexcept */ : id(32u), storage(), value(::new (&(this -> storage)) type32u(reallocator)) {}
    //     #endif

    //     /* ... */
    //     inline void* operator ()(void* const address, std::size_t const size, std::size_t const alignment) const {
    //       switch (this -> id) {
    //         case 1u : return *(reinterpret_cast<type1u  const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type1u const&>(this -> value) .operator ()<void*>(*static_cast<char*>         (address), size + (alignment - 1u)) : reinterpret_cast<type1u  const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size + (alignment - 1u));
    //         case 2u : return *(reinterpret_cast<type2u  const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type2u const&>(this -> value) .operator ()<void*>(*static_cast<char*>         (address), size, alignment)         : reinterpret_cast<type2u  const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size, alignment);
    //         case 3u : return *(reinterpret_cast<type3u  const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type3u const&>(this -> value) .operator ()<void*>(*static_cast<unsigned char*>(address), size + (alignment - 1u)) : reinterpret_cast<type3u  const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size + (alignment - 1u));
    //         case 4u : return *(reinterpret_cast<type4u  const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type4u const&>(this -> value) .operator ()<void*>(*static_cast<unsigned char*>(address), size, alignment)         : reinterpret_cast<type4u  const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size, alignment);
    //         case 5u : return                                                                                                                                                                                                                                                                                reinterpret_cast<type5u  const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size + (alignment - 1u));
    //         case 6u : return                                                                                                                                                                                                                                                                                reinterpret_cast<type6u  const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size, alignment);
    //         case 7u : return *(reinterpret_cast<type7u  const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type7u const&>(this -> value) .operator ()<void*>(*static_cast<char*>         (address), size + (alignment - 1u)) : reinterpret_cast<type7u  const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size + (alignment - 1u));
    //         case 8u : return *(reinterpret_cast<type8u  const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type8u const&>(this -> value) .operator ()<void*>(*static_cast<char*>         (address), size, alignment)         : reinterpret_cast<type8u  const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size, alignment);
    //         case 9u : return *(reinterpret_cast<type9u  const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type9u const&>(this -> value) .operator ()<void*>(*static_cast<unsigned char*>(address), size + (alignment - 1u)) : reinterpret_cast<type9u  const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size + (alignment - 1u));
    //         case 10u: return *(reinterpret_cast<type10u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type10u const&>(this -> value).operator ()<void*>(*static_cast<unsigned char*>(address), size, alignment)         : reinterpret_cast<type10u const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size, alignment);
    //         case 11u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type11u const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size + (alignment - 1u));
    //         case 12u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type12u const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size, alignment);
    //         case 13u: return *(reinterpret_cast<type13u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type13u const&>(this -> value).operator ()<void*>(*static_cast<char*>         (address), size + (alignment - 1u)) : reinterpret_cast<type13u const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size + (alignment - 1u));
    //         case 14u: return *(reinterpret_cast<type14u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type14u const&>(this -> value).operator ()<void*>(*static_cast<char*>         (address), size, alignment)         : reinterpret_cast<type14u const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size, alignment);
    //         case 15u: return *(reinterpret_cast<type15u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type15u const&>(this -> value).operator ()<void*>(*static_cast<unsigned char*>(address), size + (alignment - 1u)) : reinterpret_cast<type15u const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size + (alignment - 1u));
    //         case 16u: return *(reinterpret_cast<type16u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type16u const&>(this -> value).operator ()<void*>(*static_cast<unsigned char*>(address), size, alignment)         : reinterpret_cast<type16u const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size, alignment);
    //         case 17u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type17u const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size + (alignment - 1u));
    //         case 18u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type18u const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size, alignment);
    //         #ifdef __cpp_lib_byte // --> 201603L
    //           case 19u: return *(reinterpret_cast<type19u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type19u const&>(this -> value).operator ()<void*>(*static_cast<std::byte*>    (address), size + (alignment - 1u)) : reinterpret_cast<type19u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size + (alignment - 1u));
    //           case 20u: return *(reinterpret_cast<type20u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type20u const&>(this -> value).operator ()<void*>(*static_cast<std::byte*>    (address), size, alignment)         : reinterpret_cast<type20u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size, alignment);
    //           case 21u: return *(reinterpret_cast<type21u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type21u const&>(this -> value).operator ()<void*>(*static_cast<std::byte*>    (address), size + (alignment - 1u)) : reinterpret_cast<type21u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size + (alignment - 1u));
    //           case 22u: return *(reinterpret_cast<type22u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type22u const&>(this -> value).operator ()<void*>(*static_cast<std::byte*>    (address), size, alignment)         : reinterpret_cast<type22u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size, alignment);
    //           case 23u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type23u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size + (alignment - 1u));
    //           case 24u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type24u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size, alignment);
    //           case 25u: return *(reinterpret_cast<type25u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type25u const&>(this -> value).operator ()<void*>(*static_cast<char*>         (address), size + (alignment - 1u)) : reinterpret_cast<type25u const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size + (alignment - 1u));
    //           case 26u: return *(reinterpret_cast<type26u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type26u const&>(this -> value).operator ()<void*>(*static_cast<char*>         (address), size, alignment)         : reinterpret_cast<type26u const&>(this -> value).operator()<void*>(static_cast<char*>         (address), size, alignment);
    //           case 27u: return *(reinterpret_cast<type27u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type27u const&>(this -> value).operator ()<void*>(*static_cast<unsigned char*>(address), size + (alignment - 1u)) : reinterpret_cast<type27u const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size + (alignment - 1u));
    //           case 28u: return *(reinterpret_cast<type28u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type28u const&>(this -> value).operator ()<void*>(*static_cast<unsigned char*>(address), size, alignment)         : reinterpret_cast<type28u const&>(this -> value).operator()<void*>(static_cast<unsigned char*>(address), size, alignment);
    //           case 29u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type29u const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size + (alignment - 1u));
    //           case 30u: return                                                                                                                                                                                                                                                                                reinterpret_cast<type30u const&>(this -> value).operator()<void*>(static_cast<void*>         (address), size, alignment);
    //           case 31u: return *(reinterpret_cast<type31u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type31u const&>(this -> value).operator ()<void*>(*static_cast<std::byte*>    (address), size + (alignment - 1u)) : reinterpret_cast<type31u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size + (alignment - 1u));
    //           case 32u: return *(reinterpret_cast<type32u const&>(this -> value).qualifiers) & (MemoryAllocator::ARRAY_BASED | MemoryAllocator::TEMPORARY_ARRAY_BASED) ? reinterpret_cast<type32u const&>(this -> value).operator ()<void*>(*static_cast<std::byte*>    (address), size, alignment)         : reinterpret_cast<type32u const&>(this -> value).operator()<void*>(static_cast<std::byte*>    (address), size, alignment);
    //         #endif
    //       }

    //       return NULL;
    //     }
    // } reallocator;

  public:
    inline MemoryAllocator() /* noexcept */ :
      pool            (),
      pools           (NULL),
      poolsCapacity   (0u),
      poolsLength     (0u),
      buffer          (NULL),
      bufferCapacity  (0u),
      bufferExtendable(false),
      baseReserveSize (Memory::getAllocatorGranularity()),
      allocator       (),
      deallocator     (),
      reallocator     ()
    {}


    template <typename type, std::size_t capacity>
    /* constexpr */ inline MemoryAllocator(type (&buffer)[capacity], Memory::ControlParameter const parameter = Memory::AUTOMATIC) /* noexcept */ :
      pool            (),
      pools           (NULL),
      poolsCapacity   (0u),
      poolsLength     (0u),
      buffer          (buffer_cast<unsigned char*>(buffer)),
      bufferCapacity  (capacity),
      bufferExtendable(parameter & Memory::EXTENDED),
      baseReserveSize (this -> bufferExtendable ? Memory::getAllocatorGranularity() : 0u),
      allocator       (),
      deallocator     (),
      reallocator     ()
    {}

    template <typename type>
    /* constexpr */ inline MemoryAllocator(type* const buffer, std::size_t const capacity, Memory::ControlParameter const parameter = Memory::AUTOMATIC) /* noexcept */ :
      pool            (),
      pools           (NULL),
      poolsCapacity   (0u),
      poolsLength     (0u),
      buffer          (0u != capacity ? static_cast<unsigned char*>(buffer_cast<unsigned char*>(buffer)) : NULL),
      bufferCapacity  (capacity),
      bufferExtendable(parameter & Memory::EXTENDED),
      baseReserveSize (this -> bufferExtendable ? Memory::getAllocatorGranularity() : 0u),
      allocator       (),
      deallocator     (),
      reallocator     ()
    {}

    template <typename allocatorType, typename deallocatorType>
    inline MemoryAllocator(allocatorType& allocator, deallocatorType& deallocator) /* noexcept */ :
      pool            (),
      pools           (NULL),
      poolsCapacity   (0u),
      poolsLength     (0u),
      buffer          (NULL),
      bufferCapacity  (0u),
      bufferExtendable(false),
      baseReserveSize (0u),
      allocator       (allocator),
      deallocator     (deallocator),
      reallocator     ()
    {}

    template <typename allocatorType, typename deallocatorType, typename reallocatorType>
    inline MemoryAllocator(allocatorType& allocator, deallocatorType& deallocator, reallocatorType& reallocator) /* noexcept */ :
      pool            (),
      pools           (NULL),
      poolsCapacity   (0u),
      poolsLength     (0u),
      buffer          (NULL),
      bufferCapacity  (0u),
      bufferExtendable(false),
      baseReserveSize (0u),
      allocator       (allocator),
      deallocator     (deallocator),
      reallocator     (reallocator)
    {}

    /* ... */
    /* constexpr */ inline MemoryBuffer<> (allocate)(std::size_t const size, std::size_t const alignment, Memory::ControlParameter const parameter) /* noexcept */ {
      MemoryBuffer<> allocation = {NULL, 0u};

      // ...
      for (std::size_t assertion = 1u; assertion != alignment; assertion *= 2u)
      if (alignment < assertion) return allocation;

      if ((parameter & Memory::STACK) || (0u == size))
      return allocation;

      std::puts("bruh");
      allocation.value = this -> allocator(size, alignment);

      // // ...
      // if (AllocatorFunction::null != this -> allocator)
      //   return this -> allocator(size, alignment);
      // Memory::CLEAR;
      // Memory::EXECUTABLE;

      // #if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
      //   ::mmap(...);
      // #elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
      //   ::VirtualAllocEx(...);
      // #endif
      // Memory::getAllocatorGranularity()
      // 1  allocation(s) => 4096  bytes overall [2 ** 1] + [2 ** 12] == [2 ** 13]
      // 13 allocation(s) => 8192  bytes overall
      // 26 allocation(s) => 16384 bytes overall
      // static_cast<void>(size);
      // static_cast<void>(this -> allocator), static_cast<void>(this -> deallocator), static_cast<void>(this -> reallocator);
      // static_cast<void>(this -> buffer); static_cast<void>(this -> bufferCapacity, this -> bufferExtendable);
      // static_cast<void>(this -> pool, this -> pools), static_cast<void>(this -> poolsCapacity, this -> poolsLength), static_cast<void>(Memory::baseReserveSize); // bucket

      // ...
      return allocation;
    }

    /* constexpr */ inline MemoryBuffer<> (allocate)(std::size_t const size, std::size_t const alignment = /* --> alignof(unsigned char) */ sizeof(unsigned char)) /* noexcept */ {
      return (this -> MemoryAllocator::allocate)(size, alignment, Memory::AUTOMATIC);
    }

    // ...
    /* constexpr */ inline bool (deallocate)(void const volatile* const) /* noexcept */ {
      return false;
    }

    // ...
    template <typename type>
    type (instantiate)() /* noexcept */;

    template <typename type>
    type (instantiate)(type const&) /* noexcept */;

    // ...
    /* constexpr */ inline MemoryBuffer<> (reallocate)(void const volatile* const, std::size_t const, std::size_t const, Memory::ControlParameter const) /* noexcept */ {
      /* constexpr */ MemoryBuffer<> const null = {NULL, 0u};

      static_cast<void>(Memory::DYNAMIC);
      return null;
    }

    /* constexpr */ inline MemoryBuffer<> (reallocate)(void const volatile* const address, std::size_t const size, std::size_t const alignment) /* noexcept */ {
      return (Memory::reallocate)(address, size, alignment, Memory::AUTOMATIC);
    }
};
  #if __cplusplus >= 201103L && defined(__cpp_threadsafe_static_init) // --> 200806L
    thread_local
  #endif
  MemoryAllocator Memory::allocator = MemoryAllocator();

  /* ... */
  /* constexpr */ inline MemoryBuffer<> (Memory::allocate)(std::size_t const size, std::size_t const alignment, Memory::ControlParameter const parameter) /* noexcept */ {
    return (Memory::allocator.allocate)(size, alignment, parameter);
  }

  /* constexpr */ inline MemoryBuffer<> (Memory::reallocate)(void const volatile* const address, std::size_t const size, std::size_t const alignment, Memory::ControlParameter const parameter) /* noexcept */ {
    return (Memory::allocator.reallocate)(address, size, alignment, parameter);
  }

  /* constexpr */ inline bool (Memory::deallocate)(void const volatile* const address) /* noexcept */ {
    return (Memory::allocator.deallocate)(address);
  }

/* Main */
#include <csignal>
#include <cstdlib>

void* alloc(std::size_t) { std::puts("[allocate]"); return NULL; }
bool dealloc(void*) { std::puts("[deallocate]"); return true; }

int main(int, char*[]) /* noexcept */ {
  struct RIP { static void dead(int const) { std::puts("\r\n" "SEGFAULT"); std::exit(EXIT_SUCCESS); } };
  std::signal(SIGSEGV, &RIP::dead);
  (MemoryAllocator(alloc, dealloc).allocate)(69u);
// del allocator.exe && cls && clang++ -pedantic-errors -std=c++98 -Wall -Werror -Wextra -Wno-unused-private-field -Wno-variadic-macros allocator.cpp -o allocator.exe && allocator.exe & del allocator.exe
// del allocator.exe && cls && g++ -pedantic-errors -std=c++98 -Wall -Werror -Wextra -Wno-variadic-macros allocator.cpp -o allocator.exe && allocator.exe & del allocator.exe
  // Memory::allocate(1u, 2u);                    // Memory::                applyControlParameter()                  ->* Memory::allocate(1u, 2u);
  // Memory::allocate(1u, 2u, );                  // Memory::                applyControlParameter()                  ->* Memory::allocate(1u, 2u);
  // Memory::allocate(1u, 2u, A);                 // Memory::                applyControlParameter(A)                 ->* Memory::allocate(1u, 2u);
  // Memory::allocate(1u, 2u, B | STACK);         // Memory::                applyControlParameter(B | STACK)         ->* Memory::allocate(1u, 2u);
  // Memory::allocate(1u, 2u, B | Memory::STACK); // Memory::                applyControlParameter(B | Memory::STACK) ->* Memory::allocate(1u, 2u);
  // Memory::allocate(1u, 2u, STACK);             // Memory::                applyControlParameter(STACK)             ->* ::_alloca(static_cast<std::size_t>(1u) + (static_cast<std::size_t>(2u) - 1u));
  // Memory::allocate(1u, 2u, Memory::STACK);     // Memory::template _<85>::applyControlParameter(Memory::STACK)     ->* ::_alloca(static_cast<std::size_t>(1u) + (static_cast<std::size_t>(2u) - 1u));
  // Memory::allocate(1u, 2u, STACK         | B); // Memory::allocate_stack        | B(STACK         | B)(1u, 2u);
  // Memory::allocate(1u, 2u, Memory::STACK | B); // Memory::template _<87>::STACK | B(Memory::STACK | B)(1u, 2u);
}
