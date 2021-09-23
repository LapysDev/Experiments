#include <stdio.h>

int main(void) {
  char string[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
  constexpr unsigned char stringLength = sizeof(string) / sizeof(char);

  ::puts(string);

  for (char *iterator = string + stringLength; string != iterator--; )
  if (',' == *iterator) {
    do *iterator = *(iterator + 1);
    while (stringLength != ++iterator - string);

    break;
  }

  ::puts(string);
}
