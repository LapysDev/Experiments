/* Library Files */
    // Input-Output Stream
    #include <iostream>

    // Lapys Header
    #include "lapys (2018 - Q4).h"

/* Utilization */
    // Namespace > Standard Library
    using namespace std;

// Function
    // Sum
    float sum(float numberA, float numberB) { return numberA + numberB; }
    int sum(int numberA, int numberB) { return numberA + numberB; };

    /* Main */
    int main() {
        print("2 + 3.5 = ", sum(2.0f, 3.5f));

        // Return
        return 0;
    }
