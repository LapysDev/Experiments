#include <type_traits>
#include <utility>
#include <version>

/* ... ->> `union` class type zero-cost abstraction */
template <typename...>
struct variant final {
  template <typename...>
  friend struct variant;

  private:
    // ... ->> Flag denoting preferred/ valid member access
    enum class access : unsigned char {
      exact     = 4u, // ->> Access perfectly matches
      fit       = 3u, // ->> Access nearly matches
      tolerable = 2u, // ->> Access allowed and preferred
      inexact   = 1u, // ->> Access allowed but un-prioritized
      unfit     = 0u  // ->> Access violates strict aliasing
    };

    // ... ->> Flag denoting boolean metafunction
    enum class operation : unsigned char {
      cast,
      initialize
    };

    // ... ->> Boolean metafunction denoting the preference/ validity of possible operations
    template <variant::operation, typename, typename...>
    struct can final {
      static bool const value = false;
    };

    template <typename base, typename... bases>
    struct can<operation::cast, base, bases...> final {
      template <class, typename subbase>
      struct valueof final {
        static bool const value = std::is_void<typename std::remove_pointer<subbase>::type>::value && (
          std::is_array  <typename std::remove_reference<base>::type>::value ||
          std::is_pointer<typename std::remove_reference<base>::type>::value
        );
      };

      template <typename subbase>
      struct valueof<decltype(static_cast<void>(static_cast<subbase>(std::declval<typename std::conditional<std::is_reference<base>::value, base, base&>::type>()))), subbase> final {
        static bool const value = true;
      };

      /* ... */
      static bool const value = valueof<void, bases...>::value;
    };

    template <typename base, typename... bases>
    struct can<operation::initialize, base, bases...> final {
      template <class, typename subbase = void, typename...>
      struct valueof final {
        static bool const value = std::is_void<typename std::remove_pointer<base>::type>::value && (
          std::is_array  <typename std::remove_reference<subbase>::type>::value ||
          std::is_pointer<typename std::remove_reference<subbase>::type>::value
        );
      };

      template <typename subbase, typename... subbases>
      struct valueof<decltype(static_cast<void>(base(std::declval<typename std::conditional<std::is_void<subbase>::value, base, subbase>::type>(), std::declval<subbases>()...))), subbase, subbases...> final {
        static bool const value = true;
      };

      /* ... */
      static bool const value = valueof<void, bases...>::value;
    };

    // ... ->> Disambiguation type
    struct trait final {};

    // ... ->> Sum collection of types
    template <typename...>
    struct values final {
      // ... ->> See `enum variant<>::access`
      template <variant::operation, typename...>
      struct evaluate final {
        static variant::access const value = access::unfit;
      };

      // ... ->> Boolean denoting inclusion within a collection of values
      template <typename>
      struct in final {
        static bool const value = false;
      };

      // ... ->> Boolean denoting allowed and preferred member access in succeeding type
      template <variant::operation, variant::access, typename...>
      struct is_deferrable final {
        static bool const value = false;
      };

      // ... ->> Boolean denoting allowed and preferred member access in current type
      template <variant::operation, typename...>
      struct is_evaluable final {
        static bool const value = false;
      };

      // ... ->> Unique collection of types
      template <class, typename...>
      struct set;

      template <typename... elements>
      struct set<values<elements...> > final {
        typedef values<elements...> type;
      };

      template <typename... elements, typename base, typename... bases>
      struct set<values<elements...>, base, bases...> final {
        typedef typename std::conditional<
          values<elements...>::template in<base>::value,
          typename set<values<elements...>,       bases...>::type,
          typename set<values<elements..., base>, bases...>::type
        >::type type;
      };

      /* ... */
      template <typename... types>
      constexpr values(types&&...) noexcept {}

      /* ... */
      template <typename type>
      constexpr operator type&() const volatile noexcept = delete;
    };

    template <typename base, typename... bases>
    struct values<base, bases...> final {
      // ... ->> See `struct values<>::evaluate` -->
      template <variant::operation operation, typename... subbases>
      struct evaluate final {
        static variant::access const value = can<operation, base, subbases...>::value ? access::inexact : access::unfit;
      };

      template <variant::operation operation, typename subbase>
      struct evaluate<operation, subbase> final {
        static variant::access const value = can<operation, base, subbase>::value ?
          // typeid(base) == typeid(subbase)
          std::is_same<
            typename std::remove_cv<typename std::remove_reference<base>   ::type>::type,
            typename std::remove_cv<typename std::remove_reference<subbase>::type>::type
          >::value ? access::exact :

          // typeid(base[n]); typeid(subbase[n])
          std::is_array<typename std::remove_reference<base>::type>::value && std::is_array<typename std::remove_reference<subbase>::type>::value &&
          std::extent  <typename std::remove_reference<base>::type>::value == std::extent  <typename std::remove_reference<subbase>::type>::value && (
            std::is_same<
              typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<base>   ::type>::type>::type,
              typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<subbase>::type>::type>::type
            >::value
          ) ? access::exact :

