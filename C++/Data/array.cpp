#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <version>
#if __cplusplus >= 201103L
# include <type_traits>
# include <utility>
#endif

/* ... */
namespace {
  #if __cplusplus >= 201103L
    template <std::size_t...>
    struct collection final {};

    // ...
    template <typename... bases>
    struct pack final {
      template <std::size_t index>
      struct at final {
        private:
          template <std::size_t, typename...>                                     struct valueof;
          template <typename subbase, typename... subbases>                       struct valueof<0u, subbase, subbases...>       final { typedef subbase type; };
          template <std::size_t subindex, typename subbase, typename... subbases> struct valueof<subindex, subbase, subbases...> final { typedef typename valueof<subindex - 1u, subbases...>::type type; };

        public:
          typedef typename valueof<index, bases...>::type type;
      };
    };

    // ...
    template <std::size_t value>
    struct sequence final {
      private:
        template <std::size_t...>
        struct valueof;

        template <std::size_t... subvalues>
        struct valueof<0u, subvalues...> final { typedef collection<0u, subvalues...> type; };

        template <std::size_t subvalue, std::size_t... subvalues>
        struct valueof<subvalue, subvalues...> final { typedef typename valueof<subvalue - 1u, subvalue, subvalues...>::type type; };

      public:
        typedef typename valueof<value>::type collection;
    };
  #endif

  // ...
  #ifdef __cpp_lib_launder
    using std::launder;
  #else
    template <typename type>
    inline type* launder(type* const address) {
      return address;
    }
  #endif
}

/* Class */
template <typename, std::size_t = 0u, void* (*)(std::size_t) = &std::malloc, void (*)(void*) = &std::free, void* (*)(void*, std::size_t) = &std::realloc>
class Array;

template <>
class Array<void> {
  template <typename, std::size_t, void* (*)(std::size_t), void (*)(void*), void* (*)(void*, std::size_t)>
  friend class Array;

  template <typename>              union  element;   // ->> allows `Array` consist of reference-qualified element types
  template <typename, std::size_t> union  fixed;     // ->> container for possible `Array` array member
  template <typename>              struct reference; // ->> wraps references as elements of `Array`
  template <typename, std::size_t> union  varied;    // ->> container for dynamically-allocated `Array` elements

  /* ... */
  private:
    template <typename base>
    union element { typedef base type; };

    template <typename base>
    union element<base&> { typedef reference<base&> type; };

    #ifdef __cpp_rvalue_references
      template <typename base>
      union element<base&&> { typedef reference<base&&> type; };
    #endif

    // ...
    template <typename base, std::size_t capacity>
    union fixed {
      private:
        typedef typename element<base>::type (type)[capacity];

      public:
        typename element<base>::type value[capacity];
        /* constexpr */ inline operator type&() const /* volatile noexcept */ { return const_cast<type&>(this -> value); }
    };

    template <typename base>
    union fixed<base, 0u> {
      private:
        typedef typename element<base>::type (type)[];
    };

    // ...
    template <typename base>
    struct reference {
      base value;

      /* ... */
      /* constexpr */ inline reference(base value)                 /* noexcept */ : value((base) value) {}
      /* constexpr */ inline reference(reference const& reference) /* noexcept */ : value((base) reference.value) {}

      /* constexpr */ inline operator base() const /* noexcept */ { return (base) this -> value; }
    };

    // ...
    template <typename base, std::size_t capacity>
    union varied {
      private:
        typedef typename element<base>::type *type;

      public:
        typename element<base>::type *value;

        /* ... */
        template <typename type> /* constexpr */ inline varied& operator =(type heaped[]) /* volatile noexcept */ { this -> value = (typename element<base>::type*) heaped; return *this; }
        /* constexpr */ inline operator type&() const /* volatile noexcept */ { return const_cast<type&>(this -> value); }
    };

    // ... ->> for aggregate array member initialization only
    #if __cplusplus >= 201103L
      template <std::size_t index, typename type, typename... types>
      constexpr static typename std::enable_if<index == 0u, typename pack<type, types...>::template at<index>::type&&>::type at(type&& object, types&&...) noexcept {
        return static_cast<type&&>(object);
      }

