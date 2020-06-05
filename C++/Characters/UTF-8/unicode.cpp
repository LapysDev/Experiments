/* Import */
#include <locale.h> // Locale
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/* Main */
int main(void) {
    // Initialization > String
    const char *string = u8"ايه الاخبار";

    // ...
    ::setlocale(LC_ALL, "en-US.UTF-8");

    // Loop ...
    ::putchar('[');
    for (char *stringIterator = (char*) string; *stringIterator; ) {
        // Initialization > Character (Iterator)
        char character[5] {0};
        char *characterIterator = character;

        // Update > Character Iterator
        *characterIterator++ = *stringIterator++;

        // Logic > Update > Character Iterator
        if ((*stringIterator & 0xC0) == 0x80) *characterIterator++ = *stringIterator++;
        if ((*stringIterator & 0xC0) == 0x80) *characterIterator++ = *stringIterator++;
        if ((*stringIterator & 0xC0) == 0x80) *characterIterator++ = *stringIterator++;
        *characterIterator = '\0';

        // ...
        ::putchar('\'');
        ::putchar(*character); ::putchar(*(character + 1)); ::putchar(*(character + 2)); ::putchar(*(character + 3)); ::putchar(*(character + 4));
        ::putchar('\''); if (*stringIterator) { ::putchar(','); ::putchar(' '); }
    }
    ::putchar(']');

    // ...
    ::setlocale(LC_ALL, "");

    // Return
    return EXIT_SUCCESS;
}
