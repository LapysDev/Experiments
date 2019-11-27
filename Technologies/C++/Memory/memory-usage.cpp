/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/* Global */
union variant {unsigned char integer; long double rational;};

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > (Memory, Variant, ...)
    void *memory = NULL;
    variant variant;

    int integer = 255;
    long double rational = 12.54;

    // ...
    ::printf("[INITIATION]\n");
    ::printf("Size [Memory]: %u\n", sizeof(memory));
    ::printf("Size [Variant]: %u\n", sizeof(variant));
    ::printf("\n"); // std::fflush(stdout);

    // ...
    std::free(memory); memory = std::malloc(sizeof(rational)); *((long double*) memory) = rational;
    variant.rational = rational;

    ::printf("[ALLOCATION (long double)]\n");
    ::printf("Size [Memory]: %u, %u\n", sizeof(memory), sizeof(*((long double*) memory)));
    ::printf("Size [Variant]: %u\n", sizeof(variant));
    ::printf("\n"); // std::fflush(stdout);

    // ...
    std::free(memory); memory = std::malloc(sizeof(integer)); *((int*) memory) = integer;
    variant.integer = integer;

    ::printf("[ALLOCATION (int)]\n");
    ::printf("Size [Memory]: %u, %u\n", sizeof(memory), sizeof(*((int*) memory)));
    ::printf("Size [Variant]: %u\n", sizeof(variant));
    ::printf("\n"); // std::fflush(stdout);

    // ...
    std::free(memory); memory = NULL;
    variant.~variant();

    ::printf("[TERMINATION]\n");
    ::printf("Size [Memory]: %u\n", sizeof(memory));
    ::printf("Size [Variant]: %u", sizeof(variant));

    // Return
    return 0;
}
