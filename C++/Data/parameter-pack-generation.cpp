#include <cstdio>

/* ... */
template <typename nontype_t, template <nontype_t...> class, typename, typename>
union concatenate_packed_traits;

template <typename nontype_t, template <nontype_t...> class trait, nontype_t... packA, nontype_t... packB>
union concatenate_packed_traits<nontype_t, trait, trait<packA...>, trait<packB...>> {
  typedef trait<packA..., packB...> type;
};

// ...
template <typename nontype_t, template <nontype_t...> class trait, nontype_t start, nontype_t accept, nontype_t (*next)(nontype_t)>
union generate_packed_trait {
  typedef typename concatenate_packed_traits<
    nontype_t,
    trait,
    trait<start>,
    typename generate_packed_trait<nontype_t, trait, next(start), accept, next>::type
  >::type type;
};

template <typename nontype_t, template <nontype_t...> class trait, nontype_t state, nontype_t (*next)(nontype_t)>
union generate_packed_trait<nontype_t, trait, state, state, next> {
  typedef trait<state> type;
};

/* ... */
template <unsigned...>
struct states_t {
  char const *const label;
  states_t(char const label[] = NULL) : label(label) {}
};

template <unsigned... integers>
void print_states(states_t<integers...> const states) {
  constexpr unsigned const value[] = {integers...};

  // ...
  std::printf("%s: ", states.label);

  for (unsigned char iterator = 0u; iterator != (sizeof(value) / sizeof(int const)); ++iterator)
  std::printf("[%i]", value[iterator]);

  std::printf("%2s", "\r\n");
}

// must be compile-time compatible
constexpr unsigned add     (unsigned const value) { return value + 1u; }
constexpr unsigned divide  (unsigned const value) { return value / 2u; }
constexpr unsigned multiply(unsigned const value) { return value * 2u; }
constexpr unsigned subtract(unsigned const value) { return value - 1u; }

/* Main */
int main(void) {
  print_states(states_t<0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u>("..."));
  print_states(typename generate_packed_trait<unsigned, states_t, 0u, 9u, &add>::type("..."));
  std::puts("");

  // each generated `states_t` type must eventually have its `start` & `accept` template arguments be the same
  // otherwise it will result in a compile-time error from recursively generating too many template types
  print_states(typename generate_packed_trait<unsigned, states_t, 0u, 3u, &add     >::type("add      +"));
  print_states(typename generate_packed_trait<unsigned, states_t, 1u, 8u, &multiply>::type("multiply ×"));

  print_states(typename generate_packed_trait<unsigned, states_t, 4u, 0u, &divide  >::type("divide   ÷"));
  print_states(typename generate_packed_trait<unsigned, states_t, 3u, 0u, &subtract>::type("subtract -"));
}
