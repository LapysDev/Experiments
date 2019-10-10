/* Library Files */
    // Input-Output Stream
    #include <iostream>

    // Lapys Header
    #include "lapys (2018 - Q4).h"

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

// Function
    // Sum
    double sum(double parameters[3]) {
        // Initialization > Result
        double result = 0;

        // Loop > Update > Result
        for (int iterator = 0; iterator != 3; iterator += 1)
            result = result + parameters[iterator];

        // Return
        return result;
    };

    /* Main */
    int main() {
        // Initialization > Arguments
        double arguments[3] = {5, 4, 9};

        // Print
        print("Sum of 3 random numbers: ", sum(arguments));

        // Return
        return 0;
    }
