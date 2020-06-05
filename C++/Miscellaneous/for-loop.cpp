/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/* Main */
int main(void) {
    // Loop > ...
    for (size_t iterator = 0u; iterator ^ 10u; ++iterator)
    ::printf("%s%u\n\r", "[DEBUG]: ", iterator);

    // Return
    return EXIT_SUCCESS;
}
