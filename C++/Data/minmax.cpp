#include <cstddef>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <version>
#if defined(__cpp_impl_three_way_comparison) || defined(__cpp_lib_three_way_comparison)
# include <compare>
#endif

/* ... */
#if defined(__clang__)
# pragma clang diagnostic ignored "-Wc++17-compat-mangling"
#elif defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning (disable: 177)
# pragma warning (disable: 383)
# pragma warning (disable: 3346)
#elif defined(__GNUC__)
# pragma GCC diagnostic ignored "-Wdeprecated"
# pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
# pragma GCC diagnostic ignored "-Wnoexcept-type"
#endif

/* ... */
template <typename type>
constexpr static type instanceof() noexcept;

/* ... */
template <typename base>
struct alias final {
  typedef base type;
};

// ...
template <typename baseA, typename baseB, typename = void>
struct assess_compare final {
  static bool const value = false;
};

#if defined(__cpp_impl_three_way_comparison) || defined(__cpp_lib_three_way_comparison)
  template <typename baseA, typename baseB>
  struct assess_compare<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>() <=> instanceof<baseB>()))> final {
    typedef decltype(instanceof<baseA>() <=> instanceof<baseB>()) type;
    static bool const value = true;
  };
#endif

// ...
template <typename baseA, typename baseB, typename = void>
struct assess_equals final {
  static bool const value = false;
};

template <typename baseA, typename baseB>
struct assess_equals<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>() == instanceof<baseB>()))> final {
  typedef decltype(instanceof<baseA>() == instanceof<baseB>()) type;
  static bool const value = true;
};

// ...
template <typename baseA, typename baseB, typename = void>
struct assess_greater_than final {
  static bool const value = false;
};

template <typename baseA, typename baseB>
struct assess_greater_than<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>() > instanceof<baseB>()))> final {
  typedef decltype(instanceof<baseA>() > instanceof<baseB>()) type;
  static bool const value = true;
};

// ...
template <typename baseA, typename baseB, typename = void>
struct assess_greater_than_equals final {
  static bool const value = false;
};

template <typename baseA, typename baseB>
struct assess_greater_than_equals<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>() >= instanceof<baseB>()))> final {
  typedef decltype(instanceof<baseA>() >= instanceof<baseB>()) type;
  static bool const value = true;
};

// ...
template <typename baseA, typename baseB, typename = baseA>
struct assess_instantiate final {
  static bool const value = false;
};

template <typename baseA, typename baseB>
struct assess_instantiate<baseA, baseB, decltype(baseA(instanceof<baseB>()))> final {
  typedef baseA type;
  static bool const value = true;
};

// ...
template <typename baseA, typename baseB, typename = void>
struct assess_lesser_than final {
  static bool const value = false;
};

template <typename baseA, typename baseB>
struct assess_lesser_than<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>() < instanceof<baseB>()))> final {
  typedef decltype(instanceof<baseA>() < instanceof<baseB>()) type;
  static bool const value = true;
};

// ...
template <typename baseA, typename baseB, typename = void>
struct assess_lesser_than_equals final {
  static bool const value = false;
};

template <typename baseA, typename baseB>
struct assess_lesser_than_equals<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>() <= instanceof<baseB>()))> final {
  typedef decltype(instanceof<baseA>() <= instanceof<baseB>()) type;
  static bool const value = true;
};

// ...
template <template <typename...> class assessor, typename baseA, typename baseB>
struct assess_minmax_compare final {
  private:
    template <template <typename...> class, bool>
    struct valueof;

    template <template <typename...> class subassessor>
    struct valueof<subassessor, false> final {
      static bool const value = false;
    };

    template <template <typename...> class subassessor>
    struct valueof<subassessor, true> final {
      static bool const value = assess_instantiate<bool, typename subassessor<baseA, baseB>::type>::value;
    };

  public:
    static bool const value = valueof<assessor, assessor<baseA, baseB>::value>::value;
};

template <typename baseA, typename baseB>
struct assess_minmax_compare<assess_compare, baseA, baseB> final {
  static bool const value = assess_compare<baseA, baseB>::value;
};

// ...
template <bool boolean, bool...>
struct boolean_and final {
  static bool const value = boolean;
};

template <bool booleanA, bool booleanB, bool... booleans>
struct boolean_and<booleanA, booleanB, booleans...> final {
  static bool const value = boolean_and<booleanA && booleanB, booleans...>::value;
};

// ...
template <class, typename typeA, typename typeB, typename = bool (*)(typeA&&, typeB&&)>
struct can_minmax_compare final {
  static bool const value = false;
};

template <class comparator, typename typeA, typename typeB>
struct can_minmax_compare<comparator, typeA, typeB, decltype(static_cast<bool (*)(typeA&&, typeB&&)>(instanceof<comparator>()))> final {
  static bool const value = true;
};

// ...
struct null final {};

// ...
template <bool, typename, typename = null>
struct conditional;

template <typename base>
struct conditional<false, base, null> final {};

