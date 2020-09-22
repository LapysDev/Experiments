// ===
#include <cstdint>
#include <cstdio>
#include <iostream>

// ===
template <size_t> struct extension;
template <size_t> struct primitive;

// additional behavior based on template
template <> struct extension<0u> {
  primitive<0u> *self;
  operator char*() { return (char*) "[zero]"; }
};

template <size_t state> struct extension {
  primitive<state> *self;
  char string[20] {};

  operator char*() {
    sprintf(string, "%i", self -> value);
    return string;
  }
};

// default behavior + interface
template <size_t state>
struct primitive : extension<state> {
  int value;

  primitive(void) :
    extension<state>{this},
    value{(state << 1u) >> 1u}
  {}
};

// ===
int main(void) {
  std::cout <<
    "\n[00]: " << primitive<00>() <<
    "\n[10]: " << primitive<10>() <<
    "\n[16]: " << primitive<16>() <<
  std::flush;
}