          // typeid(base[]); typeid(subbase[n]), typeid(subbase[])
          std::is_array<typename std::remove_reference<base>   ::type>::value && 0u == std::extent<typename std::remove_reference<base>::type>::value &&
          std::is_array<typename std::remove_reference<subbase>::type>::value && (
            std::is_same<
              typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<base>   ::type>::type>::type,
              typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<subbase>::type>::type>::type
            >::value
          ) ? access::fit :

          // typeid(base*); typeid(subbase[n]), typeid(subbase[]), typeid(subbase*)
          std::is_pointer<typename std::remove_reference<base>::type>::value && ((
            std::is_array  <typename std::remove_reference<subbase>::type>::value && std::is_same<
              typename std::remove_cv<typename std::remove_pointer    <typename std::remove_reference<base>   ::type>::type>::type,
              typename std::remove_cv<typename std::remove_all_extents<typename std::remove_reference<subbase>::type>::type>::type
            >::value
          ) || (
            std::is_pointer<typename std::remove_reference<subbase>::type>::value && std::is_same<
              typename std::remove_cv<typename std::remove_pointer<typename std::remove_reference<base>   ::type>::type>::type,
              typename std::remove_cv<typename std::remove_pointer<typename std::remove_reference<subbase>::type>::type>::type
            >::value
          )) ? access::tolerable :
        access::inexact : access::unfit;
      };

      // ... ->> See `struct values<>::in`
      template <typename subbase>
      struct in final {
        static bool const value = std::is_same<
          typename std::remove_cv<typename std::remove_reference<base>   ::type>::type,
          typename std::remove_cv<typename std::remove_reference<subbase>::type>::type
        >::value || values<bases...>::template in<subbase>::value;
      };

      // ... ->> See `struct values<>::is_deferrable`
      template <variant::operation operation, variant::access evaluation, typename... subbases>
      struct is_deferrable final {
        static bool const value = (evaluation < evaluate<operation, subbases...>::value) || values<bases...>::template is_deferrable<operation, evaluation, subbases...>::value;
      };

      // ... ->> See `struct values<>::is_evaluable`
      template <variant::operation operation, typename... subbases>
      struct is_evaluable final {
        static bool const value = access::unfit != evaluate<operation, subbases...>::value || values<bases...>::template is_evaluable<operation, subbases...>::value;
      };

      // ... ->> Reference types not explicitly allowed as `union` member but supported in `variant` class
      struct member final {
        // ... ->> Accept any cv-qualification of the reference type
        typename std::conditional<std::is_lvalue_reference<base>::value, typename std::remove_reference<base>::type const volatile&,
        typename std::conditional<std::is_rvalue_reference<base>::value, typename std::remove_reference<base>::type const volatile&&,
          base
        >::type>::type value;

        /* ... */
        template <typename type>
        constexpr member(type&& argument) noexcept :
          value((decltype(member::value)) std::forward<type>(argument))
        {}

        template <typename... types>
        constexpr member(types&&... arguments) noexcept :
          value(std::forward<types>(arguments)...)
        {}
      };

      /* ... */
      union {
        values<bases...> next;
        member           value;
      };

      /* ... */
      constexpr values() noexcept :
        next()
      {}

      template <typename... types>
      constexpr values(types&&... arguments) noexcept :
        values(variant::trait{}, std::forward<types>(arguments)...)
      {}

      template <typename... types>
      constexpr values(typename std::enable_if<false == is_evaluable<operation::initialize, types...>::value, typename variant::trait>::type const, types&&...) noexcept = delete;

      template <typename... types>
      constexpr values(typename std::enable_if<is_evaluable<operation::initialize, types...>::value && false != is_deferrable<operation::initialize, evaluate<operation::initialize, types...>::value, types...>::value, typename variant::trait>::type const, types&&... arguments) noexcept :
        next(std::forward<types>(arguments)...)
      {}

      template <typename... types>
      constexpr values(typename std::enable_if<is_evaluable<operation::initialize, types...>::value && false == is_deferrable<operation::initialize, evaluate<operation::initialize, types...>::value, types...>::value, typename variant::trait>::type const, types&&... arguments) noexcept :
        value(std::forward<types>(arguments)...)
      {}

      /* ... */
      template <typename type, typename std::enable_if<false == is_evaluable<operation::cast, type>::value, std::nullptr_t>::type = nullptr>
      inline operator type&() const volatile noexcept = delete;

      template <typename type, typename std::enable_if<is_evaluable<operation::cast, type>::value && false != is_deferrable<operation::cast, evaluate<operation::cast, type>::value, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&() const volatile noexcept {
        return (type&) this -> next;
      }

      template <typename type, typename std::enable_if<is_evaluable<operation::cast, type>::value && false == is_deferrable<operation::cast, evaluate<operation::cast, type>::value, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&() const volatile noexcept {
        return (type&) this -> value.value;
      }
    };

  public:
    template <typename... types>
    constexpr variant(types&&...) noexcept {}

    /* ... */
    #if __cpp_constexpr >= 201304L
      constexpr
    #endif
    inline operator void() const volatile noexcept {}

    #ifdef __circle_lang__
      template <typename type>
      constexpr operator type&() const noexcept = delete;

