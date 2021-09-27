template <typename type> // this allows any type to be passed in
void function(type object) {}

/* ... */
int main() {
  function(0); // works!
}

// template <int... n>
// void put() { put<n..., n...>(); }

// int main() {
//   put<0>();
// }
