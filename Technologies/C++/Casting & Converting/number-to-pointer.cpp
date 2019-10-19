/* Import */
#include <fcntl.h> // Functional
#include <stdlib.h> // Standard Library

/* Function */
    // Number To Pointer --- WARN (Lapys) -> May cause undefined behavior.
    const void* number_to_pointer(const float number) {
        if (number) { char value; void *pointer = &value; return pointer; }
        else return NULL;
    }

/* Main */
int main(int argc, char* argv[]) {
    // Return
    return 0;
}
