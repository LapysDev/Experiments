/* Library Files */
    // Input-Output Stream
    #include <iostream>

    // Lapys Header
    #include "lapys (2018 - Q4).h"

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

// Function
    // Power
    double power(double x, int p) {
        // Initialization > Multiplier
        double multiplier = x;

        // Loop
        while (p != 0) {
            // Update > (...)
            x *= multiplier;
            p -= 1;
        }

        // Return
        return x;
    };

    /* Main */
    int main() {
        // Initialization > (...)
        double x = 5;
        int p = 2;

        // Print
        print("Power of (", x, ", ", p, "): ", pow(x, p));

        // Return
        return 0;
    }
