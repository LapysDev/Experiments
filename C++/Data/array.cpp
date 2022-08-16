#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdint.h>
#include <version>

/* ... */
template <typename = void>
struct null /* final */ {
  template <typename base>
  struct constant /* final */ {
    #ifdef __cpp_constexpr
      constexpr
    #endif
    static base const value = 0;
  };

  template <typename base>
  struct constant<base*> /* final */ {
    static base const value = NULL;
  };
};

// ...
template <bool, typename, typename = null<> >
struct conditional;

template <typename base>
struct conditional<false, base, null<> > /* final */ {};

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
        typedef collection<0u, subvalues...> type;
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
    static bool const value = false;
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

template <>
struct is_scalar<std::nullptr_t> /* final */ {
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

// ...
#ifdef __cpp_lib_launder
  using std::launder;
#else
  template <typename type>
  inline type* launder(type* const address) noexcept {
    return address;
  }
#endif

/* Class */
#ifndef ARRAY_REF_INITIAL_COUNT
# define ARRAY_REF_INITIAL_COUNT 31u
#endif

template <typename base,
  // ->> user-defined automatic-allocated elements, or otherwise type-specific Small-Object-Optimization
  std::size_t = 0u,

  // ->> allow for (compile-time) custom memory management functions
  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*)(std::size_t)
  = null<>::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*)(std::size_t)>::value,

  void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*)
  = null<>::template constant<void (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*)>::value,

  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*, std::size_t)
  = null<>::template constant<typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*, std::size_t)>::value,

  // ->> internal or user-facing namespace
  bool = true
> class Array;

template <
  typename    base,
  std::size_t capacity,
  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*allocator)  (std::size_t),
  void                                                                                                                                  (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type[]),
  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type[], std::size_t)
