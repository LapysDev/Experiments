/* Import */
#include <fcntl.h> // Functional
#include <stdlib.h> // Standard Library
#include <stdio.h> // Standard Input-Output

/* Function */
    // Pointer To Number
    const unsigned pointer_to_number(const void* pointer) { return unsigned(pointer); }

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > Pointer
    void *pointer;

    // ...
    pointer = NULL;
    ::printf("[POINTER]: %p\n", pointer);
    ::printf("[POINTER -> NUMBER]: %u\n\n", ::pointer_to_number(pointer));
    std::free(pointer);

    pointer = std::malloc(0u);
    ::printf("[POINTER]: %p\n", pointer);
    ::printf("[POINTER -> NUMBER]: %u\n\n", ::pointer_to_number(pointer));
    std::free(pointer);

    pointer = new char;
    ::printf("[POINTER]: %p\n", pointer);
    ::printf("[POINTER -> NUMBER]: %u\n\n", ::pointer_to_number(pointer));
    delete (char*) pointer;

    // Return
    return 0;
}

