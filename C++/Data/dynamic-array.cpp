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

  private:
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

    // ...
    template <typename base>
    union reference {
      base value;
      inline operator base() const { return (base) this -> value; }
    };

    // ...
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
    struct fixed {
      private:
        typedef typename element<base>::type (type)[capacity];

      public:
        typename element<base>::type value[capacity];
        /* constexpr */ inline operator type&() const /* volatile noexcept */ { return const_cast<type&>(this -> value); }
    };

    template <typename base>
    struct fixed<base, 0u> {};

    // ...
    template <class base, std::size_t capacity>
    union length {
      Array<base, capacity> *array;

      /* ... */
      /* constexpr */ inline length& operator =  (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(length); return *this; }
      /* constexpr */ inline length& operator += (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value +  length); return *this; }
      /* constexpr */ inline length& operator -= (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value -  length); return *this; }
      /* constexpr */ inline length& operator *= (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value *  length); return *this; }
      /* constexpr */ inline length& operator /= (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value /  length); return *this; }
      /* constexpr */ inline length& operator &= (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value &  length); return *this; }
      /* constexpr */ inline length& operator |= (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value |  length); return *this; }
      /* constexpr */ inline length& operator ^= (std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value ^  length); return *this; }
      /* constexpr */ inline length& operator <<=(std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value << length); return *this; }
      /* constexpr */ inline length& operator >>=(std::size_t const length) const /* volatile noexcept */ { this -> array -> resize(this -> value >> length); return *this; }

      /* constexpr */ inline operator std::size_t() const /* volatile noexcept */ { return NULL == this -> array -> heaped ? 0u : *launder(reinterpret_cast<std::size_t*>(+(this -> array -> heaped))); }
    };

    // ...
    template <typename base, std::size_t capacity>
    union varied {
      private:
        typedef typename element<base>::type *type;

      public:
        typename element<base>::type *value;

        template <typename type> /* constexpr */ inline varied& operator =(type heaped[]) /* volatile noexcept */ { this -> value = (typename element<base>::type*) heaped; return *this; }
        /* constexpr */ inline operator type&() const /* volatile noexcept */ { return const_cast<type&>(this -> value); }
    };
};

template <typename base, std::size_t capacity, void* (*allocator)(std::size_t), void (*deallocator)(void*), void* (*reallocator)(void*, std::size_t)>
#if __cplusplus >= 201103L
  class Array final {
    template <class, std::size_t>
    friend union Array<void>::length;

    private:
      Array<void>::fixed <base, capacity> stacked;
      Array<void>::varied<base, capacity> heaped;

    public:
      Array<void>::length<base, capacity> const length;

    /* ... */
    private:
      template <std::size_t... indexesA, std::size_t... indexesB, typename... types>
      inline Array(collection<0u, indexesA...> const, collection<0u, indexesB...> const, types&&... elements) noexcept :
        stacked{Array<void>::at<indexesA - 1u>(std::forward<types>(elements)...)...},
        heaped{NULL},
        length{this}
      { this -> add(Array<void>::at<capacity + (indexesB - 1u)>(std::forward<types>(elements)...)...); }

      template <typename... types>
      constexpr Array(bool (*const)[false + 1], types&&... elements) noexcept :
        stacked{std::forward<types>(elements)...},
        heaped{NULL},
        length{this}
      {}

      template <typename... types>
      constexpr Array(bool (*const)[true + 1], types&&... elements) noexcept :
        Array<base, capacity>::Array(typename sequence<capacity>::collection{}, typename sequence<sizeof...(elements) - capacity>::collection{}, std::forward<types>(elements)...)
      {}

      /* ... */
      inline bool grow(std::size_t const count) /* volatile */ noexcept {
        void       *allocation;
        std::size_t length = 0u;

        // ...
        if (NULL != this -> heaped) {
          length = *launder(reinterpret_cast<std::size_t*>(+(this -> heaped)));
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
          allocation = allocator(sizeof(std::size_t) + alignof(typename Array<void>::element<base>::type) + ((count + length) * sizeof(typename Array<void>::element<base>::type)));
          if (NULL == allocation) return false;
          new (allocation) std::size_t(0u);
        }

        // ...
        this -> heaped = static_cast<typename Array<void>::element<base>::type*>(allocation);
        return true;
      }

      // ...
      constexpr inline void push(typename Array<void>::element<base>::type[], std::size_t&) /* volatile */ noexcept {}

      template <typename type, typename... types>
      inline void push(typename Array<void>::element<base>::type heaped[], std::size_t& length, type&& element, types&&... elements) /* volatile */ noexcept {
        new (heaped) typename Array<void>::element<base>::type(std::forward<type>(element));
        this -> push(++heaped, ++length, std::forward<types>(elements)...);
      }

    public:
      template <typename... types>
      constexpr Array(types&&... elements) noexcept :
        Array<base, capacity>::Array(static_cast<bool (*)[(sizeof...(elements) > capacity) + 1]>(NULL), std::forward<types>(elements)...)
      {}

      inline ~Array() noexcept {
        if (NULL != this -> heaped)
        deallocator(this -> heaped);
      }

      /* ... */
      constexpr typename std::conditional<(__cplusplus >= 201103L), int, void>::type add() const /* volatile */ noexcept {
        return typename std::conditional<(__cplusplus >= 201103L), int, void>::type(0x0);
      }

      template <typename... types>
      inline bool add(types&&... elements) /* volatile */ noexcept {
        if (this -> grow(sizeof...(elements) + 1u)) {
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
      inline typename Array<void>::element<base>::type& at(std::size_t const index) const /* volatile */ noexcept {
        if (index < capacity) return this -> stacked[index];
        unsigned char *element = reinterpret_cast<unsigned char*>(+(this -> heaped)) + sizeof(std::size_t);

        // ...
        while (0u != (element - reinterpret_cast<unsigned char*>(+(this -> heaped))) % alignof(typename Array<void>::element<base>::type))
        ++element;

        return *launder(reinterpret_cast<typename Array<void>::element<base>::type*>(element) + (index - capacity));
      }

      // ...
      inline typename Array<void>::element<base>::type& operator [](std::size_t const index) const /* volatile */ noexcept {
        return this -> at(index);
      }
  };
#else
  class Array {
    template <class, std::size_t>
    friend union Array<void>::length;

    private:
      struct members {
        friend class Array;
        private:
          Array<void>::fixed <base, capacity> stacked;
          Array<void>::varied<base, capacity> heaped;
          Array<void>::length<base, capacity> length;
      };

    public:
      union {
        Array<void>::fixed<base, capacity>      value;
        typename Array<base, capacity>::members members;
      };
  };
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  Array<int, 3> array = {1, 2, 3, 4};
  std::printf("[]: {%i, %i, %i, %i}", array[0], array[1], array[2], array[3]);
}
