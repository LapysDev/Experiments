/* Import */
#include <iostream> // Input-Output Stream

/* Function > ... */
int getLocalImmutableNumber() { static int value = 2; value *= 2; return value; }
int& getLocalMutableNumber() { static int value = 0; return value; }

/* Main */
int main(int argc, char *argv[]) {
    // Print
    std::cout << "(Local Mutable) Number: " << getLocalImmutableNumber() << std::endl;
    std::cout << "(Local Mutable) Number: " << getLocalImmutableNumber() << std::endl;
    std::cout << "(Local Mutable) Number: " << getLocalImmutableNumber() << std::endl;

    std::cout << "======================================" << std::endl;

    std::cout << "(Local Mutable) Number: " << getLocalMutableNumber() << std::endl; getLocalMutableNumber() = 5;
    std::cout << "(Local Mutable) Number: " << getLocalMutableNumber() << std::endl; getLocalMutableNumber() = 10;
    std::cout << "(Local Mutable) Number: " << getLocalMutableNumber() << std::endl;

    // Return
    return 0;
}
