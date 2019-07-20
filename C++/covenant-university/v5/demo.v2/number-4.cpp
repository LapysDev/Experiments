/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Function */
    // Factorial
    long fact(int n);

    /* Main */
    int main() {
        // C Output
        cout << "Factorial of 5: " << fact(5);

        // Return
        return 0;
    }

    // Factorial
    long fact(int n) {
        // Initialization > (...)
        long f = n;

        // Loop > Update > (...)
        for (unsigned int i = 1; i != n; i += 1)
            f *= (long) i;

        // Return
        return f;
    }
