/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Sub) Iterator
        int iterator = 0, subIterator = 0;

        // Standard > C Output
        std::cout << "Printing the Letter 'B': \n" << std::endl;

        // Loop > Loop > (Standard > C Output)
        for (iterator; iterator != 7; iterator += 1) {
            for (subIterator = 0; subIterator != 6; subIterator += 1)
                std::cout << ((
                    (iterator == 0 && subIterator == 5) ||
                    ((iterator > 0 && iterator < 3) && (subIterator > 0 && subIterator < 5)) ||
                    (iterator == 3 && subIterator == 5) ||
                    ((iterator > 3 && iterator < 6) && (subIterator > 0 && subIterator < 5)) ||
                    (iterator == 6 && subIterator == 5)
                ) ? ' ' : '*');

            // Standard > C Output
            std::cout << std::endl;
        }

        // Return
        return 0;
    }
