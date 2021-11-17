#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>

/* ... */
namespace traits {
  template <std::size_t...>
  struct multiply final {
    constexpr static std::size_t value = 1u;
  };

  template <std::size_t argument, std::size_t... arguments>
  struct multiply<argument, arguments...> final {
    constexpr static std::size_t value = argument * multiply<arguments...>::value;
  };

  // ...
  template <std::size_t... values>
  struct permutation final {
    template <class>
    struct concat;

    template <std::size_t... subvalues>
    struct concat<permutation<subvalues...> > final {
      typedef permutation<values..., subvalues...> type;
    };

    // ...
    template <typename = void>
    struct first final {
      private:
        template <std::size_t subvalue, std::size_t...>
        struct valueof final {
          constexpr static std::size_t value = subvalue;
        };

      public:
        constexpr static std::size_t value = valueof<values...>::value;
    };

    // ...
    template <typename = void>
    struct last final {
      private:
        template <std::size_t subvalue, std::size_t... subvalues>
        struct valueof final {
          constexpr static std::size_t value = valueof<subvalues...>::value;
        };

        template <std::size_t subvalue>
        struct valueof<subvalue> final {
          constexpr static std::size_t value = subvalue;
        };

      public:
        constexpr static std::size_t value = valueof<values...>::value;
    };

    // ...
    template <class>
    struct next;

    template <std::size_t... subvalues>
    struct next<permutation<subvalues...> > final {
      private:
        template <class, class, class>
        struct valueof final {
          typedef permutation<values...> type;
        };

        template <std::size_t limit, std::size_t next, std::size_t... limits, std::size_t... nexts, std::size_t... rest>
        struct valueof<permutation<limit, limits...>, permutation<next, nexts...>, permutation<rest...> > final {
          typedef typename std::conditional<
            permutation<limit, limits...>::template last<>::value == permutation<next, nexts...>::template last<>::value,
            typename valueof<typename permutation<limit, limits...>::template pop<>::type, typename permutation<next, nexts...>::template pop<>::type, permutation<0u, rest...> >::type,
            typename permutation<next, nexts...>::template pop<>::type::template concat<permutation<1u + permutation<next, nexts...>::template last<>::value> >::type::template concat<permutation<rest...> >::type
          >::type type;
        };

      public:
        typedef typename valueof<permutation<values...>, permutation<subvalues...>, permutation<> >::type type;
    };

    // ...
    // template <class>
    struct permutate final {};

    // ...
    template <typename = void>
    struct pop final {
      private:
        template <class, std::size_t...>
        struct valueof;

        template <std::size_t... subvalues, std::size_t subvalue>
        struct valueof<permutation<subvalues...>, subvalue> final {
          typedef permutation<subvalues...> type;
        };

        template <std::size_t... popped, std::size_t subvalue, std::size_t... subvalues>
        struct valueof<permutation<popped...>, subvalue, subvalues...> final {
          typedef typename valueof<permutation<popped..., subvalue>, subvalues...>::type type;
        };

      public:
        typedef typename valueof<permutation<>, values...>::type type;
    };

    // ...
    template <typename = void>
    struct unshift final {
      private:
        template <std::size_t, std::size_t... subvalues>
        struct valueof final {
          typedef permutation<subvalues...> type;
        };

      public:
        typedef typename valueof<values...>::type type;
    };

    // ...
    template <typename = void>
    struct zero final {
      private:
        template <std::size_t count, std::size_t...>
        struct valueof final {
          typedef typename valueof<count - 1u, 0u>::type type;
        };

        template <std::size_t... subvalues>
        struct valueof<0u, subvalues...> final {
          typedef permutation<subvalues...> type;
        };

      public:
        typedef typename valueof<sizeof...(values), values...>::type type;
    };
  };
}

// ...
template <typename base, std::size_t...>
class MultidimensionalArray;

template <typename base, std::size_t capacity, std::size_t... capacities>
class MultidimensionalArray<base, capacity, capacities...> final {
  template <typename, std::size_t...>
  friend class MultidimensionalArray;

  typedef typename MultidimensionalArray<base, capacities...>::type (type)[capacity];
  
  private:
    base value[traits::multiply<capacities...>::value];

    template <typename subtype>
    constexpr MultidimensionalArray(subtype array[], ...) noexcept {}
    
  public:
    template <typename subtype>
    constexpr MultidimensionalArray(subtype (&array)[capacity]) noexcept :
      MultidimensionalArray<base, capacity, capacities...>::MultidimensionalArray(
        static_cast<typename std::enable_if<
          std::is_same<
            typename std::remove_cv<subtype>::type,
            typename std::remove_cv<typename MultidimensionalArray<base, capacities...>::type>::type
          >::value, subtype (&)[capacity]
        >::type>(array),
        traits::template permutation<capacity, capacities...>::permutate{}
      )
    {}
};

template <typename base>
class MultidimensionalArray<base> final {
  template <typename, std::size_t...>
  friend class MultidimensionalArray;
  
  typedef base type;
};

/* Main */
int main() {
  static_assert(std::is_same<traits::permutation<0u, 1u>, typename traits::permutation<2u, 3u>::template next<traits::permutation<0u, 0u> >::type>::value, "");
}
