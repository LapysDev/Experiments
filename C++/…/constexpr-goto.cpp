#include <stdio.h>

int main(void) {
  enum {
    // possible addresses
    address_1, address_2, address_3
  } address_sequence[] = {
    // order in which to `goto`
    address_2, address_1, address_3
  }, *current_address = address_sequence;
  char const *string;

  while (0x0 != current_address)
  switch (*current_address) {
    // addresses to be jumped to; set some parameters, maybe?
    case address_1: string = "[address #1]"; goto print_string;
    case address_2: string = "[address #2]"; goto print_string;
    case address_3: string = "[address #3]"; goto print_string;

    // the similar code for all addresses
    // basically a function at this point
    default: print_string: {
      // your code
      puts(string);

      // move onto next address or terminate
      if (++current_address - address_sequence == sizeof(address_sequence) / sizeof(*address_sequence))
      current_address = 0x0;
    } break;
  }
}
