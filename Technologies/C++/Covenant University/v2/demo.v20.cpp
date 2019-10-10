/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Factorial
    unsigned long long factorial(int integer) {
        // Initialization > Factorial
        int factorial = 1;

        // Logic > Return
        if (!integer || integer == 1)
            return 1;

        // Loop > Update > Factorial
        for (int iterator = 0; iterator != integer; iterator += 1)
            factorial *= iterator + 1;

        // Return
        return factorial;
    };

    // Main
    int main() {
        // Initialization > Integer
        int integer;

        // Standard > C (Input, Output)
        std::cout << "Program to calculate the factorial of numbers from 0-20:\n" << std::endl;

        // Loop > (Standard > C Output)
        for (int iterator = 0; iterator != 21; iterator += 1)
            std::cout << "Factorial of " << iterator << "\t= " << factorial(iterator) << std::endl;

        // Return
        return 0;
    }