template <typename baseA, typename baseB>
struct conditional<false, baseA, baseB> final {
  typedef baseB type;
};

template <typename baseA, typename baseB>
struct conditional<true, baseA, baseB> final {
  typedef baseA type;
};

// ...
template <typename>
struct is_array final {
  static bool const value = false;
};

template <typename base>
struct is_array<base[]> final {
  static bool const value = true;
};

template <typename base, std::size_t capacity>
struct is_array<base[capacity]> final {
  static bool const value = true;
};

// ...
template <typename>
struct is_const final {
  static bool const value = false;
};

template <typename base>
struct is_const<base const> final {
  static bool const value = true;
};

// ...
template <typename>
struct is_lvalue_reference final {
  static bool const value = false;
};

template <typename base>
struct is_lvalue_reference<base&> final {
  static bool const value = true;
};

// ...
template <typename>
struct is_pointer final {
  static bool const value = false;
};

template <typename base>
struct is_pointer<base*> final {
  static bool const value = true;
};

template <typename base>
struct is_pointer<base* const> final {
  static bool const value = true;
};

template <typename base>
struct is_pointer<base* const volatile> final {
  static bool const value = true;
};

template <typename base>
struct is_pointer<base* volatile> final {
  static bool const value = true;
};

// ...
template <typename>
struct is_rvalue_reference final {
  static bool const value = false;
};

template <typename base>
struct is_rvalue_reference<base&&> final {
  static bool const value = true;
};

// ...
template <typename>
struct is_void final {
  static bool const value = false;
};

template <>
struct is_void<void> final {
  static bool const value = true;
};

template <>
struct is_void<void const> final {
  static bool const value = true;
};

template <>
struct is_void<void const volatile> final {
  static bool const value = true;
};

template <>
struct is_void<void volatile> final {
  static bool const value = true;
};

// ...
template <typename>
struct is_volatile final {
  static bool const value = false;
};

template <typename base>
struct is_volatile<base volatile> final {
  static bool const value = true;
};

// ...
template <typename base>
struct remove_reference final {
  typedef base type;
};

template <typename base>
struct remove_reference<base&> final {
  typedef base type;
};

template <typename base>
struct remove_reference<base&&> final {
  typedef base type;
};

// ...
template <typename... bases>
struct pack final {
  template <std::size_t index>
  struct at final {
    private:
      template <std::size_t, class>
      struct valueof;

      template <typename subbase, typename... subbases>
      struct valueof<0u, pack<subbase, subbases...> > final {
        typedef subbase type;
      };

      template <std::size_t subindex, typename subbase, typename... subbases>
      struct valueof<subindex, pack<subbase, subbases...> > final {
        typedef typename valueof<subindex - 1u, pack<subbases...> >::type type;
      };

    public:
      typedef typename valueof<index, pack<bases...> >::type type;
  };

  // ...
  template <template <typename...> class predicator>
  struct filter final {
    private:
      template <class, class>
      struct valueof;

      template <typename... types>
      struct valueof<pack<types...>, pack<> > final {
        typedef pack<types...> type;
      };

      template <typename... types, typename subbase, typename... subbases>
      struct valueof<pack<types...>, pack<subbase, subbases...> > final {
        typedef typename conditional<
          predicator<subbase>::value,
          typename valueof<pack<types..., subbase>, pack<subbases...> >::type,
          typename valueof<pack<types...>,          pack<subbases...> >::type
        >::type type;
      };

    public:
      typedef typename valueof<pack<>, pack<bases...> >::type type;
  };

  // ...
  struct first final {
    typedef typename at<0u>::type type;
  };

  // ...
  struct last final {
    typedef typename at<sizeof...(bases) - (0u != sizeof...(bases))>::type type;
  };

  // ...
  template <template <typename...> class transformer>
  struct map final {
    private:
      template <class, class>
      struct valueof;

      template <typename... types>
      struct valueof<pack<types...>, pack<> > final {
        typedef pack<types...> type;
      };

      template <typename... types, typename subbase, typename... subbases>
      struct valueof<pack<types...>, pack<subbase, subbases...> > final {
        typedef typename valueof<
          pack<types..., typename transformer<subbase>::type>,
          pack<subbases...>
        >::type type;
      };

    public:
      typedef typename valueof<pack<>, pack<bases...> >::type type;
  };

  // ...
  struct common final {
    private:
      template <typename subbase>
      struct is_const_volatile final {
        static bool const value = is_const<subbase>::value && is_volatile<subbase>::value;
      };

      // ...
      template <std::size_t, class, class>
      struct valueof;

      template <typename... types, typename subbase, typename... subbases>
      struct valueof<0u, pack<types...>, pack<subbase, subbases...> > final {
        private:
          template <class subsubbases, typename = void>
          struct subvalueof final {
            private:
              template <class>
              struct subsubvalueof final {
                typedef void type;
              };

