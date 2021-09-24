#include <cstddef>

/* ... */
template <typename type, type...> union collection;
template <typename...> union pack;

template <std::size_t count, typename base, typename... types>
union indexed_t { typedef typename indexed_t<count - 1u, types...>::type type; };

template <typename base, typename... types>
union indexed_t<0u, base, types...> { typedef base type; };

template <typename base, typename...>
union first_t { typedef base type; };

template <typename base, typename...>
union last_t { typedef base type; };

template <typename typeA, typename typeB, typename... types>
union last_t<typeA, typeB, types...> { typedef typename last_t<typeB, types...>::type type; };

// ...
template <class, typename...>
struct implemented_trait;

template <typename packedExtension, typename... packedTypes, typename... types>
struct implemented_trait<pack<packedExtension>, pack<types...>, pack<packedTypes...> > {
  template <template <packedTypes..., packedExtension...> class, packedTypes... parameters, packedExtension... extensions>
  union packed {};

  template <template <types...> class, types... parameters>
  union untyped {};
};

template <class, typename...>
struct internal_trait;

template <std::size_t... indexes, typename... types>
struct internal_trait<collection<std::size_t, indexes...>, types...> : public internal_trait<collection<std::size_t, sizeof...(types) - sizeof...(indexes) - 1u, indexes...>, types...> {};

template <std::size_t... indexes, typename... types>
struct internal_trait<collection<std::size_t, 0u, indexes...>, types...> : public implemented_trait<
  pack<typename last_t<types...>::type>,
  pack<typename indexed_t<indexes - 1u, types...>::type...>,
  pack<types...>
> {};

template <typename type, typename... types>
struct trait : public internal_trait<collection<std::size_t>, type, types...> {};

/* Main */
template <int, bool...> union dummyA {};
template <int, bool> union dummyB {};

int main() {
  trait<int, bool>::packed<dummyA, 0, false, true, false>();
  trait<int, bool>::untyped<dummyB, 0, false>();
}
