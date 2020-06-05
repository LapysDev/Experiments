/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities*/
    // Namespace > Standard
    using namespace std;

/* Function */
    // Main
    int main() {
        // Initialization > (Iterator, Sum)
        int iterator = 2,
            sum = 0;

        // Standard > C (Input, Output)
        cout << "Program to calculate the sum on an integer set:\n" << endl;
        cout << "Sum: ";

        /* Loop
                [for statement]
        */
        while (iterator < 100) {
            // Standard > C Output
            cout << iterator << (iterator > 100 - 4 ? "" : " + ");

            // Update > (Sum, Iterator)
            sum += iterator;
            iterator += 3;
        }

        // Standard > C Output
        cout << "\n    = " << sum;

        // Return
        return 0;
    }
