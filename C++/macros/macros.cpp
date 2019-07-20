/* Import */
#include <iostream> // Input-Output Stream

// Definition > (...)
#define THIS std::cout
#define STILL << "This still works because of C++ macros!" <<
#define WORKS std::endl;
#define KINDA 2;

// Function > Main
int main(int argc, char* argv[]) {
    // (...)
    THIS STILL WORKS! KINDA

    // Return
    return 0;
}
