#include <cstdio>
#include <new>
#include <type_traits>
#include <utility>
#include <version>

/* ... */
template <typename...>
struct variant final {
  template <typename...>
  friend struct variant;

  private:
    enum access : unsigned char {
      fit       = 2u, // ->> Member access allowed and preferred
      tolerable = 1u, // ->> Member access allowed but un-prioritized
      unfit     = 0u  // ->> Member access violates strict aliasing
    };

    // ...
    template <typename baseA, typename baseB, typename = baseB>
    struct can_cast final {
      static bool const value = (
        std::is_pointer<typename std::remove_reference<baseA>::type>::value &&
        std::is_void   <typename std::remove_pointer  <baseB>::type>::value
      );
    };

    template <typename baseA, typename baseB>
    struct can_cast<baseA, baseB, decltype(static_cast<baseB>(std::declval<typename std::conditional<std::is_reference<baseA>::value, baseA, baseA&>::type>()))> final {
      static bool const value = true;
    };

    // ...
    template <typename baseA, typename, typename = baseA>
    struct can_initialize final {
      static bool const value = false;
    };

    template <typename baseA, typename baseB>
    struct can_initialize<baseA, baseB, decltype(baseA(std::declval<baseB>()))> final {
      static bool const value = true;
    };

    // ...
    template <template <typename, typename...> class, typename>
    struct evaluate final {
      static access const value = variant::unfit;
    };

    // ...
    template <template <typename, typename...> class, typename, variant::access>
    struct is_deferrable final {
      static bool const value = false;
    };

    // ...
    template <template <typename, typename...> class, typename>
    struct is_evaluable final {
      static bool const value = false;
    };

    // ...
    template <typename>
    struct is_repetitive final {
      static bool const value = false;
    };

    /* ... */
    constexpr variant() noexcept {}

    template <typename type>
    constexpr variant(type&&) noexcept {}

    /* ... */
    template <typename type>
    constexpr variant& operator =(type&&) const volatile noexcept = delete;

    /* ... */
    constexpr operator void() const volatile noexcept = delete;

    template <typename type>
    inline operator type() const volatile noexcept(false) {
      // --> std::unreachable()
      return std::declval<type>();
    }
};

template <typename base, typename... bases>
struct variant<base, bases...> final {
  template <typename...>
  friend struct variant;

  private:
    template <template <typename, typename...> class trait, typename subbase>
    struct evaluate final {
      static variant<>::access const value = trait<base, subbase>::value ? std::is_same<
        typename std::remove_cv<typename std::remove_reference<base>   ::type>::type,
        typename std::remove_cv<typename std::remove_reference<subbase>::type>::type
      >::value ? variant<>::fit : variant<>::tolerable : variant<>::unfit;
    };

    // ...
    template <template <typename, typename...> class trait, typename subbase, variant<>::access evaluation = evaluate<trait, subbase>::value>
    struct is_deferrable final {
      static bool const value = (evaluation < evaluate<trait, subbase>::value) || variant<bases...>::template is_deferrable<trait, subbase, evaluation>::value;
    };

    // ...
    template <template <typename, typename...> class trait, typename subbase>
    struct is_evaluable final {
      static bool const value = variant<>::unfit != evaluate<trait, subbase>::value || variant<bases...>::template is_evaluable<trait, subbase>::value;
    };

    // ...
    template <typename subbase = void>
    struct is_repetitive final {
      static bool const value = std::is_same<
        typename std::remove_cv<typename std::remove_reference<base>   ::type>::type,
        typename std::remove_cv<typename std::remove_reference<subbase>::type>::type
      >::value || (
        variant<bases...>::template is_repetitive<base>   ::value ||
        variant<bases...>::template is_repetitive<subbase>::value
      );
    };

    // ...
    struct variant_value final {
      base value;
    };

    /* ... */
    static_assert(false == is_repetitive<>::value, "`variant` class unexpectedly specified with duplicate member types");

    union {
      variant_value     member;
      variant<bases...> submember;
    };

  public:
    constexpr variant() noexcept :
      submember()
    {}

