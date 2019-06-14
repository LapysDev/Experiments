/* Library Files */
    // C Time
    #include <ctime>

    // Input-Output Stream
    #include <iostream>

/* Function */
    // Average
    double average(int integers[]) {
        // Initialization > (Average, Iterator, Length)
        double average = 0;
        int iterator = 0,
            length = sizeof(*integers);

        /* Loop
                Index Average.
        */
        for (iterator; iterator != length; iterator += 1)
            average += *(integers + iterator);

        // Return
        return average / length;
    };

    // Main
    int main(int argc, char* argv[]) {
        // Seed Random > Time
        std::srand(std::time(NULL));

        // Initialization > (Iterator, Length, Numbers)
        int iterator = 0,
            length = (std::rand() % 10) + 5,
            numbers[length];

        // Standard > C Output
        std::cout << "Program to calculate the average of a random set of integers:\n" << std::endl;
        std::cout << "Integers: ";

        /* Loop
                Index Numbers.
        */
        for (iterator; iterator != length; iterator += 1) {
            // Initialization > Random
            int random = ((std::rand() % 10) + 1) | 0;

            // Update > Numbers
            numbers[iterator] = random;

            // Standard > C Output
            std::cout << random << (iterator == length - 1 ? "" : ", ");
        }

        // Standard > C Output
        std::cout << std::endl;
        std::cout << "Average: " << average(numbers);

        // Return
        return 0;
    }
