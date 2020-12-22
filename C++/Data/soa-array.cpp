#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <utility>

namespace std {
  template <typename base, std::size_t capacity>
  struct soa_array {
    private:
      enum byte : unsigned char {};
      struct element final {
        private:
          soa_array *const array;
          std::size_t const index;

        public:
          // Constructor
          constexpr element(soa_array *const array, std::size_t const index) noexcept : array{array}, index{index} {}

          // Assignment Overloads
          constexpr inline element& operator =(base const& value) noexcept {
            byte (*bytes)[capacity] = array -> bytes;
            byte const *layout = reinterpret_cast<byte const*>(&value);

            for (std::size_t iterator = 0u; iterator < sizeof(base); ++iterator)
            (*(bytes++))[this -> index] = *(layout++);

            return *this;
          }
          constexpr element& operator +=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) + value); }
          constexpr element& operator -=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) - value); }
          constexpr element& operator *=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) * value); }
          constexpr element& operator /=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) / value); }
          constexpr element& operator %=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) % value); }
          constexpr element& operator &=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) & value); }
          constexpr element& operator |=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) | value); }
          constexpr element& operator ^=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) ^ value); }
          constexpr element& operator <<=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) << value); }
          constexpr element& operator >>=(base const& value) noexcept { return this -> operator =(static_cast<base const&>(*this) >> value); }

          // ... Overloads
          constexpr base* operator &(void) const noexcept;
          inline operator base const&(void) const noexcept {
            static base element[1];
            byte *buffer = reinterpret_cast<byte*>(element);
            byte const (*bytes)[capacity] = array -> bytes;

            for (std::size_t iterator = 0u; iterator < sizeof(base); ++iterator)
            *(buffer++) = (*(bytes++))[this -> index];

            return *element;
          }

          // Other overloads for specific things like:
          // - if `base` is an array type, then a subscript overload
          // - if `base` is an function type, then an invocation overload
          // - if `base` is a pointer type, then a reference overload
      };

    public:
      byte bytes[sizeof(base)][capacity];
      union { public: operator std::size_t(void) const { return capacity; } } length;

      // Constructor
      constexpr soa_array(void) noexcept : bytes{}, length{} {}

      template <typename type, typename... types>
      constexpr soa_array(type&& argument, types&&... arguments) noexcept :
        soa_array(std::forward<types>(arguments)...)
      {
        // It's backwards, tho'
        soa_array::element element = soa_array::element {const_cast<soa_array*>(this), sizeof...(types)};
        element.operator =(std::forward<type>(argument));
      }

      // Overloads
      constexpr base* operator +(void) const noexcept;
      constexpr base* operator ->(void) const noexcept;
      template <typename type> constexpr base* operator ->*(type&&) const noexcept;

      constexpr element* operator *(void) const noexcept { return this -> operator [](0u); }
      constexpr element operator [](std::size_t index) const noexcept { return {const_cast<soa_array*>(this), index}; }
  };
}

/* Main */
int main(void) {
  class Object final {
    public:
      char const *name;
      std::size_t age;

      constexpr Object(char const name[] = NULL, std::size_t age = 0u) noexcept :
        name{name}, age{age}
      {}
  };

  // ...
  std::soa_array<Object, 5u> array = {
    Object {"Person B", 2u},
    Object {"Person A", 1u}
  };

  std::printf("Array<Object, %zu>" "\r\n", static_cast<std::size_t>(array.length)); {
    // Regular array modification
    array[2] = Object {"Person C", 3u};
    array[3] = Object {"Person D", 4u};
    array[4] = Object {"Person E", 5u};

    // Regular array indexing
    for (std::size_t iterator = 0u; array.length != iterator; ++iterator) {
      std::printf("  " "[%zu]: ", iterator);
      std::printf("{%zu, \"%s\"}" "\r\n",
        // Really just a `static` object modified to represent each `iterator` index.
        static_cast<Object const&>(array[iterator]).age,
        static_cast<Object const&>(array[iterator]).name
      );
    }
  }

  // ...
  return EXIT_SUCCESS;
}