              template <typename subsubsubbaseA, typename subsubsubbaseB>
              struct subsubvalueof<pack<subsubsubbaseA, subsubsubbaseB> > final {
                typedef typename conditional<(sizeof(subsubsubbaseB) >= sizeof(subsubsubbaseA)), subsubsubbaseB, subsubsubbaseA>::type type;
              };

            public:
              typedef typename subsubvalueof<subsubbases>::type type;
          };

          template <typename subsubbase>
          struct subvalueof<pack<subsubbase> > final {
            typedef subsubbase type;
          };

          template <typename subsubbaseA, typename subsubbaseB>
          struct subvalueof<pack<subsubbaseA, subsubbaseB>, decltype(static_cast<void>(true ? instanceof<subsubbaseA>() : instanceof<subsubbaseB>()))> final {
            typedef decltype(true ? instanceof<subsubbaseA>() : instanceof<subsubbaseB>()) type;
          };

          template <typename subsubbaseA, typename subsubbaseB, typename subsubbase, typename... subsubbases>
          struct subvalueof<pack<subsubbaseA, subsubbaseB, subsubbase, subsubbases...> > final {
            typedef typename subvalueof<pack<typename subvalueof<pack<subsubbaseA, subsubbaseB> >::type, subsubbase, subsubbases...> >::type type;
          };

        public:
          typedef
            typename conditional<
              pack<types...>::template filter<is_lvalue_reference>::type::template map<remove_reference>::type::template filter<is_const_volatile>::type::length == 1u,
              typename pack<types...>::template filter<is_lvalue_reference>::type::template map<remove_reference>::type::template filter<is_const_volatile>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_lvalue_reference>::type::template map<remove_reference>::type::template filter<is_const>::type::length == 1u,
              typename pack<types...>::template filter<is_lvalue_reference>::type::template map<remove_reference>::type::template filter<is_const>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_lvalue_reference>::type::template map<remove_reference>::type::template filter<is_volatile>::type::length == 1u,
              typename pack<types...>::template filter<is_lvalue_reference>::type::template map<remove_reference>::type::template filter<is_volatile>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_lvalue_reference>::type::length == 1u,
              typename pack<types...>::template filter<is_lvalue_reference>::type::template at<0u>,

            typename conditional<
              pack<types...>::template filter<is_rvalue_reference>::type::template map<remove_reference>::type::template filter<is_const_volatile>::type::length == 1u,
              typename pack<types...>::template filter<is_rvalue_reference>::type::template map<remove_reference>::type::template filter<is_const_volatile>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_rvalue_reference>::type::template map<remove_reference>::type::template filter<is_const>::type::length == 1u,
              typename pack<types...>::template filter<is_rvalue_reference>::type::template map<remove_reference>::type::template filter<is_const>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_rvalue_reference>::type::template map<remove_reference>::type::template filter<is_volatile>::type::length == 1u,
              typename pack<types...>::template filter<is_rvalue_reference>::type::template map<remove_reference>::type::template filter<is_volatile>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_rvalue_reference>::type::length == 1u,
              typename pack<types...>::template filter<is_rvalue_reference>::type::template at<0u>,

            typename conditional<
              pack<types...>::template filter<is_const_volatile>::type::length == 1u,
              typename pack<types...>::template filter<is_const_volatile>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_const>::type::length == 1u,
              typename pack<types...>::template filter<is_const>::type::template at<0u>,
            typename conditional<
              pack<types...>::template filter<is_volatile>::type::length == 1u,
              typename pack<types...>::template filter<is_volatile>::type::template at<0u>,

            typename conditional<
              pack<types...>::length == 1u,
              typename pack<types...>::template at<0u>,
              alias<typename subvalueof<pack<types...> >::type>
            >::type
            >::type
            >::type
            >::type
            >::type
            >::type
            >::type
            >::type
            >::type
            >::type
            >::type
            >::type
          ::type type;
      };

      template <std::size_t count, typename... types, typename subbase, typename... subbases>
      struct valueof<count, pack<types...>, pack<subbase, subbases...> > final {
        typedef typename conditional<
          boolean_and<true, assess_instantiate<subbase, subbases>::value...>::value,
          typename valueof<count - 1u, pack<types..., subbase>, pack<subbases..., subbase> >::type,
          typename valueof<count - 1u, pack<types...>,          pack<subbases..., subbase> >::type
        >::type type;
      };

    public:
      typedef typename valueof<sizeof...(bases), pack<>, pack<bases...> >::type type;
  };

  // ...
  template <std::size_t begin, std::size_t end>
  struct slice final {
    private:
      template <std::size_t, typename...>        struct beginof;
      template <std::size_t, class, typename...> struct endof;

      /* ... */
      template <std::size_t count, typename subbase, typename... subbases>
      struct beginof<count, subbase, subbases...> final {
        friend struct slice;
        private: typedef typename beginof<count - 1u, subbases...>::type type;
      };

