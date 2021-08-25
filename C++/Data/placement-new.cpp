#include <cstddef>
#include <cstdio>

/* ... */
struct Object {
  char const *name;
  unsigned age;

  Object(char const name[], unsigned const age) :
    name(name), age(age)
  {}

  // ...
  void* operator new(std::size_t const, void* const pointer) throw() {
    return pointer;
  }
};

/* Main */
int main() {
  alignas(Object) unsigned char memory[sizeof(Object)];
  Object *const object = new (memory) Object("Lapys", 21u);

  std::printf("\"%s\" (%u)", object -> name, object -> age);
}
