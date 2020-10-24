#include <limits.h>
#include <stdio.h>

unsigned char digits;
unsigned radix;

inline void put(void) {
  if (0u == digits) ::printf("[...]");
  else {
    unsigned char iterator;
    unsigned char length = 1u;

    for (iterator = UCHAR_MAX; iterator /= radix; ) length *= radix;
    for (iterator = digits; length; length /= radix) ::printf("[%u]", (iterator / length) % radix);
  }

  ::printf("%s", "\r\n");
}

inline void setdigitsof(unsigned char& collection, unsigned char index, unsigned char const value, unsigned char length) {
  unsigned char digits = 0u;
  unsigned short exponent = 1u;

  ++index;
  for (unsigned char iterator = collection; index--; iterator /= radix) {
    digits += exponent * (iterator % radix);
    exponent *= radix; // exponent is unsigned short because it may overflow here
  }
  while (length--) exponent /= radix;

  collection -= digits;
  collection += (exponent * value) + (digits - (exponent * (digits / exponent)));
}

inline void set(unsigned char number) {
  unsigned char iterator;
  unsigned char length = 0u;

  for (iterator = UCHAR_MAX; iterator; iterator /= radix) ++length;

  for (iterator = 0u; number; number /= radix) setdigitsof(digits, iterator++, number % radix, 1u);
  while (iterator ^ length) setdigitsof(digits, iterator++, 0, 1u);

  for (iterator = digits, length = 1u, digits = 0u; iterator; iterator /= radix, length *= radix)
  digits += length * (iterator % radix);
}

int main(void) {
  radix = 2u; set(255u), put(); // -> All 1s because 8 of those is 255
  radix = 16u; set(255u), put(); // -> [15, 15] because 0xFF is 255
  radix = 10u; set(255u), put(); // -> 255 as expected

  // set the digits to 1, 2, and 3
  setdigitsof(digits, 2u, 12, 2u);
  setdigitsof(digits, 0u, 3, 1u);
  put();
}