      template <typename subbase, typename... subbases>
      struct beginof<0u, subbase, subbases...> final {
        friend struct slice;
        private: typedef typename endof<end - 1u, pack<subbase>, subbases...>::type type;
      };

      // ...
      template <std::size_t count, typename... sliced, typename subbase, typename... subbases>
      struct endof<count, pack<sliced...>, subbase, subbases...> final {
        friend struct slice;
        private: typedef typename endof<count - 1u, pack<sliced..., subbase>, subbases...>::type type;
      };

      template <typename... sliced, typename subbase, typename... subbases>
      struct endof<0u, pack<sliced...>, subbase, subbases...> final {
        friend struct slice;
        private: typedef pack<sliced...> type;
      };

    public:
      typedef typename beginof<begin, bases..., void>::type type;
  };

  template <std::size_t index>
  struct slice<index, index> final {
    typedef pack<> type;
  };

  /* ... */
  static std::size_t const length = sizeof...(bases);
};

/* ... */
template <typename type>
constexpr type&& pass(typename remove_reference<type>::type& object) noexcept {
  return static_cast<type&&>(object);
}

template <typename type>
constexpr type&& pass(typename remove_reference<type>::type&& object) noexcept {
  return static_cast<type&&>(object);
}

// ...
template <std::size_t index, typename type, typename... types>
constexpr typename conditional<0u == index, type&&>::type at(type&& object, types&&...) noexcept {
  return pass<type>(object);
}

template <std::size_t index, typename type, typename... types>
constexpr typename conditional<0u != index, typename pack<type, types...>::template at<index <= sizeof...(types) ? index : 0u>::type>::type at(type&&, types&&... objects) noexcept {
  return at<index - 1u>(pass<types>(objects)...);
}

// ...
template <typename type>
constexpr bool minmax_compare(type&&) noexcept(true) {
  return true;
}

// ...
template <typename typeA, typename typeB>
constexpr static bool minmax_equals(typeA&&, typeB&&) noexcept(true);

// ...
template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than_equals, type, int>::value,
  bool
>::type max_assess_compare(type&& comparison) noexcept(true) {
  return pass<type>(comparison) >= 0;
}

template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_equals,              type, int>::value &&
  false != assess_minmax_compare<assess_greater_than,        type, int>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, type, int>::value,
  bool
>::type max_assess_compare(type&& comparison) noexcept(true) {
  return static_cast<bool>(pass<type>(comparison) > 0) || static_cast<bool>(pass<type>(comparison) == 0);
}

template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_equals,              type, int>::value &&
  false == assess_minmax_compare<assess_greater_than,        type, int>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, type, int>::value,
  bool
>::type max_assess_compare(type&& comparison) noexcept(true) {
  return pass<type>(comparison) == 0;
}

template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than,        type, int>::value &&
  false == assess_minmax_compare<assess_equals,              type, int>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, type, int>::value,
  bool
>::type max_assess_compare(type&& comparison) noexcept(true) {
  return pass<type>(comparison) > 0;
}

template <typename type>
constexpr typename conditional<
  false == assess_minmax_compare<assess_greater_than,        type, int>::value &&
  false == assess_minmax_compare<assess_equals,              type, int>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, type, int>::value,
  bool
>::type max_assess_compare(type&&) noexcept(false) {
  return true;
}

// ...
template <typename typeA, typename typeB>
constexpr bool max_equals(typeA&& objectA, typeB&& objectB)
  #if __cplusplus >= 201703L || defined(_MSC_VER)
    noexcept(noexcept(static_cast<bool>(instanceof<typeA&&>() == instanceof<typeB&&>())))
  #else
    throw(std::logic_error)
  #endif
{
  static_assert(assess_minmax_compare<assess_equals, typeA, typeB>::value, "Unable to determine maximum of objects using `max(...)` due to lacking viable comparison operators");
  return static_cast<bool>(pass<typeA>(objectA) == pass<typeB>(objectB)) || (
    (throw std::logic_error("Unable to determine minimum of objects using `max(...)` due to lacking viable comparison operators")),
    minmax_equals(pass<typeA>(objectA), pass<typeB>(objectB)),
    true
  );
}

