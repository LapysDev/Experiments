#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdint.h>
#include <version>

/* ... */
#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 1419)
#endif

/* Trait */
struct null /* final */ {
  template <typename base>
  struct constant {
    static base const value = 0;
  };

  #if __cplusplus >= 201103L
    template <typename base>                    struct constant<base*>                                 /* final */ { constexpr static base *                        value                 = nullptr; };
    template <typename base>                    struct constant<base* const>                           /* final */ { constexpr static base *const                   value                 = nullptr; };
    template <typename base>                    struct constant<base* const volatile>                  /* final */ { constexpr static base *const volatile          value                 = nullptr; };
    template <typename base>                    struct constant<base* volatile>                        /* final */ { constexpr static base *volatile                value                 = nullptr; };
    template <typename base, typename... bases> struct constant<base (*)              (bases...)>      /* final */ { constexpr static base (*                       value)(bases...)      = nullptr; };
    template <typename base, typename... bases> struct constant<base (*)              (bases..., ...)> /* final */ { constexpr static base (*                       value)(bases..., ...) = nullptr; };
    template <typename base, typename... bases> struct constant<base (*const)         (bases...)>      /* final */ { constexpr static base (*const                  value)(bases...)      = nullptr; };
    template <typename base, typename... bases> struct constant<base (*const)         (bases..., ...)> /* final */ { constexpr static base (*const                  value)(bases..., ...) = nullptr; };
    template <typename base, typename... bases> struct constant<base (*const volatile)(bases...)>      /* final */ { constexpr static base (*const volatile         value)(bases...)      = nullptr; };
    template <typename base, typename... bases> struct constant<base (*const volatile)(bases..., ...)> /* final */ { constexpr static base (*const volatile         value)(bases..., ...) = nullptr; };
    template <typename base, typename... bases> struct constant<base (*volatile)      (bases...)>      /* final */ { constexpr static base (*volatile               value)(bases...)      = nullptr; };
    template <typename base, typename... bases> struct constant<base (*volatile)      (bases..., ...)> /* final */ { constexpr static base (*volatile               value)(bases..., ...) = nullptr; };
    template <class object, typename base>      struct constant<base object::*>                        /* final */ { constexpr static base object:: *               value                 = nullptr; };
    template <class object, typename base>      struct constant<base object::* const>                  /* final */ { constexpr static base object:: *const          value                 = nullptr; };
    template <class object, typename base>      struct constant<base object::* const volatile>         /* final */ { constexpr static base object:: *const volatile value                 = nullptr; };
    template <class object, typename base>      struct constant<base object::* volatile>               /* final */ { constexpr static base object:: *volatile       value                 = nullptr; };
  #elif defined(__cpp_constexpr)
    template <typename base>                    struct constant<base*>                                 /* final */ { constexpr static base *                        value                 = NULL; };
    template <typename base>                    struct constant<base* const>                           /* final */ { constexpr static base *const                   value                 = NULL; };
    template <typename base>                    struct constant<base* const volatile>                  /* final */ { constexpr static base *const volatile          value                 = NULL; };
    template <typename base>                    struct constant<base* volatile>                        /* final */ { constexpr static base *volatile                value                 = NULL; };
    template <typename base, typename... bases> struct constant<base (*)              (bases...)>      /* final */ { constexpr static base (*                       value)(bases...)      = NULL; };
    template <typename base, typename... bases> struct constant<base (*)              (bases..., ...)> /* final */ { constexpr static base (*                       value)(bases..., ...) = NULL; };
    template <typename base, typename... bases> struct constant<base (*const)         (bases...)>      /* final */ { constexpr static base (*const                  value)(bases...)      = NULL; };
    template <typename base, typename... bases> struct constant<base (*const)         (bases..., ...)> /* final */ { constexpr static base (*const                  value)(bases..., ...) = NULL; };
    template <typename base, typename... bases> struct constant<base (*const volatile)(bases...)>      /* final */ { constexpr static base (*const volatile         value)(bases...)      = NULL; };
    template <typename base, typename... bases> struct constant<base (*const volatile)(bases..., ...)> /* final */ { constexpr static base (*const volatile         value)(bases..., ...) = NULL; };
    template <typename base, typename... bases> struct constant<base (*volatile)      (bases...)>      /* final */ { constexpr static base (*volatile               value)(bases...)      = NULL; };
    template <typename base, typename... bases> struct constant<base (*volatile)      (bases..., ...)> /* final */ { constexpr static base (*volatile               value)(bases..., ...) = NULL; };
    template <class object, typename base>      struct constant<base object::*>                        /* final */ { constexpr static base object:: *               value                 = NULL; };
    template <class object, typename base>      struct constant<base object::* const>                  /* final */ { constexpr static base object:: *const          value                 = NULL; };
    template <class object, typename base>      struct constant<base object::* const volatile>         /* final */ { constexpr static base object:: *const volatile value                 = NULL; };
    template <class object, typename base>      struct constant<base object::* volatile>               /* final */ { constexpr static base object:: *volatile       value                 = NULL; };
  #else
    template <typename base>
    struct constant<base (*)(std::size_t)> {
      static base value(std::size_t const) /* throw() */;
    };

