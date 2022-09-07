#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdint.h>
#include <version>

/* ... */
#if defined(__clang__) && false == (defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
# pragma clang diagnostic ignored "-Wunused-const-variable"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__) && false == (defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
# pragma GCC diagnostic ignored "-Wunused-function"
# pragma GCC diagnostic ignored "-Wunused-variable"
#elif defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 177)
# pragma warning(disable: 383)
# pragma warning(disable: 1419)
#endif

/* Trait ->> slightly obfuscated */
template <typename type>
type instanceof() /* noexcept */;

struct null /* final */ {
  template <typename base>
  struct constant /* final */ {
    static base const value = 0;
  };

  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <typename base>                  struct constant<base  (*)(std::size_t)>        final { constexpr static base  (*value)(std::size_t)        = nullptr; };
    template <typename baseA, typename baseB> struct constant<baseA (*)(baseB, std::size_t)> final { constexpr static baseA (*value)(baseB, std::size_t) = nullptr; };
  #elif defined(__cpp_constexpr)
    template <typename base>                  struct constant<base  (*)(std::size_t)>        /* final */ { constexpr static base  (*value)(std::size_t)        = NULL; };
    template <typename baseA, typename baseB> struct constant<baseA (*)(baseB, std::size_t)> /* final */ { constexpr static baseA (*value)(baseB, std::size_t) = NULL; };
  #else
    template <typename base>                  struct constant<base  (*)(std::size_t)>        /* final */ { static base  value(std::size_t const)              /* throw() */ { return *static_cast<base volatile*>(NULL); } };
    template <typename base>                  struct constant<void  (*)(base, std::size_t)>  /* final */ { static void  value(base const, std::size_t const)  /* throw() */ {} };
    template <typename baseA, typename baseB> struct constant<baseA (*)(baseB, std::size_t)> /* final */ { static baseA value(baseB const, std::size_t const) /* throw() */ { return *static_cast<baseA volatile*>(NULL); } };
  #endif

  /* ... */
  template <typename type>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  null(type const) /* noexcept */;
};

namespace {
  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <bool boolean,  bool...>                         struct boolean_and                                  final { static bool const value = boolean; };
    template <bool booleanA, bool booleanB, bool... booleans> struct boolean_and<booleanA, booleanB, booleans...> final { static bool const value = boolean_and<booleanA && booleanB, booleans...>::value; };

    template <std::size_t...>
    struct collection final {};
  #endif

  template <bool, typename, typename = null const volatile> struct conditional;
  template <typename base>                                  struct conditional<false, base, null const volatile> /* final */ {};
  template <typename baseA, typename baseB>                 struct conditional<false, baseA, baseB>              /* final */ { typedef baseB type; };
  template <typename baseA, typename baseB>                 struct conditional<true,  baseA, baseB>              /* final */ { typedef baseA type; };

  template <typename base, base =
    #ifdef __circle_lang__
      0x0
    #else
      null::template constant<base>::value
    #endif
  >
  struct constant /* final */ {
    template <base, base>    struct is_same                     /* final */ { static bool const value = false; };
    template <base argument> struct is_same<argument, argument> /* final */ { static bool const value = true; };

    template <base argument> struct is_null /* final */ { static bool const value = is_same<argument, null::template constant<base>::value>::value; };

    /* ... */
    static base const value;
  };

  template <typename base>
  struct is_enum /* final */ {
    #ifdef __clang__
    # if __has_builtin(__is_enum)
      static bool const value = __is_enum(base);
    # else
      static bool const value = false;
    # endif
    #elif defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
    # ifdef __is_enum
      static bool const value = __is_enum(base);
    # else
      static bool const value = false;
    # endif
    #elif defined(__GNUC__) || defined(_MSC_VER)
      static bool const value = __is_enum(base);
    #else
      private:
        static null (*valueof(uintmax_t const) /* noexcept */)[true + 1];
        static null (*valueof(...) /* noexcept */)[false + 1];

      public:
        static bool const value = sizeof(valueof(instanceof<base>())) == sizeof(null (*)[true + 1]);
    #endif
  };

  template <typename>      struct is_reference        /* final */ { static bool const value = false; };
  template <typename base> struct is_reference<base&> /* final */ { static bool const value = true; };
  #ifdef __cpp_rvalue_references
    template <typename base> struct is_reference<base&&> /* final */ { static bool const value = true; };
  #endif

