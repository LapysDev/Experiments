#include <cstddef>
#include <cstdio>

/* ... */
template <typename base, std::size_t count, base... objects> // ->> empty sequence
struct sequence : sequence<base, count - 1u, objects...> {};

template <typename base, std::size_t count, base object, base... objects> // ->> filled sequence
struct sequence<base, count, object, objects...> : sequence<base, count - 1u, objects...> {
  static std::size_t const size = sizeof...(objects);
};

template <typename base, base... objects> // ->> ended sequence
struct sequence<base, 0u, objects...> {
  typedef base type;
};

// ...
template <std::size_t index, typename base, std::size_t count, base object, base... objects>
constexpr base sequence_at(sequence<base, count, object, objects...> const);

template <std::size_t, bool, typename base, std::size_t, base, base...>
struct sequence_at_impl {};

template <std::size_t index, typename base, std::size_t count, base object, base... objects>
struct sequence_at_impl<index, true, base, count, object, objects...> {
  static base const value = sequence_at<index>(sequence<base, count - 1u, objects...>());
};

template <std::size_t index, typename base, base object, base... objects>
struct sequence_at_impl<index, true, base, index + 1u, object, objects...> {
  static base const value = object;
};

template <std::size_t index, typename base, std::size_t count, base object, base... objects>
constexpr base sequence_at(sequence<base, count, object, objects...> const) { return sequence_at_impl<index, (index < count), base, count, object, objects...>::value; }
