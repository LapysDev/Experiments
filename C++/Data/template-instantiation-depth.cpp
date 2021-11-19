#include <cstddef>
#include <type_traits>

/* ... */
template <bool...> struct AND { constexpr static bool value = true; };
template <bool assertion, bool... assertions> struct AND<assertion, assertions...> { constexpr static bool value = assertion && AND<assertions...>::value; };

enum { MAX = 2u };

template <unsigned>              struct constant;
template <class...>              struct pack;
template <std::size_t, class...> struct pair;
  template <std::size_t, unsigned>                  struct build_pair;
  template <class>                                  struct filled_pair;
  template <class>                                  struct flatten_pair;
  template <class, unsigned>                        struct push_pair;
  template <unsigned, unsigned = 0u, unsigned = 1u> struct sequence_pair;

// ...
template <unsigned>
struct constant {};

template <class...>
struct pack {};

template <std::size_t, class...>
struct pair {};
  template <std::size_t depth, unsigned value>
  struct build_pair {
    private:
      template <class build, std::size_t subdepth>
      struct valueof {
        typedef typename valueof<pair<subdepth + 1u, build>, subdepth + 1u>::type type;
      };

      template <class build>
      struct valueof<build, depth> {
        typedef build type;
      };

    public:
      typedef typename valueof<pair<0u, constant<value> >, 0u>::type type;
  };

  // ...
  template <class>
  struct filled_pair {
    constexpr static bool value = true;
  };

  template <std::size_t depth, class... values>
  struct filled_pair<pair<depth, values...> > {
    constexpr static bool value = MAX == sizeof...(values) && AND<filled_pair<values>::value...>::value;
  };

  // ...
  template <class, unsigned>
  struct push_pair {
    typedef pair<0u> type;
  };

  template <unsigned value>
  struct push_pair<pair<0u>, value> {
    typedef pair<0u, constant<value> > type;
  };

  template <std::size_t depth, unsigned... values, unsigned value>
  struct push_pair<pair<depth, constant<values>...>, value> {
    typedef typename std::conditional<
      filled_pair<pair<depth, constant<values>...> >::value,
      pair<depth + 1u, pair<depth, constant<values>...>, pair<depth, constant<value> > >,
      pair<depth + 0u, constant<values>..., constant<value> >
    >::type type;
  };

  template <std::size_t depth, class... values, class... pairs, unsigned value>
  struct push_pair<pair<depth, pair<depth - 1u, values...>, pairs...>, value> {
    private:
      template <class, class...>
      struct valueof;

      template <class... filled>
      struct valueof<pair<0u, filled...> > {
        typedef typename std::conditional<
          MAX == sizeof...(filled),
          pair<depth + 1u, pair<depth, filled...>, typename build_pair<depth, value>::type>,
          pair<depth, filled..., typename build_pair<depth - 1u, value>::type>
        >::type type;
      };

      template <class... filled, class subpair, class... subpairs>
      struct valueof<pair<0u, filled...>, subpair, subpairs...> {
        typedef typename std::conditional<
          filled_pair<subpair>::value,
          typename valueof<pair<0u, filled..., subpair>, subpairs...>::type,
          pair<depth, filled..., typename push_pair<subpair, value>::type, subpairs...>
        >::type type;
      };

    public:
      typedef typename valueof<pair<0u>, pair<depth - 1u, values...>, pairs...>::type type;
  };

  // ...
  template <unsigned begin, unsigned end, unsigned increment>
  struct sequence_pair {
    private:
      template <class sequence, unsigned subbegin, unsigned subend>
      struct valueof {
        typedef typename valueof<typename push_pair<sequence, subbegin>::type, subbegin + 1u, subend>::type type;
      };

      template <class sequence, unsigned subend>
      struct valueof<sequence, subend, subend> {
        typedef sequence type;
      };

    public:
      typedef typename valueof<pair<0u>, 0u == end ? 0u : begin, 0u == end ? begin : end>::type type;
  };

/* Main */
int main() {
  static_assert(std::is_same<typename sequence_pair<0u>::type, pair<0u> >::value, "Failed sequence #0");
  static_assert(std::is_same<typename sequence_pair<1u>::type, pair<0u, constant<0u> > >::value, "Failed sequence #1");
  static_assert(std::is_same<typename sequence_pair<2u>::type, pair<0u, constant<0u>, constant<1u> > >::value, "Failed sequence #2");
  static_assert(std::is_same<typename sequence_pair<3u>::type, pair<1u,
    pair<0u, constant<0u>, constant<1u> >,
    pair<0u, constant<2u> >
  > >::value, "Failed sequence #3");
  static_assert(std::is_same<typename sequence_pair<4u>::type, pair<1u,
    pair<0u, constant<0u>, constant<1u> >,
    pair<0u, constant<2u>, constant<3u> >
  > >::value, "Failed sequence #4");
  static_assert(std::is_same<typename sequence_pair<5u>::type, pair<2u,
    pair<1u, pair<0u, constant<0u>, constant<1u> >, pair<0u, constant<2u>, constant<3u> > >,
    pair<1u, pair<0u, constant<4u> > >
  > >::value, "Failed sequence #5");
  static_assert(std::is_same<typename sequence_pair<6u>::type, pair<2u,
    pair<1u, pair<0u, constant<0u>, constant<1u> >, pair<0u, constant<2u>, constant<3u> > >,
    pair<1u, pair<0u, constant<4u>, constant<5u> > >
  > >::value, "Failed sequence #6");
  static_assert(std::is_same<typename sequence_pair<7u>::type, pair<2u,
    pair<1u, pair<0u, constant<0u>, constant<1u> >, pair<0u, constant<2u>, constant<3u> > >,
    pair<1u, pair<0u, constant<4u>, constant<5u> >, pair<0u, constant<6u> > >
  > >::value, "Failed sequence #7");
  static_assert(std::is_same<typename sequence_pair<8u>::type, pair<2u,
    pair<1u, pair<0u, constant<0u>, constant<1u> >, pair<0u, constant<2u>, constant<3u> > >,
    pair<1u, pair<0u, constant<4u>, constant<5u> >, pair<0u, constant<6u>, constant<7u> > >
  > >::value, "Failed sequence #8");
  static_assert(std::is_same<typename sequence_pair<9u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<0u>, constant<1u> >, pair<0u, constant<2u>, constant<3u> > >,
      pair<1u, pair<0u, constant<4u>, constant<5u> >, pair<0u, constant<6u>, constant<7u> > >
    >,
    pair<2u,
      pair<1u, pair<0u, constant<8u> > >
    >
  > >::value, "Failed sequence #9");
}
