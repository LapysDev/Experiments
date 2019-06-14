/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Average
    double average(int numberA, int numberB, int numberC, int numberD) {
        // Return
        return static_cast<double>(numberA + numberB + numberC + numberD) / 4;
    };

    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Length, Numbers)
        int length = 4, numbers[length];

        // Standard > C Output
        std::cout << "Program to calculate the factorial of numbers from 0-20:\n" << std::endl;

        /* Loop
                Index Numbers.

            > Standard > C (Input, Output)
        */
        for (int iterator = 0; iterator != length; iterator += 1) {
            std::cout << "Number " << (iterator + 1) << ": ";
            std::cin >> numbers[iterator];
        }

        // Standard > C Output
        std::cout << std::endl;
        std::cout << "Average: " << average(*numbers, *(numbers + 1), *(numbers + 2), *(numbers + 3));

        // Return
        return 0;
    }
