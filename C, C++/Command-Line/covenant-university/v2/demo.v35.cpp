/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Factorial
    int factorial(int number) {
        if (number == 0)
            return 0;

        else if (number == 1)
            return 1;

        else
            return number * factorial(number - 1);
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