      template <typename type>
      constexpr operator type&() const volatile noexcept = delete;

      template <typename type>
      constexpr operator type&&() const volatile noexcept = delete;
    #else
      template <typename type>
      constexpr operator type() const volatile noexcept = delete;
    #endif
};

template <typename base, typename... bases>
struct variant<base, bases...> final {
  private:
    typename variant<>::template values<>::template set<variant<>::template values<>, base, bases...>::type members;

  public:
    template <typename... types>
    constexpr variant(types&&... arguments) noexcept :
      members(std::forward<types>(arguments)...)
    {}

    /* ... */
    #if __cpp_constexpr >= 201304L
      constexpr
    #endif
    inline operator void() const volatile noexcept {}

    #ifdef __circle_lang__
      template <typename type>
      constexpr operator type&() const noexcept {
        return (type&) this -> members;
      }

      template <typename type>
      constexpr operator type&() const volatile noexcept {
        return (type&) this -> members;
      }

      template <typename type>
      constexpr operator type&&() const volatile noexcept {
        return (type&&) (type&) this -> members;
      }
    #else
      template <typename type>
      constexpr operator type() const volatile noexcept {
        return (type) (type&) this -> members;
      }

      #ifndef _MSVC_LANG
        template <typename type>
        constexpr operator type() const noexcept {
          return (type) (type&) this -> members;
        }
      #endif
    #endif
};

/* Main ->> */
#include <cstdio>
#include <new>

int main(int, char*[]) /* noexcept */ {
  auto                  unusable     = variant<int, double, void*>{};             // Uninitialized members with no provided way to construct them
  auto                  unassignable = variant<int&>              {*new int(42)}; // Initialized reference member, cannot be copy-assigned
  auto                  object       = variant<int, double, void*>{42.0};         // Active `double` member
  auto                  empty        = variant<>                  {};             // No member(s)
  constexpr static auto constant     = variant<int, double                        // Compile-time support
    #ifndef __circle_lang__
      , void* // Circle requires all members be correctly constructible when constant evaluated
    #endif
  >{42};

  /* Reference member initialization */
  variant<int const&>{42};
  variant<int&&>     {42};

  /* Access most similar member by type */
  #ifndef _MSVC_LANG
    constexpr // MSVC can not cast lvalue reference to an rvalue reference in a constant expression
  #endif
  int const          &&constant_rvalue_reference = constant.operator int const&&(); // Requires a `variant` with static storage duration to be constant evaluated
  constexpr int const  constant_value            = constant.operator int const  (); // Cast to `void` does not invoke the `void` operator overload
  constexpr int const &constant_lvalue_reference = constant.operator int const& (); // C-style cast to reference does not invoke the operator overload

  std::printf("[constant]: %i %i %i"    "\r\n", constant_lvalue_reference, constant_value, constant_rvalue_reference);
  std::printf("[constant]: %4.5s %4.5s" "\r\n",
    (void*) &constant_lvalue_reference == (void*) &constant                               ? "true" : "false",
    (void*) &constant_lvalue_reference == (void*) &(int const&) constant_rvalue_reference ? "true" : "false"
  );

  /* Modify most similar member by type */
  std::printf("[object]: %f" "\r\n", (double) object);

  object = 69.0;                                std::printf("[object]: %f" "\r\n", (double) object);
  object = variant<int, double, void*>{1337.0}; std::printf("[object]: %f" "\r\n", (double) object);

  /* Switch active member */
  #ifdef _MSVC_LANG // Disregards current active member
    object = static_cast<void const*>("Hello, World!");
  #else
    object = "Hello, World!";
  #endif
  std::printf("[object]: \"%1.13s\"" "\r\n", (char const*) object);

  object.~variant(); // Considers current active member
  ::new (&object) variant<int, double, void*>{-1};
  std::printf("[object]: %u"  "\r\n",  (unsigned)    object);
  std::printf("[object]: %hi"  "\r\n", (short)       object);
  std::printf("[object]: %hhi" "\r\n", (signed char) object);

  /* Empty or uninitialized `variant` objects can be freely destructed (multiple times over) */
  empty   .~variant();
  unusable.~variant();

  /* Assignable by proxy */
  std::printf("[unassignable]: %i" "\r\n", (int) unassignable);
  unassignable.operator int&() = 69;
  std::printf("[unassignable]: %i" "\r\n", (int) unassignable);

  /* Usable by complete re-initialization (destructor unneeded after default-initialization) */
  #ifdef _MSVC_LANG
    ::new (&unusable) variant<int, double, void*>{static_cast<void*>(&unusable)};
  #else
    ::new (&unusable) variant<int, double, void*>{&unusable};
  #endif
  std::printf("[unusable]: %4.5s" "\r\n", (void*) unusable == (void*) &unusable ? "true" : "false");

  /* Same size as `union` class type */
  std::printf("[int, double, void*]: %zu" "\r\n", sizeof(variant<int, double, void*>));
  std::printf("[int&]              : %zu" "\r\n", sizeof(variant<int&>));
  std::printf("[]                  : %zu" "\r\n", sizeof(variant<>));
}
