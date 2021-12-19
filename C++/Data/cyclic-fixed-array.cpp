#include <cstddef>
#include <iostream>
#include <utility>

/* ... */
template <typename base, std::size_t size>
class CyclicArray {
  private:
    std::size_t head;
    base value[size];

    template <typename type, std::size_t... indexes>
    constexpr CyclicArray(type value[], std::index_sequence<indexes...> const) noexcept :
      head{sizeof...(indexes)}, value{value[indexes]...}, length{this}
    {}

  public:
    class Length final {
      private:
        CyclicArray<base, size> const *const array;

      public:
        constexpr Length(CyclicArray<base, size> const* const array) noexcept : array{array} {}
        constexpr operator std::size_t() const noexcept { return array -> head; }
    } length;

    // ...
    constexpr CyclicArray() noexcept :
      head{0u}, value{}, length{this}
    {}

    template <typename type, std::size_t capacity>
    constexpr CyclicArray(type (&value)[capacity]) noexcept :
      CyclicArray<base, size>::CyclicArray(value, std::make_index_sequence<capacity>{})
    {}

    template <typename... types>
    constexpr CyclicArray(types&&... elements) noexcept :
      head{sizeof...(types)}, value{std::forward<types&&>(elements)...}, length{this}
    {}

    // ...
    constexpr void push() noexcept {}

    template <typename type, typename... types>
    void push(type&& element, types&&... elements) noexcept {
      this -> value[this -> head++ % size] = std::forward<type>(element);
      this -> push(std::forward<types>(elements)...);
    }

    // ...
    template <typename type>
    constexpr base& operator [](type&& index) noexcept {
      return this -> value[std::forward<type>(index)];
    }

    template <typename type>
    constexpr base const& operator [](type&& argument) const noexcept {
      std::size_t const index = std::forward<type>(argument);
      return this -> value[(this -> head + index) % size];
    }

    template <typename type, class traits>
    friend std::basic_ostream<type, traits>& operator <<(std::basic_ostream<type, traits>& stream, CyclicArray<base, size> const& array) {
      stream.put('{');

      for (std::size_t index = 0u; index != size; ++index) {
        stream << array.operator [](index);
        if (index != size - 1u) stream.write(", ", 2u);
      }

      stream.put('}');
      return stream;
    }
};

/* Main */
int main(int const, char*[]) /* noexcept */ {
  CyclicArray<int, 3u> array {1, 2, 3};

  std::cout << "[]: " << array << std::endl;
  array.push(4);
  std::cout << "[]: " << array << std::endl;
  array.push(5, 6);
  std::cout << "[]: " << array << std::endl;
  array.push(7);
  std::cout << "[]: " << array << std::endl;
}
