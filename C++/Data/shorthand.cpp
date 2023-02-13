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
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <version>

/* ... */
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
struct $break;     // ->> terminate    `$for` or `$while` iteration --> $break   [$$]; $break    == $break[$1]
struct $continue;  // ->> skip to next `$for` or `$while` iteration --> $continue[$$]; $continue == $continue[$1]
struct $if;        // ->> evaluates to `$shorthand` if truthy, otherwise `void` (or `$elif` or `$else`) if falsy
struct $label;     // ->> represents "ith" argument with a name (which need not be a string literal)
struct $loop;      // ->> evaluates `$shorthand` multiple times; returns `void`
struct $shorthand; // ->> functor expression; coerce-able to free function types eg: `T (*)(...)`
struct $void;      // ->> specialization test
struct $while;     //
enum   $operation : unsigned char {
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
  $nop,
  $plus,
  $post_decrement,
  $post_increment,
  $pre_decrement,
  $pre_increment,
  $right_shift,
  $subscript,
  $subtract,
  $unequals
};

template <std::size_t, typename = void> // ->> evaluates to the "ith" argument; the only `$shorthand` able to use constructor as function call
struct $;                               // --> sizeof(unsigned char : 0) | sizeof(struct { void* | T; bool; })

template <typename>
struct $as; // ->> evaluates `$shorthand` to `T`

template <typename base, typename std::conditional<std::is_same<$void, typename std::remove_cv<base>::type>::value, std::nullptr_t, base>::type = $nil<typename std::conditional<std::is_same<$void, typename std::remove_cv<base>::type>::value, std::nullptr_t, base>::type>{}()>
struct $constant; // ->> evaluates to constant object (or `$nil` otherwise)

template <std::size_t, std::size_t = 0u>
struct $for;

template <std::size_t>
struct $index; // ->> evaluates to the "ith" `$for` loop's index

#ifdef _MSC_VER
  template <unsigned char, class...>
  struct $expression;
#else
  template <enum $operation, class...>
  struct $expression;
#endif

// ...
using $i = $index<0u>;
using $j = $index<1u>;
using $k = $index<2u>;

template <typename base, base constant>
using $c = $constant<base, constant>;

/* ... */
struct $shorthand {};

// ...
template <typename base, base constant>
struct $expression<$nop, $constant<base, constant> > : public $shorthand {
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

template <std::size_t index>
struct $expression<$nop, $<index> > : public $shorthand {
  friend struct $expression<$nop, $<index + 1u> >;
  template <std::size_t, typename> friend struct $;

  private:
    #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) < 201402L
      typedef std::nullptr_t constvoid;
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
      typedef typename std::conditional<index == 1u, base, typename $expression<$nop, $<index - (index != 0u)> >::template typeat<bases...>::type>::type type;
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
      return static_cast<constvoid>(nullptr);
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

// ...
template <typename base, typename std::conditional<std::is_same<$void, typename std::remove_cv<base>::type>::value, std::nullptr_t, base>::type constant>
struct $constant : public $expression<$nop, $constant<base, constant> > {};

template <>
struct $constant<$void> : public $shorthand {
  #ifdef __cpp_nontype_template_parameter_auto
    template <auto> friend struct $e;
    template <auto> friend struct $f;
    template <auto> friend struct $s;
    template <auto> friend struct $u;
  #endif

  protected:
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
template <std::size_t index, typename base>
struct $ : public $expression<$nop, $<index> > {
  private:
    template <typename subbase, bool = std::is_function<typename std::remove_pointer<typename std::remove_reference<subbase>::type>::type>::value>
    struct cast final {
      #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
        constexpr
      #endif
      inline static subbase valueof() noexcept(false) /* --> throw(std::runtime_error) */ {
        throw std::runtime_error("Shorthand (instantiated with zero arguments) expected cast to function type");
        // ->> `static_assert(...)` preferable, but possibly runtime members are not evaluated at compile-time
        // --> std::unreachable();
      }
    };

