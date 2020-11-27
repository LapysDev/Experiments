#include <stdio.h>

int main(void) {
  char STRING[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
  constexpr unsigned char STRING_LENGTH = sizeof(STRING) / sizeof(char);

  ::puts(STRING);

  for (char *iterator = STRING + STRING_LENGTH; STRING != iterator--; )
  if (',' == *iterator) {
    do *iterator = *(iterator + 1);
    while (STRING_LENGTH != ++iterator - STRING);

    break;
  }

  ::puts(STRING);
}
