/* Library Files */
    // Input-Output Stream
    #include <iostream>

    // Lapys Header
    #include "lapys (2018 - Q4).h"

/* Utilization */
    // Namespace > Standard Library
    using namespace std;

// Function
    // Minimum
    Number min(Number numberA, Number numberB) {
        Number result = 0;

        if (numberA < numberB)
            result = numberA;

        else if (numberB < numberA)
            result = numberB;

        return result;
    };

    /* Main */
    int main() {
        Number numberA = 2, numberB = 3;
        print("Minimum of (", numberA, ", ", numberB, "): ", min(numberA, numberB));

        // Return
        return 0;
    }
