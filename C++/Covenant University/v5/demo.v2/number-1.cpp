/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Function */
    // Minimum Index
    int minIndex(float a[], int n);

    /* Main */
    int main() {
        // C Output
        cout << "Minimum Index of array [1, 0, 1]: " << minIndex(new float[3]{1, 0, 1}, 3);

        // Return
        return 0;
    }

    // Minimum Index
    int minIndex(float a[], int n) {
        // Initialization > (Minimum, Length)
        float minimum = a[0];
        int length = n;

        // Loop > Logic > Update > Minimum
        while (n)
            if (minimum > a[n -= 1])
                minimum = a[n];

        // Loop > Logic > Return
        for (n; n != length; n += 1)
            if (a[n] == minimum)
                return n;
    }
