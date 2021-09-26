#include <cfloat>
#include <climits>
#include <cstdio>

#define MAXIMUM_TEMPLATE_INSTANTIATION_DEPTH 500u /* 17u */

/* ... [Utilities] */
namespace {
  namespace {
    template <typename type, type...> union collection;
    template <typename...> union pack;
  }

  template <std::size_t, typename...> union shift_left;
  template <std::size_t, typename...> union shift_right;
  template <std::size_t, typename...> union slice_begin;
  template <typename...> union reverse;

  template <typename, typename...> union first_t;
  template <typename, typename...> union last_t;
  template <std::size_t, typename, typename...> union indexed_t;
}

namespace {
  // ... ->> get first type in parameter pack
  template <typename base, typename...>
  union first_t {
    typedef base type;
  };

  // ... ->> get type at specified index in parameter pack
  template <std::size_t count, typename base, typename... types>
  union indexed_t {
    typedef typename indexed_t<count - 1u, types...>::type type;
  };

  template <typename base, typename... types>
  union indexed_t<0u, base, types...> {
    typedef base type;
  };

  // ... ->> get last type in parameter pack
  template <typename base, typename...>
  union last_t {
    typedef base type;
  };

  template <typename typeA, typename typeB, typename... types>
  union last_t<typeA, typeB, types...> {
    typedef typename last_t<typeB, types...>::type type;
  };

  // ... ->> cycle type parameter pack
  template <std::size_t count, typename... types>
  union shift_left {
    private:
      enum { end = sizeof...(types) - count };

      template <std::size_t subcount, typename base, typename... bases>
      union parse { typedef typename parse<subcount - 1u, bases..., base>::type type; };

      template <typename base, typename... bases>
      union parse<end, base, bases...> { typedef pack<base, bases...> type; };

    public:
      typedef typename parse<3u, types...>::type type;
  };

  template <std::size_t count, typename... types>
  union shift_right {
    private:
      enum { end = count };

      template <std::size_t subcount, typename base, typename... bases>
      union parse { typedef typename parse<subcount - 1u, bases..., base>::type type; };

      template <typename base, typename... bases>
      union parse<end, base, bases...> { typedef pack<base, bases...> type; };

    public:
      typedef typename parse<3u, types...>::type type;
  };

  // ... ->> trim parameter pack
  template <std::size_t count, typename base, typename... types>
  union slice_begin<count, base, types...> {
    typedef typename slice_begin<count - 1u, types...>::type type;
  };

  template <typename base, typename... types>
  union slice_begin<0u, base, types...> {
    typedef pack<base, types...> type;
  };

  template <typename... types>
  union slice_begin<0u, types...> {
    typedef pack<types...> type;
  };

  template <std::size_t count, typename... types>
  union slice_end {
    typedef typename slice_end<count, typename reverse<types...>::type>::type type;
  };

  template <std::size_t count, typename... types>
  union slice_end<count, pack<types...> > {
    typedef typename slice_end<0u, typename slice_begin<count, types...>::type>::type type;
  };

  template <typename... types>
  union slice_end<0u, pack<types...> > {
    typedef typename reverse<types...>::type type;
  };

  // ... ->> reverse type parameter pack
  template <typename... types>
  union reverse {
    private:
      enum { length = sizeof...(types) };

      template <std::size_t... indexes>
      union parse {
        typedef typename parse<sizeof...(indexes), indexes...>::type type;
      };

      template <std::size_t... indexes>
      union parse<length, indexes...> {
        typedef pack<typename indexed_t<indexes, types...>::type...> type;
      };

    public:
      typedef typename parse<>::type type;
  };
}

/* ... */
template <typename, class, class>
struct internal_trait;

template <typename packedExtension, typename... packedTypes, typename... types>
struct internal_trait<packedExtension, pack<packedTypes...>, pack<types...> > {
  template <template <packedTypes..., packedExtension...> class trait, packedTypes... parameters, packedExtension... extensions>
  union packed { typedef trait<parameters..., extensions...> type; };

  template <template <types...> class trait, types... parameters>
  union untyped { typedef trait<parameters...> type; };
};

template <typename type, typename... types>
struct trait final : public internal_trait<typename last_t<type, types...>::type, typename slice_end<1u, type, types...>::type, pack<type, types...> > {};

/* Main */
template <int, bool...> union dummyA {};
template <int, bool> union dummyB {};

int main() {
  trait<int, bool>::packed<dummyA, 0, false, true, false>::type();
  trait<int, bool>::untyped<dummyB, 0, false>::type();
}


#include <cfloat>
#include <cstdio>

/* ... */
constexpr bool check_squared(long double const number, long double const compare, int const bit) noexcept {
  return bit < 13 && number >= compare * compare;
}

constexpr int getexp_bits(long double const number, long double const compare, int bit) noexcept {
  return (
    false == check_squared(number, compare, bit)
    ? number >= compare ? (1 << bit) | getexp_bits(number / compare, 2.0L, 0) : 0
    : getexp_bits(number, compare * compare, bit+1)
  );
}

constexpr int getexp(long double const number) noexcept {
 return getexp_bits(number, 2.0L, 0);
}

/* Main */
int main() {
  constexpr int e = getexp(LDBL_MAX);
  std::printf("%i", e);
}
