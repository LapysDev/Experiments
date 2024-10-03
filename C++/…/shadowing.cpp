#include <ciso646>
#include <cstddef>
#include <cstdio>

/* Main */
int main(int, char*[]) /* noexcept */ {
  struct fighter {
    // base
    static void attack(struct fighter*) {
    }

    // derived
    struct attack {
      static void boost(struct fighter* foo) {
        fighter::attack(foo);
        fighter::attack(foo);
      }

      static void combo  (struct fighter*);
      static void debuff (struct fighter*);
      static void element(struct fighter*);
      static void magic  (struct fighter*);
      static void multi  (struct fighter*);
      static void range  (struct fighter*);
    };
  } john = {};

  fighter::attack       (&john); // regular attack
  fighter::attack::boost(&john); // boosted attack
}
