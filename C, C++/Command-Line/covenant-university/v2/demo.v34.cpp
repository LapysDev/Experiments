/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Factorial
    int factorial(int number) {
        int result = 1;

        for (int iterator = 1; iterator <= number; iterator += 1)
            result = result * iterator;

        return result;
    }

    // Main
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to calculate the factorial of a number.\n" << std::endl;

        int number;

        std::cout << "Number: ";
        std::cin >> number;

        std::cout << "Factorial: " << factorial(number);

        // Return
        return 0;
    }
