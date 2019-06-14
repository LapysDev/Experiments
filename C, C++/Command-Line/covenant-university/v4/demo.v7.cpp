/* Library Files */
    // Input-Output Stream
    #include <iostream>

    // Lapys Header
    #include "lapys (2018 - Q4).h"

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

// Function
    // Minimum Index
    int minIndex(float a[], int n);

    /* Main */
    int main() {
        // Initialization > (...)
        float a[5] = {5, 4, 3, 8, 6};

        // Standard Library > C Output
        cout << "The index of the first minimum value in the first 3 elements of the array [5, 4, 3, 8, 6] is: " << minIndex(a, 3);
    }

    // Minimum Index
    int minIndex(float a[], int n) {
        // Initialization > Length
        int length = n, min = a[n];

        // Loop
        while (n) {
            // Update > (...)
            n -= 1;

            // Logic > Update > Minimum
            if (a[n] < min)
                min = a[n];
        }

        // Loop
        while (length) {
            // Update > Length
            length -= 1;

            // Logic > Return
            if (a[length] == min)
                return length;
        }
    }
