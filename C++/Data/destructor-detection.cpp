#include <cstddef>
#include <cstdio>

/* ... */
template <std::size_t>
struct assertion;

// ...
template <typename, typename = assertion<sizeof(bool)> >
struct has_destructor {
  static bool const value = false;
};

template <typename T>
struct has_destructor<T, assertion<sizeof(static_cast<T*>(NULL) -> ~T(), false)> > {
  static bool const value = true;
};

/* ... */
struct NonDestructible final {
  ~NonDestructible() = delete;
};

template <typename type>
void destroy(type&) {
  if (true  == has_destructor<type>::value) std::puts("calling destructor");
  if (false == has_destructor<type>::value) std::puts("unable to destruct");
}

/* Main */
int main(void) {
  int             integer = 42;
  NonDestructible *object = new NonDestructible;

  // ...
  destroy(integer); // calling destructor
  destroy(*object); // unable to destruct
}
