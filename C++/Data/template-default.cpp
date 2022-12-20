#include <cstdio>
#include <typeinfo>

/* ... */
template <typename type>
void function(type* const argument) {
  std::puts(typeid(argument).name());
}

void function(int* const argument) {
  return function<int>(argument);
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  function(static_cast<int*>(NULL));
  function(static_cast<void*>(NULL));
  function<int>(static_cast<int*>(NULL));
}
