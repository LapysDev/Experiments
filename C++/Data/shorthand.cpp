/* ... */
// #include <cstdio>
// #include <cstdlib>
// #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
// # include <windows.h>
// #   include <memoryapi.h>
// #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux)
// # include <sys/mman.h>
// #endif

// /* Main */
// int main(int, char*[]) /* noexcept */ {
//   #if false == (defined(__amd64) || defined(__amd64__) || defined(__i386) || defined(__i386__) || defined(__i386__) || defined(__i486__) || defined(__i486__) || defined(__i586__) || defined(__i586__) || defined(__i686__) || defined(__i686__) || defined(__I86__) || defined(__I86__) || defined(__INTEL__) || defined(__THW_INTEL__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_IX86) || defined(_M_X64) || defined(_X86_) || defined(i386))
//   # error no code for environment architecture
//   #endif
//   class Function /* final */ {
//     public:
//       typedef void* (*type)() /* noexcept */;

//       static void* uninitialized() /* noexcept */ { return NULL; }
//       static void* unreleased   () /* noexcept */ { return NULL; }

//       void* (*value)() /* noexcept */;

//     public:
//       Function(void* const data = NULL) /* noexcept */ : value(Function::uninitialized) {
//         if (Function::unreleased == this -> value) return;
//         #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
//           LPVOID const allocation = ::VirtualAlloc(NULL, 13u, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
//         #elif defined(__APPLE__) ||  defined(__bsdi__) ||  defined(__CYGWIN__) ||  defined(__DragonFly__) ||  defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) ||  defined(__FreeBSD__) ||  defined(__FreeBSD_version) ||  defined(__gnu_linux__) ||  defined(__linux) ||  defined(__linux__) ||  defined(__MACH__) ||  defined(__NETBSD__) ||  defined(__NETBSD_version) ||  defined(__OpenBSD__) ||  defined(__OS400__) ||  defined(__QNX__) ||  defined(__QNXNTO__) ||  defined(__sun) ||  defined(__SVR4) ||  defined(__svr4__) ||  defined(__sysv__) ||  defined(__unix) ||  defined(__unix__) ||  defined(__VMS) ||  defined(__VMS_VER) ||  defined(_NTO_VERSION) ||  defined(_POSIX_SOURCE) ||  defined(_SYSTYPE_SVR4) ||  defined(_XOPEN_SOURCE) ||  defined(linux) ||  defined(NetBSD0_8) ||  defined(NetBSD0_9) ||  defined(NetBSD1_0) ||  defined(OpenBSD2_0) ||  defined(OpenBSD2_1) ||  defined(OpenBSD2_2) ||  defined(OpenBSD2_3) ||  defined(OpenBSD2_4) ||  defined(OpenBSD2_5) ||  defined(OpenBSD2_6) ||  defined(OpenBSD2_7) ||  defined(OpenBSD2_8) ||  defined(OpenBSD2_9) ||  defined(OpenBSD3_0) ||  defined(OpenBSD3_1) ||  defined(OpenBSD3_2) ||  defined(OpenBSD3_3) ||  defined(OpenBSD3_4) ||  defined(OpenBSD3_5) ||  defined(OpenBSD3_6) ||  defined(OpenBSD3_7) ||  defined(OpenBSD3_8) ||  defined(OpenBSD3_9) ||  defined(OpenBSD4_0) ||  defined(OpenBSD4_1) ||  defined(OpenBSD4_2) ||  defined(OpenBSD4_3) ||  defined(OpenBSD4_4) ||  defined(OpenBSD4_5) ||  defined(OpenBSD4_6) ||  defined(OpenBSD4_7) ||  defined(OpenBSD4_8) ||  defined(OpenBSD4_9) ||  defined(sun) ||  defined(unix) || defined(VMS)
//           void *allocation = ::mmap(NULL, 13u, PROT_EXEC | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0L);
//           if (MAP_FAILED == allocation) allocation = NULL;
//         #else
//           void *const allocation = NULL;
//         #endif

//         for (unsigned char
//           *allocationIterator = reinterpret_cast<unsigned char*>(&allocation)      + sizeof(void*),
//           *valueIterator      = reinterpret_cast<unsigned char*>(&(this -> value)) + sizeof(void*)
//         ; allocationIterator != reinterpret_cast<unsigned char*>(&allocation); ) *--valueIterator = *--allocationIterator;

//         if (NULL == allocation) return;
//         reinterpret_cast<unsigned char*>(this -> value) [0] = 0x55u; // --> push rbp
//         reinterpret_cast<unsigned char*>(this -> value) [1] = 0x48u; // --> mov  rbp, rsp
//         reinterpret_cast<unsigned char*>(this -> value) [2] = 0x89u; //
//         reinterpret_cast<unsigned char*>(this -> value) [3] = 0xE5u; //
//         reinterpret_cast<unsigned char*>(this -> value) [4] = 0x48u; // --> mov rax
//         reinterpret_cast<unsigned char*>(this -> value) [5] = 0xC7u; //
//         reinterpret_cast<unsigned char*>(this -> value) [6] = 0xC0u; //
//         reinterpret_cast<unsigned char*>(this -> value)[11] = 0x5Du; // --> pop rbp
//         reinterpret_cast<unsigned char*>(this -> value)[12] = 0xC3u; // --> ret

//         this -> set(data);
//       }

//       ~Function() /* noexcept */ {
//         if (NULL == reinterpret_cast<void*>(this -> value)) return;
//         this -> value =
//           #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
//             FALSE == ::VirtualFree(reinterpret_cast<LPVOID>(this -> value), 13u, MEM_RELEASE)
//           #elif defined(__APPLE__) ||  defined(__bsdi__) ||  defined(__CYGWIN__) ||  defined(__DragonFly__) ||  defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) ||  defined(__FreeBSD__) ||  defined(__FreeBSD_version) ||  defined(__gnu_linux__) ||  defined(__linux) ||  defined(__linux__) ||  defined(__MACH__) ||  defined(__NETBSD__) ||  defined(__NETBSD_version) ||  defined(__OpenBSD__) ||  defined(__OS400__) ||  defined(__QNX__) ||  defined(__QNXNTO__) ||  defined(__sun) ||  defined(__SVR4) ||  defined(__svr4__) ||  defined(__sysv__) ||  defined(__unix) ||  defined(__unix__) ||  defined(__VMS) ||  defined(__VMS_VER) ||  defined(_NTO_VERSION) ||  defined(_POSIX_SOURCE) ||  defined(_SYSTYPE_SVR4) ||  defined(_XOPEN_SOURCE) ||  defined(linux) ||  defined(NetBSD0_8) ||  defined(NetBSD0_9) ||  defined(NetBSD1_0) ||  defined(OpenBSD2_0) ||  defined(OpenBSD2_1) ||  defined(OpenBSD2_2) ||  defined(OpenBSD2_3) ||  defined(OpenBSD2_4) ||  defined(OpenBSD2_5) ||  defined(OpenBSD2_6) ||  defined(OpenBSD2_7) ||  defined(OpenBSD2_8) ||  defined(OpenBSD2_9) ||  defined(OpenBSD3_0) ||  defined(OpenBSD3_1) ||  defined(OpenBSD3_2) ||  defined(OpenBSD3_3) ||  defined(OpenBSD3_4) ||  defined(OpenBSD3_5) ||  defined(OpenBSD3_6) ||  defined(OpenBSD3_7) ||  defined(OpenBSD3_8) ||  defined(OpenBSD3_9) ||  defined(OpenBSD4_0) ||  defined(OpenBSD4_1) ||  defined(OpenBSD4_2) ||  defined(OpenBSD4_3) ||  defined(OpenBSD4_4) ||  defined(OpenBSD4_5) ||  defined(OpenBSD4_6) ||  defined(OpenBSD4_7) ||  defined(OpenBSD4_8) ||  defined(OpenBSD4_9) ||  defined(sun) ||  defined(unix) || defined(VMS)
//             ::munmap(reinterpret_cast<void*>(this -> value), 13u) == -1
//           #endif
//         ? Function::unreleased : Function::uninitialized;
//       }

//       /* ... */
//       bool set(void* const data) /* noexcept */ {
//         if (Function::uninitialized == this -> value || NULL == reinterpret_cast<void*>(this -> value))
//         return false;

//         reinterpret_cast<unsigned char*>(this -> value) [7] = reinterpret_cast<unsigned char const*>(&data)[0];
//         reinterpret_cast<unsigned char*>(this -> value) [8] = reinterpret_cast<unsigned char const*>(&data)[1];
//         reinterpret_cast<unsigned char*>(this -> value) [9] = reinterpret_cast<unsigned char const*>(&data)[2];
//         reinterpret_cast<unsigned char*>(this -> value)[10] = reinterpret_cast<unsigned char const*>(&data)[3];

//         return true;
//       }

//       operator type() const /* noexcept */ {
//         return this -> value;
//       }
//   } function = Function();

//   // ...
//   function.set(NULL);
//   std::printf("%p", function());

//   return EXIT_SUCCESS;
// }

/*
  --- CITE ---
    #Lapys:
      Circle               : https://lapys.godbolt.org/z/q49899jdx
      Clang, GCC, ICC, MSVC: https://lapys.godbolt.org/z/38b1evxGP
*/
#include <atomic>
#include <climits>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <new>
#include <ratio>
#include <stdexcept>
#include <stdint.h>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <version>
#ifdef __cpp_lib_endian
# include <bit>
#endif
#ifdef __cpp_lib_three_way_comparison
# include <compare>
# ifdef __cpp_lib_coroutine
#   include <coroutine>
# endif
#endif
#ifdef __cpp_lib_ranges
# include <ranges>
#endif
#ifdef __cpp_lib_source_location
# include <source_location>
#endif

/* ... ->> Functor expression, coerce-able to a free function */
struct $shorthand {
  private:
    template <$operation_id, typename = void, typename... bases>
    struct operate final {
      static bool const value = false;

      /* ... */
      template <typename type>
      inline static type valueof(bases&&...) noexcept {
        return static_cast<type>(std::declval<type>());
      }
    };

    template <typename base, typename... bases>
    struct operate<$shorthand::$call, decltype(static_cast<void>(std::declval<base>()(std::declval<bases>()...))), base, bases...> final {
      static bool const value = true;

      template <typename>
      constexpr static decltype(std::declval<base>()(std::declval<bases>()...)) valueof(base&& operand, bases&&... operands) noexcept(noexcept(std::declval<base>()(std::declval<bases>()...))) {
        return std::forward<base>(operand)(std::forward<bases>(operands)...);
      }
    };

    template <typename baseA, typename baseB, typename baseC>
    struct operate<$shorthand::$ternary, decltype(static_cast<void>(std::declval<baseA>() ? std::declval<baseB>() : std::declval<baseC>())), baseA, baseB, baseC> final {
      static bool const value = true;

      template <typename>
      constexpr static decltype(std::declval<baseA>() ? std::declval<baseB>() : std::declval<baseC>()) valueof(baseA&& operandA, baseB&& operandB, baseC&& operandC) noexcept(noexcept(std::declval<baseA>() ? std::declval<baseB>() : std::declval<baseC>())) {
        return std::forward<baseA>(operandA) ? std::forward<baseB>(operandB) : std::forward<baseC>(operandC);
      }
    };

