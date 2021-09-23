#include <cstddef>
#include <cstdio>

/* ... */
template <bool assertion>
union constrain {
  template <typename...> union typed;
  template <typename...> union untyped;
};

template <>
union constrain<true> {
  template <typename...> union typed;
  template <typename...> union untyped;

  // ...
  template <typename...>
  union typed {
    template <template <typename...> class trait, typename... types>
    using type = trait<types...>;
  };

  #if defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__)
    template <typename... types>
    union untyped {
      template <template <types...> class trait, types... parameters>
      using type = trait<parameters...>;
    };
  #else
    template <typename base, typename... types>
    union untyped<base, types...> {
      template <template <base...> class trait, base... parameters>
      using type = trait<parameters...>;
    };
  #endif
};

// ...
template <typename> union is_void { enum { value = false }; };
template <> union is_void<void> { enum { value = true }; };

template <std::size_t...> union sum;
template <std::size_t integer> union sum<integer> { enum { value = integer }; };
template <std::size_t integerA, std::size_t integerB, std::size_t... integers> union sum<integerA, integerB, integers...> { enum { value = sum<integerA + integerB, integers...>::value }; };

/* Main */
int main() noexcept {
  std::printf("[is_void<int>] : %4.5s" "\r\n", constrain<true>::typed<>::type<is_void, int>::value  ? "true" : "false");
  std::printf("[is_void<void>]: %4.5s" "\r\n", constrain<true>::typed<>::type<is_void, void>::value ? "true" : "false");
  std::printf("[sum<2, 3>]: %u", constrain<true>::untyped<std::size_t, std::size_t>::type<sum, 2u, 3u>::value);
}