    template <typename baseA, typename baseB>
    struct constant<baseA (*)(baseB, std::size_t)> {
      static baseA value(baseB const, std::size_t const) /* throw() */;
    };
  #endif

  /* ... */
  template <typename type>
  null(type const) /* noexcept */;
};

// ...
template <typename type>
inline type instanceof(); /* noexcept */

// ...
template <bool, typename, typename = null const volatile>
struct conditional;

template <typename base>
struct conditional<false, base, null const volatile> /* final */ {};

template <typename baseA, typename baseB>
struct conditional<false, baseA, baseB> /* final */ {
  typedef baseB type;
};

template <typename baseA, typename baseB>
struct conditional<true, baseA, baseB> /* final */ {
  typedef baseA type;
};

#if __cplusplus >= 201103L
  template <std::size_t...>
  struct collection final {};

  template <typename... bases>
  struct pack final {
    template <std::size_t index>
    struct at final {
      private:
        template <std::size_t, class>
        struct valueof;

        template <typename subbase, typename... subbases>
        struct valueof<0u, pack<subbase, subbases...> > final {
          typedef subbase type;
        };

        template <std::size_t subindex, typename subbase, typename... subbases>
        struct valueof<subindex, pack<subbase, subbases...> > final {
          typedef typename valueof<subindex - 1u, pack<subbases...> >::type type;
        };

      public:
        typedef typename valueof<index, pack<bases...> >::type type;
    };
  };

  template <std::size_t value>
  struct sequence final {
    private:
      template <std::size_t...>
      struct valueof;

      template <std::size_t... subvalues>
      struct valueof<0u, subvalues...> final {
        typedef ::collection<0u, subvalues...> type;
      };

      template <std::size_t subvalue, std::size_t... subvalues>
      struct valueof<subvalue, subvalues...> final {
        typedef typename valueof<subvalue - 1u, subvalue, subvalues...>::type type;
      };

    public:
      typedef typename valueof<value>::type collection;
  };
#endif

// ...
template <typename base>
struct is_enum /* final */ {
  #if defined(__clang__)
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
      null (*valueof(uintmax_t const) /* noexcept */)[true + 1];
      null (*valueof(...) /* noexcept */)[false + 1];

    public:
      static bool const value = sizeof(valueof(instanceof<base>())) == sizeof(null (*)[true + 1]);
  #endif
};

// ...
template <typename>
struct is_reference /* final */ {
  static bool const value = false;
};

template <typename base>
struct is_reference<base&> /* final */ {
  static bool const value = true;
};

#ifdef __cpp_rvalue_references
  template <typename base>
  struct is_reference<base&&> /* final */ {
    static bool const value = true;
  };
#endif

// ...
template <typename base>
struct is_scalar /* final */ {
  static bool const value = is_enum<base>::value;
};

template <>
struct is_scalar<bool> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<char> /* final */ {
  static bool const value = true;
};

#ifdef __cpp_char8_t
  template <>
  struct is_scalar<char8_t> /* final */ {
    static bool const value = true;
  };
#endif

#ifdef __cpp_unicode_characters
  template <>
  struct is_scalar<char16_t> /* final */ {
    static bool const value = true;
  };

  template <>
  struct is_scalar<char32_t> /* final */ {
    static bool const value = true;
  };
#endif

template <>
struct is_scalar<double> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<float> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<long double> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<signed char> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<signed int> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<signed long> /* final */ {
  static bool const value = true;
};