> class Array<base, capacity, allocator, deallocator, reallocator, false> {
  protected:
    template <typename, std::size_t> union  automatic; // ->> container for possible `Array` array-member
    template <typename, std::size_t> union  dynamic;   // ->> container for dynamically-allocated `Array` elements
    template <typename>              struct reference; // ->> wraps references as elements of `Array`; allows `Array` array-members consist of reference-qualified element types

    /* ... */
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline static typename conditional<NULL != allocator, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*, null<> >::type allocate(std::size_t const count) /* noexcept(noexcept(allocator(count))) */ {
      return allocator(count);
    }

    inline static typename conditional<NULL == allocator, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*, null<> >::type allocate(std::size_t const count) /* noexcept */ {
      return static_cast<base*>(std::calloc(count, sizeof(base)));
    }

    // ...
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline static void deallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type address[], std::size_t const) /* noexcept(noexcept(deallocator(address))) */ {
      deallocator(address);
    }

    inline static void deallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type address[], std::size_t const count) /* noexcept */ {
      // ... ->> scrub the released memory (with zeroes)
      std::fill(const_cast<void volatile*>(static_cast<void const volatile*>(address + 0)), const_cast<void volatile*>(static_cast<void const volatile*>(address + count)), static_cast<unsigned char const&>(0x0u));
      std::free(const_cast<void*>(static_cast<void const volatile*>(address)));
    }

    // ...
    #ifdef __cpp_constexpr
      constexpr
    #endif
    inline static typename conditional<NULL != reallocator, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*, null<> >::type reallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type address[], std::size_t const count) /* noexcept(noexcept(reallocator(address, count))) */ {
      return reallocator(address, count);
    }

    inline static typename conditional<NULL == reallocator, typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type*, null<> >::type reallocate(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type address[], std::size_t const count) /* noexcept */ {
      return static_cast<base*>(std::realloc(const_cast<void*>(static_cast<void const volatile*>(address)), count * sizeof(base)));
    }

    /* ... */
    template <typename base, std::size_t capacity, bool = is_scalar<base>::value || is_trivially_copyable<base>::value>
    struct automatic /* final */ {
      struct /* final */ {
        // ->> allow modification of non-`const`-qualified `base`s through a `const`-qualified `Array` (through `launder(...)`ing)
        typename conditional<is_reference<base>::value, reference<base>, base>::type         elements  [capacity];
        typename conditional<is_reference<base>::value, reference<base>, base>::type mutable modifiable[capacity];
      } value;

      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline std::size_t lengthof() const /* volatile noexcept */ {
        return capacity;
      }
    };

    template <typename base>
    struct automatic<base, 0u, false> /* final */ {};

    #if __cplusplus >= 201103L
      template <typename base>
      struct automatic<base, 0u, true> final {
        struct /* final */ {
          // ->> allow modification of non-`const`-qualified `base`s through a `const`-qualified `Array` (through `launder(...)`ing)
          union {
            /* UPDATE: -sizeof(std::size_t) */
            base         elements  [maxof<128u / CHAR_BIT, sizeof(long double), sizeof(uintmax_t), sizeof(void*), sizeof(void (*)()), sizeof(void (null<>::*)())>::value - (sizeof(std::size_t) / sizeof(base))];
            base mutable modifiable[maxof<128u / CHAR_BIT, sizeof(long double), sizeof(uintmax_t), sizeof(void*), sizeof(void (*)()), sizeof(void (null<>::*)())>::value - (sizeof(std::size_t) / sizeof(base))];
          };

          std::size_t  length;
        } value;

        /* ... */
        template <typename... types>
        constexpr automatic(types&&... elements) noexcept :
          value{{pass<types>(elements)...}, sizeof...(elements)}
        {}

        /* ... */
        constexpr std::size_t lengthof() const /* volatile */ noexcept {
          return this -> value.length;
        }
      };
    #else
      template <typename base>
      struct automatic<base, 0u, true> /* final */ {
        private:
          struct initializer /* final */ { base mutable elements[maxof<128u / CHAR_BIT, sizeof(long double), sizeof(uintmax_t), sizeof(void*), sizeof(void (*)()), sizeof(void (null<>::*)())>::value]; };
          struct members     /* final */ { base mutable elements[maxof<128u / CHAR_BIT, sizeof(long double), sizeof(uintmax_t), sizeof(void*), sizeof(void (*)()), sizeof(void (null<>::*)())>::value]; std::size_t length; };

        public:
          union {
            initializer _;
            members     value;
          };

          /* ... */
          inline std::size_t lengthof() const /* volatile */ throw() {
            return this -> value.length;
          }
      };
    #endif

    // ...
    template <typename base, std::size_t capacity>
    union dynamic {
      struct /* final */ {
        typename conditional<is_reference<base>::value, reference<base>, base>::type *elements;
      } value;

      /* ... */
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline std::size_t lengthof() const /* volatile noexcept */ {
        return NULL != this -> value.elements ? *launder(reinterpret_cast<std::size_t*>(this -> value.elements)) : 0u;
      }
    };

    // ... ->> for range-based `for` loops
    #ifdef __cpp_range_based_for
      template <typename base, std::size_t capacity>
      struct iterator /* final */ {
        Array<base, capacity> *const array;
        std::size_t                  index;

        /* ... */
        #ifdef __cpp_constexpr
          constexpr
        #endif
        inline base& operator *() const /* noexcept */ {
          return this -> array -> at(this -> index);
        }

        #ifdef __cpp_constexpr
          constexpr // ->> C++11 `constexpr` injects member function `const`-specification
        #endif
        inline void operator ++() /* noexcept */ {
          // ... ->> undefined behavior if `this` is `const`-qualified
          ++const_cast<std::size_t&>(this -> index);
        }

        #ifdef __cpp_constexpr
          constexpr
        #endif
        inline bool operator !=(iterator const& end) const /* noexcept */ {
          return this -> index != end.index;
        }
      };
    #endif

    // ...
    template <typename base>
    struct reference /* final */ {
      base value;

      /* ... */
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline reference(base value) /* noexcept */ :
        value((base) value)
      {}

      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline reference(reference const& reference) /* noexcept */ :
        value((base) reference.value)
      {}

      /* ... */
      #ifdef __cpp_constexpr
        constexpr
      #endif
      inline operator base() const /* noexcept */ {
        return (base) this -> value;
      }
    };

    /* ... */
    static void      *AUTOMATIC[(std::size_t) (ARRAY_REF_INITIAL_COUNT)], **DYNAMIC; // ->> Register C++98 `Array`s for their dynamically-computed `length`s
    static void      *BUFFER;                                                        // ->> Memory bucket for trivially-copyable types using the default allocators ie: `std::malloc`, `std::realloc`, ``
    static bool const CAN_BUFFER = is_scalar<base>::value || is_trivially_copyable<base>::value;
};

