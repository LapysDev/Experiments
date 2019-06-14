/* Library Files */
    // C Time
    #include <ctime>

    // Input-Output Stream
    #include <iostream>

/* Function */
    // Index Of Array
    template <class arrayData, class matchData>
    int indexOfArray(arrayData array[], matchData match, int length = -1) {
        // Initialization > (Index, Iterator)
        int index = -1, iterator = 0;

        // Update > Length
        (length == -1) && (length = sizeof(array));

        /* Loop
                Index Array.
        */
        for (iterator; iterator != length; iterator += 1)
            /* Logic
                    [if statement]
            */
            if (array[iterator] == match) {
                // Update > Index
                index = iterator;

                // Break
                break;
            }

        // Return
        return index;
    }

    // Main
    int main(int argc, char* argv[]) {
        // Seed Random > Time
        std::srand(std::time(NULL));

        // Initialization > (Iterator, Length, Array, Match)
        int iterator = 0,
            length = (std::rand() % 10) + 5,
            array[length],
            match;

        // Standard > C Output
        std::cout << "Program to index a match from an array.\n" << std::endl;
        std::cout << "Array: ";

        /* Loop
                Index Array.
        */
        for (iterator; iterator != length; iterator += 1) {
            // Initialization > Random
            int random = ((std::rand() % 10) + 1) | 0;

            // Update > Array
            array[iterator] = random;

            // Standard > C Output
            std::cout << random << (iterator == length - 1 ? "" : ", ");
        }

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C (Input, Output)
        std::cout << "Match: ";
        std::cin >> match;

        // Standard > C Output
        std::cout << std::endl;
        std::cout << "Index: " << indexOfArray(array, match, length);

        // Return
        return 0;
    }
