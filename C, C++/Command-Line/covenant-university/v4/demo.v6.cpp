/* Library Files */
    // Input-Output Stream
    #include <iostream>

    // Lapys Header
    #include "lapys (2018 - Q4).h"

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

// Function
    /* Main */
    int main() {
        // Initialization > (N, Sum)
        int n, sum = 0;

        // Standard C (Output, Input)
        cout << "n: ";
        cin >> n;

        // Loop > Update > (Sum, Number)
        do {
            sum = sum + (n * n);
            n = n - 1;
        } while (n != 0);

        // Standard C Output
        cout << "sum: " << sum;

        // Return
        return 0;
    }