  template <typename base>                       struct is_scalar                                /* final */ { static bool const value = is_enum<base>::value; };
  template <>                                    struct is_scalar<bool>                          /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<char>                          /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<double>                        /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<float>                         /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<long double>                   /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<signed char>                   /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<signed int>                    /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<signed long>                   /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<signed short>                  /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<unsigned char>                 /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<unsigned int>                  /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<unsigned long>                 /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<unsigned short>                /* final */ { static bool const value = true; };
  template <>                                    struct is_scalar<wchar_t>                       /* final */ { static bool const value = true; };
  template <typename base>                       struct is_scalar<base*>                         /* final */ { static bool const value = true; };
  template <typename base>                       struct is_scalar<base* const>                   /* final */ { static bool const value = true; };
  template <typename base>                       struct is_scalar<base* const volatile>          /* final */ { static bool const value = true; };
  template <typename base>                       struct is_scalar<base* volatile>                /* final */ { static bool const value = true; };
  template <typename base>                       struct is_scalar<base[]>                        /* final */ { static bool const value = is_scalar<base>::value; };
  template <typename base, std::size_t capacity> struct is_scalar<base[capacity]>                /* final */ { static bool const value = is_scalar<base>::value; };
  template <class object, typename base>         struct is_scalar<object base::*>                /* final */ { static bool const value = true; };
  template <class object, typename base>         struct is_scalar<object base::* const>          /* final */ { static bool const value = true; };
  template <class object, typename base>         struct is_scalar<object base::* const volatile> /* final */ { static bool const value = true; };
  template <class object, typename base>         struct is_scalar<object base::* volatile>       /* final */ { static bool const value = true; };
  #ifdef __cpp_char8_t
    template <> struct is_scalar<char8_t> /* final */ { static bool const value = true; };
  #endif
  #ifdef __cpp_unicode_characters
    template <> struct is_scalar<char16_t> /* final */ { static bool const value = true; };
    template <> struct is_scalar<char32_t> /* final */ { static bool const value = true; };
  #endif
  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <> struct is_scalar<signed long long> /* final */ { static bool const value = true; };
  #endif
  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <> struct is_scalar<unsigned long long> /* final */ { static bool const value = true; };
  #endif
  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <> struct is_scalar<std::nullptr_t> /* final */ { static bool const value = true; };
  #endif

  template <typename base> struct is_trivially_copyable /* final */ { static bool const value = is_scalar<base>::value; };

  template <std::size_t valueA, std::size_t valueB = 0u, std::size_t valueC = 0u, std::size_t valueD = 0u, std::size_t valueE = 0u, std::size_t valueF = 0u, std::size_t valueG = 0u, std::size_t valueH = 0u> struct maxof          /* final */ { static std::size_t const value = maxof<(valueA > valueB ? valueA : valueB), valueC, valueD, valueE, valueF, valueG, valueH>::value; };
  template <std::size_t maximum>                                                                                                                                                                               struct maxof<maximum> /* final */ { static std::size_t const value = maximum; };

  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <typename... bases>
    struct pack final {
      template <std::size_t index>
      struct at final {
        private:
          template <std::size_t, class>                                           struct valueof;
          template <typename subbase, typename... subbases>                       struct valueof<0u,       pack<subbase, subbases...> > final { typedef subbase type; };
          template <std::size_t subindex, typename subbase, typename... subbases> struct valueof<subindex, pack<subbase, subbases...> > final { typedef typename valueof<subindex - 1u, pack<subbases...> >::type type; };

        public:
          typedef typename valueof<index, pack<bases...> >::type type;
      };
    };
  #endif

  template <typename base> struct remove_reference        /* final */ { typedef base type; };
  template <typename base> struct remove_reference<base&> /* final */ { typedef base type; };
  #ifdef __cpp_rvalue_references
    template <typename base> struct remove_reference<base&&> /* final */ { typedef base type; };
  #endif

  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <std::size_t value>
    struct sequence final {
      private:
        template <std::size_t...>                                 struct valueof;
        template <std::size_t... subvalues>                       struct valueof<0u,       subvalues...> final { typedef ::collection<0u, subvalues...> type; };
        template <std::size_t subvalue, std::size_t... subvalues> struct valueof<subvalue, subvalues...> final { typedef typename valueof<subvalue - 1u, subvalue, subvalues...>::type type; };

      public:
        typedef typename valueof<value>::type collection;
    };
  #endif

  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    // --> std::forward<...>(...)
    template <typename type> constexpr type&& pass(typename remove_reference<type>::type&  object) noexcept { return static_cast<type&&>(object); }
    template <typename type> constexpr type&& pass(typename remove_reference<type>::type&& object) noexcept { return static_cast<type&&>(object); }
  #endif

  // ... --- CITE (Lapys) -> https://github.com/facebook/folly/blob/main/folly/lang/Launder.h
  #ifdef __cpp_lib_launder
    using std::launder;
  #else
    #if defined(__clang__) || (defined(__GNUC__) && defined(__has_builtin))
    # if __has_builtin(__builtin_launder)
      template <typename type>
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline type* launder(type* const address) /* noexcept */ {
        return __builtin_launder(address);
      }
    # else
      template <typename type>
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline type* launder(type* const address) /* noexcept */ {
        return address;
      }
    # endif
    #elif defined(__GNUC__)
      template <typename type>
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline type* launder(type* address) /* noexcept */ {
        __asm__("" : "+r"(address));
        return address;
      }
    #elif defined(_MSC_VER) && (defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)) && defined(_ReadWriteBarrier)
      template <typename type>
      inline type* launder(type* address) noexcept {
        _ReadWriteBarrier();
        return address;
      }
    #else
      template <typename type>
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline type* launder(type* const address) /* noexcept */ {
        return address;
      }
    #endif

