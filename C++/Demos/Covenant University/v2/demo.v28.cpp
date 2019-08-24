/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Iterator, Length)
        int iterator = 0,
            length;

        // Standard > C Output
        std::cout << "Program to request a range of numbers from an array and print the resulting array items.\n" << std::endl;

        // Standard > C (Input, Output)
        std::cout << "Array Length (integer): ";
        std::cin >> length;

        // Initialization > Array
        double array[length];

        // Standard > C Output
        std::cout << "Array Items (up to " << length << " numbers): ";

        /* Loop
                Index Array.
        */
        for (iterator; iterator != length; iterator += 1) {
            // Standard > C Input
            std::cin >> array[iterator];

            // Standard > C Output
            (iterator == length - 1) || (std::cout << "   , ");
        }

        // Standard > C Output
        std::cout << "Array Items (in reverse): ";

        /* Loop
                Index Array.
        */
        while (iterator) {
            // Update > Iterator
            iterator -= 1;

            // Standard > C Output
            std::cout << *(array + iterator);
            iterator && (std::cout << ", ");
        }

        // Return
        return 0;
    }
