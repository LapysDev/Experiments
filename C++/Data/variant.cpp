/* ...
    --- CITE ---
      #Lapys:
        - Circle:                                             https://lapys.godbolt.org/z/WP8z71zaW
        - Clang, GNU, Intel, Microsoft Visual Studio, NVIDIA: https://lapys.godbolt.org/z/dMqdf6vvY
*/
#include <type_traits>
#include <utility>
#if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202002L || (defined(__circle_lang__) || defined(__clang__) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))
# include <version>
#endif

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

    // ... ->> Boolean metafunction denoting the validity of casting a type
    template <typename, typename baseA, typename baseB>
    struct can_convert final {
      static bool const value = std::is_void<typename std::remove_pointer<baseB>::type>::value && (
        std::is_array  <typename std::remove_reference<baseA>::type>::value ||
        std::is_pointer<typename std::remove_reference<baseA>::type>::value
      );
    };

    template <typename baseA, typename baseB>
    struct can_convert<decltype(static_cast<void>(static_cast<baseB>(std::declval<typename std::conditional<std::is_reference<baseA>::value, baseA, baseA&>::type>()))), baseA, baseB> final {
      static bool const value = true;
    };

    // ... ->> Boolean metafunction denoting the validity of construction/ initializing a type
    template <typename, typename base, typename... bases>
    struct can_initialize final {
      template <typename, typename, typename...>
      struct valueof final {
        static bool const value = false;
      };

      template <typename subbase, typename... subbases>
      struct valueof<decltype(static_cast<void>(
        #if defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__NVCC__) || defined(__NVCOMPILER)
          subbase{std::declval<subbases>()...}
        #else
          subbase(std::declval<subbases>()...)
        #endif
      )), subbase, subbases...> final {
        static bool const value = true;
      };

      /* ... */
      static bool const value = valueof<void, base, bases...>::value;
    };

    template <typename baseA, typename baseB>
    struct can_initialize<void, baseA, baseB> final {
      template <typename, typename subbaseA, typename subbaseB>
      struct valueof final {
        static bool const value = std::is_void<typename std::remove_pointer<subbaseA>::type>::value && (
          std::is_array  <typename std::remove_reference<subbaseB>::type>::value ||
          std::is_pointer<typename std::remove_reference<subbaseB>::type>::value
        );
      };

      template <typename subbaseA, typename subbaseB>
      struct valueof<decltype(static_cast<void>(
        subbaseA((subbaseA) std::declval<subbaseB>())
      )), subbaseA, subbaseB> final {
        static bool const value = true;
      };

      /* ... */
      static bool const value = valueof<void, baseA, baseB>::value;
    };

    // ... ->> Sum collection of types
    template <typename...>
    struct values final {
      // ... ->> See `enum variant<>::access`
      template <bool, typename...>
      struct evaluate final {
        static variant::access const value = access::unfit;
      };

      // ... ->> Boolean denoting allowed & preferred member access in current type
      template <typename>
      struct is_convertible final {
        static bool const value = false;
      };

      // ... ->> Boolean denoting allowed & preferred member access in succeeding type
      template <variant::access, typename>
      struct is_deferred_convertible final {
        static bool const value = false;
      };

      // ... ->> Boolean denoting allowed & preferred member initialization in succeeding type
      template <variant::access, typename...>
      struct is_deferred_initializable final {
        static bool const value = false;
      };

      // ... ->> Boolean denoting allowed & preferred member initialization in current type
      template <typename...>
      struct is_initializable final {
        static bool const value = false;
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
      template <bool assertion, typename...>
      struct evaluate final {
        static variant::access const value = assertion ? access::inexact : access::unfit;
      };

      template <bool assertion, typename subbase>
      struct evaluate<assertion, subbase> final {
        static variant::access const value = assertion ?
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

      // ... ->> See `struct values<>::is_convertible`
      template <typename subbase>
      struct is_convertible final {
        static bool const value = (
          access::unfit != evaluate<can_convert<void, base, subbase>::value, subbase>::value ||
          values<bases...>::template is_convertible<subbase>::value
        );
      };

      // ... ->> See `struct values<>::is_deferred_convertible`
      template <variant::access evaluation, typename subbase>
      struct is_deferred_convertible final {
        static bool const value = (
          evaluation < evaluate<can_convert<void, base, subbase>::value, subbase>::value ||
          values<bases...>::template is_deferred_convertible<evaluation, subbase>::value
        );
      };

      // ... ->> See `struct values<>::is_deferred_initializable`
      template <variant::access evaluation, typename... subbases>
      struct is_deferred_initializable final {
        static bool const value = (
          evaluation < evaluate<can_initialize<void, base, subbases...>::value, subbases...>::value ||
          values<bases...>::template is_deferred_initializable<evaluation, subbases...>::value
        );
      };

      // ... ->> See `struct values<>::is_initializable`
      template <typename... subbases>
      struct is_initializable final {
        static bool const value = (
          access::unfit != evaluate<can_initialize<void, base, subbases...>::value, subbases...>::value ||
          values<bases...>::template is_initializable<subbases...>::value
        );
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
        constexpr member(type&& argument) noexcept(noexcept((base) std::declval<type>()) && noexcept(decltype(member::value)(std::declval<decltype(member::value)>()))) :
          value(static_cast<decltype(member::value)>((base) std::forward<type>(argument)))
        {}

        template <typename type, typename... types>
        constexpr member(type&& argument, types&&... arguments) noexcept(noexcept(base(std::declval<type>(), std::declval<types>()...))) :
          value(std::forward<type>(argument), std::forward<types>(arguments)...)
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

      template <typename... types, typename std::enable_if<false == is_initializable<types...>::value, std::nullptr_t>::type = nullptr>
      constexpr values(types&&...) noexcept = delete;

      template <typename... types, typename std::enable_if<is_initializable<types...>::value && false != is_deferred_initializable<evaluate<can_initialize<void, base, types...>::value, types...>::value, types...>::value, std::nullptr_t>::type = nullptr>
      constexpr values(types&&... arguments) noexcept(noexcept(values<bases...>(std::declval<types>()...))) :
        next(std::forward<types>(arguments)...)
      {}

      template <typename... types, typename std::enable_if<is_initializable<types...>::value && false == is_deferred_initializable<evaluate<can_initialize<void, base, types...>::value, types...>::value, types...>::value, std::nullptr_t>::type = nullptr>
      constexpr values(types&&... arguments) noexcept(noexcept(member(std::declval<types>()...))) :
        value(std::forward<types>(arguments)...)
      {}

      /* ... */
      template <typename type, typename std::enable_if<false == is_convertible<type>::value, std::nullptr_t>::type = nullptr>
      inline operator type&() const volatile noexcept = delete;

      template <typename type, typename std::enable_if<is_convertible<type>::value && false != is_deferred_convertible<evaluate<can_convert<void, base, type>::value, type>::value, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&() const volatile noexcept {
        return (type&) this -> next;
      }

      template <typename type, typename std::enable_if<is_convertible<type>::value && false == is_deferred_convertible<evaluate<can_convert<void, base, type>::value, type>::value, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&() const volatile noexcept {
        return (type&) this -> value.value;
      }

      #if false == (defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(_MSC_VER) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__NVCC__) || defined(__NVCOMPILER))
        template <typename type, typename std::enable_if<is_convertible<type>::value && false != is_deferred_convertible<evaluate<can_convert<void, base, type>::value, type>::value, type>::value, std::nullptr_t>::type = nullptr>
        constexpr operator type&() const noexcept {
          return (type&) this -> next;
        }

        template <typename type, typename std::enable_if<is_convertible<type>::value && false == is_deferred_convertible<evaluate<can_convert<void, base, type>::value, type>::value, type>::value, std::nullptr_t>::type = nullptr>
        constexpr operator type&() const noexcept {
          return (type&) this -> value.value;
        }
      #endif
    };

  public:
    constexpr explicit variant() noexcept {}

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
    variant<>::template values<base, bases...> members;

  public:
    template <typename... types>
    constexpr variant(types&&... arguments) noexcept(noexcept(decltype(variant::members)(std::declval<types>()...))) :
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
      constexpr operator type() const volatile noexcept(noexcept((type) std::declval<type&>())) {
        return (type) (type&) this -> members;
      }

      #if false == (defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(_MSC_VER) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__NVCC__) || defined(__NVCOMPILER))
        template <typename type>
        constexpr operator type() const noexcept(noexcept((type) std::declval<type&>())) {
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
  constexpr static int  literal      = 42;                                        //
  auto                  empty        = variant<>                  {};             // No member(s)
  constexpr static auto constant     = variant<int, double                        // Compile-time support
    #ifndef __circle_lang__
      , void* // Circle requires all members be correctly constructible when constant evaluated
    #endif
  >{42};

  /* Reference member initialization */
  #ifndef __circle_lang__
    constexpr
    #ifdef _MSC_VER
      static
    #endif
  #endif
  int &&constant_reference = variant<int&&, int const&>{static_cast<int const&>(literal)}.operator int&&();

  variant<int const&>{42};
  variant<int&&>     {42};
  std::printf("[...]: %i" "\r\n", constant_reference);

  /* Access most similar member by type */
  #ifndef _MSC_VER
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
  #ifdef _MSC_VER // Disregards current active member
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
  unusable.~variant();
  #ifndef __ICC
    empty.~variant();
  #endif

  /* Assignable by proxy */
  std::printf("[unassignable]: %i" "\r\n", (int) unassignable);
  unassignable.operator int&() = 69;
  std::printf("[unassignable]: %i" "\r\n", (int) unassignable);

  /* Usable by complete re-initialization (destructor unneeded after default-initialization) */
  #ifdef _MSC_VER
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
