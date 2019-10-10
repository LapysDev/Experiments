/* Import */
#include <unistd.h> // UNIX Standard

/* Main */
int main(int argc, char* argv[]) {
    // Print
    write(1, "Hello, World!", 13/* * sizeof(char)*/);

    // Return
    return 0;
}
