/* Import */
#include <fcntl.h> // Functional
#include <stdlib.h> // Standard Library
#include <stdio.h> // Standard Input-Output
#include <string.h> // String

/* Function */
    // Pointer To String --- WARN (Lapys) -> Ignores leading (from the back) zeroes.
    const char* pointer_to_string(const void* pointer) {
        // Initialization > (Pointer ..., String ...)
        unsigned pointerNumber = unsigned(pointer);
        unsigned stringLength = 0u;

        static char *string = NULL;

        // Deletion; Update > String
        std::free(string);
        string = (char*) std::malloc(1u * sizeof(char));

        // Loop
        while (pointerNumber) {
            // Constant > Pointer Number Digit
            const unsigned POINTER_NUMBER_DIGIT = pointerNumber % 16u;

            // Update > (String ...)
            string = (char*) std::realloc(string, (stringLength + 2u) * sizeof(char));
            *(string + stringLength) = POINTER_NUMBER_DIGIT + (POINTER_NUMBER_DIGIT > 9u && POINTER_NUMBER_DIGIT < 36u ? 55u : 48u);

            pointerNumber /= 16u;
            stringLength += 1u;
        }

        // Update > String
        *(string + stringLength) = '\0';
        ::strrev(string);

        // Return
        return string;
    }

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > Pointer
    void *pointer;

    pointer = NULL;
    ::printf("[POINTER]: %p\n", pointer);
    ::printf("[POINTER -> STRING]: %s\n\n", ::pointer_to_string(pointer));
    std::free(pointer);

    pointer = std::malloc(0u);
    ::printf("[POINTER]: %p\n", pointer);
    ::printf("[POINTER -> STRING]: %s\n\n", ::pointer_to_string(pointer));
    std::free(pointer);

    pointer = new char;
    ::printf("[POINTER]: %p\n", pointer);
    ::printf("[POINTER -> STRING]: %s\n\n", ::pointer_to_string(pointer));
    delete (char*) pointer;

    // Return
    return 0;
}

