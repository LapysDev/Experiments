/*
  Demonstration of type loophole.
  Part of the blog post:
  http://alexpolt.github.io/type-loophole.html
*/

#include <string>
#include <type_traits>

template<int N> struct tag{};

template<typename T, int N>
struct loophole_t {
  friend auto loophole(tag<N>) { return T{}; };
};

auto loophole(tag<0>);

int main() {

sizeof( loophole_t<std::string, 0> );

return std::is_same< std::string, decltype( loophole(tag<0>{}) ) >::value;

}
