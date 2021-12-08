#include <cstddef>
#include <type_traits>

#define TEMPLATE_INSTANTIATION_DEPTH_MAX 512u

/* ... */
template <bool...> struct AND { constexpr static bool value = true; };
template <bool assertion, bool... assertions> struct AND<assertion, assertions...> { constexpr static bool value = assertion && AND<assertions...>::value; };

template <std::size_t argument> struct DECREMENT { constexpr static std::size_t value = argument - 1u; };

template <unsigned>              struct constant;
template <class...>              struct pack;
template <std::size_t, class...> struct pair;
  template <unsigned, unsigned = 0u, unsigned = 1u> struct sequence_pack;

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
    constexpr static bool value = TEMPLATE_INSTANTIATION_DEPTH_MAX == sizeof...(values) && AND<filled_pair<values>::value...>::value;
  };

  template <std::size_t depth, class... values>
  struct flatten_pair<pair<depth, values...> > {
    private:
      template <class flattened, class...>
      struct valueof {
        typedef flattened type;
      };

      template <class... flattened, unsigned subvalue, class... subpairs>
      struct valueof<pack<flattened...>, constant<subvalue>, subpairs...> {
        typedef typename valueof<pack<flattened..., constant<subvalue> >, subpairs...>::type type;
      };

      template <class... flattened, std::size_t subdepth, class... subvalues, class... subpairs>
      struct valueof<pack<flattened...>, pair<subdepth, subvalues...>, subpairs...> {
        typedef typename valueof<pack<flattened...>, subvalues..., subpairs...>::type type;
      };

    public:
      typedef typename valueof<pack<>, values...>::type type;
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
  struct push_pair<pair<depth, pair<DECREMENT<depth>::value, values...>, pairs...>, value> {
    private:
      template <class, class...>
      struct valueof;

      template <class... filled>
      struct valueof<pair<0u, filled...> > {
        typedef typename std::conditional<
          TEMPLATE_INSTANTIATION_DEPTH_MAX == sizeof...(filled),
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
        typedef typename valueof<typename push_pair<sequence, subbegin>::type, subbegin + increment, subend>::type type;
      };

      template <class sequence, unsigned subend>
      struct valueof<sequence, subend, subend> {
        typedef sequence type;
      };

    public:
      typedef typename valueof<pair<0u>, 0u == end ? 0u : begin, 0u == end ? begin : end>::type type;
  };

  // ...
  template <unsigned begin, unsigned end, unsigned increment>
  struct sequence_pack {
    private:
      template <class, unsigned, unsigned>
      struct valueof;

      template <class... values, unsigned subbegin, unsigned subend>
      struct valueof<pack<values...>, subbegin, subend> {
        typedef typename valueof<pack<values..., constant<subbegin> >, subbegin + increment, subend>::type type;
      };

      template <class... values, unsigned subend>
      struct valueof<pack<values...>, subend, subend> {
        typedef pack<values...> type;
      };

    public:
      typedef typename valueof<pack<>, 0u == end ? 0u : begin, 0u == end ? begin : end>::type type;
  };

/* Main */
int main() {}