    template <typename subbase>
    struct cast<subbase, true> final {
      constexpr static subbase valueof() noexcept(true) {
        return $expression<$nop, $<index> >::template cast<typename std::remove_pointer<typename std::remove_reference<subbase>::type>::type>::value;
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
    inline static typename std::enable_if<false == is_addressable<type>::value, typename std::remove_reference<type>::type*>::type addressof(type&& object) noexcept {
      return const_cast<type*>(reinterpret_cast<type const*>(&reinterpret_cast<unsigned char const&>(static_cast<type const&>(object))));
    }

    template <typename type>
    constexpr static typename std::enable_if<false != is_addressable<type>::value, typename std::remove_reference<type>::type*>::type addressof(type&& object) noexcept {
      return &const_cast<type&>(static_cast<type const&>(object));
    }

    /* ... */
    union {
      struct /* ->> implementation-defined unnamed `struct` with possibly reference-qualified member */ {
        typename std::conditional<std::is_void<base>::value, void /* const volatile */*, base>::type value;

        /* ... */
        template <typename type, typename std::enable_if<false == std::is_void<base>::value && false == std::is_void<type>::value, std::nullptr_t>::type = nullptr>
        constexpr operator type() const noexcept {
          return (type) this -> value;
        }

        template <typename type, typename std::enable_if<false != std::is_void<base>::value && false == std::is_void<type>::value, std::nullptr_t>::type = nullptr>
        inline operator type() const volatile noexcept {
          // --> std::unreachable();
          return reinterpret_cast<typename std::remove_reference<type>::type&>(const_cast<void*&>(this -> value));
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

    template <typename... types, typename std::enable_if<(index > sizeof...(types)), std::nullptr_t>::type = nullptr>
    constexpr $(types&&...) noexcept :
      reference   {NULL},
      instantiated(false)
    { static_assert(0u == sizeof...(types), "Shorthand expected more arguments"); }

    template <typename... types, typename std::enable_if<false == std::is_void<base>::value && (index <= sizeof...(types)), std::nullptr_t>::type = nullptr>
    constexpr $(types&&... arguments) noexcept :
      object      {(base) const_cast<typename std::remove_reference<typename $expression<$nop, $<index> >::template typeat<types&&...>::type>::type&>(static_cast<typename std::remove_reference<typename $expression<$nop, $<index> >::template typeat<types&&...>::type>::type const&>($expression<$nop, $<index> >::invoke(std::forward<types>(arguments)...)))},
      instantiated(true)
    {}

    template <typename... types, typename std::enable_if<false != std::is_void<base>::value && (index <= sizeof...(types)), std::nullptr_t>::type = nullptr>
    constexpr $(types&&... arguments) noexcept :
      reference   {addressof($expression<$nop, $<index> >::invoke(std::forward<types>(arguments)...))},
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
struct $<0u, base> : public $expression<$nop, $<0u> > {
  constexpr $(...) noexcept {}
};

template <std::size_t index> struct $<index, $void>                : public $expression<$nop, $<index> > {};
template <std::size_t index> struct $<index, $void const>          : public $<index, $void> {};
template <std::size_t index> struct $<index, $void const volatile> : public $<index, $void> {};
template <std::size_t index> struct $<index, $void volatile>       : public $<index, $void> {};

template <> struct $<0u, $void>                : public $expression<$nop, $<0u> > {};
template <> struct $<0u, $void const>          : public $<0u, $void> {};
template <> struct $<0u, $void const volatile> : public $<0u, $void> {};
template <> struct $<0u, $void volatile>       : public $<0u, $void> {};

/* ... */
#ifdef __cpp_nontype_template_parameter_auto
  template <auto constant>
  struct $e final : public std::conditional<
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
    struct $f final : public std::conditional<
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
    struct $f final : public std::conditional<(
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
  struct $s final : public std::conditional<
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
  struct $u final : public std::conditional<
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

  /* Expression */
  // std::puts&($1), std::printf&($1, $2)
  // std::bsearch(&static_cast<int const&>(42), {1, 2, 3, 4, 5}, 5u, sizeof(int), [](void const* a, void const* b) { return *(int*) a < *(int*) b ? -1 : *(int*) a > *(int*) b ? +1 : 0; });
  // std::bsearch(&static_cast<int const&>(42), {1, 2, 3, 4, 5}, 5u, sizeof(int), *$as<int*>($1) < *$as<int*>($2) ? -1 : *$as<int*>($1) > *$as<int*>($2) ? +1 : 0);

  /* ... */
  return EXIT_SUCCESS;
}
