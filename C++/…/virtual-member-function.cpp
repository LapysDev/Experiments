#include <array>
#include <cstdio>

/* ... */
#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 1419)
# pragma warning(disable: 3280)
#endif

/* ... ->> our base class */
struct base {
  protected:
    // ... ->> default function used by `member` function pointer
    constexpr char const* virtual_member() const noexcept {
      // ->> member function value
      return "[base]";
    }

    // ... ->> setup constructor used to setup default function
    constexpr base(char const* (base::* const member)() const) noexcept : member(member) {}

  public:
    // ... ->> `member` function pointer to be used as alternative `virtual` member function
    char const* (base:: *const member)() const;

    // ... ->> user-specified constructor (must delegate to setup constructor)
    constexpr base() noexcept : base(&base::virtual_member) {}
};

// ... ->> our (generic) derived class
template <std::size_t identity>
struct derived final : public base {
  private:
    // ... ->> member function value helper
    template <char...>
    struct subvalue final {};

    // ... ->> convert `identity` to a valid subpart of `derived`'s (string) member function value
    template <std::size_t subidentity, class subvalued = derived::subvalue<>, bool = 0u != subidentity>
    struct identity_to_subvalue;

    template <char... subvalues>
    struct identity_to_subvalue<0u, derived::subvalue<subvalues...>, false> final {
      using type = derived::subvalue<subvalues...>;
    };

    template <std::size_t subidentity, char... subvalues>
    struct identity_to_subvalue<subidentity, derived::subvalue<subvalues...>, true> final {
      using type = typename identity_to_subvalue<subidentity / 10u, derived::subvalue<"0123456789"[subidentity % 10u], subvalues...> >::type;
    };

    // ... ->> generate compile-time static (string) member function value
    template <class = typename identity_to_subvalue<identity>::type>
    struct get_value final {
      #if (defined(__clang__) || defined(__GNUC__)) && false == defined(__circle_lang__)
        using type = char const (&)[13];
      #else
        using type = char[13];
      #endif
      constexpr static type value = "[derived #0]";
    };

    template <char subvalue, char... subvalues>
    struct get_value<derived::subvalue<subvalue, subvalues...> > final {
      #if (defined(__clang__) || defined(__GNUC__)) && false == defined(__circle_lang__)
        using type = char const (&)[sizeof...(subvalues) + 13u];
      #else
        using type = char[sizeof...(subvalues) + 13u];
      #endif
      constexpr static type value = {'[', 'd', 'e', 'r', 'i', 'v', 'e', 'd', ' ', '#', subvalue, subvalues..., ']', '\0'};
    };

  protected:
    // ... ->> default function used by (base) `member` function pointer
    constexpr char const* virtual_member() const noexcept { return get_value<>::value; }

  public:
    // ... ->> user-specified constructor (must delegate to (base) setup constructor)
    constexpr derived() noexcept : base((char const* (base::*)() const) &derived::virtual_member) {}
};

/* ... ->> member function value need not be some `char const*` NUL-terminated string */
using type = decltype((static_cast<base*>(NULL) ->* base::member)());

/* ... */
template <std::size_t count, std::size_t... indexes>
std::array<type, count> get_erased_values(
  base const* const (&) [(count)],                                    // ->> array of type-erased `base` and `derived<…>`s
  type              (&&)[(count + 1u) * (count < sizeof...(indexes))] // ->> array of `base::member()` and `derived<…>::member()` values
) noexcept;

template <std::size_t count, std::size_t... indexes>
constexpr std::array<type, count> get_erased_values(
  base const* const (&objects)[(count)], // ->> `count + 1u` because of final `template` deduction which is SFINAE
  type              (&&values)[(count + 1u) * (count >= sizeof...(indexes))]
) noexcept {
  using next_value = type (&&)[count + 1u];
  return count != sizeof...(indexes)
    // ->> recursive because this runs on C++11's non-relaxed `constexpr` evaluation, as well
    //       regenerating the list of values is allowed as opposed to modifying its elements
    //       (likely causes redundant copies if not constant evaluated)
    ? get_erased_values<count, indexes..., sizeof...(indexes)>(objects, next_value{
      // [1] ->> previous values
      // [2] ->> current iterated value --> objects[…].member()
      values[indexes]...,
      (objects[sizeof...(indexes)] ->* objects[sizeof...(indexes)] -> member)()
    })

    // ->> can't pass references to (possibly lifetime-extended) temporary arrays
    //       but can pass trivially-copyable `struct`s
    : std::array<type, count>{values[indexes]...};
}

// ... ->> `std::array<…>{objects.member()...}` where `objects` are `typeid(base) or typeid(derived<…>)`
template <typename... types>
constexpr std::array<type, sizeof...(types)> get_values(types&&... objects) noexcept {
  // ->> erase the deducted `template` types
  // return get_erased_values<sizeof...(types)>({(base const*) &objects...}, {});
  return {(static_cast<base const&>(objects).*(static_cast<base const&>(objects).member))()...};
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  constexpr std::array<type, 3u> values = get_values(base{}, derived<1u>{}, derived<2u>{});

  // ...
  std::printf("%1.18s%zu%1.2s", "[sizeof base]   :" " ", sizeof(base),        "\r\n");
  std::printf("%1.18s%zu%1.2s", "[sizeof derived]:" " ", sizeof(derived<0u>), "\r\n");
  std::printf("%1.2s", "\r\n");

  for (type value : values)
  std::puts(value);
}
