/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Function */
    // Main
    int main() {
        // Error Handling
        try {
            // C Output
            cout << "Throwing integer exception..." << endl;

            // Throw
            throw 1;
        } catch (int i) { cout << "The exception was caught, with the value: " << i << endl; }

        // Return
        return 0;
    }
