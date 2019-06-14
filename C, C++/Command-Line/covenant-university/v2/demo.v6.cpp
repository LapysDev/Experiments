/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > Number (A, B)
        double numberA, numberB;

        // Standard > C (Output, Input)
        std::cout << "Program to test the greater of two numbers:\n" << std::endl;
        std::cout << "Number A: ";
        std::cin >> numberA;
        std::cout << "Number B: ";
        std::cin >> numberB;
        std::cout << std::endl;
        std::cout << "Number A (" << numberA << ") is " << (numberA > numberB ? "greater than" : "lesser than") << " Number B (" << numberB << ")";

        // Return
        return 0;
    }
