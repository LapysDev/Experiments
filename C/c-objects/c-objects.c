/* Import */
#include <unistd.h> // Unix Standard Library
#include "c-objects.h" // C Objects

/* Main */
int main(int argc, char* argv[]) {
    // Print
    write(1, "[PROGRAM INITIATED]\n", 20);

    // Print
    write(1, "[PROGRAM TERMIANTED]", 20);

    // Return
    return 0;
}
