/* Import */
    // Standard Library
    #include <stdlib.h>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > Buffer (A, B, C)
        int* bufferA, *bufferB, *bufferC;

        // Update > Buffer (A, B, C)
        bufferA = (int*) std::malloc(100 * sizeof(int));
        bufferB = (int*) std::calloc(100, sizeof(int));
        bufferC = (int*) std::realloc(bufferB, 500 * sizeof(int));

        // Deletion
        std::free(bufferA);
        std::free(bufferC);

        // Return
        return 0;
    }