    template <typename type, typename std::enable_if<false == is_evaluable<variant<>::can_initialize, type>::value, std::nullptr_t>::type = nullptr>
    constexpr variant(type&&) noexcept = delete;

    template <typename type, typename std::enable_if<is_evaluable<variant<>::can_initialize, type>::value && false != is_deferrable<variant<>::can_initialize, type>::value, std::nullptr_t>::type = nullptr>
    constexpr variant(type&& argument) noexcept :
      submember(std::forward<type>(argument))
    {}

    template <typename type, typename std::enable_if<is_evaluable<variant<>::can_initialize, type>::value && false == is_deferrable<variant<>::can_initialize, type>::value, std::nullptr_t>::type = nullptr>
    constexpr variant(type&& argument) noexcept :
      member{(base) std::forward<type>(argument)}
    {}

    /* ... */
    #if __cpp_constexpr >= 201304L
      constexpr
    #endif
    inline operator void() const volatile noexcept {}

    // ...
    template <typename type, typename std::enable_if<false == is_evaluable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
    constexpr operator type() const volatile noexcept;

    #ifdef __circle_lang__
      template <typename type, typename std::enable_if<false == is_evaluable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&() const volatile noexcept;

      template <typename type, typename std::enable_if<false == is_evaluable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&&() const volatile noexcept;
    #endif

    // ...
    template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false != is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
    constexpr operator type() const volatile noexcept {
      return (type) this -> submember;
    }

    #ifdef __circle_lang__
      template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false != is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&() const volatile noexcept {
        return (type&) this -> submember;
      }

      template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false != is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&&() const volatile noexcept {
        return (type&&) this -> submember;
      }
    #endif

    #ifndef _MSVC_LANG
      template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false != is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type() const noexcept {
        return (type) this -> submember;
      }
    #endif

    // ...
    template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false == is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
    constexpr operator type() const volatile noexcept {
      return (type) this -> member.value;
    }

    #ifdef __circle_lang__
      template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false == is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&() const volatile noexcept {
        return (type&) this -> member.value;
      }

      template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false == is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type&&() const volatile noexcept {
        return (type&&) this -> member.value;
      }
    #endif

    #ifndef _MSVC_LANG
      template <typename type, typename std::enable_if<is_evaluable<variant<>::can_cast, type>::value && false == is_deferrable<variant<>::can_cast, type>::value, std::nullptr_t>::type = nullptr>
      constexpr operator type() const noexcept {
        return (type) this -> member.value;
      }
    #endif
};

/* Main */
int main(int, char*[]) /* noexcept */ {
  variant<int, double, void*> unusable     = {};             // ->> all members uninitialized with no provided way to construct them
  variant<int&>               unassignable = {*new int(42)}; // ->> reference member initialized, cannot be copy-assigned
  variant<int, double, void*> object       = {42};           // ->> active `int` member

  // ->> access most similar member by type
  std::printf("[object]: %i %i %i" "\r\n", (int) object, object.operator int&(), object.operator int&&());

  // ->> modify most similar member by type
  object = 1337;
  std::printf("[object]: %i" "\r\n", (int) object);

  // ->> switch active member
  object = 420.0; // disregards current active member
  std::printf("[object]: %f" "\r\n", object.operator double&());

  object.~variant(); // considers current active member
  ::new (&object) variant<int, double, void*> {"Hello, World!"};
  std::printf("[object]: \"%1.13s\"" "\r\n", (char const*) object);

  // ->> assignable by proxy
  std::printf("[unassignable]: %i" "\r\n", (int) unassignable);
  unassignable.operator int&() = 1337;
  std::printf("[unassignable]: %i" "\r\n", (int) unassignable);

  // ->> usable by complete re-initialization (destructor unneeded after default-initialization)
  ::new (&unusable) variant<int, double, void*> {static_cast<void*>(NULL)};
  std::printf("[unusable]: %p" "\r\n", (void*) unusable);

  // ->> same size as `union` class type
  std::printf("[int, double, void*]: %zu" "\r\n", sizeof(variant<int, double, void*>));
  std::printf("[int&]              : %zu" "\r\n", sizeof(variant<int&>));
}
