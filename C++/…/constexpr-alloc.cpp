/* ... ->> since C++20, and only works in constant evaluated contexts unfortunately */
#include <memory>
#include <utility>

template <typename type, typename... types> // works for types compliant with `std::construct_at<>(...)` and `std::allocator_traits<>::allocate(...)`
constexpr type function(types&&... arguments) noexcept {
  std::allocator<type> allocator = {};
  type *const buffer             = std::allocator_traits<std::allocator<type> >::allocate(allocator, 1u);
  type  value                    = *std::construct_at<type>(buffer, std::forward<types>(arguments)...);

  // ...
  std::destroy_at(buffer);
  std::allocator_traits<std::allocator<type> >::deallocate(allocator, buffer, 1u);

  return value;
}

/* ... ->> since C++14, (or since C++11) or just pretend when it comes to trivially-copyable types */
namespace {
  template <typename type>
  struct allocator final {
    type value;
  };

  template <typename type>
  constexpr type* allocate(allocator<type> const /* volatile */& allocator) noexcept {
    return const_cast<type*>(&allocator.value);
  }

  template <typename type>
  constexpr type* allocate(allocator<type> const /* volatile */&& allocator) noexcept {
    return const_cast<type*>(&allocator.value);
  }

  template <typename type, typename... types>
  constexpr type* construct_at(type* const address, types&&... arguments) noexcept {
    return &(*address = type(std::forward<types>(arguments)...));
  }
}

template <typename type, typename... types>
constexpr type function(types&&... arguments) noexcept {
  allocator<type> allocator = {};
  type *const     buffer    = allocate(allocator);
  type const      value     = *construct_at(buffer, std::forward<types>(arguments)...);

  return value;
}
