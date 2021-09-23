#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include <new>

/* ... */
struct Object {
  Object *const reference;
  Object(void) : reference(this) {}
};

/* Main */
int main(void) {
  Object *array = NULL;
  std::size_t const base = 2u;
  std::size_t length = 0u;
  bool moved = false;

  // keep reallocating additinoal memory until the `array` block "moves"
  for (Object *buffer; false == moved; ++length) {
    std::size_t const newLength = base * (length + 1u);
    std::ptrdiff_t const offset = base * length;

    // ... -Wclass-memaccess: moving an object of non-trivially copyable type; use `new` and `delete` instead
    buffer = static_cast<Object*>(std::realloc(array, newLength * sizeof(Object)));
    moved = NULL != array && array != buffer;
    array = buffer;

    // initialize the objects
    for (unsigned char iterator = 0u; base != iterator; ++iterator)
    new (array + iterator + offset) Object();

    // print the objects
    std::printf("%p [", static_cast<void*>(array));
      for (unsigned char iterator = 0u; iterator != newLength; ++iterator)
      std::printf("%s %p" "%s",
        array + iterator == array[iterator].reference ? "==" : "!=",
        static_cast<void*>(array[iterator].reference),
        newLength - 1u == iterator ? "" : ", "
      );
    std::printf("]" "\r\n");
  }

  // ...
  for (unsigned char iterator = base * length; iterator--; )
  array[iterator].~Object();

  std::free(array);
}