      template <std::size_t index, typename type, typename... types>
      constexpr static typename std::enable_if<index != 0u, typename pack<type, types...>::template at<index>::type&&>::type at(type&&, types&&... objects) noexcept {
        return static_cast<typename pack<type, types...>::template at<index>::type&&>(at<index - 1u>(std::forward<types>(objects)...));
      }
    #endif

    // ... ->> for range-based `for` loops
    #ifdef __cpp_range_based_for
      template <typename base, std::size_t capacity>
      struct iterator final {
        Array<base, capacity> *const array;
        std::size_t                  index;

        /* ... */
        constexpr base& operator *() const noexcept { return this -> array -> at(this -> index); }
        constexpr void operator ++() noexcept { ++const_cast<std::size_t&>(this -> index); }

        constexpr bool operator !=(iterator const end) const noexcept { return this -> index != end.index; }
      };
    #endif
};

#if __cplusplus >= 201103L
  template <typename base, std::size_t capacity, void* (*allocator)(std::size_t), void (*deallocator)(void*), void* (*reallocator)(void*, std::size_t)>
  class Array final {
    private:
      Array<void>::fixed <base, capacity> stacked;
      Array<void>::varied<base, capacity> heaped;

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

        constexpr operator std::size_t() const /* volatile */ noexcept { return capacity + (NULL == this -> array -> heaped ? 0u : *launder(reinterpret_cast<std::size_t*>(+(this -> array -> heaped)))); }
      } const length;

    /* ... */
    private:
      template <std::size_t... indexesA, std::size_t... indexesB, typename... types>
      constexpr Array(collection<0u, indexesA...> const, collection<0u, indexesB...> const, types&&... elements) noexcept :
        stacked{Array<void>::at<indexesA - 1u>(std::forward<types>(elements)...)...},
        heaped{NULL},
        length{this -> add(Array<void>::at<capacity + (indexesB - 1u)>(std::forward<types>(elements)...)...), this}
      { /* ->> C++11 `constexpr` constructor body must be empty */ }

      template <typename... types>
      constexpr Array(bool (*const)[true + 1], types&&... elements) noexcept :
        Array<base, capacity>::Array(
          typename sequence<capacity>::collection{},
          typename sequence<sizeof...(elements) - capacity>::collection{},
          std::forward<types>(elements)...
        )
      {}

      template <typename... types>
      constexpr Array(bool (*const)[false + 1], types&&... elements) noexcept :
        stacked{std::forward<types>(elements)...},
        heaped{NULL},
        length{this}
      {}

      /* ... */
      inline bool grow(std::size_t const count) /* volatile */ noexcept {
        void *allocation;

        // ...
        if (NULL != this -> heaped) {
          std::size_t length = *launder(reinterpret_cast<std::size_t*>(+(this -> heaped)));

          do {
            /* constexpr */ void* (*const function)(void*, std::size_t) = reallocator;

            // ...
            if (NULL != function && (allocator == &std::malloc) == (function == &std::realloc)) {
              allocation = reallocator((void*) this -> heaped, sizeof(std::size_t) + alignof(typename Array<void>::element<base>::type) + ((count + length) * sizeof(typename Array<void>::element<base>::type)));
              if (NULL != allocation) break;
            }

            allocation = allocator(sizeof(std::size_t) + alignof(typename Array<void>::element<base>::type) + ((count + length) * sizeof(typename Array<void>::element<base>::type)));
            if (NULL == allocation) return false;

            for (unsigned char *element = reinterpret_cast<unsigned char*>(new (allocation) std::size_t(length) + 1); ; ++element)
            if (0u == (element - static_cast<unsigned char*>(allocation)) % alignof(typename Array<void>::element<base>::type)) {
              this -> heaped = reinterpret_cast<unsigned char*>(+(this -> heaped)) + (element - static_cast<unsigned char*>(allocation));
              while (length--) new (element++) typename Array<void>::element<base>::type(*launder(this -> heaped++));

              break;
            }
          } while (false);
        }

        else {
          allocation = allocator(sizeof(std::size_t) + alignof(typename Array<void>::element<base>::type) + (count * sizeof(typename Array<void>::element<base>::type)));
          if (NULL == allocation) return false;
          new (allocation) std::size_t(0u);
        }

        // ...
        this -> heaped = static_cast<typename Array<void>::element<base>::type*>(allocation);
        return true;
      }

      // ...
      constexpr typename std::conditional<(__cplusplus >= 201103L), int, void>::type push(typename Array<void>::element<base>::type[], std::size_t&) /* volatile */ noexcept {
        return typename std::conditional<(__cplusplus >= 201103L), int, void>::type(0x0);
      }

      template <typename type, typename... types>
      constexpr typename std::conditional<(__cplusplus >= 201103L), int, void>::type push(typename Array<void>::element<base>::type heaped[], std::size_t& length, type&& element, types&&... elements) /* volatile */ noexcept {
        return this -> push(new (heaped) typename Array<void>::element<base>::type(std::forward<type>(element)) + 1, ++length, std::forward<types>(elements)...);
      }

    public:
      template <typename... types>
      constexpr Array(types&&... elements) noexcept :
        Array<base, capacity>::Array(
          static_cast<bool (*)[(sizeof...(elements) > capacity) + 1]>(NULL),
          std::forward<types>(elements)...
        )
      {}

      /* constexpr */ inline ~Array() noexcept {
        if (NULL != this -> heaped)
        deallocator(this -> heaped);
      }

      /* ... */
      constexpr typename std::conditional<(__cplusplus >= 201103L), int, void>::type add() const /* volatile */ noexcept {
        return typename std::conditional<(__cplusplus >= 201103L), int, void>::type(0x0);
      }

      template <typename... types>
      inline bool add(types&&... elements) /* volatile */ noexcept {
        if (this -> grow(sizeof...(elements))) {
          std::size_t   &length  = *launder(reinterpret_cast<std::size_t*>(+(this -> heaped)));
          unsigned char *element = reinterpret_cast<unsigned char*>(&length + 1);

          // ...
          while (0u != (element - reinterpret_cast<unsigned char*>(+(this -> heaped))) % alignof(typename Array<void>::element<base>::type)) ++element;
          this -> push(reinterpret_cast<typename Array<void>::element<base>::type*>(element) + length, length, std::forward<types>(elements)...);

          return true;
        }

        return false;
      }

      // ...
      inline base& at(std::size_t const index) const& /* volatile */ noexcept {
        if (index < capacity) return (base&) this -> stacked[index];
        unsigned char *element = reinterpret_cast<unsigned char*>(+(this -> heaped)) + sizeof(std::size_t);

        while (0u != (element - reinterpret_cast<unsigned char*>(+(this -> heaped))) % alignof(typename Array<void>::element<base>::type)) ++element;
        return (base&) *launder(reinterpret_cast<typename Array<void>::element<base>::type*>(element) + (index - capacity));
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
  #ifndef ARRAY_REF_INITIAL_COUNT
  # define ARRAY_REF_INITIAL_COUNT 31u
  #endif

  template <std::size_t capacity, void* (*allocator)(std::size_t), void (*deallocator)(void*), void* (*reallocator)(void*, std::size_t)>
  class Array<void const, capacity, allocator, deallocator, reallocator> {
    template <typename, std::size_t, void* (*)(std::size_t), void (*)(void*), void* (*)(void*, std::size_t)>
    friend class Array;

    private:
      static void **HEAPED;
      static void  *STACKED[(std::size_t) (ARRAY_REF_INITIAL_COUNT)];

      template <typename base, std::size_t capacity, void* (*allocator)(std::size_t), void (*deallocator)(void*), void* (*reallocator)(void*, std::size_t)>
      inline bool add(Array<base, capacity, allocator, deallocator, reallocator> const /* volatile */* const array) throw() {
        for (void **iterator = STACKED; iterator != STACKED + (sizeof(STACKED) / sizeof(void*)); ++iterator)
        if (NULL == *iterator) { *iterator = array; return true; }

        // ...
        if (NULL == HEAPED) {
          HEAPED = static_cast<void**>(allocator(sizeof(void*) + sizeof(STACKED)));
          if (NULL != HEAPED) {
            new (HEAPED + 0) void*(array);
            new (HEAPED + 1) void*(NULL);

            return true;
          }
        }

        else {
          void* (*const function)(void*, std::size_t) = reallocator;

          // ...
          if (NULL != function && (allocator == &std::malloc) == (function == &std::realloc)) {
            void *const allocation = reallocator(HEAPED, (((iterator - HEAPED) + 1u) * sizeof(void*)) + sizeof(STACKED));
            if (NULL != allocation) { HEAPED = allocation; ... return true; }
          }
        }

        return false;
      }

      template <typename base, std::size_t capacity, void* (*allocator)(std::size_t), void (*deallocator)(void*), void* (*reallocator)(void*, std::size_t)>
      inline void remove(Array<base, capacity, allocator, deallocator, reallocator> const /* volatile */* const array) throw() {
        for (void **iterator = STACKED; iterator != STACKED + (sizeof(STACKED) / sizeof(void*)); ++iterator)
        if (array == *iterator) { *iterator = NULL; return; }
      }
  };
    void **Array<void const>::HEAPED                                           = NULL;
    void  *Array<void const>::STACKED[(std::size_t) (ARRAY_REF_INITIAL_COUNT)] = {NULL};

  template <typename base, std::size_t capacity, void* (*allocator)(std::size_t), void (*deallocator)(void*), void* (*reallocator)(void*, std::size_t)>
  class Array {
    private:
      union length {
        private:
          inline Array* get() const /* volatile */ throw() {}

        public:
          inline length& operator =  (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(length); return *this; }
          inline length& operator += (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value +  length); return *this; }
          inline length& operator -= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value -  length); return *this; }
          inline length& operator *= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value *  length); return *this; }
          inline length& operator /= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value /  length); return *this; }
          inline length& operator &= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value &  length); return *this; }
          inline length& operator |= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value |  length); return *this; }
          inline length& operator ^= (std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value ^  length); return *this; }
          inline length& operator <<=(std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value << length); return *this; }
          inline length& operator >>=(std::size_t const length) const /* volatile */ throw() { this -> get() -> resize(this -> value >> length); return *this; }

          inline operator std::size_t() const /* volatile */ throw() { return capacity + (NULL == this -> get() -> heaped ? 0u : *launder(reinterpret_cast<std::size_t*>(+(this -> array -> heaped)))); }
      };

      // ...
      struct members {
        friend class Array;
        private:
          Array<void>::fixed <base, capacity> stacked;
          Array<void>::varied<base, capacity> heaped;
      };

      /* ... */
      inline void initiate() {
        Array<void const>::add(this);
        // ... ->> subobjects aren't being initialized here, the `union` storage is incidentally used to instantiate valid objects
        // ... ->> -- or `_` is being activated/ initialized by virtue of being written to
        // (new (&this -> _.length) Array<void>::length<base, capacity>) -> array = this;

        (new (&this -> _.heaped) Array<void>::varied<base, capacity>) -> value = NULL;
      }

    public:
      union {
        Array<void>::fixed<base, capacity> value;
        Array::length                      length;
        Array::members                     _;
      };

      /* ... */
      inline ~Array() throw() {
        this -> initiate();
        Array<void const>::remove(this);

        if (NULL != this -> _.heaped)
        deallocator(this -> _.heaped);
      }

      /* ... */
  };

  #undef ARRAY_REF_INITIAL_COUNT
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  Array<int, 3> array = {1, 2, 3};

  // ...
  static_cast<void>(array);
  // array.add(4);

  // for (std::size_t index = 0u; index != array.length; ++index)
  // std::printf("[]: %i" "\r\n", array[index]);
}
