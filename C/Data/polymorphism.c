/* ... */
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Classes -> Might need additional data to simulate access specifiers. */
struct Animal { unsigned short id; void (*put)(void const*); };
struct Human { struct Animal __proto__; char const *name; };

/* Methods */
void Animal__proto__put(struct Animal const* const this) { printf("{Animal : (%u)}" "\r\n", this -> id); }
void Human__proto__put(struct Human const* const this) { printf("{Human : (%u) \"%s\"}" "\r\n", this -> __proto__.id, this -> name); }

/* Statics */
unsigned short Animal__proto__total = 0u;

/* Constructor, Destructor */
void delete(void const* const this) { free((void*) this); }
void* new(size_t const size, ...) {
  void *const allocation = malloc(size);
  va_list arguments;

  // assume is of `struct Animal` ¯\_(ツ)_/¯
  va_start(arguments, size); {
    struct Animal const animal = {++Animal__proto__total, size == sizeof(struct Human) ? (void (*)(void const*)) &Human__proto__put : (void (*)(void const*)) &Animal__proto__put};

    if (size != sizeof(struct Human)) memcpy(allocation, &animal, size);
    else {
      struct Human const human = {animal, va_arg(arguments, char const*)};
      memcpy(allocation, &human, size);
    }
  } va_end(arguments);

  return allocation;
}

/* ... */
int main(void) {
  struct Animal const *const animal = new (sizeof(struct Animal));
  struct Human const *const human = new (sizeof(struct Human), "Lapys");

  animal -> put(animal);
  human -> __proto__.put(human);

  delete (animal);
  delete (human);
}