template <
  typename    base,
  std::size_t capacity,
  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*allocator)  (std::size_t),
  void                                                                                                                                  (*deallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type[]),
  typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type* (*reallocator)(typename conditional<is_reference<base>::value, typename remove_reference<base>::type*, typename remove_reference<base>::type>::type[], std::size_t)
>
#if __cplusplus >= 201103L
  class Array : public Array<base, capacity, allocator, deallocator, reallocator, true> {
    private:
      automatic<base, capacity> automatic;
      dynamic  <base, capacity> dynamic;

    public:
      union length {
        Array *array;

        /* ... */
        constexpr length& operator =  (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(length); return *this; }
        constexpr length& operator += (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value +  length); return *this; }
        constexpr length& operator -= (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value -  length); return *this; }
        constexpr length& operator *= (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value *  length); return *this; }
        constexpr length& operator /= (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value /  length); return *this; }
        constexpr length& operator &= (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value &  length); return *this; }
        constexpr length& operator |= (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value |  length); return *this; }
        constexpr length& operator ^= (std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value ^  length); return *this; }
        constexpr length& operator <<=(std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value << length); return *this; }
        constexpr length& operator >>=(std::size_t const length) const /* volatile */ noexcept { this -> array -> resize(this -> value >> length); return *this; }

        constexpr operator std::size_t() const /* volatile */ noexcept { return this -> array.automatic.lengthof() + this -> array.dynamic.lengthof(); }
      } const length;

    /* ... */
    private:
      template <std::size_t... indexesA, std::size_t... indexesB, typename... types>
      constexpr Array(collection<0u, indexesA...> const, collection<0u, indexesB...> const, types&&... elements) noexcept :
        automatic{at<indexesA - 1u>(pass<types>(elements))...},
        dynamic  {NULL},
        length   {this -> add(at<capacity + (indexesB - 1u)>(pass<types>(elements))...), this}
      { /* ->> C++11 `constexpr` constructor body must be empty */ }

      template <typename... types>
      constexpr Array(bool (*const)[true + 1], types&&... elements) noexcept :
        Array<base, capacity>::Array(
          typename sequence<capacity>                      ::collection{},
          typename sequence<sizeof...(elements) - capacity>::collection{},
          pass<types>(elements)...
        )
      {}

      template <typename... types>
      constexpr Array(bool (*const)[false + 1], types&&... elements) noexcept :
        automatic{pass<types>(elements)...},
        dynamic  {NULL},
        length   {this}
      {}

      /* ... */
      inline bool grow(std::size_t count) /* volatile */ noexcept {
        typedef typename conditional<is_reference<base>::value, reference<base>, base>::type type;
        void *allocation;

        // ...
        if (NULL == this -> dynamic.value) {
          if (SIZE_MAX == capacity) return false;
          allocation = allocator(sizeof(std::size_t) + sizeof(std::size_t) + alignof(type) + (count * sizeof(type)));

          if (NULL == allocation) return false;
          ::new (allocation) std::size_t(0u);
          ::new (allocation) std::size_t(count);
        }

        else if (SIZE_MAX - capacity < count)
          return false;

        else for (std::size_t (&metadata)[2] = *launder(reinterpret_cast<std::size_t (*)[2]>(+(this -> dynamic))); metadata[1] < count + metadata[0]; ) {
          /* constexpr */ void* (*const function)(void*, std::size_t) = reallocator;

          // ... ->> reallocate memory for the dynamically-allocated elements
          count += *metadata;

          if (NULL != function && (allocator == &std::malloc) == (function == &std::realloc)) {
            allocation = reallocator((void*) this -> dynamic, sizeof(std::size_t[2]) + alignof(type) + (count * sizeof(type)));
            if (NULL != allocation) break;
          }

          // ... ->> "transfer" all dynamically-allocated elements to a more fitting memory region (hope copying/ destructing is cost-effective)
          allocation = allocator(sizeof(std::size_t[2]) + alignof(type) + ((capacity + count) * sizeof(type)));
          if (NULL == allocation) return false;

          for (unsigned char *element = reinterpret_cast<unsigned char*>(::new (allocation) std::size_t[2] {*metadata, capacity + count} + 2); ; ++element)
          if (0u == (element - static_cast<unsigned char*>(allocation)) % alignof(type)) {
            count           = *metadata;
            this -> dynamic = reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(+(this -> dynamic)) + (element - static_cast<unsigned char*>(allocation)));

            for (; count--; ++(this -> dynamic), element += sizeof(type)) {
              ::new (element) type(*launder(+(this -> dynamic)));
              this -> dynamic -> ~type();
            }

            // ... ->> near-consistently apply the "transfer" to the automatically-allocated elements, as well
            deallocator((void*) this -> dynamic);
            this -> dynamic = this -> automatic;

            for (count = capacity; count--; ++(this -> dynamic), element += sizeof(type)) {
              ::new (element) type(*(this -> dynamic));
              this -> dynamic -> ~type();
            }

            // ...
            this -> dynamic = this -> automatic;
            element        -= capacity * sizeof(type);

            for (count = capacity; count--; ++(this -> dynamic), element += sizeof(type)) {
              ::new (this -> dynamic) type(*launder(reinterpret_cast<type*>(element)));
              launder(reinterpret_cast<type*>(element)) -> ~type();
            }

            break;
          }

          break;
        }

        // ...
        this -> dynamic = static_cast<type*>(allocation);
        return true;
      }

      // ...
      constexpr bool push(typename conditional<is_reference<base>::value, reference<base>, base>::type[], std::size_t&) /* volatile */ noexcept {
        return true;
      }

      template <typename type, typename... types>
      constexpr bool push(typename conditional<is_reference<base>::value, reference<base>, base>::type dynamic[], std::size_t& length, type&& element, types&&... elements) /* volatile */ noexcept {
        return this -> push(::new (dynamic) typename conditional<is_reference<base>::value, reference<base>, base>::type(pass<type>(element)) + 1, ++length, pass<types>(elements)...);
      }

    public:
      template <typename... types>
      constexpr Array(types&&... elements) noexcept :
        Array<base, capacity>::Array(
          static_cast<bool (*)[(sizeof...(elements) > capacity) + 1]>(NULL),
          pass<types>(elements)...
        )
      {}

      /* constexpr */ inline ~Array() noexcept {
        if (NULL != this -> dynamic)
        deallocator(this -> dynamic);
      }

      /* ... */
      constexpr bool add() const /* volatile */ noexcept {
        return true;
      }

      template <typename... types>
      inline bool add(types&&... elements) /* volatile */ noexcept {
        if (this -> grow(sizeof...(elements))) {
          std::size_t (&metadata)[2] = *launder(reinterpret_cast<std::size_t (*)[2]>(+(this -> dynamic)));
          unsigned char *element     = reinterpret_cast<unsigned char*>(&metadata + 1);

          while (0u != (element - reinterpret_cast<unsigned char*>(+(this -> dynamic))) % alignof(typename conditional<is_reference<base>::value, reference<base>, base>::type)) ++element;
          return this -> push(reinterpret_cast<typename conditional<is_reference<base>::value, reference<base>, base>::type*>(element) + *metadata, *metadata, pass<types>(elements)...);
        }

        return false;
      }

      // ...
      inline base& at(std::size_t const index) const& /* volatile */ noexcept {
        if (index < capacity) return (base&) this -> automatic[index];
        unsigned char *element = reinterpret_cast<unsigned char*>(+(this -> dynamic)) + sizeof(std::size_t[2]);

        while (0u != (element - reinterpret_cast<unsigned char*>(+(this -> dynamic))) % alignof(typename conditional<is_reference<base>::value, reference<base>, base>::type)) ++element;
        return (base&) *launder(reinterpret_cast<typename conditional<is_reference<base>::value, reference<base>, base>::type*>(element) + (index - capacity));
      }

      constexpr base&& at(std::size_t const index) const&& /* volatile */ noexcept {
        return static_cast<base&&>(this -> at(index));
      }

      // ...
      constexpr Array<void>::iterator<base, capacity> begin() const /* volatile */ noexcept {
        return {const_cast<Array<base, capacity>*>(this), 0u};
      }

      // ...
      constexpr Array<void>::iterator<base, capacity> end() const /* volatile */ noexcept {
        return {NULL, this -> length};
      }

      /* ... */
      constexpr base&  operator [](std::size_t const index) const&  /* volatile */ noexcept { return (base&)  this -> at(index); }
      constexpr base&& operator [](std::size_t const index) const&& /* volatile */ noexcept { return (base&&) this -> at(index); }
  };