// ...
template <typename typeA, typename typeB>
constexpr bool max_compare(typeA* const objectA, typeB* const objectB) noexcept(noexcept(std::greater<void*>{}.operator ()(instanceof<void*>(), instanceof<void*>()))) {
  return std::greater<void*>{}.operator ()((void*) objectA, (void*) objectB);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than, typeA, typeB>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeA>(objectA) > pass<typeB>(objectB);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than, typeA, typeB>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeB>(objectB) > pass<typeA>(objectA));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than, typeB, typeA>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeA>(objectA) < pass<typeB>(objectB));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than,  typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,  typeA, typeB>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeB>(objectB) < pass<typeA>(objectA);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeA>(objectA) >= pass<typeB>(objectB);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeB>(objectB) >= pass<typeA>(objectA));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeA>(objectA) <= pass<typeB>(objectB));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than_equals,  typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeB>(objectB) <= pass<typeA>(objectA);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_compare,             typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeB, typeA>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB)
  #if defined(__cpp_impl_three_way_comparison) || defined(__cpp_lib_three_way_comparison)
    noexcept(noexcept(noexcept(max_assess_compare(instanceof<typeA&&>() <=> instanceof<typeB&&>())) ? max_assess_compare(instanceof<typeA&&>() <=> instanceof<typeB&&>()) : max_equals(instanceof<typeA&&>(), instanceof<typeB&&>())))
  #else
    noexcept(true)
  #endif
{
  #if defined(__cpp_impl_three_way_comparison) || defined(__cpp_lib_three_way_comparison)
    return noexcept(max_assess_compare(instanceof<typeA&&>() <=> instanceof<typeB&&>())) ?
      max_assess_compare(pass<typeA>(objectA) <=> pass<typeB>(objectB)) :
      max_equals        (pass<typeA>(objectA),    pass<typeB>(objectB));
  #else
    return false;
  #endif
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false == assess_minmax_compare<assess_compare,             typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeB, typeA>::value,
  bool
>::type max_compare(typeA&& objectA, typeB&& objectB) noexcept(noexcept(max_equals(instanceof<typeA&&>(), instanceof<typeB&&>()))) {
  return max_equals(pass<typeA>(objectA), pass<typeB>(objectB));
}

// ...
template <typename type>
constexpr type&& max(type&& object) noexcept(noexcept(minmax_compare(instanceof<type&&>()))) {
  return minmax_compare(pass<type>(object)), pass<type>(object);
}

template <typename type>
constexpr decltype(max(instanceof<type&&>())) max(type&& object, std::nullptr_t const) noexcept(noexcept(max(instanceof<type&&>()))) {
  return max(pass<type>(object));
}

template <typename type>
constexpr type&& max(type&& object, bool (*const comparator)(type&&)) noexcept(noexcept(NULL == comparator && noexcept(minmax_compare(instanceof<type&&>())))) {
  return (NULL == comparator ? static_cast<bool (*)(type&&)>(&minmax_compare) : comparator)(pass<type>(object)), pass<type>(object);
}

template <typename typeA, typename typeB>
constexpr typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&& max(typeA&& objectA, typeB&& objectB) noexcept(noexcept(max_compare(instanceof<typeA&&>(), instanceof<typeB&&>()))) {
  return max_compare(pass<typeA>(objectA), pass<typeB>(objectB)) ?
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeA>(objectA) :
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeB>(objectB);
}

template <typename typeA, typename typeB>
constexpr decltype(max(instanceof<typeA&&>(), instanceof<typeB&&>())) max(typeA&& objectA, typeB&& objectB, std::nullptr_t const) noexcept(noexcept(max(instanceof<typeA&&>(), instanceof<typeB&&>()))) {
  return max(pass<typeA>(objectA), pass<typeB>(objectB));
}

template <typename typeA, typename typeB>
constexpr typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&& max(typeA&& objectA, typeB&& objectB, bool (*const comparator)(typeA&&, typeB&&)) noexcept(noexcept((NULL == comparator || comparator == static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&max_compare)) && noexcept(max_compare(instanceof<typeA&&>(), instanceof<typeB&&>())))) {
  return (NULL == comparator || comparator == static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&max_compare) ? static_cast<bool (*)(typeA&&, typeB&&)>(&max_compare) : comparator)(pass<typeA>(objectA), pass<typeB>(objectB)) ?
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeA>(objectA) :
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeB>(objectB);
}

#ifdef __cpp_noexcept_function_type
  template <typename type>
  constexpr type&& max(type&& object, bool (*const comparator)(type&&) noexcept) noexcept(noexcept((NULL != comparator && comparator != static_cast<bool (*)(type&&) noexcept>(&minmax_compare)) || noexcept(minmax_compare(instanceof<type&&>())))) {
    return (NULL == comparator || comparator == static_cast<bool (*)(type&&) noexcept>(&minmax_compare) ? static_cast<bool (*)(type&&) noexcept>(&minmax_compare) : comparator)(pass<type>(object)), static_cast<type&&>(object);
  }

  template <typename typeA, typename typeB>
  constexpr typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&& max(typeA&& objectA, typeB&& objectB, bool (*const comparator)(typeA&&, typeB&&) noexcept) noexcept(noexcept((NULL != comparator && comparator != static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&max_compare)) || noexcept(max_compare(instanceof<typeA&&>(), instanceof<typeB&&>())))) {
    return (NULL == comparator || comparator == static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&max_compare) ? static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&max_compare) : comparator)(pass<typeA>(objectA), pass<typeB>(objectB)) ?
      (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeA>(objectA) :
      (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeB>(objectB);
  }
#endif

#ifdef _MSC_VER
  template <typename typeA, typename typeB, typename typeC, typename... types>
  constexpr typename conditional<
    can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value,
    typename conditional<is_void<typename pack<typeA, typeB, typeC, types...>::template slice<0u, 1u + sizeof...(types)>::type::common::type>::value, typeA, typename pack<typeA, typeB, typeC, types...>::template slice<0u, 1u + sizeof...(types)>::type::common::type>::type,
    typename conditional<is_void<typename pack<typeA, typeB, typeC, types...>                                                 ::common::type>::value, typeA, typename pack<typeA, typeB, typeC, types...>                                                 ::common::type>::type
  >::type&& max(typeA&& objectA, typeB&& objectB, typeC&& objectC, types&&... objects) noexcept(noexcept(max(max(instanceof<typeA&&>(), instanceof<typeB&&>(), instanceof<bool (*)(typeA&&, typeB&&)>()), instanceof<typeC&&>(), instanceof<types&&>()...))) {
    return max(max(pass<typeA>(objectA), pass<typeB>(objectB),
      can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value
      ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, pass<typeC>(objectC), pass<types>(objects)...))
      : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)
    ), pass<typeC>(objectC), pass<types>(objects)...);
  }
