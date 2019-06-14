/* Import */
#include <cstdio> // C Standard Input-Output
#include <unistd.h> // Unix Standard Header

/* Main */
int main(int argc, char* argv[]) {
    // Write
    ::write(STDOUT_FILENO, "Hello, World!", 13);
    ::write(STDOUT_FILENO, "\b\b\b\b\b\b\b\b\b\b\b\b\b", 13);
    ::write(STDOUT_FILENO, "             ", 13);
    ::write(STDOUT_FILENO, "\b\b\b\b\b\b\b\b\b\b\b\b\b", 13);
    ::write(STDOUT_FILENO, "Lorem ipsum", 11);

    // Return
    return 0;
}
