#include <cstddef>
#include <cstdio>
#include <type_traits>

/* ... */
namespace nostd {
  template <std::size_t base, std::size_t exponent> struct exponentiate           final { static std::size_t const value = base * exponentiate<base, exponent - 1u>::value; };
  template <std::size_t base>                       struct exponentiate<base, 0u> final { static std::size_t const value = 1u;   };
  template <std::size_t base>                       struct exponentiate<base, 1u> final { static std::size_t const value = base; };

  template <std::size_t, char...>                                     struct to_index final { static std::size_t const value = 0u; };
  template <std::size_t exponent, char character, char... characters> struct to_index<exponent, character, characters...>;
  template <std::size_t exponent, char... characters> struct to_index<exponent, '0', characters...> final { static std::size_t const value = (exponent * 0u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '1', characters...> final { static std::size_t const value = (exponent * 1u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '2', characters...> final { static std::size_t const value = (exponent * 2u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '3', characters...> final { static std::size_t const value = (exponent * 3u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '4', characters...> final { static std::size_t const value = (exponent * 4u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '5', characters...> final { static std::size_t const value = (exponent * 5u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '6', characters...> final { static std::size_t const value = (exponent * 6u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '7', characters...> final { static std::size_t const value = (exponent * 7u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '8', characters...> final { static std::size_t const value = (exponent * 8u) + to_index<exponent / 10u, characters...>::value; };
  template <std::size_t exponent, char... characters> struct to_index<exponent, '9', characters...> final { static std::size_t const value = (exponent * 9u) + to_index<exponent / 10u, characters...>::value; };

  // ...
  template <char... characters>
  constexpr static std::integral_constant<std::size_t, to_index<exponentiate<10u, sizeof...(characters) - 1u>::value, characters...>::value> operator ""_u() noexcept {
    return {};
  }
}

struct object final {
  template <std::size_t index>
  constexpr void operator [](std::integral_constant<std::size_t, index> const) const noexcept {}
};

/* Main */
int main(int, char*[]) /* noexcept */ {
  using namespace nostd;
  object{}[2_u];
}
