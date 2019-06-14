/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to calculate the factorial of a number.\n" << std::endl;

        int factorial = 1, number;

        std::cout << "Number: ";
        std::cin >> number;

        for (int iterator = 1; iterator <= number; iterator += 1)
            factorial = factorial * iterator;

        std::cout << "Factorial: " << factorial;

        // Return
        return 0;
    }
