#include <cstdio>

/* ... */
template <bool, typename, typename> struct conditional_type;
template <typename true_t, typename false_t> struct conditional_type<false, true_t, false_t> { typedef false_t type; };
template <typename true_t, typename false_t> struct conditional_type<true, true_t, false_t> { typedef true_t type; };

template <typename> struct is_reference { static bool const value = false; };
template <typename type> struct is_reference<type&> { static bool const value = true; };
template <typename type> struct is_reference<type&&> { static bool const value = true; };

/* ... */
template <typename type = void, typename... types>
struct pack : pack<types...> {
  typename conditional_type<is_reference<type>::value, type&, type>::type const value;

  constexpr pack(type&& argument, types&&... arguments) :
    pack<types...>(static_cast<types&&>(arguments)...),
    value {static_cast<type&&>(argument)}
  {}

  // ...
  template <template <typename> class callback>
  constexpr void foreach(void) const {
    callback<type>::invoke(this -> value);
    this -> pack<types...>::template foreach<callback>();
  }
};

template <>
struct pack<void> {
  template <template <typename> class>
  constexpr void foreach(void) const {}
};

/* Main */
template <typename type>
struct put {
  // your functions
  static void invoke(char const string[]) { std::printf("[   ]: \"%s\"" "\r\n", string); }
  static void invoke(int const integer) { std::printf("[   ]: %ii" "\r\n", integer); }

  template <bool = 0> static void invoke(type) { std::puts("[...]"); }
};

int main(void) {
  pack<
    int,
    void*,
    char const (&)[14],
    pack<>,
    void (pack<>::*)(void) const
  > const list(
    42,
    NULL,
    "Hello, World!",
    pack<>(),
    &pack<>::foreach<put>
  );

  list.foreach<put>();
}