    template <typename baseA, typename baseB> struct operate<$shorthand::$add,                   decltype(static_cast<void>(std::declval<baseA>()   + std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   + std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   + std::declval<baseB>())) { return (std::forward<baseA>(operandA)   + std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign,                decltype(static_cast<void>(std::declval<baseA>()   = std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   = std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   = std::declval<baseB>())) { return (std::forward<baseA>(operandA)   = std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_add,            decltype(static_cast<void>(std::declval<baseA>()  += std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  += std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  += std::declval<baseB>())) { return (std::forward<baseA>(operandA)  += std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_bitwise_and,    decltype(static_cast<void>(std::declval<baseA>()  &= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  &= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  &= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  &= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_bitwise_or,     decltype(static_cast<void>(std::declval<baseA>()  |= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  |= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  |= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  |= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_bitwise_xor,    decltype(static_cast<void>(std::declval<baseA>()  ^= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  ^= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  ^= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  ^= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_divide,         decltype(static_cast<void>(std::declval<baseA>()  /= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  /= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  /= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  /= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_left_shift,     decltype(static_cast<void>(std::declval<baseA>() <<= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>() <<= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>() <<= std::declval<baseB>())) { return (std::forward<baseA>(operandA) <<= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_modulo,         decltype(static_cast<void>(std::declval<baseA>()  %= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  %= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  %= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  %= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_multiply,       decltype(static_cast<void>(std::declval<baseA>()  *= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  *= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  *= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  *= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_right_shift,    decltype(static_cast<void>(std::declval<baseA>() >>= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>() >>= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>() >>= std::declval<baseB>())) { return (std::forward<baseA>(operandA) >>= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$assign_subtract,       decltype(static_cast<void>(std::declval<baseA>()  -= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  -= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  -= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  -= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$bitwise_and,           decltype(static_cast<void>(std::declval<baseA>()   & std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   & std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   & std::declval<baseB>())) { return (std::forward<baseA>(operandA)   & std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$bitwise_or,            decltype(static_cast<void>(std::declval<baseA>()   | std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   | std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   | std::declval<baseB>())) { return (std::forward<baseA>(operandA)   | std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$bitwise_xor,           decltype(static_cast<void>(std::declval<baseA>()   ^ std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   ^ std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   ^ std::declval<baseB>())) { return (std::forward<baseA>(operandA)   ^ std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$boolean_and,           decltype(static_cast<void>(std::declval<baseA>()  && std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  && std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  && std::declval<baseB>())) { return (std::forward<baseA>(operandA)  && std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$boolean_or,            decltype(static_cast<void>(std::declval<baseA>()  || std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  || std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  || std::declval<baseB>())) { return (std::forward<baseA>(operandA)  || std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$cast,                  decltype(static_cast<void>((baseB) std::declval<baseA>())),                   baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((baseB) std::declval<baseA>())                     valueof(baseA&& operand)                    noexcept(noexcept((baseB) std::declval<baseA>()))                   { return (baseB) std::forward<baseA>(operand);                              } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$comma,                 decltype(static_cast<void>(std::declval<baseA>()   , std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   , std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   , std::declval<baseB>())) { return (std::forward<baseA>(operandA)   , std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$divide,                decltype(static_cast<void>(std::declval<baseA>()   / std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   / std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   / std::declval<baseB>())) { return (std::forward<baseA>(operandA)   / std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$equals,                decltype(static_cast<void>(std::declval<baseA>()  == std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  == std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  == std::declval<baseB>())) { return (std::forward<baseA>(operandA)  == std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$equals_greater,        decltype(static_cast<void>(std::declval<baseA>()  >= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  >= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  >= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  >= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$equals_lesser,         decltype(static_cast<void>(std::declval<baseA>()  <= std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  <= std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  <= std::declval<baseB>())) { return (std::forward<baseA>(operandA)  <= std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$greater,               decltype(static_cast<void>(std::declval<baseA>()   > std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   > std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   > std::declval<baseB>())) { return (std::forward<baseA>(operandA)   > std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$left_shift,            decltype(static_cast<void>(std::declval<baseA>()  << std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  << std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  << std::declval<baseB>())) { return (std::forward<baseA>(operandA)  << std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$lesser,                decltype(static_cast<void>(std::declval<baseA>()   < std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   < std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   < std::declval<baseB>())) { return (std::forward<baseA>(operandA)   < std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$member_pointer_access, decltype(static_cast<void>(std::declval<baseA>() ->* std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>() ->* std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>() ->* std::declval<baseB>())) { return (std::forward<baseA>(operandA) ->* std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$modulo,                decltype(static_cast<void>(std::declval<baseA>()   % std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   % std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   % std::declval<baseB>())) { return (std::forward<baseA>(operandA)   % std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$multiply,              decltype(static_cast<void>(std::declval<baseA>()   * std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   * std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   * std::declval<baseB>())) { return (std::forward<baseA>(operandA)   * std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$right_shift,           decltype(static_cast<void>(std::declval<baseA>()  >> std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  >> std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  >> std::declval<baseB>())) { return (std::forward<baseA>(operandA)  >> std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$subscript,             decltype(static_cast<void>(std::declval<baseA>()[std::declval<baseB>()])),    baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()[std::declval<baseB>()]))    valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()[std::declval<baseB>()]))    { return (std::forward<baseA>(operandA)[std::forward<baseB>(operandB)]);    } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$subtract,              decltype(static_cast<void>(std::declval<baseA>()   - std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()   - std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()   - std::declval<baseB>())) { return (std::forward<baseA>(operandA)   - std::forward<baseB>(operandB)); } };
    template <typename baseA, typename baseB> struct operate<$shorthand::$unequal,               decltype(static_cast<void>(std::declval<baseA>()  != std::declval<baseB>())), baseA, baseB> final { static bool const value = true; template <typename> constexpr static decltype((std::declval<baseA>()  != std::declval<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>()  != std::declval<baseB>())) { return (std::forward<baseA>(operandA)  != std::forward<baseB>(operandB)); } };
    #ifdef __cpp_impl_three_way_comparison
      template <typename baseA, typename baseB>
      struct operate<$shorthand::$compare, decltype(static_cast<void>(std::declval<baseA>() <=> std::declval<baseB>())), baseA, baseB> final {
        static bool const value = true;

        template <typename>
        constexpr static decltype(std::declval<baseA>() <=> std::declval<baseB>()) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(std::declval<baseA>() <=> std::declval<baseB>())) {
          return (std::forward<baseA>(operandA) <=> std::forward<baseB>(operandB));
        }
      };
    #endif

    template <typename base> struct operate<$shorthand::$address,        decltype(static_cast<void>(&const_cast<typename std::remove_reference<base>::type&>(static_cast<typename std::remove_reference<base>::type const&>(std::declval<base>())))), base> final { static bool const value = true; template <typename> constexpr static decltype(&const_cast<typename std::remove_reference<base>::type&>(static_cast<typename std::remove_reference<base>::type const&>(std::declval<base>()))) valueof(base&& operand) noexcept(noexcept(&const_cast<typename std::remove_reference<base>::type&>(static_cast<typename std::remove_reference<base>::type const&>(std::declval<base>())))) { return &const_cast<typename std::remove_reference<base>::type&>(static_cast<typename std::remove_reference<base>::type const&>(std::forward<base>(operand))); } };
    template <typename base> struct operate<$shorthand::$complement,     decltype(static_cast<void>(~std::declval<base>())),                                                                                                                          base> final { static bool const value = true; template <typename> constexpr static decltype(~std::declval<base>())                                                                                                                          valueof(base&& operand) noexcept(noexcept(~std::declval<base>()))                                                                                                                          { return ~std::forward<base>(operand);                                                                                                                          } };
    template <typename base> struct operate<$shorthand::$dereference,    decltype(static_cast<void>(*std::declval<base>())),                                                                                                                          base> final { static bool const value = true; template <typename> constexpr static decltype(*std::declval<base>())                                                                                                                          valueof(base&& operand) noexcept(noexcept(*std::declval<base>()))                                                                                                                          { return *std::forward<base>(operand);                                                                                                                          } };
    template <typename base> struct operate<$shorthand::$member_access,  decltype(static_cast<void>(std::declval<base>().operator ->())),                                                                                                             base> final { static bool const value = true; template <typename> constexpr static decltype(std::declval<base>().operator ->())                                                                                                             valueof(base&& operand) noexcept(noexcept(std::declval<base>().operator ->()))                                                                                                             { return std::forward<base>(operand).operator ->();                                                                                                             } };
    template <typename base> struct operate<$shorthand::$minus,          decltype(static_cast<void>(-std::declval<base>())),                                                                                                                          base> final { static bool const value = true; template <typename> constexpr static decltype(-std::declval<base>())                                                                                                                          valueof(base&& operand) noexcept(noexcept(-std::declval<base>()))                                                                                                                          { return -std::forward<base>(operand);                                                                                                                          } };
    template <typename base> struct operate<$shorthand::$negate,         decltype(static_cast<void>(!std::declval<base>())),                                                                                                                          base> final { static bool const value = true; template <typename> constexpr static decltype(!std::declval<base>())                                                                                                                          valueof(base&& operand) noexcept(noexcept(!std::declval<base>()))                                                                                                                          { return !std::forward<base>(operand);                                                                                                                          } };
    template <typename base> struct operate<$shorthand::$plus,           decltype(static_cast<void>(+std::declval<base>())),                                                                                                                          base> final { static bool const value = true; template <typename> constexpr static decltype(+std::declval<base>())                                                                                                                          valueof(base&& operand) noexcept(noexcept(+std::declval<base>()))                                                                                                                          { return +std::forward<base>(operand);                                                                                                                          } };
    template <typename base> struct operate<$shorthand::$post_decrement, decltype(static_cast<void>(std::declval<base>()--)),                                                                                                                         base> final { static bool const value = true; template <typename> constexpr static decltype(std::declval<base>()--)                                                                                                                         valueof(base&& operand) noexcept(noexcept(std::declval<base>()--))                                                                                                                         { return std::forward<base>(operand)--;                                                                                                                         } };
    template <typename base> struct operate<$shorthand::$post_increment, decltype(static_cast<void>(std::declval<base>()++)),                                                                                                                         base> final { static bool const value = true; template <typename> constexpr static decltype(std::declval<base>()++)                                                                                                                         valueof(base&& operand) noexcept(noexcept(std::declval<base>()++))                                                                                                                         { return std::forward<base>(operand)++;                                                                                                                         } };
    template <typename base> struct operate<$shorthand::$pre_decrement,  decltype(static_cast<void>(--std::declval<base>())),                                                                                                                         base> final { static bool const value = true; template <typename> constexpr static decltype(--std::declval<base>())                                                                                                                         valueof(base&& operand) noexcept(noexcept(--std::declval<base>()))                                                                                                                         { return --std::forward<base>(operand);                                                                                                                         } };
    template <typename base> struct operate<$shorthand::$pre_increment,  decltype(static_cast<void>(++std::declval<base>())),                                                                                                                         base> final { static bool const value = true; template <typename> constexpr static decltype(++std::declval<base>())                                                                                                                         valueof(base&& operand) noexcept(noexcept(++std::declval<base>()))                                                                                                                         { return ++std::forward<base>(operand);                                                                                                                         } };
    template <typename base> struct operate<$shorthand::$self,           void,                                                                                                                                                                        base> final { static bool const value = true; template <typename> constexpr static decltype(std::declval<base>())                                                                                                                           valueof(base&& operand) noexcept                                                                                                                                                           { return std::forward<base>(operand);                                                                                                                           } };

    // ...
    struct operation_arity final {
      enum type : unsigned char {
        niladic  = 0u,
        monoadic = 1u,
        diadic   = 2u,
        triadic  = 3u,
        variadic = static_cast<unsigned char>(-1)
      };
    };

    // ... ->> Flags denoting overload-able C++ operators; used as type-agnostic `$shorthand::operation`, which is un-preferably type-erased
    struct operation_identity final {
      enum type : unsigned char {
        $add,
        $address,
        $assign,
        $assign_add,
        $assign_bitwise_and,
        $assign_bitwise_or,
        $assign_bitwise_xor,
        $assign_divide,
        $assign_left_shift,
        $assign_modulo,
        $assign_multiply,
        $assign_right_shift,
        $assign_subtract,
        $bitwise_and,
        $bitwise_or,
        $bitwise_xor,
        $boolean_and,
        $boolean_or,
        $call,
        $cast,
        $comma,
        $compare,
        $complement,
        $dereference,
        $divide,
        $equals,
        $equals_greater,
        $equals_lesser,
        $greater,
        $left_shift,
        $lesser,
        $member_access,
        $member_pointer_access,
        $minus,
        $modulo,
        $multiply,
        $negate,
        $plus,
        $post_decrement,
        $post_increment,
        $pre_decrement,
        $pre_increment,
        $right_shift,
        $self,
        $subscript,
        $subtract,
        $ternary,
        $unequal
      };
    };

    // ... ->> Type-agnostic operation
    struct operation_value final {};

  public:
    typedef $shorthand::operation_value evaluation;
    typedef $shorthand::operation_value operand;

    // ... ->> Type-erased function without generic or template template function parameters available ie: `auto (*)(auto&&...)`
    typedef $shorthand::evaluation (*operation)($shorthand::operand const (&&)[]);

  private:
    typedef $shorthand::evaluation (*$void)($shorthand::operand const (&&)[]); // ->> Disambiguation trait type; used for SFINAE/ specializations

    /* ... */
    constexpr static $shorthand::evaluation (*$voidop)($shorthand::operand const (&&)[]) noexcept = nullptr;

    template <$shorthand::operation_identity::type identity, unsigned char arity>
    constexpr static $shorthand::evaluation $op($shorthand::operand const (&&)[]) noexcept(false) /* --> throw(std::runtime_error) */ {}
};

/* === */
/* ... ->> functor expression; coerce-able to free function types eg: `T (*)(...)` */
struct $shorthand {
  private:
    template <$shorthand::$operation_id, unsigned char, bool, unsigned char...>
    friend $evaluation& $op($operand const (&&)[], $evaluation&) noexcept(false) /* --> throw(std::runtime_error) */;
};

// ... ->> information on `$expression` operands which get passed to an `$operation`
struct $operand {
  friend struct $evaluation;
  template <$operation, class...> friend struct $expression;

  // ...
  static unsigned char const QUALIFIER_MAX = 12u;

  /* ... */
  enum $qualifier_type : unsigned char {
    $const = 0x1u,
    $pointer,
    $unbounded,
    $volatile
  };

  // ...
  struct $qualifier final {
    template <$qualifier_type...>
    struct $collection final {};

    // ...
    template <typename, class>
    struct from_collection;

    template <typename base>
    struct from_collection<base, $collection<> > final {
      typedef base type;
    };

    template <typename base, $qualifier_type qualifier, $qualifier_type... qualifiers>
    struct from_collection<base, $collection<qualifier, qualifiers...> > final {
      typedef typename from_collection<
        typename std::conditional<qualifier == $operand::$const,     base const,
        typename std::conditional<qualifier == $operand::$pointer,   base*,
        typename std::conditional<qualifier == $operand::$unbounded, base[],
        typename std::conditional<qualifier == $operand::$volatile,  base volatile,
          base
        >::type>::type>::type>::type>::type>::type,
        $collection<qualifiers...>
      >::type type;
    };

    // ...
    template <typename base>
    struct to_collection final {
      private:
        template <typename, $qualifier_type... qualifiers>
        struct valueof final {
          typedef $collection<qualifiers...> type;
        };

        template <typename subbase, $qualifier_type... qualifiers> struct valueof<subbase const>          final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers..., $operand::$const>                     ::type>::type type; };
        template <typename subbase, $qualifier_type... qualifiers> struct valueof<subbase const volatile> final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers..., $operand::$const, $operand::$volatile>::type>::type type; };
        template <typename subbase, $qualifier_type... qualifiers> struct valueof<subbase volatile>       final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers..., $operand::$volatile>                  ::type>::type type; };
        template <typename subbase, $qualifier_type... qualifiers> struct valueof<subbase*>               final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers..., $operand::$pointer>                   ::type>::type type; };
        template <typename subbase, $qualifier_type... qualifiers> struct valueof<subbase[]>              final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers..., $operand::$unbounded>                 ::type>::type type; };

        template <typename subbase,                       $qualifier_type... qualifiers> struct valueof<subbase&>          final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers...>                    ::type>::type type; };
        template <typename subbase,                       $qualifier_type... qualifiers> struct valueof<subbase&&>         final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers...>                    ::type>::type type; };
        template <typename subbase, std::size_t capacity, $qualifier_type... qualifiers> struct valueof<subbase[capacity]> final { typedef typename std::conditional<$operand::QUALIFIER_MAX == sizeof...(qualifiers), $collection<qualifiers...>, typename valueof<subbase, qualifiers..., $operand::$pointer>::type>::type type; };

      public:
        typedef typename valueof<base>::type type;
    };
  };

  // ...
  union $value {
    friend struct $operand;
    template <typename type> friend type cast($operand const&) const noexcept(false);

    public:
      long double        decimal; // ->> floating-point   form of value evaluated from `$shorthand`
      unsigned long long integer; // ->> integral         form of value evaluated from `$shorthand`
      void              *pointer; // ->> (object) pointer form of value evaluated from `$shorthand`, or address of value evaluated from `$shorthand`; is `NULL` when value represents a type

    private:
      // TODO (Lapys) -> Check which ones are copy-constructible
      std::allocator_arg_t            standard1;
      std::atomic_bool                standard2;
      std::atomic_char                standard3;
      std::atomic_char16_t            standard4;
      std::atomic_char32_t            standard5;
      std::atomic_char8_t             standard6;
      std::atomic_flag                standard7;
      std::atomic_int                 standard8;
      std::atomic_int_fast16_t        standard9;
      std::atomic_int_fast32_t        standard10;
      std::atomic_int_fast64_t        standard11;
      std::atomic_int_fast8_t         standard12;
      std::atomic_int_least16_t       standard13;
      std::atomic_int_least32_t       standard14;
      std::atomic_int_least64_t       standard15;
      std::atomic_int_least8_t        standard16;
      std::atomic_intmax_t            standard17;
      std::atomic_llong               standard18;
      std::atomic_long                standard19;
      std::atomic_ptrdiff_t           standard20;
      std::atomic_schar               standard21;
      std::atomic_short               standard22;
      std::atomic_size_t              standard23;
      std::atomic_uchar               standard24;
      std::atomic_uint                standard25;
      std::atomic_uint_fast16_t       standard26;
      std::atomic_uint_fast32_t       standard27;
      std::atomic_uint_fast64_t       standard28;
      std::atomic_uint_fast8_t        standard29;
      std::atomic_uint_least16_t      standard30;
      std::atomic_uint_least32_t      standard31;
      std::atomic_uint_least64_t      standard32;
      std::atomic_uint_least8_t       standard33;
      std::atomic_uintmax_t           standard34;
      std::atomic_ullong              standard35;
      std::atomic_ulong               standard36;
      std::atomic_ushort              standard37;
      std::atomic_wchar_t             standard38;
      std::atto                       standard39;
      std::bad_alloc                  standard40;
      std::bad_array_new_length       standard41;
      std::bad_cast                   standard42;
      std::bad_exception              standard43;
      std::bad_function_call          standard44;
      std::bad_typeid                 standard45;
      std::bad_weak_ptr               standard46;
      std::bidirectional_iterator_tag standard47;
      std::centi                      standard48;
      std::deca                       standard49;
      std::deci                       standard50;
      std::div_t                      standard51;
      std::endian                     standard52;
      std::exa                        standard53;
      std::exception                  standard54;
      std::exception_ptr              standard55;
      std::false_type                 standard56;
      std::femto                      standard57;
      std::forward_iterator_tag       standard58;
      std::giga                       standard59;
      std::hecto                      standard60;
      std::in_place_t                 standard61;
      std::initializer_list           standard62;
      std::input_iterator_tag         standard63;
      std::kilo                       standard64;
      std::ldiv_t                     standard65;
      std::lldiv_t                    standard66;
      std::mega                       standard67;
      std::memory_order               standard68;
      std::micro                      standard69;
      std::milli                      standard70;
      std::nano                       standard71;
      std::nested_exception           standard72;
      std::new_handler                standard73;
      std::nothrow_t                  standard74;
      std::output_iterator_tag        standard75;
      std::owner_less<void>           standard76;
      std::peta                       standard77;
      std::pico                       standard78;
      std::piecewise_construct_t      standard79;
      std::random_access_iterator_tag standard80;
      std::tera                       standard81;
      std::terminate_handler          standard82;
      std::true_type                  standard83;
      std::type_info                  standard84;
      std::va_list                    standard85;
      std::void_t                     standard86;
      decltype(std::placeholders::_1) standard87;
      decltype(std::placeholders::_2) standard88;
      #ifdef __cpp_aligned_new
        std::align_val_t standard89;
      #endif
      #ifdef __cpp_lib_ranges
        std::dangling      standard90;
        std::from_range_t  standard91;
        std::subrange_kind standard92;
      #endif
      #ifdef __cpp_lib_source_location
        std::source_location standard93;
      #endif
      #ifdef __cpp_lib_three_way_comparison
        std::compare_three_way        standard94;
        std::compare_three_way_result standard95;
        std::partial_ordering         standard96;
        std::strong_ordering          standard97;
        std::weak_ordering            standard98;
        #ifdef __cpp_lib_coroutine
          std::coroutine_handle<void>                        standard99;
          std::coroutine_handle<std::noop_coroutine_promise> standard100;
          std::noop_coroutine_handle                         standard101;
          std::noop_coroutine_promise                        standard102;
          std::suspend_always                                standard103;
          std::suspend_never                                 standard104;
        #endif
      #endif
      #ifdef INTMAX_MAX
        #if INTMAX_MAX >= 1000000000000000000000
          std::zepto standard105;
          std::zetta standard106;
          #if INTMAX_MAX >= 1000000000000000000000000
            std::yocto standard107;
            std::yotta standard108;
          #endif
        #endif
      #endif
      #if defined(INT16_MAX) && defined(INT16_MIN)
        std::atomic_int16_t standard109;
      #endif
      #if defined(INT32_MAX) && defined(INT32_MIN)
        std::atomic_int32_t standard110;
      #endif
      #if defined(INT64_MAX) && defined(INT64_MIN)
        std::atomic_int64_t standard111;
      #endif
      #if defined(INT8_MAX)  && defined(INT8_MIN)
        std::atomic_int8_t standard112;
      #endif
      #if defined(INTPTR_MAX) && defined(INTPTR_MIN)
        std::atomic_intptr_t standard113;
      #endif
      #if defined(UINT16_MAX) && defined(UINT16_MIN)
        std::atomic_uint16_t standard114;
      #endif
      #if defined(UINT32_MAX) && defined(UINT32_MIN)
        std::atomic_uint32_t standard115;
      #endif
      #if defined(UINT64_MAX) && defined(UINT64_MIN)
        std::atomic_uint64_t standard116;
      #endif
      #if defined(UINT8_MAX)  && defined(UINT8_MIN)
        std::atomic_uint8_t standard117;
      #endif
      #if defined(UINTPTR_MAX) && defined(UINTPTR_MIN)
        std::atomic_uintptr_t standard118;
      #endif
      #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
        std::bit_and      <void> standard119; // --> $bitwise_and
        std::bit_not      <>     standard120; // --> $complement
        std::bit_or       <void> standard121; // --> $bitwise_or
        std::bit_xor      <void> standard122; // --> $bitwise_xor
        std::divides      <void> standard123; // --> $divide
        std::equal_to     <void> standard124; // --> $equals
        std::greater      <void> standard125; // --> $greater
        std::greater_equal<void> standard126; // --> $equals_greater
        std::less         <void> standard127; // --> $lesser
        std::less_equal   <void> standard128; // --> $equals_lesser
        std::logical_and  <void> standard129; // --> $boolean_and
        std::logical_not  <void> standard130; // --> $negate
        std::logical_or   <void> standard131; // --> $boolean_or
        std::minus        <void> standard132; // --> $subtract
        std::modulus      <void> standard133; // --> $modulo
        std::multiplies   <void> standard134; // --> $multiply
        std::negate       <void> standard135; // --> $minus
        std::not_equal_to <void> standard136; // --> $unequals
        std::plus         <void> standard137; // --> $add
      #endif
      #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) < 201703L
        std::unexpected_handler standard138;
      #endif
      #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202002L
        std::contiguous_iterator_tag standard139;
        std::default_sentinel_t      standard140;
        std::destroying_delete_t     standard141;
        std::identity                standard142; // --> $self
        std::unreachable_sentinel_t  standard143;
      #endif
      #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
        std::pointer_safety standard144;
      #endif

      /* ... */
      constexpr $value(long double        const decimal) noexcept : decimal(decimal) {}
      constexpr $value(unsigned long long const integer) noexcept : integer(integer) {}
      constexpr $value(void*              const pointer) noexcept : pointer(pointer) {}

      constexpr $value(std::div_t   const object) noexcept : std1(object) {}
      constexpr $value(std::ldiv_t  const object) noexcept : std2(object) {}
      constexpr $value(std::lldiv_t const object) noexcept : std3(object) {}

      /* ... */
  };

  // ...
  template <typename...>
  struct variant final {
    template <typename...>
    friend struct variant;

    private:
      // ... ->> Flag denoting preferred/ valid member access
      enum class access : unsigned char {
        exact     = 4u, // ->> Access perfectly matches
        fit       = 3u, // ->> Access nearly matches
        tolerable = 2u, // ->> Access allowed and preferred
        inexact   = 1u, // ->> Access allowed but un-prioritized
        unfit     = 0u  // ->> Access violates strict aliasing
      };

      // ... ->> Flag denoting boolean metafunction
      enum class operation : unsigned char {
        cast,
        initialize
      };

      // ... ->> Boolean metafunction denoting the preference/ validity of possible operations
      template <variant::operation, typename, typename...>
      struct can final {
        static bool const value = false;
      };

      template <typename base, typename... bases>
      struct can<operation::cast, base, bases...> final {
        template <class, typename subbase>
        struct valueof final {
          static bool const value = std::is_void<typename std::remove_pointer<subbase>::type>::value && (
            std::is_array  <typename std::remove_reference<base>::type>::value ||
            std::is_pointer<typename std::remove_reference<base>::type>::value
          );
        };

        template <typename subbase>
        struct valueof<decltype(static_cast<void>(static_cast<subbase>(std::declval<typename std::conditional<std::is_reference<base>::value, base, base&>::type>()))), subbase> final {
          static bool const value = true;
        };

        /* ... */
        static bool const value = valueof<void, bases...>::value;
      };

      template <typename base, typename... bases>
      struct can<operation::initialize, base, bases...> final {
        template <class, typename subbase = void, typename...>
        struct valueof final {
          static bool const value = std::is_void<typename std::remove_pointer<base>::type>::value && (
            std::is_array  <typename std::remove_reference<subbase>::type>::value ||
            std::is_pointer<typename std::remove_reference<subbase>::type>::value
          );
        };

        template <typename subbase, typename... subbases>
        struct valueof<decltype(static_cast<void>(base(std::declval<typename std::conditional<std::is_void<subbase>::value, base, subbase>::type>(), std::declval<subbases>()...))), subbase, subbases...> final {
          static bool const value = true;
        };

        /* ... */
        static bool const value = valueof<void, bases...>::value;
      };

      // ... ->> Disambiguation type
      struct trait final {};

      // ... ->> Sum collection of types
      template <typename...>
      struct values final {
        // ... ->> See `enum variant<>::access`
        template <variant::operation, typename...>
        struct evaluate final {
          static access const value = access::unfit;
        };

        // ... ->> Boolean denoting inclusion within a collection of values
        template <typename>
        struct in final {
          static bool const value = false;
        };

        // ... ->> Boolean denoting allowed and preferred member access in succeeding type
        template <variant::operation, variant::access, typename...>
        struct is_deferrable final {
          static bool const value = false;
        };

        // ... ->> Boolean denoting allowed and preferred member access in current type
        template <variant::operation, typename...>
        struct is_evaluable final {
          static bool const value = false;
        };

        // ... ->> Unique collection of types
        template <class, typename...>
        struct set;

        template <typename... elements>
        struct set<values<elements...> > final {
          typedef values<elements...> type;
        };

        template <typename... elements, typename base, typename... bases>
        struct set<values<elements...>, base, bases...> final {
          typedef typename std::conditional<
            values<elements...>::template in<base>::value,
            typename set<values<elements...>,       bases...>::type,
            typename set<values<elements..., base>, bases...>::type
          >::type type;
        };

        /* ... */
        template <typename... types>
        constexpr values(types&&...) noexcept {}

        /* ... */
        template <typename type>
        constexpr operator type&() const volatile noexcept = delete;
      };

      template <typename base, typename... bases>
      struct values<base, bases...> final {
        // ... ->> See `struct values<>::evaluate` -->
        template <variant::operation operation, typename... subbases>
        struct evaluate final {
          static variant::access const value = can<operation, base, subbases...>::value ? access::inexact : access::unfit;
        };

        template <variant::operation operation, typename subbase>
        struct evaluate<operation, subbase> final {
          static variant::access const value = can<operation, base, subbase>::value ?
            // typeid(base) == typeid(subbase)
            std::is_same<
              typename std::remove_cv<typename std::remove_reference<base>   ::type>::type,
              typename std::remove_cv<typename std::remove_reference<subbase>::type>::type
            >::value ? access::exact :

            // typeid(base[n]); typeid(subbase[n])
            std::is_array<typename std::remove_reference<base>::type>::value && std::is_array<typename std::remove_reference<subbase>::type>::value &&
            std::extent  <typename std::remove_reference<base>::type>::value == std::extent  <typename std::remove_reference<subbase>::type>::value && (
              std::is_same<
                typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<base>   ::type>::type>::type,
                typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<subbase>::type>::type>::type
              >::value
            ) ? access::exact :

            // typeid(base[]); typeid(subbase[n]), typeid(subbase[])
            std::is_array<typename std::remove_reference<base>   ::type>::value && 0u == std::extent<typename std::remove_reference<base>::type>::value &&
            std::is_array<typename std::remove_reference<subbase>::type>::value && (
              std::is_same<
                typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<base>   ::type>::type>::type,
                typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<subbase>::type>::type>::type
              >::value
            ) ? access::fit :

            // typeid(base*); typeid(subbase[n]), typeid(subbase[]), typeid(subbase*)
            std::is_pointer<typename std::remove_reference<base>::type>::value && ((
              std::is_array  <typename std::remove_reference<subbase>::type>::value && std::is_same<
                typename std::remove_cv<typename std::remove_pointer    <typename std::remove_reference<base>   ::type>::type>::type,
                typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<subbase>::type>::type>::type
              >::value
            ) || (
              std::is_pointer<typename std::remove_reference<subbase>::type>::value && std::is_same<
                typename std::remove_cv<typename std::remove_pointer<typename std::remove_reference<base>   ::type>::type>::type,
                typename std::remove_cv<typename std::remove_pointer<typename std::remove_reference<subbase>::type>::type>::type
              >::value
            )) ? access::tolerable :
          access::inexact : access::unfit;
        };

        // ... ->> See `struct values<>::in`
        template <typename subbase>
        struct in final {
          static bool const value = std::is_same<
            typename std::remove_cv<typename std::remove_reference<base>   ::type>::type,
            typename std::remove_cv<typename std::remove_reference<subbase>::type>::type
          >::value || values<bases...>::template in<subbase>::value;
        };

        // ... ->> See `struct values<>::is_deferrable`
        template <variant::operation operation, variant::access evaluation, typename... subbases>
        struct is_deferrable final {
          static bool const value = (evaluation < evaluate<operation, subbases...>::value) || values<bases...>::template is_deferrable<operation, evaluation, subbases...>::value;
        };

        // ... ->> See `struct values<>::is_evaluable`
        template <variant::operation operation, typename... subbases>
        struct is_evaluable final {
          static bool const value = access::unfit != evaluate<operation, subbases...>::value || values<bases...>::template is_evaluable<operation, subbases...>::value;
        };

        // ... ->> Reference types not explicitly allowed as `union` member but supported in `variant` class
        struct member final {
          // ... ->> Accept any cv-qualification of the reference type
          typename std::conditional<std::is_lvalue_reference<base>::value, typename std::remove_reference<base>::type const volatile&,
          typename std::conditional<std::is_rvalue_reference<base>::value, typename std::remove_reference<base>::type const volatile&&,
            base
          >::type>::type value;

          /* ... */
          template <typename type>
          constexpr member(type&& argument) noexcept :
            value((decltype(member::value)) std::forward<type>(argument))
          {}

          template <typename... types>
          constexpr member(types&&... arguments) noexcept :
            value(std::forward<types>(arguments)...)
          {}
        };

        /* ... */
        union {
          values<bases...> next;
          member           value;
        };

        /* ... */
        constexpr values() noexcept :
          next()
        {}

        template <typename... types>
        constexpr values(types&&... arguments) noexcept :
          values(variant::trait{}, std::forward<types>(arguments)...)
        {}

        template <typename... types>
        constexpr values(typename std::enable_if<false == is_evaluable<operation::initialize, types...>::value, typename variant::trait>::type const, types&&...) noexcept = delete;

        template <typename... types>
        constexpr values(typename std::enable_if<is_evaluable<operation::initialize, types...>::value && false != is_deferrable<operation::initialize, evaluate<operation::initialize, types...>::value, types...>::value, typename variant::trait>::type const, types&&... arguments) noexcept :
          next(std::forward<types>(arguments)...)
        {}

        template <typename... types>
        constexpr values(typename std::enable_if<is_evaluable<operation::initialize, types...>::value && false == is_deferrable<operation::initialize, evaluate<operation::initialize, types...>::value, types...>::value, typename variant::trait>::type const, types&&... arguments) noexcept :
          value(std::forward<types>(arguments)...)
        {}

        /* ... */
        template <typename type, typename std::enable_if<false == is_evaluable<operation::cast, type>::value, std::nullptr_t>::type = nullptr>
        inline operator type&() const volatile noexcept = delete;

        template <typename type, typename std::enable_if<is_evaluable<operation::cast, type>::value && false != is_deferrable<operation::cast, evaluate<operation::cast, type>::value, type>::value, std::nullptr_t>::type = nullptr>
        constexpr operator type&() const volatile noexcept {
          return (type&) this -> next;
        }

        template <typename type, typename std::enable_if<is_evaluable<operation::cast, type>::value && false == is_deferrable<operation::cast, evaluate<operation::cast, type>::value, type>::value, std::nullptr_t>::type = nullptr>
        constexpr operator type&() const volatile noexcept {
          return (type&) this -> value.value;
        }
      };

    public:
      template <typename... types>
      constexpr variant(types&&...) noexcept {}

      /* ... */
      #if __cpp_constexpr >= 201304L
        constexpr
      #endif
      inline operator void() const volatile noexcept {}

      #ifdef __circle_lang__
        template <typename type>
        constexpr operator type&() const noexcept = delete;

        template <typename type>
        constexpr operator type&() const volatile noexcept = delete;

        template <typename type>
        constexpr operator type&&() const volatile noexcept = delete;
      #else
        template <typename type>
        constexpr operator type() const volatile noexcept = delete;
      #endif
  };

  template <typename base, typename... bases>
  struct variant<base, bases...> final {
    private:
      typename variant<>::template values<>::template set<variant<>::template values<>, base, bases...>::type members;

    public:
      template <typename... types>
      constexpr variant(types&&... arguments) noexcept :
        members(std::forward<types>(arguments)...)
      {}

      /* ... */
      #if __cpp_constexpr >= 201304L
        constexpr
      #endif
      inline operator void() const volatile noexcept {}

      #ifdef __circle_lang__
        template <typename type>
        constexpr operator type&() const noexcept {
          return (type&) this -> members;
        }

        template <typename type>
        constexpr operator type&() const volatile noexcept {
          return (type&) this -> members;
        }

        template <typename type>
        constexpr operator type&&() const volatile noexcept {
          return (type&&) (type&) this -> members;
        }
      #else
        template <typename type>
        constexpr operator type() const volatile noexcept {
          return (type) (type&) this -> members;
        }

        #ifndef _MSVC_LANG
          template <typename type>
          constexpr operator type() const noexcept {
            return (type) (type&) this -> members;
          }
        #endif
      #endif
  };

  $operand::kindof<$operand::$decimal>(operand) then operand.value.operator $operand::$decimal()
  $operand::kindof<std::div_t>(operand) then operand.value.operator std::div_t()

  /* ... */
  $qualifier_type       qualifiers[QUALIFIER_MAX]; // ->> type qualifier information of value evaluated from `$shorthand`
  $value                value;                     // ->> value evaluated from `$shorthand`
  std::type_info const &type;                      // ->> type information of value evaluated from `$shorthand`
  std::size_t           alignment;                 // ->> byte offset      of value evaluated from `$shorthand`
  std::size_t           size;                      // ->> byte size        of value evaluated from `$shorthand`

  private:
    typedef decltype($value::decimal) $decimal;
    typedef decltype($value::integer) $integer;
    typedef decltype($value::pointer) $pointer;

    $kind kind;      // ->> `$operand::$value` type information
    void *reference; // ->> true address of value evaluated from `$shorthand`

    /* ... */
    template <typename type, $qualifier_type... qualifiers>
    constexpr $operand(type&& value, $qualifier::$collection<qualifiers...> const, typename std::enable_if<false == (
      std::is_enum          <typename std::remove_reference<type>::type>::value || /* TODO (Lapys) */
      std::is_floating_point<typename std::remove_reference<type>::type>::value ||
      std::is_integral      <typename std::remove_reference<type>::type>::value ||
      std::is_pointer       <typename std::remove_reference<type>::type>::value ||
      std::is_same<std::nullptr_t, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value ||
      #ifdef __cpp_lib_byte
        std::is_same<std::byte, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value ||
      #endif
      false
    ), $void>::type const = $voidop) noexcept :
      qualifiers{qualifiers..., static_cast<$qualifier_type>(0x0u)},
      value     {static_cast<void*>(&const_cast<typename std::remove_reference<type>::type&>(static_cast<typename std::remove_reference<type>::type const volatile&>(std::forward<type>(value))))},
      type      {typeid (type)},
      alignment (alignof(type)),
      size      (sizeof (type)),

      kind     (static_cast<$kind>(0x0u)),
      reference(this -> value.pointer)
    {}

    template <typename type, $qualifier_type... qualifiers>
    constexpr $operand(type&& value, $qualifier::$collection<qualifiers...> const, typename std::enable_if<
      std::is_floating_point<typename std::remove_reference<type>::type>::value,
      $void
    >::type const = $voidop) noexcept :
      qualifiers{qualifiers..., static_cast<$qualifier_type>(0x0u)},
      value     {static_cast<long double>(value)},
      type      (typeid (type)),
      alignment (alignof(type)),
      size      (sizeof (type)),

      kind     ($operand::$decimal),
      reference(&const_cast<typename std::remove_reference<type>::type&>(static_cast<typename std::remove_reference<type>::type const volatile&>(std::forward<type>(value))))
    {}

    template <typename type, $qualifier_type... qualifiers>
    constexpr $operand(type&& value, $qualifier::$collection<qualifiers...> const, typename std::enable_if<(
      std::is_integral<typename std::remove_reference<type>::type>::value ||
      #ifdef __cpp_lib_byte
        std::is_same<std::byte, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value ||
      #endif
      false
    ), $void>::type const = $voidop) noexcept :
      qualifiers{qualifiers..., static_cast<$qualifier_type>(0x0u)},
      value     {static_cast<unsigned long long>(value)},
      type      (typeid (type)),
      alignment (alignof(type)),
      size      (sizeof (type)),

      kind     ($operand::$integer),
      reference(&const_cast<typename std::remove_reference<type>::type&>(static_cast<typename std::remove_reference<type>::type const volatile&>(std::forward<type>(value))))
    {}

    template <typename type, $qualifier_type... qualifiers>
    constexpr $operand(type&& value, $qualifier::$collection<qualifiers...> const, typename std::enable_if<(
      std::is_pointer<typename std::remove_reference<type>::type>::value ||
      std::is_same<std::nullptr_t, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value
    ), $void>::type const = $voidop) noexcept :
      qualifiers{qualifiers..., static_cast<$qualifier_type>(0x0u)},
      value     {const_cast<void*>(static_cast<void const volatile*>(value))},
      type      (typeid (type)),
      alignment (alignof(type)),
      size      (sizeof (type)),

      kind     ($operand::$pointer),
      reference(&const_cast<typename std::remove_reference<type>::type&>(static_cast<typename std::remove_reference<type>::type const volatile&>(std::forward<type>(value))))
    {}

    constexpr $operand(std::type_info const& typeInformation, std::size_t const size, std::size_t const alignment) noexcept :
      qualifiers{static_cast<$qualifier_type>(0x0u)},
      value     {static_cast<void*>(NULL)},
      type      (typeInformation),
      alignment (alignment),
      size      (size),

      kind     (static_cast<$kind>(0x0u))
      reference(NULL)
    {}

    template <typename type>
    constexpr $operand(type&& value) noexcept :
      $operand(std::forward<type>(value), typename $qualifier::to_collection<type>::type{})
    {}

    /* ... */
    template <typename type>
    inline type cast($operand const& operand) const noexcept(false) /* --> throw(std::runtime_error) */ {
      if (NULL == operand.reference) throw std::runtime_error("Shorthand type operand cannot be cast to another type");
      if ($operand::template typeis<type>(operand)) return (type) *static_cast<typename std::remove_reference<type>::type*>(operand.reference);

      throw std::runtime_error("Shorthand operand expected cast to valid type");

      // if (std::is_pointer <type>::value) return $shorthand::template operate<$shorthand::$cast, void, void*, type>::template valueof<type>(this -> value);
      // if (std::is_integral<type>::value) {
      //   #ifdef __cpp_char8_t
      //     if ($operand::template typeis<char8_t>(evaluation)) return $shorthand::template operate<$shorthand::$cast, void, char8_t, type>::template valueof<type>(*$operand::template as<char8_t>(evaluation));
      //   #endif
      //   #ifdef __cpp_lib_byte
      //     if ($operand::template typeis<std::byte>(evaluation)) return $shorthand::template operate<$shorthand::$cast, void, std::byte, type>::template valueof<type>(*$operand::template as<std::byte>(evaluation));
      //   #endif
      //   #ifdef __cpp_unicode_characters
      //     if ($operand::template typeis<char16_t>(evaluation)) return $shorthand::template operate<$shorthand::$cast, void, char16_t, type>::template valueof<type>(*$operand::template as<char16_t>(evaluation));
      //     if ($operand::template typeis<char32_t>(evaluation)) return $shorthand::template operate<$shorthand::$cast, void, char32_t, type>::template valueof<type>(*$operand::template as<char32_t>(evaluation));
      //   #endif
      // }
    }

    // ...
    template <typename type, typename std::enable_if<false != std::is_reference<type>::value, $void>::type = $voidop>
    inline static bool typeis($operand const& operand, std::type_info const& typeInformation) noexcept {
      return typeInformation == operand.type;
    }

    template <typename type, typename std::enable_if<false == std::is_reference<type>::value, $void>::type = $voidop>
    constexpr static bool typeis($operand const& operand, std::type_info const& typeInformation) noexcept {
      return (
        $operand::kindis<$operand::$decimal>(operand) ? std::is_floating_point<type>::value :
        $operand::kindis<$operand::$integer>(operand) ? std::is_integral      <type>::value :
        $operand::kindis<$operand::$pointer>(operand) ? std::is_pointer       <type>::value :
        typeInformation == operand.type
      );
    }

    // ...
    constexpr static std::size_t lengthof($operand const *const operands) noexcept {
      return NULL != operands -> value ? lengthof(operands + 1) + 1u : 0u;
    }

  public:
    template <...>
    constexpr static bool kindis($operand const& operand) noexcept {
      return true;
    }

    // ...
    constexpr static std::size_t lengthof($operand const (&&operands)[]) noexcept {
      return lengthof(static_cast<$operand const*>(operands));
    }

    // ...
    template <typename type>
    constexpr static bool typeis($operand const& operand) noexcept {
      return typeis<type>(operand, typeid(type));
    }

    /* ... */
    #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
      constexpr
    #endif
    inline operator void() const volatile noexcept {
      return static_cast<void>(0x00u);
    }

    template <typename type, typename std::enable_if<std::is_floating_point<type>::value, $void>::type = $voidop>
    constexpr operator type() const noexcept(noexcept(std::declval<$operand const>().cast<type>(std::declval<char const (&)[]>()))) {
      return $operand::$decimal == this -> kind ? static_cast<type>(this -> value.decimal) : cast<type>(*this);
    }

    template <typename type, typename std::enable_if<std::is_integral<type>::value, $void>::type = $voidop>
    constexpr operator type() const noexcept(noexcept(std::declval<$operand const>().cast<type>(std::declval<char const (&)[]>()))) {
      return $operand::$integer == this -> kind ? static_cast<type>(this -> value.integer) : cast<type>(*this);
    }

    template <typename type, typename std::enable_if<std::is_pointer<type>::value, $void>::type = $voidop>
    constexpr operator type() const noexcept(noexcept(std::declval<$operand const>().cast<type>(std::declval<char const (&)[]>()))) {
      return $operand::$pointer == this -> kind ? static_cast<type>(this -> value.pointer) : cast<type>(*this);
    }

    template <typename type, typename std::enable_if<std::is_reference<type>::value, $void>::type = $voidop>
    inline operator type() const noexcept(noexcept(std::declval<$operand const>().cast<type>(std::declval<char const (&)[]>()))) {
      return cast<type>();
    }
};

// ... ->> information on an `$expression` result which gets passed from an `$operation`
struct $evaluation : public $operand {
  using $operand::$operand;

  template <typename type, typename std::enable_if<std::is_reference<type>::value, $void>::type = $voidop>
  inline operator type() const noexcept(noexcept(std::declval<$operand const>().cast<type>())) {
    return $operand::cast<type>(*this);
  }
};

// ... ->> operator functions for expression operands
template <$operation, class...>
struct $expression; // ->> tree of `$shorthand`s inter-operated by `$operation`s

constexpr static $evaluation& $nop          ($operand const (&&)[], $evaluation& evaluation) noexcept { return evaluation; }
constexpr static $evaluation& $member_access($operand const (&&)[], $evaluation& evaluation) noexcept { return evaluation; }

template <$shorthand::$operation_id identity, unsigned char arity, bool variadic = false, $operand::$qualifier_type... qualifiers>
inline $evaluation $op($operand const (&&operands)[], $evaluation& evaluation) noexcept(false) /* --> throw(std::runtime_error) */ {
  constexpr std::size_t count = $operand::lengthof(static_cast<$operand const (&&)[]>(operands));

  // ...
  if (false == variadic) {
    if (count == 0u)   return NULL;
    if (count < arity) throw std::runtime_error("Shorthand (instantiated with zero arguments) expected cast to function type");
  }

  // ... ->> Re-build type qualifiers on inquired `std::type_info` to match later queried types (see next comment for types)
  if (sizeof...(qualifiers) != operands -> qualifiers)
  switch (operands -> qualifiers[sizeof...(qualifiers)]) {
    case $operand::$const    : return $op<identity, arity, qualifiers..., $operand::$const>                            (static_cast<$operand const (&&)[]>(operands), evaluation);
    case $operand::$pointer  : return $op<identity, arity, qualifiers..., $operand::$pointer>                          (static_cast<$operand const (&&)[]>(operands), evaluation);
    case $operand::$unbounded: return $op<identity, arity, qualifiers..., $operand::$unbounded>                        (static_cast<$operand const (&&)[]>(operands), evaluation);
    case $operand::$volatile : return $op<identity, arity, qualifiers..., $operand::$volatile>                         (static_cast<$operand const (&&)[]>(operands), evaluation);
    default:                   return $op<identity, arity, qualifiers..., static_cast<$operand::$qualifier_type>(0x0u)>(static_cast<$operand const (&&)[]>(operands), evaluation);
  }

  // ... ->> Operate on possible built-in type or standard (non-`template`) type from freestanding standard header libraries
  #define $operand_as(base, index) for (                                                                                                                                                                                                                             \
    typename $operand::template $qualifier::template from_collection<base, qualifiers...>::type *value ## index = $operand::template as<typename $operand::template $qualifier::template from_collection<base, qualifiers...>::type>(operands[index]); \
    NULL != value ## index;                                                                                                                                                                                                                                          \
    value ## index = NULL                                                                                                                                                                                                                                            \
  )

  $operand_as(bool, 0) {
    $operand_as(bool,                    1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(char,                    1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(double,                  1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(float,                   1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(int,                     1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(intmax_t,                1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(long,                    1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(long double,             1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(long long,               1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(short,                   1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(signed char,             1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(uintmax_t,               1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(unsigned char,           1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(unsigned int,            1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(unsigned long,           1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(unsigned long long,      1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(unsigned short,          1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(void*,                   1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(wchar_t,                 1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(std::div_t,              1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(std::float_denorm_style, 1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(std::float_round_style,  1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(std::ldiv_t,             1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(std::lldiv_t,            1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(std::nullptr_t,          1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
    $operand_as(decltype(NULL),          1) { if ($shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::value) return $shorthand::template operate<$self, decltype(*value0), decltype(*value1)>::valueof(*value0, *value1); }
  }

  #undef $operand_as

  #ifdef __cpp_char8_t
    ::new (&type) std::type_info(typeid(char8_t)); if (type == operands -> type) { *static_cast<char8_t*>(operands -> value); } type.~std::type_info();
  #endif
  #ifdef __cpp_unicode_characters
    ::new (&type) std::type_info(typeid(char16_t)); if (type == operands -> type) { *static_cast<char16_t*>(operands -> value); } type.~std::type_info();
    ::new (&type) std::type_info(typeid(char32_t)); if (type == operands -> type) { *static_cast<char32_t*>(operands -> value); } type.~std::type_info();
  #endif
  #ifdef __cpp_lib_byte
    ::new (&type) std::type_info(typeid(std::byte)); if (type == operands -> type) { *static_cast<std::byte*>(operands -> value); } type.~std::type_info();
  #endif

  switch (identity) {
    case $shorthand::$add:                   {                 } break;
    case $shorthand::$address:               {                 } break;
    case $shorthand::$assign:                {                 } break;
    case $shorthand::$assign_add:            {                 } break;
    case $shorthand::$assign_bitwise_and:    {                 } break;
    case $shorthand::$assign_bitwise_or:     {                 } break;
    case $shorthand::$assign_bitwise_xor:    {                 } break;
    case $shorthand::$assign_divide:         {                 } break;
    case $shorthand::$assign_left_shift:     {                 } break;
    case $shorthand::$assign_modulo:         {                 } break;
    case $shorthand::$assign_multiply:       {                 } break;
    case $shorthand::$assign_right_shift:    {                 } break;
    case $shorthand::$assign_subtract:       {                 } break;
    case $shorthand::$bitwise_and:           {                 } break;
    case $shorthand::$bitwise_or:            {                 } break;
    case $shorthand::$bitwise_xor:           {                 } break;
    case $shorthand::$boolean_and:           {                 } break;
    case $shorthand::$boolean_or:            {                 } break;
    case $shorthand::$call:                  {                 } break;
    case $shorthand::$cast:                  {                 } break;
    case $shorthand::$comma:                 {                 } break;
    case $shorthand::$compare:               {                 } break;
    case $shorthand::$complement:            {                 } break;
    case $shorthand::$dereference:           {                 } break;
    case $shorthand::$divide:                {                 } break;
    case $shorthand::$equals:                {                 } break;
    case $shorthand::$equals_greater:        {                 } break;
    case $shorthand::$equals_lesser:         {                 } break;
    case $shorthand::$greater:               {                 } break;
    case $shorthand::$left_shift:            {                 } break;
    case $shorthand::$lesser:                {                 } break;
    case $shorthand::$member_access:         {                 } break;
    case $shorthand::$member_pointer_access: {                 } break;
    case $shorthand::$minus:                 {                 } break;
    case $shorthand::$modulo:                {                 } break;
    case $shorthand::$multiply:              {                 } break;
    case $shorthand::$negate:                {                 } break;
    case $shorthand::$plus:                  {                 } break;
    case $shorthand::$post_decrement:        {                 } break;
    case $shorthand::$post_increment:        {                 } break;
    case $shorthand::$pre_decrement:         {                 } break;
    case $shorthand::$pre_increment:         {                 } break;
    case $shorthand::$right_shift:           {                 } break;
    case $shorthand::$self:                  {                 } break;
    case $shorthand::$subscript:             {                 } break;
    case $shorthand::$subtract:              {                 } break;
    case $shorthand::$ternary:               { bool condition; } break;
    case $shorthand::$unequal:               {                 } break;
  }

  return NULL;
}

constexpr static $evaluation& (*$add)                  ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$add,                   2u>;
constexpr static $evaluation& (*$address)              ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$address,               1u>;
constexpr static $evaluation& (*$assign)               ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign,                2u>;
constexpr static $evaluation& (*$assign_add)           ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_add,            2u>;
constexpr static $evaluation& (*$assign_bitwise_and)   ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_bitwise_and,    2u>;
constexpr static $evaluation& (*$assign_bitwise_or)    ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_bitwise_or,     2u>;
constexpr static $evaluation& (*$assign_bitwise_xor)   ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_bitwise_xor,    2u>;
constexpr static $evaluation& (*$assign_divide)        ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_divide,         2u>;
constexpr static $evaluation& (*$assign_left_shift)    ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_left_shift,     2u>;
constexpr static $evaluation& (*$assign_modulo)        ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_modulo,         2u>;
constexpr static $evaluation& (*$assign_multiply)      ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_multiply,       2u>;
constexpr static $evaluation& (*$assign_right_shift)   ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_right_shift,    2u>;
constexpr static $evaluation& (*$assign_subtract)      ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$assign_subtract,       2u>;
constexpr static $evaluation& (*$bitwise_and)          ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$bitwise_and,           2u>;
constexpr static $evaluation& (*$bitwise_or)           ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$bitwise_or,            2u>;
constexpr static $evaluation& (*$bitwise_xor)          ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$bitwise_xor,           2u>;
constexpr static $evaluation& (*$boolean_and)          ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$boolean_and,           2u>;
constexpr static $evaluation& (*$boolean_or)           ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$boolean_or,            2u>;
constexpr static $evaluation& (*$call)                 ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$call,                  0u, true>;
constexpr static $evaluation& (*$cast)                 ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$cast,                  2u>;
constexpr static $evaluation& (*$comma)                ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$comma,                 2u>;
constexpr static $evaluation& (*$compare)              ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$compare,               2u>;
constexpr static $evaluation& (*$complement)           ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$complement,            1u>;
constexpr static $evaluation& (*$dereference)          ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$dereference,           1u>;
constexpr static $evaluation& (*$divide)               ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$divide,                2u>;
constexpr static $evaluation& (*$equals)               ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$equals,                2u>;
constexpr static $evaluation& (*$equals_greater)       ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$equals_greater,        2u>;
constexpr static $evaluation& (*$equals_lesser)        ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$equals_lesser,         2u>;
constexpr static $evaluation& (*$greater)              ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$greater,               2u>;
constexpr static $evaluation& (*$left_shift)           ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$left_shift,            2u>;
constexpr static $evaluation& (*$lesser)               ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$lesser,                2u>;
constexpr static $evaluation& (*$member_access)        ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$member_access,         1u>;
constexpr static $evaluation& (*$member_pointer_access)($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$member_pointer_access, 2u>;
constexpr static $evaluation& (*$minus)                ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$minus,                 1u>;
constexpr static $evaluation& (*$modulo)               ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$modulo,                2u>;
constexpr static $evaluation& (*$multiply)             ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$multiply,              2u>;
constexpr static $evaluation& (*$negate)               ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$negate,                1u>;
constexpr static $evaluation& (*$plus)                 ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$plus,                  1u>;
constexpr static $evaluation& (*$post_decrement)       ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$post_decrement,        1u>;
constexpr static $evaluation& (*$post_increment)       ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$post_increment,        1u>;
constexpr static $evaluation& (*$pre_decrement)        ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$pre_decrement,         1u>;
constexpr static $evaluation& (*$pre_increment)        ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$pre_increment,         1u>;
constexpr static $evaluation& (*$right_shift)          ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$right_shift,           2u>;
constexpr static $evaluation& (*$self)                 ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$self,                  1u>;
constexpr static $evaluation& (*$subscript)            ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$subscript,             2u>;
constexpr static $evaluation& (*$subtract)             ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$subtract,              2u>;
constexpr static $evaluation& (*$ternary)              ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$ternary,               3u>;
constexpr static $evaluation& (*$unequal)              ($operand const (&&)[], $evaluation& evaluation) noexcept(false) = $op<$shorthand::$unequal,               2u>;

// ... ->> evaluates to nil constant object ie: zero or default-constructed
template <typename base, typename = base>
struct $nil final {
  constexpr base operator ()() const&& noexcept {
    return {};
  }
};

template <typename base>
struct $nil<base, decltype((base) 0x00u)> final {
  constexpr base operator ()() const&& noexcept {
    return (base) 0x00u;
  }
};

// ...
struct $$;         // ->> compose `$shorthand` list as multiple "ith" arguments
struct $break;     // ->> terminate    `$for` or `$while` iteration --> $break   [$$]; $break    == $break   [$1]
struct $continue;  // ->> skip to next `$for` or `$while` iteration --> $continue[$$]; $continue == $continue[$1]
struct $if;        // ->> evaluates to `$shorthand` if truthy, otherwise `void` (or `$elif` or `$else`) if falsy
struct $label;     // ->> represents "ith" argument with a name (which need not be a string literal)
struct $loop;      // ->> evaluates `$shorthand` multiple times; returns `void`
struct $while;     //

template <unsigned char, typename = void>       struct $;           // ->> evaluates to the "ith" argument; the only `$shorthand` able to use constructor as function call
                                                                    // --> sizeof(unsigned char : 0) | sizeof(struct { void* | T; bool; })
template <typename>                             struct $as;         // ->> evaluates `$shorthand` to `T`
template <typename base, base = $nil<base>{}()> struct $constant;   // ->> evaluates to constant object (or `$nil` otherwise specified)
template <std::size_t, std::size_t = 0u>        struct $for;        //
template <std::size_t>                          struct $index;      // ->> evaluates to the "ith" `$for` loop's index
template <typename>                             struct $object;     // ->> evaluates to runtime object

// ...
using $i = $index<0u>;
using $j = $index<1u>;
using $k = $index<2u>;

template <typename base, base constant>
using $c = $constant<base, constant>;

/* ... */
// template <typename type, class $shorthand>
// constexpr friend $expression<$call, $expression<$self, $object<type> >, $expression<$self, $shorthand> > operator &(type function, $expression<$self, $shorthand> const& shorthand) noexcept {
//   return {function, shorthand};
// }

// ...
template <>
struct $expression<$voidop> final : public $shorthand {
  public:
    template <class>
    struct is_expression {};

  private:
    template <class>
    struct is_object final {
      static bool const value = false;
    };

    template <typename base>
    struct is_object<$expression<$self, $object<base> > > final {
      static bool const value = true;
    };

    template <$operation operation, class $shorthand, class... $shorthands>
    struct is_object<$expression<operation, $shorthand, $shorthands...> > final {
      static bool const value = false;
      // static bool const value = is_object<$expression<$self, $shorthand> >::value || is_object<$expression<$self, $shorthands...> >::value;
    };
};

template <$operation operation, class... $shorthands>
struct $expression : public $expression<operation,
typename std::conditional<
typename std::is_base_of<$shorthand, $shorthands>::value,
$shorthands
>::type...
> {};

template <$operation operation, $operation operationA, class $shorthandA, $operation operationB, class $shorthandB>
struct $expression<operation, $expression<operationA, $shorthandA>, $expression<operationB, $shorthandB>, typename std::enable_if<false != $expression<$voidop>::template is_object<$shorthandA>::value, $void>::type> : public $shorthand {
  unsigned long long : CHAR_BIT * sizeof(unsigned long long);
};

template <$operation operation, $operation operationA, class $shorthandA, $operation operationB, class $shorthandB>
struct $expression<operation, $expression<operationA, $shorthandA>, $expression<operationB, $shorthandB>, typename std::enable_if<false == $expression<$voidop>::template is_object<$shorthandA>::value, $void>::type> : public $shorthand {
};

// template <unsigned char operation, class base, class $shorthand>
// struct $expression<operation, $expression<$self, $object<base> >, $shorthand> : public ::$shorthand {};

template <unsigned char index>
struct $expression<$self, $<index> > : public $shorthand {
  friend struct $expression<$self, $<index + 1u> >;
  template <unsigned char, typename> friend struct $;

  private:
    #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) < 201402L
      typedef $void constvoid;
    #else
      typedef void constvoid;
    #endif

    /* ... */
    template <typename...>
    struct typeat final {
      typedef void type;
    };

    template <typename base, typename... bases>
    struct typeat<base, bases...> final {
      typedef typename std::conditional<index == 1u, base, typename $expression<$self, $<index - (index != 0u)> >::template typeat<bases...>::type>::type type;
    };

    // ...
    template <typename base>
    struct cast final {
      static_assert(sizeof(typename std::conditional<std::is_void<base>::value, $void, base>::type) == 0u, "Shorthand expected cast to function type");
      static typename std::conditional<std::is_void<base>::value, $void, base>::type value;
    };

    template <typename base, typename... bases>
    struct cast<base (bases...)> final {
      constexpr static base value(bases... arguments) noexcept {
        return static_cast<base>(invoke(static_cast<bases>(arguments)...));
      }
    };

    template <typename base, typename... bases>
    struct cast<base (bases..., ...)> final {
      constexpr static base value(bases... arguments, ...) noexcept {
        return static_cast<base>(invoke(static_cast<bases>(arguments)...));
      }
    };

    #ifdef __cpp_noexcept_function_type
      template <typename base, typename... bases>
      struct cast<base (bases...) noexcept> final {
        constexpr static base (&value)(bases...) noexcept = cast<base (bases...)>::value;
      };

      template <typename base, typename... bases>
      struct cast<base (bases..., ...) noexcept> final {
        constexpr static base (&value)(bases..., ...) noexcept = cast<base (bases..., ...)>::value;
      };
    #endif

    /* ... */
    template <std::size_t count = index, typename = void, typename... types>
    constexpr static constvoid invoke(types&&...) noexcept {
      static_assert(count == 0u, "Shorthand expected more arguments");
      return static_cast<constvoid>($voidop);
    }

    template <std::size_t count = index, typename = void, typename type, typename... types>
    constexpr static typename std::enable_if<count == 1u, type&&>::type invoke(type&& argument, types&&...) noexcept {
      return std::forward<type>(argument);
    }

    template <std::size_t count = index, typename base = void, typename type, typename... types>
    constexpr static typename std::enable_if<(count > 1u), typename std::conditional<std::is_void<base>::value, typename typeat<type&&, types&&...>::type, base>::type>::type invoke(type&&, types&&... arguments) noexcept {
      return static_cast<typename std::conditional<std::is_void<base>::value, typename typeat<type&&, types&&...>::type, base>::type>(invoke<count - 1u, typename std::conditional<std::is_void<base>::value, typename typeat<type&&, types&&...>::type, base>::type, types&&...>(std::forward<types>(arguments)...));
    }

  public:
    #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
      constexpr
    #endif
    inline operator void() const volatile noexcept {
      return cast<void>::value;
    }

    template <typename type>
    constexpr operator type() const volatile noexcept {
      return static_cast<type>(cast<typename std::conditional<std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value, typename std::remove_pointer<typename std::remove_reference<type>::type>::type, type>::type>::value);
    }

    template <typename... types>
    constexpr typename typeat<types&&...>::type operator ()(types&&... arguments) const volatile noexcept {
      return static_cast<typename typeat<types&&...>::type>(invoke(std::forward<types>(arguments)...));
    }
};

template <typename base, base constant>
struct $expression<$self, $constant<base, constant> > : public $shorthand {
  private:
    template <typename subbase>
    struct cast final {
      static_assert(sizeof(typename std::conditional<std::is_void<subbase>::value, $void, subbase>::type) == 0u, "Shorthand expected cast to function type");
      static typename std::conditional<std::is_void<subbase>::value, $void, subbase>::type value;
    };

    template <typename subbase, typename... subbases>
    struct cast<subbase (subbases...)> final {
      constexpr static subbase value(subbases...) noexcept {
        return (subbase) constant;
      }
    };

    template <typename subbase, typename... subbases>
    struct cast<subbase (subbases..., ...)> final {
      constexpr static subbase value(subbases..., ...) noexcept {
        return (subbase) constant;
      }
    };

    #ifdef __cpp_noexcept_function_type
      template <typename subbase, typename... subbases>
      struct cast<subbase (subbases...) noexcept> final {
        constexpr static subbase (&value)(subbases...) noexcept = cast<subbase (subbases...)>::value;
      };

      template <typename subbase, typename... subbases>
      struct cast<subbase (subbases..., ...) noexcept> final {
        constexpr static subbase (&value)(subbases..., ...) noexcept = cast<subbase (subbases..., ...)>::value;
      };
    #endif

  public:
    #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
      constexpr
    #endif
    inline operator void() const volatile noexcept {
      return cast<void>::value;
    }

    template <typename type>
    constexpr operator type() const volatile noexcept {
      return static_cast<type>(cast<typename std::conditional<std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value, typename std::remove_pointer<typename std::remove_reference<type>::type>::type, type>::type>::value);
    }

    template <typename... types>
    constexpr base operator ()(types&&...) const volatile noexcept {
      return constant;
    }
};

template <typename base>
struct $expression<$self, $object<base> > : public $shorthand {
  private:
    base value;

    /* ... */
    constexpr $expression($expression<$self, $object<base> > const& shorthand) noexcept :
      value(static_cast<base>(shorthand.value))
    {}

    template <typename type>
    constexpr $expression(type&& argument) noexcept :
      value((base) (typename std::remove_reference<base>::type&) const_cast<typename std::remove_reference<type>::type&>((typename std::remove_reference<type>::type const&) std::forward<type>(argument)))
    {}
};

// ...
template <unsigned char index, typename base>
struct $ : public $expression<$self, $<index> > {
  private:
    template <typename subbase, bool = std::is_function<typename std::remove_pointer<typename std::remove_reference<subbase>::type>::type>::value>
    struct cast final {
      #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
        constexpr
      #endif
      inline static subbase valueof() noexcept(false) /* --> throw(std::runtime_error) */ {
        throw std::runtime_error("Shorthand (instantiated with zero arguments) expected cast to function type");
        // ->> `static_assert(...)` preferable, but possibly runtime members are not evaluated at compile-time
      }
    };

    template <typename subbase>
    struct cast<subbase, true> final {
      constexpr static subbase valueof() noexcept(true) {
        return $expression<$self, $<index> >::template cast<typename std::remove_pointer<typename std::remove_reference<subbase>::type>::type>::value;
      }
    };

    // ...
    template <typename subbase, class = $void>
    struct is_addressable final {
      static bool const value = true;
    };

    template <typename subbase>
    struct is_addressable<subbase, decltype(static_cast<void>(std::declval<subbase>().operator &()), std::declval<$void>())> final {
      static bool const value = std::is_scalar<subbase>::value;
    };

    /* ... */
    template <typename type>
    constexpr static typename std::enable_if<false != is_addressable<type>::value, typename std::remove_reference<type>::type*>::type addressof(type&& object) noexcept {
      return &const_cast<type&>(static_cast<type const&>(object));
    }

    template <typename type>
    inline static typename std::enable_if<false == is_addressable<type>::value, typename std::remove_reference<type>::type*>::type addressof(type&& object) noexcept {
      return const_cast<type*>(reinterpret_cast<type const*>(&reinterpret_cast<unsigned char const&>(static_cast<type const&>(object))));
    }

    /* ... */
    union {
      struct /* ->> implementation-defined unnamed `struct` with possibly reference-qualified member */ {
        typename std::conditional<std::is_void<base>::value, void /* const volatile */*, base>::type value;

        /* ... */
        template <typename type, typename std::enable_if<false != std::is_void<base>::value && false == std::is_void<type>::value, $void>::type = $voidop>
        inline operator type() const volatile noexcept {
          // --> std::unreachable();
          return reinterpret_cast<typename std::remove_reference<type>::type&>(const_cast<void*&>(this -> value));
        }

        template <typename type, typename std::enable_if<false == std::is_void<base>::value && false == std::is_void<type>::value, $void>::type = $voidop>
        constexpr operator type() const noexcept {
          return (type) this -> value;
        }
      } object;

      union {
        void const volatile *value;

        /* ... */
        template <typename type>
        constexpr operator type() const noexcept {
          return static_cast<type>(*static_cast<typename std::remove_reference<type>::type*>(const_cast<void*>(this -> value)));
        }
      } reference;
    };
    bool instantiated;

  public:
    constexpr $() noexcept :
      reference   {NULL},
      instantiated(false)
    {}

    template <typename... types, typename std::enable_if<(index > sizeof...(types)), $void>::type = $voidop>
    constexpr $(types&&...) noexcept :
      reference   {NULL},
      instantiated(false)
    { static_assert(0u == sizeof...(types), "Shorthand expected more arguments"); }

    template <typename... types, typename std::enable_if<false != std::is_void<base>::value && (index <= sizeof...(types)), $void>::type = $voidop>
    constexpr $(types&&... arguments) noexcept :
      reference   {addressof($expression<$self, $<index> >::invoke(std::forward<types>(arguments)...))},
      instantiated(true)
    {}

    template <typename... types, typename std::enable_if<false == std::is_void<base>::value && (index <= sizeof...(types)), $void>::type = $voidop>
    constexpr $(types&&... arguments) noexcept :
      object      {(base) const_cast<typename std::remove_reference<typename $expression<$self, $<index> >::template typeat<types&&...>::type>::type&>(static_cast<typename std::remove_reference<typename $expression<$self, $<index> >::template typeat<types&&...>::type>::type const&>($expression<$self, $<index> >::invoke(std::forward<types>(arguments)...)))},
      instantiated(true)
    {}

    /* ... */
    #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
      constexpr
    #endif
    operator void() const&& noexcept(noexcept(cast<void>::valueof())) {
      return this -> instantiated ? static_cast<void>(0x00u) : cast<void>::valueof();
    }

    template <typename type>
    constexpr operator type() const&& noexcept(noexcept(cast<type>::valueof())) {
      return this -> instantiated ? std::is_void<base>::value ? this -> reference.operator type() : this -> object.operator type() : cast<type>::valueof();
    }
};

template <typename base>
struct $<0u, base> : public $expression<$self, $<0u> > {
  constexpr $(...) noexcept {}
};

template <unsigned char index> struct $<index, $void>                : public $expression<$self, $<index> > {};
template <unsigned char index> struct $<index, $void const>          : public $<index, $void> {};
template <unsigned char index> struct $<index, $void const volatile> : public $<index, $void> {};
template <unsigned char index> struct $<index, $void volatile>       : public $<index, $void> {};

template <> struct $<0u, $void>                : public $expression<$self, $<0u> > {};
template <> struct $<0u, $void const>          : public $<0u, $void> {};
template <> struct $<0u, $void const volatile> : public $<0u, $void> {};
template <> struct $<0u, $void volatile>       : public $<0u, $void> {};

// ...
template <typename base, base constant>
struct $constant : public $expression<$self, $constant<base, constant> > {};

template <>
struct $constant<$void> : public $shorthand {
  friend struct $constant<$void const>;
  friend struct $constant<$void const volatile>;
  friend struct $constant<$void volatile>;

  #ifdef __cpp_nontype_template_parameter_auto
    template <auto> friend struct $e;
    template <auto> friend struct $f;
    template <auto> friend struct $s;
    template <auto> friend struct $u;
  #endif

  private:
    template <typename baseA, typename baseB, typename = baseB>
    struct is_convertible final {
      static const bool value = false;
    };

    template <typename baseA, typename baseB>
    struct is_convertible<baseA, baseB, decltype((baseB) std::declval<baseA>())> final {
      static const bool value = true;
    };

    // ...
    template <typename baseA, typename baseB, bool = is_convertible<baseA, baseB>::value>
    struct cast final {
      template <baseA constant, baseB>
      constexpr static baseB valueof() noexcept {
        return (baseB) constant;
      }
    };

    template <typename baseA, typename baseB>
    struct cast<baseA, baseB, false> final {
      template <baseA, baseB constant /* --> std::unexpected() */>
      constexpr static baseB valueof() noexcept {
        return constant;
      }
    };
};

template <> struct $constant<$void const>          : public $constant<$void> { using $constant<$void>::is_convertible; };
template <> struct $constant<$void const volatile> : public $constant<$void> { using $constant<$void>::is_convertible; };
template <> struct $constant<$void volatile>       : public $constant<$void> { using $constant<$void>::is_convertible; };

// ...
template <typename base>
struct $object : public $expression<$self, $object<base> > {
  using $expression<$self, $object<base> >::$expression;
};

/* ... */
#ifdef __cpp_nontype_template_parameter_auto
  template <auto constant>
  struct $e : public std::conditional<
    #if defined(_MSVC_LANG) || __cplusplus >= 201402L
      std::is_enum<decltype(constant)>::value,
    #else
      $constant<$void>::template is_convertible<decltype(constant), signed   char>     ::value ||
      $constant<$void>::template is_convertible<decltype(constant), signed   int>      ::value ||
      $constant<$void>::template is_convertible<decltype(constant), signed   long>     ::value ||
      $constant<$void>::template is_convertible<decltype(constant), signed   long long>::value ||
      $constant<$void>::template is_convertible<decltype(constant), signed   short>    ::value ||
      $constant<$void>::template is_convertible<decltype(constant), unsigned char>     ::value ||
      $constant<$void>::template is_convertible<decltype(constant), unsigned int>      ::value ||
      $constant<$void>::template is_convertible<decltype(constant), unsigned long>     ::value ||
      $constant<$void>::template is_convertible<decltype(constant), unsigned long long>::value ||
      $constant<$void>::template is_convertible<decltype(constant), unsigned short>    ::value ||
      false,
    #endif
    $constant<decltype(constant), constant>,
    $constant<unsigned long long, 0x00u>
  >::type {
    private:
      template <typename base>
      struct is_instantiable final {
        static bool const value = (
          #if defined(_MSVC_LANG) || __cplusplus >= 201402L
            std::is_enum<decltype(constant)>::value
          #else
            $constant<$void>::template is_convertible<base, signed   char>     ::value ||
            $constant<$void>::template is_convertible<base, signed   int>      ::value ||
            $constant<$void>::template is_convertible<base, signed   long>     ::value ||
            $constant<$void>::template is_convertible<base, signed   long long>::value ||
            $constant<$void>::template is_convertible<base, signed   short>    ::value ||
            $constant<$void>::template is_convertible<base, unsigned char>     ::value ||
            $constant<$void>::template is_convertible<base, unsigned int>      ::value ||
            $constant<$void>::template is_convertible<base, unsigned long>     ::value ||
            $constant<$void>::template is_convertible<base, unsigned long long>::value ||
            $constant<$void>::template is_convertible<base, unsigned short>    ::value ||
            false
          #endif
        );
      };

      static_assert(is_instantiable<decltype(constant)>::value, "Shorthand unable to instantiate enumerator constant");
  };

  // ...
  #if defined(__cpp_nontype_template_args) && __cpp_nontype_template_args >= 201911L
    template <auto constant>
    struct $f : public std::conditional<
      std::is_floating_point<decltype(constant)>::value,
      $constant<decltype(constant), constant>,
    typename std::conditional<
      $constant<$void>::template is_convertible<decltype(constant), long double>::value,
      $constant<long double, $constant<$void>::template cast<decltype(constant), long double>::template valueof<constant, 0.0L>()>,
    typename std::conditional<
      $constant<$void>::template is_convertible<decltype(constant), double>::value,
      $constant<double, $constant<$void>::template cast<decltype(constant), double>::template valueof<constant, 0.0>()>,
    typename std::conditional<
      $constant<$void>::template is_convertible<decltype(constant), float>::value,
      $constant<float, $constant<$void>::template cast<decltype(constant), float>::template valueof<constant, 0.0f>()>,

      $constant<float, 0.0f>
    >::type>::type>::type>::type {
      private:
        template <typename base>
        struct is_instantiable final {
          static bool const value = (
            $constant<$void>::template is_convertible<base, double>     ::value ||
            $constant<$void>::template is_convertible<base, float>      ::value ||
            $constant<$void>::template is_convertible<base, long double>::value ||
            std::is_floating_point<base>::value
          );
        };

        static_assert(is_instantiable<decltype(constant)>::value, "Shorthand unable to instantiate floating-point constant");
    };
  #else
    template <auto constant>
    struct $f : public std::conditional<(
      $constant<$void>::template is_convertible<decltype(constant), double>     ::value ||
      $constant<$void>::template is_convertible<decltype(constant), float>      ::value ||
      $constant<$void>::template is_convertible<decltype(constant), long double>::value ||
      std::is_floating_point<decltype(constant)>::value
    ), $constant<decltype(constant), constant>, $constant<unsigned long long, 0x00u> >::type {
      private:
        template <typename base>
        struct is_instantiable final {
          static bool const value = (
            $constant<$void>::template is_convertible<base, double>     ::value ||
            $constant<$void>::template is_convertible<base, float>      ::value ||
            $constant<$void>::template is_convertible<base, long double>::value ||
            std::is_floating_point<base>::value
          );
        };

        static_assert(is_instantiable<decltype(constant)>::value, "Shorthand unable to instantiate floating-point constant");
    };
  #endif

  // ...
  template <auto constant>
  struct $s : public std::conditional<
    std::is_signed<decltype(constant)>::value,
    $constant<decltype(constant), constant>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), signed long long>::value,
    $constant<signed long long, $constant<$void>::template cast<decltype(constant), signed long long>::template valueof<constant, 0uLL>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), signed long>::value,
    $constant<signed long, $constant<$void>::template cast<decltype(constant), signed long>::template valueof<constant, 0uL>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), signed int>::value,
    $constant<signed int, $constant<$void>::template cast<decltype(constant), signed int>::template valueof<constant, 0u>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), signed short>::value,
    $constant<signed short, $constant<$void>::template cast<decltype(constant), signed short>::template valueof<constant, 0u>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), signed char>::value,
    $constant<signed char, $constant<$void>::template cast<decltype(constant), signed char>::template valueof<constant, 0u>()>,

    $constant<signed, 0u>
  >::type>::type>::type>::type>::type>::type {
    private:
      template <typename base>
      struct is_instantiable final {
        static bool const value = (
          $constant<$void>::template is_convertible<base, signed char>     ::value ||
          $constant<$void>::template is_convertible<base, signed int>      ::value ||
          $constant<$void>::template is_convertible<base, signed long>     ::value ||
          $constant<$void>::template is_convertible<base, signed long long>::value ||
          $constant<$void>::template is_convertible<base, signed short>    ::value ||
          std::is_signed<base>::value
        );
      };

      static_assert(is_instantiable<decltype(constant)>::value, "Shorthand unable to instantiate (signed) integer constant");
  };

  // ...
  template <auto constant>
  struct $u : public std::conditional<
    std::is_unsigned<decltype(constant)>::value,
    $constant<decltype(constant), constant>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), unsigned long long>::value,
    $constant<unsigned long long, $constant<$void>::template cast<decltype(constant), unsigned long long>::template valueof<constant, 0uLL>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), unsigned long>::value,
    $constant<unsigned long, $constant<$void>::template cast<decltype(constant), unsigned long>::template valueof<constant, 0uL>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), unsigned int>::value,
    $constant<unsigned int, $constant<$void>::template cast<decltype(constant), unsigned int>::template valueof<constant, 0u>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), unsigned short>::value,
    $constant<unsigned short, $constant<$void>::template cast<decltype(constant), unsigned short>::template valueof<constant, 0u>()>,
  typename std::conditional<
    $constant<$void>::template is_convertible<decltype(constant), unsigned char>::value,
    $constant<unsigned char, $constant<$void>::template cast<decltype(constant), unsigned char>::template valueof<constant, 0u>()>,

    $constant<unsigned, 0u>
  >::type>::type>::type>::type>::type>::type {
    private:
      template <typename base>
      struct is_instantiable final {
        static bool const value = (
          $constant<$void>::template is_convertible<base, unsigned char>     ::value ||
          $constant<$void>::template is_convertible<base, unsigned int>      ::value ||
          $constant<$void>::template is_convertible<base, unsigned long>     ::value ||
          $constant<$void>::template is_convertible<base, unsigned long long>::value ||
          $constant<$void>::template is_convertible<base, unsigned short>    ::value ||
          std::is_unsigned<base>::value
        );
      };

      static_assert(is_instantiable<decltype(constant)>::value, "Shorthand unable to instantiate unsigned integer constant");
  };
#else
  template <unsigned long long constant>
  using $e = $constant<unsigned long long, constant>;

  // ...
  #if defined(__cpp_nontype_template_args) && __cpp_nontype_template_args >= 201911L && false == defined(__circle_lang__)
    template <long double constant>
    using $f = $constant<long double, constant>;
  #else
    template <unsigned long long constant>
    struct $f : public $constant<unsigned long long, constant> {
      static_assert(constant != constant, "Shorthand unable to instantiate floating-point constant");
    };
  #endif

  // ...
  template <signed long long constant>
  using $s = $constant<signed long long, constant>;

  // ...
  template <unsigned long long constant>
  using $u = $constant<unsigned long long, constant>;
#endif

/* ... */
#if defined(__clang__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
  constexpr static $<0u, $void> $0 {};
  constexpr static $<1u, $void> $1 {};
  constexpr static $<2u, $void> $2 {};
  constexpr static $<3u, $void> $3 {};
  constexpr static $<4u, $void> $4 {};
  constexpr static $<5u, $void> $5 {};
  constexpr static $<6u, $void> $6 {};
  constexpr static $<7u, $void> $7 {};
  constexpr static $<8u, $void> $8 {};
  constexpr static $<9u, $void> $9 {};
#else
  constexpr static union {
    $<0u, $void> $0;
    $<1u, $void> $1;
    $<2u, $void> $2;
    $<3u, $void> $3;
    $<4u, $void> $4;
    $<5u, $void> $5;
    $<6u, $void> $6;
    $<7u, $void> $7;
    $<8u, $void> $8;
    $<9u, $void> $9;
  };
#endif

/* Main */
#include <cstdio>

// ...
template <intmax_t value>
struct $int : public $s<value> {
  constexpr static $void (*$fused_multiply_add)($operand const (&&operands)[], ) noexcept(false) {
    return $voidop;
  }

  template <class... $shorthands>
  constexpr $expression<$int::$fused_multiply_add, $<>, $<>, $<> > fused_multiply_add($shorthands&&... operands) const volatile noexcept(noexcept(...)) {
    return {*this, std::forward<$shorthands>(operands)...};
  }
};

(int) $int<a>{}.fused_multiply_add($s<b>{}, $s<c>{})

// ...
int main(int, char*[]) /* noexcept */ {
  /* Function call */
  $0(static_cast<void*>(NULL), 1, 2.0);                               // --> void
  std::printf("[]: %p" "\r\n", $1(static_cast<void*>(NULL), 1, 2.0)); // --> void*&&
  std::printf("[]: %i" "\r\n", $2(static_cast<void*>(NULL), 1, 2.0)); // --> int  &&
  std::printf("[]: %f" "\r\n", $3(static_cast<void*>(NULL), 1, 2.0)); // --> float&&
  std::puts("...");

  /* Function cast */
  typedef int (function)(int, ...); // ->> Variadics supported, but the optional arguments get ignored

  #if defined(__circle_lang__) || defined(__clang__)                                                  //
    std::printf("[]: %i"    "\r\n", static_cast<function*>($1)(3));                                   // --> int&&
    std::printf("[]: %4.5s" "\r\n", static_cast<function*>($1) == (function*) $1 ? "true" : "false"); // ->> Conversion operator call
  #else                                                                                               //
    std::printf("[]: %i"    "\r\n", $1.operator function*()(3));                                      // --> int&&
    std::printf("[]: %i"    "\r\n", $1.operator function&()(3));                                      // --> int&&
    std::printf("[]: %4.5s" "\r\n", $1.operator function*() == (function*) $1 ? "true" : "false");    // ->> Conversion operator call
    std::printf("[]: %4.5s" "\r\n", $1.operator function&() == (function&) $1 ? "true" : "false");    // ->> Wary of cast-to-reference
  #endif                                                                                              //
  std::puts("...");

  /* Constructor as function call */
  std::printf("[]: %i" "\r\n", static_cast<int>($<1u>{}    (4.0f))); // ->> Constructor (call), then function call
  std::printf("[]: %i" "\r\n", static_cast<int>($<1u>      (4.0f))); // ->> Undefined behavior a la `*(int*) (void*) &(float&&{...})`
  std::printf("[]: %i" "\r\n", static_cast<int>($<1u, int> (4.0f))); // ->> Defined   behavior a la `(int)  float&&{...}` via `private` `int`  member access
  std::printf("[]: %i" "\r\n", static_cast<int>($<1u, int&>(4.0f))); // ->> Undefined behavior a la `(int&) float&&{...}` via `private` `int&` member access
  std::puts("...");

  /* Constants */
  std::printf("[]: %llu" "\r\n",                                    ($u<5uLL>{})()); // --> unsigned int
  std::printf("[]: %lli" "\r\n", static_cast<signed long long (*)()>($s<-5LL>{})()); // --> signed   int
  std::puts("...");

  /* Function expression */
  // std::printf("[]: %zu" "\r\n", sizeof($expression<$comma, $expression<$self, $<1u> >,        $expression<$self, $<2u> >, $void>));
  // std::printf("[]: %zu" "\r\n", sizeof($expression<$comma, $expression<$self, $object<int> >, $expression<$self, $<2u> >, $void>));
  // std::printf("[]: %1.1s" "\r\n", std::puts&($1)("6"));
  std::puts("...");

  /* Expression */
  // std::puts&($1), std::printf&($1, $2)
  // std::bsearch(&static_cast<int const&>(42), {1, 2, 3, 4, 5}, 5u, sizeof(int), [](void const* a, void const* b) { return *(int*) a < *(int*) b ? -1 : *(int*) a > *(int*) b ? +1 : 0; });
  // std::bsearch(&static_cast<int const&>(42), {1, 2, 3, 4, 5}, 5u, sizeof(int), *$as<int*>($1) < *$as<int*>($2) ? -1 : *$as<int*>($1) > *$as<int*>($2) ? +1 : 0);

  /* ... */
  return EXIT_SUCCESS;
}