    #ifdef __cpp_constexpr
      template <> constexpr char*                         launder(char* const                         address) /* noexcept */ { return address; }
      template <> constexpr char const*                   launder(char const* const                   address) /* noexcept */ { return address; }
      template <> constexpr char const volatile*          launder(char const volatile* const          address) /* noexcept */ { return address; }
      template <> constexpr char volatile*                launder(char volatile* const                address) /* noexcept */ { return address; }
      template <> constexpr unsigned char*                launder(unsigned char* const                address) /* noexcept */ { return address; }
      template <> constexpr unsigned char const*          launder(unsigned char const* const          address) /* noexcept */ { return address; }
      template <> constexpr unsigned char const volatile* launder(unsigned char const volatile* const address) /* noexcept */ { return address; }
      template <> constexpr unsigned char volatile*       launder(unsigned char volatile* const       address) /* noexcept */ { return address; }

      #ifdef __cpp_lib_byte
        template <> constexpr std::byte*                launder(std::byte* const                address) /* noexcept */ { return address; }
        template <> constexpr std::byte const*          launder(std::byte const* const          address) /* noexcept */ { return address; }
        template <> constexpr std::byte const volatile* launder(std::byte const volatile* const address) /* noexcept */ { return address; }
        template <> constexpr std::byte volatile*       launder(std::byte volatile* const       address) /* noexcept */ { return address; }
      #endif
    #else
      template <> inline char*                         launder(char* const                         address) /* throw() */ { return address; }
      template <> inline char const*                   launder(char const* const                   address) /* throw() */ { return address; }
      template <> inline char const volatile*          launder(char const volatile* const          address) /* throw() */ { return address; }
      template <> inline char volatile*                launder(char volatile* const                address) /* throw() */ { return address; }
      template <> inline unsigned char*                launder(unsigned char* const                address) /* throw() */ { return address; }
      template <> inline unsigned char const*          launder(unsigned char const* const          address) /* throw() */ { return address; }
      template <> inline unsigned char const volatile* launder(unsigned char const volatile* const address) /* throw() */ { return address; }
      template <> inline unsigned char volatile*       launder(unsigned char volatile* const       address) /* throw() */ { return address; }

      #ifdef __cpp_lib_byte
        template <> inline std::byte*                launder(std::byte* const                address) /* throw() */ { return address; }
        template <> inline std::byte const*          launder(std::byte const* const          address) /* throw() */ { return address; }
        template <> inline std::byte const volatile* launder(std::byte const volatile* const address) /* throw() */ { return address; }
        template <> inline std::byte volatile*       launder(std::byte volatile* const       address) /* throw() */ { return address; }
      #endif
    #endif
  #endif

  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    template <std::size_t index, typename type, typename... types>
    constexpr static typename conditional<index == 0u, typename pack<type, types...>::template at<index>::type&&>::type at(type&& object, types&&...) noexcept {
      return static_cast<type&&>(object);
    }

    template <std::size_t index, typename type, typename... types>
    constexpr static typename conditional<index != 0u, typename pack<type, types...>::template at<index>::type&&>::type at(type&&, types&&... objects) noexcept {
      return static_cast<typename pack<type, types...>::template at<index>::type&&>(at<index - 1u>(pass<types>(objects)...));
    }
  #endif
}

/* Constant */
template <typename type>
#ifdef __cpp_constexpr
  constexpr
#endif
type ARRAY_FIXED(std::size_t const) /* noexcept */ {
  return NULL;
}

enum
#if __cplusplus >= 201103L || defined(_MSVC_LANG)
  : uint_fast8_t
#endif
{ ARRAY_REF_INITIAL_COUNT = 31u };

#ifndef ARRAY_SOO_SIZE
# define ARRAY_SOO_SIZE (maxof<128u / CHAR_BIT, sizeof(long double), sizeof(uintmax_t), sizeof(void*), sizeof(void (*)()), sizeof(void (null::*)())>::value - sizeof(std::size_t)) / sizeof(base)
#endif

/* Class */
template <typename base,
  // ->> user-specified automatic-allocated elements, or otherwise type-specific Small-Object-Optimization
  std::size_t = 0u,

  // ->> allow for (compile-time) custom memory management functions
  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t) =
  #ifdef __circle_lang__
    nullptr,
  #else
    null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t)>::value,
  #endif

  void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t) =
  #ifdef __circle_lang__
    nullptr,
  #else
    null::template constant<void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value,
  #endif

  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t) =
  #ifdef __circle_lang__
    nullptr
  #else
    null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value
  #endif
> class Array;

