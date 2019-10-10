/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Minimum
    int min(int a, int b) {
        // Return
        return a < b ? a : b;
    };

    int min(int a, int b, int c) {
        // Return
        return min(min(a, b), c);
    };

    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Iterator, Length, Numbers)
        int iterator = 0,
            length = 3,
            numbers[length];

        // Standard > C Output
        std::cout << "Program to calculate the minimum of a set of integers:\n" << std::endl;

        /* Loop
                [for statement]

            > Standard > C (Input, Output)
        */
        for (iterator; iterator != length; iterator += 1) {
            std::cout << "Number " << (iterator + 1) << ": ";
            std::cin >> numbers[iterator];
        }

        // Standard > C Output
        std::cout << std::endl;
        std::cout << "Minimum: " << (length == 2 ? min(*numbers, *(numbers + 1)) : min(*numbers, *(numbers + 1), *(numbers + 2)));

        // Return
        return 0;
    }
