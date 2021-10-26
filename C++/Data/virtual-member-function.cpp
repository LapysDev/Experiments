#include <cstdio>

class Animal { public:
  // function pointer & constructor
  void (Animal:: *const write)() const noexcept;
  constexpr Animal(void (Animal::*const write)() const /* noexcept */ = &Animal::put) : write{write} {}

  // virtual
  virtual void put() const noexcept { std::puts("Animal"); }
};

class Elephant : public Animal { public:
  // constructor
  constexpr Elephant() : Animal{static_cast<void (Animal::*)() const>(&Elephant::put)} {}

  // overridden virtual
  void put() const noexcept override { std::puts("Elephant"); }
};

int main() {
  Animal const animal = {};
  Elephant const elephant = {};

  // ...
  Animal const *object = NULL;

  object = &animal;
  object -> put();
  (object ->* (object -> write))();

  object = &elephant;
  object -> put();
  (object ->* (object -> write))();
}
