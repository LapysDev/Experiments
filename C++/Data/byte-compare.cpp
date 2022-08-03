#include <cstddef>     // --> std::size_t
#include <cstring>     // --> std::memcmp
#include <type_traits> // --> std::is_array, std::conditional, std::declval, std::enable_if, std::is_scalar, std::remove_reference

/* ... */
namespace {
  // --> has_overload_equals<T1, T2, bool>::value ->> check if the object has overloaded the `==` operator
  template <typename, typename, bool membered, typename = void>
  struct has_overload_equals final {
    static bool const value = false;
  };

  template <typename baseA, typename baseB>
  struct has_overload_equals<baseA, baseB, false, decltype(static_cast<void>(operator ==(std::declval<baseA>(), std::declval<baseB>())))>  final {
    static bool const value = true;
  };

  template <typename baseA, typename baseB>
  struct has_overload_equals<baseA, baseB, true, decltype(static_cast<void>(std::declval<baseA>().operator ==(std::declval<baseB>())))> final {
    static bool const value = true;
  };

  // --> has_overloaded_addressof<T, bool>::value ->> check if the object has overloaded the `&` operator
  template <typename, bool membered, typename = void>
  struct has_overloaded_addressof final {
    static bool const value = false;
  };

  template <typename base>
  struct has_overloaded_addressof<base, false, decltype(static_cast<void>(operator &(std::declval<base>())))> final {
    static bool const value = true;
  };

  template <typename base>
  struct has_overloaded_addressof<base, true, decltype(static_cast<void>(std::declval<base>().operator &()))> final {
    static bool const value = true;
  };

  // --> can_direct_equals<T1, T2>::value ->> check if the object's bytes should be walked through
  template <typename, typename, typename = bool>
  struct can_direct_equals final {
    static bool const value = false;
  };

  template <typename baseA, typename baseB>
  struct can_direct_equals<baseA, baseB, decltype(
    std::declval<typename std::conditional<std::is_array<typename std::remove_reference<baseA>::type>::value, typename std::remove_extent<typename std::remove_reference<baseA>::type>::type*, baseA>::type>() ==
    std::declval<typename std::conditional<std::is_array<typename std::remove_reference<baseB>::type>::value, typename std::remove_extent<typename std::remove_reference<baseB>::type>::type*, baseB>::type>()
  )> final {
    static bool const value = (
      std::is_scalar<typename std::remove_reference<baseA>::type>::value &&
      std::is_scalar<typename std::remove_reference<baseB>::type>::value &&
      false == has_overload_equals<baseA, baseB, false>::value &&
      false == has_overload_equals<baseA, baseB, true> ::value
    );
  };

  // --> addressof(obj) ->> some object addresses can be retrieved at compile-time
  template <typename base>
  constexpr typename std::enable_if<false == (
    has_overloaded_addressof<base, false>::value ||
    has_overloaded_addressof<base, true> ::value
  ), base>::type* addressof(base& object) noexcept {
    return &object;
  }

  template <typename base>
  constexpr typename std::enable_if<false == (
    has_overloaded_addressof<base, false>::value ||
    has_overloaded_addressof<base, true> ::value
  ), base>::type* addressof(base&& object) noexcept {
    return &static_cast<base&>(object);
  }

  template <typename base>
  inline typename std::enable_if<false != (
    has_overloaded_addressof<base, false>::value ||
    has_overloaded_addressof<base, true> ::value
  ), base>::type* addressof(base& object) noexcept {
    return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(object)));
  }

  template <typename base>
  inline typename std::enable_if<false != (
    has_overloaded_addressof<base, false>::value ||
    has_overloaded_addressof<base, true> ::value
  ), base>::type* addressof(base&& object) noexcept {
    return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(static_cast<base&>(object))));
  }

  template <typename base, std::size_t capacity>
  constexpr base (*addressof(base (&object)[capacity])  noexcept)[capacity] {
    return &object;
  }

  template <typename base, std::size_t capacity>
  constexpr base (*addressof(base (&&object)[capacity]) noexcept)[capacity] {
    return &static_cast<base (&)[capacity]>(object);
  }
}

/* ... */
template <typename baseA, typename baseB, typename std::enable_if<false != can_direct_equals<baseA, baseB>::value, int>::type = 0>
constexpr bool equals(baseA&& objectA, baseB&& objectB) noexcept {
  return sizeof(baseA) == sizeof(baseB) && objectA == objectB;
}

template <typename baseA, typename baseB, typename std::enable_if<false == can_direct_equals<baseA, baseB>::value, int>::type = 0>
constexpr bool equals(baseA&& objectA, baseB&& objectB) noexcept {
  return sizeof(baseA) == sizeof(baseB) && (
    static_cast<void const volatile*>(addressof(objectA)) == static_cast<void const volatile*>(addressof(objectB)) ||
    0 == std::memcmp(&const_cast<unsigned char&>(reinterpret_cast<unsigned char const volatile&>(objectA)), &const_cast<unsigned char&>(reinterpret_cast<unsigned char const volatile&>(objectB)), sizeof(baseA) | sizeof(baseB))
  );
}

template <typename baseA, typename baseB, std::size_t capacity, std::size_t offset, typename std::enable_if<capacity == offset, int>::type = 0>
constexpr bool equals(baseA (&)[capacity], baseB (&)[capacity]) noexcept {
  return true;
}

template <typename baseA, typename baseB, std::size_t capacity, std::size_t offset = 0, typename std::enable_if<capacity != offset, int>::type = 0>
constexpr bool equals(baseA (&arrayA)[capacity], baseB (&arrayB)[capacity]) noexcept {
  return capacity == offset || (equals(arrayA[offset], arrayB[offset]) && equals<baseA, baseB, capacity, offset + 1>(arrayA, arrayB));
}

template <typename baseA, typename baseB, std::size_t capacity>
constexpr bool equals(baseA (&arrayA)[capacity], baseB (&&arrayB)[capacity]) noexcept {
  return equals(arrayA, static_cast<baseB (&&)[capacity]>(arrayB));
}

template <typename baseA, typename baseB, std::size_t capacity>
constexpr bool equals(baseA (&&arrayA)[capacity], baseB (&arrayB)[capacity]) noexcept {
  return equals(static_cast<baseA (&&)[capacity]>(arrayA), arrayB);
}

template <typename baseA, typename baseB, std::size_t capacity>
constexpr bool equals(baseA (&&arrayA)[capacity], baseB (&&arrayB)[capacity]) noexcept {
  return equals(static_cast<baseA (&&)[capacity]>(arrayA), static_cast<baseB (&&)[capacity]>(arrayB));
}
