/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Function */
    // Main
    int main() {
        // Initialization > (Iterator, Length, Sum)
        int iterator = 0, length = 100;
        int sum = 0;

        // C Output
        cout << "for loop:\t";

        // Loop
        for (iterator; iterator != length; iterator += 1)
            // Logic
            if (!(iterator % 6)) {
                // Update > Sum
                sum += iterator;

                // C Output
                cout << iterator;

                // Logic > C Output
                if (iterator < length - 6) cout << " + ";
                else cout << " = " << sum;
            }

        // C Output
        cout << "\nwhile loop:\t";

        // Update > Sum
        sum = 0;

        // Loop
        while (iterator) {
            // Logic
            if (!(iterator % 6)) {
                // Update > Sum
                sum += iterator;

                // C Output
                cout << iterator;

                // Logic > C Output
                if (iterator > 6) cout << " + ";
                else cout << " = " << sum;
            }

            // Update > Iterator
            iterator -= 1;
        }

        // Return
        return 0;
    }