#else
  class Array : public Array<void> {
    private:
      // union length {
      //   private:
      //     inline Array* get() const /* volatile */ throw() {}

      //   public:
      //     inline length& operator =  (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(length); return *this; }
      //     inline length& operator += (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value +  length); return *this; }
      //     inline length& operator -= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value -  length); return *this; }
      //     inline length& operator *= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value *  length); return *this; }
      //     inline length& operator /= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value /  length); return *this; }
      //     inline length& operator &= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value &  length); return *this; }
      //     inline length& operator |= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value |  length); return *this; }
      //     inline length& operator ^= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value ^  length); return *this; }
      //     inline length& operator <<=(std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value << length); return *this; }
      //     inline length& operator >>=(std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value >> length); return *this; }

      //     inline operator std::size_t() const /* volatile */ throw() { return capacity + (NULL == this -> get() -> dynamic ? 0u : *launder(reinterpret_cast<std::size_t*>(+(this -> array -> dynamic)))); }
      // };

      // ...
      struct members {
        friend class Array;
        private:
          automatic<base, capacity> mutable automatic;
          dynamic  <base, capacity> dynamic;
      };

      /* ... */
      inline void initiate() {
        // Array<void const>::add(this);
        // // ... ->> subobjects aren't being initialized here, the `union` storage is incidentally used to instantiate valid objects
        // // ... ->> -- or `_` is being activated/ initialized by virtue of being written to
        // // (::new (&this -> _.length) Array<void>::length<base, capacity>) -> array = this;

        // (::new (&this -> _.heaped) Array<void>::dynamic<base, capacity>) -> value = NULL;
      }

    public:
      union {
        automatic<base, capacity> value;
        length                    length;
        members                   _;
      };

      /* ... */
      inline ~Array() throw() {
        // this -> initiate();
        // Array<void const>::remove(this);

        // if (NULL != this -> _.heaped)
        // deallocator(this -> _.heaped);
      }

      /* ... */
  };
    void  *Array<void>::AUTOMATIC[(std::size_t) (ARRAY_REF_INITIAL_COUNT)] = {NULL};
    void **Array<void>::DYNAMIC                                            = NULL;
#endif

#undef ARRAY_REF_INITIAL_COUNT

/* Main */
int main(int, char*[]) /* noexcept */ {
  Array<int> array = {};

  // ...
  // static_cast<void>(array);
  for (std::size_t count = 0u; count != 5u; ++count) {
    if (0u == array.length) array.add(1);
    else for (std::size_t length = array.length; length--; ) array.add(array[array.length - 1u] + 1);

    std::printf("%1.5s", "[]: {");
      for (std::size_t index = 0u; index != array.length; ++index)
      std::printf("%i%s", array[index], index == array.length - 1u ? "" : ", ");
    std::printf("%1.3s", "}" "\r\n");
  }
}
