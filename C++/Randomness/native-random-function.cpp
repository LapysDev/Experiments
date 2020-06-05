/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/* Main */
int main(int argumentCount, char* argumentVector[]) {
    // Loop
    for (unsigned char iterator = 0u, length = -1; iterator ^ length; iterator += 1u) {
        // Constant > Value
        const unsigned long value = ::rand();

        // ...; Logic > ...
        ::printf("Random Value: %u (%i)", ((unsigned char) value) % 10u, value);
        if (iterator ^ length - 1u) { ::putchar('\n'); ::fflush(stdout); }
    }

    // Return
    return 0;
}
