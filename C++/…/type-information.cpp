#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <limits.h>
#include <new>
#include <stdint.h>
#include <typeinfo>
#include <type_traits>

/* … */
struct typeinfo {
  struct callback final {
    void (*const value)(...);

    template <typename T>
    constexpr callback(T const& function) noexcept :
      value(reinterpret_cast<void (*)(...)>(+function))
    {}
  };

  template <typename T>
  struct inspect final {
    static bool        const bounded    = std::is_array<typename std::remove_reference<T>::type>::value;
    static std::size_t const bounds     = std::extent<typename std::conditional<bounded, typename std::remove_reference<T>::type, std::nullptr_t[]>::type>::value;
    static bool        const constancy  = std::is_const<typename std::remove_reference<T>::type>::value;
    static bool        const lvalue     = std::is_lvalue_reference<T>::value;
    static bool        const pointer    = std::is_pointer<T>::value;
    static bool        const rvalue     = std::is_rvalue_reference<T>::value;
    static bool        const volatility = std::is_volatile<typename std::remove_reference<T>::type>::value;
  };

  enum qualification : std::size_t {
    unbounded = 0u,
    bounded   = SIZE_MAX >> ((CHAR_BIT * sizeof(std::size_t)) - 5u),

    constancy  = static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof(std::size_t)) - 1u),
    lvalue     = static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof(std::size_t)) - 4u),
    pointer    = static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof(std::size_t)) - 3u),
    rvalue     = static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof(std::size_t)) - 5u),
    volatility = static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof(std::size_t)) - 2u)
  };

  /* … */
  template <typename T, typename U = typename std::remove_reference<T>::type>
  constexpr static auto constructorof() noexcept {
    return +[](void* const address, void const* const object = nullptr) noexcept(false) -> void* {
      return object != nullptr ? ::new (address) U(*static_cast<U const*>(object)) : ::new (address) U();
    };
  }

  template <typename T, typename U = typename std::remove_reference<T>::type>
  constexpr static auto destructorof() noexcept {
    return +[](void* const address) noexcept(noexcept(std::declval<U&>().~U())) {
      return static_cast<U*>(address) -> ~U();
    };
  }

  template <typename T, typename U = typename std::remove_reference<T>::type>
  constexpr static auto evaluatorof() noexcept {
    return +[](void* const address, struct callback const callback) noexcept(false) {
      return reinterpret_cast<void (*)(U&)>(callback.value)(*static_cast<U*>(address));
    };
  }

  /* … → Must be type-agnostic */
  std::size_t    const  alignment;
  std::size_t    const  bounds;
  void*        (*const construct)(void*, void const*);
  void         (*const destruct) (void*);
  void         (*const evaluate) (void*, struct callback);
  std::type_info const &information;
  qualification  const qualifiers;
  std::size_t    const size;

  template <typename T>
  constexpr typeinfo(inspect<T> const inspection) noexcept :
    alignment  (alignof(T)),
    bounds     (inspection.bounds),
    construct  (constructorof<T>()),
    destruct   (destructorof <T>()),
    evaluate   (evaluatorof  <T>()),
    information(typeid(T)),
    qualifiers (static_cast<qualification>(
      (inspection.constancy  ? typeinfo::constancy  : static_cast<qualification>(0x00u)) |
      (inspection.lvalue     ? typeinfo::lvalue     : static_cast<qualification>(0x00u)) |
      (inspection.pointer    ? typeinfo::pointer    : static_cast<qualification>(0x00u)) |
      (inspection.rvalue     ? typeinfo::rvalue     : static_cast<qualification>(0x00u)) |
      (inspection.volatility ? typeinfo::volatility : static_cast<qualification>(0x00u)) |
      static_cast<qualification>(inspection.bounds)
    )),
    size(sizeof(T))
  {}
};

#define typeinfo(typeid) typeinfo(typeinfo::inspect<typeid>{})

/* Main */
int main(int, char*[]) /* noexcept */ {
  for (typeinfo &info : std::vector<typeinfo>{typeinfo(std::string)}) {
    using namespace std::string_literals;
    void *const object = info.construct(&std::array<char, sizeof(std::string)>{}, &"Hello, World!"s);

    // …
    if (object == nullptr) break;

    info.evaluate(object, [](std::string& object) { std::cout << object; });
    info.destruct(object);
  }
}
