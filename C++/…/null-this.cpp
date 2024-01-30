#include <cstdio>

/* ... */
class Object {
  public:
  void method(void) const {
    std::printf("%p -> method();" "\r\n", static_cast<void const*>(this));
  }
};

/* Main */
int main(void) {
  Object *object;
  object = NULL;
  object -> method();
}
