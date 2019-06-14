/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Dividend, Divisor)
        unsigned long int dividend, divisor;

        // Standard > C (Output, Input)
        std::cout << "Program to test for the divisibility of an integer:\n" << std::endl;
        std::cout << "Dividend: "; std::cin >> dividend;
        std::cout << "Divisor: "; std::cin >> divisor;
        std::cout << std::endl;
        std::cout << dividend << " is" << (dividend % divisor ? " not" : "") << " divisible by " << divisor;

        // Return
        return 0;
    }
