/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities*/
    // Namespace > Standard
    using namespace std;

/* Global Data */
    // Index
    int index = 1;

/* Function */
    // Main
    int main() {
        /* Logic
                [if:else statement]
        */
        if (index != 6) {
            // Standard > C Output
            std::cout << index << ". Hello, from the Main Program" << std::endl;

            // Update > Index
            index += 1;

            // Main
            main();
        }

        else {
            // Standard > C Output
            std::cout << std::endl;

            /* Loop
                    [for statement]

                > Standard > C Output
            */
            for (int index = 0; index != 6; index += 1)
                std::cout << index << ". Hello, from the for Loop" << std::endl;
        }

        // Return
        return 0;
    }
