/* Import */
#include <iostream> // Input-Output Stream

/* Main */
int main(void) {
    // ...
    for (unsigned iterator = 0u; iterator ^ (13u + 1u); iterator += 1u) std::cout << iterator["Hello, World!"]; std::cout << std::endl;
    for (char *iterator = (char*) "Hello, World!"; iterator[0] ^ '\0'; iterator += 1u) std::cout << iterator[0]; std::cout << std::endl;

    // ...
    std::cout << std::flush;

    // Return
    return 0;
}
