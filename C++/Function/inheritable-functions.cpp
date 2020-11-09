#include <stdio.h>

class Animal { public:
  // function pointer & constructor
  void (Animal:: *const write)(void) const noexcept;
  constexpr Animal(void (Animal::*const write)(void) const /* noexcept */ = &Animal::put) : write{write} {}

  // virtual
  virtual void put(void) const noexcept { ::puts("Animal"); }
};

class Elephant : public Animal { public:
  // constructor
  constexpr Elephant(void) : Animal{static_cast<void (Animal::*)(void) const>(&Elephant::put)} {}

  // overridden virtual
  void put(void) const noexcept override { ::puts("Elephant"); }
};

int main(void) {
  Animal const animal = {};
  Elephant const elephant = {};

  Animal const *object = nullptr; {
    object = &animal;
      object -> put();
      (object ->* (object -> write))();

    object = &elephant;
      object -> put();
      (object ->* (object -> write))();
  }
}