#else
  template <typename typeA, typename typeB, typename typeC, typename... types>
  constexpr decltype(max(max(instanceof<typeA&&>(), instanceof<typeB&&>(), can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, instanceof<typeC&&>(), instanceof<types&&>()...)) : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)), instanceof<typeC&&>(), instanceof<types&&>()...)) max(typeA&& objectA, typeB&& objectB, typeC&& objectC, types&&... objects) noexcept(noexcept(max(max(instanceof<typeA&&>(), instanceof<typeB&&>(), can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, instanceof<typeC&&>(), instanceof<types&&>()...)) : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)), instanceof<typeC&&>(), instanceof<types&&>()...))) {
    return max(max(pass<typeA>(objectA), pass<typeB>(objectB), can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, pass<typeC>(objectC), pass<types>(objects)...)) : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)), pass<typeC>(objectC), pass<types>(objects)...);
  }
#endif

// ...
template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than_equals, type, int>::value,
  bool
>::type min_assess_compare(type&& comparison) noexcept(true) {
  return pass<type>(comparison) <= 0;
}

template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_equals,             type, int>::value &&
  false != assess_minmax_compare<assess_lesser_than,        type, int>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, type, int>::value,
  bool
>::type min_assess_compare(type&& comparison) noexcept(true) {
  return static_cast<bool>(pass<type>(comparison) < 0) || static_cast<bool>(pass<type>(comparison) == 0);
}

template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_equals,             type, int>::value &&
  false == assess_minmax_compare<assess_lesser_than,        type, int>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, type, int>::value,
  bool
>::type min_assess_compare(type&& comparison) noexcept(true) {
  return pass<type>(comparison) == 0;
}

template <typename type>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than,        type, int>::value &&
  false == assess_minmax_compare<assess_equals,             type, int>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, type, int>::value,
  bool
>::type min_assess_compare(type&& comparison) noexcept(true) {
  return pass<type>(comparison) < 0;
}

template <typename type>
constexpr typename conditional<
  false == assess_minmax_compare<assess_lesser_than,        type, int>::value &&
  false == assess_minmax_compare<assess_equals,             type, int>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, type, int>::value,
  bool
>::type min_assess_compare(type&&) noexcept(false) {
  return true;
}

// ...
template <typename typeA, typename typeB>
constexpr bool min_equals(typeA&& objectA, typeB&& objectB)
  #if __cplusplus >= 201703L || defined(_MSC_VER)
    noexcept(noexcept(static_cast<bool>(instanceof<typeA&&>() == instanceof<typeB&&>())))
  #else
    throw(std::logic_error)
  #endif
{
  static_assert(assess_minmax_compare<assess_equals, typeA, typeB>::value, "Unable to determine minimum of objects using `min(...)` due to lacking viable comparison operators");
  return static_cast<bool>(pass<typeA>(objectA) == pass<typeB>(objectB)) || (
    (throw std::logic_error("Unable to determine minimum of objects using `min(...)` due to lacking viable comparison operators")),
    minmax_equals(pass<typeA>(objectA), pass<typeB>(objectB)),
    true
  );
}