template <>
class Array<null> {
  template <typename base, std::size_t, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t), void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
  friend class Array;

  /* Constant */
  union layout {
    enum {
      automatic              = 0x1u,
      dynamic                = 0x2u,
      small_object_optimized = 0x3u,

      null = 0x0u
    };
  };

  static void *AUTOMATIC[static_cast<std::size_t>(ARRAY_REF_INITIAL_COUNT)], **DYNAMIC; // ->> Register C++98 `Array`s for their dynamically-computed `length`s
  static void *BUFFER;                                                                  // ->> Memory bucket for trivially-copyable types using the default allocators ie: `std::malloc(...)`

  /* Class */
  // ... ->> container for `Array`-of-reference elements
  template <typename base>
  union reference {
    private:
      // ... ->> allow `reference`s exist in `union` containers
      typename remove_reference<base>::type *const value;

    public:
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline reference(base const reference) /* noexcept */ :
        value(&(base&) reference)
      {}

      /* ... */
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline operator base() const /* volatile noexcept */ {
        return (base) *(this -> value);
      }
  };

  // ... --- CITE (Lapys) -> https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/length
  template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t), void (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
  struct length /* final */ {
    private:
      inline Array<base, capacity, allocator, deallocator, reallocator>& get() const /* volatile noexcept */;

      // ...
      inline std::size_t valueof(Array<base, capacity, allocator, deallocator, reallocator>& array) const /* volatile noexcept */ {
        return array.automatic.lengthof() + array.dynamic.lengthof();
      }

    public:
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline length() /* noexcept */ {}

      /* ... */
      inline length& operator =  (std::size_t const length) const /* volatile noexcept */ { this -> get().resize(length); return *this; }
      inline length& operator += (std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) +  length); return *this; }
      inline length& operator -= (std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) -  length); return *this; }
      inline length& operator *= (std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) *  length); return *this; }
      inline length& operator /= (std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) /  length); return *this; }
      inline length& operator &= (std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) &  length); return *this; }
      inline length& operator |= (std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) |  length); return *this; }
      inline length& operator ^= (std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) ^  length); return *this; }
      inline length& operator <<=(std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) << length); return *this; }
      inline length& operator >>=(std::size_t const length) const /* volatile noexcept */ { Array<base, capacity, allocator, deallocator, reallocator> &array = this -> get(); array.resize(this -> valueof(array) >> length); return *this; }

      inline operator std::size_t() const /* volatile noexcept */ { return this -> valueof(this -> get()); }
  };

  // ... ->> intended for range-based `for` loops only
  #ifdef __cpp_range_based_for
    template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t), void (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
    struct iterator /* final */ {
      Array<base, capacity, allocator, deallocator, reallocator> *const array;
      std::size_t                                                       index;

      /* ... */
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline iterator(Array<base, capacity, allocator, deallocator, reallocator>* const array, std::size_t const index) /* noexcept */ :
        array(array),
        index(index)
      {}

      /* ... */
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline decltype(instanceof<Array<base, capacity, allocator, deallocator, reallocator> >() -> at(instanceof<std::size_t>())) operator *() const /* noexcept */ {
        return this -> array -> at(this -> index);
      }

      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline bool operator !=(iterator const& end) const /* noexcept */ {
        return this -> index != end.index;
      }

      #ifdef __clang__
      # pragma clang diagnostic push
      # pragma clang diagnostic ignored "-Wconstexpr-not-const"
      #elif defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
      # pragma warning(disable: 3699)
      #endif
        #ifdef __cpp_constexpr
          constexpr // ->> C++11 `constexpr` injects member function `const`-specification
        #endif
        inline typename conditional<(__cplusplus < 201103L), void, int>::type operator ++() /* noexcept */ {
          // ... ->> undefined behavior if `this` is `const`-qualified
          return ++const_cast<std::size_t&>(this -> index), static_cast<typename conditional<(__cplusplus < 201103L), void, int>::type>(0x0);
        }
      #ifdef __clang__
      # pragma clang diagnostic pop
      #endif
    };
  #endif

  // ... ->> container for dynamically-allocated `Array` elements
  template <typename base>
  union dynamic {
    struct /* final */ {
      typename conditional<is_reference<base>::value, reference<base>, base>::type *elements;
      std::size_t                                                                   length;
    } value;

    /* ... */
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline std::size_t& lengthof() const /* volatile noexcept */ {
      return const_cast<std::size_t&>(this -> value.length);
    }
  };

  // ... ->> container for possible `Array` array-member
  template <typename base, std::size_t capacity, bool = 0u != static_cast<std::size_t>(ARRAY_SOO_SIZE) && (is_reference<base>::value || is_trivially_copyable<base>::value), unsigned = layout::automatic>
  struct automatic {
    static std::size_t const maximum = capacity;
    struct /* final */ {
      mutable typename conditional<is_reference<base>::value, reference<base>, base>::type elements[capacity];
    } value;

    // ...
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline std::size_t lengthof() const volatile /* noexcept */ {
      return capacity;
    }
  };

  template <typename base, std::size_t capacity>
  struct automatic<base, capacity, true, layout::small_object_optimized> {
    static std::size_t const maximum = ARRAY_SOO_SIZE;
    struct /* final */ {
      mutable typename conditional<is_reference<base>::value, reference<base>, base>::type elements[static_cast<std::size_t>(ARRAY_SOO_SIZE)];
      typename conditional<(UINT_FAST64_MAX < static_cast<std::size_t>(ARRAY_SOO_SIZE)),
        std::size_t,
      typename conditional<(UINT_FAST32_MAX < static_cast<std::size_t>(ARRAY_SOO_SIZE)),
        uint_fast64_t,
      typename conditional<(UINT_FAST16_MAX < static_cast<std::size_t>(ARRAY_SOO_SIZE)),
        uint_fast32_t,
      typename conditional<(UINT_FAST8_MAX < static_cast<std::size_t>(ARRAY_SOO_SIZE)),
        uint_fast16_t,
        uint_fast8_t
      >::type>::type>::type>::type length;
    } value;

    // ...
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline std::size_t lengthof() const volatile /* noexcept */ {
      return capacity;
    }
  };

  template <typename base>
  struct automatic<base, 0u, false, layout::automatic> /* final */ {
    static std::size_t const maximum = 0u;
  };

  template <typename base>
  struct automatic<base, 0u, true, layout::automatic> /* final */ : public automatic<base, (ARRAY_SOO_SIZE), true, layout::small_object_optimized> {
    #if __cplusplus >= 201103L || defined(_MSVC_LANG)
      private:
        template <std::size_t... rest, typename... types>
        constexpr automatic(null* const, collection<rest...> const, types&&... elements) noexcept :
          automatic<base, (ARRAY_SOO_SIZE), true, layout::small_object_optimized>::automatic{
            pass<types>(elements)...,
            (static_cast<void>(rest), typename conditional<is_reference<base>::value, reference<base>, base>::type())...,
            sizeof...(elements) // ->> initialize additional `soo_optimized` `automatic::length` member
          }
        {}

        template <typename... types>
        constexpr automatic(null (*const)[false + 1], types&&...) noexcept = delete;

        template <typename... types>
        constexpr automatic(null (*const)[true + 1], types&&... elements) noexcept :
          automatic(static_cast<null*>(NULL), typename sequence<static_cast<std::size_t>(ARRAY_SOO_SIZE) - sizeof...(elements)>::collection{}, pass<types>(elements)...)
        {}

      public:
        template <typename... types>
        constexpr automatic(types&&... elements) noexcept :
          automatic(static_cast<null (*)[(static_cast<std::size_t>(ARRAY_SOO_SIZE) >= sizeof...(elements)) + 1]>(NULL), pass<types>(elements)...)
        {}

        // ...
        constexpr std::size_t& lengthof() const /* volatile */ noexcept {
          return const_cast<std::size_t&>(this -> value.length);
        }
    #else
      inline std::size_t& lengthof() const /* volatile */ throw() {
        // ->> assumed `launder(...)`ed into validity for access
        return const_cast<std::size_t&>(this -> value.length);
      }
    #endif
  };

  // ...
  template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t), unsigned = static_cast<unsigned>(layout::small_object_optimized) & ~(
    static_cast<unsigned>(0u == automatic<base, capacity>::maximum ? static_cast<unsigned>(layout::automatic) : 0x0u) |
    static_cast<unsigned>(constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t)>::template is_same<&ARRAY_FIXED, allocator>::value ? static_cast<unsigned>(layout::dynamic) : 0x0u)
  )>
  struct members /* final */ {
    enum { type = layout::small_object_optimized };

    Array<null>::automatic<base, capacity> automatic;
    Array<null>::dynamic  <base>           dynamic;
  };

  template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t)>
  struct members<base, capacity, allocator, layout::automatic> /* final */ {
    enum { type = layout::automatic };

    #ifdef _MSC_VER
    # pragma warning(disable: 4848)
      [[msvc::no_unique_address]]
    #elif defined(__GNUC__) ? __cplusplus >= 201103L : __has_cpp_attribute(no_unique_address) || (__cplusplus >= 201103L && (defined(__clang__) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)))
      [[no_unique_address]]
    #endif
    Array<null>::automatic<base, capacity> automatic;
  };

  template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t)>
  struct members<base, capacity, allocator, layout::dynamic> /* final */ {
    enum { type = layout::dynamic };
    Array<null>::dynamic<base> dynamic;
  };

  template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t)>
  struct members<base, capacity, allocator, layout::null> /* final */ {
    enum { type = layout::null };
  };

  /* Trait */
  private:
    template <typename base>
    struct is_default /* final */ {
      template <typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*suballocator)(std::size_t), typename = void>
      struct allocator /* final */ {
        #ifdef __circle_lang__
        static bool value = false;
        #else
          static bool const value = constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t)>::template is_null<suballocator>::value;
        #endif
      };

      template <void (*subdeallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename = void>
      struct deallocator /* final */ {
        #ifdef __circle_lang__
          static bool value = false;
        #else
          static bool const value = constant<void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::template is_null<subdeallocator>::value;
        #endif
      };

      template <typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*subreallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename = void>
      struct reallocator /* final */ {
        #ifdef __circle_lang__
          static bool value = false;
        #else
          static bool const value = constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::template is_null<subreallocator>::value;
        #endif
      };

      #ifndef _MSC_VER
        template <typename dummy>
        struct allocator<&ARRAY_FIXED, dummy> /* final */ {
          static bool const value = false;
        };

        template <typename dummy>
        struct allocator<null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t)>::value, dummy> /* final */ {
          static bool const value = true;
        };

        template <typename dummy>
        struct deallocator<null::template constant<void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value, dummy> /* final */ {
          static bool const value = true;
        };

        template <typename dummy>
        struct reallocator<null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value, dummy> /* final */ {
          static bool const value = true;
        };
      #endif
    };
};
  void  *Array<null>::AUTOMATIC[(std::size_t) (ARRAY_REF_INITIAL_COUNT)] = {NULL};
  void  *Array<null>::BUFFER                                             = NULL;
  void **Array<null>::DYNAMIC                                            = NULL;

