#include <cstddef>
#include <cstdio>

/* ... */
namespace {
  typedef unsigned char depth_t;
  typedef std::size_t   size_t;

  // ...
  template <bool, typename> struct conditional;
  template <typename base>  struct conditional<true, base> { typedef base type; };

  template <typename>                         struct is_array                  { static bool const value = false; };
  template <typename base, ::size_t capacity> struct is_array<base [capacity]> { static bool const value = true ; };
}

// ... ->> implementation
template <::depth_t depth, typename base, ::size_t capacity, typename type>
constexpr typename conditional<false == is_array<base>::value, ::depth_t>::type foreach(base (&array)[capacity], type (&callback)(base&, ::size_t const, ::size_t const), ::size_t const iterator) {
  return capacity != iterator ? (
    callback(array[iterator], iterator, capacity),
    foreach<depth>(array, callback, iterator + 1u)
  ) : depth;
}

template <::depth_t depth, typename base, ::size_t capacity, typename type>
constexpr typename conditional<true  == is_array<base>::value, ::depth_t>::type foreach(base (&array)[capacity], type& callback, ::size_t const iterator) {
  return capacity != iterator ? (
    foreach<depth>(array, callback, iterator + 1u),
    foreach<depth + 1u>(array[capacity - iterator - 1u], callback, 0u)
  ) : 0u;
}

// ... ->> interface
template <typename base, ::size_t capacity, typename type>
constexpr typename conditional<false == is_array<base>::value, ::depth_t>::type foreach(base (&array)[capacity], type (&callback)(base&, ::size_t const, ::size_t const)) {
  return foreach<1u>(array, callback, 0u);
}

template <typename base, ::size_t capacity, typename type>
constexpr typename conditional<true  == is_array<base>::value, ::depth_t>::type foreach(base (&array)[capacity], type& callback) {
  return foreach<1u>(array, callback, 0u);
}

/* Main */
static char const sentences[][5][11] = {
  {"Lapys", "was", "a", "Rust", "developer" "."},
  {"The", "quick", "brown", "fox", "jumped" "."},
  {"Lorem", "ipsum", "dolor", "sit", "amet" "."}
};

constexpr static int nil(char const&, std::size_t const, std::size_t const) { return 0x0; }
static void print(char const& element, std::size_t const index, std::size_t const length) { std::printf("%c%.1s", element, index + 1u == length ? " " : ""); }

// ...
int main() {
  std::printf("Depth: %hu" "\r\n", foreach(sentences, nil));
  std::printf("Elements: "); foreach(sentences, print);
}