#if __cplusplus >= 201103L
  template <>
  struct is_scalar<signed long long> /* final */ {
    static bool const value = true;
  };
#endif

template <>
struct is_scalar<signed short> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<unsigned char> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<unsigned int> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<unsigned long> /* final */ {
  static bool const value = true;
};

#if __cplusplus >= 201103L
  template <>
  struct is_scalar<unsigned long long> /* final */ {
    static bool const value = true;
  };
#endif

template <>
struct is_scalar<unsigned short> /* final */ {
  static bool const value = true;
};

template <>
struct is_scalar<wchar_t> /* final */ {
  static bool const value = true;
};

template <typename base>
struct is_scalar<base*> /* final */ {
  static bool const value = true;
};

template <typename base>
struct is_scalar<base* const> /* final */ {
  static bool const value = true;
};

template <typename base>
struct is_scalar<base* const volatile> /* final */ {
  static bool const value = true;
};

template <typename base>
struct is_scalar<base* volatile> /* final */ {
  static bool const value = true;
};

template <typename base>
struct is_scalar<base[]> /* final */ {
  static bool const value = is_scalar<base>::value;
};

template <typename base, std::size_t capacity>
struct is_scalar<base[capacity]> /* final */ {
  static bool const value = is_scalar<base>::value;
};

template <class object, typename base>
struct is_scalar<object base::*> /* final */ {
  static bool const value = true;
};

template <class object, typename base>
struct is_scalar<object base::* const> /* final */ {
  static bool const value = true;
};

template <class object, typename base>
struct is_scalar<object base::* const volatile> /* final */ {
  static bool const value = true;
};

template <class object, typename base>
struct is_scalar<object base::* volatile> /* final */ {
  static bool const value = true;
};

#if __cplusplus >= 201103L
  template <>
  struct is_scalar<std::nullptr_t> /* final */ {
    static bool const value = true;
  };
#endif

// ...
template <typename>
struct is_trivially_copyable /* final */ {
  static bool const value = false;
};

// ...
template <std::size_t valueA, std::size_t valueB = 0u, std::size_t valueC = 0u, std::size_t valueD = 0u, std::size_t valueE = 0u, std::size_t valueF = 0u, std::size_t valueG = 0u, std::size_t valueH = 0u>
struct maxof /* final */ {
  static std::size_t const value = maxof<(valueA > valueB ? valueA : valueB), valueC, valueD, valueE, valueF, valueG, valueH>::value;
};

template <std::size_t maximum>
struct maxof<maximum, 0u> /* final */ {
  static std::size_t const value = maximum;
};

// ...
template <typename base>
struct remove_reference /* final */ {
  typedef base type;
};

template <typename base>
struct remove_reference<base&> /* final */ {
  typedef base type;
};

#ifdef __cpp_rvalue_references
  template <typename base>
  struct remove_reference<base&&> /* final */ {
    typedef base type;
  };
#endif

/* ... */
#if __cplusplus >= 201103L
  template <typename type>
  constexpr type&& pass(typename remove_reference<type>::type& object) noexcept {
    return static_cast<type&&>(object);
  }

  template <typename type>
  constexpr type&& pass(typename remove_reference<type>::type&& object) noexcept {
    return static_cast<type&&>(object);
  }
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

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline char* launder(char* const address) /* noexcept */ {
    return address;
  }

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline char const* launder(char const* const address) /* noexcept */ {
    return address;
  }

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline char const volatile* launder(char const volatile* const address) /* noexcept */ {
    return address;
  }

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline char volatile* launder(char volatile* const address) /* noexcept */ {
    return address;
  }

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline unsigned char* launder(unsigned char* const address) /* noexcept */ {
    return address;
  }

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline unsigned char const* launder(unsigned char const* const address) /* noexcept */ {
    return address;
  }

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline unsigned char const volatile* launder(unsigned char const volatile* const address) /* noexcept */ {
    return address;
  }

  template <>
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline unsigned char volatile* launder(unsigned char volatile* const address) /* noexcept */ {
    return address;
  }

  #ifdef __cpp_lib_byte
    template <>
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline std::byte* launder(std::byte* const address) /* noexcept */ {
      return address;
    }

    template <>
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline std::byte const* launder(std::byte const* const address) /* noexcept */ {
      return address;
    }

    template <>
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline std::byte const volatile* launder(std::byte const volatile* const address) /* noexcept */ {
      return address;
    }

    template <>
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline std::byte volatile* launder(std::byte volatile* const address) /* noexcept */ {
      return address;
    }
  #endif
