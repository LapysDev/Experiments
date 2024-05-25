#include <cstddef>
#include <cstdio>
#include <type_traits>

/* ... */
struct fallback { unsigned char const member; };

template <class object>
struct detector : public fallback, public object {};

// ...
template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value>
union has_member {
  enum { value = false == derivable };
};

template <class object>
union has_member<object, typename std::integral_constant<std::size_t, sizeof(detector<object>::member)>::value_type, false> {
  enum { value = false };
};

template <class object>
union has_member<object, decltype(sizeof(&object::member)), true> {
  enum { value = true };
};

/* Main */
class A { int member; };
class B { int member(); };
class C { static int member(); };
class D { typedef int member; };
class E { union member; };
class F { template <int> union member; };
class G {};

union H { int member; };
union I { int member(); };
union J { static int member(); };
union K { typedef int member; };
union L { class member; };
union M { template <int> class member; };
union N {};

int main() {
  std::puts("[class]");
  std::printf("  [A]: %4.5s" "\r\n", has_member<A>::value ? "true" : "false");
  std::printf("  [B]: %4.5s" "\r\n", has_member<B>::value ? "true" : "false");
  std::printf("  [C]: %4.5s" "\r\n", has_member<C>::value ? "true" : "false");
  std::printf("  [D]: %4.5s" "\r\n", has_member<D>::value ? "true" : "false");
  std::printf("  [E]: %4.5s" "\r\n", has_member<E>::value ? "true" : "false");
  std::printf("  [F]: %4.5s" "\r\n", has_member<F>::value ? "true" : "false");
  std::printf("  [G]: %4.5s" "\r\n", has_member<G>::value ? "true" : "false");
  std::puts("[union]");
  std::printf("  [H]: %4.5s" "\r\n", has_member<H>::value ? "true" : "false");
  std::printf("  [I]: %4.5s" "\r\n", has_member<I>::value ? "true" : "false");
  std::printf("  [J]: %4.5s" "\r\n", has_member<J>::value ? "true" : "false");
  std::printf("  [K]: %4.5s" "\r\n", has_member<K>::value ? "true" : "false");
  std::printf("  [L]: %4.5s" "\r\n", has_member<L>::value ? "true" : "false");
  std::printf("  [M]: %4.5s" "\r\n", has_member<M>::value ? "true" : "false");
  std::printf("  [N]: %4.5s" "\r\n", has_member<N>::value ? "true" : "false");
}