// ...
template <typename typeA, typename typeB>
constexpr bool min_compare(typeA* const objectA, typeB* const objectB) noexcept(noexcept(std::less_equal<void*>{}.operator ()(instanceof<void*>(), instanceof<void*>()))) {
  return std::less_equal<void*>{}.operator ()((void*) objectA, (void*) objectB);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than_equals, typeA, typeB>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeA>(objectA) <= pass<typeB>(objectB);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeA, typeB>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeB>(objectB) <= pass<typeA>(objectA));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than,       typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeA>(objectA) > pass<typeB>(objectB));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than,       typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than,       typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeB>(objectB) > pass<typeA>(objectA);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,       typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,       typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeA>(objectA) < pass<typeB>(objectB);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_lesser_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than,       typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,       typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals, typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeB>(objectB) < pass<typeA>(objectA));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return false == static_cast<bool>(pass<typeA>(objectA) >= pass<typeB>(objectB));
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(true) {
  return pass<typeB>(objectB) >= pass<typeA>(objectA);
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false != assess_minmax_compare<assess_compare,             typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB)
  #if defined(__cpp_impl_three_way_comparison) || defined(__cpp_lib_three_way_comparison)
    noexcept(noexcept(noexcept(min_assess_compare(instanceof<typeA&&>() <=> instanceof<typeB&&>())) ? min_assess_compare(instanceof<typeA&&>() <=> instanceof<typeB&&>()) : min_equals(instanceof<typeA&&>(), instanceof<typeB&&>())))
  #else
    noexcept(true)
  #endif
{
  #if defined(__cpp_impl_three_way_comparison) || defined(__cpp_lib_three_way_comparison)
    return noexcept(min_assess_compare(instanceof<typeA&&>() <=> instanceof<typeB&&>())) ?
      min_assess_compare(pass<typeA>(objectA) <=> pass<typeB>(objectB)) :
      min_equals        (pass<typeA>(objectA),    pass<typeB>(objectB));
  #else
    return false;
  #endif
}

template <typename typeA, typename typeB>
constexpr typename conditional<
  false == assess_minmax_compare<assess_compare,             typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than,        typeB, typeA>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeA, typeB>::value &&
  false == assess_minmax_compare<assess_greater_than_equals, typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than,         typeB, typeA>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeA, typeB>::value &&
  false == assess_minmax_compare<assess_lesser_than_equals,  typeB, typeA>::value,
  bool
>::type min_compare(typeA&& objectA, typeB&& objectB) noexcept(noexcept(min_equals(instanceof<typeA&&>(), instanceof<typeB&&>()))) {
  return min_equals(pass<typeA>(objectA), pass<typeB>(objectB));
}

// ...
template <typename type>
constexpr type&& min(type&& object) noexcept(noexcept(minmax_compare(instanceof<type&&>()))) {
  return minmax_compare(pass<type>(object)), pass<type>(object);
}

template <typename type>
constexpr decltype(min(instanceof<type&&>())) min(type&& object, std::nullptr_t const) noexcept(noexcept(min(instanceof<type&&>()))) {
  return min(pass<type>(object));
}

template <typename type>
constexpr type&& min(type&& object, bool (*const comparator)(type&&)) noexcept(noexcept(NULL == comparator && noexcept(minmax_compare(instanceof<type&&>())))) {
  return (NULL == comparator ? static_cast<bool (*)(type&&)>(&minmax_compare) : comparator)(pass<type>(object)), pass<type>(object);
}

template <typename typeA, typename typeB>
constexpr typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&& min(typeA&& objectA, typeB&& objectB) noexcept(noexcept(min_compare(instanceof<typeA&&>(), instanceof<typeB&&>()))) {
  return min_compare(pass<typeA>(objectA), pass<typeB>(objectB)) ?
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeA>(objectA) :
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeB>(objectB);
}

template <typename typeA, typename typeB>
constexpr decltype(min(instanceof<typeA&&>(), instanceof<typeB&&>())) min(typeA&& objectA, typeB&& objectB, std::nullptr_t const) noexcept(noexcept(min(instanceof<typeA&&>(), instanceof<typeB&&>()))) {
  return min(pass<typeA>(objectA), pass<typeB>(objectB));
}

template <typename typeA, typename typeB>
constexpr typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&& min(typeA&& objectA, typeB&& objectB, bool (*const comparator)(typeA&&, typeB&&)) noexcept(noexcept((NULL == comparator || comparator == static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&min_compare)) && noexcept(min_compare(instanceof<typeA&&>(), instanceof<typeB&&>())))) {
  return (NULL == comparator || comparator == static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&min_compare) ? static_cast<bool (*)(typeA&&, typeB&&)>(&min_compare) : comparator)(pass<typeA>(objectA), pass<typeB>(objectB)) ?
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeA>(objectA) :
    (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeB>(objectB);
}

#ifdef __cpp_noexcept_function_type
  template <typename type>
  constexpr type&& min(type&& object, bool (*const comparator)(type&&) noexcept) noexcept(noexcept((NULL != comparator && comparator != static_cast<bool (*)(type&&) noexcept>(&minmax_compare)) || noexcept(minmax_compare(instanceof<type&&>())))) {
    return (NULL == comparator || comparator == static_cast<bool (*)(type&&) noexcept>(&minmax_compare) ? static_cast<bool (*)(type&&) noexcept>(&minmax_compare) : comparator)(pass<type>(object)), static_cast<type&&>(object);
  }

  template <typename typeA, typename typeB>
  constexpr typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&& min(typeA&& objectA, typeB&& objectB, bool (*const comparator)(typeA&&, typeB&&) noexcept) noexcept(noexcept((NULL != comparator && comparator != static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&min_compare)) || noexcept(min_compare(instanceof<typeA&&>(), instanceof<typeB&&>())))) {
    return (NULL == comparator || comparator == static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&min_compare) ? static_cast<bool (*)(typeA&&, typeB&&) noexcept>(&min_compare) : comparator)(pass<typeA>(objectA), pass<typeB>(objectB)) ?
      (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeA>(objectA) :
      (typename conditional<is_void<typename pack<typeA, typeB>::common::type>::value, typeA, typename pack<typeA, typeB>::common::type>::type&&) pass<typeB>(objectB);
  }
