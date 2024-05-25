#include <stdio.h>

int main(void) {
  unsigned char const count = 3u;
  struct person {
    unsigned short age;
    char name[64 + 1];
  } people[count];

  // ...
  for (unsigned char iterator = 0u; count != iterator; ++iterator) {
    unsigned char length;

    // ...
    people[iterator].age = 0u;
    people[iterator].name[0] = '\0';

    /* ... --> scanf("%64s", people[iterator].name); */
    printf("Please enter name %u: ", iterator + 1u);
    for (length = 0u; length != 64u; ++length) {
      int const character = getchar();
      if (EOF == character || '\n' == character) break;

      people[iterator].name[length] = character;
    } people[iterator].name[length] = '\0';

    /* ... --> scanf("%hu", &people[iterator].age); */
    printf("Please enter age %u: ", iterator + 1u);
    for (length = 100u; length != 0u; length /= 10u) {
      int const character = getchar();
      if (EOF == character || '\n' == character) break;

      people[iterator].age += length * (character - '0');
    } while (length != 0u) { people[iterator].age /= 10u; length /= 10u; }
  }

  // ...
  puts("*************************");

  for (unsigned char iterator = 0u; count != iterator; ++iterator)
  printf("\"%s\" %hu" "\r\n", people[iterator].name, people[iterator].age);
}
