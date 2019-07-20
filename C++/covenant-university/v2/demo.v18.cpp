/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities*/
    // Namespace > Standard
    using namespace std;

/* Function */
    // Factorial
    int factorial(int integer) {
        /* Logic
                [if:else if statement]

            > Return
        */
        if (!integer)
            return 0;

        else if (integer == 1)
            return 1;

        // Return
        return integer * factorial(integer - 1);
    };

    // Main
    int main() {
        // Initialization > Integer
        int integer;

        // Standard > C (Input, Output)
        std::cout << "Program to calculate the factorial of an integer:\n" << std::endl;
        std::cout << "Integer: ";
        std::cin >> integer;
        std::cout << "Factorial: " << factorial(integer);

        // Return
        return 0;
    }
