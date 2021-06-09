#include <cstdio>

/* ... */
class Person {
  private: char const *const name;
  public:
    Person(char const name[]) : name(name) {}
    char const* getName(void) const;
};

char const* Person::getName(void) const {
  static Person const *const that = this;
  struct lambda { static char const* call(void) { return that -> name; } };

  return lambda::call();
}

/* Main */
int main(void) {
  Person const person = Person("Lapys");
  std::printf("[]: \"%s\"", person.getName());
}
