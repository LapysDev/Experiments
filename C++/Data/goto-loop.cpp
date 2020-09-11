/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/* Main */
int main(void) {
    // Loop
    { size_t iterator = 0u; iterate: if (iterator ^ 10u) {
        // ...
        ::printf("%s%u\n\r", "[DEBUG]: ", iterator);

        // Continue
        ++iterator; goto iterate;
    } }

    // Return
    return EXIT_SUCCESS;
}
