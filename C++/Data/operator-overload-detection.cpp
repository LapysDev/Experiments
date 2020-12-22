#include <cstddef>
#include <iostream>

// ...
struct add_overload { public: void operator +(void); };
template <class object> struct inherited : public object, public add_overload {};
template <typename type> constexpr type&& instanceof(void) noexcept;

// ...
template <class, typename = void>
struct has_overload { static bool const value = true; };

template <class object>
struct has_overload<object, decltype(static_cast<void>(
  &inherited<object>::operator +
))> { static bool const value = false; };

// ...
class A { public: void operator +(void); };
class B { public: void operator +(int); };
class C { protected: void operator +(A const&); };
class D { private: void operator +(A const&); };
class E { private: void operator +(add_overload const&); };
class F { private: void operator +(void); void operator +(A const&); };
class G { private: friend void operator +(G const&); };
class H {};

/* Main */
int main(void) {
  std::boolalpha(std::cout);

  std::cout << "[A]: " << has_overload<A>::value << std::endl;
  std::cout << "[B]: " << has_overload<B>::value << std::endl;
  std::cout << "[C]: " << has_overload<C>::value << std::endl;
  std::cout << "[D]: " << has_overload<D>::value << std::endl;
  std::cout << "[E]: " << has_overload<E>::value << std::endl;
  std::cout << "[F]: " << has_overload<F>::value << std::endl;
  std::cout << "[G]: " << has_overload<G>::value << std::endl;
  std::cout << "[H]: " << has_overload<H>::value << std::endl;
}
