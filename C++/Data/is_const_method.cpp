#include <cstdio>
#include <type_traits>
#include <utility>

namespace lapys {
    // ...
    template <class...>
    using void_t = void;

    // ...
    template <class object, class = void_t<>>
    struct is_method_const : std::false_type {};

    template <class object>
    struct is_method_const<object, void_t<decltype(std::declval<typename std::add_const<object>::type>().method())>> : std::true_type {};
}

/* Main */
int main(void) {
  class Immutable { public: void method(void) const {} };
  class Mutable { public: void method(void) {} };

  // Checks if a `.method()` call (which resolves potential overloads)
  //   uses a `const`-qualified function or not.
  //   *not sure how this fully works with derived types.
  std::printf("[Immutable]: %s" "\r\n", lapys::is_method_const<Immutable>::value ? "true" : "false");
  std::printf("[Mutable]: %s" "\r\n", lapys::is_method_const<Mutable>::value ? "true" : "false");
}