template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t), void (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
class Array {
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline static typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* allocate(typename conditional<false == Array<null>::template is_default<base>::template allocator<allocator>::value, std::size_t, null>::type const count) /* noexcept(noexcept(suballocator(count))) */ {
    return allocator(count);
  }

  inline static typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* allocate(typename conditional<false != Array<null>::template is_default<base>::template allocator<allocator>::value, std::size_t, null>::type const count) /* noexcept */ {
    // ... ->> allocate zero-bit'ed memory
    return static_cast<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type*>(std::calloc(count, sizeof(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type)));
  }

  // ...
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline static typename conditional<(__cplusplus < 201103L), void, int>::type deallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false == Array<null>::template is_default<base>::template deallocator<deallocator>::value, std::size_t, null>::type const) /* noexcept(noexcept(subdeallocator(address))) */ {
    return subdeallocator(address), static_cast<typename conditional<(__cplusplus < 201103L), void, int>::type>(0x0);
  }

  inline static void deallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false != Array<null>::template is_default<base>::template deallocator<deallocator>::value, std::size_t, null>::type const count) /* noexcept */ {
    // ... ->> scrub the released memory (with zeroes)
    std::fill(const_cast<void volatile*>(static_cast<void const volatile*>(address + 0)), const_cast<void volatile*>(static_cast<void const volatile*>(address + count)), static_cast<unsigned char const&>(0x0u));
    std::free(const_cast<void*>(static_cast<void const volatile*>(address)));
  }

  // ...
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline static typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* reallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false == Array<null>::template is_default<base>::template reallocator<reallocator>::value, std::size_t, null>::type const count) /* noexcept(noexcept(subreallocator(address, count))) */ {
    return subreallocator(address, count);
  }

  template <typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*subreallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
  inline static typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* reallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false != Array<null>::template is_default<base>::template reallocator<reallocator>::value, std::size_t, null>::type const count) /* noexcept */ {
    return static_cast<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type*>(std::realloc(const_cast<void*>(static_cast<void const volatile*>(address)), count * sizeof(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type)));
  }

  /* ... */
  #if __cplusplus >= 201103L || defined(_MSVC_LANG)
    public:
      union {
        Array<null>::members<base, capacity, allocator>                           _;
        Array<null>::length <base, capacity, allocator, deallocator, reallocator> length;
      };

    /* ... */
    private:
      template <std::size_t... indexes, std::size_t... rest, typename... types>
      constexpr Array(null* const, collection<0u, indexes...> const, collection<0u, rest...> const, types&&... elements) noexcept(boolean_and<noexcept(base(instanceof<typename pack<types...>::template at<indexes - 1u>::type&&>()))...>::value && noexcept(instanceof<Array>().add(static_cast<null*>(NULL), instanceof<std::size_t&>(), instanceof<std::size_t&>(), instanceof<typename pack<types...>::template at<(rest + sizeof...(indexes)) - 1u>::type&&>()...))) :
        _{
          {at<indexes - 1u>(pass<types>(elements)...)...},
          {NULL, this -> add(static_cast<null*>(NULL), const_cast<std::size_t&>(static_cast<std::size_t const&>(capacity)), const_cast<std::size_t&>(static_cast<std::size_t const&>(static_cast<std::size_t&&>(0u))), at<(rest + sizeof...(indexes)) - 1u>(pass<types>(elements)...)...) ? sizeof...(rest) : 0u}
        }
      {}

      // ...
      template <typename... types>
      constexpr Array(null (*const)[Array<null>::layout::automatic + 1], types&&... elements) noexcept(boolean_and<noexcept(base(instanceof<types&&>()))...>::value) :
        _{pass<types>(elements)...}
      { static_assert(Array<null>::automatic<base, capacity>::maximum >= sizeof...(elements), "Excessive number of elements upon initializing fixed-sized `Array`"); }

      template <typename... types>
      constexpr Array(null (*const)[Array<null>::layout::dynamic + 1], types&&... elements) noexcept(noexcept(instanceof<Array>().add(static_cast<null*>(NULL), instanceof<std::size_t&>(), instanceof<std::size_t&>(), instanceof<types&&>()...))) :
        _{NULL, this -> add(static_cast<null*>(NULL), const_cast<std::size_t&>(static_cast<std::size_t const&>(capacity)), const_cast<std::size_t&>(static_cast<std::size_t const&>(static_cast<std::size_t&&>(0u))), pass<types>(elements)...) ? sizeof...(elements) : 0u}
      {}

      template <typename... types>
      constexpr Array(null (*const)[Array<null>::layout::small_object_optimized + 1], types&&... elements) noexcept(noexcept(Array(static_cast<null*>(NULL), instanceof<typename sequence<(Array<null>::automatic<base, capacity>::maximum < sizeof...(elements)) ? Array<null>::automatic<base, capacity>::maximum : sizeof...(elements)>::collection>(), instanceof<typename sequence<(Array<null>::automatic<base, capacity>::maximum < sizeof...(elements)) ? sizeof...(elements) - Array<null>::automatic<base, capacity>::maximum : 0u>::collection>(), instanceof<types&&>()...))) :
        Array(
          static_cast<null*>(NULL),
          typename sequence<(Array<null>::automatic<base, capacity>::maximum < sizeof...(elements)) ? Array<null>::automatic<base, capacity>::maximum                       : sizeof...(elements)>::collection{},
          typename sequence<(Array<null>::automatic<base, capacity>::maximum < sizeof...(elements)) ? sizeof...(elements) - Array<null>::automatic<base, capacity>::maximum : 0u>                 ::collection{},
          pass<types>(elements)...
        )
      {}

      template <typename... types>
      constexpr Array(null (*const)[Array<null>::layout::null + 1], types&&... elements) noexcept :
        _{}
      { static_assert(0u != sizeof...(elements), "Expected no elements upon initializing fixed zero-sized `Array`"); }

      /* ... */
      #ifdef __clang__
      # pragma clang diagnostic push
      # pragma clang diagnostic ignored "-Wconstexpr-not-const"
      #endif
        constexpr bool add(null* const, std::size_t&, std::size_t&) noexcept {
          return true;
        }

        template <typename... types>
        constexpr bool add(null* const, std::size_t& automaticLength, std::size_t& dynamicLength, types&&...) noexcept {
          // automaticLength == automatic<base, capacity>::maximum
          return static_cast<void>(automaticLength), static_cast<void>(dynamicLength), true;
        }

        template <typename... types>
        constexpr bool add(null (*const)[Array<null>::layout::automatic + 1], types&&... elements) /* volatile */ noexcept(noexcept(instanceof<Array>().add(static_cast<null*>(NULL), instanceof<std::size_t&>(), instanceof<std::size_t&>(), instanceof<types&&>()...))) {
          return this -> add(static_cast<null*>(NULL), const_cast<std::size_t&>(static_cast<std::size_t const&>(const_cast<Array*>(this) -> _.automatic.lengthof())), const_cast<std::size_t&>(static_cast<std::size_t const&>(static_cast<std::size_t&&>(0u))), pass<types>(elements)...);
        }

        template <typename... types>
        constexpr bool add(null (*const)[Array<null>::layout::dynamic + 1], types&&... elements) /* volatile */ noexcept(noexcept(instanceof<Array>().add(static_cast<null*>(NULL), instanceof<std::size_t&>(), instanceof<std::size_t&>(), instanceof<types&&>()...))) {
          return this -> add(static_cast<null*>(NULL), const_cast<std::size_t&>(static_cast<std::size_t const&>(static_cast<std::size_t&&>(0u))), const_cast<Array*>(this) -> _.dynamic.lengthof(), pass<types>(elements)...);
        }

        template <typename... types>
        constexpr bool add(null (*const)[Array<null>::layout::small_object_optimized + 1], types&&... elements) /* volatile */ noexcept(noexcept(instanceof<Array /* volatile */>().add(static_cast<null*>(NULL), instanceof<std::size_t&>(), instanceof<std::size_t&>(), instanceof<types&&>()...))) {
          return this -> add(static_cast<null*>(NULL), const_cast<std::size_t&>(static_cast<std::size_t const&>(const_cast<Array*>(this) -> _.automatic.lengthof())), const_cast<Array*>(this) -> _.dynamic.lengthof(), pass<types>(elements)...);
        }

        template <typename... types>
        constexpr bool add(null (*const)[Array<null>::layout::null + 1], types&&...) volatile noexcept {
          return false;
        }
      #ifdef __clang__
      # pragma clang diagnostic pop
      #endif

    public:
      template <typename... types>
      constexpr Array(types&&... elements) noexcept(noexcept(Array(static_cast<null (*)[Array<null>::members<base, capacity, allocator>::type]>(NULL), instanceof<types&&>()...))) :
        Array(static_cast<null (*)[Array<null>::members<base, capacity, allocator>::type + 1]>(NULL), pass<types>(elements)...)
      {}

      #if defined(__cpp_constexpr) && __cplusplus >= 202002L
        constexpr
      #endif
      inline ~Array() noexcept = default;

      /* ... */
      #ifdef __clang__
      # pragma clang diagnostic push
      # pragma clang diagnostic ignored "-Wconstexpr-not-const"
      #endif
        constexpr bool add() volatile noexcept {
          return true;
        }

        template <typename... types>
        constexpr bool add(types&&... elements) /* volatile */ noexcept(noexcept(instanceof<Array>().add(static_cast<null (*)[Array<null>::members<base, capacity, allocator>::type + 1]>(NULL), instanceof<types&&>()...))) {
          return this -> add(static_cast<null (*)[Array<null>::members<base, capacity, allocator>::type + 1]>(NULL), pass<types>(elements)...);
        }

        // ...
        constexpr Array<null>::iterator<base, capacity, allocator, deallocator, reallocator> begin() const /* volatile */ noexcept {
          return {const_cast<Array*>(this), 0u};
        }

        // ...
        constexpr Array<null>::iterator<base, capacity, allocator, deallocator, reallocator> end() const /* volatile */ noexcept {
          return {NULL, this -> length};
        }
      #ifdef __clang__
      # pragma clang diagnostic pop
      #endif

      /* ... */
      constexpr base&  operator [](std::size_t const index) const&  /* volatile */ noexcept { return (base&)  this -> at(index); }
      constexpr base&& operator [](std::size_t const index) const&& /* volatile */ noexcept { return (base&&) this -> at(index); }
  #else
    private:
      inline void initiate() throw() {}

    public:
      #ifdef __clang__
      # pragma clang diagnostic push
      # pragma clang diagnostic ignored "-Wmissing-braces"
      # pragma clang diagnostic ignored "-Wmissing-field-initializers"
      #elif defined(__GNUC__) && false == (defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
      # pragma GCC diagnostic push
      # pragma GCC diagnostic ignored "-Wmissing-field-initializers"
      #endif
      Array<null>::members<base, capacity, allocator>                                 _;
      Array<null>::length <base, capacity, allocator, deallocator, reallocator> const length;

      /* ... */
      inline ~Array() throw() {}
  #endif
};

