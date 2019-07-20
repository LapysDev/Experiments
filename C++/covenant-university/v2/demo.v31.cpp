/* Library Files */
    // C Time
    #include <ctime>

    // Input-Output Stream
    #include <iostream>

/* Function */
    /* Sorted
            --- NOTE ---
                #Lapys: Determines if an array is sorted in ascending order.
    */
    template <typename data>
    bool sorted(data array, int length = -1) {
        int iterator = 0;
        (length == -1) && (length = sizeof(array));

        for (iterator; iterator != length; iterator += 1)
            if (array[iterator] > array[iterator + 1])
                return false;

        // Return
        return true;
    }

    // Main
    int main(int argc, char* argv[]) {
        // Seed Random > Time
        std::srand(std::time(NULL));

        // Initialization > (Iterator, Length, Array, Match)
        int iterator = 0,
            length = (std::rand() % 3) + 2,
            array[length],
            match;

        // Standard > C Output
        std::cout << "Program to determine if an array is sorted.\n" << std::endl;
        std::cout << "Array: ";

        /* Loop
                Index Array.
        */
        for (iterator; iterator != length; iterator += 1) {
            // Initialization > Random
            int random = ((std::rand() % 5) + 1) | 0;

            // Update > Array
            array[iterator] = random;

            // Standard > C Output
            std::cout << random << (iterator == length - 1 ? "" : ", ");
        }

        // Standard > C Output
        std::cout << std::endl;
        std::cout << "Sorted (Ascending): " << (sorted(array, length) ? "True" : "False");

        // Return
        return 0;
    }
