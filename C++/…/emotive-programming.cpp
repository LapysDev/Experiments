#include <cstdio>

/* ... */
struct Person {
  bool 💙(Person const) const {
    return true;
  }
};

/* ... */
int main() {
  Person const clara;
  Person const timothy;

  std::puts((clara) .💙 (timothy) ? "true" : "false");
}