// #if __cplusplus >= 201103L || defined(_MSVC_LANG)
//   template <typename base, std::size_t capacity, void (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
//   class Array<base, capacity, &ARRAY_FIXED, deallocator, reallocator> final : public Array<base, capacity, &ARRAY_FIXED, deallocator, reallocator> {};
// #endif

/* Main */
union string {
  char const *value;
  struct {
    inline operator std::size_t() const {
      for (char const *iterator = launder(reinterpret_cast<string const*>(this)) -> value; ; ++iterator)
      if ('\0' == *iterator) return iterator - launder(reinterpret_cast<string const*>(this)) -> value;
    }
  } length;

  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline string(char const string[]) : value(string) {}

  static string* allocator(std::size_t const) { return NULL; }
  inline operator char const*() const { return this -> value; }
};

int main(int, char*[]) /* noexcept */ {
  // constexpr Array<string>                        A = {"A", "B", "C", "..."};
  // constexpr Array<string, 3u>                    B = {"A", "B", "C", "..."};
  // constexpr Array<string, 3u, string::allocator> C = {"A", "B", "C", "..."};
  // constexpr Array<string, 3u, ARRAY_FIXED>       D = {"A", "B", "C"};

  // static_cast<void>(A);
  // static_cast<void>(B);
  // static_cast<void>(C);
  // static_cast<void>(D);

  std::printf("[string*; std::size_t]           : %lu" "\r\n", static_cast<unsigned long>(sizeof(string*) + sizeof(std::size_t)));
  std::printf("[Array<string>]                  : %lu" "\r\n", static_cast<unsigned long>(sizeof(Array<string>)));
  std::printf("[string[3]; string*; std::size_t]: %lu" "\r\n", static_cast<unsigned long>(sizeof(string[3]) + sizeof(string*) + sizeof(std::size_t)));
  std::printf("[Array<string, 3>]               : %lu" "\r\n", static_cast<unsigned long>(sizeof(Array<string, 3u>)));
  std::printf("[Array<string, 3, ...>]          : %lu" "\r\n", static_cast<unsigned long>(sizeof(Array<string, 3u, string::allocator>)));
  std::printf("[string[3]]                      : %lu" "\r\n", static_cast<unsigned long>(sizeof(string[3])));
  std::printf("[Array<string, 3, ARRAY_FIXED>]  : %lu" "\r\n", static_cast<unsigned long>(sizeof(Array<string, 3u, ARRAY_FIXED>)));

  /* ... */
  return EXIT_SUCCESS;
}
