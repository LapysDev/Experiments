/* Import */
#include <iostream> // Input-Output Stream

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > (Un)Signed Integer
    signed signedInteger; unsigned unsignedInteger;

    // Update > (Un)Signed Integer
    signedInteger = -1;
    unsignedInteger = signedInteger;
    signedInteger = unsignedInteger;

    // Print
    std::cout << "[Signed = -1]" << std::endl;
    std::cout << "Signed: " << signedInteger << std::endl;
    std::cout << "Unsigned: " << unsignedInteger << std::endl;
    std::cout << std::endl;

    // Update > (Un)Signed Integer
    unsignedInteger = 4294967295;
    signedInteger = unsignedInteger;
    unsignedInteger = signedInteger;

    // Print
    std::cout << "[Unsigned = 4294967295]" << std::endl;
    std::cout << "Signed: " << signedInteger << std::endl;
    std::cout << "Unsigned: " << unsignedInteger << std::endl;
    std::cout << std::endl;

    // Return
    return 0;
}