#endif

#ifdef _MSC_VER
  template <typename typeA, typename typeB, typename typeC, typename... types>
  constexpr typename conditional<
    can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value,
    typename conditional<is_void<typename pack<typeA, typeB, typeC, types...>::template slice<0u, 1u + sizeof...(types)>::type::common::type>::value, typeA, typename pack<typeA, typeB, typeC, types...>::template slice<0u, 1u + sizeof...(types)>::type::common::type>::type,
    typename conditional<is_void<typename pack<typeA, typeB, typeC, types...>                                                 ::common::type>::value, typeA, typename pack<typeA, typeB, typeC, types...>                                                 ::common::type>::type
  >::type&& min(typeA&& objectA, typeB&& objectB, typeC&& objectC, types&&... objects) noexcept(noexcept(min(min(instanceof<typeA&&>(), instanceof<typeB&&>(), instanceof<bool (*)(typeA&&, typeB&&)>()), instanceof<typeC&&>(), instanceof<types&&>()...))) {
    return min(min(pass<typeA>(objectA), pass<typeB>(objectB),
      can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value
      ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, pass<typeC>(objectC), pass<types>(objects)...))
      : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)
    ), pass<typeC>(objectC), pass<types>(objects)...);
  }
#else
  template <typename typeA, typename typeB, typename typeC, typename... types>
  constexpr decltype(min(min(instanceof<typeA&&>(), instanceof<typeB&&>(), can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, instanceof<typeC&&>(), instanceof<types&&>()...)) : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)), instanceof<typeC&&>(), instanceof<types&&>()...)) min(typeA&& objectA, typeB&& objectB, typeC&& objectC, types&&... objects) noexcept(noexcept(min(min(instanceof<typeA&&>(), instanceof<typeB&&>(), can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, instanceof<typeC&&>(), instanceof<types&&>()...)) : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)), instanceof<typeC&&>(), instanceof<types&&>()...))) {
    return min(min(pass<typeA>(objectA), pass<typeB>(objectB), can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? static_cast<bool (*)(typeA&&, typeB&&)>(at<can_minmax_compare<typename pack<typeC, types...>::last::type, typeA, typeB>::value ? sizeof...(types) + 1u : 0u>(nullptr, pass<typeC>(objectC), pass<types>(objects)...)) : static_cast<bool (*)(typeA&&, typeB&&)>(NULL)), pass<typeC>(objectC), pass<types>(objects)...);
  }
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  // Play around with the `max(...)` and `min(...)` functions
  //   watch out for SFINAE errors, though! (first draft)
  int a = 0;
  int b = 0;

  std::boolalpha(std::cout);
  std::cout << (&max(a, b) != &min(a, b)) << std::endl;
  std::cout << (&max(a, b) == &b)         << std::endl;
  std::cout << (&min(a, b) == &a)         << std::endl;

  // ...
  std::endl(std::cout);
  std::cout << min(5)       << std::endl;
  std::cout << min(5, 3)    << std::endl;
  std::cout << min(5, 2, 3) << std::endl;

  std::endl(std::cout);
  std::cout << min(5,       nullptr) << std::endl;
  std::cout << min(5, 3,    nullptr) << std::endl;
  std::cout << min(5, 2, 3, nullptr) << std::endl;

  std::endl(std::cout);
  std::cout << min(5,       static_cast<bool (*)(int&&)        noexcept>(NULL)) << std::endl;
  std::cout << min(5, 3,    static_cast<bool (*)(int&&, int&&) noexcept>(NULL)) << std::endl;
  std::cout << min(5, 2, 3, static_cast<bool (*)(int&&, int&&) noexcept>(NULL)) << std::endl;

  std::endl(std::cout);
  std::cout << min(5,       +[](int&&)            noexcept { return true;   }) << std::endl;
  std::cout << min(5, 3,    +[](int&& a, int&& b) noexcept { return a <= b; }) << std::endl;
  std::cout << min(5, 2, 3, +[](int&& a, int&& b) noexcept { return a <= b; }) << std::endl;

  // ...
  std::endl(std::cout);
  std::cout << max(std::string("one"), std::string("two")) << std::endl;
  std::cout << min(std::string("one"), std::string("two")) << std::endl;

  // ...
  constexpr std::size_t size = max(sizeof(long double), sizeof(long long), sizeof(void*));
  alignas(size) unsigned char variant[size];

  static_cast<void>(variant);
}
