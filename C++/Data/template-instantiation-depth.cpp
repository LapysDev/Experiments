#include <cstddef>
#include <type_traits>

/* ... */
template <bool...> struct AND { constexpr static bool value = true; };
template <bool assertion, bool... assertions> struct AND<assertion, assertions...> { constexpr static bool value = assertion && AND<assertions...>::value; };

enum { MAX = 2u };

template <std::size_t>           struct constant;
template <std::size_t, class...> struct pair;
  template <std::size_t, class = pair<0u>, std::size_t = 0u > struct build_pair;
  template <class>                                            struct assess_pair;
  template <std::size_t, class, std::size_t = 0u>             struct generate_pair;

// ...
template <std::size_t>
struct constant {};

// ...
template <>
struct pair<0u> {
  constexpr static bool is_filled = false;

  template <std::size_t subvalue>
  struct next {
    typedef pair<0u, constant<subvalue> > type;
  };
};

template <std::size_t depth, std::size_t... values>
struct pair<depth, constant<values>...> {
  constexpr static bool is_filled = assess_pair<pair<depth, constant<values>...> >::filled;

  template <std::size_t subvalue>
  struct next {
    typedef typename std::conditional<
      MAX == sizeof...(values),
      pair<depth + 1u, pair<depth, constant<values>...>, pair<depth, constant<subvalue> > >,
      pair<depth + 0u, constant<values>..., constant<subvalue> >
    >::type type;
  };
};

template <std::size_t depth, class... value, class... values>
struct pair<depth, pair<depth - 1u, value...>, values...> {
  constexpr static bool is_filled = assess_pair<pair<depth, pair<depth - 1u, value...>, values...> >::filled;

  template <std::size_t subvalue>
  struct next {
    private:
      template <class, class...>
      struct valueof;

      template <class... filled>
      struct valueof<pair<0u, filled...> > {
        typedef typename std::conditional<
          MAX == sizeof...(filled),
          pair<depth + 1u, pair<depth, filled...>, typename generate_pair<depth, constant<subvalue> >::type>,
          pair<depth, filled..., typename generate_pair<depth - 1u, constant<subvalue> >::type>
        >::type type;
      };

      template <class subsubvalue, class... filled, class... subsubvalues>
      struct valueof<pair<0u, filled...>, subsubvalue, subsubvalues...> {
        typedef typename std::conditional<
          subsubvalue::is_filled,
          typename valueof<pair<0u, filled..., subsubvalue>, subsubvalues...>::type,
          pair<depth, filled..., typename subsubvalue::template next<subvalue>::type, subsubvalues...>
        >::type type;
      };

    public:
      typedef typename valueof<pair<0u>, pair<depth - 1u, value...>, values...>::type type;
  };
};
  template <std::size_t depth, class... values>
  struct assess_pair<pair<depth, values...> > {
    private:
      template <class>
      struct valueof {
        constexpr static bool filled = true;
      };

      template <std::size_t subdepth, class... subvalues>
      struct valueof<pair<subdepth, subvalues...> > {
        constexpr static bool filled = MAX == sizeof...(subvalues) && AND<valueof<subvalues>::filled...>::value;
      };

    public:
      constexpr static bool filled = valueof<pair<depth, values...> >::filled;
  };

  // ...
  template <std::size_t length, class value, std::size_t count>
  struct build_pair {
    typedef typename build_pair<length - 1u, typename value::template next<count + 1u>::type, count + 1u>::type type;
  };

  template <class value, std::size_t count>
  struct build_pair<0u, value, count> {
    typedef value type;
  };

  // ...
  template <std::size_t depth, class value, std::size_t count>
  struct generate_pair {
    typedef typename generate_pair<depth - 1u, pair<count, value>, count + 1u>::type type;
  };

  template <class value, std::size_t count>
  struct generate_pair<0u, value, count> {
    typedef pair<count, value> type;
  };

/* Main */
int main() {
  static_assert(std::is_same<typename build_pair<0u>::type, pair<0u> >::value, "A");
  static_assert(std::is_same<typename build_pair<1u>::type, pair<0u, constant<1u> > >::value, "B");
  static_assert(std::is_same<typename build_pair<2u>::type, pair<0u, constant<1u>, constant<2u> > >::value, "C");
  static_assert(std::is_same<typename build_pair<3u>::type, pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u> > > >::value, "D");
  static_assert(std::is_same<typename build_pair<4u>::type, pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > > >::value, "E");
  static_assert(std::is_same<typename build_pair<5u>::type, pair<2u,
    pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
    pair<1u, pair<0u, constant<5u> > >
  > >::value, "F");
  static_assert(std::is_same<typename build_pair<6u>::type, pair<2u,
    pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
    pair<1u, pair<0u, constant<5u>, constant<6u> > >
  > >::value, "G");
  static_assert(std::is_same<typename build_pair<7u>::type, pair<2u,
    pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
    pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u> > >
  > >::value, "H");
  static_assert(std::is_same<typename build_pair<8u>::type, pair<2u,
    pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
    pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
  > >::value, "I");

  static_assert(std::is_same<typename build_pair<9u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u> > >
    >
  > >::value, "J");

  static_assert(std::is_same<typename build_pair<10u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u>, constant<10u> > >
    >
  > >::value, "K");

  static_assert(std::is_same<typename build_pair<11u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u>, constant<10u> >, pair<0u, constant<11u> > >
    >
  > >::value, "L");

  static_assert(std::is_same<typename build_pair<12u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u>, constant<10u> >, pair<0u, constant<11u>, constant<12u> > >
    >
  > >::value, "M");

  static_assert(std::is_same<typename build_pair<13u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u>, constant<10u> >, pair<0u, constant<11u>, constant<12u> > >,
      pair<1u, pair<0u, constant<13u> > >
    >
  > >::value, "N");

  static_assert(std::is_same<typename build_pair<14u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u>, constant<10u> >, pair<0u, constant<11u>, constant<12u> > >,
      pair<1u, pair<0u, constant<13u>, constant<14u> > >
    >
  > >::value, "O");

  static_assert(std::is_same<typename build_pair<15u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u>, constant<10u> >, pair<0u, constant<11u>, constant<12u> > >,
      pair<1u, pair<0u, constant<13u>, constant<14u> >, pair<0u, constant<15u> > >
    >
  > >::value, "O");

  static_assert(std::is_same<typename build_pair<16u>::type, pair<3u,
    pair<2u,
      pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
      pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
    >,

    pair<2u,
      pair<1u, pair<0u, constant<9u>, constant<10u> >, pair<0u, constant<11u>, constant<12u> > >,
      pair<1u, pair<0u, constant<13u>, constant<14u> >, pair<0u, constant<15u>, constant<16u> > >
    >
  > >::value, "P");

  static_assert(std::is_same<typename build_pair<17u>::type, pair<4u,
    pair<3u,
      pair<2u,
        pair<1u, pair<0u, constant<1u>, constant<2u> >, pair<0u, constant<3u>, constant<4u> > >,
        pair<1u, pair<0u, constant<5u>, constant<6u> >, pair<0u, constant<7u>, constant<8u> > >
      >,

      pair<2u,
        pair<1u, pair<0u, constant<9u>, constant<10u> >, pair<0u, constant<11u>, constant<12u> > >,
        pair<1u, pair<0u, constant<13u>, constant<14u> >, pair<0u, constant<15u>, constant<16u> > >
      >
    >,

    pair<3u, pair<2u, pair<1u, pair<0u, constant<17u> > > > >
  > >::value, "Q");
}