#endif

// ...
#if __cplusplus >= 201103L
  template <std::size_t index, typename type, typename... types>
  constexpr static typename conditional<index == 0u, typename pack<type, types...>::template at<index>::type&&>::type at(type&& object, types&&...) noexcept {
    return static_cast<type&&>(object);
  }

  template <std::size_t index, typename type, typename... types>
  constexpr static typename conditional<index != 0u, typename pack<type, types...>::template at<index>::type&&>::type at(type&&, types&&... objects) noexcept {
    return static_cast<typename pack<type, types...>::template at<index>::type&&>(at<index - 1u>(pass<types>(objects)...));
  }
#endif

/* Constant */
enum
#if __cplusplus >= 201103L
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
  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t)
  = null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t)>::value,

  void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)
  = null::template constant<void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value,

  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)
  = null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value
> class Array;

template <>
class Array<null> {
  template <typename base, std::size_t, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t), void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
  friend class Array;

  private:
    /* ... ->> container for "array-of-reference" elements */
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

        // ...
        #ifdef __cpp_constexpr
          constexpr
        #endif
        inline operator base() const /* volatile noexcept */ {
          return (base) *(this -> value);
        }
    };

    // ...
    template <class Array>
    struct length /* final */ {
      private:
        inline Array& get() const /* volatile noexcept */;

        // ...
        inline std::size_t valueof(Array& array) const /* volatile noexcept */ {
          return array.automatic.lengthof() + array.dynamic.lengthof();
        }

      public:
        inline length& operator =  (std::size_t const length) const /* volatile noexcept */ { this -> get().resize(length); return *this; }
        inline length& operator += (std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) +  length); return *this; }
        inline length& operator -= (std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) -  length); return *this; }
        inline length& operator *= (std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) *  length); return *this; }
        inline length& operator /= (std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) /  length); return *this; }
        inline length& operator &= (std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) &  length); return *this; }
        inline length& operator |= (std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) |  length); return *this; }
        inline length& operator ^= (std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) ^  length); return *this; }
        inline length& operator <<=(std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) << length); return *this; }
        inline length& operator >>=(std::size_t const length) const /* volatile noexcept */ { Array &array = this -> get(); array.resize(this -> valueof(array) >> length); return *this; }

        // ...
        inline operator std::size_t() const /* volatile noexcept */ { return this -> valueof(this -> get()); }
    };

    // ... ->> intended for range-based `for` loops only
    #ifdef __cpp_range_based_for
      template <class Array>
      struct iterator /* final */ {
        Array *const array;
        std::size_t  index;

        /* ... */
        #ifdef __cpp_constexpr
          constexpr
        #endif
        inline iterator(Array* const array, std::size_t const index) /* noexcept */ :
          array(array),
          index(index)
        {}

        /* ... */
        #ifdef __cpp_constexpr
          constexpr
        #endif
        inline decltype(instanceof<Array>() -> at(instanceof<std::size_t>())) operator *() const /* noexcept */ {
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
      inline std::size_t lengthof() const /* volatile noexcept */ {
        return this -> length;
      }
    };

    // ... ->> container for possible `Array` array-member
    template <typename base, std::size_t capacity, bool referrable = is_reference<base>::value, bool = is_scalar<base>::value || is_trivially_copyable<base>::value, bool = 0u != (ARRAY_SOO_SIZE), bool soo_optimized = false>
    struct automatic {
      static std::size_t const maximum = capacity;

      private:
        template <bool, typename>
        struct submembers;

        template <typename dummy>
        struct submembers<false, dummy> /* final */ {
          typename conditional<referrable, reference<base>, base>::type mutable elements[capacity];
        };

        template <typename dummy>
        struct submembers<true, dummy> /* final */ {
          typename conditional<referrable, reference<base>, base>::type mutable elements[capacity];
          typename conditional<(CHAR_BIT * sizeof(capacity) > 64u),
            std::size_t,
          typename conditional<(CHAR_BIT * sizeof(capacity) > 32u),
            uint_fast64_t,
          typename conditional<(CHAR_BIT * sizeof(capacity) > 16u),
            uint_fast32_t,
          typename conditional<(CHAR_BIT * sizeof(capacity) > 8u),
            uint_fast16_t,
            uint_fast8_t
          >::type>::type>::type>::type length;
        };

      public:
        submembers<soo_optimized, void> value;

        // ...
        #ifdef __cpp_constexpr
          constexpr
        #endif
        inline std::size_t lengthof() const volatile /* noexcept */ {
          return capacity;
        }
    };

    template <typename base, bool referrable, bool trivial>
    struct automatic<base, 0u, referrable, trivial, true, false> /* final */ : public automatic<base, (ARRAY_SOO_SIZE), referrable, trivial, true, true> {
      #if __cplusplus >= 201103L
        private:
          template <std::size_t... rest, typename... types>
          constexpr automatic(null* const, collection<rest...> const, types&&... elements) noexcept :
            automatic<base, (ARRAY_SOO_SIZE), referrable, trivial, true>::automatic{
              pass<types>(elements)...,
              (static_cast<void>(rest), typename conditional<referrable, reference<base>, base>::type())...,
              sizeof...(elements) // ->> initialize additional `soo_optimized` `automatic::length` member
            }
          {}

          template <typename... types>
          constexpr automatic(null (*const)[false + 1], types&&...) noexcept = delete;

          template <typename... types>
          constexpr automatic(null (*const)[true + 1], types&&... elements) noexcept :
            automatic(static_cast<null*>(NULL), typename sequence<(ARRAY_SOO_SIZE) - sizeof...(elements)>::collection{}, pass<types>(elements)...)
          {}

        public:
          template <typename... types>
          constexpr automatic(types&&... elements) noexcept :
            automatic(static_cast<null (*)[((ARRAY_SOO_SIZE) >= sizeof...(elements)) + 1]>(NULL), pass<types>(elements)...)
          {}

          // ...
          constexpr std::size_t lengthof() const /* volatile */ noexcept {
            return this -> value.length;
          }
      #else
        inline std::size_t lengthof() const /* volatile */ throw() {
          // ->> assumed `launder(...)`ed into validity for access
          return this -> value.length;
        }
      #endif
    };

    template <typename base>
    struct automatic<base, 0u, false, false, false, false> /* final */ {
      static std::size_t const maximum = 0u;
    };

    template <typename base>
    struct automatic<base, 0u, false, false, true, false> /* final */ {
      static std::size_t const maximum = 0u;
    };

    // ...
    template <class>
    struct members;

    template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t), void (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
    struct members<Array<base, capacity, allocator, deallocator, reallocator> > /* final */ {
      #ifdef _MSC_VER
      # pragma warning(disable: 4848)
        [[msvc::no_unique_address]]
      #elif defined(__GNUC__) ? __cplusplus >= 201103L : __has_cpp_attribute(no_unique_address) || (__cplusplus >= 201103L && (defined(__clang__) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)))
        [[no_unique_address]]
      #endif
      Array<null>::automatic<base, capacity> automatic;
      Array<null>::dynamic  <base>           dynamic;
    };

    /* ... */
    static void *AUTOMATIC[(std::size_t) (ARRAY_REF_INITIAL_COUNT)], **DYNAMIC; // ->> Register C++98 `Array`s for their dynamically-computed `length`s
    static void *BUFFER;                                                        // ->> Memory bucket for trivially-copyable types using the default allocators ie: `std::malloc(...)`
};
  void  *Array<null>::AUTOMATIC[(std::size_t) (ARRAY_REF_INITIAL_COUNT)] = {NULL};
  void  *Array<null>::BUFFER                                             = NULL;
  void **Array<null>::DYNAMIC                                            = NULL;

