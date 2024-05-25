#include <cstdio>
#include <type_traits>

template <bool state> typename std::enable_if<false == state>::type put(void) { std::puts("[false]"); }
template <bool state> typename std::enable_if<true == state>::type put(void) { std::puts("[true]"); }

int main(void) {
    put<false>();
    put<true>();
}
