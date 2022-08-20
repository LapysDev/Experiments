#include <cstdio>
#include <type_traits>

/* ... */
#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning (disable: 177)
#endif

/* ... */
namespace {
  template <typename base, base based>
  struct constant final {
    constexpr static base value = based;
  };

  // ...
  template <typename... bases>
  struct pack final {
    template <typename... types>
    struct add final {
      typedef pack<bases..., types...> type;
    };
  };

  // ...
  template <typename base = void, base...>
  struct range;

  template <typename base, base index>
  struct range<base, index, index> final {
    typedef void next;
    typedef base type;

    /* ... */
    constexpr static base const current  = index;
    constexpr static bool const has_next = false;
  };

  template <typename base, base start, base end>
  struct range<base, start, end> final {
    typedef range<base, start + 1, end> next;
    typedef base                        type;

    constexpr static base const current  = start;
    constexpr static bool const has_next = true;
  };

  template <>
  struct range<void> {
    private:
      template <class functor, class pack, typename = void>
      struct assess_call final {
        struct type final { template <typename subtype> constexpr type(subtype&&) noexcept; };

        static bool const throwable = false;
        static bool const value     = false;
      };

      template <class functor, class... constants>
      struct assess_call<functor, pack<constants...>, decltype(static_cast<void>(functor::template call<constants::value...>()))> final {
        typedef decltype(functor::template call<constants::value...>()) type;

        static bool const throwable = false == noexcept(functor::template call<constants::value...>());
        static bool const value     = true;
      };

      // ...
      template <typename typeA, typename, typename = typeA>
      struct assess_instantiate final {
        static bool const value = false;
      };

      template <typename typeA, typename typeB>
      struct assess_instantiate<typeA, typeB, decltype(typeA(std::declval<typeB>()))> final {
        static bool const value = true;
      };

      /* ... */
      template <class functor, class... constants>
      constexpr static decltype(functor::template call<constants::value...>()) call(pack<constants...> const) noexcept(noexcept(functor::template call<constants::value...>())) {
        return functor::template call<constants::value...>();
      }

      // ... ->>
      template <class functor, class pack>
      constexpr static decltype(call<functor>(pack{})) subcall(pack const) noexcept(noexcept(call<functor>(pack{}))) {
        return call<functor>(pack{});
      }

      template <class functor, class pack, class range, class... ranges>
      constexpr static typename std::enable_if<false != range::has_next,
        typename std::conditional<
          false == assess_call<functor, typename pack::template add<constant<typename range::next::type, range::next::current>, constant<typename ranges::type, ranges::current>...>::type>::value,
          typename assess_call<functor, typename pack::template add<constant<typename range::type,       range::current>,       constant<typename ranges::type, ranges::current>...>::type>::type,
        typename std::conditional<
          false == assess_call<functor, typename pack::template add<constant<typename range::type,       range::current>,       constant<typename ranges::type, ranges::current>...>::type>::value,
          typename assess_call<functor, typename pack::template add<constant<typename range::next::type, range::next::current>, constant<typename ranges::type, ranges::current>...>::type>::type,
          typename std::conditional<
            assess_instantiate<
              typename assess_call<functor, typename pack::template add<constant<typename range::type,       range::current>,       constant<typename ranges::type, ranges::current>...>::type>::type,
              typename assess_call<functor, typename pack::template add<constant<typename range::next::type, range::next::current>, constant<typename ranges::type, ranges::current>...>::type>::type
            >::value,
            typename assess_call<functor, typename pack::template add<constant<typename range::type,       range::current>,       constant<typename ranges::type, ranges::current>...>::type>::type,
            typename assess_call<functor, typename pack::template add<constant<typename range::next::type, range::next::current>, constant<typename ranges::type, ranges::current>...>::type>::type
          >::type
        >::type
        >::type
      >::type subcall(pack const, typename range::type const value, typename ranges::type const... values) noexcept(!assess_call<functor, typename pack::template add<constant<typename range::type, range::current>, constant<typename ranges::type, ranges::current>...>::type>::throwable && !assess_call<functor, typename pack::template add<constant<typename range::next::type, range::next::current>, constant<typename ranges::type, ranges::current>...>::type>::throwable) {
        // attempt to merge all possible `return` types of `functor::template call<...>()`
        #ifdef _MSC_VER
          if (range::current == value) return subcall<functor, typename pack::template add<constant<typename range::type, range::current> >::type, ranges...>(typename pack::template add<constant<typename range::type, range::current> >::type{}, values...);
          return subcall<functor, pack, typename range::next, ranges...>(pack{}, value, values...);
        #else
          return range::current == value
            ? subcall<functor, typename pack::template add<constant<typename range::type, range::current> >::type, ranges...>(typename pack::template add<constant<typename range::type, range::current> >::type{}, values...)
            : subcall<functor, pack, typename range::next, ranges...>(pack{}, value, values...);
        #endif
      }

      template <class functor, class pack, class range, class... ranges>
      constexpr static typename std::enable_if<false == range::has_next, decltype(subcall<functor, typename pack::template add<constant<typename range::type, range::current> >::type, ranges...>(typename pack::template add<constant<typename range::type, range::current> >::type{}, std::declval<typename ranges::type>()...))>::type subcall(pack const, typename range::type const value, typename ranges::type const... values) noexcept(noexcept(subcall<functor, typename pack::template add<constant<typename range::type, range::current> >::type, ranges...>(typename pack::template add<constant<typename range::type, range::current> >::type{}, std::declval<typename ranges::type>()...))) {
        // out-of-`range` errors result in a null-pointer dereference
        #if defined(__clang__)
        # pragma clang diagnostic ignored "-Wnull-dereference"
        #elif defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
        # pragma warning (disable: 327)
        #endif

        return static_cast<void>(range::current == value ? 0x0u : *static_cast<unsigned char volatile*>(NULL)), subcall<functor, typename pack::template add<constant<typename range::type, range::current> >::type, ranges...>(typename pack::template add<constant<typename range::type, range::current> >::type{}, values...);
      }

    public:
      template <class functor, class... ranges>
      constexpr static decltype(subcall<functor, pack<>, ranges...>(pack<>{}, std::declval<typename ranges::type>()...)) call(typename ranges::type const... values) noexcept(noexcept(subcall<functor, pack<>, ranges...>(pack<>{}, values...))) {
        return subcall<functor, pack<>, ranges...>(pack<>{}, values...);
      }
  };
}

struct my_functor final {
  // ... ->> compile-time parameters
  template <char*, bool, int>
  constexpr static char const (&call() noexcept)[14] {
    return "Hello, World!";
  }
};

/* Main */
int main(int, char*[]) /* noexcept */ {
  // ... ->> runtime parameters
  constexpr char const (&string)[14] = range<>::call<my_functor,
    range<char*, nullptr, nullptr>,
    range<bool,  false,   true>,
    range<int,   -1,      1>
  >(nullptr, true, 0);

  std::puts(string);
}
