/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Function */
    // Even
    int even() {
        // Initialization > (Iterator, Sum)
        int iterator = 100, sum = 0;

        // Loop > Logic > Update > Sum
        while (iterator)
            if (!((iterator -= 1) % 2))
                sum += iterator;

        // Return
        return sum;
    }

    // Odd
    int odd() {
        // Initialization > (Iterator, Sum)
        int iterator = 100, sum = 0;

        // Loop > Logic > Update > Sum
        while (iterator)
            if ((iterator -= 1) % 2)
                sum += iterator;

        // Return
        return sum;
    }

    // Main
    int main() {
        // C Output
        cout << "Sum of even Numbers from 1 - 100: " << even() << endl;
        cout << "Sum of odd Numbers from 1 - 100: " << odd() << endl;
        cout << "\nSum of even & odd Numbers from 1 - 100: " << even() + odd();

        // Return
        return 0;
    }
