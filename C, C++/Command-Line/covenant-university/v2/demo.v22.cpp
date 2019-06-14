/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to experiment with loops:\n" << std::endl;

        // Initialization > Counter
        int counter = 0;

        /* Loop
                [while statement]
        */
        while (counter < 5) {
            // Standard > C Output
            std::cout << "Counted to " << counter << " so far..." << std::endl;

            // Update > Counter
            counter += 1;
        }

        // Standard > C Output
        std::cout << std::endl;

        do {
            // Standard > C Output
            std::cout << "Counted regardless of condition..." << std::endl;
        } while (false);

        // Standard > C Output
        std::cout << std::endl;

        /* Loop
                [for statement]

            > Standard > C Output
        */
        for (
            int new_counter = 0;
            new_counter < 5;
            new_counter += 1
        )
            std::cout << "Counted to " << new_counter << " so far..." << std::endl;

        // Return
        return 0;
    }
