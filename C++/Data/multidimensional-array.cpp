#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>

/* ... */
template <bool...>
struct AND { constexpr static bool value = true; };

template <bool boolean, bool... booleans>
struct AND<boolean, booleans...> { constexpr static bool value = boolean && AND<booleans...>::value; };

// ...
template <typename, std::size_t...>
class MultidimensionalArray;

template <typename base, std::size_t capacity, std::size_t... capacities>
class MultidimensionalArray<base, capacity, capacities...> final {
  template <typename, std::size_t...>
  friend class MultidimensionalArray;
  
  typedef typename MultidimensionalArray<base, capacities...>::type (type)[capacity];

  private:
    MultidimensionalArray<base, capacities...> value[capacity];
    
    template <typename subtype, std::size_t... indexes>
    constexpr MultidimensionalArray(subtype array[], std::index_sequence<indexes...> const) noexcept(AND<noexcept(MultidimensionalArray<base, capacities...>(array[indexes]))...>::value) :
      value{array[indexes]...}
    {}
    
  public:
    constexpr MultidimensionalArray() noexcept(noexcept(MultidimensionalArray<base, capacities...>{})) :
      value{}
    {}

    template <typename subtype, std::size_t length>
    constexpr MultidimensionalArray(subtype (&array)[length]) noexcept(noexcept(MultidimensionalArray(std::declval<subtype (&)[length]>(), std::make_index_sequence<length>()))) :
      MultidimensionalArray<base, capacity, capacities...>::MultidimensionalArray(
        static_cast<typename std::enable_if<
          std::is_same<
            typename std::remove_cv<subtype>::type,
            typename std::remove_cv<typename MultidimensionalArray<base, capacities...>::type>::type
          >::value, subtype (&)[length]
        >::type>(array),
        std::make_index_sequence<length>()
      )
    {}
    
    // ...
    template <typename subtype> constexpr MultidimensionalArray<base, capacities...>      & operator [](subtype&& index)       noexcept { return this -> value[index]; }
    template <typename subtype> constexpr MultidimensionalArray<base, capacities...> const& operator [](subtype&& index) const noexcept { return this -> value[index]; }

    constexpr operator type      &()       noexcept { return reinterpret_cast<type&>(this -> value); }
    constexpr operator type const&() const noexcept { return reinterpret_cast<type const&>(this -> value); }
};

template <typename base>
class MultidimensionalArray<base> final {
  template <typename, std::size_t...>
  friend class MultidimensionalArray;

  typedef base type;

  private:
    base value;

  public:
    constexpr MultidimensionalArray() noexcept(noexcept(base())) :
      value{}
    {}

    template <typename... subtypes>
    constexpr MultidimensionalArray(subtypes&&... arguments) noexcept(noexcept(base(std::declval<subtypes>()...))) :
      value{std::forward<subtypes>(arguments)...}
    {}

    // ...
    constexpr operator type      &()       noexcept { return this -> value; }
    constexpr operator type const&() const noexcept { return this -> value; }
};

/* Main */
int main() {
  constexpr MultidimensionalArray<char, 14u> message("Hello, World!");

  std::puts(message);
  std::putchar(message[0]);
}
