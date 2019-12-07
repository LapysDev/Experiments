/* Import */
#include <stdio.h> // Standard Input-Output

/* Main */
int main(int argumentCount, char* argumentVector[]) {
    // ... --- NOTE (Lapys) -> Print the number of arguments.
    ::printf("Argument Count: %i\n\n", argumentCount);

    // Loop --- NOTE (Lapys) -> Print the arguments.
    for (unsigned argumentVectorIndex = 0u; argumentVectorIndex ^ argumentCount; argumentVectorIndex += 1u) {
        // ...; Logic > ...
        ::printf("Argument Vector [%u]: \"%s\"", argumentVectorIndex, *(argumentVector + argumentVectorIndex));
        if (argumentVectorIndex ^ argumentCount - 1) { ::putchar('\n'); ::fflush(stdout); }
    }

    // Return
    return 0;
}
