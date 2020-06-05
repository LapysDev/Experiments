/* Import */
#include <iostream> // Input-Output Stream

/* Function > ... */
int get_local_immutable_number() { static int value = 2; value *= 2; return value; }
int& get_local_mutable_number() { static int value = 0; return value; }

/* Main */
int main(int argc, char *argv[]) {
    // Print
    std::cout << "(Local Immutable) Number: " << get_local_immutable_number() << std::endl;
    std::cout << "(Local Immutable) Number: " << get_local_immutable_number() << std::endl;
    std::cout << "(Local Immutable) Number: " << get_local_immutable_number() << std::endl;

    std::cout << "======================================" << std::endl;

    std::cout << "(Local Mutable) Number: " << get_local_mutable_number() << std::endl; get_local_mutable_number() = 5;
    std::cout << "(Local Mutable) Number: " << get_local_mutable_number() << std::endl; get_local_mutable_number() = 10;
    std::cout << "(Local Mutable) Number: " << get_local_mutable_number() << std::endl;

    // Return
    return 0;
}
