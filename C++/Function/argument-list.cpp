#include <iostream>

template <typename type> constexpr void put(type const[]) {}
template <typename type, typename... types>
constexpr void put(type list[], type argument, types... arguments) {
  *list = argument;
  put(++list, arguments...);
}

template <typename type, typename... types>
constexpr type* get(type argument, types... arguments) {
  type *const list = new type[1u + sizeof...(arguments)];
  put(list, argument, arguments...);
  return list;
}

int main(void) { std::cout << get(1, 2, 3)[0]; }