template <typename base, std::size_t capacity, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*allocator)(std::size_t), void (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
class Array /* final */ {
  template <typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t), typename = void>
  struct is_default_allocator /* final */ {
    static bool const value = false;
  };

  template <typename dummy>
  struct is_default_allocator<null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(std::size_t)>::value, dummy> /* final */ {
    static bool const value = true;
  };

  // ...
  template <void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename = void>
  struct is_default_deallocator /* final */ {
    static bool const value = false;
  };

  template <typename dummy>
  struct is_default_deallocator<null::template constant<void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value, dummy> /* final */ {
    static bool const value = true;
  };

  // ...
  template <typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t), typename = void>
  struct is_default_reallocator /* final */ {
    static bool const value = false;
  };

  template <typename dummy>
  struct is_default_reallocator<null::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>::value> /* final */ {
    static bool const value = true;
  };

  /* ... */
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline static typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* allocate(typename conditional<false == is_default_allocator<allocator>::value, std::size_t, null>::type const count) /* noexcept(noexcept(suballocator(count))) */ {
    return allocator(count);
  }

  inline static typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* allocate(typename conditional<false != is_default_allocator<allocator>::value, std::size_t, null>::type const count) /* noexcept */ {
    // ... ->> allocate zero-bit'ed memory
    return static_cast<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type*>(std::calloc(count, sizeof(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type)));
  }

  // ...
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline static typename conditional<(__cplusplus < 201103L), void, int>::type deallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false == is_default_deallocator<deallocator>::value, std::size_t, null>::type const) /* noexcept(noexcept(subdeallocator(address))) */ {
    return subdeallocator(address), static_cast<typename conditional<(__cplusplus < 201103L), void, int>::type>(0x0);
  }

  inline void deallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false != is_default_deallocator<deallocator>::value, std::size_t, null>::type const count) /* noexcept */ {
    // ... ->> scrub the released memory (with zeroes)
    std::fill(const_cast<void volatile*>(static_cast<void const volatile*>(address + 0)), const_cast<void volatile*>(static_cast<void const volatile*>(address + count)), static_cast<unsigned char const&>(0x0u));
    std::free(const_cast<void*>(static_cast<void const volatile*>(address)));
  }

  // ...
  #ifdef __cpp_constexpr
    constexpr
  #endif
  inline static typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* reallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false == is_default_reallocator<reallocator>::value, std::size_t, null>::type const count) /* noexcept(noexcept(subreallocator(address, count))) */ {
    return subreallocator(address, count);
  }

  template <typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* (*subreallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type[], std::size_t)>
  inline typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type* reallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type address[], typename conditional<false != is_default_reallocator<reallocator>::value, std::size_t, null>::type const count) /* noexcept */ {
    return static_cast<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type*>(std::realloc(const_cast<void*>(static_cast<void const volatile*>(address)), count * sizeof(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, base>::type)));
  }

  /* ... */
  #if __cplusplus >= 201103L
    public:
      union {
        Array<null>::members<Array> _;
        Array<null>::length <Array> const length;
      };

    /* ... */
    private:
      template <typename... types>
      constexpr Array(null (*const)[false + 1], types&&...) noexcept {}

      template <typename... types>
      constexpr Array(null (*const)[true + 1], types&&...) noexcept {}

    public:
      template <typename... types>
      constexpr Array(types&&... /*elements*/) noexcept //:
        // Array<base, capacity, allocator, deallocator, reallocator>::Array(static_cast<null (*)[automatic<base, capacity>::maximum >= sizeof...(elements)]>(NULL), pass<types>(elements)...)
      {}

      inline ~Array() noexcept {}

      /* ... */
      constexpr Array<null>::iterator<Array> begin() const /* volatile */ noexcept {
        return {const_cast<Array<base, capacity>*>(this), 0u};
      }

      // ...
      constexpr Array<null>::iterator<Array> end() const /* volatile */ noexcept {
        return {NULL, this -> length};
      }

      /* ... */
      constexpr base&  operator [](std::size_t const index) const&  /* volatile */ noexcept { return (base&)  this -> at(index); }
      constexpr base&& operator [](std::size_t const index) const&& /* volatile */ noexcept { return (base&&) this -> at(index); }
  #else
    private:
      inline void initiate() throw() {}

    public:
      #if defined(__clang__)
      # pragma clang diagnostic push
      # pragma clang diagnostic ignored "-Wmissing-braces"
      # pragma clang diagnostic ignored "-Wmissing-field-initializers"
      #elif defined(__GNUC__) && false == (defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
      # pragma GCC diagnostic push
      # pragma GCC diagnostic ignored "-Wmissing-field-initializers"
      #endif
      Array<null>::members<Array> _;
      Array<null>::length <Array> length;

      /* ... */
      inline ~Array() throw() {}
  #endif
};

/* Main */
#include <string>

int main(int, char*[]) /* noexcept */ {
  Array<std::string, 3u> strings = {"A", "B", "C"};
  static_cast<void>(strings);
}
