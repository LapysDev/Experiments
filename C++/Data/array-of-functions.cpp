#include <cstdio>

/* ... */
struct Base {};
struct Child1 : Base {};
struct Child2 : Base {};

void foo(Child1 const&) { std::puts("Child 1"); }
void bar(Child2 const&) { std::puts("Child 2"); }

/* Main */
int main(void) {
  foo(Child1());
  bar(Child2());

  // ... -> this can be `typedef`ed/ `using`ed for clarity sake
  void (*const pointers[2])(void) = {
    reinterpret_cast<void (*)(void)>(&foo),
    reinterpret_cast<void (*)(void)>(&bar)
  };

  reinterpret_cast<void (*)(Child1 const&)>(pointers[0])(Child1());
  reinterpret_cast<void (*)(Child2 const&)>(pointers[1])(Child2());

  // ...
  union {
    void (*foo)(Child1 const&);
    void (*bar)(Child2 const&);
  } aliases[2];

  aliases[0].foo = &foo;
  aliases[0].foo(Child1());

  aliases[1].bar = &bar;
  aliases[1].bar(Child2());
}
